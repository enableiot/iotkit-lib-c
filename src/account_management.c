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

bool createAnAccount(char *account_name) {
    struct curl_slist *headers = NULL;
    char *url;
    char body[BODY_SIZE_MIN];

    if(!account_name) {
        fprintf(stderr, "createAnAccount::Account name cannot be NULL");
        return false;
    }

    prepareUrl(&url, configurations.base_url, configurations.create_an_account);

    appendHttpHeader(&headers, HEADER_CONTENT_TYPE_NAME, HEADER_CONTENT_TYPE_JSON);
    appendHttpHeader(&headers, HEADER_AUTHORIZATION, getConfigAuthorizationToken());

    sprintf(body, "{\"name\":\"%s\"}", account_name);

    doHttpPost(url, headers, body);

    return true;
}

bool getAccountInformation() { // TODO: this should taken data account id as a parameter
    struct curl_slist *headers = NULL;
    char *url;

    appendHttpHeader(&headers, HEADER_CONTENT_TYPE_NAME, HEADER_CONTENT_TYPE_JSON);
    appendHttpHeader(&headers, HEADER_AUTHORIZATION, getConfigAuthorizationToken());

    prepareUrl(&url, configurations.base_url, configurations.get_account_information);

    doHttpGet(url, headers);

    return true;
}

bool getAccountActivationCode() { // TODO: this should taken data account id as a parameter
    struct curl_slist *headers = NULL;
    char *url;

    appendHttpHeader(&headers, HEADER_CONTENT_TYPE_NAME, HEADER_CONTENT_TYPE_JSON);
    appendHttpHeader(&headers, HEADER_AUTHORIZATION, getConfigAuthorizationToken());

    prepareUrl(&url, configurations.base_url, configurations.get_account_activation_code);

    doHttpGet(url, headers);

    return true;
}


bool renewActivationCode() {
    struct curl_slist *headers = NULL;
    char *url;

    prepareUrl(&url, configurations.base_url, configurations.renew_account_activation);

    appendHttpHeader(&headers, HEADER_CONTENT_TYPE_NAME, HEADER_CONTENT_TYPE_JSON);
    appendHttpHeader(&headers, HEADER_AUTHORIZATION, getConfigAuthorizationToken());

    // TODO: GET THE NEW ACTIVATION CODE AND STORE IT IN CONFIG FILE
    doHttpPut(url, headers, NULL);

    return true;
}

bool updateAnAccount(char *account_name) {
    struct curl_slist *headers = NULL;
    char *url;
    char body[BODY_SIZE_MIN];

    prepareUrl(&url, configurations.base_url, configurations.update_an_account_name);

    appendHttpHeader(&headers, HEADER_CONTENT_TYPE_NAME, HEADER_CONTENT_TYPE_JSON);
    appendHttpHeader(&headers, HEADER_AUTHORIZATION, getConfigAuthorizationToken());

    sprintf(body, "{\"name\":\"%s\"}", account_name);
    // TODO: GET THE NEW ACTIVATION CODE AND STORE IT IN CONFIG FILE

    doHttpPut(url, headers, body);

    return true;
}

bool deleteAnAccount() {
    struct curl_slist *headers = NULL;
    char *url;

    prepareUrl(&url, configurations.base_url, configurations.delete_an_account_name);

    appendHttpHeader(&headers, HEADER_CONTENT_TYPE_NAME, HEADER_CONTENT_TYPE_JSON);
    appendHttpHeader(&headers, HEADER_AUTHORIZATION, getConfigAuthorizationToken());

    // TODO: GET THE NEW ACTIVATION CODE AND STORE IT IN CONFIG FILE

    doHttpDelete(url, headers);

    return true;
}
