/*******************************************************************************
*
*Copyright:novigo
*
*File name: cp_vdu_process_struct.h
*
*Author:fangzhenmu@novigo.com.cn
*
*Version: 1.0
*
*Date:2018/02/02
*
*Description: create (cp_vdu_process_struct.h)
*
*Others:
*
*History:
*******************************************************************************/

#ifndef _CP_VDU_PROCESS_STRUCT_H_
#define _CP_VDU_PROCESS_STRUCT_H_




#include "cp_module.h"
#include "cp_coordinate.h"




typedef		struct cp_vdu_process_s						cp_vdu_process_t;
typedef		struct cp_vdu_channel_process_s				cp_vdu_channel_process_t;
//typedef	enum cp_vdu_process_struct_type_enum		cp_vdu_process_struct_type_e;




/************************************************************************/
/*ģ������,��ģ����Ϣ����̳и���Ϣ                                       */
/************************************************************************/
#define CP_VDU_PROCESS_STRUCT_FIELDS																			\
			cp_void_t						*vdu;							/*��ʾ����Ԫ���ݵ�ַ*/				\
			cp_void_t						*channel;						/*��ʾ����ͨ�����ݵ�ַ*/				\
			cp_vdu_process_struct_type_e	type;							/*��ʾ����ṹ������*/				\
			cp_coordinate_t					coordinate;						/*��ʾ������Ϣ*/						\
			cp_rect_t						vdu_rect;						/*��ʾͼƬԴ������Ϣ*/				\
			cp_rect_t						image_rect;						/*��ʾ���ɵ�ͼƬ��С������һ�����ŵĲ���*/				\
			cp_uchar_t						*buf;							/*��ʾ����ռ�*/						\
			cp_bool_t						is_debug_mode;					/*��ʾ�Ƿ��debug ģʽ*/			\
			cp_char_t						*debug_path;					/*��ʾdebug��Ϣ�����Ŀ¼*/			\
			cp_int32_t						buf_length;						/*��ʾ����ռ��С*/					\
			cp_int32_t						image_length;					/*��ʾͼƬ���ݵĳ���*/				\
			cp_codec_pixel_format_e			pixel_format;					/*��ʾͼƬ��ʽ����*/					\
			cp_module_type_e				vdu_channel_module_type;		/*��ʾvdu channel������*/			\
			CP_MODULE_ERROR_FIELDS											/*��ʾģ��Ĵ�����Ϣ*/				\



/************************************************************************/
/* ��ʾ����ṹ������                                                    */
/************************************************************************/
typedef	enum cp_vdu_process_struct_type_enum
{
	cp_vdu_process_struct_type_none = 0,
	cp_vdu_process_struct_type_process,
	cp_vdu_process_struct_type_channel,
}cp_vdu_process_struct_type_e;



/************************************************************************/
/* ��ʾvdu ���������Ϣ�ṹ��                                            */
/************************************************************************/
struct cp_vdu_process_s
{
	CP_VDU_PROCESS_STRUCT_FIELDS									/*��ʾ����ṹ����*/
};



/************************************************************************/
/* ��ʾvdu channel���������Ϣ�ṹ��                                            */
/************************************************************************/
struct cp_vdu_channel_process_s
{
	CP_VDU_PROCESS_STRUCT_FIELDS									/*��ʾ����ṹ����*/
	cp_int32_t							index;						/*��ʾͨ����������*/
};



#endif