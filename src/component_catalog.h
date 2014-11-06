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

#ifndef __COMPONENT_CATALOG_H
#define __COMPONENT_CATALOG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "iotkit.h"

/** Actuator Command list
*/
typedef struct _ActuatorCommandParams {
    char *name;
    char *value;

    struct ActuatorCommandParams *next;
} ActuatorCommandParams;

typedef struct _ComponentCatalog {
    char *name;
    char *version;
    char *type;
    char *datatype;
    char *format;
    bool isMinPresent;
    double minvalue;
    bool isMaxPresent;
    double maxvalue;
    char *unit;
    char *display;
    char *command;

    ActuatorCommandParams *parameters;
} ComponentCatalog;

char *listAllComponentCatalogs();
char *getComponentCatalogDetails(char *cmp_id);
char *createAnComponentCatalog(ComponentCatalog *cmpCatalogObject);
char *updateAnComponentCatalog(ComponentCatalog *cmpCatalogObject, char *cmp_id);

#ifdef __cplusplus
}
#endif

#endif
