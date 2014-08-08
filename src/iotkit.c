/*
 * iotkit 'C' Library to communicate with IoT Cloud via REST APIs
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
 * @file iotkit.c
 * @brief Implementation of iotkit library
 *
 * Provides features for communication with IoT Cloud server
 */

#include "iotkit.h"

static bool isInitialized = false;

void iotkit_init() {

    if(!isInitialized) {
        CURLcode code = rest_init();
        if(code) {
            fprintf(stderr, "Unable to initialize CURL %d\n", code);
        } else {
            isInitialized = true;
            puts("Library initialized successfully");
        }
    } else {
        puts("Library is already initialized and doesn't need to be re-initialized");
    }
}

void iotkit_cleanup() {
    if(isInitialized) {
        rest_cleanup();
        isInitialized = false;
    } else {
        puts("Library is not initialized and doesn't need to cleanup resources");
    }
}


#if DEBUG

    void main() {
        struct curl_slist *headers = NULL;
        puts("Iotkit Library to communicate with IoT Cloud via REST APIs");

        iotkit_init();

        appendHttpHeader(&headers, "Content-Type", "application/json");
        appendHttpHeader(&headers, "Authorization", "Bearer eyJ0eXAiOiJKV1QiLCJhbGciOiJSUzI1NiJ9.eyJqdGkiOiI3ZGQ2Mzc1Yy02ZWNlLTQ2ZjUtYWVmYi0wODVlYzVlMjc4YzAiLCJpc3MiOiJodHRwOi8vZW5hYmxlaW90LmNvbSIsInN1YiI6IjUzY2Q2NDQ2ZmJhYzdlMDM1ZjcxYmM3ZSIsImV4cCI6IjIwMjQtMDgtMDRUMjI6MDI6MjguMzY5WiJ9.nSl4BC9z_3j8JOxcvfi9UtrgJjVRdx_szO00y1wn66mgdZre1xpjVOmxoB30Xi5cLU5l7CEPpmCXUnzXTqZs_3slkQtO2_Yxk77LamX5ePkRzfDq50yPVnFlQzrgRxs_bdKcEJQMrhdsIhGq_IsSFZB0QMPGEXIxbLe2V2rjbK4dDmazb8q7uhlZ8GqT8sMQnl717b6iqJ8WtGbbRcoWuh9uQqDJsb9B_d6xIDYVONr3DrdBfOytNQPeqFWzGMP7NC34ygRyqYg4lscbAPC4ghf1pZ1sjLJUPAmyBjf9De7nIlXcwIDZYu8K7tptZ6XOGqTQiGzGQsg6Ar35R7CPAA");
        appendHttpHeader(&headers, "Expect", "");

        doHttpPut("https://dashboard.us.enableiot.com/v1/api/accounts/53cd6446fbac7e035f71bc7e/activationcode/refresh", \
                headers, NULL);


        iotkit_cleanup();
    }

#endif
