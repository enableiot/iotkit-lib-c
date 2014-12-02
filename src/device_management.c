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

/**
 * @file device_management.c
 *
 * Provides API to handle Device Management
 */

#include "device_management.h"

/**
 * @defgroup devicemanagement
 * This is Device Management Module
 *  @{
 */

/**
 * REST API to list all the devices under the account
 *
 * @return returns the result received from server, otherwise NULL
 */
char *listAllDevices() {
    struct curl_slist *headers = NULL;
    char *url;
    HttpResponse *response = (HttpResponse *)malloc(sizeof(HttpResponse));
    response->code = 0;
    response->data = NULL;

    appendHttpHeader(&headers, HEADER_CONTENT_TYPE_NAME, HEADER_CONTENT_TYPE_JSON);
    appendHttpHeader(&headers, HEADER_AUTHORIZATION, getConfigAuthorizationToken());

    if(prepareUrl(&url, configurations.base_url, configurations.list_all_devices, NULL)){
        doHttpGet(url, headers, response);

        return createHttpResponseJson(response);
    }

    return NULL;
}

/**
 * REST API to get own device info. For another device please use getOneDeviceInfo()
 *
 * @return returns the result received from server, otherwise NULL
 */
char *getMyDeviceInfo() {
    struct curl_slist *headers = NULL;
    char *url;
    HttpResponse *response = (HttpResponse *)malloc(sizeof(HttpResponse));
    response->code = 0;
    response->data = NULL;

    appendHttpHeader(&headers, HEADER_CONTENT_TYPE_NAME, HEADER_CONTENT_TYPE_JSON);
    appendHttpHeader(&headers, HEADER_AUTHORIZATION, getDeviceAuthorizationToken());

    if(prepareUrl(&url, configurations.base_url, configurations.get_my_device_info, NULL)){
        doHttpGet(url, headers, response);

        return createHttpResponseJson(response);
    }

    return NULL;
}

/**
 * REST API to get a specific device info. For own device please use getMyDeviceInfo()
 *
 * @param device_id specifies the device ID
 * @return returns the result received from server, otherwise NULL
 */
char *getOneDeviceInfo(char *device_id) {
    struct curl_slist *headers = NULL;
    char *url;
    KeyValueParams *urlParams = NULL;
    HttpResponse *response = (HttpResponse *)malloc(sizeof(HttpResponse));
    response->code = 0;
    response->data = NULL;

    urlParams = (KeyValueParams *)malloc(sizeof(KeyValueParams));
    urlParams->name = "other_device_id";
    urlParams->value = device_id;
    urlParams->next = NULL;

    appendHttpHeader(&headers, HEADER_CONTENT_TYPE_NAME, HEADER_CONTENT_TYPE_JSON);
    appendHttpHeader(&headers, HEADER_AUTHORIZATION, getConfigAuthorizationToken());

    if(prepareUrl(&url, configurations.base_url, configurations.get_device_info, urlParams)){
        doHttpGet(url, headers, response);

        return createHttpResponseJson(response);
    }

    return NULL;
}

/**
 * Creates an data object to be used to generate JSON Body during createADevice() REST call
 *
 * @param device_id specifies the device ID
 * @param gateway_id specifies the gateway ID
 * @param device_name specifies the device name
 * @return returns the created object if memory is available, otherwise NULL
 */
DeviceCreationObj *createDeviceCreationObject(char *device_id, char *gateway_id, char *device_name) {
    DeviceCreationObj *createDeviceObj = (DeviceCreationObj *)malloc(sizeof(DeviceCreationObj));
    if(!createDeviceObj) {
        fprintf(stderr, "createRetrieveDataObject::Could not allocate memory\n");
        return NULL;
    }

    createDeviceObj->device_id = strdup(device_id);
    createDeviceObj->gateway_id = strdup(gateway_id);
    createDeviceObj->device_name = strdup(device_name);

    createDeviceObj->tags = NULL;

    createDeviceObj->latitude = NULL;
    createDeviceObj->longitude = NULL;
    createDeviceObj->height = NULL;

    createDeviceObj->attributes = NULL;

    return createDeviceObj;
}

/**
 * sets the location information for the object created through createDeviceCreationObject()
 *
 * @param createDeviceObj the object created using createDeviceCreationObject()
 * @param latitide specifies the geo location - latitude of the device
 * @param longitude specifies the geo location - longitude of the device
 * @param height specifies the physical height of the device
 */
DeviceCreationObj *addLocInfo(DeviceCreationObj *createDeviceObj, char *latitude, char *longitude, char *height) {

    if(latitude && longitude) {
        createDeviceObj->latitude = strdup(latitude);
        createDeviceObj->longitude = strdup(longitude);

        if(height) {
            createDeviceObj->height = strdup(height);
        }
    }

    return createDeviceObj;
}

/**
 * add the tags. Can be called multiple times to add different tags
 *
 * @param createDeviceObj the object created using createDeviceCreationObject()
 * @param tagName specifies the tag to be attached to a device
 */
DeviceCreationObj *addTagInfo(DeviceCreationObj *createDeviceObj, char *tagName) {
    StringList *tagData;

    tagData = (StringList *)malloc(sizeof(StringList));
    tagData->data = strdup(tagName);
    tagData->next = NULL;

    if(!createDeviceObj->tags) {
        createDeviceObj->tags = tagData;
    } else {
        StringList *traverseId = createDeviceObj->tags;

        while(traverseId->next) {
            traverseId = traverseId->next;
        }
        traverseId->next = tagData;
    }

    return createDeviceObj;
}

/**
 * add device attributes information. Can be called multiple times to add different attributes
 *
 * @param createDeviceObj the object created using createDeviceCreationObject()
 * @param name specifes the parameter name in the attribute
 * @param value specifes the parameter value in the attribute
 */
DeviceCreationObj *addAttributesInfo(DeviceCreationObj *createDeviceObj, char *name, char *value) {
    KeyValueParams *keyValue;

    keyValue = (KeyValueParams *)malloc(sizeof(KeyValueParams));
    keyValue->name = strdup(name);
    keyValue->value = strdup(value);
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

/**
 * REST API to create a device
 *
 * @param createDeviceObj the object created using createDeviceCreationObject()
 * @return returns the result received from server, otherwise NULL
 */
char *createADevice(DeviceCreationObj *createDeviceObj) {
    struct curl_slist *headers = NULL;
    char *url;
    char body[BODY_SIZE_MED];
    HttpResponse *response = (HttpResponse *)malloc(sizeof(HttpResponse));
    response->code = 0;
    response->data = NULL;

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
        StringList *traverse = createDeviceObj->tags;

            strcat(body, ",\"tags\":[");

            while(traverse != NULL) {
                strcat(body, "\"");
                strcat(body, traverse->data);
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

        doHttpPost(url, headers, body, response);

        if(response->data) {
            storeDeviceID(response->data);
        }

        return createHttpResponseJson(response);
    }

    return NULL;
}

/**
 * REST API to update an existing device
 *
 * @param createDeviceObj the object created using createDeviceCreationObject()
 * @return returns the result received from server, otherwise NULL
 */
char *updateADevice(DeviceCreationObj *createDeviceObj) {
    struct curl_slist *headers = NULL;
    char *url;
    char body[BODY_SIZE_MED];
    bool isCommaRequired = false;
    HttpResponse *response = (HttpResponse *)malloc(sizeof(HttpResponse));
    response->code = 0;
    response->data = NULL;

    if(prepareUrl(&url, configurations.base_url, configurations.update_a_device, NULL)) {
        appendHttpHeader(&headers, HEADER_CONTENT_TYPE_NAME, HEADER_CONTENT_TYPE_JSON);
        appendHttpHeader(&headers, HEADER_AUTHORIZATION, getConfigAuthorizationToken());

       sprintf(body, "{\"gatewayId\":\"%s\",\"name\":\"%s\"", createDeviceObj->gateway_id, createDeviceObj->device_name);

               if(createDeviceObj->tags) {
               StringList *traverse = createDeviceObj->tags;

                   strcat(body, ",\"tags\":[");

                   while(traverse != NULL) {
                       strcat(body, "\"");
                       strcat(body, traverse->data);
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

        doHttpPut(url, headers, body, response);

        return createHttpResponseJson(response);
    }

    return NULL;
}

/**
 * REST API to activate a device
 *
 * @param activation_code specifies the activation code
 * @return returns the result received from server, otherwise NULL
 */
char *activateADevice(char *activation_code) {
    struct curl_slist *headers = NULL;
    char *url;
    char body[BODY_SIZE_MED];
    HttpResponse *response = (HttpResponse *)malloc(sizeof(HttpResponse));
    response->code = 0;
    response->data = NULL;

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

        doHttpPut(url, headers, body, response);

        if(response->data) {
            storeDeviceToken(response->data);
        }

        return createHttpResponseJson(response);
    }

    return NULL;
}

/**
 * REST API to delete an existing device
 *
 * @param device_id specifies the device ID
 * @return returns the result received from server, otherwise NULL
 */
char *deleteADevice(char *device_id) {
    struct curl_slist *headers = NULL;
    char *url;
    KeyValueParams *urlParams = NULL;
    HttpResponse *response = (HttpResponse *)malloc(sizeof(HttpResponse));
    response->code = 0;
    response->data = NULL;

    urlParams = (KeyValueParams *)malloc(sizeof(KeyValueParams));
    urlParams->name = "other_device_id";
    urlParams->value = device_id;
    urlParams->next = NULL;

    if(prepareUrl(&url, configurations.base_url, configurations.delete_a_device, urlParams)) {

        appendHttpHeader(&headers, HEADER_CONTENT_TYPE_NAME, HEADER_CONTENT_TYPE_JSON);
        appendHttpHeader(&headers, HEADER_AUTHORIZATION, getConfigAuthorizationToken());

        doHttpDelete(url, headers, response);

        return createHttpResponseJson(response);
    }

    return NULL;
}

/* Stores device configuration JSON
*/
void storeComponent(char *response) {
    cJSON *json = NULL, *jitem = NULL, *child = NULL;
    char *cid = NULL, *name = NULL, *type = NULL;
    int store_path_length = strlen(configurations.store_path) + strlen(SENSOR_LIST_FILE_NAME) + 2;
    char *config_file_path = (char *)malloc(sizeof(char) * store_path_length);

    strcpy(config_file_path, configurations.store_path);
    strcat(config_file_path, SENSOR_LIST_FILE_NAME);

    if(response != NULL) {
        // parse the file
        json = cJSON_Parse(response);
        if (!json) {
            fprintf(stderr,"Error Parsing response: [%s]\n",cJSON_GetErrorPtr());
            return;
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
                cJSON *root = NULL;
                char *out = NULL;
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

                fclose(fp);

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
    int store_path_length = strlen(configurations.store_path) + strlen(SENSOR_LIST_FILE_NAME) + 2;
    char *config_file_path = (char *)malloc(sizeof(char) * store_path_length);
    char *out;
    int i = 0;
    cJSON *json, *jitem, *child;
    char *cid, *name, *type;
    SensorComp *traverse = NULL;

    strcpy(config_file_path, configurations.store_path);
    strcat(config_file_path, SENSOR_LIST_FILE_NAME);

    FILE *fp = fopen(config_file_path, "rb");
    if (fp == NULL) {
//        fprintf(stderr,"Error can't open file %s\n", config_file_path);
        sensorsList = NULL;
    } else {
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


/**
 * Checks whether a sensor is already registered or not
 *
 * @param name specifies the sensor name
 * @return returns 'true' if already registered otherwise 'false'
 */
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

/**
 * Gets the ID for a given sensor name
 *
 * @param name specifies the sensor name
 * @return returns the ID if available, otherwise NULL
 */
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
    int store_path_length = strlen(configurations.store_path) + strlen(SENSOR_LIST_FILE_NAME) + 2;
    char *config_file_path = (char *)malloc(sizeof(char) * store_path_length);
    SensorComp *traverse = sensorsList;
    cJSON *root, *jitem;
    FILE *fp = NULL;
    char *out;

    strcpy(config_file_path, configurations.store_path);
    strcat(config_file_path, SENSOR_LIST_FILE_NAME);

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
        return false;
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

/**
 * REST API to add a component (also known as sensor) to device
 *
 * @param cmp_name specifies the sensor name
 * @param cmp_type specifies the sensor type
 * @return returns the result received from server, otherwise NULL
 */
char *addComponent(char *cmp_name, char *cmp_type) {
    char  uuid_str[38];
    struct curl_slist *headers = NULL;
    char *url;
    char body[BODY_SIZE_MIN];
    HttpResponse *response = (HttpResponse *)malloc(sizeof(HttpResponse));
    response->code = 0;
    response->data = NULL;

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

        doHttpPost(url, headers, body, response);

        #if DEBUG
            printf("Received Response is %s\n", response->data);
        #endif
        if(response->data) {
            storeComponent(response->data);
        }

        return createHttpResponseJson(response);
    }

    return NULL;
}

/**
 * REST API to delete a component (also known as sensor) from a device
 *
 * @param cmp_name specifies the sensor name
 * @return returns the result received from server, otherwise NULL
 */
char *deleteComponent(char *sensor_name) {
    struct curl_slist *headers = NULL;
    char *url;
    KeyValueParams *urlParams = NULL;
    char *cid = NULL;
    HttpResponse *response = (HttpResponse *)malloc(sizeof(HttpResponse));
    response->code = 0;
    response->data = NULL;

    cid = getSensorComponentId(sensor_name);
    urlParams = (KeyValueParams *)malloc(sizeof(KeyValueParams));
    urlParams->name = "cid";
    urlParams->value = cid;
    urlParams->next = NULL;

    if(prepareUrl(&url, configurations.base_url, configurations.delete_a_component, urlParams)) {

        appendHttpHeader(&headers, HEADER_CONTENT_TYPE_NAME, HEADER_CONTENT_TYPE_JSON);
        appendHttpHeader(&headers, HEADER_AUTHORIZATION, getConfigAuthorizationToken());

        doHttpDelete(url, headers, response);

        if(response->code == 204) {
            // delete successful, perform cleanup
            removeSensorComponentFromCache(sensor_name);
        }

        return createHttpResponseJson(response);
    }

    return NULL;
}

/**
 * Specifies whether the device is activated or not
 *
 * @return returns 'true' if already activated, otherwise 'false'
 */
bool isDeviceActivated() {
    return configurations.device_id && configurations.deviceToken;
}

/**
 * REST API to list all the tags of the device
 *
 * @return returns the result received from server, otherwise NULL
 */
char *listAllTagsForDevices() {
    struct curl_slist *headers = NULL;
    char *url;
    HttpResponse *response = (HttpResponse *)malloc(sizeof(HttpResponse));
    response->code = 0;
    response->data = NULL;

    appendHttpHeader(&headers, HEADER_CONTENT_TYPE_NAME, HEADER_CONTENT_TYPE_JSON);
    appendHttpHeader(&headers, HEADER_AUTHORIZATION, getConfigAuthorizationToken());

    if(prepareUrl(&url, configurations.base_url, configurations.list_all_tags_for_devices, NULL)){
        doHttpGet(url, headers, response);

        return createHttpResponseJson(response);
    }

    return NULL;
}

/**
 * REST API to list all the attributes of the device
 *
 * @return returns the result received from server, otherwise NULL
 */
char *listAllAttributesForDevices() {
    struct curl_slist *headers = NULL;
    char *url;
    HttpResponse *response = (HttpResponse *)malloc(sizeof(HttpResponse));
    response->code = 0;
    response->data = NULL;

    appendHttpHeader(&headers, HEADER_CONTENT_TYPE_NAME, HEADER_CONTENT_TYPE_JSON);
    appendHttpHeader(&headers, HEADER_AUTHORIZATION, getConfigAuthorizationToken());

    if(prepareUrl(&url, configurations.base_url, configurations.list_all_attributes_for_devices, NULL)){
        doHttpGet(url, headers, response);

        return createHttpResponseJson(response);
    }

    return NULL;
}

/** @} */ // end of devicemanagement
