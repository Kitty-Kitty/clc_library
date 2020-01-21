/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/

#ifndef	_CP_RENDER_FUNC_MANAGER_INCLUDE_H_
#define _CP_RENDER_FUNC_MANAGER_INCLUDE_H_

#include "cp_render_func_core.h"




//typedef struct cp_render_func_manager_s						cp_render_func_manager_t;

#define		CP_RENDER_FUNC_MAX_NUMBER							128				//表示允许同时播放的视频数量



#pragma pack(1)


#define CP_RENDER_FUNC_MANAGER_FIELDS																	\
		CP_FUNC_MANAGER_FIELDS																			\
		cp_array_t						render_modules;		/*视频模块列表，保存模块地址指针*/				\
		cp_mutex_t						vm_mutex;			/*表示视频模块管理*/							\


struct cp_render_func_manager_s
{
	CP_RENDER_FUNC_MANAGER_FIELDS
};

#pragma pack()


cp_render_func_manager_t* create_render_func_manager
	(cp_module_manager_register_t *register_info, cp_app_t *app, cp_render_func_manager_info_t *info);
cp_int32_t destroy_render_func_manager(cp_app_t *app, cp_render_func_manager_t* manager);



#endif


