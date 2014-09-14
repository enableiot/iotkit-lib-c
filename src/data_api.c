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

#include "iotkit.h"
#include <sys/time.h>

long getCurrentTimeInMillis() {
    struct timeval tv;
    long millis = -1L;
    if (gettimeofday(&tv, NULL) == 0) {
        millis = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
    }

    return millis;
}

char *submitData(char *cid, char *value) {
// TODO: TODO: pass sensor name instead of cid as argument and later lookup for its cid
// TODO: TODO: TODO: Support location info
    struct curl_slist *headers = NULL;
    char *url;
    char body[BODY_SIZE_MED];
    char *response = NULL;
    char currentTimeInMills[BODY_SIZE_MED];

    if(!cid) {
        fprintf(stderr, "submitData::Component ID cannot be NULL");
        return NULL;
    }

    if(!value) {
        fprintf(stderr, "submitData::Value cannot be NULL");
        return NULL;
    }

    if(!configurations.data_account_id) {
        fprintf(stderr, "submitData::Account is NULL. Device appears to be unactivated");
        return NULL;
    }

    if(prepareUrl(&url, configurations.base_url, configurations.submit_data)) {
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
        strcat(body, ",\"value\":\"");
        strcat(body, value);
        strcat(body, "\"}]}");

        #if DEBUG
            printf("Prepared BODY is %s\n", body);
        #endif

        doHttpPost(url, headers, body, &response);

        return response;
    }

    return NULL;
}

char *retrieveData(long fromMillis, long toMillis, char *deviceId, char *componentId) {
// TODO: TODO: should be able to retrieve data from multiple devices
// TODO: TODO: should be able to retrieve data for multiple sensor components
    struct curl_slist *headers = NULL;
    char *url;
    char body[BODY_SIZE_MED];
    char *response = NULL;
    char fromTimeInMillis[BODY_SIZE_MIN];
    char toTimeInMillis[BODY_SIZE_MIN];

    if(!deviceId) {
        fprintf(stderr, "retrieveData::Device ID cannot be NULL");
        return NULL;
    }

    if(!componentId) {
        fprintf(stderr, "retrieveData::Component ID cannot be NULL");
        return NULL;
    }

    if(prepareUrl(&url, configurations.base_url, configurations.retrieve_data)) {
        appendHttpHeader(&headers, HEADER_CONTENT_TYPE_NAME, HEADER_CONTENT_TYPE_JSON);
        appendHttpHeader(&headers, HEADER_AUTHORIZATION, getConfigAuthorizationToken());

        sprintf(fromTimeInMillis, "%ld", fromMillis);
        sprintf(toTimeInMillis, "%ld", toMillis);

        strcpy(body, "{");
        strcat(body, "\"from\":");
        strcat(body, fromTimeInMillis);
        strcat(body, ",\"to\":");
        strcat(body, toTimeInMillis);
        strcat(body, ",\"targetFilter\":{\"deviceList\":[\"");
        strcat(body, deviceId);
        strcat(body, "\"]},\"metrics\":[{\"id\":\"");
        strcat(body, componentId);
        strcat(body, "\",\"op\":\"none\"");
        strcat(body, "}]}");

        #if DEBUG
            printf("Prepared BODY is %s\n", body);
        #endif

        doHttpPost(url, headers, body, &response);

        return response;
    }

    return NULL;
}
