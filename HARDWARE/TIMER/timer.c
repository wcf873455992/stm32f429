#include "timer.h"
#include "led.h"

////////////////////////////////////////////////////////////////////////////////// 	
//修改说明
//V1.1 20160106
//新增TIM3_PWM_Init函数,用于PWM输出
////////////////////////////////////////////////////////////////////////////////// 	 

TIM_HandleTypeDef TIM3_Handler;         //定时器3PWM句柄 
TIM_OC_InitTypeDef TIM3_CH4Handler;	    //定时器3通道4句柄
TIM_OC_InitTypeDef TIM3_CH3Handler;	    //定时器3通道3句柄

//通用定时器3中断初始化
//arr：自动重装值。
//psc：时钟预分频数
//定时器溢出时间计算方法:Tout=((arr+1)*(psc+1))/Ft us.
//Ft=定时器工作频率,单位:Mhz
//这里使用的是定时器3!(定时器3挂在APB1上，时钟为HCLK/2)
void TIM3_Init(u16 arr,u16 psc)
{  
    TIM3_Handler.Instance=TIM3;                          //通用定时器3
    TIM3_Handler.Init.Prescaler=psc;                     //分频
    TIM3_Handler.Init.CounterMode=TIM_COUNTERMODE_UP;    //向上计数器
    TIM3_Handler.Init.Period=arr;                        //自动装载值
    TIM3_Handler.Init.ClockDivision=TIM_CLOCKDIVISION_DIV1;
    HAL_TIM_Base_Init(&TIM3_Handler);
    
    HAL_TIM_Base_Start_IT(&TIM3_Handler); //使能定时器3和定时器3中断   
}

//TIM3 PWM部分初始化 
//PWM输出初始化
//arr：自动重装值
//psc：时钟预分频数
void TIM3_PWM_Init(u16 arr,u16 psc)
{ 
    TIM3_Handler.Instance=TIM3;            //定时器3
    TIM3_Handler.Init.Prescaler=psc;       //定时器分频
    TIM3_Handler.Init.CounterMode=TIM_COUNTERMODE_UP;//向上计数模式
    TIM3_Handler.Init.Period=arr;          //自动重装载值
    TIM3_Handler.Init.ClockDivision=TIM_CLOCKDIVISION_DIV1;
    HAL_TIM_PWM_Init(&TIM3_Handler);       //初始化PWM
    
    TIM3_CH3Handler.OCMode=TIM_OCMODE_PWM1; //模式选择PWM1
    TIM3_CH3Handler.Pulse=arr/2;            //设置比较值,此值用来确定占空比，
                                            //默认比较值为自动重装载值的一半,即占空比为50%
    TIM3_CH3Handler.OCPolarity=TIM_OCPOLARITY_LOW; //输出比较极性为低 
    HAL_TIM_PWM_ConfigChannel(&TIM3_Handler,&TIM3_CH3Handler,TIM_CHANNEL_3);//配置TIM3通道3
    HAL_TIM_PWM_Start(&TIM3_Handler,TIM_CHANNEL_3);//开启PWM通道3
}

//定时器底册驱动，开启时钟，设置中断优先级
//此函数会被HAL_TIM_Base_Init()函数调用
void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htim)
{
    __HAL_RCC_TIM3_CLK_ENABLE();            //使能TIM3时钟
    HAL_NVIC_SetPriority(TIM3_IRQn,1,3);    //设置中断优先级，抢占优先级1，子优先级3
    HAL_NVIC_EnableIRQ(TIM3_IRQn);          //开启ITM3中断   
}

//定时器底层驱动，时钟使能，引脚配置
//此函数会被HAL_TIM_PWM_Init()调用
//htim:定时器句柄
void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef *htim)
{
    GPIO_InitTypeDef GPIO_Initure;
	__HAL_RCC_TIM3_CLK_ENABLE();			//使能定时器3
    __HAL_RCC_GPIOB_CLK_ENABLE();			//开启GPIOB时钟
	
    GPIO_Initure.Pin=GPIO_PIN_0;           	//PB0
    GPIO_Initure.Mode=GPIO_MODE_AF_PP;  	//复用推完输出
    GPIO_Initure.Pull=GPIO_PULLUP;          //上拉
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;     //高速
	GPIO_Initure.Alternate= GPIO_AF2_TIM3;	//PB1复用为TIM3_CH4
    HAL_GPIO_Init(GPIOB,&GPIO_Initure);
}

//定时器3中断服务函数
void TIM3_IRQHandler(void)
{
    HAL_TIM_IRQHandler(&TIM3_Handler);
}

//定时器3中断服务函数调用
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if(htim==(&TIM3_Handler))
    {
        LED1=!LED1;        //LED1反转
    }
}

//设置TIM通道4的占空比
//TIM_TypeDef:定时器
//compare:比较值
void TIM_SetCompare4(TIM_TypeDef *TIMx,u32 compare)
{
	TIMx->CCR4=compare;
}

//设置TIM通道3的占空比
//TIM_TypeDef:定时器
//compare:比较值
void TIM_SetCompare3(TIM_TypeDef *TIMx,u32 compare)
{
	TIMx->CCR3=compare;
}
