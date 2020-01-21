/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/

#ifndef	_CP_PTP_FUNC_INCLUDE_H_
#define _CP_PTP_FUNC_INCLUDE_H_



#include "cp_ptp_func_core.h"



//typedef struct cp_ptp_func_s					cp_ptp_func_t;
typedef enum cp_ptp_func_thread_status_enum		cp_ptp_func_thread_status_e;



#pragma pack(1)


#define CP_PTP_FUNC_FIELDS																	\
		CP_FUNC_FIELDS																		\
		cp_codec_t								*codec;			/*解码器信息*/				\
		cp_dev_t								*dev;			/*播放设备信息*/				\
		cp_filter_t								*filter;		/*数据过滤器*/				\
		cp_ptp_func_configure_t					ptp_conf;		/*ptp配置信息*/				\


/************************************************************************/
/*                                                                      */
/************************************************************************/
struct cp_ptp_func_s {
	CP_PTP_FUNC_FIELDS											/*表示时间模块信息*/
		
	FILE										*file;			/*媒体文件*/						
};


enum cp_ptp_func_thread_status_enum
{
	cp_ptp_func_thread_status_init = 1,
	cp_ptp_func_thread_status_start,
	cp_ptp_func_thread_status_stop,
};


#pragma pack()


cp_ptp_func_t* create_ptp_func(cp_module_register_t *register_info, cp_socket_manager_t *manager, cp_ptp_func_info_t *info);
cp_int32_t destroy_ptp_func(cp_player_func_manager_t *manager, cp_ptp_func_t* ptp_func);


#endif


