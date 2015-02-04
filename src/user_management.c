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
 * @file user_management.c
 *
 * Provides API to handle User Management
 */

#include "user_management.h"

/**
 * @defgroup usermanagement
 * This is User Management Module
 *  @{
 */

/**
 * REST API to create an user
 *
 * @param emailAddress specifies the username (email address) for the user
 * @param password specifies the password for the user
 * @return returns the result received from server, otherwise NULL
 */
char *createAnUser(char *emailAddress, char *password, bool acceptTermsAndConditions) {
    struct curl_slist *headers = NULL;
    char *url;
    char body[BODY_SIZE_MIN];
    HttpResponse *response = (HttpResponse *)malloc(sizeof(HttpResponse));
    response->code = 0;
    response->data = NULL;

    if(!emailAddress || !password) {
        fprintf(stderr, "createAnUser::Mandatory parameters cannot be NULL");
        return NULL;
    }

    if(prepareUrl(&url, configurations.base_url, configurations.create_a_user, NULL)) {
        appendHttpHeader(&headers, HEADER_CONTENT_TYPE_NAME, HEADER_CONTENT_TYPE_JSON);

        sprintf(body, "{\"email\":\"%s\",\"password\":\"%s\",", emailAddress, password);

        if(acceptTermsAndConditions) {
            strcat(body, "\"termsAndConditions\": true");
        } else {
            strcat(body, "\"termsAndConditions\": false");
        }

        strcat(body, "}");

        #if DEBUG
            printf("Prepared BODY is %s\n", body);
        #endif

        doHttpPost(url, headers, body, response);

        return createHttpResponseJson(response);
    }

    return NULL;
}

/**
 * REST API to get information for a specific user
 *
 * @param user_id specifies the user ID
 * @return returns the result received from server, otherwise NULL
 */
char *getUserInformation(char *userId) {
    struct curl_slist *headers = NULL;
    char *url;
    KeyValueParams *urlParams = NULL;
    char *authorizationHeader = (char *)getConfigAuthorizationToken();
    HttpResponse *response = NULL;

    if(authorizationHeader == NULL) {
        fprintf(stderr, "getUserInformation::Authorization Token not available\n");
        return NULL;
    }

    response = (HttpResponse *)malloc(sizeof(HttpResponse));
    response->code = 0;
    response->data = NULL;

    urlParams = (KeyValueParams *)malloc(sizeof(KeyValueParams));
    urlParams->name = "user_id";
    if(userId) {
        urlParams->value = strdup(userId);
    } else {
        urlParams->value = strdup(configurations.user_account_id);
    }
    urlParams->next = NULL;

    appendHttpHeader(&headers, HEADER_CONTENT_TYPE_NAME, HEADER_CONTENT_TYPE_JSON);
    appendHttpHeader(&headers, HEADER_AUTHORIZATION, authorizationHeader);

    if(prepareUrl(&url, configurations.base_url, configurations.get_user_information, urlParams)) {
        doHttpGet(url, headers, response);

        return createHttpResponseJson(response);
    }

    return NULL;
}

/**
 * REST API to update user attributes
 *
 * @param user_id specifies the user ID
 * @param attributes specifies the user attributes
 * @return returns the result received from server, otherwise NULL
 */
char *updateUserAttributes(char *userId, KeyValueParams *attributes) {
    struct curl_slist *headers = NULL;
    char *url;
    char body[BODY_SIZE_MED];
    KeyValueParams *urlParams = NULL;
    char *authorizationHeader = (char *)getConfigAuthorizationToken();
    HttpResponse *response = NULL;

    if(authorizationHeader == NULL) {
        fprintf(stderr, "updateUserAttributes::Authorization Token not available\n");
        return NULL;
    }

    response = (HttpResponse *)malloc(sizeof(HttpResponse));
    response->code = 0;
    response->data = NULL;

    if(!attributes) {
        fprintf(stderr, "updateUserAttributes::Parameter attribute list cannot be NULL");
        return NULL;
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
        appendHttpHeader(&headers, HEADER_AUTHORIZATION, authorizationHeader);

        strcpy(body, "{\"id\":\"");
        if(userId) {
            strcat(body, userId);
        } else {
            strcat(body, configurations.user_account_id);
        }
        strcat(body, "\",\"attributes\":{");
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

        doHttpPut(url, headers, body, response);

        return createHttpResponseJson(response);
    }

    return NULL;
}

/**
 * REST API to accept terms and conditions
 *
 * @param user_id specifies the user ID
 * @param accept 'true' to accept, 'false' to decline
 * @return returns the result received from server, otherwise NULL
 */
char *acceptTermsAndConditions(char *userId, bool accept) {
    struct curl_slist *headers = NULL;
    char *url;
    char body[BODY_SIZE_MIN];
    KeyValueParams *urlParams = NULL;
    char *authorizationHeader = (char *)getConfigAuthorizationToken();
    HttpResponse *response = NULL;

    if(authorizationHeader == NULL) {
        fprintf(stderr, "acceptTermsAndConditions::Authorization Token not available\n");
        return NULL;
    }

    response = (HttpResponse *)malloc(sizeof(HttpResponse));
    response->code = 0;
    response->data = NULL;

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
        appendHttpHeader(&headers, HEADER_AUTHORIZATION, authorizationHeader);

        strcpy(body, "{\"id\":\"");
        if(userId) {
            strcat(body, userId);
        } else {
            strcat(body, configurations.user_account_id);
        }
        strcat(body, "\",\"termsAndConditions\":");

        if(accept == true) {
            strcat(body, "true");
        } else {
            strcat(body, "false");
        }
        strcat(body, "}");

        #if DEBUG
            printf("Prepared BODY is %s\n", body);
        #endif

        doHttpPut(url, headers, body, response);

        return createHttpResponseJson(response);
    }

    return NULL;
}

/**
 * REST API to delete a user
 *
 * @param user_id specifies the user ID
 * @return returns the result received from server, otherwise NULL
 */
char *deleteAUser(char *userId) {
    struct curl_slist *headers = NULL;
    char *url;
    KeyValueParams *urlParams = NULL;
    char *authorizationHeader = (char *)getConfigAuthorizationToken();
    HttpResponse *response = NULL;

    if(authorizationHeader == NULL) {
        fprintf(stderr, "deleteAUser::Authorization Token not available\n");
        return NULL;
    }

    response = (HttpResponse *)malloc(sizeof(HttpResponse));
    response->code = 0;
    response->data = NULL;

    urlParams = (KeyValueParams *)malloc(sizeof(KeyValueParams));
    urlParams->name = "user_id";
    if(userId) {
        urlParams->value = strdup(userId);
    } else {
        urlParams->value = strdup(configurations.user_account_id);
    }
    urlParams->next = NULL;

    if(prepareUrl(&url, configurations.base_url, configurations.delete_a_user, urlParams)) {

        appendHttpHeader(&headers, HEADER_CONTENT_TYPE_NAME, HEADER_CONTENT_TYPE_JSON);
        appendHttpHeader(&headers, HEADER_AUTHORIZATION, authorizationHeader);

        doHttpDelete(url, headers, response);

        return createHttpResponseJson(response);
    }

    return NULL;
}

/**
 * REST API to initiate request for a change of password process
 *
 * @param emailAddress specifies the username of the user
 * @return returns the result received from server, otherwise NULL
 */
char *requestChangePassword(char *emailAddress) {
    struct curl_slist *headers = NULL;
    char *url;
    char body[BODY_SIZE_MIN];
    char *authorizationHeader = (char *)getConfigAuthorizationToken();
    HttpResponse *response = NULL;

    if(authorizationHeader == NULL) {
        fprintf(stderr, "requestChangePassword::Authorization Token not available\n");
        return NULL;
    }

    response = (HttpResponse *)malloc(sizeof(HttpResponse));
    response->code = 0;
    response->data = NULL;

    if(!emailAddress) {
        fprintf(stderr, "requestChangePassword::Parameter email address cannot be NULL");
        return false;
    }

    if(prepareUrl(&url, configurations.base_url, configurations.request_change_password, NULL)) {
        appendHttpHeader(&headers, HEADER_CONTENT_TYPE_NAME, HEADER_CONTENT_TYPE_JSON);
        appendHttpHeader(&headers, HEADER_AUTHORIZATION, authorizationHeader);

        sprintf(body, "{\"email\":\"%s\"}", emailAddress);

        #if DEBUG
            printf("Prepared BODY is %s\n", body);
        #endif

        doHttpPost(url, headers, body, response);

        return createHttpResponseJson(response);
    }

    return NULL;
}

/**
 * REST API to update forgot password
 *
 * @param token specifies the token received by email to reset password
 * @param new_password specifies the new password
 * @return returns the result received from server, otherwise NULL
 */
char *updateForgotPassword(char *token, char *new_password) {
    struct curl_slist *headers = NULL;
    char *url;
    char body[BODY_SIZE_MIN];
    char *authorizationHeader = (char *)getConfigAuthorizationToken();
    HttpResponse *response = NULL;

    if(authorizationHeader == NULL) {
        fprintf(stderr, "updateForgotPassword::Authorization Token not available\n");
        return NULL;
    }

    response = (HttpResponse *)malloc(sizeof(HttpResponse));
    response->code = 0;
    response->data = NULL;

    if(!token || !new_password) {
        fprintf(stderr, "updateForgotPassword::Mandatory parameters cannot be NULL");
        return NULL;
    }

    if(prepareUrl(&url, configurations.base_url, configurations.request_change_password, NULL)) {
        appendHttpHeader(&headers, HEADER_CONTENT_TYPE_NAME, HEADER_CONTENT_TYPE_JSON);
        appendHttpHeader(&headers, HEADER_AUTHORIZATION, authorizationHeader);

        sprintf(body, "{\"token\":\"%s\",\"password\":\"%s\"}", token, new_password);

        #if DEBUG
            printf("Prepared BODY is %s\n", body);
        #endif

        doHttpPut(url, headers, body, response);

        return createHttpResponseJson(response);
    }

    return NULL;
}

/**
 * REST API to change an user password
 *
 * @param emailAddress specifies the username of the user
 * @param current_password specifies the current password
 * @param new_password specifies the new password
 * @return returns the result received from server, otherwise NULL
 */
char *changePassword(char *emailAddress, char *current_password, char *new_password) {
    struct curl_slist *headers = NULL;
    char *url;
    char body[BODY_SIZE_MIN];
    KeyValueParams *urlParams = NULL;
    char *authorizationHeader = (char *)getConfigAuthorizationToken();
    HttpResponse *response = NULL;

    if(authorizationHeader == NULL) {
        fprintf(stderr, "changePassword::Authorization Token not available\n");
        return NULL;
    }

    response = (HttpResponse *)malloc(sizeof(HttpResponse));
    response->code = 0;
    response->data = NULL;

    urlParams = (KeyValueParams *)malloc(sizeof(KeyValueParams));
    urlParams->name = "email_id";
    urlParams->value = strdup(emailAddress);
    urlParams->next = NULL;

    if(!emailAddress || !current_password || !new_password) {
        fprintf(stderr, "changePassword::Mandatory parameters cannot be NULL");
        return NULL;
    }

    if(prepareUrl(&url, configurations.base_url, configurations.change_password, urlParams)) {
        appendHttpHeader(&headers, HEADER_CONTENT_TYPE_NAME, HEADER_CONTENT_TYPE_JSON);
        appendHttpHeader(&headers, HEADER_AUTHORIZATION, authorizationHeader);

        sprintf(body, "{\"currentpwd\":\"%s\",\"password\":\"%s\"}", current_password, new_password);

        #if DEBUG
            printf("Prepared BODY is %s\n", body);
        #endif

        doHttpPut(url, headers, body, response);

        return createHttpResponseJson(response);
    }

    return NULL;
}

/** @} */ // end of usermanagement
