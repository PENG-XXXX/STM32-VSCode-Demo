/*******************************************************
 Copyright (C), XXX Co.,Ltd.
 File name:			app_task_test.c
 Author: PENG		Version: V1.0		Date:2026/01/12
 Description:
 Function List:
 History:
*******************************************************/
#include "app_task.h"
#include "bsp_adc.h"
#include "bsp_led.h"
#include "bsp_usart.h"

#include "iwdg.h"
#include <stdio.h>
#include <string.h>

/*******************************************************
 Author: PENG		Version: V1.0		Date:2025/06/26
 Function:			Task_Test
 Description:
 Calls:
 Called By:
 Input:
 Output:
 Return:
 Others:
*******************************************************/
void Task_Test(void)
{
#ifdef DEBUG
	short temp;						// 内部温度
    static char TaskInfo[512]={0};	// 任务状态统计信息字符串
#endif

    App_Printf("Ver: %d.%d.%d\r\n", VER_X, VER_Y, VER_Z);

	while(1)
	{
#ifdef DEBUG
        /* 获取任务状态统计信息 */
        memset(TaskInfo, 0, sizeof(TaskInfo));
        vTaskList(TaskInfo);
        App_Printf("-----------------Task List---------------\r\n");
        App_Printf("Task\t\tState\tPrio\tStack\tNum\r\n");
        App_Printf("%s\r\n", TaskInfo);
        App_Printf("B:Blocked R:Ready X:Running S:Suspended D:Deleted\r\n");

        /* 获取任务运行时间统计信息 */
        memset(TaskInfo, 0, sizeof(TaskInfo));
        vTaskGetRunTimeStats(TaskInfo);
        App_Printf("--------------CPU Percentage-------------\r\n");
        App_Printf("Task\t\tRunTime\tPercent\r\n");
        App_Printf("%s\r\n", TaskInfo);
        App_Printf("-----------------------------------------\r\n");

		/* 芯片内部温度 */
        temp = Get_TempInter_Data();
		App_Printf("Temp: %02d.%2d\r\n", temp/100, temp%100);
        App_Printf("-----------------------------------------\r\n");
#endif

        HAL_IWDG_Refresh(&hiwdg);	// 喂狗

		LED0_TOGGLE();
		osDelay(1000);
	}
}
