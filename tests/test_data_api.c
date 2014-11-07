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

#include "../src/data_api.h"

bool testSubmitData() {
    char *response = NULL;

    response = submitData("madras9", "26.15", "45.540164", "-122.926048", "124.3");
    printf("Response Received :%s\n", response);

    return true;
}

bool testRetrieveData() {
    RetrieveData *retrieveObj;
    char *response = NULL;

    retrieveObj = createRetrieveDataObject(1410387088000, 1415301870434);
    addDeviceId(retrieveObj, "02-00-a7-81-77-ff");
    addDeviceId(retrieveObj, "c0-3f-d5-60-d0-74");
    addSensorId(retrieveObj, "madras7");
    addSensorId(retrieveObj, "madras9");

    response = retrieveData(retrieveObj);
    printf("Response Received :%s\n", response);

    return true;
}
