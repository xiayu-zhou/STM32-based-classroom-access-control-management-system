#include "nbiot.h"
#include "timer.h"






bool Flag_Need_Init_Nbiot = 1;
bool Flag_device_error = 0;

unsigned char NB_Send_buf[355]={0};
unsigned char addr = 0;
unsigned int i;
unsigned char len_1 = 0;
char Up_Data[200];//�ϴ�������֡
char Send_data_buf[150];
extern unsigned char  RxBuffer[255],RxCounter;
char *strx,*extstrx;

u32 int num;

void Init_Nbiot(void)//��ʼ��Nbiotģ��
{
	unsigned int i,j,n = 3;
	char n_str;
	char temp_str[30];
	for(i = 0;i < 30;i ++)
	temp_str[i] = 0;
	USART1TxStr("���NBģ���ϵ�ʱ���ص�����...\r\n");
	NB_PWR_ON();			//NBģ���ϵ�
	LCD_ShowString(8*2,16*2,"restarting...");	
	delay_ms(1500);
	delay_ms(1500);
	Wait_Str1_Str2_x_100ms(2,USART2_RX_BUF,USART_REC_LEN,&Flag_Usart2_Receive,1,1,"Leaving the BROM","",60); 
	CLR_Buf2();
	
	delay_ms(1000);

	while(n--)
	{
		USART1TxStr("����AT...\r\n");
		n_str = (3-n)+'0';
		LCD_ShowString(8*1-3,16*3,&n_str);
		LCD_ShowString(8*2,16*3,"AT...");
		USART2TxStr("AT\r\n");//����NBģ��
		if(!Wait_Str1_Str2_x_100ms(2,USART2_RX_BUF,USART_REC_LEN,&Flag_Usart2_Receive,1,1,"OK","",50))
			n = 0;
		
	}CLR_Buf2();

	delay_ms(1000);

	n = 3;
	while(n--)
	{
		USART1TxStr("��ѯ�豸PDP��ַ...\r\n");
		n_str = (3-n)+'0';
		LCD_ShowString(8*1-3,16*4,&n_str);
		LCD_ShowString(8*2,16*4,"AT+CGPADDR=1");
		USART2TxStr("AT+CGPADDR=1\r\n");//��ѯ�豸��PDP��ַ�����ظ�ʽ��+CGPADDR: 1,21.176.194.17,0.0.0.0.0.0.0.0.0.0.0.0.0.0.0.1    ���OK
		if(!Wait_Str1_Str2_x_100ms(2,USART2_RX_BUF,USART_REC_LEN,&Flag_Usart2_Receive,2,2,"+CGPADDR:","OK",50))
			n = 0;
		
	}CLR_Buf2();

	delay_ms(1000);

	n = 3;
	while(n--)
	{
		USART1TxStr("���õ���IOTƽ̨��ַ�Ͷ˿ں�...\r\n");
		n_str = (3-n)+'0';
		LCD_ShowString(8*1-3,16*5,&n_str);
		LCD_ShowString(8*2,16*5,"AT+QLWSERV=\"221.229.214.202\",5683");
		USART2TxStr("AT+QLWSERV=\"221.229.214.202\",5683\r\n");//���õ���IOTƽ̨��ַ�Ͷ˿ڣ����ظ�ʽ��OK
		if(!Wait_Str1_Str2_x_100ms(2,USART2_RX_BUF,USART_REC_LEN,&Flag_Usart2_Receive,1,1,"OK","",50))
			n = 0;
		
	}CLR_Buf2();
	
	delay_ms(1000);

	n = 3;
	while(n--)
	{
		USART1TxStr("��ѯIMEI��...\r\n");
		n_str = (3-n)+'0';
		LCD_ShowString(8*1-3,16*6,&n_str);
		LCD_ShowString(8*2,16*6,"AT+CGSN=1");
		USART2TxStr("AT+CGSN=1\r\n");//��ѯIMEI�� ���ظ�ʽӦ��Ϊ��+CGSN: 123456789ABCDEF   ���OK
		if(!Wait_Str1_Str2_x_100ms(2,USART2_RX_BUF,USART_REC_LEN,&Flag_Usart2_Receive,2,2,"+CGSN:","OK",50))//�ɹ��յ�IMEI��� 
			
		{//�ж�IMEI��λ�ã���ȡIMEI�룬ƴ����һ��ATָ�AT+QLWCONF="123456789ABCDEF"
			for(i = 0;i < USART_REC_LEN;i ++)//�ж�IMEI��λ��
			{
				if((USART2_RX_BUF[i] == '+') 
					&& (USART2_RX_BUF[i+1] == 'C')
					&& (USART2_RX_BUF[i+2] == 'G')
					&& (USART2_RX_BUF[i+3] == 'S')
					&& (USART2_RX_BUF[i+4] == 'N')
					&& (USART2_RX_BUF[i+5] == ':'))
				{
					strcpy(temp_str,"AT+QLWCONF=\"");//�༭��һ��ATָ��
					for(j = 0;j < 15;j ++,i ++)
						temp_str[j+12] = USART2_RX_BUF[i+7];//��ȡIMEI�룬����ƴ��
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
		USART1TxStr("���õ���IOTƽ̨����...\r\n");
		n_str = (3-n)+'0';
		LCD_ShowString(8*1-3,16*7,&n_str);
		LCD_ShowString(8*2,16*7,temp_str);
		USART2TxStr(temp_str);//����ATָ�AT+QLWCONF="123456789ABCDEF" ���õ���IOTƽ̨������ ���ظ�ʽ��OK
		if(2,USART2_RX_BUF,USART_REC_LEN,&Flag_Usart2_Receive,1,1,"OK","",50)
			n = 0;
		for(i = 0;i < 30;i ++)
			temp_str[i] = 0;
		
	}CLR_Buf2();
	
	delay_ms(1000);

	n = 3;
	while(n--)
	{
		USART1TxStr("���LwM2M����...\r\n");
		n_str = (3-n)+'0';
		LCD_ShowString(8*1-3,16*8,&n_str);
		LCD_ShowString(8*2,16*8,"AT+QLWADDOBJ=19,0,1,\"0\"");
		USART2TxStr("AT+QLWADDOBJ=19,0,1,\"0\"\r\n");//���LwM2M���󣬷��ظ�ʽ��OK

		if(!Wait_Str1_Str2_x_100ms(2,USART2_RX_BUF,USART_REC_LEN,&Flag_Usart2_Receive,1,1,"OK","",50)) 
			n = 0;
		delay_ms(1000);delay_ms(1000);delay_ms(1000);
	}CLR_Buf2();

	delay_ms(1000);

	n = 3;
	while(n--)
	{
		USART1TxStr("����Ƶ������ע������...\r\n");
		n_str = (3-n)+'0';
		LCD_ShowString(8*1-3,16*9,&n_str);
		LCD_ShowString(8*2,16*9,"AT+QLWOPEN=0");
		USART2TxStr("AT+QLWOPEN=0\r\n");//����Ƶ������ע���������̷��� OK��֮��ȴ�Լ7�룬�ɹ����� CONNECT OK ,�ٵȴ�Լ4�룬����+QLWOBSERVE: 0,19,0,0
		if(!Wait_Str1_Str2_x_100ms(2,USART2_RX_BUF,USART_REC_LEN,&Flag_Usart2_Receive,1,1,"CONNECT OK","",100))//���ȴ�10��
		{
			USART1TxStr("�ɹ����ӷ�������\r\n");
		}
		if(!Wait_Str1_Str2_x_100ms(2,USART2_RX_BUF,USART_REC_LEN,&Flag_Usart2_Receive,1,1,"+QLWOBSERVE:","",70)) 
			n = 0;
		
	}CLR_Buf2();

	delay_ms(1000);

	n = 3;
	while(n--)
	{
		USART1TxStr("�������ݸ�ʽ...\r\n");
		n_str = (3-n)+'0';
		LCD_ShowString(8*1-3,16*10,&n_str);
		LCD_ShowString(8*2,16*10,"AT+QLWCFG=\"dataformat\",1,1");
		USART2TxStr("AT+QLWCFG=\"dataformat\",1,1\r\n");//�������ݸ�ʽΪʮ�������ַ�����ʽ�����ظ�ʽ��OK
		if(!Wait_Str1_Str2_x_100ms(2,USART2_RX_BUF,USART_REC_LEN,&Flag_Usart2_Receive,1,1,"OK","",50))
			n = 0;
		
	}CLR_Buf2();
	
	delay_ms(1000);

	n = 3;
	while(n--)
	{
		USART1TxStr("��������֡...\r\n");
		n_str = (3-n)+'0';
		LCD_ShowString(8*1-3,16*11,&n_str);
		LCD_ShowString(8*2,16*11,"AT+QLWDATASEND=19,0,1,14,02......");
		USART2TxStr("AT+QLWDATASEND=19,0,1,14,02000100070007636f6e6e656374,0x0100\r\n");//��������֡�����̷���OK���ȴ�Լ7�룬�ɹ�����SEND OK 

		if(2,USART2_RX_BUF,USART_REC_LEN,&Flag_Usart2_Receive,1,1,"SEND OK","",100)
		{
			n = 0;
			LCD_ShowString(8*2,16*12,"send ok!");
			delay_ms(1000);
			LCD_Clear(BLACK); //���� 
			
		}
		else
		{
			LCD_ShowString(8*2,16*12,"fail   !");
		}
		
	}CLR_Buf2();
}

char *my_strcat(char *str1, char *str2)  //ƴ���ַ���
{
    char *pt = str1;
    while(*str1!='\0') str1++;
    while(*str2!='\0') *str1++ = *str2++;
    *str1 = '\0';
    return pt;
}
void StringToHexstring(char *string,char *hexstring)   //�ַ���ת��ʮ��������ʽ���ַ��������ڷ��͸�ʮ�����ƽ��յ��豸����
	//string��Ҫת�����ַ��� ֱ������������ ����Test1[10]="123";����Test1 
//hexstring��ת����Ҫ��������顣���綨���һ�� Test2[]
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
	CLR_Buf1();	//�������1���ջ���
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
		if(Flag_Usart1_Receive//�������1�����ݽ���
		&&(!Count_Timer3_value_USART1_receive_timeout))//����������ճ�ʱ
		{
			Flag_Usart1_Receive = 0;
			if(Query(USART1_RX_BUF,str1,USART1_REC_LEN))
			{
				Flag_receive_right = 1;
				USART2TxStr(USART1_RX_BUF);
				USART2TxStr("������ȷ��\r\n");
			}
			else if(Query(USART1_RX_BUF,str2,USART1_REC_LEN))
			{
				Flag_receive_right = 1;
				USART2TxStr(USART1_RX_BUF);
				USART2TxStr("������ȷ��\r\n");
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
		return 1;//��ʱ����1
	else
		return 0;//��������0
}
bool Wait_Str1_Str2_x_100ms(
															char uartx,								//���ںţ�ֵ��1~5
															char* USARTx_RX_BUF,			//�������Ļ����׵�ַ
															unsigned int LEN,					//�������Ļ����ܳ���
															bool* add_Flag_Usart_x_Receive,//���ڽ��յ����ݵı�־�����ĵ�ַ
															char and_or,							//ֵ��1~2 ��1��ֻ�����Ƿ��������һ���ַ����� 2��ͬʱ�����Ƿ����2���ַ�����
															char str_NO,							//ֵ��1~2 ����and_orȡֵ1ʱ����ȡֵ����Ч��1��������һ���ַ����� 2�������ڶ����ַ�����
															char* str1,								//��һ���ַ������׵�ַ
															char* str2,								//�ڶ����ַ������׵�ַ
															unsigned char Value_Count_time_wait_ok_x_100ms//��ʱʱ�䣺x * 100ms
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
		if(*add_Flag_Usart_x_Receive//�������x�����ݽ���
		&&(!*add_Count_Timer3_value_USART_x_receive_timeout))//����������ճ�ʱ
		{
			*add_Flag_Usart_x_Receive = 0;
			if(and_or == 2)//���Ҫ�����������ַ���
			{
				if(Query(USARTx_RX_BUF,str1,LEN) && Query(USARTx_RX_BUF,str2,LEN))
				{
					Flag_receive_right = 1;
//					USART2TxStr(USARTx_RX_BUF);
//					USART2TxStr("������ȷ��\r\n");
				}
			}
			else if(and_or == 1)//���ֻҪ�����һ���ַ���
			{
				if(str_NO == 1)//���ֻҪ�������һ���ַ���
				{
					if(Query(USARTx_RX_BUF,str1,LEN))
					{
						Flag_receive_right = 1;
						//USART1TxStr(USARTx_RX_BUF);
						//USART1TxStr("������ȷ��\r\n");
					}
				}
				else if(str_NO == 2)//���ֻҪ������ڶ����ַ���
				{				
					if(Query(USARTx_RX_BUF,str2,LEN))
					{
						Flag_receive_right = 1;
						//USART1TxStr(USARTx_RX_BUF);
						//USART1TxStr("������ȷ��\r\n");
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
		return 1;//��ʱ����1
	else
		return 0;//��������0
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
			USART2TxStr("wifi�����ɹ���\r\n");
		}	
	}	
	if(!Count_time_wait_ok)
	{
		Flag_device_error = 1;
		USART2TxStr("Flag_device_error = 1\r\n");
	}
	delay_ms(100);
	if(Flag_device_error)
		return 1;//��ʱ����1
	else
		return 0;//��������0
}

unsigned char Query(char * src,char * des,unsigned int LEN)
	//��ѯ�������ް������ַ��������򷵻�1�����򷵻�0
{
	unsigned int y= 0,len= 0,n= 0;
	unsigned char Result = 0;
	char * i;
	i = des;
	for(; *i != '\0';i ++,len ++){}// �ж���Ҫ�����ַ��ĳ���
	for(y = 0; y < LEN - len;y ++)
		//��ʼ��⣬����Ϊ�ܳ��ȼ�ȥ�ַ����ȵ��ֽ���
	{
		for(n = 0;n < len;n ++)
		{
			if(*(src + y + n) == *(des + n))
				//��ʼ���˫���ĵ�һ���ֽڣ���������������1�����Ҽ������˫���ĵڶ����ֽ�
			{
				Result = 1;				
			}
			else
			{
				Result = 0;	//�������������0�������˳��˴�ѭ����
										//��ʼ�������ĵڶ����ֽں��ַ��ĵ�һ���ֽ�
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

void Array_CLR(char *src,char len) //�������
{	
	unsigned int y=0;	
	for( y= 0;y < len;y ++)
	{
		src[y] = '\0';
	}
} 




void Send_flag(int n){//���ͳɹ���־���������Ƿ�ɹ��ϴ���ƽ̨�ı�־��ʾ��LCD��ʾ����
	
	while(n--)
		{
			USART1TxStr(NB_Send_buf);

			USART2TxStr((char*)NB_Send_buf);//ͨ��NBģ�鷢������
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

void CLR(void){//������棬������3�Ľ��յ���������գ����Up_Data֮�е�����
	for(i = addr;i < 150;i ++)
		//Up_Data[i] = 0;	
	  Send_data_buf[i] = 0;	
		CLR_Buf3();
}

void CLR_Send_Buff(void)     //�������
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
		DealUpData(Send_data_buf,&NB_Send_buf[15],strlen(Send_data_buf),id);//������ת��ʮ�������ַ�����ʽ��ƴ�ӳ�ATָ��
		Send_flag(1);
	  USART1TxStr("send ok11");
		CLR_Send_Buff();//��ջ���
}

void BC26_IOTSenddata(char* data)//�Ϸ����ݣ��Ϸ������ݸ���Ӧ�Ĳ���й�ϵ���û���Ҫע����Ȼ���Ӧ���ݼ���
{ 
    printf(data);//�Ϸ�����,
    delay_ms(1500);
		delay_ms(1500);
    strx=strstr((const char*)RxBuffer,(const char*)"SEND OK");//��SEND OK
    while(strx==NULL)
    {
			  LCD_ShowString(8*2,16*11,"BC26_Send ERROR");
        strx=strstr((const char*)RxBuffer,(const char*)"SEND OK");//��SEND OK	
			  LCD_ShowString(8*2,16*11,"BC26_Send");
    }
		LCD_ShowString(8*2,16*11,"BC26_Send OK   ");
    RxCounter=0; 
}

