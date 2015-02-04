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

#include "authorization.h"

void saveAuthInfoInStore(char *authToken, char *expiry, char *user_account_id) {
    int store_path_length = strlen(configurations.store_path) + strlen(AUTHORIZATION_FILE_NAME) + 2;
    char *config_file_path = (char *)malloc(sizeof(char) * store_path_length);
    FILE *fp = NULL;

    #if DEBUG
        printf("authToken is :%s\n", authToken);
        printf("expiry is :%s\n", expiry);
    #endif

    strcpy(config_file_path, configurations.store_path);
    strcat(config_file_path, AUTHORIZATION_FILE_NAME);

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
        } else {
            cJSON_AddItemToObject(root, "authorization", cJSON_CreateFalse());
        }

        if(expiry) {
            cJSON_AddItemToObject(root, "expiry", cJSON_CreateString(expiry));
        } else {
            cJSON_AddItemToObject(root, "expiry", cJSON_CreateFalse());
        }

        if(user_account_id) {
            cJSON_AddItemToObject(root, "user_account_id", cJSON_CreateString(user_account_id));
        } else {
            cJSON_AddItemToObject(root, "user_account_id", cJSON_CreateFalse());
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
}

/** Parses configuration JSON
* @param[in] config file path to the JSON
* @return returns client query description object upon successful parsing and NULL otherwise
*/
void parseAuthorizationToken() {
    int store_path_length = strlen(configurations.store_path) + strlen(AUTHORIZATION_FILE_NAME) + 2;
    char *config_file_path = (char *)malloc(sizeof(char) * store_path_length);
    char *out;
    int i = 0;
    cJSON *json, *jitem, *child;
    bool status = true;

    strcpy(config_file_path, configurations.store_path);
    strcat(config_file_path, AUTHORIZATION_FILE_NAME);

    FILE *fp = fopen(config_file_path, "rb");
    if (fp == NULL) {
        saveAuthInfoInStore(NULL, NULL, NULL); // create default store
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
                #if DEBUG
                    printf("Read authorization_key is %s\n", configurations.authorization_key);
                #endif
            } else {
                configurations.authorization_key = NULL;
                #if DEBUG
                    puts("Read authorization_key is NULL");
                #endif
            }

            jitem = cJSON_GetObjectItem(json, "expiry");
            if (!isJsonString(jitem) && !isJsonBooleanFalse(jitem)) {
                fprintf(stderr,"Invalid JSON format for json property %s\n", jitem->string);
                return;
            }

            if (isJsonString(jitem)) {
                configurations.authorization_key_expiry = strdup(jitem->valuestring);
                #if DEBUG
                    printf("Read authorization_key expiry is %s\n", configurations.authorization_key_expiry);
                #endif
            } else {
                configurations.authorization_key_expiry = NULL;
                #if DEBUG
                    puts("Read authorization_key expiry is NULL");
                #endif
            }

            jitem = cJSON_GetObjectItem(json, "user_account_id");
            if (!isJsonString(jitem) && !isJsonBooleanFalse(jitem)) {
                fprintf(stderr,"Invalid JSON format for json property %s\n", jitem->string);
                return;
            }

            if (isJsonString(jitem)) {
                configurations.user_account_id = strdup(jitem->valuestring);
                #if DEBUG
                    printf("Read user_account_id is %s\n", configurations.user_account_id);
                #endif
            } else {
                configurations.user_account_id = NULL;
                #if DEBUG
                    puts("Read user_account_id is NULL");
                #endif
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
    char *authToken = NULL;
    char *expiry = NULL;
    char *user_account_id = NULL;
    char *validateToken = NULL;
    cJSON *json, *jitem, *child;

    if(response != NULL) {
        // parse the file
        json = cJSON_Parse(response);
        if (!json) {
            fprintf(stderr,"Error Parsing response: [%s]\n",cJSON_GetErrorPtr());
            return;
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
            configurations.authorization_key = authToken;
        }
    }

    // retrieve the expiry info
    validateToken = getUserJwtTokenInfo();
    if(validateToken != NULL) {
        #if DEBUG
            printf("Token validation API returned: %s\n", validateToken);
        #endif
        // parse the file
        json = cJSON_Parse(validateToken);
        if (!json) {
            fprintf(stderr,"Error Parsing response: [%s]\n",cJSON_GetErrorPtr());
            return;
        }
        else {
            if (!isJsonObject(json)) {
                fprintf(stderr,"Ignoring invalid JSON response while token validation\n");
            }

            jitem = cJSON_GetObjectItem(json, "data");
            if (!jitem || !isJsonObject(jitem)) {
                fprintf(stderr,"Ignoring invalid JSON response while token validation\n");
            } else {
                jitem = cJSON_GetObjectItem(jitem, "payload");

                if(!jitem) {
                    // token not found; means the call did not go through successfully
                    fprintf(stderr,"Could not retrieve payload from JSON response\n");
                } else {
                    child = cJSON_GetObjectItem(jitem, "exp");

                    if(child) {
                        expiry = strdup(child->valuestring);
                    }

                    child = cJSON_GetObjectItem(jitem, "sub");

                    if(child) {
                        user_account_id = strdup(child->valuestring);
                    }
                }
            }
        }
    }

    saveAuthInfoInStore(authToken, expiry, user_account_id);

    return ;
}

void storeDataAccountIdInfo() {
    cJSON *json, *jitem, *child;
    char *response = NULL;

    // retrieve the expiry info
    response = getUserJwtTokenInfo();
    if(response != NULL) {
        // parse the file
        json = cJSON_Parse(response);
        if (!json) {
            fprintf(stderr,"Error Parsing response: [%s]\n",cJSON_GetErrorPtr());
            return;
        }
        else {
            if (!isJsonObject(json)) {
                fprintf(stderr,"Ignoring invalid JSON response while token validation\n");
            }

            jitem = cJSON_GetObjectItem(json, "data");
            if (!jitem || !isJsonObject(jitem)) {
                fprintf(stderr,"Ignoring invalid JSON response while token validation\n");
            } else {
                jitem = cJSON_GetObjectItem(jitem, "payload");

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
}
