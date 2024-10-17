#include "sys.h"
#include "RC522.h"
#include "delay.h"
#include "string.h"
#include "usart.h"

#define EN 1
#define CN 0
unsigned char SelectedSnr[4];
 unsigned char SN[4]; //����

//������
int LOCK_PASSWD = 123456;

void print_info(unsigned char *p,int cnt)
{
  int i;
	for(i=0;i<cnt;i++)
	{
		printf("0x%X ",p[i]);
	}
	printf("\r\n");
}


/**********************************************
RCC522��������
RCC522��ʼ��
Ѱ��
if(Ѱ�� == yes) ����ײ
ѡ��
��֤��Ƭ
����Ƭ/д��Ƭ
������Ƭ����

u8   req_code; //Ѱ��ģʽ
u8 *pTagType;  //�����͡�


����˵��: req_code[IN]:Ѱ����ʽ
                0x52 = Ѱ��Ӧ�������з���14443A��׼�Ŀ�
                0x26 = Ѱδ��������״̬�Ŀ�

          			pTagType[OUT]����Ƭ���ʹ���
                0x4400 = Mifare_UltraLight
                0x0400 = Mifare_One(S50)
                0x0200 = Mifare_One(S70)
                0x0800 = Mifare_Pro(X)
                0x4403 = Mifare_DESFire
*/

unsigned char KEY[14][6]={
													{0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
													{0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
													{0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5},
													{0xB0, 0xB1, 0xB2, 0xB3, 0xB4, 0xB5},
													{0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF},
													{0x4D, 0x3A, 0x99, 0xC3, 0x51, 0xDD},
													{0x1A, 0x98, 0x2C, 0x7E, 0x45, 0x9A},
													{0x71, 0x4C, 0x5C, 0x88, 0x6E, 0x97},
													{0x58, 0x7E, 0xE5, 0xF9, 0x35, 0x0F},
													{0xA0, 0x47, 0x8C, 0xC3, 0x90, 0x91},
													{0x53, 0x3C, 0xB6, 0xC7, 0x23, 0xf6},
													{0x8F, 0xD0, 0xA4, 0xF2, 0x56, 0xE9},
													{0x66, 0x55, 0x44, 0x11, 0x22, 0x33},
													{0x66, 0x55, 0x44, 0x33, 0x22, 0x11}
};


int read_card()
{
	unsigned char CT[2];//������
	u8 status=1;
	status=RC522_PcdRequest(PICC_REQIDL ,CT);//(Ѱ��ģʽ��������),�ɹ�����0
	if(status==MI_OK)//Ѱ���ɹ�
	{
	  status=MI_ERR;
	  status=RC522_PcdAnticoll(SN);  //����ײ���ɹ�����0��SN�Ƕ������ŵĵ�ַ
		
		
		
		printf("������:");
		print_info(CT,2);//��ӡ����
		printf("����:");
	  print_info(SN,4);//��ӡ����
	}
	if(status==MI_OK)
	{
		status=MI_ERR;	
		status=RC522_PcdSelect(SN);	//ѡ����Ƭ��SN���������к�
	}
	  return status;
}


/*
���ܣ� �޸Ŀ�����
������
u8   auth_mode ����֤��������͡�����ΪPICC_AUTHENT1A��PICC_AUTHENT1B��
u8   addr      �������ŵĵ�ַ�����������ÿ�������ĵ�3���顣��һ�������Ƚ����⡣��
                 һ���3��7��11.....����
u8 *Src_Key    ��ԭ���� 
u8 *New_Key    ��������
u8 *pSnr       ������

�����ʽ��
u8 KEY[6]={0xff,0xff,0xff,0xff,0xff,0xff}; //��֤A����B����ĸ�ʽ
u8 MIMA_1[16]={88,88,88,88,88,88,0xff,0x07,0x80,0x29,88,88,88,88,88,88}; //�޸�������ĸ�ʽ(A���� ����λ  B���� )
*/
int card_passworld(u8 auth_mode,u8 addr,u8 *Src_Key,u8 *New_Key,u8 *pSnr)
{
		int status;
	 /*1. Ѱ��*/
    status=read_card(); 
	 /*2. ��֤������*/
		if(status==MI_OK)
		{
			status=RC522_PcdAuthState(auth_mode,addr,Src_Key,pSnr);   //��֤��Ƭ���� �ββ�������֤��ʽ�����ַ�����룬�����к�
	  }
	 /*3. д���ݵ���*/
		if(status==MI_OK)
		{
		   status=RC522_PcdWrite(addr,New_Key); //д���ݵ���addr�飬New_Keyд�������ֵ��
		}
		return status;
}


/*
���ܣ�д���ݵ�ָ����
������
u8   addr      �����ݴ�ŵĵ�ַ��ÿ��������0��1��2���Ǵ�����ݡ�3�Ǵ�����롣
                һ���0��1��2 ��4��5��6��8��9��10
����һ���ʽ��u8 SJ[16]={255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255}; //д��Ľ�

*/
u8 write_card_data(u8 *data)
{
	u8 KEY[6]={0xff,0xff,0xff,0xff,0xff,0xff}; //������-��ʼ����--�׿��ĳ�������--
	
	 int status=MI_ERR;
	 
	 /*1. Ѱ��*/
    status=read_card(); 
	 
	/*2. ��֤������*/
		if(status==MI_OK)
		{
			 status=RC522_PcdAuthState(PICC_AUTHENT1A,3,KEY,SN);   //��֤��Ƭ���� �ββ�������֤��ʽ�����ַ�����룬�����к�
		}
		
	 /*3. д���ݵ���*/
		if(status==MI_OK)
		{
		   status=RC522_PcdWrite(2,data); //д���ݵ���addr�飬data�������ֵ��
		}
		if(status==MI_OK)
		{
			print_info(data,16);
		}
		return status;
}


/*
���ܣ������ݵ�ָ����
������
u8   auth_mode ����֤��������͡�����ΪPICC_AUTHENT1A��PICC_AUTHENT1B��
u8   addr      �����ݴ�ŵĵ�ַ��ÿ��������0��1��2���Ǵ�����ݡ�3�Ǵ�����롣
               һ���0��1��2 ��4��5��6��8��9��10
u8 *Src_Key    ��ԭ���� 
u8 *data       ������������
u8 *pSnr       ������

����һ���ʽ��u8 SJ[16]={255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255}; //д��Ľ�

*/
u8 read_card_data()
{
	 u8 KEY[6]={0xff,0xff,0xff,0xff,0xff,0xff}; //������-��ʼ����--�׿��ĳ�������--
	 char status;
	 u8 data[16];
	 /*1. Ѱ��*/
	 printf("read card\n");
    status=read_card(); 
	 /*2. ��֤������*/
		if(status==MI_OK)
		{
			status=RC522_PcdAuthState(PICC_AUTHENT1A,3,KEY,SN);   //��֤��Ƭ���� �ββ�������֤��ʽ�����ַ�����룬�����к�
		}
	//printf("RC522_PcdAuthState=%s",status);
//USART1TxChar(status);
	 /*3. ��������*/
		if(status==MI_OK)
		{
		   status=RC522_PcdRead(2,data); //�ӵ�addr���������ֵ��
		}
		if(status==MI_OK)
		{
				print_info(data,16);
		}
		return status;
}


/*
�������ܣ���ֲ�ӿ�--SPIʱ���дһ���ֽ�
����������data:Ҫд�������
�� �� ֵ������������
*/
u8 RC522_SPI_ReadWriteOneByte(u8 tx_data)
{			  	 
	u8 rx_data=0;				 
  u8 i;
  for(i=0;i<8;i++)
	{
		RC522_SCLK=0;  
		if(tx_data&0x80){RC522_OUTPUT=1;}
		else {RC522_OUTPUT=0;}
		tx_data<<=1;	
		RC522_SCLK=1;
		rx_data<<=1;
		if(RC522_INPUT)rx_data|=0x01;
	}
	return rx_data; 
}


/*
�������ܣ���ʼ��RC522��IO��	  
*/

/*
RC522��Ƶģ���ⲿ�Ľӿ�:    
*1--SDA <----->PC6--Ƭѡ�� 
*2--SCK <----->PC7--ʱ����
*3--MOSI<----->PC8--���
*4--MISO<----->PB6--����
*5--����
*6--GND <----->GND
*7--RST <----->PC9--��λ��
*8--VCC <----->VCC
*/



void RC522_IO_Init(void)
{
	 GPIO_InitTypeDef  GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);        //ʹ��PC�˿�ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);        //ʹ��PB�˿�ʱ��

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;      //�������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;     //IO���ٶ�Ϊ50MHz
    GPIO_Init(GPIOC, &GPIO_InitStructure);
    GPIO_SetBits(GPIOC,GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9);  //����

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;      //��������
    GPIO_Init(GPIOB, &GPIO_InitStructure);
}	


/*
��������:ѡ����ȡ���洢������
�������:serNum ���뿨���к�
�� �� ֵ:�ɹ����ؿ�����
*/
u8 RC522_MFRC522_SelectTag(u8 *serNum) //��ȡ���洢������
{     
	u8 i;     
	u8 status;     
	u8 size;     
	u8 recvBits;     
	u8 buffer[9];
	     
	buffer[0]=PICC_ANTICOLL1;	  //��ײ��1     
	buffer[1]=0x70;
	buffer[6]=0x00;						     
	for(i=0;i<4;i++)					
	{
		buffer[i+2]=*(serNum+i);	//buffer[2]-buffer[5]Ϊ�����к�
		buffer[6]^=*(serNum+i);	  //��У����
	}
	
	RC522_CalulateCRC(buffer,7,&buffer[7]);	//buffer[7]-buffer[8]ΪRCRУ����
	RC522_ClearBitMask(Status2Reg,0x08);
	status=RC522_PcdComMF522(PCD_TRANSCEIVE,buffer,9,buffer,&recvBits);
	
	if((status==MI_OK)&&(recvBits==0x18))    
		size=buffer[0];     
	else    
		size=0;
	
	return size; 
}


/*
��ʱ���������뼶
*/
void RC522_Delay(u32 ns)
{
  u32 i;
  for(i=0;i<ns;i++)
  {
    __nop();
    __nop();
    __nop();
  }
}


/*
�������ܣ�RC522оƬ��ʼ��
*/
void RC522_Init(void)
{
  RC522_IO_Init();	//RC522��ʼ��
  RC522_PcdReset();  			//��λRC522 
  RC522_PcdAntennaOff();	//�ر�����
  delay_ms(2);  		  //��ʱ2����
  RC522_PcdAntennaOn();		//��������
  M500PcdConfigISOType('A'); //����RC632�Ĺ�����ʽ
}


/*
�������ܣ���λRC522
*/
void RC522_Reset(void)
{
  RC522_PcdReset();				//��λRC522
  RC522_PcdAntennaOff();	//�ر�����
  delay_ms(2);  		  //��ʱ2����
  RC522_PcdAntennaOn();		//��������  	
}     


/*
��    ��: Ѱ��
����˵��: req_code[IN]:Ѱ����ʽ
                0x52   = Ѱ��Ӧ�������з���14443A��׼�Ŀ�
                0x26   = Ѱδ��������״̬�Ŀ�
          			pTagType[OUT]:��Ƭ���ʹ���
                0x4400 = Mifare_UltraLight
                0x0400 = Mifare_One(S50)
                0x0200 = Mifare_One(S70)
                0x0800 = Mifare_Pro(X)
                0x4403 = Mifare_DESFire
�� �� ֵ: �ɹ�����MI_OK
*/
char RC522_PcdRequest(u8 req_code,u8 *pTagType)
{
	char status;  
	u8 unLen;
	u8 ucComMF522Buf[MAXRLEN];  	   // MAXRLEN  18

	RC522_ClearBitMask(Status2Reg,0x08);	//��RC522�Ĵ���λ,/������������
	RC522_WriteRawRC(BitFramingReg,0x07); //дRC632�Ĵ���
	RC522_SetBitMask(TxControlReg,0x03);  //��RC522�Ĵ���λ
 
	ucComMF522Buf[0]=req_code; 	    //Ѱ����ʽ
	
	status=RC522_PcdComMF522(PCD_TRANSCEIVE,ucComMF522Buf,1,ucComMF522Buf,&unLen); //ͨ��RC522��ISO14443��ͨѶ
	
	if((status==MI_OK)&&(unLen==0x10))
	{    
		*pTagType=ucComMF522Buf[0];
		*(pTagType+1)=ucComMF522Buf[1];
	}
	else
	{
	  status = MI_ERR;
	}  
	return status;
}


/*
��    ��: ����ײ
����˵��: pSnr[OUT]:��Ƭ���кţ�4�ֽ�
��    ��: �ɹ�����MI_OK
*/
char RC522_PcdAnticoll(u8 *pSnr)
{
    char status;
    u8 i,snr_check=0;
    u8 unLen;
    u8 ucComMF522Buf[MAXRLEN]; 
    
    RC522_ClearBitMask(Status2Reg,0x08);  //��RC522�Ĵ���λ 
    RC522_WriteRawRC(BitFramingReg,0x00); //д
    RC522_ClearBitMask(CollReg,0x80);     //��
 
    ucComMF522Buf[0]=PICC_ANTICOLL1;   //PICC_ANTICOLL1 = 0x93
    ucComMF522Buf[1]=0x20;
	
    status=RC522_PcdComMF522(PCD_TRANSCEIVE,ucComMF522Buf,2,ucComMF522Buf,&unLen); //0x0c,ͨ��RC522��ISO14443��ͨѶ
											 //PCD_TRANSCEIVE =���Ͳ���������
											 //2��д�뿨��������ֽڳ���
											 //ucComMF522Buf:������ݵĵ�ַ
											 //unLen���ӿ�����������ݳ���
    if(status==MI_OK)
    {
    	 for(i=0;i<4;i++)
			 {   
					 *(pSnr+i)=ucComMF522Buf[i];  //�Ѷ����Ŀ��Ÿ�ֵ��pSnr
					 snr_check^=ucComMF522Buf[i];
			 }
			 if(snr_check!=ucComMF522Buf[i])
			 {
					status = MI_ERR;
			 }
    }   
    RC522_SetBitMask(CollReg,0x80);
    return status;
}


/*
��    �ܣ�ѡ����Ƭ
����˵����pSnr[IN]:��Ƭ���кţ�4�ֽ�
��    �أ��ɹ�����MI_OK
*/
char RC522_PcdSelect(u8 *pSnr)
{
    char status;
    u8 i;
    u8 unLen;
    u8 ucComMF522Buf[MAXRLEN]; 
    
    ucComMF522Buf[0]=PICC_ANTICOLL1;
    ucComMF522Buf[1]=0x70;
    ucComMF522Buf[6]=0;
	
    for(i=0;i<4;i++)
    {
    	ucComMF522Buf[i+2]=*(pSnr+i);
    	ucComMF522Buf[6]^=*(pSnr+i);
    }
		
    RC522_CalulateCRC(ucComMF522Buf,7,&ucComMF522Buf[7]); //��MF522����CRC16������У������
    RC522_ClearBitMask(Status2Reg,0x08);	                //��RC522�Ĵ���λ
    status=RC522_PcdComMF522(PCD_TRANSCEIVE,ucComMF522Buf,9,ucComMF522Buf,&unLen);
    if((status==MI_OK)&&(unLen==0x18))status=MI_OK;
    else status=MI_ERR;
		
    return status;
}


/*
��    �ܣ���֤��Ƭ����
����˵����auth_mode[IN]: ������֤ģʽ
                 0x60 = ��֤A��Կ
                 0x61 = ��֤B��Կ 
          addr[IN]�����ַ
          pKey[IN]����������
          pSnr[IN]����Ƭ���кţ�4�ֽ�
��    �أ��ɹ�����MI_OK
*/               
char RC522_PcdAuthState(u8 auth_mode,u8 addr,u8 *pKey,u8 *pSnr)
{
    char status;
    u8 unLen;
    u8 ucComMF522Buf[MAXRLEN];  //MAXRLEN  18(����Ĵ�С)
	  
	  //��֤ģʽ+���ַ+��������+�����к�   
    ucComMF522Buf[0]=auth_mode;		
    ucComMF522Buf[1]=addr;				
    memcpy(&ucComMF522Buf[2],pKey,6); //����������
    memcpy(&ucComMF522Buf[8],pSnr,4); 
	 
    status=RC522_PcdComMF522(PCD_AUTHENT,ucComMF522Buf,12,ucComMF522Buf,&unLen);
    if((status!= MI_OK)||(!(RC522_ReadRawRC(Status2Reg)&0x08)))status = MI_ERR;
    return status;
}


/*
��    �ܣ���ȡM1��һ������
����˵���� 
					addr�����ַ
          p   �������Ŀ����ݣ�16�ֽ�
��    �أ��ɹ�����MI_OK
*/ 
char RC522_PcdRead(u8 addr,u8 *p)
{
    char status;
    u8 unLen;
    u8 i,ucComMF522Buf[MAXRLEN]; //18

    ucComMF522Buf[0]=PICC_READ;
    ucComMF522Buf[1]=addr;
    RC522_CalulateCRC(ucComMF522Buf,2,&ucComMF522Buf[2]);
    status=RC522_PcdComMF522(PCD_TRANSCEIVE,ucComMF522Buf,4,ucComMF522Buf,&unLen);//ͨ��RC522��ISO14443��ͨѶ
    if((status==MI_OK&&(unLen==0x90)))
    {
        for(i=0;i<16;i++)
				{
						*(p +i)=ucComMF522Buf[i];
				}
    }
    else
    {   
			status=MI_ERR;
		}
    return status;
}


/*
��    �ܣ�д���ݵ�M1��ָ����
����˵����addr�����ַ
          p   �����д������ݣ�16�ֽ�
��    �أ��ɹ�����MI_OK
*/                  
char RC522_PcdWrite(u8 addr,u8 *p)
{
    char status;
    u8 unLen;
    u8 i,ucComMF522Buf[MAXRLEN]; 
    
    ucComMF522Buf[0]=PICC_WRITE;// 0xA0 //д��
    ucComMF522Buf[1]=addr;      //���ַ
    RC522_CalulateCRC(ucComMF522Buf,2,&ucComMF522Buf[2]);
 
    status=RC522_PcdComMF522(PCD_TRANSCEIVE,ucComMF522Buf,4,ucComMF522Buf,&unLen);

    if((status!= MI_OK)||(unLen != 4)||((ucComMF522Buf[0]&0x0F)!=0x0A))
    {
				status = MI_ERR;
		}
		
    if(status==MI_OK)
    {
        for(i=0;i<16;i++)//��FIFOд16Byte���� 
        {    
        	ucComMF522Buf[i]=*(p +i);   
        }
        RC522_CalulateCRC(ucComMF522Buf,16,&ucComMF522Buf[16]);
        status = RC522_PcdComMF522(PCD_TRANSCEIVE,ucComMF522Buf,18,ucComMF522Buf,&unLen);
        if((status != MI_OK)||(unLen != 4)||((ucComMF522Buf[0]&0x0F)!=0x0A))
        {   
					status = MI_ERR;   
				}
    }
    return status;
}


/*
��    �ܣ����Ƭ��������״̬
��    �أ��ɹ�����MI_OK
*/
char RC522_PcdHalt(void)
{
    u8 status;
    u8 unLen;
    u8 ucComMF522Buf[MAXRLEN]; //MAXRLEN==18
	  status=status;
    ucComMF522Buf[0]=PICC_HALT;
    ucComMF522Buf[1]=0;
    RC522_CalulateCRC(ucComMF522Buf,2,&ucComMF522Buf[2]);
    status=RC522_PcdComMF522(PCD_TRANSCEIVE,ucComMF522Buf,4,ucComMF522Buf,&unLen);
    return MI_OK;
}


/*
��    �ܣ���MF522����CRC16����
��    ����
				*pIn ��Ҫ����CRC������
				len��-���ݳ���
				*pOut�������CRC���
*/
void RC522_CalulateCRC(u8 *pIn ,u8 len,u8 *pOut )
{
    u8 i,n;
    RC522_ClearBitMask(DivIrqReg,0x04);  //CRCIrq = 0  
    RC522_WriteRawRC(CommandReg,PCD_IDLE);
    RC522_SetBitMask(FIFOLevelReg,0x80); //��FIFOָ��
    
	  //��FIFO��д������  
		for(i=0;i<len;i++)
    {  
			RC522_WriteRawRC(FIFODataReg,*(pIn +i));  //��ʼRCR����
		}
		
		RC522_WriteRawRC(CommandReg,PCD_CALCCRC);   //�ȴ�CRC������� 
		i=0xFF;
    do 
    {
        n=RC522_ReadRawRC(DivIrqReg);
        i--;
    }
    while((i!=0)&&!(n&0x04));//CRCIrq = 1
	  
		//��ȡCRC������ 
		pOut[0]=RC522_ReadRawRC(CRCResultRegL);
    pOut[1]=RC522_ReadRawRC(CRCResultRegM);
}


/*
��    �ܣ���λRC522
��    �أ��ɹ�����MI_OK
*/
char RC522_PcdReset(void)
{
	  RC522_RST=1;   //PF1д1
    RC522_Delay(10);
	  RC522_RST=0;   //PF1��0
    RC522_Delay(10);
	  RC522_RST=1;	 //PF1д1
    RC522_Delay(10);
	
		// PCD_RESETPHASEλRC522�еĸ�λ�֣�CommandReg��ַ��������������ֹͣ�����ִ�� 
    // PCD_RESETPHASE = 0x0F 
    RC522_WriteRawRC(CommandReg,PCD_RESETPHASE);  //дRC632�Ĵ�������λ
	  RC522_WriteRawRC(CommandReg,PCD_RESETPHASE);	//дRC632�Ĵ�������λ
    RC522_Delay(10);
    
	  // ���巢�ͺͽ��յĳ���ģʽ
    RC522_WriteRawRC(ModeReg,0x3D);             //��Mifare��ͨѶ��CRC��ʼֵ0x6363
    // ��װ��ֵλ30
		RC522_WriteRawRC(TReloadRegL,30);           //дRC632�Ĵ���   
    RC522_WriteRawRC(TReloadRegH,0);
		// �����ڲ���ʱ��ģʽ
    RC522_WriteRawRC(TModeReg,0x8D);
		// ��Ƶϵ����62
    RC522_WriteRawRC(TPrescalerReg,0x3E);
		// ��װ��ֵ 64
	  RC522_WriteRawRC(TxAutoReg,0x40);//����Ҫ
    return MI_OK;
}


/*
�������ܣ�����RC632�Ĺ�����ʽ 
*/
char M500PcdConfigISOType(u8 type)
{
   if(type=='A')                        //ISO14443_A
   { 
		 RC522_ClearBitMask(Status2Reg,0x08);     //��RC522�Ĵ���λ
		 RC522_WriteRawRC(ModeReg,0x3D);          //3F//CRC��ʼֵ0x6363
		 RC522_WriteRawRC(RxSelReg,0x86);         //84
		 RC522_WriteRawRC(RFCfgReg,0x7F);         //4F  //�������ĸ�Ӧ����//RxGain = 48dB���ڿ���Ӧ����  
		 RC522_WriteRawRC(TReloadRegL,30);        //tmoLength);// TReloadVal = 'h6a =tmoLength(dec) 
	   RC522_WriteRawRC(TReloadRegH,0);
		 RC522_WriteRawRC(TModeReg,0x8D);
	   RC522_WriteRawRC(TPrescalerReg,0x3E);
	   RC522_Delay(1000);
     RC522_PcdAntennaOn();		//�������� 
   }
   else return 1;       //ʧ�ܣ�����1
   return MI_OK;				//�ɹ�����0
}


/*
��    �ܣ���RC632�Ĵ���
����˵����Address[IN]:�Ĵ�����ַ
��    �أ�������ֵ
*/
u8 RC522_ReadRawRC(u8 Address)
{
    u8 ucAddr;
    u8 ucResult=0;		
		RC522_CS=0;						//Ƭѡѡ��RC522
		// ��ȡ��һλ��1�����Ի���0x80
    ucAddr=((Address<<1)&0x7E)|0x80;
		RC522_SPI_ReadWriteOneByte(ucAddr);		  //��������
		ucResult=RC522_SPI_ReadWriteOneByte(0); //��ȡRC522���ص�����
		RC522_CS=1;						   //�ͷ�Ƭѡ��(PF0)
		return ucResult;         //���ض���������
}


/*
��    �ܣ�дRC632�Ĵ���
����˵����Address[IN]:�Ĵ�����ַ
          value[IN] :д���ֵ
*/
void RC522_WriteRawRC(u8 Address,u8 value)
{  
  u8 ucAddr;
	RC522_CS=0; //PF0д 0 (SDA)(SPI1Ƭѡ�ߣ��͵�ƽ��Ч)
	// ��������Ϊ��ȷ����ַ������0x7e��ȡ1��6λ
  ucAddr=((Address<<1)&0x7E); 
	RC522_SPI_ReadWriteOneByte(ucAddr); //SPI1����һ���ֽ�
	RC522_SPI_ReadWriteOneByte(value);  //SPI1����һ���ֽ�
	RC522_CS=1;										      //PF1д1(SDA)(SPI1Ƭѡ��)
}


/*
��    �ܣ���RC522�Ĵ���λ
����˵����reg[IN]:�Ĵ�����ַ
          mask[IN]:��λֵ
*/
void RC522_SetBitMask(u8 reg,u8 mask)  
{
    char tmp=0x0;
    tmp=RC522_ReadRawRC(reg);					//��RC632�Ĵ���
    RC522_WriteRawRC(reg,tmp|mask);   //дRC632�Ĵ���
}


/*
��    �ܣ���RC522�Ĵ���λ
����˵����reg[IN]:�Ĵ�����ַ
         mask[IN]:��λֵ
*/
void RC522_ClearBitMask(u8 reg,u8 mask)  
{
    char tmp=0x0;
    tmp=RC522_ReadRawRC(reg);        //��RC632�Ĵ���
    RC522_WriteRawRC(reg,tmp&~mask); // clear bit mask
} 


/*
��    �ܣ�ͨ��RC522��ISO14443��ͨѶ
����˵����Command[IN]:RC522������
          pIn [IN]:ͨ��RC522���͵���Ƭ������
          InLenByte[IN]:�������ݵ��ֽڳ���
          pOut [OUT]:���յ��Ŀ�Ƭ��������
          *pOutLenBit[OUT]:�������ݵ�λ����
*/
char RC522_PcdComMF522(u8 Command,u8 *pIn,u8 InLenByte,u8 *pOut,u8 *pOutLenBit)
{
    char status=MI_ERR;
    u8 irqEn=0x00;
    u8 waitFor=0x00;
    u8 lastBits;
    u8 n;
    u16 i;
	
    switch(Command)
    {
			case PCD_AUTHENT:    //��֤��Կ
					 irqEn=0x12;
					 waitFor=0x10;
					 break;
			case PCD_TRANSCEIVE: //���Ͳ���������
					 irqEn=0x77;
					 waitFor=0x30;
					 break;
			default:
					 break;
    }
    RC522_WriteRawRC(ComIEnReg,irqEn|0x80);	
    RC522_ClearBitMask(ComIrqReg,0x80);			//�������ж�λ
    RC522_WriteRawRC(CommandReg,PCD_IDLE);	
    RC522_SetBitMask(FIFOLevelReg,0x80);	 	//��FIFO����
    
    for(i=0;i<InLenByte;i++)
    {   
				RC522_WriteRawRC(FIFODataReg,pIn[i]);
		}
		
		RC522_WriteRawRC(CommandReg,Command);	 
		if(Command==PCD_TRANSCEIVE)
		{  
			RC522_SetBitMask(BitFramingReg,0x80);	 //StartSend��λ�������ݷ��� ��λ���շ�����ʹ��ʱ����Ч
		}
    
		
    //i = 600;//����ʱ��Ƶ�ʵ���������M1�����ȴ�ʱ��25ms
		  i=2000;
			do 
			{
				n=RC522_ReadRawRC(ComIrqReg); //��ѯ�¼��ж�
				i--;
			}
			while((i!=0)&&!(n&0x01)&&!(n&waitFor));
				
			RC522_ClearBitMask(BitFramingReg,0x80);
			if(i!=0)
			{    
        if(!(RC522_ReadRawRC(ErrorReg)&0x1B))
        {
            status=MI_OK;
            if(n&irqEn&0x01)
            {
							status=MI_NOTAGERR;
						}
            if(Command==PCD_TRANSCEIVE)
            {
               	n=RC522_ReadRawRC(FIFOLevelReg);
              	lastBits=RC522_ReadRawRC(ControlReg)&0x07;
                if(lastBits)
                {
									*pOutLenBit=(n-1)*8+lastBits;
								}
                else
                {   
									*pOutLenBit=n*8;   
								}
								
                if(n==0)n=1;
                if(n>MAXRLEN)n=MAXRLEN;
                for(i=0; i<n; i++)
                {   
									pOut[i]=RC522_ReadRawRC(FIFODataReg);    
								}
            }
        }
        else
        {   
					status=MI_ERR;   
				}
    }
    RC522_SetBitMask(ControlReg,0x80);// stop timer now
    RC522_WriteRawRC(CommandReg,PCD_IDLE); 
    return status;
}


/*
�������ܣ���������  
��    ����ÿ��������ر����շ���֮��Ӧ������1ms�ļ��
*/
void RC522_PcdAntennaOn(void)
{
    u8 i;
    i=RC522_ReadRawRC(TxControlReg);
    if(!(i&0x03))
    {
        RC522_SetBitMask(TxControlReg,0x03);
    }
}


/*
�������ܣ��ر�����  
��    ����ÿ��������ر����շ���֮��Ӧ������1ms�ļ��
*/
void RC522_PcdAntennaOff(void)
{
	RC522_ClearBitMask(TxControlReg,0x03); //��RC522�Ĵ���λ
}



 
//				
//					notarize = 1 ����
//					
		
 
//u8  DefaultKey[6] ={0xff,0xff,0xff,0xff,0xff,0xff}; //Ĭ������ 	

 
void  notarize_type1(){
		u8 status;
		u8 section=0;
		u8 block = 0;
		unsigned char block_value[16];
u8 KEY[6]={0xff,0xff,0xff,0xff,0xff,0xff}; //������-��ʼ����--�׿��ĳ�������--
//u8 KEY[6]={0x00,0x00,0x00,0x00,0x00,0x0}; //������-��ʼ����--�׿��ĳ�������--
		u8 i=0;
		status = read_card();
			if(!status){
				if(EN)printf("function NO1 Read the card ...\r\n");
				if(CN)printf("����1 ��ȡ��Ƭ \r\n");
				//if(OLED)GUI_ShowString(48,0,"NO_1",16,1);
						for( section = 0 ; section <16 ; section++ ){
								//printf("section:%d , section1:%d \r\n ",section,(section*4+3));
                status=RC522_PcdAuthState(PICC_AUTHENT1A,(section*4+3),KEY,SN);   //��֤��Ƭ���� �ββ�������֤��ʽ�����ַ�����룬�����к�

							if(!status)
								{		
									for(block = 0; block< 4 ; block++){
										status = RC522_PcdRead((section*4+block), block_value);  // ��������ȡ1����0�����ݵ�buf[0]-buf[16]
										//status = RC522_PcdRead(2,block_value);  // ��������ȡ1����0�����ݵ�buf[0]-buf[16
										
										if(EN)printf("SQ:%d , QK:%d     ",section,block);
											if(EN)printf("passA	");
											for (i = 0 ; i<6; i++)
											{
											if(EN)printf("%X ",block_value[i]);
											}
											if(EN)printf("		Value	");
											for (i = 6; i<10; i++)
											{
											if(EN)printf("%X ",block_value[i]);
											}
											if(EN)printf("		passB	");
											for (i = 10; i<16; i++)
											{    
											if(EN)printf("%X ",block_value[i]);
											}
											if(EN)printf("\r\n");
									}
								}else {
									if(EN)printf("wrong password \r\n");
									if(CN)printf("������� \r\n");
									//if(OLED)GUI_ShowString(0,16,"5",16,1);
								}
							}
							if(EN)printf("\r\n");
							if(EN)printf("\r\n");
							if(EN)printf("\r\n");
				
				
				
			}else{
				if(EN)printf("Looking for failure \r\n");
				if(CN)printf("��Ƭδ�ҵ� \r\n");
				//if(OLED)GUI_ShowString(0,16,"4",16,1);
			}
	}

	 
//				
//					notarize = 3 �����������
//					
		
		void  notarize_type3(){
		u8 status;
		u8 section=0;
		u8 block_num=0;
		u8 KEY_num = 0 ;
		unsigned char block_value[16];
	
		u8 i=0;
		status = read_card();
			if(!status){
				if(EN)printf("function NO3 Password test ...\r\n");
				if(CN)printf("����3 ����������� \r\n");
				//if(OLED)GUI_ShowString(48,0,"NO_3",16,1);
						for( section = 0 ; section <16 ; section++ ){
					for( KEY_num =0 ; KEY_num < 13 ; KEY_num++){
								status = read_card();
						if(!status){
								//printf("section:%d  KEY:%d %d %d %d %d %d   ",section,KEY[KEY_num][0],KEY[KEY_num][1],KEY[KEY_num][2],KEY[KEY_num][3],KEY[KEY_num][4],KEY[KEY_num][5]);
								status = RC522_PcdAuthState(PICC_AUTHENT1A, (section*4+3), KEY[KEY_num], SN);// У��1�������룬����λ��ÿһ������3��
							if(!status)
								{
									status = 1;
									//for(block_num = 0; block_num< 4 ; block_num++){
										
										status = RC522_PcdRead((section*4+3), block_value);  // ��������ȡ1����0�����ݵ�buf[0]-buf[16] 
										if(EN)printf("SQ:%d , QK:%d  KEY:%X %X %X %X %X %X   ",section,3,KEY[KEY_num][0],KEY[KEY_num][1],KEY[KEY_num][2],KEY[KEY_num][3],KEY[KEY_num][4],KEY[KEY_num][5]);
											if(EN)printf("passA	");
											for (i = 0 ; i<6; i++)
											{ 
											if(EN)printf("%X ",block_value[i]);
											}
											if(EN)printf("		Value	");
											for (i = 6; i<10; i++)
											{    
											if(EN)printf("%X ",block_value[i]);
											}
											if(EN)printf("		passB	");
											for (i = 10; i<16; i++)
											{    
											if(EN)printf("%X ",block_value[i]);
											}
											if(EN)printf("\r\n");
											
									//}	
									
									
									
								}else {
									      if(EN)printf("wrong password \r\n");
								}
							}
							status = 1;
						}
					}
							if(EN)printf("\r\n");
							if(EN)printf("\r\n");
							if(EN)printf("\r\n");
						
			}else{
				if(EN)printf("Looking for failure \r\n");
				if(CN)printf("��Ƭδ�ҵ� \r\n");
				//if(OLED)GUI_ShowString(0,16,"4",16,1);
			}
	}
	