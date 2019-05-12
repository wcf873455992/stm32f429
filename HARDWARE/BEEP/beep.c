#include "beep.h"


//BEEP初始化
void BEEP_Init(void)
{
    GPIO_InitTypeDef GPIO_Initure;
    __HAL_RCC_GPIOA_CLK_ENABLE();           //开启GPIOA时钟
	
    GPIO_Initure.Pin=GPIO_PIN_6; //PA.6
    GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;  //推挽输出
    GPIO_Initure.Pull=GPIO_PULLUP;          //上拉
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;     //高速
    HAL_GPIO_Init(GPIOA,&GPIO_Initure);
	
    HAL_GPIO_WritePin(GPIOA,GPIO_PIN_6,GPIO_PIN_RESET);	
	
		BEEP_ON();
		delay_ms(300);
		BEEP_OFF();
}
