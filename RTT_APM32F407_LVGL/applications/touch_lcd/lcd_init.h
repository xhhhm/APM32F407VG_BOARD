#ifndef __LCD_INIT_H
#define __LCD_INIT_H

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>


#define _LCD_2_8_

#define USE_HORIZONTAL 0  //设置横屏或者竖屏显示 0或1为竖屏 2或3为横屏
#define Chip_Selection 1   //设置芯片初始化 0为ILI9341  1为ST7789


#if USE_HORIZONTAL==0||USE_HORIZONTAL==1
#define LCD_W 240
#define LCD_H 320

//#define LCD_W 240
//#define LCD_H 280

#else
#define LCD_W 320
#define LCD_H 240
#endif

#define LCD_DC_PIN    GET_PIN(E, 1)
#define LCD_CS_PIN    GET_PIN(E, 0)
#define LCD_SCL_PIN   GET_PIN(B, 9)
#define LCD_SDA_PIN   GET_PIN(B, 8)
#define LCD_BL_PIN   GET_PIN(D, 10)
#define LCD_RES_PIN   GET_PIN(D, 11)


//-----------------LCD端口定义---------------- 

#define LCD_SCLK_Clr() rt_pin_write(LCD_SCL_PIN, PIN_LOW)//SCL=SCLK
#define LCD_SCLK_Set() rt_pin_write(LCD_SCL_PIN, PIN_HIGH)

#define LCD_MOSI_Clr() rt_pin_write(LCD_SDA_PIN, PIN_LOW)//SDA=MOSI
#define LCD_MOSI_Set() rt_pin_write(LCD_SDA_PIN, PIN_HIGH)

#define LCD_RES_Clr()  rt_pin_write(LCD_RES_PIN, PIN_LOW)//RES
#define LCD_RES_Set()  rt_pin_write(LCD_RES_PIN, PIN_HIGH)

#define LCD_DC_Clr()   rt_pin_write(LCD_DC_PIN, PIN_LOW)//DC
#define LCD_DC_Set()   rt_pin_write(LCD_DC_PIN, PIN_HIGH)
 		     
#define LCD_CS_Clr()   rt_pin_write(LCD_CS_PIN, PIN_LOW)//CS
#define LCD_CS_Set()   rt_pin_write(LCD_CS_PIN, PIN_HIGH)

#define LCD_BLK_Clr()  rt_pin_write(LCD_BL_PIN, PIN_LOW)//BLK
#define LCD_BLK_Set()  rt_pin_write(LCD_BL_PIN, PIN_HIGH)




void LCD_GPIO_Init(void);//初始化GPIO
void LCD_Writ_Bus(u8 dat);//模拟SPI时序
void LCD_WR_DATA8(u8 dat);//写入一个字节
void LCD_WR_DATA(u16 dat);//写入两个字节
void LCD_WR_REG(u8 dat);//写入一个指令
void LCD_Address_Set(u16 x1,u16 y1,u16 x2,u16 y2);//设置坐标函数
void LCD_Init(void);//LCD初始化
#endif




