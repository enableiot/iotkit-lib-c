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

#include "../src/account_management.h"

bool testCreateAnAccount() {
    char *response = NULL;

    response = createAnAccount("willitcreate5");

    printf("Response Received :%s\n", response);

    /*if(response->code == 201) {
        return true;
    }*/

    return false;
}

bool testGetAccountInformation() {
    char *response = NULL;

    response = getAccountInformation();

    printf("Response Received :%s\n", response);

    /*if(response->code == 200) {
        return true;
    }*/

    return false;
}

bool testGetAccountActivationCode() {
    char *response = NULL;

    response = getAccountActivationCode();

    printf("Response Received :%s\n", response);

    /*if(response->code == 200) {
        return true;
    }*/

    return false;
}

bool testRenewAccountActivationCode() {
    char *response = NULL;

    response = renewActivationCode();

    printf("Response Received :%s\n", response);

    /*if(response->code == 200) {
        return true;
    }*/

    return false;
}

bool testUpdateAnAccount() {
    char *response = NULL;
    // TODO: json object needs to be sent for updation

    response = updateAnAccount("willitcreate2");

    printf("Response Received :%s\n", response);

    /*if(response->code == 200) {
        return true;
    }*/

    return false;
}

bool testDeleteAnAccount() {
    char *response = NULL;

    response = deleteAnAccount();

    printf("Response Received :%s\n", response);

    /*if(response->code == 204) {
        return true;
    }*/

    return false;
}

bool testGetUserAssociatedWithAccount() {
    char *response = NULL;

    response = getUserAssociatedWithAccount();

    printf("Response Received :%s\n", response);

    /*if(response->code == 200) {
        return true;
    }*/

    return false;
}

bool testAddAnUserToAccount() {
    char *response = NULL;

    response = addAnUserToAccount("5cf1f891-b388-4795-8abc-b604ded6b163", "53fe452fd6e2061551153a88", false);

    printf("Response Received :%s\n", response);

    /*if(response->code == 200) {
        return true;
    }*/

    return false;
}

/*
bool testUpdateUserAssociatedWithAccount() {
    UpdateUserAccount *userData = NULL;
    char *response = NULL;
    long httpResponseCode;

    userData = createUpdateUserAccountObject();
    addUpdateUserAccountAttributes(userData, "phone", "5036568978");
    addUpdateUserAccountAttributes(userData, "new_name", "new_value");
    //addUpdateUserAccountEmail(userData, "pradyp7tmp@gmail.com");
    addUpdateUserAccountTerms(userData, true);
    addUpdateUserAccountVerified(userData, true);

    updateUserAssociatedWithAccount(userData, &httpResponseCode, &response);

    printf("Response Received :%s\n", response);

    if(httpResponseCode == 200) {
        return true;
    }

    return false;
}
*/
