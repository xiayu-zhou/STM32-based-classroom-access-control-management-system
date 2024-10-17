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

void key_init(){//初始化按键
	
	GPIO_InitTypeDef GPIO_InitStruture;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);//打开PD时钟
	
	GPIO_InitStruture.GPIO_Mode = GPIO_Mode_IPU;//上拉输入
	GPIO_InitStruture.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7| GPIO_Pin_8| GPIO_Pin_11| GPIO_Pin_12; //设置端口
	GPIO_Init(GPIOA,&GPIO_InitStruture);//初始化POID
	
}

/*void key_scan(void)
{
	static u8 flag = 1;//之前没有按键按下
	if(flag==1&&(key1==0||key2==0||key3==0||key4==0||key5==0))//之前没有按键按下且当前有key0或者key1按下时
	{
		flag = 0;//按键key0或者key1按下，flag置0（即为有按键按下）
		delay_ms(10);//延时按键消抖	
		if(key1==0){
			//plus();//加一
			G_LED_ON;
		}else if(key2==1){
			//reudce();//减一
			G_LED_OFF;
		}
		else if(key3==0){
			//reudce(); //移位
		}
		else if(key4==0){
			//reudce();  //确定
		}
	}
	else if(key1==1&&key2==1&&key3==1&&key4==1&&key5==1) flag = 1;//没有按键按下时，flag置1
	
	
}*/

void key_scan_task(int key_vaule)
{
		
}
	


//按键处理函数
//返回按键值
//mode:0,不支持连续按;1,支持连续按;

u8 KEY_Scan(u8 mode)
{	 
	static u8 flag = 1;//之前没有按键按下
	//static u8 key_up=1;//按键按松开标志
	if(mode)flag=1;  //支持连按		  
	if(flag==1&&(key1==0||key2==0||key3==0||key4==0||key5==0))
	{
		delay_ms(10);//去抖动 
		flag=0;
		if(key1==0)return keyHome;
		else if(key2==0)return keyInc;
		else if(key3==0)return keyDec;
		else if(key4==0)return keyMode;
		else if(key5==0)return keyEnter;
	}
	else if(key1==1&&key2==1&&key3==1&&key4==1&&key5==1)flag=1; 	    
 	return 0;// 无按键按下
}


void Key_Show(void)
{
	static u8 menu=0; //一级菜单初始化
	static u8 incDecFlag=0;    //区分一级菜单和二级菜单增减量键
	static u8 home_flag=0;     //主菜单标志位
	static u8 modeFlag=0;    //位数切换标志位
	static u8 weishuPointerKey=0;//位数指针
	static u8 KeyIndex=0;//进给速度指针，每一级代表一个进给速度，每次增量为1

	u8 keyTemp;                //临时保存按键值

	
  
		
	keyTemp=KEY_Scan(0);       //获取按键值 
	if(keyTemp==keyHome||home_flag==1)  //控制版上的按键  Home Inc Dec Mode Enter
	{
		
		 TIM_Cmd(TIM3, DISABLE);  //失能TIMx	 DISABLE
		 LCD_Clear(BLACK); //清屏 
	   LCD_Fill(40+16,40+16*0,40+16*2,40+16*1,YELLOW);  //LCD显示黄色方块
		 LCD_Show_Chinese16x16(40+16*2,40+16*0,"阈值设定");
		 LCD_Fill(40+16,40+16*2,40+16*2,40+16*3,YELLOW);  //LCD显示黄色方块
		 LCD_Show_Chinese16x16(40+16*2,40+16*2,"手动模式");
		 LCD_Fill(40+16,40+16*4,40+16*2,40+16*5,YELLOW);  //LCD显示黄色方块
		 LCD_Show_Chinese16x16(40+16*2,40+16*4,"开始采集");
		 LCD_Fill(40+16,40+16*6,40+16*2,40+16*7,YELLOW);  //LCD显示黄色方块
		 LCD_Show_Chinese16x16(40+16*2,40+16*6,"上传数据");
	
		 
		 POINT_COLOR=RED;		//笔画为红色	
		 LCD_Show_Chinese16x16(280-16*3,40,"操作说明");
		 POINT_COLOR=GREEN;		//笔画为绿色	
		 LCD_ShowString(280-16*3,40+16*1,"HOME");
		 LCD_ShowString(280-16*3-8,40+16*1,"*");
		 LCD_Show_Chinese16x16(280-16*3,40+16*2,"模式切换");
		 LCD_ShowString(280-16*3-8,40+16*2,"*");
		 LCD_ShowString(280-16*3,40+16*3,"----");
		 LCD_ShowString(280-16*3-8,40+16*3,"*");
		 LCD_ShowString(280-16*3,40+16*4,"----");
		 LCD_ShowString(280-16*3-8,40+16*4,"*");
		 LCD_Show_Chinese16x16(280-16*3,40+16*5,"确定");
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
		
		menu++;//在一级菜单中选择
		if(menu>4)
		{
			menu=1;
		}
		if(menu == 1)	 //若为1则选择第一行
		{
      
			LCD_ShowString(40,40+16*0,"1");
			LCD_ShowString(40,40+16*2," ");
			LCD_ShowString(40,40+16*4," ");
			LCD_ShowString(40,40+16*6," ");
	
			
		}
		if(menu == 2)	  //若为2则选择第二行
		{
			LCD_ShowString(40,40+16*0," ");
			LCD_ShowString(40,40+16*2,"1");
			LCD_ShowString(40,40+16*4," ");
			LCD_ShowString(40,40+16*6," ");
			
		}
	  if(menu == 3)	  //若为3则选择第三行
		{
			LCD_ShowString(40,40+16*0," ");
			LCD_ShowString(40,40+16*2," ");
			LCD_ShowString(40,40+16*4,"1");
			LCD_ShowString(40,40+16*6," ");
		}
    if(menu == 4)	  //若为4则选择第四行
		{
			LCD_ShowString(40,40+16*0," ");
			LCD_ShowString(40,40+16*2," ");
			LCD_ShowString(40,40+16*4," ");
			LCD_ShowString(40,40+16*6,"1");
		}
		if(menu == 5)	  //若为5则选择第五行
		{
			
		}
		if(menu == 6)	  //若为6则选择第六行
		{
			
		}
	}
	
	if(keyTemp == keyEnter)	//确认键按下 
	{
		if(menu == 1)		      //设置阈值
		{
			incDecFlag=1;    //区分一级菜单和二级菜单增减量键
		 LCD_Clear(BLACK); //清屏 
			LCD_Show_Chinese16x16(40+16*2,40+16*0,"阈值设定");
			LCD_ShowString(40+16*2+4*16,40+16*0,"----");
			
			POINT_COLOR=RED;		//笔画为红色	
		 LCD_Show_Chinese16x16(280-16*3,40,"操作说明");
		 POINT_COLOR=GREEN;		//笔画为绿色	
		 LCD_ShowString(280-16*3,40+16*1,"HOME");
		 LCD_ShowString(280-16*3-8,40+16*1,"*");
		 LCD_Show_Chinese16x16(280-16*3,40+16*2,"加");
		 LCD_ShowString(280-16*3-8,40+16*2,"*");
		 LCD_Show_Chinese16x16(280-16*3,40+16*3,"减");
		 LCD_ShowString(280-16*3-8,40+16*3,"*");
		 LCD_Show_Chinese16x16(280-16*3,40+16*4,"位数切换");
		 LCD_ShowString(280-16*3-8,40+16*4,"*");
		 LCD_Show_Chinese16x16(280-16*3,40+16*5,"确定");
		 LCD_ShowString(280-16*3-8,40+16*5,"*");
	
			
		  
		}
	}	
	
	if(keyTemp == keyEnter)	
	{
		
		if(menu == 2)		  //
		{
			
		  LCD_Clear(BLACK); //清屏 
			
			
			
		
		}
	}	
	
	if(keyTemp == keyEnter)	
	{
		if(menu == 3)		  //菜单的第三项开始采集数据
		{
			LCD_Clear(BLACK); //清屏 
			basic_show();
			LCD_Show_Chinese16x16(20,220,"阈值");
			LCD_ShowString(20+16*2,220,charthreshold);
			TIM_Cmd(TIM3, ENABLE);  //使能TIMx	 DISABLE
			
		}
	}
	
	if(keyTemp == keyEnter)	
	{
		if(menu == 4)		  //开始上传数据
		{
			
			LCD_Clear(BLACK); //清屏 
			TIM_Cmd(TIM3, ENABLE);  //使能TIMx	 DISABLE
			LCD_Show_Chinese16x16(20,220,"阈值");
			LCD_ShowString(20+16*2,220,charthreshold);
			upDataFlag=1;
			
			
			
			
		 
		}
	}

	if(keyTemp == keyEnter)	
	{
		if(menu == 5)		  //未定义
		{
		
		  LCD_Clear(BLACK); //清屏 
		 
		}
	}	

	if(keyTemp == keyEnter)	
	{
		if(menu == 6)		  //未定义
		{

			LCD_Clear(BLACK); //清屏 
      
		}
	}		
	
	if(menu==1&&incDecFlag==1)         //位数切换
	{
		 LCD_DrawRectangle(0, 0, 320, 240);	//画矩形框	
	   LCD_ShowString(280-5*8,220,"30248");
	   LCD_Show_Chinese16x16(280,220,"覃畅");
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
	if((menu==1&&incDecFlag==1&&modeFlag==1&&keyTemp == keyInc)||(menu==1&&incDecFlag==1&&modeFlag==1&&keyTemp == keyDec))         //位数加减
	{
		
	if(keyTemp == keyInc)  //加
		        {
              //KeyIndex++;
							threshold[weishuPointerKey]++;
							if(threshold[weishuPointerKey]>9) threshold[weishuPointerKey]=0;
							
					    
						}
					
	if(keyTemp == keyDec)  //减
		        {
              //KeyIndex++;
							threshold[weishuPointerKey]--;
							if(threshold[weishuPointerKey]<0) threshold[weishuPointerKey]=9;
							
					    
						}
						charthreshold[weishuPointerKey]=(char)(threshold[weishuPointerKey]+'0');
						LCD_ShowString(40+16*2+4*16+8*weishuPointerKey,40+16*0,&charthreshold[weishuPointerKey]);
					
	
	}
	
	if(menu==1&&incDecFlag==1&&modeFlag==1&&keyTemp == keyEnter)         //设置完阈值按下确定键
	{
		  threshold_total=threshold[0]*1000+threshold[0]*100+threshold[0]*10+threshold[0]*1;
		  menu=0;
		  incDecFlag=0;
		modeFlag=0;
		home_flag=1;
		Y_LED_ON;
		
		
	}
	
	
}