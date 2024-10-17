#include "key.h"
#include "stm32f10x.h"
#include "delay.h"
#include "gpio.h"
#include "lcd.h"
#include "nbiot.h"

int mode_flag=0;
int  threshold_total=0;
extern char charthreshold_total=0;
u8 NBiniFlag=0;
u8 upDataFlag=0;
  static int threshold[4]={0,0,0,0};
char charthreshold[5]={0,0,0,0};
int r_flag=0;

extern unsigned char NB_Send_buf[355];
extern char Send_data_buf[150];

extern char CO2_up[13];
extern char Datag_up[13];

void key_init(){//��ʼ������
	
	GPIO_InitTypeDef GPIO_InitStruture;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);//��PDʱ��
	
	GPIO_InitStruture.GPIO_Mode = GPIO_Mode_IPU;//��������
	GPIO_InitStruture.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7| GPIO_Pin_8| GPIO_Pin_11| GPIO_Pin_12; //���ö˿�
	GPIO_Init(GPIOA,&GPIO_InitStruture);//��ʼ��POID
	
}

/*void key_scan(void)
{
	static u8 flag = 1;//֮ǰû�а�������
	if(flag==1&&(key1==0||key2==0||key3==0||key4==0||key5==0))//֮ǰû�а��������ҵ�ǰ��key0����key1����ʱ
	{
		flag = 0;//����key0����key1���£�flag��0����Ϊ�а������£�
		delay_ms(10);//��ʱ��������	
		if(key1==0){
			//plus();//��һ
			G_LED_ON;
		}else if(key2==1){
			//reudce();//��һ
			G_LED_OFF;
		}
		else if(key3==0){
			//reudce(); //��λ
		}
		else if(key4==0){
			//reudce();  //ȷ��
		}
	}
	else if(key1==1&&key2==1&&key3==1&&key4==1&&key5==1) flag = 1;//û�а�������ʱ��flag��1
	
	
}*/

void key_scan_task(int key_vaule)
{
		
}
	


//����������
//���ذ���ֵ
//mode:0,��֧��������;1,֧��������;

u8 KEY_Scan(u8 mode)
{	 
	static u8 flag = 1;//֮ǰû�а�������
	//static u8 key_up=1;//�������ɿ���־
	if(mode)flag=1;  //֧������		  
	if(flag==1&&(key1==0||key2==0||key3==0||key4==0||key5==0))
	{
		delay_ms(10);//ȥ���� 
		flag=0;
		if(key1==0)return keyHome;
		else if(key2==0)return keyInc;
		else if(key3==0)return keyDec;
		else if(key4==0)return keyMode;
		else if(key5==0)return keyEnter;
	}
	else if(key1==1&&key2==1&&key3==1&&key4==1&&key5==1)flag=1; 	    
 	return 0;// �ް�������
}


void Key_Show(void)
{
	static u8 menu=0; //һ���˵���ʼ��
	static u8 incDecFlag=0;    //����һ���˵��Ͷ����˵���������
	static u8 home_flag=0;     //���˵���־λ
	static u8 modeFlag=0;    //λ���л���־λ
	static u8 weishuPointerKey=0;//λ��ָ��
	static u8 KeyIndex=0;//�����ٶ�ָ�룬ÿһ������һ�������ٶȣ�ÿ������Ϊ1

	u8 keyTemp;                //��ʱ���水��ֵ

	
  
		
	keyTemp=KEY_Scan(0);       //��ȡ����ֵ 
	if(keyTemp==keyHome||home_flag==1)  //���ư��ϵİ���  Home Inc Dec Mode Enter
	{
		
		 TIM_Cmd(TIM3, DISABLE);  //ʧ��TIMx	 DISABLE
		 LCD_Clear(BLACK); //���� 
	   LCD_Fill(40+16,40+16*0,40+16*2,40+16*1,YELLOW);  //LCD��ʾ��ɫ����
		 LCD_Show_Chinese16x16(40+16*2,40+16*0,"��ֵ�趨");
		 LCD_Fill(40+16,40+16*2,40+16*2,40+16*3,YELLOW);  //LCD��ʾ��ɫ����
		 LCD_Show_Chinese16x16(40+16*2,40+16*2,"�ֶ�ģʽ");
		 LCD_Fill(40+16,40+16*4,40+16*2,40+16*5,YELLOW);  //LCD��ʾ��ɫ����
		 LCD_Show_Chinese16x16(40+16*2,40+16*4,"��ʼ�ɼ�");
		 LCD_Fill(40+16,40+16*6,40+16*2,40+16*7,YELLOW);  //LCD��ʾ��ɫ����
		 LCD_Show_Chinese16x16(40+16*2,40+16*6,"�ϴ�����");
	
		 
		 POINT_COLOR=RED;		//�ʻ�Ϊ��ɫ	
		 LCD_Show_Chinese16x16(280-16*3,40,"����˵��");
		 POINT_COLOR=GREEN;		//�ʻ�Ϊ��ɫ	
		 LCD_ShowString(280-16*3,40+16*1,"HOME");
		 LCD_ShowString(280-16*3-8,40+16*1,"*");
		 LCD_Show_Chinese16x16(280-16*3,40+16*2,"ģʽ�л�");
		 LCD_ShowString(280-16*3-8,40+16*2,"*");
		 LCD_ShowString(280-16*3,40+16*3,"----");
		 LCD_ShowString(280-16*3-8,40+16*3,"*");
		 LCD_ShowString(280-16*3,40+16*4,"----");
		 LCD_ShowString(280-16*3-8,40+16*4,"*");
		 LCD_Show_Chinese16x16(280-16*3,40+16*5,"ȷ��");
		 LCD_ShowString(280-16*3-8,40+16*5,"*");
	
		
		
		  incDecFlag=0;
		  incDecFlag=0;
		  modeFlag=0;
		  home_flag=0;
		  Y_LED_ON;
			upDataFlag=0;
			r_flag=0;
		  menu=0;
		  
		  
		  
	}
	if(keyTemp==keyInc&&incDecFlag==0)
	{
		
		menu++;//��һ���˵���ѡ��
		if(menu>4)
		{
			menu=1;
		}
		if(menu == 1)	 //��Ϊ1��ѡ���һ��
		{
      
			LCD_ShowString(40,40+16*0,"1");
			LCD_ShowString(40,40+16*2," ");
			LCD_ShowString(40,40+16*4," ");
			LCD_ShowString(40,40+16*6," ");
	
			
		}
		if(menu == 2)	  //��Ϊ2��ѡ��ڶ���
		{
			LCD_ShowString(40,40+16*0," ");
			LCD_ShowString(40,40+16*2,"1");
			LCD_ShowString(40,40+16*4," ");
			LCD_ShowString(40,40+16*6," ");
			
		}
	  if(menu == 3)	  //��Ϊ3��ѡ�������
		{
			LCD_ShowString(40,40+16*0," ");
			LCD_ShowString(40,40+16*2," ");
			LCD_ShowString(40,40+16*4,"1");
			LCD_ShowString(40,40+16*6," ");
		}
    if(menu == 4)	  //��Ϊ4��ѡ�������
		{
			LCD_ShowString(40,40+16*0," ");
			LCD_ShowString(40,40+16*2," ");
			LCD_ShowString(40,40+16*4," ");
			LCD_ShowString(40,40+16*6,"1");
		}
		if(menu == 5)	  //��Ϊ5��ѡ�������
		{
			
		}
		if(menu == 6)	  //��Ϊ6��ѡ�������
		{
			
		}
	}
	
	if(keyTemp == keyEnter)	//ȷ�ϼ����� 
	{
		if(menu == 1)		      //������ֵ
		{
			incDecFlag=1;    //����һ���˵��Ͷ����˵���������
		 LCD_Clear(BLACK); //���� 
			LCD_Show_Chinese16x16(40+16*2,40+16*0,"��ֵ�趨");
			LCD_ShowString(40+16*2+4*16,40+16*0,"----");
			
			POINT_COLOR=RED;		//�ʻ�Ϊ��ɫ	
		 LCD_Show_Chinese16x16(280-16*3,40,"����˵��");
		 POINT_COLOR=GREEN;		//�ʻ�Ϊ��ɫ	
		 LCD_ShowString(280-16*3,40+16*1,"HOME");
		 LCD_ShowString(280-16*3-8,40+16*1,"*");
		 LCD_Show_Chinese16x16(280-16*3,40+16*2,"��");
		 LCD_ShowString(280-16*3-8,40+16*2,"*");
		 LCD_Show_Chinese16x16(280-16*3,40+16*3,"��");
		 LCD_ShowString(280-16*3-8,40+16*3,"*");
		 LCD_Show_Chinese16x16(280-16*3,40+16*4,"λ���л�");
		 LCD_ShowString(280-16*3-8,40+16*4,"*");
		 LCD_Show_Chinese16x16(280-16*3,40+16*5,"ȷ��");
		 LCD_ShowString(280-16*3-8,40+16*5,"*");
	
			
		  
		}
	}	
	
	if(keyTemp == keyEnter)	
	{
		
		if(menu == 2)		  //
		{
			
		  LCD_Clear(BLACK); //���� 
			
			
			
		
		}
	}	
	
	if(keyTemp == keyEnter)	
	{
		if(menu == 3)		  //�˵��ĵ����ʼ�ɼ�����
		{
			LCD_Clear(BLACK); //���� 
			basic_show();
			LCD_Show_Chinese16x16(20,220,"��ֵ");
			LCD_ShowString(20+16*2,220,charthreshold);
			TIM_Cmd(TIM3, ENABLE);  //ʹ��TIMx	 DISABLE
			
		}
	}
	
	if(keyTemp == keyEnter)	
	{
		if(menu == 4)		  //��ʼ�ϴ�����
		{
			
			LCD_Clear(BLACK); //���� 
			TIM_Cmd(TIM3, ENABLE);  //ʹ��TIMx	 DISABLE
			LCD_Show_Chinese16x16(20,220,"��ֵ");
			LCD_ShowString(20+16*2,220,charthreshold);
			upDataFlag=1;
			
			
			
			
		 
		}
	}

	if(keyTemp == keyEnter)	
	{
		if(menu == 5)		  //δ����
		{
		
		  LCD_Clear(BLACK); //���� 
		 
		}
	}	

	if(keyTemp == keyEnter)	
	{
		if(menu == 6)		  //δ����
		{

			LCD_Clear(BLACK); //���� 
      
		}
	}		
	
	if(menu==1&&incDecFlag==1)         //λ���л�
	{
		 LCD_DrawRectangle(0, 0, 320, 240);	//�����ο�	
	   LCD_ShowString(280-5*8,220,"30248");
	   LCD_Show_Chinese16x16(280,220,"����");
		if(keyTemp == keyMode)
		{
			
			
			modeFlag=1;
			weishuPointerKey++;
			if(weishuPointerKey>3) weishuPointerKey=0;
			LCD_ShowString(40+16*2+4*16+8*weishuPointerKey,40+16*0+16,".");
		}
		
	}
	
	if(menu==2&&incDecFlag==1)         
	{
		
		if(keyTemp==keyInc)
			{
			    keyTemp=KEY_Scan(1);
				  while(keyTemp==keyInc)
			{
				keyTemp=KEY_Scan(1);
				G_LED_ON;			
			}
				
			
			}
      	
			if(keyTemp==keyDec)
			{
			    r_flag++;
				 
				  
			}
			if(r_flag==1)
			{
			     R_LED_ON;
				  delay_ms(500);
				  R_LED_OFF;
				  delay_ms(500);
				  R_LED_ON;
				  
				 
				
			}
			if (r_flag>1)
					{
					   R_LED_OFF;
						 r_flag=0;
					}
			
			if(keyTemp==keyMode)
				
			{
			
			
			}
			G_LED_OFF;	
	}
	
	if(menu==6&&incDecFlag==1)
	{
		
	}	
	if((menu==1&&incDecFlag==1&&modeFlag==1&&keyTemp == keyInc)||(menu==1&&incDecFlag==1&&modeFlag==1&&keyTemp == keyDec))         //λ���Ӽ�
	{
		
	if(keyTemp == keyInc)  //��
		        {
              //KeyIndex++;
							threshold[weishuPointerKey]++;
							if(threshold[weishuPointerKey]>9) threshold[weishuPointerKey]=0;
							
					    
						}
					
	if(keyTemp == keyDec)  //��
		        {
              //KeyIndex++;
							threshold[weishuPointerKey]--;
							if(threshold[weishuPointerKey]<0) threshold[weishuPointerKey]=9;
							
					    
						}
						charthreshold[weishuPointerKey]=(char)(threshold[weishuPointerKey]+'0');
						LCD_ShowString(40+16*2+4*16+8*weishuPointerKey,40+16*0,&charthreshold[weishuPointerKey]);
					
	
	}
	
	if(menu==1&&incDecFlag==1&&modeFlag==1&&keyTemp == keyEnter)         //��������ֵ����ȷ����
	{
		  threshold_total=threshold[0]*1000+threshold[0]*100+threshold[0]*10+threshold[0]*1;
		  menu=0;
		  incDecFlag=0;
		modeFlag=0;
		home_flag=1;
		Y_LED_ON;
		
		
	}
	
	
}