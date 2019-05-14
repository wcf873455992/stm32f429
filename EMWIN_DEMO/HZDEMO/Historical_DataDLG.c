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
#define ID_DROPDOWN_0     (GUI_ID_USER + 0x02)
#define ID_CHECKBOX_0     (GUI_ID_USER + 0x03)
#define ID_CHECKBOX_1     (GUI_ID_USER + 0x04)
#define ID_CHECKBOX_2     (GUI_ID_USER + 0x05)
#define ID_CHECKBOX_3     (GUI_ID_USER + 0x06)
#define ID_TEXT_1     (GUI_ID_USER + 0x07)
#define ID_EDIT_0     (GUI_ID_USER + 0x08)
#define ID_EDIT_1     (GUI_ID_USER + 0x09)
#define ID_BUTTON_0     (GUI_ID_USER + 0x0A)
#define ID_LISTVIEW_0     (GUI_ID_USER + 0x0B)
#define ID_SCROLLBAR_0     (GUI_ID_USER + 0x0C)
#define ID_BUTTON_1     (GUI_ID_USER + 0x0D)
#define ID_BUTTON_2     (GUI_ID_USER + 0x0E)
#define ID_BUTTON_3     (GUI_ID_USER + 0x0F)
#define ID_TEXT_2     (GUI_ID_USER + 0x10)
#define ID_EDIT_2     (GUI_ID_USER + 0x11)


// USER START (Optionally insert additional defines)
//extern WM_HWIN hDialog;
void read_data(void);
// USER END

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/

// USER START (Optionally insert additional static data)
static const char *_ListViewTable1[][5]={
	{"1#变送器",	"20.5%","300PPM","2019-5-11 18:34:20", "CO2超标"},
	{"2#变送器",	"20.5%","300PPM","2019-5-11 18:34:20", " "},
	{"3#变送器",	"20.5%","300PPM","2019-5-11 18:34:20", "O2超标"},
	{"4#变送器",	"20.5%","300PPM","2019-5-11 18:34:20", " "},
	{"5#变送器",	"20.5%","300PPM","2019-5-11 18:34:20", " "},
	{"6#变送器",	"20.5%","300PPM","2019-5-11 18:34:20", " "},
	{"7#变送器",	"20.5%","300PPM","2019-5-11 18:34:20", "  "},
};
static const char *tempdata[2] = {"1#变送器","2#变送器"};
static const char tempdata2[] = "1#变送器";

REAL_TIME_DATA real_data;
#define	ROW_MAX	7
// USER END

/*********************************************************************
*
*       _aDialogCreate
*/
static const GUI_WIDGET_CREATE_INFO _aDialogCreate[] = {
  { FRAMEWIN_CreateIndirect, "Historical_Data", ID_FRAMEWIN_0, 0, 0, 800, 480, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "name", ID_TEXT_0, 5, 5, 500, 38, 0, 0x0, 0 },
  { DROPDOWN_CreateIndirect, "Dropdown", ID_DROPDOWN_0, 83, 200, 105, 18, 0, 0x0, 0 },
  { CHECKBOX_CreateIndirect, "O2", ID_CHECKBOX_0, 227, 11, 103, 20, 0, 0x0, 0 },
  { CHECKBOX_CreateIndirect, "SF6", ID_CHECKBOX_1, 300, 10, 115, 20, 0, 0x0, 0 },
  { CHECKBOX_CreateIndirect, "temperature", ID_CHECKBOX_2, 389, 8, 153, 20, 0, 0x0, 0 },
  { CHECKBOX_CreateIndirect, "Checkbox", ID_CHECKBOX_3, 547, 10, 104, 21, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "time", ID_TEXT_1, 5, 200, 82, 27, 0, 0x0, 0 },
  { EDIT_CreateIndirect, "time_start", ID_EDIT_0, 86, 200, 180, 25, 0, 0x64, 0 },
  { EDIT_CreateIndirect, "Edit", ID_EDIT_1, 337, 49, 193, 26, 0, 0x64, 0 },
  { BUTTON_CreateIndirect, "OK", ID_BUTTON_0, 591, 46, 104, 34, 0, 0x0, 0 },
  { LISTVIEW_CreateIndirect, "Listview", ID_LISTVIEW_0, 0, 84, 762, 286, 0, 0x0, 0 },
  { SCROLLBAR_CreateIndirect, "Scrollbar", ID_SCROLLBAR_0, 759, 83, 28, 286, 8, 0x0, 0 },
  { BUTTON_CreateIndirect, "previous", ID_BUTTON_1, 305, 384, 95, 29, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "next", ID_BUTTON_2, 422, 384, 90, 27, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "close", ID_BUTTON_3, 576, 379, 111, 36, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "page", ID_TEXT_2, 46, 378, 211, 31, 0, 0x0, 0 },
  { EDIT_CreateIndirect, "Edit", ID_EDIT_2, 106, 374, 66, 25, 0, 0x64, 0 },
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
// USER END

/*********************************************************************
*
*       _cbDialog
*/
static void _cbDialog(WM_MESSAGE * pMsg) {
  WM_HWIN hItem;
  int     NCode;
  int     Id;
	UINT	i;
  // USER START (Optionally insert additional variables)
	hItem = pMsg->hWin;
  // USER END

  switch (pMsg->MsgId) {
  case WM_INIT_DIALOG:
    //
    // Initialization of 'Historical_Data'
    //
    hItem = pMsg->hWin;
    FRAMEWIN_SetFont(hItem, GUI_FONT_32_ASCII);
    //
    // Initialization of 'name'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_0);
    TEXT_SetFont(hItem, GUI_FONT_24_ASCII);
    //
    // Initialization of 'Dropdown'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_DROPDOWN_0);
    DROPDOWN_SetFont(hItem, GUI_FONT_24_ASCII);
    //
    // Initialization of 'O2'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_CHECKBOX_0);
    CHECKBOX_SetText(hItem, "O2");
    CHECKBOX_SetFont(hItem, GUI_FONT_24_ASCII);
    //
    // Initialization of 'SF6'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_CHECKBOX_1);
    CHECKBOX_SetText(hItem, "SF6");
    CHECKBOX_SetFont(hItem, GUI_FONT_24_ASCII);
    //
    // Initialization of 'temperature'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_CHECKBOX_2);
    CHECKBOX_SetText(hItem, "temperature");
    CHECKBOX_SetFont(hItem, GUI_FONT_24_ASCII);
    //
    // Initialization of 'Checkbox'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_CHECKBOX_3);
    CHECKBOX_SetText(hItem, "Check");
    CHECKBOX_SetFont(hItem, GUI_FONT_24_ASCII);
    //
    // Initialization of 'time'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_1);
    TEXT_SetFont(hItem, GUI_FONT_24_ASCII);
    //
    // Initialization of 'time_start'
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
    LISTVIEW_AddColumn(hItem, 65, "Col 0", GUI_TA_HCENTER | GUI_TA_VCENTER);
    LISTVIEW_AddColumn(hItem, 350, "Col 1", GUI_TA_HCENTER | GUI_TA_VCENTER);
    LISTVIEW_AddColumn(hItem, 350, "Col 2", GUI_TA_HCENTER | GUI_TA_VCENTER);
    LISTVIEW_AddRow(hItem, NULL);
    LISTVIEW_SetGridVis(hItem, 1);
    LISTVIEW_SetFont(hItem, &GUI_FontHZ16);
		/*for(i=0;i<(_ListViewTable1);i++)
		{
				LISTVIEW_AddRow(hItem,_ListViewTable1[i]);
		}*/
		for(i=0;i<ROW_MAX;i++)
		{
				//LISTVIEW_AddRow(hItem,(GUI_ConstString *)real_data.Date);
		}
		
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
    BUTTON_SetFont(hItem, GUI_FONT_24_ASCII);
    //
    // Initialization of 'page'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_2);
    TEXT_SetFont(hItem, GUI_FONT_24_ASCII);
    //
    // Initialization of 'Edit'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_EDIT_2);
    EDIT_SetText(hItem, "123");
    EDIT_SetFont(hItem, GUI_FONT_24_ASCII);
    // USER START (Optionally insert additional code for further widget initialization)
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
    case ID_CHECKBOX_0: // Notifications sent by 'O2'
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
    case ID_CHECKBOX_1: // Notifications sent by 'SF6'
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
    case ID_CHECKBOX_2: // Notifications sent by 'temperature'
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
    case ID_CHECKBOX_3: // Notifications sent by 'Checkbox'
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
    case ID_EDIT_0: // Notifications sent by 'time_start'
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
			read_data();
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
*       CreateHistorical_Data
*/
WM_HWIN hWin_historical;
WM_HWIN CreateHistorical_Data(void);
WM_HWIN CreateHistorical_Data(void) {
  //WM_HWIN hWin;

  hWin_historical = GUI_CreateDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), _cbDialog, WM_HBKWIN, 0, 0);
  return hWin_historical;
}

// USER START (Optionally insert additional public code)

FIL* f_rec=0;			//文件

u32 emwin_print(char * buffer)
{
    WM_HWIN hItem;
    //char buffer[10];
    hItem=WM_GetDialogItem(hWin_historical,ID_TEXT_0);
    //sprintf(buffer,"%d%%",t);
    TEXT_SetText(hItem,buffer);
    GUI_Exec();
	return 0;					    
} 
void recoder_new_pathname(char * pname)
{	 
	u8 res;					 
	u16 index=0;
	while(index<0XFFFF)
	{
		sprintf((char*)pname,"0:historical/REC%05d.txt",index);
		res=f_open(ftemp,(const TCHAR*)pname,FA_READ);//尝试打开这个文件
		if(res==FR_NO_FILE)break;		//该文件名不存在=正是我们需要的.
		index++;
	}
	emwin_print(pname);
	GUI_Delay(3000);
} 

void read_once_record(void){
	RTC_TimeTypeDef	RTC_TimeStruct;
	RTC_DateTypeDef RTC_DateStruct;
	static u32 index=0;
	
	HAL_RTC_GetTime(&RTC_Handler,&RTC_TimeStruct,RTC_FORMAT_BIN); 
	HAL_RTC_GetDate(&RTC_Handler,&RTC_DateStruct,RTC_FORMAT_BIN);
	sprintf((char *)real_data.Date,"20%02d-%02d-%02d\t",
				RTC_DateStruct.Year,RTC_DateStruct.Month,RTC_DateStruct.Date);
	sprintf((char *)real_data.Time,"%02d:%02d:%02d\t",
				RTC_TimeStruct.Hours,RTC_TimeStruct.Minutes,RTC_TimeStruct.Seconds);	
	sprintf((char *)real_data.name,"%3d#变送器\t",index) ;
	sprintf((char *)real_data.alarm,"CO2报警\r\n") ;
	sprintf((char *)real_data.O2,"%.1f\t",356.3) ;
	sprintf((char *)real_data.CO2,"%.1f\t",24.5) ;
	index++;
	/* //
	float i = strtol((char *)real_data.O2,NULL ,10);
	emwin_print("a=%.1f",i);	
	emwin_print(real_data.O2);*/
}
void write_once_record(){
	u8 res;
	res=f_write(f_rec,(const void*)real_data.Date,strlen(real_data.Date),&bw);
	res=f_write(f_rec,(const void*)real_data.Time,strlen(real_data.Time),&bw);
	res=f_write(f_rec,(const void*)real_data.name,strlen(real_data.name),&bw);
	res=f_write(f_rec,(const void*)real_data.O2,strlen(real_data.O2),&bw);
	res=f_write(f_rec,(const void*)real_data.CO2,strlen(real_data.CO2),&bw);
	res=f_write(f_rec,(const void*)real_data.alarm,strlen(real_data.alarm),&bw);

}
void read_data(void){
	DIR recdir;	 			//目录
	u8 *pname=0;
	u8 res;
	char pos[20]="";
	while(f_opendir(&recdir,"0:/historical"))//打开录音文件夹
 	{
		emwin_print("dir wrong!"); 		
		f_mkdir("0:/historical");				//创建该目录   
	}
  f_rec=(FIL *)mymalloc(SRAMIN,sizeof(FIL));		//开辟FIL字节的内存区域 
	real_data.Date=(char *)mymalloc(SRAMIN,sizeof(real_data.Date));
	real_data.Time=(char *)mymalloc(SRAMIN,sizeof(real_data.Time));
	real_data.name=(char *)mymalloc(SRAMIN,sizeof(real_data.name));
	real_data.alarm=(char *)mymalloc(SRAMIN,sizeof(real_data.alarm));
	real_data.O2=(char *)mymalloc(SRAMIN,sizeof(real_data.O2));
	real_data.CO2=(char *)mymalloc(SRAMIN,sizeof(real_data.CO2)); 	
	pname=mymalloc(SRAMIN,30);						//申请30个字节内存,类似"0:RECORDER/REC00001.wav"	
	pname[0]=0;					//pname没有任何文件名
	sprintf((char*)pname,"0:historical/historical.xls");
	res=f_open(f_rec,(const TCHAR*)pname, FA_READ | FA_WRITE); 
	if(res)			//文件创建失败
	{
		emwin_print("creat file fail"); 		
		res=f_open(f_rec,(const TCHAR*)pname, FA_CREATE_ALWAYS | FA_WRITE); 
		f_close(f_rec);
	}else	{
		res=f_lseek(f_rec,f_size(f_rec));
		sprintf((char*)pos,"OK,f_lseek=%05d",f_rec->obj.objsize);
		emwin_print(pos);
		read_once_record();
		write_once_record();
		f_close(f_rec);
	}
	myfree(SRAMIN,f_rec);		//释放内存
	myfree(SRAMIN,pname);		//释放内存
	myfree(SRAMIN,real_data.Date);		//释放内存
	myfree(SRAMIN,real_data.Time);		//释放内存 	
	myfree(SRAMIN,real_data.name);		//释放内存 	
	myfree(SRAMIN,real_data.alarm);		//释放内存 
	myfree(SRAMIN,real_data.O2);		//释放内存
	myfree(SRAMIN,real_data.CO2);		//释放内存
}
// USER END

/*************************** End of file ****************************/
