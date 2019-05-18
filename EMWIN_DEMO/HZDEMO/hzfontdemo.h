#ifndef _HZFONTDEMO_H
#define _HZFONTDEMO_H
#include "sys.h"
#if 1

#define MAX_TRANSMITTER 50

typedef struct{
	_Bool	state;	
	RTC_TimeTypeDef	start_time;
	RTC_DateTypeDef start_date;
	RTC_TimeTypeDef	end_time;
	RTC_DateTypeDef end_date;
	int 	Last_run_min;	
}FAN;

enum	trasmitter_alarm{
	NO,
	O2,
	CO2,
	O2_CO2,
};
typedef	struct{
	int number;
	int O2;
	int CO2;	
	int	alarm;
	RTC_TimeTypeDef	Time;
	RTC_DateTypeDef Date;
	//enum  trasmitter_alarm alarm;//0=无，1=O2报警，2=CO2报警，3=O2，CO2报警
}TRANSMITTER;
typedef struct{
	FAN fan;
	TRANSMITTER	transmitter[MAX_TRANSMITTER];	
	RTC_TimeTypeDef	sys_Time;
	RTC_DateTypeDef sys_Date;
}REAL_DATA;

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
