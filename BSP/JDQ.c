#include "JDQ.h"
#include "lcd_zk.h"
#include "APPfunction.h"
#define  GetJDQ1_H  HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_0)==1
#define  GetJDQ1_L  HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_0)==0
#define  GetJDQ2_H  HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_1)==1
#define  GetJDQ2_L  HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_1)==0
#define  GetJDQ3_H  HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_2)==1
#define  GetJDQ3_L  HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_2)==0
#define  GetJDQ4_H  HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_3)==1
#define  GetJDQ4_L  HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_3)==0
#define  GetJDQ5_H  HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_4)==1
#define  GetJDQ5_L  HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_4)==0
#define  GetJDQ6_H  HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_5)==1
#define  GetJDQ6_L  HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_5)==0
#define  GetJDQ7_H  HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_6)==1
#define  GetJDQ7_L  HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_6)==0
#define  GetJDQ8_H  HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_7)==1
#define  GetJDQ8_L  HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_7)==0
#define  GetJDQ9_H  HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_8)==1
#define  GetJDQ9_L  HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_8)==0
#define  GetJDQ10_H  HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_11)==1
#define  GetJDQ10_L  HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_11)==0


#define const_JDQ_time  30

unsigned int StrC[15];
uint8_t IRAddr[2]={0xFA,0XF1};
unsigned char ucJDQSec=0;   //按键选择
unsigned int  uiJDQTimeCnt1=0; 	//按键1去抖时间
unsigned char ucJDQLock1=0;   //按键1自锁防止持续触发

unsigned int  uiJDQTimeCnt2=0;  //按键2去抖时间
unsigned char ucJDQLock2=0; //按键2自锁防止持续触发

unsigned int  uiJDQTimeCnt3=0;  //按键3去抖时间
unsigned char ucJDQLock3=0; //按键3自锁防止持续触发

unsigned int  uiJDQTimeCnt4=0; 	//按键1去抖时间
unsigned char ucJDQLock4=0;   //按键1自锁防止持续触发

unsigned int  uiJDQTimeCnt5=0;  //按键2去抖时间
unsigned char ucJDQLock5=0; //按键2自锁防止持续触发

unsigned int  uiJDQTimeCnt6=0;  //按键3去抖时间
unsigned char ucJDQLock6=0; //按键3自锁防止持续触发

unsigned int  uiJDQTimeCnt7=0; 	//按键1去抖时间
unsigned char ucJDQLock7=0;   //按键1自锁防止持续触发

unsigned int  uiJDQTimeCnt8=0;  //按键2去抖时间
unsigned char ucJDQLock8=0; //按键2自锁防止持续触发

unsigned int  uiJDQTimeCnt9=0;  //按键3去抖时间
unsigned char ucJDQLock9=0; //按键3自锁防止持续触发

unsigned int  uiJDQTimeCnt10=0;  //按键3去抖时间
unsigned char ucJDQLock10=0; //按键3自锁防止持续触发


void JDQ_Init(void)
{
	  GPIO_InitTypeDef GPIO_InitStruct;
	   __HAL_RCC_GPIOA_CLK_ENABLE();
  /*Configure GPIO pins : PA0 PA1 PA2 PA3 
                           PA4 PA5 PA6 PA7 
                           PA8 PA11 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3 
                          |GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7 
                          |GPIO_PIN_8|GPIO_PIN_11;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}

void JDQ_scan(void)
{
	
  if(GetJDQ1_H)																
  {
        ucJDQLock1=0; 
        uiJDQTimeCnt1=0;
  }
  else if(ucJDQLock1==0)
  {
     uiJDQTimeCnt1++;
     if(uiJDQTimeCnt1>const_JDQ_time)
     {
        uiJDQTimeCnt1=0; 
        ucJDQLock1=1; 
        ucJDQSec=1;
     }
  }

  if(GetJDQ2_H)																
  {
        ucJDQLock2=0; 
        uiJDQTimeCnt2=0;														
  }
  else if(ucJDQLock2==0)
  {
     uiJDQTimeCnt2++; 
     if(uiJDQTimeCnt2>const_JDQ_time)
     {
        uiJDQTimeCnt2=0;
        ucJDQLock2=1; 
        ucJDQSec=2;
     }
  }
	
	  if(GetJDQ3_H)													
  {
     ucJDQLock3=0; 
     uiJDQTimeCnt3=0;													
  }
  else if(ucJDQLock3==0)
  {
     uiJDQTimeCnt3++;
     if(uiJDQTimeCnt3>const_JDQ_time)
     {
        uiJDQTimeCnt3=0; 
        ucJDQLock3=1; 
        ucJDQSec=3;
     }
  }
	
		  if(GetJDQ4_H)													
  {
     ucJDQLock4=0; 
     uiJDQTimeCnt4=0;													
  }
  else if(ucJDQLock4==0)
  {
     uiJDQTimeCnt4++;
     if(uiJDQTimeCnt4>const_JDQ_time)
     {
        uiJDQTimeCnt4=0; 
        ucJDQLock4=1; 
        ucJDQSec=4;
     }
  }
	
		  if(GetJDQ5_H)													
  {
     ucJDQLock5=0; 
     uiJDQTimeCnt5=0;													
  }
  else if(ucJDQLock5==0)
  {
     uiJDQTimeCnt5++;
     if(uiJDQTimeCnt5>const_JDQ_time)
     {
        uiJDQTimeCnt5=0; 
        ucJDQLock5=1; 
        ucJDQSec=5;
     }
  }
	
		  if(GetJDQ6_H)													
  {
     ucJDQLock6=0; 
     uiJDQTimeCnt6=0;													
  }
  else if(ucJDQLock6==0)
  {
     uiJDQTimeCnt6++;
     if(uiJDQTimeCnt6>const_JDQ_time)
     {
        uiJDQTimeCnt6=0; 
        ucJDQLock6=1; 
        ucJDQSec=6;
     }
  }
	
		  if(GetJDQ7_H)													
  {
     ucJDQLock7=0; 
     uiJDQTimeCnt7=0;													
  }
  else if(ucJDQLock7==0)
  {
     uiJDQTimeCnt7++;
     if(uiJDQTimeCnt7>const_JDQ_time)
     {
        uiJDQTimeCnt7=0; 
        ucJDQLock7=1; 
        ucJDQSec=7;
     }
  }
	
		  if(GetJDQ8_H)													
  {
     ucJDQLock8=0; 
     uiJDQTimeCnt8=0;													
  }
  else if(ucJDQLock8==0)
  {
     uiJDQTimeCnt8++;
     if(uiJDQTimeCnt8>const_JDQ_time)
     {
        uiJDQTimeCnt8=0; 
        ucJDQLock8=1; 
        ucJDQSec=8;
     }
  }
	
		  if(GetJDQ9_H)
  {
     ucJDQLock9=0; 
     uiJDQTimeCnt9=0;													
  }
  else if(ucJDQLock9==0)
  {
     uiJDQTimeCnt9++;
     if(uiJDQTimeCnt9>const_JDQ_time)
     {
        uiJDQTimeCnt9=0; 
        ucJDQLock9=1; 
        ucJDQSec=9;
     }
  }
	
		  if(GetJDQ10_H)													
  {
     ucJDQLock10=0; 
     uiJDQTimeCnt10=0;													
  }
  else if(ucJDQLock10==0)
  {
     uiJDQTimeCnt10++;
     if(uiJDQTimeCnt10>const_JDQ_time)
     {
        uiJDQTimeCnt10=0; 
        ucJDQLock10=1; 
        ucJDQSec=10;
     }
  }

}

char str1[5]={0xFA,0xF1,0x00,0xF0,0x40};
void JDQSevice(void)
{
	 switch(ucJDQSec)
	 {
		 case 1:
			 	OLED_ShowString(8,55,"JDQ1 ");
				HAL_UART_Transmit(&huart1,IRAddr,2,0XFF);
		 HAL_UART_Transmit(&huart1,IRToSend1[0],3,0XFF);
		 ucJDQSec=0;
			 break;
	   case 2:
			 OLED_ShowString(8,55,"JDQ2 ");
//			 	OLED_ShowString(8,55,IRToSend1[1]);
		 				HAL_UART_Transmit(&huart1,IRAddr,2,0XFF);
		 HAL_UART_Transmit(&huart1,IRToSend1[1],3,0XFF);
		 ucJDQSec=0;
		   break;
		 case 3:
			 OLED_ShowString(8,55,"JDQ3 ");
//			 	OLED_ShowString(8,55,IRToSend1[2]);
		 				HAL_UART_Transmit(&huart1,IRAddr,2,0XFF);
		 HAL_UART_Transmit(&huart1,IRToSend1[2],3,0XFF);
		 ucJDQSec=0;
		   break;
		 case 4:
			 OLED_ShowString(8,55,"JDQ4 ");
//			 	OLED_ShowString(8,55,IRToSend1[3]);
		 				HAL_UART_Transmit(&huart1,IRAddr,2,0XFF);
		 HAL_UART_Transmit(&huart1,IRToSend1[3],3,0XFF);
		 ucJDQSec=0;	
		   break;
		 case 5:
			 OLED_ShowString(8,55,"JDQ5 ");
//			 	OLED_ShowString(8,55,IRToSend1[4]);
		 				HAL_UART_Transmit(&huart1,IRAddr,2,0XFF);
		 HAL_UART_Transmit(&huart1,IRToSend1[4],3,0XFF);
		 ucJDQSec=0;
		   break;
		 case 6:
			OLED_ShowString(8,55,"JDQ6 ");
		   break;
		 case 7:
			OLED_ShowString(8,55,"JDQ7 ");
		   break;
		 case 8:
			OLED_ShowString(8,55,"JDQ8 ");
		   break;
		 case 9:
			 OLED_ShowString(8,55,"JDQ9 ");
		   break;
		 case 10:
			OLED_ShowString(8,55,"JDQ10");
		   break;	 
		 default:
		 	 break;
	 }


}
