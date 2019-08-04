#include "stm32f1xx_hal.h"
#include "knob.h"
#include "lcd_zk.h"
char str3[5];
int temp1;
unsigned int tmp;		//ȫ�ֱ��������к�ǿ�ļ���ЧӦ��ע��ʹ��
unsigned char Aold,Bold;
unsigned char st;

int LimitH,LimitL,Step1;

void encoder_GPIO_Init(void)
{
	  GPIO_InitTypeDef GPIO_InitStruct;
	 __HAL_RCC_GPIOB_CLK_ENABLE();
  GPIO_InitStruct.Pin = GPIO_PIN_6|GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}
int encodingWitchPolling(void)
{
		if(A_ON&&B_ON)	  //�������Ŷ��ߵ�ƽ
				st=1;
		
		if(st)												//������ִ�������ɨ��
		{
			if(A_OFF&&B_OFF)		//��������Ŷ���͵�ƽ��
			{
				if(Bold)										//���B�Ÿ߾ͽ�TMP++
				{
					st=0;
					if(tmp==LimitH)
						tmp=LimitH;
					else
						tmp+=Step1;
				}
				if(Aold)										//���A�Ÿ߾ͽ�TMP--��
				{
					st=0;
				if(tmp==LimitL)
					tmp=LimitL;
				else
					tmp-=Step1;
				}
			}
		}
		Aold=HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_7);			//���¶�ȡA��B��������
		Bold=HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_6);
		return tmp;
}
void Knob_covered_Votage(void)			//���ּ���ʱ��ץȡ��������
{
	temp1=encodingWitchPolling();
	str3[0]=temp1/1000+'0';
	str3[1]=temp1%1000/100+'0';
	str3[2]=temp1%1000%100/10+'0';
	str3[3]=temp1%10+'0';
	str3[4]=' ';
	OLED_ShowChar(88,4,str3[3]);
}

	
