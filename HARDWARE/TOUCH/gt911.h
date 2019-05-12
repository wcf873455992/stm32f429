#ifndef _BSP_GT911_H
#define _BSP_GT911_H
#include "sys.h"


//IO操作函数	 
#define GT_RST  PIout(8) //GT911复位引脚
#define GT_INT  PHin(7)  //GT911中断引脚		   	
 
//I2C读写命令	
#define GT911_CMD_WR 		0XBA     	//写命令
#define GT911_CMD_RD 		0XBB		//读命令
  
#define GT911_READ_XY_REG 	0x814E	/* 坐标寄存器 */
#define GT911_CLEARBUF_REG 	0x814E	/* 清除坐标寄存器 */
#define GT911_CONFIG_REG	0x8047	/* 配置参数寄存器 */
#define GT911_COMMAND_REG   0x8040  /* 实时命令 */
#define GT911_PRODUCT_ID_REG 0x8140 /*productid*/
#define GT911_VENDOR_ID_REG   0x814A  /* 当前模组选项信息 */
#define GT911_CONFIG_VERSION_REG   0x8047  /* 配置文件版本号 */
#define GT911_CONFIG_CHECKSUM_REG   0x80FF  /* 配置文件校验码 */
#define GT911_FIRMWARE_VERSION_REG   0x8144  /* 固件版本号 */

#define GT911_GSTID_REG 	0X814E   	//GT911当前检测到的触摸情况
#define GT911_TP1_REG 		0X8150  	//第一个触摸点数据地址
#define GT911_TP2_REG 		0X8158		//第二个触摸点数据地址
#define GT911_TP3_REG 		0X8160		//第三个触摸点数据地址
#define GT911_TP4_REG 		0X8168		//第四个触摸点数据地址
#define GT911_TP5_REG 		0X8170		//第五个触摸点数据地址 



/* 定义写RST和INT的宏 */
#define GT911_RST_1()  HAL_GPIO_WritePin(GPIOI,GPIO_PIN_8,GPIO_PIN_SET)	  /* RST = 1 */
#define GT911_RST_0()  HAL_GPIO_WritePin(GPIOI,GPIO_PIN_8,GPIO_PIN_RESET)	/* RST = 0 */

#define GT911_INT_1()  HAL_GPIO_WritePin(GPIOH,GPIO_PIN_7,GPIO_PIN_SET)		/* INT = 1 */
#define GT911_INT_0()  HAL_GPIO_WritePin(GPIOH,GPIO_PIN_7,GPIO_PIN_RESET)	/* INT = 0 */
 
 
 
void GT911_WriteReg(uint16_t _usRegAddr, uint8_t *_pRegBuf, uint8_t _ucLen);
void GT911_ReadReg(uint16_t _usRegAddr, uint8_t *_pRegBuf, uint8_t _ucLen);
u8 GT911_Init(void);
u8 GT911_Scan(u8 mode);

#endif

