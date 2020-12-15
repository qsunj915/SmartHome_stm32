#include "dj.h"
#include "delay.h"
#include "key.h"

int angle=0, angle_local=0, angle_localCurt=-1;


void Angle_DoorCmd()//门控函数，外接PA7
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


void Angle_CURTCmd(void)//窗帘控制函数，外接PA0
{
	if(!KEY_DOOR)
	{
		delay_ms(10);
		if((!KEY_DOOR)&&(angle_localCurt==-1))
			angle = 45;
		else if((!KEY_DOOR)&&(angle_localCurt==45))
			angle = 90;
		else if((!KEY_DOOR)&&(angle_localCurt==90))
			angle = 135;
		else if((!KEY_DOOR)&&(angle_localCurt==135))
			angle = -1;
		angle_localCurt = angle;
		while(!KEY_DOOR);//松开按键标志
		TIM_SetCompare2(TIM5, Data_pro(angle));
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
		case -1:
			lo_data = 0;
			break;
	}
	return(lo_data-1);//输出比较值
}

