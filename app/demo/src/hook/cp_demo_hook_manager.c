/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/
#include "cp_demo_hook_manager.h"
#include "cp_include.h"



//定义模块注册管理器的最大数量
#define CP_LIBRARY_CSS_HOOK_MODULE_MANAGER_MAX_SIZE				8

//定义模块注册器的最大数量
#define CP_LIBRARY_CSS_HOOK_MODULE_MAX_SIZE						128


//模块创建接口，表示创建一个模块
cp_int32_t init_demo_hook_manager(cp_demo_hook_manager_t *manager, const cp_demo_hook_manager_info_t *info);
//模块打开运行接口，在模块init之后，会被调用
cp_int32_t start_demo_hook_manager(cp_demo_hook_manager_t *manager, const cp_demo_hook_manager_info_t *info);
//读取模块数据，flag为读取模式的扩展标志。默认为0，其他为预留
cp_int32_t stop_demo_hook_manager(cp_demo_hook_manager_t *manager);
//设置模块参数
cp_int32_t ctrl_demo_hook_manager(cp_demo_hook_manager_t *manager, cp_int32_t optname, const cp_void_t* optval);
//模块创建接口，表示创建一个模块
cp_demo_hook_t* create_demo_hook_module(cp_demo_hook_manager_t *manager, const cp_demo_hook_info_t *info);
//模块查询接口，表示从管理器中查询一个模块
cp_demo_hook_t* get_demo_hook_module(cp_demo_hook_manager_t *manager, const cp_demo_hook_info_t *info);
//写模块数据，flag为写模式的扩展标志。默认为0，其他为预留
cp_int32_t register_demo_hook_module(cp_demo_hook_manager_t *manager, cp_demo_hook_t *demo_hook);
//关闭模块
cp_int32_t cancel_demo_hook_module(cp_demo_hook_manager_t *manager, cp_demo_hook_t *demo_hook);
//退出模块
cp_int32_t destroy_demo_hook_module(cp_demo_hook_manager_t *manager, cp_demo_hook_t *demo_hook);
//设置模块参数
cp_int32_t ctrl_demo_hook_module(cp_demo_hook_manager_t *manager, cp_demo_hook_t *demo_hook, cp_int32_t optname, const cp_void_t* optval);
//处理模块的各种依赖关系
cp_int32_t demo_hook_dependent(cp_demo_hook_manager_t *manager);



cp_demo_hook_manager_t* create_demo_hook_manager(cp_module_manager_register_t *register_info, cp_app_t *app, cp_demo_hook_manager_info_t *info)
{
	cp_demo_hook_manager_t			*tmp_manager = CP_NULL;


	if (!app || !info) {
		return tmp_manager;
	}

	//配置一个manager 内存空间
	CP_MODULE_MANAGER_MALLOC(tmp_manager, app, cp_demo_hook_manager_t);

	if (tmp_manager) {
		//配置manager信息
		tmp_manager->register_info = *register_info;
		//为设备分配空间
		tmp_manager->pool = cp_create_pool(app);
		//设置各种操作句柄
		CP_MODULE_MANAGER_SET_HANDLERS(tmp_manager, demo_hook);
		//初始化模块中的所有队列
		cp_manager_create_register_memory(tmp_manager, CP_LIBRARY_MODULE_MANAGER_MAX_SIZE,
			CP_LIBRARY_CSS_HOOK_MODULE_MANAGER_MAX_SIZE, CP_LIBRARY_CSS_HOOK_MODULE_MAX_SIZE);
	}

	return tmp_manager;
}

cp_int32_t destroy_demo_hook_manager(cp_app_t *app, cp_demo_hook_manager_t* manager)
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
cp_int32_t init_demo_hook_manager(cp_demo_hook_manager_t *manager, const cp_demo_hook_manager_info_t *info)
{
	cp_int32_t								ret_int = 0;
	cp_int32_t								i = 0;
	cp_demo_hook_t							*hook;
	cp_demo_hook_register_t					*tmp_chr = CP_NULL;
	cp_demo_hook_info_t						tmp_hook_info;
	cp_char_t								tmp_buf[CP_APP_DEFAULT_BUFFER_LENGTH] = { 0, };


	//设置子模块管理器的module注册信息
	CP_MODULE_DEPENDENT(demo_hook, manager->app);

	//初始化handle模块内存空间
	manager->hook_array = cp_palloc(manager->pool, cp_sizeof(cp_demo_hook_t*) *
		CP_GET_LIBRARY_SUB_MODULE_TYPE(cp_css_rtp_hook_type_end));
	if (!manager->hook_array) {
		return -1;
	}
	cp_memset(&tmp_hook_info, 0, cp_sizeof(tmp_hook_info));
	cp_memset(manager->hook_array, 0, cp_sizeof(cp_demo_hook_t*) * 
		CP_GET_LIBRARY_SUB_MODULE_TYPE(cp_css_rtp_hook_type_end));
	//创建各个hook模块
	for (i = 0; i < (cp_int32_t)cp_array_max_size(&manager->module_register); i++) {
		tmp_chr = *(cp_demo_hook_register_t**)cp_array_get(&manager->module_register, i);
		if (!tmp_chr) {
			continue;
		}
		//判断类型是否合法
		if (tmp_chr->type < 0 ||
			tmp_chr->type > cp_css_rtp_hook_type_end) {
			cp_log_error(manager->logger, "create %s error. unknow handle type[%d].",
				cp_print_module_register_info(&hook->register_info, tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH),
				tmp_chr->type);
			continue;
		}
		//如果指定类型的handle已经存在，则不做处理
		//系统默认取第一个handle做为有效handle
		if (manager->hook_array[CP_GET_LIBRARY_SUB_MODULE_TYPE(tmp_chr->type)]) {
			cp_log_error(manager->logger, "create %s error. handle exist.",
				cp_print_module_register_info(tmp_chr, tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH));
			continue;
		}
		//根据注册内容创建一个handle
		hook = (cp_demo_hook_t*)cp_create_module(tmp_chr, manager, info);
		//按照模块位置存储
		if (hook) {
			manager->hook_array[CP_GET_LIBRARY_SUB_MODULE_TYPE(hook->register_info.type)] = (cp_hook_t *)hook;
		} else {
			cp_log_error(manager->logger, "create %s error.", 
				cp_print_module_register_info(tmp_chr, tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH));
		}
	}
	//初始化各个hook模块
	for (i = 0; i < CP_GET_LIBRARY_SUB_MODULE_TYPE(cp_css_rtp_hook_type_end); i++) {
		if (manager->hook_array[i]) {
			ret_int = cp_init_module(manager->hook_array[i], &tmp_hook_info);
			if (ret_int) {
				cp_log_error(manager->logger, "init %s error. handle init error.",
					cp_print_module_register_info(&manager->hook_array[i]->register_info, tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH));
				//初始化失败，则销毁模块
				cp_destroy_module(manager, manager->hook_array[i]);
				//将位置清空
				manager->hook_array[i] = CP_NULL;
			}
		}
	}
	//处理各个模块的依赖关系
	ret_int = demo_hook_dependent(manager);
	return 0;
}

//模块打开运行接口，在模块init之后，会被调用
cp_int32_t start_demo_hook_manager(cp_demo_hook_manager_t *manager, const cp_demo_hook_manager_info_t *info)
{
	return 0;
}

//读取模块数据，flag为读取模式的扩展标志。默认为0，其他为预留
cp_int32_t stop_demo_hook_manager(cp_demo_hook_manager_t *manager)
{
	return 0;
}

//设置模块参数
cp_int32_t ctrl_demo_hook_manager(cp_demo_hook_manager_t *manager, cp_int32_t optname, const cp_void_t* optval)
{

	return 0;
}

//模块创建接口，表示创建一个模块
cp_demo_hook_t* create_demo_hook_module(cp_demo_hook_manager_t *manager, const cp_demo_hook_info_t *info)
{
	return CP_NULL;
}

//模块查询接口，表示从管理器中查询一个模块
cp_demo_hook_t* get_demo_hook_module(cp_demo_hook_manager_t *manager, const cp_demo_hook_info_t *info)
{
	cp_queue_t								*modules;
	cp_queue_t								*current;
	cp_demo_hook_t							*tmp_hook;


	//处理filter manager部分内容
	modules = &manager->modules;
	for (current = cp_queue_next(modules); current != modules;
		current = cp_queue_next(current)) {
		tmp_hook = cp_queue_data(current, cp_demo_hook_t, queue);
		if (tmp_hook->command == info->command) {
			return tmp_hook;
		}
	}
	return CP_NULL;
}

//写模块数据，flag为写模式的扩展标志。默认为0，其他为预留
cp_int32_t register_demo_hook_module(cp_demo_hook_manager_t *manager, cp_demo_hook_t *module)
{
	return 0;
}

//关闭模块
cp_int32_t cancel_demo_hook_module(cp_demo_hook_manager_t *manager, cp_demo_hook_t *module)
{
	return 0;
}

//退出模块
cp_int32_t destroy_demo_hook_module(cp_demo_hook_manager_t *manager, cp_demo_hook_t *module)
{
	return 0;
}
//设置模块参数
cp_int32_t ctrl_demo_hook_module(cp_demo_hook_manager_t *manager, cp_demo_hook_t *module, cp_int32_t optname, const cp_void_t* optval)
{
	return 0;
}
//处理模块的各种依赖关系
cp_int32_t demo_hook_dependent(cp_demo_hook_manager_t *manager)
{
	//处理入口函数的依赖关系
	cp_demo_hook_entry_dependent(manager);

	//处理正确返回的依赖关系
	cp_demo_hook_right_dependent(manager);

	//处理错误返回的依赖关系
	cp_demo_hook_error_dependent(manager);

	return 0;
}



