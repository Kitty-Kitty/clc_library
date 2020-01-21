/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/

#ifndef	_CP_CODEC_INCLUDE_H_
#define _CP_CODEC_INCLUDE_H_




#include "cp_codec_core.h"




//typedef struct cp_codec_s				cp_codec_t;
typedef	struct cp_codec_callback_handle_s				cp_codec_callback_handle_t;



#pragma pack(1)



typedef cp_int32_t(*cp_codec_general_cb_handle)(cp_module_t *module,
	cp_codec_callback_info_t *ccb_info_p, cp_media_packet_t *mp);				/*����ص�����*/



#define CP_CODEC_FIELDS																						\
		CP_MODULE_FIELDS																					\


/************************************************************************/
/*��������Ϣ                                                             */
/************************************************************************/
struct cp_codec_s {
	CP_CODEC_FIELDS																/*��ʾʱ��ģ����Ϣ*/
};


/************************************************************************/
/* �������쳣��Ϣ                                                        */
/************************************************************************/
struct cp_codec_status_info_s
{
	cp_int32_t					status;
};


/************************************************************************/
/* �������ص�����Ҫ�������ݴ����ͬ���ص�����һ��ͬ������                   */
/************************************************************************/
struct cp_codec_callback_handle_s
{
	cp_codec_general_cb_handle		read_cb;							//��ʾ������������ص�����
	cp_codec_general_cb_handle		write_cb;							//��ʾ������д����ص�����
	cp_codec_general_cb_handle		error_cb;							//��ʾ������������ص�����
};


/************************************************************************/
/* ������������Ϣ��������ͨ������ṹ�ж��Ƿ�ͬ���ص�                      */
/************************************************************************/
struct cp_codec_callback_info_s
{
	cp_codec_callback_handle_t		handle;							//��ʾ�ص����
	cp_codec_status_info_t			status_info;					//��ʾ������״̬��Ϣ
	cp_module_t						*module;
	cp_uchar_t						**buf;
	cp_int32_t						len;
	cp_int32_t						flag;
};


#pragma pack()



#endif


