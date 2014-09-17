/*
 * Authorization token module to store and retrieve authorization
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
 * @file authorization_token.c
 * @brief Implementation of Authorization Token
 *
 * Provides features to store and retrieve authorization token
 */

#include "iotkit.h"

/** Parses configuration JSON
* @param[in] config file path to the JSON
* @return returns client query description object upon successful parsing and NULL otherwise
*/
void parseAuthorizationToken() {
    char *config_file_path = "../config/authorization.json";
    char *out;
    int i = 0;
    cJSON *json, *jitem, *child;
    bool status = true;

    FILE *fp = fopen(config_file_path, "rb");
    if (fp == NULL) {
        fprintf(stderr,"Error can't open file %s\n", config_file_path);

        configurations.authorization_key = NULL;
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

            jitem = cJSON_GetObjectItem(json, "authorization");
            if (!isJsonString(jitem) && !isJsonBooleanFalse(jitem)) {
                fprintf(stderr,"Invalid JSON format for json property %s\n", jitem->string);
                return;
            }

            if (isJsonString(jitem)) {
                configurations.authorization_key = strdup(jitem->valuestring);
                printf("Read authorization_key is %s\n", configurations.authorization_key);
            } else {
                configurations.authorization_key = NULL;
                puts("Read authorization_key is NULL");
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
void storeAuthorizationToken(char * response) {
    char *config_file_path = "../config/authorization.json";
    char *authToken = NULL;
    char *expiry = NULL;
    char * validateToken = NULL;
    FILE *fp = NULL;
    cJSON *json, *jitem, *child;

    if(response != NULL) {
        // parse the file
        json = cJSON_Parse(response);
        if (!json) {
            fprintf(stderr,"Error Parsing response: [%s]\n",cJSON_GetErrorPtr());
        }
        else {
            if (!isJsonObject(json)) {
                fprintf(stderr,"Invalid JSON response during authorization token generation\n");
                return;
            }

            jitem = cJSON_GetObjectItem(json, "token");

            if(!jitem) {
                // token not found; means the call did not go through successfully
                fprintf(stderr,"Could not retrieve Authorization Token\n");

                return;
            }

            authToken = strdup(jitem->valuestring);
        }
    }

    // retrieve the expiry info
    validateToken = validateAuthorizationToken();
    if(validateToken != NULL) {
        // parse the file
        json = cJSON_Parse(validateToken);
        if (!json) {
            fprintf(stderr,"Error Parsing response: [%s]\n",cJSON_GetErrorPtr());
        }
        else {
            if (!isJsonObject(json)) {
                fprintf(stderr,"Ignoring invalid JSON response while token validation\n");
            }

            jitem = cJSON_GetObjectItem(json, "payload");

            if(!jitem) {
                // token not found; means the call did not go through successfully
                fprintf(stderr,"Could not retrieve payload from JSON response\n");
            } else {
                child = cJSON_GetObjectItem(jitem, "exp");

                if(child) {
                    expiry = strdup(child->valuestring);
                }
            }
        }
    }

    #if DEBUG
        printf("authToken is :%s\n", authToken);
        printf("expiry is :%s\n", expiry);
    #endif

    fp = fopen(config_file_path, "w+");
    if (fp == NULL) {
        fprintf(stderr,"Error can't open file %s\n", config_file_path);
    }
    else {
        cJSON *root;
        char *out;
        root=cJSON_CreateObject();

        if(authToken) {
            cJSON_AddItemToObject(root, "authorization", cJSON_CreateString(authToken));
            configurations.authorization_key = authToken;
        } else {
            cJSON_AddItemToObject(root, "authorization", cJSON_CreateFalse());
        }

        if(expiry) {
            cJSON_AddItemToObject(root, "expiry", cJSON_CreateString(expiry));
        } else {
            cJSON_AddItemToObject(root, "expiry", cJSON_CreateFalse());
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

void storeDataAccountIdInfo() {
    cJSON *json, *jitem, *child;

    // retrieve the expiry info
    char * response = validateAuthorizationToken();
    if(response != NULL) {
        // parse the file
        json = cJSON_Parse(response);
        if (!json) {
            fprintf(stderr,"Error Parsing response: [%s]\n",cJSON_GetErrorPtr());
        }
        else {
            if (!isJsonObject(json)) {
                fprintf(stderr,"Ignoring invalid JSON response while token validation\n");
            }

            jitem = cJSON_GetObjectItem(json, "payload");

            if(!jitem) {
                // token not found; means the call did not go through successfully
                fprintf(stderr,"Could not retrieve payload from JSON response\n");
            } else {
                child = cJSON_GetObjectItem(jitem, "accounts");

                if(child && isJsonArray(child)) {
                    if(cJSON_GetArraySize(child) > 0) {
                        // we consider only the first account details
                        cJSON *item = cJSON_GetArrayItem(child, 0);

                        if(item) {
                            cJSON *accountId = cJSON_GetObjectItem(item, "id");
                            cJSON *accountName = cJSON_GetObjectItem(item, "name");

                            if(accountId && accountName) {
                                storeDeviceCredentials(configurations.device_id, configurations.deviceToken, accountId->valuestring, accountName->valuestring);
                            } else {
                                fprintf(stderr,"Could not retrieve accounts id and name from JSON response\n");
                            }
                        } else {
                            fprintf(stderr,"Could not retrieve accounts item from JSON response\n");
                        }
                    } else {
                        fprintf(stderr,"account does not contain any values\n");
                    }
                } else {
                    fprintf(stderr,"Could not retrieve account from JSON response\n");
                }
            }
        }
    }
}
