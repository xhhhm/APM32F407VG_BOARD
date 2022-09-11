/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-08-20     Abbcc        first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>

#include "CST816.h"

#include "lcd_init.h"
#include "lcd.h"
//#include "pic.h"
#include "ft6336.h"

#include "lvgl.h"

/* defined the LED2 pin: PE6 */
#define LED2_PIN    GET_PIN(E, 6)
#define LED1_PIN    GET_PIN(E, 5)
#define HX710_SCK		GET_PIN(C, 4)
#define HX710_DIO		GET_PIN(C, 5)
//#define CST816_INT_PIN    GET_PIN(A, 0)

rt_thread_t task1=RT_NULL;

void read_hx710b_data(void *par);

int main(void)
{
//    rt_base_t level0;
		uint32_t sysclock = 0;
    /* set LED2 pin mode to output */
    rt_pin_mode(LED2_PIN, PIN_MODE_OUTPUT);
		rt_pin_mode(LED1_PIN, PIN_MODE_OUTPUT);
//		rt_pin_mode(CST816_INT_PIN, PIN_MODE_INPUT_PULLUP);
//		rt_pin_attach_irq(CST816_INT_PIN, PIN_IRQ_MODE_FALLING, read_touch, RT_NULL);
//	
	
//		if!=RT_EOK)
//		{
//			rt_kprintf("CST816_INT_PIN IRQ ERR=%d\r\n",(int)(rt_pin_irq_enable(CST816_INT_PIN,PIN_IRQ_ENABLE)));
//		}
    /* Print system clock */
    sysclock = RCM_ReadSYSCLKFreq();
    rt_kprintf("System Clock: %d\n", sysclock);
//		level0=rt_hw_interrupt_disable();
		LCD_Init();//LCD≥ı ºªØ
		LCD_Fill(0,0,LCD_W,LCD_H,WHITE);
////		rt_hw_interrupt_enable(level0);
		IIC_Init();
//		CST816_Set_AutoRST(1);
	LCD_ShowString(25,0,"2.8 touch lcd",RED,WHITE,24,0);
	LCD_ShowString(0+10,40,"LCD_W:",RED,WHITE,16,0);
	LCD_ShowString(80+30,40,"LCD_H:",RED,WHITE,16,0);
	LCD_ShowString(0+10,60,"START:",RED,WHITE,16,0);
//	

//	task1=rt_thread_create("HX710",read_hx710b_data,RT_NULL,512,4,5);
//if(task1!=RT_NULL)
//{
//	rt_thread_startup(task1);
//}

//	if()
//	{
//		rt_kprintf("create hx710 err \r\n");
//	}


    while (1)
    {
//			get_touch_data();
//			
			
//			lv_task_handler();
			rt_thread_mdelay(1);
			lv_tick_inc(1);
//			if(FT6336_TOUCH.Sta)
//			{
//				if(rt_pin_read(LED2_PIN)==PIN_LOW)	
//				{
//					rt_pin_write(LED2_PIN,PIN_HIGH);
//				}
//				else
//				{
//					rt_pin_write(LED2_PIN,PIN_LOW);
//				}
////				rt_kprintf("x:%d\r\ny:%d\r\n",FT6336_TOUCH.X_Pos,FT6336_TOUCH.Y_Pos);
//			}
//			
//				if(rt_pin_read(LED1_PIN)==PIN_LOW)	
//				{
//					rt_pin_write(LED1_PIN,PIN_HIGH);
//				}
//				else
//				{
//					rt_pin_write(LED1_PIN,PIN_LOW);
//				}
//		LCD_ShowIntNum(48,40,FT6336_TOUCH.X_Pos,5,RED,WHITE,16);
//		
//		LCD_ShowIntNum(128+20,40,FT6336_TOUCH.Y_Pos,5,RED,WHITE,16);

//		LCD_ShowIntNum(48,60,FT6336_TOUCH.Sta,5,RED,WHITE,16);
    }
}


void read_hx710b_data(void *par)
{	
	rt_pin_mode(HX710_SCK,PIN_MODE_OUTPUT);
	rt_pin_mode(HX710_DIO,PIN_MODE_INPUT_PULLUP);
	
	
	u32 count=0;
	u8 i=0;
	
	rt_pin_write(HX710_SCK,PIN_LOW);
	
	while(1)
	{
		while(rt_pin_read(HX710_DIO))
		{
			rt_thread_mdelay(10);
		}
		for(i=0;i<24;i++)
		{
			rt_pin_write(HX710_SCK,PIN_HIGH);
			count=count<<1;
			rt_pin_write(HX710_SCK,PIN_LOW);
			if(rt_pin_read(HX710_DIO))count++;
		}
		rt_pin_write(HX710_SCK,PIN_HIGH);
		count=count^0x800000;
		rt_pin_write(HX710_SCK,PIN_LOW);
		
		LCD_ShowIntNum(58,40,count,6,RED,WHITE,16);
	}
}


