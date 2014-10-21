/*
 * Invitation Management API module to communicate with IoT Cloud via REST APIs
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
 * @file invitation_management.c
 * @brief Implementation of Invitation Management API
 *
 * Provides features for communication with IoT Cloud server
 */

#include "iotkit.h"

bool getListOfInvitation(long *httpResponseCode, char **response) {
    struct curl_slist *headers = NULL;
    char *url;

    appendHttpHeader(&headers, HEADER_CONTENT_TYPE_NAME, HEADER_CONTENT_TYPE_JSON);
    appendHttpHeader(&headers, HEADER_AUTHORIZATION, getDeviceAuthorizationToken());

    if(prepareUrl(&url, configurations.base_url, configurations.get_list_of_invitation, NULL)) {

        doHttpGet(url, headers, httpResponseCode, response);

        return true;
    }

    return false;
}

bool getInvitationListSendToSpecificUser(char *email_id, long *httpResponseCode, char **response) {
    struct curl_slist *headers = NULL;
    char *url;
    KeyValueParams *urlParams = NULL;

    urlParams = (KeyValueParams *)malloc(sizeof(KeyValueParams));
    urlParams->name = "email_id";
    urlParams->value = strdup(email_id);
    urlParams->next = NULL;

    appendHttpHeader(&headers, HEADER_CONTENT_TYPE_NAME, HEADER_CONTENT_TYPE_JSON);
    appendHttpHeader(&headers, HEADER_AUTHORIZATION, getDeviceAuthorizationToken());

    if(prepareUrl(&url, configurations.base_url, configurations.get_invitation_list_send_to_specific_user, urlParams)) {

        doHttpGet(url, headers, httpResponseCode, response);

        return true;
    }

    return false;
}

bool createInvitation(char *email, long *httpResponseCode, char **response) {
    struct curl_slist *headers = NULL;
    char *url;
    char body[BODY_SIZE_MIN];

    if(!email) {
        fprintf(stderr, "createInvitation::email cannot be NULL");
        return false;
    }

    if(prepareUrl(&url, configurations.base_url, configurations.create_invitation, NULL)) {
        appendHttpHeader(&headers, HEADER_CONTENT_TYPE_NAME, HEADER_CONTENT_TYPE_JSON);
        appendHttpHeader(&headers, HEADER_AUTHORIZATION, getConfigAuthorizationToken());

        sprintf(body, "{\"email\":\"%s\"}", email);

        #if DEBUG
            printf("Prepared BODY is %s\n", body);
        #endif

        doHttpPost(url, headers, body, httpResponseCode, response);

        return true;
    }

    return false;
}

bool deleteInvitation(char *email_id, long *httpResponseCode, char **response) {
    struct curl_slist *headers = NULL;
    char *url;
    KeyValueParams *urlParams = NULL;

    urlParams = (KeyValueParams *)malloc(sizeof(KeyValueParams));
    urlParams->name = "email_id";
    urlParams->value = strdup(email_id);
    urlParams->next = NULL;

    if(prepareUrl(&url, configurations.base_url, configurations.delete_invitations, urlParams)) {

        appendHttpHeader(&headers, HEADER_CONTENT_TYPE_NAME, HEADER_CONTENT_TYPE_JSON);
        appendHttpHeader(&headers, HEADER_AUTHORIZATION, getConfigAuthorizationToken());

        doHttpDelete(url, headers, httpResponseCode, response);

        return true;
    }

    return false;
}
