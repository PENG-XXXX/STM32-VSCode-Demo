/*******************************************************
 Copyright (C), XXX Co.,Ltd.
 File name:			bsp_adc.c
 Author: PENG		Version: V1.0		Date:2025/06/26
 Description:    	ADC配置文件
 Function List:
 History:
*******************************************************/

#include "bsp_adc.h"
#include "bsp_delay.h"
#include <stdio.h>


/*******************************************************
 Author: PENG		Version: V1.0		Date:2025/06/26
 Function:			Get_ADC1CH_Val
 Description:		获取AD值
 Calls:
 Called By:
 Input:				无
 Output:			无
 Return:			ad_data AD值
 Others:			无
*******************************************************/
int Get_ADC1CH_Val(uint32_t ch)
{
	int ad_data;

	/* 通道配置 */
    ADC_ChannelConfTypeDef adc_ch_conf;
    adc_ch_conf.Channel = ch;								/* 通道 */
    adc_ch_conf.Rank = ADC_REGULAR_RANK_1;					/* 序列 */
	adc_ch_conf.SamplingTime = ADC_SAMPLETIME_239CYCLES_5;	    /* 采样时间 */
    HAL_ADC_ConfigChannel(&hadc1, &adc_ch_conf);

	HAL_ADC_Start(&hadc1);					/* 启动ADC转换 */
	HAL_ADC_PollForConversion(&hadc1, 10);	/* 轮询转换 等待转换完成 */
	ad_data = HAL_ADC_GetValue(&hadc1);		/* 读取转换结果 */
	HAL_ADC_Stop(&hadc1);					/* 停止ADC转换 */

	return ad_data;
}

/*******************************************************
 Author: PENG		Version: V1.0		Date:2025/06/26
 Function:			Get_ADC1CH_Val_AVG
 Description:		获取AD值  取10次平均值
 Calls:
 Called By:
 Input:				无
 Output:			无
 Return:			ad_avg AD值
 Others:			无
*******************************************************/
uint16_t Get_ADC1CH_Val_AVG(uint32_t ch)
{
	uint8_t i, j;
	uint16_t ad_data[15];
	uint32_t ad_sum = 0;
	uint16_t ad_avg = 0;
	uint16_t ad_temp;

	/* 获取AD值 */
	for(i=0; i<15; i++)
	{
		ad_data[i] = Get_ADC1CH_Val(ch);
		delay_us(10);
	}

	/* AD值排序 */
	for(i=0; i<15; i++)
	{
		for(j=i+1; j<15; j++)
		{
			if(ad_data[j] < ad_data[i])
			{
				ad_temp = ad_data[i];
				ad_data[i] = ad_data[j];
				ad_data[j] = ad_temp;
			}
		}
	}

	/* 取10次平均 */
	for(i=3; i<13; i++)
	{
		ad_sum = ad_sum + ad_data[i];
	}
	ad_avg = ad_sum/10;

	if(ad_avg > 65535)
	{
		//printf("Get_ADC1CH_Val_AVG Error: ch=%d ad=%d\r\n", ch, ad_avg);
		return 0;
	}
	else if(ad_avg <= 0)
	{
		//printf("Get_ADC1CH_Val_AVG Error: ch=%d ad=%d\r\n", ch, ad_avg);
		return 0;
	}

	//printf("Get_ADC1CH_Val_AVG  ch=%d ad=%d\r\n", ch, ad_avg);
	return ad_avg;
}

/*******************************************************
 Author: PENG		Version: V1.0		Date:2023/9/2
 Function:			Get_TempInter_Data
 Description:		获取内部温度值
 Calls:
 Called By:
 Input:				无
 Output:			无
 Return:			temp 温度值值
 Others:			无
*******************************************************/
short Get_TempInter_Data(void)
{
	uint16_t ts_cal1, ts_cal2;
	uint16_t ts_data;
	float k;
	float temp;

	ts_cal1 = *(volatile uint16_t*)TS_CAL1_ADDR;	/* 温度传感器在30℃时的校准值，固定保存在芯片内部 */
	ts_cal2 = *(volatile uint16_t*)TS_CAL2_ADDR;	/* 温度传感器在130℃时的校准值，固定保存在芯片内部 */
	k = (float)(130.0-30.0)/(ts_cal2-ts_cal1);		/* 计算比例系数 */
	ts_data = Get_ADC1CH_Val_AVG(CH_TEMP);
	ts_data = ts_data *3.3/3;
	temp = (float)(k*(ts_data - ts_cal1) + 30);		/* 温度值计算 */

	return (short)(temp*100);						/* 温度值放大100倍 */
}



