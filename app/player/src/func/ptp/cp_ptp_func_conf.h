/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-12-20

Description:

**************************************************************************/

#ifndef _CP_PTP_FUNC_CONF_INCLUDE_H_
#define _CP_PTP_FUNC_CONF_INCLUDE_H_


#include "cp_core.h"
#include "cp_module_core.h"
#include "cp_ptp_func_conf_string.h"



#define		CP_PTP_FUNC_IP_ADDRESS_LENGTH				16
#define		CP_PTP_DEFAULT_BUFFER_LENGTH				256


typedef struct cp_ptp_func_configure_s					cp_ptp_func_configure_t;



#pragma pack(1)

/************************************************************************/
/* 音频处理相关配置                                                      */
/************************************************************************/
struct cp_ptp_func_configure_s
{
	cp_char_t						address[CP_PTP_FUNC_IP_ADDRESS_LENGTH];			//表示ptp组播地址
	cp_char_t						debug_path[CP_PTP_DEFAULT_BUFFER_LENGTH];		//表示ptp 调试信息保存位置
	cp_int32_t						port;											//表示ptp组播端口
	cp_bool_t						is_debug;										//表示是否调试
	cp_bool_t						is_use;
};

#pragma pack()


/************************************************************************/
/*解析配置文件                                                           */
/************************************************************************/
cp_int32_t	ptp_func_parse_configure(cp_module_t *module, cp_ptp_func_configure_t *fc);


#endif