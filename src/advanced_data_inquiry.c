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
 * @file advanced_data_inquiry.c
 *
 * Provides API to handle Advanced Data Inquiry
 */

#include "advanced_data_inquiry.h"

/**
 * @defgroup advanceddatainquiry
 * This is Advanced Data Inquiry Module
 *  @{
 */

/**
 * Creates an data object to be used to generate JSON Body in Advanced Data Inquiry REST call
 *
 * @return returns the created object if memory is available, otherwise NULL
 */
AdvancedDataInquiry *createAdvancedDataInquiryObject() {
    AdvancedDataInquiry *newObject = (AdvancedDataInquiry *)malloc(sizeof(AdvancedDataInquiry));

    if(!newObject) {
        return NULL;
    }

    newObject->msgType = NULL;
    newObject->gatewayIds = NULL;
    newObject->deviceIds = NULL;
    newObject->componentIds = NULL;

    newObject->startTimestamp = 0L;
    newObject->endTimestamp = 0L;

    newObject->returnedMeasureAttributes = NULL;

    newObject->showMeasureLocation = false;

    newObject->devCompAttributeFilter = NULL;
    newObject->measurementAttributeFilter = NULL;
    newObject->valueFilter = NULL;

    newObject->componentRowLimit = 0;
    newObject->countOnly = false;
    newObject->sort = NULL;

    return newObject;
}

/**
 * Sets the message type
 *
 * @param advancedDataInquiryObject object created using createAdvancedDataInquiryObject"()"
 * @param msgType message type is always 'advancedDataInquiryRequest'
 */
AdvancedDataInquiry *setMessageType(AdvancedDataInquiry *advancedDataInquiryObject, char *msgType) {
    advancedDataInquiryObject->msgType = strdup(msgType);

    return advancedDataInquiryObject;
}

/**
 * add device gateway ID. Can be called multiple times to add different IDs
 *
 * @param advancedDataInquiryObject object created using createAdvancedDataInquiryObject"()"
 * @param gatewayId gateway ID
 */
AdvancedDataInquiry *addGatewayIds(AdvancedDataInquiry *advancedDataInquiryObject, char *gatewayId) {
    StringList *addId;

    addId = (StringList *)malloc(sizeof(StringList));
    addId->data = strdup(gatewayId);
    addId->next = NULL;

    if(!advancedDataInquiryObject->gatewayIds) {
        advancedDataInquiryObject->gatewayIds = addId;
    } else {
        StringList *traverseId = advancedDataInquiryObject->gatewayIds;

        while(traverseId->next) {
            traverseId = traverseId->next;
        }
        traverseId->next = addId;
    }

    return advancedDataInquiryObject;
}

/**
 * add device ID. Can be called multiple times to add different IDs
 *
 * @param advancedDataInquiryObject object created using createAdvancedDataInquiryObject"()"
 * @param deviceId device ID
 */
AdvancedDataInquiry *addDeviceIds(AdvancedDataInquiry *advancedDataInquiryObject, char *deviceId) {
    StringList *addId;

    addId = (StringList *)malloc(sizeof(StringList));
    addId->data = strdup(deviceId);
    addId->next = NULL;

    if(!advancedDataInquiryObject->deviceIds) {
        advancedDataInquiryObject->deviceIds = addId;
    } else {
        StringList *traverseId = advancedDataInquiryObject->deviceIds;

        while(traverseId->next) {
            traverseId = traverseId->next;
        }
        traverseId->next = addId;
    }

    return advancedDataInquiryObject;
}

/**
 * add component ID. Can be called multiple times to add different IDs
 *
 * @param advancedDataInquiryObject object created using createAdvancedDataInquiryObject"()"
 * @param componentId component ID
 */
AdvancedDataInquiry *addComponentIds(AdvancedDataInquiry *advancedDataInquiryObject, char *componentId) {
    StringList *addId;

    addId = (StringList *)malloc(sizeof(StringList));
    addId->data = strdup(componentId);
    addId->next = NULL;

    if(!advancedDataInquiryObject->componentIds) {
        advancedDataInquiryObject->componentIds = addId;
    } else {
        StringList *traverseId = advancedDataInquiryObject->componentIds;

        while(traverseId->next) {
            traverseId = traverseId->next;
        }
        traverseId->next = addId;
    }

    return advancedDataInquiryObject;
}

/**
 * set the data inquiry start timestamp
 *
 * @param advancedDataInquiryObject object created using createAdvancedDataInquiryObject"()"
 * @param startTimestamp time stamp in milliseconds
 */
AdvancedDataInquiry *setStartTimestamp(AdvancedDataInquiry *advancedDataInquiryObject, long startTimestamp) {
    advancedDataInquiryObject->startTimestamp = startTimestamp;

    return advancedDataInquiryObject;
}

/**
 * set the data inquiry end timestamp
 *
 * @param advancedDataInquiryObject object created using createAdvancedDataInquiryObject"()"
 * @param endTimestamp time stamp in milliseconds
 */
AdvancedDataInquiry *setEndTimestamp(AdvancedDataInquiry *advancedDataInquiryObject, long endTimestamp) {
    advancedDataInquiryObject->endTimestamp = endTimestamp;

    return advancedDataInquiryObject;
}

/**
 * add returned measure attributes. Can be called multiple times to add different attributes
 *
 * @param advancedDataInquiryObject object created using createAdvancedDataInquiryObject"()"
 * @param attribute attribute to be added
 */
AdvancedDataInquiry *addReturnedMeasureAttributes(AdvancedDataInquiry *advancedDataInquiryObject, char *attribute) {
    StringList *addId;

    addId = (StringList *)malloc(sizeof(StringList));
    addId->data = strdup(attribute);
    addId->next = NULL;

    if(!advancedDataInquiryObject->returnedMeasureAttributes) {
        advancedDataInquiryObject->returnedMeasureAttributes = addId;
    } else {
        StringList *traverseId = advancedDataInquiryObject->returnedMeasureAttributes;

        while(traverseId->next) {
            traverseId = traverseId->next;
        }
        traverseId->next = addId;
    }

    return advancedDataInquiryObject;
}

/**
 * specifies whether or not to include measure location in the report
 *
 * @param advancedDataInquiryObject object created using createAdvancedDataInquiryObject"()"
 * @param measureLocation 'true' to include, otherwise not
 */
AdvancedDataInquiry *setShowMeasureLocation(AdvancedDataInquiry *advancedDataInquiryObject, bool measureLocation) {
    advancedDataInquiryObject->showMeasureLocation = measureLocation;

    return advancedDataInquiryObject;
}

/**
 * creates an attribute filter object which can be used in addDevCompAttributeFilter"()", addMeasurementAttributeFilter"()" and addValueFilter"()"
 *
 * @param filterName attribute filter name
 */
AttributeFilter *createAttributeFilterObject(char *filterName) {
    AttributeFilter *newObject = (AttributeFilter *)malloc(sizeof(AttributeFilter));

    if(!newObject) {
         return NULL;
     }

     newObject->filterName = strdup(filterName);
     newObject->filterValues = NULL;

     return newObject;
}

/**
 * add attribute filter value. Can be called multiple times to add different values
 *
 * @param attributeFilter attribute filter object created by createAttributeFilterObject"()"
 * @param filterValue attribute filter value
 */
AttributeFilter *addAttributeFilterValues(AttributeFilter *attributeFilter, char *filterValue) {
    StringList *addId;

    if(!attributeFilter) {
         return NULL;
     }

    addId = (StringList *)malloc(sizeof(StringList));
    addId->data = strdup(filterValue);
    addId->next = NULL;

    if(!attributeFilter->filterValues) {
        attributeFilter->filterValues = addId;
    } else {
        StringList *traverseId = attributeFilter->filterValues;

        while(traverseId->next) {
            traverseId = traverseId->next;
        }
        traverseId->next = addId;
    }

     return attributeFilter;
}

/**
 * add device component attribute filter. Can be called multiple times to add different filters
 *
 * @param advancedDataInquiryObject object created using createAdvancedDataInquiryObject"()"
 * @param attributeFilter attribute filter object created by createAttributeFilterObject"()"
 */
AdvancedDataInquiry *addDevCompAttributeFilter(AdvancedDataInquiry *advancedDataInquiryObject, AttributeFilter *attributeFilter) {
    AttributeFilterList *filterItem = (AttributeFilterList *)malloc(sizeof(AttributeFilterList));
    filterItem->filterData = attributeFilter;
    filterItem->next = NULL;

    if(!advancedDataInquiryObject->devCompAttributeFilter) {
        advancedDataInquiryObject->devCompAttributeFilter = filterItem;
    } else {
        AttributeFilterList *traverseFilter = advancedDataInquiryObject->devCompAttributeFilter;

        while(traverseFilter->next) {
            traverseFilter = traverseFilter->next;
        }
        traverseFilter->next = filterItem;
    }

    return advancedDataInquiryObject;
}

/**
 * add measurement attribute filter. Can be called multiple times to add different filters
 *
 * @param advancedDataInquiryObject object created using createAdvancedDataInquiryObject"()"
 * @param attributeFilter attribute filter object created by createAttributeFilterObject"()"
 */
AdvancedDataInquiry *addMeasurementAttributeFilter(AdvancedDataInquiry *advancedDataInquiryObject, AttributeFilter *attributeFilter) {
    AttributeFilterList *filterItem = (AttributeFilterList *)malloc(sizeof(AttributeFilterList));
    filterItem->filterData = attributeFilter;
    filterItem->next = NULL;

    if(!advancedDataInquiryObject->measurementAttributeFilter) {
        advancedDataInquiryObject->measurementAttributeFilter = filterItem;
    } else {
        AttributeFilterList *traverseFilter = advancedDataInquiryObject->measurementAttributeFilter;

        while(traverseFilter->next) {
            traverseFilter = traverseFilter->next;
        }
        traverseFilter->next = filterItem;
    }

    return advancedDataInquiryObject;
}

/**
 * add value filter. Can be called multiple times to add different values
 *
 * @param advancedDataInquiryObject object created using createAdvancedDataInquiryObject"()"
 * @param attributeFilter attribute filter object created by createAttributeFilterObject"()"
 */
AdvancedDataInquiry *addValueFilter(AdvancedDataInquiry *advancedDataInquiryObject, AttributeFilter *attributeFilter) {
    if(!advancedDataInquiryObject->valueFilter) {
        advancedDataInquiryObject->valueFilter = attributeFilter;
    } else {
        AttributeFilter *traverseFilter = advancedDataInquiryObject->valueFilter;

        while(traverseFilter->next) {
            traverseFilter = traverseFilter->next;
        }
        traverseFilter->next = attributeFilter;
    }

    return advancedDataInquiryObject;
}

/**
 * sets the number of records returned for each component in response
 *
 * @param advancedDataInquiryObject object created using createAdvancedDataInquiryObject"()"
 * @param componentRowLimit limit of records to be returned for each component in response
 */
AdvancedDataInquiry *setComponentRowLimit(AdvancedDataInquiry *advancedDataInquiryObject, int componentRowLimit) {
    advancedDataInquiryObject->componentRowLimit = componentRowLimit;

    return advancedDataInquiryObject;
}

/**
 * specifies to return only the count of records that would have returned from the query
 *
 * @param advancedDataInquiryObject object created using createAdvancedDataInquiryObject"()"
 * @param countOnly 'true' gets only the count, otherwise the complete query response is received
 */
AdvancedDataInquiry *setCountOnly(AdvancedDataInquiry *advancedDataInquiryObject, bool countOnly) {
    advancedDataInquiryObject->countOnly = countOnly;

    return advancedDataInquiryObject;
}

/**
 * add sort information. Can be called multiple times to add different sorts
 *
 * @param advancedDataInquiryObject object created using createAdvancedDataInquiryObject"()"
 * @param name name of the field
 * @param value value of the field (ASC or DESC)
 */
AdvancedDataInquiry *addSortInfo(AdvancedDataInquiry *advancedDataInquiryObject, char *name, char *value) {
    KeyValueParams *keyValue;

    keyValue = (KeyValueParams *)malloc(sizeof(KeyValueParams));
    keyValue->name = strdup(name);
    keyValue->value = strdup(value);
    keyValue->next = NULL;

    if(!advancedDataInquiryObject->sort) {
        advancedDataInquiryObject->sort = keyValue;
    } else {
        KeyValueParams *traverseSort = advancedDataInquiryObject->sort;

        while(traverseSort->next) {
            traverseSort = traverseSort->next;
        }
        traverseSort->next = keyValue;
    }

    return advancedDataInquiryObject;
}

/**
 * REST API for advanced data inquiry
 *
 * @param advancedDataInquiryObject object created using createAdvancedDataInquiryObject"()"
 * @return returns the result received from server, otherwise NULL
 */
char *advancedDataInquiry(AdvancedDataInquiry *advancedDataInquiryObject) {

    struct curl_slist *headers = NULL;
    char *url;
    char body[BODY_SIZE_MED];
    StringList *traverse = NULL;
    HttpResponse *response = (HttpResponse *)malloc(sizeof(HttpResponse));
    response->code = 0;
    response->data = NULL;

    if(prepareUrl(&url, configurations.base_url, configurations.advanced_data_inquiry, NULL)) {
        appendHttpHeader(&headers, HEADER_CONTENT_TYPE_NAME, HEADER_CONTENT_TYPE_JSON);
        appendHttpHeader(&headers, HEADER_AUTHORIZATION, getConfigAuthorizationToken());

        strcpy(body, "{");

        strcat(body, "\"msgType\":\"");
        if(advancedDataInquiryObject->msgType) {
            strcat(body, advancedDataInquiryObject->msgType);
            strcat(body, "\"");
        } else {
            strcat(body, "advancedDataInquiryRequest\"");
        }

        if(advancedDataInquiryObject->gatewayIds) {
            strcat(body, ",\"gatewayIds\":[");

            traverse = advancedDataInquiryObject->gatewayIds;
            while (traverse != NULL) {
                strcat(body, "\"");
                strcat(body, traverse->data);
                strcat(body, "\"");
                traverse = traverse->next;

                if(traverse) {
                    strcat(body, ",");
                }
            }
            strcat(body, "]");
        }

        if(advancedDataInquiryObject->deviceIds) {
            strcat(body, ",\"deviceIds\":[");

            traverse = advancedDataInquiryObject->deviceIds;
            while (traverse != NULL) {
                strcat(body, "\"");
                strcat(body, traverse->data);
                strcat(body, "\"");
                traverse = traverse->next;

                if(traverse) {
                    strcat(body, ",");
                }
            }
            strcat(body, "]");
        }

        if(advancedDataInquiryObject->componentIds) {
            strcat(body, ",\"componentIds\":[");

            traverse = advancedDataInquiryObject->componentIds;
            while (traverse != NULL) {
                strcat(body, "\"");
                strcat(body, traverse->data);
                strcat(body, "\"");
                traverse = traverse->next;

                if(traverse) {
                    strcat(body, ",");
                }
            }
            strcat(body, "]");
        }

//        if(advancedDataInquiryObject->startTimestamp > 0L)
        {
            char timeStamp[BODY_SIZE_MIN];
            sprintf(timeStamp, "%ld", advancedDataInquiryObject->startTimestamp);
            strcat(body, ",\"startTimestamp\":");
            strcat(body, timeStamp);
        }

//        if(advancedDataInquiryObject->endTimestamp> 0L)
        {
            char timeStamp[BODY_SIZE_MIN];
            sprintf(timeStamp, "%ld", advancedDataInquiryObject->endTimestamp);
            strcat(body, ",\"endTimestamp\":");
            strcat(body, timeStamp);
        }

        if(advancedDataInquiryObject->returnedMeasureAttributes) {
            strcat(body, ",\"returnedMeasureAttributes\":[");

            traverse = advancedDataInquiryObject->returnedMeasureAttributes;
            while (traverse != NULL) {
                strcat(body, "\"");
                strcat(body, traverse->data);
                strcat(body, "\"");
                traverse = traverse->next;

                if(traverse) {
                    strcat(body, ",");
                }
            }
            strcat(body, "]");
        }

        if(advancedDataInquiryObject->showMeasureLocation) {
            strcat(body, ",\"showMeasureLocation\": true");
        }

        if(advancedDataInquiryObject->componentRowLimit) {
            char rowLimit[BODY_SIZE_MIN];
            sprintf(rowLimit, "%d", advancedDataInquiryObject->componentRowLimit);
            strcat(body, ",\"componentRowLimit\":");
            strcat(body, rowLimit);
        }

        if(advancedDataInquiryObject->sort) {
            KeyValueParams *traverseKeyValues = advancedDataInquiryObject->sort;
            strcat(body, ",\"sort\":[");

            while(traverseKeyValues != NULL) {

                strcat(body, "{\"");
                strcat(body, traverseKeyValues->name);
                strcat(body, "\":\"");
                strcat(body, traverseKeyValues->value);
                strcat(body, "\"}");

                traverseKeyValues = traverseKeyValues->next;

                if(traverseKeyValues) {
                    strcat(body, ",");
                }
            }
            strcat(body, "]");
        }

        if(advancedDataInquiryObject->countOnly) {
            strcat(body, ",\"countOnly\": true");
        }

        if(advancedDataInquiryObject->devCompAttributeFilter) {
            AttributeFilterList *attributesList = advancedDataInquiryObject->devCompAttributeFilter;

            strcat(body, ",\"devCompAttributeFilter\":{");

            while(attributesList) {
                AttributeFilter *attributes = attributesList->filterData;

                #if DEBUG
                    printf("Attributes filter is %d\n", attributesList->filterData);
                #endif

                while(attributes) {
                    #if DEBUG
                        printf("Attributes filter Name is %s\n", attributes->filterName);
                    #endif
                    strcat(body, "\"");
                    strcat(body, attributes->filterName);
                    strcat(body, "\":[");

                    traverse = attributes->filterValues;
                    while (traverse != NULL) {
                        strcat(body, "\"");
                        strcat(body, traverse->data);
                        strcat(body, "\"");
                        traverse = traverse->next;

                        if(traverse) {
                            strcat(body, ",");
                        }
                    }
                    strcat(body, "]");

                    attributes = attributes->next;

                    if(attributes) {
                        strcat(body, ",");
                    }
                }

                attributesList = attributesList->next;
                if(attributesList) {
                    strcat(body, ",");
                }
            }

            strcat(body, "}");
        }


        if(advancedDataInquiryObject->measurementAttributeFilter) {
            AttributeFilterList *attributesList = advancedDataInquiryObject->measurementAttributeFilter;

            strcat(body, ",\"measurementAttributeFilter\":{");

            while(attributesList) {
                AttributeFilter *attributes = attributesList->filterData;

                while(attributes) {
                    strcat(body, "\"");
                    strcat(body, attributes->filterName);
                    strcat(body, "\":[");

                    traverse = attributes->filterValues;
                    while (traverse != NULL) {
                        strcat(body, "\"");
                        strcat(body, traverse->data);
                        strcat(body, "\"");
                        traverse = traverse->next;

                        if(traverse) {
                            strcat(body, ",");
                        }
                    }
                    strcat(body, "]");

                    attributes = attributes->next;

                    if(attributes) {
                        strcat(body, ",");
                    }
                }

                attributesList = attributesList->next;
                if(attributesList) {
                    strcat(body, ",");
                }
            }

            strcat(body, "}");
        }

        if(advancedDataInquiryObject->valueFilter) {
            strcat(body, ",\"valueFilter\":{\"");
            strcat(body, advancedDataInquiryObject->valueFilter->filterName);
            strcat(body, "\":[");

            traverse = advancedDataInquiryObject->valueFilter->filterValues;
            while (traverse != NULL) {
                strcat(body, "\"");
                strcat(body, traverse->data);
                strcat(body, "\"");
                traverse = traverse->next;

                if(traverse) {
                    strcat(body, ",");
                }
            }
            strcat(body, "]}");
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

/** @} */ // end of advanceddatainquiry
