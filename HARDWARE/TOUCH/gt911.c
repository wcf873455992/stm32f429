#include "gt911.h"
#include "touch.h"
#include "ctiic.h"
#include "tftlcd.h"
#include "usart.h"
#include "delay.h" 
#include "string.h" 




///* GT911�����������ò�����һ����д�� */
//u8 GT911_CFG_TBL[]=
//{
//0x42,		//0x8047		�汾��
//0x20,0x03,	//0x8048/8049	X����������ֵ800
//0xE0,0x01,	//0x804a/804b	Y����������ֵ480
////0x25,0x02,	//0x804a/804b	Y����������ֵ480
//0x05,	//0x804c	��������������
//0x3D,	//0x804d	������룬�½��ش���
//0x00,	//0x804e	reserved
//0x01,	//0x804f	��ָ����ȥ��������
//0x08,	//0x8050	ԭʼ���괰���˲�ֵ	
//0x28,	//0x8051	������������
//0x08,	//0x8052	��������ֵ
//0x50,	//0x8053	���ϴ�������޵��е���ֵ
//0x3C,	//0x8054	���ϴ�������е��޵���ֵ
//0x03,	//0x8055	���͹���ʱ��	s
//0x05,	//0x8056	�����ϱ���
//0x00,	//0x8057	X�������������
//0x00,	//0x8058	Y�������������
//0x00,0x00,	//0x8059-0x805a	reserved
//0x00,	//0x805b	reserved
//0x00,	//0x805c	reserved
//0x00,	//0x805d	���߹�����Сfilter����
//0x18,	//0x805e	��������	1	ϵ��
//0x1A,	//0x805f	��������	2	ϵ��
//0x1E,	//0x8060	��������	3	ϵ��
//0x14,	//0x8061	�������������
//0x89,	//0x8062	����
//0x2A,	//0x8063	����
//0x0B,	//0x8064	����
//0x40,	//0x8065	������A������Ƶ�ʱ�Ƶϵ��
//0x42,	//0x8066	������B������Ƶ�ʱ�Ƶϵ��
//0xB5,	//0x8067	������A��B�Ļ�Ƶ
//0x06,	//0x8068	
//0x00,	//0x8069	�������������ź����ʱ����
//0x00,	//0x806a	
//0x00,	//0x806b	����
//0x02,	//0x806c	����
//0x02,	//0x806d	ԭʼֵ�Ŵ�ϵ��
//0x1D,	//0x806e	����
//0x00,	//0x806f	reserved
//0x01,	//0x8070	����
//0x00,0x00,	//reserved
//0x00,	//0x8073	����
//0x03,0x64,0x00,0x00,0x00,0x00,		//0x8071 - 0x8079 reserved
//0x32,         //0x807a	��Ƶ��Χ�����Ƶ��
//0x5A,	//0x807b	��Ƶ��Χ���յ�Ƶ��
//0x94,	//0x807c	�����������ȷ����������1-63��Ч
//0xC5,	//0x807d	������ⳬʱʱ��
//0x02,	//0x807e	����
//0x08,	//0x807f	�б��и��ŵ�����
//0x00,0x00,	//0x8081	reserved	
//0x00,         //0x8082	��Ƶ�������Ƶ��1���ĵ��Ƶ������������A��B��
//0x98,	//0x8083
//0x35,	//0x8084	��Ƶ�������Ƶ��1���ĵ㱶Ƶϵ��
//0x00,	//0x8085	��Ƶ�������Ƶ��2���ĵ��Ƶ(����A��B�ڴ˻����ϻ���)
//0x8A,	//0x8086	
//0x3B,	//0x8087	��Ƶ�������Ƶ��2���ĵ㱶Ƶϵ��
//0x00,	//0x8088	��Ƶ�������Ƶ��3���ĵ��Ƶ������������A��B��
//0x7A,	//0x8089	
//0x43,	//0x808a	��Ƶ�������Ƶ��3���ĵ㱶Ƶϵ��
//0x00,	//0x808b	��Ƶ�������Ƶ��4���ĵ��Ƶ������������A��B��
//0x6E,	//0x808c	
//0x4B,	//0x808d	��Ƶ�������Ƶ��4���ĵ㱶Ƶϵ��
//0x00,	//0x808e	��Ƶ�������Ƶ��5���ĵ��Ƶ������������A��B��
//0x62,	//0x808f	
//0x55,	//0x8090	��Ƶ�������Ƶ��5���ĵ㱶Ƶϵ��
//0x00,0x62,		//reserved
//0x00,	//0x8093	key1λ��	0���ް���
//0x00,	//0x8094	key2λ��	0���ް���
//0x00,	//0x8095	key3λ��	0���ް���
//0x00,	//0x8096	key4λ��	0���ް���
//0x00,	//0x8097	reserved
//0x00,	//0x8098	reserved
//0x00,	//0x8099	reserved
//0x00,	//0x809a	reserved
//0x00,	//0x809b	reserved
//0x00,	//0x809c	reserved
//0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,\
//0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,	//0x809d-0x80b2	reserved
//0x00,	//0x80b3	�Ͽ����
//0x00,	//0x80b4
//0x00,0x00,	//0x80b6	reserved
//0x02,	//0x80b7
//0x04,	//0x80b8
//0x06,	//0x80b9
//0x08,	//0x80ba
//0x0A,	//0x80bb
//0x0C,	//0x80bc
//0x0E,	//0x80bd
//0x10,	//0x80be
//0x12,	//0x80bf
//0x14,	//0x80c0
//0xFF,	//0x80c1
//0xFF,	//0x80c2
//0xFF,	//0x80c3
//0xFF,	//0x80c4
//0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//0x00,0x00,0x00,0x00,	//0x80c5-0x80d4	reserved
//0x00,	//0x80d5
//0x02,	//0x80d6
//0x04,	//0x80d7
//0x06,	//0x80d8
//0x08,	//0x80d9
//0x0A,	//0x80da
//0x0F,	//0x80db
//0x10,	//0x80dc
//0x12,	//0x80dd
//0x16,	//0x80de
//0x18,	//0x80df
//0x1C,	//0x80e0
//0x1D,	//0x80e1
//0x1E,	//0x80e2
//0x1F,	//0x80e3
//0x20,	//0x80e4
//0x21,	//0x80e5
//0x22,	//0x80e6
//0x24,	//0x80e7
//0xFF,	//0x80e8
//0xFF,	//0x80e9
//0xFF,	//0x80ea
//0xFF,	//0x80eb
//0xFF,	//0x80ec
//0xFF,	//0x80ed
//0xFF,	//0x80ee
//0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//0x00,0x00,0x00,0x00,	//0x80ef-0x80fe	reserved
//0x60,	//0x80ff	������ϢУ��
//0x01	//0x8100	�����Ը��±��
//};


/*
*********************************************************************************************************
*	�� �� ��: GT911_INT_GPIO_Init
*	����˵��: ��ʼ��RST����Ϊ�������
*	��    ��:  ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void GT911_RST_INT_GPIO_Init(void)
{
	 GPIO_InitTypeDef GPIO_Initure;
    
    __HAL_RCC_GPIOH_CLK_ENABLE();			//����GPIOHʱ��
    __HAL_RCC_GPIOI_CLK_ENABLE();			//����GPIOIʱ��
          
		//PI8
    GPIO_Initure.Pin=GPIO_PIN_8;            //PI8
    GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;  //�������
		GPIO_Initure.Pull=GPIO_NOPULL;          //���������費ʹ��
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;     //����
    HAL_GPIO_Init(GPIOI,&GPIO_Initure);     //��ʼ��
			
    //PH7
    GPIO_Initure.Pin=GPIO_PIN_7;            //PH7
    GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;      //��Ϊ��©ģʽ 
    GPIO_Initure.Pull=GPIO_NOPULL;          //���������費ʹ��
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;     //����
    HAL_GPIO_Init(GPIOH,&GPIO_Initure);     //��ʼ��             
}
/*
*********************************************************************************************************
*	�� �� ��: GT911_INT_GPIO_Input_Init
*	����˵��: �趨INT����Ϊ��������
*	��    ��:  ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void GT911_INT_GPIO_Input_Init(void)
{
	GPIO_InitTypeDef GPIO_Initure;
    
  __HAL_RCC_GPIOH_CLK_ENABLE();			//����GPIOHʱ��
	GPIO_Initure.Pin=GPIO_PIN_7;            //PH7
	GPIO_Initure.Mode=GPIO_MODE_INPUT;      //����
	GPIO_Initure.Pull=GPIO_NOPULL;          //���������費ʹ��
	GPIO_Initure.Speed=GPIO_SPEED_HIGH;     //����
	HAL_GPIO_Init(GPIOH,&GPIO_Initure);     //��ʼ��
    
}


/*
*********************************************************************************************************
*	�� �� ��: GT911_Hard_Reset
*	����˵��: G911Ӳ��λ����
*	��    ��:  ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void GT911_Hard_Reset(void)
{
    GT911_RST_INT_GPIO_Init();
		GT911_RST_0();                //RST���ŵ͵�ƽ
		GT911_INT_0();                //INT���ŵ͵�ƽ
		delay_ms(30);               //��ʱ30ms�����1
		GT911_RST_1();                //RST���Ÿߵ�ƽ
		GT911_INT_0();                //INT���ŵ͵�ƽ
		delay_ms(30);              //��ʱ30ms�����20
		GT911_INT_0();
		delay_ms(30);              //��ʱ30ms�����20
		GT911_INT_1();
           
}
/*
*********************************************************************************************************
*	�� �� ��: GT911_Soft_Reset
*	����˵��: G911��λ������
*	��    ��:  ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void GT911_Soft_Reset(void)
{
    uint8_t buf[1];
    buf[0] = 0x01;
    GT911_WriteReg(GT911_COMMAND_REG, (uint8_t *)buf, 1);
}
/*
*********************************************************************************************************
*	�� �� ��: GT911_Init
*	����˵��: ���ô���оƬ.
*	��    ��:  ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
u8 GT911_Init(void)
{
		u8 buf[4];
   // u8 config_Checksum = 0,i;	
    CT_IIC_Init();
    GT911_Hard_Reset(); //Ӳ��λGT911
    GT911_Soft_Reset(); //��λGT911
		
		GT911_ReadReg(GT911_PRODUCT_ID_REG, (uint8_t *)&buf[0], 3);
		buf[3]=0;
		printf("CTP ID:%s\r\n",buf);	//��ӡID
		if(strcmp((char*)buf,"911")==0)//ID==911
		{
			GT911_ReadReg(GT911_CONFIG_VERSION_REG, (uint8_t *)&buf[0], 1);
			printf("CTP Ver:%2x\r\n",buf[0]);
			
//			GT911_CFG_TBL[0] = buf[0];//��ȡ�����ļ��汾������У���
//			for(i=0;i<sizeof(GT911_CFG_TBL)-2;i++)
//			{
//					config_Checksum += GT911_CFG_TBL[i];
//			}
//			GT911_CFG_TBL[184] = (~config_Checksum)+1;  
//			GT911_WriteReg(GT911_CONFIG_REG, (uint8_t *)GT911_CFG_TBL, sizeof(GT911_CFG_TBL));// ����������Ϣ����
			GT911_INT_GPIO_Input_Init();  //�趨INT����Ϊ�������� 
			GT911_Soft_Reset(); //��λGT911
			delay_ms(200);   //��ʼ��У׼���ȴ�200ms
			return 0;
		} 
		return 1;
}



/*
*********************************************************************************************************
*	�� �� ��: GT911_WriteReg
*	����˵��: д1���������Ķ���Ĵ���
*	��    ��: _usRegAddr : �Ĵ�����ַ
*			  _pRegBuf : �Ĵ������ݻ�����
*			 _ucLen : ���ݳ���
*	�� �� ֵ: ��
*********************************************************************************************************
*/
static void GT911_WriteReg(uint16_t _usRegAddr, uint8_t *_pRegBuf, uint8_t _ucLen)
{
	uint8_t i;

	CT_IIC_Start();					/* ���߿�ʼ�ź� */
	CT_IIC_Send_Byte(GT911_CMD_WR);	/* �����豸��ַ+д�ź� */
	CT_IIC_Wait_Ack();
	CT_IIC_Send_Byte(_usRegAddr >> 8);	/* ��ַ��8λ */
	CT_IIC_Wait_Ack();
	CT_IIC_Send_Byte(_usRegAddr);		/* ��ַ��8λ */
	CT_IIC_Wait_Ack();
	for (i = 0; i < _ucLen; i++)
	{
	  CT_IIC_Send_Byte(_pRegBuf[i]);		/* �Ĵ������� */
		CT_IIC_Wait_Ack();
	}
  CT_IIC_Stop();                   			/* ����ֹͣ�ź� */
}

/*
*********************************************************************************************************
*	�� �� ��: GT911_ReadReg
*	����˵��: ��1���������Ķ���Ĵ���
*	��    ��: _usRegAddr : �Ĵ�����ַ
*			  _pRegBuf : �Ĵ������ݻ�����
*			 _ucLen : ���ݳ���
*	�� �� ֵ: ��
*********************************************************************************************************
*/
static void GT911_ReadReg(uint16_t _usRegAddr, uint8_t *_pRegBuf, uint8_t _ucLen)
{
	uint8_t i;

	CT_IIC_Start();					/* ���߿�ʼ�ź� */
	CT_IIC_Send_Byte(GT911_CMD_WR);	/* �����豸��ַ+д�ź� */
	CT_IIC_Wait_Ack();
	CT_IIC_Send_Byte(_usRegAddr >> 8);	/* ��ַ��8λ */
	CT_IIC_Wait_Ack();
	CT_IIC_Send_Byte(_usRegAddr);		/* ��ַ��8λ */
	CT_IIC_Wait_Ack();
	CT_IIC_Stop();	
	CT_IIC_Start();
	CT_IIC_Send_Byte(GT911_CMD_RD);	/* �����豸��ַ+���ź� */
	CT_IIC_Wait_Ack();
	for (i = 0; i < _ucLen - 1; i++)
	{
		_pRegBuf[i] = CT_IIC_Read_Byte(1);	/* ���Ĵ������� */
	}

	/* ���һ������ */
	_pRegBuf[i] = CT_IIC_Read_Byte(0);		/* ���Ĵ������� */
	CT_IIC_Stop();							/* ����ֹͣ�ź� */
}


const u16 GT911_TPX_TBL[5]={GT911_TP1_REG,GT911_TP2_REG,GT911_TP3_REG,GT911_TP4_REG,GT911_TP5_REG};
//ɨ�败����(���ò�ѯ��ʽ)
//mode:0,����ɨ��.
//����ֵ:��ǰ����״̬.
//0,�����޴���;1,�����д���
u8 GT911_Scan(u8 mode)
{
	u8 buf[4];
	u8 i=0;
	u8 res=0;
	u8 temp;
	u8 tempsta;
// 	static u8 t=0;//���Ʋ�ѯ���,�Ӷ�����CPUռ����   
//	t++;
//	if((t%10)==0||t<10)//����ʱ,ÿ����10��CTP_Scan�����ż��1��,�Ӷ���ʡCPUʹ����
//	{
		GT911_ReadReg(GT911_GSTID_REG, &mode, 1); //��ȡ�������״̬  
	
 		if(mode&0X80&&((mode&0XF)<6))
		{
			temp=0;
			GT911_WriteReg(GT911_CLEARBUF_REG,&temp, 1);//���־ 	
		}		
		if((mode&0XF)&&((mode&0XF)<6))
		{
			temp=0XFF<<(mode&0XF);		//����ĸ���ת��Ϊ1��λ��,ƥ��tp_dev.sta���� 
			tempsta=tp_dev.sta;			//���浱ǰ��tp_dev.staֵ
			tp_dev.sta=(~temp)|TP_PRES_DOWN|TP_CATH_PRES; 
			tp_dev.x[4]=tp_dev.x[0];	//���津��0������
			tp_dev.y[4]=tp_dev.y[0];
			for(i=0;i<5;i++)
			{
				if(tp_dev.sta&(1<<i))	//������Ч?
				{
					GT911_ReadReg(GT911_TPX_TBL[i],buf,4);	//��ȡXY����ֵ
					if(tp_dev.touchtype&0X01)//����
					{
						tp_dev.x[i]=((u16)buf[1]<<8)+buf[0];
						tp_dev.y[i]=((u16)buf[3]<<8)+buf[2];
					}else
					{
						tp_dev.y[i]=((u16)buf[1]<<8)+buf[0];
						tp_dev.x[i]=479-(((u16)buf[3]<<8)+buf[2]);
					}  
					//printf("x[%d]:%d,y[%d]:%d\r\n",i,tp_dev.x[i],i,tp_dev.y[i]);
				}			
			} 
			res=1;
			tp_dev.x[0] *=0.78125f;
			tp_dev.y[0] *=0.8f;
			if(tp_dev.x[0]>lcddev.width||tp_dev.y[0]>lcddev.height)//�Ƿ�����(���곬����)
			{ 
				if((mode&0XF)>1)		//��������������,�򸴵ڶ�����������ݵ���һ������.
				{
					tp_dev.x[0]=tp_dev.x[1];
					tp_dev.y[0]=tp_dev.y[1];
					//t=0;				//����һ��,��������������10��,�Ӷ����������
				}else					//�Ƿ�����,����Դ˴�����(��ԭԭ����)  
				{
					tp_dev.x[0]=tp_dev.x[4];
					tp_dev.y[0]=tp_dev.y[4];
					mode=0X80;		
					tp_dev.sta=tempsta;	//�ָ�tp_dev.sta
				}
			}//else t=0;					//����һ��,��������������10��,�Ӷ����������
		}
	//}
	if((mode&0X8F)==0X80)//�޴����㰴��
	{ 
		if(tp_dev.sta&TP_PRES_DOWN)	//֮ǰ�Ǳ����µ�
		{
			tp_dev.sta&=~(1<<7);	//��ǰ����ɿ�
		}else						//֮ǰ��û�б�����
		{ 
			tp_dev.x[0]=0xffff;
			tp_dev.y[0]=0xffff;
			tp_dev.sta&=0XE0;	//�������Ч���	
		}	 
	} 	
	//if(t>240)t=10;//���´�10��ʼ����
	return res;
}

///*
//*********************************************************************************************************
//*	�� �� ��: GT911_ReadProductID
//*	����˵��: ʶ����ʾģ����𡣶�ȡGT911 ProductID��
//*	��    ��: ��
//*	�� �� ֵ: ��ʾģ�����
//*********************************************************************************************************
//*/
//uint32_t GT911_ReadProductID(void)
//{
//	uint8_t buf[4];
//	uint32_t value = 0;
//	/* 	Product_ID*/
//	GT911_ReadReg(GT911_PRODUCT_ID_REG, buf, 4);
//	value = ((uint32_t)buf[3]<<24)+((uint32_t)buf[2]<<16)+((uint32_t)buf[1]<<8)+buf[0];
//	return value;
//}

///*
//*********************************************************************************************************
//*	�� �� ��: GT911_ReadFirmwareVersion
//*	����˵��: ���GT911��оƬ�̼��汾
//*	��    ��: ��
//*	�� �� ֵ: 16λ�汾��
//*********************************************************************************************************
//*/
//uint16_t GT911_ReadFirmwareVersion(void)
//{
//	uint8_t buf[2];

//	GT911_ReadReg(GT911_FIRMWARE_VERSION_REG, buf, 2);

//	return ((uint16_t)buf[1] << 8) + buf[0];
//}









