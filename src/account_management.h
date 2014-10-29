/*
 * Account Management API module to communicate with IoT Cloud via REST APIs
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
 * @file account_management.h
 * @brief Implementation of Account Management API
 *
 * Provides features for communication with IoT Cloud server
 */

#ifndef __COMPONENT_CATALOG_H
#define __COMPONENT_CATALOG_H


#ifdef __cplusplus
extern "C" {
#endif

#include "iotkit.h"

typedef struct _UpdateUserAccount {

    KeyValueParams *attributes;

    char *email;
    bool termsAndConditions;
    bool verified;
} UpdateUserAccount;

#ifdef __cplusplus
}
#endif

#endif
