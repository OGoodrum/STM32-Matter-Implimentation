/*
 *
 *    Copyright (c) 2018 Nest Labs, Inc.
 *    All rights reserved.
 *
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *
 *        http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 */

#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#ifndef APP_EVENT_H
#define APP_EVENT_H

struct AppEvent;
typedef void (*EventHandler)(AppEvent *);

struct AppEvent
{
    enum AppEventTypes
    {
        kEventType_Button = 0,
        kEventType_Timer,
        kEventType_Level,
        kEventType_Install,
        kEventType_Sensor,
    };

    uint16_t Type;

    union
    {
        struct
        {
            uint8_t ButtonIdx;
            uint8_t Action;
        } ButtonEvent;
        struct
        {
            void * Context;
        } TimerEvent;
        struct
        {
            uint8_t Action;
            int32_t Color;
        } LightingEvent;
        struct
        {
            int16_t CO2ppm;       // CO2 in ppm (raw integer)
            int16_t TemperatureCx10; // Temperature in 0.1 °C steps (e.g. 245 = 24.5 °C)
            int16_t HumidityPctx10;  // Relative humidity in 0.1 % steps (e.g. 382 = 38.2 %)
        } SensorEvent;
    };

    EventHandler Handler;
};

#endif // APP_EVENT_H
