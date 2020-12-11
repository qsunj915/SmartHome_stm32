#include "dj.h"
#include "delay.h"

int angle=0, angle_local=0;


void Angle_Cmd()
{
		/*
		if(!KEY_DOOR)
		{
			delay_ms(10);
			if(!KEY_DOOR)
				angle += 45;
			if(angle>180)
				angle = angle_local;
			while(!KEY_DOOR);//松开按键标志
		}
		if(!KEY_DOOR)//控制初始角度位置
		{
			delay_ms(10);
			if(!KEY_DOOR)
			{
				angle_local = angle;
				while(!KEY_DOOR);
			}
		}*/
	
	if(!KEY_DOOR)
	{
		delay_ms(10);
		if((!KEY_DOOR)&&(angle_local==0))
			angle = 90;
		else if((!KEY_DOOR)&&(angle_local==90))
			angle = 0;
		angle_local = angle;
		while(!KEY_DOOR);//松开按键标志
		TIM_SetCompare1(TIM14, Data_pro(angle));
	}
}


int Data_pro(int angle)		//KEY_DOOR定义在dj.h中
{
	int lo_data;//装载值
	int angle_current;
	
	angle_current = angle-angle_local;
	if(angle_current<0)
		angle_current += 180;
	
	switch(angle_current)
	{
		case 0:
			lo_data = 0.5/0.1;
			break;
		case 45:
			lo_data = 1.0/0.1;
			break;
		case 90:
			lo_data = 1.5/0.1;
			break;
		case 135:
			lo_data = 2.0/0.1;
			break;
		case 180:
			lo_data = 2.5/0.1;
			break;
	}
	return(lo_data-1);//输出比较值
}

