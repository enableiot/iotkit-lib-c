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

bool testGetUserInformation() {
    char *response = NULL;
    long httpResponseCode;

// pass user ID explicitly
//    getUserInformation("544c093c676e33cf6a779070", &httpResponseCode, &response);

// or pass NULL to consider own user ID
    getUserInformation(NULL, &httpResponseCode, &response);

    printf("Response Received :%s\n", response);

    if(httpResponseCode == 200) {
        return true;
    }

    return false;
}

bool testAcceptTermsAndConditions() {
    char *response = NULL;
    long httpResponseCode;

// pass user ID explicitly
//    getUserInformation("544c093c676e33cf6a779070", &httpResponseCode, &response);

// or pass NULL to consider own user ID
    acceptTermsAndConditions(NULL, true, &httpResponseCode, &response);

    printf("Response Received :%s\n", response);

    if(httpResponseCode == 200) {
        return true;
    }

    return false;
}

bool testRequestChangePassword() {
    char *response = NULL;
    long httpResponseCode;

    requestChangePassword("pradeep.chenthati@aricent.com", &httpResponseCode, &response);

    printf("Response Received :%s\n", response);

    if(httpResponseCode == 200) {
        return true;
    }

    return false;
}

bool testUpdateForgotPassword() {
    char *response = NULL;
    long httpResponseCode;

    updateForgotPassword("YM93XKO1lbIrBHek", "Password2", &httpResponseCode, &response);

    printf("Response Received :%s\n", response);

    if(httpResponseCode == 200) {
        return true;
    }

    return false;
}

bool testChangePassword() {
    char *response = NULL;
    long httpResponseCode;
    changePassword("544c093c676e33cf6a779070", "Password2", "Password1", &httpResponseCode, &response);

    printf("Response Received :%s\n", response);

    if(httpResponseCode == 200) {
        return true;
    }

    return false;
}
