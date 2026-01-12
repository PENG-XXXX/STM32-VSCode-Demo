/*******************************************************
 Copyright (C), XXX Co.,Ltd.
 File name:			bsp_usart.h
 Author: PENG		Version: V1.0		Date:2025/04/11
 Description:    	串口配置头文件
 	 	 	 	 	对驱动层进行重新封装
 Function List:
 History:
*******************************************************/

#ifndef INC_BSP_USART_H_
#define INC_BSP_USART_H_

#include "main.h"
#include "usart.h"

/* printf对应串口 */
#define uart_p huart1


void App_Printf(const char *fmt, ...);
void Usart_Send_Data(uint8_t *data, uint32_t size);	/* 串口发送 */

#endif /* INC_BSP_USART_H_ */
