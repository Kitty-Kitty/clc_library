/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-12-20

Description:

**************************************************************************/

#ifndef _CP_HI3531_VO_CONF_INCLUDE_H_
#define _CP_HI3531_VO_CONF_INCLUDE_H_


#include "cp_core.h"
#include "cp_module_core.h"
#include "cp_hi3531_dev_include.h"
#include "cp_hi3531_vo_conf_string.h"



#define	CP_HI3531_VO_BACK_COLOR_STRING_SIZE							16									//表示vo背景色字节长宽



typedef struct	cp_hi3531_vo_channel_configure_s					cp_hi3531_vo_channel_configure_t;
typedef struct	cp_hi3531_vo_configure_s							cp_hi3531_vo_configure_t;



/************************************************************************/
/* 视频通道属性相关配置                                                  */
/************************************************************************/
struct cp_hi3531_vo_channel_configure_s
{
	cp_int32_t								id;															//表示通道编号,取值[0, 63]
	cp_bool_t								is_used;													//标记是否被使用
#if defined(CP_HI3531_DEV_MODE)
	VO_CHN_ATTR_S							attr;														//vo 通道属性
#endif
};


/************************************************************************/
/* 视频处理相关配置                                                      */
/************************************************************************/
struct cp_hi3531_vo_configure_s
{
	cp_int32_t								dev_id;														//表示设备编号,取值[0, 7]
	cp_int32_t								intf_type;													//接口类型,取值[0, 8]
	cp_int32_t								intf_sync;													//接口时序典型配置,取值[0, 24]
	cp_bool_t								enable_double_frame;										//是否需要倍帧,取值[0, 1]；0:表示不用使能；1:表示使能
	cp_bool_t								is_used;													//标记是否被使用
	cp_char_t								back_color[CP_HI3531_VO_BACK_COLOR_STRING_SIZE];			//表示内存所在DDR的名字
};



/************************************************************************/
/*解析配置文件                                                           */
/************************************************************************/
cp_int32_t	hi3531_vo_parse_configure(cp_module_t *module, cp_hi3531_vo_configure_t *hacc);

#endif