/*
 * Device Management API module to communicate with IoT Cloud via REST APIs
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
 * @file device_management.c
 * @brief Implementation of Device Management API
 *
 * Provides features for communication with IoT Cloud server
 */

#include "iotkit.h"

char *validateDeviceToken() {
    struct curl_slist *headers = NULL;
    char *url;
    char *response = NULL;

    appendHttpHeader(&headers, HEADER_CONTENT_TYPE_NAME, HEADER_CONTENT_TYPE_JSON);
    appendHttpHeader(&headers, HEADER_AUTHORIZATION, getDeviceAuthorizationToken());

    if(prepareUrl(&url, configurations.base_url, configurations.auth_token_info)) {

        doHttpGet(url, headers, &response);

        // TODO: store the account id in the config.json file

        return response;
    }

    return NULL;
}

char *listAllDevices() {
    struct curl_slist *headers = NULL;
    char *url;
    char *response = NULL;

    appendHttpHeader(&headers, HEADER_CONTENT_TYPE_NAME, HEADER_CONTENT_TYPE_JSON);
    appendHttpHeader(&headers, HEADER_AUTHORIZATION, getConfigAuthorizationToken());

    if(prepareUrl(&url, configurations.base_url, configurations.list_all_devices)){
        doHttpGet(url, headers, &response);

        return response;
    }

    return NULL;
}

char *getMyDeviceInfo() {
    struct curl_slist *headers = NULL;
    char *url;
    char *response = NULL;

    appendHttpHeader(&headers, HEADER_CONTENT_TYPE_NAME, HEADER_CONTENT_TYPE_JSON);
    appendHttpHeader(&headers, HEADER_AUTHORIZATION, getDeviceAuthorizationToken());

    if(prepareUrl(&url, configurations.base_url, configurations.get_device_info)){
        doHttpGet(url, headers, &response);

        return response;
    }

    return NULL;
}

char *getOneDeviceInfo() {
    struct curl_slist *headers = NULL;
    char *url;
    char *response = NULL;

    appendHttpHeader(&headers, HEADER_CONTENT_TYPE_NAME, HEADER_CONTENT_TYPE_JSON);
    appendHttpHeader(&headers, HEADER_AUTHORIZATION, getConfigAuthorizationToken());

    if(prepareUrl(&url, configurations.base_url, configurations.get_device_info)){
        doHttpGet(url, headers, &response);

        return response;
    }

    return NULL;
}

char *createADevice(char *device_id, char *gateway_id, char *device_name) {
// TODO: TODO: TODO: Support for tags, loc and attributes while creating a device
    struct curl_slist *headers = NULL;
    char *url;
    char body[BODY_SIZE_MED];
    char *response = NULL;

    if(!device_id) {
        fprintf(stderr, "createADevice::Device ID cannot be NULL");
        return NULL;
    }

    if(!gateway_id) {
        fprintf(stderr, "createADevice::Gateway ID cannot be NULL");
        return NULL;
    }

    if(!device_name) {
        fprintf(stderr, "createADevice::Device Name cannot be NULL");
        return NULL;
    }

    if(prepareUrl(&url, configurations.base_url, configurations.create_a_device)) {
        appendHttpHeader(&headers, HEADER_CONTENT_TYPE_NAME, HEADER_CONTENT_TYPE_JSON);
        appendHttpHeader(&headers, HEADER_AUTHORIZATION, getConfigAuthorizationToken());

        sprintf(body, "{\"deviceId\":\"%s\",\"gatewayId\":\"%s\",\"name\":\"%s\"}", device_id, gateway_id, device_name);

        doHttpPost(url, headers, body, &response);

        storeDeviceID(response);

        return response;
    }

    return NULL;
}

char *updateADevice(char *device_id, char *gateway_id, char *device_name) {

// TODO: TODO: TODO: This does not support tags, loc and attributes while updating a device

    struct curl_slist *headers = NULL;
    char *url;
    char body[BODY_SIZE_MED];
    char *response = NULL;
    bool isCommaRequired = false;

    if(!device_id) {
        fprintf(stderr, "updateADevice::Device ID cannot be NULL");
        return NULL;
    }

    if(prepareUrl(&url, configurations.base_url, configurations.update_a_device)) {
        appendHttpHeader(&headers, HEADER_CONTENT_TYPE_NAME, HEADER_CONTENT_TYPE_JSON);
        appendHttpHeader(&headers, HEADER_AUTHORIZATION, getConfigAuthorizationToken());

        strcpy(body, "{");

        if(gateway_id != NULL) {
            strcat(body, "\"gatewayId\":\"");
            strcat(body, gateway_id);
            strcat(body, "\"");
            isCommaRequired = true;
        }

        if(device_name != NULL) {
            if(isCommaRequired) {
                strcat(body, ",");
            }
            strcat(body, "\"name\":\"");
            strcat(body, device_name);
            strcat(body, "\"");
            isCommaRequired = true;
        }

        strcat(body, "}");

        #if DEBUG
            printf("Prepared BODY is %s\n", body);
        #endif

        doHttpPut(url, headers, body, &response);

        return response;
    }

    return NULL;
}

char *activateADevice(char *activation_code) {
    struct curl_slist *headers = NULL;
    char *url;
    char body[BODY_SIZE_MED];
    char *response = NULL;

    if(configurations.deviceToken) {
        fprintf(stderr, "activateADevice::Device appears to be already activated. Could not proceed\n");
        return NULL;
    }

    if(!activation_code) {
        fprintf(stderr, "activateADevice::Activation Code cannot be NULL");
        return NULL;
    }

    if(prepareUrl(&url, configurations.base_url, configurations.activate_a_device)) {
        appendHttpHeader(&headers, HEADER_CONTENT_TYPE_NAME, HEADER_CONTENT_TYPE_JSON);
        appendHttpHeader(&headers, HEADER_AUTHORIZATION, getConfigAuthorizationToken());

        strcpy(body, "{");

        strcat(body, "\"activationCode\":\"");
        strcat(body, activation_code);
        strcat(body, "\"");

        strcat(body, "}");

        #if DEBUG
            printf("Prepared BODY is %s\n", body);
        #endif

        doHttpPut(url, headers, body, &response);

        storeDeviceToken(response);

        return response;
    }

    return NULL;
}

char *deleteADevice() {
    struct curl_slist *headers = NULL;
    char *url;
    char *response = NULL;

    if(prepareUrl(&url, configurations.base_url, configurations.delete_a_device)) {

        appendHttpHeader(&headers, HEADER_CONTENT_TYPE_NAME, HEADER_CONTENT_TYPE_JSON);
        appendHttpHeader(&headers, HEADER_AUTHORIZATION, getConfigAuthorizationToken());

        doHttpDelete(url, headers);

        return response;
    }

    return NULL;
}

char *addComponent(char *cmp_name, char *cmp_type) {
// TODO: TODO: TODO: Generate GUID
    struct curl_slist *headers = NULL;
    char *url;
    char body[BODY_SIZE_MIN];
    char *response = NULL;

    if(!cmp_name) {
        fprintf(stderr, "createAComponent::Component Name cannot be NULL");
        return NULL;
    }

    if(!cmp_type) {
        fprintf(stderr, "createAComponent::Component Type cannot be NULL");
        return NULL;
    }

    if(prepareUrl(&url, configurations.base_url, configurations.add_a_component)) {
        appendHttpHeader(&headers, HEADER_CONTENT_TYPE_NAME, HEADER_CONTENT_TYPE_JSON);
        appendHttpHeader(&headers, HEADER_AUTHORIZATION, getDeviceAuthorizationToken());

//        sprintf(body, "{\"cid\":\"%s\",\"name\":\"%s\",\"type\":\"%s\"}", "aedf4b3b-32db-4e09-8da2-fbbdfbcee37b", cmp_name, cmp_type);
        sprintf(body, "{\"cid\":\"%s\",\"name\":\"%s\",\"type\":\"%s\"}", "3601c9ad-77db-4f9a-89bf-1e6a045edb21", cmp_name, cmp_type);

        #if DEBUG
            printf("Prepared BODY is %s\n", body);
        #endif

        doHttpPost(url, headers, body, &response);

        return response;
    }

    return NULL;
}

char *deleteComponent() {
    struct curl_slist *headers = NULL;
    char *url;
    char *response = NULL;

    if(prepareUrl(&url, configurations.base_url, configurations.delete_a_component)) {

        appendHttpHeader(&headers, HEADER_CONTENT_TYPE_NAME, HEADER_CONTENT_TYPE_JSON);
        appendHttpHeader(&headers, HEADER_AUTHORIZATION, getConfigAuthorizationToken());

        doHttpDelete(url, headers);

        return response;
    }

    return NULL;
}
