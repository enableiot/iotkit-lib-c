/*
 * Test Suite for Advanced Data Inquiry
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
 * @file test_advanced_data_inquiry.c
 *
 * Test Suite for Advanced Data Inquiry
 */

#include "../src/advanced_data_inquiry.h"

bool testAdvancedDataInquiry() {
    char *response = NULL;

    AttributeFilter *devCompAttributeFilter1 = NULL, *devCompAttributeFilter2 = NULL;
    AttributeFilter *measurementAttributeFilter1 = NULL, *measurementAttributeFilter2 = NULL;
    AttributeFilter *valueFilter = NULL;
    AdvancedDataInquiry *advancedDataInquiryObj = createAdvancedDataInquiryObject();

    addGatewayIds(advancedDataInquiryObj, "02-00-a7-81-77-ff");
    addGatewayIds(advancedDataInquiryObj, "02-00-86-81-77-14");
    addGatewayIds(advancedDataInquiryObj, "02-00-86-81-77-15");

    addDeviceIds(advancedDataInquiryObj, "02-00-a7-81-77-ff");
    addDeviceIds(advancedDataInquiryObj, "02-00-86-81-77-18");
    addDeviceIds(advancedDataInquiryObj, "02-00-86-81-77-19");

    addComponentIds(advancedDataInquiryObj, "madras7");
    addComponentIds(advancedDataInquiryObj, "madras9");
    addComponentIds(advancedDataInquiryObj, "garage3");

    setStartTimestamp(advancedDataInquiryObj, 1391971083468L);
    setEndTimestamp(advancedDataInquiryObj, 1415301870434);

    addReturnedMeasureAttributes(advancedDataInquiryObj, "attr_1");
    addReturnedMeasureAttributes(advancedDataInquiryObj, "attr_2");
    addReturnedMeasureAttributes(advancedDataInquiryObj, "attr_3");

    setShowMeasureLocation(advancedDataInquiryObj, true);

    devCompAttributeFilter1 = createAttributeFilterObject("filter_1");
    addAttributeFilterValues(devCompAttributeFilter1, "value1");
    addAttributeFilterValues(devCompAttributeFilter1, "value2");
    addAttributeFilterValues(devCompAttributeFilter1, "value3");

    devCompAttributeFilter2 = createAttributeFilterObject("filter_2");
    addAttributeFilterValues(devCompAttributeFilter2, "value11");
    addAttributeFilterValues(devCompAttributeFilter2, "value22");
    addAttributeFilterValues(devCompAttributeFilter2, "value33");

    addDevCompAttributeFilter(advancedDataInquiryObj, devCompAttributeFilter1);
    addDevCompAttributeFilter(advancedDataInquiryObj, devCompAttributeFilter2);

    measurementAttributeFilter1 = createAttributeFilterObject("mfilter_1");
    addAttributeFilterValues(measurementAttributeFilter1, "mValue1");
    addAttributeFilterValues(measurementAttributeFilter1, "mValue2");
    addAttributeFilterValues(measurementAttributeFilter1, "mValue3");

    measurementAttributeFilter2 = createAttributeFilterObject("mfilter_2");
    addAttributeFilterValues(measurementAttributeFilter2, "mValue11");
    addAttributeFilterValues(measurementAttributeFilter2, "mValue22");
    addAttributeFilterValues(measurementAttributeFilter2, "mValue33");

    addMeasurementAttributeFilter(advancedDataInquiryObj, measurementAttributeFilter1);
    addMeasurementAttributeFilter(advancedDataInquiryObj, measurementAttributeFilter2);


    valueFilter = createAttributeFilterObject("value");
    addAttributeFilterValues(valueFilter, "filter_value1");
    addAttributeFilterValues(valueFilter, "filter_value2");
    addAttributeFilterValues(valueFilter, "filter_value3");
    addValueFilter(advancedDataInquiryObj, valueFilter);

    setComponentRowLimit(advancedDataInquiryObj, 5);
    setCountOnly(advancedDataInquiryObj, true);

    addSortInfo(advancedDataInquiryObj, "sortField1", "ASC");
    addSortInfo(advancedDataInquiryObj, "sortField2", "DESC");


    response = advancedDataInquiry(advancedDataInquiryObj);

    printf("Response Received :%s\n", response);

    /*if(response->code == 200) {
        return true;
    }*/

    return false;
}
