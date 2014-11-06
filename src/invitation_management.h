/*
 * Invitation Management API module to communicate with IoT Cloud via REST APIs
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
 * @file invitation_management.h
 * @brief Implementation of Invitation Management API
 *
 * Provides features for communication with IoT Cloud server
 */
#ifndef __INVITATION_MANAGEMENT_H
#define __INVITATION_MANAGEMENT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "iotkit.h"

char *getListOfInvitation();
char *getInvitationListSendToSpecificUser(char *email_id);
char *createInvitation(char *email);
char *deleteInvitation(char *email_id);

#ifdef __cplusplus
}
#endif

#endif
