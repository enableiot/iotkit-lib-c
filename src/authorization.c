/*
 * Authorization API module to communicate with IoT Cloud via REST APIs
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
 * @file authorization.c
 * @brief Implementation of Authorization API
 *
 * Provides features for communication with IoT Cloud server
 */


#include "authorization.h"


char *getUserJwtToken(char *username, char *password) {
    struct curl_slist *headers = NULL;
    char *url;
    char body[BODY_SIZE_MIN];
    HttpResponse *response = (HttpResponse *)malloc(sizeof(HttpResponse));
    response->code = 0;
    response->data = NULL;

    if(!username) {
        fprintf(stderr, "Username cannot be NULL");
        return NULL;
    }

    if(!password) {
        fprintf(stderr, "Password cannot be NULL");
        return NULL;
    }


    if(prepareUrl(&url, configurations.base_url, configurations.new_auth_token, NULL)) {

        sprintf(body, "{\"username\":\"%s\",\"password\":\"%s\"}", username, password);

        appendHttpHeader(&headers, HEADER_CONTENT_TYPE_NAME, HEADER_CONTENT_TYPE_JSON);

        doHttpPost(url, headers, body, response);

        if(response->data) {
            storeAuthorizationToken(response->data);

            // if data account is already created using web portal
            if(configurations.data_account_id) {
                storeDataAccountIdInfo();
            }
        }

        return createHttpResponseJson(response);
    }

    return NULL;
}


char *getUserJwtTokenInfo() {
    struct curl_slist *headers = NULL;
    char *url;
    HttpResponse *response = (HttpResponse *)malloc(sizeof(HttpResponse));
    response->code = 0;
    response->data = NULL;

    appendHttpHeader(&headers, HEADER_CONTENT_TYPE_NAME, HEADER_CONTENT_TYPE_JSON);
    appendHttpHeader(&headers, HEADER_AUTHORIZATION, getConfigAuthorizationToken());

    if(prepareUrl(&url, configurations.base_url, configurations.auth_token_info, NULL)) {

        doHttpGet(url, headers, response);

        return createHttpResponseJson(response);
    }

    return NULL;
}


// Deprecated API
char *getAuthorizationTokenMeInfo() {
    struct curl_slist *headers = NULL;
    char *url;
    HttpResponse *response = (HttpResponse *)malloc(sizeof(HttpResponse));
    response->code = 0;
    response->data = NULL;

    appendHttpHeader(&headers, HEADER_CONTENT_TYPE_NAME, HEADER_CONTENT_TYPE_JSON);
    appendHttpHeader(&headers, HEADER_AUTHORIZATION, getConfigAuthorizationToken());

    if(prepareUrl(&url, configurations.base_url, configurations.me_info, NULL)) {

        doHttpGet(url, headers, response);

        return createHttpResponseJson(response);
    }

    return NULL;
}
