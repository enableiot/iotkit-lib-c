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

#include "account_management.h"

char *createAnAccount(char *account_name) {
    struct curl_slist *headers = NULL;
    char *url;
    char body[BODY_SIZE_MIN];
    HttpResponse *response = (HttpResponse *)malloc(sizeof(HttpResponse));
    response->code = 0;
    response->data = NULL;

    if(!account_name) {
        fprintf(stderr, "createAnAccount::Account name cannot be NULL");
        return NULL;
    }

    if(prepareUrl(&url, configurations.base_url, configurations.create_an_account, NULL)) {
        appendHttpHeader(&headers, HEADER_CONTENT_TYPE_NAME, HEADER_CONTENT_TYPE_JSON);
        appendHttpHeader(&headers, HEADER_AUTHORIZATION, getConfigAuthorizationToken());

        sprintf(body, "{\"name\":\"%s\"}", account_name);

        doHttpPost(url, headers, body, response);

        if(response->data) {
            storeAccountInfo(response->data);
        }

        return createHttpResponseJson(response);
    }

    return NULL;
}

char *getAccountInformation() {
    struct curl_slist *headers = NULL;
    char *url;
    HttpResponse *response = (HttpResponse *)malloc(sizeof(HttpResponse));
    response->code = 0;
    response->data = NULL;

    appendHttpHeader(&headers, HEADER_CONTENT_TYPE_NAME, HEADER_CONTENT_TYPE_JSON);
    appendHttpHeader(&headers, HEADER_AUTHORIZATION, getConfigAuthorizationToken());

    if(prepareUrl(&url, configurations.base_url, configurations.get_account_information, NULL)){
        doHttpGet(url, headers, response);

        return createHttpResponseJson(response);
    }

    return NULL;
}

char *getAccountActivationCode() {
    struct curl_slist *headers = NULL;
    char *url;
    HttpResponse *response = (HttpResponse *)malloc(sizeof(HttpResponse));
    response->code = 0;
    response->data = NULL;

    appendHttpHeader(&headers, HEADER_CONTENT_TYPE_NAME, HEADER_CONTENT_TYPE_JSON);
    appendHttpHeader(&headers, HEADER_AUTHORIZATION, getConfigAuthorizationToken());

    if(prepareUrl(&url, configurations.base_url, configurations.get_account_activation_code, NULL)) {

        doHttpGet(url, headers, response);

        return createHttpResponseJson(response);
    }

    return NULL;
}


char *renewActivationCode() {
    struct curl_slist *headers = NULL;
    char *url;
    HttpResponse *response = (HttpResponse *)malloc(sizeof(HttpResponse));
    response->code = 0;
    response->data = NULL;

    if(prepareUrl(&url, configurations.base_url, configurations.renew_account_activation, NULL)) {

        appendHttpHeader(&headers, HEADER_CONTENT_TYPE_NAME, HEADER_CONTENT_TYPE_JSON);
        appendHttpHeader(&headers, HEADER_AUTHORIZATION, getConfigAuthorizationToken());

        doHttpPut(url, headers, NULL, response);

        return createHttpResponseJson(response);
    }

    return NULL;
}

char *updateAnAccount(char *account_name) {
    struct curl_slist *headers = NULL;
    char *url;
    char body[BODY_SIZE_MIN];
    HttpResponse *response = (HttpResponse *)malloc(sizeof(HttpResponse));
    response->code = 0;
    response->data = NULL;

    // TODO: json object needs to be sent for updation
    if(prepareUrl(&url, configurations.base_url, configurations.update_an_account_name, NULL)) {

        appendHttpHeader(&headers, HEADER_CONTENT_TYPE_NAME, HEADER_CONTENT_TYPE_JSON);
        appendHttpHeader(&headers, HEADER_AUTHORIZATION, getConfigAuthorizationToken());

        sprintf(body, "{\"name\":\"%s\"}", account_name);

        doHttpPut(url, headers, body, response);

        return createHttpResponseJson(response);
    }

    return NULL;
}

char *deleteAnAccount() {
    struct curl_slist *headers = NULL;
    char *url;
    HttpResponse *response = (HttpResponse *)malloc(sizeof(HttpResponse));
    response->code = 0;
    response->data = NULL;

    if(prepareUrl(&url, configurations.base_url, configurations.delete_an_account_name, NULL)) {

        appendHttpHeader(&headers, HEADER_CONTENT_TYPE_NAME, HEADER_CONTENT_TYPE_JSON);
        appendHttpHeader(&headers, HEADER_AUTHORIZATION, getConfigAuthorizationToken());

        doHttpDelete(url, headers, response);

        if(response->code == 204) {
            // delete successful, perform cleanup
        }

        return createHttpResponseJson(response);
    }

    return NULL;
}

char *getUserAssociatedWithAccount() {
    struct curl_slist *headers = NULL;
    char *url;
    HttpResponse *response = (HttpResponse *)malloc(sizeof(HttpResponse));
    response->code = 0;
    response->data = NULL;

    appendHttpHeader(&headers, HEADER_AUTHORIZATION, getConfigAuthorizationToken());

    if(prepareUrl(&url, configurations.base_url, configurations.get_user_associated_with_account, NULL)) {

        doHttpGet(url, headers, response);

        return createHttpResponseJson(response);
    }

    return NULL;
}

char *addAnUserToAccount(char *account_id, char * user_id, bool isAdmin) {
// TODO: to be verified
    struct curl_slist *headers = NULL;
    char *url;
    char body[BODY_SIZE_MIN];
    KeyValueParams *urlParams = NULL;
    HttpResponse *response = (HttpResponse *)malloc(sizeof(HttpResponse));
    response->code = 0;
    response->data = NULL;

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

        doHttpPut(url, headers, body, response);

        return createHttpResponseJson(response);
    }

    return NULL;
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
