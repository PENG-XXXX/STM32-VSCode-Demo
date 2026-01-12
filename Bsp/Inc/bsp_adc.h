/*******************************************************
 Copyright (C), XXX Co.,Ltd.
 File name:			bsp_adc.h
 Author: PENG		Version: V1.0		Date:2025/06/26
 Description:    	ADC配置头文件
 Function List:
 History:
*******************************************************/

#ifndef INC_BSP_ADC_H_
#define INC_BSP_ADC_H_

#include "adc.h"

#define CH_TEMP ADC_CHANNEL_TEMPSENSOR	    /* 内部温度通道 */
#define TS_CAL1_ADDR   0x1FFFF7B8			/* 温度传感器在30℃时的校准值，固定保存在芯片内部 */
#define TS_CAL2_ADDR   0x1FFFF7C2			/* 温度传感器在110℃时的校准值，固定保存在芯片内部 */


short Get_TempInter_Data(void);		/* 获取芯片内部温度 */


#endif /* INC_BSP_ADC_H_ */
