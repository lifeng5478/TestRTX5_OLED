#define _APPFUNCTION_H_
#ifdef _APPFUNCTION_H_


#include "knob.h"
#include "lcd_zk.h"
#include "key.h"
#include "JDQ.h"
#include "FlashEEPROM.h"
#include "usart.h"
extern uint8_t IRToSend[15];
extern uint8_t IRToSend1[5][3];
void Init_All_Perih(void);
void Init_Func(void);
void CheckControl(void);
void UIService(void);
void LearningSevice(void);
#endif
