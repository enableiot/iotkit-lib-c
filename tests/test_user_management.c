/*
 * Test Suite for User Management
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
 * @file test_user_management.c
 *
 * Test Suite for User Management
 */

#include "../src/iotkit.h"

bool testCreateAnUser() {
    char *response = NULL;
    long httpResponseCode;

    createAnUser("pradeep.chenthati@aricent.com", "Password1", &httpResponseCode, &response);

    printf("Response Received :%s\n", response);

    if(httpResponseCode == 201) {
        return true;
    }

    return false;
}
