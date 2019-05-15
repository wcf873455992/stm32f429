#ifndef _SYS_SET_H
#define _SYS_SET_H

typedef struct{
	_Bool	enable;
	float	O2;
	float	CO2;
	float	Temperature;
	float	Humidity;
}ALARM_VALUE;

typedef struct{
	_Bool	enable;
	int	Value;
}FAN_GANG;

typedef	struct{
	int	start_hour;
	int	start_min;
	int	end_hour;
	int	end_min;
}TIMING_TIME;

typedef struct{	
	int value;
	_Bool	enable;
}VOICE;
typedef struct{
	ALARM_VALUE	alarm;
	FAN_GANG	fan_gang[4];
	TIMING_TIME	timing[8];
	int	fan_run_time;
	int sample_interval;
	VOICE voice;
}SYS_SET;

#endif