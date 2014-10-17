/*
 * Aggregated Report Interface API module to communicate with IoT Cloud via REST APIs
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
 * @file aggregated_report_interface.c
 * @brief Implementation of Aggregated Report Interface
 *
 * Provides features for communication with IoT Cloud server
 */

#include "aggregated_report_interface.h"

AggregatedReportInterface *createAggregatedReportInterface() {
    AggregatedReportInterface *newObject = (AggregatedReportInterface *)malloc(sizeof(AggregatedReportInterface));

    if(!newObject) {
        return NULL;
    }

    newObject->msgType = NULL;
    newObject->startTimestamp = 0L;
    newObject->endTimestamp = 0L;
    newObject->aggregationMethods = NULL;
    newObject->dimensions = NULL;
    newObject->offset = 0;
    newObject->limit = 0;
    newObject->countOnly = false;
    newObject->outputType = NULL;
    newObject->gatewayIds = NULL;
    newObject->deviceIds = NULL;
    newObject->componentIds = NULL;
    newObject->sort = NULL;
    newObject->filters = NULL;

    return newObject;
}

AggregatedReportInterface *setReportMessageType(AggregatedReportInterface *aggregatedReportInterfaceObject, char *msgType) {
    aggregatedReportInterfaceObject->msgType = strdup(msgType);

    return aggregatedReportInterfaceObject;
}

AggregatedReportInterface *setReportStartTimestamp(AggregatedReportInterface *aggregatedReportInterfaceObject, long startTimestamp) {
    aggregatedReportInterfaceObject->startTimestamp = startTimestamp;

    return aggregatedReportInterfaceObject;
}

AggregatedReportInterface *setReportEndTimestamp(AggregatedReportInterface *aggregatedReportInterfaceObject, long endTimestamp) {
    aggregatedReportInterfaceObject->endTimestamp = endTimestamp;

    return aggregatedReportInterfaceObject;
}

AggregatedReportInterface *addAggregationMethods(AggregatedReportInterface *aggregatedReportInterfaceObject, char *aggregation) {
    StringList *addId;

    addId = (StringList *)malloc(sizeof(StringList));
    addId->data = strdup(aggregation);
    addId->next = NULL;

    if(!aggregatedReportInterfaceObject->aggregationMethods) {
        aggregatedReportInterfaceObject->aggregationMethods = addId;
    } else {
        StringList *traverseId = aggregatedReportInterfaceObject->aggregationMethods;

        while(traverseId->next) {
            traverseId = traverseId->next;
        }
        traverseId->next = addId;
    }

    return aggregatedReportInterfaceObject;
}

AggregatedReportInterface *addDimensions(AggregatedReportInterface *aggregatedReportInterfaceObject, char *dimension) {
    StringList *addId;

    addId = (StringList *)malloc(sizeof(StringList));
    addId->data = strdup(dimension);
    addId->next = NULL;

    if(!aggregatedReportInterfaceObject->dimensions) {
        aggregatedReportInterfaceObject->dimensions = addId;
    } else {
        StringList *traverseId = aggregatedReportInterfaceObject->dimensions;

        while(traverseId->next) {
            traverseId = traverseId->next;
        }
        traverseId->next = addId;
    }

    return aggregatedReportInterfaceObject;
}

AggregatedReportInterface *setOffset(AggregatedReportInterface *aggregatedReportInterfaceObject, int offset) {
    aggregatedReportInterfaceObject->offset = offset;

    return aggregatedReportInterfaceObject;
}

AggregatedReportInterface *setLimit(AggregatedReportInterface *aggregatedReportInterfaceObject, int limit) {
    aggregatedReportInterfaceObject->limit = limit;

    return aggregatedReportInterfaceObject;
}

AggregatedReportInterface *setReportCountOnly(AggregatedReportInterface *aggregatedReportInterfaceObject, bool countOnly) {
    aggregatedReportInterfaceObject->countOnly = countOnly;

    return aggregatedReportInterfaceObject;
}

AggregatedReportInterface *setOutputType(AggregatedReportInterface *aggregatedReportInterfaceObject, char *outputType) {
    aggregatedReportInterfaceObject->outputType = strdup(outputType);

    return aggregatedReportInterfaceObject;
}

AggregatedReportInterface *addReportDeviceIds(AggregatedReportInterface *aggregatedReportInterfaceObject, char *deviceId) {
    StringList *addId;

    addId = (StringList *)malloc(sizeof(StringList));
    addId->data = strdup(deviceId);
    addId->next = NULL;

    if(!aggregatedReportInterfaceObject->deviceIds) {
        aggregatedReportInterfaceObject->deviceIds = addId;
    } else {
        StringList *traverseId = aggregatedReportInterfaceObject->deviceIds;

        while(traverseId->next) {
            traverseId = traverseId->next;
        }
        traverseId->next = addId;
    }

    return aggregatedReportInterfaceObject;
}

AggregatedReportInterface *addReportGatewayIds(AggregatedReportInterface *aggregatedReportInterfaceObject, char *gatewayId) {
    StringList *addId;

    addId = (StringList *)malloc(sizeof(StringList));
    addId->data = strdup(gatewayId);
    addId->next = NULL;

    if(!aggregatedReportInterfaceObject->gatewayIds) {
        aggregatedReportInterfaceObject->gatewayIds = addId;
    } else {
        StringList *traverseId = aggregatedReportInterfaceObject->gatewayIds;

        while(traverseId->next) {
            traverseId = traverseId->next;
        }
        traverseId->next = addId;
    }

    return aggregatedReportInterfaceObject;
}

AggregatedReportInterface *addReportComponentIds(AggregatedReportInterface *aggregatedReportInterfaceObject, char *componentId) {
    StringList *addId;

    addId = (StringList *)malloc(sizeof(StringList));
    addId->data = strdup(componentId);
    addId->next = NULL;

    if(!aggregatedReportInterfaceObject->componentIds) {
        aggregatedReportInterfaceObject->componentIds = addId;
    } else {
        StringList *traverseId = aggregatedReportInterfaceObject->componentIds;

        while(traverseId->next) {
            traverseId = traverseId->next;
        }
        traverseId->next = addId;
    }

    return aggregatedReportInterfaceObject;
}

AggregatedReportInterface *addReportSortInfo(AggregatedReportInterface *aggregatedReportInterfaceObject, char *name, char *value) {
    KeyValueParams *keyValue;

    keyValue = (KeyValueParams *)malloc(sizeof(KeyValueParams));
    keyValue->name = strdup(name);
    keyValue->value = strdup(value);
    keyValue->next = NULL;

    if(!aggregatedReportInterfaceObject->sort) {
        aggregatedReportInterfaceObject->sort = keyValue;
    } else {
        KeyValueParams *traverseSort = aggregatedReportInterfaceObject->sort;

        while(traverseSort->next) {
            traverseSort = traverseSort->next;
        }
        traverseSort->next = keyValue;
    }

    return aggregatedReportInterfaceObject;
}


/*AttributeFilter *createAttributeFilterObject(char *filterName) {
    AttributeFilter *newObject = (AttributeFilter *)malloc(sizeof(AttributeFilter));

    if(!newObject) {
         return NULL;
     }

     newObject->filterName = strdup(filterName);
     newObject->filterValues = NULL;

     return newObject;
}

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
*/
AggregatedReportInterface *addFilters(AggregatedReportInterface *aggregatedReportInterfaceObject, AttributeFilter *attributeFilter) {
    AttributeFilterList *filterItem = (AttributeFilterList *)malloc(sizeof(AttributeFilterList));
    filterItem->filterData = attributeFilter;
    filterItem->next = NULL;

    if(!aggregatedReportInterfaceObject->filters) {
        aggregatedReportInterfaceObject->filters = filterItem;
    } else {
        AttributeFilterList *traverseFilter = aggregatedReportInterfaceObject->filters;

        while(traverseFilter->next) {
            traverseFilter = traverseFilter->next;
        }
        traverseFilter->next = filterItem;
    }

    return aggregatedReportInterfaceObject;
}


bool aggregatedReportInterface(AggregatedReportInterface *aggregatedReportInterfaceObject, long *httpResponseCode, char **response) {

    struct curl_slist *headers = NULL;
    char *url;
    char body[BODY_SIZE_MED];
    StringList *traverse = NULL;

    if(prepareUrl(&url, configurations.base_url, configurations.aggregated_report_interface, NULL)) {
        appendHttpHeader(&headers, HEADER_CONTENT_TYPE_NAME, HEADER_CONTENT_TYPE_JSON);
        appendHttpHeader(&headers, HEADER_AUTHORIZATION, getConfigAuthorizationToken());

        strcpy(body, "{");

        strcat(body, "\"msgType\":\"");
        if(aggregatedReportInterfaceObject->msgType) {
            strcat(body, aggregatedReportInterfaceObject->msgType);
            strcat(body, "\"");
        } else {
            strcat(body, "aggregatedReportRequest\"");
        }


//        if(aggregatedReportInterfaceObject->startTimestamp > 0L)
        {
            char timeStamp[BODY_SIZE_MIN];
            sprintf(timeStamp, "%ld", aggregatedReportInterfaceObject->startTimestamp);
            strcat(body, ",\"startTimestamp\":");
            strcat(body, timeStamp);
        }

//        if(aggregatedReportInterfaceObject->endTimestamp> 0L)
        {
            char timeStamp[BODY_SIZE_MIN];
            sprintf(timeStamp, "%ld", aggregatedReportInterfaceObject->endTimestamp);
            strcat(body, ",\"endTimestamp\":");
            strcat(body, timeStamp);
        }

        if(aggregatedReportInterfaceObject->aggregationMethods) {
            strcat(body, ",\"aggregationMethods\":[");

            traverse = aggregatedReportInterfaceObject->aggregationMethods;
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

        if(aggregatedReportInterfaceObject->dimensions) {
            strcat(body, ",\"dimensions\":[");

            traverse = aggregatedReportInterfaceObject->dimensions;
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

        {
            char offsetInt[BODY_SIZE_MIN];
            sprintf(offsetInt, "%d", aggregatedReportInterfaceObject->offset);
            strcat(body, ",\"offset\":");
            strcat(body, offsetInt);
        }

        {
            char limitInt[BODY_SIZE_MIN];
            sprintf(limitInt, "%d", aggregatedReportInterfaceObject->limit);
            strcat(body, ",\"limit\":");
            strcat(body, limitInt);
        }

        if(aggregatedReportInterfaceObject->countOnly) {
            strcat(body, ",\"countOnly\": true");
        }

        if(aggregatedReportInterfaceObject->outputType) {
            strcat(body, ",\"outputType\":\"");
            strcat(body, aggregatedReportInterfaceObject->outputType);
            strcat(body, "\"");
        }

        if(aggregatedReportInterfaceObject->deviceIds) {
            strcat(body, ",\"deviceIds\":[");

            traverse = aggregatedReportInterfaceObject->deviceIds;
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

        if(aggregatedReportInterfaceObject->gatewayIds) {
            strcat(body, ",\"gatewayIds\":[");

            traverse = aggregatedReportInterfaceObject->gatewayIds;
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

        if(aggregatedReportInterfaceObject->componentIds) {
            strcat(body, ",\"componentIds\":[");

            traverse = aggregatedReportInterfaceObject->componentIds;
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

        if(aggregatedReportInterfaceObject->sort) {
            KeyValueParams *traverseKeyValues = aggregatedReportInterfaceObject->sort;
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


        if(aggregatedReportInterfaceObject->filters) {
            AttributeFilterList *attributesList = aggregatedReportInterfaceObject->filters;

            strcat(body, ",\"filters\":{");

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

        strcat(body, "}");

        #if DEBUG
            printf("Prepared BODY is %s\n", body);
        #endif

        doHttpPost(url, headers, body, httpResponseCode, response);

        return true;
    }

    return false;
}
