#ifndef __BEEP_H
#define __BEEP_H	 
#include "sys.h"
#include "delay.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32F407������
//��������������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2014/5/3
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 

//LED�˿ڶ���
#define BEEP PFout(8)	// ����������IO 

void BEEP_Init(void);//��ʼ��	
void Beep_On(void);
//void Beep_AutoCut(void);
void Beep_TimeBar(void);


#endif

















