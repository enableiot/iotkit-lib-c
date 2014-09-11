/*
 * rest Library to support rest based SSL communication
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
 * @file rest.c
 * @brief Implementation of rest library
 *
 * Provides features for communication with Web server
 */

#include "rest.h"

CURLcode rest_init(bool isSecure) {
    CURLcode returnCode;

    if(isSecure) {
        returnCode = curl_global_init(CURL_GLOBAL_SSL);
    } else {
        returnCode = curl_global_init(CURL_GLOBAL_NOTHING);
    }

    return returnCode;
}


void rest_cleanup(void) {
    curl_global_cleanup();
}


bool setUrl(CURL *curl, char *url) {
    if(!curl) {
        fprintf(stderr, "error: Curl handle cannot be NULL");
        return false;
    }

    if(!url) {
        fprintf(stderr, "error: url cannot be NULL");
        return false;
    }

    curl_easy_setopt(curl, CURLOPT_URL, url);
    return true;
}

bool addUrlParam(CURL *curl, char *paramname, char *paramvalue) {
    if(!curl) {
        fprintf(stderr, "error: Curl handle cannot be NULL");
        return false;
    }

    return true;
}

void addBody(CURL *curl_handle, char *body) {
}

bool appendHttpHeader(struct curl_slist ** headerList, char *headername, char *headervalue) {

    char *header = NULL;

    if(!headername) {
        fprintf(stderr, "Name cannot be null");

        return false;
    }

    header = (char *)malloc(sizeof(char) * (strlen(headername) + strlen(headervalue) + 2));
    sprintf(header, "%s:%s", headername, headervalue);


    *headerList = curl_slist_append(*headerList, header);

    return true;
}

size_t static write_callback_func(void *buffer, size_t size, size_t nmemb, char **userp)
{
    size_t write_length = 0;

    *userp = strndup(buffer, (size_t)(size *nmemb));
    write_length = strlen(*userp);

    printf("Values received :%s\n", *userp);
    return write_length;
}

int doHttpGet(char *url, struct curl_slist *headers, char **response) {
    CURL *curl;
    CURLcode res;

    curl = curl_easy_init();
    if(curl) {

        setUrl(curl, url);

        /* set the headers */
        if(headers) {
            curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        }

        /* display verbose */
        curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
        /* incase of redirection, follow the new url */
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

        /* callback function to return data */
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback_func);

        /* pass the response to callback function */
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, response);

        res = curl_easy_perform(curl);
        if(res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n",
                  curl_easy_strerror(res));

            curl_easy_cleanup(curl);
            return 1;
        }

        curl_easy_cleanup(curl);
    }

    return 0;
}


int doHttpPut(char *url, struct curl_slist *headers, char *body, char **response) {
    CURL *curl;
    CURLcode res;

    curl = curl_easy_init();
    if(curl) {

        setUrl(curl, url);

        /* set the headers */
        if(headers) {
            curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        }

        /* display verbose */
        curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
        /* incase of redirection, follow the new url */
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "PUT");

        if(body) {
            curl_easy_setopt(curl, CURLOPT_POSTFIELDS, body);
        }

        /* callback function to return data */
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback_func);

        /* pass the response to callback function */
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, response);

        res = curl_easy_perform(curl);
        if(res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n",
                  curl_easy_strerror(res));

            curl_easy_cleanup(curl);
            return 1;
        }

        curl_easy_cleanup(curl);
    }

    return 0;
}

int doHttpPost(char *url, struct curl_slist *headers, char *body, char **response) {
    CURL *curl;
    CURLcode res;

    curl = curl_easy_init();
    if(curl) {

        setUrl(curl, url);

        /* set the headers */
        if(headers) {
            curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        }

        /* display verbose */
        curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
        /* incase of redirection, follow the new url */
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

        if(body) {
            curl_easy_setopt(curl, CURLOPT_POSTFIELDS, body);
        }

        /* callback function to return data */
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback_func);

        /* pass the response to callback function */
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, response);

        res = curl_easy_perform(curl);
        if(res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n",
                  curl_easy_strerror(res));

            curl_easy_cleanup(curl);
            return 1;
        }

        curl_easy_cleanup(curl);
    }

    return 0;
}

int doHttpDelete(char *url, struct curl_slist *headers) {
    CURL *curl;
    CURLcode res;

    curl = curl_easy_init();
    if(curl) {

        setUrl(curl, url);

        /* set the headers */
        if(headers) {
            curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        }

        /* display verbose */
        curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

        /* incase of redirection, follow the new url */
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "DELETE");

        res = curl_easy_perform(curl);
        if(res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n",
                  curl_easy_strerror(res));

            curl_easy_cleanup(curl);
            return 1;
        }

        curl_easy_cleanup(curl);
    }

    return 0;
}
