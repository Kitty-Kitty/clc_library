/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/
#include "cp_include.h"
#include "cp_player_filter_manager.h"





//模块创建接口，表示创建一个模块
cp_int32_t init_player_filter_manager(cp_player_filter_manager_t *manager, const cp_player_filter_manager_info_t *info);
//模块打开运行接口，在模块init之后，会被调用
cp_int32_t start_player_filter_manager(cp_player_filter_manager_t *manager, const cp_player_filter_manager_info_t *info);
//读取模块数据，flag为读取模式的扩展标志。默认为0，其他为预留
cp_int32_t stop_player_filter_manager(cp_player_filter_manager_t *manager);
//设置模块参数
cp_int32_t ctrl_player_filter_manager(cp_player_filter_manager_t *manager, cp_int32_t optname, const cp_void_t* optval);
//模块创建接口，表示创建一个模块
cp_player_filter_t* create_player_filter_module(cp_player_filter_manager_t *manager, const cp_player_filter_info_t *info);
//模块查询接口
cp_player_filter_t* get_player_filter_module(cp_player_filter_manager_t *manager, const cp_player_filter_info_t *info);
//写模块数据，flag为写模式的扩展标志。默认为0，其他为预留
cp_int32_t register_player_filter_module(cp_player_filter_manager_t *manager, cp_player_filter_t *func);
//关闭模块
cp_int32_t cancel_player_filter_module(cp_player_filter_manager_t *manager, cp_player_filter_t *func);
//退出模块
cp_int32_t destroy_player_filter_module(cp_player_filter_manager_t *manager, cp_player_filter_t *func);
//设置模块参数
cp_int32_t ctrl_player_filter_module(cp_player_filter_manager_t *manager, cp_player_filter_t *func, cp_int32_t optname, const cp_void_t* optval);




cp_player_filter_manager_t* create_player_filter_manager(cp_module_manager_register_t *register_info, cp_app_t *app, cp_player_filter_manager_info_t *info)
{
	cp_player_filter_manager_t			*tmp_manager = CP_NULL;


	if (!app || !info) {
		return tmp_manager;
	}

	//配置一个manager 内存空间
	CP_MODULE_MANAGER_MALLOC(tmp_manager, app, cp_player_filter_manager_t);

	if (tmp_manager) {
		//配置manager信息
		tmp_manager->register_info = *register_info;
		//为设备分配空间
		tmp_manager->pool = cp_create_pool(app);
		//设置各种操作句柄
		CP_MODULE_MANAGER_SET_HANDLERS(tmp_manager, player_filter);
		//初始化模块中的所有队列
		cp_manager_create_register_memory(tmp_manager, CP_LIBRARY_MODULE_MANAGER_MAX_SIZE,
			CP_LIBRARY_MODULE_MANAGER_MAX_SIZE, CP_LIBRARY_MODULE_MAX_SIZE);
	}

	return tmp_manager;
}

cp_int32_t destroy_player_filter_manager(cp_app_t *app, cp_player_filter_manager_t* manager)
{
	if (!manager) {
		return 0;
	}

	if (manager->pool) {
		cp_destroy_pool(manager->pool);
	}

	CP_MODULE_MANAGER_FREE(manager);

	return 0;
}


//模块创建接口，表示创建一个模块
cp_int32_t init_player_filter_manager(cp_player_filter_manager_t *manager, const cp_player_filter_manager_info_t *info)
{
	return 0;
}
//模块打开运行接口，在模块init之后，会被调用
cp_int32_t start_player_filter_manager(cp_player_filter_manager_t *manager, const cp_player_filter_manager_info_t *info)
{
	cp_int32_t							i = 0;
	cp_module_register_t				*tmp_module_register = CP_NULL;


	//根据模块注册器，创建各个模块
	for (i = 0; i < (cp_int32_t)cp_array_max_size(&manager->module_register); i++) {
		tmp_module_register = *(cp_module_register_t**)cp_array_get(&manager->module_register, i);
		if (!tmp_module_register) {
			continue;
		}
		cp_create_module(tmp_module_register, manager, info);
	}
	return 0;
}
//读取模块数据，flag为读取模式的扩展标志。默认为0，其他为预留
cp_int32_t stop_player_filter_manager(cp_player_filter_manager_t *manager)
{
	return 0;
}
//设置模块参数
cp_int32_t ctrl_player_filter_manager(cp_player_filter_manager_t *manager, cp_int32_t optname, const cp_void_t* optval)
{
	return 0;
}
//模块创建接口，表示创建一个模块
cp_player_filter_t* create_player_filter_module(cp_player_filter_manager_t *manager, const cp_player_filter_info_t *info)
{
	return (cp_player_filter_t*)cp_manager_create_module_by_register(manager, info);
}
//模块查询接口
cp_player_filter_t* get_player_filter_module(cp_player_filter_manager_t *manager, const cp_player_filter_info_t *info)
{
	cp_queue_t								*modules;
	cp_queue_t								*current;
	cp_player_filter_t						*filter;


	if (!manager || !info) {
		return CP_NULL;
	}

	//处理filter manager部分内容
	modules = &manager->modules;
	for (current = cp_queue_next(modules); current != modules;
		current = cp_queue_next(current)) {
		filter = (cp_player_filter_t*)cp_queue_data(current, cp_filter_t, queue);
		if (filter->register_info.type == info->type) {
			return filter;
		}
	}
	return CP_NULL;
}
//写模块数据，flag为写模式的扩展标志。默认为0，其他为预留
cp_int32_t register_player_filter_module(cp_player_filter_manager_t *manager, cp_player_filter_t *module)
{
	return 0;
}
//关闭模块
cp_int32_t cancel_player_filter_module(cp_player_filter_manager_t *manager, cp_player_filter_t *module)
{
	return 0;
}
//退出模块
cp_int32_t destroy_player_filter_module(cp_player_filter_manager_t *manager, cp_player_filter_t *module)
{
	return 0;
}
//设置模块参数
cp_int32_t ctrl_player_filter_module(cp_player_filter_manager_t *manager, cp_player_filter_t *module, cp_int32_t optname, const cp_void_t* optval)
{
	return 0;
}





