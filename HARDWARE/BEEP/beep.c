#include "beep.h" 

//初始化PF8为输出口		    
//BEEP IO初始化
void BEEP_Init(void)
{   
  GPIO_InitTypeDef  GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);//使能GPIOF时钟
  
  //初始化蜂鸣器对应引脚GPIOF8
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输出模式
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;//下拉
  GPIO_Init(GPIOF, &GPIO_InitStructure);//初始化GPIO
	
  GPIO_ResetBits(GPIOF,GPIO_Pin_8);  //蜂鸣器对应引脚GPIOF8拉低， 
}

void Beep_On(void)//蜂鸣器开启
{
	BEEP = 1;
}

/*废物一个
void Beep_AutoCut(void)
{
	static int index=0;
	if(BEEP)
	{
		delay_ms(10);
		if(BEEP)
		{
			index = 1000;
		}
	}
	if(!index)
		BEEP = 0;
	index--;
}*/

void Beep_TimeBar(void)
{
	BEEP = 1;
	delay_ms(50);
	BEEP = 0;
}
