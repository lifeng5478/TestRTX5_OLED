#include "key.h"
#include	"lcd_zk.h"
#include "flasheeprom.h"
#include "menu.h"
#define  GetKey1_H  HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_5)==1
#define  GetKey1_L  HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_5)==0
#define  GetKey2_H  HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_4)==1
#define  GetKey2_L  HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_4)==0
#define  GetKey3_H  HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_3)==1
#define  GetKey3_L  HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_3)==0

#define const_key_time1  30
#define const_key_time2  20
#define const_key_time3  20

extern uint8_t FlashRemember[46];
extern uint8_t UINum;
uint8_t ControlNum=0;
uint8_t ControlSelectNum=0;
uint8_t ControlLeaningNum=0;
uint8_t LearningFlag=0;

extern int LimitH;
extern int	LimitL;
extern int	Step1;
extern int temp1;
extern unsigned int tmp;	
extern char str3[5];

unsigned char ucKeySec=0;   //按键Sellect
unsigned char ucKey1Num=0;   //按键1次数
unsigned char ucKey2Num=0;//按键2次数
unsigned char ucKey3Num=0;//按键3次数
unsigned int  uiKeyTimeCnt1=0; 	//按键1去抖时间
unsigned char ucKeyLock1=0;   //按键1自锁防止持续触发

unsigned int  uiKeyTimeCnt2=0;  //按键2去抖时间
unsigned char ucKeyLock2=0; //按键2自锁防止持续触发

unsigned int  uiKeyTimeCnt3=0;  //按键3去抖时间
unsigned char ucKeyLock3=0; //按键3自锁防止持续触发

void (*Current_Menu_Func)();

typedef struct
{
	uint8_t current;
	uint8_t Key_UP;
	uint8_t Key_DOWN;
	uint8_t Key_ENTER;
	void (*current_fun_index)();
}Key_Table;

uint8_t workingFlag=0;
uint8_t MenuIndex;
const Key_Table table[30]=
{
	{0,0,0,1,(*RootMenu)},
	{1,2,2,4,(*Menu1_1)},
	{2,1,3,10,(*Menu1_2)},
	{3,0,0,1,(*Menu1_3)},
	{4,6,5,7,(*Menu2_1)},
	{5,4,6,8,(*Menu2_2)},
	{6,5,4,9,(*Menu2_3)},
	{7,7,7,7,(*CTSelFun1_1)},
	{8,8,8,7,(*CTSelFun1_2)},
	{9,0,0,7,(*CTSelFun1_3)},
	{10,12,11,13,(*Menu3_1)},
	{11,10,12,14,(*Menu3_2)},
	{12,11,10,15,(*Menu3_3)},
	{13,13,13,3,(*CTLeanFun1_1)},
	{14,14,14,3,(*CTLeanFun1_2)},
	{15,15,15,3,(*CTLeanFun1_3)},
	{16,16,16,1,(*WorkingFun1)},
	{17,17,17,1,(*WorkingFun2)},
	{18,18,18,1,(*WorkingFun3)},
};


extern void CheckControl(void);

void Key_Init(void)
{
	  GPIO_InitTypeDef GPIO_InitStruct;
	  __HAL_RCC_GPIOB_CLK_ENABLE();
	  /*Configure GPIO pins : PB3 PB4 PB5 PB6 
                           PB7 */
  GPIO_InitStruct.Pin = GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}

void key_scan(void)
{
	
  if(GetKey1_H)																
  {
        ucKeyLock1=0; 
        uiKeyTimeCnt1=0;
  }
  else if(ucKeyLock1==0)
  {
     uiKeyTimeCnt1++;
     if(uiKeyTimeCnt1>const_key_time1)
     {
        uiKeyTimeCnt1=0; 
        ucKeyLock1=1; 
        ucKeySec=1;
     }
  }

  if(GetKey2_H)																
  {
        ucKeyLock2=0; 
        uiKeyTimeCnt2=0;														
  }
  else if(ucKeyLock2==0)
  {
     uiKeyTimeCnt2++; 
     if(uiKeyTimeCnt2>const_key_time2)
     {
        uiKeyTimeCnt2=0;
        ucKeyLock2=1; 
        ucKeySec=2;
     }
  }
	
	  if(GetKey3_H)													
  {
     ucKeyLock3=0; 
     uiKeyTimeCnt3=0;													
  }
  else if(ucKeyLock3==0)
  {
     uiKeyTimeCnt3++;
     if(uiKeyTimeCnt3>const_key_time3)
     {
        uiKeyTimeCnt3=0; 
        ucKeyLock3=1; 
        ucKeySec=3;
     }
  }
}

void CheckMode(void)
{
	uint16_t i;
	i=FlashRemember[0];
  if (workingFlag==1)
	{
		switch (i)
		{
			case 1:
				HAL_Delay(500);
				workingFlag=0;
				MenuIndex=16;
				break;
			case 2:
				HAL_Delay(500);
				workingFlag=0;
				MenuIndex=17;
				break;
			case 3:
				HAL_Delay(500);
				workingFlag=0;
				MenuIndex=18;
				break;
		}
	}
	if(MenuIndex==16||MenuIndex==17||MenuIndex==18)
	{
		UINum=0;
	}
	else if(MenuIndex==13||MenuIndex==14||MenuIndex==15)
	{
	UINum=1;
	LimitH=9;
	LimitL=0;
	Step1=1;
	}

	if(MenuIndex!=13&&MenuIndex!=14&&MenuIndex!=15)
	{
		LearningFlag=0;
		temp1=0;
		tmp=0;	
		str3[3]=0;
	}
}

void MenuSevice(void)
{
	switch(ucKeySec)
	{
		case 1:
			ucKeySec=0;
			MenuIndex=table[MenuIndex].Key_UP;
			break;
		case 2:
			ucKeySec=0;
			MenuIndex=table[MenuIndex].Key_DOWN;
			break;
		case 3:
			ucKeySec=0;
			MenuIndex=table[MenuIndex].Key_ENTER;
			break;
	}
	Current_Menu_Func=table[MenuIndex].current_fun_index;	//读取入口函数指针地址
			(*Current_Menu_Func)();//执行当前操作函数
	CheckMode();
}
