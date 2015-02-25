/*
 * Copyright (c) 2014 Intel Corporation.
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
 * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/**
 * @file data_api.c
 *
 * Provides API to handle Data Submit and Retrieve
 */

#include "data_api.h"

/**
 * @defgroup dataapi
 * This is Data API Module
 *  @{
 */

long getCurrentTimeInSeconds() {
    long elapsedtime = -1L;

    time(&elapsedtime);

    return elapsedtime;
}

/**
 * REST API to submit data along with sensor location
 *
 * @param cname specifies the component name
 * @param value specifies the value
 * @param latitide specifies the geo location - latitude of the measurement
 * @param longitude specifies the geo location - longitude of the measurement
 * @param height specifies the physical height of the component during the measurement
 * @return returns the result received from server, otherwise NULL
 */
char *submitDataWithLoc(char *cname, char *value, char *latitude, char *longitude, char *height) {
    struct curl_slist *headers = NULL;
    char *url;
    char body[BODY_SIZE_MED];
    char *cid = NULL;
    char currentTimeInMills[BODY_SIZE_MED];
    char *deviceAuthorizationHeader = (char *)getDeviceAuthorizationToken();
    HttpResponse *response = NULL;

    if(deviceAuthorizationHeader == NULL) {
        fprintf(stderr, "submitData::Device Authorization Token not available\n");
        return NULL;
    }

    response = (HttpResponse *)malloc(sizeof(HttpResponse));
    response->code = 0;
    response->data = NULL;

    if(!cname) {
        fprintf(stderr, "submitData::Component Name cannot be NULL\n");
        return NULL;
    }

    cid = getSensorComponentId(cname);
    if(!cid) {
        fprintf(stderr, "submitData::Component is not registered\n");
        return NULL;
    }

    if(!value) {
        fprintf(stderr, "submitData::Value cannot be NULL\n");
        return NULL;
    }

    if(!configurations.data_account_id) {
        fprintf(stderr, "submitData::Account is NULL. Device appears to be unactivated\n");
        return NULL;
    }

    if(prepareUrl(&url, configurations.base_url, configurations.submit_data, NULL)) {
        appendHttpHeader(&headers, HEADER_CONTENT_TYPE_NAME, HEADER_CONTENT_TYPE_JSON);
        appendHttpHeader(&headers, HEADER_AUTHORIZATION, deviceAuthorizationHeader);

        sprintf(currentTimeInMills, "%lld", (long long) getCurrentTimeInSeconds() * 1000L);

        strcpy(body, "{");
        strcat(body, "\"on\":");
        strcat(body, currentTimeInMills);
        strcat(body, ",\"accountId\":\"");
        strcat(body, configurations.data_account_id);
        strcat(body, "\",\"data\":[{\"componentId\":\"");
        strcat(body, cid);
        strcat(body, "\",\"on\":");
        strcat(body, currentTimeInMills);

        if(latitude != NULL && longitude != NULL) {
            strcat(body, ",\"loc\":[");

            strcat(body, latitude);
            strcat(body, ",");
            strcat(body, longitude);

            if(height) {
                strcat(body, ",");
                strcat(body, height);
            }
            strcat(body, "]");
        }

        strcat(body, ",\"value\":\"");
        strcat(body, value);
        strcat(body, "\"}]}");

        #if DEBUG
            printf("Prepared BODY is %s\n", body);
        #endif

        doHttpPost(url, headers, body, response);

        return createHttpResponseJson(response);
    }

    return NULL;
}

/**
 * REST API to submit data
 *
 * @param cname specifies the component name
 * @param value specifies the value
 * @return returns the result received from server, otherwise NULL
 */
char *submitData(char *cname, char *value) {
    if(!cname) {
        fprintf(stderr, "submitData::Component Name cannot be NULL\n");
        return NULL;
    }

    if(!value) {
        fprintf(stderr, "submitData::Value cannot be NULL\n");
        return NULL;
    }

    return submitDataWithLoc(cname, value, NULL, NULL, NULL);
}

/**
 * Creates an data object to be used to generate JSON Body in retrieve data REST call
 *
 * @param fromMillis specifies the timestamp in milliseconds from which data should be considered
 * @param toMillis specifies the timestamp in milliseconds till when the data should be considered
 * @return returns the created object if memory is available, otherwise NULL
 */
RetrieveData *createRetrieveDataObject(long fromMillis, long toMillis) {
    RetrieveData *retrieveObj = (RetrieveData *)malloc(sizeof(RetrieveData));
    if(!retrieveObj) {
        fprintf(stderr, "createRetrieveDataObject::Could not allocate memory\n");
        return NULL;
    }

    retrieveObj->fromMillis = fromMillis;
    retrieveObj->toMillis = toMillis;

    retrieveObj->componentId = NULL;
    retrieveObj->deviceList = NULL;

    return retrieveObj;
}

/**
 * add device ID. Can be called multiple times to add different device IDs
 *
 * @param retrieveObj the object created using createRetrieveDataObject()
 * @param id specifies the device ID
 */
RetrieveData *addDeviceId(RetrieveData *retrieveObj, char *id) {
    StringList *addId;

    addId = (StringList *)malloc(sizeof(StringList));
    addId->data = strdup(id);
    addId->next = NULL;

    if(!retrieveObj->deviceList) {
        retrieveObj->deviceList = addId;
    } else {
        StringList *traverseId = retrieveObj->deviceList;

        while(traverseId->next) {
            traverseId = traverseId->next;
        }
        traverseId->next = addId;
    }

    return retrieveObj;
}

/**
 * add sensor name. This API will replace the sensor name with its corresponding ID.
 * If sensor ID is already known, then please use addSensorId().
 * Can be called multiple times to add different sensor IDs
 *
 * @param retrieveObj the object created using createRetrieveDataObject()
 * @param sensorName specifies the sensor name
 */
RetrieveData *addSensorName(RetrieveData *retrieveObj, char *sensorName) {
    char *cid = NULL;
    StringList *addId;

    cid = getSensorComponentId(sensorName);

    return addSensorId(retrieveObj, cid);
}

/**
 * add sensor ID. Can be called multiple times to add different sensor IDs
 *
 * @param retrieveObj the object created using createRetrieveDataObject()
 * @param id specifies the sensor ID
 */
RetrieveData *addSensorId(RetrieveData *retrieveObj, char *id) {
    char *cid = NULL;
    StringList *addId;

    if(id != NULL) {
        cid = strdup(id);

        addId = (StringList *)malloc(sizeof(StringList));
        addId->data = cid;
        addId->next = NULL;

        if(!retrieveObj->componentId) {
            retrieveObj->componentId = addId;
        } else {
            StringList *traverseId = retrieveObj->componentId;

            while(traverseId->next) {
                traverseId = traverseId->next;
            }
            traverseId->next = addId;
        }
    }

    return retrieveObj;
}

/**
 * REST API to retrieve data
 *
 * @param retrieveObj the object created using createRetrieveDataObject()
 * @return returns the result received from server, otherwise NULL
 */
char *retrieveData(RetrieveData *retrieveObj) {
    struct curl_slist *headers = NULL;
    char *url;
    char body[BODY_SIZE_MED];
    char fromTimeInMillis[BODY_SIZE_MIN];
    char toTimeInMillis[BODY_SIZE_MIN];
    StringList *traverse = NULL;
    char *authorizationHeader = (char *)getConfigAuthorizationToken();
    HttpResponse *response = NULL;

    if(authorizationHeader == NULL) {
        fprintf(stderr, "retrieveData::Authorization Token not available\n");
        return NULL;
    }

    response = (HttpResponse *)malloc(sizeof(HttpResponse));
    response->code = 0;
    response->data = NULL;

    if(!retrieveObj->deviceList) {
        fprintf(stderr, "retrieveData::Device ID cannot be NULL");
        return NULL;
    }

    if(!retrieveObj->componentId) {
        fprintf(stderr, "retrieveData::Component ID cannot be NULL");
        return NULL;
    }

    if(prepareUrl(&url, configurations.base_url, configurations.retrieve_data, NULL)) {
        appendHttpHeader(&headers, HEADER_CONTENT_TYPE_NAME, HEADER_CONTENT_TYPE_JSON);
        appendHttpHeader(&headers, HEADER_AUTHORIZATION, authorizationHeader);

        sprintf(fromTimeInMillis, "%lld", (long long) retrieveObj->fromMillis * 1000L);
        sprintf(toTimeInMillis, "%lld", (long long) retrieveObj->toMillis * 1000L);

        strcpy(body, "{");
        strcat(body, "\"from\":");
        strcat(body, fromTimeInMillis);
        strcat(body, ",\"to\":");
        strcat(body, toTimeInMillis);
        strcat(body, ",\"targetFilter\":{\"deviceList\":[");

        traverse = retrieveObj->deviceList;
        while(traverse != NULL) {
            strcat(body, "\"");
            strcat(body, traverse->data);
            strcat(body, "\"");

            traverse = traverse->next;

            if(traverse) {
                strcat(body, ",");
            }
        }

        strcat(body, "]}");

        strcat(body, ",\"metrics\":[");

        traverse = retrieveObj->componentId;
        while(traverse != NULL) {
            strcat(body, "{\"id\":\"");
            strcat(body, traverse->data);
            strcat(body, "\",\"op\":\"none\"}");

            traverse = traverse->next;

            if(traverse) {
                strcat(body, ",");
            }
        }

        strcat(body, "]}");

        #if DEBUG
            printf("Prepared BODY is %s\n", body);
        #endif

        doHttpPost(url, headers, body, response);

        return createHttpResponseJson(response);
    }

    return NULL;
}

/**
 * REST API to retrieve data using device token instead of authorization token.
 * This is helpful when a device is activated directly using activation code from portal.
 *
 * @param retrieveObj the object created using createRetrieveDataObject()
 * @return returns the result received from server, otherwise NULL
 */
char *retrieveData2(RetrieveData *retrieveObj) {
    struct curl_slist *headers = NULL;
    char *url;
    char body[BODY_SIZE_MED];
    char fromTimeInMillis[BODY_SIZE_MIN];
    char toTimeInMillis[BODY_SIZE_MIN];
    StringList *traverse = NULL;
    char *deviceAuthorizationHeader = (char *)getDeviceAuthorizationToken();
    HttpResponse *response = NULL;

    if(deviceAuthorizationHeader == NULL) {
        fprintf(stderr, "retrieveData::Device Token not available\n");
        return NULL;
    }

    response = (HttpResponse *)malloc(sizeof(HttpResponse));
    response->code = 0;
    response->data = NULL;

    if(!retrieveObj->deviceList) {
        fprintf(stderr, "retrieveData::Device ID cannot be NULL");
        return NULL;
    }

    if(!retrieveObj->componentId) {
        fprintf(stderr, "retrieveData::Component ID cannot be NULL");
        return NULL;
    }

    if(prepareUrl(&url, configurations.base_url, configurations.retrieve_data, NULL)) {
        appendHttpHeader(&headers, HEADER_CONTENT_TYPE_NAME, HEADER_CONTENT_TYPE_JSON);
        appendHttpHeader(&headers, HEADER_AUTHORIZATION, deviceAuthorizationHeader);

        sprintf(fromTimeInMillis, "%lld", (long long) retrieveObj->fromMillis * 1000L);
        sprintf(toTimeInMillis, "%lld", (long long) retrieveObj->toMillis * 1000L);

        strcpy(body, "{");
        strcat(body, "\"from\":");
        strcat(body, fromTimeInMillis);
        strcat(body, ",\"to\":");
        strcat(body, toTimeInMillis);
        strcat(body, ",\"targetFilter\":{\"deviceList\":[");

        traverse = retrieveObj->deviceList;
        while(traverse != NULL) {
            strcat(body, "\"");
            strcat(body, traverse->data);
            strcat(body, "\"");

            traverse = traverse->next;

            if(traverse) {
                strcat(body, ",");
            }
        }

        strcat(body, "]}");

        strcat(body, ",\"metrics\":[");

        traverse = retrieveObj->componentId;
        while(traverse != NULL) {
            strcat(body, "{\"id\":\"");
            strcat(body, traverse->data);
            strcat(body, "\",\"op\":\"none\"}");

            traverse = traverse->next;

            if(traverse) {
                strcat(body, ",");
            }
        }

        strcat(body, "]}");

        #if DEBUG
            printf("Prepared BODY is %s\n", body);
        #endif

        doHttpPost(url, headers, body, response);

        return createHttpResponseJson(response);
    }

    return NULL;
}

/** @} */ // end of dataapi
