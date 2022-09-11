#ifndef __CST816_H
#define __CST816_H

//#include "main.h"
#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>

#define bitband_en 0				//是否使能位带操作				//还不能用

/****************************************IIC驱动部分*******************************/
	#define CST816_ADDR	0x15		//写地址0x2A		读地址0x2B
	#define write 0
	#define read 	1

//#define CST816_SCL_PORT	GPIOB
//#define CST816_SCL			GPIO_Pin_0
//#define CST816_SDA_PORT	GPIOF
//#define CST816_SDA			GPIO_Pin_11

#define CST816_SCL_PIN    GET_PIN(D, 13)
#define CST816_SDA_PIN    GET_PIN(D, 14)




#define CST816_SDA_IN() 	rt_pin_mode(CST816_SDA_PIN, PIN_MODE_INPUT) 	//PF11输入模式
#define CST816_SDA_OUT() 	rt_pin_mode(CST816_SDA_PIN, PIN_MODE_OUTPUT)  //PF11输出模式


#define CST816_SCL_Clr() 	rt_pin_write(CST816_SCL_PIN, PIN_LOW)//SCL=SCLK
#define CST816_SCL_Set() 	rt_pin_write(CST816_SCL_PIN, PIN_HIGH)

//#define CST816_SDA_IN() 	GPIO_InitStruct.Pin = TP_SDA_Pin;GPIO_InitStruct.Mode = GPIO_MODE_INPUT;GPIO_InitStruct.Pull = GPIO_PULLUP;GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;HAL_GPIO_Init(TP_SDA_GPIO_Port, &GPIO_InitStruct)
#define CST816_SDA_Get()	rt_pin_read(CST816_SDA_PIN)

//#define CST816_SDA_OUT()	GPIO_InitStruct.Pin = TP_SDA_Pin;GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;GPIO_InitStruct.Pull = GPIO_PULLUP;GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;HAL_GPIO_Init(TP_SDA_GPIO_Port, &GPIO_InitStruct)
#define CST816_SDA_Clr() 	rt_pin_write(CST816_SDA_PIN, PIN_LOW)
#define CST816_SDA_Set() 	rt_pin_write(CST816_SDA_PIN, PIN_HIGH)

#if bitband_en

	#define CST816_SCL_Clr() 	PCout(7)=0
	#define CST816_SCL_Set() 	PCout(7)=1

	#define CST816_SDA_IN() 	GPIO_InitStruct.Pin = TP_SDA_Pin;GPIO_InitStruct.Mode = GPIO_MODE_INPUT;GPIO_InitStruct.Pull = GPIO_PULLUP;GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;HAL_GPIO_Init(TP_SDA_GPIO_Port, &GPIO_InitStruct)
	#define CST816_SDA_Get()	PCin(8)
	
	#define CST816_SDA_OUT()	GPIO_InitStruct.Pin = TP_SDA_Pin;GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;GPIO_InitStruct.Pull = GPIO_PULLUP;GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;HAL_GPIO_Init(TP_SDA_GPIO_Port, &GPIO_InitStruct)
	#define CST816_SDA_Clr() 	PCout(8)=0
	#define CST816_SDA_Set() 	PCout(8)=1

#else

//	#define CST816_SCL_Clr() 	HAL_GPIO_WritePin(TP_SCL_GPIO_Port,TP_SCL_Pin, GPIO_PIN_RESET)//SCL=SCLK
//	#define CST816_SCL_Set() 	HAL_GPIO_WritePin(TP_SCL_GPIO_Port,TP_SCL_Pin, GPIO_PIN_SET)

//	#define CST816_SDA_IN() 	GPIO_InitStruct.Pin = TP_SDA_Pin;GPIO_InitStruct.Mode = GPIO_MODE_INPUT;GPIO_InitStruct.Pull = GPIO_PULLUP;GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;HAL_GPIO_Init(TP_SDA_GPIO_Port, &GPIO_InitStruct)
//	#define CST816_SDA_Get()	HAL_GPIO_ReadPin(TP_SDA_GPIO_Port,TP_SDA_Pin)

//	#define CST816_SDA_OUT()	GPIO_InitStruct.Pin = TP_SDA_Pin;GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;GPIO_InitStruct.Pull = GPIO_PULLUP;GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;HAL_GPIO_Init(TP_SDA_GPIO_Port, &GPIO_InitStruct)
//	#define CST816_SDA_Clr() 	HAL_GPIO_WritePin(TP_SDA_GPIO_Port,TP_SDA_Pin, GPIO_PIN_RESET)
//	#define CST816_SDA_Set() 	HAL_GPIO_WritePin(TP_SDA_GPIO_Port,TP_SDA_Pin, GPIO_PIN_SET)

#endif
void CST816_IIC_ACK(void);
void CST816_IIC_NACK(void);
unsigned char CST816_IIC_Wait_ACK(void);
void CST816_IIC_Start(void);
void CST816_IIC_Stop(void);
void CST816_IIC_SendByte(unsigned char byte);
void CST816_IIC_WriteREG(unsigned char reg,unsigned char date);
unsigned char CST816_IIC_ReadREG(unsigned char reg);
unsigned char CST816_IIC_RecvByte(void);

/*************************************寄存器操作部分********************************/
typedef struct
{
	unsigned char chipID;
	unsigned int X_Pos;			//X坐标
	unsigned int Y_Pos;			//Y坐标
	unsigned char Sta;			//记录触摸状态
	unsigned char Gesture;	//触发手势
	
}CST816_Info;

//
//CST816寄存器
#define GestureID			0x01		//手势寄存器
#define FingerNum			0x02		//手指数量
#define XposH					0x03		//x高四位
#define XposL					0x04		//x低八位
#define YposH					0x05		//y高四位
#define YposL					0x06		//y低八位
#define ChipID				0xA7		//芯片型号
#define	MotionMask		0xEC		//触发动作
#define AutoSleepTime	0xF9		//自动休眠
#define IrqCrl				0xFA		//中断控制
#define AutoReset			0xFB		//无手势休眠
#define LongPressTime	0xFC		//长按休眠
#define DisAutoSleep	0xFE		//使能低功耗模式

//

//MotionMask
#define EnConLR		1<<2		//连续左右滑动
#define EnConUD		1<<1		//连续上下滑动
#define EnDClick 	1				//双击

//IRQCtrl								//中断低电平
#define EnTest		1<<7	//中断测试
#define EnToucj		1<<6	//触摸触发中断
#define EnChange	1<<5	//触摸状态变化触发中断
#define EnMotion	1<<4	//检测到手势触发中断
#define OnceWLP		1			//检测到长按触发中断

//AutoSleep
#define ENABLE 1
#define FALSE  0

extern CST816_Info CST816_Instance;

void CST816_Init(void);
unsigned char CST816_Get_ChipID(void);
void CST816_Get_XY(void);								//得到当前触摸的坐标


unsigned char CST816_Get_Sta(void);			//更新触摸状态
void CST816_Set_MotionMask(unsigned char Motion);
void CST816_Set_IrqCtrl(unsigned char IRQCtrl);
void CST816_Set_AutoRST(unsigned char time);				//设置多长时间无触摸自动复位，默认5s,写0则禁用功能
void CST816_Set_LongPressRST(unsigned char time);		//设置长按多长时间复位，默认为10s，写0禁用功能
void CST816_Set_AutoSleep(unsigned char en);				//是否使能自动进入低功耗模式


#endif
