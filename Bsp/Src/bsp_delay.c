/*******************************************************
 Copyright (C), XXX Co.,Ltd.
 File name:			bsp_delay.c
 Author: PENG		Version: V1.0		Date:2025/04/12
 Description:    	延时函数

 Function List:
 History:
*******************************************************/

#include "bsp_delay.h"
//#include "cmsis_os.h"


/*******************************************************
 Author: PENG		Version: V1.0		Date:2025/04/11
 Function:			delay_us
 Description:		us级延时函数
					使用SysTick实现高精度延时
 Calls:
 Called By:
 Input:				nus 延时时间
 Output:			无
 Return:			无
 Others:			暂未考虑系统调度的影响
*******************************************************/
void delay_us(uint32_t nus)
{
    uint32_t ticks;
    uint32_t told, tnow , tcnt;
    uint32_t reload;

    //vTaskSuspendAll();		/* 禁止线程调度，防止打断us延时 */

    tcnt = 0;
    ticks = nus * SYSCLK;		/* 节拍数 延时时间*系统时钟频率 */
    reload = SysTick->LOAD;
    told = SysTick->VAL;		/* 初始计数器值 */

    while(1)
    {
        tnow = SysTick->VAL;	/* 当前节拍数 */
        if(tnow != told)
        {
            if(tnow < told)
            {
            	tcnt += told - tnow;
            }
            else
            {
            	tcnt += reload - tnow + told;
            }
            told = tnow;

            if(tcnt >= ticks)
            {
            	break;
            }
        }
    }

    //xTaskResumeAll();			/* 恢复线程调度 */
}

/*******************************************************
 Author: PENG		Version: V1.0		Date:2025/04/11
 Function:			delay_ms
 Description:		ms级延时函数
					非阻滞
 Calls:
 Called By:
 Input:				nms 延时时间
 Output:			无
 Return:			无
 Others:			暂未考虑系统调度的影响
*******************************************************/
void delay_ms(uint16_t nms)
{
    uint32_t i;
    for (i=0; i<nms; i++)
    {
        delay_us(1000);
    }
}

