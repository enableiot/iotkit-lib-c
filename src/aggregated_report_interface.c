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
 * @file aggregated_report_interface.c
 *
 * Provides API to handle Aggregated Report Interface
 */

#include "aggregated_report_interface.h"

/**
 * @defgroup aggregatedreportinterface
 * This is Aggregated Report Interface Module
 *  @{
 */

/**
 * Creates an data object to be used to generate JSON Body in Aggregated Report Interface REST call
 *
 * @return returns the created object if memory is available, otherwise NULL
 */
AggregatedReportInterface *createAggregatedReportInterface() {
    AggregatedReportInterface *newObject = (AggregatedReportInterface *)malloc(sizeof(AggregatedReportInterface));

    if(!newObject) {
        return NULL;
    }

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

/**
 * set report start timestamp
 *
 * @param aggregatedReportInterfaceObject object created using createAggregatedReportInterface()
 * @param startTimestamp time stamp in milliseconds
 */
AggregatedReportInterface *setReportStartTimestamp(AggregatedReportInterface *aggregatedReportInterfaceObject, long long startTimestamp) {
    aggregatedReportInterfaceObject->startTimestamp = startTimestamp;

    return aggregatedReportInterfaceObject;
}

/**
 * set report end timestamp
 *
 * @param aggregatedReportInterfaceObject object created using createAggregatedReportInterface()
 * @param endTimestamp time stamp in milliseconds
 */
AggregatedReportInterface *setReportEndTimestamp(AggregatedReportInterface *aggregatedReportInterfaceObject, long long endTimestamp) {
    aggregatedReportInterfaceObject->endTimestamp = endTimestamp;

    return aggregatedReportInterfaceObject;
}

/**
 * add aggregation methods. Can be called multiple times to add different methods
 *
 * @param aggregatedReportInterfaceObject object created using createAggregatedReportInterface()
 * @param aggregation aggregation method
 */
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

/**
 * add dimension for measurements aggregation. Can be called multiple times to add different dimensions
 *
 * @param aggregatedReportInterfaceObject object created using createAggregatedReportInterface()
 * @param dimension dimension of measurement
 */
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

/**
 * set offset data to return in the response
 *
 * @param aggregatedReportInterfaceObject object created using createAggregatedReportInterface()
 * @param offset offset number
 */
AggregatedReportInterface *setOffset(AggregatedReportInterface *aggregatedReportInterfaceObject, int offset) {
    aggregatedReportInterfaceObject->offset = offset;

    return aggregatedReportInterfaceObject;
}

/**
 * set row limit to return in the response
 *
 * @param aggregatedReportInterfaceObject object created using createAggregatedReportInterface()
 * @param limit row limit number
 */
AggregatedReportInterface *setLimit(AggregatedReportInterface *aggregatedReportInterfaceObject, int limit) {
    aggregatedReportInterfaceObject->limit = limit;

    return aggregatedReportInterfaceObject;
}

/**
 * specifies to return only the count of records that would have returned from the query
 *
 * @param aggregatedReportInterfaceObject object created using createAggregatedReportInterface()
 * @param countOnly 'true' gets only the count, otherwise the complete query response is received
 */
AggregatedReportInterface *setReportCountOnly(AggregatedReportInterface *aggregatedReportInterfaceObject, bool countOnly) {
    aggregatedReportInterfaceObject->countOnly = countOnly;

    return aggregatedReportInterfaceObject;
}

/**
 * specifies the response type
 *
 * @param aggregatedReportInterfaceObject object created using createAggregatedReportInterface()
 * @param outputType the desired response type (json, csv etc.)
 */
AggregatedReportInterface *setOutputType(AggregatedReportInterface *aggregatedReportInterfaceObject, char *outputType) {
    aggregatedReportInterfaceObject->outputType = strdup(outputType);

    return aggregatedReportInterfaceObject;
}

/**
 * add device ID. Can be called multiple times to add different IDs
 *
 * @param aggregatedReportInterfaceObject object created using createAggregatedReportInterface()
 * @param deviceId device ID
 */
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

/**
 * add device gateway ID. Can be called multiple times to add different IDs
 *
 * @param aggregatedReportInterfaceObject object created using createAggregatedReportInterface()
 * @param gatewayId gateway ID
 */
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

/**
 * add component ID. Can be called multiple times to add different IDs
 *
 * @param aggregatedReportInterfaceObject object created using createAggregatedReportInterface()
 * @param componentId component ID
 */
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

/**
 * add sort information. Can be called multiple times to add different sorts
 *
 * @param aggregatedReportInterfaceObject object created using createAggregatedReportInterface()
 * @param name name of the field
 * @param value value of the field (ASC or DESC)
 */
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

/**
 * add attribute filter. Can be called multiple times to add different filters
 *
 * @param aggregatedReportInterfaceObject object created using createAggregatedReportInterface()
 * @param attributeFilter attribute filter object created by createAttributeFilterObject()
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

/**
 * REST API for aggregated report interface
 *
 * @param aggregatedReportInterfaceObject object created using createAggregatedReportInterface()
 * @return returns the result received from server, otherwise NULL
 */
char *aggregatedReportInterface(AggregatedReportInterface *aggregatedReportInterfaceObject) {

    struct curl_slist *headers = NULL;
    char *url;
    char body[BODY_SIZE_MED];
    StringList *traverse = NULL;
    HttpResponse *response = (HttpResponse *)malloc(sizeof(HttpResponse));
    response->code = 0;
    response->data = NULL;

    if(prepareUrl(&url, configurations.base_url, configurations.aggregated_report_interface, NULL)) {
        appendHttpHeader(&headers, HEADER_CONTENT_TYPE_NAME, HEADER_CONTENT_TYPE_JSON);
        appendHttpHeader(&headers, HEADER_AUTHORIZATION, getConfigAuthorizationToken());

        strcpy(body, "{");

//        if(aggregatedReportInterfaceObject->startTimestamp > 0L)
        {
            char timeStamp[BODY_SIZE_MIN];
            sprintf(timeStamp, "%lld", aggregatedReportInterfaceObject->startTimestamp);
            strcat(body, "\"from\":");
            strcat(body, timeStamp);
        }

//        if(aggregatedReportInterfaceObject->endTimestamp> 0L)
        {
            char timeStamp[BODY_SIZE_MIN];
            sprintf(timeStamp, "%lld", aggregatedReportInterfaceObject->endTimestamp);
            strcat(body, ",\"to\":");
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

        doHttpPost(url, headers, body, response);

        return createHttpResponseJson(response);
    }

    return NULL;
}

/** @} */ // end of aggregatedreportinterface
