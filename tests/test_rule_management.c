/*
 * Test Suite for Rule Management
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
 * @file test_rule_management.c
 *
 * Test Suite for Rule Management
 */

#include "../src/rule_management.h"

bool testCreateAnRule() {
    char *response = NULL;
    long httpResponseCode;

    CreateRule *createRuleObj = createRuleObject();
    CreateRuleActions *createRuleActionObj = createRuleActionObject();
    CreateRuleConditionValues *createRuleConditionValuesObj = createRuleConditionValuesObject();

    setRuleName(createRuleObj, "Test Rule");
    setRuleDescription(createRuleObj, "This is a test rule");
    setRulePriority(createRuleObj, "Medium");
    setRuleType(createRuleObj, "Regular");
    setRuleStatus(createRuleObj, "Active");
    setRuleResetType(createRuleObj, "Automatic");

    setRuleActionObjType(createRuleActionObj, "mail");
    addRuleActionObjTarget(createRuleActionObj, "pradeep.chenthati@aricent.com");
    addRuleActionObjTarget(createRuleActionObj, "pradeepx.chenthati@intel.com");

    setRuleActions(createRuleObj, createRuleActionObj);
    addRulePopulationId(createRuleObj, "685.1.1.1");

    addConditionComponent(createRuleConditionValuesObj, "dataType", "Number");
    addConditionComponent(createRuleConditionValuesObj, "name", "Temp.01.1");
    setConditionType(createRuleConditionValuesObj, "basic");
    addConditionValues(createRuleConditionValuesObj, "25");
    setConditionOperator(createRuleConditionValuesObj, ">");

    setRuleConditionOp(createRuleObj, "OR");
    addRuleConditionValues(createRuleObj, createRuleConditionValuesObj);

    createAnRule(createRuleObj, &httpResponseCode, &response);

    printf("Response Received :%s\n", response);

    return true;
}

bool testUpdateAnRule() {
    char *response = NULL;
    long httpResponseCode;

    CreateRule *createRuleObj = createRuleObject();
    CreateRuleActions *createRuleActionObj = createRuleActionObject();
    CreateRuleConditionValues *createRuleConditionValuesObj = createRuleConditionValuesObject();

    setRuleName(createRuleObj, "Test Rule 1");
    setRuleDescription(createRuleObj, "This is a test rule 1");
    setRulePriority(createRuleObj, "Medium");
    setRuleType(createRuleObj, "Regular");
    setRuleStatus(createRuleObj, "Active");
    setRuleResetType(createRuleObj, "Automatic");

    setRuleActionObjType(createRuleActionObj, "mail");
    addRuleActionObjTarget(createRuleActionObj, "pradeep.chenthati@aricent.com");
    addRuleActionObjTarget(createRuleActionObj, "pradeepx.chenthati@intel.com");

    setRuleActions(createRuleObj, createRuleActionObj);
    addRulePopulationId(createRuleObj, "685.1.1.1");

    addConditionComponent(createRuleConditionValuesObj, "dataType", "Number");
    addConditionComponent(createRuleConditionValuesObj, "name", "Temp.01.1");
    setConditionType(createRuleConditionValuesObj, "basic");
    addConditionValues(createRuleConditionValuesObj, "26");
    setConditionOperator(createRuleConditionValuesObj, ">");

    setRuleConditionOp(createRuleObj, "OR");
    addRuleConditionValues(createRuleObj, createRuleConditionValuesObj);

    updateAnRule(createRuleObj, "65424", &httpResponseCode, &response);

    printf("Response Received :%s\n", response);

    return true;
}

bool testGetListOfRules() {
    char *response = NULL;
    long httpResponseCode;

    getListOfRules(&httpResponseCode, &response);

    printf("Response Received :%s\n", response);

    if(httpResponseCode == 200) {
        return true;
    }

    return false;
}
