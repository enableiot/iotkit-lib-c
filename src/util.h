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

#ifndef __CJSON_UTIL_H
#define __CJSON_UTIL_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdbool.h>
#include "cJSON.h"

/** Check whether JSON item is a boolean false */
static inline bool isJsonBooleanFalse(cJSON *item) {
    if (item == NULL || item->type != cJSON_False) {
        return false;
    }
    return true;
}

/** Check whether JSON item is a boolean true */
static inline bool isJsonBooleanTrue(cJSON *item) {
    if (item == NULL || item->type != cJSON_True) {
        return false;
    }
    return true;
}

/** Check whether JSON item is a NULL object */
static inline bool isJsonNull(cJSON *item) {
    if (item == NULL || item->type != cJSON_NULL) {
        return false;
    }
    return true;
}

/** Check whether JSON item is a string. */
static inline bool isJsonString(cJSON *item) {
    if (item == NULL || item->type != cJSON_String) {
        return false;
    }
    return true;
}

/** Check whether JSON item is a number. */
static inline bool isJsonNumber(cJSON *item) {
    if (item == NULL || item->type != cJSON_Number) {
        return false;
    }
    return true;
}

/** Check whether JSON item is an object. */
static inline bool isJsonObject(cJSON *item) {
    if (item == NULL || item->type != cJSON_Object) {
        return false;
    }
    return true;
}

/** Check whether JSON item is an array. */
static inline bool isJsonArray(cJSON *item) {
    if (item == NULL || item->type != cJSON_Array) {
        return false;
    }
    return true;
}

#ifdef __cplusplus
}
#endif

#endif
