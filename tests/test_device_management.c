/*
 * Test to create a device
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
 * @file testCreateADevice.c
 *
 * Test to create a device
 */

#include "../src/iotkit.h"

bool testCreateADevice() {
    char * response = createADevice("02-00-86-81-77-aa", "02-00-86-81-77-aa", "maha25");
    printf("Response Received :%s\n", response);

    if(response != NULL) {
        char *out;
        cJSON *json, *jitem, *child;

        // parse the file
        json = cJSON_Parse(response);
        if (!json) {
            fprintf(stderr,"Error Parsing response: [%s]\n",cJSON_GetErrorPtr());
        }
        else {
            #if DEBUG
                out = cJSON_Print(json, 2);
                printf("%s\n", out);
                free(out);
            #endif

            if (!isJsonObject(json)) {
                fprintf(stderr,"Invalid JSON response\n");
                return false;
            }

            jitem = cJSON_GetObjectItem(json, "status");

            if(!jitem || strcmp(jitem->valuestring, "created")) {
                // Status not found; means the call did not go through successfully
                jitem = cJSON_GetObjectItem(json, "message");

                if(jitem) {
                    fprintf(stderr,"Could not create device: %s\n", jitem->valuestring);
                } else {
                    fprintf(stderr,"Could not create device\n");
                }

                return false;
            }

            jitem = cJSON_GetObjectItem(json, "deviceId");

            printf("Created device for ID %s\n", jitem->valuestring);

            storeDeviceCredentials(jitem->valuestring, NULL);

            return true;
        }
    }

    return false;
}

bool testActivateADevice(char *authCode) {

    char * response = activateADevice(authCode);

    printf("Response Received :%s\n", response);

    if(response != NULL) {
        char *out;
        cJSON *json, *jitem, *child;
        char *deviceToken = NULL, *accountId = NULL;

        // parse the file
        json = cJSON_Parse(response);
        if (!json) {
            fprintf(stderr,"Error Parsing response: [%s]\n",cJSON_GetErrorPtr());
        }
        else {
            #if DEBUG
                out = cJSON_Print(json, 2);
                printf("%s\n", out);
                free(out);
            #endif

            if (!isJsonObject(json)) {
                fprintf(stderr,"Invalid JSON response\n");
                return false;
            }

            jitem = cJSON_GetObjectItem(json, "message");

            if(jitem) {
                fprintf(stderr,"Could not create device: %s\n", jitem->valuestring);
                return false;
            }

            jitem = cJSON_GetObjectItem(json, "deviceToken");

            if(jitem) {
                deviceToken = strdup(jitem->valuestring);
            }

            jitem = cJSON_GetObjectItem(json, "domainId");

            if(jitem) {
                accountId = strdup(jitem->valuestring);
            }

            storeDeviceCredentials(configurations.device_id, deviceToken);

            return true;
        }
    }

    return false;
}
