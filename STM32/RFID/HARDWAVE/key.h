#ifndef _KEY_H
#define _KEY_H

#include "sys.h"

//
#define key1 GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_6)
#define key2 GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_7)
#define key3 GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_8)
#define key4 GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_11)
#define key5 GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_12)


#define keyHome 	1	//主菜单键
#define keyInc	  2	//增量键  increment 增量
#define keyDec    3	//减量键  decrement 减量
#define keyMode   4	//减量键  decrement 减量
#define keyEnter  5	//确认键


void key_init();
u8 KEY_Scan(u8);  	//按键扫描函数	
void Key_Show(void);//键盘与显示菜单

#endif
