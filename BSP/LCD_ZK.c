//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//�о�԰����
//���̵�ַ��http://shop73023976.taobao.com/?spm=2013.1.0.0.M4PqC2
//
//  �� �� ��   : main.c
//  �� �� ��   : v2.0
//  ��    ��   : HuangKai
//  ��������   : 2014-0101
//  ����޸�   : 
//  ��������   : OLED 4�ӿ���ʾ����(51ϵ��)
//              ˵��: 
//              ----------------------------------------------------------------
//              GND    ��Դ��
//              VCC  ��5V��3.3v��Դ
//              D0   ��PA5��SCL��
//              D1   ��PA7��SDA��
//              RES  ��PB0
//              DC   ��PB1
//              CS   ��PA4               
//              ----------------------------------------------------------------
// �޸���ʷ   :
// ��    ��   : 
// ��    ��   : HuangKai
// �޸�����   : �����ļ�
//��Ȩ���У�����ؾ���
//Copyright(C) �о�԰����2014/3/16
//All rights reserved
//******************************************************************************/

#include "lcd_zk.h"
#include "stdlib.h"
#include "oledfont.h"  	 
//#include "delay.h"
//OLED���Դ�
//��Ÿ�ʽ����.
//[0]0 1 2 3 ... 127	
//[1]0 1 2 3 ... 127	
//[2]0 1 2 3 ... 127	
//[3]0 1 2 3 ... 127	
//[4]0 1 2 3 ... 127	
//[5]0 1 2 3 ... 127	
//[6]0 1 2 3 ... 127	
//[7]0 1 2 3 ... 127   

#if OLED_MODE==1
//��SSD1106д��һ���ֽڡ�
//dat:Ҫд�������/����
//cmd:����/�����־ 0,��ʾ����;1,��ʾ����;
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
//��SSD1106д��һ���ֽڡ�
//dat:Ҫд�������/����
//cmd:����/�����־ 0,��ʾ����;1,��ʾ����;


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

//    //���������
//    OLED_Set_Pos(x,y);
//    //p�����Ƿ񳬳���Χ
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

    //������ʾλ�á��иߵ�ַ
 //   OLED_WR_Byte(s_ucGRAM[x][pos],OLED_DATA); 
 
 
 	uint8_t pos,bx,temp=0;
	if(x>131||y>63)return;//������Χ��.
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
//����OLED��ʾ    
void OLED_Display_On(void)
{
	OLED_WR_Byte(0X8D,OLED_CMD);  //SET DCDC����
	OLED_WR_Byte(0X14,OLED_CMD);  //DCDC ON
	OLED_WR_Byte(0XAF,OLED_CMD);  //DISPLAY ON
}
//�ر�OLED��ʾ     
void OLED_Display_Off(void)
{
	OLED_WR_Byte(0X8D,OLED_CMD);  //SET DCDC����
	OLED_WR_Byte(0X10,OLED_CMD);  //DCDC OFF
	OLED_WR_Byte(0XAE,OLED_CMD);  //DISPLAY OFF
}		   			 
//��������,������,������Ļ�Ǻ�ɫ��!��û����һ��!!!	  
void OLED_Clear(void)  
{  
//	uint8_t i,n;		    
//	for(i=0;i<8;i++)  
//	{  
//		OLED_WR_Byte (0xb0+i,OLED_CMD);    //����ҳ��ַ��0~7��
//		OLED_WR_Byte (0x00,OLED_CMD);      //������ʾλ�á��е͵�ַ
//		OLED_WR_Byte (0x10,OLED_CMD);      //������ʾλ�á��иߵ�ַ   
//		for(n=0;n<128;n++)OLED_WR_Byte(0,OLED_DATA); 
//	} //������ʾ
//	

	uint8_t i,n;  
	for(i=0;i<8;i++)for(n=0;n<128;n++)s_ucGRAM[n][i]=0X00;  
	OLED_refresh_Gram();//������ʾ

}


//��ָ��λ����ʾһ���ַ�,���������ַ�
//x:0~127
//y:0~63
//mode:0,������ʾ;1,������ʾ				 
//size:ѡ������ 16/12 
void OLED_ShowChar(uint8_t x,uint8_t y,uint8_t chr)
{
	unsigned char c=0,i=0;	
		c=chr-' ';//�õ�ƫ�ƺ��ֵ			
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
//m^n����
uint32_t oled_pow(uint8_t m,uint8_t n)
{
	uint32_t result=1;	 
	while(n--)result*=m;    
	return result;
}				  
//��ʾ2������
//x,y :�������	 
//len :���ֵ�λ��
//size:�����С
//mode:ģʽ	0,���ģʽ;1,����ģʽ
//num:��ֵ(0~4294967295);	 		  
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
//��ʾһ���ַ��Ŵ�
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
//��ʾ����
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
/***********������������ʾ��ʾBMPͼƬ128��64��ʼ������(x,y),x�ķ�Χ0��127��yΪҳ�ķ�Χ0��7*****************/
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
//        //����ҳ��ַ��0~7��
//        OLED_WR_Byte(0xb0 + i,OLED_CMD);
//        //������ʾλ�á��е͵�ַ
//        OLED_WR_Byte(0x02,OLED_CMD);
//        //������ʾλ�á��иߵ�ַ   
//        OLED_WR_Byte(0x10,OLED_CMD);

//        //��������
//        for (n = 0;n < 128;n++)
//        {
//            OLED_WR_Byte(s_ucGRAM[n][i],OLED_DATA); 
//        }
//    }
	uint8_t i,n;		    
	for(i=0;i<8;i++)  
	{  
		OLED_WR_Byte (0xb0+i,OLED_CMD);    //����ҳ��ַ��0~7��
		OLED_WR_Byte (0x00,OLED_CMD);      //������ʾλ�á��е͵�ַ
		OLED_WR_Byte (0x10,OLED_CMD);      //������ʾλ�á��иߵ�ַ   
		for(n=0;n<128;n++)OLED_WR_Byte(s_ucGRAM[n][i],OLED_DATA); 
	}   
}

//x1,y1,x2,y2 �������ĶԽ�����
//ȷ��x1<=x2;y1<=y2 0<=x1<=127 0<=y1<=63	 	 
//dot:0,���;1,���	  
void OLED_Fill(uint8_t x1,uint8_t y1,uint8_t x2,uint8_t y2,uint8_t dot)  
{  
	uint8_t x,y;  
	for(x=x1;x<=x2;x++)
	{
		for(y=y1;y<=y2;y++)OLED_draw_pixel(x,y,dot);
	}													    
	OLED_refresh_Gram();//������ʾ
}

//��ʼ��SSD1306					    
void OLED_Init(void)
{ 	
 
 	 
// 	GPIO_InitTypeDef  GPIO_InitStructure;
// 	
// 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	 //ʹ��A�˿�ʱ��
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_7;	 
// 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//�ٶ�50MHz
// 	GPIO_Init(GPIOA, &GPIO_InitStructure);	  //��ʼ��GPIOD3,6
// 	GPIO_SetBits(GPIOA,GPIO_Pin_5|GPIO_Pin_7|GPIO_Pin_4);	
//	
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 //ʹ��A�˿�ʱ��
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_8;	 
// 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//�ٶ�50MHz
// 	GPIO_Init(GPIOB, &GPIO_InitStructure);	  //��ʼ��GPIOD3,6
// 	GPIO_SetBits(GPIOB,GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_8);	
	 GPIO_InitTypeDef GPIO_InitStruct;

	/*����GPIOC������ʱ��*/
  __HAL_RCC_GPIOD_CLK_ENABLE();
	/*ѡ��Ҫ���Ƶ�GPIOC���� Configure GPIO pins : PB0 PB1 PB10 PB11 PB12 PB13 */													   
   GPIO_InitStruct.Pin = GPIO_PIN_9|GPIO_PIN_3|GPIO_PIN_5|GPIO_PIN_7;

 
	/*��������ģʽΪͨ���������*/
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
	/*������������Ϊ50MHz */   
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;

	/*���ÿ⺯������ʼ��GPIOB*/
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);  

	/* �ر�����led��	*/
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
	OLED_WR_Byte(0xA1,OLED_CMD);//--Set SEG/Column Mapping     0xa0���ҷ��� 0xa1����
	OLED_WR_Byte(0xC8,OLED_CMD);//Set COM/Row Scan Direction   0xc0���·��� 0xc8����
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
	OLED_SCLK_Clr();
	HAL_SPI_Transmit(&hspi1,&temp, 1, 0xffff);
	OLED_SCLK_Set();
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






















