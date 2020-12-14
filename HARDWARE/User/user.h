#ifndef __USER_H
#define __USER_H
#include "sys.h"

/*void TimeUser_init(void);
void Time_RightCheck(void);
*/

extern int alarm_config;

int AlarmUser_Change(int RTC_AlarmUser[]);
void Alarm_RightCheck(int RTC_AlarmUser[]);
	    
#endif
