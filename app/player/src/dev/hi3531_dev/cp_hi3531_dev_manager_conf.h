/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-12-20

Description:

**************************************************************************/

#ifndef _CP_HI3531_DEV_MANAGER_CONF_INCLUDE_H_
#define _CP_HI3531_DEV_MANAGER_CONF_INCLUDE_H_


#include "cp_core.h"
#include "cp_module_core.h"
#include "cp_hi3531_dev_manager_conf_string.h"




//定义配置数量
#define		CP_HI3531_DEV_VDEC_MEMORY_NAME_SIZE											16				//表示vdec内存名称长度
#define		CP_HI3531_DEV_VO_BACK_COLOR_STRING_SIZE										16				//表示vo背景色字节长宽
#define		CP_HI3531_DEV_VO_MEM_NAME_STRING_SIZE										16				//表示vo内存名称长度
#define		CP_HI3531_DEV_VO_DEVICE_SIZE												8				//表示vo设备的最大数量


typedef struct	cp_hi3531_dev_system_configure_s										cp_hi3531_dev_system_configure_t;
typedef struct	cp_hi3531_dev_vdec_configure_s											cp_hi3531_dev_vdec_configure_t;
typedef struct cp_hi3531_dev_vo_configure_s												cp_hi3531_dev_vo_configure_t;
typedef struct cp_hi3531_dev_hdmi_configure_s											cp_hi3531_dev_hdmi_configure_t;
typedef struct	cp_hi3531_dev_configure_s												cp_hi3531_dev_configure_t;



/************************************************************************/
/* hi3531系统相关配置                                                      */
/************************************************************************/
struct cp_hi3531_dev_system_configure_s
{
	cp_int32_t								max_pool_count;												//表示最大的内存池数量
	cp_int32_t								align_width;												//表示对齐宽度
};


/************************************************************************/
/* hi3531解码相关配置                                                      */
/************************************************************************/
struct cp_hi3531_dev_vdec_configure_s
{
	cp_int32_t								vdec_mpp_dev_id;											//表示模块设备号
	cp_int32_t								vdec_mpp_channel_number;									//表示模块设备通道使用内存DDR数量
	cp_char_t								vdec_mmz_name[CP_HI3531_DEV_VDEC_MEMORY_NAME_SIZE];			//表示内存所在DDR的名字
};


/************************************************************************/
/* hi3531vo相关配置                                                      */
/************************************************************************/
struct cp_hi3531_dev_vo_configure_s
{
	cp_int32_t								dev_id;														//表示设备编号,取值[0, 7]
	cp_int32_t								channel_id;													//表示通道编号,取值[0, 7]
	cp_int32_t								source_frame_rate;											//表示表示源帧率信息
	cp_int32_t								dest_frame_rate;											//表示表示目标帧率信息
	cp_int32_t								intf_type;													//接口类型,取值[0, 8]
	cp_int32_t								intf_sync;													//接口时序典型配置,取值[0, 24]
	cp_bool_t								enable_double_frame;										//是否需要倍帧,取值[0, 1]；0:表示不用使能；1:表示使能
	cp_bool_t								is_used;													//标记是否被使用
	cp_char_t								back_color[CP_HI3531_DEV_VO_BACK_COLOR_STRING_SIZE];		//表示背景色字节
	cp_char_t								mem_name[CP_HI3531_DEV_VO_MEM_NAME_STRING_SIZE];			//表示内存所在DDR的名字
};


/************************************************************************/
/* hi3531 hdmi 相关配置                                                  */
/************************************************************************/
struct cp_hi3531_dev_hdmi_configure_s
{
	cp_int32_t								dev_id;														//表示设备编号,取值[0, 7]
	cp_bool_t								enable_hdmi;												//是否强制HDMI输出,取值[0, 1]；0:表示不用HDMI，使用DVI；1:表示用HDMI
	cp_bool_t								enable_video;												//是否输出视频,取值[0, 1]；0:表示不用使能；1:表示使能
	cp_int32_t								video_out_mode;												//HDMI输出视频模式,取值[1, 2, 3]；1:表示VIDEO_MODE_YCBCR444; 2:表示VIDEO_MODE_YCBCR422; 3:表示VIDEO_MODE_RGB444
	cp_bool_t								enable_xvycc_mode;											//是否使能xvYCC输出模式,取值[0, 1]；0:表示不用使能；1:表示使能
	cp_bool_t								enable_audio;												//是否使能音频,取值[0, 1]；0:表示不用使能；1:表示使能
	cp_bool_t								enable_multi_channel;										//多声道还是立体声,取值[0, 1]；0:表示立体声；1:表示多声道,固定为8 声道
};


/************************************************************************/
/* 音频处理相关配置                                                      */
/************************************************************************/
struct cp_hi3531_dev_configure_s
{
	cp_hi3531_dev_system_configure_t		system_conf;											//表示系统配置项内容
	cp_hi3531_dev_vdec_configure_t			vdec_conf;												//表示hi3531 vdec配置信息
	cp_hi3531_dev_vo_configure_t			vo_conf[CP_HI3531_DEV_VO_DEVICE_SIZE];					//表示vo配置信息
	cp_hi3531_dev_hdmi_configure_t			hdmi_conf;												//表示hdmi配置信息
};


/************************************************************************/
/*解析配置文件                                                           */
/************************************************************************/
cp_int32_t	hi3531_dev_manager_parse_configure(const cp_module_manager_t *manager, cp_hi3531_dev_configure_t *hacc);

/************************************************************************/
/*解析system配置文件                                                     */
/************************************************************************/
cp_int32_t	hi3531_dev_manager_parse_system_configure(const cp_module_manager_t *manager, cp_hi3531_dev_configure_t *hacc);

/************************************************************************/
/*解析vdec配置文件                                                     */
/************************************************************************/
cp_int32_t	hi3531_dev_manager_parse_vdec_configure(const cp_module_manager_t *manager, cp_hi3531_dev_configure_t *hacc);

/************************************************************************/
/*解析vo配置文件                                                     */
/************************************************************************/
cp_int32_t	hi3531_dev_manager_parse_vo_configure(const cp_module_manager_t *manager, cp_hi3531_dev_configure_t *hacc);

/************************************************************************/
/*解析hdmi配置文件                                                     */
/************************************************************************/
cp_int32_t	hi3531_dev_manager_parse_hdmi_configure(const cp_module_manager_t *manager, cp_hi3531_dev_configure_t *hacc);

#endif