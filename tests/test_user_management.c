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
#include "../lib/cJSON/cJSON.h"

bool testCreateAnUser() {
    cJSON *json, *jitem;
    char *response = NULL;
    int httpResponseCode;

    response = createAnUser("pradeep.chenthati@aricent.com", "Password1");

    printf("Response Received :%s\n", response);

    // parse the file
    json = cJSON_Parse(response);
    if (!json) {
        fprintf(stderr,"Error Parsing response: [%s]\n",cJSON_GetErrorPtr());
        return;
    }
    else {
        jitem = cJSON_GetObjectItem(json, "data");
        if(jitem && isJsonNumber(jitem)) {
            httpResponseCode = jitem->valueint;

            if(httpResponseCode == 201) {
                printf("testCreateAnUser:: Test Case Passed\n");
                return true;
            }
        }
    }

    return false;
}

bool testGetUserInformation() {
    char *response = NULL;

// pass user ID explicitly
//    getUserInformation("544c093c676e33cf6a779070", &httpResponseCode, &response);

// or pass NULL to consider own user ID
    response = getUserInformation("545aebf56329f63c4518b1ab");

    printf("Response Received :%s\n", response);

    /*if(httpResponseCode == 200) {
        return true;
    }*/

    return true;
}

bool testUpdateUserAttributes() {
    char *response = NULL;
    KeyValueParams *attributesList = NULL, *attribute1 = NULL, *attribute2 = NULL, *attribute3 = NULL;

    attribute3 = (KeyValueParams *)malloc(sizeof(KeyValueParams));
    attribute3->name = strdup("new");
    attribute3->value = strdup("next_string_value");
    attribute3->next = NULL;

    attribute2 = (KeyValueParams *)malloc(sizeof(KeyValueParams));
    attribute2->name = strdup("another_attribute");
    attribute2->value = strdup("another_value");
    attribute2->next = attribute3;

    attribute1 = (KeyValueParams *)malloc(sizeof(KeyValueParams));
    attribute1->name = strdup("phone");
    attribute1->value = strdup("123456789");
    attribute1->next = attribute2;

    attributesList = attribute1;

// pass user ID explicitly
//    getUserInformation("544c093c676e33cf6a779070", &httpResponseCode, &response);

// or pass NULL to consider own user ID
    response = updateUserAttributes(NULL, attributesList);

    printf("Response Received :%s\n", response);

    /*if(httpResponseCode == 200) {
        return true;
    }*/

    return true;
}

bool testAcceptTermsAndConditions() {
    char *response = NULL;

// pass user ID explicitly
//    getUserInformation("544c093c676e33cf6a779070", &httpResponseCode, &response);

// or pass NULL to consider own user ID
    response = acceptTermsAndConditions(NULL, true);

    printf("Response Received :%s\n", response);

    /*if(httpResponseCode == 200) {
        return true;
    }*/

    return true;
}

bool testDeleteAUser() {
    char *response = NULL;

// pass user ID explicitly
//    deleteAUser("544c093c676e33cf6a779070", &httpResponseCode, &response);

// or pass NULL to consider own user ID
    response = deleteAUser(NULL);

    printf("Response Received :%s\n", response);

    /*if(httpResponseCode == 204) {
        return true;
    }*/

    return true;
}

bool testRequestChangePassword() {
    char *response = NULL;

    response = requestChangePassword("pradeep.chenthati@aricent.com");

    printf("Response Received :%s\n", response);

    /*if(httpResponseCode == 200) {
        return true;
    }*/

    return true;
}

bool testUpdateForgotPassword() {
    char *response = NULL;

    response = updateForgotPassword("gdFIZRcKh48JkcGm", "Password2");

    printf("Response Received :%s\n", response);

    /*if(httpResponseCode == 200) {
        return true;
    }*/

    return true;
}

bool testChangePassword() {
    char *response = NULL;

    response = changePassword("pradeep.chenthati@aricent.com", "Password2", "Password1");

    printf("Response Received :%s\n", response);

    /*if(httpResponseCode == 200) {
        return true;
    }*/

    return true;
}
