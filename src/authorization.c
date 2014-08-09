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


#include "iotkit.h"


bool getNewAuthorizationToken(char *username, char *password) {
    struct curl_slist *headers = NULL;
    char *url;
    char body[BODY_SIZE_MIN];

    if(!username) {
        fprintf(stderr, "Username cannot be NULL");
        return false;
    }

    if(!password) {
        fprintf(stderr, "Password cannot be NULL");
        return false;
    }


    prepareUrl(&url, configurations.base_url, configurations.new_auth_token);


    sprintf(body, "{\"username\":\"%s\",\"password\":\"%s\"}", username, password);

    appendHttpHeader(&headers, HEADER_CONTENT_TYPE_NAME, HEADER_CONTENT_TYPE_JSON);

    doHttpPost(url, headers, body);


    // TODO: store the authorization token in the config.json file


    return true;
}


bool validateAuthorizationToken() {
    struct curl_slist *headers = NULL;
    char *url;

    appendHttpHeader(&headers, HEADER_CONTENT_TYPE_NAME, HEADER_CONTENT_TYPE_JSON);
    appendHttpHeader(&headers, HEADER_AUTHORIZATION, getConfigAuthorizationToken());

    prepareUrl(&url, configurations.base_url, configurations.auth_token_info);

    doHttpGet(url, headers);

    // TODO: store the account id in the config.json file

    return true;
}



bool getAuthorizationTokenMeInfo() {
    struct curl_slist *headers = NULL;
    char *url;

    appendHttpHeader(&headers, HEADER_CONTENT_TYPE_NAME, HEADER_CONTENT_TYPE_JSON);
    appendHttpHeader(&headers, HEADER_AUTHORIZATION, getConfigAuthorizationToken());

    prepareUrl(&url, configurations.base_url, configurations.me_info);

    doHttpGet(url, headers);

    // TODO: store the account name etc in config.json file

    return true;
}


/*

Content-Type: application/json

Authorization: Bearer <token>

Get: https://dashboard.us.enableiot.com/v1/api/auth/tokeninfo

token: eyJ0eXAiOiJKV1QiLCJhbGciOiJSUzI1NiJ9.eyJqdGkiOiI4OTQ2YzVhYy1jYTE2LTRhODgtOGQ4Yi0zYzRiOGIzYTlhMTEiLCJpc3MiOiJodHRwOi8vZW5hYmxlaW90LmNvbSIsInN1YiI6IjUzY2Q2NDQ2ZmJhYzdlMDM1ZjcxYmM3ZSIsImV4cCI6IjIwMjQtMDgtMDVUMTk6MTk6NDYuMzY5WiJ9.VoWiV0cDUgcQwksX68r53b_vW7IoATy-vvBP2bFSA4f6QlgtOtk7nHswBdN8XFYA4v6EuF-zxSdBrBHfF1BTRwztFVrOAlLsMCyvoplf3i_2lWYjlFh6BnJ5uW8rykyKRd9oorNaPBnSwas3mSUKC0IcUNH02eRKbn4_mJ9GS2-UJiQAeLwjAsPCcGSQn9WxKQgq_CRZ7Mfw2dbB-vQc8I2TzCLtJaqd0UpHDTXpYs5eYZkuChDefeVGWY0-c3SDkhd3hS4J14lXdR-vaS54lrCKpYnCOj0KBDhj--80D1v9Z7LivIFO8-PJGtgtS-npoUhAeKVZsRE94exubsPXmg

accountid: 53cd6446fbac7e035f71bc7e
*/