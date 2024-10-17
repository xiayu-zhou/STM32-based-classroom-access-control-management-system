#include "timer.h"
#include "usart.h"
//////////////////////////////////////////////////////////////////////////////////	 
//ͨ�ö�ʱ��3�жϳ�ʼ��
//����ʱ��ѡ��ΪAPB1��2������APB1Ϊ36M
//arr���Զ���װֵ��
//psc��ʱ��Ԥ��Ƶ��
//����ʹ�õ��Ƕ�ʱ��3!
unsigned char Count_timer = 0;
unsigned char Count_timer1 = 0;
unsigned char Count_timer10 = 0;

unsigned char Flag_timer_2S = 0;
unsigned char Flag_timer_1S = 0;
unsigned char Flag_timer_10S = 0;
unsigned char Count_time_wait_ok = 0;
#define Time_Send_interval        5  // x * 100 ����

unsigned int Count_timer_100ms_x_Collect_Interval = 65530;//Ĭ���Ȳ������ɼ���ʱ
unsigned char Count_timer_100ms_x_Send_Interval_after_collect = 201;//Ĭ�ϲ��������ͼ�ʱ

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

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //ʱ��ʹ��
	
	//��ʱ��TIM3��ʼ��
	TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //����ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
 
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE ); //ʹ��ָ����TIM3�ж�,��������ж�

	//�ж����ȼ�NVIC����
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  //TIM3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //��ռ���ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //�����ȼ�3��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  //��ʼ��NVIC�Ĵ���

	TIM_Cmd(TIM3, ENABLE);  //ʹ��TIMx					 
}
//��ʱ��3�жϷ������
void TIM3_IRQHandler(void)   //TIM3�ж� 100ms
{		
	if(TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)  //���TIM3�����жϷ������
	{
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update  );  //���TIMx�����жϱ�־
		
		
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

