/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/
#include "cp_thread_core.h"
#include "cp_include.h"





cp_thread_t* cp_create_thread(const cp_app_t *app, cp_thread_cb entry, cp_void_t* arg)
{
	cp_thread_t						*tmp_thread = CP_NULL;
	cp_thread_manager_t				*tmp_manager = CP_NULL;
	cp_module_register_t			*tmp_module_register = CP_NULL;

	cp_thread_info_t				tmp_thread_info;
	cp_module_manager_info_t		tmp_module_manager_info;



	CP_MODULE_MANAGER_INFO_SET_TYPE(&tmp_module_manager_info, CP_MODULE_MANAGER_TYPE_THREAD(1));
	tmp_manager = (cp_thread_manager_t*)cp_get_manager(app, &tmp_module_manager_info);
	if (!tmp_manager) {
		return CP_NULL;
	}

	cp_memset(&tmp_thread_info, 0, cp_sizeof(tmp_thread_info));

	tmp_thread_info.thread_cb = entry;
	tmp_thread_info.args = arg;

	//这里先获取模块的注册器
	tmp_module_register = cp_manager_get_module_register(tmp_manager, CP_MODULE_TYPE_THREAD(1));
	if (!tmp_module_register) {
		return CP_NULL;
	}

	//通过模块的注册器，来创建一个模块
	tmp_thread = (cp_thread_t *)cp_create_module(tmp_module_register, tmp_manager, &tmp_thread_info);

	return tmp_thread;
}

cp_int32_t cp_destroy_thread(cp_thread_t *tid)
{
	cp_thread_manager_t				*tmp_manager = CP_NULL;
	cp_module_manager_info_t		tmp_module_manager_info;



	CP_MODULE_MANAGER_INFO_SET_TYPE(&tmp_module_manager_info, cp_module_manager_type_thread);
	tmp_manager = (cp_thread_manager_t*)cp_get_manager(tid->manager->app, &tmp_module_manager_info);

	return cp_destroy_module((cp_module_manager_t *)tmp_manager, (cp_module_t *)tid);
}

// cp_thread_t cp_thread_self()
// {
// 	cp_thread_t						tmp_tid;
// 
// 	return tmp_tid;
// }

cp_int32_t cp_thread_join(cp_thread_t *tid)
{
	return tid->set_option((cp_module_t *)tid, cp_thread_set_option_join, CP_NULL);
}

cp_int32_t cp_thread_equal(const cp_thread_t *t1, const cp_thread_t *t2)
{
	return 0;
}

