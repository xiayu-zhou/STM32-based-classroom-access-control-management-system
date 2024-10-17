#include "sys.h"
#include "usart.h"
#include "GPIO.h"
#include "stdbool.h"
#include "string.h"
#include "timer.h"
//如果使用ucos,则包括下面的头文件即可.
#if SYSTEM_SUPPORT_OS
#include "includes.h"					//ucos 使用	  
#endif
//////////////////////////////////////////////////////////////////////////////////	 

char USART1_RX_BUF[USART1_REC_LEN];     //接收缓冲,最大USART_REC_LEN个字节.
char USART2_RX_BUF[USART_REC_LEN];     //接收缓冲,最大USART_REC_LEN个字节.
unsigned char USART3_RX_BUF[USART_REC_LEN];     //接收缓冲,最大USART_REC_LEN个字节.
char UART4_RX_BUF[USART_REC_LEN];     //接收缓冲,最大USART_REC_LEN个字节.
char UART5_RX_BUF[USART_REC_LEN];     //接收缓冲,最大USART_REC_LEN个字节.



u16 USART1_RX_STA=0;       //接收状态标记	  
u16 USART2_RX_STA=0;       //接收状态标记
u16 USART3_RX_STA=0;       //接收状态标记 
u16 UART4_RX_STA=0;       //接收状态标记 
u16 UART5_RX_STA=0;       //接收状态标记 

unsigned char Count_Timer3_value_USART1_receive_timeout = 0;
unsigned char Count_Timer3_value_USART2_receive_timeout = 0;
unsigned char Count_Timer3_value_USART3_receive_timeout = 0;

bool  Flag_Usart1_Receive;
bool  Flag_Usart1_Remap_Receive;
bool  Flag_Usart2_Receive;
bool  Flag_Usart3_Receive;
bool  Flag_Usart1_Remap;
bool  Flag_Usart3_Remap;
bool  Flag_Usart3_Receive_Complete;
bool  Flag_usart1_receive_OK = 0;
bool 	Flag_usart1_receive_T = 0;
bool 	Flag_usart2_receive_T = 0;
char RxCounter,RxBuffer[USART_REC_LEN];     //接收缓冲,最大USART_REC_LEN个字节.
char RxCounter1,RxBuffer1[USART_REC_LEN];     //接收缓冲,最大USART_REC_LEN个字节.
unsigned char Flag_Uart4_Receive;
bool Flag_Uart5_Receive;

int TCP_START = 0;
int TCP_END = 0;
uint8_t TCP_FLAG = 0;

unsigned char Flag_uart4_receive_OK = 0;
 
#if 1
#pragma import(__use_no_semihosting)             
//标准库需要的支持函数                 
struct __FILE 
{ 
	int handle; 

}; 

FILE __stdout;       
//定义_sys_exit()以避免使用半主机模式    
_sys_exit(int x) 
{ 
	x = x; 
} 
//重定义fputc函数 
int fputc(int ch, FILE *f)
{      
	while((USART1->SR&0X40)==0);//循环发送,直到发送完毕   
    USART1->DR = (u8) ch;      
	return ch;
}
#endif 

#if EN_USART1_RX   //如果使能了接收
//串口1中断服务程序
//注意,读取USARTx->SR能避免莫名其妙的错误   	
u8 USART_RX_BUF[USART_REC_LEN];     //接收缓冲,最大USART_REC_LEN个字节.
//接收状态
//bit15，	接收完成标志
//bit14，	接收到0x0d
//bit13~0，	接收到的有效字节数目
u16 USART_RX_STA=0;       //接收状态标记	  
  
void Usart1_Init(u32 bound)
{
  //GPIO端口设置
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO, ENABLE);	//使能USART1，GPIOA时钟
    GPIO_PinRemapConfig(GPIO_Remap_USART1,DISABLE);//重映射关闭	
	//USART1_TX   PA.9初始化
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.9
   
  //USART1_RX	  GPIOA.10初始化
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//PA10
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.10  
	
  //Usart1 NVIC 配置
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; //抢占优先级0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;	//子优先级0
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;	//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器

   //USART 初始化设置
	USART_InitStructure.USART_BaudRate = bound;	//一般设置为9600
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;	//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;	//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;	//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;	//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式

	USART_Init(USART1,&USART_InitStructure);	//初始化串口
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);	//开启中断
	USART_Cmd(USART1, ENABLE);	//使能串口

}

void Usart1_Remap_Init(u32 bound)
{
  //GPIO端口设置
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO, ENABLE);	//使能USART1，GPIOA时钟
  GPIO_PinRemapConfig(GPIO_Remap_USART1, ENABLE);

	//USART1_TX   PB.6初始化
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6; //PB.6
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
  GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIOB.6
   
  //USART1_RX	  GPIOB.7初始化
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;//PB7
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
  GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIOAB.7  

  //Usart1 NVIC 配置
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; //抢占优先级0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;	//子优先级0
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;	//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器

   //USART 初始化设置
	USART_InitStructure.USART_BaudRate = bound;	//一般设置为9600
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;	//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;	//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;	//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;	//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式

	USART_Init(USART1,&USART_InitStructure);	//初始化串口
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);	//开启中断
	USART_Cmd(USART1, ENABLE);	//使能串口

}

/* USART1发送一个字符 */ 
void USART1TxChar(char ch)
{
	USART_SendData(USART1,(u8) ch);
	while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET)
	{}

}

/* USART1发送一个数组数据（十六进制） */
void USART1TxData(unsigned char *pt)
{
	while(*pt != '\0')
	{
		USART1TxChar(*pt);
		pt++;
	}
}

void USART1TxData_hex(unsigned char *pt,unsigned char len)
{
  while(len)   
  {
    USART1TxChar(*pt);
    pt++;
    len --; 
  }
}

/* USART1发送一个字符串 */ 
void USART1TxStr(char *pt) 
{
	while(*pt != '\0')   
	{
		USART1TxChar(*pt);
		pt++;
	}
}

void USART1_IRQHandler(void)                	//串口1中断服务程序
{
	u8 Res;
	if(USART_GetFlagStatus(USART1, USART_IT_RXNE) != RESET)	//接收中断
	{
		Res = USART_ReceiveData(USART1);	//读取接收到的数据
		USART1_RX_BUF[USART1_RX_STA] = Res;
		if(USART1_RX_BUF[USART1_RX_STA] == 'K')
		{
			if(USART1_RX_BUF[USART1_RX_STA - 1] == 'O')
			{
				Flag_usart1_receive_OK = 1;
			}
		}
		if(USART1_RX_BUF[USART1_RX_STA] == 'T')
		{
			Flag_usart1_receive_T = 1;
		}
		USART1_RX_STA ++;
		if(USART1_RX_STA > (USART1_REC_LEN - 1))
			USART1_RX_STA = 0;
		Flag_usart1_receive_T = 1;
		Count_Timer3_value_USART1_receive_timeout = 2;
	}
} 

void CLR_Buf1(void)     //清除串口1接收缓存
{
	unsigned int y=0;
	for( y= 0;y < USART1_REC_LEN;y ++)
	{
		USART1_RX_BUF[y] = '\0';
	}
	USART1_RX_STA = 0;
} 

/**************************串口2初始化********************************/

/*串口2初始化*/
void Usart2_Init(u32 bound) 
{
	USART2_RCC_Configuration();   
	GPIO_PinRemapConfig(GPIO_Remap_USART2,DISABLE);//重映射关闭	
	USART2_GPIO_Configuration();  
	USART2_Configuration(bound);   
	USART2_NVIC_Configuration();
}

void Usart2_Remap_Init(u32 bound) 
{
	USART2_RCC_Configuration();  
	GPIO_PinRemapConfig(GPIO_Remap_USART2,ENABLE);//重映射打开	
	USART2_GPIO_Configuration();  
	USART2_Configuration(bound);   
	USART2_NVIC_Configuration();
}

/*初始化串口2的时钟*/
static void USART2_RCC_Configuration(void)
{  
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOD | RCC_APB2Periph_AFIO, ENABLE);  
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2 | RCC_APB1Periph_TIM3, ENABLE); 
}

/*配置串口2的GPIO*/
static void USART2_GPIO_Configuration(void)	
{
	/*定义GPIO初始化结构体*/
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;       //PA.2 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用推挽输出
	GPIO_Init(GPIOA, &GPIO_InitStructure);      //初始化PA.2 
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;	//PA.3
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	//浮空输入
	GPIO_Init(GPIOA, &GPIO_InitStructure);	//初始化PA.3
	
	/*配置USART2的发送端口*/   
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;       //PD.5 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用推挽输出
	GPIO_Init(GPIOD, &GPIO_InitStructure);      //初始化PD.5 
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;     //PD.6
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 
	GPIO_Init(GPIOD, &GPIO_InitStructure);     //初始化PD.6 
}

/*配置串口2的工作参数*/
static void USART2_Configuration(u32 bound) 
{
	USART_InitTypeDef USART_InitStructure; 
	/*USART相关时钟初始化配置*/  
	USART2_RCC_Configuration();
	/*USART相关GPIO初始化配置*/   
	USART2_GPIO_Configuration();
	USART_InitStructure.USART_BaudRate = bound;	//波特率一般设置为9600
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;	//字长为8位
	USART_InitStructure.USART_StopBits = USART_StopBits_1;	//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;	//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;	//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; 	//收发模式
	/*配置USART2的异步双工串行工作模式*/  
	USART_Init(USART2, &USART_InitStructure); 
	/*使能USART2的接收中断 */   
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
	/*使能USART2*/   
	USART_Cmd(USART2, ENABLE);
}

//配置中断优先级函数  
static void USART2_NVIC_Configuration(void) 
{
	NVIC_InitTypeDef NVIC_InitStructure; 
	/* Configure the NVIC Preemption Priority Bits */  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
	/* USART2中断优先级*/   
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2 ;//抢占优先级优先级别为第三
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2; 
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
	NVIC_Init(&NVIC_InitStructure); 
}


/* USART2发送一个字符 */ 
void USART2TxChar(int ch) 
{ 
	USART_SendData(USART2,(u8) ch);         
	while(USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET)
	{}
}

/* USART2发送一个数组数据（十六进制） */
void USART2TxData(unsigned char *pt)
{
	while(*pt != '\0')   
	{
		USART2TxChar(*pt);
		pt++;
	}
}

void USART2TxData_hex(unsigned char *pt,unsigned char len)
{
  while(len)   
  {
    USART2TxChar(*pt);
    pt++;
    len --; 
  }
}

/* USART2发送一个字符串 */ 
void USART2TxStr(char *pt) 
{
	while(*pt != '\0')   
	{
		USART2TxChar(*pt);
		pt++;
	}
}


char *str;


/*串口2中断服务程序*/
void USART2_IRQHandler(void) 
{
	u8 Res;	
	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)  //接收中断
	{

		Res =USART_ReceiveData(USART2);	//读取接收到的数据

		USART1TxChar(Res);
		
		USART2_RX_BUF[USART2_RX_STA] = Res;

		str=strstr((const char*)USART2_RX_BUF,(const char*)"QLWDATARECV");//返OK//QLWDATARECV为接收表示符
		if(str!=NULL)
		{
					
				switch(USART2_RX_BUF[USART2_RX_STA])
				{
				 case '0': //数据 0 为红灯关
					 R_LED_OFF
									break; 
				 case '1': //数据 1 为红灯开
					 R_LED_ON
									break;	
				 case '2': //数据 2 为绿灯开
					 G_LED_ON
									break;
				 case '3': //数据 3 为绿灯关
					 G_LED_OFF
									break;
				 case '4': //数据 4 为黄灯开
					 Y_LED_ON
									break;
				 case '5': //数据 5 为黄灯关
					 Y_LED_OFF
									break;

				}
				str=NULL;
			}

		//		if((USART2_RX_BUF[USART2_RX_STA] == 'E')//红灯亮
//		&&(USART2_RX_BUF[USART2_RX_STA - 1] == '4')
//		&&(USART2_RX_BUF[USART2_RX_STA - 2] == '2')
//		&&(USART2_RX_BUF[USART2_RX_STA - 3] == '5')){
//			R_LED_ON;
//			USART1TxStr("\r\nR_LED_ON\r\n");
//		}else if((USART2_RX_BUF[USART2_RX_STA] == '6')//红灯灭
//		&&(USART2_RX_BUF[USART2_RX_STA - 1] == '4')
//		&&(USART2_RX_BUF[USART2_RX_STA - 2] == '2')
//		&&(USART2_RX_BUF[USART2_RX_STA - 3] == '5')){
//			R_LED_OFF;
//			USART1TxStr("\r\nR_LED_OFF\r\n");
//		}else if((USART2_RX_BUF[USART2_RX_STA] == 'E')//绿灯亮
//		&&(USART2_RX_BUF[USART2_RX_STA - 1] == '4')
//		&&(USART2_RX_BUF[USART2_RX_STA - 2] == '7')
//		&&(USART2_RX_BUF[USART2_RX_STA - 3] == '4')){
//			G_LED_ON;
//			USART1TxStr("\r\nG_LED_ON\r\n");
//		}else if((USART2_RX_BUF[USART2_RX_STA] == '6')//绿灯灭
//		&&(USART2_RX_BUF[USART2_RX_STA - 1] == '4')
//		&&(USART2_RX_BUF[USART2_RX_STA - 2] == '7')
//		&&(USART2_RX_BUF[USART2_RX_STA - 3] == '4')){
//			G_LED_OFF;
//			USART1TxStr("\r\nG_LED_OFF\r\n");
//		}else if((USART2_RX_BUF[USART2_RX_STA] == 'E')//黄灯亮
//		&&(USART2_RX_BUF[USART2_RX_STA - 1] == '4')
//		&&(USART2_RX_BUF[USART2_RX_STA - 2] == '9')
//		&&(USART2_RX_BUF[USART2_RX_STA - 3] == '5')){
//			Y_LED_ON;
//			USART1TxStr("\r\nY_LED_ON\r\n");
//		}else if((USART2_RX_BUF[USART2_RX_STA] == '6')//黄灯灭
//		&&(USART2_RX_BUF[USART2_RX_STA - 1] == '4')
//		&&(USART2_RX_BUF[USART2_RX_STA - 2] == '9')
//		&&(USART2_RX_BUF[USART2_RX_STA - 3] == '5')){
//			Y_LED_OFF;
//			USART1TxStr("\r\nY_LED_OFF\r\n");
//		}
		
		USART2_RX_STA++;
		if(USART2_RX_STA > (USART_REC_LEN - 1))
		USART2_RX_STA = 0;
		Flag_Usart2_Receive = 1; //数据接收标识至1，表示有数据接收，在main函数中判断
		Count_Timer3_value_USART2_receive_timeout = 2;	
	}
}

void CLR_Buf2(void)     //清除串口2接收缓存
{
	unsigned int y=0;
	for( y= 0;y < USART_REC_LEN;y ++)
	{
		USART2_RX_BUF[y] = '\0';
	}
	USART2_RX_STA =0;
}

/**************************串口3初始化********************************/
/*初始化串口3的时钟*/
static void USART3_RCC_Configuration(void)
{  
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC|RCC_APB2Periph_AFIO, ENABLE);  
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE); 
}

/*配置串口3的GPIO*/
static void USART3_GPIO_Configuration(void)	
{
	/*定义GPIO初始化结构体*/
	GPIO_InitTypeDef GPIO_InitStructure;
	
	//串口3GPIO初始化
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;       //PB.10
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用推挽输出
	GPIO_Init(GPIOB, &GPIO_InitStructure);      //初始化PB.10
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;	//PB.11
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	//浮空输入
	GPIO_Init(GPIOB, &GPIO_InitStructure);	//初始化PB.11
	
	//串口3重映射GPIO初始化
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;	//PC.10
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用推挽输出
	GPIO_Init(GPIOC, &GPIO_InitStructure);	//初始化PC.10
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;	//PC.11
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	//浮空输入
	GPIO_Init(GPIOC, &GPIO_InitStructure);	//初始化PC.11
	
}

/*配置串口3的工作参数*/
static void USART3_Configuration(u32 bound) 
{
	USART_InitTypeDef USART_InitStructure; 
	/*USART相关时钟初始化配置*/  
	USART3_RCC_Configuration();
	/*USART相关GPIO初始化配置*/   
	USART3_GPIO_Configuration();
	USART_InitStructure.USART_BaudRate = bound;	//波特率一般设置为9600
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;	//字长为8位
	USART_InitStructure.USART_StopBits = USART_StopBits_1;	//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;	//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;	//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; 	//收发模式
	/*配置USART3的异步双工串行工作模式*/  
	USART_Init(USART3, &USART_InitStructure); 
	/*使能USART3的接收中断 */   
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
	/*使能USART3*/   
	USART_Cmd(USART3, ENABLE);
}

//配置中断优先级函数  
static void USART3_NVIC_Configuration(void) 
{
	NVIC_InitTypeDef NVIC_InitStructure; 
	/* Configure the NVIC Preemption Priority Bits */  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
	/* USART3中断优先级*/   
	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1 ;//抢占优先级优先级别为第二
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1; 
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
	NVIC_Init(&NVIC_InitStructure); 
}

/*串口3初始化*/
void Usart3_Init(u32 bound) 
{
	USART3_RCC_Configuration();  
	USART3_GPIO_Configuration();  
	USART3_Configuration(bound);   
	USART3_NVIC_Configuration();
}

/*串口3重映射初始化*/
void Usart3_Remap_Init(u32 bound) 
{
	GPIO_PinRemapConfig(GPIO_PartialRemap_USART3,ENABLE);//部分重映射
	USART3_RCC_Configuration();  
	USART3_GPIO_Configuration();  
	USART3_Configuration(bound);   
	USART3_NVIC_Configuration();
}

/* USART3发送一个字符 */ 
void USART3TxChar(int ch) 
{ 
	USART_SendData(USART3,(u8) ch);         
	while(USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET)
	{}
}

/* USART3发送一个数组数据（十六进制） */
void USART3TxData(unsigned char *pt)
{
	while(*pt != '\0')   
	{
		USART3TxChar(*pt);
		pt++;
	}
}

void USART3TxData_hex(unsigned char *pt,unsigned char len)
{
  while(len)   
  {
    USART3TxChar(*pt);
    pt++;
    len --; 
  }
}

/* USART3发送一个字符串 */ 
void USART3TxStr(char *pt) 
{
	while(*pt != '\0')   
	{
		USART3TxChar(*pt);
		pt++;
	}
}

//unsigned int Tem_value,Hum_value ,Dus_value ,Fum_value;
//unsigned int Dust_PM25_value ;
//unsigned int Noise_value;


/*串口3中断服务程序*/
void USART3_IRQHandler(void) 
{
	u8 Res;	
	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)  //接收中断
	{
		Res =USART_ReceiveData(USART3);	//读取接收到的数据
		//判断读取到的数据地址是 01 02 03，然后在这里解析数据帧
		USART3_RX_BUF[USART3_RX_STA & 0X3FFF] = Res;
		/*
		//地址为01的是噪声传感器
		if(USART3_RX_BUF[0]==0x01)
		{
			Noise_value = USART3_RX_BUF[3];
			Noise_value <<= 8;
			Noise_value |= USART3_RX_BUF[4];
			//USART1TxChar("Noise");
		}		
		//地址为02的是PM2.5传感器
		if(USART3_RX_BUF[0]==0x02)
		{
			Dust_PM25_value = USART3_RX_BUF[3];
			Dust_PM25_value <<= 8;
			Dust_PM25_value |= USART3_RX_BUF[4];
			//USART1TxChar("Dust_PM25_value");
		}
		//地址为03的是温湿度传感器
		//if(USART3_RX_BUF[0]==0x03)
		if(USART3_RX_BUF[0]==0xFF)
		{
			Tem_value = USART3_RX_BUF[3];
			Tem_value <<= 8;
			Tem_value |= USART3_RX_BUF[4];
			
			Hum_value = USART3_RX_BUF[5];
			Hum_value <<= 8;
			Hum_value |= USART3_RX_BUF[6];
			//USART1TxChar("Tem_value");
			
		} */

		USART3_RX_STA++;
		if(USART3_RX_STA > (USART_REC_LEN - 1))
			USART3_RX_STA = 0;
		Flag_Usart3_Receive = 1;
		
		//printf("\r\n");
		Count_Timer3_value_USART3_receive_timeout = 2;//定时200ms
	}
}

void CLR_Buf3(void)     //清除串3接收缓存
{
	unsigned int y=0;
	for( y= 0;y < USART_REC_LEN;y ++)
	{
		USART3_RX_BUF[y] = '\0';
	}
	USART3_RX_STA =0;
}

////////////////////////////串口4初始化////////////////////////////////////////////////////////
static void UART4_GPIO_Configuration(void) 
{ 
	/*定义GPIO初始化结构体*/  
	GPIO_InitTypeDef GPIO_InitStructure; 
	/*初始化结构体*/   
	GPIO_StructInit(&GPIO_InitStructure);
	/*配置UART4的接收端口*/   
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;     //Px.11
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //浮空输入
	GPIO_Init(GPIOC, &GPIO_InitStructure);     //初始化PC.11 //
	/*配置UART4的发送端口*/   
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;       //PC.10 //
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用推挽输出
	GPIO_Init(GPIOC, &GPIO_InitStructure);      //初始化PC.10 
}
//配置UART4的工作参数  
static void UART4_Configuration(u32 bound) 
{
	USART_InitTypeDef USART_InitStructure;   
	USART_InitStructure.USART_BaudRate = bound;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b; 
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; 
	/*配置UART4的异步双工串行工作模式*/  
	USART_Init(UART4, &USART_InitStructure); 
	/*使能UART4的接收中断 */   
	USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);
	/*使能UART4*/   
	USART_Cmd(UART4, ENABLE);
}

//配置中断优先级函数  
static void UART4_NVIC_Configuration(void) 
{
	NVIC_InitTypeDef NVIC_InitStructure; 
	/* Configure the NVIC Preemption Priority Bits */  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
	/* UART4中断优先级*/   
	NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2 ;//抢占优先级优先级别为第二
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1; 
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
	NVIC_Init(&NVIC_InitStructure); 
}
void Uart4_Init(u32 bound)//串口4标准接口初始化
{ 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4,ENABLE);  
	UART4_GPIO_Configuration();  
	UART4_Configuration(bound);   
	UART4_NVIC_Configuration();
}
/* UART4发送一个字符 */ 
void UART4TxChar(int ch) 
{ 
	USART_SendData(UART4,(u8) ch);         
	while(USART_GetFlagStatus(UART4, USART_FLAG_TXE) == RESET)
	{}
}
/* UART4发送一个数组数据（十六进制） */
void UART4TxData(unsigned char *pt)
{
	while(*pt != '\0')   
	{
		UART4TxChar(*pt);
		pt++;
	}
}
void UART4TxData_hex(unsigned char *pt,unsigned char len)
{
  while(len)   
  {
    UART4TxChar(*pt);
    pt++;
    len --; 
  }
}
/* UART4发送一个字符串 */ 
void UART4TxStr(char *pt) 
{
	while(*pt != '\0')   
	{
		UART4TxChar(*pt);
		pt++;
	}
}
void UART4_IRQHandler(void)                	//串口4中断服务程序
{
	u8 Res;
	if(USART_GetITStatus(UART4, USART_IT_RXNE) != RESET)  //接收中断
	{		
		Res =USART_ReceiveData(UART4);	//读取接收到的数据
		UART4_RX_BUF[UART4_RX_STA]=Res;
		USART2TxChar(Res); 

		if(UART4_RX_BUF[UART4_RX_STA] == 'K')
		{
			if(UART4_RX_BUF[UART4_RX_STA - 1] == 'O')
			{
				Flag_uart4_receive_OK = 1;
			}
		}
		
		if(Res == '@')
		{
			TCP_START = UART4_RX_STA + 1;
			TCP_FLAG = 0;
		}
		else if(Res == '*')
		{
			TCP_END = UART4_RX_STA - 1;
			TCP_FLAG = 1;
		}

		UART4_RX_STA++;
		if(UART4_RX_STA > (USART_REC_LEN - 1))
			UART4_RX_STA = 0;
		Flag_Uart4_Receive = 1;
		Count_Timer3_value_UART4_receive_timeout = 2;//定时200ms
	}
}
void CLR_Buf4(void)     //清除串口4接收缓存
{
	unsigned int y=0;
//#ifdef Debug_Mode
//	USART2TxStr("Erase usart3 rxbuf\r\n");
//#endif
	for( y= 0;y < USART_REC_LEN;y ++)
	{
		UART4_RX_BUF[y] = '\0';
	}
	UART4_RX_STA =0;
	
	TCP_START = 0;
	TCP_END = 0;
}


///////////////////////////串口5初始化/////////////////////////////////////////////   

static void UART5_GPIO_Configuration(void) 
{ 
	/*定义GPIO初始化结构体*/  
	GPIO_InitTypeDef GPIO_InitStructure; 
	/*初始化结构体*/   
	GPIO_StructInit(&GPIO_InitStructure);
	
	//配置UART5的接收端口    RX  
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;     //PD.2 //浮空输入
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //浮空输入
	GPIO_Init(GPIOD, &GPIO_InitStructure);     //初始化PD.2 
	//配置UART5的发送端口    TX  
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;       //PC.12 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用推挽输出
	GPIO_Init(GPIOC, &GPIO_InitStructure);      //初始化PC.12 
}
//配置UART5的工作参数  
static void UART5_Configuration(u32 bound) 
{
	USART_InitTypeDef USART_InitStructure;   
	/*USART相关GPIO初始化配置*/   
	USART_InitStructure.USART_BaudRate = bound;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b; 
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; 
	/*配置UART5的异步双工串行工作模式*/  
	USART_Init(UART5, &USART_InitStructure); 
	/*使能UART5的接收中断 */   
	USART_ITConfig(UART5, USART_IT_RXNE, ENABLE);
	/*使能UART5*/   
	USART_Cmd(UART5, ENABLE);
}

//配置中断优先级函数  
static void UART5_NVIC_Configuration(void) 
{
	NVIC_InitTypeDef NVIC_InitStructure; 
	/* Configure the NVIC Preemption Priority Bits */  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
	/* UART5中断优先级*/   
	NVIC_InitStructure.NVIC_IRQChannel = UART5_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2 ;//抢占优先级优先级别为第二
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1; 
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
	NVIC_Init(&NVIC_InitStructure); 
}
void Uart5_Init(u32 bound)//串口5标准接口初始化
{ 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5,ENABLE);  
	UART5_GPIO_Configuration();  
	UART5_Configuration(bound);   
	UART5_NVIC_Configuration();
}
/* UART5发送一个字符 */ 
void UART5TxChar(int ch) 
{ 
	USART_SendData(UART5,(u8) ch);         
	while(USART_GetFlagStatus(UART5, USART_FLAG_TXE) == RESET)
	{}
}
/* UART5发送一个数组数据（十六进制） */
void UART5TxData(unsigned char *pt)
{
	while(*pt != '\0')   
	{
		UART5TxChar(*pt);
		pt++;
	}
}
void UART5TxData_hex(unsigned char *pt,unsigned char len)
{
  while(len)   
  {
    UART5TxChar(*pt);
    pt++;
    len --; 
  }
}
/* UART5发送一个字符串 */ 
void UART5TxStr(char *pt) 
{
	while(*pt != '\0')   
	{
		UART5TxChar(*pt);
		pt++;
	}
}
void UART5_IRQHandler(void)                	//串口4中断服务程序
{
	u8 Res;
	if(USART_GetITStatus(UART5, USART_IT_RXNE) != RESET)  //接收中断
	{		
		Res =USART_ReceiveData(UART5);	//读取接收到的数据
		UART5_RX_BUF[UART5_RX_STA]=Res;
//#ifdef USART2_to_UART5_EC20_AT_debug
		USART2TxChar(Res);
//#endif		 
		UART5_RX_STA++;
		
		if(UART5_RX_STA > (USART_REC_LEN - 1))
			UART5_RX_STA = 0;
		Flag_Uart5_Receive = 1;
		Count_Timer3_value_UART5_receive_timeout = 2;//定时200ms
	}
}
void CLR_Buf5(void)     //清除串口3接收缓存
{
	unsigned int y=0;
//#ifdef Debug_Mode
//	USART2TxStr("Erase usart3 rxbuf\r\n");
//#endif
	for( y= 0;y < USART_REC_LEN;y ++)
	{
		UART5_RX_BUF[y] = '\0';
	}
	UART5_RX_STA =0;
}
///////////////////////////////////////////////////


#endif
