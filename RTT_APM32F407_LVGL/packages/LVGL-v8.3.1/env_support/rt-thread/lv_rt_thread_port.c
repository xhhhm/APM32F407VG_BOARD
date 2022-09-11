/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: MIT
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-10-18     Meco Man     the first version
 * 2022-05-10     Meco Man     improve rt-thread initialization process
 */

#ifdef __RTTHREAD__

#include <lvgl.h>
#include <rtthread.h>

#define DBG_TAG    "LVGL"
#define DBG_LVL    DBG_INFO
#include <rtdbg.h>

#ifndef PKG_LVGL_THREAD_STACK_SIZE
#define PKG_LVGL_THREAD_STACK_SIZE 4096
#endif /* PKG_LVGL_THREAD_STACK_SIZE */

#ifndef PKG_LVGL_THREAD_PRIO
#define PKG_LVGL_THREAD_PRIO (RT_THREAD_PRIORITY_MAX*2/3)
#endif /* PKG_LVGL_THREAD_PRIO */

//extern void lv_port_disp_init(void);
//extern void lv_port_indev_init(void);
extern void lv_user_gui_init(void);

static struct rt_thread lvgl_thread;
static rt_uint8_t lvgl_thread_stack[PKG_LVGL_THREAD_STACK_SIZE];

//#include "lv_demo_rtt_music_main.h"

#include "ft6336.h"
#include "lcd_init.h"
#include "lcd.h"
#include "lv_100ask_demo_course_2_2_5.h"

#define MY_DISP_HOR_RES 240
#define MY_DISP_VER_RES 320
#define LV_VER_RES_MAX 10

#define COLOR_SIZE         (240*320)


void LCD_Color_Fill(u16 sx, u16 sy, u16 ex, u16 ey, lv_color_t *color)
{
	u16 i,j;
	u32 k=0;
	uint32_t x=0,y=0; 
	u16 height, width;
	width = ex - sx + 1;            //得到填充的宽度
  height = ey - sy + 1;           //高度
	
	LCD_Address_Set(sx,sy,ex,ey);
	
	for(y = 0; y <width*height; y++) 
	{
		LCD_WR_DATA(color->full);
		color++;
  }
}

static void disp_flush(lv_disp_drv_t * disp_drv, const lv_area_t * area, lv_color_t * color_p)
{
    /*The most simple case (but also the slowest) to put all pixels to the screen one-by-one*/
LCD_Color_Fill(area->x1,area->y1,area->x2,area->y2,color_p);
//    int32_t x;
//    int32_t y;
//    for(y = area->y1; y <= area->y2; y++) {
//        for(x = area->x1; x <= area->x2; x++) {
//            /*Put a pixel to the display. For example:*/
////            put_px(x, y, *color_p)
//						LCD_Address_Set(x,y,x,y);//设置光标位置 
//						LCD_WR_DATA(color_p->full);
////						LCD_DrawPoint(x, y, color_p->full);
//            color_p++;
//        }
//    }

    /*IMPORTANT!!!
     *Inform the graphics library that you are ready with the flushing*/
    lv_disp_flush_ready(disp_drv);
}


void lv_port_disp_init(void)
{
//	CST816_Init();
//	CST816_Set_AutoRST(1);
	LCD_Init();//LCD初始化

	
	
//    static lv_disp_draw_buf_t draw_buf_dsc_1;
//    static lv_color_t buf_1[COLOR_SIZE];                          /*A buffer for 10 rows*/
//    lv_disp_draw_buf_init(&draw_buf_dsc_1, buf_1, NULL, COLOR_SIZE);   /*Initialize the display buffer*/
//	
		static lv_disp_draw_buf_t draw_buf_dsc_2;
    static lv_color_t buf_2_1[MY_DISP_HOR_RES * 10];                        /*A buffer for 10 rows*/
    static lv_color_t buf_2_2[MY_DISP_HOR_RES * 10];                        /*An other buffer for 10 rows*/
    lv_disp_draw_buf_init(&draw_buf_dsc_2, buf_2_1, buf_2_2, MY_DISP_HOR_RES * 10);   /*Initialize the display buffer*/

//    /* Example for 3) also set disp_drv.full_refresh = 1 below*/
//    static lv_disp_draw_buf_t draw_buf_dsc_3;
//    static lv_color_t buf_3_1[MY_DISP_HOR_RES * MY_DISP_VER_RES];            /*A screen sized buffer*/
//    static lv_color_t buf_3_2[MY_DISP_HOR_RES * MY_DISP_VER_RES];            /*Another screen sized buffer*/
//    lv_disp_draw_buf_init(&draw_buf_dsc_3, buf_3_1, buf_3_2, MY_DISP_VER_RES * LV_VER_RES_MAX);   /*Initialize the display buffer*/

    /*-----------------------------------
     * Register the display in LVGL
     *----------------------------------*/

    static lv_disp_drv_t disp_drv;                         /*Descriptor of a display driver*/
    lv_disp_drv_init(&disp_drv);                    /*Basic initialization*/

    /*Set up the functions to access to your display*/

    /*Set the resolution of the display*/
    disp_drv.hor_res = MY_DISP_HOR_RES;
    disp_drv.ver_res = MY_DISP_VER_RES;

    /*Used to copy the buffer's content to the display*/
    disp_drv.flush_cb = disp_flush;

    /*Set a display buffer*/
    disp_drv.draw_buf = &draw_buf_dsc_2;

    /*Required for Example 3)*/
    //disp_drv.full_refresh = 1

    /* Fill a memory array with a color if you have GPU.
     * Note that, in lv_conf.h you can enable GPUs that has built-in support in LVGL.
     * But if you have a different GPU you can use with this callback.*/
    //disp_drv.gpu_fill_cb = gpu_fill;

    /*Finally register the driver*/
    lv_disp_drv_register(&disp_drv);
	
}




static void touchpad_read(lv_indev_drv_t * indev_drv, lv_indev_data_t * data);
lv_indev_t * indev_touchpad;

void lv_port_indev_init(void)
{
    static lv_indev_drv_t indev_drv;
//		rt_kprintf("enter lv_port_indev_init\r\n");
    /*------------------
     * Touchpad
     * -----------------*/

    /*Initialize your touchpad if you have*/
//    touchpad_init();

    /*Register a touchpad input device*/
    lv_indev_drv_init(&indev_drv);
    indev_drv.type = LV_INDEV_TYPE_POINTER;
    indev_drv.read_cb = touchpad_read;
    indev_touchpad = lv_indev_drv_register(&indev_drv);
	
//		rt_kprintf("exit lv_port_indev_init \r\n");
}


/*Will be called by the library to read the touchpad*/
static void touchpad_read(lv_indev_drv_t * indev_drv, lv_indev_data_t * data)
{
    static lv_coord_t last_x = 0;
    static lv_coord_t last_y = 0;
	
//		rt_kprintf("enter touchpad_read");

		if(FT6336_TOUCH.Sta/*&TP_PRES_DOWN*/)//触摸按下了
		{
			last_x = FT6336_TOUCH.X_Pos;
			last_y = FT6336_TOUCH.Y_Pos;
			data->point.x = last_x;
			data->point.y = last_y;
			data->state = LV_INDEV_STATE_PR;
//			rt_kprintf("x:%d\r\ny:%d\r\n",FT6336_TOUCH.X_Pos,FT6336_TOUCH.Y_Pos);
		}else{
			data->point.x = last_x;
			data->point.y = last_y;
			data->state = LV_INDEV_STATE_REL;
		}
		
	
//    /*Save the pressed coordinates and the state*/
//    if(touchpad_is_pressed()) {
//        touchpad_get_xy(&last_x, &last_y);
//        data->state = LV_INDEV_STATE_PR;
//    } else {
//        data->state = LV_INDEV_STATE_REL;
//    }

//    /*Set the last pressed coordinates*/
//    data->point.x = last_x;
//    data->point.y = last_y;
}



//void read_touch(void *argv)
//{


//rt_kprintf("read touch data\r\n");
//}





#if LV_USE_LOG
static void lv_rt_log(const char *buf)
{
    LOG_I(buf);
}
#endif /* LV_USE_LOG */

static void lvgl_thread_entry(void *parameter)
{
	rt_uint32_t level;
	
#if LV_USE_LOG
    lv_log_register_print_cb(lv_rt_log);
#endif /* LV_USE_LOG */
    lv_init();
    lv_port_disp_init();
    lv_port_indev_init();
    lv_user_gui_init();
//		lv_100ask_demo_course_2_2_5();
    /* handle the tasks of LVGL */
    while(1)
    {
      get_touch_data();
			level = rt_hw_interrupt_disable();/* 关闭全局中断 */
			lv_task_handler();
			rt_hw_interrupt_enable(level);/* 恢复全局中断 */
      rt_thread_mdelay(LV_DISP_DEF_REFR_PERIOD);
    }
}

static int lvgl_thread_init(void)
{
    rt_err_t err;

    err = rt_thread_init(&lvgl_thread, "LVGL", lvgl_thread_entry, RT_NULL,
           &lvgl_thread_stack[0], sizeof(lvgl_thread_stack), PKG_LVGL_THREAD_PRIO, 0);
    if(err != RT_EOK)
    {
        LOG_E("Failed to create LVGL thread");
        return -1;
    }
    rt_thread_startup(&lvgl_thread);

    return 0;
}
//MSH_CMD_EXPORT(lvgl_thread_init,lvgl);
INIT_APP_EXPORT(lvgl_thread_init);

#endif /*__RTTHREAD__*/
