/*���ڼ򵥿�ݳ�ʼ���ļ�*/
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
			while(!KEY0);//�ɿ�����
			alarm_config = !alarm_config;//ʹ��ʵʱ��������&&ʧ��ʱд������
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
		flag_change = 1;//��־���ݸ��Ĺ�
		Alarm_RightCheck(RTC_AlarmUser);
	}
	
	return(flag);
}

void Alarm_RightCheck(int RTC_AlarmUser[])
{
	//��λ�ĺ����Լ��
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
	
	//��λ�ĺ����Լ��
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
	
	//ʱλ�ĺ����Լ��
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
	
	RTC_WriteBackupRegister(RTC_BKP_DR0,0x5051);//����ʱ�ӱ༭
	if(WK_UP)
	{
		while(WK_UP);//�ɿ�����

		RTC_GetTime(RTC_Format_BIN,&RTC_TimeStruct);//���ʱ������
		RTC_GetDate(RTC_Format_BIN, &RTC_DateStruct);//�����������
		
		while(!WK_UP)//�ڰ�����һ�ΰ���֮ǰ
		{
			if(!KEY2)//ʱ���
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
			
			if(!KEY1)//ʱ���
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
			
			if(!KEY0)//�ƶ�����λ��
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
			
			Time_RightCheck();//ʱ����ʾ����ȷ�Լ��
		}
		
		RTC_Set_Time(RTC_TimeStruct.RTC_Hours, RTC_TimeStruct.RTC_Minutes, RTC_TimeStruct.RTC_Seconds, RTC_H12_AM);	//����ʱ��
		RTC_Set_Date(RTC_DateStruct.RTC_Year, RTC_DateStruct.RTC_Month, RTC_DateStruct.RTC_Date, RTC_DateStruct.RTC_WeekDay);		//��������
	}
	
}

void Time_RightCheck()
{
	//��λ�ĺ����Լ��
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
	
	//��λ�ĺ����Լ��
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
	
	//ʱλ�ĺ����Լ��
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
	
	//����λ�ĺ����Լ��
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
	
	//��λ�ĺ����Լ��
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
