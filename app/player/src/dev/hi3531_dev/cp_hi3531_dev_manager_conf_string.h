/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-12-20

Description:

**************************************************************************/

#ifndef _CP_HI3531_DEV_MANAGER_CONF_STRING_INCLUDE_H_
#define _CP_HI3531_DEV_MANAGER_CONF_STRING_INCLUDE_H_



#define CP_HI3531_DEV_MANAGER_CONF_STRING_HI3531_CONFIGURE						"hi3531_configure"							//表示hi3531配置项


#define CP_HI3531_DEV_MANAGER_CONF_STRING_HI3531_SYSTEM							"hi3531_system"								//表示hi3531系统内容
#define CP_HI3531_DEV_MANAGER_CONF_STRING_MAX_POOL_COUNT						"max_pool_count"							//表示最大的内存池数量
#define CP_HI3531_DEV_MANAGER_CONF_STRING_ALIGN_WIDTH							"align_width"								//表示对齐宽度


#define CP_HI3531_DEV_MANAGER_CONF_STRING_HI3531_DEV_VDEC						"hi3531_dev_vdec"							//表示hi3531 vdec配置信息
#define CP_HI3531_DEV_MANAGER_CONF_STRING_VDEC_MPP_DEV_ID						"vdec_mpp_dev_id"							//表示模块设备号
#define CP_HI3531_DEV_MANAGER_CONF_STRING_VDEC_MPP_CHANNEL_NUMBER				"vdec_mpp_channel_number"					//表示模块设备通道使用内存DDR数量
#define CP_HI3531_DEV_MANAGER_CONF_STRING_VDEC_MMZ_NAME							"vdec_mmz_name"								//表示内存所在DDR的名字


#define CP_HI3531_DEV_MANAGER_CONF_STRING_VDEC_VIDEO_ATTR						"vdec_video_attr"							//表示视频相关属性信息
#define CP_HI3531_DEV_MANAGER_CONF_STRING_VDEC_MAX_WIDTH						"vdec_max_width"							//表示最大支持分辨率宽度
#define CP_HI3531_DEV_MANAGER_CONF_STRING_VDEC_MAX_HEIGHT						"vdec_max_height"							//表示最大支持分辨率高度
#define CP_HI3531_DEV_MANAGER_CONF_STRING_VDEC_REF_FRAME_NUMBER					"vdec_ref_frame_number"						//表示参考帧的数目,取值范围[1, 16],以帧为单位
#define CP_HI3531_DEV_MANAGER_CONF_STRING_VDEC_STREAM_MODE						"vdec_stream_mode"							//表示码流发送方式, 0:表示Stream以流方式；1表示frame以帧为单位
#define CP_HI3531_DEV_MANAGER_CONF_STRING_VDEC_SUPPORT_BFRAME					"vdec_support_bframe"						//表示是否支持B帧解码, 取值范围[0, 1]


#define CP_HI3531_DEV_MANAGER_CONF_STRING_HI3531_VO								"hi3531_vo"									//配置的hi3531vo内容
#define CP_HI3531_DEV_MANAGER_CONF_STRING_HI3531_VO_ITEMS						"hi3531_vo_items"							//配置的hi3531vo内容
#define CP_HI3531_DEV_MANAGER_CONF_STRING_HI3531_VO_ITEM						"hi3531_vo_item"							//配置的hi3531vo内容
#define CP_HI3531_DEV_MANAGER_CONF_STRING_DEV_ID								"dev_id"									//表示模块设备号
#define CP_HI3531_DEV_MANAGER_CONF_STRING_CHANNEL_ID							"channel_id"								//表示模块通道号
#define CP_HI3531_DEV_MANAGER_CONF_STRING_SOURCE_FRAME_RATE						"source_frame_rate"							//表示源帧率信息
#define CP_HI3531_DEV_MANAGER_CONF_STRING_DEST_FRAME_RATE						"dest_frame_rate"							//表示目标帧率信息
#define CP_HI3531_DEV_MANAGER_CONF_STRING_BACK_COLOR							"back_color"								//表示设备背景色RGB888,格式:XXXXXX,例如:001122
#define CP_HI3531_DEV_MANAGER_CONF_STRING_MEM_NAME								"mem_name"									//表示内存所在DDR的名字
#define CP_HI3531_DEV_MANAGER_CONF_STRING_INTF_TYPE								"intf_type"									//表示接口类型,取值[0, 8]
#define CP_HI3531_DEV_MANAGER_CONF_STRING_INTF_SYNC								"intf_sync"									//表示接口时序典型配置,取值[0, 24]
#define CP_HI3531_DEV_MANAGER_CONF_STRING_ENABLE_DOUBLE_FRAME					"enable_double_frame"						//表示是否需要倍帧,取值[0, 1]；0:表示不用使能；1:表示使能


#define CP_HI3531_DEV_MANAGER_CONF_STRING_HI3531_HDMI							"hi3531_hdmi"								//表示HDMI相关属性信息
#define CP_HI3531_DEV_MANAGER_CONF_STRING_ENABLE_HDMI							"enable_hdmi"								//表示是否强制HDMI输出,取值[0, 1]；0:表示不用HDMI，使用DVI；1:表示用HDMI
#define CP_HI3531_DEV_MANAGER_CONF_STRING_ENABLE_VIDEO							"enable_video"								//表示是否输出视频,取值[0, 1]；0:表示不用使能；1:表示使能
#define CP_HI3531_DEV_MANAGER_CONF_STRING_VIDEO_OUT_MODE						"video_out_mode"							//表示HDMI输出视频模式,取值[1, 2, 3]；1:表示VIDEO_MODE_YCBCR444; 2:表示VIDEO_MODE_YCBCR422; 3:表示VIDEO_MODE_RGB444
#define CP_HI3531_DEV_MANAGER_CONF_STRING_ENABLE_XVYCC_MODE						"enable_xvycc_mode"							//表示是否使能xvYCC输出模式,取值[0, 1]；0:表示不用使能；1:表示使能
#define CP_HI3531_DEV_MANAGER_CONF_STRING_ENABLE_AUDIO							"enable_audio"								//表示是否使能音频,取值[0, 1]；0:表示不用使能；1:表示使能
#define CP_HI3531_DEV_MANAGER_CONF_STRING_ENABLE_MULTI_CHANNEL					"enable_multi_channel"						//表示多声道还是立体声,取值[0, 1]；0:表示立体声；1:表示多声道,固定为8 声道



#endif