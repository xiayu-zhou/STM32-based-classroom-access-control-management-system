#ifndef _KEY_H
#define _KEY_H

#include "sys.h"

//
#define key1 GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_6)
#define key2 GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_7)
#define key3 GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_8)
#define key4 GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_11)
#define key5 GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_12)


#define keyHome 	1	//���˵���
#define keyInc	  2	//������  increment ����
#define keyDec    3	//������  decrement ����
#define keyMode   4	//������  decrement ����
#define keyEnter  5	//ȷ�ϼ�


void key_init();
u8 KEY_Scan(u8);  	//����ɨ�躯��	
void Key_Show(void);//��������ʾ�˵�

#endif
