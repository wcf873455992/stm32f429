#ifndef _BSP_BEEP_H
#define _BSP_BEEP_H
#include "sys.h"

#define BEEP_ON()  HAL_GPIO_WritePin(GPIOA,GPIO_PIN_6,GPIO_PIN_SET)
#define BEEP_OFF() HAL_GPIO_WritePin(GPIOA,GPIO_PIN_6,GPIO_PIN_RESET)


void BEEP_Init(void);


#endif
