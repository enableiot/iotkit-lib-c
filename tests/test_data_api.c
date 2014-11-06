/*
 * Test Suite for data submit and retrieval APIs
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
 * @file test_data_api.c
 *
 * Test Suite for data submit and retrieval
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
