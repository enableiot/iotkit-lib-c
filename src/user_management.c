/*
 * User Management module to communicate with IoT Cloud via REST APIs
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
 * @file user_management.c
 * @brief Implementation of User Management
 *
 * Provides features for communication with IoT Cloud server
 */

#include "iotkit.h"

bool createAnUser(char *emailAddress, char *password, long *httpResponseCode, char **response) {
    struct curl_slist *headers = NULL;
    char *url;
    char body[BODY_SIZE_MIN];

    if(!emailAddress || !password) {
        fprintf(stderr, "createAnUser::Mandatory parameters cannot be NULL");
        return false;
    }

    if(prepareUrl(&url, configurations.base_url, configurations.create_a_user, NULL)) {
        appendHttpHeader(&headers, HEADER_CONTENT_TYPE_NAME, HEADER_CONTENT_TYPE_JSON);
//        appendHttpHeader(&headers, HEADER_AUTHORIZATION, getConfigAuthorizationToken());

        sprintf(body, "{\"email\":\"%s\",\"password\":\"%s\"}", emailAddress, password);

        #if DEBUG
            printf("Prepared BODY is %s\n", body);
        #endif

        doHttpPost(url, headers, body, httpResponseCode, response);

        return true;
    }

    return false;
}

bool getUserInformation(char *userId, long *httpResponseCode, char **response) {
    struct curl_slist *headers = NULL;
    char *url;
    KeyValueParams *urlParams = NULL;

    urlParams = (KeyValueParams *)malloc(sizeof(KeyValueParams));
    urlParams->name = "user_id";
    if(userId) {
        urlParams->value = strdup(userId);
    } else {
        urlParams->value = strdup(configurations.user_account_id);
    }
    urlParams->next = NULL;

    appendHttpHeader(&headers, HEADER_CONTENT_TYPE_NAME, HEADER_CONTENT_TYPE_JSON);
    appendHttpHeader(&headers, HEADER_AUTHORIZATION, getConfigAuthorizationToken());

    if(prepareUrl(&url, configurations.base_url, configurations.get_user_information, urlParams)) {
        doHttpGet(url, headers, httpResponseCode, response);

        return true;
    }

    return false;
}
