#include "timer.h"
#include "usart.h"
//////////////////////////////////////////////////////////////////////////////////	 
//通用定时器3中断初始化
//这里时钟选择为APB1的2倍，而APB1为36M
//arr：自动重装值。
//psc：时钟预分频数
//这里使用的是定时器3!
unsigned char Count_timer = 0;
unsigned char Count_timer1 = 0;
unsigned char Count_timer10 = 0;

unsigned char Flag_timer_2S = 0;
unsigned char Flag_timer_1S = 0;
unsigned char Flag_timer_10S = 0;
unsigned char Count_time_wait_ok = 0;
#define Time_Send_interval        5  // x * 100 毫秒

unsigned int Count_timer_100ms_x_Collect_Interval = 65530;//默认先不触发采集计时
unsigned char Count_timer_100ms_x_Send_Interval_after_collect = 201;//默认不触发发送计时

unsigned char Count_time_wait_ok_x_100ms = 0;
unsigned char Count_wait_ok = 0;	
unsigned char Count_Send_Time_Interval = 0;
unsigned char count_time = 0;
bool Flag_allow_dsplay_time;
unsigned char Count_Timer3_value_UART4_receive_timeout;
unsigned char Count_Timer3_value_UART5_receive_timeout;
		
void TIM3_Int_Init(u16 arr,u16 psc)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //时钟使能
	
	//定时器TIM3初始化
	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //根据指定的参数初始化TIMx的时间基数单位
 
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE ); //使能指定的TIM3中断,允许更新中断

	//中断优先级NVIC设置
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  //TIM3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //先占优先级0级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //从优先级3级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //初始化NVIC寄存器

	TIM_Cmd(TIM3, ENABLE);  //使能TIMx					 
}
//定时器3中断服务程序
void TIM3_IRQHandler(void)   //TIM3中断 100ms
{		
	if(TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)  //检查TIM3更新中断发生与否
	{
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update  );  //清除TIMx更新中断标志
		
		
		if(Count_timer < 20)
		{			
			Count_timer++;
		}
		else
		{
			Flag_timer_2S = 1;
			Count_timer = 0;
		}
		
		if(Count_timer1 < 10)
		{			
			Count_timer1++;
		}
		else
		{
			Flag_timer_1S = 1;
			Count_timer1 = 0;
		}
		

		if(Count_timer10 < 100)
		{			
			Count_timer10++;
		}
		else
		{
			Flag_timer_10S = 1;
			Count_timer10 = 0;
		}
		
		
		if(Count_Timer3_value_USART3_receive_timeout)
		{
			Count_Timer3_value_USART3_receive_timeout --;
		}
		
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
		
		if(Count_Timer3_value_USART2_receive_timeout)
			Count_Timer3_value_USART2_receive_timeout --;
		if(Count_Timer3_value_USART3_receive_timeout)
			Count_Timer3_value_USART3_receive_timeout --;			
		if(Count_Send_Time_Interval)
			 Count_Send_Time_Interval --;
		if(Count_Timer3_value_USART1_receive_timeout)
			Count_Timer3_value_USART1_receive_timeout --;
		if(Count_Timer3_value_USART2_receive_timeout)
			Count_Timer3_value_USART2_receive_timeout --;
		
		if(count_time)
			count_time --;
		if(Count_time_wait_ok)
			Count_time_wait_ok --;
		if(Count_timer_100ms_x_Collect_Interval < 65530)
		{
			Count_timer_100ms_x_Collect_Interval ++;
			Flag_allow_dsplay_time = 1;
		}
		if(Count_timer_100ms_x_Send_Interval_after_collect < 200)
		{
			Count_timer_100ms_x_Send_Interval_after_collect ++;
		}
			
	}
}

