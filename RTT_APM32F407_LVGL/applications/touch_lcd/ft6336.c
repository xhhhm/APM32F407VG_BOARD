#include "ft6336.h"

#ifdef STM32F407_HAL

//void SDA_IN(void)
//{
//	#ifdef STM32F407_HAL
//	GPIO_InitTypeDef GPIO_Initure;
//	GPIO_Initure.Pin=FT6336_SDA;
//	GPIO_Initure.Mode=GPIO_MODE_INPUT;  
//	GPIO_Initure.Pull=GPIO_PULLUP;         
//	GPIO_Initure.Speed=GPIO_SPEED_FAST;     
//	HAL_GPIO_Init(FT6336_PORT,&GPIO_Initure);
//	#else
//	
//	#endif
//}

//void SDA_OUT(void)
//{
//	#ifdef STM32F407_HAL
//	
//	GPIO_InitTypeDef GPIO_Initure;
//	GPIO_Initure.Pin=FT6336_SDA;
//	GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;  
//	GPIO_Initure.Pull=GPIO_PULLUP;         
//	GPIO_Initure.Speed=GPIO_SPEED_FAST;     
//	HAL_GPIO_Init(FT6336_PORT,&GPIO_Initure);
//	#else
//	
//	#endif
//}

#endif
FT6336_Info FT6336_TOUCH;

void tp_delay_us(unsigned int x)
{
		unsigned long i;
		while(--x!=0){
			i=4000;
			while(i--);
		}
}



void IIC_Init(void)
{
#ifdef STM32F407_HAL
	rt_pin_mode(FT6336_SCL_PIN, PIN_MODE_OUTPUT);
	rt_pin_mode(FT6336_SDA_PIN, PIN_MODE_OUTPUT);
//	GPIO_InitTypeDef GPIO_Initure;

//	__HAL_RCC_GPIOB_CLK_ENABLE();   


//	GPIO_Initure.Pin=FT6336_SDA|FT6336_SCL;
//	GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;  
//	GPIO_Initure.Pull=GPIO_PULLUP;         
//	GPIO_Initure.Speed=GPIO_SPEED_FAST;     
//	HAL_GPIO_Init(FT6336_PORT,&GPIO_Initure);

//	IIC_SDA(1);
//	IIC_SCL(1);  
#else
  GPIO_InitTypeDef  GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB | RCC_AHB1Periph_GPIOF, ENABLE);//使能GPIOB时钟

  //GPIOF9,F10初始化设置
  GPIO_InitStructure.GPIO_Pin = FT6336_SDA ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输出模式
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
	
  GPIO_Init(FT6336_SDA_PORT, &GPIO_InitStructure);//初始化
	GPIO_SetBits(FT6336_SDA_PORT,FT6336_SDA );//GPIOF9,F10设置高，灯灭
	
	GPIO_InitStructure.GPIO_Pin = FT6336_SCL ;
  GPIO_Init(FT6336_SCL_PORT, &GPIO_InitStructure);//初始化
	GPIO_SetBits(FT6336_SCL_PORT,FT6336_SCL );//GPIOF9,F10设置高，灯灭
#endif
}



void IIC_Start(void)
{
	FT6336_SDA_OUT();     
	IIC_SDA(1);	  	  
	IIC_SCL(1);
	tp_delay_us(4);
 	IIC_SDA(0);
	tp_delay_us(4);
	IIC_SCL(0);
}	  

void IIC_Stop(void)
{
	FT6336_SDA_OUT();
	IIC_SCL(0);
	IIC_SDA(0);
 	tp_delay_us(4);
	IIC_SCL(1); 
	tp_delay_us(4);			
	IIC_SDA(1);  	
}

unsigned char IIC_Wait_Ack(void)
{
	unsigned char ret_data=0;
	
	int ucErrTime=0;
	FT6336_SDA_IN();     
	IIC_SDA(1);tp_delay_us(1);	   
	IIC_SCL(1);tp_delay_us(1);	 
	while(READ_SDA)
	{
		ucErrTime++;
		if(ucErrTime>1000)
		{
			IIC_Stop();
			ret_data=1;
			return ret_data;
			
		}
	}

	IIC_SCL(0); 
	ret_data=0;
	
	return ret_data;  
} 

void IIC_Ack(void)
{
	IIC_SCL(0);
	FT6336_SDA_OUT();
	IIC_SDA(0);
	tp_delay_us(2);
	IIC_SCL(1);
	tp_delay_us(2);
	IIC_SCL(0);
}
	    
void IIC_NAck(void)
{
	IIC_SCL(0);
	FT6336_SDA_OUT();
	IIC_SDA(1);
	tp_delay_us(2);
	IIC_SCL(1);
	tp_delay_us(2);
	IIC_SCL(0);
}					 				     

void IIC_Send_Byte(unsigned char txd)
{                        
    unsigned char t;   
	FT6336_SDA_OUT(); 	    
    IIC_SCL(0);
    for(t=0;t<8;t++)
    {              
        IIC_SDA((txd&0x80)>>7);
        txd<<=1; 	  
		tp_delay_us(2);  
		IIC_SCL(1);
		tp_delay_us(2); 
		IIC_SCL(0);	
		tp_delay_us(2);
    }	 
} 	    

unsigned char IIC_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
	FT6336_SDA_IN();
    for(i=0;i<8;i++ )
	{
		IIC_SCL(0); 
		tp_delay_us(2);
		IIC_SCL(1);
		receive<<=1;
		if(READ_SDA)receive++;   
		tp_delay_us(1); 
  }					 
    if (!ack)
        IIC_NAck();
    else
        IIC_Ack();  
    return receive;
}

unsigned char ft6336_write_byte(unsigned char addr,unsigned char reg,unsigned char data)
{
    IIC_Start();
    IIC_Send_Byte((addr<<1)|0); 
    if(IIC_Wait_Ack())          
    {
        IIC_Stop();
        return 1;
    }
    IIC_Send_Byte(reg);         
    IIC_Wait_Ack();             
    IIC_Send_Byte(data);        
    if(IIC_Wait_Ack())          
    {
        IIC_Stop();
        return 1;
    }
    IIC_Stop();
    return 0;
}

unsigned char ft6336_read_byte(unsigned char addr,unsigned char reg)
{
    unsigned char res=0;
    IIC_Start();
    IIC_Send_Byte((addr<<1)|0); 
      if(IIC_Wait_Ack())          
    {
        IIC_Stop();
        return 1;
    }           
    IIC_Send_Byte(reg);         
      if(IIC_Wait_Ack())          
    {
        IIC_Stop();
        return 1;
    }           
	  IIC_Start();                
    IIC_Send_Byte((addr<<1)|1); 
      if(IIC_Wait_Ack())          
    {
        IIC_Stop();
        return 1;
    }            
    res=IIC_Read_Byte(0);		
    IIC_Stop();                 
    return res;  
}

unsigned char ft6336_get_td_status(void)
{
		unsigned char a;
		a=ft6336_read_byte(FT6336_ADDR,FT6336_ADDR_TD_STATUS);
		return a;
}

void ft6336_get_touch1_position(unsigned int *x,unsigned int *y)
{
		unsigned int xh=0,xl=0,yh=0,yl=0;
		xh=ft6336_read_byte(FT6336_ADDR,FT6336_ADDR_TOUCH1_XH);
		xl=ft6336_read_byte(FT6336_ADDR,FT6336_ADDR_TOUCH1_XL);
		yh=ft6336_read_byte(FT6336_ADDR,FT6336_ADDR_TOUCH1_YH);
		yl=ft6336_read_byte(FT6336_ADDR,FT6336_ADDR_TOUCH1_YL);
		*x=((xh&0x000F)<<8)|xl;
		*y=((yh&0x000F)<<8)|yl;
}

void ft6336_get_touch2_position(unsigned int *x,unsigned int *y)
{
		unsigned int xh=0,xl=0,yh=0,yl=0;
		xh=ft6336_read_byte(FT6336_ADDR,FT6336_ADDR_TOUCH2_XH);
		xl=ft6336_read_byte(FT6336_ADDR,FT6336_ADDR_TOUCH2_XL);
		yh=ft6336_read_byte(FT6336_ADDR,FT6336_ADDR_TOUCH2_YH);
		yl=ft6336_read_byte(FT6336_ADDR,FT6336_ADDR_TOUCH2_YL);
		*x=((xh&0x000F)<<8)|xl;
		*y=((yh&0x000F)<<8)|yl;
}



void get_touch_data(void)
{
	int count_touch=0;
	ft6336_get_touch1_position(&FT6336_TOUCH.X_Pos,&FT6336_TOUCH.Y_Pos);
	FT6336_TOUCH.Sta=ft6336_get_td_status();
	if(count_touch%50==0)
	{
//		rt_kprintf("x:%d  y:%d\r\n",FT6336_TOUCH.X_Pos,FT6336_TOUCH.Y_Pos);
	}
	count_touch++;
	
}

