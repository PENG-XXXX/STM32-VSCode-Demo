/*******************************************************
 Copyright (C), XXX Co.,Ltd.
 File name:			bsp_led.h
 Author: PENG		Version: V1.0		Date:2025/06/26
 Description:    	LED配置头文件

 Function List:
 History:
*******************************************************/

#ifndef INC_BSP_LED_H_
#define INC_BSP_LED_H_

#include "gpio.h"

/* LED控制*/
#define LED0(x)   		do{ x ? \
                      	  HAL_GPIO_WritePin(LED0_GPIO_Port, LED0_Pin, GPIO_PIN_SET): \
						  HAL_GPIO_WritePin(LED0_GPIO_Port, LED0_Pin, GPIO_PIN_RESET); \
                  	  	}while(0)

/* LED状态翻转 */
#define LED0_TOGGLE()   do{ \
							HAL_GPIO_TogglePin(LED0_GPIO_Port, LED0_Pin); \
						}while(0)


#endif /* INC_BSP_LED_H_ */
