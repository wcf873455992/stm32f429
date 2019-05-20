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
#include "EmWinHZFont.h"
#include "ini.h"
#include "ff.h"
#include "exfuns.h"
#include "malloc.h"
// USER END

#include "DIALOG.h"

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
#define ID_FRAMEWIN_0 (GUI_ID_USER + 0x00)
#define ID_DROPDOWN_0 (GUI_ID_USER + 0x01)
#define ID_DROPDOWN_1 (GUI_ID_USER + 0x02)
#define ID_DROPDOWN_2 (GUI_ID_USER + 0x03)
#define ID_TEXT_0 (GUI_ID_USER + 0x04)
#define ID_TEXT_1 (GUI_ID_USER + 0x05)
#define ID_TEXT_2 (GUI_ID_USER + 0x06)
#define ID_BUTTON_0 (GUI_ID_USER + 0x07)
#define ID_BUTTON_1 (GUI_ID_USER + 0x08)
#define ID_BUTTON_2 (GUI_ID_USER + 0x09)
#define ID_BUTTON_3 (GUI_ID_USER + 0x0A)
#define ID_BUTTON_4 (GUI_ID_USER + 0x0B)
#define ID_BUTTON_5 (GUI_ID_USER + 0x0C)
#define ID_EDIT_0 (GUI_ID_USER + 0x0D)
#define ID_TEXT_3 (GUI_ID_USER + 0x0E)
#define ID_LISTVIEW_0 (GUI_ID_USER + 0x0F)


// USER START (Optionally insert additional defines)
extern WM_HWIN hDialog;
#define MAX_DEVICE_NUMBER	50
#define MAX_NAME_LONG		30
#define MAX_TYPE_LONG		30
typedef struct{
	int number;
	char addr;
	char name[MAX_NAME_LONG];
	char	type[MAX_TYPE_LONG];
	char	state[20];
}DEVICE_INI;
DEVICE_INI device[MAX_DEVICE_NUMBER];
// USER END

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/

// USER START (Optionally insert additional static data)

INI_FILE device_ini;
static const char *filename_device = "0:device.ini";
static int device_number;
static int cur_number;
static  char *device_listView1[7][5];
static  char *device_listView[7][5]={
	{"11   ",	"101", "客厅",	"温湿度变送器", "正常"},
	{"21   ",	"202", "餐厅",	"双气体变送器", "正常"},
	{"31   ",	"303", "厨房",	"双气体变送器", "正常"},
	{"41   ",	"404", "卧室",	"温湿度变送器", "异常"},
	{"51   ",	"505", "储藏室","双气体变送器", "正常"},
	{"61   ",	"606", "大门",	"双气体变送器", "正常"},
	{"71   ",	"707", "院子",	"双气体变送器", "正常"},
};
// USER END

/*********************************************************************
*
*       _aDialogCreate
*/
static const GUI_WIDGET_CREATE_INFO _aDialogCreate[] = {
  { FRAMEWIN_CreateIndirect, "Device_Config", ID_FRAMEWIN_0, 0, 0, 800, 480, 0, 0x0, 0 },
  { DROPDOWN_CreateIndirect, "Dropdown", ID_DROPDOWN_0, 700, 56, 80, 29, 0, 0x0, 0 },
  { DROPDOWN_CreateIndirect, "Dropdown", ID_DROPDOWN_1, 702, 13, 80, 29, 0, 0x0, 0 },
  { DROPDOWN_CreateIndirect, "Dropdown", ID_DROPDOWN_2, 642, 121, 142, 29, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "address", ID_TEXT_0, 644, 16, 62, 23, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "name", ID_TEXT_1, 644, 56, 61, 29, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "type", ID_TEXT_2, 649, 92, 56, 30, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "close", ID_BUTTON_0, 677, 312, 87, 35, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "del", ID_BUTTON_1, 676, 258, 85, 32, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "modification ", ID_BUTTON_2, 676, 208, 86, 29, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "add", ID_BUTTON_3, 674, 159, 83, 26, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "previous", ID_BUTTON_4, 344, 377, 91, 26, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "next", ID_BUTTON_5, 462, 375, 92, 26, 0, 0x0, 0 },
  { EDIT_CreateIndirect, "Edit", ID_EDIT_0, 80, 378, 46, 28, 0, 0x64, 0 },
  { TEXT_CreateIndirect, "page", ID_TEXT_3, 38, 378, 276, 28, 0, 0x0, 0 },
  { LISTVIEW_CreateIndirect, "Listview", ID_LISTVIEW_0, 0, 0, 638, 364, 0, 0x0, 0 },
  // USER START (Optionally insert additional widgets)
  // USER END
};

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/
static void update_device_List(WM_MESSAGE * pMsg, int number){
	int i,j;
	WM_HWIN hItem;
	
	for(i=0; i<7;i++){
		if((i+number) > (device_number-1)){
			for(j = 0; j<5; j++)
				sprintf((char*)device_listView[i][j],"");
		}else{
			sprintf((char*)device_listView[i][0],"%d",device[number].number);
			//sprintf((char*)device_listView[i][1],"%d",device[number].addr);
			//device_listView[i][0] = device[number].name;
			device_listView[i][1] = &device[number].addr;
			device_listView[i][2] = device[number].type;
			device_listView[i][3] = device[number].state;
			//sprintf((char*)device_listView[i][3],"%d",device[number].state);
		}
	}
	hItem = WM_GetDialogItem(pMsg->hWin, ID_LISTVIEW_0);
	for (i = 0; i < 7; i++)
		for (j = 0; j < GUI_COUNTOF(device_listView[i]); j++) {
				LISTVIEW_SetItemText(hItem, j, i, device_listView[i][j]);
		}
}
static int read_device_ini(INI_FILE *file ){	
	int i,n;
	char number[10];
 	
	iniFileLoad(file);
	//for(i=0;i<MAX_DEVICE_NUMBER;i++){
	for(i=0, device_number =0;i<10;i++){
		device[i].number = i+1;
		sprintf(number,"NUMBER=%d",i+1);
		//device[i].addr 	=iniGetInt(file, number, "ADDR",  0);
		iniGetString(file, number, "ADDR", device[i].name,MAX_NAME_LONG, "no name");
		//if(device[i].addr == 0)break;
		iniGetString(file, number, "NAME", device[i].name,MAX_NAME_LONG, "no name");
		iniGetString(file, number, "TYPE",device[i].type, MAX_TYPE_LONG,"no type");
		iniGetString(file, number, "STATE",device[i].state, MAX_TYPE_LONG,"no state");
		//device[i].state 	=iniGetInt(file, "NUMBER=1", "STATE",  1);
		device_number++;
	}
	
	iniFileFree(file);
}
// USER START (Optionally insert additional static code)
static void init(WM_MESSAGE * pMsg){
	WM_HWIN hItem;
	WM_HWIN hHeader;
  int     NCode;
  int     Id;
	int i;
	//初始化FRAMEWIN
	hItem = pMsg->hWin;
	//FRAMEWIN_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
	//FRAMEWIN_SetTitleHeight(hItem, 10);
	FRAMEWIN_SetFont(hItem,&GUI_FontHZ32);
	//FRAMEWIN_SetTextColor(hItem, GUI_RED);
	FRAMEWIN_SetText(hItem, "设备配置");
    
	
    // Initialization of 'Dropdown'
    hItem = WM_GetDialogItem(pMsg->hWin, ID_DROPDOWN_2);
    DROPDOWN_SetFont(hItem, &GUI_FontHZ16);
    DROPDOWN_AddString(hItem, "双气体变送器");
    DROPDOWN_AddString(hItem, "温湿度变送器");
	
		hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_0);
		TEXT_SetFont(hItem,&GUI_FontHZ24);		
		TEXT_SetText(hItem, "地址");	
		hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_1);
		TEXT_SetFont(hItem,&GUI_FontHZ24);		
		TEXT_SetText(hItem, "名称");	
		hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_2);
		TEXT_SetFont(hItem,&GUI_FontHZ24);		
		TEXT_SetText(hItem, "类型");	
		hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_3);
		TEXT_SetFont(hItem,&GUI_FontHZ24);		
		TEXT_SetText(hItem, "第       页，共5页");	
    // Initialization of 'close'
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_0);
    BUTTON_SetFont(hItem, &GUI_FontHZ24);
    BUTTON_SetText(hItem, "关闭");
    // Initialization of 'del'
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_1);
    BUTTON_SetFont(hItem, &GUI_FontHZ24);
    BUTTON_SetText(hItem, "删除");
    // Initialization of 'modification '
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_2);
    BUTTON_SetFont(hItem, &GUI_FontHZ24);
    BUTTON_SetText(hItem, "修改");
    // Initialization of 'add'
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_3);
    BUTTON_SetFont(hItem, &GUI_FontHZ24);
    BUTTON_SetText(hItem, "增加");
    // Initialization of 'Button'
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_4);
    BUTTON_SetFont(hItem, &GUI_FontHZ24);
    BUTTON_SetText(hItem, "上一页");
    // Initialization of 'Button'
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_5);
    BUTTON_SetFont(hItem, &GUI_FontHZ24);
    BUTTON_SetText(hItem, "下一页");
		
    // Initialization of 'Listview'
	hItem = WM_GetDialogItem(pMsg->hWin, ID_LISTVIEW_0);
	hHeader = LISTVIEW_GetHeader(hItem);
	LISTVIEW_SetHeaderHeight(hItem, 100);
	HEADER_SetFont(hHeader,&GUI_FontHZ24);
	LISTVIEW_AddColumn(hItem, 100, "序号", GUI_TA_HCENTER | GUI_TA_VCENTER);
	LISTVIEW_AddColumn(hItem, 100, "地址", GUI_TA_HCENTER | GUI_TA_VCENTER);
	LISTVIEW_AddColumn(hItem, 200, "设备名称", GUI_TA_HCENTER | GUI_TA_VCENTER);
	LISTVIEW_AddColumn(hItem, 200, "设备类型", GUI_TA_HCENTER | GUI_TA_VCENTER);
	LISTVIEW_AddColumn(hItem, 100, "设备状态", GUI_TA_HCENTER | GUI_TA_VCENTER);
	LISTVIEW_SetGridVis(hItem, 1);
	LISTVIEW_SetAutoScrollH(hItem, 1);
	LISTVIEW_SetAutoScrollV(hItem, 1);
	LISTVIEW_SetRowHeight(hItem, 30);
	LISTVIEW_SetFont(hItem,&GUI_FontHZ16);
	LISTVIEW_SetBkColor(hItem,LISTVIEW_CI_UNSEL,GUI_ORANGE);
		
		device_ini.name =filename_device;
		if(read_device_ini(&device_ini)!= FR_OK) return;
		for(i=0;i<GUI_COUNTOF(device_listView);i++)
		{
			LISTVIEW_AddRow(hItem,device_listView[i]);
		}
		//cur_number= 0;
		update_device_List(pMsg,cur_number);
		
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
    // Initialization of 'Device_Config'
    //
    hItem = pMsg->hWin;
    FRAMEWIN_SetFont(hItem, GUI_FONT_32_ASCII);
    FRAMEWIN_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
    //
    // Initialization of 'Dropdown'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_DROPDOWN_0);
    DROPDOWN_SetFont(hItem, GUI_FONT_24_ASCII);
    DROPDOWN_AddString(hItem, "name");
    //
    // Initialization of 'Dropdown'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_DROPDOWN_1);
    DROPDOWN_SetFont(hItem, GUI_FONT_24_ASCII);
    DROPDOWN_AddString(hItem, "1");
    DROPDOWN_AddString(hItem, "2");
    DROPDOWN_AddString(hItem, "3");
    DROPDOWN_AddString(hItem, "4");
    DROPDOWN_AddString(hItem, "5");
    DROPDOWN_AddString(hItem, "6");
    //
    // Initialization of 'Dropdown'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_DROPDOWN_2);
    DROPDOWN_SetFont(hItem, GUI_FONT_24_ASCII);
    DROPDOWN_AddString(hItem, "gas");
    DROPDOWN_AddString(hItem, "humiture");
    DROPDOWN_SetListHeight(hItem, 60);
    //
    // Initialization of 'address'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_0);
    TEXT_SetFont(hItem, GUI_FONT_24_ASCII);
    //
    // Initialization of 'name'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_1);
    TEXT_SetFont(hItem, GUI_FONT_24_ASCII);
    //
    // Initialization of 'type'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_2);
    TEXT_SetFont(hItem, GUI_FONT_24_ASCII);
    //
    // Initialization of 'close'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_0);
    BUTTON_SetFont(hItem, GUI_FONT_24_ASCII);
    //
    // Initialization of 'del'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_1);
    BUTTON_SetFont(hItem, GUI_FONT_24_ASCII);
    //
    // Initialization of 'modification '
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_2);
    BUTTON_SetFont(hItem, GUI_FONT_24_ASCII);
    //
    // Initialization of 'add'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_3);
    BUTTON_SetFont(hItem, GUI_FONT_24_ASCII);
    //
    // Initialization of 'previous'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_4);
    BUTTON_SetFont(hItem, GUI_FONT_24_ASCII);
    //
    // Initialization of 'next'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_5);
    BUTTON_SetFont(hItem, GUI_FONT_24_ASCII);
    //
    // Initialization of 'Edit'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_EDIT_0);
    EDIT_SetText(hItem, "123");
    EDIT_SetFont(hItem, GUI_FONT_24_ASCII);
    //
    // Initialization of 'page'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_3);
    TEXT_SetFont(hItem, GUI_FONT_24_ASCII);
    //
    // Initialization of 'Listview'
    //
    
    // USER START (Optionally insert additional code for further widget initialization)
		init(pMsg);
    // USER END
    break;
  case WM_NOTIFY_PARENT:
    Id    = WM_GetId(pMsg->hWinSrc);
    NCode = pMsg->Data.v;
    switch(Id) {
    case ID_DROPDOWN_0: // Notifications sent by 'Dropdown'
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
    case ID_DROPDOWN_1: // Notifications sent by 'Dropdown'
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
    case ID_DROPDOWN_2: // Notifications sent by 'Dropdown'
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
    case ID_BUTTON_0: // Notifications sent by 'close'
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
    case ID_BUTTON_1: // Notifications sent by 'del'
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
    case ID_BUTTON_2: // Notifications sent by 'modification '
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
    case ID_BUTTON_3: // Notifications sent by 'add'
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
    case ID_BUTTON_4: // Notifications sent by 'previous'
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
    case ID_BUTTON_5: // Notifications sent by 'next'
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
*       CreateDevice_Config
*/
WM_HWIN CreateDevice_Config(void);
WM_HWIN CreateDevice_Config(void) {
  WM_HWIN hWin;

  hWin = GUI_CreateDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), _cbDialog, WM_HBKWIN, 0, 0);
  return hWin;
}

// USER START (Optionally insert additional public code)
// USER END

/*************************** End of file ****************************/
