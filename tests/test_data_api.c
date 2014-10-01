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

bool testRetrieveData() {
    RetrieveData *retrieveObj;

    retrieveObj = createRetrieveDataObject(1410387088000, 1412198993108);
    addDeviceId(retrieveObj, "02-00-86-81-77-cf");
    addDeviceId(retrieveObj, "c0-3f-d5-60-d0-74");
    addSensorId(retrieveObj, "madras7");
    addSensorId(retrieveObj, "madras9");

    char * response = retrieveData(retrieveObj);
    printf("Response Received :%s\n", response);

    return true;
}
