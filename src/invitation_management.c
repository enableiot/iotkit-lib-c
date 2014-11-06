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

#include "invitation_management.h"

char *getListOfInvitation() {
    struct curl_slist *headers = NULL;
    char *url;
    HttpResponse *response = (HttpResponse *)malloc(sizeof(HttpResponse));
    response->code = 0;
    response->data = NULL;

    appendHttpHeader(&headers, HEADER_CONTENT_TYPE_NAME, HEADER_CONTENT_TYPE_JSON);
    appendHttpHeader(&headers, HEADER_AUTHORIZATION, getConfigAuthorizationToken());

    if(prepareUrl(&url, configurations.base_url, configurations.get_list_of_invitation, NULL)) {

        doHttpGet(url, headers, response);

        return createHttpResponseJson(response);
    }

    return NULL;
}

char *getInvitationListSendToSpecificUser(char *email_id) {
    struct curl_slist *headers = NULL;
    char *url;
    KeyValueParams *urlParams = NULL;
    HttpResponse *response = (HttpResponse *)malloc(sizeof(HttpResponse));
    response->code = 0;
    response->data = NULL;

    urlParams = (KeyValueParams *)malloc(sizeof(KeyValueParams));
    urlParams->name = "email_id";
    urlParams->value = strdup(email_id);
    urlParams->next = NULL;

    appendHttpHeader(&headers, HEADER_CONTENT_TYPE_NAME, HEADER_CONTENT_TYPE_JSON);
    appendHttpHeader(&headers, HEADER_AUTHORIZATION, getConfigAuthorizationToken());

    if(prepareUrl(&url, configurations.base_url, configurations.get_invitation_list_send_to_specific_user, urlParams)) {

        doHttpGet(url, headers, response);

        return createHttpResponseJson(response);
    }

    return NULL;
}

char *createInvitation(char *email) {
    struct curl_slist *headers = NULL;
    char *url;
    char body[BODY_SIZE_MIN];
    HttpResponse *response = (HttpResponse *)malloc(sizeof(HttpResponse));
    response->code = 0;
    response->data = NULL;

    if(!email) {
        fprintf(stderr, "createInvitation::email cannot be NULL");
        return NULL;
    }

    if(prepareUrl(&url, configurations.base_url, configurations.create_invitation, NULL)) {
        appendHttpHeader(&headers, HEADER_CONTENT_TYPE_NAME, HEADER_CONTENT_TYPE_JSON);
        appendHttpHeader(&headers, HEADER_AUTHORIZATION, getConfigAuthorizationToken());

        sprintf(body, "{\"email\":\"%s\"}", email);

        #if DEBUG
            printf("Prepared BODY is %s\n", body);
        #endif

        doHttpPost(url, headers, body, response);

        return createHttpResponseJson(response);
    }

    return NULL;
}

char *deleteInvitation(char *email_id) {
    struct curl_slist *headers = NULL;
    char *url;
    KeyValueParams *urlParams = NULL;
    HttpResponse *response = (HttpResponse *)malloc(sizeof(HttpResponse));
    response->code = 0;
    response->data = NULL;

    urlParams = (KeyValueParams *)malloc(sizeof(KeyValueParams));
    urlParams->name = "email_id";
    urlParams->value = strdup(email_id);
    urlParams->next = NULL;

    if(prepareUrl(&url, configurations.base_url, configurations.delete_invitations, urlParams)) {

        appendHttpHeader(&headers, HEADER_CONTENT_TYPE_NAME, HEADER_CONTENT_TYPE_JSON);
        appendHttpHeader(&headers, HEADER_AUTHORIZATION, getConfigAuthorizationToken());

        doHttpDelete(url, headers, response);

        return createHttpResponseJson(response);
    }

    return NULL;
}
