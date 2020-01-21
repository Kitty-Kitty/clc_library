/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-12-20

Description:

**************************************************************************/

#ifndef _CP_HI3531_VDEC_CODEC_CONF_STRING_INCLUDE_H_
#define _CP_HI3531_VDEC_CODEC_CONF_STRING_INCLUDE_H_


#define CP_HI3531_VIDEO_VDEC_CONF_STRING_VDEC_VIDEO_ATTR								"vdec_video_attr"							//表示视频相关属性信息
#define CP_HI3531_VIDEO_VDEC_CONF_STRING_VDEC_MAX_WIDTH									"vdec_max_width"							//表示最大支持分辨率宽度
#define CP_HI3531_VIDEO_VDEC_CONF_STRING_VDEC_MAX_HEIGHT								"vdec_max_height"							//表示最大支持分辨率高度
#define CP_HI3531_VIDEO_VDEC_CONF_STRING_VDEC_REF_FRAME_NUMBER							"vdec_ref_frame_number"						//表示参考帧的数目,取值范围[1, 16],以帧为单位
#define CP_HI3531_VIDEO_VDEC_CONF_STRING_VDEC_STREAM_MODE								"vdec_stream_mode"							//表示码流发送方式, 0:表示Stream以流方式；1表示frame以帧为单位
#define CP_HI3531_VIDEO_VDEC_CONF_STRING_VDEC_SUPPORT_BFRAME							"vdec_support_bframe"						//表示是否支持B帧解码, 取值范围[0, 1]
#define CP_HI3531_VIDEO_VDEC_CONF_STRING_VDEC_DEFAULT_PRIORITY							"vdec_default_priority"						//表示通道优先级,取值范围为[1, 255],值越大优先级越高.0表明此通道不被调度


#define CP_HI3531_VIDEO_VDEC_CONF_STRING_VDEC_VIDEO_CHANNEL_PRARAM						"vdec_video_channel_praram"					//表示视频相关属性信息
#define CP_HI3531_VIDEO_VDEC_CONF_STRING_CHANNEL_ERR_THR								"channel_err_thr"							//表示最大支持分辨率宽度
#define CP_HI3531_VIDEO_VDEC_CONF_STRING_CHANNEL_STREAM_OF_THR							"channel_stream_of_thr"						//表示最大支持分辨率高度
#define CP_HI3531_VIDEO_VDEC_CONF_STRING_DECODE_MODE									"decode_mode"								//表示参考帧的数目,取值范围[1, 16],以帧为单位
#define CP_HI3531_VIDEO_VDEC_CONF_STRING_DECODE_ORDER_OUTPUT							"decode_order_output"						//表示码流发送方式, 0:表示Stream以流方式；1表示frame以帧为单位


#define CP_HI3531_VIDEO_VDEC_CONF_STRING_VDEC_VIDEO_PRTCL_PRARAM						"vdec_video_prtcl_praram"					//表示视频相关属性信息
#define CP_HI3531_VIDEO_VDEC_CONF_STRING_MAX_SLICE_NUMBER								"max_slice_number"							//表示最大支持分辨率宽度
#define CP_HI3531_VIDEO_VDEC_CONF_STRING_MAX_SPS_NUMBER									"max_sps_number"							//表示最大支持分辨率高度
#define CP_HI3531_VIDEO_VDEC_CONF_STRING_MAX_PPS_NUMBER									"max_pps_number"							//表示参考帧的数目,取值范围[1, 16],以帧为单位
#define CP_HI3531_VIDEO_VDEC_CONF_STRING_SCD_BUFFER_SIZE								"scd_buffer_size"							//表示码流发送方式, 0:表示Stream以流方式；1表示frame以帧为单位
#define CP_HI3531_VIDEO_VDEC_CONF_STRING_DISPLAY_FRAME_NUMBER							"display_frame_number"						//表示码流发送方式, 0:表示Stream以流方式；1表示frame以帧为单位



#endif