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

#include "alert_management.h"

CreateNewAlert *createNewAlertObject() {
    CreateNewAlert *newObject = (CreateNewAlert *)malloc(sizeof(CreateNewAlert));

    if(!newObject) {
        return NULL;
    }

    newObject->msgType = NULL;
    newObject->dataList = NULL;

    return newObject;
}

CreateNewAlert *cna_setMsgType(CreateNewAlert *createNewAlertObj, char *msgType) {
    createNewAlertObj->msgType = strdup(msgType);
    createNewAlertObj->dataList = NULL;

    return createNewAlertObj;
}

CreateNewAlertData *createNewAlertDataObject() {
    CreateNewAlertData *newObject = (CreateNewAlertData *)malloc(sizeof(CreateNewAlertData));

    if(!newObject) {
        return NULL;
    }

    newObject->accountId = NULL;
    newObject->alertId = -1; // IDs are never expected to be -1
    newObject->ruleId = -1; // IDs are never expected to be -1
    newObject->deviceId = NULL;
    newObject->alertStatus = NULL;
    newObject->timestamp = 0L;
    newObject->resetTimestamp = 0L;
    newObject->resetType = NULL;
    newObject->lastUpdateDate = 0L;
    newObject->ruleName = NULL;
    newObject->rulePriority = NULL;
    newObject->naturalLangAlert = NULL;
    newObject->ruleExecutionTimestamp = -1; // timestamps are never -1

    newObject->conditions = NULL;

    return newObject;
}

CreateNewAlertData *cna_setAccountId(CreateNewAlertData *createNewAlertDataObj, char *accountId) {
    createNewAlertDataObj->accountId = strdup(accountId);
    return createNewAlertDataObj;
}

CreateNewAlertData *cna_setAlertId(CreateNewAlertData *createNewAlertDataObj, int alertId) {
    createNewAlertDataObj->alertId = alertId;
    return createNewAlertDataObj;
}

CreateNewAlertData *cna_setRuleId(CreateNewAlertData *createNewAlertDataObj, int ruleId) {
    createNewAlertDataObj->ruleId = ruleId;
    return createNewAlertDataObj;
}

CreateNewAlertData *cna_setDeviceId(CreateNewAlertData *createNewAlertDataObj, char *deviceId) {
    createNewAlertDataObj->deviceId = strdup(deviceId);
    return createNewAlertDataObj;
}

CreateNewAlertData *cna_setAlertStatus(CreateNewAlertData *createNewAlertDataObj, char *alertStatus) {
    createNewAlertDataObj->alertStatus = strdup(alertStatus);
    return createNewAlertDataObj;
}

CreateNewAlertData *cna_setTimestamp(CreateNewAlertData *createNewAlertDataObj, long timestamp) {
    createNewAlertDataObj->timestamp = timestamp;
    return createNewAlertDataObj;
}

CreateNewAlertData *cna_setResetTimestamp(CreateNewAlertData *createNewAlertDataObj, long resetTimestamp) {
    createNewAlertDataObj->resetTimestamp = resetTimestamp;
    return createNewAlertDataObj;
}

CreateNewAlertData *cna_setResetType(CreateNewAlertData *createNewAlertDataObj, char *resetType) {
    createNewAlertDataObj->resetType = strdup(resetType);

    return createNewAlertDataObj;
}

CreateNewAlertData *cna_setLastUpdateDate(CreateNewAlertData *createNewAlertDataObj, long lastUpdateDate) {
    createNewAlertDataObj->lastUpdateDate = lastUpdateDate;
    return createNewAlertDataObj;
}

CreateNewAlertData *cna_setRuleName(CreateNewAlertData *createNewAlertDataObj, char *ruleName) {
    createNewAlertDataObj->ruleName = strdup(ruleName);
    return createNewAlertDataObj;
}

CreateNewAlertData *cna_setRulePriority(CreateNewAlertData *createNewAlertDataObj, char *rulePriority) {\
    createNewAlertDataObj->rulePriority = strdup(rulePriority);
    return createNewAlertDataObj;
}

CreateNewAlertData *cna_setNaturalLangAlert(CreateNewAlertData *createNewAlertDataObj, char *naturalLangAlert) {
    createNewAlertDataObj->naturalLangAlert = strdup(naturalLangAlert);
    return createNewAlertDataObj;
}

CreateNewAlertData *cna_setRuleExecutionTimestamp(CreateNewAlertData *createNewAlertDataObj, long ruleExecutionTimestamp) {
    createNewAlertDataObj->ruleExecutionTimestamp = ruleExecutionTimestamp;
    return createNewAlertDataObj;
}

CreateNewAlert *addNewAlertDataObject(CreateNewAlert *createNewAlertObj, CreateNewAlertData *createNewAlertDataObj) {

    CreateNewAlertDataList *newObject = (CreateNewAlertDataList *)malloc(sizeof(CreateNewAlertDataList));
    newObject->data = createNewAlertDataObj;
    newObject->next = NULL;

    if(createNewAlertObj->dataList == NULL) {
        createNewAlertObj->dataList = newObject;
    } else {
        CreateNewAlertDataList *traverse = createNewAlertObj->dataList;
        while(traverse->next != NULL) {
            traverse = traverse->next;
        }
        traverse->next = newObject;
    }

    return createNewAlertObj;
}

CreateNewAlertDataConditions *createNewAlertDataConditionsObject() {
    CreateNewAlertDataConditions *newObject = (CreateNewAlertDataConditions *)malloc(sizeof(CreateNewAlertDataConditions));

    if(!newObject) {
        return NULL;
    }

    newObject->c_conditionSequence = -1;
    newObject->c_naturalLangCondition = NULL;
    newObject->components = NULL;

    return newObject;
}


CreateNewAlertDataConditions *cna_setConditionSequence(CreateNewAlertDataConditions *createNewAlertDataConditionsObj, int conditionSequence) {
    createNewAlertDataConditionsObj->c_conditionSequence = conditionSequence;
    return createNewAlertDataConditionsObj;
}

CreateNewAlertDataConditions *cna_setNaturalLanguageCondition(CreateNewAlertDataConditions *createNewAlertDataConditionsObj, char *naturalLangCondition) {
    createNewAlertDataConditionsObj->c_naturalLangCondition = strdup(naturalLangCondition);
    return createNewAlertDataConditionsObj;
}

CreateNewAlertData *addNewAlertConditions(CreateNewAlertData *createNewAlertDataObj, CreateNewAlertDataConditions *conditionsObj) {
    CreateNewAlertDataConditionsList *newObject = (CreateNewAlertDataConditionsList *)malloc(sizeof(CreateNewAlertDataConditionsList));
    newObject->condition = conditionsObj;
    newObject->next = NULL;

    if(createNewAlertDataObj->conditions == NULL) {
        createNewAlertDataObj->conditions = newObject;
    } else {
        CreateNewAlertDataConditionsList *traverse = createNewAlertDataObj->conditions;
        while(traverse->next != NULL) {
            traverse = traverse->next;
        }
        traverse->next = conditionsObj;
    }

    return createNewAlertDataObj;
}

CreateNewAlertDataConditions *cna_addComponents(CreateNewAlertDataConditions *createNewAlertDataConditionsObj, CreateNewAlertDataConditionCmps *component) {
    CreateNewAlertDataConditionCmpsList *newObject = (CreateNewAlertDataConditionCmpsList *)malloc(sizeof(CreateNewAlertDataConditionCmpsList));

    newObject->component = component;
    newObject->next = NULL;

    if(createNewAlertDataConditionsObj->components == NULL) {
        createNewAlertDataConditionsObj->components = newObject;
    } else {
        CreateNewAlertDataConditionCmpsList *traverse = createNewAlertDataConditionsObj->components;
        while(traverse->next != NULL) {
            traverse = traverse->next;
        }

        traverse->next = newObject;
    }

    return createNewAlertDataConditionsObj;
}

CreateNewAlertDataConditionCmps *createNewAlertDataConditionCmpsObject() {
    CreateNewAlertDataConditionCmps * newObject = (CreateNewAlertDataConditionCmps *)malloc(sizeof(CreateNewAlertDataConditionCmps));

    if(newObject == NULL) {
        return NULL;
    }

    newObject->cmp_componentId = NULL;
    newObject->cmp_dataType = NULL;
    newObject->cmp_componentName = NULL;
    newObject->valuePoints = NULL;

    return newObject;
}

CreateNewAlertDataConditionCmps *cnac_setComponentId(CreateNewAlertDataConditionCmps *createNewAlertDataConditionCmpsObj, char *cmpId) {
    createNewAlertDataConditionCmpsObj->cmp_componentId = strdup(cmpId);
    return createNewAlertDataConditionCmpsObj;
}

CreateNewAlertDataConditionCmps *cnac_setDataType(CreateNewAlertDataConditionCmps *createNewAlertDataConditionCmpsObj, char *cmdDataType) {
    createNewAlertDataConditionCmpsObj->cmp_dataType = strdup(cmdDataType);
    return createNewAlertDataConditionCmpsObj;
}

CreateNewAlertDataConditionCmps *cnac_setComponentName(CreateNewAlertDataConditionCmps *createNewAlertDataConditionCmpsObj, char *cmpName) {
    createNewAlertDataConditionCmpsObj->cmp_componentName = strdup(cmpName);
    return createNewAlertDataConditionCmpsObj;
}

CreateNewAlertDataConditionCmps *cnac_addValuePoints(CreateNewAlertDataConditionCmps *createNewAlertDataConditionCmpsObj, long timestamp, char *value) {
    ConditionCmpsValuePoints *valuePoint = (ConditionCmpsValuePoints *)malloc(sizeof(ConditionCmpsValuePoints));
    CreateNewAlertDataConditionCmpsValuePoints *valuePoints = (CreateNewAlertDataConditionCmpsValuePoints *)malloc(sizeof(CreateNewAlertDataConditionCmpsValuePoints));
    valuePoint->timestamp = timestamp;
    valuePoint->value = strdup(value);

    valuePoints->valuePoint = valuePoint;
    valuePoints->next = NULL;

    if(createNewAlertDataConditionCmpsObj->valuePoints == NULL) {
        createNewAlertDataConditionCmpsObj->valuePoints = valuePoints;
    } else {
        CreateNewAlertDataConditionCmpsValuePoints *traverse = createNewAlertDataConditionCmpsObj->valuePoints;
        while(traverse->next != NULL) {
            traverse = traverse->next;
        }

        traverse->next = valuePoints;
    }

    return createNewAlertDataConditionCmpsObj;
}

bool createNewAlert(CreateNewAlert *createNewAlertObj, long *httpResponseCode, char **response) {
    struct curl_slist *headers = NULL;
    char *url;
    char body[BODY_SIZE_MAX];
    StringList *traverse = NULL;

    if(prepareUrl(&url, configurations.base_url, configurations.create_new_alert, NULL)) {
        appendHttpHeader(&headers, HEADER_CONTENT_TYPE_NAME, HEADER_CONTENT_TYPE_JSON);
        appendHttpHeader(&headers, HEADER_AUTHORIZATION, getConfigAuthorizationToken());

        strcpy(body, "{");

        strcat(body, "\"msgType\":\"");
        if(createNewAlertObj->msgType) {
            strcat(body, createNewAlertObj->msgType);
            strcat(body, "\"");
        } else {
            strcat(body, "alertsPush\"");
        }


        if(createNewAlertObj->dataList != NULL) {
            CreateNewAlertDataList *traverseDataList = createNewAlertObj->dataList;

            strcat(body, ",\"data\":[");
            while(traverseDataList) {

                CreateNewAlertData *traverseAlertData = traverseDataList->data;
                strcat(body, "{");
                strcat(body, "\"accountId\":\"");
                if(traverseAlertData->accountId) {
                    strcat(body, traverseAlertData->accountId);
                } else {
                    strcat(body, configurations.data_account_id);
                }
                strcat(body, "\"");

                if(traverseAlertData->alertId != -1) {
                    char tempstr[BODY_SIZE_MIN];
                    sprintf(tempstr, "%d", traverseAlertData->alertId);
                    strcat(body, ",\"alertId\":");
                    strcat(body, tempstr);
                }

                if(traverseAlertData->ruleId != -1) {
                    char tempstr[BODY_SIZE_MIN];
                    sprintf(tempstr, "%d", traverseAlertData->ruleId);
                    strcat(body, ",\"ruleId\":");
                    strcat(body, tempstr);
                }

                strcat(body, ",\"deviceId\":\"");
                if(traverseAlertData->deviceId) {
                    strcat(body, traverseAlertData->deviceId);
                } else {
                    strcat(body, configurations.device_id);
                }
                strcat(body, "\"");

                if(traverseAlertData->alertStatus) {
                    strcat(body, ",\"alertStatus\":\"");
                    strcat(body, traverseAlertData->alertStatus);
                    strcat(body, "\"");
                }

                if(traverseAlertData->timestamp > 0L) {
                    char tempstr[BODY_SIZE_MIN];
                    sprintf(tempstr, "%ld", traverseAlertData->timestamp);
                    strcat(body, ",\"timestamp\":");
                    strcat(body, tempstr);
                }

                if(traverseAlertData->resetTimestamp > 0L) {
                    char tempstr[BODY_SIZE_MIN];
                    sprintf(tempstr, "%ld", traverseAlertData->resetTimestamp);
                    strcat(body, ",\"resetTimestamp\":");
                    strcat(body, tempstr);
                }

                if(traverseAlertData->resetType) {
                    strcat(body, ",\"resetType\":\"");
                    strcat(body, traverseAlertData->resetType);
                    strcat(body, "\"");
                }

                if(traverseAlertData->lastUpdateDate > 0L) {
                    char tempstr[BODY_SIZE_MIN];
                    sprintf(tempstr, "%ld", traverseAlertData->lastUpdateDate);
                    strcat(body, ",\"lastUpdateDate\":");
                    strcat(body, tempstr);
                }

                if(traverseAlertData->ruleName) {
                    strcat(body, ",\"ruleName\":\"");
                    strcat(body, traverseAlertData->ruleName);
                    strcat(body, "\"");
                }

                if(traverseAlertData->rulePriority) {
                    strcat(body, ",\"rulePriority\":\"");
                    strcat(body, traverseAlertData->rulePriority);
                    strcat(body, "\"");
                }

                if(traverseAlertData->naturalLangAlert) {
                    strcat(body, ",\"naturalLangAlert\":\"");
                    strcat(body, traverseAlertData->naturalLangAlert);
                    strcat(body, "\"");
                }

                if(traverseAlertData->ruleExecutionTimestamp > 0L) {
                    char tempstr[BODY_SIZE_MIN];
                    sprintf(tempstr, "%ld", traverseAlertData->ruleExecutionTimestamp);
                    strcat(body, ",\"ruleExecutionTimestamp\":");
                    strcat(body, tempstr);
                }

                if(traverseAlertData->conditions) {
                    CreateNewAlertDataConditionsList *traverseDataConditionsList = traverseAlertData->conditions;

                    strcat(body, ",\"conditions\":[");
                    while(traverseDataConditionsList) {
                        strcat(body, "{");
                        CreateNewAlertDataConditions *dataCondition = traverseDataConditionsList->condition;

                        if(dataCondition->c_conditionSequence > -1) {
                            char tempstr[BODY_SIZE_MIN];
                            sprintf(tempstr, "%d", dataCondition->c_conditionSequence);
                            strcat(body, "\"conditionSequence\":");
                            strcat(body, tempstr);
                        }

                        if(dataCondition->c_naturalLangCondition) {
                            strcat(body, ",\"naturalLangCondition\":\"");
                            strcat(body, dataCondition->c_naturalLangCondition);
                            strcat(body, "\"");
                        }

                        if(dataCondition->components) {
                            CreateNewAlertDataConditionCmpsList *traverseCmpsList = dataCondition->components;
                            strcat(body, ",\"components\":[");

                            while(traverseCmpsList) {
                                CreateNewAlertDataConditionCmps *conComponent = traverseCmpsList->component;
                                strcat(body, "{");

                                if(conComponent->cmp_componentId) {
                                    strcat(body, "\"componentId\":\"");
                                    strcat(body, conComponent->cmp_componentId);
                                    strcat(body, "\"");
                                }
                                if(conComponent->cmp_dataType) {
                                    strcat(body, ",\"dataType\":\"");
                                    strcat(body, conComponent->cmp_dataType);
                                    strcat(body, "\"");
                                }

                                if(conComponent->cmp_componentName) {
                                    strcat(body, ",\"componentName\":\"");
                                    strcat(body, conComponent->cmp_componentName);
                                    strcat(body, "\"");
                                }

                                if(conComponent->valuePoints) {
                                    CreateNewAlertDataConditionCmpsValuePoints *traverseValuePointList = conComponent->valuePoints;
                                    strcat(body, ",\"valuePoints\":[");

                                    while(traverseValuePointList) {
                                        ConditionCmpsValuePoints *valuePoint = traverseValuePointList->valuePoint;
                                        strcat(body, "{");
                                        // TODO: some issue in the following loop; resulting into seg fault
                                        /*while(valuePoint) {
                                            char tempstr[BODY_SIZE_MIN];
                                            sprintf(tempstr, "%ld", valuePoint->timestamp);
                                            strcat(body, "\"timestamp\":");
                                            strcat(body, tempstr);
                                            strcat(body, ",\"value\":\"");
                                            strcat(body, valuePoint->value);
                                            strcat(body, "\"");
                                        }*/
                                        strcat(body, "}");
                                        traverseValuePointList = traverseValuePointList->next;

                                        if(traverseValuePointList) {
                                            strcat(body, ",");
                                        }
                                    }
                                    strcat(body, "]");
                                }
                                strcat(body, "}");

                                traverseCmpsList = traverseCmpsList->next;

                                if(traverseCmpsList) {
                                    strcat(body, ",");
                                }
                            }
                            strcat(body, "]");
                        }
                        strcat(body, "}");

                        traverseDataConditionsList = traverseDataConditionsList->next;

                        if(traverseDataConditionsList) {
                            strcat(body, ",");
                        }
                    }
                    strcat(body, "]");
                }
                strcat(body, "}");
                traverseDataList = traverseDataList->next;

                if(traverseDataList) {
                    strcat(body, ",");
                }
            }
            strcat(body, "]");
        }

        strcat(body, "}");

        #if DEBUG
            printf("Prepared BODY is %s\n", body);
        #endif

        doHttpPost(url, headers, body, httpResponseCode, response);

        return true;
    }

    return false;
}

bool getListOfAlerts(long *httpResponseCode, char **response) {
    struct curl_slist *headers = NULL;
    char *url;

    appendHttpHeader(&headers, HEADER_AUTHORIZATION, getConfigAuthorizationToken());

    if(prepareUrl(&url, configurations.base_url, configurations.get_list_of_alerts, NULL)) {

        doHttpGet(url, headers, httpResponseCode, response);

        return true;
    }

    return false;
}
