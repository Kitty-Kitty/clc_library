/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/
#include "cp_include.h"
#include "cp_dev_manager.h"





//模块创建接口，表示创建一个模块
cp_int32_t init_dev_manager(cp_dev_manager_t *manager, const cp_dev_manager_info_t *info);
//模块打开运行接口，在模块init之后，会被调用
cp_int32_t start_dev_manager(cp_dev_manager_t *manager, const cp_dev_manager_info_t *info);
//读取模块数据，flag为读取模式的扩展标志。默认为0，其他为预留
cp_int32_t stop_dev_manager(cp_dev_manager_t *manager);
//设置模块参数
cp_int32_t ctrl_dev_manager(cp_dev_manager_t *manager, cp_int32_t optname, const cp_void_t* optval);
//模块创建接口，表示创建一个模块
cp_dev_t* create_dev_module(cp_dev_manager_t *manager, const cp_dev_info_t *info);
//模块查询接口
cp_dev_t* get_dev_module(cp_dev_manager_t *manager, const cp_dev_info_t *info);
//写模块数据，flag为写模式的扩展标志。默认为0，其他为预留
cp_int32_t register_dev_module(cp_dev_manager_t *manager, cp_dev_t *dev);
//关闭模块
cp_int32_t cancel_dev_module(cp_dev_manager_t *manager, cp_dev_t *dev);
//退出模块
cp_int32_t destroy_dev_module(cp_dev_manager_t *manager, cp_dev_t *dev);
//设置模块参数
cp_int32_t ctrl_dev_module(cp_dev_manager_t *manager, cp_dev_t *dev, cp_int32_t optname, const cp_void_t* optval);




cp_dev_manager_t* create_dev_manager(cp_module_manager_register_t *register_info, cp_app_t *app, cp_dev_manager_info_t *info)
{
	cp_dev_manager_t			*tmp_manager = CP_NULL;
	cp_module_manager_register_t *tmp_register_info = CP_NULL;



	if (!app || !info) {
		return tmp_manager;
	}

	//配置一个manager 内存空间
	CP_MODULE_MANAGER_MALLOC(tmp_manager, app, cp_dev_manager_t);

	if (tmp_manager) {
		//配置manager信息
		tmp_manager->register_info = *register_info;

		//为设备分配空间
		tmp_manager->pool = cp_create_pool(app);

		//设置各种操作句柄
		CP_MODULE_MANAGER_SET_HANDLERS(tmp_manager, dev);

		//初始化模块中的所有队列
		cp_manager_create_register_memory(tmp_manager, CP_LIBRARY_MODULE_MANAGER_MAX_SIZE,
			CP_LIBRARY_MODULE_MANAGER_MAX_SIZE, CP_LIBRARY_MODULE_MAX_SIZE);
	}

	return tmp_manager;
}

cp_int32_t destroy_dev_manager(cp_app_t *app, cp_dev_manager_t* manager)
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
cp_int32_t init_dev_manager(cp_dev_manager_t *manager, const cp_dev_manager_info_t *info)
{
	return 0;
}
//模块打开运行接口，在模块init之后，会被调用
cp_int32_t start_dev_manager(cp_dev_manager_t *manager, const cp_dev_manager_info_t *info)
{
	return 0;
}
//读取模块数据，flag为读取模式的扩展标志。默认为0，其他为预留
cp_int32_t stop_dev_manager(cp_dev_manager_t *manager)
{
	return 0;
}
//设置模块参数
cp_int32_t ctrl_dev_manager(cp_dev_manager_t *manager, cp_int32_t optname, const cp_void_t* optval)
{
	return 0;
}
//模块创建接口，表示创建一个模块
cp_dev_t* create_dev_module(cp_dev_manager_t *manager, const cp_dev_info_t *info)
{
	return CP_NULL;
}
//模块查询接口
cp_dev_t* get_dev_module(cp_dev_manager_t *manager, const cp_dev_info_t *info)
{
	return CP_NULL;
}
//写模块数据，flag为写模式的扩展标志。默认为0，其他为预留
cp_int32_t register_dev_module(cp_dev_manager_t *manager, cp_dev_t *module)
{
	return 0;
}
//关闭模块
cp_int32_t cancel_dev_module(cp_dev_manager_t *manager, cp_dev_t *module)
{
	return 0;
}
//退出模块
cp_int32_t destroy_dev_module(cp_dev_manager_t *manager, cp_dev_t *module)
{
	return 0;
}
//设置模块参数
cp_int32_t ctrl_dev_module(cp_dev_manager_t *manager, cp_dev_t *module, cp_int32_t optname, const cp_void_t* optval)
{
	return 0;
}





