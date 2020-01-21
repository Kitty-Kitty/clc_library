/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/

#ifndef	_CP_VIDEO_FUNC_INCLUDE_H_
#define _CP_VIDEO_FUNC_INCLUDE_H_

#include "cp_video_func_core.h"



//#define		CP_VIDEO_FILE_DEBUG										1
//#define		CP_VIDEO_FRAME_TIMESTAMP								1
#define		CP_VIDEO_FUNC_MEDIA_ARRAY_SIZE								1024							//���������С


//typedef struct cp_video_func_s										cp_video_func_t;
typedef enum cp_video_func_thread_status_enum							cp_video_func_thread_status_e;
typedef struct cp_video_func_media_process_struct						cp_video_func_media_process_t;


#pragma pack(1)


#define CP_VIDEO_FUNC_FIELDS																			\
		CP_FUNC_FIELDS																					\
		cp_video_func_configure_t				afc;					/*��Ƶ�����������Ϣ*/			\
		cp_codec_t								*codec;					/*��������Ϣ*/					\
		cp_dev_t								*dev;					/*�����豸��Ϣ*/					\
		cp_filter_t								*filter;				/*���ݹ�����*/					\
		cp_memh_socket_data_t					*msd;					/*��ʾ���յ�ý��Դ����*/			\
		cp_video_func_media_process_t			mp_info;				/*ý�崦����Ϣ*/					\
		cp_channel_manager_t					cm;						/*ͨ��������*/					\
		cp_media_channel_info_t					mci;					/*��ʾ��ǰ���ŵ�ý����Ϣ*/		\
		cp_video_description_t					decode_md;				/*��ʾ������ý����Ϣ*/			\
		cp_codec_callback_info_t				cc_info;				/*��ʾ�������ص�����*/			\




/************************************************************************/
/* video func thread status                                             */
/************************************************************************/
enum cp_video_func_thread_status_enum
{
	cp_video_func_thread_status_init = 1,
	cp_video_func_thread_status_start,
	cp_video_func_thread_status_stop,
};


/************************************************************************/
/* ý�崦����Ϣ����                                                      */
/************************************************************************/
struct cp_video_func_media_process_struct
{
	cp_thread_t								*decode_thread;				/*�̹߳�����*/
	cp_thread_t								*merge_thread;				/*�̹߳�����*/
	cp_media_packet_t						*decode_mp;					/*����ý������*/
	cp_media_packet_t						*merge_cache_mp;			/*ý�崦��������*/
	cp_safe_queue_t							*merge_sq;					/*ý�崦��ʹ�ð�ȫ����*/
	cp_safe_queue_t							*merge_cache_sq;			/*ý�崦��ʹ�ð�ȫ����*/
	cp_bool_t								is_open_codec;				/*��ʾ�Ƿ�򿪽�����*/
	cp_video_func_thread_status_e			thread_status;				/*�߳�״̬*/
};


/************************************************************************/
/*                                                                      */
/************************************************************************/
struct cp_video_func_s {
	CP_VIDEO_FUNC_FIELDS												/*��ʾʱ��ģ����Ϣ*/

#if defined(CP_VIDEO_FILE_DEBUG)
	FILE											*file;				/*ý���ļ�*/						
#endif

#if defined(CP_VIDEO_FRAME_TIMESTAMP)
	FILE											*timestamp_file;	/*ʱ����ļ�*/
#endif
	cp_int32_t										play_flag;
};



#pragma pack()


cp_video_func_t* create_video_func(cp_module_register_t *register_info, cp_socket_manager_t *manager, cp_video_func_info_t *info);
cp_int32_t destroy_video_func(cp_video_func_manager_t *manager, cp_video_func_t* video_func);


#endif


