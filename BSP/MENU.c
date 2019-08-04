#include "lcd_zk.h"
#include "menu.h"
#include "FlashEEPROM.h"

extern uint8_t workingFlag;
extern uint8_t FlashRemember[46];
extern uint8_t LearningFlag;
void RootMenu(void)	//初始界面
{
	OLED_ShowString(1,0,"RED IR Leaning");
	OLED_ShowString(1,2,"    DSI");
	OLED_ShowString(1,4," LT_T Delta");
	OLED_ShowString(1,6," 2018-7-02");
}

void Menu1_1(void)	//界面1-1
{
OLED_ShowString(1,0,"  Setting：    ");
OLED_ShowString(1,2,">1:CT Select   ");
OLED_ShowString(1,4," 2:CT Leaning! ");
OLED_ShowString(1,6,"   Seting OK?  ");
}

void Menu1_2(void)	//界面1-2
{
OLED_ShowString(1,0,"  Setting：    ");
OLED_ShowString(1,2," 1:CT Select   ");
OLED_ShowString(1,4,">2:CT Leaning! ");
OLED_ShowString(1,6,"   Seting OK?  ");
}

void Menu1_3(void)	//界面1-3
{
OLED_ShowString(1,0,"  Keep Date   ");
OLED_ShowString(1,2," Now IS bakup ");
OLED_ShowString(1,4,"   Waiting    ");
OLED_ShowString(1,6,"   Lifeng     ");
STMFLASH_Write(0, (uint16_t*)FlashRemember, sizeof(FlashRemember));
	workingFlag=1;
}

void Menu2_1(void)	//界面2-1
{
OLED_ShowString(1,0," CT Sellect   ");
OLED_ShowString(1,2,">Controler1   ");
OLED_ShowString(1,4," Controler2   ");
OLED_ShowString(1,6," Controler3   ");
}
void Menu2_2(void) //界面2-2
{
OLED_ShowString(1,0," CT Sellect   ");
OLED_ShowString(1,2," Controler1   ");
OLED_ShowString(1,4,">Controler2   ");
OLED_ShowString(1,6," Controler3   ");
}
void Menu2_3(void) //界面2-3
{
OLED_ShowString(1,0," CT Sellect   ");
OLED_ShowString(1,2," Controler1   ");
OLED_ShowString(1,4," Controler2   ");
OLED_ShowString(1,6,">Controler3   ");
}

void CTSelFun1_1(void)
{
OLED_ShowString(1,0," CT Sellected ");
OLED_ShowString(1,2,"  Controler1  ");
OLED_ShowString(1,4," GoTo Working ");
OLED_ShowString(1,6," EditByLifeng ");
FlashRemember[0]=0x01;
STMFLASH_Write(0, (uint16_t*)FlashRemember, sizeof(FlashRemember));
	workingFlag=1;
}

void CTSelFun1_2(void)
{
OLED_ShowString(1,0," CT Sellected ");
OLED_ShowString(1,2,"  Controler2  ");
OLED_ShowString(1,4," GoTo Working ");
OLED_ShowString(1,6," EditByLifeng ");
FlashRemember[0]=0x02;
STMFLASH_Write(0, (uint16_t*)FlashRemember, sizeof(FlashRemember));
	workingFlag=1;
}

void CTSelFun1_3(void)
{
OLED_ShowString(1,0," CT Sellected ");
OLED_ShowString(1,2,"  Controler3  ");
OLED_ShowString(1,4," GoTo Working ");
OLED_ShowString(1,6," EditByLifeng ");
FlashRemember[0]=0x03;
STMFLASH_Write(0, (uint16_t*)FlashRemember, sizeof(FlashRemember));
	workingFlag=1;
}

void Menu3_1(void)
{
OLED_ShowString(1,0," CT Leaning:  ");
OLED_ShowString(1,2,">CT1 Leaning  ");
OLED_ShowString(1,4," CT2 Leaning  ");
OLED_ShowString(1,6," CT3 Leaning  ");
}

void Menu3_2(void)
{
OLED_ShowString(1,0," CT Leaning:");
OLED_ShowString(1,2," CT1 Leaning  ");
OLED_ShowString(1,4,">CT2 Leaning  ");
OLED_ShowString(1,6," CT3 Leaning  ");
}

void Menu3_3(void)
{
OLED_ShowString(1,0," CT Leaning:");
OLED_ShowString(1,2," CT1 Leaning  ");
OLED_ShowString(1,4," CT2 Leaning  ");
OLED_ShowString(1,6,">CT3 Leaning  ");
}
#include "knob.h"
#include "usart.h"
extern int temp1;
uint8_t IRReceive[10];
void CTLeanFun1_1(void)
{
	LearningFlag=1;
OLED_ShowString(1,0," CT Leaning! ");
OLED_ShowString(1,2,"Controler1   ");
OLED_ShowString(1,4," Leaning!:   ");
OLED_ShowString(1,6,"waiting IR...");
Knob_covered_Votage();
	if(temp1!=0)
			{
					HAL_UART_Receive_IT(&huart1,IRReceive,3);
			//	OLED_ShowString(6,45,IRReceive);
			}
}

void CTLeanFun1_2(void)
{
	LearningFlag=2;
OLED_ShowString(1,0," CT Leaning! ");
OLED_ShowString(1,2,"Controler2   ");
OLED_ShowString(1,4," Leaning!:   ");
OLED_ShowString(1,6,"waiting IR...");
Knob_covered_Votage();
	if(temp1!=0)
			{
					HAL_UART_Receive_IT(&huart1,IRReceive,3);
			//	OLED_ShowString(6,45,IRReceive);
			}
}

void CTLeanFun1_3(void)
{
	LearningFlag=3;
OLED_ShowString(1,0," CT Leaning! ");
OLED_ShowString(1,2,"Controler3   ");
OLED_ShowString(1,4," Leaning!:   ");
OLED_ShowString(1,6,"waiting IR...");
Knob_covered_Votage();
if(temp1!=0)
			{
					HAL_UART_Receive_IT(&huart1,IRReceive,3);
			//	OLED_ShowString(6,45,IRReceive);
			}
}

void WorkingFun1(void)
{
OLED_ShowString(1,0,"  Working Mode  ");
OLED_ShowString(1,2,"Now Cotroler 1  ");
OLED_ShowString(1,4,"  Waiting JDQ   ");
}

void WorkingFun2(void)
{
OLED_ShowString(1,0,"  Working Mode  ");
OLED_ShowString(1,2,"Now Cotroler 2  ");
OLED_ShowString(1,4,"  Waiting JDQ   ");
}

void WorkingFun3(void)
{
OLED_ShowString(1,0,"  Working Mode  ");
OLED_ShowString(1,2,"Now Cotroler 3  ");
OLED_ShowString(1,4,"  Waiting JDQ   ");
}
