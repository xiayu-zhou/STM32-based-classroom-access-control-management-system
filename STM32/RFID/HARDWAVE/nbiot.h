#ifndef __nbiot_H
#define __nbiot_H

#include "sys.h"
#include <string.h>
#include "stm32f10x.h"
#include "delay.h"
#include "gpio.h"
#include "delay.h"
#include "sys.h"
#include "lcd.h"
#include "spi.h"
#include "usart.h"
#include "timer.h"
#include "string.h"

void Clear_Buffer(void);//��ջ���	
void Init_Nbiot(void);//��ʼ��Nbiotģ��
void BC26_IOTSenddata(char* data);
void Send_Buff(char Send_data_buf[],char id[]);
unsigned char Query(char * src,char * des,unsigned int LEN);
bool Wait_Str_x_100ms(char* str1,char* str2,unsigned char time_x_100ms);
bool Wait_Str1_Str2_x_100ms(
															char uartx,								//���ںţ�ֵ��1~5
															char* USARTx_RX_BUF,			//�������Ļ����׵�ַ
															unsigned int LEN,					//�������Ļ����ܳ���
															bool* add_Flag_Usart_x_Receive,//���ڽ��յ����ݵı�־�����ĵ�ַ
															char and_or,							//ֵ��1~2 ��1��ֻ�����Ƿ��������һ���ַ����� 2��ͬʱ�����Ƿ����2���ַ�����
															char str_NO,							//ֵ��1~2 ����and_orȡֵ1ʱ����ȡֵ����Ч��1��������һ���ַ����� 2�������ڶ����ַ�����
															char* str1,								//��һ���ַ������׵�ַ
															char* str2,								//�ڶ����ַ������׵�ַ
															unsigned char Count_time_wait_ok_x_100ms//��ʱʱ�䣺x * 100ms
														);
bool Wait_OK_x_100ms(unsigned char time_x_100ms);


void Wait_OK(void);
void copy_str(char* des,char* src,unsigned char len);
//void DealUpData(char *from,uint8_t *to,uint16_t len);
void Array_CLR(char *src,char len) ;
void Send_flag(int n);

void DealUpData(char *from,u8 *to,u16 len,char *id);
void BC26_IOTSenddata(char* data);
void CLR(void);

#endif