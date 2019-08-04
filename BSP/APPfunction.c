#include "APPfunction.h"
#include "string.h"
#include "bmp.h"
uint8_t FlashToRemember[46]={0X11,0X22,0X33,0X04,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26
,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46};
uint8_t FlashRemember[46];

uint8_t IRToSend[15]={0};

uint8_t IRToSend1[5][3]={0};
extern char str3[5];
uint8_t UINum;
extern uint8_t TimeFlag;
extern uint8_t ControlNum;
extern uint8_t ControlSelectNum;
extern uint8_t ControlLeaningNum;
extern uint8_t LearningFlag;

extern uint8_t workingFlag;


/*
FlashRemember·Ö²¼£º
	FlashRemember[0]£ºÒ£¿ØÆ÷±àºÅ
										·¶Î§1-3£¬¿ÉÑ¡Ôñ3¸öÒ£¿ØÆ÷£¬¿ª»ú×Ô¶¯¶ÁÈ¡Ò£¿ØÆ÷±àºÅ
	FlashRemember[1-3]£º1ºÅÒ£¿ØÆ÷ 1ºÅ¹¦ÄÜÂë
	FlashRemember[4-6]£º1ºÅÒ£¿ØÆ÷ 2ºÅ¹¦ÄÜÂë
	FlashRemember[7-9]£º1ºÅÒ£¿ØÆ÷ 3ºÅ¹¦ÄÜÂë
	FlashRemember[10-12]£º1ºÅÒ£¿ØÆ÷ 4ºÅ¹¦ÄÜÂë
	FlashRemember[13-15]£º1ºÅÒ£¿ØÆ÷ 5ºÅ¹¦ÄÜÂë
	
	FlashRemember[16-18]£º2ºÅÒ£¿ØÆ÷ 1ºÅ¹¦ÄÜÂë
	FlashRemember[19-21]£º2ºÅÒ£¿ØÆ÷ 2ºÅ¹¦ÄÜÂë
	FlashRemember[22-24]£º2ºÅÒ£¿ØÆ÷ 3ºÅ¹¦ÄÜÂë
	FlashRemember[25-27]£º2ºÅÒ£¿ØÆ÷ 4ºÅ¹¦ÄÜÂë
	FlashRemember[28-30]£º2ºÅÒ£¿ØÆ÷ 5ºÅ¹¦ÄÜÂë
	
	FlashRemember[31-33]£º3ºÅÒ£¿ØÆ÷ 1ºÅ¹¦ÄÜÂë
	FlashRemember[34-36]£º3ºÅÒ£¿ØÆ÷ 2ºÅ¹¦ÄÜÂë
	FlashRemember[37-39]£º3ºÅÒ£¿ØÆ÷ 3ºÅ¹¦ÄÜÂë
	FlashRemember[40-42]£º3ºÅÒ£¿ØÆ÷ 4ºÅ¹¦ÄÜÂë
	FlashRemember[43-45]£º3ºÅÒ£¿ØÆ÷ 5ºÅ¹¦ÄÜÂë
*/

void Init_All_Perih(void)
{
	Key_Init();		//°´¼ü³õÊ¼»¯
	JDQ_Init();		//¼ÌµçÆ÷³õÊ¼»¯
	encoder_GPIO_Init();	//Knob³õÊ¼»¯
	OLED_Init();	//oled³õÊ¼»¯
}

void Init_Func(void)
{
	int x;
		OLED_Clear();	//ÇåÆÁ
//	OLED_ShowString(0,1,"ºìÍâÑ§Ï°ÏµÍ³");
//	OLED_ShowString(1,1,"DSI");
//	OLED_ShowString(2,1," LT_T Delta");
	OLED_ShowString(1,0,"RED IR Leaning");
	OLED_ShowString(1,2,"    DSI");
	OLED_ShowString(1,4," LT_T Delta");
	OLED_ShowString(1,6," 2018-7-02");
//	OLED_DrawBMP(0,0,128,8,BMP2);
	STMFLASH_Read(0, (uint16_t*)FlashRemember, sizeof(FlashRemember));
	//STMFLASH_Write(0, (uint16_t*)FlashToRemember, sizeof(FlashToRemember));
//	while(1)
//	{
////		x++;
////		if(x>=20)
////			x=0;
////		HAL_Delay(500);
////		OLED_ShowString(1,x,"2018-7-02");
//	}
	CheckControl(); 
//	UINum=0;
}

void CheckControl(void)
{
	uint16_t i;
	i=FlashRemember[0]; //   ÐèÒªµ÷Õû
	HAL_Delay(200);
	OLED_ShowString(1,0,"Ready TO Work");
	HAL_Delay(200);
	OLED_ShowString(1,2,"Init IR...   ");
	HAL_Delay(200);
	OLED_ShowString(1,4,"Init JDQ...  ");
	HAL_Delay(200);
	OLED_ShowString(1,6,"Init Done.   ");
	switch(i)
	{
		case 1:
		memcpy(IRToSend,(FlashRemember+1),15);
			break;
		case 2: 
		memcpy(IRToSend,(FlashRemember+16),15);
			break;
		case 3: 
		memcpy(IRToSend,(FlashRemember+31),15);
			break;
	}
		memcpy(IRToSend1[0],(IRToSend),3);
		memcpy(IRToSend1[1],(IRToSend+3),3);
		memcpy(IRToSend1[2],(IRToSend+6),3);
		memcpy(IRToSend1[3],(IRToSend+9),3);
		memcpy(IRToSend1[4],(IRToSend+12),3);
			HAL_Delay(500);
		workingFlag=1;
}

void UIService(void)
{
switch(UINum)
{
	case 0:
	JDQSevice();
		if(TimeFlag)
		{	
		TimeFlag=0;
		HAL_GPIO_TogglePin(GPIOC,GPIO_PIN_13);
		}
		break;
	case 1:
//		LearningSevice();
		break;
	case 2:
	break;
	default:
		break;
}
}
