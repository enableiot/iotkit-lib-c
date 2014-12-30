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

#ifndef __ACCOUNT_MANAGEMENT_H
#define __ACCOUNT_MANAGEMENT_H


#ifdef __cplusplus
extern "C" {
#endif

#include "iotkit.h"

typedef struct _UpdateUserAccount {
    char *new_name;
    KeyValueParams *attributes;
    int healthTimePeriod;
    int exec_interval;
    int base_line_exec_interval;
    int cd_model_frequency;
    int cd_execution_frequency;
    int data_retention;
} UpdateUserAccount;


char *createAnAccount(char *account_name);
char *getAccountInformation();
char *getAccountActivationCode();
char *renewActivationCode();
char *updateAnAccount(UpdateUserAccount *updateUserAccount);
char *deleteAnAccount();
char *getUserAssociatedWithAccount();
char *addAnUserToAccount(char *account_id, char * user_id, bool isAdmin);

UpdateUserAccount *createUpdateUserAccountObject(char *new_name);
void setUpdateAccountAttributes(UpdateUserAccount *updateUserAccount, KeyValueParams *attributes);
void setUpdateAccountHealthTimePeriod(UpdateUserAccount *updateUserAccount, int healthTimePeriod);
void setUpdateAccountExecInterval(UpdateUserAccount *updateUserAccount, int exec_interval);
void setUpdateAccountBaseLineExecInterval(UpdateUserAccount *updateUserAccount, int base_line_exec_interval);
void setUpdateAccountCdModelFrequency(UpdateUserAccount *updateUserAccount, int cd_model_frequency);
void setUpdateAccountCdExecutionFrequency(UpdateUserAccount *updateUserAccount, int cd_execution_frequency);
void setUpdateAccountDataRetention(UpdateUserAccount *updateUserAccount, int data_retention);

#ifdef __cplusplus
}
#endif

#endif
