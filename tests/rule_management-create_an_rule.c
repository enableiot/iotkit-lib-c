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

#include "rule_management.h"

int main(void) {
    char *response = NULL;

    CreateRule *createRuleObj = NULL;
    CreateRuleActions *createRuleActionObj = NULL;
    CreateRuleConditionValues *createRuleConditionValuesObj = NULL;

    iotkit_init();

    createRuleObj = createRuleObject();
    createRuleActionObj = createRuleActionObject();
    createRuleConditionValuesObj = createRuleConditionValuesObject();

    setRuleName(createRuleObj, "Test Rule");
    setRuleDescription(createRuleObj, "This is a test rule");
    setRulePriority(createRuleObj, "Medium");
    setRuleType(createRuleObj, "Regular");
    setRuleStatus(createRuleObj, "Active");
    setRuleResetType(createRuleObj, "Automatic");

    setRuleActionObjType(createRuleActionObj, "mail");
    addRuleActionObjTarget(createRuleActionObj, "snowysnops@gmail.com");
    addRuleActionObjTarget(createRuleActionObj, "snowysnops3@gmail.com");

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

    iotkit_cleanup();

    if(checkResponseValue(response, 201) == true) {
        exit(EXIT_SUCCESS);
    }

    exit(EXIT_FAILURE);
}
