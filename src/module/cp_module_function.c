/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/
#include "cp_include.h"
#include "cp_module_function.h"
#include "cp_pool_core.h"


/************************************************************************/
/* 该宏                                                                     */
/************************************************************************/
#define		CHECK_MODULE_HANDLE_EXIST(module, handle_name)															\
	do {																											\
		cp_char_t					tmp_buf[CP_APP_DEFAULT_BUFFER_LENGTH] = { 0, };									\
																													\
		if (!(module)) {																							\
			return -1;																								\
		}																											\
		if (!(module)->handle_name) {																				\
			print_module_register_info(&((module)->register_info), tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH);			\
			cp_module_log(error, (module), #handle_name "%s error! not found [" #handle_name "] handle error.",		\
				tmp_buf);																							\
			return -2;																								\
		}																											\
	}while(0);																										\



cp_char_t *print_module_register_info(cp_module_register_t *module_register, cp_char_t *buf, cp_int32_t len)
{
	char				tmp_buf[CP_APP_DEFAULT_BUFFER_LENGTH] = { 0, };



	if (!module_register || !buf || !len) {
		return buf;
	}
	cp_memset(buf, 0, len);
	cp_snprintf(buf, len, "module[ t:%d(%d-%d-%d-%d) | n:%s/%s (%d) | d:%s ]-[%s]",
		module_register->type,
		CP_GET_LIBRARY_TYPE(module_register->type) >> 24,
		CP_GET_LIBRARY_REAL_MODULE_TYPE(module_register->type),
		0,
		CP_GET_LIBRARY_SUB_MODULE_TYPE(module_register->type),
		module_register->name,
		cp_version_itoa(module_register->version, tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH),
		module_register->version,
		module_register->description,
		CP_VER);

	return buf;
}


cp_module_t*_malloc_module(cp_module_manager_t *manager, cp_int32_t module_mem_size, cp_module_info_t *info)
{
	cp_module_t							*tmp_module = CP_NULL;
	cp_pool_t							*tmp_pool = CP_NULL;


	tmp_pool = cp_create_pool_ex(manager->app, (cp_pool_info_t*)info);
	if (!tmp_pool) {
		cp_manager_log(error, manager, "module malloc() create pool error.");
		return CP_NULL;
	}

	//tmp_module = (cp_module_t*)cp_palloc(tmp_pool, module_mem_size);
	tmp_module = (cp_module_t*)cp_malloc(module_mem_size);
	if (!tmp_module) {
		//cp_destroy_pool(tmp_pool);
		cp_manager_log(error, manager, "palloc() module error.");
		return CP_NULL;
	}
	cp_memset(tmp_module, 0, module_mem_size);
	tmp_module->pool = tmp_pool;

	return tmp_module;
}

cp_int32_t _free_module(cp_module_t *module)
{
	if (module && module->pool) {
		cp_destroy_pool((module)->pool);
		cp_free(module);
	}

	return 0;
}

cp_module_t* _create_module(cp_module_register_t *register_info, cp_module_manager_t *manager, cp_module_info_t *info)
{
	cp_module_t					*tmp_module = CP_NULL;
	cp_char_t					tmp_buf[CP_APP_DEFAULT_BUFFER_LENGTH] = { 0, };




	if (!register_info) {
		return tmp_module;
	}

	print_module_register_info(register_info, tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH);

	if (!register_info->module_create) {
		cp_log_error(manager->app->logger, "create %s error! handle[manager_create = null]",
			tmp_buf);
		return tmp_module;
	}
	//加锁
	cp_mutex_lock(&manager->module_mutex);
	//调用模块注册的创建接口创建模块
	tmp_module = register_info->module_create(register_info, manager, info);
	if (!tmp_module) {
		cp_log_error(manager->app->logger, "create %s error! return null.", tmp_buf);
		//解锁
		cp_mutex_unlock(&manager->module_mutex);
		return tmp_module;
	}
	//初始化manager的基础信息
	if (!tmp_module->register_info.name) {
		tmp_module->register_info = *register_info;
	}
	//初始化其他信息	
	tmp_module->manager = manager;
	tmp_module->logger = manager->app->logger;
	tmp_module->conf = manager->conf;
	cp_queue_init(&tmp_module->queue);
	//设置模块状态值
	CP_MODULE_SET_STATUS(tmp_module, cp_module_status_create);
	//注册模块
	cp_manager_register_module(manager, tmp_module);
	//解锁
	cp_mutex_unlock(&manager->module_mutex);
	cp_log_notice(manager->app->logger, "create [0x%x] %s success!",
		tmp_module,
		tmp_buf);
	return tmp_module;
}

cp_int32_t _destroy_module(cp_module_manager_t *manager, cp_module_t *module)
{
	cp_int32_t					ret_int = 0;
	cp_char_t					tmp_buf[CP_APP_DEFAULT_BUFFER_LENGTH] = { 0, };



	if (!module) {
		return -1;
	}

	print_module_register_info(&(module->register_info), tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH);
	//销毁各个模块管理器
	if (!module->register_info.module_destroy) {
		cp_log_error(manager->app->logger, "destroy [0x%x] %s error! handle[manager_destroy = null]",
			module,
			tmp_buf);
		return -1;
	}

	//加锁
	cp_mutex_lock(&manager->module_mutex);
	//取消注册模块
	cp_manager_cancel_module(manager, module);
	CP_MODULE_UNSET_STATUS(module, cp_module_status_create);
	//调用句柄进行模块停止
	ret_int = module->register_info.module_destroy(manager, module);
	//解锁
	cp_mutex_unlock(&manager->module_mutex);
	if (ret_int) {
		cp_log_error(manager->app->logger, "destroy [0x%x] %s error! return[%d] error.",
			module,
			tmp_buf,
			ret_int);
		return -2;
	}
	cp_log_notice(manager->app->logger, "destroy [0x%x] %s success!",
		module,
		tmp_buf);

	return 0;
}

cp_int32_t _init_module(cp_module_t *module, const cp_module_info_t *info)
{
	cp_int32_t					ret_int = 0;


	if (!module || !info) {
		return -1;
	}

	CHECK_MODULE_HANDLE_EXIST(module, init);

	ret_int = module->init(module, info);
	if (!ret_int) {
		CP_MODULE_SET_STATUS(module, cp_module_status_init);
	}
	return ret_int;
}
cp_int32_t _open_module(cp_module_t *module, const cp_module_info_t *info)
{
	cp_int32_t					ret_int = 0;


	if (!module || !info) {
		return -1;
	}

	CHECK_MODULE_HANDLE_EXIST(module, open);

	ret_int = module->open(module, info);
	if (!ret_int) {
		CP_MODULE_SET_STATUS(module, cp_module_status_open);
	}
	return ret_int;
}
cp_int32_t _read_module(cp_module_t *module, cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag)
{
	if (!module) {
		return -1;
	}

	CHECK_MODULE_HANDLE_EXIST(module, read);

	return module->read(module, buf, len, flag);
}
cp_int32_t _write_module(cp_module_t *module, const cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag)
{
	if (!module) {
		return -1;
	}

	CHECK_MODULE_HANDLE_EXIST(module, write);

	return module->write(module, buf, len, flag);
}
cp_int32_t _close_module(cp_module_t *module)
{
	cp_int32_t					ret_int = 0;


	if (!module) {
		return -1;
	}

	CHECK_MODULE_HANDLE_EXIST(module, close);

	ret_int = module->close(module);
	if (!ret_int) {
		CP_MODULE_UNSET_STATUS(module, cp_module_status_open);
	}
	return ret_int;
}
cp_int32_t _exit_module(cp_module_t *module)
{
	cp_int32_t					ret_int = 0;


	if (!module) {
		return -1;
	}

	CHECK_MODULE_HANDLE_EXIST(module, exit);

	ret_int = module->exit(module);
	if (!ret_int) {
		CP_MODULE_UNSET_STATUS(module, cp_module_status_init);
	}
	return ret_int;
}
cp_int32_t _set_option_module(cp_module_t *module, cp_int32_t optname, const cp_void_t* optval)
{
	if (!module) {
		return -1;
	}

	CHECK_MODULE_HANDLE_EXIST(module, set_option);

	return module->set_option(module, optname, optval);
}
cp_int32_t _get_option_module(cp_module_t *module, cp_int32_t optname, cp_void_t* optval)
{
	if (!module) {
		return -1;
	}

	CHECK_MODULE_HANDLE_EXIST(module, get_option);

	return module->get_option(module, optname, optval);
}


cp_int32_t _set_module_error(cp_module_t *module, const cp_int32_t error_no, const cp_char_t *format, ...)
{
	return 0;
}
cp_int32_t _get_module_error_no(cp_module_t *module)
{
	return 0;
}
cp_char_t* _get_module_error_text(cp_module_t *module)
{
	return 0;
}




/*******************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: _app_create_module_by_type
*
* 函数全名: _app_create_module_by_type
*
* 函数访问: public 
*
* 函数说明: app 根据类型创建一个模块
*
* 参    数: cp_app_t * app						[in/out]参数说明
* 参    数: cp_module_manager_type_e manager_type						[in/out]参数说明
* 参    数: cp_module_type_e module_type						[in/out]参数说明
* 参    数: cp_module_info_t * module_info						[in/out]参数说明
*
* 返 回 值: cp_module_t*
*           0  : 成功
*         非0  : 失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2018-2-11 15:22:48
********************************************************************************/
cp_module_t* _app_create_module_by_type(cp_app_t *app,
	cp_module_manager_type_e manager_type, cp_module_type_e module_type, cp_module_info_t *module_info)
{
	cp_module_t									*tmp_module = CP_NULL;
	cp_module_manager_t							*tmp_manager = CP_NULL;
	cp_module_manager_info_t					tmp_manager_info = { 0, };
	cp_module_register_t						*tmp_module_register = CP_NULL;



	CP_MODULE_MANAGER_INFO_SET_TYPE(&tmp_manager_info, manager_type);

	//获取管理器
	tmp_manager = cp_get_manager(app, &tmp_manager_info);
	if (!tmp_manager) {
		cp_app_log(warn, app, "not found manager by type[%d]");
		return CP_NULL;
	}

	//创建一个处理模块
	CP_MODULE_INFO_SET_TYPE(module_info, module_type);

	//先查找一个模块是否存在
	tmp_module = cp_manager_get_module(tmp_manager, module_info);
	if (!tmp_module) {
		//不存在则开始创建
		tmp_module_register = _manager_get_module_register(tmp_manager, module_type);
		if (tmp_module_register) {
			tmp_module = cp_create_module(tmp_module_register, tmp_manager, module_info);
		}
	}
	return tmp_module;
}

/*******************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: _app_get_module_by_type
*
* 函数全名: _app_get_module_by_type
*
* 函数访问: public
*
* 函数说明: app 根据类型获取一个模块
*
* 参    数: cp_app_t * app						[in/out]参数说明
* 参    数: cp_module_manager_type_e manager_type						[in/out]参数说明
* 参    数: cp_module_type_e module_type						[in/out]参数说明
*
* 返 回 值: cp_extern cp_module_t*
*           0  : 成功
*         非0  : 失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2018-2-11 15:21:45
********************************************************************************/
cp_extern cp_module_t* _app_get_module_by_type(cp_app_t *app,
	cp_module_manager_type_e manager_type, cp_module_type_e module_type)
{
	cp_module_manager_t							*tmp_manager = CP_NULL;
	cp_module_manager_info_t					tmp_manager_info = { 0, };
	cp_module_info_t							tmp_module_info = { 0, };



	CP_MODULE_MANAGER_INFO_SET_TYPE(&tmp_manager_info, manager_type);

	//获取管理器
	tmp_manager = cp_get_manager(app, &tmp_manager_info);
	if (!tmp_manager) {
		cp_app_log(warn, app, "not found manager by type[%d]");
		return CP_NULL;
	}

	//创建一个处理模块
	CP_MODULE_INFO_SET_TYPE(&tmp_module_info, module_type);

	return cp_manager_get_module(tmp_manager, &tmp_module_info);
}




