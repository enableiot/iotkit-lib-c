/*
 * Authorization API module to communicate with IoT Cloud via REST APIs
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
 * @file authorization.c
 * @brief Implementation of Authorization API
 *
 * Provides features for communication with IoT Cloud server
 */

#include "component_catalog.h"

char * listAllComponentCatalogs() {
    struct curl_slist *headers = NULL;
    char *url;
    char *response = NULL;

    appendHttpHeader(&headers, HEADER_AUTHORIZATION, getDeviceAuthorizationToken());

    if(prepareUrl(&url, configurations.base_url, configurations.list_components)) {

        doHttpGet(url, headers, &response);

        return response;
    }

    return NULL;
}

char * getComponentCatalogDetails() {
    struct curl_slist *headers = NULL;
    char *url;
    char *response = NULL;

    appendHttpHeader(&headers, HEADER_AUTHORIZATION, getDeviceAuthorizationToken());

    if(prepareUrl(&url, configurations.base_url, configurations.get_component_details)) {

        doHttpGet(url, headers, &response);

        return response;
    }

    return NULL;
}

ComponentCatalog *createComponentCatalogObject(char *cmp_name, char *cmp_version, char *cmp_type, char *cmp_datatype, \
            char *cmp_format, char *cmp_unit, char *cmp_display) {
    ComponentCatalog *newObject = (ComponentCatalog *)malloc(sizeof(ComponentCatalog));

    if(!newObject) {
        return NULL;
    }

    newObject->name = cmp_name;
    newObject->version = cmp_version;
    newObject->type = cmp_type;
    newObject->datatype = cmp_datatype;
    newObject->format = cmp_format;

    newObject->unit = cmp_unit;
    newObject->display = cmp_display;

    newObject->isMinPresent = false;
    newObject->isMaxPresent = false;

    newObject->minvalue = 0.0f;
    newObject->maxvalue = 0.0f;

    newObject->parameters = NULL;

    return newObject;
}

ComponentCatalog *addMinValue(ComponentCatalog *cmpCatalogObject, double cmp_minvalue) {
    cmpCatalogObject->isMinPresent = true;
    cmpCatalogObject->minvalue = cmp_minvalue;

    return cmpCatalogObject;
}

ComponentCatalog *addMaxValue(ComponentCatalog *cmpCatalogObject, double cmp_maxvalue) {
    cmpCatalogObject->isMaxPresent = true;
    cmpCatalogObject->maxvalue = cmp_maxvalue;

    return cmpCatalogObject;
}

ComponentCatalog *addCommandString(ComponentCatalog *cmpCatalogObject, char *cmp_command) {
    cmpCatalogObject->command = cmp_command;

    return cmpCatalogObject;
}

ComponentCatalog *addCommandParams(ComponentCatalog *cmpCatalogObject, char *cmd_name, char *cmd_value) {
    ActuatorCommandParams *newParam = (ActuatorCommandParams *)malloc(sizeof(ActuatorCommandParams));

    newParam->name = cmd_name;
    newParam->value = cmd_value;
    newParam->next = NULL;

    if(!cmpCatalogObject->parameters) {
        cmpCatalogObject->parameters = newParam;
    } else {
        ActuatorCommandParams *traverse = cmpCatalogObject->parameters;

        while(traverse->next != NULL) {
            traverse = traverse->next;
        }

        traverse->next = newParam;
    }

    return cmpCatalogObject;
}

char *createAnComponentCatalog(ComponentCatalog *cmpCatalogObject) {

    struct curl_slist *headers = NULL;
    char *url;
    char body[BODY_SIZE_MIN];
    char *response = NULL;

    if(cmpCatalogObject->name == NULL || cmpCatalogObject->version == NULL || \
            cmpCatalogObject->type == NULL || cmpCatalogObject->datatype == NULL || \
            cmpCatalogObject->format == NULL || cmpCatalogObject->unit == NULL || \
            cmpCatalogObject->display == NULL) {
        printf("Mandatory field missing to create component catalog\n");

        return NULL;
    }

    if(strcmp(cmpCatalogObject->type, "actuator") ==0 && cmpCatalogObject->parameters == NULL) {
        printf("Command Parameters are mandatory for component catalog type \"actuator\"\n");

        return NULL;
    }

    if(prepareUrl(&url, configurations.base_url, configurations.create_an_cmp_catalog)) {
        appendHttpHeader(&headers, HEADER_CONTENT_TYPE_NAME, HEADER_CONTENT_TYPE_JSON);
        appendHttpHeader(&headers, HEADER_AUTHORIZATION, getConfigAuthorizationToken());

        strcpy(body, "{");

        strcat(body, "\"dimension\":\"");
        strcat(body, cmpCatalogObject->name);
        strcat(body, "\"");

        strcat(body, ",\"version\":\"");
        strcat(body, cmpCatalogObject->version);
        strcat(body, "\"");

        strcat(body, ",\"type\":\"");
        strcat(body, cmpCatalogObject->type);
        strcat(body, "\"");

        strcat(body, ",\"dataType\":\"");
        strcat(body, cmpCatalogObject->datatype);
        strcat(body, "\"");

        strcat(body, ",\"format\":\"");
        strcat(body, cmpCatalogObject->format);
        strcat(body, "\"");

        char value[BODY_SIZE_MIN];
        if(cmpCatalogObject->isMinPresent == true) {
            sprintf(value, "%f", cmpCatalogObject->minvalue);
            strcat(body, ",\"min\":");
            strcat(body, value);
        }

        if(cmpCatalogObject->isMaxPresent == true) {
            sprintf(value, "%f", cmpCatalogObject->maxvalue);
            strcat(body, ",\"max\":");
            strcat(body, value);
        }

        strcat(body, ",\"measureunit\":\"");
        strcat(body, cmpCatalogObject->unit);
        strcat(body, "\"");

        strcat(body, ",\"display\":\"");
        strcat(body, cmpCatalogObject->display);
        strcat(body, "\"");

        if(cmpCatalogObject->command != NULL) {
            ActuatorCommandParams * traverse = cmpCatalogObject->parameters;
            strcat(body, ",\"command\":{\"parameters\":[");

            while(traverse != NULL) {
                strcat(body, "{\"name\":\"");
                strcat(body, traverse->name);
                strcat(body, "\",\"values\":\"");
                strcat(body, traverse->value);
                strcat(body, "\"}");

                traverse = traverse->next;

                if(traverse != NULL) {
                    strcat(body, ",");
                }
            }

            strcat(body, "],\"commandString\":\"");
            strcat(body, cmpCatalogObject->command);
            strcat(body, "\"}");
        }



        strcat(body, "}");

        #if DEBUG
            printf("Prepared BODY is %s\n", body);
        #endif

        doHttpPost(url, headers, body, &response);

        return response;
    }

    return NULL;
}

char *updateAnComponentCatalog(char *cmp_type, char *cmp_datatype, \
        char *cmp_format, bool isMinPresent, double cmp_minvalue, bool isMaxPresent, double cmp_maxvalue,
        char *cmp_unit, char *cmp_display, char *cmp_command) {

// TODO: TODO: TODO: TODO: THIS DOES NOT SUPPORT ACTUATOR AS OF NOW

    struct curl_slist *headers = NULL;
    char *url;
    char body[BODY_SIZE_MIN];
    char *response = NULL;
    bool isCommaRequired = false;

    if(prepareUrl(&url, configurations.base_url, configurations.update_an_cmp_catalog)) {
        appendHttpHeader(&headers, HEADER_CONTENT_TYPE_NAME, HEADER_CONTENT_TYPE_JSON);
        appendHttpHeader(&headers, HEADER_AUTHORIZATION, getConfigAuthorizationToken());

        strcpy(body, "{");

        if(cmp_type != NULL) {
            strcat(body, "\"type\":\"");
            strcat(body, cmp_type);
            strcat(body, "\"");
            isCommaRequired = true;
        }

        if(cmp_datatype != NULL) {
            if(isCommaRequired) {
                strcat(body, ",");
            }
            strcat(body, "\"dataType\":\"");
            strcat(body, cmp_datatype);
            strcat(body, "\"");
            isCommaRequired = true;
        }

        if(cmp_format != NULL) {
            if(isCommaRequired) {
                strcat(body, ",");
            }
            strcat(body, "\"format\":\"");
            strcat(body, cmp_format);
            strcat(body, "\"");
            isCommaRequired = true;
        }

        char value[BODY_SIZE_MIN];
        if(isMinPresent == true) {
            sprintf(value, "%f", cmp_minvalue);
            if(isCommaRequired) {
                strcat(body, ",");
            }
            strcat(body, "\"min\":");
            strcat(body, value);
            isCommaRequired = true;
        }

        if(isMaxPresent == true) {
            sprintf(value, "%f", cmp_maxvalue);
            if(isCommaRequired) {
                strcat(body, ",");
            }
            strcat(body, "\"max\":");
            strcat(body, value);
            isCommaRequired = true;
        }

        if(cmp_unit != NULL) {
            if(isCommaRequired) {
                strcat(body, ",");
            }
            strcat(body, "\"measureunit\":\"");
            strcat(body, cmp_unit);
            strcat(body, "\"");
            isCommaRequired = true;
        }

        if(cmp_display != NULL) {
            if(isCommaRequired) {
                strcat(body, ",");
            }
            strcat(body, "\"display\":\"");
            strcat(body, cmp_display);
            strcat(body, "\"");
            isCommaRequired = true;
        }

        if(cmp_command != NULL) {
            // TODO: TODO: NEED TO BE VALIDATED FOR ACTUATOR
            if(isCommaRequired) {
                strcat(body, ",");
            }
            strcat(body, "\"command\":\"");
            strcat(body, cmp_command);
            strcat(body, "\"");
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
