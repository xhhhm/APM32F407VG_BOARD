#ifndef __CST816_H
#define __CST816_H

//#include "main.h"
#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>

#define bitband_en 0				//�Ƿ�ʹ��λ������				//��������

/****************************************IIC��������*******************************/
	#define CST816_ADDR	0x15		//д��ַ0x2A		����ַ0x2B
	#define write 0
	#define read 	1

//#define CST816_SCL_PORT	GPIOB
//#define CST816_SCL			GPIO_Pin_0
//#define CST816_SDA_PORT	GPIOF
//#define CST816_SDA			GPIO_Pin_11

#define CST816_SCL_PIN    GET_PIN(D, 13)
#define CST816_SDA_PIN    GET_PIN(D, 14)




#define CST816_SDA_IN() 	rt_pin_mode(CST816_SDA_PIN, PIN_MODE_INPUT) 	//PF11����ģʽ
#define CST816_SDA_OUT() 	rt_pin_mode(CST816_SDA_PIN, PIN_MODE_OUTPUT)  //PF11���ģʽ


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

/*************************************�Ĵ�����������********************************/
typedef struct
{
	unsigned char chipID;
	unsigned int X_Pos;			//X����
	unsigned int Y_Pos;			//Y����
	unsigned char Sta;			//��¼����״̬
	unsigned char Gesture;	//��������
	
}CST816_Info;

//
//CST816�Ĵ���
#define GestureID			0x01		//���ƼĴ���
#define FingerNum			0x02		//��ָ����
#define XposH					0x03		//x����λ
#define XposL					0x04		//x�Ͱ�λ
#define YposH					0x05		//y����λ
#define YposL					0x06		//y�Ͱ�λ
#define ChipID				0xA7		//оƬ�ͺ�
#define	MotionMask		0xEC		//��������
#define AutoSleepTime	0xF9		//�Զ�����
#define IrqCrl				0xFA		//�жϿ���
#define AutoReset			0xFB		//����������
#define LongPressTime	0xFC		//��������
#define DisAutoSleep	0xFE		//ʹ�ܵ͹���ģʽ

//

//MotionMask
#define EnConLR		1<<2		//�������һ���
#define EnConUD		1<<1		//�������»���
#define EnDClick 	1				//˫��

//IRQCtrl								//�жϵ͵�ƽ
#define EnTest		1<<7	//�жϲ���
#define EnToucj		1<<6	//���������ж�
#define EnChange	1<<5	//����״̬�仯�����ж�
#define EnMotion	1<<4	//��⵽���ƴ����ж�
#define OnceWLP		1			//��⵽���������ж�

//AutoSleep
#define ENABLE 1
#define FALSE  0

extern CST816_Info CST816_Instance;

void CST816_Init(void);
unsigned char CST816_Get_ChipID(void);
void CST816_Get_XY(void);								//�õ���ǰ����������


unsigned char CST816_Get_Sta(void);			//���´���״̬
void CST816_Set_MotionMask(unsigned char Motion);
void CST816_Set_IrqCtrl(unsigned char IRQCtrl);
void CST816_Set_AutoRST(unsigned char time);				//���ö೤ʱ���޴����Զ���λ��Ĭ��5s,д0����ù���
void CST816_Set_LongPressRST(unsigned char time);		//���ó����೤ʱ�临λ��Ĭ��Ϊ10s��д0���ù���
void CST816_Set_AutoSleep(unsigned char en);				//�Ƿ�ʹ���Զ�����͹���ģʽ


#endif
