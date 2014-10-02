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

#include "device_management.h"

char *validateDeviceToken() {
    struct curl_slist *headers = NULL;
    char *url;
    char *response = NULL;

    appendHttpHeader(&headers, HEADER_CONTENT_TYPE_NAME, HEADER_CONTENT_TYPE_JSON);
    appendHttpHeader(&headers, HEADER_AUTHORIZATION, getDeviceAuthorizationToken());

    if(prepareUrl(&url, configurations.base_url, configurations.auth_token_info, NULL)) {

        doHttpGet(url, headers, &response);

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

    if(prepareUrl(&url, configurations.base_url, configurations.list_all_devices, NULL)){
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

    if(prepareUrl(&url, configurations.base_url, configurations.get_device_info, NULL)){
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

    if(prepareUrl(&url, configurations.base_url, configurations.get_device_info, NULL)){
        doHttpGet(url, headers, &response);

        return response;
    }

    return NULL;
}

DeviceCreationObj *createDeviceCreationObject(char *device_id, char *gateway_id, char *device_name) {
    DeviceCreationObj *createDeviceObj = (DeviceCreationObj *)malloc(sizeof(DeviceCreationObj));
    if(!createDeviceObj) {
        fprintf(stderr, "createRetrieveDataObject::Could not allocate memory\n");
        return NULL;
    }

    createDeviceObj->device_id = device_id;
    createDeviceObj->gateway_id = gateway_id;
    createDeviceObj->device_name = device_name;

    createDeviceObj->tags = NULL;

    createDeviceObj->latitude = NULL;
    createDeviceObj->longitude = NULL;
    createDeviceObj->height = NULL;

    createDeviceObj->attributes = NULL;

    return createDeviceObj;
}

DeviceCreationObj *addLocInfo(DeviceCreationObj *createDeviceObj, char *latitude, char *longitude, char *height) {

    if(latitude && longitude) {
        createDeviceObj->latitude = latitude;
        createDeviceObj->longitude = longitude;

        if(height) {
            createDeviceObj->height = height;
        }
    }

    return createDeviceObj;
}

DeviceCreationObj *addTagInfo(DeviceCreationObj *createDeviceObj, char *tagName) {
    IdList *tagData;

    tagData = (IdList *)malloc(sizeof(IdList));
    tagData->id = tagName;
    tagData->next = NULL;

    if(!createDeviceObj->tags) {
        createDeviceObj->tags = tagData;
    } else {
        IdList *traverseId = createDeviceObj->tags;

        while(traverseId->next) {
            traverseId = traverseId->next;
        }
        traverseId->next = tagData;
    }

    return createDeviceObj;
}

DeviceCreationObj *addAttributesInfo(DeviceCreationObj *createDeviceObj, char *name, char *value) {
    KeyValueParams *keyValue;

    keyValue = (KeyValueParams *)malloc(sizeof(KeyValueParams));
    keyValue->name = name;
    keyValue->value = value;
    keyValue->next = NULL;

    if(!createDeviceObj->attributes) {
        createDeviceObj->attributes = keyValue;
    } else {
        KeyValueParams *traverseId = createDeviceObj->attributes;

        while(traverseId->next) {
            traverseId = traverseId->next;
        }
        traverseId->next = keyValue;
    }

    return createDeviceObj;
}

char *createADevice(DeviceCreationObj *createDeviceObj) {
    struct curl_slist *headers = NULL;
    char *url;
    char body[BODY_SIZE_MED];
    char *response = NULL;

    if(!createDeviceObj->device_id) {
        fprintf(stderr, "createADevice::Device ID cannot be NULL");
        return NULL;
    }

    if(!createDeviceObj->gateway_id) {
        fprintf(stderr, "createADevice::Gateway ID cannot be NULL");
        return NULL;
    }

    if(!createDeviceObj->device_name) {
        fprintf(stderr, "createADevice::Device Name cannot be NULL");
        return NULL;
    }

    if(prepareUrl(&url, configurations.base_url, configurations.create_a_device, NULL)) {
        appendHttpHeader(&headers, HEADER_CONTENT_TYPE_NAME, HEADER_CONTENT_TYPE_JSON);
        appendHttpHeader(&headers, HEADER_AUTHORIZATION, getConfigAuthorizationToken());

        sprintf(body, "{\"deviceId\":\"%s\",\"gatewayId\":\"%s\",\"name\":\"%s\"", createDeviceObj->device_id, createDeviceObj->gateway_id, createDeviceObj->device_name);

        if(createDeviceObj->tags) {
        IdList *traverse = createDeviceObj->tags;

            strcat(body, ",\"tags\":[");

            while(traverse != NULL) {
                strcat(body, "\"");
                strcat(body, traverse->id);
                strcat(body, "\"");

                traverse = traverse->next;
                if(traverse != NULL) {
                    strcat(body, ",");
                }
            }

            strcat(body, "]");
        }

        if(createDeviceObj->latitude && createDeviceObj->longitude) {
            strcat(body, ",\"loc\":[");
            strcat(body, createDeviceObj->latitude);
            strcat(body, ",");
            strcat(body, createDeviceObj->longitude);

            if(createDeviceObj->height) {
                strcat(body, ",");
                strcat(body, createDeviceObj->height);
            }
            strcat(body, "]");
        }

        if(createDeviceObj->attributes) {
            KeyValueParams *traverseParams = createDeviceObj->attributes;

            strcat(body, ",\"attributes\":{");

            while(traverseParams != NULL) {
                strcat(body, "\"");
                strcat(body, traverseParams->name);
                strcat(body, "\":\"");
                strcat(body, traverseParams->value);
                strcat(body, "\"");

                traverseParams = traverseParams->next;
                if(traverseParams != NULL) {
                    strcat(body, ",");
                }
            }

            strcat(body, "}");
        }

        strcat(body, "}");

        #if DEBUG
            printf("Prepared BODY is %s\n", body);
        #endif

        doHttpPost(url, headers, body, &response);

        storeDeviceID(response);

        return response;
    }

    return NULL;
}

char *updateADevice(DeviceCreationObj *createDeviceObj) {
    struct curl_slist *headers = NULL;
    char *url;
    char body[BODY_SIZE_MED];
    char *response = NULL;
    bool isCommaRequired = false;

    if(prepareUrl(&url, configurations.base_url, configurations.update_a_device, NULL)) {
        appendHttpHeader(&headers, HEADER_CONTENT_TYPE_NAME, HEADER_CONTENT_TYPE_JSON);
        appendHttpHeader(&headers, HEADER_AUTHORIZATION, getConfigAuthorizationToken());

       sprintf(body, "{\"gatewayId\":\"%s\",\"name\":\"%s\"", createDeviceObj->gateway_id, createDeviceObj->device_name);

               if(createDeviceObj->tags) {
               IdList *traverse = createDeviceObj->tags;

                   strcat(body, ",\"tags\":[");

                   while(traverse != NULL) {
                       strcat(body, "\"");
                       strcat(body, traverse->id);
                       strcat(body, "\"");

                       traverse = traverse->next;
                       if(traverse != NULL) {
                           strcat(body, ",");
                       }
                   }

                   strcat(body, "]");
               }

               if(createDeviceObj->latitude && createDeviceObj->longitude) {
                   strcat(body, ",\"loc\":[");
                   strcat(body, createDeviceObj->latitude);
                   strcat(body, ",");
                   strcat(body, createDeviceObj->longitude);

                   if(createDeviceObj->height) {
                       strcat(body, ",");
                       strcat(body, createDeviceObj->height);
                   }
                   strcat(body, "]");
               }

               if(createDeviceObj->attributes) {
                   KeyValueParams *traverseParams = createDeviceObj->attributes;

                   strcat(body, ",\"attributes\":{");

                   while(traverseParams != NULL) {
                       strcat(body, "\"");
                       strcat(body, traverseParams->name);
                       strcat(body, "\":\"");
                       strcat(body, traverseParams->value);
                       strcat(body, "\"");

                       traverseParams = traverseParams->next;
                       if(traverseParams != NULL) {
                           strcat(body, ",");
                       }
                   }

                   strcat(body, "}");
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

    if(prepareUrl(&url, configurations.base_url, configurations.activate_a_device, NULL)) {
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

    if(prepareUrl(&url, configurations.base_url, configurations.delete_a_device, NULL)) {

        appendHttpHeader(&headers, HEADER_CONTENT_TYPE_NAME, HEADER_CONTENT_TYPE_JSON);
        appendHttpHeader(&headers, HEADER_AUTHORIZATION, getConfigAuthorizationToken());

        doHttpDelete(url, headers);

        return response;
    }

    return NULL;
}

/** Stores device configuration JSON
*/
void storeComponent(char *response) {
    cJSON *json, *jitem, *child;
    char *cid = NULL, *name = NULL, *type = NULL;
    char *config_file_path = "../config/sensor-list.json";

    if(response != NULL) {
        // parse the file
        json = cJSON_Parse(response);
        if (!json) {
            fprintf(stderr,"Error Parsing response: [%s]\n",cJSON_GetErrorPtr());
        } else {
            if (!isJsonObject(json)) {
                fprintf(stderr,"Ignoring invalid JSON response while token validation\n");
            }

            jitem = cJSON_GetObjectItem(json, "cid");

            if(jitem) {
                cid = strdup(jitem->valuestring);
            }

            jitem = cJSON_GetObjectItem(json, "name");

            if(jitem) {
                name = strdup(jitem->valuestring);
            }

            jitem = cJSON_GetObjectItem(json, "type");

            if(jitem) {
                type = strdup(jitem->valuestring);
            }

            if(cid && name && type) {
                cJSON *root;
                char *out;
                jitem=cJSON_CreateObject();

                cJSON_AddItemToObject(jitem, "cid", cJSON_CreateString(cid));
                cJSON_AddItemToObject(jitem, "name", cJSON_CreateString(name));
                cJSON_AddItemToObject(jitem, "type", cJSON_CreateString(type));


                FILE *fp = fopen(config_file_path, "rb");
                if (fp == NULL) {
                    root = cJSON_CreateArray();
                }
                else {
                    fseek(fp, 0, SEEK_END);
                    long size = ftell(fp);
                    rewind(fp);

                    // read the file
                    char *buffer = (char *)malloc(size+1);
                    fread(buffer, 1, size, fp);

                    // parse the file
                    root = cJSON_Parse(buffer);
                    if (!root) {
                        fprintf(stderr,"Error before: [%s]\n",cJSON_GetErrorPtr());
                    }
                    else {
                        if (!isJsonArray(root)) {
                            fprintf(stderr,"Invalid JSON format for %s file\n", config_file_path);
                            return;
                        }
                    }
                }

                free(fp);

                cJSON_AddItemToArray(root, jitem);

                fp = fopen(config_file_path, "w+");
                if (fp == NULL) {
                    fprintf(stderr,"Error can't open file %s\n", config_file_path);
                }
                else {
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
        }
    }
}

void parseComponentsList() {
    char *config_file_path = "../config/sensor-list.json";
    char *out;
    int i = 0;
    cJSON *json, *jitem, *child;
    char *cid, *name, *type;
    SensorComp *traverse = NULL;

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

            if (!isJsonArray(json)) {
                fprintf(stderr,"Invalid JSON format for %s file\n", config_file_path);
                return;
            }

            for (i = 0; i < cJSON_GetArraySize(json); i++) {
                jitem=cJSON_GetArrayItem(json,i);

                child = cJSON_GetObjectItem(jitem, "cid");
                if (!isJsonString(child)) {
                    fprintf(stderr,"Invalid JSON format for json property %s\n", child->string);
                    return;
                }

                cid = strdup(child->valuestring);

                child = cJSON_GetObjectItem(jitem, "name");
                if (!isJsonString(child)) {
                    fprintf(stderr,"Invalid JSON format for json property %s\n", child->string);
                    return;
                }

                name = strdup(child->valuestring);

                child = cJSON_GetObjectItem(jitem, "type");
                if (!isJsonString(child)) {
                    fprintf(stderr,"Invalid JSON format for json property %s\n", child->string);
                    return;
                }

                type = strdup(child->valuestring);

                SensorComp *newSensor = (SensorComp *)malloc(sizeof(SensorComp));
                if (newSensor != NULL) {
                    newSensor->next = NULL;
                    newSensor->cid = cid;
                    newSensor->name = name;
                    newSensor->type = type;

                    if(sensorsList == NULL) {
                        sensorsList = newSensor;
                    } else {
                        traverse = sensorsList;
                        while(traverse->next != NULL) {
                            traverse = traverse->next;
                        }

                        traverse->next = newSensor;
                    }
                }
            }

            cJSON_Delete(json);
        }

        #if DEBUG
            traverse = sensorsList;
            while(traverse != NULL) {
                printf("Component id : %s\n", traverse->cid);
                printf("Name : %s\n", traverse->name);
                printf("Type : %s\n", traverse->type);

                traverse = traverse->next;
            }
        #endif

        // free buffers
        fclose(fp);
        free(buffer);
    }

    return ;
}


bool isSensorRegistered(char *name) {
    SensorComp *traverse = sensorsList;

    if(!name) {
        fprintf(stderr, "isSensorRegistered::Component Name cannot be NULL");
        return false;
    }
    while(traverse != NULL) {
        if(strcmp(name, traverse->name) == 0)
            return true;

        traverse = traverse->next;
    }

    return false;
}

char *getSensorComponentId(char *name) {
    SensorComp *traverse = sensorsList;

    if(!name) {
        fprintf(stderr, "getSensorComponentId::Component Name cannot be NULL");
        return NULL;
    }
    while(traverse != NULL) {
        if(strcmp(name, traverse->name) == 0)
            return traverse->cid;

        traverse = traverse->next;
    }

    return NULL;
}

bool storeSensorsFromList() {
    SensorComp *traverse = sensorsList;
    cJSON *root, *jitem;
    char *config_file_path = "../config/sensor-list.json";
    FILE *fp = NULL;
    char *out;

    root=cJSON_CreateArray();

    while(traverse != NULL) {
        jitem=cJSON_CreateObject();

        cJSON_AddItemToObject(jitem, "cid", cJSON_CreateString(traverse->cid));
        cJSON_AddItemToObject(jitem, "name", cJSON_CreateString(traverse->name));
        cJSON_AddItemToObject(jitem, "type", cJSON_CreateString(traverse->type));

        cJSON_AddItemToArray(root, jitem);

        traverse = traverse->next;
    }

    fp = fopen(config_file_path, "w+");
    if (fp == NULL) {
        fprintf(stderr,"Error can't open file %s\n", config_file_path);
    } else {
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

bool removeSensorComponentFromCache(char *name) {
    SensorComp *traverse = sensorsList;
    SensorComp *prevNode = NULL;

    if(!name) {
        fprintf(stderr, "removeSensorComponentFromCache::Component Name cannot be NULL");
        return NULL;
    }
    while(traverse != NULL) {
        if(strcmp(name, traverse->name) == 0) {
            if(!prevNode) {
                // means this is root node
                sensorsList = traverse->next;
            } else {
                prevNode->next = traverse->next;
            }

            free(traverse->cid);
            free(traverse->name);
            free(traverse->type);
            free(traverse);

            storeSensorsFromList();
            return true;
        }

        prevNode = traverse;
        traverse = traverse->next;
    }

    return false;
}

char *addComponent(char *cmp_name, char *cmp_type) {
    char  uuid_str[38];
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

    // generate UUID
    get_uuid_string(uuid_str,sizeof(uuid_str));

    if(prepareUrl(&url, configurations.base_url, configurations.add_a_component, NULL)) {
        appendHttpHeader(&headers, HEADER_CONTENT_TYPE_NAME, HEADER_CONTENT_TYPE_JSON);
        appendHttpHeader(&headers, HEADER_AUTHORIZATION, getDeviceAuthorizationToken());

        sprintf(body, "{\"cid\":\"%s\",\"name\":\"%s\",\"type\":\"%s\"}", uuid_str, cmp_name, cmp_type);

        #if DEBUG
            printf("Prepared BODY is %s\n", body);
        #endif

        doHttpPost(url, headers, body, &response);

        if(response) {
            storeComponent(response);
        }

        return response;
    }

    return NULL;
}

char *deleteComponent(char *sensor_name) {
    struct curl_slist *headers = NULL;
    char *url;
    char *response = NULL;
    KeyValueParams *urlParams = NULL;
    char *cid = NULL;
    long httpResponseCode = 0;

    cid = getSensorComponentId(sensor_name);
    urlParams = (KeyValueParams *)malloc(sizeof(KeyValueParams));
    urlParams->name = "cid";
    urlParams->value = cid;
    urlParams->next = NULL;

    if(prepareUrl(&url, configurations.base_url, configurations.delete_a_component, urlParams)) {

        appendHttpHeader(&headers, HEADER_CONTENT_TYPE_NAME, HEADER_CONTENT_TYPE_JSON);
        appendHttpHeader(&headers, HEADER_AUTHORIZATION, getConfigAuthorizationToken());

        doHttpDelete(url, headers, &httpResponseCode);

        if(httpResponseCode == 204) {
            // delete successful, perform cleanup
            removeSensorComponentFromCache(sensor_name);
        }

        return response;
    }

    return NULL;
}

bool isDeviceActivated() {
    return configurations.device_id && configurations.deviceToken;
}
