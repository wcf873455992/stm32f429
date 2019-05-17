#include "hzfontdemo.h"
#include "EmWinHZFont.h"
#include "DIALOG.h"
#include "rtc.h"
#include "malloc.h"


#define ID_FRAMEWIN_0 	(GUI_ID_USER + 0)
#define ID_MULTIEDIT_0 	(GUI_ID_USER + 1)
#define ID_BUTTON_0 	(GUI_ID_USER + 2)
#define ID_BUTTON_1 	(GUI_ID_USER + 3)
#define ID_BUTTON_2 	(GUI_ID_USER + 4)
#define ID_BUTTON_3 	(GUI_ID_USER + 5)
#define ID_BUTTON_4 	(GUI_ID_USER + 6)
#define ID_BUTTON_5 	(GUI_ID_USER + 7)
#define ID_BUTTON_6 	(GUI_ID_USER + 8)
#define ID_LISTVIEW_0 	(GUI_ID_USER + 9)

#define ID_CHECKBOX_0 	(GUI_ID_USER + 240)
#define ID_CHECKBOX_1 	(GUI_ID_USER + 250)
#define ID_CHECKBOX_2 	(GUI_ID_USER + 260)
#define ID_CHECKBOX_3 	(GUI_ID_USER + 270)
#define ID_RADIO_0 		(GUI_ID_USER + 280)

#define ID_DROPDOWN_0 	(GUI_ID_USER + 10)
#define ID_TEXT_0 		(GUI_ID_USER + 11)
#define ID_TEXT_1 		(GUI_ID_USER + 12)
#define ID_TEXT_2 		(GUI_ID_USER + 13)
#define ID_TEXT_3 		(GUI_ID_USER + 14)
#define ID_TEXT_4 		(GUI_ID_USER + 15)
#define ID_TEXT_5 		(GUI_ID_USER + 16)
#define ID_TEXT_6 		(GUI_ID_USER + 17)
#define ID_SCROLLBAR_0 	(GUI_ID_USER + 150)
#define ID_SLIDER_0 	(GUI_ID_USER + 160)
#define ID_LISTVIEW_1 	(GUI_ID_USER + 170)


#define MAX_TRANSMITTER 10

WM_HWIN hDialog;
WM_HWIN hDialog_help_t;
GUI_HWIN	hwin_data;


typedef struct{
	_Bool	state;	
	RTC_TimeTypeDef	Time;
	RTC_DateTypeDef Date;
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
	//enum  trasmitter_alarm alarm;//0=�ޣ�1=O2������2=CO2������3=O2��CO2����
}TRANSMITTER;
typedef struct{
	FAN fan;
	TRANSMITTER	transmitter[MAX_TRANSMITTER];	
	RTC_TimeTypeDef	sys_Time;
	RTC_DateTypeDef sys_Date;
}REAL_DATA;
static REAL_DATA data;

typedef struct{
	char name[20];
	char O2[20];
	char CO2[20];
	char time[20];
	char alarm[30];
}TEMP_LIST;
//static TEMP_LIST *transmitter[MAX_TRANSMITTER];

#if 0
static char *transmitter[7][5]={
	{"1#������",	"20.5%","300PPM","2019-5-11 18:34:20", "CO2����"},
	{"2#������",	"20.5%","300PPM","2019-5-11 18:34:20", " "},
	{"3#������",	"20.5%","300PPM","2019-5-11 18:34:20", "O2����"},
	{"4#������",	"20.5%","300PPM","2019-5-11 18:34:20", " "},
	{"5#������",	"20.5%","300PPM","2019-5-11 18:34:20", " "},
	{"6#������",	"20.5%","300PPM","2019-5-11 18:34:20", " "},
	{"7#������",	"20.5%","300PPM","2019-5-11 18:34:20", "  "},
};
#else
static char *transmitter[7][5];
#endif


/**/
static const char *_ListViewTable[][5]={
	{"1#������",	"20.5%","300PPM","2019-5-11 18:34:20", "CO2����"},
	{"2#������",	"20.5%","300PPM","2019-5-11 18:34:20", " "},
	{"3#������",	"20.5%","300PPM","2019-5-11 18:34:20", "O2����"},
	{"4#������",	"20.5%","300PPM","2019-5-11 18:34:20", " "},
	{"5#������",	"20.5%","300PPM","2019-5-11 18:34:20", " "},
	{"6#������",	"20.5%","300PPM","2019-5-11 18:34:20", " "},
	{"7#������",	"20.5%","300PPM","2019-5-11 18:34:20", "  "},
};

	
//�Ի�����Դ�б�
static const GUI_WIDGET_CREATE_INFO _aDialogCreate[] = {
  { FRAMEWIN_CreateIndirect, 	"Framewin", 	ID_FRAMEWIN_0, 	0, 		0, 		800, 	480, 	0, 0x64, 0 },
  //{ MULTIEDIT_CreateIndirect, 	"Multiedit", 	ID_MULTIEDIT_0, 20, 	250, 	300, 	160, 	0, 0x0, 0 },
  { BUTTON_CreateIndirect, 		"ϵͳ����", 		ID_BUTTON_0, 	1,	0, 	133, 	50, 	0, 0x0, 0 },
  { BUTTON_CreateIndirect, 		"�豸����", 		ID_BUTTON_1, 	134,	0, 	133, 	50, 	0, 0x0, 0 },
  { BUTTON_CreateIndirect, 		"ʵʱ����", 		ID_BUTTON_2, 	267,	0, 	133, 	50, 	0, 0x0, 0 },
  { BUTTON_CreateIndirect, 		"��ʷ����", 		ID_BUTTON_3, 	400,	0, 	133, 	50, 	0, 0x0, 0 },
  { BUTTON_CreateIndirect, 		"�����¼", 		ID_BUTTON_4, 	533,	0, 	133, 	50, 	0, 0x0, 0 },
  { BUTTON_CreateIndirect, 		"ʹ�ð���", 		ID_BUTTON_5, 	666, 	0, 	133, 	50, 	0, 0x0, 0 },
  { BUTTON_CreateIndirect, 		"״̬�л�", 		ID_BUTTON_6, 	25, 	390, 	100, 	30, 	0, 0x0, 0 },
  { LISTVIEW_CreateIndirect, 	"Listview", 	ID_LISTVIEW_0, 	5, 	55, 	780, 	300, 	0, 0x0, 0 },
  { TEXT_CreateIndirect, 		"״̬", 		ID_TEXT_0, 		160, 	398, 	700, 	30, 	0, 0x64, 0 },
  { TEXT_CreateIndirect, 		"ϵͳʱ��", 		ID_TEXT_4, 		280, 	440, 	500, 	35, 	0, 0x64, 0 },
  { TEXT_CreateIndirect, 		"ʱ�����", 		ID_TEXT_5, 		0, 	440, 	200, 	35, 	0, 0x64, 0 },
  { TEXT_CreateIndirect, 		"���", 		ID_TEXT_6, 		20, 	360, 	30, 	30, 	0, 0x64, 0 },
};




char timebuf[40];
void GetSysTime(){
	HAL_RTC_GetTime(&RTC_Handler,&data.sys_Time,RTC_FORMAT_BIN); 
	HAL_RTC_GetDate(&RTC_Handler,&data.sys_Date,RTC_FORMAT_BIN);
	sprintf((char*)timebuf,"ϵͳʱ�䣺20%02d-%02d-%02d %02d:%02d:%02d  �汾V1.0",
				data.sys_Date.Year,data.sys_Date.Month,data.sys_Date.Date,
				data.sys_Time.Hours,data.sys_Time.Minutes,data.sys_Time.Seconds); 
		
}
void update_fan(WM_MESSAGE * pMsg){
	WM_HWIN hItem;
	char buf[100];
	RTC_TimeTypeDef	stop_time;
	RTC_DateTypeDef stop_date;
		if(data.fan.state	)
		{
			HAL_RTC_GetTime(&RTC_Handler,&data.fan.Time,RTC_FORMAT_BIN); 
			HAL_RTC_GetDate(&RTC_Handler,&data.fan.Date,RTC_FORMAT_BIN);
		}else{
			HAL_RTC_GetTime(&RTC_Handler,&stop_time,RTC_FORMAT_BIN); 
			HAL_RTC_GetDate(&RTC_Handler,&stop_date,RTC_FORMAT_BIN);
			if(&stop_date == &data.fan.Date){
				data.fan.Last_run_min= 10;//stop_time.Minutes - data.fan.Time.Minutes;
			}
		}
		hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_0);
		TEXT_SetFont(hItem,&GUI_FontHZ16);
		//TEXT_SetTextColor(hItem,GUI_YELLOW);
		sprintf(buf,"״̬:%d   %d�ϴ�����ʱ�䣺20%02d-%02d-%02d %02d:%02d:%02d   �ϴ����У�%d����",	data.fan.state,stop_time.Minutes,
					data.fan.Date.Year,data.fan.Date.Month,data.fan.Date.Date,
					data.fan.Time.Hours,data.fan.Time.Minutes,data.fan.Time.Seconds,
					data.fan.Last_run_min);
		TEXT_SetText(hItem, buf);
}
void update_List(WM_MESSAGE * pMsg,int number){	
	WM_HWIN hItem;
	int i,j;
	char buf[40];
	for(i = 0; i<7;i++)
		for(j = 0;j<5;j++)
				transmitter[i][j]=(char *)mymalloc(SRAMIN,40);		//����40�ֽڵ��ڴ�����
	for(i=0; i<7;i++){
		sprintf((char*)transmitter[i][0],"%d#������",data.transmitter[i+number].number);
		sprintf((char*)transmitter[i][1],"O2:%d ",data.transmitter[i+number].O2);
		sprintf((char*)transmitter[i][2],"CO2:%dPPM",data.transmitter[i+number].CO2);
		sprintf((char*)transmitter[i][3],"20%02d-%02d-%02d %02d:%02d:%02d",
					data.transmitter[i+number].Date.Year,data.transmitter[i+number].Date.Month,data.transmitter[i+number].Date.Date,
					data.transmitter[i+number].Time.Hours,data.transmitter[i+number].Time.Minutes,data.transmitter[i+number].Time.Seconds);		
		sprintf((char*)transmitter[i][4],"%d����",data.transmitter[i+number].alarm);
	}	
	hItem = WM_GetDialogItem(pMsg->hWin, ID_LISTVIEW_0);
	for(i=0;i<GUI_COUNTOF(transmitter);i++)
	{
		LISTVIEW_SetUserDataRow(hItem,i,transmitter[i]);
	}
}
	
//�Ի��򴰿ڻص�����
static void _cbDialog(WM_MESSAGE * pMsg) 
{	
	WM_HWIN hItem;
	WM_HWIN hHeader;
	int     NCode;
	int     Id;
	int 	i;
	switch (pMsg->MsgId) 
	{
		case WM_INIT_DIALOG:
			
			//��ʼ��FRAMEWIN
			hwin_data= pMsg->hWin;
			hItem = pMsg->hWin;
			FRAMEWIN_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
			FRAMEWIN_SetTitleHeight(hItem, 1);
			FRAMEWIN_SetFont(hItem,&GUI_FontHZ16);
			//FRAMEWIN_SetTextColor(hItem, GUI_RED);
			//FRAMEWIN_SetText(hItem, "��ʾ");
		
			//��ʼ��BUTTON
			hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_0);
			BUTTON_SetFont(hItem,&GUI_FontHZ32);
			BUTTON_SetText(hItem,"ϵͳ����");
			hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_1);
			BUTTON_SetFont(hItem,&GUI_FontHZ32);
			BUTTON_SetText(hItem,"�豸����");
			hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_2);
			BUTTON_SetFont(hItem,&GUI_FontHZ32);
			BUTTON_SetText(hItem,"ʵʱ����");
			hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_3);
			BUTTON_SetFont(hItem,&GUI_FontHZ32);
			BUTTON_SetText(hItem,"��ʷ����");
			hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_4);
			BUTTON_SetFont(hItem,&GUI_FontHZ32);
			BUTTON_SetText(hItem,"�����¼");
			hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_5);
			BUTTON_SetFont(hItem,&GUI_FontHZ32);
			BUTTON_SetText(hItem,"ʹ�ð���");
			hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_6);
			BUTTON_SetFont(hItem,&GUI_FontHZ24);
			if(data.fan.state)
				BUTTON_SetText(hItem,"ֹͣ");
			else
				BUTTON_SetText(hItem,"��ʼ");
		
  
			//��ʼ��LISTVIEW
			hItem = WM_GetDialogItem(pMsg->hWin, ID_LISTVIEW_0);
			hHeader = LISTVIEW_GetHeader(hItem);
			LISTVIEW_SetHeaderHeight(hItem, 100);
			HEADER_SetFont(hHeader,&GUI_FontHZ24);
			LISTVIEW_AddColumn(hItem, 100, "����", GUI_TA_HCENTER | GUI_TA_VCENTER);
			LISTVIEW_AddColumn(hItem, 140, "����", GUI_TA_HCENTER | GUI_TA_VCENTER);
			LISTVIEW_AddColumn(hItem, 140, "������̼", GUI_TA_HCENTER | GUI_TA_VCENTER);
			LISTVIEW_AddColumn(hItem, 200, "ʱ��", GUI_TA_HCENTER | GUI_TA_VCENTER);
			LISTVIEW_AddColumn(hItem, 160, "������Ϣ", GUI_TA_HCENTER | GUI_TA_VCENTER);
			LISTVIEW_SetGridVis(hItem, 1);
			LISTVIEW_SetAutoScrollH(hItem, 1);
			LISTVIEW_SetAutoScrollV(hItem, 1);
			LISTVIEW_SetRowHeight(hItem, 30);
			LISTVIEW_SetFont(hItem,&GUI_FontHZ16);
			LISTVIEW_SetBkColor(hItem,LISTVIEW_CI_UNSEL,GUI_ORANGE);
			for(i=0;i<GUI_COUNTOF(_ListViewTable);i++)
			{
				LISTVIEW_AddRow(hItem,_ListViewTable[i]);
			}
			update_List(pMsg,0);
 
			//��ʼ��TEXT
			update_fan(pMsg);
			hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_6);
			TEXT_SetFont(hItem,&GUI_FontHZ16);
			TEXT_SetText(hItem, "���");					
			break;
		case WM_NOTIFY_PARENT:
			Id = WM_GetId(pMsg->hWinSrc);
			NCode = pMsg->Data.v;
			switch(Id) 
			{
				case ID_MULTIEDIT_0: 
					switch(NCode) 
					{
						case WM_NOTIFICATION_CLICKED:
						
							break;
						case WM_NOTIFICATION_RELEASED:
							
							break;
						case WM_NOTIFICATION_VALUE_CHANGED:
							
						break;
					}
					break;
				case ID_BUTTON_0: //ϵͳ����
					switch(NCode) 
					{
						case WM_NOTIFICATION_RELEASED:
							CreateSys_Set();
							break;
					}
					break;
				case ID_BUTTON_1://�豸����
					switch(NCode) 
					{
						case WM_NOTIFICATION_RELEASED:
							CreateDevice_Config();
							break;
					}
					break;
				case ID_BUTTON_2://ʵʱ����
					switch(NCode) 
					{
						case WM_NOTIFICATION_RELEASED:
							
							break;
					}
					break;
				case ID_BUTTON_3://��ʷ����
					switch(NCode) 
					{
						case WM_NOTIFICATION_RELEASED:
							CreateHistorical_Data();
							break;
					}
					break;
				case ID_BUTTON_4://�����¼
					switch(NCode) 
					{
						case WM_NOTIFICATION_RELEASED:
							CreateFan_Record();
							break;
					}
					break;
				case ID_BUTTON_5://����
					switch(NCode) 
					{
						case WM_NOTIFICATION_RELEASED:							
							CreateHELP();
							break;
					}
					break;
				case ID_BUTTON_6://״̬�л�
					hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_6);
					switch(NCode) 
					{
						case WM_NOTIFICATION_RELEASED:					
							if(data.fan.state){
								data.fan.state = 0;
								BUTTON_SetText(hItem,"��ʼ");
								update_fan(pMsg);
							}else{								
								data.fan.state = 1;
								BUTTON_SetText(hItem,"ֹͣ");
								update_fan(pMsg);
							}
							break;
					}
					break;
			}
			break;
		case WM_TIMER:
			WM_RestartTimer(pMsg->Data.v, 1000);
			GetSysTime();
			hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_4);
			TEXT_SetFont(hItem,&GUI_FontHZ24);
			//TEXT_SetTextColor(hItem,GUI_YELLOW);
			TEXT_SetText(hItem, timebuf);		
			for(i=0;i<MAX_TRANSMITTER;i+=8){
				update_List(pMsg,i);
			}
			break;
		default:
			WM_DefaultProc(pMsg);
			break;
	}
}

//���ڻص�����
//pMsg:��Ϣ
static void _cbBkWindow(WM_MESSAGE *pMsg)
{
	//WM_HWIN hItem;
	switch(pMsg->MsgId)
	{
		case WM_PAINT:
			GUI_SetBkColor(GUI_BLUE);
			GUI_Clear();
		default:
			WM_DefaultProc(pMsg);
	}
}

static void _cbWin(WM_MESSAGE * pMsg){
//	WM_HWIN hItem;
	switch (pMsg->MsgId) {
  default:
    WM_DefaultProc(pMsg);
  }

}
void HZFontDemo(void) 
{
	int i;
	GUI_CURSOR_Show();
	#if GUI_SUPPORT_MEMDEV
		WM_SetCreateFlags(WM_CF_MEMDEV);
	#endif		
	data.fan.state = 0;
	data.fan.Last_run_min = 0;
	for(i = 1;i<MAX_TRANSMITTER;i++){
		data.transmitter[i].number=i;
		data.transmitter[i].O2	= i;
		data.transmitter[i].CO2 = i;
		data.transmitter[i].alarm = i;
	}
  WM_SetCallback(WM_HBKWIN,_cbBkWindow);
	hDialog = GUI_CreateDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), _cbDialog, WM_HBKWIN, 0, 0);
	
	WM_HTIMER hTimer;
	hTimer = WM_CreateTimer(WM_GetClientWindow(hDialog), 0, 1000, 0);
	
	GUI_Exec();
	while(1)
	{
		GUI_Delay(100);
	}
}
