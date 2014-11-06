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
 * @file aggregated_report_interface.h
 * @brief Implementation of Aggregated Report Interface
 *
 * Provides features for communication with IoT Cloud server
 */


#ifndef __AGGREGATED_REPORT_INTERFACE_H
#define __AGGREGATED_REPORT_INTERFACE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "iotkit.h"

typedef struct _AggregatedReportInterface {

    char *msgType;
    long startTimestamp;
    long endTimestamp;
    StringList *aggregationMethods;
    StringList *dimensions;
    int offset;
    int limit;
    bool countOnly;
    char *outputType;
    StringList *gatewayIds;
    StringList *deviceIds;
    StringList *componentIds;
    KeyValueParams *sort;
    AttributeFilterList *filters;
} AggregatedReportInterface;

char *aggregatedReportInterface(AggregatedReportInterface *aggregatedReportInterfaceObject);

#ifdef __cplusplus
}
#endif

#endif
