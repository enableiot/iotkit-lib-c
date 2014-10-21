/*
 * Test Suite for Alert Management
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
 * @file test_alert_management.c
 *
 * Test Suite for Alert Management
 */

#include "../src/alert_management.h"

bool testCreateNewAlert() {
    char *response = NULL;
    long httpResponseCode;
    CreateNewAlert *createNewAlertObj = NULL;
    CreateNewAlertData *createNewAlertDataObj = NULL;
    CreateNewAlertDataConditions *createNewAlertDataConditionsObj = NULL;
    CreateNewAlertDataConditionCmps *createNewAlertDataConditionCmpsObj = NULL;

    createNewAlertObj = createNewAlertObject();
    createNewAlertDataObj = createNewAlertDataObject();
    createNewAlertDataConditionsObj = createNewAlertDataConditionsObject();
    createNewAlertDataConditionCmpsObj = createNewAlertDataConditionCmpsObject();

    cna_setAlertId(createNewAlertDataObj, 75);
    cna_setRuleId(createNewAlertDataObj, 1206);
    cna_setAlertStatus(createNewAlertDataObj, "Open");
    cna_setTimestamp(createNewAlertDataObj, 1402580459000L);
    cna_setResetTimestamp(createNewAlertDataObj, 123);
    cna_setResetType(createNewAlertDataObj, "Automatic");
    cna_setLastUpdateDate(createNewAlertDataObj, 2934209384029);
    cna_setRuleName(createNewAlertDataObj, "rule 2 - basic condition new");
    cna_setRulePriority(createNewAlertDataObj, "Low");
    cna_setNaturalLangAlert(createNewAlertDataObj, "temperature > 17.2");
    cna_setRuleExecutionTimestamp(createNewAlertDataObj, 1402580459000L);

    addNewAlertDataObject(createNewAlertObj, createNewAlertDataObj);

    cna_setConditionSequence(createNewAlertDataConditionsObj, 1);
    cna_setNaturalLanguageCondition(createNewAlertDataConditionsObj, "temperature > 17.23");

    addNewAlertConditions(createNewAlertDataObj, createNewAlertDataConditionsObj);

    cnac_setComponentId(createNewAlertDataConditionCmpsObj, "3523dsdfg-2354sdf-23423fs2-wdfsdf");
    cnac_setDataType(createNewAlertDataConditionCmpsObj, "Number");
    cnac_setComponentName(createNewAlertDataConditionCmpsObj, "GA9c-3-Temp.Sensor");
    cnac_addValuePoints(createNewAlertDataConditionCmpsObj, 1402580459000L, "21");

    cna_addComponents(createNewAlertDataConditionsObj, createNewAlertDataConditionCmpsObj);

    createNewAlert(createNewAlertObj, &httpResponseCode, &response);

    printf("Response Received :%s\n", response);

    if(httpResponseCode == 201) {
        return true;
    }

    return false;
}

bool testGetListOfAlerts() {
    char *response = NULL;
    long httpResponseCode;

    getListOfAlerts(&httpResponseCode, &response);

    printf("Response Received :%s\n", response);

    if(httpResponseCode == 200) {
        return true;
    }

    return false;
}
