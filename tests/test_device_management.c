/*
 * Test to create a device
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
 * @file testCreateADevice.c
 *
 * Test to create a device
 */

#include "../src/iotkit.h"

bool testCreateADevice() {
    char * response = createADevice("02-00-86-81-77-cf", "02-00-86-81-77-cf", "maha35");
    printf("Response Received :%s\n", response);

    return true;
}

bool testActivateADevice(char *authCode) {

    char * response = activateADevice(authCode);
    printf("Response Received :%s\n", response);

    return true;
}

bool testAddComponent() {

    char * response = addComponent("madras7", "temperature.v1.0");
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
