#include "nbiot.h"
#include "timer.h"






bool Flag_Need_Init_Nbiot = 1;
bool Flag_device_error = 0;

unsigned char NB_Send_buf[355]={0};
unsigned char addr = 0;
unsigned int i;
unsigned char len_1 = 0;
char Up_Data[200];//上传的数据帧
char Send_data_buf[150];
extern unsigned char  RxBuffer[255],RxCounter;
char *strx,*extstrx;

u32 int num;

void Init_Nbiot(void)//初始化Nbiot模块
{
	unsigned int i,j,n = 3;
	char n_str;
	char temp_str[30];
	for(i = 0;i < 30;i ++)
	temp_str[i] = 0;
	USART1TxStr("检测NB模块上电时返回的数据...\r\n");
	NB_PWR_ON();			//NB模块上电
	LCD_ShowString(8*2,16*2,"restarting...");	
	delay_ms(1500);
	delay_ms(1500);
	Wait_Str1_Str2_x_100ms(2,USART2_RX_BUF,USART_REC_LEN,&Flag_Usart2_Receive,1,1,"Leaving the BROM","",60); 
	CLR_Buf2();
	
	delay_ms(1000);

	while(n--)
	{
		USART1TxStr("发送AT...\r\n");
		n_str = (3-n)+'0';
		LCD_ShowString(8*1-3,16*3,&n_str);
		LCD_ShowString(8*2,16*3,"AT...");
		USART2TxStr("AT\r\n");//测试NB模块
		if(!Wait_Str1_Str2_x_100ms(2,USART2_RX_BUF,USART_REC_LEN,&Flag_Usart2_Receive,1,1,"OK","",50))
			n = 0;
		
	}CLR_Buf2();

	delay_ms(1000);

	n = 3;
	while(n--)
	{
		USART1TxStr("查询设备PDP地址...\r\n");
		n_str = (3-n)+'0';
		LCD_ShowString(8*1-3,16*4,&n_str);
		LCD_ShowString(8*2,16*4,"AT+CGPADDR=1");
		USART2TxStr("AT+CGPADDR=1\r\n");//查询设备的PDP地址，返回格式：+CGPADDR: 1,21.176.194.17,0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.1    后跟OK
		if(!Wait_Str1_Str2_x_100ms(2,USART2_RX_BUF,USART_REC_LEN,&Flag_Usart2_Receive,2,2,"+CGPADDR:","OK",50))
			n = 0;
		
	}CLR_Buf2();

	delay_ms(1000);

	n = 3;
	while(n--)
	{
		USART1TxStr("配置电信IOT平台地址和端口号...\r\n");
		n_str = (3-n)+'0';
		LCD_ShowString(8*1-3,16*5,&n_str);
		LCD_ShowString(8*2,16*5,"AT+QLWSERV=\"221.229.214.202\",5683");
		USART2TxStr("AT+QLWSERV=\"221.229.214.202\",5683\r\n");//配置电信IOT平台地址和端口，返回格式：OK
		if(!Wait_Str1_Str2_x_100ms(2,USART2_RX_BUF,USART_REC_LEN,&Flag_Usart2_Receive,1,1,"OK","",50))
			n = 0;
		
	}CLR_Buf2();
	
	delay_ms(1000);

	n = 3;
	while(n--)
	{
		USART1TxStr("查询IMEI码...\r\n");
		n_str = (3-n)+'0';
		LCD_ShowString(8*1-3,16*6,&n_str);
		LCD_ShowString(8*2,16*6,"AT+CGSN=1");
		USART2TxStr("AT+CGSN=1\r\n");//查询IMEI码 返回格式应该为：+CGSN: 123456789ABCDEF   后跟OK
		if(!Wait_Str1_Str2_x_100ms(2,USART2_RX_BUF,USART_REC_LEN,&Flag_Usart2_Receive,2,2,"+CGSN:","OK",50))//成功收到IMEI码后 
			
		{//判断IMEI码位置，提取IMEI码，拼成下一条AT指令：AT+QLWCONF="123456789ABCDEF"
			for(i = 0;i < USART_REC_LEN;i ++)//判断IMEI码位置
			{
				if((USART2_RX_BUF[i] == '+') 
					&& (USART2_RX_BUF[i+1] == 'C')
					&& (USART2_RX_BUF[i+2] == 'G')
					&& (USART2_RX_BUF[i+3] == 'S')
					&& (USART2_RX_BUF[i+4] == 'N')
					&& (USART2_RX_BUF[i+5] == ':'))
				{
					strcpy(temp_str,"AT+QLWCONF=\"");//编辑下一条AT指令
					for(j = 0;j < 15;j ++,i ++)
						temp_str[j+12] = USART2_RX_BUF[i+7];//提取IMEI码，进行拼接
					strcpy(&temp_str[27],"\"\r\n");
					i = USART_REC_LEN;
				}
			}
			n = 0;
		}
	}CLR_Buf2();

	delay_ms(1000);

	n = 3;
	while(n--)
	{
		USART1TxStr("配置电信IOT平台参数...\r\n");
		n_str = (3-n)+'0';
		LCD_ShowString(8*1-3,16*7,&n_str);
		LCD_ShowString(8*2,16*7,temp_str);
		USART2TxStr(temp_str);//发送AT指令：AT+QLWCONF="123456789ABCDEF" 配置电信IOT平台参数， 返回格式：OK
		if(2,USART2_RX_BUF,USART_REC_LEN,&Flag_Usart2_Receive,1,1,"OK","",50)
			n = 0;
		for(i = 0;i < 30;i ++)
			temp_str[i] = 0;
		
	}CLR_Buf2();
	
	delay_ms(1000);

	n = 3;
	while(n--)
	{
		USART1TxStr("添加LwM2M对象...\r\n");
		n_str = (3-n)+'0';
		LCD_ShowString(8*1-3,16*8,&n_str);
		LCD_ShowString(8*2,16*8,"AT+QLWADDOBJ=19,0,1,\"0\"");
		USART2TxStr("AT+QLWADDOBJ=19,0,1,\"0\"\r\n");//添加LwM2M对象，返回格式：OK

		if(!Wait_Str1_Str2_x_100ms(2,USART2_RX_BUF,USART_REC_LEN,&Flag_Usart2_Receive,1,1,"OK","",50)) 
			n = 0;
		delay_ms(1000);delay_ms(1000);delay_ms(1000);
	}CLR_Buf2();

	delay_ms(1000);

	n = 3;
	while(n--)
	{
		USART1TxStr("打开射频，发送注册请求...\r\n");
		n_str = (3-n)+'0';
		LCD_ShowString(8*1-3,16*9,&n_str);
		LCD_ShowString(8*2,16*9,"AT+QLWOPEN=0");
		USART2TxStr("AT+QLWOPEN=0\r\n");//打开射频，发送注册请求，立刻返回 OK，之后等待约7秒，成功返回 CONNECT OK ,再等待约4秒，返回+QLWOBSERVE: 0,19,0,0
		if(!Wait_Str1_Str2_x_100ms(2,USART2_RX_BUF,USART_REC_LEN,&Flag_Usart2_Receive,1,1,"CONNECT OK","",100))//最多等待10秒
		{
			USART1TxStr("成功连接服务器！\r\n");
		}
		if(!Wait_Str1_Str2_x_100ms(2,USART2_RX_BUF,USART_REC_LEN,&Flag_Usart2_Receive,1,1,"+QLWOBSERVE:","",70)) 
			n = 0;
		
	}CLR_Buf2();

	delay_ms(1000);

	n = 3;
	while(n--)
	{
		USART1TxStr("设置数据格式...\r\n");
		n_str = (3-n)+'0';
		LCD_ShowString(8*1-3,16*10,&n_str);
		LCD_ShowString(8*2,16*10,"AT+QLWCFG=\"dataformat\",1,1");
		USART2TxStr("AT+QLWCFG=\"dataformat\",1,1\r\n");//设置数据格式为十六进制字符串格式，返回格式：OK
		if(!Wait_Str1_Str2_x_100ms(2,USART2_RX_BUF,USART_REC_LEN,&Flag_Usart2_Receive,1,1,"OK","",50))
			n = 0;
		
	}CLR_Buf2();
	
	delay_ms(1000);

	n = 3;
	while(n--)
	{
		USART1TxStr("发送握手帧...\r\n");
		n_str = (3-n)+'0';
		LCD_ShowString(8*1-3,16*11,&n_str);
		LCD_ShowString(8*2,16*11,"AT+QLWDATASEND=19,0,1,14,02......");
		USART2TxStr("AT+QLWDATASEND=19,0,1,14,02000100070007636f6e6e656374,0x0100\r\n");//发送握手帧，立刻返回OK，等待约7秒，成功返回SEND OK 

		if(2,USART2_RX_BUF,USART_REC_LEN,&Flag_Usart2_Receive,1,1,"SEND OK","",100)
		{
			n = 0;
			LCD_ShowString(8*2,16*12,"send ok!");
			delay_ms(1000);
			LCD_Clear(BLACK); //清屏 
			
		}
		else
		{
			LCD_ShowString(8*2,16*12,"fail   !");
		}
		
	}CLR_Buf2();
}

char *my_strcat(char *str1, char *str2)  //拼接字符串
{
    char *pt = str1;
    while(*str1!='\0') str1++;
    while(*str2!='\0') *str1++ = *str2++;
    *str1 = '\0';
    return pt;
}
void StringToHexstring(char *string,char *hexstring)   //字符串转成十六进制形式的字符串，便于发送给十六进制接收的设备解析
	//string：要转换的字符串 直接填入数组名 例如Test1[10]="123";填入Test1 
//hexstring：转换好要存入的数组。例如定义好一个 Test2[]
{
  int b;  
	int length;
  char str2[16] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f' };
  char s1 ; 
	char s2 ;
	int i,j=0;
	length=strlen(string);
  for (i = 0,j = 0; (i < length) && (j < 2*length); i++, j++)
  { 
    b = 0x0f & (string[i] >> 4);
    s1 = str2[b];
    hexstring[j] = s1;
    b = 0x0f & string[i];
     s2 = str2[b];
    j++;
    hexstring[j] = s2;
  }
}

void Wait_OK(void)
{
	while(!Flag_usart1_receive_OK);
	Flag_usart1_receive_OK = 0;
	CLR_Buf1();	//清除串口1接收缓存
}

void copy_str(char* des,char* src,unsigned char len)
{
	unsigned char i;
	for(i = 0;i < len;i ++)
	{
		*(des + i) = *(src + i);
	}
}

bool Wait_Str_x_100ms(char* str1,char* str2,unsigned char time_x_100ms)
{
	bool Flag_receive_right = 0;
	Count_time_wait_ok = time_x_100ms;
	while(!Flag_receive_right && Count_time_wait_ok)
	{
		if(Flag_Usart1_Receive//如果串口1有数据接收
		&&(!Count_Timer3_value_USART1_receive_timeout))//并且如果接收超时
		{
			Flag_Usart1_Receive = 0;
			if(Query(USART1_RX_BUF,str1,USART1_REC_LEN))
			{
				Flag_receive_right = 1;
				USART2TxStr(USART1_RX_BUF);
				USART2TxStr("返回正确！\r\n");
			}
			else if(Query(USART1_RX_BUF,str2,USART1_REC_LEN))
			{
				Flag_receive_right = 1;
				USART2TxStr(USART1_RX_BUF);
				USART2TxStr("返回正确！\r\n");
			}
		}
	}
	if(!Count_time_wait_ok)
	{
		USART2TxStr("Flag_device_error = 1 \r\n");
		Flag_device_error = 1;
	}
	else
		Flag_device_error = 0;
	USART2TxStr("Count_time_wait_ok = ");
	USART2TxChar(Count_time_wait_ok / 100 + '0'); 
	USART2TxChar(Count_time_wait_ok % 100 / 10 + '0'); 
	USART2TxChar(Count_time_wait_ok % 10 + '0');
  USART2TxStr("\r\n");	
	delay_ms(100);	
	if(Flag_device_error)
		return 1;//超时返回1
	else
		return 0;//正常返回0
}
bool Wait_Str1_Str2_x_100ms(
															char uartx,								//串口号，值：1~5
															char* USARTx_RX_BUF,			//被检索的缓存首地址
															unsigned int LEN,					//被检索的缓存总长度
															bool* add_Flag_Usart_x_Receive,//串口接收到数据的标志变量的地址
															char and_or,							//值：1~2 （1：只检索是否包含其中一个字符串。 2：同时检索是否包含2个字符串）
															char str_NO,							//值：1~2 （在and_or取值1时，该取值才有效。1：检索第一个字符串。 2：检索第二个字符串）
															char* str1,								//第一个字符串的首地址
															char* str2,								//第二个字符串的首地址
															unsigned char Value_Count_time_wait_ok_x_100ms//超时时间：x * 100ms
														)
{
	bool Flag_device_error = 0;
	bool Flag_receive_right = 0;
  unsigned char * add_Count_Timer3_value_USART_x_receive_timeout;	
	switch(uartx)
	{
		case 1:add_Count_Timer3_value_USART_x_receive_timeout = &Count_Timer3_value_USART1_receive_timeout;break;
		case 2:add_Count_Timer3_value_USART_x_receive_timeout = &Count_Timer3_value_USART2_receive_timeout;break;
		case 3:add_Count_Timer3_value_USART_x_receive_timeout = &Count_Timer3_value_USART3_receive_timeout;break;
		case 4:add_Count_Timer3_value_USART_x_receive_timeout = &Count_Timer3_value_UART4_receive_timeout;break;
		case 5:add_Count_Timer3_value_USART_x_receive_timeout = &Count_Timer3_value_UART5_receive_timeout;break;
	}
  Count_time_wait_ok_x_100ms = Value_Count_time_wait_ok_x_100ms;
	while(!Flag_receive_right && Count_time_wait_ok_x_100ms)
	{
		if(*add_Flag_Usart_x_Receive//如果串口x有数据接收
		&&(!*add_Count_Timer3_value_USART_x_receive_timeout))//并且如果接收超时
		{
			*add_Flag_Usart_x_Receive = 0;
			if(and_or == 2)//如果要求满足两个字符串
			{
				if(Query(USARTx_RX_BUF,str1,LEN) && Query(USARTx_RX_BUF,str2,LEN))
				{
					Flag_receive_right = 1;
//					USART2TxStr(USARTx_RX_BUF);
//					USART2TxStr("返回正确！\r\n");
				}
			}
			else if(and_or == 1)//如果只要求检索一个字符串
			{
				if(str_NO == 1)//如果只要求检索第一个字符串
				{
					if(Query(USARTx_RX_BUF,str1,LEN))
					{
						Flag_receive_right = 1;
						//USART1TxStr(USARTx_RX_BUF);
						//USART1TxStr("返回正确！\r\n");
					}
				}
				else if(str_NO == 2)//如果只要求检索第二个字符串
				{				
					if(Query(USARTx_RX_BUF,str2,LEN))
					{
						Flag_receive_right = 1;
						//USART1TxStr(USARTx_RX_BUF);
						//USART1TxStr("返回正确！\r\n");
					}
					
				}
			}
		}
	}
	if(!Count_time_wait_ok_x_100ms)
	{
		//USART2TxStr("Flag_device_error = 1 \r\n");
		//USART2TxStr(USARTx_RX_BUF);
		Flag_device_error = 1;
		//R_LED_ON;
	}
	else
	{
		//R_LED_OFF;
		Flag_device_error = 0;
	}
//	USART2TxStr("Count_time_wait_ok = ");
//	USART2TxChar(Count_time_wait_ok / 100 + '0'); 
//	USART2TxChar(Count_time_wait_ok % 100 / 10 + '0'); 
//	USART2TxChar(Count_time_wait_ok % 10 + '0');
//  USART2TxStr("\r\n");	
	delay_ms(100);	
	if(Flag_device_error)
		return 1;//超时返回1
	else
		return 0;//正常返回0
}

bool Wait_ready_x_100ms(unsigned char time_x_100ms)
{
	bool Flag_usart1_receive_ready = 0;
	Count_time_wait_ok = time_x_100ms;
	while(!Flag_usart1_receive_ready && Count_time_wait_ok)
	{	
		if(Query(USART1_RX_BUF,"ready",USART1_REC_LEN))
		{
			Flag_usart1_receive_ready = 1;
			USART2TxStr("wifi重启成功！\r\n");
		}	
	}	
	if(!Count_time_wait_ok)
	{
		Flag_device_error = 1;
		USART2TxStr("Flag_device_error = 1\r\n");
	}
	delay_ms(100);
	if(Flag_device_error)
		return 1;//超时返回1
	else
		return 0;//正常返回0
}

unsigned char Query(char * src,char * des,unsigned int LEN)
	//查询数组有无包含该字符串，有则返回1，无则返回0
{
	unsigned int y= 0,len= 0,n= 0;
	unsigned char Result = 0;
	char * i;
	i = des;
	for(; *i != '\0';i ++,len ++){}// 判断需要检测的字符的长度
	for(y = 0; y < LEN - len;y ++)
		//开始检测，次数为总长度减去字符长度的字节数
	{
		for(n = 0;n < len;n ++)
		{
			if(*(src + y + n) == *(des + n))
				//开始检测双方的第一个字节，如果相等则结果等于1，并且继续检测双方的第二个字节
			{
				Result = 1;				
			}
			else
			{
				Result = 0;	//不相等则结果等于0，并且退出此次循环，
										//开始检测数组的第二个字节和字符的第一个字节
				break;
			}
		}
		if(n == len)
		{
			return Result;
		}
	}
	return Result;
}

/*void DealUpData(char *from,uint8_t *to,uint16_t len)
{
	int i=0;
	uint16_t tlen=len+7;
	char tmp[3]={0};
	strcat((char *)to,"19,0,1,");
	to+=7;
	if(tlen>=100)
	{
		*to=tlen/100+'0';
		to++;
		*to=(tlen%100)/10+'0';
		to++;
		*to=tlen%10+'0';
		to++;
	}else if(tlen>=10){
		*to=tlen/10+'0';
		to++;
		*to=tlen%10+'0';
		to++;
	}else{
		*to=tlen+'0';
		to++;
	}
	strcat((char *)to,",020005000700");
	to+=13;
	sprintf((char *)to,"%02x",len);
	
	to++;
	for(i=0;i<strlen(from);i++)
	{
		sprintf(tmp,"%02x",from[i]);
		strcat((char *)to,tmp);
	}
	strcat((char *)to,",0x0100\r\n");
}*/

void DealUpData(char *from,u8 *to,u16 len,char *id)
{
	int i=0;
	uint16_t tlen=len+7;
	char tmp[3]={0};
	strcat((char *)to,"19,0,1,");//"19,0,1,"
	to+=7;
	if(tlen>=100)
	{
		*to=tlen/100+'0';
		to++;
		*to=(tlen%100)/10+'0';
		to++;
		*to=tlen%10+'0';
		to++;
	}else if(tlen>=10){
		*to=tlen/10+'0';
		to++;
		*to=tlen%10+'0';
		to++;
	}else{
		*to=tlen+'0';
		to++;
	}
	//strcat((char *)to,id);//",020001000700" ;(const char *)id
	sprintf((char *)to,"%s",id);
	to+=13;
	sprintf((char *)to,"%02x",len);
	
	to++;
	for(i=0;i<strlen(from);i++)
	{
		sprintf(tmp,"%02x",from[i]);
		strcat((char *)to,tmp);
	}
	strcat((char *)to,",0x0100\r\n");
}

void Array_CLR(char *src,char len) //清除数组
{	
	unsigned int y=0;	
	for( y= 0;y < len;y ++)
	{
		src[y] = '\0';
	}
} 




void Send_flag(int n){//发送成功标志，将数据是否成功上传至平台的标志显示在LCD显示屏上
	
	while(n--)
		{
			USART1TxStr(NB_Send_buf);

			USART2TxStr((char*)NB_Send_buf);//通过NB模块发送数据
			LCD_ShowString(8*2,16*12,"send....");
			if(!Wait_Str1_Str2_x_100ms(2,USART2_RX_BUF,USART_REC_LEN,&Flag_Usart2_Receive,1,1,"SEND OK","",100)) 
			{
				n = 0;

				Flag_Need_Init_Nbiot = 0;
				LCD_ShowString(8*2,16*12,"send ok!");
			}
			else
			{
				Flag_Need_Init_Nbiot = 1;
				LCD_ShowString(8*2,16*12,"Fail !  ");
			}			
		}
		CLR_Buf2();	
}

void CLR(void){//清除缓存，将串口3的接收到的数据清空，清除Up_Data之中的数据
	for(i = addr;i < 150;i ++)
		//Up_Data[i] = 0;	
	  Send_data_buf[i] = 0;	
		CLR_Buf3();
}

void CLR_Send_Buff(void)     //清除缓存
{
	unsigned int y=0;
	for( y= 0;y < USART_REC_LEN;y ++)
	{
		Send_data_buf[y] = '\0';
	}
}


void Send_Buff(char Send_data_buf[],char id[])
{
	  LCD_ShowString(8*2,16*11,"BC26_Send... ");
		//strcat(Send_data_buf,buff);
	USART1TxStr(Send_data_buf);
		strcpy((char *)NB_Send_buf,"AT+QLWDATASEND=");
		DealUpData(Send_data_buf,&NB_Send_buf[15],strlen(Send_data_buf),id);//把数据转成十六进制字符串格式并拼接成AT指令
		Send_flag(1);
	  USART1TxStr("send ok11");
		CLR_Send_Buff();//清空缓存
}

void BC26_IOTSenddata(char* data)//上发数据，上发的数据跟对应的插件有关系，用户需要注意插件然后对应数据即可
{ 
    printf(data);//上发数据,
    delay_ms(1500);
		delay_ms(1500);
    strx=strstr((const char*)RxBuffer,(const char*)"SEND OK");//返SEND OK
    while(strx==NULL)
    {
			  LCD_ShowString(8*2,16*11,"BC26_Send ERROR");
        strx=strstr((const char*)RxBuffer,(const char*)"SEND OK");//返SEND OK	
			  LCD_ShowString(8*2,16*11,"BC26_Send");
    }
		LCD_ShowString(8*2,16*11,"BC26_Send OK   ");
    RxCounter=0; 
}

