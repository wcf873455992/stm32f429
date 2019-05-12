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
//Ĭ��Ϊtouchtype=0������.

u8 CMD_RDX=0XD0;
u8 CMD_RDY=0X90;

u16  Adjustd_XYL[5][2];//У׼ʹ�õ��߼�����
u16  Adjustd_XY[5][2]={ //У׼ʹ�õ���������
{LCD_WIDTH/2,LCD_HEIGHT/2},//���ĵ�
{20,20},
{LCD_WIDTH-20,20},
{LCD_WIDTH-20,LCD_HEIGHT-20},
{20,LCD_HEIGHT-20},
};
//SPIд����
//������ICд��1byte����    
//num:Ҫд�������
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
		TCLK=1;		//��������Ч	        
	}		 			    
} 		 
//SPI������ 
//�Ӵ�����IC��ȡadcֵ
//CMD:ָ��
//����ֵ:����������	   
u16 TP_Read_AD(u8 CMD)	  
{ 	 
	u8 count=0; 	  
	u16 Num=0; 
	TCLK=0;		//������ʱ�� 	 
	TDIN=0; 	//����������
	TCS=0; 		//ѡ�д�����IC
	TP_Write_Byte(CMD);//����������
	delay_us(6);//ADS7846��ת��ʱ���Ϊ6us
	TCLK=0; 	     	    
	delay_us(1);    	   
	TCLK=1;		//��1��ʱ�ӣ����BUSY
	delay_us(1);    
	TCLK=0; 	     	    
	for(count=0;count<16;count++)//����16λ����,ֻ�и�12λ��Ч 
	{ 				  
		Num<<=1; 	 
		TCLK=0;	//�½�����Ч  	    	   
		delay_us(1);    
 		TCLK=1;
 		if(DOUT)Num++; 		 
	}  	
	Num>>=4;   	//ֻ�и�12λ��Ч.
	Num = 0x0fff-Num;
	TCS=1;		//�ͷ�Ƭѡ	 
	return(Num);   
}
//��ȡһ������ֵ(x����y)
//������ȡREAD_TIMES������,����Щ������������,
//Ȼ��ȥ����ͺ����LOST_VAL����,ȡƽ��ֵ 
//xy:ָ�CMD_RDX/CMD_RDY��
//����ֵ:����������
#define READ_TIMES 5 	//��ȡ����
#define LOST_VAL 1	  	//����ֵ
u16 TP_Read_XOY(u8 xy)
{
	u16 i, j;
	u16 buf[READ_TIMES];
	u16 sum=0;
	u16 temp;
	for(i=0;i<READ_TIMES;i++)buf[i]=TP_Read_AD(xy);		 		    
	for(i=0;i<READ_TIMES-1; i++)//����
	{
		for(j=i+1;j<READ_TIMES;j++)
		{
			if(buf[i]>buf[j])//��������
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
//��ȡx,y����
//��Сֵ��������100.
//x,y:��ȡ��������ֵ
//����ֵ:0,ʧ��;1,�ɹ���
u8 TP_Read_XY(u16 *x,u16 *y)
{
	u16 xtemp,ytemp;			 	 		  
	xtemp=TP_Read_XOY(CMD_RDX);
	ytemp=TP_Read_XOY(CMD_RDY);	  												   
	//if(xtemp<100||ytemp<100)return 0;//����ʧ��
	*x=xtemp;
	*y=ytemp;
	return 1;//�����ɹ�
}
//����2�ζ�ȡ������IC,�������ε�ƫ��ܳ���
//ERR_RANGE,��������,����Ϊ������ȷ,�����������.	   
//�ú����ܴ�����׼ȷ��
//x,y:��ȡ��������ֵ
//����ֵ:0,ʧ��;1,�ɹ���
#define ERR_RANGE 50 //��Χ 
u8 TP_Read_XY2(u16 *x,u16 *y) 
{
	u16 x1,y1;
 	u16 x2,y2;
 	u8 flag;    
    flag=TP_Read_XY(&x1,&y1);   
    if(flag==0)return(0);
    flag=TP_Read_XY(&x2,&y2);	   
    if(flag==0)return(0);   
    if(((x2<=x1&&x1<x2+ERR_RANGE)||(x1<=x2&&x2<x1+ERR_RANGE))//ǰ�����β�����+-50��
    &&((y2<=y1&&y1<y2+ERR_RANGE)||(y1<=y2&&y2<y1+ERR_RANGE)))
    {
        *x=(x1+x2)/2;
        *y=(y1+y2)/2;
        return 1;
    }else return 0;	  
}   
//////////////////////////////////////////////////////////////////////////////////		  
//��LCD�����йصĺ���  
//��һ��������
//����У׼�õ�
//x,y:����
//bcolor:����ɫ
//pcolor:��ɫ
void TP_Drow_Touch_Point(u16 x,u16 y,u16 bcolor,u16 pcolor)
{
	LCD_DrawLine(x-12,y,x+13,y,1,pcolor);//����
	LCD_DrawLine(x,y-12,x,y+13,1,pcolor);//����
	LCD_DrawPoint(x+1,y+1,pcolor);
	LCD_DrawPoint(x-1,y+1,pcolor);
	LCD_DrawPoint(x+1,y-1,pcolor);
	LCD_DrawPoint(x-1,y-1,pcolor);
	LCD_Draw_Circle(x,y,6,1,bcolor,pcolor);//������Ȧ
}	  
//��һ�����(2*2�ĵ�)		   
//x,y:����
//color:��ɫ
void TP_Draw_Big_Point(u16 x,u16 y,u16 color)
{	    
	POINT_COLOR=color;
	LCD_DrawPoint(x,y,color);//���ĵ� 
	LCD_DrawPoint(x+1,y,color);
	LCD_DrawPoint(x,y+1,color);
	LCD_DrawPoint(x+1,y+1,color);	 	  	
}							  
//////////////////////////////////////////////////////////////////////////////////		  
//��������ɨ��
//tp:0,��Ļ����(��������);1,�߼�����(У׼�����ⳡ����)
//����ֵ:��ǰ����״̬.
//0,�����޴���;1,�����д���
u8 TP_Scan(u8 tp)
{			   
	if(PEN==0)//�а�������
	{
		if(tp)TP_Read_XY2(&tp_dev.x[0],&tp_dev.y[0]);//��ȡ��������
		else if(TP_Read_XY2(&tp_dev.x[0],&tp_dev.y[0]))//��ȡ��Ļ����
		{
			tp_dev.x[0] = (float)((long)tp_dev.x[0]-(long)tp_dev.XLC)/tp_dev.KX+tp_dev.XC;//�����ת��Ϊ��Ļ����
			tp_dev.y[0] = (float)((long)tp_dev.y[0]-(long)tp_dev.YLC)/tp_dev.KY+tp_dev.YC;
	 	} 
		if((tp_dev.sta&TP_PRES_DOWN)==0)//֮ǰû�б�����
		{		 
			tp_dev.sta=TP_PRES_DOWN|TP_CATH_PRES;//��������  
			tp_dev.x[4]=tp_dev.x[0];//��¼��һ�ΰ���ʱ������
			tp_dev.y[4]=tp_dev.y[0];  	   			 
		}			   
	}else
	{
		if(tp_dev.sta&TP_PRES_DOWN)//֮ǰ�Ǳ����µ�
		{
			tp_dev.sta&=~(1<<7);//��ǰ����ɿ�	
		}else//֮ǰ��û�б�����
		{
			tp_dev.x[4]=0;
			tp_dev.y[4]=0;
			tp_dev.x[0]=0xffff;
			tp_dev.y[0]=0xffff;
		}	    
	}
	return tp_dev.sta&TP_PRES_DOWN;//���ص�ǰ�Ĵ���״̬
}  

//У��У׼����ֵ�Ƿ����Ҫ��
u8 CheckPoint(void)
{
	if(Adjustd_XYL[2][0] > Adjustd_XYL[1][0]\
		&&Adjustd_XYL[3][0] > Adjustd_XYL[4][0]\
		&&Adjustd_XYL[3][1] > Adjustd_XYL[2][1]\
		&&Adjustd_XYL[4][1] > Adjustd_XYL[1][1])//�ж��ĸ���������Ƿ�������λ��
	return 1;
	return 0;
}
//��������ֵ�ľ���ֵ
float subAbs(u32 a,u32 b)
{
	if(a>b)return (a-b);
	return (b-a);
}
//////////////////////////////////////////////////////////////////////////	 
//������flash����ĵ�ַ
#define ADJUSTDADDR  1024*1024*31+1024*512 					//31.5M
//����У׼����										    
void TP_Save_Adjdata(void)
{
	Adj_cfg.KX = tp_dev.KX; //xУ������ 
	Adj_cfg.KY = tp_dev.KY; //yУ������   
	Adj_cfg.XLC = tp_dev.XLC;//�е�x�߼�ֵ
	Adj_cfg.YLC = tp_dev.YLC;//�е�y�߼�ֵ
	Adj_cfg.touchtype = tp_dev.touchtype;//��������
	Adj_cfg.ENABLE = 0X0A;//���У׼����
	W25QXX_Write((u8*)&Adj_cfg,ADJUSTDADDR,sizeof(Adj_cfg));//У׼���ݱ��浽flash	 
}
//�õ�������EEPROM�����У׼ֵ
//����ֵ��1���ɹ���ȡ����
//        0����ȡʧ�ܣ�Ҫ����У׼
u8 TP_Get_Adjdata(void)
{					  
	W25QXX_Read((u8*)&Adj_cfg,ADJUSTDADDR,sizeof(Adj_cfg));//��flash�ж�ȡУ׼����		 
	if(Adj_cfg.ENABLE==0X0A)//�������Ѿ�У׼����			   
	{    			
		tp_dev.KX = Adj_cfg.KX;//�õ�xУ׼����
		tp_dev.KY = Adj_cfg.KY;//�õ�yУ׼����
		tp_dev.XLC = Adj_cfg.XLC;//�õ��е�x�߼�ֵ
		tp_dev.YLC = Adj_cfg.YLC;//�õ��е�y�߼�ֵ
		tp_dev.touchtype = Adj_cfg.touchtype;//��ȡ�������ͱ��
		tp_dev.XC = Adjustd_XY[0][0];//�е���������
		tp_dev.YC = Adjustd_XY[0][1];		 
		return 1;	 
	}
	return 0;
}	 
//��ʾ�ַ���
char* const TP_REMIND_MSG_TBL="��ʹ����д�ʵ����Ļ�ϵ�ʮ�֣�ֱ����Ļ�������";
 					  	 
//������У׼����
//�õ��ĸ�У׼����
void TP_Adjust(void)
{								 
	u8  cnt=0;	
	u32 S1L,S2L,S3L,S4L;
	u16 S1,S2;//,S3,S4;	
	u16 outtime=0;
 	cnt=0;				
	LCD_Clear(WHITE);//����   	   
	Show_Str(40,50,(u8*)TP_REMIND_MSG_TBL,24,0,WHITE,BLACK);//��ʾ��ʾ��Ϣ
	TP_Drow_Touch_Point(Adjustd_XY[0][0],Adjustd_XY[0][1],WHITE,RED);//����0 
	tp_dev.sta=0;//���������ź� 
	while(1)//�������10����û�а���,���Զ��˳�
	{
		tp_dev.scan(1);//ɨ����������
		if((tp_dev.sta&0xc0)==TP_CATH_PRES)//����������һ��(��ʱ�����ɿ���.)
		{	
			outtime=0;		
			tp_dev.sta&=~(1<<6);//��ǰ����Ѿ����������.
						   			   
			Adjustd_XYL[cnt][0]=tp_dev.x[0];
			Adjustd_XYL[cnt][1]=tp_dev.y[0];
			cnt++;	  
			switch(cnt)
			{			
				case 1:						 
					TP_Drow_Touch_Point(Adjustd_XY[0][0],Adjustd_XY[0][1],WHITE,WHITE);				//�����0 
					TP_Drow_Touch_Point(Adjustd_XY[1][0],Adjustd_XY[1][1],WHITE,RED);	//����1
					break;
				case 2:						 
					TP_Drow_Touch_Point(Adjustd_XY[1][0],Adjustd_XY[1][1],WHITE,WHITE);				//�����1 
					TP_Drow_Touch_Point(Adjustd_XY[2][0],Adjustd_XY[2][1],WHITE,RED);	//����2
					break;
				case 3:
 					TP_Drow_Touch_Point(Adjustd_XY[2][0],Adjustd_XY[2][1],WHITE,WHITE);	//�����2
					TP_Drow_Touch_Point(Adjustd_XY[3][0],Adjustd_XY[3][1],WHITE,RED);	//����3
					break;
				case 4:
 					TP_Drow_Touch_Point(Adjustd_XY[3][0],Adjustd_XY[3][1],WHITE,WHITE);			//�����3
 					TP_Drow_Touch_Point(Adjustd_XY[4][0],Adjustd_XY[4][1],WHITE,RED);	//����4
					break;
				case 5:	 //ȫ��5�����Ѿ��õ�
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
							LCD_Clear(WHITE);//����
							LCD_SystemString(35,110,"Touch Screen Adjust OK!",16,WHITE,BLUE);//У�����
							delay_ms(1000);
							TP_Save_Adjdata();  
							LCD_Clear(BACK_COLOR);//����   
							return;//У�����		
						}
						else
						{
							cnt=0;
							TP_Drow_Touch_Point(Adjustd_XY[4][0],Adjustd_XY[4][1],WHITE,WHITE);			//�����4
							TP_Drow_Touch_Point(Adjustd_XY[0][0],Adjustd_XY[0][1],WHITE,RED);	//����0
						}
					}
					else 
					{
						cnt=0;
						TP_Drow_Touch_Point(Adjustd_XY[4][0],Adjustd_XY[4][1],WHITE,WHITE);			//�����4
						TP_Drow_Touch_Point(Adjustd_XY[0][0],Adjustd_XY[0][1],WHITE,RED);	//����0
					}
			}
		}
		delay_ms(10);
		outtime++;
		if(outtime>1000)
		{
			TP_Get_Adjdata();
			LCD_Clear(BACK_COLOR);//����   
			break;
	 	} 
 	}
}
//��������ʼ��  		    
//����ֵ:0,û�н���У׼
//       1,���й�У׼
u8 TP_Init(void)
{	
   GPIO_InitTypeDef GPIO_Initure;
	if(GT911_Init()==0)//GT911��ʼ���ɹ���˵��ʹ�õĵ�����
	{
		tp_dev.scan=GT911_Scan;		//ɨ�躯��ָ��GT911������ɨ��		
		tp_dev.touchtype|=0X80;			//������ 
		tp_dev.touchtype|=lcddev.dir&0X01;//������������ 
	}else //������
	{
        
		__HAL_RCC_GPIOA_CLK_ENABLE();			//����GPIOAʱ��
		__HAL_RCC_GPIOH_CLK_ENABLE();			//����GPIOHʱ��
		__HAL_RCC_GPIOI_CLK_ENABLE();			//����GPIOIʱ��
		__HAL_RCC_GPIOG_CLK_ENABLE();			//����GPIOGʱ��
		
		GPIO_Initure.Pin=GPIO_PIN_0;            //PA0      //�ֶ�У׼��ť
    GPIO_Initure.Mode=GPIO_MODE_INPUT;      //����
    GPIO_Initure.Pull=GPIO_PULLDOWN;        //����
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;     //����
    HAL_GPIO_Init(GPIOA,&GPIO_Initure);
        
		//PH6
		GPIO_Initure.Pin=GPIO_PIN_6;            //PH6
		GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;  //�������
		GPIO_Initure.Pull=GPIO_PULLUP;          //����
		GPIO_Initure.Speed=GPIO_SPEED_HIGH;     //����
		HAL_GPIO_Init(GPIOH,&GPIO_Initure);     //��ʼ��
        
		//PI3,8
		GPIO_Initure.Pin=GPIO_PIN_3|GPIO_PIN_8; //PI3,8
		HAL_GPIO_Init(GPIOI,&GPIO_Initure);     //��ʼ��
        
		//PH7
		GPIO_Initure.Pin=GPIO_PIN_7;            //PH7
		GPIO_Initure.Mode=GPIO_MODE_INPUT;      //����
		HAL_GPIO_Init(GPIOH,&GPIO_Initure);     //��ʼ��
        
		//PG3
		GPIO_Initure.Pin=GPIO_PIN_3;            //PG3
		HAL_GPIO_Init(GPIOG,&GPIO_Initure);     //��ʼ��
		TP_Read_XY(&tp_dev.x[0],&tp_dev.y[0]);//��һ�ζ�ȡ��ʼ��	 
//		while(1)
//		{
//			tp_dev.scan(1);//ɨ����������
//			LCD_ShowNum(0,100,tp_dev.x[0],5,24,0x80,BACK_COLOR,POINT_COLOR);
//			LCD_ShowNum(0,130,tp_dev.y[0],5,24,0x80,BACK_COLOR,POINT_COLOR);			   			   
//		}
        
		
		if((TP_Get_Adjdata()==0)||(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_0)==GPIO_PIN_SET))//δУ׼���ֶ���ΪУ׼
		{ 										    
			LCD_Clear(WHITE);//����
			TP_Adjust();  	//��ĻУ׼  
		}	
		else return 0;				
	}
	return 1; 									 
}









