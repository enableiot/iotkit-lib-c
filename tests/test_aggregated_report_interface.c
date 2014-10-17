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

#include "../src/aggregated_report_interface.h"

bool testAggregatedReportInterface() {
    char *response = NULL;
    long httpResponseCode;
    AttributeFilter *valueFilter = NULL;
    AggregatedReportInterface *aggregatedReportInterfaceObj = createAggregatedReportInterface();


    setReportStartTimestamp(aggregatedReportInterfaceObj, 1391971083468L);
    setReportEndTimestamp(aggregatedReportInterfaceObj, 1413504889801L);

    addAggregationMethods(aggregatedReportInterfaceObj, "aggr1");
    addAggregationMethods(aggregatedReportInterfaceObj, "aggr2");
    addAggregationMethods(aggregatedReportInterfaceObj, "aggr3");

    addDimensions(aggregatedReportInterfaceObj, "dimen1");
    addDimensions(aggregatedReportInterfaceObj, "dimen2");
    addDimensions(aggregatedReportInterfaceObj, "dimen3");

    setOffset(aggregatedReportInterfaceObj, 0);
    setLimit(aggregatedReportInterfaceObj, 0);

    setReportCountOnly(aggregatedReportInterfaceObj, true);
    setOutputType(aggregatedReportInterfaceObj, "json");

    addReportDeviceIds(aggregatedReportInterfaceObj, "02-00-86-81-77-17");
    addReportDeviceIds(aggregatedReportInterfaceObj, "02-00-86-81-77-18");
    addReportDeviceIds(aggregatedReportInterfaceObj, "02-00-86-81-77-19");

    addReportGatewayIds(aggregatedReportInterfaceObj, "02-00-86-81-77-13");
    addReportGatewayIds(aggregatedReportInterfaceObj, "02-00-86-81-77-14");
    addReportGatewayIds(aggregatedReportInterfaceObj, "02-00-86-81-77-15");

    addReportComponentIds(aggregatedReportInterfaceObj, "garage1");
    addReportComponentIds(aggregatedReportInterfaceObj, "garage2");
    addReportComponentIds(aggregatedReportInterfaceObj, "garage3");

    addReportSortInfo(aggregatedReportInterfaceObj, "sortField1", "ASC");
    addReportSortInfo(aggregatedReportInterfaceObj, "sortField2", "DESC");

/////////////////////////
    valueFilter = createAttributeFilterObject("filter_1");
    addAttributeFilterValues(valueFilter, "value1");
    addAttributeFilterValues(valueFilter, "value2");

    addFilters(aggregatedReportInterfaceObj, valueFilter);


    aggregatedReportInterface(aggregatedReportInterfaceObj, &httpResponseCode, &response);

    printf("Response Received :%s\n", response);

    if(httpResponseCode == 200) {
        return true;
    }

    return false;
}