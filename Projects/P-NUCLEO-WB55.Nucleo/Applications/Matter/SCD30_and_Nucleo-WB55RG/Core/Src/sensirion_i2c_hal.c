/*
 * Copyright (c) 2018, Sensirion AG
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 *
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 * * Neither the name of Sensirion AG nor the names of its
 *   contributors may be used to endorse or promote products derived from
 *   this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */
#include <stm32wbxx_hal.h>
#include "cmsis_os.h"

#include "sensirion_i2c_hal.h"
#include "sensirion_common.h"
#include "sensirion_config.h"

/**
 * Use the I2C handle already defined and initialized in main.cpp
 */
extern I2C_HandleTypeDef hi2c1;

int16_t sensirion_i2c_hal_select_bus(uint8_t bus_idx) {
    return NOT_IMPLEMENTED_ERROR;
}

void sensirion_i2c_hal_init(void) {
    /* I2C1 is already initialized in main.cpp via MX_I2C1_Init() */
}

void sensirion_i2c_hal_free(void) {
    /* Nothing to free */
}

int8_t sensirion_i2c_hal_read(uint8_t address, uint8_t* data, uint8_t count) {
    return (int8_t)HAL_I2C_Master_Receive(&hi2c1, (uint16_t)(address << 1),
                                          data, count, 200);
}

int8_t sensirion_i2c_hal_write(uint8_t address, const uint8_t* data,
                               uint8_t count) {
    return (int8_t)HAL_I2C_Master_Transmit(&hi2c1, (uint16_t)(address << 1),
                                           (uint8_t*)data, count, 200);
}

void sensirion_i2c_hal_sleep_usec(uint32_t useconds) {
    uint32_t msec = useconds / 1000;
    if (useconds % 1000 > 0) {
        msec++;
    }
    // Use FreeRTOS-aware delay instead of busy-wait HAL_Delay
    if (msec > 0) {
        osDelay(msec);
    }
}
