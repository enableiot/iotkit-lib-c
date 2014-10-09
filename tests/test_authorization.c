/*
 * Authorization API module to communicate with IoT Cloud via REST APIs
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
 * @file testauthorization.c
 * @brief Implementation of Authorization API
 *
 * Provides features for communication with IoT Cloud server
 */

#include "../src/iotkit.h"

bool testValidateAuthorizationToken() {
    char *response = NULL;
    long httpResponseCode;

    validateAuthorizationToken(&httpResponseCode, &response);
    printf("Response Received :%s\n", response);

    return true;
}


bool testGetNewAuthorizationToken() {
    char *response = NULL;
    long httpResponseCode;

    getNewAuthorizationToken("pradeep.chenthati@aricent.com", "Password1", &httpResponseCode, &response);
    printf("Response Received :%s\n", response);

    return true;
}

bool testGetAuthorizationTokenMeInfo() {
    char *response = NULL;
    long httpResponseCode;

    getAuthorizationTokenMeInfo(&httpResponseCode, &response);
    printf("Response Received :%s\n", response);

    return true;
}
