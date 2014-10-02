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

#include "iotkit.h"

char *createAnAccount(char *account_name) {
    struct curl_slist *headers = NULL;
    char *url;
    char body[BODY_SIZE_MIN];
    char *response = NULL;

    if(!account_name) {
        fprintf(stderr, "createAnAccount::Account name cannot be NULL");
        return NULL;
    }

    if(prepareUrl(&url, configurations.base_url, configurations.create_an_account, NULL)) {
        appendHttpHeader(&headers, HEADER_CONTENT_TYPE_NAME, HEADER_CONTENT_TYPE_JSON);
        appendHttpHeader(&headers, HEADER_AUTHORIZATION, getConfigAuthorizationToken());

        sprintf(body, "{\"name\":\"%s\"}", account_name);

        doHttpPost(url, headers, body, &response);

        return response;
    }

    return NULL;
}

char *getAccountInformation() {
    struct curl_slist *headers = NULL;
    char *url;
    char *response = NULL;

    appendHttpHeader(&headers, HEADER_CONTENT_TYPE_NAME, HEADER_CONTENT_TYPE_JSON);
    appendHttpHeader(&headers, HEADER_AUTHORIZATION, getConfigAuthorizationToken());

    if(prepareUrl(&url, configurations.base_url, configurations.get_account_information, NULL)){
        doHttpGet(url, headers, &response);

        return response;
    }

    return NULL;
}

char *getAccountActivationCode() {
    struct curl_slist *headers = NULL;
    char *url;
    char *response = NULL;

    appendHttpHeader(&headers, HEADER_CONTENT_TYPE_NAME, HEADER_CONTENT_TYPE_JSON);
    appendHttpHeader(&headers, HEADER_AUTHORIZATION, getConfigAuthorizationToken());

    if(prepareUrl(&url, configurations.base_url, configurations.get_account_activation_code, NULL)) {

        doHttpGet(url, headers, &response);

        return response;
    }

    return NULL;
}


char *renewActivationCode() {
    struct curl_slist *headers = NULL;
    char *url;
    char *response = NULL;

    if(prepareUrl(&url, configurations.base_url, configurations.renew_account_activation, NULL)) {

        appendHttpHeader(&headers, HEADER_CONTENT_TYPE_NAME, HEADER_CONTENT_TYPE_JSON);
        appendHttpHeader(&headers, HEADER_AUTHORIZATION, getConfigAuthorizationToken());

        doHttpPut(url, headers, NULL, &response);

        return response;
    }

    return NULL;
}

char *updateAnAccount(char *account_name) {
    struct curl_slist *headers = NULL;
    char *url;
    char body[BODY_SIZE_MIN];
    char *response = NULL;

    if(prepareUrl(&url, configurations.base_url, configurations.update_an_account_name, NULL)) {

        appendHttpHeader(&headers, HEADER_CONTENT_TYPE_NAME, HEADER_CONTENT_TYPE_JSON);
        appendHttpHeader(&headers, HEADER_AUTHORIZATION, getConfigAuthorizationToken());

        sprintf(body, "{\"name\":\"%s\"}", account_name);

        doHttpPut(url, headers, body, &response);

        return response;
    }

    return NULL;
}

char *deleteAnAccount() {
    struct curl_slist *headers = NULL;
    char *url;
    char *response = NULL;
    long httpResponseCode = 0;

    if(prepareUrl(&url, configurations.base_url, configurations.delete_an_account_name, NULL)) {

        appendHttpHeader(&headers, HEADER_CONTENT_TYPE_NAME, HEADER_CONTENT_TYPE_JSON);
        appendHttpHeader(&headers, HEADER_AUTHORIZATION, getConfigAuthorizationToken());

        doHttpDelete(url, headers, &httpResponseCode);

        if(httpResponseCode == 204) {
            // delete successful, perform cleanup
        }

        return response;
    }

    return NULL;
}
