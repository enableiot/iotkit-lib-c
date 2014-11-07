/*
 * Copyright (c) 2014 Intel Corporation.
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
 * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
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

char *createNewAlert(CreateNewAlert *createNewAlertObj);
char *getListOfAlerts();
char *getAlertInformation(char *alertId);
char *resetAlert(char *alertId);
char *updateAlertStatus(char *alertId, char *status_name);
char *addCommentToAlert(char *alertId, char *user, long timestamp, char *comment);

#ifdef __cplusplus
}
#endif

#endif
