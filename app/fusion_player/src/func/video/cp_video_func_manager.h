/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/

#ifndef	_CP_VIDEO_FUNC_MANAGER_INCLUDE_H_
#define _CP_VIDEO_FUNC_MANAGER_INCLUDE_H_

#include "cp_video_func_core.h"




//typedef struct cp_video_func_manager_s						cp_video_func_manager_t;

#define		CP_VIDEO_FUNC_MAX_NUMBER							4				//��ʾ����ͬʱ���ŵ���Ƶ����



#pragma pack(1)


#define CP_VIDEO_FUNC_MANAGER_FIELDS																	\
		CP_FUSION_PLAYER_FUNC_MANAGER_FIELDS																	\
		cp_array_t						video_modules;		/*��Ƶģ���б�����ģ���ַָ��*/				\
		cp_mutex_t						vm_mutex;			/*��ʾ��Ƶģ�����*/							\


struct cp_video_func_manager_s
{
	CP_VIDEO_FUNC_MANAGER_FIELDS
};

#pragma pack()


cp_video_func_manager_t* create_video_func_manager
	(cp_module_manager_register_t *register_info, cp_app_t *app, cp_video_func_manager_info_t *info);
cp_int32_t destroy_video_func_manager(cp_app_t *app, cp_video_func_manager_t* manager);



#endif


