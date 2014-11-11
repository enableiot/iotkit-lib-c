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

#ifndef __RULE_MANAGEMENT_H
#define __RULE_MANAGEMENT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "iotkit.h"

typedef struct _CreateRuleActions {
    char *type;
    StringList *target;
} CreateRuleActions;

typedef struct _CreateRuleActionsList {
    CreateRuleActions *data;
    struct _CreateRuleActionsList *next;
} CreateRuleActionsList;


typedef struct _CreateRuleConditionValues {
    KeyValueParams *component;
    char *type;
    StringList *values;
    char *opname; // operator
} CreateRuleConditionValues;

typedef struct _CreateRuleConditionValuesList {
    CreateRuleConditionValues *data;
    struct _CreateRuleConditionValuesList *next;
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
    char *opname; // operator
    CreateRuleConditionValuesList *values;
} CreateRule;

CreateRule *createRuleObject();
CreateRule *setRuleName(CreateRule *createRuleObj, char *name);
CreateRule *setRuleDescription(CreateRule *createRuleObj, char *description);
CreateRule *setRulePriority(CreateRule *createRuleObj, char *priority);
CreateRule *setRuleType(CreateRule *createRuleObj, char *type);
CreateRule *setRuleStatus(CreateRule *createRuleObj, char *status);
CreateRule *setRuleResetType(CreateRule *createRuleObj, char *resetType);
CreateRuleActions *createRuleActionObject();
CreateRuleActions *setRuleActionObjType(CreateRuleActions *createRuleActionObj, char *type);
CreateRuleActions *addRuleActionObjTarget(CreateRuleActions *createRuleActionObj, char *target);
CreateRule *setRuleActions(CreateRule *createRuleObj, CreateRuleActions *action);
CreateRule *addRulePopulationId(CreateRule *createRuleObj, char *populationId);
CreateRule *setRulePopulationAttributes(CreateRule *createRuleObj, char *attributes);
CreateRuleConditionValues *createRuleConditionValuesObject();
CreateRuleConditionValues *addConditionComponent(CreateRuleConditionValues *createRuleConditionValuesObj, char *keyName, char *keyValue);
CreateRuleConditionValues *setConditionType(CreateRuleConditionValues *createRuleConditionValuesObj, char *type);
CreateRuleConditionValues *addConditionValues(CreateRuleConditionValues *createRuleConditionValuesObj, char *value);
CreateRuleConditionValues *setConditionOperator(CreateRuleConditionValues *createRuleConditionValuesObj, char *opname);
CreateRule *setRuleConditionOp(CreateRule *createRuleObj, char *opname);
CreateRule *addRuleConditionValues(CreateRule *createRuleObj, CreateRuleConditionValues *createRuleConditionValuesObj);

char *createAnRule(CreateRule *createRuleObj);
char *updateAnRule(CreateRule *createRuleObj, char *rule_id);
char *getListOfRules();
char *getOneRuleInformation(char *rule_id);
char *createARuleAsDraft(char *rule_name);
char *updateStatusOfARule(char *rule_id, char *rule_status);
char *deleteADraftRule(char *rule_id);

#ifdef __cplusplus
}
#endif

#endif
