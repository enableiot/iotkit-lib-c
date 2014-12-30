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

#include "account_management.h"

bool storeActivationCode(char *response) {
    cJSON *json = NULL, *jitem = NULL, *child = NULL;

    // parse the file
    json = cJSON_Parse(response);
    if (!json) {
        fprintf(stderr,"Could not parse reponse, error before: [%s]\n",cJSON_GetErrorPtr());
    } else {
        if (!isJsonObject(json)) {
            fprintf(stderr,"Invalid JSON format response\n");
        } else {
            jitem = cJSON_GetObjectItem(json, "data");
            if (!jitem) {
                fprintf(stderr,"Invalid JSON format for json property %s\n", jitem->string);
            } else {
                child = cJSON_GetObjectItem(jitem, "activationCode");
                if (!isJsonString(child)) {
                    fprintf(stderr,"Invalid value for activationCode\n");
                } else {
                    FILE *fp = fopen(".tempcode", "w+");
                    if (fp == NULL) {
                        fprintf(stderr,"Error can't open file .tempcode\n");
                    }
                    else {
                        fwrite(child->valuestring, strlen(child->valuestring), sizeof(char), fp);
                        fclose(fp);
                        return true;
                    }
                }
            }
        }
    }

    return false;
}

int main(void) {
    char *response = NULL;

    iotkit_init();

    response = getAccountActivationCode();

    printf("Response Received :%s\n", response);

    iotkit_cleanup();

    if(checkResponseValue(response, 200) == true) {
        if(storeActivationCode(response) == true) {
            exit(EXIT_SUCCESS);
        }
    }

    exit(EXIT_FAILURE);
}
