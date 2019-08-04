#ifndef _KNOB_H
#define _KNOB_H

#define A_ON   HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_7) == 1
#define A_OFF  HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_7) == 0
#define B_ON   HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_6) == 1
#define B_OFF  HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_6) == 0

extern unsigned int tmp;
extern int temp1;
void encoder_GPIO_Init(void);
int encodingWitchPolling(void);
void Knob_covered_Votage(void);
#endif
