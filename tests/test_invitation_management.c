/*
 * Test Suite for Invitation Management
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
 * @file test_invitation_management.c
 *
 * Test Suite for Invitation Management
 */

#include "../src/iotkit.h"

bool testGetListOfInvitation() {
    char *response = NULL;

    response = getListOfInvitation();

    printf("Response Received :%s\n", response);

    return true;
}

bool testGetInvitationListSendToSpecificUser() {
    char *response = NULL;

    response = getInvitationListSendToSpecificUser("pradyp7@gmail.com");

    printf("Response Received :%s\n", response);

    return true;
}

bool testCreateInvitation() {
    char *response = NULL;

    response = createInvitation("pradyp7@gmail.com");

    printf("Response Received :%s\n", response);

    return true;
}

bool testDeleteInvitation() {
    char *response = NULL;

    response = deleteInvitation("pradyp7@gmail.com");

    printf("Response Received :%s\n", response);

    return true;
}
