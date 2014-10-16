/*
 * Data API module to communicate with IoT Cloud via REST APIs
 * Copyright (c) 2014, Intel Corporation.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU Lesser General Public License,
 * version 2.1, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for
 * more details.
 */

/**
 * @file data_api.c
 * @brief Implementation of Data API
 *
 * Provides features for communication with IoT Cloud server
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

bool submitData(char *cname, char *value, char *latitude, char *longitude, char *height, long *httpResponseCode, char **response) {
    struct curl_slist *headers = NULL;
    char *url;
    char body[BODY_SIZE_MED];
    char *cid = NULL;
    char currentTimeInMills[BODY_SIZE_MED];

    if(!cname) {
        fprintf(stderr, "submitData::Component Name cannot be NULL\n");
        return false;
    }

    cid = getSensorComponentId(cname);
    if(!cid) {
        fprintf(stderr, "submitData::Component is not registered\n");
        return false;
    }

    if(!value) {
        fprintf(stderr, "submitData::Value cannot be NULL\n");
        return false;
    }

    if(!configurations.data_account_id) {
        fprintf(stderr, "submitData::Account is NULL. Device appears to be unactivated\n");
        return false;
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

        doHttpPost(url, headers, body, httpResponseCode, response);

        return true;
    }

    return false;
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

bool retrieveData(RetrieveData *retrieveObj, long *httpResponseCode, char **response) {
    struct curl_slist *headers = NULL;
    char *url;
    char body[BODY_SIZE_MED];
    char fromTimeInMillis[BODY_SIZE_MIN];
    char toTimeInMillis[BODY_SIZE_MIN];
    StringList *traverse = NULL;

    if(!retrieveObj->deviceList) {
        fprintf(stderr, "retrieveData::Device ID cannot be NULL");
        return false;
    }

    if(!retrieveObj->componentId) {
        fprintf(stderr, "retrieveData::Component ID cannot be NULL");
        return false;
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

        doHttpPost(url, headers, body, httpResponseCode, response);

        return true;
    }

    return false;
}
