/*
 * Test Suite for component catalog
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
 * @file test_component_catalog.c
 *
 * Test Suite for component catalog
 */

#include "../src/iotkit.h"

bool testCreateAnComponentCatalog() {
//    char * response = createAnComponentCatalog("funny16", "1.0", "sensor", "Number", "float", true, -150.0f, true, 150.0f, "Degrees Celsius", "timeSeries", NULL);
    char * response = createAnComponentCatalog("actua12", "1.0", "actuator", "Number", "float", true, -150.0f, true, 150.0f, "Degrees Celsius", "timeSeries", "on", "my1", "1-5");
    printf("Response Received :%s\n", response);

    return true;
}
