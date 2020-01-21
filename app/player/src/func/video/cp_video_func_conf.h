/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-12-20

Description:

**************************************************************************/

#ifndef _CP_VIDEO_FUNC_CONF_INCLUDE_H_
#define _CP_VIDEO_FUNC_CONF_INCLUDE_H_


#include "cp_core.h"
#include "cp_module_core.h"
#include "cp_video_description.h"
#include "cp_video_func_conf_string.h"



typedef struct cp_video_func_configure_s					cp_video_func_configure_t;



#pragma pack(1)

/************************************************************************/
/* ��Ƶ�����������                                                      */
/************************************************************************/
struct cp_video_func_configure_s
{
	cp_int32_t						convert_flag;								//��ʾ�Ƿ������Ƶ�ز�����ȡֵ��0��ʾ���زɣ�1��ʾ�ز�
	//cp_video_channel_layout_e		channel_layout;								//��ʾ���˳���������ȡֵ��1��ʾ��������2��ʾSTEREO������
	cp_int32_t						sample_format;								//��ʾ�����������ͣ�ȡֵ��1��ʾ8λ��2��ʾ16λ��3��ʾ32λ
	cp_int32_t						sample_rate;								//��ʾ��������Ƶ�ʣ�ȡֵ��44100/48000��
	cp_int32_t						samples;									//��ʾ�����Ĳ���buffer��С
	cp_int32_t						buffer_size;								//��ʾ��ǰʹ�õĻ�������
	cp_int32_t						each_buffer_length;								//��ʾ��ǰʹ�õ�ÿ�������С
};

#pragma pack()


/************************************************************************/
/*���������ļ�                                                           */
/************************************************************************/
cp_int32_t	video_func_parse_configure(cp_module_t *module, cp_video_func_configure_t *afc);


#endif