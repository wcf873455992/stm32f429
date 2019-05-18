/*********************************************************************
*                                                                    *
*                SEGGER Microcontroller GmbH & Co. KG                *
*        Solutions for real time microcontroller applications        *
*                                                                    *
**********************************************************************
*                                                                    *
* C-file generated by:                                               *
*                                                                    *
*        GUI_Builder for emWin version 5.30                          *
*        Compiled Jul  1 2015, 10:50:32                              *
*        (c) 2015 Segger Microcontroller GmbH & Co. KG               *
*                                                                    *
**********************************************************************
*                                                                    *
*        Internet: www.segger.com  Support: support@segger.com       *
*                                                                    *
**********************************************************************
*/

// USER START (Optionally insert additional includes)
#include "hzfontdemo.h"
#include "EmWinHZFont.h"
#include "ff.h"
#include "exfuns.h"
#include "malloc.h"
#include "rtc.h"
// USER END

#include "DIALOG.h"

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
#define ID_FRAMEWIN_0     (GUI_ID_USER + 0x00)
#define ID_TEXT_0     (GUI_ID_USER + 0x01)
#define ID_EDIT_0     (GUI_ID_USER + 0x02)
#define ID_EDIT_1     (GUI_ID_USER + 0x03)
#define ID_BUTTON_0     (GUI_ID_USER + 0x04)
#define ID_LISTVIEW_0     (GUI_ID_USER + 0x05)
#define ID_SCROLLBAR_0     (GUI_ID_USER + 0x06)
#define ID_TEXT_1     (GUI_ID_USER + 0x07)
#define ID_EDIT_2     (GUI_ID_USER + 0x08)
#define ID_EDIT_3     (GUI_ID_USER + 0x09)
#define ID_BUTTON_1     (GUI_ID_USER + 0x0A)
#define ID_BUTTON_2     (GUI_ID_USER + 0x0B)
#define ID_BUTTON_3     (GUI_ID_USER + 0x0C)


// USER START (Optionally insert additional defines)
extern WM_HWIN hDialog;
// USER END

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/

// USER START (Optionally insert additional static data)

static const	char *pname_fan ="0:fan/fan_record.xls";
// USER END

/*********************************************************************
*
*       _aDialogCreate
*/
static const GUI_WIDGET_CREATE_INFO _aDialogCreate[] = {
  { FRAMEWIN_CreateIndirect, "Fan_Record", ID_FRAMEWIN_0, 0, 0, 800, 480, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "time", ID_TEXT_0, 26, 13, 113, 39, 0, 0x0, 0 },
  { EDIT_CreateIndirect, "Edit", ID_EDIT_0, 96, 20, 164, 30, 0, 0x64, 0 },
  { EDIT_CreateIndirect, "Edit", ID_EDIT_1, 334, 17, 155, 31, 0, 0x64, 0 },
  { BUTTON_CreateIndirect, "OK", ID_BUTTON_0, 584, 17, 123, 34, 0, 0x0, 0 },
  { LISTVIEW_CreateIndirect, "Listview", ID_LISTVIEW_0, 1, 57, 760, 308, 0, 0x0, 0 },
  { SCROLLBAR_CreateIndirect, "Scrollbar", ID_SCROLLBAR_0, 761, 60, 20, 305, 8, 0x0, 0 },
  { TEXT_CreateIndirect, "page", ID_TEXT_1, 44, 377, 314, 26, 0, 0x0, 0 },
  { EDIT_CreateIndirect, "Edit", ID_EDIT_2, 105, 373, 50, 27, 0, 0x64, 0 },
  { EDIT_CreateIndirect, "Edit", ID_EDIT_3, 199, 373, 48, 27, 0, 0x64, 0 },
  { BUTTON_CreateIndirect, "previous", ID_BUTTON_1, 276, 373, 98, 28, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "next", ID_BUTTON_2, 396, 373, 100, 28, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "close", ID_BUTTON_3, 575, 372, 114, 41, 0, 0x0, 0 },
  // USER START (Optionally insert additional widgets)
  // USER END
};

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/

// USER START (Optionally insert additional static code)

void save_fan_record(FAN * fan)
{	
	FIL *f_rec;
	u8 res;	
	char buf[100];
	
  f_rec=(FIL *)mymalloc(SRAMIN,sizeof(FIL));		//开辟FIL字节的内存区域 
	res=f_open(f_rec,(const TCHAR*)pname_fan, FA_READ | FA_WRITE); 
	if(res)			//文件创建失败
	{ 
		res=f_open(f_rec,(const TCHAR*)pname_fan, FA_CREATE_ALWAYS | FA_WRITE); 
		sprintf(buf,"序号\t开始时间\t结束时间\t运行时间\r\n");
		res=f_write(f_rec,(const void*)buf,strlen(buf),&bw);
		f_close(f_rec);
		res=f_open(f_rec,(const TCHAR*)pname_fan, FA_READ | FA_WRITE); 
	}
	
		res=f_lseek(f_rec,f_size(f_rec));
		sprintf(buf,"1\t20%02d-%02d-%02d %02d:%02d:%02d\t20%02d-%02d-%02d %02d:%02d:%02d \t%d\r\n",	
					fan->start_date.Year, fan->start_date.Month, fan->start_date.Date,
					fan->start_time.Hours, fan->start_time.Minutes, fan->start_time.Seconds,
					fan->end_date.Year, fan->end_date.Month, fan->end_date.Date,
					fan->end_time.Hours, fan->end_time.Minutes, fan->end_time.Seconds,
					fan->Last_run_min);
		res=f_write(f_rec,(const void*)buf,strlen(buf),&bw);
		f_close(f_rec);
	
	myfree(SRAMIN,f_rec);		//释放内存
}


// USER END

/*********************************************************************
*
*       _cbDialog
*/
static void _cbDialog(WM_MESSAGE * pMsg) {
  WM_HWIN hItem;
  int     NCode;
  int     Id;
  // USER START (Optionally insert additional variables)
	hItem = pMsg->hWin;
  // USER END

  switch (pMsg->MsgId) {
  case WM_INIT_DIALOG:
    //
    // Initialization of 'Fan_Record'
    //
    hItem = pMsg->hWin;
    FRAMEWIN_SetFont(hItem, GUI_FONT_32_ASCII);
    //
    // Initialization of 'time'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_0);
    TEXT_SetFont(hItem, GUI_FONT_32_ASCII);
    //
    // Initialization of 'Edit'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_EDIT_0);
    EDIT_SetText(hItem, "123");
    EDIT_SetFont(hItem, GUI_FONT_24_ASCII);
    //
    // Initialization of 'Edit'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_EDIT_1);
    EDIT_SetText(hItem, "123");
    EDIT_SetFont(hItem, GUI_FONT_24_ASCII);
    //
    // Initialization of 'OK'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_0);
    BUTTON_SetFont(hItem, GUI_FONT_24_ASCII);
    //
    // Initialization of 'Listview'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_LISTVIEW_0);
    LISTVIEW_AddColumn(hItem, 60, "Col 0", GUI_TA_HCENTER | GUI_TA_VCENTER);
    LISTVIEW_AddColumn(hItem, 350, "Col 1", GUI_TA_HCENTER | GUI_TA_VCENTER);
    LISTVIEW_AddColumn(hItem, 350, "Col 2", GUI_TA_HCENTER | GUI_TA_VCENTER);
    LISTVIEW_AddRow(hItem, NULL);
    LISTVIEW_SetGridVis(hItem, 1);
    LISTVIEW_SetFont(hItem, GUI_FONT_20_ASCII);
    //
    // Initialization of 'page'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_1);
    TEXT_SetFont(hItem, GUI_FONT_24_ASCII);
    //
    // Initialization of 'Edit'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_EDIT_2);
    EDIT_SetText(hItem, "123");
    EDIT_SetFont(hItem, GUI_FONT_24_ASCII);
    //
    // Initialization of 'Edit'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_EDIT_3);
    EDIT_SetText(hItem, "123");
    EDIT_SetFont(hItem, GUI_FONT_24_ASCII);
    //
    // Initialization of 'previous'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_1);
    BUTTON_SetFont(hItem, GUI_FONT_24_ASCII);
    //
    // Initialization of 'next'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_2);
    BUTTON_SetFont(hItem, GUI_FONT_24_ASCII);
    //
    // Initialization of 'close'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_3);
    BUTTON_SetFont(hItem, GUI_FONT_32_ASCII);
    // USER START (Optionally insert additional code for further widget initialization)
    // USER END
    break;
  case WM_NOTIFY_PARENT:
    Id    = WM_GetId(pMsg->hWinSrc);
    NCode = pMsg->Data.v;
    switch(Id) {
    case ID_EDIT_0: // Notifications sent by 'Edit'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_VALUE_CHANGED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_EDIT_1: // Notifications sent by 'Edit'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_VALUE_CHANGED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_BUTTON_0: // Notifications sent by 'OK'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_LISTVIEW_0: // Notifications sent by 'Listview'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_SEL_CHANGED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_SCROLLBAR_0: // Notifications sent by 'Scrollbar'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_VALUE_CHANGED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_EDIT_2: // Notifications sent by 'Edit'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_VALUE_CHANGED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_EDIT_3: // Notifications sent by 'Edit'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_VALUE_CHANGED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_BUTTON_1: // Notifications sent by 'previous'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_BUTTON_2: // Notifications sent by 'next'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_BUTTON_3: // Notifications sent by 'close'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
				GUI_EndDialog(hItem, 0 );
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    // USER START (Optionally insert additional code for further Ids)
    // USER END
    }
    break;
  // USER START (Optionally insert additional message handling)
  // USER END
  default:
    WM_DefaultProc(pMsg);
    break;
  }
}

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       CreateFan_Record
*/
WM_HWIN CreateFan_Record(void);
WM_HWIN CreateFan_Record(void) {
  WM_HWIN hWin;

  hWin = GUI_CreateDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), _cbDialog, WM_HBKWIN, 0, 0);
  return hWin;
}

// USER START (Optionally insert additional public code)
// USER END

/*************************** End of file ****************************/
