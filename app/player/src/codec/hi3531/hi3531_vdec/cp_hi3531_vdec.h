/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-12-25

Description:

**************************************************************************/

#ifndef _CP_HI3531_DEC_AV_SAMPLE_INCLUDE_H_
#define _CP_HI3531_DEC_AV_SAMPLE_INCLUDE_H_




#include "cp_hi3531_vdec_codec_core.h"




/************************************************************************/
/* hi3531配置信息                                                        */
/************************************************************************/
struct cp_hi3531_vdec_info_s
{
	cp_hi3531_vdec_codec_t							*hi3531_vdec_codec;
	cp_video_description_t							*vd;

#if defined(CP_HI3531_VDEC_MODE)
	VDEC_CHN										vdec_channel;
	VDEC_CHN_ATTR_S									vdec_channel_attr;
	VDEC_CHN_PARAM_S								vdec_channel_param;
	VDEC_PRTCL_PARAM_S								vdec_prtcl_param;
#endif
};


#if defined(CP_HI3531_VDEC_MODE)
/************************************************************************/
/* hi3531信号格式的转换对应表                                            */
/************************************************************************/
typedef struct cp_pixel_format_contrast_s
{
	PIXEL_FORMAT_E									pf;
	cp_codec_pixel_format_e							cpf;
}cp_pixel_format_contrast_t;
#endif

/*创建hi3531 信息*/
cp_int32_t create_hi3531_vdec_info(cp_hi3531_vdec_codec_t *hi3531_vdec_codec, cp_hi3531_vdec_codec_info_t *hi3531_vdec_codec_info);

/*销毁hi3531 信息*/
cp_int32_t destroy_hi3531_vdec_info(cp_hi3531_vdec_codec_t *hi3531_vdec_codec);





/*初始化hi3531 信息*/
cp_int32_t init_hi3531_vdec(cp_hi3531_vdec_codec_t *hi3531_vdec_codec, cp_hi3531_vdec_info_t *hi3531_vdec_info);

#if defined(CP_HI3531_VDEC_MODE)
/*获取hi3531 playload 类型*/
PAYLOAD_TYPE_E get_hi3531_vdec_payload_type(cp_hi3531_vdec_codec_t *hi3531_vdec_codec, cp_hi3531_vdec_info_t *hi3531_vdec_info);

//将hi3531 VIDEO_FRAME_INFO_S中部分数据保存到cp_media_packet_t中
cp_int32_t hi3531_vdec_convert_vfi2mp(cp_media_packet_t *mp, VIDEO_FRAME_INFO_S *vfi);

//将hi3531中PIXEL_FORMAT_E 类型转换为 cp_codec_pixel_format_e类型数值
cp_codec_pixel_format_e hi3531_vdec_convert_pf2cpf(PIXEL_FORMAT_E pf);

#endif




/*启动hi3531 信息*/
cp_int32_t start_hi3531_vdec(cp_hi3531_vdec_codec_t *hi3531_vdec_codec, cp_hi3531_vdec_info_t *hi3531_vdec_info);

/*设置hi3531 定义与协议相关的内存分配参数*/
cp_int32_t hi3531_vdec_set_prtcl_param(cp_hi3531_vdec_codec_t *hi3531_vdec_codec, cp_hi3531_vdec_info_t *hi3531_vdec_info);

/*设置hi3531 定义解码通道参数*/
cp_int32_t hi3531_vdec_set_channel_param(cp_hi3531_vdec_codec_t *hi3531_vdec_codec, cp_hi3531_vdec_info_t *hi3531_vdec_info);

/*读取模块数据，flag为读取模式的扩展标志。默认为0，其他为预留*/
cp_int32_t read_hi3531_vdec_data(cp_hi3531_vdec_codec_t *hi3531_vdec_codec, cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag);

/*写模块数据，flag为写模式的扩展标志。默认为0，其他为预留*/
cp_int32_t write_hi3531_vdec_data(cp_hi3531_vdec_codec_t *hi3531_vdec_codec, const cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag);




/*停止hi3531 信息*/
cp_int32_t stop_hi3531_vdec(cp_hi3531_vdec_codec_t *hi3531_vdec_codec, cp_hi3531_vdec_info_t *hi3531_vdec_info);





#endif