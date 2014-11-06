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
 * @file authorization.c
 * @brief Implementation of Authorization API
 *
 * Provides features for communication with IoT Cloud server
 */

#ifndef __AUTHORIZATION_H
#define __AUTHORIZATION_H

#ifdef __cplusplus
extern "C" {
#endif

#include "iotkit.h"

char *getUserJwtToken(char *username, char *password);
char *getUserJwtTokenInfo();
char *getAuthorizationTokenMeInfo();

#ifdef __cplusplus
}
#endif

#endif
