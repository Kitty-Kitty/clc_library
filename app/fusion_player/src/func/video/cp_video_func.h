/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/

#ifndef	_CP_VIDEO_FUNC_INCLUDE_H_
#define _CP_VIDEO_FUNC_INCLUDE_H_

#include "cp_video_func_core.h"
#include "cp_video_func_proc.h"


//#define		CP_VIDEO_FILE_DEBUG										1
//#define		CP_VIDEO_FRAME_TIMESTAMP								1
#define		CP_VIDEO_FUNC_MEDIA_ARRAY_SIZE								1024							//���������С


//typedef struct cp_video_func_s										cp_video_func_t;


#pragma pack(1)



#define CP_VIDEO_FUNC_FIELDS																			\
		CP_FUNC_FIELDS																					\
		cp_video_func_configure_t				afc;					/*��Ƶ�����������Ϣ*/			\
		cp_dev_t								*dev;					/*�����豸��Ϣ*/					\
		cp_memh_socket_data_t					*msd;					/*��ʾ���յ�ý��Դ����*/			\
		cp_video_func_codec_process_t			codec_process_info[CP_VIDEO_SOURCES_MAX_NUMBER];				/*ý����봦����Ϣ*/					\
		cp_video_func_check_process_t			check_process_info;		/*��ʾ����ͼ��У������*/			\
		cp_video_func_merge_process_t			merge_process_info;		/*��ʾ����ͼ��ƴ������*/			\
		cp_media_channel_info_t					mci;					/*��ʾ��ǰ���ŵ�ý����Ϣ*/		\


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


