//inirw.h头文件：
#ifndef _INI_RW_H_
#define _INI_RW_H_
#ifdef __cplusplus
extern "C" {
#endif
#include	"ff.h"
typedef struct{
	const char *name;
	FIL	*	fil;
	char *buf;
	int	buflen;
}INI_FILE;

//加载ini文件至内存
int iniFileLoad(INI_FILE *file);
//释放ini文件所占资源
void iniFileFree(INI_FILE *file);
//获取字符串，不带引号
int iniGetString(INI_FILE *file,const char *section, const char *key, char *value, int size, const char *defvalue);
//获取整数值
int iniGetInt(INI_FILE *file,const char *section, const char *key, int defvalue);
//获取浮点数
double iniGetDouble(INI_FILE *file,const char *section, const char *key, double defvalue);
//设置字符串：若value为NULL，则删除该key所在行，包括注释
int iniSetString(INI_FILE *file,const char *section, const char *key, const char *value);
//设置整数值：base取值10、16、8，分别表示10、16、8进制，缺省为10进制
int iniSetInt(INI_FILE *file, const char *section, const char *key, int value, int base);
#ifdef __cplusplus
}
#endif
#endif