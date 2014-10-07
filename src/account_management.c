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

bool createAnAccount(char *account_name, long *httpResponseCode, char **response) {
    struct curl_slist *headers = NULL;
    char *url;
    char body[BODY_SIZE_MIN];

    if(!account_name) {
        fprintf(stderr, "createAnAccount::Account name cannot be NULL");
        return false;
    }

    if(prepareUrl(&url, configurations.base_url, configurations.create_an_account, NULL)) {
        appendHttpHeader(&headers, HEADER_CONTENT_TYPE_NAME, HEADER_CONTENT_TYPE_JSON);
        appendHttpHeader(&headers, HEADER_AUTHORIZATION, getConfigAuthorizationToken());

        sprintf(body, "{\"name\":\"%s\"}", account_name);

        doHttpPost(url, headers, body, httpResponseCode, response);

        return true;
    }

    return false;
}

bool getAccountInformation(long *httpResponseCode, char **response) {
    struct curl_slist *headers = NULL;
    char *url;

    appendHttpHeader(&headers, HEADER_CONTENT_TYPE_NAME, HEADER_CONTENT_TYPE_JSON);
    appendHttpHeader(&headers, HEADER_AUTHORIZATION, getConfigAuthorizationToken());

    if(prepareUrl(&url, configurations.base_url, configurations.get_account_information, NULL)){
        doHttpGet(url, headers, httpResponseCode, response);

        return true;
    }

    return false;
}

bool getAccountActivationCode(long *httpResponseCode, char **response) {
    struct curl_slist *headers = NULL;
    char *url;

    appendHttpHeader(&headers, HEADER_CONTENT_TYPE_NAME, HEADER_CONTENT_TYPE_JSON);
    appendHttpHeader(&headers, HEADER_AUTHORIZATION, getConfigAuthorizationToken());

    if(prepareUrl(&url, configurations.base_url, configurations.get_account_activation_code, NULL)) {

        doHttpGet(url, headers, httpResponseCode, response);

        return true;
    }

    return false;
}


bool renewActivationCode(long *httpResponseCode, char **response) {
    struct curl_slist *headers = NULL;
    char *url;

    if(prepareUrl(&url, configurations.base_url, configurations.renew_account_activation, NULL)) {

        appendHttpHeader(&headers, HEADER_CONTENT_TYPE_NAME, HEADER_CONTENT_TYPE_JSON);
        appendHttpHeader(&headers, HEADER_AUTHORIZATION, getConfigAuthorizationToken());

        doHttpPut(url, headers, NULL, httpResponseCode, response);

        return true;
    }

    return false;
}

bool updateAnAccount(char *account_name, long *httpResponseCode, char **response) {
    struct curl_slist *headers = NULL;
    char *url;
    char body[BODY_SIZE_MIN];
    // TODO: json object needs to be sent for updation
    if(prepareUrl(&url, configurations.base_url, configurations.update_an_account_name, NULL)) {

        appendHttpHeader(&headers, HEADER_CONTENT_TYPE_NAME, HEADER_CONTENT_TYPE_JSON);
        appendHttpHeader(&headers, HEADER_AUTHORIZATION, getConfigAuthorizationToken());

        sprintf(body, "{\"name\":\"%s\"}", account_name);

        doHttpPut(url, headers, body, httpResponseCode, response);

        return true;
    }

    return false;
}

bool deleteAnAccount(long *httpResponseCode, char **response) {
    struct curl_slist *headers = NULL;
    char *url;

    if(prepareUrl(&url, configurations.base_url, configurations.delete_an_account_name, NULL)) {

        appendHttpHeader(&headers, HEADER_CONTENT_TYPE_NAME, HEADER_CONTENT_TYPE_JSON);
        appendHttpHeader(&headers, HEADER_AUTHORIZATION, getConfigAuthorizationToken());

        doHttpDelete(url, headers, httpResponseCode);

        if(httpResponseCode == 204) {
            // delete successful, perform cleanup
        }

        return true;
    }

    return false;
}

bool getUserAssociatedWithAccount(long *httpResponseCode, char **response) {
    struct curl_slist *headers = NULL;
    char *url;

    appendHttpHeader(&headers, HEADER_AUTHORIZATION, getConfigAuthorizationToken());

    if(prepareUrl(&url, configurations.base_url, configurations.get_user_associated_with_account, NULL)) {

        doHttpGet(url, headers, httpResponseCode, response);

        return true;
    }

    return false;
}
