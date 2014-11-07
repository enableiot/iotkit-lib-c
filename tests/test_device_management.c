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

#include "../src/device_management.h"

bool testValidateDeviceToken() {
    char *response = NULL;

    response = validateDeviceToken();

    printf("Response Received :%s\n", response);

    return true;
}

bool testListAllDevices() {
    char *response = NULL;

    response = listAllDevices();

    printf("Response Received :%s\n", response);

    return true;
}

bool testGetMyDeviceInfo() {
    char *response = NULL;

    response = getMyDeviceInfo();

    printf("Response Received :%s\n", response);

    return true;
}

bool testGetOneDeviceInfo() {
    char *response = NULL;

    response = getOneDeviceInfo("02-00-a7-81-77-ff");

    printf("Response Received :%s\n", response);

    return true;
}

bool testCreateADevice() {
    DeviceCreationObj *createDeviceObj;
    char *response = NULL;

    createDeviceObj = createDeviceCreationObject("02-00-a7-81-77-ff", "02-00-a7-81-77-ff", "anddre4");
    addLocInfo(createDeviceObj, "45.540164", "-122.926048", "55.0");
    addTagInfo(createDeviceObj, "USA");
    addTagInfo(createDeviceObj, "Oregon");
    addTagInfo(createDeviceObj, "Hillsboro");
    addAttributesInfo(createDeviceObj, "vendor", "Intel");
    addAttributesInfo(createDeviceObj, "platform", "x86");
    addAttributesInfo(createDeviceObj, "os", "Ubuntu");

    response = createADevice(createDeviceObj);
    printf("Response Received :%s\n", response);

    return true;
}

bool testUpdateADevice() {
    DeviceCreationObj *createDeviceObj;
    char *response = NULL;

    createDeviceObj = createDeviceCreationObject(NULL, "02-00-a7-81-77-ff", "anddre4");
    addLocInfo(createDeviceObj, "55.540164", "-112.926048", "25.0");
    addTagInfo(createDeviceObj, "United States of America");
    addTagInfo(createDeviceObj, "Oregon State");
    addTagInfo(createDeviceObj, "Hillsboro City");
    addAttributesInfo(createDeviceObj, "vendor", "Intel Corp.");
    addAttributesInfo(createDeviceObj, "platform", "x86");
    addAttributesInfo(createDeviceObj, "os", "Ubuntu 14.04");

    response = updateADevice(createDeviceObj);
    printf("Response Received :%s\n", response);

    return true;
}

bool testActivateADevice(char *authCode) {
    char *response = NULL;

    response = activateADevice(authCode);
    printf("Response Received :%s\n", response);

    return true;
}

bool testDeleteADevice() {
    char *response = NULL;

    response = deleteADevice("02-00-a7-81-77-f1");
    printf("Response Received :%s\n", response);

    return true;
}

bool testAddComponent() {
    char *response = NULL;

    response = addComponent("madras9", "temperature.v1.0");
    printf("Response Received :%s\n", response);

    return true;
}

bool testDeleteComponent() {
    char *response = NULL;

    response = deleteComponent("madras7");
    printf("Response Received :%s\n", response);

    return true;
}

bool testDeviceActivationStatus() {
    bool isActivated = isDeviceActivated();

    if(isActivated) {
        puts("Device activated : true");
    } else {
        puts("Device activated : false");
    }

    return true;
}

bool testSensorRegistrationStatus() {
    if(isSensorRegistered("madras7")) {
        printf("Yes, sensor is already registered !!\n");
    } else {
        printf("No, sensor is not yet registered !!\n");
    }

    return true;
}

bool testGetSensorId() {
    printf("Sensor id for \"%s\" is :%s\n", "madras7", getSensorComponentId("madras7"));

    return true;
}

bool testListAllTagsForDevices() {
    char *response = NULL;

    response = listAllTagsForDevices();
    printf("Response Received :%s\n", response);

    return true;
}

bool testListAllAttributesForDevices() {
    char *response = NULL;

    response = listAllAttributesForDevices();
    printf("Response Received :%s\n", response);

    return true;
}
