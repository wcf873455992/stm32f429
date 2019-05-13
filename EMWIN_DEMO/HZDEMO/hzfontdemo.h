#ifndef _HZFONTDEMO_H
#define _HZFONTDEMO_H
#include "sys.h"

typedef struct{
	RTC_TimeTypeDef	Time;
	RTC_DateTypeDef Date;
	char	* number;
	float		O2;
	float		CO2;
	char		alarm;
}REAL_TIME_DATA;


void HZFontDemo(void); 
#endif
