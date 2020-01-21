/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/
#include "cp_include.h"
#include "cp_player_func_manager.h"




extern cp_module_register_t  func_module_manager_list[];
extern cp_int32_t func_module_manager_list_size;
extern cp_module_register_t  func_module_list[];
extern cp_int32_t func_module_list_size;




//模块初始化接口，在模块create之后，会被调用
cp_int32_t init_player_func_manager(cp_player_func_manager_t *manager, const cp_player_func_manager_info_t *info);
//模块打开运行接口，在模块init之后，会被调用
cp_int32_t start_player_func_manager(cp_player_func_manager_t *manager, const cp_player_func_manager_info_t *info);
//读取模块数据，flag为读取模式的扩展标志。默认为0，其他为预留
cp_int32_t stop_player_func_manager(cp_player_func_manager_t *manager);
//设置模块参数
cp_int32_t ctrl_player_func_manager(cp_player_func_manager_t *manager, cp_int32_t optname, const cp_void_t* optval);
//模块初始化接口，在模块create之后，会被调用
cp_player_func_t* create_player_func_module(cp_player_func_manager_t *manager, const cp_player_func_info_t *info);
//模块查询接口，表示从管理器中查询一个模块
cp_player_func_t* get_player_func_module(cp_player_func_manager_t *manager, const cp_player_func_info_t *info);
//写模块数据，flag为写模式的扩展标志。默认为0，其他为预留
cp_int32_t register_player_func_module(cp_player_func_manager_t *manager, cp_player_func_t *func);
//关闭模块
cp_int32_t cancel_player_func_module(cp_player_func_manager_t *manager, cp_player_func_t *func);
//退出模块
cp_int32_t destory_player_func_module(cp_player_func_manager_t *manager, cp_player_func_t *func);
//设置模块参数
cp_int32_t ctrl_player_func_module(cp_player_func_manager_t *manager, cp_player_func_t *func, cp_int32_t optname, const cp_void_t* optval);




cp_player_func_manager_t* create_player_func_manager(cp_module_manager_register_t *register_info, cp_app_t *app, cp_player_func_manager_info_t *info)
{
	cp_player_func_manager_t			*tmp_manager = CP_NULL;


	if (!app || !info) {
		return tmp_manager;
	}

	//配置一个manager 内存空间
	CP_MODULE_MANAGER_MALLOC(tmp_manager, app, cp_player_func_manager_t);

	if (tmp_manager) {
		//配置manager信息
		tmp_manager->register_info = *register_info;
		//为设备分配空间
		tmp_manager->pool = cp_create_pool();
		//设置各种操作句柄
		CP_MODULE_MANAGER_SET_HANDLERS(tmp_manager, player_func);
		//设置模块管理器的module注册信息
		CP_MODULE_MANAGER_SET_REGISTER(tmp_manager, func_module_list, func_module_list_size);
	}
	return tmp_manager;
}

cp_int32_t destory_player_func_manager(cp_app_t *app, cp_player_func_manager_t* manager)
{
	if (manager) {
		cp_free(manager);
	}
	return 0;
}



//模块初始化接口，在模块create之后，会被调用
cp_int32_t init_player_func_manager(cp_player_func_manager_t *manager, const cp_player_func_manager_info_t *info)
{
	cp_int32_t						i = 0;


	for (i = 0; i < func_module_list_size; i++) {
		cp_create_module(&func_module_list[i], manager, info);
	}
	return 0;
}
//模块打开运行接口，在模块init之后，会被调用
cp_int32_t start_player_func_manager(cp_player_func_manager_t *manager, const cp_player_func_manager_info_t *info)
{
	return 0;
}
//读取模块数据，flag为读取模式的扩展标志。默认为0，其他为预留
cp_int32_t stop_player_func_manager(cp_player_func_manager_t *manager)
{
	return 0;
}
//设置模块参数
cp_int32_t ctrl_player_func_manager(cp_player_func_manager_t *manager, cp_int32_t optname, const cp_void_t* optval)
{
	return 0;
}
//模块初始化接口，在模块create之后，会被调用
cp_player_func_t* create_player_func_module(cp_player_func_manager_t *manager, const cp_player_func_info_t *info)
{
	return CP_NULL;
}
//模块查询接口，表示从管理器中查询一个模块
cp_player_func_t* get_player_func_module(cp_player_func_manager_t *manager, const cp_player_func_info_t *info)
{
	return CP_NULL;
}
//写模块数据，flag为写模式的扩展标志。默认为0，其他为预留
cp_int32_t register_player_func_module(cp_player_func_manager_t *manager, cp_player_func_t *module)
{
	return 0;
}
//关闭模块
cp_int32_t cancel_player_func_module(cp_player_func_manager_t *manager, cp_player_func_t *module)
{
	return 0;
}
//退出模块
cp_int32_t destory_player_func_module(cp_player_func_manager_t *manager, cp_player_func_t *module)
{
	return 0;
}
//设置模块参数
cp_int32_t ctrl_player_func_module(cp_player_func_manager_t *manager, cp_player_func_t *module, cp_int32_t optname, const cp_void_t* optval)
{
	return 0;
}





