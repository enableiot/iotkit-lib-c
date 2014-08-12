/*
 * Authorization API module to communicate with IoT Cloud via REST APIs
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
 * @file authorization.c
 * @brief Implementation of Authorization API
 *
 * Provides features for communication with IoT Cloud server
 */

bool test_validateAuthorizationToken() {
    struct curl_slist *headers = NULL;

    iotkit_init();

    appendHttpHeader(&headers, "Content-Type", "application/json");
    appendHttpHeader(&headers, "Authorization", "Bearer eyJ0eXAiOiJKV1QiLCJhbGciOiJSUzI1NiJ9.eyJqdGkiOiI3ZGQ2Mzc1Yy02ZWNlLTQ2ZjUtYWVmYi0wODVlYzVlMjc4YzAiLCJpc3MiOiJodHRwOi8vZW5hYmxlaW90LmNvbSIsInN1YiI6IjUzY2Q2NDQ2ZmJhYzdlMDM1ZjcxYmM3ZSIsImV4cCI6IjIwMjQtMDgtMDRUMjI6MDI6MjguMzY5WiJ9.nSl4BC9z_3j8JOxcvfi9UtrgJjVRdx_szO00y1wn66mgdZre1xpjVOmxoB30Xi5cLU5l7CEPpmCXUnzXTqZs_3slkQtO2_Yxk77LamX5ePkRzfDq50yPVnFlQzrgRxs_bdKcEJQMrhdsIhGq_IsSFZB0QMPGEXIxbLe2V2rjbK4dDmazb8q7uhlZ8GqT8sMQnl717b6iqJ8WtGbbRcoWuh9uQqDJsb9B_d6xIDYVONr3DrdBfOytNQPeqFWzGMP7NC34ygRyqYg4lscbAPC4ghf1pZ1sjLJUPAmyBjf9De7nIlXcwIDZYu8K7tptZ6XOGqTQiGzGQsg6Ar35R7CPAA");

    doHttpGet("https://dashboard.us.enableiot.com/v1/api/auth/tokeninfo", headers);


    iotkit_cleanup();
}
