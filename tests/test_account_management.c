/*
 * Test Suite for Account Management
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
 * @file test_account_management.c
 *
 * Test Suite for Account Management
 */

#include "../src/account_management.h"

bool testCreateAnAccount() {
    char *response = NULL;
    long httpResponseCode;

    createAnAccount("willitcreate2", &httpResponseCode, &response);

    printf("Response Received :%s\n", response);

    if(httpResponseCode == 201) {
        return true;
    }

    return false;
}

bool testGetAccountInformation() {
    char *response = NULL;
    long httpResponseCode;

    getAccountInformation(&httpResponseCode, &response);

    printf("Response Received :%s\n", response);

    if(httpResponseCode == 200) {
        return true;
    }

    return false;
}

bool testGetAccountActivationCode() {
    char *response = NULL;
    long httpResponseCode;

    getAccountActivationCode(&httpResponseCode, &response);

    printf("Response Received :%s\n", response);

    if(httpResponseCode == 200) {
        return true;
    }

    return false;
}

bool testRenewAccountActivationCode() {
    char *response = NULL;
    long httpResponseCode;

    renewActivationCode(&httpResponseCode, &response);

    printf("Response Received :%s\n", response);

    if(httpResponseCode == 200) {
        return true;
    }

    return false;
}

bool testUpdateAnAccount() {
    char *response = NULL;
    long httpResponseCode;
    // TODO: json object needs to be sent for updation

    updateAnAccount("willitcreate2", &httpResponseCode, &response);

    printf("Response Received :%s\n", response);

    if(httpResponseCode == 200) {
        return true;
    }

    return false;
}

bool testDeleteAnAccount() {
    char *response = NULL;
    long httpResponseCode;

    deleteAnAccount(&httpResponseCode, &response);

    printf("Response Received :%s\n", response);

    if(httpResponseCode == 204) {
        return true;
    }

    return false;
}

bool testGetUserAssociatedWithAccount() {
    char *response = NULL;
    long httpResponseCode;

    getUserAssociatedWithAccount(&httpResponseCode, &response);

    printf("Response Received :%s\n", response);

    if(httpResponseCode == 200) {
        return true;
    }

    return false;
}

bool testAddAnUserToAccount() {
    char *response = NULL;
    long httpResponseCode;

    addAnUserToAccount("5cf1f891-b388-4795-8abc-b604ded6b163", "53fe452fd6e2061551153a88", false, &httpResponseCode, &response);

    printf("Response Received :%s\n", response);

    if(httpResponseCode == 200) {
        return true;
    }

    return false;
}

/*
bool testUpdateUserAssociatedWithAccount() {
    UpdateUserAccount *userData = NULL;
    char *response = NULL;
    long httpResponseCode;

    userData = createUpdateUserAccountObject();
    addUpdateUserAccountAttributes(userData, "phone", "5036568978");
    addUpdateUserAccountAttributes(userData, "new_name", "new_value");
    //addUpdateUserAccountEmail(userData, "pradyp7tmp@gmail.com");
    addUpdateUserAccountTerms(userData, true);
    addUpdateUserAccountVerified(userData, true);

    updateUserAssociatedWithAccount(userData, &httpResponseCode, &response);

    printf("Response Received :%s\n", response);

    if(httpResponseCode == 200) {
        return true;
    }

    return false;
}
*/
