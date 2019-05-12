#include "gt911.h"
#include "touch.h"
#include "ctiic.h"
#include "tftlcd.h"
#include "usart.h"
#include "delay.h" 
#include "string.h" 




///* GT911单个触点配置参数，一次性写入 */
//u8 GT911_CFG_TBL[]=
//{
//0x42,		//0x8047		版本号
//0x20,0x03,	//0x8048/8049	X坐标输出最大值800
//0xE0,0x01,	//0x804a/804b	Y坐标输出最大值480
////0x25,0x02,	//0x804a/804b	Y坐标输出最大值480
//0x05,	//0x804c	输出触点个数上限
//0x3D,	//0x804d	软件降噪，下降沿触发
//0x00,	//0x804e	reserved
//0x01,	//0x804f	手指按下去抖动次数
//0x08,	//0x8050	原始坐标窗口滤波值	
//0x28,	//0x8051	大面积触点个数
//0x08,	//0x8052	噪声消除值
//0x50,	//0x8053	屏上触摸点从无到有的阈值
//0x3C,	//0x8054	屏上触摸点从有到无的阈值
//0x03,	//0x8055	进低功耗时间	s
//0x05,	//0x8056	坐标上报率
//0x00,	//0x8057	X坐标输出门上限
//0x00,	//0x8058	Y坐标输出门上限
//0x00,0x00,	//0x8059-0x805a	reserved
//0x00,	//0x805b	reserved
//0x00,	//0x805c	reserved
//0x00,	//0x805d	划线过程中小filter设置
//0x18,	//0x805e	拉伸区间	1	系数
//0x1A,	//0x805f	拉伸区间	2	系数
//0x1E,	//0x8060	拉伸区间	3	系数
//0x14,	//0x8061	各拉伸区间基数
//0x89,	//0x8062	、、
//0x2A,	//0x8063	、、
//0x0B,	//0x8064	、、
//0x40,	//0x8065	驱动组A的驱动频率倍频系数
//0x42,	//0x8066	驱动组B的驱动频率倍频系数
//0xB5,	//0x8067	驱动组A、B的基频
//0x06,	//0x8068	
//0x00,	//0x8069	相邻两次驱动信号输出时间间隔
//0x00,	//0x806a	
//0x00,	//0x806b	、、
//0x02,	//0x806c	、、
//0x02,	//0x806d	原始值放大系数
//0x1D,	//0x806e	、、
//0x00,	//0x806f	reserved
//0x01,	//0x8070	、、
//0x00,0x00,	//reserved
//0x00,	//0x8073	、、
//0x03,0x64,0x00,0x00,0x00,0x00,		//0x8071 - 0x8079 reserved
//0x32,         //0x807a	跳频范围的起点频率
//0x5A,	//0x807b	跳频范围的终点频率
//0x94,	//0x807c	多次噪声检测后确定噪声量，1-63有效
//0xC5,	//0x807d	噪声检测超时时间
//0x02,	//0x807e	、、
//0x08,	//0x807f	判别有干扰的门限
//0x00,0x00,	//0x8081	reserved	
//0x00,         //0x8082	跳频检测区间频段1中心点基频（适用于驱动A、B）
//0x98,	//0x8083
//0x35,	//0x8084	跳频检测区间频段1中心点倍频系数
//0x00,	//0x8085	跳频检测区间频段2中心点基频(驱动A、B在此基础上换算)
//0x8A,	//0x8086	
//0x3B,	//0x8087	跳频检测区间频段2中心点倍频系数
//0x00,	//0x8088	跳频检测区间频段3中心点基频（适用于驱动A、B）
//0x7A,	//0x8089	
//0x43,	//0x808a	跳频检测区间频段3中心点倍频系数
//0x00,	//0x808b	跳频检测区间频段4中心点基频（适用于驱动A、B）
//0x6E,	//0x808c	
//0x4B,	//0x808d	跳频检测区间频段4中心点倍频系数
//0x00,	//0x808e	跳频检测区间频段5中心点基频（适用于驱动A、B）
//0x62,	//0x808f	
//0x55,	//0x8090	跳频检测区间频段5中心点倍频系数
//0x00,0x62,		//reserved
//0x00,	//0x8093	key1位置	0：无按键
//0x00,	//0x8094	key2位置	0：无按键
//0x00,	//0x8095	key3位置	0：无按键
//0x00,	//0x8096	key4位置	0：无按键
//0x00,	//0x8097	reserved
//0x00,	//0x8098	reserved
//0x00,	//0x8099	reserved
//0x00,	//0x809a	reserved
//0x00,	//0x809b	reserved
//0x00,	//0x809c	reserved
//0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,\
//0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,	//0x809d-0x80b2	reserved
//0x00,	//0x80b3	合框距离
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
//0x60,	//0x80ff	配置信息校验
//0x01	//0x8100	配置以更新标记
//};


/*
*********************************************************************************************************
*	函 数 名: GT911_INT_GPIO_Init
*	功能说明: 初始化RST引脚为推挽输出
*	形    参:  无
*	返 回 值: 无
*********************************************************************************************************
*/
void GT911_RST_INT_GPIO_Init(void)
{
	 GPIO_InitTypeDef GPIO_Initure;
    
    __HAL_RCC_GPIOH_CLK_ENABLE();			//开启GPIOH时钟
    __HAL_RCC_GPIOI_CLK_ENABLE();			//开启GPIOI时钟
          
		//PI8
    GPIO_Initure.Pin=GPIO_PIN_8;            //PI8
    GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;  //推挽输出
		GPIO_Initure.Pull=GPIO_NOPULL;          //上下拉电阻不使能
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;     //高速
    HAL_GPIO_Init(GPIOI,&GPIO_Initure);     //初始化
			
    //PH7
    GPIO_Initure.Pin=GPIO_PIN_7;            //PH7
    GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;      //设为开漏模式 
    GPIO_Initure.Pull=GPIO_NOPULL;          //上下拉电阻不使能
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;     //高速
    HAL_GPIO_Init(GPIOH,&GPIO_Initure);     //初始化             
}
/*
*********************************************************************************************************
*	函 数 名: GT911_INT_GPIO_Input_Init
*	功能说明: 设定INT引脚为输入悬空
*	形    参:  无
*	返 回 值: 无
*********************************************************************************************************
*/
void GT911_INT_GPIO_Input_Init(void)
{
	GPIO_InitTypeDef GPIO_Initure;
    
  __HAL_RCC_GPIOH_CLK_ENABLE();			//开启GPIOH时钟
	GPIO_Initure.Pin=GPIO_PIN_7;            //PH7
	GPIO_Initure.Mode=GPIO_MODE_INPUT;      //输入
	GPIO_Initure.Pull=GPIO_NOPULL;          //上下拉电阻不使能
	GPIO_Initure.Speed=GPIO_SPEED_HIGH;     //高速
	HAL_GPIO_Init(GPIOH,&GPIO_Initure);     //初始化
    
}


/*
*********************************************************************************************************
*	函 数 名: GT911_Hard_Reset
*	功能说明: G911硬复位操作
*	形    参:  无
*	返 回 值: 无
*********************************************************************************************************
*/
void GT911_Hard_Reset(void)
{
    GT911_RST_INT_GPIO_Init();
		GT911_RST_0();                //RST引脚低电平
		GT911_INT_0();                //INT引脚低电平
		delay_ms(30);               //延时30ms，最短1
		GT911_RST_1();                //RST引脚高电平
		GT911_INT_0();                //INT引脚低电平
		delay_ms(30);              //延时30ms，最短20
		GT911_INT_0();
		delay_ms(30);              //延时30ms，最短20
		GT911_INT_1();
           
}
/*
*********************************************************************************************************
*	函 数 名: GT911_Soft_Reset
*	功能说明: G911软复位操作。
*	形    参:  无
*	返 回 值: 无
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
*	函 数 名: GT911_Init
*	功能说明: 配置触摸芯片.
*	形    参:  无
*	返 回 值: 无
*********************************************************************************************************
*/
u8 GT911_Init(void)
{
		u8 buf[4];
   // u8 config_Checksum = 0,i;	
    CT_IIC_Init();
    GT911_Hard_Reset(); //硬复位GT911
    GT911_Soft_Reset(); //软复位GT911
		
		GT911_ReadReg(GT911_PRODUCT_ID_REG, (uint8_t *)&buf[0], 3);
		buf[3]=0;
		printf("CTP ID:%s\r\n",buf);	//打印ID
		if(strcmp((char*)buf,"911")==0)//ID==911
		{
			GT911_ReadReg(GT911_CONFIG_VERSION_REG, (uint8_t *)&buf[0], 1);
			printf("CTP Ver:%2x\r\n",buf[0]);
			
//			GT911_CFG_TBL[0] = buf[0];//读取配置文件版本，计算校验和
//			for(i=0;i<sizeof(GT911_CFG_TBL)-2;i++)
//			{
//					config_Checksum += GT911_CFG_TBL[i];
//			}
//			GT911_CFG_TBL[184] = (~config_Checksum)+1;  
//			GT911_WriteReg(GT911_CONFIG_REG, (uint8_t *)GT911_CFG_TBL, sizeof(GT911_CFG_TBL));// 发送配置信息参数
			GT911_INT_GPIO_Input_Init();  //设定INT引脚为输入悬空 
			GT911_Soft_Reset(); //软复位GT911
			delay_ms(200);   //初始化校准，等待200ms
			return 0;
		} 
		return 1;
}



/*
*********************************************************************************************************
*	函 数 名: GT911_WriteReg
*	功能说明: 写1个或连续的多个寄存器
*	形    参: _usRegAddr : 寄存器地址
*			  _pRegBuf : 寄存器数据缓冲区
*			 _ucLen : 数据长度
*	返 回 值: 无
*********************************************************************************************************
*/
static void GT911_WriteReg(uint16_t _usRegAddr, uint8_t *_pRegBuf, uint8_t _ucLen)
{
	uint8_t i;

	CT_IIC_Start();					/* 总线开始信号 */
	CT_IIC_Send_Byte(GT911_CMD_WR);	/* 发送设备地址+写信号 */
	CT_IIC_Wait_Ack();
	CT_IIC_Send_Byte(_usRegAddr >> 8);	/* 地址高8位 */
	CT_IIC_Wait_Ack();
	CT_IIC_Send_Byte(_usRegAddr);		/* 地址低8位 */
	CT_IIC_Wait_Ack();
	for (i = 0; i < _ucLen; i++)
	{
	  CT_IIC_Send_Byte(_pRegBuf[i]);		/* 寄存器数据 */
		CT_IIC_Wait_Ack();
	}
  CT_IIC_Stop();                   			/* 总线停止信号 */
}

/*
*********************************************************************************************************
*	函 数 名: GT911_ReadReg
*	功能说明: 读1个或连续的多个寄存器
*	形    参: _usRegAddr : 寄存器地址
*			  _pRegBuf : 寄存器数据缓冲区
*			 _ucLen : 数据长度
*	返 回 值: 无
*********************************************************************************************************
*/
static void GT911_ReadReg(uint16_t _usRegAddr, uint8_t *_pRegBuf, uint8_t _ucLen)
{
	uint8_t i;

	CT_IIC_Start();					/* 总线开始信号 */
	CT_IIC_Send_Byte(GT911_CMD_WR);	/* 发送设备地址+写信号 */
	CT_IIC_Wait_Ack();
	CT_IIC_Send_Byte(_usRegAddr >> 8);	/* 地址高8位 */
	CT_IIC_Wait_Ack();
	CT_IIC_Send_Byte(_usRegAddr);		/* 地址低8位 */
	CT_IIC_Wait_Ack();
	CT_IIC_Stop();	
	CT_IIC_Start();
	CT_IIC_Send_Byte(GT911_CMD_RD);	/* 发送设备地址+读信号 */
	CT_IIC_Wait_Ack();
	for (i = 0; i < _ucLen - 1; i++)
	{
		_pRegBuf[i] = CT_IIC_Read_Byte(1);	/* 读寄存器数据 */
	}

	/* 最后一个数据 */
	_pRegBuf[i] = CT_IIC_Read_Byte(0);		/* 读寄存器数据 */
	CT_IIC_Stop();							/* 总线停止信号 */
}


const u16 GT911_TPX_TBL[5]={GT911_TP1_REG,GT911_TP2_REG,GT911_TP3_REG,GT911_TP4_REG,GT911_TP5_REG};
//扫描触摸屏(采用查询方式)
//mode:0,正常扫描.
//返回值:当前触屏状态.
//0,触屏无触摸;1,触屏有触摸
u8 GT911_Scan(u8 mode)
{
	u8 buf[4];
	u8 i=0;
	u8 res=0;
	u8 temp;
	u8 tempsta;
// 	static u8 t=0;//控制查询间隔,从而降低CPU占用率   
//	t++;
//	if((t%10)==0||t<10)//空闲时,每进入10次CTP_Scan函数才检测1次,从而节省CPU使用率
//	{
		GT911_ReadReg(GT911_GSTID_REG, &mode, 1); //读取触摸点的状态  
	
 		if(mode&0X80&&((mode&0XF)<6))
		{
			temp=0;
			GT911_WriteReg(GT911_CLEARBUF_REG,&temp, 1);//清标志 	
		}		
		if((mode&0XF)&&((mode&0XF)<6))
		{
			temp=0XFF<<(mode&0XF);		//将点的个数转换为1的位数,匹配tp_dev.sta定义 
			tempsta=tp_dev.sta;			//保存当前的tp_dev.sta值
			tp_dev.sta=(~temp)|TP_PRES_DOWN|TP_CATH_PRES; 
			tp_dev.x[4]=tp_dev.x[0];	//保存触点0的数据
			tp_dev.y[4]=tp_dev.y[0];
			for(i=0;i<5;i++)
			{
				if(tp_dev.sta&(1<<i))	//触摸有效?
				{
					GT911_ReadReg(GT911_TPX_TBL[i],buf,4);	//读取XY坐标值
					if(tp_dev.touchtype&0X01)//横屏
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
			if(tp_dev.x[0]>lcddev.width||tp_dev.y[0]>lcddev.height)//非法数据(坐标超出了)
			{ 
				if((mode&0XF)>1)		//有其他点有数据,则复第二个触点的数据到第一个触点.
				{
					tp_dev.x[0]=tp_dev.x[1];
					tp_dev.y[0]=tp_dev.y[1];
					//t=0;				//触发一次,则会最少连续监测10次,从而提高命中率
				}else					//非法数据,则忽略此次数据(还原原来的)  
				{
					tp_dev.x[0]=tp_dev.x[4];
					tp_dev.y[0]=tp_dev.y[4];
					mode=0X80;		
					tp_dev.sta=tempsta;	//恢复tp_dev.sta
				}
			}//else t=0;					//触发一次,则会最少连续监测10次,从而提高命中率
		}
	//}
	if((mode&0X8F)==0X80)//无触摸点按下
	{ 
		if(tp_dev.sta&TP_PRES_DOWN)	//之前是被按下的
		{
			tp_dev.sta&=~(1<<7);	//标记按键松开
		}else						//之前就没有被按下
		{ 
			tp_dev.x[0]=0xffff;
			tp_dev.y[0]=0xffff;
			tp_dev.sta&=0XE0;	//清除点有效标记	
		}	 
	} 	
	//if(t>240)t=10;//重新从10开始计数
	return res;
}

///*
//*********************************************************************************************************
//*	函 数 名: GT911_ReadProductID
//*	功能说明: 识别显示模块类别。读取GT911 ProductID。
//*	形    参: 无
//*	返 回 值: 显示模块类别
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
//*	函 数 名: GT911_ReadFirmwareVersion
//*	功能说明: 获得GT911的芯片固件版本
//*	形    参: 无
//*	返 回 值: 16位版本号
//*********************************************************************************************************
//*/
//uint16_t GT911_ReadFirmwareVersion(void)
//{
//	uint8_t buf[2];

//	GT911_ReadReg(GT911_FIRMWARE_VERSION_REG, buf, 2);

//	return ((uint16_t)buf[1] << 8) + buf[0];
//}









