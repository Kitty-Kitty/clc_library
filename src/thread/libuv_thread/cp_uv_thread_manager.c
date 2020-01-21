
/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/
#include "cp_uv_thread_manager.h"
#include "cp_include.h"




//模块创建接口，表示创建一个模块
cp_int32_t init_uv_thread_manager(cp_uv_thread_manager_t *manager, const cp_uv_thread_manager_info_t *info);
//模块打开运行接口，在模块init之后，会被调用
cp_int32_t start_uv_thread_manager(cp_uv_thread_manager_t *manager, const cp_uv_thread_manager_info_t *info);
//读取模块数据，flag为读取模式的扩展标志。默认为0，其他为预留
cp_int32_t stop_uv_thread_manager(cp_uv_thread_manager_t *manager);
//设置模块参数
cp_int32_t ctrl_uv_thread_manager(cp_uv_thread_manager_t *manager, cp_int32_t optname, const cp_void_t* optval);
//模块创建接口，表示创建一个模块
cp_thread_t* create_uv_thread_module(cp_uv_thread_manager_t *manager, const cp_thread_info_t *info);
//模块查询接口，表示从管理器中查询一个模块
cp_thread_t* get_uv_thread_module(cp_uv_thread_manager_t *manager, const cp_thread_info_t *info);
//写模块数据，flag为写模式的扩展标志。默认为0，其他为预留
cp_int32_t register_uv_thread_module(cp_uv_thread_manager_t *manager, cp_thread_t *thread);
//关闭模块
cp_int32_t cancel_uv_thread_module(cp_uv_thread_manager_t *manager, cp_thread_t *thread);
//退出模块
cp_int32_t destroy_uv_thread_module(cp_uv_thread_manager_t *manager, cp_thread_t *thread);
//设置模块参数
cp_int32_t ctrl_uv_thread_module(cp_uv_thread_manager_t *manager, cp_thread_t *thread, cp_int32_t optname, const cp_void_t* optval);




cp_uv_thread_manager_t* create_uv_thread_manager(cp_module_manager_register_t *register_info, cp_app_t *app, cp_uv_thread_manager_info_t *info)
{
	cp_uv_thread_manager_t			*tmp_manager = CP_NULL;


	if (!app || !info) {
		return tmp_manager;
	}

	//配置一个manager 内存空间
	CP_MODULE_MANAGER_MALLOC(tmp_manager, app, cp_uv_thread_manager_t);

	if (tmp_manager) {
		//配置manager信息
		tmp_manager->register_info = *register_info;
		//为设备分配空间
		tmp_manager->pool = cp_create_pool(app);
		//设置各种操作句柄
		CP_MODULE_MANAGER_SET_HANDLERS(tmp_manager, uv_thread);
		//初始化模块中的所有队列
		cp_manager_create_register_memory(tmp_manager, CP_LIBRARY_MODULE_MANAGER_MAX_SIZE,
			CP_LIBRARY_MODULE_MANAGER_MAX_SIZE, CP_LIBRARY_MODULE_MAX_SIZE);
	}

	return tmp_manager;
}

cp_int32_t destroy_uv_thread_manager(cp_app_t *app, cp_uv_thread_manager_t* manager)
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
cp_int32_t init_uv_thread_manager(cp_uv_thread_manager_t *manager, const cp_uv_thread_manager_info_t *info)
{
	//设置子模块管理器的module注册信息
	CP_MODULE_DEPENDENT(thread, manager->app);
	return 0;
}
//模块打开运行接口，在模块init之后，会被调用
cp_int32_t start_uv_thread_manager(cp_uv_thread_manager_t *manager, const cp_uv_thread_manager_info_t *info)
{
	return 0;
}
//读取模块数据，flag为读取模式的扩展标志。默认为0，其他为预留
cp_int32_t stop_uv_thread_manager(cp_uv_thread_manager_t *manager)
{
	return 0;
}
//设置模块参数
cp_int32_t ctrl_uv_thread_manager(cp_uv_thread_manager_t *manager, cp_int32_t optname, const cp_void_t* optval)
{
	return 0;
}
//模块创建接口，表示创建一个模块
cp_thread_t* create_uv_thread_module(cp_uv_thread_manager_t *manager, const cp_thread_info_t *info)
{
	return CP_NULL;
}
//模块查询接口，表示从管理器中查询一个模块
cp_thread_t* get_uv_thread_module(cp_uv_thread_manager_t *manager, const cp_thread_info_t *info)
{
	return CP_NULL;
}
//写模块数据，flag为写模式的扩展标志。默认为0，其他为预留
cp_int32_t register_uv_thread_module(cp_uv_thread_manager_t *manager, cp_thread_t *module)
{
	return 0;
}
//关闭模块
cp_int32_t cancel_uv_thread_module(cp_uv_thread_manager_t *manager, cp_thread_t *module)
{
	return 0;
}
//退出模块
cp_int32_t destroy_uv_thread_module(cp_uv_thread_manager_t *manager, cp_thread_t *module)
{
	return 0;
}
//设置模块参数
cp_int32_t ctrl_uv_thread_module(cp_uv_thread_manager_t *manager, cp_thread_t *module, cp_int32_t optname, const cp_void_t* optval)
{
	return 0;
}

