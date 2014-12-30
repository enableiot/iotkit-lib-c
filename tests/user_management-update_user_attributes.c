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

#include "iotkit.h"
#include "cJSON.h"

int main(void) {
    char *response = NULL;
    KeyValueParams *attributesList = NULL, *attribute1 = NULL, *attribute2 = NULL, *attribute3 = NULL;

    iotkit_init();

    attribute3 = (KeyValueParams *)malloc(sizeof(KeyValueParams));
    attribute3->name = strdup("new");
    attribute3->value = strdup("next_string_value");
    attribute3->next = NULL;

    attribute2 = (KeyValueParams *)malloc(sizeof(KeyValueParams));
    attribute2->name = strdup("another_attribute");
    attribute2->value = strdup("another_value");
    attribute2->next = attribute3;

    attribute1 = (KeyValueParams *)malloc(sizeof(KeyValueParams));
    attribute1->name = strdup("phone");
    attribute1->value = strdup("123456789");
    attribute1->next = attribute2;

    attributesList = attribute1;

// pass user ID explicitly
//    getUserInformation("544c093c676e33cf6a779070", &httpResponseCode, &response);

// or pass NULL to consider own user ID
    response = updateUserAttributes(NULL, attributesList);

    printf("Response Received :%s\n", response);

    iotkit_cleanup();

    if(checkResponseValue(response, 200) == true) {
        exit(EXIT_SUCCESS);
    }

    exit(EXIT_FAILURE);
}
