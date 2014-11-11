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

AdvancedDataInquiry *createAdvancedDataInquiryObject();
AdvancedDataInquiry *setMessageType(AdvancedDataInquiry *advancedDataInquiryObject, char *msgType);
AdvancedDataInquiry *addGatewayIds(AdvancedDataInquiry *advancedDataInquiryObject, char *gatewayId);
AdvancedDataInquiry *addDeviceIds(AdvancedDataInquiry *advancedDataInquiryObject, char *deviceId);
AdvancedDataInquiry *addComponentIds(AdvancedDataInquiry *advancedDataInquiryObject, char *componentId);
AdvancedDataInquiry *setStartTimestamp(AdvancedDataInquiry *advancedDataInquiryObject, long startTimestamp);
AdvancedDataInquiry *setEndTimestamp(AdvancedDataInquiry *advancedDataInquiryObject, long endTimestamp);
AdvancedDataInquiry *addReturnedMeasureAttributes(AdvancedDataInquiry *advancedDataInquiryObject, char *attribute);
AdvancedDataInquiry *setShowMeasureLocation(AdvancedDataInquiry *advancedDataInquiryObject, bool measureLocation);
AttributeFilter *createAttributeFilterObject(char *filterName);
AttributeFilter *addAttributeFilterValues(AttributeFilter *attributeFilter, char *filterValue);
AdvancedDataInquiry *addDevCompAttributeFilter(AdvancedDataInquiry *advancedDataInquiryObject, AttributeFilter *attributeFilter);
AdvancedDataInquiry *addMeasurementAttributeFilter(AdvancedDataInquiry *advancedDataInquiryObject, AttributeFilter *attributeFilter);
AdvancedDataInquiry *addValueFilter(AdvancedDataInquiry *advancedDataInquiryObject, AttributeFilter *attributeFilter);
AdvancedDataInquiry *setComponentRowLimit(AdvancedDataInquiry *advancedDataInquiryObject, int componentRowLimit);
AdvancedDataInquiry *setCountOnly(AdvancedDataInquiry *advancedDataInquiryObject, bool countOnly);
AdvancedDataInquiry *addSortInfo(AdvancedDataInquiry *advancedDataInquiryObject, char *name, char *value);

char *advancedDataInquiry(AdvancedDataInquiry *advancedDataInquiryObject);

#ifdef __cplusplus
}
#endif

#endif
