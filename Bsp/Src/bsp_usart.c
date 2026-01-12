/*******************************************************
 Copyright (C), Hangzhou Jianjia Robot Co.,Ltd.
 File name:			bsp_usart.c
 Author: PENG		Version: V1.0		Date:2025/06/26
 Description:    	串口配置文件
 	 	 	 	 	对驱动层进行重新封装
 Function List:
 History:
*******************************************************/

#include "bsp_usart.h"
//#include "usart.h"
//#include "dma.h"
#include <stdarg.h>
#include <stdio.h>
#include "cmsis_os.h"

/*******************************************************
 Author: PENG		Version: V1.0		Date:2025/06/26
 Function:			__io_putchar
 Description:		重映射printf函数
 Calls:				HAL_UART_Transmit
 Called By:
 Input:				ch
 Output:			无
 Return:			ch
 Others:			无
*******************************************************/
#ifdef __GNUC__
int __io_putchar(int ch)
{
    HAL_UART_Transmit(&uart_p, (uint8_t *)&ch, 1, 0x200);
    return ch;
}
#else
int fputc(int ch, FILE *f)
{
    HAL_UART_Transmit(&uart_p, (uint8_t *)&ch, 1, 0x200);
    return ch;
}
#endif

/*******************************************************
 Author: PENG		Version: V1.0		Date:2025/06/26
 Function:			App_Printf
 Description:		线程安全的printf函数
 	 	 	 	 	当无法列出传递函数的所有实参的类型和数目时,可以用省略号指定参数表
 Calls:				printf
 Called By:
 Input:				同printf的参数
 Output:			无
 Return:			无
 Others:			无
*******************************************************/
void App_Printf(const char *fmt, ...)
{
	char buf_str[1024];		/* printf发送缓存 */
	va_list v_args;

	vTaskSuspendAll();		/* 禁止线程调度，防止打断printf */

	va_start(v_args, fmt);
	(void)vsnprintf((char *)&buf_str[0],
					(size_t)sizeof(buf_str),
					(char const *)fmt,
					v_args);
	va_end(v_args);

	printf("%s", buf_str);

	xTaskResumeAll();		/* 恢复线程调度 */
}

/*******************************************************
 Author: PENG		Version: V1.0		Date:2025/06/26
 Function:			Usart_Send_Data
 Description:		串口发送
 Calls:				HAL_UART_Transmit
 Called By:
 Input:				data 待发送的数据帧/数组
 	 	 	 	 	size 长度
 Output:			无
 Return:			无
 Others:			无
*******************************************************/
void Usart_Send_Data(uint8_t *data, uint32_t size)
{
    HAL_UART_Transmit_DMA(&huart2, data, size);
	//HAL_UART_Transmit(&huart2, data, size, 0x200);
}



