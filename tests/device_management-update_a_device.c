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

#include "device_management.h"

int main(void) {
    char *response = NULL;
    DeviceCreationObj *createDeviceObj;

    iotkit_init();

    createDeviceObj = createDeviceCreationObject(NULL, "ff-32-dd-ba-bb-cc", "anddr34e3");
    addLocInfo(createDeviceObj, "55.540164", "-112.926048", "25.0");
    addTagInfo(createDeviceObj, "United States of America");
    addTagInfo(createDeviceObj, "Oregon State");
    addTagInfo(createDeviceObj, "Hillsboro City");
    addAttributesInfo(createDeviceObj, "vendor", "Intel Corp.");
    addAttributesInfo(createDeviceObj, "platform", "x86");
    addAttributesInfo(createDeviceObj, "os", "Ubuntu 14.04");

    response = updateADevice(createDeviceObj);
    printf("Response Received :%s\n", response);

    iotkit_cleanup();

    if(checkResponseValue(response, 200) == true) {
        exit(EXIT_SUCCESS);
    }

    exit(EXIT_FAILURE);
}
