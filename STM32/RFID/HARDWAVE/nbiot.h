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

void Clear_Buffer(void);//清空缓存	
void Init_Nbiot(void);//初始化Nbiot模块
void BC26_IOTSenddata(char* data);
void Send_Buff(char Send_data_buf[],char id[]);
unsigned char Query(char * src,char * des,unsigned int LEN);
bool Wait_Str_x_100ms(char* str1,char* str2,unsigned char time_x_100ms);
bool Wait_Str1_Str2_x_100ms(
															char uartx,								//串口号，值：1~5
															char* USARTx_RX_BUF,			//被检索的缓存首地址
															unsigned int LEN,					//被检索的缓存总长度
															bool* add_Flag_Usart_x_Receive,//串口接收到数据的标志变量的地址
															char and_or,							//值：1~2 （1：只检索是否包含其中一个字符串。 2：同时检索是否包含2个字符串）
															char str_NO,							//值：1~2 （在and_or取值1时，该取值才有效。1：检索第一个字符串。 2：检索第二个字符串）
															char* str1,								//第一个字符串的首地址
															char* str2,								//第二个字符串的首地址
															unsigned char Count_time_wait_ok_x_100ms//超时时间：x * 100ms
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