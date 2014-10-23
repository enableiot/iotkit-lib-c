/*
 * Rule Management module to communicate with IoT Cloud via REST APIs
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
 * @file rule_management.c
 * @brief Implementation of Rule Management
 *
 * Provides features for communication with IoT Cloud server
 */

#ifndef __RULE_MANAGEMENT_H
#define __RULE_MANAGEMENT_H

#include "iotkit.h"

typedef struct _CreateRuleActions {
    char *type;
    StringList *target;
} CreateRuleActions;

typedef struct _CreateRuleActionsList {
    CreateRuleActions *data;
    struct CreateRuleActionsList *next;
} CreateRuleActionsList;


typedef struct _CreateRuleConditionValues {
    KeyValueParams *component;
    char *type;
    StringList *values;
    char *operator;
} CreateRuleConditionValues;

typedef struct _CreateRuleConditionValuesList {
    CreateRuleConditionValues *data;
    struct CreateRuleConditionValuesList *next;
} CreateRuleConditionValuesList;

typedef struct _CreateRule {
    char *name;
    char *description;
    char *priority;
    char *type;
    char *status;
    char *resetType;

    CreateRuleActionsList *actions;

    // population
    StringList *population_ids;
    char *population_attributes;

    //conditions
    char *operator;
    CreateRuleConditionValuesList *values;
} CreateRule;

#endif
