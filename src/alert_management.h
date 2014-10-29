/*
 * Alert Management API module to communicate with IoT Cloud via REST APIs
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
 * @file alert_management.c
 * @brief Implementation of Alert Management
 *
 * Provides features for communication with IoT Cloud server
 */

#ifndef __ALERT_MANAGEMENT_H
#define __ALERT_MANAGEMENT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "iotkit.h"

typedef struct _ConditionCmpsValuePoints{
    long timestamp;
    char *value;
} ConditionCmpsValuePoints;

typedef struct _CreateNewAlertDataConditionCmpsValuePoints{
    ConditionCmpsValuePoints *valuePoint;
    ConditionCmpsValuePoints *next;
} CreateNewAlertDataConditionCmpsValuePoints;

typedef struct _CreateNewAlertDataConditionCmps {
    // components
    char *cmp_componentId;
    char *cmp_dataType;
    char *cmp_componentName;

    //value points
    CreateNewAlertDataConditionCmpsValuePoints *valuePoints;
} CreateNewAlertDataConditionCmps;

typedef struct _CreateNewAlertDataConditionCmpsList {
    CreateNewAlertDataConditionCmps *component;
    struct _CreateNewAlertDataConditionCmpsList *next;
} CreateNewAlertDataConditionCmpsList;

typedef struct _CreateNewAlertDataConditions {
    // conditions
    int c_conditionSequence;
    char *c_naturalLangCondition;

    // components
    CreateNewAlertDataConditionCmpsList *components;
} CreateNewAlertDataConditions;

typedef struct _CreateNewAlertDataConditionsList {
    CreateNewAlertDataConditions *condition;
    struct _CreateNewAlertDataConditionsList *next;
} CreateNewAlertDataConditionsList;

typedef struct _CreateNewAlertData {
//data
    char *accountId;
    int alertId;
    int ruleId;
    char *deviceId;
    char *alertStatus;
    long timestamp;
    long resetTimestamp;
    char *resetType;
    long lastUpdateDate;
    char *ruleName;
    char *rulePriority;
    char *naturalLangAlert;
    long ruleExecutionTimestamp;


    CreateNewAlertDataConditionsList *conditions;
} CreateNewAlertData;

typedef struct _CreateNewAlertDataList {
    CreateNewAlertData *data;
    struct _CreateNewAlertDataList *next;
} CreateNewAlertDataList;

typedef struct _CreateNewAlert {
    char *msgType;

    CreateNewAlertDataList *dataList;
} CreateNewAlert;

#ifdef __cplusplus
}
#endif

#endif
