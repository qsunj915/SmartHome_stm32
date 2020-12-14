#ifndef __DJ_H
#define __DJ_H

#include "stm32f4xx.h"

#define KEY_DOOR KEY0

extern int angle, angle_local;


void Angle_Cmd(void);
int Data_pro(int);//输入角度，输出比较值


#endif
