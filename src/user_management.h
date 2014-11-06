/*
 * User Management module to communicate with IoT Cloud via REST APIs
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
 * @file user_management.h
 * @brief Implementation of User Management
 *
 * Provides features for communication with IoT Cloud server
 */

#ifndef __RULE_MANAGEMENT_H
#define __RULE_MANAGEMENT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "iotkit.h"

char *createAnUser(char *emailAddress, char *password);
char *getUserInformation(char *userId);
char *updateUserAttributes(char *userId, KeyValueParams *attributes);
char *acceptTermsAndConditions(char *userId, bool accept);
char *deleteAUser(char *userId);
char *requestChangePassword(char *emailAddress);
char *updateForgotPassword(char *token, char *new_password);
char *changePassword(char *emailAddress, char *current_password, char *new_password);

#ifdef __cplusplus
}
#endif

#endif
