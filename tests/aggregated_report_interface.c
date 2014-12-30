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

#include "../src/aggregated_report_interface.h"

long long getCurrentTimeInMillis() {
    long elapsedtime = -1L;
    long long currentTimeInMills;

    time(&elapsedtime);

    currentTimeInMills = (long long)elapsedtime * 1000L;

    return currentTimeInMills;
}

int main(void) {
    char *response = NULL;
    AttributeFilter *valueFilter = NULL;
    AggregatedReportInterface *aggregatedReportInterfaceObj = NULL;

    iotkit_init();

    aggregatedReportInterfaceObj = createAggregatedReportInterface();

    setReportStartTimestamp(aggregatedReportInterfaceObj, 1413504889801L);
    setReportEndTimestamp(aggregatedReportInterfaceObj, getCurrentTimeInMillis());

    addAggregationMethods(aggregatedReportInterfaceObj, "average");
    addAggregationMethods(aggregatedReportInterfaceObj, "min");
    addAggregationMethods(aggregatedReportInterfaceObj, "max");

  /*  addDimensions(aggregatedReportInterfaceObj, "dimen1");
    addDimensions(aggregatedReportInterfaceObj, "dimen2");
    addDimensions(aggregatedReportInterfaceObj, "dimen3");

    setOffset(aggregatedReportInterfaceObj, 0);
    setLimit(aggregatedReportInterfaceObj, 0); */

    setReportCountOnly(aggregatedReportInterfaceObj, true);
    setOutputType(aggregatedReportInterfaceObj, "json");

    addReportDeviceIds(aggregatedReportInterfaceObj, "ff-32-dd-ba-bb-cc");
    addReportDeviceIds(aggregatedReportInterfaceObj, "02-00-86-81-77-18");
    addReportDeviceIds(aggregatedReportInterfaceObj, "02-00-86-81-77-19");

    addReportGatewayIds(aggregatedReportInterfaceObj, "ff-32-dd-ba-bb-cc");
    addReportGatewayIds(aggregatedReportInterfaceObj, "02-00-86-81-77-14");
    addReportGatewayIds(aggregatedReportInterfaceObj, "02-00-86-81-77-15");

    addReportComponentIds(aggregatedReportInterfaceObj, "garage1");
    addReportComponentIds(aggregatedReportInterfaceObj, "garage2");
    addReportComponentIds(aggregatedReportInterfaceObj, "madras9");

    /*addReportSortInfo(aggregatedReportInterfaceObj, "sortField1", "ASC");
    addReportSortInfo(aggregatedReportInterfaceObj, "sortField2", "DESC");

/////////////////////////
    valueFilter = createAttributeFilterObject("filter_1");
    addAttributeFilterValues(valueFilter, "value1");
    addAttributeFilterValues(valueFilter, "value2");

    addFilters(aggregatedReportInterfaceObj, valueFilter);
*/

    response = aggregatedReportInterface(aggregatedReportInterfaceObj);

    printf("Response Received :%s\n", response);

    iotkit_cleanup();

    if(checkResponseValue(response, 200) == true) {
        exit(EXIT_SUCCESS);
    }

    exit(EXIT_FAILURE);
}
