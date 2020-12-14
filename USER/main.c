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
V1.0 实现基本的显示时钟功能
V2.0 实现闹钟功能（定点长时间鸣叫，整点报时）
V3.0 实现闹钟时间实时调整功能（不包括周）,解决时间超限问题（25：70：70）
*/

int main(void)
{ 

	RTC_TimeTypeDef RTC_TimeStruct;
	RTC_DateTypeDef RTC_DateStruct;
	
	int RTC_AlarmUser[3]={12,00,0};

	u8 tbuf[40];
	u8 t=0;

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
	delay_init(168);      //初始化延时函数
	uart_init(115200);		//初始化串口波特率为115200
	TIM3_Int_Init(5000-1,8400-1);	//定时器时钟84M，分频系数8400，所以84M/8400=10Khz的计数频率，计数5000次为500ms     

	
	usmart_dev.init(84); 	//初始化USMART	
	LED_Init();					  //初始化LED
	BEEP_Init();				//初始化BEEP
	KEY_Init();					//初始化kEY
 	LCD_Init();					  //初始化LCD
	TIM14_PWM_Init(200-1, 8400-1);				//PWM 0.1ms*20ms
	My_RTC_Init();		 		//初始化RTC
	RTC_Set_AlarmA(3, 20, 10, 00);			//开启闹钟：时间：week3,12:00:00
 
	RTC_Set_WakeUp(RTC_WakeUpClock_CK_SPRE_16bits,0);		//配置WAKE UP中断,1秒钟中断一次
	
	POINT_COLOR=RED;
	LCD_ShowString(30,50,200,16,16, "Explorer STM32F4");	
	LCD_ShowString(30,70,200,16,16, "project:Smart Home");	
	LCD_ShowString(30,90,200,16,16, "Author@YiXieTe");
	LCD_ShowString(30,110,200,16,16, "2020/12/8*V3.0");	
  	while(1) 
	{	
		/*模式一：实时时钟*/
		if(mode==0)
		{
			t++;
			if((t%10)==0)	//每100ms更新一次显示数据
			{
				RTC_GetTime(RTC_Format_BIN,&RTC_TimeStruct);
				
				sprintf((char*)tbuf,"Time:%02d:%02d:%02d",RTC_TimeStruct.RTC_Hours,RTC_TimeStruct.RTC_Minutes,RTC_TimeStruct.RTC_Seconds); 
				LCD_ShowString(30,140,210,16,16,tbuf);	
				
				RTC_GetDate(RTC_Format_BIN, &RTC_DateStruct);
				
				sprintf((char*)tbuf,"Date:20%02d-%02d-%02d",RTC_DateStruct.RTC_Year,RTC_DateStruct.RTC_Month,RTC_DateStruct.RTC_Date); 
				LCD_ShowString(30,160,210,16,16,tbuf);	
				sprintf((char*)tbuf,"Week:%d",RTC_DateStruct.RTC_WeekDay); 
				LCD_ShowString(30,180,210,16,16,tbuf);
				
				//闹钟显示
				sprintf((char*)tbuf,"Alarm:%02d:%02d:%02d,%02d",RTC_AlarmUser[0], RTC_AlarmUser[1], RTC_AlarmUser[2], alarm_config); 
				LCD_ShowString(30,200,210,16,16,tbuf);
				
				
				if(AlarmUser_Change(RTC_AlarmUser))//更改闹钟时间==解决BUG（2020/12/11）：返回值无法传入
				{
					RTC_Set_AlarmA(3, RTC_AlarmUser[0], RTC_AlarmUser[1], RTC_AlarmUser[2]);//控制闹钟时间
				}
				if((!RTC_TimeStruct.RTC_Seconds) && (!RTC_TimeStruct.RTC_Minutes))//整点报时
				{
					Beep_TimeBar();
				}
			} 
		}
		
		/*模式二：温湿度显示*/
		else if(mode==1)
		{
			
		}
		
		/*模式三：门的控制*/
		else if(mode==2)
		{
			Angle_Cmd();		//添加舵机（门的控制）2020/12/11
		}
		
		/*模式四：窗帘的控制*/
		else if(mode==3)
		{
			
		}
		
		/*模式修正*/
		else mode = 0;
		
		
		/*模式切换函数*/
		KEY_ModeChange();
		
		/*显示现在位于的模式*/
		sprintf((char*)tbuf,"MODE:%02d",mode); 
		LCD_ShowString(30,220,210,16,16,tbuf);
		
		if((t%20)==0)LED0=!LED0;	//每200ms,翻转一次LED0 
		delay_ms(10);
	}	
}


