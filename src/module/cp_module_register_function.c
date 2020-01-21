/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-08-09

Description:

**************************************************************************/

#include "cp_include.h"
#include "cp_module_register_function.h"





/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: cp_module_register
*
* 函数说明: 将模块注册到模块管理器中
*
* 参    数: cp_module_register_t * register_info					[in]参数说明
* 参    数: cp_module_manager_t * manager						[in]参数说明
*
* 返 回 值: cp_int32_t
*           0  : 成功 
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2016-08-09 11:24:37
******************************************************************************************************/
cp_int32_t cp_module_register(cp_module_register_t *register_info, cp_module_manager_t *manager)
{
	return 0;
}

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: cp_module_unregister
*
* 函数说明: 将模块从模块管理器中取消注册
*
* 参    数: cp_module_register_t * register_info						[in]参数说明
* 参    数: cp_module_manager_t * manager						[in]参数说明
*
* 返 回 值: cp_int32_t
*           0  : 成功 
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2016-08-09 11:24:38
******************************************************************************************************/
cp_int32_t cp_module_unregister(cp_module_register_t *register_info, cp_module_manager_t *manager)
{
	return 0;
}

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: cp_module_register_set_option
*
* 函数说明: 更新模块注册信息
*
* 参    数: cp_module_register_t * register_info						[in]参数说明
* 参    数: cp_int32_t optname						[in]参数说明
* 参    数: const cp_void_t * optval						[in]参数说明
*
* 返 回 值: cp_int32_t
*           0  : 成功 
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2016-08-09 11:24:41
******************************************************************************************************/
cp_int32_t cp_module_register_set_option(cp_module_register_t *register_info, cp_int32_t optname, const cp_void_t* optval)
{
	return 0;
}

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: cp_module_register_get_option
*
* 函数说明: 获取模块注册信息
*
* 参    数: cp_module_register_t * register_info						[in]参数说明
* 参    数: cp_int32_t optname						[in]参数说明
* 参    数: cp_void_t * optval						[in]参数说明
*
* 返 回 值: cp_int32_t
*           0  : 成功 
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2016-08-09 11:24:43
******************************************************************************************************/
cp_int32_t cp_module_register_get_option(cp_module_register_t *register_info, cp_int32_t optname, cp_void_t* optval)
{
	return 0;
}








//主要初始化各个模块的管理器内容空间大小
cp_int32_t _manager_create_register_memory(cp_module_manager_t *manager, cp_int32_t manager_register_size,
	cp_int32_t manager_size, cp_int32_t module_register_size)
{
	cp_module_manager_register_t**				tmp_mmr = CP_NULL;
	cp_module_register_t**						tmp_mr = CP_NULL;
	cp_module_manager_t**						tmp_mm = CP_NULL;
	cp_char_t							tmp_buf[CP_APP_DEFAULT_BUFFER_LENGTH] = { 0, };



	if (!manager->pool) {
		cp_log_error(manager->app->logger, "create register memory %s error! manager[%p] pool is null!",
			cp_print_module_register_info(&(manager->register_info), tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH),
			manager);
		return -1;
	}

	//初始化模块管理器注册器
	tmp_mmr = (cp_module_manager_register_t**)cp_palloc(manager->pool,
		cp_sizeof(cp_module_manager_register_t*) * manager_register_size);
	if (!tmp_mmr) {
		cp_log_error(manager->app->logger, 
			"create register memory %s error! manager[%p] palloc manager register memory[%d] failed!",
			cp_print_module_register_info(&(manager->register_info), tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH),
			manager,
			cp_sizeof(cp_module_manager_register_t*) * manager_register_size);
		return -2;
	}
	cp_memset(tmp_mmr, 0, cp_sizeof(cp_module_manager_register_t*) * manager_register_size);
	cp_array_init(&(manager->module_manager_register), 
		tmp_mmr, cp_sizeof(cp_module_manager_register_t*), manager_register_size);

	//初始化模块管理器
	tmp_mm = (cp_module_manager_t**)cp_palloc(manager->pool, cp_sizeof(cp_module_manager_t*) * manager_size);
	if (!tmp_mm) {
		cp_log_error(manager->app->logger, 
			"create register memory %s error! manager[%p] palloc module manager memory[%d] failed!",
			cp_print_module_register_info(&(manager->register_info), tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH),
			manager,
			cp_sizeof(cp_module_manager_t*) * manager_size);
		return -3;
	}
	cp_memset(tmp_mm, 0, cp_sizeof(cp_module_manager_t*) * manager_size);
	cp_array_init(&(manager->module_managers), tmp_mm, cp_sizeof(cp_module_manager_t*), manager_size);

	//初始化子模块注册器
	tmp_mr = (cp_module_register_t**)cp_palloc(manager->pool, cp_sizeof(cp_module_register_t*) * module_register_size);
	if (!tmp_mr) {
		cp_log_error(manager->app->logger, 
			"create register memory %s error! manager[%p] palloc module register memory[%d] failed!",
			cp_print_module_register_info(&(manager->register_info), tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH),
			manager,
			cp_sizeof(cp_module_register_t*) * module_register_size);
		return -4;
	}
	cp_memset(tmp_mr, 0, cp_sizeof(cp_module_register_t*) * module_register_size);
	cp_array_init(&(manager->module_register), 
		tmp_mr, cp_sizeof(cp_module_register_t*), module_register_size);

	return 0;
}

//为模块管理器添加模块的注册信息
cp_int32_t _manager_set_module_register(cp_module_manager_t *manager, 
	cp_module_register_t *module_register_list, cp_int32_t module_register_list_size, cp_int32_t size)
{
	cp_int32_t							i = 0;
	cp_char_t							tmp_buf[CP_APP_DEFAULT_BUFFER_LENGTH] = { 0, };
	cp_module_register_t				*tmp_module_register = CP_NULL;



	if (!manager || !module_register_list || !module_register_list_size) {
		cp_log_error(manager->app->logger, 
			"set module register %s error! manager[%p] module_register_list[%p] module_register_list_size[%d]!",
			cp_print_module_register_info(&(manager->register_info), tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH),
			manager,
			module_register_list,
			module_register_list_size);
		return -1;
	}

	if (module_register_list_size > (cp_int32_t)cp_array_max_size(&manager->module_register)) {
		cp_log_error(manager->app->logger, "set module register %s error! module_register_list_size[%d] more than [%d]!",
			cp_print_module_register_info(&(manager->register_info), tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH),
			module_register_list_size,
			cp_array_max_size(&manager->module_register));
		return -2;
	}

	for (i = 0; i < module_register_list_size; i++) {
		//判断这个类型是否已经存在，已经存在则不插入
		tmp_module_register = _manager_get_module_register(manager, module_register_list[i].type);
		if (tmp_module_register) {
			cp_log_error(manager->app->logger, 
				"set module register %s error! register existed!",
				cp_print_module_register_info(&(module_register_list[i]), tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH));
			continue;
		}

		tmp_module_register = (cp_module_register_t*)cp_palloc(manager->pool, size);
		if (!tmp_module_register) {
			cp_log_error(manager->app->logger, 
				"set module register %s error! palloc memory[%d] error!",
				cp_print_module_register_info(&(module_register_list[i]), tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH),
				cp_sizeof(cp_module_register_t));
			continue;
		}
		cp_memset(tmp_module_register, 0, size);
		cp_memcpy(tmp_module_register, &module_register_list[i], size);
		//*tmp_module_register = module_register_list[i];
		//cp_array_set_back(&(manager->module_register), &tmp_module_register);
		cp_array_set(&(manager->module_register), 
			&tmp_module_register, CP_GET_LIBRARY_SUB_MODULE_TYPE(tmp_module_register->type));
	}

	return 0;
}

//获取模块注册信息
cp_module_register_t* _manager_get_module_register(cp_module_manager_t *manager, cp_int32_t type)
{
	cp_int32_t				i = 0;
	cp_module_register_t	**tmp_module_register = CP_NULL;


	if (!manager || !type) {
		return CP_NULL;
	}

	if (!cp_array_length(&(manager->module_register))) {
		return CP_NULL;
	}

	for (i = 0; i < (cp_int32_t)cp_array_max_size(&manager->module_register); i++) {
		tmp_module_register = (cp_module_register_t	**)cp_array_get(&(manager->module_register), i);
		if (*tmp_module_register && type == (*tmp_module_register)->type) {
			return *tmp_module_register;
		}
	}

	return *tmp_module_register;
}

//为模块增加子管理模块的注册信息
cp_int32_t _manager_set_sub_manager_register(cp_module_manager_t *manager,
	cp_module_manager_register_t *manager_register_list, cp_int32_t manager_register_list_size, cp_uint32_t size)
{
	cp_int32_t							i = 0;
	cp_char_t							tmp_buf[CP_APP_DEFAULT_BUFFER_LENGTH] = { 0, };
	cp_module_manager_register_t		*tmp_module_manager_register = CP_NULL;



	if (!manager || !manager_register_list || !manager_register_list_size) {
		cp_log_error(manager->app->logger,
			"set sub manager register %s error! manager[%p] manager_register_list[%p] manager_register_list_size[%d]!",
			cp_print_manager_register_info(&(manager->register_info), tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH),
			manager,
			manager_register_list,
			manager_register_list_size);
		return -1;
	}

	if (manager_register_list_size > (cp_int32_t)cp_array_max_size(&manager->module_manager_register)) {
		cp_log_error(manager->app->logger,
			"set sub manager register %s error! module_register_list_size[%d] more than [%d]!",
			cp_print_manager_register_info(&(manager->register_info), tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH),
			manager_register_list_size,
			cp_array_max_size(&manager->module_manager_register));
		return -2;
	}

	for (i = 0; i < manager_register_list_size; i++) {
		//判断这个类型是否已经存在，已经存在则不插入
		tmp_module_manager_register = _manager_get_sub_manager_register(manager, manager_register_list[i].type);
		if (tmp_module_manager_register) {
			cp_log_error(manager->app->logger,
				"set sub manager register %s error! register existed!",
				cp_print_manager_register_info(&(manager_register_list[i]), tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH));
			continue;
		}

		tmp_module_manager_register = (cp_module_manager_register_t*)cp_palloc(manager->pool, size);
		if (!tmp_module_manager_register) {
			cp_log_error(manager->app->logger,
				"set sub manager register %s error! palloc memory[%d] error!",
				cp_print_manager_register_info(&(manager_register_list[i]), tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH),
				cp_sizeof(cp_module_register_t));
			continue;
		}
		cp_memset(tmp_module_manager_register, 0, size);
		cp_memcpy(tmp_module_manager_register, &manager_register_list[i], size);
		//*tmp_module_manager_register = manager_register_list[i];
		//cp_array_set_back(&(manager->module_manager_register), &tmp_module_manager_register);
		cp_array_set(&(manager->module_manager_register), &tmp_module_manager_register,
			CP_GET_LIBRARY_SUB_MODULE_TYPE(tmp_module_manager_register->type));
	}

	return 0;
}

//获取模块的子模块管理器信息
cp_module_manager_register_t* _manager_get_sub_manager_register(cp_module_manager_t *manager, cp_int32_t type)
{
	cp_module_manager_t				*tmp_root_manager = CP_NULL;




	if (!manager) {
		return CP_NULL;
	}

	if (CP_GET_LIBRARY_MODULE_TYPE(manager->register_info.type) ==
		CP_GET_LIBRARY_MODULE_TYPE(type)) {
		tmp_root_manager = manager;
	} else {
		//获取根管理器
		tmp_root_manager = cp_manager_get_root_manager(manager->app, type);
	}

	if (!tmp_root_manager) {
		return CP_NULL;
	}
	//判断模块类型是否合法
	if (CP_GET_LIBRARY_SUB_MODULE_TYPE(type) > (cp_int32_t)cp_array_max_size(&tmp_root_manager->module_manager_register)) {
		return CP_NULL;
	}

	return *((cp_module_manager_register_t**)
		cp_array_get(&(tmp_root_manager->module_manager_register), CP_GET_LIBRARY_SUB_MODULE_TYPE(type)));
}

//设置一个根模块管理器注册器信息
cp_int32_t _manager_set_root_manager_register(cp_app_t *app, cp_module_manager_register_t *module_manager_register, cp_uint32_t size)
{
	cp_module_manager_register_t						*tmp_module_manager_register = CP_NULL;




	if (!app || !module_manager_register) {
		return -1;
	}
	tmp_module_manager_register = _manager_get_root_manager_register(app, module_manager_register->type);
	if (!tmp_module_manager_register) {
		tmp_module_manager_register = cp_mpalloc(app->mpool, size);
		if (!tmp_module_manager_register) {
			cp_app_log(error, app, "_manager_set_root_manager_register() error! malloc error.");
			return -2;
		}
		cp_memset(tmp_module_manager_register, 0, size);
		cp_memcpy(tmp_module_manager_register, module_manager_register, size);
		//*tmp_module_manager_register = *module_manager_register;
		cp_array_set(&(app->root_module_manager_register), &tmp_module_manager_register, 
			CP_GET_LIBRARY_REAL_MODULE_TYPE(module_manager_register->type));
	}

	return 0;
}

//获取根管理器注册器
cp_module_manager_register_t* _manager_get_root_manager_register(cp_app_t *app, cp_int32_t type)
{
	return *((cp_module_manager_register_t**)
		cp_array_get(&(app->root_module_manager_register), CP_GET_LIBRARY_REAL_MODULE_TYPE(type)));
}
