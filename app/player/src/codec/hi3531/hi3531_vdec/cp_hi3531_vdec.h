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
/* hi3531������Ϣ                                                        */
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
/* hi3531�źŸ�ʽ��ת����Ӧ��                                            */
/************************************************************************/
typedef struct cp_pixel_format_contrast_s
{
	PIXEL_FORMAT_E									pf;
	cp_codec_pixel_format_e							cpf;
}cp_pixel_format_contrast_t;
#endif

/*����hi3531 ��Ϣ*/
cp_int32_t create_hi3531_vdec_info(cp_hi3531_vdec_codec_t *hi3531_vdec_codec, cp_hi3531_vdec_codec_info_t *hi3531_vdec_codec_info);

/*����hi3531 ��Ϣ*/
cp_int32_t destroy_hi3531_vdec_info(cp_hi3531_vdec_codec_t *hi3531_vdec_codec);





/*��ʼ��hi3531 ��Ϣ*/
cp_int32_t init_hi3531_vdec(cp_hi3531_vdec_codec_t *hi3531_vdec_codec, cp_hi3531_vdec_info_t *hi3531_vdec_info);

#if defined(CP_HI3531_VDEC_MODE)
/*��ȡhi3531 playload ����*/
PAYLOAD_TYPE_E get_hi3531_vdec_payload_type(cp_hi3531_vdec_codec_t *hi3531_vdec_codec, cp_hi3531_vdec_info_t *hi3531_vdec_info);

//��hi3531 VIDEO_FRAME_INFO_S�в������ݱ��浽cp_media_packet_t��
cp_int32_t hi3531_vdec_convert_vfi2mp(cp_media_packet_t *mp, VIDEO_FRAME_INFO_S *vfi);

//��hi3531��PIXEL_FORMAT_E ����ת��Ϊ cp_codec_pixel_format_e������ֵ
cp_codec_pixel_format_e hi3531_vdec_convert_pf2cpf(PIXEL_FORMAT_E pf);

#endif




/*����hi3531 ��Ϣ*/
cp_int32_t start_hi3531_vdec(cp_hi3531_vdec_codec_t *hi3531_vdec_codec, cp_hi3531_vdec_info_t *hi3531_vdec_info);

/*����hi3531 ������Э����ص��ڴ�������*/
cp_int32_t hi3531_vdec_set_prtcl_param(cp_hi3531_vdec_codec_t *hi3531_vdec_codec, cp_hi3531_vdec_info_t *hi3531_vdec_info);

/*����hi3531 �������ͨ������*/
cp_int32_t hi3531_vdec_set_channel_param(cp_hi3531_vdec_codec_t *hi3531_vdec_codec, cp_hi3531_vdec_info_t *hi3531_vdec_info);

/*��ȡģ�����ݣ�flagΪ��ȡģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��*/
cp_int32_t read_hi3531_vdec_data(cp_hi3531_vdec_codec_t *hi3531_vdec_codec, cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag);

/*дģ�����ݣ�flagΪдģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��*/
cp_int32_t write_hi3531_vdec_data(cp_hi3531_vdec_codec_t *hi3531_vdec_codec, const cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag);




/*ֹͣhi3531 ��Ϣ*/
cp_int32_t stop_hi3531_vdec(cp_hi3531_vdec_codec_t *hi3531_vdec_codec, cp_hi3531_vdec_info_t *hi3531_vdec_info);





#endif