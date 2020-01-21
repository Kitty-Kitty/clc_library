/*******************************************************************************
*
*Copyright:novigo
*
*File name: cp_hi3531_dev_conf.h
*
*Author:fangzhenmu@novigo.com.cn
*
*Version: 1.0
*
*Date:2017/08/17
*
*Description: create (cp_hi3531_dev_conf.h)
*
*Others:
*
*History:
*******************************************************************************/

#ifndef _CP_HI3531_DEV_CONF_H_
#define _CP_HI3531_DEV_CONF_H_



#include "cp_core.h"
#include "cp_module_core.h"
#include "cp_hi3531_dev_conf_string.h"


typedef struct cp_hi3531_dev_configure_s					cp_hi3531_dev_configure_t;



#pragma pack(1)

/************************************************************************/
/* hi3531相关配置                                                      */
/************************************************************************/
struct cp_hi3531_dev_configure_s
{
	cp_int32_t						each_buffer_length;								//表示当前使用的每个缓存大小
};

#pragma pack()




#endif //_CP_HI3531_DEV_CONF_H_


