/*
 * iotkit 'C' Library to communicate with IoT Cloud via REST APIs
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
 * @file iotkit.h
 * @brief Header file of iotkit library
 *
 * Data Structures and function declarations
 */

#ifndef __IOTKIT_H
#define __IOTKIT_H


#include <stdlib.h>
#include <stdbool.h>
#include "../lib/cJSON/cJSON.h"
#include "util.h"
#include "rest.h"

#ifndef DEBUG
   #define DEBUG 1
#endif

#define BODY_SIZE_MIN 1024
#define BODY_SIZE_MED 4096
#define BODY_SIZE_MAX 12288

#define HTTP_PROTOCOL "http://"
#define HTTPS_PROTOCOL "https://"

#define HEADER_CONTENT_TYPE_NAME "Content-Type"
#define HEADER_CONTENT_TYPE_JSON "application/json"


#define HEADER_AUTHORIZATION "Authorization"
#define HEADER_AUTHORIZATION_BEARER "Bearer "

/** Sensor list to hold sensors
*/
typedef struct _SensorComp {
    char *cid;
    char *name;
    char *type;

    struct SensorComp *next;
} SensorComp;


typedef struct _Configurations {
    bool isSecure;

    char *account_id;
    char *base_url;

    char *data_account_id;
    char *data_account_name;
    char *device_id;
    // account management
    char *create_an_account;
    char *get_account_information;
    char *get_account_activation_code;
    char *renew_account_activation;
    char *update_an_account_name;
    char *delete_an_account_name;

    // account authorization
    char *authorization_key;
    char *new_auth_token;
    char *auth_token_info;
    char *me_info;

    // component catalogs
    char *list_components;
    char *get_component_details;
    char *create_an_cmp_catalog;
    char *update_an_cmp_catalog;

    // device management
    char *list_all_devices;
    char *get_device_info;
    char *create_a_device;
    char *update_a_device;
    char *activate_a_device;
    char *delete_a_device;
    char *add_a_component;
    char *delete_a_component;
    char *deviceToken;

    // data api
    char *submit_data;
    char *retrieve_data;
} Configurations;


Configurations configurations;
SensorComp *sensorsList;

void parseConfiguration(char *config_file_path);
bool prepareUrl(char **full_url, char *url_prepend, char *url_append);
char *getConfigAuthorizationToken();

#endif
