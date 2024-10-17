#ifndef __TIMER_H
#define __TIMER_H
#include "sys.h" 

extern unsigned char Count_timer;

extern unsigned char Count_time_wait_ok_x_100ms;
extern unsigned char Flag_timer_5S;
extern unsigned char Count_Timer3_value_USART1_receive_timeout;
extern unsigned char Count_Timer3_value_USART2_receive_timeout;
extern unsigned char Count_Timer3_value_USART3_receive_timeout;
extern unsigned char Count_Timer3_value_UART4_receive_timeout;
extern unsigned char Count_Timer3_value_UART5_receive_timeout;
extern unsigned char Flag_timer_2S;
extern unsigned char Flag_timer_1S;
extern unsigned char Flag_timer_10S;

void TIM3_Int_Init(u16 arr,u16 psc);
#endif
