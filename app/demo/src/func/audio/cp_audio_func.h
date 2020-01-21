/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/

#ifndef	_CP_AUDIO_FUNC_INCLUDE_H_
#define _CP_AUDIO_FUNC_INCLUDE_H_

#include "cp_audio_func_core.h"



#define		CP_AUDIO_FILE_DEBUG									1
#define		CP_AUDIO_FUNC_MEDIA_ARRAY_SIZE						1024					//���������С


//typedef struct cp_audio_func_s					cp_audio_func_t;
typedef enum cp_audio_func_thread_status_enum		cp_audio_func_thread_status_e;



#pragma pack(1)


#define CP_AUDIO_FUNC_FIELDS																	\
		CP_FUNC_FIELDS																			\
		cp_audio_func_configure_t				afc;			/*��Ƶ�����������Ϣ*/			\
		cp_codec_t								*codec;			/*��������Ϣ*/					\
		cp_dev_t								*dev;			/*�����豸��Ϣ*/					\
		cp_filter_t								*filter;		/*���ݹ�����*/					\
		cp_thread_t								*thread;		/*�̹߳�����*/					\
		cp_media_packet_t						*decode_mp;		/*����ý������*/					\
		cp_bool_t								is_open_codec;	/*��ʾ�Ƿ�򿪽�����*/			\
		cp_audio_func_thread_status_e			thread_status;	/*�߳�״̬*/						\
		cp_channel_manager_t					cm;				/*ͨ��������*/					\
		cp_media_channel_info_t					mci;			/*��ʾ��ǰ���ŵ�ý����Ϣ*/		\
		cp_audio_description_t					decode_md;		/*��ʾ������ý����Ϣ*/			\
		cp_codec_callback_info_t				cc_info;		/*��ʾ�������ص�����*/			\


/************************************************************************/
/*                                                                      */
/************************************************************************/
struct cp_audio_func_s {
	CP_AUDIO_FUNC_FIELDS										/*��ʾʱ��ģ����Ϣ*/
		
#if defined(CP_AUDIO_FILE_DEBUG)
		FILE											*file;	/*ý���ļ�*/						
#endif
};


enum cp_audio_func_thread_status_enum
{
	cp_audio_func_thread_status_init = 1,
	cp_audio_func_thread_status_start,
	cp_audio_func_thread_status_stop,
};


#pragma pack()


cp_audio_func_t* create_audio_func(cp_module_register_t *register_info, cp_socket_manager_t *manager, cp_audio_func_info_t *info);
cp_int32_t destroy_audio_func(cp_audio_func_manager_t *manager, cp_audio_func_t* audio_func);


#endif


