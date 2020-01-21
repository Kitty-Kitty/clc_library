/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-12-20

Description:

**************************************************************************/

#ifndef _CP_HI3531_MANAGER_CONF_STRING_INCLUDE_H_
#define _CP_HI3531_MANAGER_CONF_STRING_INCLUDE_H_



#define CP_HI3531_MANAGER_CONF_STRING_HI3531_CONFIGURE						"hi3531_configure"							//表示hi3531配置项


#define CP_HI3531_MANAGER_CONF_STRING_HI3531_SYSTEM							"hi3531_system"								//表示hi3531系统内容
#define CP_HI3531_MANAGER_CONF_STRING_MAX_POOL_COUNT						"max_pool_count"							//表示最大的内存池数量
#define CP_HI3531_MANAGER_CONF_STRING_ALIGN_WIDTH							"align_width"								//表示对齐宽度


#define CP_HI3531_MANAGER_CONF_STRING_HI3531_VDEC							"hi3531_vdec"								//表示hi3531 vdec配置信息
#define CP_HI3531_MANAGER_CONF_STRING_VDEC_MPP_DEV_ID						"vdec_mpp_dev_id"							//表示模块设备号
#define CP_HI3531_MANAGER_CONF_STRING_VDEC_MPP_CHANNEL_NUMBER				"vdec_mpp_channel_number"					//表示模块设备通道使用内存DDR数量
#define CP_HI3531_MANAGER_CONF_STRING_VDEC_MMZ_NAME							"vdec_mmz_name"								//表示内存所在DDR的名字


#define CP_HI3531_MANAGER_CONF_STRING_VDEC_VIDEO_ATTR						"vdec_video_attr"							//表示视频相关属性信息
#define CP_HI3531_MANAGER_CONF_STRING_VDEC_MAX_WIDTH						"vdec_max_width"							//表示最大支持分辨率宽度
#define CP_HI3531_MANAGER_CONF_STRING_VDEC_MAX_HEIGHT						"vdec_max_height"							//表示最大支持分辨率高度
#define CP_HI3531_MANAGER_CONF_STRING_VDEC_REF_FRAME_NUMBER					"vdec_ref_frame_number"						//表示参考帧的数目,取值范围[1, 16],以帧为单位
#define CP_HI3531_MANAGER_CONF_STRING_VDEC_STREAM_MODE						"vdec_stream_mode"							//表示码流发送方式, 0:表示Stream以流方式；1表示frame以帧为单位
#define CP_HI3531_MANAGER_CONF_STRING_VDEC_SUPPORT_BFRAME					"vdec_support_bframe"						//表示是否支持B帧解码, 取值范围[0, 1]



#endif