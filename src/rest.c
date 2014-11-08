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

    if(*userp != NULL) {
        // means this is a multi-part response
        // so we need to append this response to the previous response fragment
        char *fragment = strndup(buffer, (size_t)(size *nmemb));
        int size = strlen(*userp);
        size += strlen(fragment) + 1;

        *userp = (char *)realloc(*userp, size * sizeof(char));
        strcat(*userp, fragment);

        write_length = strlen(fragment);

        free(fragment);
    } else {
        *userp = strndup(buffer, (size_t)(size *nmemb));
        write_length = strlen(*userp);
    }

    #if DEBUG
        printf("Values received :%s\n", *userp);
    #endif
    return write_length;
}

int doHttpGet(char *url, struct curl_slist *headers, HttpResponse *response) {
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
        #if DEBUG
            curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
        #else
            curl_easy_setopt(curl, CURLOPT_VERBOSE, 0L);
        #endif
        /* incase of redirection, follow the new url */
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

        /* callback function to return data */
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback_func);

        /* pass the response to callback function */
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response->data);

        res = curl_easy_perform(curl);

        if(response) {
            response->code = 0;
            curl_easy_getinfo (curl, CURLINFO_RESPONSE_CODE, &response->code);
        }

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


int doHttpPut(char *url, struct curl_slist *headers, char *body, HttpResponse *response) {
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
        #if DEBUG
            curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
        #else
            curl_easy_setopt(curl, CURLOPT_VERBOSE, 0L);
        #endif
        /* incase of redirection, follow the new url */
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "PUT");

        if(body) {
            curl_easy_setopt(curl, CURLOPT_POSTFIELDS, body);
        }

        /* callback function to return data */
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback_func);

        /* pass the response to callback function */
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response->data);

        res = curl_easy_perform(curl);

        if(response) {
            response->code = 0;
            curl_easy_getinfo (curl, CURLINFO_RESPONSE_CODE, &response->code);
        }

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

int doHttpPost(char *url, struct curl_slist *headers, char *body, HttpResponse *response) {
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
        #if DEBUG
            curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
        #else
            curl_easy_setopt(curl, CURLOPT_VERBOSE, 0L);
        #endif
        /* incase of redirection, follow the new url */
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

        if(body) {
            curl_easy_setopt(curl, CURLOPT_POSTFIELDS, body);
        }

        /* callback function to return data */
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback_func);

        /* pass the response to callback function */
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response->data);

        res = curl_easy_perform(curl);

        if(response) {
            response->code = 0;
            curl_easy_getinfo (curl, CURLINFO_RESPONSE_CODE, &response->code);
        }

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

int doHttpDelete(char *url, struct curl_slist *headers, HttpResponse *response) {
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
        #if DEBUG
            curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
        #else
            curl_easy_setopt(curl, CURLOPT_VERBOSE, 0L);
        #endif

        /* incase of redirection, follow the new url */
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "DELETE");

        /* callback function to return data */
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback_func);

        /* pass the response to callback function */
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response->data);

        res = curl_easy_perform(curl);

        if(response) {
            response->code = 0;
            curl_easy_getinfo (curl, CURLINFO_RESPONSE_CODE, &response->code);
        }

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
