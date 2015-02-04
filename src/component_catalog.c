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
 * @file component_catalog.c
 *
 * Provides API to handle Component Catalogs
 */

#include "component_catalog.h"

/**
 * @defgroup componentcatalog
 * This is Component Catalog Module
 *  @{
 */

/**
 * REST API to list all component types
 *
 * @return returns the result received from server, otherwise NULL
 */
char *listAllComponentCatalogs() {
    struct curl_slist *headers = NULL;
    char *url;
    char *authorizationHeader = (char *)getConfigAuthorizationToken();
    HttpResponse *response = NULL;

    if(authorizationHeader == NULL) {
        fprintf(stderr, "listAllComponentCatalogs::Authorization Token not available\n");
        return NULL;
    }

    response = (HttpResponse *)malloc(sizeof(HttpResponse));
    response->code = 0;
    response->data = NULL;

    appendHttpHeader(&headers, HEADER_AUTHORIZATION, authorizationHeader);

    if(prepareUrl(&url, configurations.base_url, configurations.list_components, NULL)) {

        doHttpGet(url, headers, response);

        return createHttpResponseJson(response);
    }

    return NULL;
}

/**
 * REST API to get component type details
 *
 * @param cmp_id specifies the component type ID
 * @return returns the result received from server, otherwise NULL
 */
char *getComponentCatalogDetails(char *cmp_id) {
    struct curl_slist *headers = NULL;
    char *url;
    KeyValueParams *urlParams = NULL;
    char *authorizationHeader = (char *)getConfigAuthorizationToken();
    HttpResponse *response = NULL;

    if(authorizationHeader == NULL) {
        fprintf(stderr, "getComponentCatalogDetails::Authorization Token not available\n");
        return NULL;
    }

    response = (HttpResponse *)malloc(sizeof(HttpResponse));
    response->code = 0;
    response->data = NULL;

    urlParams = (KeyValueParams *)malloc(sizeof(KeyValueParams));
    urlParams->name = "cmp_catalog_id";
    urlParams->value = cmp_id;
    urlParams->next = NULL;

    appendHttpHeader(&headers, HEADER_AUTHORIZATION, authorizationHeader);

    if(prepareUrl(&url, configurations.base_url, configurations.get_component_details, urlParams)) {

        doHttpGet(url, headers, response);

        return createHttpResponseJson(response);
    }

    return NULL;
}

/**
 * Creates an data object to be used to generate JSON Body in Advanced Data Inquiry REST call
 *
 * @param cmp_name specifies the component name
 * @param cmp_version specifies the component version
 * @param cmp_type specifies the component type
 * @param cmp_datatype specifies the component data type
 * @param cmp_format specifies the component format
 * @param cmp_unit specifies the component units
 * @param cmp_display specifies the component display type
 * @return returns the created object if memory is available, otherwise NULL
 */
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

/**
 * sets the min value to the object created using createComponentCatalogObject()
 *
 * @param cmpCatalogObject the object created using createComponentCatalogObject()
 * @param cmp_minvalue specifies the min value
 */
ComponentCatalog *addMinValue(ComponentCatalog *cmpCatalogObject, double cmp_minvalue) {
    cmpCatalogObject->isMinPresent = true;
    cmpCatalogObject->minvalue = cmp_minvalue;

    return cmpCatalogObject;
}

/**
 * sets the max value to the object created using createComponentCatalogObject()
 *
 * @param cmpCatalogObject the object created using createComponentCatalogObject()
 * @param cmp_maxvalue specifies the max value
 */
ComponentCatalog *addMaxValue(ComponentCatalog *cmpCatalogObject, double cmp_maxvalue) {
    cmpCatalogObject->isMaxPresent = true;
    cmpCatalogObject->maxvalue = cmp_maxvalue;

    return cmpCatalogObject;
}

/**
 * sets the command string to the object created using createComponentCatalogObject()
 *
 * @param cmpCatalogObject the object created using createComponentCatalogObject()
 * @param cmp_command specifies the command string
 */
ComponentCatalog *addCommandString(ComponentCatalog *cmpCatalogObject, char *cmp_command) {
    cmpCatalogObject->command = cmp_command;

    return cmpCatalogObject;
}

/**
 * adds the command parameters to the object created using createComponentCatalogObject()
 *
 * @param cmpCatalogObject the object created using createComponentCatalogObject()
 * @param cmp_name specifies the component name
 * @param cmd_value specifies the component value
 */
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

/**
 * REST API to create a component catalog
 *
 * @param cmpCatalogObject the object created using createComponentCatalogObject()
 * @return returns the result received from server, otherwise NULL
 */
char *createAnComponentCatalog(ComponentCatalog *cmpCatalogObject) {

    struct curl_slist *headers = NULL;
    char *url;
    char body[BODY_SIZE_MIN];
    char *authorizationHeader = (char *)getConfigAuthorizationToken();
    HttpResponse *response = NULL;

    if(authorizationHeader == NULL) {
        fprintf(stderr, "createAnComponentCatalog::Authorization Token not available\n");
        return NULL;
    }

    response = (HttpResponse *)malloc(sizeof(HttpResponse));
    response->code = 0;
    response->data = NULL;

    if(cmpCatalogObject->name == NULL || cmpCatalogObject->version == NULL || \
            cmpCatalogObject->type == NULL || cmpCatalogObject->datatype == NULL || \
            cmpCatalogObject->format == NULL || cmpCatalogObject->unit == NULL || \
            cmpCatalogObject->display == NULL) {
        fprintf(stderr, "Mandatory field missing to create component catalog\n");

        return NULL;
    }

    if(strcmp(cmpCatalogObject->type, "actuator") ==0 && cmpCatalogObject->parameters == NULL) {
        fprintf(stderr, "Command Parameters are mandatory for component catalog type \"actuator\"\n");

        return NULL;
    }

    if(prepareUrl(&url, configurations.base_url, configurations.create_an_cmp_catalog, NULL)) {
        appendHttpHeader(&headers, HEADER_CONTENT_TYPE_NAME, HEADER_CONTENT_TYPE_JSON);
        appendHttpHeader(&headers, HEADER_AUTHORIZATION, authorizationHeader);

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

        doHttpPost(url, headers, body, response);

        return createHttpResponseJson(response);
    }

    return NULL;
}

/**
 * REST API to update a component catalog
 *
 * @param cmpCatalogObject the object created using createComponentCatalogObject()
 * @param cmp_id specifies the component ID which has to be updated
 * @return returns the result received from server, otherwise NULL
 */
char *updateAnComponentCatalog(ComponentCatalog *cmpCatalogObject, char *cmp_id) {

    struct curl_slist *headers = NULL;
    char *url;
    char body[BODY_SIZE_MIN];
    bool isCommaRequired = false;
    KeyValueParams *urlParams = NULL;
    char value[BODY_SIZE_MIN];
    char *authorizationHeader = (char *)getConfigAuthorizationToken();
    HttpResponse *response = NULL;

    if(authorizationHeader == NULL) {
        fprintf(stderr, "updateAnComponentCatalog::Authorization Token not available\n");
        return NULL;
    }

    response = (HttpResponse *)malloc(sizeof(HttpResponse));
    response->code = 0;
    response->data = NULL;

    if(strcmp(cmpCatalogObject->type, "actuator") ==0 && cmpCatalogObject->parameters == NULL) {
        fprintf(stderr, "Command Parameters are mandatory for component catalog type \"actuator\"\n");

        return NULL;
    }

    urlParams = (KeyValueParams *)malloc(sizeof(KeyValueParams));
    urlParams->name = "cmp_catalog_id";
    urlParams->value = cmp_id;
    urlParams->next = NULL;

    if(prepareUrl(&url, configurations.base_url, configurations.update_an_cmp_catalog, urlParams)) {
        appendHttpHeader(&headers, HEADER_CONTENT_TYPE_NAME, HEADER_CONTENT_TYPE_JSON);
        appendHttpHeader(&headers, HEADER_AUTHORIZATION, authorizationHeader);

        strcpy(body, "{");

        if(cmpCatalogObject->type != NULL) {
            strcat(body, "\"type\":\"");
            strcat(body, cmpCatalogObject->type);
            strcat(body, "\"");

            isCommaRequired = true;
        }

        if(cmpCatalogObject->datatype != NULL) {
            if(isCommaRequired) {
                strcat(body, ",");
            }

            strcat(body, "\"dataType\":\"");
            strcat(body, cmpCatalogObject->datatype);
            strcat(body, "\"");

            isCommaRequired = true;
        }

        if(cmpCatalogObject->format) {
            if(isCommaRequired) {
                strcat(body, ",");
            }

            strcat(body, "\"format\":\"");
            strcat(body, cmpCatalogObject->format);
            strcat(body, "\"");

            isCommaRequired = true;
        }

        if(cmpCatalogObject->isMinPresent == true) {
            if(isCommaRequired) {
                strcat(body, ",");
            }

            sprintf(value, "%f", cmpCatalogObject->minvalue);
            strcat(body, "\"min\":");
            strcat(body, value);

            isCommaRequired = true;
        }

        if(cmpCatalogObject->isMaxPresent == true) {
            if(isCommaRequired) {
                strcat(body, ",");
            }

            sprintf(value, "%f", cmpCatalogObject->maxvalue);
            strcat(body, "\"max\":");
            strcat(body, value);

            isCommaRequired = true;
        }

        if(cmpCatalogObject->unit) {
            if(isCommaRequired) {
                strcat(body, ",");
            }

            strcat(body, "\"measureunit\":\"");
            strcat(body, cmpCatalogObject->unit);
            strcat(body, "\"");

            isCommaRequired = true;
        }

        if(cmpCatalogObject->display) {
            if(isCommaRequired) {
                strcat(body, ",");
            }

            strcat(body, "\"display\":\"");
            strcat(body, cmpCatalogObject->display);
            strcat(body, "\"");

            isCommaRequired = true;
        }

        if(cmpCatalogObject->command != NULL) {
            ActuatorCommandParams * traverse = cmpCatalogObject->parameters;

            if(isCommaRequired) {
                strcat(body, ",");
            }

            strcat(body, "\"command\":{\"parameters\":[");

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

        doHttpPut(url, headers, body, response);

        return createHttpResponseJson(response);
    }

    return NULL;
}

/** @} */ // end of componentcatalog
