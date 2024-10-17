#ifndef _PWM_H_
#define _PWM_H_
 #include "stm32f10x.h"
 
void PWM_Init(void);
void PWM_SetCompare1(uint16_t compare);
void PWM_SetCompare2(uint16_t compare);
 
#endif
