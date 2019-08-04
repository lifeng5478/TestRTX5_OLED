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
FlashRemember�ֲ���
	FlashRemember[0]��ң�������
										��Χ1-3����ѡ��3��ң�����������Զ���ȡң�������
	FlashRemember[1-3]��1��ң���� 1�Ź�����
	FlashRemember[4-6]��1��ң���� 2�Ź�����
	FlashRemember[7-9]��1��ң���� 3�Ź�����
	FlashRemember[10-12]��1��ң���� 4�Ź�����
	FlashRemember[13-15]��1��ң���� 5�Ź�����
	
	FlashRemember[16-18]��2��ң���� 1�Ź�����
	FlashRemember[19-21]��2��ң���� 2�Ź�����
	FlashRemember[22-24]��2��ң���� 3�Ź�����
	FlashRemember[25-27]��2��ң���� 4�Ź�����
	FlashRemember[28-30]��2��ң���� 5�Ź�����
	
	FlashRemember[31-33]��3��ң���� 1�Ź�����
	FlashRemember[34-36]��3��ң���� 2�Ź�����
	FlashRemember[37-39]��3��ң���� 3�Ź�����
	FlashRemember[40-42]��3��ң���� 4�Ź�����
	FlashRemember[43-45]��3��ң���� 5�Ź�����
*/

void Init_All_Perih(void)
{
	Key_Init();		//������ʼ��
	JDQ_Init();		//�̵�����ʼ��
	encoder_GPIO_Init();	//Knob��ʼ��
	OLED_Init();	//oled��ʼ��
}

void Init_Func(void)
{
	int x;
		OLED_Clear();	//����
//	OLED_ShowString(0,1,"����ѧϰϵͳ");
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
	i=FlashRemember[0]; //   ��Ҫ����
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
