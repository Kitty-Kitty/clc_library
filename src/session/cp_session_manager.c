/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/
#include "cp_include.h"
#include "cp_session_manager.h"




extern cp_module_register_t  session_module_manager_list[];
extern cp_int32_t session_module_manager_list_size;
extern cp_module_register_t  session_module_list[];
extern cp_int32_t session_module_list_size;




//模块创建接口，表示创建一个模块
cp_int32_t init_session_manager(cp_session_manager_t *manager, const cp_session_manager_info_t *info);
//模块打开运行接口，在模块init之后，会被调用
cp_int32_t start_session_manager(cp_session_manager_t *manager, const cp_session_manager_info_t *info);
//读取模块数据，flag为读取模式的扩展标志。默认为0，其他为预留
cp_int32_t stop_session_manager(cp_session_manager_t *manager);
//设置模块参数
cp_int32_t ctrl_session_manager(cp_session_manager_t *manager, cp_int32_t optname, const cp_void_t* optval);
//模块创建接口，表示创建一个模块
cp_session_t* create_session_module(cp_session_manager_t *manager, const cp_session_info_t *info);
//模块查询接口，表示从管理器中查询一个模块
cp_session_t* get_session_module(cp_session_manager_t *manager, const cp_session_info_t *info);
//写模块数据，flag为写模式的扩展标志。默认为0，其他为预留
cp_int32_t register_session_module(cp_session_manager_t *manager, cp_session_t *session);
//关闭模块
cp_int32_t cancel_session_module(cp_session_manager_t *manager, cp_session_t *session);
//退出模块
cp_int32_t destroy_session_module(cp_session_manager_t *manager, cp_session_t *session);
//设置模块参数
cp_int32_t ctrl_session_module(cp_session_manager_t *manager, cp_session_t *session, cp_int32_t optname, const cp_void_t* optval);




cp_session_manager_t* create_session_manager(cp_module_manager_register_t *register_info, cp_app_t *app, cp_session_manager_info_t *info)
{
	cp_session_manager_t			*tmp_manager = CP_NULL;
	cp_module_manager_register_t *tmp_register_info = CP_NULL;



	if (!app || !info) {
		return tmp_manager;
	}

	//配置一个manager 内存空间
	CP_MODULE_MANAGER_MALLOC(tmp_manager, app, cp_session_manager_t);

	if (tmp_manager) {
		//配置manager信息
		tmp_manager->register_info = *register_info;

		//为设备分配空间
		tmp_manager->pool = cp_create_pool(app);

		//设置各种操作句柄
		CP_MODULE_MANAGER_SET_HANDLERS(tmp_manager, session);

		//初始化模块中的所有队列
		cp_manager_create_register_memory(tmp_manager, CP_LIBRARY_MODULE_MANAGER_MAX_SIZE,
			CP_LIBRARY_MODULE_MANAGER_MAX_SIZE, CP_LIBRARY_MODULE_MAX_SIZE);
	}

	return tmp_manager;
}

cp_int32_t destroy_session_manager(cp_app_t *app, cp_session_manager_t* manager)
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
cp_int32_t init_session_manager(cp_session_manager_t *manager, const cp_session_manager_info_t *info)
{
	return 0;
}
//模块打开运行接口，在模块init之后，会被调用
cp_int32_t start_session_manager(cp_session_manager_t *manager, const cp_session_manager_info_t *info)
{
	return 0;
}
//读取模块数据，flag为读取模式的扩展标志。默认为0，其他为预留
cp_int32_t stop_session_manager(cp_session_manager_t *manager)
{
	return 0;
}
//设置模块参数
cp_int32_t ctrl_session_manager(cp_session_manager_t *manager, cp_int32_t optname, const cp_void_t* optval)
{
	return 0;
}
//模块创建接口，表示创建一个模块
cp_session_t* create_session_module(cp_session_manager_t *manager, const cp_session_info_t *info)
{
	return CP_NULL;
}
//模块查询接口，表示从管理器中查询一个模块
cp_session_t* get_session_module(cp_session_manager_t *manager, const cp_session_info_t *info)
{
	return CP_NULL;
}
//写模块数据，flag为写模式的扩展标志。默认为0，其他为预留
cp_int32_t register_session_module(cp_session_manager_t *manager, cp_session_t *module)
{
	return 0;
}
//关闭模块
cp_int32_t cancel_session_module(cp_session_manager_t *manager, cp_session_t *module)
{
	return 0;
}
//退出模块
cp_int32_t destroy_session_module(cp_session_manager_t *manager, cp_session_t *module)
{
	return 0;
}
//设置模块参数
cp_int32_t ctrl_session_module(cp_session_manager_t *manager, cp_session_t *module, cp_int32_t optname, const cp_void_t* optval)
{
	return 0;
}





