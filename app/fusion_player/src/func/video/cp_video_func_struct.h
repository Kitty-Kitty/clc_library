/*******************************************************************************
*
*Copyright:novigo
*
*File name: cp_video_func_struct.h
*
*Author:fangzhenmu@novigo.com.cn
*
*Version: 1.0
*
*Date:2017/08/09
*
*Description: create (cp_video_func_struct.h)
*
*Others:
*
*History:
*******************************************************************************/

#ifndef _CP_VIDEO_FUNC_STRUCT_H_
#define _CP_VIDEO_FUNC_STRUCT_H_



#include "cp_core.h"
#include "cp_include.h"
#include "cp_socket.h"
#include "cp_safe_queue.h"



typedef enum cp_video_func_thread_status_enum							cp_video_func_thread_status_e;
typedef struct cp_video_func_media_process_struct						cp_video_func_media_process_t;
typedef struct cp_video_func_codec_process_struct						cp_video_func_codec_process_t;
typedef struct cp_video_func_check_process_struct						cp_video_func_check_process_t;
typedef struct cp_video_func_merge_process_struct						cp_video_func_merge_process_t;



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
	cp_thread_t								*thread;					/*�̹߳�����*/
	cp_media_packet_t						*decode_mp;					/*����ý������*/
	cp_media_packet_t						*cache_mp;					/*ý�崦��������*/
	cp_safe_queue_t							*media_sq;					/*ý�崦��ʹ�ð�ȫ����*/
	cp_safe_queue_t							*media_cache_sq;			/*ý�崦��ʹ�ð�ȫ����*/
	cp_video_func_thread_status_e			thread_status;				/*�߳�״̬*/
};


/************************************************************************/
/* ý����봦����Ϣ����                                                      */
/************************************************************************/
struct cp_video_func_codec_process_struct
{
	cp_func_t								*video_func;				/*��Ƶfunc*/
	cp_codec_t								*codecs;					/*��������Ϣ*/
	cp_video_description_t					decode_md;					/*��ʾ������ý����Ϣ*/
	cp_codec_callback_info_t				cc_info;					/*��ʾ�������ص�����*/
	cp_video_func_media_process_t			mp_info;					/*ý�崦����Ϣ*/
	cp_bool_t								is_open_codec;				/*��ʾ�Ƿ�򿪽�����*/
};



/************************************************************************/
/* ý�����ƴ����Ϣ����                                                      */
/************************************************************************/
struct cp_video_func_check_process_struct
{
	cp_func_t								*video_func;				/*��Ƶfunc*/
	cp_video_func_media_process_t			mp_info;					/*ý�崦����Ϣ*/
};


/************************************************************************/
/* ý�����ƴ����Ϣ����                                                      */
/************************************************************************/
struct cp_video_func_merge_process_struct
{
	cp_func_t								*video_func;				/*��Ƶfunc*/
	cp_video_func_media_process_t			mp_info;					/*ý�崦����Ϣ*/
};



#endif //_CP_VIDEO_FUNC_STRUCT_H_


