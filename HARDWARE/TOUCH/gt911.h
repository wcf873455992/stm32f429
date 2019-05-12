#ifndef _BSP_GT911_H
#define _BSP_GT911_H
#include "sys.h"


//IO��������	 
#define GT_RST  PIout(8) //GT911��λ����
#define GT_INT  PHin(7)  //GT911�ж�����		   	
 
//I2C��д����	
#define GT911_CMD_WR 		0XBA     	//д����
#define GT911_CMD_RD 		0XBB		//������
  
#define GT911_READ_XY_REG 	0x814E	/* ����Ĵ��� */
#define GT911_CLEARBUF_REG 	0x814E	/* �������Ĵ��� */
#define GT911_CONFIG_REG	0x8047	/* ���ò����Ĵ��� */
#define GT911_COMMAND_REG   0x8040  /* ʵʱ���� */
#define GT911_PRODUCT_ID_REG 0x8140 /*productid*/
#define GT911_VENDOR_ID_REG   0x814A  /* ��ǰģ��ѡ����Ϣ */
#define GT911_CONFIG_VERSION_REG   0x8047  /* �����ļ��汾�� */
#define GT911_CONFIG_CHECKSUM_REG   0x80FF  /* �����ļ�У���� */
#define GT911_FIRMWARE_VERSION_REG   0x8144  /* �̼��汾�� */

#define GT911_GSTID_REG 	0X814E   	//GT911��ǰ��⵽�Ĵ������
#define GT911_TP1_REG 		0X8150  	//��һ�����������ݵ�ַ
#define GT911_TP2_REG 		0X8158		//�ڶ������������ݵ�ַ
#define GT911_TP3_REG 		0X8160		//���������������ݵ�ַ
#define GT911_TP4_REG 		0X8168		//���ĸ����������ݵ�ַ
#define GT911_TP5_REG 		0X8170		//��������������ݵ�ַ 



/* ����дRST��INT�ĺ� */
#define GT911_RST_1()  HAL_GPIO_WritePin(GPIOI,GPIO_PIN_8,GPIO_PIN_SET)	  /* RST = 1 */
#define GT911_RST_0()  HAL_GPIO_WritePin(GPIOI,GPIO_PIN_8,GPIO_PIN_RESET)	/* RST = 0 */

#define GT911_INT_1()  HAL_GPIO_WritePin(GPIOH,GPIO_PIN_7,GPIO_PIN_SET)		/* INT = 1 */
#define GT911_INT_0()  HAL_GPIO_WritePin(GPIOH,GPIO_PIN_7,GPIO_PIN_RESET)	/* INT = 0 */
 
 
 
void GT911_WriteReg(uint16_t _usRegAddr, uint8_t *_pRegBuf, uint8_t _ucLen);
void GT911_ReadReg(uint16_t _usRegAddr, uint8_t *_pRegBuf, uint8_t _ucLen);
u8 GT911_Init(void);
u8 GT911_Scan(u8 mode);

#endif

