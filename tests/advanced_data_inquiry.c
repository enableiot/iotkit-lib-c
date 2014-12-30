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

#include "../src/advanced_data_inquiry.h"

long long getCurrentTimeInMillis() {
    long elapsedtime = -1L;
    long long currentTimeInMills;

    time(&elapsedtime);

    currentTimeInMills = (long long)elapsedtime * 1000L;

    return currentTimeInMills;
}

int main(void) {
    char *response = NULL;

    iotkit_init();

    AttributeFilter *devCompAttributeFilter1 = NULL, *devCompAttributeFilter2 = NULL;
    AttributeFilter *measurementAttributeFilter1 = NULL, *measurementAttributeFilter2 = NULL;
    AttributeFilter *valueFilter = NULL;
    AdvancedDataInquiry *advancedDataInquiryObj = createAdvancedDataInquiryObject();

    addGatewayIds(advancedDataInquiryObj, "ff-32-dd-ba-bb-cc");
    addGatewayIds(advancedDataInquiryObj, "02-00-86-81-77-14");
    addGatewayIds(advancedDataInquiryObj, "02-00-86-81-77-15");

    addDeviceIds(advancedDataInquiryObj, "ff-32-dd-ba-bb-cc");
    addDeviceIds(advancedDataInquiryObj, "02-00-86-81-77-18");
    addDeviceIds(advancedDataInquiryObj, "02-00-86-81-77-19");

    addComponentIds(advancedDataInquiryObj, "madras7");
    addComponentIds(advancedDataInquiryObj, "madras9");
    addComponentIds(advancedDataInquiryObj, "garage3");

    setStartTimestamp(advancedDataInquiryObj, 1415301870434L);
    setEndTimestamp(advancedDataInquiryObj, getCurrentTimeInMillis());

    addReturnedMeasureAttributes(advancedDataInquiryObj, "attr_1");
    addReturnedMeasureAttributes(advancedDataInquiryObj, "attr_2");
    addReturnedMeasureAttributes(advancedDataInquiryObj, "attr_3");

    setShowMeasureLocation(advancedDataInquiryObj, true);

    /*devCompAttributeFilter1 = createAttributeFilterObject("filter_1");
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
*/

    response = advancedDataInquiry(advancedDataInquiryObj);

    printf("Response Received :%s\n", response);

    iotkit_cleanup();

    if(checkResponseValue(response, 200) == true) {
        exit(EXIT_SUCCESS);
    }

    exit(EXIT_FAILURE);
}
