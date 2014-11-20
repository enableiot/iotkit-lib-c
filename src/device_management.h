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

#ifndef __DEVICE_MANAGEMENT_H
#define __DEVICE_MANAGEMENT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "iotkit.h"

typedef struct _DeviceCreationObj {
    char *device_id;
    char *gateway_id;
    char *device_name;

    StringList *tags;

    char *latitude;
    char *longitude;
    char *height;

    KeyValueParams *attributes;
} DeviceCreationObj;

char *listAllDevices();
char *getMyDeviceInfo();
char *getOneDeviceInfo(char *device_id);

DeviceCreationObj *createDeviceCreationObject(char *device_id, char *gateway_id, char *device_name);
DeviceCreationObj *addLocInfo(DeviceCreationObj *createDeviceObj, char *latitude, char *longitude, char *height);
DeviceCreationObj *addTagInfo(DeviceCreationObj *createDeviceObj, char *tagName);
DeviceCreationObj *addAttributesInfo(DeviceCreationObj *createDeviceObj, char *name, char *value);

char *createADevice(DeviceCreationObj *createDeviceObj);
char *updateADevice(DeviceCreationObj *createDeviceObj);
char *activateADevice(char *activation_code);
char *deleteADevice(char *device_id);

bool isSensorRegistered(char *name);
char *getSensorComponentId(char *name);
bool isDeviceActivated();

char *addComponent(char *cmp_name, char *cmp_type);
char *deleteComponent(char *sensor_name);
char *listAllTagsForDevices();
char *listAllAttributesForDevices();

#ifdef __cplusplus
}
#endif

#endif
