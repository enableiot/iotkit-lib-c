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

#include "device_management.h"

int main(void) {
    char *response = NULL;
/*
    char *activationCode = NULL;
    FILE *fp = fopen(".tempcode", "rb");

    if (fp == NULL) {
        fprintf(stderr,"Error can't open file .tempcode\n");
    } else {
        fseek(fp, 0, SEEK_END);
        long size = ftell(fp);
        rewind(fp);

        // read the file
        activationCode = (char *)malloc(size+1);
        fread(activationCode, 1, size, fp);
        activationCode[size] = '\0';
        fclose(fp);
        remove(".tempcode");
    }

    activationCode = strdup("v54iwMu7");
*/
    iotkit_init();

    response = activateADevice2("2r3QciFH", "02-00-86-81-77-12");
    printf("Response Received :%s\n", response);

    iotkit_cleanup();

    if(checkResponseValue(response, 200) == true) {
        exit(EXIT_SUCCESS);
    }

    exit(EXIT_FAILURE);
}
