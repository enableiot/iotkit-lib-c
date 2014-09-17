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
    char * response = createADevice("02-00-86-81-77-bf", "02-00-86-81-77-bf", "maha32");
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
