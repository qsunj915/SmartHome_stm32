#ifndef __DJ_H
#define __DJ_H

#include "stm32f4xx.h"

#define KEY_DOOR PAin(9)

extern int angle, angle_local;


void Angle_Cmd(void);
int Data_pro(int);//����Ƕȣ�����Ƚ�ֵ


#endif
