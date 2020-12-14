/*日期简单快捷初始化文件*/
#include "user.h"
#include "key.h"
#include "delay.h"
#include "rtc.h"
#include "sys.h"

int alarm_config=0;

int AlarmUser_Change(int RTC_AlarmUser[])
{
	static int flag_Alarm=0, flag_change=0;
	int flag=0;
	
	if(!KEY0)
	{
		delay_ms(10);
		if(!KEY0)
		{
			while(!KEY0);//松开按键
			alarm_config = !alarm_config;//使能实时控制闹钟&&失能时写入闹钟
			if(alarm_config==0 && flag_change==1)
			{
				flag = 1;
				flag_change = 0;
			}
		}
	}
		
	if(alarm_config)
	{
		if(!KEY1)
		{
			delay_ms(10);
			if(!KEY1)
				RTC_AlarmUser[flag_Alarm]++;
			while(!KEY1);
		}
		
		if(!KEY2)
		{
			delay_ms(10);
			if(!KEY2)
			{
				flag_Alarm++;
				if(flag_Alarm==3)
					flag_Alarm = 0;
				while(!KEY2);
			}
		}
		flag_change = 1;//标志数据更改过
		Alarm_RightCheck(RTC_AlarmUser);
	}
	
	return(flag);
}

void Alarm_RightCheck(int RTC_AlarmUser[])
{
	//秒位的合理性检查
	if(RTC_AlarmUser[2]>60)
	{
		RTC_AlarmUser[2] = 0;
		RTC_AlarmUser[1]++;
	}
	if(RTC_AlarmUser[2]<0)
	{
		RTC_AlarmUser[2] = 59;
		RTC_AlarmUser[1]--;
	}
	
	//分位的合理性检查
	if(RTC_AlarmUser[1]>59)
	{
		RTC_AlarmUser[1] = 0;
		RTC_AlarmUser[0]++;
	}
	if(RTC_AlarmUser[1]<0)
	{
		RTC_AlarmUser[1] = 59;
		RTC_AlarmUser[0]--;
	}
	
	//时位的合理性检查
	if(RTC_AlarmUser[0]>23)
	{
		RTC_AlarmUser[0] = 0;
	}
	if(RTC_AlarmUser[0]<0)
	{
		RTC_AlarmUser[0] = 23;
	}
}



/*
RTC_TimeTypeDef RTC_TimeStruct;
RTC_DateTypeDef RTC_DateStruct;

void TimeUser_init(void)
{
	int flag_Time=7;
	
	RTC_WriteBackupRegister(RTC_BKP_DR0,0x5051);//开启时钟编辑
	if(WK_UP)
	{
		while(WK_UP);//松开按键

		RTC_GetTime(RTC_Format_BIN,&RTC_TimeStruct);//获得时间数据
		RTC_GetDate(RTC_Format_BIN, &RTC_DateStruct);//获得日期数据
		
		while(!WK_UP)//在按下下一次按键之前
		{
			if(!KEY2)//时间加
			{
				delay_ms(10);
				if(!KEY2)
					switch(flag_Time)
					{
						case 1: RTC_DateStruct.RTC_WeekDay++;
							break;
						case 2: RTC_DateStruct.RTC_Date++;
							break;
						case 3: RTC_DateStruct.RTC_Month++;
							break;
						case 4: RTC_DateStruct.RTC_Year++;
							break;
						case 5: RTC_TimeStruct.RTC_Seconds++;
							break;
						case 6: RTC_TimeStruct.RTC_Minutes++;
							break;
						case 7: RTC_TimeStruct.RTC_Hours++;
							break;
						
					}
				while(!KEY2);
			}
			
			if(!KEY1)//时间减
			{
				delay_ms(10);
				if(!KEY1)
					switch(flag_Time)
					{
						case 1: RTC_DateStruct.RTC_WeekDay--;
							break;
						case 2: RTC_DateStruct.RTC_Date--;
							break;
						case 3: RTC_DateStruct.RTC_Month--;
							break;
						case 4: RTC_DateStruct.RTC_Year--;
							break;
						case 5: RTC_TimeStruct.RTC_Seconds--;
							break;
						case 6: RTC_TimeStruct.RTC_Minutes--;
							break;
						case 7: RTC_TimeStruct.RTC_Hours--;
							break;
						
					}
				while(!KEY1);

			}
			
			if(!KEY0)//移动控制位置
			{
				delay_ms(10);
				if(!KEY0)
				{
					flag_Time--;
					if(!flag_Time)
						flag_Time = 7;
					while(!KEY0);
				}
			}
			
			Time_RightCheck();//时间显示的正确性检查
		}
		
		RTC_Set_Time(RTC_TimeStruct.RTC_Hours, RTC_TimeStruct.RTC_Minutes, RTC_TimeStruct.RTC_Seconds, RTC_H12_AM);	//设置时间
		RTC_Set_Date(RTC_DateStruct.RTC_Year, RTC_DateStruct.RTC_Month, RTC_DateStruct.RTC_Date, RTC_DateStruct.RTC_WeekDay);		//设置日期
	}
	
}

void Time_RightCheck()
{
	//秒位的合理性检查
	if(RTC_TimeStruct.RTC_Seconds>60)
	{
		RTC_TimeStruct.RTC_Seconds = 0;
		RTC_TimeStruct.RTC_Minutes++;
	}
	if(RTC_TimeStruct.RTC_Seconds<0)
	{
		RTC_TimeStruct.RTC_Seconds = 59;
		RTC_TimeStruct.RTC_Minutes--;
	}
	
	//分位的合理性检查
	if(RTC_TimeStruct.RTC_Minutes>60)
	{
		RTC_TimeStruct.RTC_Minutes = 0;
		RTC_TimeStruct.RTC_Hours++;
	}
	if(RTC_TimeStruct.RTC_Minutes<0)
	{
		RTC_TimeStruct.RTC_Minutes = 59;
		RTC_TimeStruct.RTC_Hours--;
	}
	
	//时位的合理性检查
	if(RTC_TimeStruct.RTC_Hours>23)
	{
		RTC_TimeStruct.RTC_Minutes = 0;
		RTC_DateStruct.RTC_Date++;
	}
	if(RTC_TimeStruct.RTC_Hours<0)
	{
		RTC_TimeStruct.RTC_Minutes = 23;
		RTC_DateStruct.RTC_Date--;
	}
	
	//日期位的合理性检查
	if(RTC_DateStruct.RTC_Date>30)
	{
		RTC_DateStruct.RTC_Date = 1;
		RTC_DateStruct.RTC_Month++;
	}
	if(RTC_DateStruct.RTC_Date<1)
	{
		RTC_DateStruct.RTC_Date = 30;
		RTC_DateStruct.RTC_Month--;
	}
	
	//周位的合理性检查
	if(RTC_DateStruct.RTC_WeekDay>5)
	{
		RTC_DateStruct.RTC_WeekDay = 1;
	}
	if(RTC_DateStruct.RTC_WeekDay<0)
	{
		RTC_DateStruct.RTC_WeekDay = 5;
	}
	
	
	
}
*/
