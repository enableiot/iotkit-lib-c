/*
 * Advanced Data Inquiry API module to communicate with IoT Cloud via REST APIs
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
 * @file advanced_data_inquiry.c
 * @brief Implementation of Advanced Data Inquiry API
 *
 * Provides features for communication with IoT Cloud server
 */


#ifndef __ADVANCED_DATA_INQUIRY_H
#define __ADVANCED_DATA_INQUIRY_H

#ifdef __cplusplus
extern "C" {
#endif

#include "iotkit.h"

typedef struct _AdvancedDataInquiry {

    char *msgType;
    StringList *gatewayIds;
    StringList *deviceIds;
    StringList *componentIds;

    long startTimestamp;
    long endTimestamp;

    StringList *returnedMeasureAttributes;

    bool showMeasureLocation;

    AttributeFilterList *devCompAttributeFilter;
    AttributeFilterList *measurementAttributeFilter;
    AttributeFilter *valueFilter;

    int componentRowLimit;
    bool countOnly;
    KeyValueParams *sort;


} AdvancedDataInquiry;

char *advancedDataInquiry(AdvancedDataInquiry *advancedDataInquiryObject);

#ifdef __cplusplus
}
#endif

#endif
