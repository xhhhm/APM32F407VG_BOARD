//#include "main.h"
#include "CST816.h"
#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>
//#include "usermain.h"
#include "math.h"


CST816_Info	CST816_Instance;			//����CST816ʵ����

void delay_us (int time)
{
	for(int j=0;j<time;j++)
	{
		for(int i=0;i<168;i++);
	}
}

static void delay_ms(int time)
{
	rt_thread_mdelay(time);
}

/*
void CST816_SDA_IN(void) 
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Pin = TP_SDA_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	HAL_GPIO_Init(TP_SDA_GPIO_Port, &GPIO_InitStruct);
}
void CST816_SDA_OUT(void)	
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Pin = TP_SDA_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	HAL_GPIO_Init(TP_SDA_GPIO_Port, &GPIO_InitStruct);
}
*/

//GPIO_InitTypeDef GPIO_InitStruct = {0};
void CST816_IIC_Start(void)
{
//	GPIO_InitTypeDef GPIO_InitStruct = {0};
	
  CST816_SDA_OUT();
  CST816_SDA_Set();
  CST816_SCL_Set();
  delay_us(4);	
  CST816_SDA_Clr();
  delay_us(4); 
  CST816_SCL_Clr();
}


void CST816_IIC_Stop(void)
{
//	GPIO_InitTypeDef GPIO_InitStruct = {0};
	CST816_SDA_OUT();
	
	CST816_SCL_Clr(); 
	CST816_SDA_Clr();  
	delay_us(4);	
	CST816_SCL_Set();
	CST816_SDA_Set();
	delay_us(4);
}

void CST816_IIC_ACK(void)
{
//	GPIO_InitTypeDef GPIO_InitStruct = {0};
  CST816_SDA_OUT();
	
  CST816_SCL_Clr();
//	delay_us(4);				//jia
  CST816_SDA_Clr();
  delay_us(2);     
  CST816_SCL_Set();
  delay_us(2);                  
  CST816_SCL_Clr();   
}
void CST816_IIC_NACK(void)
{
//	GPIO_InitTypeDef GPIO_InitStruct = {0};
  CST816_SDA_OUT();
  CST816_SCL_Clr();
	
  CST816_SDA_Set();
  delay_us(2);     
  CST816_SCL_Set();
  delay_us(2);                  
  CST816_SCL_Clr(); 
}

unsigned char CST816_IIC_Wait_ACK(void)
{
//	GPIO_InitTypeDef GPIO_InitStruct = {0};
  unsigned char t = 0;

	CST816_SDA_IN();
	CST816_SDA_Set();
	delay_us(1); 
	CST816_SCL_Set();
	delay_us(1); 
	while(CST816_SDA_Get())
	{
		t++;
		if(t>250)
		{
			CST816_IIC_Stop();
			return 1;
		}
	}
  CST816_SCL_Clr();              
  return 0;	
}



void CST816_IIC_SendByte(unsigned char byte)
{
//	GPIO_InitTypeDef GPIO_InitStruct = {0};
	unsigned char  BitCnt;
	CST816_SDA_OUT();
	CST816_SCL_Clr();
	for(BitCnt=0;BitCnt<8;BitCnt++)//Ҫ���͵����ݳ���Ϊ8λ
	{
//		delay_us(5);
		if(byte&0x80) CST816_SDA_Set();//�жϷ���λ
		else CST816_SDA_Clr(); 
		byte<<=1;
		delay_us(2); 
		CST816_SCL_Set();
		delay_us(2);
		CST816_SCL_Clr();
		delay_us(2);
	}
}
unsigned char CST816_IIC_RecvByte(void)
{
//	GPIO_InitTypeDef GPIO_InitStruct = {0};
  unsigned char retc;
  unsigned char BitCnt;
  retc=0; 
  CST816_SDA_IN();//��������Ϊ���뷽ʽ                
  for(BitCnt=0;BitCnt<8;BitCnt++)
  {        
		CST816_SCL_Clr();
		delay_us(2);
		CST816_SCL_Set();//��ʱ����Ϊ��ʹ��������������Ч                
		retc=retc<<1;
		if(CST816_SDA_Get()) retc++;//������λ,���յ�����λ����retc�� 
		delay_us(1);
  }
  return(retc);
}

void CST816_IIC_WriteREG(unsigned char reg,unsigned char date)
{
	CST816_IIC_Start();
	CST816_IIC_SendByte(0x2A);
	CST816_IIC_Wait_ACK();
	CST816_IIC_SendByte(reg);
	CST816_IIC_Wait_ACK();
	CST816_IIC_SendByte(date);
	CST816_IIC_Wait_ACK();
	CST816_IIC_Stop();
	delay_ms(10);
//	HAL_Delay(10);
}

unsigned char CST816_IIC_ReadREG(unsigned char reg)
{
	unsigned char date;
	CST816_IIC_Start();
	CST816_IIC_SendByte(0x2A);
	CST816_IIC_Wait_ACK();
	CST816_IIC_SendByte(reg);
	CST816_IIC_Wait_ACK();
	CST816_IIC_Start();
//	delay_us(4);
	CST816_IIC_SendByte(0x2B);
	CST816_IIC_Wait_ACK();
	date=CST816_IIC_RecvByte();
	CST816_IIC_ACK();
	CST816_IIC_Stop();
//	delay_us(5);
	return date;
}







void CST816_Init(void)
{
	
	rt_pin_mode(CST816_SCL_PIN, PIN_MODE_OUTPUT);
	rt_pin_mode(CST816_SDA_PIN, PIN_MODE_OUTPUT);
//  GPIO_InitTypeDef  GPIO_InitStructure;

//  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB | RCC_AHB1Periph_GPIOF, ENABLE);//ʹ��GPIOBʱ��

//  //GPIOF9,F10��ʼ������
//  GPIO_InitStructure.GPIO_Pin = CST816_SDA ;
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//��ͨ���ģʽ
//  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
//  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
//	
//  GPIO_Init(CST816_SDA_PORT, &GPIO_InitStructure);//��ʼ��
//	GPIO_SetBits(CST816_SDA_PORT,CST816_SDA );//GPIOF9,F10���øߣ�����
//	
//	GPIO_InitStructure.GPIO_Pin = CST816_SCL ;
//  GPIO_Init(CST816_SCL_PORT, &GPIO_InitStructure);//��ʼ��
//	GPIO_SetBits(CST816_SCL_PORT,CST816_SCL );//GPIOF9,F10���øߣ�����
}
unsigned char CST816_Get_ChipID()
{
	return CST816_IIC_ReadREG(ChipID);
}


void CST816_Get_XY()
{
	unsigned char temp[4];
	unsigned int x,y;
	
	CST816_IIC_Start();
	CST816_IIC_SendByte(0x2A);
	CST816_IIC_Wait_ACK();
	CST816_IIC_SendByte(0x03);
	CST816_IIC_Wait_ACK();
	CST816_IIC_Start();
//	delay_us(4);
	CST816_IIC_SendByte(0x2B);
	CST816_IIC_Wait_ACK();
	temp[0]=CST816_IIC_RecvByte();
	CST816_IIC_ACK();
	temp[1]=CST816_IIC_RecvByte();
	CST816_IIC_ACK();
	temp[2]=CST816_IIC_RecvByte();
	CST816_IIC_ACK();
	temp[3]=CST816_IIC_RecvByte();
	CST816_IIC_ACK();
	CST816_IIC_Stop();
	
	x=(unsigned int)((temp[0]&0x0F)<<8)|temp[1];//(temp[0]&0X0F)<<4|
	y=(unsigned int)((temp[2]&0x0F)<<8)|temp[3];//(temp[2]&0X0F)<<4|
	if(x<240&&y<280)
	{
		CST816_Instance.X_Pos	=	x;
		CST816_Instance.Y_Pos	=	y;
	}
}



unsigned char CST816_Get_Sta()
{
	unsigned char sta;
	
	CST816_IIC_Start();
	CST816_IIC_SendByte(0x2A);
	CST816_IIC_Wait_ACK();
	CST816_IIC_SendByte(0x01);
	CST816_IIC_Wait_ACK();
	CST816_IIC_Start();
//	delay_us(4);
	CST816_IIC_SendByte(0x2B);
	CST816_IIC_Wait_ACK();
	CST816_IIC_RecvByte();
	CST816_IIC_ACK();
	sta=CST816_IIC_RecvByte();
	CST816_IIC_ACK();
	CST816_IIC_Stop();
//	LCD_ShowIntNum(80,200,sta,5,BLACK,WHITE,16);
	if(sta!=255&sta!=0)return 1;
	else return 0;
//	return CST816_IIC_ReadREG(FingerNum);
}

void CST816_Set_MotionMask(unsigned char Motion)
{
	CST816_IIC_WriteREG(MotionMask,Motion);
}


void CST816_Set_IrqCtrl(unsigned char IRQCtrl)
{
	CST816_IIC_WriteREG(IrqCrl,IRQCtrl);
}


void CST816_Set_AutoSleep(unsigned char en)		//�Ƿ�ʹ���Զ�����͹���ģʽ		
{
	if(en==FALSE)
	{
		CST816_IIC_WriteREG(DisAutoSleep,FALSE);
	}
	else
	{
		CST816_IIC_WriteREG(DisAutoSleep,ENABLE);
		CST816_IIC_WriteREG(AutoSleepTime,en);
	}
}
void CST816_Set_AutoRST(unsigned char time)		//���ö೤ʱ���޴����Զ���λ��Ĭ��5s,д0����ù���
{
	CST816_IIC_WriteREG(AutoReset,time);
}
void CST816_Set_LongPressRST(unsigned char time)//���ó����೤ʱ�临λ��Ĭ��Ϊ10s��д0���ù���
{
	CST816_IIC_WriteREG(LongPressTime,time);
}

