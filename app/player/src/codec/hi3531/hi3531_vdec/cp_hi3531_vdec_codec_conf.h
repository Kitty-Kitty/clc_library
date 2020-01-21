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



//����vdec_default_priority�����ֵ����Сֵ
#define	CP_HI3531_VIDEO_VDEC_CONF_VDEC_DEFAULT_PRIORITY_MIN_VALUE					1
#define	CP_HI3531_VIDEO_VDEC_CONF_VDEC_DEFAULT_PRIORITY_MAX_VALUE					255




typedef struct cp_hi3531_vdec_video_configure_s										cp_hi3531_vdec_video_configure_t;
typedef struct cp_hi3531_vdec_channel_param_s										cp_hi3531_vdec_channel_param_t;
typedef struct cp_hi3531_vdec_prtcl_param_s											cp_hi3531_vdec_prtcl_param_t;
typedef struct cp_hi3531_vdec_codec_configure_s										cp_hi3531_vdec_codec_configure_t;


/************************************************************************/
/* ��Ƶ�����������                                                      */
/************************************************************************/
struct cp_hi3531_vdec_video_configure_s
{
	cp_int32_t											vdec_max_width;											//��ʾ������֧�ֵ������
	cp_int32_t											vdec_max_height;										//��ʾ������֧�ֵ����߶�
	cp_int32_t											vdec_ref_frame_number;									//��ʾ�ο�֡����Ŀ,ȡֵ��Χ[1, 16],��֡Ϊ��λ
	cp_int32_t											vdec_stream_mode;										//��ʾ�������ͷ�ʽ, 0:��ʾStream������ʽ��1��ʾframe��֡Ϊ��λ
	cp_int32_t											vdec_support_bframe;									//��ʾ�Ƿ�֧��B֡����, ȡֵ��Χ[0, 1]
	cp_int32_t											vdec_default_priority;									//��ʾͨ�����ȼ�,ȡֵ��ΧΪ[1, 255],ֵԽ�����ȼ�Խ��.0������ͨ����������
};

/************************************************************************/
/* �������ͨ������                                                     */
/************************************************************************/
struct cp_hi3531_vdec_channel_param_s
{
	cp_int32_t											channel_err_thr;										//��ʾ������ֵ,ȡֵ��Χ[0,100]. 0�����д���;100�������۴�����پ�����������ʾ
	cp_int32_t											channel_stream_of_thr;									//��ʾ����ǰ��֡��ֵ,ȡֵ��Χ����0
	cp_int32_t											decode_mode;											//��ʾ����ģʽ, 0:����ģʽ��I,P,B ֡�����룩; 1:IP ģʽ�������ο���B ֡�������⣩; 2:I ģʽ��ֻ��I ֡��P,B ֡��������;
	cp_int32_t											decode_order_output;									//��ʾ����ͼ�����˳��, 0:��ʾ�����; 1:���������
};

/************************************************************************/
/* ������Э����ص��ڴ�������                                                     */
/************************************************************************/
struct cp_hi3531_vdec_prtcl_param_s
{
	cp_int32_t											max_slice_number;										//��ʾ��ͨ������֧�ֵ����Slice����,Ĭ��Ϊ16,����H.264��Ч,ȡֵ��ΧΪ[1, 136]
	cp_int32_t											max_sps_number;											//��ʾ��ͨ������֧�ֵ����SPS����,Ĭ��Ϊ2,����H.264��Ч,ȡֵ��ΧΪ[1, 32]
	cp_int32_t											max_pps_number;											//��ʾ��ͨ������֧�ֵ����PPS����,Ĭ��Ϊ2,����H.264��Ч,ȡֵ��ΧΪ[1, 256]
	cp_int32_t											scd_buffer_size;										//��ʾ�����з�ģ���buffer��С,��JPEG/MJPEG��Ч,h264����ʱ,ȡֵΪ���ڵ���MAX��256 x 1024,ͨ����x ͨ���� x3/2��;����Э�����ʱȡֵΪ���ڵ��ڽ���ͨ����С����x �ߣ���
	cp_int32_t											display_frame_number;									//��ʾ��ʾ�����뻺���ͼ�����С֡��,��H.264����ͨ��Ĭ��Ϊ2,��JPEG����ͨ��Ĭ��Ϊ4��ȡֵ��Χ[1, 16]
};

/************************************************************************/
/* hi3531�����������                                                      */
/************************************************************************/
struct cp_hi3531_vdec_codec_configure_s
{
	cp_hi3531_vdec_video_configure_t					vdec_video_conf;										//��ʾ��Ƶ�������
	cp_hi3531_vdec_channel_param_t						vdec_channle_param;										//��ʾ�������ͨ������
	cp_hi3531_vdec_prtcl_param_t						vdec_prtcl_param;
};


/************************************************************************/
/*���������ļ�                                                           */
/************************************************************************/
cp_int32_t	hi3531_vdec_codec_parse_configure(cp_module_t *module, cp_hi3531_vdec_codec_configure_t *hacc);

/************************************************************************/
/*����vdec ����video �����ļ�                                                     */
/************************************************************************/
cp_int32_t	hi3531_vdec_codec_parse_video_configure(cp_module_t *module, cp_hi3531_vdec_codec_configure_t *hacc);

/************************************************************************/
/*�������ͨ������                                                    */
/************************************************************************/
cp_int32_t	hi3531_vdec_codec_parse_channel_param(cp_module_t *module, cp_hi3531_vdec_codec_configure_t *hacc);

/************************************************************************/
/*������Э����ص��ڴ�������                                                    */
/************************************************************************/
cp_int32_t	hi3531_vdec_codec_parse_prtcl_param(cp_module_t *module, cp_hi3531_vdec_codec_configure_t *hacc);


#endif