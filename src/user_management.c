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

bool updateUserAttributes(char *userId, KeyValueParams *attributes, long *httpResponseCode, char **response) {
    struct curl_slist *headers = NULL;
    char *url;
    char body[BODY_SIZE_MED];
    KeyValueParams *urlParams = NULL;

    if(!attributes) {
        fprintf(stderr, "updateUserAttributes::Parameter attribute list cannot be NULL");
        return false;
    }

    urlParams = (KeyValueParams *)malloc(sizeof(KeyValueParams));
    urlParams->name = "user_id";
    if(userId) {
        urlParams->value = strdup(userId);
    } else {
        urlParams->value = strdup(configurations.user_account_id);
    }
    urlParams->next = NULL;

    if(prepareUrl(&url, configurations.base_url, configurations.update_user_attributes, urlParams)) {
        KeyValueParams *traverse = attributes;

        appendHttpHeader(&headers, HEADER_CONTENT_TYPE_NAME, HEADER_CONTENT_TYPE_JSON);
        appendHttpHeader(&headers, HEADER_AUTHORIZATION, getConfigAuthorizationToken());

        strcpy(body, "{\"attributes\":{");
        while(traverse != NULL) {
            strcat(body, "\"");
            strcat(body, traverse->name);
            strcat(body, "\":\"");
            strcat(body, traverse->value);
            strcat(body, "\"");

            traverse = traverse->next;

            if(traverse) {
                strcat(body, ",");
            }
        }
        strcat(body, "}}");

        #if DEBUG
            printf("Prepared BODY is %s\n", body);
        #endif

        doHttpPut(url, headers, body, httpResponseCode, response);

        return true;
    }

    return false;
}

bool acceptTermsAndConditions(char *userId, bool accept, long *httpResponseCode, char **response) {
    struct curl_slist *headers = NULL;
    char *url;
    char body[BODY_SIZE_MIN];
    KeyValueParams *urlParams = NULL;

    urlParams = (KeyValueParams *)malloc(sizeof(KeyValueParams));
    urlParams->name = "user_id";
    if(userId) {
        urlParams->value = strdup(userId);
    } else {
        urlParams->value = strdup(configurations.user_account_id);
    }
    urlParams->next = NULL;

    if(prepareUrl(&url, configurations.base_url, configurations.accept_terms_and_conditions, urlParams)) {

        appendHttpHeader(&headers, HEADER_CONTENT_TYPE_NAME, HEADER_CONTENT_TYPE_JSON);
        appendHttpHeader(&headers, HEADER_AUTHORIZATION, getConfigAuthorizationToken());

        if(accept == true) {
            sprintf(body, "{\"termsAndConditions\":true}");
        } else {
            sprintf(body, "{\"termsAndConditions\":false}");
        }

        #if DEBUG
            printf("Prepared BODY is %s\n", body);
        #endif

        doHttpPut(url, headers, body, httpResponseCode, response);

        return true;
    }

    return false;
}

bool requestChangePassword(char *emailAddress, long *httpResponseCode, char **response) {
    struct curl_slist *headers = NULL;
    char *url;
    char body[BODY_SIZE_MIN];

    if(!emailAddress) {
        fprintf(stderr, "requestChangePassword::Parameter email address cannot be NULL");
        return false;
    }

    if(prepareUrl(&url, configurations.base_url, configurations.request_change_password, NULL)) {
        appendHttpHeader(&headers, HEADER_CONTENT_TYPE_NAME, HEADER_CONTENT_TYPE_JSON);
        appendHttpHeader(&headers, HEADER_AUTHORIZATION, getConfigAuthorizationToken());

        sprintf(body, "{\"email\":\"%s\"}", emailAddress);

        #if DEBUG
            printf("Prepared BODY is %s\n", body);
        #endif

        doHttpPost(url, headers, body, httpResponseCode, response);

        return true;
    }

    return false;
}

bool updateForgotPassword(char *token, char *new_password, long *httpResponseCode, char **response) {
    struct curl_slist *headers = NULL;
    char *url;
    char body[BODY_SIZE_MIN];

    if(!token || !new_password) {
        fprintf(stderr, "updateForgotPassword::Mandatory parameters cannot be NULL");
        return false;
    }

    if(prepareUrl(&url, configurations.base_url, configurations.request_change_password, NULL)) {
        appendHttpHeader(&headers, HEADER_CONTENT_TYPE_NAME, HEADER_CONTENT_TYPE_JSON);
        appendHttpHeader(&headers, HEADER_AUTHORIZATION, getConfigAuthorizationToken());

        sprintf(body, "{\"token\":\"%s\",\"password\":\"%s\"}", token, new_password);

        #if DEBUG
            printf("Prepared BODY is %s\n", body);
        #endif

        doHttpPut(url, headers, body, httpResponseCode, response);

        return true;
    }

    return false;
}

bool changePassword(char *emailAddress, char *current_password, char *new_password, long *httpResponseCode, char **response) {
    struct curl_slist *headers = NULL;
    char *url;
    char body[BODY_SIZE_MIN];
    KeyValueParams *urlParams = NULL;

    urlParams = (KeyValueParams *)malloc(sizeof(KeyValueParams));
    urlParams->name = "email_id";
    urlParams->value = strdup(emailAddress);
    urlParams->next = NULL;

    if(!emailAddress || !current_password || !new_password) {
        fprintf(stderr, "changePassword::Mandatory parameters cannot be NULL");
        return false;
    }

    if(prepareUrl(&url, configurations.base_url, configurations.change_password, urlParams)) {
        appendHttpHeader(&headers, HEADER_CONTENT_TYPE_NAME, HEADER_CONTENT_TYPE_JSON);
        appendHttpHeader(&headers, HEADER_AUTHORIZATION, getConfigAuthorizationToken());

        sprintf(body, "{\"currentpwd\":\"%s\",\"password\":\"%s\"}", current_password, new_password);

        #if DEBUG
            printf("Prepared BODY is %s\n", body);
        #endif

        doHttpPut(url, headers, body, httpResponseCode, response);

        return true;
    }

    return false;
}
