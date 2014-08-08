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

CURLcode rest_init() {
    CURLcode returnCode;

    returnCode = curl_global_init(CURL_GLOBAL_SSL);

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

int doHttpGet(char *url, struct curl_slist *headers) {
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


static size_t readCallbackForPut(void *ptr, size_t size, size_t nmemb, struct putData *userdata)
{
  size_t curl_size = nmemb * size;
  size_t to_copy = (userdata->len < curl_size) ? userdata->len : curl_size;
  memcpy(ptr, userdata->data, to_copy);
  userdata->len -= to_copy;
  userdata->data += to_copy;
  return to_copy;
}

int doHttpPut(char *url, struct curl_slist *headers, char *body) {
    CURL *curl;
    CURLcode res;
    struct putData *datal = (struct putData *)malloc(sizeof(struct putData));
    datal->data = "{}";
    datal->len = 2;

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

        curl_easy_setopt(curl, CURLOPT_PUT, 1L);

        /*if(!body) {
            curl_easy_setopt(curl, CURLOPT_POSTFIELDS, body);
        }*/

        /* we want to use our own read function */
        curl_easy_setopt(curl, CURLOPT_READDATA, datal);
        /* we want to use our own read function */
        curl_easy_setopt(curl, CURLOPT_READFUNCTION, readCallbackForPut);

        /* enable uploading */
        curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);

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

int doHttpPost(char *url, struct curl_slist *headers, char *body) {
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

        if(!body) {
            curl_easy_setopt(curl, CURLOPT_POSTFIELDS, body);
        }

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
