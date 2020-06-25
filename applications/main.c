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

    rt_device_t lcd;

    
    gpiohs_set_drive_mode(LED_1_PIN, GPIO_DM_OUTPUT);
    gpiohs_set_drive_mode(LED_2_PIN, GPIO_DM_OUTPUT);
    gpiohs_set_drive_mode(LED_3_PIN, GPIO_DM_OUTPUT);

    //gpiohs_set_drive_mode(LCD_RST_PIN, GPIO_DM_OUTPUT);
    //gpiohs_set_drive_mode(LCD_DC_PIN, GPIO_DM_OUTPUT);
    
    rt_kprintf("Hello, world\n");

    //uart_send_data(UART_DEVICE_1, "aaaaaaaaa", 5);

    for (i = 0; i < 10; i++)
    {
        rt_kprintf("this is a test!!!\n");
    }

    //spi_init(SPI_DEVICE_0, SPI_WORK_MODE_0, SPI_FF_OCTAL, 8, 0);
    //spi_set_clk_rate(SPI_DEVICE_0, 10000000);

    

    uartx = rt_device_find("uarths");
    rt_device_write(uartx, 0, "aaaaaaaaa", 5);

    lcd = rt_device_find("lcd_9341");
    rt_device_init(lcd);

    while(1)
    {
        gpiohs_set_pin(LED_1_PIN, GPIO_PV_HIGH);
        gpiohs_set_pin(LED_2_PIN, GPIO_PV_HIGH);
        //gpiohs_set_pin(LCD_RST_PIN, GPIO_PV_HIGH);
        //gpiohs_set_pin(LCD_DC_PIN, GPIO_PV_HIGH);
        rt_thread_mdelay(1000);
        
        gpiohs_set_pin(LED_1_PIN, GPIO_PV_LOW);
        gpiohs_set_pin(LED_2_PIN, GPIO_PV_LOW);
        //gpiohs_set_pin(LCD_RST_PIN, GPIO_PV_LOW);
        //gpiohs_set_pin(LCD_DC_PIN, GPIO_PV_LOW);
        rt_thread_mdelay(1000);
    }
    
    return 0;
}
