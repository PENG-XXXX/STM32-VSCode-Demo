/*******************************************************
 Copyright (C), XXX Co.,Ltd.
 File name:			bsp_delay.h
 Author: PENG		Version: V1.0		Date:2025/04/11
 Description:    	延时函数配置头文件

 Function List:
 History:
*******************************************************/

#ifndef INC_BSP_DELAY_H_
#define INC_BSP_DELAY_H_

#include "main.h"


#define SYSCLK 72	/* System Clock MHz */

void delay_us(uint32_t nus);
void delay_ms(uint16_t nms);

#endif /* INC_BSP_DELAY_H_ */
