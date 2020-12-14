#include "sys.h"
#include "delay.h"  
#include "usart.h"  
#include "led.h"
#include "lcd.h"
#include "usmart.h"
#include "rtc.h"
#include "beep.h"
#include "key.h"
#include "timer.h"
#include "user.h"
#include "dj.h"

/*
V1.0 ʵ�ֻ�������ʾʱ�ӹ���
V2.0 ʵ�����ӹ��ܣ����㳤ʱ�����У����㱨ʱ��
V3.0 ʵ������ʱ��ʵʱ�������ܣ��������ܣ�,���ʱ�䳬�����⣨25��70��70��
*/

int main(void)
{ 

	RTC_TimeTypeDef RTC_TimeStruct;
	RTC_DateTypeDef RTC_DateStruct;
	
	int RTC_AlarmUser[3]={12,00,0};

	u8 tbuf[40];
	u8 t=0;

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
	delay_init(168);      //��ʼ����ʱ����
	uart_init(115200);		//��ʼ�����ڲ�����Ϊ115200
	TIM3_Int_Init(5000-1,8400-1);	//��ʱ��ʱ��84M����Ƶϵ��8400������84M/8400=10Khz�ļ���Ƶ�ʣ�����5000��Ϊ500ms     

	
	usmart_dev.init(84); 	//��ʼ��USMART	
	LED_Init();					  //��ʼ��LED
	BEEP_Init();				//��ʼ��BEEP
	KEY_Init();					//��ʼ��kEY
 	LCD_Init();					  //��ʼ��LCD
	TIM14_PWM_Init(200-1, 8400-1);				//PWM 0.1ms*20ms
	My_RTC_Init();		 		//��ʼ��RTC
	RTC_Set_AlarmA(3, 20, 10, 00);			//�������ӣ�ʱ�䣺week3,12:00:00
 
	RTC_Set_WakeUp(RTC_WakeUpClock_CK_SPRE_16bits,0);		//����WAKE UP�ж�,1�����ж�һ��
	
	POINT_COLOR=RED;
	LCD_ShowString(30,50,200,16,16, "Explorer STM32F4");	
	LCD_ShowString(30,70,200,16,16, "project:Smart Home");	
	LCD_ShowString(30,90,200,16,16, "Author@YiXieTe");
	LCD_ShowString(30,110,200,16,16, "2020/12/8*V3.0");	
  	while(1) 
	{	
		/*ģʽһ��ʵʱʱ��*/
		if(mode==0)
		{
			t++;
			if((t%10)==0)	//ÿ100ms����һ����ʾ����
			{
				RTC_GetTime(RTC_Format_BIN,&RTC_TimeStruct);
				
				sprintf((char*)tbuf,"Time:%02d:%02d:%02d",RTC_TimeStruct.RTC_Hours,RTC_TimeStruct.RTC_Minutes,RTC_TimeStruct.RTC_Seconds); 
				LCD_ShowString(30,140,210,16,16,tbuf);	
				
				RTC_GetDate(RTC_Format_BIN, &RTC_DateStruct);
				
				sprintf((char*)tbuf,"Date:20%02d-%02d-%02d",RTC_DateStruct.RTC_Year,RTC_DateStruct.RTC_Month,RTC_DateStruct.RTC_Date); 
				LCD_ShowString(30,160,210,16,16,tbuf);	
				sprintf((char*)tbuf,"Week:%d",RTC_DateStruct.RTC_WeekDay); 
				LCD_ShowString(30,180,210,16,16,tbuf);
				
				//������ʾ
				sprintf((char*)tbuf,"Alarm:%02d:%02d:%02d,%02d",RTC_AlarmUser[0], RTC_AlarmUser[1], RTC_AlarmUser[2], alarm_config); 
				LCD_ShowString(30,200,210,16,16,tbuf);
				
				
				if(AlarmUser_Change(RTC_AlarmUser))//��������ʱ��==���BUG��2020/12/11��������ֵ�޷�����
				{
					RTC_Set_AlarmA(3, RTC_AlarmUser[0], RTC_AlarmUser[1], RTC_AlarmUser[2]);//��������ʱ��
				}
				if((!RTC_TimeStruct.RTC_Seconds) && (!RTC_TimeStruct.RTC_Minutes))//���㱨ʱ
				{
					Beep_TimeBar();
				}
			} 
		}
		
		/*ģʽ������ʪ����ʾ*/
		else if(mode==1)
		{
			
		}
		
		/*ģʽ�����ŵĿ���*/
		else if(mode==2)
		{
			Angle_Cmd();		//��Ӷ�����ŵĿ��ƣ�2020/12/11
		}
		
		/*ģʽ�ģ������Ŀ���*/
		else if(mode==3)
		{
			
		}
		
		/*ģʽ����*/
		else mode = 0;
		
		
		/*ģʽ�л�����*/
		KEY_ModeChange();
		
		/*��ʾ����λ�ڵ�ģʽ*/
		sprintf((char*)tbuf,"MODE:%02d",mode); 
		LCD_ShowString(30,220,210,16,16,tbuf);
		
		if((t%20)==0)LED0=!LED0;	//ÿ200ms,��תһ��LED0 
		delay_ms(10);
	}	
}


