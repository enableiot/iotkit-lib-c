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

bool testListAllComponentCatalogs() {
    char *response = NULL;
    long httpResponseCode;

    listAllComponentCatalogs(&httpResponseCode, &response);

    printf("Response Received :%s\n", response);

    return true;
}

bool testGetComponentCatalogDetails() {
    char *response = NULL;
    long httpResponseCode;

    getComponentCatalogDetails("actua13.v1.0", &httpResponseCode, &response);

    printf("Response Received :%s\n", response);

    return true;
}

bool testCreateAnComponentCatalog() {
    char *response = NULL;
    long httpResponseCode;

    ComponentCatalog *cmpObject = createComponentCatalogObject("actua13", "1.0", "actuator", "Number", "float", "Degrees Celsius", "timeSeries");
    addMinValue(cmpObject, -150.0f);
    addMaxValue(cmpObject, 150.0f);
    addCommandString(cmpObject, "on");

    addCommandParams(cmpObject, "my1", "1-5");
    addCommandParams(cmpObject, "my2", "1,2");
    addCommandParams(cmpObject, "my3", "5,6,7");

    createAnComponentCatalog(cmpObject, &httpResponseCode, &response);
    printf("Response Received :%s\n", response);

    return true;
}

bool testUpdateAnComponentCatalog() {
    char *response = NULL;
    long httpResponseCode;

    ComponentCatalog *cmpObject = createComponentCatalogObject(NULL, NULL, "actuator", "Number", "integer", "Degrees Celsius2", "timeSeries");
    addMinValue(cmpObject, -150.0f);
    addMaxValue(cmpObject, 150.0f);
    addCommandString(cmpObject, "off");

    addCommandParams(cmpObject, "my12", "1-5");
    addCommandParams(cmpObject, "my22", "5-10");

    updateAnComponentCatalog(cmpObject, "actua13.v1.0", &httpResponseCode, &response);
    printf("Response Received :%s\n", response);

    return true;
}
