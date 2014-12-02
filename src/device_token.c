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

#include "iotkit.h"

/** Parses configuration JSON
* @param[in] config file path to the JSON
* @return returns client query description object upon successful parsing and NULL otherwise
*/
void parseDeviceToken() {
    char *out;
    int i = 0;
    cJSON *json, *jitem, *child;
    bool status = true;
    int store_path_length = strlen(configurations.store_path) + strlen(DEVICE_CONFIG_FILE_NAME) + 2;
    char *config_file_path = (char *)malloc(sizeof(char) * store_path_length);

    strcpy(config_file_path, configurations.store_path);
    strcat(config_file_path, DEVICE_CONFIG_FILE_NAME);

    FILE *fp = fopen(config_file_path, "rb");
    if (fp == NULL) {
//        fprintf(stderr,"Error can't open file %s\n", config_file_path);

        configurations.device_id = NULL;
        configurations.deviceToken = NULL;
        storeDeviceCredentials(NULL, NULL, NULL, NULL); // create the file with default values
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
                #if DEBUG
                    printf("Device ID %s\n", configurations.device_id);
                #endif
            } else {
                configurations.device_id = NULL;
                #if DEBUG
                    puts("Device ID is NULL");
                #endif
            }

            jitem = cJSON_GetObjectItem(json, "deviceToken");
            if (!isJsonString(jitem) && !isJsonBooleanFalse(jitem)) {
                fprintf(stderr,"Invalid JSON format for json property %s\n", jitem->string);
                return;
            }

            if (isJsonString(jitem)) {
                configurations.deviceToken = strdup(jitem->valuestring);
                #if DEBUG
                    printf("Device Token %s\n", configurations.deviceToken);
                #endif
            } else {
                configurations.deviceToken = NULL;
                #if DEBUG
                    puts("Device Token is NULL");
                #endif
            }

            jitem = cJSON_GetObjectItem(json, "data_account_id");
            if (!isJsonString(jitem) && !isJsonBooleanFalse(jitem)) {
                fprintf(stderr,"Invalid JSON format for json property %s\n", jitem->string);
                return;
            }

            if (isJsonString(jitem)) {
                configurations.data_account_id = strdup(jitem->valuestring);
                #if DEBUG
                    printf("Data Account ID is %s\n", configurations.data_account_id);
                #endif
            } else {
                configurations.data_account_id = NULL;
                #if DEBUG
                    puts("Data Account ID is NULL");
                #endif
            }

            jitem = cJSON_GetObjectItem(json, "data_account_name");
            if (!isJsonString(jitem) && !isJsonBooleanFalse(jitem)) {
                fprintf(stderr,"Invalid JSON format for json property %s\n", jitem->string);
                return;
            }

            if (isJsonString(jitem)) {
                configurations.data_account_name = strdup(jitem->valuestring);
            } else {
                configurations.data_account_name = NULL;
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
void storeDeviceCredentials(char *deviceId, char *deviceToken, char *data_account_id, char *data_account_name) {
    int store_path_length = strlen(configurations.store_path) + strlen(DEVICE_CONFIG_FILE_NAME) + 2;
    char *config_file_path = (char *)malloc(sizeof(char) * store_path_length);

    strcpy(config_file_path, configurations.store_path);
    strcat(config_file_path, DEVICE_CONFIG_FILE_NAME);

    #if DEBUG
        if(deviceId) {
            printf("deviceId is :%s\n", deviceId);
        } else {
            printf("deviceId is NULL\n");
        }

        if(deviceToken) {
            printf("deviceToken is :%s\n", deviceToken);
        } else {
            printf("deviceToken is NULL\n");
        }

        if(data_account_id) {
            printf("data_account_id is :%s\n", data_account_id);
        } else {
            printf("data_account_id is NULL\n");
        }

        if(data_account_name) {
            printf("data_account_name is :%s\n", data_account_name);
        } else {
            printf("data_account_name is NULL\n");
        }
    #endif

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
            configurations.deviceToken = strdup(deviceToken);
        } else {
            cJSON_AddItemToObject(root, "deviceToken", cJSON_CreateFalse());
        }

        if(data_account_id) {
            cJSON_AddItemToObject(root, "data_account_id", cJSON_CreateString(data_account_id));
            configurations.data_account_id = strdup(data_account_id);
        } else {
            cJSON_AddItemToObject(root, "data_account_id", cJSON_CreateFalse());
        }

        if(data_account_name) {
            cJSON_AddItemToObject(root, "data_account_name", cJSON_CreateString(data_account_name));
            configurations.data_account_name = strdup(data_account_name);
        } else {
            cJSON_AddItemToObject(root, "data_account_name", cJSON_CreateFalse());
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


void storeDeviceID(char *response) {

    if(response != NULL) {
        char *out;
        cJSON *json, *jitem;

        // parse the file
        json = cJSON_Parse(response);
        if (!json) {
            fprintf(stderr,"Error Parsing response: [%s]\n",cJSON_GetErrorPtr());
            return;
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

            #if DEBUG
                printf("Created device for ID %s\n", jitem->valuestring);
            #endif

            // overwrite device token if any present
            configurations.deviceToken = NULL;
            storeDeviceCredentials(jitem->valuestring, configurations.deviceToken, configurations.data_account_id, configurations.data_account_name);

            return true;
        }
    }
}

void storeDeviceToken(char *response) {
    if(response != NULL) {
        char *out;
        cJSON *json, *jitem;
        char *deviceToken = NULL, *accountId = NULL;

        // parse the file
        json = cJSON_Parse(response);
        if (!json) {
            fprintf(stderr,"Error Parsing response: [%s]\n",cJSON_GetErrorPtr());
            return;
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

            storeDeviceCredentials(configurations.device_id, deviceToken, configurations.data_account_id, configurations.data_account_name);

            return true;
        }
    }
}

void storeAccountInfo(char *response) {
    if(response != NULL) {
        char *out;
        cJSON *json, *jitem;
        char *accountName = NULL, *accountId = NULL;

        // parse the file
        json = cJSON_Parse(response);
        if (!json) {
            fprintf(stderr,"Error Parsing response: [%s]\n",cJSON_GetErrorPtr());
            return;
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

            jitem = cJSON_GetObjectItem(json, "name");

            if(jitem) {
                accountName = strdup(jitem->valuestring);
            }

            jitem = cJSON_GetObjectItem(json, "id");

            if(jitem) {
                accountId = strdup(jitem->valuestring);
            }

            storeDeviceCredentials(configurations.device_id, configurations.deviceToken, accountId, accountName);
        }
    }
}
