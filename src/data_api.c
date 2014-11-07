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

#include "data_api.h"

long getCurrentTimeInMillis() {
    struct timeval tv;
    long millis = -1L;
    if (gettimeofday(&tv, NULL) == 0) {
        millis = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
    }

    return millis;
}

char *submitData(char *cname, char *value, char *latitude, char *longitude, char *height) {
    struct curl_slist *headers = NULL;
    char *url;
    char body[BODY_SIZE_MED];
    char *cid = NULL;
    char currentTimeInMills[BODY_SIZE_MED];
    HttpResponse *response = (HttpResponse *)malloc(sizeof(HttpResponse));
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
        appendHttpHeader(&headers, HEADER_AUTHORIZATION, getDeviceAuthorizationToken());

        sprintf(currentTimeInMills, "%ld", getCurrentTimeInMillis());

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

RetrieveData *addDeviceId(RetrieveData *retrieveObj, char *id) {
    StringList *addId;

    addId = (StringList *)malloc(sizeof(StringList));
    addId->data = id;
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

RetrieveData *addSensorId(RetrieveData *retrieveObj, char *sensorName) {
    char *cid = NULL;
    StringList *addId;

    cid = getSensorComponentId(sensorName);

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

    return retrieveObj;
}

char *retrieveData(RetrieveData *retrieveObj) {
    struct curl_slist *headers = NULL;
    char *url;
    char body[BODY_SIZE_MED];
    char fromTimeInMillis[BODY_SIZE_MIN];
    char toTimeInMillis[BODY_SIZE_MIN];
    StringList *traverse = NULL;
    HttpResponse *response = (HttpResponse *)malloc(sizeof(HttpResponse));
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
        appendHttpHeader(&headers, HEADER_AUTHORIZATION, getConfigAuthorizationToken());

        sprintf(fromTimeInMillis, "%ld", retrieveObj->fromMillis);
        sprintf(toTimeInMillis, "%ld", retrieveObj->toMillis);

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
