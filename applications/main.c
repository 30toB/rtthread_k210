/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018/09/30     Bernard      The first version
 */

#include <rtthread.h>
#include <stdio.h>

#include "uart.h"
#include "spi.h"

#include "drv_io_config.h"
#include <gpiohs.h>


int main(void)
{
    uint32_t i = 0;

    rt_device_t uartx;

    gpiohs_set_drive_mode(LED_1_PIN, GPIO_DM_OUTPUT);
    gpiohs_set_drive_mode(LED_2_PIN, GPIO_DM_OUTPUT);
    gpiohs_set_drive_mode(LED_3_PIN, GPIO_DM_OUTPUT);

    rt_kprintf("Hello, world\n");

    uartx = rt_device_find("uarths");
    rt_device_write(uartx, 0, "aaaaaaaaa", 5);


    while(1)
    {
        gpiohs_set_pin(LED_1_PIN, GPIO_PV_HIGH);
        gpiohs_set_pin(LED_2_PIN, GPIO_PV_HIGH);
        rt_thread_mdelay(1000);
        
        gpiohs_set_pin(LED_1_PIN, GPIO_PV_LOW);
        gpiohs_set_pin(LED_2_PIN, GPIO_PV_LOW);
        rt_thread_mdelay(1000);
    }
    
    return 0;
}
