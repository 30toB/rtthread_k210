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
#include "lvgl.h"

#include <gpiohs.h>

//-----------------------------------------------------------------------------
// lv_tutorial_hello_world
//-----------------------------------------------------------------------------
void lv_tutorial_hello_world1(void)
{
    lv_obj_t * scr = lv_disp_get_scr_act(NULL);
    
    lv_obj_t * label2 = lv_label_create(scr, NULL);
    lv_label_set_text(label2, "Hello World!");
    lv_obj_align(label2, NULL, LV_ALIGN_CENTER, 0, 0);
    
    lv_obj_t * btn1 = lv_btn_create(scr, NULL);
    lv_btn_set_style(btn1, LV_BTN_STYLE_TGL_REL, NULL);
    lv_obj_align(btn1, NULL, LV_ALIGN_IN_BOTTOM_MID, 10, -10);
    
    lv_obj_t * label2;//????1?????label1
    label2 = lv_label_create(btn1, NULL);//???btn1???label1??
    lv_label_set_text(label2, "Button");//??label?text	
}

//-----------------------------------------------------------------------------
// main
//-----------------------------------------------------------------------------
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

    rt_thread_mdelay(1000);
    
    lv_tutorial_hello_world1();

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
