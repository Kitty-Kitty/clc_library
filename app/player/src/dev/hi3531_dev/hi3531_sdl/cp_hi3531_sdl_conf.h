/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-12-20

Description:

**************************************************************************/

#ifndef _CP_HI3531_SDL_CONF_INCLUDE_H_
#define _CP_HI3531_SDL_CONF_INCLUDE_H_


#include "cp_core.h"
#include "cp_module_core.h"
#include "cp_hi3531_sdl_conf_string.h"





typedef struct	cp_hi3531_sdl_configure_s							cp_hi3531_sdl_configure_t;



/************************************************************************/
/* ��Ƶ�����������                                                      */
/************************************************************************/
struct cp_hi3531_sdl_configure_s
{
	cp_int32_t							width;										//��ʾ�����������Ƶ���
	cp_int32_t							heigth;										//��ʾ�����������Ƶ�߶�
	cp_int32_t							fps;										//��ʾ����֡��
	cp_int32_t							bitrate;									//��ʾ������������ʣ���λkbps
	cp_int32_t							mode;										//��ʾcodec����ģʽ��1��ʾvi-venc��2��ʾvi-fisheye-vpss-vencģʽ
};



/************************************************************************/
/*���������ļ�                                                           */
/************************************************************************/
cp_int32_t	hi3531_sdl_parse_configure(cp_module_t *module, cp_hi3531_sdl_configure_t *hacc);

#endif