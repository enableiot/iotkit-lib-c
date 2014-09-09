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

char *listAllDevices() {
    struct curl_slist *headers = NULL;
    char *url;
    char *response;

    appendHttpHeader(&headers, HEADER_CONTENT_TYPE_NAME, HEADER_CONTENT_TYPE_JSON);
    appendHttpHeader(&headers, HEADER_AUTHORIZATION, getConfigAuthorizationToken());

    if(prepareUrl(&url, configurations.base_url, configurations.list_all_devices)){
        doHttpGet(url, headers, &response);

        return response;
    }

    return NULL;
}

char *getOneDeviceInfo() {
    struct curl_slist *headers = NULL;
    char *url;
    char *response;

    appendHttpHeader(&headers, HEADER_CONTENT_TYPE_NAME, HEADER_CONTENT_TYPE_JSON);
    appendHttpHeader(&headers, HEADER_AUTHORIZATION, getConfigAuthorizationToken());

    if(prepareUrl(&url, configurations.base_url, configurations.get_device_info)){
        doHttpGet(url, headers, &response);

        return response;
    }

    return NULL;
}

char *createADevice(char *device_id, char *gateway_id, char *device_name) {
    struct curl_slist *headers = NULL;
    char *url;
    char body[BODY_SIZE_MED];
    char *response;

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

        doHttpPost(url, headers, body);

        return response;
    }

    return NULL;
}