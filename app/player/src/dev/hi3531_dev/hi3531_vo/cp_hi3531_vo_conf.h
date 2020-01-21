/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-12-20

Description:

**************************************************************************/

#ifndef _CP_HI3531_VO_CONF_INCLUDE_H_
#define _CP_HI3531_VO_CONF_INCLUDE_H_


#include "cp_core.h"
#include "cp_module_core.h"
#include "cp_hi3531_dev_include.h"
#include "cp_hi3531_vo_conf_string.h"



#define	CP_HI3531_VO_BACK_COLOR_STRING_SIZE							16									//��ʾvo����ɫ�ֽڳ���



typedef struct	cp_hi3531_vo_channel_configure_s					cp_hi3531_vo_channel_configure_t;
typedef struct	cp_hi3531_vo_configure_s							cp_hi3531_vo_configure_t;



/************************************************************************/
/* ��Ƶͨ�������������                                                  */
/************************************************************************/
struct cp_hi3531_vo_channel_configure_s
{
	cp_int32_t								id;															//��ʾͨ�����,ȡֵ[0, 63]
	cp_bool_t								is_used;													//����Ƿ�ʹ��
#if defined(CP_HI3531_DEV_MODE)
	VO_CHN_ATTR_S							attr;														//vo ͨ������
#endif
};


/************************************************************************/
/* ��Ƶ�����������                                                      */
/************************************************************************/
struct cp_hi3531_vo_configure_s
{
	cp_int32_t								dev_id;														//��ʾ�豸���,ȡֵ[0, 7]
	cp_int32_t								intf_type;													//�ӿ�����,ȡֵ[0, 8]
	cp_int32_t								intf_sync;													//�ӿ�ʱ���������,ȡֵ[0, 24]
	cp_bool_t								enable_double_frame;										//�Ƿ���Ҫ��֡,ȡֵ[0, 1]��0:��ʾ����ʹ�ܣ�1:��ʾʹ��
	cp_bool_t								is_used;													//����Ƿ�ʹ��
	cp_char_t								back_color[CP_HI3531_VO_BACK_COLOR_STRING_SIZE];			//��ʾ�ڴ�����DDR������
};



/************************************************************************/
/*���������ļ�                                                           */
/************************************************************************/
cp_int32_t	hi3531_vo_parse_configure(cp_module_t *module, cp_hi3531_vo_configure_t *hacc);

#endif