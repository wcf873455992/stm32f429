#include "hzfontdemo.h"
#include "EmWinHZFont.h"
#include "DIALOG.h"
//#include "help.h"
#include "rtc.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK STM32开发板
//STemwin 外置字库汉字显示    
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//创建日期:2016/3/30
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	


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

WM_HWIN hDialog;
WM_HWIN hDialog_help_t;

static const char *_ListViewTable[][5]={
	{"1#变送器",	"20.5%","300PPM","2019-5-11 18:34:20", "CO2超标"},
	{"2#变送器",	"20.5%","300PPM","2019-5-11 18:34:20", " "},
	{"3#变送器",	"20.5%","300PPM","2019-5-11 18:34:20", "O2超标"},
	{"4#变送器",	"20.5%","300PPM","2019-5-11 18:34:20", " "},
	{"5#变送器",	"20.5%","300PPM","2019-5-11 18:34:20", " "},
	{"6#变送器",	"20.5%","300PPM","2019-5-11 18:34:20", " "},
	{"7#变送器",	"20.5%","300PPM","2019-5-11 18:34:20", "  "},
};

char *MultiEdit_String	=  
"STM32F4/F7阿波罗开发板\r\n\
CPU:STM32F429/F746\r\n\
FLASH:1M\r\n\
RAM	 :240/256K\r\n\
板载:10M/100M以太网PHY芯片\r\n\
     WM8978音频DAC	";
	
//对话框资源列表
static const GUI_WIDGET_CREATE_INFO _aDialogCreate[] = {
  { FRAMEWIN_CreateIndirect, 	"Framewin", 	ID_FRAMEWIN_0, 	0, 		0, 		800, 	480, 	FRAMEWIN_CF_MOVEABLE, 0x64, 0 },
  //{ MULTIEDIT_CreateIndirect, 	"Multiedit", 	ID_MULTIEDIT_0, 20, 	250, 	300, 	160, 	0, 0x0, 0 },
  { BUTTON_CreateIndirect, 		"系统设置", 		ID_BUTTON_0, 	1,	0, 	133, 	50, 	0, 0x0, 0 },
  { BUTTON_CreateIndirect, 		"设备配置", 		ID_BUTTON_1, 	134,	0, 	133, 	50, 	0, 0x0, 0 },
  { BUTTON_CreateIndirect, 		"实时数据", 		ID_BUTTON_2, 	267,	0, 	133, 	50, 	0, 0x0, 0 },
  { BUTTON_CreateIndirect, 		"历史数据", 		ID_BUTTON_3, 	400,	0, 	133, 	50, 	0, 0x0, 0 },
  { BUTTON_CreateIndirect, 		"风机记录", 		ID_BUTTON_4, 	533,	0, 	133, 	50, 	0, 0x0, 0 },
  { BUTTON_CreateIndirect, 		"使用帮助", 		ID_BUTTON_5, 	666, 	0, 	133, 	50, 	0, 0x0, 0 },
  { BUTTON_CreateIndirect, 		"状态切换", 		ID_BUTTON_6, 	25, 	390, 	100, 	30, 	0, 0x0, 0 },
  //{ CHECKBOX_CreateIndirect, 	"Checkbox", 	ID_CHECKBOX_0, 	530, 	90, 	120, 	30, 	0, 0x0, 0 },
  //{ CHECKBOX_CreateIndirect, 	"Checkbox",		ID_CHECKBOX_1, 	530, 	130, 	120, 	30, 	0, 0x0, 0 },
  //{ CHECKBOX_CreateIndirect, 	"Checkbox", 	ID_CHECKBOX_2, 	530, 	170, 	120, 	30, 	0, 0x0, 0 },
  //{ CHECKBOX_CreateIndirect, 	"Checkbox", 	ID_CHECKBOX_3, 	530, 	210, 	120, 	30, 	0, 0x0, 0 },
  //{ RADIO_CreateIndirect, 		"Radio", 		ID_RADIO_0, 	650, 	119, 	90, 	90, 	0, 0x1404,0 },
  { LISTVIEW_CreateIndirect, 	"Listview", 	ID_LISTVIEW_0, 	5, 	55, 	780, 	300, 	0, 0x0, 0 },
  //{ LISTVIEW_CreateIndirect, 	"Listview", 	ID_LISTVIEW_1, 	5, 	0, 	780, 	50, 	0, 0x0, 0 },
  //{ DROPDOWN_CreateIndirect, 	"Dropdown", 	ID_DROPDOWN_0, 	324, 	22, 	150, 	100, 	0, 0x0, 0 },
  { TEXT_CreateIndirect, 		"状态", 		ID_TEXT_0, 		160, 	398, 	700, 	30, 	0, 0x64, 0 },
  //{ TEXT_CreateIndirect, 		"上次运行", 		ID_TEXT_1, 		240, 	398, 	110, 	30, 	0, 0x64, 0 },
  //{ TEXT_CreateIndirect, 		"上次运行时间", 		ID_TEXT_2, 		550, 	398, 	90, 	30, 	0, 0x64, 0 },
  //{ TEXT_CreateIndirect, 		"分钟", 		ID_TEXT_3, 		730, 	398, 	30, 	30, 	0, 0x64, 0 },
  { TEXT_CreateIndirect, 		"系统时间", 		ID_TEXT_4, 		280, 	440, 	500, 	35, 	0, 0x64, 0 },
  { TEXT_CreateIndirect, 		"时间测试", 		ID_TEXT_5, 		0, 	440, 	200, 	35, 	0, 0x64, 0 },
  { TEXT_CreateIndirect, 		"风机", 		ID_TEXT_6, 		20, 	360, 	30, 	30, 	0, 0x64, 0 },
  //{ SCROLLBAR_CreateIndirect, 	"Scrollbar", 	ID_SCROLLBAR_0, 482, 	310, 	260, 	40, 	0, 0x0, 0 },
  //{ SLIDER_CreateIndirect, 		"Slider", 		ID_SLIDER_0, 	513, 	18, 	259, 	38, 	0, 0x0, 0 },
};

static const GUI_WIDGET_CREATE_INFO _aDialogCreate_help_t[] = {
  { FRAMEWIN_CreateIndirect, 	"Framewin", 	ID_FRAMEWIN_0, 	0, 		0, 		800, 	480, 	FRAMEWIN_CF_MOVEABLE, 0x64, 0 },
  //{ MULTIEDIT_CreateIndirect, 	"Multiedit", 	ID_MULTIEDIT_0, 20, 	250, 	300, 	160, 	0, 0x0, 0 },
  { BUTTON_CreateIndirect, 		"help", 		ID_BUTTON_0, 	1,	0, 	133, 	50, 	0, 0x0, 0 },
};


u8 timebuf[40];
void GetSysTime(){
	RTC_TimeTypeDef	RTC_TimeStruct;
	RTC_DateTypeDef RTC_DateStruct;
	
	HAL_RTC_GetTime(&RTC_Handler,&RTC_TimeStruct,RTC_FORMAT_BIN); 
	HAL_RTC_GetDate(&RTC_Handler,&RTC_DateStruct,RTC_FORMAT_BIN);
	sprintf((char*)timebuf,"系统时间：20%02d-%02d-%02d %02d:%02d:%02d  版本V1.0",
				RTC_DateStruct.Year,RTC_DateStruct.Month,RTC_DateStruct.Date,
				RTC_TimeStruct.Hours,RTC_TimeStruct.Minutes,RTC_TimeStruct.Seconds); 
		
}

//对话框窗口回调函数
static void _cbDialog_help_t(WM_MESSAGE * pMsg) 
{
	WM_HWIN hItem;
	WM_HWIN hHeader;
	int     NCode;
	int     Id;
	
	hItem = pMsg->hWin;
	switch (pMsg->MsgId) 
	{
		case WM_INIT_DIALOG:
			//初始化BUTTON
			hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_0);
			BUTTON_SetFont(hItem,&GUI_FontHZ16);
			BUTTON_SetText(hItem,"关闭");
			break;		
		case WM_NOTIFY_PARENT:
			Id = WM_GetId(pMsg->hWinSrc);
			NCode = pMsg->Data.v;
			switch(Id) 
			{case ID_BUTTON_0: //系统设置
					switch(NCode) 
					{
						case WM_NOTIFICATION_RELEASED:
							GUI_EndDialog(hItem,0);
							break;
					}
					break;
			
			
			}
		default:
			WM_DefaultProc(pMsg);
			break;
	}
}
	
//对话框窗口回调函数
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
			
			//初始化FRAMEWIN
			hItem = pMsg->hWin;
			FRAMEWIN_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
			FRAMEWIN_SetTitleHeight(hItem, 10);
			FRAMEWIN_SetFont(hItem,&GUI_FontHZ16);
			FRAMEWIN_SetTextColor(hItem, GUI_RED);
			FRAMEWIN_SetText(hItem, "显示");
		
			//初始化MULTIEDIT
			hItem = WM_GetDialogItem(pMsg->hWin, ID_MULTIEDIT_0);
			MULTIEDIT_SetTextColor(hItem,MULTIEDIT_CI_EDIT,GUI_BLACK);
			MULTIEDIT_SetBkColor(hItem,MULTIEDIT_CI_EDIT,GUI_LIGHTCYAN);
			MULTIEDIT_SetFont(hItem,&GUI_FontHZ16);
			MULTIEDIT_SetText(hItem,MultiEdit_String);
            MULTIEDIT_EnableBlink(hItem,500,1);
		
			//初始化BUTTON
			hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_0);
			BUTTON_SetFont(hItem,&GUI_FontHZ32);
			BUTTON_SetText(hItem,"系统设置");
			hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_1);
			BUTTON_SetFont(hItem,&GUI_FontHZ32);
			BUTTON_SetText(hItem,"设备配置");
			hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_2);
			BUTTON_SetFont(hItem,&GUI_FontHZ32);
			BUTTON_SetText(hItem,"实时数据");
			hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_3);
			BUTTON_SetFont(hItem,&GUI_FontHZ32);
			BUTTON_SetText(hItem,"历史数据");
			hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_4);
			BUTTON_SetFont(hItem,&GUI_FontHZ32);
			BUTTON_SetText(hItem,"风机记录");
			hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_5);
			BUTTON_SetFont(hItem,&GUI_FontHZ32);
			BUTTON_SetText(hItem,"使用帮助");
			hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_6);
			BUTTON_SetFont(hItem,&GUI_FontHZ24);
			BUTTON_SetText(hItem,"状态切换");
		
			//初始化CHECKBOX
			hItem = WM_GetDialogItem(pMsg->hWin, ID_CHECKBOX_0);
			CHECKBOX_SetFont(hItem,&GUI_FontHZ16);
			CHECKBOX_SetText(hItem, "复选框 1");
			hItem = WM_GetDialogItem(pMsg->hWin, ID_CHECKBOX_1);
			CHECKBOX_SetFont(hItem,&GUI_FontHZ16);
			CHECKBOX_SetText(hItem, "复选框 2");
			hItem = WM_GetDialogItem(pMsg->hWin, ID_CHECKBOX_2);
			CHECKBOX_SetFont(hItem,&GUI_FontHZ16);
			CHECKBOX_SetText(hItem, "复选框 3");
			hItem = WM_GetDialogItem(pMsg->hWin, ID_CHECKBOX_3);
			CHECKBOX_SetFont(hItem,&GUI_FontHZ16);
			CHECKBOX_SetText(hItem, "复选框 4");
		
			//初始化RADIO
			hItem = WM_GetDialogItem(pMsg->hWin, ID_RADIO_0);
			RADIO_SetFont(hItem,&GUI_Font13HB_ASCII);
            RADIO_SetText(hItem, "Option 1", 0);
			RADIO_SetText(hItem, "Option 2", 1);
			RADIO_SetText(hItem, "Option 3", 2);
			RADIO_SetText(hItem, "Option 4", 3);
  
			//初始化LISTVIEW
			hItem = WM_GetDialogItem(pMsg->hWin, ID_LISTVIEW_0);
			hHeader = LISTVIEW_GetHeader(hItem);
			LISTVIEW_SetHeaderHeight(hItem, 100);
			HEADER_SetFont(hHeader,&GUI_FontHZ24);
			LISTVIEW_AddColumn(hItem, 100, "名称", GUI_TA_HCENTER | GUI_TA_VCENTER);
			LISTVIEW_AddColumn(hItem, 140, "氧气", GUI_TA_HCENTER | GUI_TA_VCENTER);
			LISTVIEW_AddColumn(hItem, 140, "二氧化碳", GUI_TA_HCENTER | GUI_TA_VCENTER);
			LISTVIEW_AddColumn(hItem, 200, "时间", GUI_TA_HCENTER | GUI_TA_VCENTER);
			LISTVIEW_AddColumn(hItem, 160, "报警信息", GUI_TA_HCENTER | GUI_TA_VCENTER);
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
			//初始化DROPDOWN
			hItem = WM_GetDialogItem(pMsg->hWin, ID_DROPDOWN_0);
			DROPDOWN_SetAutoScroll(hItem,1);//开启自动滚动条
			DROPDOWN_SetFont(hItem,&GUI_FontHZ16);
			DROPDOWN_AddString(hItem, "汉语");
			DROPDOWN_AddString(hItem, "英语");
			DROPDOWN_AddString(hItem, "韩语");
			DROPDOWN_AddString(hItem, "马来西亚语");
			DROPDOWN_AddString(hItem, "西班牙语");
			DROPDOWN_AddString(hItem, "其他语言......");
 
			//初始化TEXT
			hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_0);
			TEXT_SetFont(hItem,&GUI_FontHZ16);
			//TEXT_SetTextColor(hItem,GUI_YELLOW);
			TEXT_SetText(hItem, "状态:关闭   上次运行时间：2019-5-11 18:23:45   上次运行：18分钟");	
			/*hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_1);
			TEXT_SetFont(hItem,&GUI_FontHZ16);
			//TEXT_SetTextColor(hItem,GUI_YELLOW);
			TEXT_SetText(hItem, "上次运行时间");			
			hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_2);
			TEXT_SetFont(hItem,&GUI_FontHZ16);
			//TEXT_SetTextColor(hItem,GUI_YELLOW);
			TEXT_SetText(hItem, "上次运行");			
			hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_3);
			TEXT_SetFont(hItem,&GUI_FontHZ16);
			//TEXT_SetTextColor(hItem,GUI_YELLOW);
			TEXT_SetText(hItem, "分钟");	*/		
			//hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_4);
			//TEXT_SetFont(hItem,&GUI_FontHZ24);
			//TEXT_SetTextColor(hItem,GUI_YELLOW);
			//TEXT_SetText(hItem, "系统时间:2019-5-11 18:23:45   版本：V1.0");			
			//hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_5);
			//TEXT_SetFont(hItem,&GUI_FontHZ24);
			//TEXT_SetTextColor(hItem,GUI_YELLOW);
			//TEXT_SetText(hItem, "版本V1.0");			
			hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_6);
			TEXT_SetFont(hItem,&GUI_FontHZ16);
			//TEXT_SetTextColor(hItem,GUI_YELLOW);
			TEXT_SetText(hItem, "风机");					
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
				case ID_BUTTON_0: //系统设置
					switch(NCode) 
					{
						case WM_NOTIFICATION_RELEASED:
							CreateSys_Set();
							break;
					}
					break;
				case ID_BUTTON_1://设备配置
					switch(NCode) 
					{
						case WM_NOTIFICATION_RELEASED:
							CreateDevice_Config();
							break;
					}
					break;
				case ID_BUTTON_2://实时数据
					switch(NCode) 
					{
						case WM_NOTIFICATION_RELEASED:
							
							break;
					}
					break;
				case ID_BUTTON_3://历史数据
					switch(NCode) 
					{
						case WM_NOTIFICATION_RELEASED:
							CreateHistorical_Data();
							break;
					}
					break;
				case ID_BUTTON_4://风机记录
					switch(NCode) 
					{
						case WM_NOTIFICATION_RELEASED:
							CreateFan_Record();
							break;
					}
					break;
				case ID_BUTTON_5://帮助
					switch(NCode) 
					{
						case WM_NOTIFICATION_RELEASED:							
							CreateHELP();
							break;
					}
					break;
				case ID_BUTTON_6://状态切换
					switch(NCode) 
					{
						case WM_NOTIFICATION_RELEASED:	
							hDialog_help_t=GUI_CreateDialogBox(_aDialogCreate_help_t, GUI_COUNTOF(_aDialogCreate_help_t), _cbDialog_help_t, hDialog, 0, 0);
							break;
					}
					break;
			}
			break;
		case WM_TIMER:
			GetSysTime();
			hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_4);
			TEXT_SetFont(hItem,&GUI_FontHZ24);
			//TEXT_SetTextColor(hItem,GUI_YELLOW);
			TEXT_SetText(hItem, timebuf);		
			WM_RestartTimer(pMsg->Data.v, 1000);
			break;
		default:
			WM_DefaultProc(pMsg);
			break;
	}
}

//窗口回掉函数
//pMsg:消息
static void _cbBkWindow(WM_MESSAGE *pMsg)
{
	WM_HWIN hItem;
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
	WM_HWIN hItem;
	switch (pMsg->MsgId) {
  default:
    WM_DefaultProc(pMsg);
  }

}
void HZFontDemo(void) 
{
	GUI_CURSOR_Show();
	#if GUI_SUPPORT_MEMDEV
		WM_SetCreateFlags(WM_CF_MEMDEV);
	#endif		
  WM_SetCallback(WM_HBKWIN,_cbBkWindow);
	hDialog = GUI_CreateDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), _cbDialog, WM_HBKWIN, 0, 0);
	
	WM_HTIMER hTimer;
	hTimer = WM_CreateTimer(WM_GetClientWindow(hDialog), 0, 1000, 0);
	
	GUI_Exec();
	while(1)
	{
		GUI_Delay(100);
	}/**/
}
