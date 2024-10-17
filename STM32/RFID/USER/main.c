#include "stm32f10x.h"
#include "delay.h"
#include "sys.h"
#include "lcd.h"
#include "spi.h"
#include "usart.h"
#include "timer.h"
#include "gpio.h"
#include "key.h"
#include "RC522.h"
#include <stdio.h>
#include "PWM.h"
#include <stdlib.h>
#include <string.h>

#define WIFI_ON				{GPIO_SetBits(GPIOB,GPIO_Pin_7);}
#define WIFI_OFF			{GPIO_ResetBits(GPIOB,GPIO_Pin_7);}

unsigned char data1[16] = {0x12,0x34,0x56,0x78,0xED,0xCB,0xA9,0x87,0x12,0x34,0x56,0x78,0x01,0xFE,0x01,0xFE};
unsigned char DefaultKey2[6] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}; 
unsigned char DefaultKey[6] = {0xD3, 0xF7, 0xD3, 0xF7, 0xD3, 0xF7}; 

static uint8_t LOCK_Flag = 0;

char TCP_SEND_DATA[100];

uint8_t Error = 0;

uint8_t E_num = 0;

uint8_t Start_Init = 0;//开始录卡

uint8_t Error_light_flag = 0;

uint8_t This_Class_Num[] = "M510";

uint8_t Passwd[16] = {0};

uint8_t NowRwrite = 0;

unsigned char status;

unsigned char k;

void wait_OK(void)
{
	while(!Flag_uart4_receive_OK);
	Flag_uart4_receive_OK = 0;
	CLR_Buf4();     
}

void WIFI_Init()
{
	delay_ms(1000);
	UART4TxStr("AT\r\n");
	wait_OK();
	USART1TxStr("AT\r\n");
	UART4TxStr("+++\r\n");
	delay_ms(1000);
	UART4TxStr("AT+CIPMODE=0\r\n");
	wait_OK();
	USART1TxStr("AT+CIPMODE=0\r\n");
	UART4TxStr("AT+RST\r\n");
	wait_OK();
	delay_ms(1000);
	USART1TxStr("AT+RST\r\n");
	UART4TxStr("AT+CWMODE=1\r\n");
	wait_OK();
	USART1TxStr("AT+CWMODE=1\r\n");
	UART4TxStr("AT+CWJAP=\"kiana\",\"12345678\"\r\n");
	wait_OK();
	USART1TxStr("AT+CWJAP=\"kiana\",\"12345678\"\r\n");

	UART4TxStr("AT+CIPMUX=0\r\n");
	wait_OK();
	USART1TxStr("AT+CIPMUX=0\r\n");

	UART4TxStr("AT+CIPSTART=\"TCP\",\"192.168.14.175\",7772\r\n");
	wait_OK();
	USART1TxStr("AT+CIPSTART=\"TCP\",\"192.168.14.175\",7772\r\n");

	UART4TxStr("AT+CIPMODE=1\r\n");
	wait_OK();
	USART1TxStr("AT+CIPMODE=1\r\n");

	UART4TxStr("AT+CIPSEND\r\n");
	wait_OK();
	USART1TxStr("AT+CIPSEND\r\n");

	USART1TxStr("finish\r\n");
}

void WIFI_GPIO()
{
	GPIO_InitTypeDef GPIO_InitStructure; 
	GPIO_StructInit(&GPIO_InitStructure);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);//使能PC端口时钟 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;       
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//普通推挽输出 
	GPIO_Init(GPIOB, &GPIO_InitStructure); //初始化PB.7，控制传感器开关
}

int main(void)
{
	uint8_t ucArray_ID [4] = {0,0,0,0};    
	uint8_t ucStatusReturn;     
	uint8_t dataBuffer[16]; 
	uint8_t blockAddress = 17; 
	char data[10];
	uint8_t i;
	GPIO_Configuration();			//GPIO初始化
	delay_init();	    	 							//延时函数初始化
	Lcd_Init();												//初始化LCD
	Usart1_Init(115200);						//串口1初始化
	Usart2_Init(115200);			  //连接NBIOT
	Uart4_Init(115200);
	Usart3_Init(9600);						//串口3初始化 
	//NVIC_Configuration(); 		//设置NVIC中断分组2:2位抢占优先级，2位响应优先级 
	TIM3_Int_Init(999,7199);	//开启定时器3，计数100ms
	Sensor_PWR_ON();					//传感器上电
	BACK_COLOR=BLACK;		//背景为黑色
	POINT_COLOR=YELLOW;	//画笔为黄色
	LCD_ShowString(20,20,"class number:");
	LCD_ShowString(20 + 8*13 ,20 ,This_Class_Num);
	LCD_ShowString(20,40,"ID:");
	LCD_ShowString(20,60,"door status:");

	POINT_COLOR=GREEN;		//笔画为绿色	
	LCD_DrawRectangle(0, 0, 320, 240);	//画矩形框	
	key_init();
	
	LCD_ShowString(220-5*4,220,"20");
	LCD_Show_Chinese16x16(220,220,"周夏宇");
	TIM_Cmd(TIM3, ENABLE);  //失能TIMx	 DISABLE
	
	PWM_Init();
	PWM_SetCompare1(0);
	
	WIFI_GPIO();
	WIFI_Init();
	
	
	
	RC522_Init();		 //RC522
	RC522_PcdReset();
	
	CLR_Buf4();
	G_LED_OFF;
	while(1)
	{	
		
		if(TCP_FLAG != 0)
		{
			USART1TxStr(UART4_RX_BUF);
			USART1TxStr("\r\n");
			TCP_FLAG = 0;
			if(UART4_RX_BUF[TCP_START] == 'o')
			{
				if(UART4_RX_BUF[TCP_START + 1] == This_Class_Num[0] && UART4_RX_BUF[TCP_START + 2] == This_Class_Num[1] 
					&& UART4_RX_BUF[TCP_START + 3] == This_Class_Num[2] && UART4_RX_BUF[TCP_START + 4] == This_Class_Num[3])
				{
					G_LED_ON;
					R_LED_OFF;
					USART1TxStr("open lock\r\n");
					LOCK_Flag = 1;
					Error = 0;
					LCD_ShowString(20 + 8 * 12,60  ,"open");
					PWM_SetCompare1(90);
				}
			}else if(UART4_RX_BUF[TCP_START] == 'c')
			{
				if(UART4_RX_BUF[TCP_START + 1] == This_Class_Num[0] && UART4_RX_BUF[TCP_START + 2] == This_Class_Num[1] 
					&& UART4_RX_BUF[TCP_START + 3] == This_Class_Num[2] && UART4_RX_BUF[TCP_START + 4] == This_Class_Num[3])
				{
					G_LED_OFF;
					USART1TxStr("close lock\r\n");
					LOCK_Flag = 0;
					LCD_ShowString(20 + 8 * 12,60 ,"close");
					PWM_SetCompare1(0);
				}
			}
			else if(UART4_RX_BUF[TCP_START] == 'e')
			{
				if(UART4_RX_BUF[TCP_START + 1] == This_Class_Num[0] && UART4_RX_BUF[TCP_START + 2] == This_Class_Num[1] 
					&& UART4_RX_BUF[TCP_START + 3] == This_Class_Num[2] && UART4_RX_BUF[TCP_START + 4] == This_Class_Num[3])
				{
					Error = 1;
					USART1TxStr("open error\r\n");
					LOCK_Flag = 0;
				}
			}
			else if(UART4_RX_BUF[TCP_START] == 'l')
			{
				if(UART4_RX_BUF[TCP_START + 1] == This_Class_Num[0] && UART4_RX_BUF[TCP_START + 2] == This_Class_Num[1] 
					&& UART4_RX_BUF[TCP_START + 3] == This_Class_Num[2] && UART4_RX_BUF[TCP_START + 4] == This_Class_Num[3])
				{
					Start_Init = 1;
					USART1TxStr("start init rfid card\r\n");
				}
			}
			else if(UART4_RX_BUF[TCP_START] == 'g')
			{
				if(UART4_RX_BUF[TCP_START + 1] == This_Class_Num[0] && UART4_RX_BUF[TCP_START + 2] == This_Class_Num[1] 
					&& UART4_RX_BUF[TCP_START + 3] == This_Class_Num[2] && UART4_RX_BUF[TCP_START + 4] == This_Class_Num[3])
				{
					Start_Init = 0;
					USART1TxStr("end init rfid card\r\n");
				}
			}
			else if(UART4_RX_BUF[TCP_START] == 'i')
			{
				if(UART4_RX_BUF[TCP_START + 1] == This_Class_Num[0] && UART4_RX_BUF[TCP_START + 2] == This_Class_Num[1] 
					&& UART4_RX_BUF[TCP_START + 3] == This_Class_Num[2] && UART4_RX_BUF[TCP_START + 4] == This_Class_Num[3])
				{
					NowRwrite = 1;
					for(k = 0;k < 16;k++)
					{
						if(UART4_RX_BUF[TCP_START + k + 5] == '*')
						{
							Passwd[k] = 0;
						}else{
							Passwd[k] = UART4_RX_BUF[TCP_START + k + 5];
						}
					}
					RC522_PcdWrite(60,This_Class_Num);
					USART1TxStr("int rfid id\r\n");
				}
			}
			CLR_Buf4();
			//CLR_TCP();
		}
		if(LOCK_Flag == 0)
		{
			if (( ucStatusReturn = RC522_PcdRequest (PICC_REQALL, ucArray_ID) ) == MI_OK )
			{
				USART1TxStr("ok\r\n");
				if ( RC522_PcdAnticoll ( ucArray_ID ) == MI_OK )                                                                   
				{
					RC522_PcdSelect(ucArray_ID);
					for( i = 0;i < 4;++i)
					{
						
						sprintf(data,"%02x",ucArray_ID[i]);
						LCD_ShowString(54 + i * 16,40,data);
						USART1TxStr(data);
					}
					USART1TxStr("\r\n");
					if(Start_Init == 0)
					{
						memset(Passwd,0,sizeof(Passwd));
						status = RC522_PcdAuthState(PICC_AUTHENT1A, 63, DefaultKey, ucArray_ID);
						if(status == MI_OK)
						{
							USART1TxStr("yes!\r\n");
						}else{
						    //USART1TxStr("no!\r\n");
							RC522_PcdAuthState(PICC_AUTHENT1A, 62, DefaultKey2, ucArray_ID);
						}
						sprintf(TCP_SEND_DATA,"%d\r\n",status);
						USART1TxStr(TCP_SEND_DATA);
						
						RC522_PcdRead(60,Passwd);
						for(k = 0;k < 16; k++)
						{
							sprintf(data,"%02x ",Passwd[k]);
							USART1TxStr(data);
						}
						USART1TxStr("\r\n");
						
						sprintf(TCP_SEND_DATA,"o#%02x%02x%02x%02x#%s#%s",ucArray_ID[0],ucArray_ID[1],ucArray_ID[2],ucArray_ID[3],Passwd,This_Class_Num);
						UART4TxStr(TCP_SEND_DATA);
						USART1TxStr(TCP_SEND_DATA);
						USART1TxStr("\r\n");
						delay_ms(5000);					
					}else{
						if(NowRwrite == 0)
						{
							sprintf(TCP_SEND_DATA,"i#%02x%02x%02x%02x",ucArray_ID[0],ucArray_ID[1],ucArray_ID[2],ucArray_ID[3]);
							UART4TxStr(TCP_SEND_DATA);
							USART1TxStr("\r\n");
							USART1TxStr(TCP_SEND_DATA);
							USART1TxStr("\r\n");
							delay_ms(5000);							
						}else{
							status = RC522_PcdAuthState(PICC_AUTHENT1A, 63, DefaultKey, ucArray_ID);
							if(status == MI_OK)
							{
								USART1TxStr("yes!\r\n");
							}else{
								//USART1TxStr("no!\r\n");
								status = RC522_PcdAuthState(PICC_AUTHENT1A, 62, DefaultKey2, ucArray_ID);
							}
							sprintf(TCP_SEND_DATA,"RC522_PcdAuthState%d\r\n",status);
							USART1TxStr(TCP_SEND_DATA);
							
							status = RC522_PcdWrite(60, Passwd);
							sprintf(TCP_SEND_DATA,"%d\r\n",status);
							USART1TxStr(TCP_SEND_DATA);
							if(status == MI_OK)
							{
								UART4TxStr("f#finish");
								USART1TxStr("write rfid card finish\r\n");
							}else{
								UART4TxStr("e#error");
								USART1TxStr("write rfid card error\r\n");
							}
							NowRwrite = 0;
						}
					}
				}
			}
			else if( ucStatusReturn == MI_ERR)
			{
				//USART1TxStr("No\r\n");
			}
			
			if(Error == 1 && Flag_timer_1S != 0)
			{
				Flag_timer_1S = 0;
				if(Error_light_flag == 0)
				{
					R_LED_ON;
					Error_light_flag = ~Error_light_flag;
				}else{
					R_LED_OFF;
					Error_light_flag = ~Error_light_flag;
				}
			}else if(Error == 0)
				R_LED_OFF;
			
		}
	}
}


