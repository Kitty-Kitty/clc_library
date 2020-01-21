/*******************************************************************************
*
*Copyright:novigo
*
*File name: cp_hi3531_dev_printf.h
*
*Author:fangzhenmu@novigo.com.cn
*
*Version: 1.0
*
*Date:2017/07/28
*
*Description: create (cp_hi3531_dev_printf.h)
*
*Others:
*
*History:
*******************************************************************************/

#ifndef _CP_HI3531_DEV_PRINTF_H_
#define _CP_HI3531_DEV_PRINTF_H_




#include "cp_hi3531_dev_system.h"




//这里重新包装了打印信息的格式
#define	 cp_hi3531_dev_log(level, hi3531_dev, format, ...)											\
	do {																							\
			cp_module_log(level, (hi3531_dev), "hi3531[%s] " format,								\
				get_hi3531_version_info((hi3531_dev)->manager),										\
				##__VA_ARGS__)																		\
	;} while (0)																					\




#endif //_CP_HI3531_DEV_PRINTF_H_


