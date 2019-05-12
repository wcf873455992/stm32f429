#ifndef __HZFONTUPDATA_H
#define __HZFONTUPDATA_H
#include "sys.h"
#include "GUI.h"

u32 emwin_fupd_prog(u32 fsize,u32 pos); //EMWIN使用的显示更新进度
u8 emwin_updata_fontx(u8 *fxpath,u8 fx);//EMWIN使用的更新指定字库函数
u8 emwin_update_font(u8* src);    //EMWIN使用的字库更新函数
void HzFontupdataCreate(void);
#endif
