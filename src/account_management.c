/*
 * Account Management API module to communicate with IoT Cloud via REST APIs
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
 * @file account_management.c
 * @brief Implementation of Account Management API
 *
 * Provides features for communication with IoT Cloud server
 */

#include "account_management.h"

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

bool addAnUserToAccount(char *account_id, char * user_id, bool isAdmin, long *httpResponseCode, char **response) {
// TODO: to be verified
    struct curl_slist *headers = NULL;
    char *url;
    char body[BODY_SIZE_MIN];
    KeyValueParams *urlParams = NULL;

    urlParams = (KeyValueParams *)malloc(sizeof(KeyValueParams));
    urlParams->name = "user_id";
    urlParams->value = strdup(user_id);
    urlParams->next = NULL;

    if(prepareUrl(&url, configurations.base_url, configurations.add_an_user_to_account, urlParams)) {

        appendHttpHeader(&headers, HEADER_CONTENT_TYPE_NAME, HEADER_CONTENT_TYPE_JSON);
        appendHttpHeader(&headers, HEADER_AUTHORIZATION, getConfigAuthorizationToken());

        if(isAdmin) {
            sprintf(body, "{\"accounts\":{\"%s\":\"%s\"}}", account_id, "admin");
        } else {
            sprintf(body, "{\"accounts\":{\"%s\":\"%s\"}}", account_id, "user");
        }

        #if DEBUG
            printf("Prepared BODY is %s\n", body);
        #endif

        doHttpPut(url, headers, body, httpResponseCode, response);

        return true;
    }

    return false;
}

/*
UpdateUserAccount *createUpdateUserAccountObject() {
    UpdateUserAccount *newObject = (UpdateUserAccount *)malloc(sizeof(UpdateUserAccount));

    if(!newObject) {
        return NULL;
    }

    newObject->attributes = NULL;
    newObject->email = NULL;
    newObject->termsAndConditions = false;
    newObject->verified = false;
}

UpdateUserAccount *addUpdateUserAccountAttributes(UpdateUserAccount *updateUserAccount, char *name, char *value) {
    KeyValueParams *newParam = (KeyValueParams *)malloc(sizeof(KeyValueParams));

    newParam->name = name;
    newParam->value = value;
    newParam->next = NULL;

    if(!updateUserAccount->attributes) {
        updateUserAccount->attributes = newParam;
    } else {
        KeyValueParams *traverse = updateUserAccount->attributes;

        while(traverse->next != NULL) {
            traverse = traverse->next;
        }

        traverse->next = newParam;
    }

    return updateUserAccount;
}

UpdateUserAccount *addUpdateUserAccountEmail(UpdateUserAccount *updateUserAccount, char *email) {
    updateUserAccount->email = email;

    return updateUserAccount;
}

UpdateUserAccount *addUpdateUserAccountTerms(UpdateUserAccount *updateUserAccount, bool terms) {
    updateUserAccount->termsAndConditions = terms;

    return updateUserAccount;
}

UpdateUserAccount *addUpdateUserAccountVerified(UpdateUserAccount *updateUserAccount, bool verified) {
    updateUserAccount->verified = verified;

    return updateUserAccount;
}

bool updateUserAssociatedWithAccount(UpdateUserAccount *updateUserAccount, long *httpResponseCode, char **response) {
    struct curl_slist *headers = NULL;
    char *url;
    char body[BODY_SIZE_MED];
    KeyValueParams *traverse = updateUserAccount->attributes;

    appendHttpHeader(&headers, HEADER_AUTHORIZATION, getConfigAuthorizationToken());

    if(prepareUrl(&url, configurations.base_url, configurations.update_user_associated_with_account, NULL)) {

        strcpy(body, "{");

        strcat(body, "\"id\":\"");
        strcat(body, configurations.data_account_id);
        strcat(body, "\",");

        strcat(body, "\"accounts\":{\"");
        strcat(body, configurations.data_account_id);
        strcat(body, "\":\"admin\"},");

        strcat(body, "\"attributes\":{");
        while(traverse) {
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
        strcat(body, "},");

        if(updateUserAccount->email) {
            strcat(body, "\"email\":\"");
            strcat(body, updateUserAccount->email);
            strcat(body, "\",");
        }

        strcat(body, "\"termsAndConditions\":\"");
        if(updateUserAccount->termsAndConditions) {
            strcat(body, "true");
        } else {
            strcat(body, "false");
        }
        strcat(body, "\",");

        strcat(body, "\"verified\":");
        if(updateUserAccount->verified) {
            strcat(body, "true");
        } else {
            strcat(body, "false");
        }

        strcat(body, "}");

        #if DEBUG
            printf("Prepared BODY is %s\n", body);
        #endif

        doHttpPut(url, headers, body, httpResponseCode, response);

        return true;
    }

    return false;
}
*/
