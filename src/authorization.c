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
 * @file authorization.c
 *
 * Provides API to handle Alert Management
 */

#include "authorization.h"

/**
 * @defgroup authorization
 * This is Authorization Module
 *  @{
 */

/**
 * REST API to get user JWT token
 *
 * @param username specifies the username
 * @param password specifies the password
 * @return returns the result received from server, otherwise NULL
 */
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

/**
 * REST API to get user JWT token information
 *
 * @return returns the result received from server, otherwise NULL
 */
char *getUserJwtTokenInfo() {
    struct curl_slist *headers = NULL;
    char *url;
    char *authorizationHeader = (char *)getConfigAuthorizationToken();
    HttpResponse *response = NULL;

    if(authorizationHeader == NULL) {
        fprintf(stderr, "getUserJwtTokenInfo::Authorization Token not available\n");
        return NULL;
    }

    response = (HttpResponse *)malloc(sizeof(HttpResponse));
    response->code = 0;
    response->data = NULL;

    appendHttpHeader(&headers, HEADER_CONTENT_TYPE_NAME, HEADER_CONTENT_TYPE_JSON);
    appendHttpHeader(&headers, HEADER_AUTHORIZATION, authorizationHeader);

    if(prepareUrl(&url, configurations.base_url, configurations.auth_token_info, NULL)) {

        doHttpGet(url, headers, response);

        return createHttpResponseJson(response);
    }

    return NULL;
}

/* Deprecated API
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
} */

/** @} */ // end of authorization