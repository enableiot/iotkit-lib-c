/*
 * REST Library to support rest based SSL communication
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
 * @file rest.h
 * @brief Header file of rest library
 *
 * Data Structures and function declarations
 */

#ifndef __REST_H
#define __REST_H

#include <stdbool.h>
#include <curl/curl.h>


struct putData {
  char *data;
  size_t len;
};

#endif
