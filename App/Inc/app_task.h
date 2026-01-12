/*******************************************************
 Copyright (C), XXX Co.,Ltd.
 File name:			app_task.h
 Author: PENG		Version: V1.0		Date:2026/01/12
 Description:    	线程配置头文件
 Function List:
 History:
*******************************************************/

#ifndef APP_TASK_H_
#define APP_TASK_H_

#include "main.h"
#include "cmsis_os.h"
//#include "bsp_delay.h"
//#include "bsp_usart.h"


/* 软件版本 */
#define	VER_X	1
#define	VER_Y	0
#define	VER_Z	0

/**********************
 * 串口通信数据包格式:      *
 * 包头标准位1		1个字节 *
 * 包头标志位2		1个字节 *
 * 数据发起方		1个字节 *
 * 数据接收方		1个字节 *
 * 帧序列号(自增1)	2个字节 *
 * 命令版本		1个字节 *
 * 命令			1个字节 *
 * 包头校验码		1个字节 *
 * 数据主体长度		2个字节 *
 * 数据主体		n个字节 *
 * 数据校验码		1个字节 *
 * 包尾标志位1		1个字节 *
 * 包尾标志位2		1个字节 *
***********************/

/* 串口通信数据包 */
#define	COM_HEAD1		0x80			/* 包头标志位1 */
#define	COM_HEAD2		0x81			/* 包头标志位2 */
#define	COM_EMD			0x00			/* 主机端 */
#define DEVICE_1		0x01			/* 设备端(器械臂1) */
#define DEVICE_2		0x02			/* 设备端(器械臂2) */
#define DEVICE_3		0x03			/* 设备端(器械臂3) */
#define DEVICE_4		0x04			/* 设备端(器械臂4) */
#define BROAD			0x10			/* 广播 */
#define	COM_END1		0x81			/* 包尾标志位1 */
#define	COM_END2		0x82			/* 包尾标志位2 */

/* 命令解析结果 */
#define COM_OK			0x00			/* 命令解析成功 */
#define COM_ERR			0x01			/* 命令解析失败 */

#define	HEAD_LEN		9				/* 包头长度 数据主体长度前 */
#define	END_LEN			3				/* 包尾长度 数据主体后 */

#define CMDV1_SETDEVICE	0x41	        /* A 设置设备(器械臂)ID命令 */
#define CMDV1_CONNECT	0x42	        /* B 获取器械连接状态 */
#define CMDV1_READ		0x43	        /* C 读取器械ID和使用次数 */
#define CMDV1_WRITE		0x44	        /* D 写入器械ID和使用次数 */


typedef struct
{
    uint16_t   	cmdv;					/* 命令 含版本 */
    uint16_t  	requ_no;				/* 请求序列号 */
    uint16_t  	datalen;				/* 数据主体长度 */
    uint8_t   	*data;					/* 数据主体指针 */
}rxdata_t;	/* 解析后的数据结构体 */

typedef struct
{
    uint16_t    datalen;				/* 待发送的数据长度 */
    uint8_t     *data;					/* 待发送的数据指针 */
}txdata_t;	/* 待发送的数据结构体 */


void Task_Test(void);
// void Task_EEPROM(void);
// void Task_COM(void);

#endif /* APP_TASK_H_ */
