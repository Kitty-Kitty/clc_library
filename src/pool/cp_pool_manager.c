/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/
#include "cp_include.h"
#include "cp_pool_manager.h"




extern cp_module_register_t  pool_module_list[];




//模块创建接口，表示创建一个模块
cp_int32_t init_pool_manager(cp_pool_manager_t *manager, const cp_pool_manager_info_t *info);
//模块打开运行接口，在模块init之后，会被调用
cp_int32_t start_pool_manager(cp_pool_manager_t *manager, const cp_pool_manager_info_t *info);
//读取模块数据，flag为读取模式的扩展标志。默认为0，其他为预留
cp_int32_t stop_pool_manager(cp_pool_manager_t *manager);
//设置模块参数
cp_int32_t ctrl_pool_manager(cp_pool_manager_t *manager, cp_int32_t optname, const cp_void_t* optval);
//模块创建接口，表示创建一个模块
cp_pool_t* create_pool_module(cp_pool_manager_t *manager, const cp_pool_info_t *info);
//模块查询接口，表示从管理器中查询一个模块
cp_pool_t* get_pool_module(cp_pool_manager_t *manager, const cp_pool_info_t *info);
//写模块数据，flag为写模式的扩展标志。默认为0，其他为预留
cp_int32_t register_pool_module(cp_pool_manager_t *manager, cp_pool_t *pool);
//关闭模块
cp_int32_t cancel_pool_module(cp_pool_manager_t *manager, cp_pool_t *pool);
//退出模块
cp_int32_t destroy_pool_module(cp_pool_manager_t *manager, cp_pool_t *pool);
//设置模块参数
cp_int32_t ctrl_pool_module(cp_pool_manager_t *manager, cp_pool_t *pool, cp_int32_t optname, const cp_void_t* optval);




cp_pool_manager_t* create_pool_manager(cp_module_manager_register_t *register_info, cp_app_t *app, cp_pool_manager_info_t *info)
{
	cp_pool_manager_t				*tmp_manager = CP_NULL;
	cp_module_manager_register_t	*tmp_register_info = CP_NULL;
	cp_pool_info_t					tmp_pool_info;



	if (!app || !info) {
		return tmp_manager;
	}

	//配置一个manager 内存空间
	CP_MODULE_MANAGER_MALLOC(tmp_manager, app, cp_pool_manager_t);

	if (tmp_manager) {
		//配置manager信息
		tmp_manager->register_info = *register_info;

		cp_memset(&tmp_pool_info, 0, cp_sizeof(tmp_pool_info));
		tmp_pool_info.size = CP_APP_DEFAULT_BUFFER_LENGTH;

		//为设备分配空间
		//tmp_manager->pool = cp_create_pool(app);
		tmp_manager->pool = (cp_pool_t *)(pool_module_list[0].module_create(&pool_module_list[0],
			(cp_module_manager_t *)tmp_manager, (cp_module_info_t *)&tmp_pool_info));

		//设置各种操作句柄
		CP_MODULE_MANAGER_SET_HANDLERS(tmp_manager, pool);

		//初始化模块中的所有队列
		cp_manager_create_register_memory(tmp_manager, CP_LIBRARY_MODULE_MANAGER_MAX_SIZE,
			CP_LIBRARY_MODULE_MANAGER_MAX_SIZE, CP_LIBRARY_MODULE_MAX_SIZE);
	}

	return tmp_manager;
}

cp_int32_t destroy_pool_manager(cp_app_t *app, cp_pool_manager_t* manager)
{
	if (!manager) {
		return 0;
	}

	if (manager->pool) {
		pool_module_list[0].module_destroy((cp_module_manager_t *)manager, (cp_module_t *)(manager->pool));
	}

	CP_MODULE_MANAGER_FREE(manager);

	return 0;
}



//模块创建接口，表示创建一个模块
cp_int32_t init_pool_manager(cp_pool_manager_t *manager, const cp_pool_manager_info_t *info)
{
	cp_int32_t						ret_int = 0;


	//设置一个模块注册器
	ret_int = cp_manager_set_module_register(manager, pool_module_list, 1, cp_sizeof(cp_module_register_t*));
	if (ret_int) {
		return -1;
	}
	return 0;
}
//模块打开运行接口，在模块init之后，会被调用
cp_int32_t start_pool_manager(cp_pool_manager_t *manager, const cp_pool_manager_info_t *info)
{
	return 0;
}
//读取模块数据，flag为读取模式的扩展标志。默认为0，其他为预留
cp_int32_t stop_pool_manager(cp_pool_manager_t *manager)
{
	return 0;
}
//设置模块参数
cp_int32_t ctrl_pool_manager(cp_pool_manager_t *manager, cp_int32_t optname, const cp_void_t* optval)
{
	return 0;
}
//模块创建接口，表示创建一个模块
cp_pool_t* create_pool_module(cp_pool_manager_t *manager, const cp_pool_info_t *info)
{
	return CP_NULL;
}
//模块查询接口，表示从管理器中查询一个模块
cp_pool_t* get_pool_module(cp_pool_manager_t *manager, const cp_pool_info_t *info)
{
	return CP_NULL;
}
//写模块数据，flag为写模式的扩展标志。默认为0，其他为预留
cp_int32_t register_pool_module(cp_pool_manager_t *manager, cp_pool_t *module)
{
	return 0;
}
//关闭模块
cp_int32_t cancel_pool_module(cp_pool_manager_t *manager, cp_pool_t *module)
{
	return 0;
}
//退出模块
cp_int32_t destroy_pool_module(cp_pool_manager_t *manager, cp_pool_t *module)
{
	return 0;
}
//设置模块参数
cp_int32_t ctrl_pool_module(cp_pool_manager_t *manager, cp_pool_t *module, cp_int32_t optname, const cp_void_t* optval)
{
	switch (optname)
	{
	case CP_POOL_OPTION_ALLOC:
	case CP_POOL_OPTION_FREE:
	{
		return cp_manager_ctrl_module(manager, module, optname, optval);
	}
	break;
	default:
		return -1;
		break;
	}
	return 0;
}





