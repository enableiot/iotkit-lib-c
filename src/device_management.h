/*
 * Device Management API module to communicate with IoT Cloud via REST APIs
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
 * @file device_management.h
 * @brief Implementation of Device Management
 *
 * Provides features for communication with IoT Cloud server
 */

#ifndef __DEVICE_MANAGEMENT_H
#define __DEVICE_MANAGEMENT_H

#include "iotkit.h"

typedef struct _DeviceCreationObj {
    char *device_id;
    char *gateway_id;
    char *device_name;

    StringList *tags;

    char *latitude;
    char *longitude;
    char *height;

    KeyValueParams *attributes;
} DeviceCreationObj;

#endif
