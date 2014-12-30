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
 * @file account_management.c
 *
 * Provides APIs to handle Accounts and User related operations
 */

#include "account_management.h"

/**
 * @defgroup accountmanagement
 * This is Account Management Module
 *  @{
 */

/**
 * REST API to create an Account under the user and stores the account ID in 'device_config.json'
 *
 * @param account_name an character pointer
 * @return returns the result received from server, otherwise NULL
 */
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

/**
 * REST API to retrieve the Account information
 *
 * @return returns the result received from server, otherwise NULL
 */
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

/**
 * REST API to retrieve the Account Activation code if valid
 *
 * @return returns the result containing the activation code received from server, otherwise NULL
 */
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

/**
 * REST API to force the renewal of the Account Activation code
 *
 * @return returns the result containing the activation code received from server, otherwise NULL
 */
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

/**
 * Create Update User Account Object
 *
 * @param new_name an character pointer representing new account name
 * @return returns the object created if successful, otherwise NULL
 */
UpdateUserAccount *createUpdateUserAccountObject(char *new_name) {
    UpdateUserAccount *newObject = (UpdateUserAccount *)malloc(sizeof(UpdateUserAccount));

    if(!newObject) {
        return NULL;
    }

    newObject->new_name = strdup(new_name);

    // assign default values
    newObject->attributes = NULL;
    newObject->healthTimePeriod = 86400;
    newObject->exec_interval = 120;
    newObject->base_line_exec_interval = 86400;
    newObject->cd_model_frequency = 604800;
    newObject->cd_execution_frequency = 600;
    newObject->data_retention = 0;

    return newObject;
}

/**
 * set Update User Account attributes
 *
 * @param updateUserAccount representing Update User Account Object
 * @param attributes list of key value pairs
 */
void setUpdateAccountAttributes(UpdateUserAccount *updateUserAccount, KeyValueParams *attributes) {
    updateUserAccount->attributes = attributes;
}

/**
 * set Update User Account health time period
 *
 * @param updateUserAccount representing Update User Account Object
 * @param healthTimePeriod value of health time period
 */
void setUpdateAccountHealthTimePeriod(UpdateUserAccount *updateUserAccount, int healthTimePeriod) {
    updateUserAccount->healthTimePeriod = healthTimePeriod;
}

/**
 * set Update User Account execution interval
 *
 * @param updateUserAccount representing Update User Account Object
 * @param exec_interval value of execution interval
 */
void setUpdateAccountExecInterval(UpdateUserAccount *updateUserAccount, int exec_interval) {
    updateUserAccount->exec_interval = exec_interval;
}

/**
 * set Update User Account base line execution interval
 *
 * @param updateUserAccount representing Update User Account Object
 * @param base_line_exec_interval value of base line execution interval
 */
void setUpdateAccountBaseLineExecInterval(UpdateUserAccount *updateUserAccount, int base_line_exec_interval) {
    updateUserAccount->base_line_exec_interval = base_line_exec_interval;
}

/**
 * set Update User Account cd model frequency
 *
 * @param updateUserAccount representing Update User Account Object
 * @param cd_model_frequency value of cd_model_frequency
 */
void setUpdateAccountCdModelFrequency(UpdateUserAccount *updateUserAccount, int cd_model_frequency) {
    updateUserAccount->cd_model_frequency = cd_model_frequency;
}

/**
 * set Update User Account cd execution frequency
 *
 * @param updateUserAccount representing Update User Account Object
 * @param cd_execution_frequency value of cd_execution_frequency
 */
void setUpdateAccountCdExecutionFrequency(UpdateUserAccount *updateUserAccount, int cd_execution_frequency) {
    updateUserAccount->cd_execution_frequency = cd_execution_frequency;
}

/**
 * set Update User Account Data Retention
 *
 * @param updateUserAccount representing Update User Account Object
 * @param data_retention value of data_retention
 */
void setUpdateAccountDataRetention(UpdateUserAccount *updateUserAccount, int data_retention) {
    updateUserAccount->data_retention = data_retention;
}

/**
 * REST API to update an Account properties under the user
 *
 * @param account_name an character pointer
 * @return returns the result received from server, otherwise NULL
 */
char *updateAnAccount(UpdateUserAccount *updateUserAccount) {
    struct curl_slist *headers = NULL;
    char *url;
    char body[BODY_SIZE_MIN];
    char  uuid_str[38];
    HttpResponse *response = (HttpResponse *)malloc(sizeof(HttpResponse));
    response->code = 0;
    response->data = NULL;

    if(prepareUrl(&url, configurations.base_url, configurations.update_an_account_name, NULL)) {

        // generate UUID
        get_uuid_string(uuid_str,sizeof(uuid_str));

        appendHttpHeader(&headers, HEADER_CONTENT_TYPE_NAME, HEADER_CONTENT_TYPE_JSON);
        appendHttpHeader(&headers, HEADER_AUTHORIZATION, getConfigAuthorizationToken());

        sprintf(body, "{\"name\":\"%s\",\"healthTimePeriod\":%d,\"exec_interval\":%d,\"base_line_exec_interval\":%d"
        ",\"cd_model_frequency\":%d,\"cd_execution_frequency\":%d,\"data_retention\":%d",
        updateUserAccount->new_name, updateUserAccount->healthTimePeriod, updateUserAccount->exec_interval, \
        updateUserAccount->base_line_exec_interval, updateUserAccount->cd_model_frequency, updateUserAccount->cd_execution_frequency, updateUserAccount->data_retention);

        strcat(body, ",\"attributes\":{");

        if(updateUserAccount->attributes) {
            KeyValueParams *traverseKeyValues = updateUserAccount->attributes;

            while(traverseKeyValues != NULL) {

                strcat(body, "\"");
                strcat(body, traverseKeyValues->name);
                strcat(body, "\":\"");
                strcat(body, traverseKeyValues->value);
                strcat(body, "\"");

                traverseKeyValues = traverseKeyValues->next;

                if(traverseKeyValues) {
                    strcat(body, ",");
                }
            }
        }

        strcat(body, "}");
        strcat(body, ", \"id\":\"");
        strcat(body, configurations.data_account_id);
        strcat(body, "\"");
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
 * REST API to delete an Account under the user
 *
 * @return returns the result received from server, otherwise NULL
 */
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

/**
 * REST API to retrieve the user information associated with an Account
 *
 * @return returns the result received from server, otherwise NULL
 */
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

/**
 * REST API to add another user to Account under the current user
 *
 * @param account_id an character pointer
 * @param user_id user to be added to the account
 * @param isAdmin 'true' specifies the new user should be provided with admin privilege otherwise normal user privilege
 * @return returns the result received from server, otherwise NULL
 */
char *addAnUserToAccount(char *account_id, char * user_id, bool isAdmin) {
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

        sprintf(body, "{\"id\":\"%s\",\"accounts\":{\"", user_id);
        if(account_id) {
            strcat(body, account_id);
        } else {
            strcat(body, configurations.data_account_id);
        }

        strcat(body, "\":\"");

        if(isAdmin) {
            strcat(body, "admin");
        } else {
            strcat(body, "user");
        }

        strcat(body, "\"}}");

        #if DEBUG
            printf("Prepared BODY is %s\n", body);
        #endif

        doHttpPut(url, headers, body, response);

        return createHttpResponseJson(response);
    }

    return NULL;
}

/** @} */ // end of accountmanagement
