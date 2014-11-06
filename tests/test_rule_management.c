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

    response = createAnRule(createRuleObj);

    printf("Response Received :%s\n", response);

    return true;
}

bool testUpdateAnRule() {
    char *response = NULL;

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

    response = updateAnRule(createRuleObj, "82957");

    printf("Response Received :%s\n", response);

    return true;
}

bool testGetListOfRules() {
    char *response = NULL;

    response = getListOfRules();

    printf("Response Received :%s\n", response);

    return true;
}

bool testGetOneRuleInformation() {
    char *response = NULL;

    response = getOneRuleInformation("82957");

    printf("Response Received :%s\n", response);

    /*if(httpResponseCode == 200) {
        return true;
    }*/

    return true;
}

bool testCreateARuleAsDraft() {
    char *response = NULL;

    response = createARuleAsDraft("mahatest");

    printf("Response Received :%s\n", response);

    /*if(httpResponseCode == 200) {
        return true;
    }*/

    return true;
}

bool testUpdateStatusOfARule() {
    char *response = NULL;

    response = updateStatusOfARule("82957", "Archived");

    printf("Response Received :%s\n", response);

    /*if(httpResponseCode == 200) {
        return true;
    }*/

    return true;
}

bool testDeleteADraftRule() {
    char *response = NULL;

    // pass external ID
    response = deleteADraftRule("0ca2381578bcdfe5a5794cea7ea98b071f6a6d38");

    printf("Response Received :%s\n", response);

    /*if(httpResponseCode == 200) {
        return true;
    }*/

    return true;
}
