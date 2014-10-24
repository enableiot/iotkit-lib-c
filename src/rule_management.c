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

#include "rule_management.h"

CreateRule *createRuleObject() {
    CreateRule *newObject = (CreateRule *)malloc(sizeof(CreateRule));

    if(!newObject) {
        return NULL;
    }

    newObject->name = NULL;
    newObject->description = NULL;
    newObject->priority = NULL;
    newObject->type = NULL;
    newObject->status = NULL;
    newObject->resetType = NULL;

    newObject->actions = NULL;

    // population
    newObject->population_ids = NULL;
    newObject->population_attributes = NULL;

    //conditions
    newObject->opname = NULL;
    newObject->values = NULL;

    return newObject;
}

CreateRule *setRuleName(CreateRule *createRuleObj, char *name) {
    createRuleObj->name = strdup(name);

    return createRuleObj;
}

CreateRule *setRuleDescription(CreateRule *createRuleObj, char *description) {
    createRuleObj->description = strdup(description);

    return createRuleObj;
}

CreateRule *setRulePriority(CreateRule *createRuleObj, char *priority) {
    createRuleObj->priority = strdup(priority);

    return createRuleObj;
}

CreateRule *setRuleType(CreateRule *createRuleObj, char *type) {
    createRuleObj->type = strdup(type);

    return createRuleObj;
}

CreateRule *setRuleStatus(CreateRule *createRuleObj, char *status) {
    createRuleObj->status = strdup(status);

    return createRuleObj;
}

CreateRule *setRuleResetType(CreateRule *createRuleObj, char *resetType) {
    createRuleObj->resetType = strdup(resetType);

    return createRuleObj;
}

CreateRuleActions *createRuleActionObject() {
    CreateRuleActions *newObject = (CreateRuleActions *)malloc(sizeof(CreateRuleActions));

    if(!newObject) {
        return NULL;
    }

    newObject->type = NULL;
    newObject->target = NULL;

    return newObject;
}

CreateRuleActions *setRuleActionObjType(CreateRuleActions *createRuleActionObj, char *type) {
    createRuleActionObj->type = strdup(type);

    return createRuleActionObj;
}

CreateRuleActions *addRuleActionObjTarget(CreateRuleActions *createRuleActionObj, char *target) {
    StringList *newObject = (StringList *)malloc(sizeof(StringList));
    newObject->data = strdup(target);
    newObject->next = NULL;

    if(createRuleActionObj->target == NULL) {
        createRuleActionObj->target = newObject;
    } else {
        StringList *traverse = createRuleActionObj->target;
        while(traverse->next != NULL) {
            traverse = traverse->next;
        }

        traverse->next = newObject;
    }

    return createRuleActionObj;
}

CreateRule *setRuleActions(CreateRule *createRuleObj, CreateRuleActions *action) {
    CreateRuleActionsList *newObject = (CreateRuleActionsList *)malloc(sizeof(CreateRuleActionsList));
    newObject->data = action;
    newObject->next = NULL;

    if(createRuleObj->actions == NULL) {
        createRuleObj->actions = newObject;
    } else {
        CreateRuleActionsList *traverse = createRuleObj->actions;
        while(traverse->next != NULL) {
            traverse = traverse->next;
        }

        traverse->next = newObject;
    }

    return createRuleObj;
}

CreateRule *addRulePopulationId(CreateRule *createRuleObj, char *populationId) {
    StringList *newObject = (StringList *)malloc(sizeof(StringList));
    newObject->data = strdup(populationId);
    newObject->next = NULL;

    if(createRuleObj->population_ids == NULL) {
        createRuleObj->population_ids = newObject;
    } else {
        StringList *traverse = createRuleObj->population_ids;
        while(traverse->next != NULL) {
            traverse = traverse->next;
        }

        traverse->next = newObject;
    }

    return createRuleObj;
}

CreateRule *setRulePopulationAttributes(CreateRule *createRuleObj, char *attributes) {
    createRuleObj->population_attributes = strdup(attributes);

    return createRuleObj;
}

CreateRuleConditionValues *createRuleConditionValuesObject() {
    CreateRuleConditionValues *newObject = (CreateRuleConditionValues *)malloc(sizeof(CreateRuleConditionValues));

    if(!newObject) {
        return NULL;
    }

    newObject->component = NULL;
    newObject->type = NULL;
    newObject->values = NULL;
    newObject->opname = NULL;

    return newObject;
}

CreateRuleConditionValues *addConditionComponent(CreateRuleConditionValues *createRuleConditionValuesObj, char *keyName, char *keyValue) {
    KeyValueParams *newObject = (KeyValueParams *)malloc(sizeof(KeyValueParams));
    newObject->name = strdup(keyName);
    newObject->value = strdup(keyValue);
    newObject->next = NULL;

    if(createRuleConditionValuesObj->component == NULL) {
        createRuleConditionValuesObj->component = newObject;
    } else {
        KeyValueParams *traverse = createRuleConditionValuesObj->component;
        while(traverse->next != NULL) {
            traverse = traverse->next;
        }

        traverse->next = newObject;
    }

    return createRuleConditionValuesObj;
}

CreateRuleConditionValues *setConditionType(CreateRuleConditionValues *createRuleConditionValuesObj, char *type) {
    createRuleConditionValuesObj->type = strdup(type);

    return createRuleConditionValuesObj;
}

CreateRuleConditionValues *addConditionValues(CreateRuleConditionValues *createRuleConditionValuesObj, char *value) {
    StringList *newObject = (StringList *)malloc(sizeof(StringList));
    newObject->data = strdup(value);
    newObject->next = NULL;

    if(createRuleConditionValuesObj->values == NULL) {
        createRuleConditionValuesObj->values = newObject;
    } else {
        StringList *traverse = createRuleConditionValuesObj->values;
        while(traverse->next != NULL) {
            traverse = traverse->next;
        }

        traverse->next = newObject;
    }

    return createRuleConditionValuesObj;
}

CreateRuleConditionValues *setConditionOperator(CreateRuleConditionValues *createRuleConditionValuesObj, char *opname) {
    createRuleConditionValuesObj->opname = strdup(opname);

    return createRuleConditionValuesObj;
}

CreateRule *setRuleConditionOp(CreateRule *createRuleObj, char *opname) {
    createRuleObj->opname = strdup(opname);

    return createRuleObj;
}

CreateRule *addRuleConditionValues(CreateRule *createRuleObj, CreateRuleConditionValues *createRuleConditionValuesObj) {
    CreateRuleConditionValuesList *newObject = (CreateRuleConditionValuesList *)malloc(sizeof(CreateRuleConditionValuesList));
    newObject->data = createRuleConditionValuesObj;
    newObject->next = NULL;

    if(createRuleObj->values == NULL) {
        createRuleObj->values = newObject;
    } else {
        CreateRuleConditionValuesList *traverse = createRuleObj->values;
        while(traverse->next != NULL) {
            traverse = traverse->next;
        }

        traverse->next = newObject;
    }

    return createRuleObj;
}

char *createRuleHttpRequestBody(CreateRule *createRuleObj) {
    char *body = (char *)malloc(sizeof(char) *BODY_SIZE_MAX);

    strcpy(body, "{");
        if(createRuleObj->name) {
            strcat(body, "\"name\":\"");
            strcat(body, createRuleObj->name);
            strcat(body, "\"");
        }

        if(createRuleObj->description) {
            strcat(body, ",\"description\":\"");
            strcat(body, createRuleObj->description);
            strcat(body, "\"");
        }

        if(createRuleObj->priority) {
            strcat(body, ",\"priority\":\"");
            strcat(body, createRuleObj->priority);
            strcat(body, "\"");
        }


        if(createRuleObj->type) {
            strcat(body, ",\"type\":\"");
            strcat(body, createRuleObj->type);
            strcat(body, "\"");
        }

        if(createRuleObj->status) {
            strcat(body, ",\"status\":\"");
            strcat(body, createRuleObj->status);
            strcat(body, "\"");
        }

        if(createRuleObj->resetType) {
            strcat(body, ",\"resetType\":\"");
            strcat(body, createRuleObj->resetType);
            strcat(body, "\"");
        }

        if(createRuleObj->actions) {
            CreateRuleActionsList *traverse = createRuleObj->actions;
            strcat(body, ",\"actions\":[");

            while(traverse) {
                CreateRuleActions *action = traverse->data;
                strcat(body, "{");

                if(action->type) {
                    strcat(body, "\"type\":\"");
                    strcat(body, action->type);
                    strcat(body, "\"");

                    if(action->target) {
                        StringList *traverseTarget = action->target;
                        strcat(body, ",\"target\":[");
                            while(traverseTarget) {
                                strcat(body, "\"");
                                strcat(body, traverseTarget->data);
                                strcat(body, "\"");

                                traverseTarget = traverseTarget->next;

                                if(traverseTarget) {
                                    strcat(body, ",");
                                }
                            }
                        strcat(body, "]");
                    }
                }
                strcat(body, "}");

                traverse = traverse->next;

                if(traverse) {
                    strcat(body, ",");
                }
            }
            strcat(body, "]");
        }

        strcat(body, ",\"population\":{");
        if(createRuleObj->population_ids) {
            StringList *traversePopIds = createRuleObj->population_ids;

            strcat(body, "\"ids\":[");
            while(traversePopIds) {
                strcat(body, "\"");
                strcat(body, traversePopIds->data);
                strcat(body, "\"");

                traversePopIds = traversePopIds->next;

                if(traversePopIds) {
                    strcat(body, ",");
                }
            }
            strcat(body, "]");
        }
        strcat(body, ",\"attributes\":");
        if(createRuleObj->population_attributes) {
            strcat(body, "\"");
            strcat(body, createRuleObj->population_attributes);
            strcat(body, "\"");
        } else {
            strcat(body, "null");
        }
        strcat(body, "}");

        strcat(body, ",\"conditions\":{");
        if(createRuleObj->opname) {
            strcat(body, "\"operator\":\"");
            strcat(body, createRuleObj->opname);
            strcat(body, "\"");
        }

        if(createRuleObj->values) {
            CreateRuleConditionValuesList *traverseConditionValues = createRuleObj->values;
            strcat(body, ",\"values\":[");
            while(traverseConditionValues) {
                CreateRuleConditionValues *conditionValue = traverseConditionValues->data;
                strcat(body, "{");

                if(conditionValue->component) {
                    KeyValueParams *keyValues = conditionValue->component;
                    strcat(body, "\"component\":{");
                    while(keyValues) {
                        strcat(body, "\"");
                        strcat(body, keyValues->name);
                        strcat(body, "\":\"");
                        strcat(body, keyValues->value);
                        strcat(body, "\"");

                        keyValues = keyValues->next;

                        if(keyValues) {
                            strcat(body, ",");
                        }
                    }
                    strcat(body, "}");
                }

                if(conditionValue->type) {
                    strcat(body, ",\"type\":\"");
                    strcat(body, conditionValue->type);
                    strcat(body, "\"");
                }

                if(conditionValue->values) {
                    StringList *valueItem = conditionValue->values;
                    strcat(body, ",\"values\":[");
                    while(valueItem) {
                        strcat(body, "\"");
                        strcat(body, valueItem->data);
                        strcat(body, "\"");
                        valueItem = valueItem->next;

                        if(valueItem) {
                            strcat(body, ",");
                        }
                    }
                    strcat(body, "]");
                }

                if(conditionValue->opname) {
                    strcat(body, ",\"operator\":\"");
                    strcat(body, conditionValue->opname);
                    strcat(body, "\"");
                }

                strcat(body, "}");

                traverseConditionValues = traverseConditionValues->next;
                if(traverseConditionValues) {
                    strcat(body, ",");
                }
            }
            strcat(body, "]");
        }
        strcat(body, "}");

        strcat(body, "}");


        #if DEBUG
            printf("Prepared BODY is %s\n", body);
        #endif

    return body;
}

bool createAnRule(CreateRule *createRuleObj, long *httpResponseCode, char **response) {
    struct curl_slist *headers = NULL;
    char *url;
    char *body = NULL;

    if(!createRuleObj) {
        fprintf(stderr, "createAnRule::Mandatory parameters cannot be NULL");
        return false;
    }

    if(prepareUrl(&url, configurations.base_url, configurations.create_a_rule, NULL)) {
        appendHttpHeader(&headers, HEADER_CONTENT_TYPE_NAME, HEADER_CONTENT_TYPE_JSON);
        appendHttpHeader(&headers, HEADER_AUTHORIZATION, getConfigAuthorizationToken());

        body = createRuleHttpRequestBody(createRuleObj);

        doHttpPost(url, headers, body, httpResponseCode, response);

        return true;
    }

    return false;
}

bool updateAnRule(CreateRule *createRuleObj, char *rule_id, long *httpResponseCode, char **response) {
    struct curl_slist *headers = NULL;
    char *url;
    char *body = NULL;
    KeyValueParams *urlParams = NULL;

    urlParams = (KeyValueParams *)malloc(sizeof(KeyValueParams));
    urlParams->name = "rule_id";
    urlParams->value = strdup(rule_id);
    urlParams->next = NULL;

    if(!createRuleObj) {
        fprintf(stderr, "createAnRule::Mandatory parameters cannot be NULL");
        return false;
    }

    if(prepareUrl(&url, configurations.base_url, configurations.update_a_rule, urlParams)) {
        appendHttpHeader(&headers, HEADER_CONTENT_TYPE_NAME, HEADER_CONTENT_TYPE_JSON);
        appendHttpHeader(&headers, HEADER_AUTHORIZATION, getConfigAuthorizationToken());

        body = createRuleHttpRequestBody(createRuleObj);

        doHttpPut(url, headers, body, httpResponseCode, response);

        return true;
    }

    return false;
}

bool getListOfRules(long *httpResponseCode, char **response) {
    struct curl_slist *headers = NULL;
    char *url;

    appendHttpHeader(&headers, HEADER_CONTENT_TYPE_NAME, HEADER_CONTENT_TYPE_JSON);
    appendHttpHeader(&headers, HEADER_AUTHORIZATION, getConfigAuthorizationToken());

    if(prepareUrl(&url, configurations.base_url, configurations.get_list_of_rules, NULL)){
        doHttpGet(url, headers, httpResponseCode, response);

        return true;
    }

    return false;
}

bool getOneRuleInformation(char *rule_id, long *httpResponseCode, char **response) {
    struct curl_slist *headers = NULL;
    char *url;
    KeyValueParams *urlParams = NULL;

    urlParams = (KeyValueParams *)malloc(sizeof(KeyValueParams));
    urlParams->name = "rule_id";
    urlParams->value = strdup(rule_id);
    urlParams->next = NULL;

    appendHttpHeader(&headers, HEADER_CONTENT_TYPE_NAME, HEADER_CONTENT_TYPE_JSON);
    appendHttpHeader(&headers, HEADER_AUTHORIZATION, getConfigAuthorizationToken());

    if(prepareUrl(&url, configurations.base_url, configurations.get_one_rule_info, urlParams)){
        doHttpGet(url, headers, httpResponseCode, response);

        return true;
    }

    return false;
}

bool createARuleAsDraft(char *rule_name, long *httpResponseCode, char **response) {
    struct curl_slist *headers = NULL;
    char *url;
    char body[BODY_SIZE_MIN];

    if(!rule_name) {
        fprintf(stderr, "createAnRule::Rule Name parameter is mandatory and cannot be NULL");
        return false;
    }

    if(prepareUrl(&url, configurations.base_url, configurations.create_a_rule_as_draft, NULL)) {
        appendHttpHeader(&headers, HEADER_CONTENT_TYPE_NAME, HEADER_CONTENT_TYPE_JSON);
        appendHttpHeader(&headers, HEADER_AUTHORIZATION, getConfigAuthorizationToken());

        sprintf(body, "{\"name\":\"%s\"}", rule_name);

        doHttpPut(url, headers, body, httpResponseCode, response);

        return true;
    }

    return false;
}

bool updateStatusOfARule(char *rule_id, char *rule_status, long *httpResponseCode, char **response) {
    struct curl_slist *headers = NULL;
    char *url;
    char body[BODY_SIZE_MIN];
    KeyValueParams *urlParams = NULL;

    urlParams = (KeyValueParams *)malloc(sizeof(KeyValueParams));
    urlParams->name = "rule_id";
    urlParams->value = strdup(rule_id);
    urlParams->next = NULL;

    if(!rule_id || !rule_status) {
        fprintf(stderr, "createAnRule::Mandatory parameters cannot be NULL");
        return false;
    }

    if(prepareUrl(&url, configurations.base_url, configurations.update_status_of_a_rule, urlParams)) {
        appendHttpHeader(&headers, HEADER_CONTENT_TYPE_NAME, HEADER_CONTENT_TYPE_JSON);
        appendHttpHeader(&headers, HEADER_AUTHORIZATION, getConfigAuthorizationToken());

        sprintf(body, "{\"status\":\"%s\"}", rule_status);

        doHttpPut(url, headers, body, httpResponseCode, response);

        return true;
    }

    return false;
}

bool deleteADraftRule(char *rule_id, long *httpResponseCode, char **response) {
    struct curl_slist *headers = NULL;
    char *url;
    KeyValueParams *urlParams = NULL;

    urlParams = (KeyValueParams *)malloc(sizeof(KeyValueParams));
    urlParams->name = "rule_id";
    urlParams->value = strdup(rule_id);
    urlParams->next = NULL;

    if(prepareUrl(&url, configurations.base_url, configurations.delete_a_draft_rule, urlParams)) {

        appendHttpHeader(&headers, HEADER_CONTENT_TYPE_NAME, HEADER_CONTENT_TYPE_JSON);
        appendHttpHeader(&headers, HEADER_AUTHORIZATION, getConfigAuthorizationToken());

        doHttpDelete(url, headers, httpResponseCode, response);

        return true;
    }

    return false;
}
