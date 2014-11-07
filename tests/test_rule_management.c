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
