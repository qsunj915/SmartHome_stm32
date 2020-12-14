#include "dj.h"
#include "delay.h"
#include "key.h"

int angle=0, angle_local=0;


void Angle_Cmd()
{
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
	
	angle_current = angle;
	
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

