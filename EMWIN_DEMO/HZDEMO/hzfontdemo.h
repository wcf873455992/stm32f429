#ifndef _HZFONTDEMO_H
#define _HZFONTDEMO_H
#include "sys.h"
#if 1
typedef struct{
	char	*	Date;	
	char 	*	Time;
	char	*	name;
	char	*	O2;
	char	*	CO2;
	char	*	alarm;
	//char	end[3];
}REAL_TIME_DATA;
#else
typedef struct{
	char		Date[11];	
	char 		Time[9];
	char		name[10];
	char		O2[10];
	char	CO2[10];
	char		alarm[20];
	//char	end[3];
}REAL_TIME_DATA;
#endif
void HZFontDemo(void); 
#endif
