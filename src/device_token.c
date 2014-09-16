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

/** Parses configuration JSON
* @param[in] config file path to the JSON
* @return returns client query description object upon successful parsing and NULL otherwise
*/
void parseDeviceToken() {
    char *config_file_path = "../config/device_config.json";
    char *out;
    int i = 0;
    cJSON *json, *jitem, *child;
    bool status = true;

    FILE *fp = fopen(config_file_path, "rb");
    if (fp == NULL) {
        fprintf(stderr,"Error can't open file %s\n", config_file_path);
    }
    else {
        fseek(fp, 0, SEEK_END);
        long size = ftell(fp);
        rewind(fp);

        // read the file
        char *buffer = (char *)malloc(size+1);
        fread(buffer, 1, size, fp);

        // parse the file
        json = cJSON_Parse(buffer);
        if (!json) {
            fprintf(stderr,"Error before: [%s]\n",cJSON_GetErrorPtr());
        }
        else {
            #if DEBUG
                out = cJSON_Print(json, 2);
                printf("%s\n", out);
                free(out);
            #endif

            if (!isJsonObject(json)) {
                fprintf(stderr,"Invalid JSON format for %s file\n", config_file_path);
                return;
            }

            jitem = cJSON_GetObjectItem(json, "deviceId");
            if (!isJsonString(jitem) && !isJsonBooleanFalse(jitem)) {
                fprintf(stderr,"Invalid JSON format for json property %s\n", jitem->string);
                return;
            }

            if (isJsonString(jitem)) {
                configurations.device_id = strdup(jitem->valuestring);
                printf("Device ID %s\n", configurations.device_id);
            } else {
                configurations.device_id = NULL;
                puts("Device ID is NULL");
            }

            jitem = cJSON_GetObjectItem(json, "deviceToken");
            if (!isJsonString(jitem) && !isJsonBooleanFalse(jitem)) {
                fprintf(stderr,"Invalid JSON format for json property %s\n", jitem->string);
                return;
            }

            if (isJsonString(jitem)) {
                configurations.deviceToken = strdup(jitem->valuestring);
                printf("Device Token %s\n", configurations.deviceToken);
            } else {
                configurations.deviceToken = NULL;
                puts("Device Token is NULL");
            }

            cJSON_Delete(json);
        }

        // free buffers
        fclose(fp);
        free(buffer);
    }

    return ;
}

/** Stores device configuration JSON
*/
void storeDeviceCredentials(char *deviceId, char *deviceToken) {
    char *config_file_path = "../config/device_config.json";

    printf("deviceId is :%s\n", deviceId);
    printf("deviceToken is :%s\n", deviceToken);

    FILE *fp = fopen(config_file_path, "w+");
    if (fp == NULL) {
        fprintf(stderr,"Error can't open file %s\n", config_file_path);
    }
    else {
        cJSON *root;
        char *out;
        root=cJSON_CreateObject();

        if(deviceId) {
            cJSON_AddItemToObject(root, "deviceId", cJSON_CreateString(deviceId));
            configurations.device_id = strdup(deviceId);
        } else {
            cJSON_AddItemToObject(root, "deviceId", cJSON_CreateFalse());
        }

        if(deviceToken) {
            cJSON_AddItemToObject(root, "deviceToken", cJSON_CreateString(deviceToken));
        } else {
            cJSON_AddItemToObject(root, "deviceToken", cJSON_CreateFalse());
        }

        out = cJSON_Print(root, 2);

        #if DEBUG
            printf("%s\n", out);
        #endif

        fwrite(out, strlen(out), sizeof(char), fp);

        // free buffers
        free(out);
        cJSON_Delete(root);
        fclose(fp);
    }

    return ;
}
