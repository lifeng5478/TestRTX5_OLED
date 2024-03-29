//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//中景园电子
//店铺地址：http://shop73023976.taobao.com/?spm=2013.1.0.0.M4PqC2
//
//  文 件 名   : main.c
//  版 本 号   : v2.0
//  作    者   : HuangKai
//  生成日期   : 2014-0101
//  最近修改   : 
//  功能描述   : OLED 4接口演示例程(51系列)
//              说明: 
//              ----------------------------------------------------------------
//              GND    电源地
//              VCC  接5V或3.3v电源
//              D0   接PA5（SCL）
//              D1   接PA7（SDA）
//              RES  接PB0
//              DC   接PB1
//              CS   接PA4               
//              ----------------------------------------------------------------
// 修改历史   :
// 日    期   : 
// 作    者   : HuangKai
// 修改内容   : 创建文件
//版权所有，盗版必究。
//Copyright(C) 中景园电子2014/3/16
//All rights reserved
//******************************************************************************/

#include "lcd_zk.h"
#include "stdlib.h"
#include "oledfont.h"  	 
//#include "delay.h"
//OLED的显存
//存放格式如下.
//[0]0 1 2 3 ... 127	
//[1]0 1 2 3 ... 127	
//[2]0 1 2 3 ... 127	
//[3]0 1 2 3 ... 127	
//[4]0 1 2 3 ... 127	
//[5]0 1 2 3 ... 127	
//[6]0 1 2 3 ... 127	
//[7]0 1 2 3 ... 127   

#if OLED_MODE==1
//向SSD1106写入一个字节。
//dat:要写入的数据/命令
//cmd:数据/命令标志 0,表示命令;1,表示数据;
void OLED_WR_Byte(uint8_t dat,uint8_t cmd)
{
	DATAOUT(dat);	    
	if(cmd)
	  OLED_DC_Set();
	else 
	  OLED_DC_Clr();		   
	OLED_CS_Clr();
	OLED_WR_Clr();	 
	OLED_WR_Set();
	OLED_CS_Set();	  
	OLED_DC_Set();	 
} 	    	    
#else
//向SSD1106写入一个字节。
//dat:要写入的数据/命令
//cmd:数据/命令标志 0,表示命令;1,表示数据;


static uint8_t s_ucGRAM[128][8];


uint8_t OLED_GetPixel(uint16_t _usX, uint16_t _usY)
{
	uint8_t ucValue;
	uint8_t ucPageAddr;
	uint8_t ucColAddr;

	ucPageAddr = _usY / 8;
	ucColAddr = _usX;

	ucValue = s_ucGRAM[ucPageAddr][ucColAddr];
	if (ucValue & (_usY % 8))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void OLED_draw_pixel(uint8_t x,uint8_t y,uint8_t show)
{
//    uint8_t pos = 0;
//    uint8_t bx = 0;
//    uint8_t temp = 0;

//    //设置坐标点
//    OLED_Set_Pos(x,y);
//    //p岸段是否超出范围
//    if (x > 127 || y > 63)
//    {
//        return;
//    }

//    pos =y / 8;
//    bx = y % 8;
//    temp = 1 << bx;
//    if (show)
//    {
//        s_ucGRAM[x][pos] |= temp;
//    }
//    else
//    {
//        s_ucGRAM[x][pos] &= ~temp;
//    }

    //设置显示位置—列高地址
 //   OLED_WR_Byte(s_ucGRAM[x][pos],OLED_DATA); 
 
 
 	uint8_t pos,bx,temp=0;
	if(x>131||y>63)return;//超出范围了.
	pos=y/8;
	bx=y%8;
	temp=1<<(bx);
	if(show)s_ucGRAM[x][pos]|=temp;
	else s_ucGRAM[x][pos]&=~temp;	    
 
}

#endif
	void OLED_Set_Pos(unsigned char x, unsigned char y) 
{ 
	OLED_WR_Byte(0xb0+(y/8),OLED_CMD);
  //OLED_WR_Byte(0xb0 + (7 - y / 8),OLED_CMD);
  OLED_WR_Byte(((x & 0xf0) >> 4) | 0x10,OLED_CMD);
  OLED_WR_Byte((x & 0x0f),OLED_CMD); 
}   	  
//开启OLED显示    
void OLED_Display_On(void)
{
	OLED_WR_Byte(0X8D,OLED_CMD);  //SET DCDC命令
	OLED_WR_Byte(0X14,OLED_CMD);  //DCDC ON
	OLED_WR_Byte(0XAF,OLED_CMD);  //DISPLAY ON
}
//关闭OLED显示     
void OLED_Display_Off(void)
{
	OLED_WR_Byte(0X8D,OLED_CMD);  //SET DCDC命令
	OLED_WR_Byte(0X10,OLED_CMD);  //DCDC OFF
	OLED_WR_Byte(0XAE,OLED_CMD);  //DISPLAY OFF
}		   			 
//清屏函数,清完屏,整个屏幕是黑色的!和没点亮一样!!!	  
void OLED_Clear(void)  
{  
//	uint8_t i,n;		    
//	for(i=0;i<8;i++)  
//	{  
//		OLED_WR_Byte (0xb0+i,OLED_CMD);    //设置页地址（0~7）
//		OLED_WR_Byte (0x00,OLED_CMD);      //设置显示位置—列低地址
//		OLED_WR_Byte (0x10,OLED_CMD);      //设置显示位置—列高地址   
//		for(n=0;n<128;n++)OLED_WR_Byte(0,OLED_DATA); 
//	} //更新显示
//	

//	uint8_t i,n;  
//	for(i=0;i<8;i++)for(n=0;n<128;n++)s_ucGRAM[n][i]=0X00;  
//	OLED_refresh_Gram();//更新显示
	OLED_Fill(0,0,127,64,0);
}


//在指定位置显示一个字符,包括部分字符
//x:0~127
//y:0~63
//mode:0,反白显示;1,正常显示				 
//size:选择字体 16/12 
void OLED_ShowChar(uint8_t x,uint8_t y,uint8_t chr)
{
	unsigned char c=0,i=0;	
		c=chr-' ';//得到偏移后的值			
		if(x>Max_Column-1){x=0;y=y+1;}
		if(SIZE ==16)
			{
			OLED_Set_Pos(x,y*16);	
			for(i=0;i<8;i++)
			OLED_WR_Byte(F8X16[c*16+i],OLED_DATA);
			OLED_Set_Pos(x,y*16+8);
			for(i=0;i<8;i++)
			OLED_WR_Byte(F8X16[c*16+i+8],OLED_DATA);
			}
			else {	
				OLED_Set_Pos(x,y*8+1);
				for(i=0;i<6;i++)
				OLED_WR_Byte(F6x8[c][i],OLED_DATA);
				
			}
}
//m^n函数
uint32_t oled_pow(uint8_t m,uint8_t n)
{
	uint32_t result=1;	 
	while(n--)result*=m;    
	return result;
}				  
//显示2个数字
//x,y :起点坐标	 
//len :数字的位数
//size:字体大小
//mode:模式	0,填充模式;1,叠加模式
//num:数值(0~4294967295);	 		  
void OLED_ShowNum(uint8_t x,uint8_t y,uint32_t num,uint8_t len,uint8_t size)
{         	
	uint8_t t,temp;
	uint8_t enshow=0;						   
	for(t=0;t<len;t++)
	{
		temp=(num/oled_pow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				OLED_ShowChar(x+(size/2)*t,y,' ');
				continue;
			}else enshow=1; 
		 	 
		}
	 	OLED_ShowChar(x+(size/2)*t,y,temp+'0'); 
	}
} 
//显示一个字符号串
void OLED_ShowString(uint8_t x,uint8_t y,uint8_t *chr)
{
	unsigned char j=0;
	while (chr[j]!='\0')
	{		OLED_ShowChar(x,y,chr[j]);
			x+=8;
		if(x>120){x=0;y+=1;}
			j++;
	}
}
//显示汉字
void OLED_ShowCHinese(uint8_t x,uint8_t y,uint8_t no)
{      			    
	uint8_t t,adder=0;
	OLED_Set_Pos(x,y);	
    for(t=0;t<16;t++)
		{
				OLED_WR_Byte(Hzk[2*no][t],OLED_DATA);
				adder+=1;
     }	
		OLED_Set_Pos(x,y+1);	
    for(t=0;t<16;t++)
			{	
				OLED_WR_Byte(Hzk[2*no+1][t],OLED_DATA);
				adder+=1;
      }					
}
/***********功能描述：显示显示BMP图片128×64起始点坐标(x,y),x的范围0～127，y为页的范围0～7*****************/
void OLED_DrawBMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP[])
{ 	
 unsigned int j=0;
 unsigned char x,y;
  
  if(y1%8==0) y=y1/8;      
  else y=y1/8+1;
	for(y=y0;y<y1;y++)
	{
		OLED_Set_Pos(x0,y);
    for(x=x0;x<x1;x++)
	    {      
	    	OLED_WR_Byte(BMP[j++],OLED_DATA);	    	
	    }
	}
}

void OLED_DrawPoint(uint8_t x,uint8_t y,uint8_t t)
{
	//OLED_Set_Pos(x,y);
//	OLED_WR_Byte(0xb0+y/8,OLED_CMD);
  OLED_WR_Byte(0xb0+(y/8),OLED_CMD);
  OLED_WR_Byte(((x & 0xf0) >> 4) | 0x10,OLED_CMD);
  OLED_WR_Byte((x & 0x0f),OLED_CMD); 
	OLED_WR_Byte(t,OLED_DATA);
}

void OLED_refresh_Gram(void)
{
//    uint8_t i = 0;
//    uint8_t n = 0;

//    for (i = 0;i < 8;i++)  
//    {  
//        //设置页地址（0~7）
//        OLED_WR_Byte(0xb0 + i,OLED_CMD);
//        //设置显示位置—列低地址
//        OLED_WR_Byte(0x02,OLED_CMD);
//        //设置显示位置—列高地址   
//        OLED_WR_Byte(0x10,OLED_CMD);

//        //更新数据
//        for (n = 0;n < 128;n++)
//        {
//            OLED_WR_Byte(s_ucGRAM[n][i],OLED_DATA); 
//        }
//    }
	uint8_t i,n;		    
	for(i=0;i<8;i++)  
	{  
		OLED_WR_Byte (0xb0+i,OLED_CMD);    //设置页地址（0~7）
		OLED_WR_Byte (0x00,OLED_CMD);      //设置显示位置—列低地址
		OLED_WR_Byte (0x10,OLED_CMD);      //设置显示位置—列高地址   
		for(n=0;n<128;n++)OLED_WR_Byte(s_ucGRAM[n][i],OLED_DATA); 
	}   
}

//x1,y1,x2,y2 填充区域的对角坐标
//确保x1<=x2;y1<=y2 0<=x1<=127 0<=y1<=63	 	 
//dot:0,清空;1,填充	  
void OLED_Fill(uint8_t x1,uint8_t y1,uint8_t x2,uint8_t y2,uint8_t dot)  
{  
	uint8_t x,y;  
	for(x=x1;x<=x2;x++)
	{
		for(y=y1;y<=y2;y++)OLED_draw_pixel(x,y,dot);
	}													    
	OLED_refresh_Gram();//更新显示
}

//初始化SSD1306					    
void OLED_Init(void)
{ 	
 
 	 
// 	GPIO_InitTypeDef  GPIO_InitStructure;
// 	
// 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	 //使能A端口时钟
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_7;	 
// 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//速度50MHz
// 	GPIO_Init(GPIOA, &GPIO_InitStructure);	  //初始化GPIOD3,6
// 	GPIO_SetBits(GPIOA,GPIO_Pin_5|GPIO_Pin_7|GPIO_Pin_4);	
//	
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 //使能A端口时钟
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_8;	 
// 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//速度50MHz
// 	GPIO_Init(GPIOB, &GPIO_InitStructure);	  //初始化GPIOD3,6
// 	GPIO_SetBits(GPIOB,GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_8);	
	 GPIO_InitTypeDef GPIO_InitStruct;

	/*开启GPIOC的外设时钟*/
  __HAL_RCC_GPIOD_CLK_ENABLE();
	/*选择要控制的GPIOC引脚 Configure GPIO pins : PB0 PB1 PB10 PB11 PB12 PB13 */													   
   GPIO_InitStruct.Pin = GPIO_PIN_9|GPIO_PIN_3|GPIO_PIN_5|GPIO_PIN_7;

 
	/*设置引脚模式为通用推挽输出*/
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
	/*设置引脚速率为50MHz */   
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;

	/*调用库函数，初始化GPIOB*/
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);  

	/* 关闭所有led灯	*/
  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_9|GPIO_PIN_3|GPIO_PIN_5|GPIO_PIN_7 
                          , GPIO_PIN_RESET);



 
  OLED_RST_Set();
	HAL_Delay(100);
	OLED_RST_Clr();
	HAL_Delay(200);
	OLED_RST_Set(); 
					  
	OLED_WR_Byte(0xAE,OLED_CMD);//--turn off oled panel
	OLED_WR_Byte(0x00,OLED_CMD);//---set low column address
	OLED_WR_Byte(0x10,OLED_CMD);//---set high column address
	OLED_WR_Byte(0x40,OLED_CMD);//--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
	OLED_WR_Byte(0x81,OLED_CMD);//--set contrast control register
	OLED_WR_Byte(0xCF,OLED_CMD); // Set SEG Output Current Brightness
	OLED_WR_Byte(0xA1,OLED_CMD);//--Set SEG/Column Mapping     0xa0左右反置 0xa1正常
	OLED_WR_Byte(0xC8,OLED_CMD);//Set COM/Row Scan Direction   0xc0上下反置 0xc8正常
	OLED_WR_Byte(0xA6,OLED_CMD);//--set normal display
	OLED_WR_Byte(0xA8,OLED_CMD);//--set multiplex ratio(1 to 64)
	OLED_WR_Byte(0x3f,OLED_CMD);//--1/64 duty
	OLED_WR_Byte(0xD3,OLED_CMD);//-set display offset	Shift Mapping RAM Counter (0x00~0x3F)
	OLED_WR_Byte(0x00,OLED_CMD);//-not offset
	OLED_WR_Byte(0xd5,OLED_CMD);//--set display clock divide ratio/oscillator frequency
	OLED_WR_Byte(0x80,OLED_CMD);//--set divide ratio, Set Clock as 100 Frames/Sec
	OLED_WR_Byte(0xD9,OLED_CMD);//--set pre-charge period
	OLED_WR_Byte(0xF1,OLED_CMD);//Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
	OLED_WR_Byte(0xDA,OLED_CMD);//--set com pins hardware configuration
	OLED_WR_Byte(0x12,OLED_CMD);
	OLED_WR_Byte(0xDB,OLED_CMD);//--set vcomh
	OLED_WR_Byte(0x40,OLED_CMD);//Set VCOM Deselect Level
	OLED_WR_Byte(0x20,OLED_CMD);//-Set Page Addressing Mode (0x00/0x01/0x02)
	OLED_WR_Byte(0x02,OLED_CMD);//
	OLED_WR_Byte(0x8D,OLED_CMD);//--set Charge Pump enable/disable
	OLED_WR_Byte(0x14,OLED_CMD);//--set(0x10) disable
	OLED_WR_Byte(0xA4,OLED_CMD);// Disable Entire Display On (0xa4/0xa5)
	OLED_WR_Byte(0xA6,OLED_CMD);// Disable Inverse Display On (0xa6/a7) 
	OLED_WR_Byte(0xAF,OLED_CMD);//--turn on oled panel
	OLED_WR_Byte(0xAF,OLED_CMD); /*display ON*/ 
	OLED_Clear();
	OLED_Set_Pos(0,0); 	
}  

#if spisoftflag ==1
void OLED_WR_Byte(uint8_t dat,uint8_t cmd)
{
	uint8_t i;
	if(cmd)
	  OLED_DC_Set();
	else
	  OLED_DC_Clr();
	OLED_CS_Clr();
	for(i=0;i<8;i++)
	{
		OLED_SCLK_Clr();
		if(dat&0x80)
		   OLED_SDIN_Set();
		else
		   OLED_SDIN_Clr();
		OLED_SCLK_Set();
		dat<<=1;
	}
	OLED_CS_Set();
	OLED_DC_Set();
}
#else
#include "spi.h"
/**
  * @brief 向LCD屏幕写一个字节的命令
  * @param 命令内容，具体命令可以参照手册
  * @retval None
  */
void OLED_WR_Byte(uint8_t temp,uint8_t cmd)
{
	if(cmd)
	  OLED_DC_Set();
	else
	  OLED_DC_Clr();
//	OLED_CS_Clr();
	//OLED_SCLK_Clr();
	HAL_SPI_Transmit(&hspi1,&temp, 1, 0xffff);
//	OLED_CS_Set();
//	OLED_SCLK_Set();
}


/**
  * @brief 向LCD屏幕写两个字节的数据
  * @param 16位的数据
	* @note  此函数可以直接调用LCD_WriteData两次，但是IO的操作是多余的
  *        由于每个图片的数据都是16位的，所以此函数很常用，因此稍作优化，减少操作IO
  * @retval None
  */
static void LCD_WD_U16(uint16_t temp)
{
	uint8_t tempBuf[2];
	tempBuf[0] = temp>>8;
	tempBuf[1] = temp;
	OLED_DC_Set();
	OLED_SCLK_Clr();
	HAL_SPI_Transmit(&hspi1,tempBuf, 2, 0xffff);
	OLED_SCLK_Set();
}

/**
  * @brief 向LCD屏幕写一个数组的长度
  * @param 数组地址与长度
	* @note  此函数可以直接调用LCD_WriteData若干次，但是IO的操作是多余的
  *        由于每个图片的数据都是16位的很长的数组，所以此函数很常用，因此稍作优化，减少操作IO，一个图片的数组值操作一次IO
  * @retval None
  */
static void LCD_WD_buf(uint8_t *pData, uint16_t Size)
{
	OLED_DC_Set();
	OLED_SCLK_Clr();
	HAL_SPI_Transmit(&hspi1,pData, Size, 0xffff);
	OLED_SCLK_Set();
}



#endif


























