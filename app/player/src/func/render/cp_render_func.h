/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/

#ifndef	_CP_RENDER_FUNC_INCLUDE_H_
#define _CP_RENDER_FUNC_INCLUDE_H_

#include "cp_render_func_core.h"



#define		CP_RENDER_FILE_DEBUG									1
#define		CP_RENDER_FUNC_MEDIA_ARRAY_SIZE						1024					//���������С


//typedef struct cp_render_func_s					cp_render_func_t;
typedef enum cp_render_func_thread_status_enum		cp_render_func_thread_status_e;



#pragma pack(1)


#define CP_RENDER_FUNC_FIELDS																	\
		CP_FUNC_FIELDS																			\
		cp_dev_t								*dev;			/*�����豸��Ϣ*/					\
		cp_filter_t								*filter;		/*���ݹ�����*/					\
		cp_thread_t								*thread;		/*�̹߳�����*/					\
		cp_media_packet_t						*decode_mp;		/*����ý������*/					\
		cp_render_func_thread_status_e			thread_status;	/*�߳�״̬*/						\


/************************************************************************/
/*                                                                      */
/************************************************************************/
struct cp_render_func_s {
	CP_RENDER_FUNC_FIELDS												/*��ʾʱ��ģ����Ϣ*/
		
#if defined(CP_RENDER_FILE_DEBUG)
		FILE											*file;			/*ý���ļ�*/						
#endif
};


enum cp_render_func_thread_status_enum
{
	cp_render_func_thread_status_init = 1,
	cp_render_func_thread_status_start,
	cp_render_func_thread_status_stop,
};


#pragma pack()


cp_render_func_t* create_render_func(cp_module_register_t *register_info, cp_socket_manager_t *manager, cp_render_func_info_t *info);
cp_int32_t destroy_render_func(cp_render_func_manager_t *manager, cp_render_func_t* render_func);


#endif


