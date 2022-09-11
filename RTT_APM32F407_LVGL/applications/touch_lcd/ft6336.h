#ifndef _FT6336_H
#define _FT6336_H

#define STM32F407_HAL 


#ifdef STM32F407_HAL
//#include <stm32f4xx_hal.h>  //change the header file for your own STM32 devices

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>




//#define FT6336_PORT GPIOB
//#define FT6336_SDA GPIO_PIN_3
//#define FT6336_SCL GPIO_PIN_4  //change the GPIO port for your own IO connection

#define FT6336_SCL_PIN    GET_PIN(D, 13)
#define FT6336_SDA_PIN    GET_PIN(D, 14)


#define FT6336_SDA_IN() 	rt_pin_mode(FT6336_SDA_PIN, PIN_MODE_INPUT) 	//PF11输入模式
#define FT6336_SDA_OUT() 	rt_pin_mode(FT6336_SDA_PIN, PIN_MODE_OUTPUT)  //PF11输出模式

#define IIC_SCL(n)  (n?rt_pin_write(FT6336_SCL_PIN,PIN_HIGH):rt_pin_write(FT6336_SCL_PIN,PIN_LOW)) 
#define IIC_SDA(n)  (n?rt_pin_write(FT6336_SDA_PIN,PIN_HIGH):rt_pin_write(FT6336_SDA_PIN,PIN_LOW)) 
#define READ_SDA    rt_pin_read(FT6336_SDA_PIN)

#else
#include "sys.h"
#include "delay.h"
#define FT6336_SDA_PORT GPIOF
#define FT6336_SDA GPIO_Pin_11
#define FT6336_SCL_PORT GPIOB
#define FT6336_SCL GPIO_Pin_0  //change the GPIO port for your own IO connection

#define SDA_IN()  {GPIOF->MODER&=~(3<<(2*11));GPIOF->MODER|=0<<2*11;}	//PF11输入模式
#define SDA_OUT() {GPIOF->MODER&=~(3<<(2*11));GPIOF->MODER|=1<<2*11;} 	//PF11输出模式

#define IIC_SCL(n)  ((n)?(GPIO_SetBits(FT6336_SCL_PORT,FT6336_SCL)):(GPIO_ResetBits(FT6336_SCL_PORT,FT6336_SCL))) 
#define IIC_SDA(n)  ((n)?(GPIO_SetBits(FT6336_SDA_PORT,FT6336_SDA)):(GPIO_ResetBits(FT6336_SDA_PORT,FT6336_SDA))) 
#define READ_SDA    PFin(11)  

#endif


typedef struct
{
//	unsigned char chipID;
	unsigned int X_Pos;			//X坐标
	unsigned int Y_Pos;			//Y坐标
	unsigned char Sta;			//记录触摸状态
	unsigned char Gesture;	//触发手势
	
}FT6336_Info;


extern FT6336_Info FT6336_TOUCH;
#define FT6336_GEST_ID 						0X01


#define FT6336_ADDR               0x38

#define FT6336_ADDR_DEVICE_MODE   0x00
#define FT6336_ADDR_TD_STATUS     0x02

#define FT6336_ADDR_TOUCH1_EVENT  0x03
#define FT6336_ADDR_TOUCH1_ID     0x05
#define FT6336_ADDR_TOUCH1_XH     0x03
#define FT6336_ADDR_TOUCH1_XL     0x04
#define FT6336_ADDR_TOUCH1_YH     0x05
#define FT6336_ADDR_TOUCH1_YL     0x06

#define FT6336_ADDR_TOUCH2_EVENT  0x09
#define FT6336_ADDR_TOUCH2_ID     0x0B
#define FT6336_ADDR_TOUCH2_XH     0x09
#define FT6336_ADDR_TOUCH2_XL     0x0A
#define FT6336_ADDR_TOUCH2_YH     0x0B
#define FT6336_ADDR_TOUCH2_YL     0x0C

#define FT6336_ADDR_FIRMARE_ID    0xA6

void IIC_Init(void);
unsigned char ft6336_write_byte(unsigned char addr,unsigned char reg,unsigned char data);
unsigned char ft6336_read_byte(unsigned char addr,unsigned char reg);
unsigned char ft6336_get_td_status(void);
void ft6336_get_touch1_position(unsigned int *x,unsigned int *y);
void ft6336_get_touch2_position(unsigned int *x,unsigned int *y);
void get_touch_data(void);
#endif
