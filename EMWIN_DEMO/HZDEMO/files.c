#include "files.h"
#include "stdlib.h"
#include "lib_str.h"
#include "malloc.h"
#include "DIALOG.h"
#include "ff.h"
#include "exfuns.h"

#if SYSTEM_SUPPORT_OS
#include "includes.h"					//ucos 使用	  
#endif

#define SIZE_LINE		1024	//每行最大长度
#define SIZE_FILENAME	256		//文件名最大长度
#define min(x, y)		(x <= y) ? x : y

typedef enum _ELineType_ {
  LINE_IDLE,		//未处理行
	LINE_ERROR,		//错误行
	LINE_EMPTY,		//空白行或注释行
	LINE_SECTION,	//节定义行
	LINE_VALUE		//值定义行
} ELineType ;

static char *StrStrip(char *s)
{
	size_t size;
	char *p1, *p2;
	size = Str_Len(s);
	if (!size)
		return s;
	p2 = s + size - 1;
	while ((p2 >= s) && isspace(*p2))
		p2 --;
	*(p2 + 1) = 0x00;
	p1 = s;
	while (*p1 && isspace(*p1))
		p1 ++;
	if (s != p1)
		memmove(s, p1, p2 - p1 + 2);
	return s;
}

//不区分大小写比较字符串
static int StriCmp(const char *s1, const char *s2)
{
	int ch1, ch2;
	do{
		ch1 = (unsigned char)*(s1++);
		if ((ch1 >= 'A') && (ch1 <= 'Z')) 
			ch1 += 0x20; 
		ch2 = (unsigned char)*(s2++); 
		if ((ch2 >= 'A') && (ch2 <= 'Z')) 
			ch2 += 0x20; 
	} while ( ch1 && (ch1 == ch2) ); 
	return(ch1 - ch2); 
} 
 
//取一行
//输入：数据区(指针及长度)
//输出：行类型、有效内容串(去首尾空格)、注释首、注释尾、下一行首(行尾与下一行首间为换行符)
//      有效内容位置为[buf, rem1)
static int GetLine(char *buf, int buflen, char *content, char **rem1, char **rem2, char **nextline)
 { 
	char *cont1, *cont2;
	int cntblank, cntCR, cntLF;		//连续空格、换行符数量
	char isQuot1, isQuot2;			//引号
	int i;
	char *p;
 
	//首先断行断注释，支持如下换行符：r、n、rn、nr 
	cntblank = 0; 
	cntCR = cntLF = 0; 
	isQuot1 = isQuot2 = 0; 
	cont1 = *rem1 = 0; 
	content[0] = 0; 
	for (i = 0, p = buf; i < buflen; i ++, p ++) 
	{ 
		if (*p == 0) { 
			p ++; 
			break; 
		} 
		//2个CR或LF，行结束 
		if (cntCR == 2 || cntLF == 2) {
			p --;	//回溯1 
			break; 
		} 
		//CR或LF各1个之后任意字符，行结束
 		if (cntCR + cntLF >= 2) {
 			break;
 		}
 		//CR或LF之后出现其它字符，行结束
 		if ((cntCR || cntLF) && *p != 'r' && *p != 'n')
 			break;
 		switch (*p) {
			case '\r':
				cntCR ++;
				break;
			case '\n':
				cntLF ++;
				break;
			//case ''':
			case ' ':
				if (!isQuot2)
 				isQuot1 = 1 - isQuot1;
				break;
			case '"':
 			if (!isQuot1) 
				isQuot2 = 1 - isQuot2; 
			break; 
		case ';':
 		case '#':
 			if (isQuot1 || isQuot2)
 				break;
 			if (*rem1 == NULL)
 				*rem1 = p - cntblank;
			break;
		default: 
			if (ASCII_IS_SPACE((unsigned char)*p)) {
 				cntblank ++;
 			} else {
 				cntblank = 0;
 				if ((*rem1 == NULL) && (cont1 == NULL))
 					cont1 = p;
 			} 
			break;
 		}
 	}
  
	*nextline = p;
 	*rem2 = p - cntCR - cntLF;
 	if (*rem1 == NULL)
 		*rem1 = *rem2;
	cont2 = *rem1 - cntblank;
 	if (cont1 == NULL) {
 		cont1 = cont2;
 		return LINE_EMPTY;
 	}
 	i = (int)(cont2 - cont1);
 	if (i >= SIZE_LINE) 
		return LINE_ERROR;
  
	//内容头尾已无空格
 	mymemcpy(content, cont1, i);
 	content[i] = 0;
 	if (content[0] == '[' && content[i - 1] == ']')
 		return LINE_SECTION;
 	if (Str_Char(content, '=') != NULL) 
		return LINE_VALUE; 
	return LINE_ERROR; 
}
 
//取一节section 
//输入：节名称 
//输出：成功与否、节名称首、节名称尾、节内容首、节内容尾(含换行)、下一节首(节尾与下一节首间为空行或注释行)
 static int FindSection(LOAD_FILE file,const char *section, char **sect1, char **sect2, char **cont1, char **cont2, char **nextsect)
 {
 	int type;
 	char content[SIZE_LINE];
 	char *rem1, *rem2, *nextline;
 	char *p;
 	char *empty;
 	int uselen = 0;
 	char found = 0;
  
	if (file.buf == NULL) {
 		return 0;
 	}
 	while (file.buflen - uselen > 0) {
 		p = file.buf + uselen;
		type = GetLine(p, file.buflen - uselen, content, &rem1, &rem2, &nextline);
		uselen += (int)(nextline - p);
		if (LINE_SECTION == type) {
			if (found || section == NULL) break;		//发现另一section
			content[Str_Len(content) - 1] = 0;			//去尾部]
			StrStrip(content + 1);						//去首尾空格
			if (StriCmp(content + 1, section) == 0) {
				found = 1;
				*sect1 = p;
				*sect2 = rem1;
				*cont1 = nextline;
			}
 			empty = nextline;
 		} else
 		if (LINE_VALUE == type) {
 			if (!found && section == NULL) {
				found = 1;
				*sect1 = p;
				*sect2 = p;
				*cont1 = p;
			}
			empty = nextline;
		}
	}
	if (!found) return 0;
	*cont2 = empty;
	*nextsect = nextline;
	return 1;
}
 
//从一行取键、值
 //输入：内容串(将被改写)
 //输出：键串、值串
 static void GetKeyValue(char *content, char **key, char **value)
 {
 	char *p;
 	p = Str_Char(content, '=');
 	*p = 0x00;
 	StrStrip(content);
	StrStrip(p + 1);
	*key = content;
 	*value = p + 1;
 }
 
//释放文件所占资源
void FileFree(LOAD_FILE *file)
{
	if (file->buf != NULL) {
		myfree(SRAMIN,file->buf);		//释放内存
 		file->buf = 0;
 		file->buflen = 0;
	}
}
//加载文件至内存
 int FileLoad(LOAD_FILE *file)
 {
	#if SYSTEM_SUPPORT_OS
		CPU_SR_ALLOC();
	#endif
	int ret;
	 
 	FileFree(file);
 	if (Str_Len(file->name) >= SIZE_FILENAME)//sizeof(gFilename))
 		return 0;
	
 	ret = f_open(&file->fil,(const TCHAR*)file->name, FA_READ|FA_WRITE);
 	/*if (ret){
		ret=f_open(&file.fil,(const TCHAR*)file.name, FA_CREATE_ALWAYS | FA_WRITE); //创建ini文件
		f_close(&file.fil);
		ret = f_open(&file.fil,(const TCHAR*)file.name, FA_READ|FA_WRITE);
 		return 0;
	}*/
	if(ret != FR_OK)		return	1;
	file->buf=(char *)mymalloc(SRAMIN,file->fil.obj.objsize);		//开辟fan_record_buf内存区域
	if( file->buf==NULL)		return	2;
		
	#if SYSTEM_SUPPORT_OS
		OS_CRITICAL_ENTER();		//临界区
	#endif
	ret = f_read(&file->fil, file->buf ,file->fil.obj.objsize,&file->buflen );	
	if(ret != FR_OK)	return	3;
	#if SYSTEM_SUPPORT_OS
		OS_CRITICAL_EXIT();	//退出临界区
	#endif	
	f_close(&file->fil);
	/*
	file.buf[0] = 0;
	f_lseek(file.fil, 0);
	len = f_read(file->fil,file->buf, len, &br);
	file->buflen = Str_Len(file->buf);
	f_close(file->fil);
	*/
	return 0;
}
//读取值原始串
 static int GetValue(LOAD_FILE file, const char *section, const char *key, char *value, int maxlen, const char *defvalue)
 {
	int type;
 	char content[SIZE_LINE];
 	char *rem1, *rem2, *nextline;
 	char *key0, *value0;
 	char *p;
 
	int uselen = 0;
 	char found = 0;
 	int len;
 	if (file.buf == NULL || key == NULL) {
 		if (value != NULL)
 			value[0] = 0;
 		return 0;
 	}
 	while (file.buflen - uselen > 0) {
 		p = file.buf + uselen;
 		type = GetLine(p, file.buflen - uselen, content, &rem1, &rem2, &nextline);
 		uselen += (int)(nextline - p);
 		if (LINE_SECTION == type) {
 			if (found || section == NULL) break;		//发现另一section
 			content[Str_Len(content) - 1] = 0;			//去尾部]
 			StrStrip(content + 1);						//去首尾空格
 			if (StriCmp(content + 1, section) == 0) {
 				found = 1;
 			}
 		} else
 		if (LINE_VALUE == type) {
 			if (!found && section == NULL) {
 				found = 1;
 			}
 			if (!found)
 				continue;
 			GetKeyValue(content, &key0, &value0);
 			if (StriCmp(key0, key) == 0) {
 				len = Str_Len(value0);
 				if (len == 0) break;		//空值视为无效
 				if (value != NULL) {
 					len = min(len, maxlen - 1);
 					Str_Copy_N(value, value0, len);
 					value[len] = 0x00;
 				}
 				return 1;
 			}
 		}
 	}
  
	//未发现键值取缺省
 	if (value != NULL) {
 		if (defvalue != NULL) {
 			len = min(Str_Len(defvalue), maxlen - 1);
 			Str_Copy_N(value, defvalue, len);
 			value[len] = 0;
 		} else {
 			value[0] = 0;
 		}
 	}
 	return 0;
 }
//获取字符串，不带引号
 int GetString(LOAD_FILE file,const char *section, const char *key, char *value, int maxlen, const char *defvalue)
 {
 	int ret;
 	int len;
  
	ret = GetValue(file, section, key, value, maxlen, defvalue);
 	if (!ret)
 		return ret;
 	//去首尾空格
 	len = Str_Len(value);
 	//if (value[0] == ''' && value[len - 1] == ''') {	
 	if (value[0] == ' ' && value[len - 1] == ' ') {
 		value[len - 1] = 0;
 		memmove(value, value + 1, len - 1);
 	} else
 	if (value[0] == '"' && value[len - 1] == '"') {
 		value[len - 1] = 0;
 		memmove(value, value + 1, len - 1);
 	}
 	return ret;
 }
//获取整数值
 int GetInt(LOAD_FILE file,const char *section, const char *key, int defvalue)
 {
 	char valstr[64];
 
	if (GetValue(file, section, key, valstr, sizeof(valstr), NULL))
 	    return (int)strtol(valstr, NULL, 0);
 	return defvalue;
 }
  
//获取浮点数
 double GetDouble(LOAD_FILE file, const char *section, const char *key, double defvalue)
 {
 	char valstr[64];
 	if (GetValue(file, section, key, valstr, sizeof(valstr), NULL))
 	    return (int)atof(valstr);
 	return defvalue;
 }
//设置字符串：若value为NULL，则删除该key所在行，包括注释
 int SetString(LOAD_FILE file, const char *section, const char *key, const char *value)
 {
 	//FIL *file;
 	char *sect1, *sect2, *cont1, *cont2, *nextsect;
 	char *p;
 	int len, type;
 	char content[SIZE_LINE];
 	char *key0, *value0;
 	char *rem1, *rem2, *nextline;
	int ret;
  
	if (file.buf == NULL) {
 		return 0;
 	}
 	if (FindSection(file ,section, &sect1, &sect2, &cont1, &cont2, &nextsect) == 0)
 	{
 		//未找到节
 		//value无效则返回
 		if (value == NULL) 
 			return 0;
 		//在文件尾部添加
		 
 		ret = f_open(&file.fil,file.name, FA_READ|FA_WRITE);
 		if (ret) 
 			return 0;
 		///_fprintf(file, "n[%s]n%s = %sn", section, key, value);
 		f_close(&file.fil);
 		FileLoad(&file);
 		return 1;
 	}
 
 
	//找到节，则节内查找key
 	p = cont1;
 	len = (int)(cont2 - cont1);
 	while (len > 0) {
 		type = GetLine(p, len, content, &rem1, &rem2, &nextline);
 		if (LINE_VALUE == type) {
 			GetKeyValue(content, &key0, &value0);
 			if (StriCmp(key0, key) == 0) {
 				//找到keyf_open(file->fil,(const TCHAR*)file->name, FA_READ|FA_WRITE);
 				ret = f_open(&file.fil,(const TCHAR*) file.name, FA_WRITE|FA_WRITE);
 				if (ret)
 					return 0;
 				len = (int)(p - file.buf);
 				f_write(&file.fil,file.buf, len,&bw );					//写入key之前部分
 				if (value == NULL) {
 					//value无效，删除
 					len = (int)(nextline - file.buf);			//整行连同注释一并删除
 				} else {
 					//value有效，改写
 					f_printf(&file.fil, "%s = %s", key, value);
 					len = (int)(rem1 - file.buf);				//保留尾部原注释!
 				}//	res=f_write(f_rec,(const void*)real_data.Date,strlen(real_data.Date),&bw);
 				f_write(&file.fil, (const void*)(file.buf + len),  file.buflen - len,&bw );	//写入key所在行含注释之后部分
 				f_close(&file.fil);
 				FileLoad(&file);
 				return 1;
 			}
 		}
 		len -= (int)(nextline - p);
 		p = nextline;
 	}
 
 
	//未找到key
 	//value无效则返回
 	if (value == NULL) 
 		return 0;
 	//在文件尾部添加
 	ret = f_open(&file.fil,file.name, FA_WRITE);
 	if (ret) 
 		return 0;
 	len = (int)(cont2 - file.buf);
 	f_write(&file.fil,file.buf, len,&bw );					//写入key之前部分
 	//fprintf(file, "%s = %sn", key, value);
 	f_write(&file.fil,file.buf + len,  file.buflen - len,&bw );	//写入key之后部分
 	f_close(&file.fil);
 	FileLoad(&file);
 	return 1;
 }
//设置整数值：base取值10、16、8，分别表示10、16、8进制，缺省为10进制
 int SetInt(LOAD_FILE file, const char *section, const char *key, int value, int base)
 {
 	char valstr[64];
  
	switch (base) {
 	case 16:
 		sprintf(valstr, "0x%x", value);
 		return SetString(file,section, key, valstr);
 	case 8:
 		sprintf(valstr, "0%o", value);
 		return SetString(file,section, key, valstr);
 	default:	//10
 		sprintf(valstr, "%d", value);
 		return SetString(file,section, key, valstr);
 	}
 }
  