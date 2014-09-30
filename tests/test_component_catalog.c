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

#include "../src/component_catalog.h"

bool testCreateAnComponentCatalog() {
//    char * response = createAnComponentCatalog("funny16", "1.0", "sensor", "Number", "float", true, -150.0f, true, 150.0f, "Degrees Celsius", "timeSeries", NULL);

    ComponentCatalog *cmpObject = createComponentCatalogObject("actua12", "1.0", "actuator", "Number", "float", "Degrees Celsius", "timeSeries");
    addMinValue(cmpObject, -150.0f);
    addMaxValue(cmpObject, 150.0f);
    addCommandString(cmpObject, "on");

    addCommandParams(cmpObject, "my1", "1-5");
    addCommandParams(cmpObject, "my2", "1,2");
    addCommandParams(cmpObject, "my3", "5,6,7");

    char * response = createAnComponentCatalog(cmpObject);
    printf("Response Received :%s\n", response);

    return true;
}

bool testUpdateAnComponentCatalog() {
    ComponentCatalog *cmpObject = createComponentCatalogObject(NULL, NULL, "actuator", "Number", "integer", "Degrees Celsius", "timeSeries");
    addMinValue(cmpObject, -150.0f);
    addMaxValue(cmpObject, 150.0f);
    addCommandString(cmpObject, "on");

    addCommandParams(cmpObject, "my1", "1-5");
    addCommandParams(cmpObject, "my2", "5-10");

    char * response = updateAnComponentCatalog(cmpObject);
    printf("Response Received :%s\n", response);

    return true;
}
