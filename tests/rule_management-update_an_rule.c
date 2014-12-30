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

int getRuleIDFromResponse(char *response) {
    cJSON *json = NULL, *jitem = NULL, *child = NULL, *child2 = NULL;

// parse the file
    json = cJSON_Parse(response);
    if (!json) {
        fprintf(stderr,"Error before: [%s]\n",cJSON_GetErrorPtr());
    } else {
        jitem = cJSON_GetObjectItem(json, "data");
        if(isJsonArray(jitem) && cJSON_GetArraySize(jitem) > 0) {
            int i = 0;
            while(i < cJSON_GetArraySize(jitem)) {
                child = cJSON_GetArrayItem(jitem, i);
                if (!isJsonObject(child)) {
                    fprintf(stderr,"Invalid JSON format for json property %s\n", child->string);
                    return 0;
                }

                child2 = cJSON_GetObjectItem(child, "status");
                if(child2 && isJsonString(child2) && strcmp(child2->valuestring, "Active") == 0) {
                    child2 = cJSON_GetObjectItem(child, "externalId");

                    if (isJsonNumber(child2)) {
                        return child2->valueint;
                    }
                }

                i ++;
            }
        }
    }

    return 0;
}

int main(void) {
    char *response = NULL;
    int ruleID;
    char rule_id_string[128];

    iotkit_init();

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
    addRuleActionObjTarget(createRuleActionObj, "snowysnops@gmail.com");
    addRuleActionObjTarget(createRuleActionObj, "snowysnops3@gmail.com");

    setRuleActions(createRuleObj, createRuleActionObj);
    addRulePopulationId(createRuleObj, "685.1.1.1");

    addConditionComponent(createRuleConditionValuesObj, "dataType", "Number");
    addConditionComponent(createRuleConditionValuesObj, "name", "Temp.01.1");
    setConditionType(createRuleConditionValuesObj, "basic");
    addConditionValues(createRuleConditionValuesObj, "26");
    setConditionOperator(createRuleConditionValuesObj, ">");

    setRuleConditionOp(createRuleObj, "OR");
    addRuleConditionValues(createRuleObj, createRuleConditionValuesObj);

    response = getListOfRules();
    printf("List of Rules Received :%s\n", response);
    ruleID = getRuleIDFromResponse(response);
    printf("Rule ID :%d\n", ruleID);
    sprintf(rule_id_string, "%d", ruleID);

    response = updateAnRule(createRuleObj, rule_id_string);

    printf("Response Received :%s\n", response);

    iotkit_cleanup();

    if(checkResponseValue(response, 200) == true || checkResponseValue(response, 201) == true) {
        exit(EXIT_SUCCESS);
    }

    exit(EXIT_FAILURE);
}
