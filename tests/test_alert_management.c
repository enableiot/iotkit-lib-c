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

#include "../src/alert_management.h"

bool testCreateNewAlert() {
    char *response = NULL;
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

    response = createNewAlert(createNewAlertObj);

    printf("Response Received :%s\n", response);

    /*if(response->code == 201) {
        return true;
    }*/

    return false;
}

bool testGetListOfAlerts() {
    char *response = NULL;

    response = getListOfAlerts();

    printf("Response Received :%s\n", response);

    /*if(response->code == 200) {
        return true;
    }*/

    return false;
}

bool testGetAlertInformation() {
    char *response = NULL;

    response = getAlertInformation("75");

    printf("Response Received :%s\n", response);

    /*if(response->code == 200) {
        return true;
    }*/

    return false;
}

bool testResetAlert() {
    char *response = NULL;

    response = resetAlert("75");

    printf("Response Received :%s\n", response);

    /*if(response->code == 200) {
        return true;
    }*/

    return false;
}

bool testUpdateAlertStatus() {
    char *response = NULL;

    response = updateAlertStatus("75", "Open");

    printf("Response Received :%s\n", response);

    /*if(response->code == 200) {
        return true;
    }*/

    return false;
}

bool testAddCommentToAlert() {
    char *response = NULL;

    response = addCommentToAlert("75", "pradyp7@gmail.com", 45972979284L, "Machinery arrival");

    printf("Response Received :%s\n", response);

    /*if(response->code == 200) {
        return true;
    }*/

    return false;
}
