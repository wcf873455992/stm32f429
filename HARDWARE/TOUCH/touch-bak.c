#include "touch.h" 
//#include "display.h"
#include "delay.h"
#include "stdlib.h"
#include "math.h"
//#include "bsp_w25qxx.h"   
//#include "config.h"


Adjustd_t Adj_cfg;
_m_tp_dev tp_dev=
{
	TP_Init,
	TP_Scan,
	TP_Adjust,
	0,
	0, 
	0,
	0,
	0,
	0,	  	 		
	0,
	0,	  	 		
};					
//默认为touchtype=0的数据.

u8 CMD_RDX=0XD0;
u8 CMD_RDY=0X90;

u16  Adjustd_XYL[5][2];//校准使用的逻辑坐标
u16  Adjustd_XY[5][2]={ //校准使用的物理坐标
{LCD_WIDTH/2,LCD_HEIGHT/2},//中心点
{20,20},
{LCD_WIDTH-20,20},
{LCD_WIDTH-20,LCD_HEIGHT-20},
{20,LCD_HEIGHT-20},
};
//SPI写数据
//向触摸屏IC写入1byte数据    
//num:要写入的数据
void TP_Write_Byte(u8 num)    
{  
	u8 count=0;   
	for(count=0;count<8;count++)  
	{ 	  
		if(num&0x80)TDIN=1;  
		else TDIN=0;   
		num<<=1;    
		TCLK=0; 
		delay_us(1);
		TCLK=1;		//上升沿有效	        
	}		 			    
} 		 
//SPI读数据 
//从触摸屏IC读取adc值
//CMD:指令
//返回值:读到的数据	   
u16 TP_Read_AD(u8 CMD)	  
{ 	 
	u8 count=0; 	  
	u16 Num=0; 
	TCLK=0;		//先拉低时钟 	 
	TDIN=0; 	//拉低数据线
	TCS=0; 		//选中触摸屏IC
	TP_Write_Byte(CMD);//发送命令字
	delay_us(6);//ADS7846的转换时间最长为6us
	TCLK=0; 	     	    
	delay_us(1);    	   
	TCLK=1;		//给1个时钟，清除BUSY
	delay_us(1);    
	TCLK=0; 	     	    
	for(count=0;count<16;count++)//读出16位数据,只有高12位有效 
	{ 				  
		Num<<=1; 	 
		TCLK=0;	//下降沿有效  	    	   
		delay_us(1);    
 		TCLK=1;
 		if(DOUT)Num++; 		 
	}  	
	Num>>=4;   	//只有高12位有效.
	Num = 0x0fff-Num;
	TCS=1;		//释放片选	 
	return(Num);   
}
//读取一个坐标值(x或者y)
//连续读取READ_TIMES次数据,对这些数据升序排列,
//然后去掉最低和最高LOST_VAL个数,取平均值 
//xy:指令（CMD_RDX/CMD_RDY）
//返回值:读到的数据
#define READ_TIMES 5 	//读取次数
#define LOST_VAL 1	  	//丢弃值
u16 TP_Read_XOY(u8 xy)
{
	u16 i, j;
	u16 buf[READ_TIMES];
	u16 sum=0;
	u16 temp;
	for(i=0;i<READ_TIMES;i++)buf[i]=TP_Read_AD(xy);		 		    
	for(i=0;i<READ_TIMES-1; i++)//排序
	{
		for(j=i+1;j<READ_TIMES;j++)
		{
			if(buf[i]>buf[j])//升序排列
			{
				temp=buf[i];
				buf[i]=buf[j];
				buf[j]=temp;
			}
		}
	}	  
	sum=0;
	for(i=LOST_VAL;i<READ_TIMES-LOST_VAL;i++)sum+=buf[i];
	temp=sum/(READ_TIMES-2*LOST_VAL);
	return temp;   
} 
//读取x,y坐标
//最小值不能少于100.
//x,y:读取到的坐标值
//返回值:0,失败;1,成功。
u8 TP_Read_XY(u16 *x,u16 *y)
{
	u16 xtemp,ytemp;			 	 		  
	xtemp=TP_Read_XOY(CMD_RDX);
	ytemp=TP_Read_XOY(CMD_RDY);	  												   
	//if(xtemp<100||ytemp<100)return 0;//读数失败
	*x=xtemp;
	*y=ytemp;
	return 1;//读数成功
}
//连续2次读取触摸屏IC,且这两次的偏差不能超过
//ERR_RANGE,满足条件,则认为读数正确,否则读数错误.	   
//该函数能大大提高准确度
//x,y:读取到的坐标值
//返回值:0,失败;1,成功。
#define ERR_RANGE 50 //误差范围 
u8 TP_Read_XY2(u16 *x,u16 *y) 
{
	u16 x1,y1;
 	u16 x2,y2;
 	u8 flag;    
    flag=TP_Read_XY(&x1,&y1);   
    if(flag==0)return(0);
    flag=TP_Read_XY(&x2,&y2);	   
    if(flag==0)return(0);   
    if(((x2<=x1&&x1<x2+ERR_RANGE)||(x1<=x2&&x2<x1+ERR_RANGE))//前后两次采样在+-50内
    &&((y2<=y1&&y1<y2+ERR_RANGE)||(y1<=y2&&y2<y1+ERR_RANGE)))
    {
        *x=(x1+x2)/2;
        *y=(y1+y2)/2;
        return 1;
    }else return 0;	  
}   
//////////////////////////////////////////////////////////////////////////////////		  
//与LCD部分有关的函数  
//画一个触摸点
//用来校准用的
//x,y:坐标
//bcolor:背景色
//pcolor:颜色
void TP_Drow_Touch_Point(u16 x,u16 y,u16 bcolor,u16 pcolor)
{
	LCD_DrawLine(x-12,y,x+13,y,1,pcolor);//横线
	LCD_DrawLine(x,y-12,x,y+13,1,pcolor);//竖线
	LCD_DrawPoint(x+1,y+1,pcolor);
	LCD_DrawPoint(x-1,y+1,pcolor);
	LCD_DrawPoint(x+1,y-1,pcolor);
	LCD_DrawPoint(x-1,y-1,pcolor);
	LCD_Draw_Circle(x,y,6,1,bcolor,pcolor);//画中心圈
}	  
//画一个大点(2*2的点)		   
//x,y:坐标
//color:颜色
void TP_Draw_Big_Point(u16 x,u16 y,u16 color)
{	    
	POINT_COLOR=color;
	LCD_DrawPoint(x,y,color);//中心点 
	LCD_DrawPoint(x+1,y,color);
	LCD_DrawPoint(x,y+1,color);
	LCD_DrawPoint(x+1,y+1,color);	 	  	
}							  
//////////////////////////////////////////////////////////////////////////////////		  
//触摸按键扫描
//tp:0,屏幕坐标(物理坐标);1,逻辑坐标(校准等特殊场合用)
//返回值:当前触屏状态.
//0,触屏无触摸;1,触屏有触摸
u8 TP_Scan(u8 tp)
{			   
	if(PEN==0)//有按键按下
	{
		if(tp)TP_Read_XY2(&tp_dev.x[0],&tp_dev.y[0]);//读取物理坐标
		else if(TP_Read_XY2(&tp_dev.x[0],&tp_dev.y[0]))//读取屏幕坐标
		{
			tp_dev.x[0] = (float)((long)tp_dev.x[0]-(long)tp_dev.XLC)/tp_dev.KX+tp_dev.XC;//将结果转换为屏幕坐标
			tp_dev.y[0] = (float)((long)tp_dev.y[0]-(long)tp_dev.YLC)/tp_dev.KY+tp_dev.YC;
	 	} 
		if((tp_dev.sta&TP_PRES_DOWN)==0)//之前没有被按下
		{		 
			tp_dev.sta=TP_PRES_DOWN|TP_CATH_PRES;//按键按下  
			tp_dev.x[4]=tp_dev.x[0];//记录第一次按下时的坐标
			tp_dev.y[4]=tp_dev.y[0];  	   			 
		}			   
	}else
	{
		if(tp_dev.sta&TP_PRES_DOWN)//之前是被按下的
		{
			tp_dev.sta&=~(1<<7);//标记按键松开	
		}else//之前就没有被按下
		{
			tp_dev.x[4]=0;
			tp_dev.y[4]=0;
			tp_dev.x[0]=0xffff;
			tp_dev.y[0]=0xffff;
		}	    
	}
	return tp_dev.sta&TP_PRES_DOWN;//返回当前的触屏状态
}  

//校验校准坐标值是否符合要求
u8 CheckPoint(void)
{
	if(Adjustd_XYL[2][0] > Adjustd_XYL[1][0]\
		&&Adjustd_XYL[3][0] > Adjustd_XYL[4][0]\
		&&Adjustd_XYL[3][1] > Adjustd_XYL[2][1]\
		&&Adjustd_XYL[4][1] > Adjustd_XYL[1][1])//判断四个检测坐标是否在正常位置
	return 1;
	return 0;
}
//两个数差值的绝对值
float subAbs(u32 a,u32 b)
{
	if(a>b)return (a-b);
	return (b-a);
}
//////////////////////////////////////////////////////////////////////////	 
//保存在flash里面的地址
#define ADJUSTDADDR  1024*1024*31+1024*512 					//31.5M
//保存校准参数										    
void TP_Save_Adjdata(void)
{
	Adj_cfg.KX = tp_dev.KX; //x校正因子 
	Adj_cfg.KY = tp_dev.KY; //y校正因子   
	Adj_cfg.XLC = tp_dev.XLC;//中点x逻辑值
	Adj_cfg.YLC = tp_dev.YLC;//中点y逻辑值
	Adj_cfg.touchtype = tp_dev.touchtype;//触屏类型
	Adj_cfg.ENABLE = 0X0A;//标记校准过了
	W25QXX_Write((u8*)&Adj_cfg,ADJUSTDADDR,sizeof(Adj_cfg));//校准数据保存到flash	 
}
//得到保存在EEPROM里面的校准值
//返回值：1，成功获取数据
//        0，获取失败，要重新校准
u8 TP_Get_Adjdata(void)
{					  
	W25QXX_Read((u8*)&Adj_cfg,ADJUSTDADDR,sizeof(Adj_cfg));//从flash中读取校准数据		 
	if(Adj_cfg.ENABLE==0X0A)//触摸屏已经校准过了			   
	{    			
		tp_dev.KX = Adj_cfg.KX;//得到x校准参数
		tp_dev.KY = Adj_cfg.KY;//得到y校准参数
		tp_dev.XLC = Adj_cfg.XLC;//得到中点x逻辑值
		tp_dev.YLC = Adj_cfg.YLC;//得到中点y逻辑值
		tp_dev.touchtype = Adj_cfg.touchtype;//读取触屏类型标记
		tp_dev.XC = Adjustd_XY[0][0];//中点物理坐标
		tp_dev.YC = Adjustd_XY[0][1];		 
		return 1;	 
	}
	return 0;
}	 
//提示字符串
char* const TP_REMIND_MSG_TBL="请使用手写笔点击屏幕上的十字，直到屏幕调整完成";
 					  	 
//触摸屏校准代码
//得到四个校准参数
void TP_Adjust(void)
{								 
	u8  cnt=0;	
	u32 S1L,S2L,S3L,S4L;
	u16 S1,S2;//,S3,S4;	
	u16 outtime=0;
 	cnt=0;				
	LCD_Clear(WHITE);//清屏   	   
	Show_Str(40,50,(u8*)TP_REMIND_MSG_TBL,24,0,WHITE,BLACK);//显示提示信息
	TP_Drow_Touch_Point(Adjustd_XY[0][0],Adjustd_XY[0][1],WHITE,RED);//画点0 
	tp_dev.sta=0;//消除触发信号 
	while(1)//如果连续10秒钟没有按下,则自动退出
	{
		tp_dev.scan(1);//扫描物理坐标
		if((tp_dev.sta&0xc0)==TP_CATH_PRES)//按键按下了一次(此时按键松开了.)
		{	
			outtime=0;		
			tp_dev.sta&=~(1<<6);//标记按键已经被处理过了.
						   			   
			Adjustd_XYL[cnt][0]=tp_dev.x[0];
			Adjustd_XYL[cnt][1]=tp_dev.y[0];
			cnt++;	  
			switch(cnt)
			{			
				case 1:						 
					TP_Drow_Touch_Point(Adjustd_XY[0][0],Adjustd_XY[0][1],WHITE,WHITE);				//清除点0 
					TP_Drow_Touch_Point(Adjustd_XY[1][0],Adjustd_XY[1][1],WHITE,RED);	//画点1
					break;
				case 2:						 
					TP_Drow_Touch_Point(Adjustd_XY[1][0],Adjustd_XY[1][1],WHITE,WHITE);				//清除点1 
					TP_Drow_Touch_Point(Adjustd_XY[2][0],Adjustd_XY[2][1],WHITE,RED);	//画点2
					break;
				case 3:
 					TP_Drow_Touch_Point(Adjustd_XY[2][0],Adjustd_XY[2][1],WHITE,WHITE);	//清除点2
					TP_Drow_Touch_Point(Adjustd_XY[3][0],Adjustd_XY[3][1],WHITE,RED);	//画点3
					break;
				case 4:
 					TP_Drow_Touch_Point(Adjustd_XY[3][0],Adjustd_XY[3][1],WHITE,WHITE);			//清除点3
 					TP_Drow_Touch_Point(Adjustd_XY[4][0],Adjustd_XY[4][1],WHITE,RED);	//画点4
					break;
				case 5:	 //全部5个点已经得到
					if(CheckPoint())
					{
						S1L=Adjustd_XYL[2][0] - Adjustd_XYL[1][0];
						S3L=Adjustd_XYL[3][0] - Adjustd_XYL[4][0];
						S2L=Adjustd_XYL[3][1] - Adjustd_XYL[2][1];
						S4L=Adjustd_XYL[4][1] - Adjustd_XYL[1][1];
						S1=Adjustd_XY[2][0] - Adjustd_XY[1][0];
						if(((subAbs(S1L,S3L)/(S1L+S3L)))<0.07f&&((subAbs(S2L,S4L)/(S2L+S4L)))<0.07f)
						{
							//S3=Adjustd_XY[3][0] - Adjustd_XY[4][0];
							S2=Adjustd_XY[3][1] - Adjustd_XY[2][1];
							//S4=Adjustd_XY[4][1] - Adjustd_XY[1][1];
							tp_dev.KX = (float)(( S1L + S3L )/2)/S1;
							tp_dev.KY = (float)(( S2L + S4L )/2)/S2;
							tp_dev.XLC = Adjustd_XYL[0][0];
							tp_dev.YLC = Adjustd_XYL[0][1];
							tp_dev.XC = Adjustd_XY[0][0];
							tp_dev.YC = Adjustd_XY[0][1];
							LCD_Clear(WHITE);//清屏
							LCD_SystemString(35,110,"Touch Screen Adjust OK!",16,WHITE,BLUE);//校正完成
							delay_ms(1000);
							TP_Save_Adjdata();  
							LCD_Clear(BACK_COLOR);//清屏   
							return;//校正完成		
						}
						else
						{
							cnt=0;
							TP_Drow_Touch_Point(Adjustd_XY[4][0],Adjustd_XY[4][1],WHITE,WHITE);			//清除点4
							TP_Drow_Touch_Point(Adjustd_XY[0][0],Adjustd_XY[0][1],WHITE,RED);	//画点0
						}
					}
					else 
					{
						cnt=0;
						TP_Drow_Touch_Point(Adjustd_XY[4][0],Adjustd_XY[4][1],WHITE,WHITE);			//清除点4
						TP_Drow_Touch_Point(Adjustd_XY[0][0],Adjustd_XY[0][1],WHITE,RED);	//画点0
					}
			}
		}
		delay_ms(10);
		outtime++;
		if(outtime>1000)
		{
			TP_Get_Adjdata();
			LCD_Clear(BACK_COLOR);//清屏   
			break;
	 	} 
 	}
}
//触摸屏初始化  		    
//返回值:0,没有进行校准
//       1,进行过校准
u8 TP_Init(void)
{	
   GPIO_InitTypeDef GPIO_Initure;
	if(GT911_Init()==0)//GT911初始化成功，说明使用的电容屏
	{
		tp_dev.scan=GT911_Scan;		//扫描函数指向GT911触摸屏扫描		
		tp_dev.touchtype|=0X80;			//电容屏 
		tp_dev.touchtype|=lcddev.dir&0X01;//横屏还是竖屏 
	}else //电阻屏
	{
        
		__HAL_RCC_GPIOA_CLK_ENABLE();			//开启GPIOA时钟
		__HAL_RCC_GPIOH_CLK_ENABLE();			//开启GPIOH时钟
		__HAL_RCC_GPIOI_CLK_ENABLE();			//开启GPIOI时钟
		__HAL_RCC_GPIOG_CLK_ENABLE();			//开启GPIOG时钟
		
		GPIO_Initure.Pin=GPIO_PIN_0;            //PA0      //手动校准按钮
    GPIO_Initure.Mode=GPIO_MODE_INPUT;      //输入
    GPIO_Initure.Pull=GPIO_PULLDOWN;        //下拉
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;     //高速
    HAL_GPIO_Init(GPIOA,&GPIO_Initure);
        
		//PH6
		GPIO_Initure.Pin=GPIO_PIN_6;            //PH6
		GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;  //推挽输出
		GPIO_Initure.Pull=GPIO_PULLUP;          //上拉
		GPIO_Initure.Speed=GPIO_SPEED_HIGH;     //高速
		HAL_GPIO_Init(GPIOH,&GPIO_Initure);     //初始化
        
		//PI3,8
		GPIO_Initure.Pin=GPIO_PIN_3|GPIO_PIN_8; //PI3,8
		HAL_GPIO_Init(GPIOI,&GPIO_Initure);     //初始化
        
		//PH7
		GPIO_Initure.Pin=GPIO_PIN_7;            //PH7
		GPIO_Initure.Mode=GPIO_MODE_INPUT;      //输入
		HAL_GPIO_Init(GPIOH,&GPIO_Initure);     //初始化
        
		//PG3
		GPIO_Initure.Pin=GPIO_PIN_3;            //PG3
		HAL_GPIO_Init(GPIOG,&GPIO_Initure);     //初始化
		TP_Read_XY(&tp_dev.x[0],&tp_dev.y[0]);//第一次读取初始化	 
//		while(1)
//		{
//			tp_dev.scan(1);//扫描物理坐标
//			LCD_ShowNum(0,100,tp_dev.x[0],5,24,0x80,BACK_COLOR,POINT_COLOR);
//			LCD_ShowNum(0,130,tp_dev.y[0],5,24,0x80,BACK_COLOR,POINT_COLOR);			   			   
//		}
        
		
		if((TP_Get_Adjdata()==0)||(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_0)==GPIO_PIN_SET))//未校准或手动人为校准
		{ 										    
			LCD_Clear(WHITE);//清屏
			TP_Adjust();  	//屏幕校准  
		}	
		else return 0;				
	}
	return 1; 									 
}









