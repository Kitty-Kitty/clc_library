/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-12-20

Description:

**************************************************************************/

#ifndef _CP_HI3531_VDEC_CODEC_CONF_INCLUDE_H_
#define _CP_HI3531_VDEC_CODEC_CONF_INCLUDE_H_


#include "cp_core.h"
#include "cp_module_core.h"
#include "cp_hi3531_vdec_codec_conf_string.h"



//定义vdec_default_priority的最大值和最小值
#define	CP_HI3531_VIDEO_VDEC_CONF_VDEC_DEFAULT_PRIORITY_MIN_VALUE					1
#define	CP_HI3531_VIDEO_VDEC_CONF_VDEC_DEFAULT_PRIORITY_MAX_VALUE					255




typedef struct cp_hi3531_vdec_video_configure_s										cp_hi3531_vdec_video_configure_t;
typedef struct cp_hi3531_vdec_channel_param_s										cp_hi3531_vdec_channel_param_t;
typedef struct cp_hi3531_vdec_prtcl_param_s											cp_hi3531_vdec_prtcl_param_t;
typedef struct cp_hi3531_vdec_codec_configure_s										cp_hi3531_vdec_codec_configure_t;


/************************************************************************/
/* 视频解码相关配置                                                      */
/************************************************************************/
struct cp_hi3531_vdec_video_configure_s
{
	cp_int32_t											vdec_max_width;											//表示解码器支持的最大宽度
	cp_int32_t											vdec_max_height;										//表示解码器支持的最大高度
	cp_int32_t											vdec_ref_frame_number;									//表示参考帧的数目,取值范围[1, 16],以帧为单位
	cp_int32_t											vdec_stream_mode;										//表示码流发送方式, 0:表示Stream以流方式；1表示frame以帧为单位
	cp_int32_t											vdec_support_bframe;									//表示是否支持B帧解码, 取值范围[0, 1]
	cp_int32_t											vdec_default_priority;									//表示通道优先级,取值范围为[1, 255],值越大优先级越高.0表明此通道不被调度
};

/************************************************************************/
/* 定义解码通道参数                                                     */
/************************************************************************/
struct cp_hi3531_vdec_channel_param_s
{
	cp_int32_t											channel_err_thr;										//表示错误阈值,取值范围[0,100]. 0代表有错即丢;100代表无论错误多少均继续解码显示
	cp_int32_t											channel_stream_of_thr;									//表示解码前丢帧阈值,取值范围：≥0
	cp_int32_t											decode_mode;											//表示解码模式, 0:正常模式（I,P,B 帧都解码）; 1:IP 模式（不作参考的B 帧丢弃不解）; 2:I 模式（只解I 帧，P,B 帧均丢弃）;
	cp_int32_t											decode_order_output;									//表示解码图像输出顺序, 0:显示序输出; 1:解码序输出
};

/************************************************************************/
/* 定义与协议相关的内存分配参数                                                     */
/************************************************************************/
struct cp_hi3531_vdec_prtcl_param_s
{
	cp_int32_t											max_slice_number;										//表示该通道解码支持的最大Slice个数,默认为16,仅对H.264有效,取值范围为[1, 136]
	cp_int32_t											max_sps_number;											//表示该通道解码支持的最大SPS个数,默认为2,仅对H.264有效,取值范围为[1, 32]
	cp_int32_t											max_pps_number;											//表示该通道解码支持的最大PPS个数,默认为2,仅对H.264有效,取值范围为[1, 256]
	cp_int32_t											scd_buffer_size;										//表示码流切分模块的buffer大小,对JPEG/MJPEG无效,h264解码时,取值为大于等于MAX（256 x 1024,通道宽x 通道高 x3/2）;其它协议解码时取值为大于等于解码通道大小（宽x 高）。
	cp_int32_t											display_frame_number;									//表示显示及解码缓存的图像的最小帧数,对H.264解码通道默认为2,对JPEG解码通道默认为4。取值范围[1, 16]
};

/************************************************************************/
/* hi3531解码相关配置                                                      */
/************************************************************************/
struct cp_hi3531_vdec_codec_configure_s
{
	cp_hi3531_vdec_video_configure_t					vdec_video_conf;										//表示视频相关配置
	cp_hi3531_vdec_channel_param_t						vdec_channle_param;										//表示定义解码通道参数
	cp_hi3531_vdec_prtcl_param_t						vdec_prtcl_param;
};


/************************************************************************/
/*解析配置文件                                                           */
/************************************************************************/
cp_int32_t	hi3531_vdec_codec_parse_configure(cp_module_t *module, cp_hi3531_vdec_codec_configure_t *hacc);

/************************************************************************/
/*解析vdec 解码video 配置文件                                                     */
/************************************************************************/
cp_int32_t	hi3531_vdec_codec_parse_video_configure(cp_module_t *module, cp_hi3531_vdec_codec_configure_t *hacc);

/************************************************************************/
/*定义解码通道参数                                                    */
/************************************************************************/
cp_int32_t	hi3531_vdec_codec_parse_channel_param(cp_module_t *module, cp_hi3531_vdec_codec_configure_t *hacc);

/************************************************************************/
/*定义与协议相关的内存分配参数                                                    */
/************************************************************************/
cp_int32_t	hi3531_vdec_codec_parse_prtcl_param(cp_module_t *module, cp_hi3531_vdec_codec_configure_t *hacc);


#endif