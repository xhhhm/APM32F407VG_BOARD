#include "lcd_init.h"
static void delay_ms(int time)
{
	rt_thread_mdelay(time);
}

void LCD_GPIO_Init(void)
{
	
	
	rt_pin_mode(LCD_DC_PIN, PIN_MODE_OUTPUT);
	rt_pin_mode(LCD_CS_PIN, PIN_MODE_OUTPUT);
	rt_pin_mode(LCD_SCL_PIN, PIN_MODE_OUTPUT);
	rt_pin_mode(LCD_SDA_PIN, PIN_MODE_OUTPUT);
//  GPIO_InitTypeDef  GPIO_InitStructure;
//	
//	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA|RCC_AHB1Periph_GPIOB|RCC_AHB1Periph_GPIOC|RCC_AHB1Periph_GPIOD|RCC_AHB1Periph_GPIOE|RCC_AHB1Periph_GPIOG, ENABLE);//使能PORTA~E,PORTG时钟
// 
//  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输出模式
//  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
//  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
//  GPIO_Init(GPIOG, &GPIO_InitStructure);//初始化
//	GPIO_SetBits(GPIOG,GPIO_Pin_12);
//	
//  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_15 ;
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输出模式
//  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
//  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
//  GPIO_Init(GPIOD, &GPIO_InitStructure);//初始化
//	GPIO_SetBits(GPIOD,GPIO_Pin_1|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_15);
//	
//	
//  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_5|GPIO_Pin_7 ;
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输出模式
//  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
//  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
//  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化
//	GPIO_SetBits(GPIOA,GPIO_Pin_3|GPIO_Pin_5|GPIO_Pin_7);
//	
//	
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
//	GPIO_Init(GPIOC, &GPIO_InitStructure);//初始化
//	GPIO_SetBits(GPIOC,GPIO_Pin_5);

//  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_10;
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输出模式
//  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
//  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
//  GPIO_Init(GPIOE, &GPIO_InitStructure);//初始化
//	GPIO_SetBits(GPIOE,GPIO_Pin_8|GPIO_Pin_10);
}


/******************************************************************************
      函数说明：LCD串行数据写入函数
      入口数据：dat  要写入的串行数据
      返回值：  无
******************************************************************************/
void LCD_Writ_Bus(u8 dat) 
{	
	u8 i;
	LCD_CS_Clr();
	for(i=0;i<8;i++)
	{			  
		LCD_SCLK_Clr();
		if(dat&0x80)
		{
		   LCD_MOSI_Set();
		}
		else
		{
		   LCD_MOSI_Clr();
		}
		LCD_SCLK_Set();
		dat<<=1;
	}	
  LCD_CS_Set();	
}


/******************************************************************************
      函数说明：LCD写入数据
      入口数据：dat 写入的数据
      返回值：  无
******************************************************************************/
void LCD_WR_DATA8(u8 dat)
{
	LCD_Writ_Bus(dat);
}


/******************************************************************************
      函数说明：LCD写入数据
      入口数据：dat 写入的数据
      返回值：  无
******************************************************************************/
void LCD_WR_DATA(u16 dat)
{
	LCD_Writ_Bus(dat>>8);
	LCD_Writ_Bus(dat);
}


/******************************************************************************
      函数说明：LCD写入命令
      入口数据：dat 写入的命令
      返回值：  无
******************************************************************************/
void LCD_WR_REG(u8 dat)
{
	LCD_DC_Clr();//写命令
	LCD_Writ_Bus(dat);
	LCD_DC_Set();//写数据
}


/******************************************************************************
      函数说明：设置起始和结束地址
      入口数据：x1,x2 设置列的起始和结束地址
                y1,y2 设置行的起始和结束地址
      返回值：  无
******************************************************************************/
void LCD_Address_Set(u16 x1,u16 y1,u16 x2,u16 y2)
{
#ifdef _LCD_2_8_
		LCD_WR_REG(0x2a);//列地址设置
		LCD_WR_DATA(x1);
		LCD_WR_DATA(x2);
		LCD_WR_REG(0x2b);//行地址设置
		LCD_WR_DATA(y1);
		LCD_WR_DATA(y2);
		LCD_WR_REG(0x2c);//储存器写
#else
if(USE_HORIZONTAL==0)
	{
		LCD_WR_REG(0x2a);//列地址设置
		LCD_WR_DATA(x1);
		LCD_WR_DATA(x2);
		LCD_WR_REG(0x2b);//行地址设置
		LCD_WR_DATA(y1+20);
		LCD_WR_DATA(y2+20);
		LCD_WR_REG(0x2c);//储存器写
	}
	else if(USE_HORIZONTAL==1)
	{
		LCD_WR_REG(0x2a);//列地址设置
		LCD_WR_DATA(x1);
		LCD_WR_DATA(x2);
		LCD_WR_REG(0x2b);//行地址设置
		LCD_WR_DATA(y1+20);
		LCD_WR_DATA(y2+20);
		LCD_WR_REG(0x2c);//储存器写
	}
	else if(USE_HORIZONTAL==2)
	{
		LCD_WR_REG(0x2a);//列地址设置
		LCD_WR_DATA(x1+20);
		LCD_WR_DATA(x2+20);
		LCD_WR_REG(0x2b);//行地址设置
		LCD_WR_DATA(y1);
		LCD_WR_DATA(y2);
		LCD_WR_REG(0x2c);//储存器写
	}
	else
	{
		LCD_WR_REG(0x2a);//列地址设置
		LCD_WR_DATA(x1+20);
		LCD_WR_DATA(x2+20);
		LCD_WR_REG(0x2b);//行地址设置
		LCD_WR_DATA(y1);
		LCD_WR_DATA(y2);
		LCD_WR_REG(0x2c);//储存器写
	}
	
#endif

}

/******************************************************************************
      函数说明：LCD初始化函数
      入口数据：无
      返回值：  无
******************************************************************************/
void LCD_Init(void)
{
  if(Chip_Selection==0)  //初始化ILI9341
	{
	LCD_GPIO_Init();//初始化GPIO
	
	LCD_RES_Clr();//复位
	delay_ms(10);
	LCD_RES_Set();
	delay_ms(10);
	
	LCD_BLK_Set();//打开背光
  delay_ms(10);
	
	//************* Start Initial Sequence **********//
	LCD_WR_REG(0x11); //Sleep out 
	delay_ms(15);              //Delay 120ms 
	//************* Start Initial Sequence **********// 
	LCD_WR_REG(0xCF);
	LCD_WR_DATA8(0x00);
	LCD_WR_DATA8(0xC1);
	LCD_WR_DATA8(0X30);
	LCD_WR_REG(0xED);
	LCD_WR_DATA8(0x64);
	LCD_WR_DATA8(0x03);
	LCD_WR_DATA8(0X12);
	LCD_WR_DATA8(0X81);
	LCD_WR_REG(0xE8);
	LCD_WR_DATA8(0x85);
	LCD_WR_DATA8(0x00);
	LCD_WR_DATA8(0x79);
	LCD_WR_REG(0xCB);
	LCD_WR_DATA8(0x39);
	LCD_WR_DATA8(0x2C);
	LCD_WR_DATA8(0x00);
	LCD_WR_DATA8(0x34);
	LCD_WR_DATA8(0x02);
	LCD_WR_REG(0xF7);
	LCD_WR_DATA8(0x20);
	LCD_WR_REG(0xEA);
	LCD_WR_DATA8(0x00);
	LCD_WR_DATA8(0x00);
	LCD_WR_REG(0xC0); //Power control
	LCD_WR_DATA8(0x1D); //VRH[5:0]
	LCD_WR_REG(0xC1); //Power control
	LCD_WR_DATA8(0x12); //SAP[2:0];BT[3:0]
	LCD_WR_REG(0xC5); //VCM control
	LCD_WR_DATA8(0x33);
	LCD_WR_DATA8(0x3F);
	LCD_WR_REG(0xC7); //VCM control
	LCD_WR_DATA8(0x92);
	LCD_WR_REG(0x3A); // Memory Access Control
	LCD_WR_DATA8(0x55);
	LCD_WR_REG(0x36); // Memory Access Control
	if(USE_HORIZONTAL==0)LCD_WR_DATA8(0x08);
	else if(USE_HORIZONTAL==1)LCD_WR_DATA8(0xC8);
	else if(USE_HORIZONTAL==2)LCD_WR_DATA8(0x78);
	else LCD_WR_DATA8(0xA8);
	LCD_WR_REG(0xB1);
	LCD_WR_DATA8(0x00);
	LCD_WR_DATA8(0x12);
	LCD_WR_REG(0xB6); // Display Function Control
	LCD_WR_DATA8(0x0A);
	LCD_WR_DATA8(0xA2);

	LCD_WR_REG(0x44);
	LCD_WR_DATA8(0x02);

	LCD_WR_REG(0xF2); // 3Gamma Function Disable
	LCD_WR_DATA8(0x00);
	LCD_WR_REG(0x26); //Gamma curve selected
	LCD_WR_DATA8(0x01);
	LCD_WR_REG(0xE0); //Set Gamma
	LCD_WR_DATA8(0x0F);
	LCD_WR_DATA8(0x22);
	LCD_WR_DATA8(0x1C);
	LCD_WR_DATA8(0x1B);
	LCD_WR_DATA8(0x08);
	LCD_WR_DATA8(0x0F);
	LCD_WR_DATA8(0x48);
	LCD_WR_DATA8(0xB8);
	LCD_WR_DATA8(0x34);
	LCD_WR_DATA8(0x05);
	LCD_WR_DATA8(0x0C);
	LCD_WR_DATA8(0x09);
	LCD_WR_DATA8(0x0F);
	LCD_WR_DATA8(0x07);
	LCD_WR_DATA8(0x00);
	LCD_WR_REG(0XE1); //Set Gamma
	LCD_WR_DATA8(0x00);
	LCD_WR_DATA8(0x23);
	LCD_WR_DATA8(0x24);
	LCD_WR_DATA8(0x07);
	LCD_WR_DATA8(0x10);
	LCD_WR_DATA8(0x07);
	LCD_WR_DATA8(0x38);
	LCD_WR_DATA8(0x47);
	LCD_WR_DATA8(0x4B);
	LCD_WR_DATA8(0x0A);
	LCD_WR_DATA8(0x13);
	LCD_WR_DATA8(0x06);
	LCD_WR_DATA8(0x30);
	LCD_WR_DATA8(0x38);
	LCD_WR_DATA8(0x0F);
	LCD_WR_REG(0x29); //Display on
 }
	else          //初始化ST7789
	{
		LCD_GPIO_Init();//初始化GPIO
		LCD_RES_Clr();  //复位
		delay_ms(2);
		LCD_RES_Set();
		delay_ms(2);
		LCD_BLK_Set();//打开背光
		delay_ms(5);
		LCD_WR_REG(0x11);
		delay_ms(2); //Delay 120ms
//************* Start Initial Sequence **********// 
//------------------------------display and color format setting--------------------------------//
	
		LCD_WR_REG(0X36);// Memory Access Control
		if(USE_HORIZONTAL==0)LCD_WR_DATA8(0x00);
		else if(USE_HORIZONTAL==1)LCD_WR_DATA8(0xC0);
		else if(USE_HORIZONTAL==2)LCD_WR_DATA8(0x70);
		else LCD_WR_DATA8(0xA0);
		LCD_WR_REG(0X3A);
		LCD_WR_DATA8(0X05);
	//--------------------------------ST7789S Frame rate setting-------------------------

		LCD_WR_REG(0xb2);
		LCD_WR_DATA8(0x0c);
		LCD_WR_DATA8(0x0c);
		LCD_WR_DATA8(0x00);
		LCD_WR_DATA8(0x33);
		LCD_WR_DATA8(0x33);
		LCD_WR_REG(0xb7);
		LCD_WR_DATA8(0x35);
		//---------------------------------ST7789S Power setting-----------------------------


#ifdef _LCD_2_8_

		LCD_WR_REG(0xbb);
		LCD_WR_DATA8(0x35);
		LCD_WR_REG(0xc0);
		LCD_WR_DATA8(0x2c);
		LCD_WR_REG(0xc2);
		LCD_WR_DATA8(0x01);
		LCD_WR_REG(0xc3);
		LCD_WR_DATA8(0x13);
		LCD_WR_REG(0xc4);
		LCD_WR_DATA8(0x20);
		LCD_WR_REG(0xc6);
		LCD_WR_DATA8(0x0f);
		LCD_WR_REG(0xca);
		LCD_WR_DATA8(0x0f);
		LCD_WR_REG(0xc8);
		LCD_WR_DATA8(0x08);
		LCD_WR_REG(0x55);
		LCD_WR_DATA8(0x90);
		LCD_WR_REG(0xd0);
		LCD_WR_DATA8(0xa4);
		LCD_WR_DATA8(0xa1);
		//--------------------------------ST7789S gamma setting------------------------------
		LCD_WR_REG(0xe0);
		LCD_WR_DATA8(0xd0);
		LCD_WR_DATA8(0x00);
		LCD_WR_DATA8(0x06);
		LCD_WR_DATA8(0x09);
		LCD_WR_DATA8(0x0b);
		LCD_WR_DATA8(0x2a);
		LCD_WR_DATA8(0x3c);
		LCD_WR_DATA8(0x55);
		LCD_WR_DATA8(0x4b);
		LCD_WR_DATA8(0x08);
		LCD_WR_DATA8(0x16);
		LCD_WR_DATA8(0x14);
		LCD_WR_DATA8(0x19);
		LCD_WR_DATA8(0x20);
		LCD_WR_REG(0xe1);
		LCD_WR_DATA8(0xd0);
		LCD_WR_DATA8(0x00);
		LCD_WR_DATA8(0x06);
		LCD_WR_DATA8(0x09);
		LCD_WR_DATA8(0x0b);
		LCD_WR_DATA8(0x29);
		LCD_WR_DATA8(0x36);
		LCD_WR_DATA8(0x54);
		LCD_WR_DATA8(0x4b);
		LCD_WR_DATA8(0x0d);
		LCD_WR_DATA8(0x16);
		LCD_WR_DATA8(0x14);
		LCD_WR_DATA8(0x21);
		LCD_WR_DATA8(0x20);
		LCD_WR_REG(0x29);

#else

	LCD_WR_REG(0xBB);			
	LCD_WR_DATA8(0x32); //Vcom=1.35V
					
	LCD_WR_REG(0xC2);
	LCD_WR_DATA8(0x01);

	LCD_WR_REG(0xC3);			
	LCD_WR_DATA8(0x15); //GVDD=4.8V  颜色深度
				
	LCD_WR_REG(0xC4);			
	LCD_WR_DATA8(0x20); //VDV, 0x20:0v

	LCD_WR_REG(0xC6);			
	LCD_WR_DATA8(0x0F); //0x0F:60Hz        	

	LCD_WR_REG(0xD0);			
	LCD_WR_DATA8(0xA4);
	LCD_WR_DATA8(0xA1); 

	LCD_WR_REG(0xE0);
	LCD_WR_DATA8(0xD0);   
	LCD_WR_DATA8(0x08);   
	LCD_WR_DATA8(0x0E);   
	LCD_WR_DATA8(0x09);   
	LCD_WR_DATA8(0x09);   
	LCD_WR_DATA8(0x05);   
	LCD_WR_DATA8(0x31);   
	LCD_WR_DATA8(0x33);   
	LCD_WR_DATA8(0x48);   
	LCD_WR_DATA8(0x17);   
	LCD_WR_DATA8(0x14);   
	LCD_WR_DATA8(0x15);   
	LCD_WR_DATA8(0x31);   
	LCD_WR_DATA8(0x34);   

	LCD_WR_REG(0xE1);     
	LCD_WR_DATA8(0xD0);   
	LCD_WR_DATA8(0x08);   
	LCD_WR_DATA8(0x0E);   
	LCD_WR_DATA8(0x09);   
	LCD_WR_DATA8(0x09);   
	LCD_WR_DATA8(0x15);   
	LCD_WR_DATA8(0x31);   
	LCD_WR_DATA8(0x33);   
	LCD_WR_DATA8(0x48);   
	LCD_WR_DATA8(0x17);   
	LCD_WR_DATA8(0x14);   
	LCD_WR_DATA8(0x15);   
	LCD_WR_DATA8(0x31);   
	LCD_WR_DATA8(0x34);
	LCD_WR_REG(0x21); 

	LCD_WR_REG(0x29);

#endif

}
}






