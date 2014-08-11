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
 * @file iotkit.c
 * @brief Implementation of iotkit library
 *
 * Provides features for communication with IoT Cloud server
 */

#include "iotkit.h"

static bool isInitialized = false;

void iotkit_init() {

parseConfiguration("../config/config.json");

    if(!isInitialized) {
        CURLcode code = rest_init(configurations.isSecure);
        if(code) {
            fprintf(stderr, "Unable to initialize CURL %d\n", code);
        } else {
            isInitialized = true;
            puts("Library initialized successfully");
        }
    } else {
        puts("Library is already initialized and doesn't need to be re-initialized");
    }
}

void iotkit_cleanup() {
    if(isInitialized) {
        rest_cleanup();
        isInitialized = false;
    } else {
        puts("Library is not initialized and doesn't need to cleanup resources");
    }
}


/** Parses configuration JSON
* @param[in] config file path to the JSON
* @return returns client query description object upon successful parsing and NULL otherwise
*/
void parseConfiguration(char *config_file_path) {
    char *out;
    int i = 0;
    cJSON *json, *jitem, *child1, *child2;
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

            jitem = cJSON_GetObjectItem(json, "isSecure");
            if (!isJsonBooleanTrue(jitem)) {
                fprintf(stderr,"Invalid JSON format for json property %s\n", jitem->string);
                return;
            }
            configurations.isSecure = true;

            jitem = cJSON_GetObjectItem(json, "account_id");
            if (!isJsonString(jitem)) {
                fprintf(stderr,"Invalid JSON format for json property %s\n", jitem->string);
                return;
            }
            configurations.account_id = strdup(jitem->valuestring);
            printf("Read Account ID %s\n", configurations.account_id);

            jitem = cJSON_GetObjectItem(json, "authorization_key");

            if (!isJsonString(jitem)) {
                fprintf(stderr,"Invalid JSON format for json property %s\n", jitem->string);
                return;
            }

            configurations.authorization_key = strdup(jitem->valuestring);

            printf("Read authorization_key is %s\n", configurations.authorization_key);


            jitem = cJSON_GetObjectItem(json, "host");

            if (!isJsonString(jitem)) {
                fprintf(stderr,"Invalid JSON format for json property %s\n", jitem->string);
                return;
            }

            configurations.base_url = strdup(jitem->valuestring);

            jitem = cJSON_GetObjectItem(json, "apipath");

            if (!isJsonObject(jitem)) {
                fprintf(stderr,"Invalid JSON format for json property %s\n", jitem->string);
                return;
            }

            child1 = cJSON_GetObjectItem(jitem, "account_management");
            if (!isJsonObject(child1)) {
                fprintf(stderr,"Invalid JSON format for json property %s\n", child1->string);
                return;
            }

            child2 = cJSON_GetObjectItem(child1, "renew_account_activation");
            if (!isJsonString(child2)) {
                fprintf(stderr,"Invalid JSON format for json property %s\n", child2->string);
                return;
            }

            configurations.renew_account_activation = strdup(child2->valuestring);


            child1 = cJSON_GetObjectItem(jitem, "authorization");

            if (!isJsonObject(child1)) {
                fprintf(stderr,"Invalid JSON format for json property %s\n", child1->string);
                return;
            }

            child2 = cJSON_GetObjectItem(child1, "new_auth_token");

            if (!isJsonString(child2)) {
                fprintf(stderr,"Invalid JSON format for json property %s\n", child2->string);
                return;
            }

            configurations.new_auth_token = strdup(child2->valuestring);


            child2 = cJSON_GetObjectItem(child1, "auth_token_info");

            if (!isJsonString(child2)) {
                fprintf(stderr,"Invalid JSON format for json property %s\n", child2->string);
                return;
            }

            configurations.auth_token_info = strdup(child2->valuestring);

            printf("Read auth_token_info is %s\n", configurations.auth_token_info);


            child2 = cJSON_GetObjectItem(child1, "me_info");

            if (!isJsonString(child2)) {
                fprintf(stderr,"Invalid JSON format for json property %s\n", child2->string);
                return;
            }

            configurations.me_info = strdup(child2->valuestring);

            printf("Read me_info is %s\n", configurations.me_info);





            cJSON_Delete(json);
        }

        // free buffers
        fclose(fp);
        free(buffer);
    }

    return ;
}


bool prepareUrl(char **full_url, char *url_prepend, char *url_append) {
    int urlSize;
    char *url_post = NULL;

    if(!url_prepend || !url_append) {
        fprintf(stderr, "prepareUrl: Parameter cannot be NULL");
        return false;
    }

    if(strstr(url_append, "{")) {
        char *start = strstr(url_append, "{");
        char *end = strstr(url_append, "}");

        char strtokensize = end - start;
        char *strtoken = (char *)malloc(sizeof(char) * strtokensize);
        strncpy(strtoken, start + 1, strtokensize -1);
        strtoken[strtokensize - 1] = '\0';

        if(strcmp(strtoken, "account_id") == 0) {
            int url_post_size = (start - url_append) + strlen(configurations.account_id) + strlen(end);
            url_post = (char *)malloc(sizeof(char) * url_post_size);

            strncpy(url_post, url_append, (start - url_append));
            url_post[start - url_append] = '\0';
            strcat(url_post, configurations.account_id);
            strcat(url_post, end + 1);
        } else {
            url_post = url_append;
        }
    } else {
        url_post = url_append;
    }

    urlSize = configurations.isSecure ? strlen(HTTPS_PROTOCOL) : strlen(HTTP_PROTOCOL);
    urlSize += strlen(url_prepend) + strlen(url_post) + 1;
    *full_url = (char *)malloc(sizeof(char) * urlSize);
    if(configurations.isSecure){
        strcpy(*full_url, HTTPS_PROTOCOL);
    } else {
        strcpy(*full_url, HTTP_PROTOCOL);
    }

    strcat(*full_url, url_prepend);
    strcat(*full_url, url_post);


    #if DEBUG
        printf("URL prepared is %s\n", *full_url);
    #endif

    return true;
}


char *getConfigAuthorizationToken() {
    char *authorization;
    int authorizationSize = strlen(HEADER_AUTHORIZATION_BEARER) + configurations.authorization_key + 1;

    authorization = (char *)malloc(sizeof(char) * authorizationSize);
    strcpy(authorization, HEADER_AUTHORIZATION_BEARER);
    strcat(authorization, configurations.authorization_key);

    return authorization;
}

#if DEBUG

    void main() {
        struct curl_slist *headers = NULL;
        puts("Iotkit Library to communicate with IoT Cloud via REST APIs");

        iotkit_init();

        renewActivationCode();


        iotkit_cleanup();
    }

#endif
