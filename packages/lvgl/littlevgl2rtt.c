#include "littlevgl2rtt.h"
#include "lvgl.h"

//-----------------------------------------------------------------------------
// type define
//-----------------------------------------------------------------------------

#define LVGL_BUFFER_SIZE    (LV_HOR_RES_MAX * LV_VER_RES_MAX)

//-----------------------------------------------------------------------------
// global variables
//-----------------------------------------------------------------------------
static rt_device_t lcd_device = RT_NULL;
static struct rt_device_graphic_info *graphic_info = RT_NULL;

//-----------------------------------------------------------------------------
// lv_tutorial_hello_world
//-----------------------------------------------------------------------------
void lv_tutorial_hello_world(void)
{
    lv_obj_t * scr = lv_disp_get_scr_act(NULL);
    lv_obj_t * label1 = lv_label_create(scr, NULL);
    lv_label_set_text(label1, "Hello World!");
    lv_obj_align(label1, NULL, LV_ALIGN_CENTER, 0, 0);
    
    lv_obj_t * btn1 = lv_btn_create(scr, NULL);
    lv_btn_set_style(btn1, LV_BTN_STYLE_TGL_REL, NULL);
    lv_obj_align(btn1, NULL, LV_ALIGN_IN_BOTTOM_MID, 10, -10);
    
    lv_obj_t * label2;//????1?????label1
    label2 = lv_label_create(btn1, NULL);//???btn1???label1??
    lv_label_set_text(label2, "Button");//??label?text	
}

//-----------------------------------------------------------------------------
// input_read
// 读取输入控制信息
//-----------------------------------------------------------------------------
static bool input_read(lv_indev_drv_t *drv, lv_indev_data_t *data)
{
    static rt_bool_t touch_down = RT_FALSE;

    int x      = 0;
    int y      = 0;
    
    /*
        int status = TOUCHSCREEN_STATUS_IDLE;

    touchscreen_read(&status, &x, &y);
    if (status == TOUCHSCREEN_STATUS_PRESS)
    {
        touch_down = RT_TRUE;
    }
    else if (status == TOUCHSCREEN_STATUS_RELEASE)
    {
        touch_down = RT_FALSE;
    }*/

    data->point.x = x;
    data->point.y = y;
    data->state   = (touch_down == RT_TRUE) ? LV_INDEV_STATE_PR : LV_INDEV_STATE_REL;

    return false;
}

//-----------------------------------------------------------------------------
// disp_flush
// 刷新缓存到屏幕中，此函数为核心函数
//-----------------------------------------------------------------------------
static void disp_flush(lv_disp_drv_t *disp_drv, const lv_area_t *area, lv_color_t *color_p)
{
    int32_t x;
    int32_t y;
    struct rt_device_rect_info rect_info;

    RT_ASSERT(lcd_device != RT_NULL);

    rect_info.x = area->x1;
    rect_info.y = area->y1;
    rect_info.width = area->x2 - area->x1;
    rect_info.height = area->y2 - area->y1;

    lcd_device->control(lcd_device, RTGRAPHIC_CTRL_RECT_UPDATE, (void *)&rect_info);
    
    lv_disp_flush_ready(disp_drv);
}

static void lvgl_tick_run(void *p)
{
    while (1)
    {
        lv_tick_inc(20);
        rt_thread_delay(20);
    }
}

static void lvgl_handle_thread(void *p)
{
    rt_tick_t t = RT_TICK_PER_SECOND / 60;
    rt_tick_t start, end;
    uint32_t fps = 0;

    while (1)
    {
        start = rt_tick_get();
        
        lv_task_handler();
        
        rt_thread_delay(t);
        
        end = rt_tick_get();
        
        fps = RT_TICK_PER_SECOND * 100 / (end - start);
        /* keep 30fps */
        if (fps > 3000)
            t++;
        else
            t--;
        if (t > RT_TICK_PER_SECOND) t = 0;
    }
}

#if USE_LV_LOG
void littlevgl2rtt_log_register(lv_log_level_t level, const char *file, uint32_t line, const char *dsc)
{
    if (level >= LV_LOG_LEVEL)
    {
        // Show the log level if you want
        if (level == LV_LOG_LEVEL_TRACE)
        {
            rt_kprintf("Trace:");
        }

        rt_kprintf("%s\n", dsc);
        // You can write 'file' and 'line' too similary if required.
    }
}
#endif

static int littlevgl2rtt_init(void)
{
    static lv_disp_buf_t disp_buf;
    static lv_disp_drv_t disp_drv;
    static lv_indev_drv_t indev_drv;

    /* LCD Device Init */
    lcd_device = rt_device_find("lcd_9341");
    RT_ASSERT(lcd_device != RT_NULL);
    if (rt_device_init(lcd_device) != RT_EOK)
    {
        return -1;
    }
    
    graphic_info = (struct rt_device_graphic_info *)lcd_device->user_data;

    if ((graphic_info->bits_per_pixel != LV_COLOR_DEPTH) && (graphic_info->bits_per_pixel != 32 && LV_COLOR_DEPTH != 24))
    {
        rt_kprintf("Error: framebuffer color depth mismatch! (Should be %d to match with LV_COLOR_DEPTH)",
                   graphic_info->bits_per_pixel);
        return RT_ERROR;
    }

    /*
    device = rt_device_find("touch");
    RT_ASSERT(device != RT_NULL);
    if (rt_device_init(device) != RT_EOK)
    {
        return -2;
    }
    */

    /* littlevgl Init */
    lv_init();

#if USE_LV_LOG
    /* littlevgl Log Init */
    lv_log_register_print(littlevgl2rtt_log_register);
#endif

    /* littlevGL Display device interface */
    lv_disp_buf_init(&disp_buf, graphic_info->framebuffer, NULL, LVGL_BUFFER_SIZE);
    lv_disp_drv_init(&disp_drv);

    disp_drv.flush_cb = disp_flush;
    disp_drv.buffer   = &disp_buf;

    //输入设备注册
    lv_disp_drv_register(&disp_drv);

    /*
    //输入设备注册
    lv_indev_drv_init(&indev_drv);

    indev_drv.type    = LV_INDEV_TYPE_POINTER;
    indev_drv.read_cb = input_read;

    lv_indev_drv_register(&indev_drv);
    */

    /* littlevGL Tick thread */
    rt_thread_t thread = RT_NULL;

    thread = rt_thread_create("lv_tick", lvgl_tick_run, RT_NULL, 1024, 6, 10);
    if (thread == RT_NULL)
    {
        return RT_ERROR;
    }
    rt_thread_startup(thread);

    thread = rt_thread_create("lvgl", lvgl_handle_thread, RT_NULL, 8192, 10, 100);
    if (thread == RT_NULL)
    {
        return RT_ERROR;
    }
    rt_thread_startup(thread);

    lv_tutorial_hello_world();

    return 0;
}
INIT_ENV_EXPORT(littlevgl2rtt_init);
