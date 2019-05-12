#include "help.h"
#include "EmWinHZFont.h"
#include "DIALOG.h"
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

WM_HWIN hDialog_help;



char *MultiEdit_Help	=  
"STM32F4/F7阿波罗开发板\r\n\
CPU:STM32F429/F746\r\n\
FLASH:1M\r\n\
RAM	 :240/256K\r\n\
板载:10M/100M以太网PHY芯片\r\n\
     WM8978音频DAC	";
	
//对话框资源列表
static const GUI_WIDGET_CREATE_INFO _aDialogCreate_help[] = {
  { FRAMEWIN_CreateIndirect, 	"使用帮助", 	ID_FRAMEWIN_0, 	0, 		0, 		800, 	480, 	FRAMEWIN_CF_MOVEABLE, 0x64, 0 },
  { MULTIEDIT_CreateIndirect, 	"帮助说明", 	ID_MULTIEDIT_0, 0, 	0, 	800, 	320, 	0, 0x0, 0 },
  { BUTTON_CreateIndirect, 		"上一页", 		ID_BUTTON_0, 	200,	370, 	70, 	30, 	0, 0x0, 0 },
  { BUTTON_CreateIndirect, 		"下一页", 		ID_BUTTON_1, 	300,	370, 	70, 	30, 	0, 0x0, 0 },
  { BUTTON_CreateIndirect, 		"关闭", 		ID_BUTTON_2, 	430,	370, 	50, 	30, 	0, 0x0, 0 },
  { TEXT_CreateIndirect, 		"页面信息", 		ID_TEXT_0, 		0, 	360, 	140, 	30, 	0, 0x64, 0 },
  //{ TEXT_CreateIndirect, 		"上次运行", 		ID_TEXT_1, 		240, 	398, 	110, 	30, 	0, 0x64, 0 },
  //{ TEXT_CreateIndirect, 		"上次运行时间", 		ID_TEXT_2, 		550, 	398, 	90, 	30, 	0, 0x64, 0 },
  //{ TEXT_CreateIndirect, 		"分钟", 		ID_TEXT_3, 		730, 	398, 	30, 	30, 	0, 0x64, 0 },
  //{ TEXT_CreateIndirect, 		"系统时间", 		ID_TEXT_4, 		375, 	440, 	100, 	35, 	0, 0x64, 0 },
  //{ TEXT_CreateIndirect, 		"版本", 		ID_TEXT_5, 		670, 	440, 	100, 	35, 	0, 0x64, 0 },
  //{ TEXT_CreateIndirect, 		"风机", 		ID_TEXT_6, 		20, 	360, 	30, 	30, 	0, 0x64, 0 },
  //{ TEXT_CreateIndirect, 		"Text1",  		ID_TEXT_1, 		327, 	200, 	150, 	20, 	0, 0x64, 0 },
  //{ TEXT_CreateIndirect, 		"Text2", 		ID_TEXT_2, 		327, 	220, 	200, 	30, 	0, 0x64, 0 },
  //{ TEXT_CreateIndirect, 		"Text3", 		ID_TEXT_3, 		327, 	250, 	300, 	50, 	0, 0x64, 0 },
  //{ SCROLLBAR_CreateIndirect, 	"Scrollbar", 	ID_SCROLLBAR_0, 482, 	310, 	260, 	40, 	0, 0x0, 0 },
  //{ SLIDER_CreateIndirect, 		"Slider", 		ID_SLIDER_0, 	513, 	18, 	259, 	38, 	0, 0x0, 0 },
};

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
			FRAMEWIN_SetTitleHeight(hItem, 30);
			FRAMEWIN_SetFont(hItem,&GUI_FontHZ24);
			FRAMEWIN_SetTextColor(hItem, GUI_RED);
			FRAMEWIN_SetText(hItem, "使用帮助");
		
			//初始化MULTIEDIT
			hItem = WM_GetDialogItem(pMsg->hWin, ID_MULTIEDIT_0);
			MULTIEDIT_SetTextColor(hItem,MULTIEDIT_CI_EDIT,GUI_BLACK);
			MULTIEDIT_SetBkColor(hItem,MULTIEDIT_CI_EDIT,GUI_LIGHTCYAN);
			MULTIEDIT_SetFont(hItem,&GUI_FontHZ16);
			MULTIEDIT_SetText(hItem,MultiEdit_Help);
            MULTIEDIT_EnableBlink(hItem,500,1);
		
			//初始化BUTTON
			hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_0);
			BUTTON_SetFont(hItem,&GUI_FontHZ24);
			BUTTON_SetText(hItem,"上一页");
			hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_1);
			BUTTON_SetFont(hItem,&GUI_FontHZ24);
			BUTTON_SetText(hItem,"下一页");
			hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_2);
			BUTTON_SetFont(hItem,&GUI_FontHZ24);
			BUTTON_SetText(hItem,"关闭");
		
		
  
			
 
			//初始化TEXT
			hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_0);
			TEXT_SetFont(hItem,&GUI_FontHZ16);
			//TEXT_SetTextColor(hItem,GUI_YELLOW);
			TEXT_SetText(hItem, "第 1 页  共 1 页");	
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
				case ID_BUTTON_0: 
					switch(NCode) 
					{
						case WM_NOTIFICATION_RELEASED:
							break;
					}
					break;
				case ID_BUTTON_1: 
					switch(NCode) 
					{
						case WM_NOTIFICATION_RELEASED:
							break;
					}
					break;
				case ID_BUTTON_2: 
					switch(NCode) 
					{
						case WM_NOTIFICATION_RELEASED:
							GUI_EndDialog(hDialog_help, 0 );
							break;
					}
					break;
					
			}
			break;
		default:
			WM_DefaultProc(pMsg);
			break;
	}
}

extern WM_HWIN hDialog;
void SysHelp(void) 
{
	GUI_CURSOR_Show();
	hDialog_help = GUI_CreateDialogBox(_aDialogCreate_help, GUI_COUNTOF(_aDialogCreate_help), _cbDialog, hDialog, 0, 0);	
	//GUI_Exec();
}
