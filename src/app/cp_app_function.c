/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/

#if defined(__linux__)
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/signal.h>
#endif

#include "cp_app_function.h"
#include "cp_utils.h"
#include "cp_daemon.h"



//引用守护信息
CP_EXTERN_GLOBAL_APP_DAEMON();



//打印app信息到指定的缓存中
cp_char_t *print_app_info(cp_app_info_t *app_info, cp_char_t *buf, cp_int32_t len)
{
	char				tmp_buf[CP_APP_DEFAULT_BUFFER_LENGTH] = { 0, };


	if (!buf || !len) {
		return buf;
	}
	cp_memset(buf, 0, len);
	cp_snprintf(buf, len, "app[ t:%d(%d-%d-%d-%d) | n:%s/%s (%d) | d:%s ]-[%s]",
		app_info->type,
		CP_GET_LIBRARY_TYPE(app_info->type) >> 24,
		CP_GET_LIBRARY_REAL_MODULE_TYPE(app_info->type),
		0,
		CP_GET_LIBRARY_SUB_MODULE_TYPE(app_info->type),
		app_info->name,
		cp_version_itoa(app_info->version, tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH),
		app_info->version,
		app_info->description,
		CP_VER);

	return buf;
}

//初始化app
cp_int32_t init_app(cp_app_t *app, cp_app_info_t *app_info)
{
	cp_int32_t			ret_int = 0;



	//初始化配置文件信息
	ret_int = init_app_config(app, app_info);
	if (ret_int) {
		cp_log_printf("init configure failed!");
		return ret_int;
	}
	//初始化日志库信息
	ret_int = init_app_log(app, app_info);
	if (ret_int) {
		cp_log_printf("init log failed!");
		return ret_int;
	}
	//创建模块
	ret_int = create_app_root_manager(app, app->root_module_manager_register.elts, cp_array_max_size(&app->root_module_manager_register));
	if (ret_int) {
		cp_app_log(error, app, "init_app() error! create_app_root_manager() error!");
		return ret_int;
	}

	return 0;
}

//启动app
cp_int32_t start_app(cp_app_t *app, cp_app_info_t *app_info)
{
	cp_int32_t			ret_int = 0;



	//启动模块信息
	ret_int = start_app_manager(app, cp_array_get_elts(&app->root_module_manager_array),
		cp_array_length(&app->root_module_manager_array));
	if (ret_int) {
		cp_app_log(error, app, "start_app() error! start_app_manager() error!");
		return ret_int;
	}

	//启动daemon
	ret_int = start_daemon_signal_thread(app);
	if (ret_int) {
		cp_app_log(error, app, "start_app() error! start_daemon_signal_thread() error!");
		return ret_int;
	}
	else {
		cp_app_log(notice, app, "start_daemon_signal_thread() success!");
	}

	return 0;
}

//停止app
cp_int32_t stop_app(cp_app_t *app)
{
	cp_int32_t			ret_int = 0;



	//停止模块信息
	ret_int = stop_app_manager(app, cp_array_get_elts(&app->root_module_manager_array),
		cp_array_length(&app->root_module_manager_array));
	if (ret_int) {
		cp_app_log(error, app, "stop_app() error! stop_app_manager() error!");
		return ret_int;
	}
	//销毁模块配置信息
	ret_int = destroy_app_config(app);
	if (ret_int) {
		cp_app_log(error, app, "stop_app() error! destroy_app_config() error!");
		return ret_int;
	}
	//销毁模块日志信息
	ret_int = destroy_app_log(app);
	if (ret_int) {
		cp_app_log(error, app, "stop_app() error! destroy_app_log() error!");
		return ret_int;
	}
	return 0;
}

//表示获取当前的app指针
cp_app_t *get_app()
{
	return cp_global_daemon_info->app;
}

//初始化app配置文件信息
cp_int32_t init_app_config(cp_app_t *app, cp_app_info_t *app_info)
{
	cp_int32_t			ret_int = 0;
	cp_char_t			*tmp_env_conf = CP_NULL;
	cp_char_t			*tmp_entry_conf = CP_NULL;



	//先判断是否配置了entry_config_path
	if (cp_strlen(app_info->entry_config_path)) {
		tmp_entry_conf = app_info->entry_config_path;
		cp_log_printf("app_config used app_info [entry_config_path = %s] ", tmp_entry_conf);
	}
	else {
		//没有配置用环境变量
		tmp_env_conf = cp_get_set_null_env(CP_DEFAULT_ENV_CP_CONF_FILE, CP_DEFAULT_CONF_FILE);
		if (!(tmp_env_conf)) {
			cp_log_printf("cp_get_env_conf error!");
			return -1;
		}
		tmp_entry_conf = tmp_env_conf;
		cp_log_printf("app_config used env_info [entry_config_path = %s] ", tmp_entry_conf);
	}

	app->conf = cp_conf_create(app);
	if (!(app->conf)) {
		cp_log_printf("cp_conf_create error!");
		return -1;
	}

	ret_int = cp_conf_init(app->conf, app, tmp_entry_conf);
	if (ret_int) {
		cp_log_printf("cp_conf_init error!");
		return -1;
	}

	return ret_int;
}

//销毁app配置文件
cp_int32_t destroy_app_config(cp_app_t *app)
{
	int			ret_int = 0;


	ret_int = cp_conf_destroy(app->conf);
	if (ret_int) {
		cp_log_printf("cp_conf_destroy error!");
		return -1;
	}
	return 0;
}

//初始化日志信息
cp_int32_t init_app_log(cp_app_t *app, cp_app_info_t *app_info)
{
	cp_int32_t			ret_int = 0;



	app->logger = cp_log_create();
	if (!(app->logger)) {
		cp_log_printf("cp_log_create error!");
		return -1;
	}

	ret_int = cp_log_init(app->logger, app->conf);
	if (ret_int) {
		cp_log_printf("log init error");
		return -2;
	}

	app->conf->logger = app->logger;
	return ret_int;
}

cp_int32_t destroy_app_log(cp_app_t *app)
{
	cp_int32_t			ret_int = 0;


	if (app && app->logger) {
		ret_int = app->logger->log_stop(app->logger, 0, CP_NULL);
		if (ret_int) {
			cp_log_printf("log stop error!");
			return 0;
		}
		ret_int = cp_log_destroy(app->logger);
		if (ret_int) {
			cp_log_printf("cp_log_destroy error!");
			return -1;
		}
	}
	
	return 0;
}



//创建模块管理器的注册器保存空间
cp_int32_t create_app_root_register_memory(cp_app_t *app, cp_int32_t size)
{
	cp_void_t								*tmp_mem = CP_NULL;



	if (!app) {
		return -1;
	}
	//根据模块管理器的数量创建一个指针数组，保存各个管理器的指针地址
	tmp_mem = cp_mpalloc(app->mpool, (cp_sizeof(cp_module_manager_register_t*) * size));
	if (!tmp_mem) {
		cp_app_log(error, app, 
			"create_app_root_register_memory() error! malloc error. manager_size[%d]",
			size);
		return -1;
	}
	cp_memset(tmp_mem, 0, cp_sizeof(cp_module_manager_register_t*) * size);
	cp_array_init(&(app->root_module_manager_register), tmp_mem, cp_sizeof(cp_module_manager_register_t*), size);
	return 0;
}

//销毁模块管理器的注册器保存空间
cp_int32_t destroy_app_root_register_memory(cp_app_t *app)
{
	if (!app) {
		return -1;
	}

	return 0;
}

//主要创建根管理器
cp_int32_t create_app_root_manager(cp_app_t *app, cp_module_manager_register_t **manager_register, cp_int32_t manager_size)
{
	cp_int32_t								i = 0;
	cp_void_t								*tmp_mem = CP_NULL;
	cp_module_manager_t						*tmp_manager = CP_NULL;
	cp_module_manager_info_t				tmp_manager_info = { 0, };
	cp_char_t								tmp_buf[CP_APP_DEFAULT_BUFFER_LENGTH] = { 0, };



	if (!app) {
		return -1;
	}
	if (!manager_register || !manager_size) {
		cp_app_log(error, app, "create_app_root_manager() error! app[%p] manager_register[%p] manager_size[%d]",
			app,
			manager_register,
			manager_size);
		return -2;
	}
	//根据模块管理器的数量创建一个指针数组，保存各个管理器的指针地址
	tmp_mem = cp_mpalloc(app->mpool, (cp_sizeof(cp_module_manager_t*) * CP_GET_LIBRARY_REAL_MODULE_TYPE(cp_module_manager_type_end)));
	if (!tmp_mem) {
		cp_app_log(error, app, "create_app_root_manager() error! malloc error. manager_size[%d]",
			manager_size);
		return -3;
	}
	cp_memset(tmp_mem, 0, cp_sizeof(cp_module_manager_t*) * CP_GET_LIBRARY_REAL_MODULE_TYPE(cp_module_manager_type_end));
	cp_array_init(&(app->root_module_manager_array), tmp_mem,
		cp_sizeof(cp_module_manager_t*), CP_GET_LIBRARY_REAL_MODULE_TYPE(cp_module_manager_type_end));

	//开始创建各个模块管理器
	for (i = 0; i < manager_size; i++) {
		if (!manager_register[i]) {
			//这里判断是否为空，因为第0个可能是空指针，没有被使用，模块都是1开始编号
			continue;
		}

		//准备模块数据
		tmp_manager_info.app = app;
		tmp_manager_info.version = manager_register[i]->version;

		//查看一下是否已经存在，存在则不创建模块管理器
		tmp_manager = *(cp_module_manager_t**)cp_array_get(&(app->root_module_manager_array), i);
		if (!tmp_manager) {
			//调用模块注册的创建接口创建模块
			tmp_manager = cp_create_manager(manager_register[i], app, &tmp_manager_info);
			if (!tmp_manager) {
				cp_app_log(error, app, "create_app_root_manager() error! create %s error! return null.",
					cp_print_manager_register_info(manager_register[i], tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH));
				continue;
			}
		}

		//初始化manager的基础信息
		tmp_manager->register_info = *manager_register[i];

		//创建成功，将模块存在相应的位置
		cp_array_set(&(app->root_module_manager_array), &tmp_manager, i);
		// 		cp_app_log(notice, app, "create %s success!",
		// 			cp_print_manager_register_info(manager_register[i], tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH));
	}
	return 0;
}
//创建子模块管理器
cp_int32_t create_app_all_sub_manager(cp_app_t *app)
{
	cp_int32_t								i = 0;
	cp_int32_t								tmp_ret_int = 0;
	cp_module_manager_t						**tmp_root_manager = CP_NULL;



	if (!app) {
		return -1;
	}

	for (i = 0; i < (cp_int32_t)cp_array_max_size(&app->root_module_manager_array); i++)	{
		tmp_root_manager = cp_array_get(&(app->root_module_manager_array), i);
		if (!(*tmp_root_manager) || !cp_array_is_empty(&(*tmp_root_manager)->module_manager_register)) {
			continue;
		}

		tmp_ret_int = cp_manager_create_all_sub_manager((*tmp_root_manager));
		if (!tmp_ret_int) {
			cp_manager_log(error, (*tmp_root_manager), "cp_manager_create_all_sub_manager() error! return [%d].",
				tmp_ret_int);
			continue;
		}
	}

	return 0;
}
//为根节点创建子模块管理器
cp_int32_t create_app_root_sub_manager(cp_module_manager_t *root_manager)
{
	cp_int32_t								i = 0;
	cp_void_t								*tmp_mem = CP_NULL;
	cp_module_manager_t						*tmp_manager = CP_NULL;
	cp_module_manager_register_t			**tmp_sub_manager_register = CP_NULL;
	cp_module_manager_info_t				tmp_manager_info = { 0, };
	cp_char_t								tmp_buf[CP_APP_DEFAULT_BUFFER_LENGTH] = { 0, };



	if (!root_manager) {
		return -1;
	}

	//如果为初始化，则进行初始化处理
	if (!cp_array_is_null(&(root_manager->module_managers))) {
		tmp_mem = cp_palloc(root_manager->pool, (cp_sizeof(cp_module_manager_t*) * CP_LIBRARY_MODULE_MANAGER_MAX_SIZE));
		if (!tmp_mem) {
			cp_log_error(root_manager->logger, "create_app_all_sub_manager() error! malloc error.");
			return -2;
		}
		cp_memset(tmp_mem, 0, cp_sizeof(cp_module_manager_t*) * CP_LIBRARY_MODULE_MANAGER_MAX_SIZE);
		cp_array_init(&(root_manager->module_managers),
			tmp_mem, cp_sizeof(cp_module_manager_t*), CP_LIBRARY_MODULE_MANAGER_MAX_SIZE);
	}
	//开始创建各个模块管理器
	for (i = 0; i < (cp_int32_t)cp_array_max_size(&root_manager->module_manager_register); i++) {
		tmp_sub_manager_register = cp_array_get(&(root_manager->module_manager_register), i);
		if (!(*tmp_sub_manager_register)) {
			//这里判断是否为空，因为第0个可能是空指针，没有被使用，模块都是1开始编号
			continue;
		}

		//准备模块数据
		tmp_manager_info.app = root_manager->app;
		tmp_manager_info.version = (*tmp_sub_manager_register)->version;

		//查看一下是否已经存在，存在则不创建模块管理器
		tmp_manager = *(cp_module_manager_t**)cp_array_get(&(root_manager->module_managers), i);
		if (!tmp_manager) {
			//调用模块注册的创建接口创建模块
			tmp_manager = cp_create_manager((*tmp_sub_manager_register), root_manager->app, &tmp_manager_info);
			if (!tmp_manager) {
				cp_log_error(root_manager->logger, "create_app_all_sub_manager() error! create %s error! return null.",
					cp_print_manager_register_info((*tmp_sub_manager_register), tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH));
				continue;
			}
		}

		//初始化manager的基础信息
		tmp_manager->register_info = *(*tmp_sub_manager_register);

		//创建成功，将模块存在相应的位置
		cp_array_set(&(root_manager->module_managers), &tmp_manager, i);
		// 		cp_log_notice(root_manager->logger, "create %s success!",
		// 			cp_print_manager_register_info((*tmp_sub_manager_register), tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH));
	}

	return 0;
}
//初始化根模块管理器
cp_int32_t init_app_root_manager(cp_app_t *app, cp_module_manager_t **mm_array, cp_int32_t mm_size)
{
	cp_int32_t					i = 0;
	cp_int32_t					ret_int = 0;
	cp_module_manager_info_t	tmp_manager_info = { 0, };
	cp_char_t					tmp_buf[CP_APP_DEFAULT_BUFFER_LENGTH] = { 0, };



	//开始创建各个模块管理器
	for (i = 0; i < CP_GET_LIBRARY_REAL_MODULE_TYPE(cp_module_manager_type_end); i++) {
		if (mm_array[i]) {
			//准备模块数据
			tmp_manager_info.app = app;
			tmp_manager_info.version = mm_array[i]->register_info.version;
			//调用初始化句柄进行模块初始化
			ret_int = cp_init_manager(mm_array[i], &tmp_manager_info);
			if (ret_int) {
				cp_app_log(error, app, "init_app_root_manager() error! init %s error! return[%d] error.",
					cp_print_manager_register_info(&(mm_array[i]->register_info), tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH),
					ret_int);
				continue;
			}
			//创建各个子模块管理器信息
			ret_int = create_app_root_sub_manager(mm_array[i]);
			if (ret_int) {
				cp_log_printf("init_app_root_manager() error. create_app_root_sub_manager() error.");
				return ret_int;
			}
			// 			cp_app_log(notice, app, "init %s success!",
			// 				cp_print_manager_register_info(&(mm_array[i]->register_info), tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH));
		}
	}
	return 0;
}

//初始化子模块管理器信息
cp_int32_t init_app_sub_manager(cp_app_t *app)
{
	cp_int32_t								i = 0;
	cp_int32_t								ret_int = 0;
	cp_module_manager_t						**tmp_root_manager = CP_NULL;
	cp_char_t								tmp_buf[CP_APP_DEFAULT_BUFFER_LENGTH] = { 0, };



	if (!app) {
		return -1;
	}

	for (i = 0; i < (cp_int32_t)cp_array_max_size(&app->root_module_manager_array); i++)	{
		tmp_root_manager = cp_array_get(&(app->root_module_manager_array), i);
		if (!(*tmp_root_manager) || !cp_array_is_empty(&(*tmp_root_manager)->module_manager_register)) {
			continue;
		}
		//开始创建各个模块管理器
		ret_int = cp_manager_init_all_sub_manager((*tmp_root_manager));
		if (ret_int) {
			cp_manager_log(error, (*tmp_root_manager), "cp_manager_init_all_sub_manager() error! create %s error! return [%d].",
				cp_print_manager_register_info(&(*tmp_root_manager)->register_info, tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH),
				ret_int);
			continue;
		}
		//cp_manager_log(notice, (*tmp_root_manager), "init %s success!",
		//	cp_print_manager_register_info(&(*tmp_root_manager)->register_info, tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH));
	}

	return 0;
}

//启动根模块管理器
cp_int32_t start_app_root_manager(cp_app_t *app, cp_module_manager_t **mm_array, cp_int32_t mm_size)
{
	cp_int32_t					i = 0;
	cp_int32_t					ret_int = 0;
	cp_module_manager_info_t	tmp_manager_info = { 0, };
	cp_char_t					tmp_buf[CP_APP_DEFAULT_BUFFER_LENGTH] = { 0, };



	//开始创建各个模块管理器
	for (i = 0; i < CP_GET_LIBRARY_REAL_MODULE_TYPE(cp_module_manager_type_end); i++) {
		if (mm_array[i]) {
			//准备模块数据
			tmp_manager_info.app = app;
			tmp_manager_info.version = mm_array[i]->register_info.version;
			//调用启动句柄进行模块启动
			ret_int = cp_start_manager(mm_array[i], &tmp_manager_info);
			if (ret_int) {
				cp_app_log(error, app, "start_app_manager() error! start %s error! return[%d] error.",
					cp_print_manager_register_info(&(mm_array[i]->register_info), tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH),
					ret_int);
				continue;
			}
			// 			cp_app_log(notice, app, "start %s success!",
			// 				cp_print_manager_register_info(&(mm_array[i]->register_info), tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH));
		}
	}
	return 0;
}

//启动根模块管理器
cp_int32_t start_app_sub_manager(cp_app_t *app)
{
	cp_int32_t								i = 0;
	cp_int32_t								ret_int = 0;
	cp_module_manager_t						**tmp_root_manager = CP_NULL;
	cp_char_t								tmp_buf[CP_APP_DEFAULT_BUFFER_LENGTH] = { 0, };



	if (!app) {
		return -1;
	}

	for (i = 0; i < (cp_int32_t)cp_array_max_size(&app->root_module_manager_array); i++)	{
		tmp_root_manager = cp_array_get(&(app->root_module_manager_array), i);
		if (!(*tmp_root_manager) || !cp_array_is_empty(&(*tmp_root_manager)->module_manager_register)) {
			continue;
		}
		//开始启动各个模块管理器
		ret_int = cp_manager_start_all_sub_manager((*tmp_root_manager));
		if (ret_int) {
			cp_manager_log(error, (*tmp_root_manager), "cp_manager_start_all_sub_manager() error! create %s error! return [%d].",
				cp_print_manager_register_info(&(*tmp_root_manager)->register_info, tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH),
				ret_int);
			continue;
		}
	}

	return 0;
}

//停止所有的根模块管理器
cp_int32_t stop_app_root_manager(cp_app_t *app, cp_module_manager_t **mm_array, cp_int32_t mm_size)
{
	cp_int32_t					i = 0;
	cp_int32_t					ret_int = 0;
	cp_char_t					tmp_buf[CP_APP_DEFAULT_BUFFER_LENGTH] = { 0, };


	if (!mm_array || !mm_size) {
		return 0;
	}

	//开始创建各个模块管理器
	for (i = 0; i < CP_GET_LIBRARY_REAL_MODULE_TYPE(cp_module_manager_type_end); i++) {
		if (!mm_array[0]) {
			continue;
		}
		//调用句柄进行模块停止
		ret_int = cp_stop_manager(mm_array[i]);
		if (ret_int) {
			cp_app_log(error, app, "stop_app_manager() error! stop %s error! return[%d] error.",
				cp_print_manager_register_info(&(mm_array[i]->register_info), tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH),
				ret_int);
			continue;
		}
// 		cp_app_log(notice, app, "stop %s success!",
// 			cp_print_manager_register_info(&(mm_array[i]->register_info), tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH));
	}
	return 0;
}

//函数说明: 停止所有的子模块管理器
cp_int32_t stop_app_sub_manager(cp_app_t *app)
{
	cp_int32_t								i = 0;
	cp_int32_t								ret_int = 0;
	cp_module_manager_t						**tmp_root_manager = CP_NULL;
	cp_char_t								tmp_buf[CP_APP_DEFAULT_BUFFER_LENGTH] = { 0, };



	if (!app) {
		return -1;
	}

	for (i = 0; i < (cp_int32_t)cp_array_max_size(&app->root_module_manager_array); i++)	{
		tmp_root_manager = cp_array_get(&(app->root_module_manager_array), i);
		if (!(*tmp_root_manager) || !cp_array_is_empty(&(*tmp_root_manager)->module_manager_register)) {
			continue;
		}
		ret_int = cp_manager_stop_all_sub_manager((*tmp_root_manager));
		if (ret_int) {
			cp_manager_log(error, (*tmp_root_manager), "cp_manager_stop_all_sub_manager() error! create %s error! return [%d].",
				cp_print_manager_register_info(&(*tmp_root_manager)->register_info, tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH),
				ret_int);
			continue;
		}

// 		cp_app_log(notice, app, "stop all sub manager for %s success!",
// 			cp_print_manager_register_info(&((*tmp_root_manager)->register_info), tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH));
	}

	return 0;
}


/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: destroy_app_root_manager
*
* 函数说明: 销毁所有的根模块管理器
*
* 参    数: cp_app_t * app						[in]参数说明
* 参    数: cp_module_manager_t * * mm_array						[in]参数说明
* 参    数: cp_int32_t mm_size						[in]参数说明
*
* 返 回 值: cp_int32_t
*           0  : 成功
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2016-08-21 15:31:06
******************************************************************************************************/
cp_int32_t destroy_app_root_manager(cp_app_t *app, cp_module_manager_t **mm_array, cp_int32_t mm_size)
{
	cp_int32_t					i = 0;
	cp_int32_t					ret_int = 0;
	cp_char_t					tmp_buf[CP_APP_DEFAULT_BUFFER_LENGTH] = { 0, };



	if (!mm_array || !mm_size) {
		return 0;
	}

	//销毁各个模块管理器
	//1、这里先销毁非pool manager
	for (i = 0; i < CP_GET_LIBRARY_REAL_MODULE_TYPE(cp_module_manager_type_end); i++) {
		if (mm_array[i] && cp_module_manager_type_pool != mm_array[i]->register_info.type) {
			//ret_int = cp_manager_destroy_all_sub_manager(mm_array[i]->)
			//调用句柄进行模块停止
			ret_int = cp_destroy_manager(app, mm_array[i]);
			if (ret_int) {
				cp_app_log(error, app, "destroy_app_manager() error! destroy %s error! return[%d] error.",
					cp_print_manager_register_info(&(mm_array[i]->register_info), tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH),
					ret_int);
				continue;
			}
			// 		cp_log_debug(app->logger, "destroy %s success!",
			// 			cp_print_manager_register_info(&(mm_array[i]->register_info), tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH));
		}
	}

	//销毁各个模块管理器
	//2、在销毁pool manager部分
	for (i = 0; i < CP_GET_LIBRARY_REAL_MODULE_TYPE(cp_module_manager_type_end); i++) {
		if (mm_array[i] && cp_module_manager_type_pool == mm_array[i]->register_info.type) {
			//调用句柄进行模块停止
			ret_int = cp_destroy_manager(app, mm_array[i]);
			if (ret_int) {
				cp_app_log(error, app, "destroy_app_manager() error! destroy %s error! return[%d] error.",
					cp_print_manager_register_info(&(mm_array[i]->register_info), tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH),
					ret_int);
				continue;
			}
			// 		cp_log_debug(app->logger, "destroy %s success!",
			// 			cp_print_manager_register_info(&(mm_array[i]->register_info), tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH));
		}
	}

	//cp_free(mm_array);
	return 0;
}

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: destroy_app_sub_manager
*
* 函数说明: 销毁所有的子模块管理器
*
* 参    数: cp_app_t * app						[in]参数说明
*
* 返 回 值: cp_int32_t
*           0  : 成功
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2016-08-21 15:31:32
******************************************************************************************************/
cp_int32_t destroy_app_sub_manager(cp_app_t *app)
{
	cp_int32_t								i = 0;
	cp_int32_t								ret_int = 0;
	cp_module_manager_t						**tmp_root_manager = CP_NULL;
	cp_char_t								tmp_buf[CP_APP_DEFAULT_BUFFER_LENGTH] = { 0, };



	if (!app) {
		return -1;
	}

	for (i = 0; i < (cp_int32_t)cp_array_max_size(&app->root_module_manager_array); i++) {
		tmp_root_manager = cp_array_get(&(app->root_module_manager_array), i);
		if (!(*tmp_root_manager) || !cp_array_is_empty(&(*tmp_root_manager)->module_manager_register)) {
			continue;
		}
		ret_int = cp_manager_destroy_all_sub_manager((*tmp_root_manager));
		if (ret_int) {
			cp_manager_log(error, (*tmp_root_manager), "cp_manager_destroy_all_sub_manager() error! create %s error! return [%d].",
				cp_print_manager_register_info(&(*tmp_root_manager)->register_info, tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH),
				ret_int);
			continue;
		}
	}

	return 0;
}

//初始化app
cp_int32_t init_app_manager(cp_app_t *app, cp_module_manager_t **mm_array, cp_int32_t mm_size)
{
	cp_int32_t						ret_int = 0;


	//初始化根模块管理器
	ret_int = init_app_root_manager(app, mm_array, mm_size);
	if (ret_int) {
		cp_app_log(error, app, "init_app_root_manager() error! ");
		return ret_int;
	}

	//初始化子模块管理器信息
	ret_int = init_app_sub_manager(app);
	if (ret_int) {
		cp_app_log(error, app, "init_app_sub_manager() error! ");
		return ret_int;
	}

	return 0;
}
//启动这个app
cp_int32_t start_app_manager(cp_app_t *app, cp_module_manager_t **mm_array, cp_int32_t mm_size)
{
	cp_int32_t						ret_int = 0;


	//启动根模块管理器
	ret_int = start_app_root_manager(app, mm_array, mm_size);
	if (ret_int) {
		cp_app_log(error, app, "start_app_root_manager() error! ");
		return ret_int;
	}

	//启动子模块管理器信息
	ret_int = start_app_sub_manager(app);
	if (ret_int) {
		cp_app_log(error, app, "start_app_sub_manager() error! ");
		return ret_int;
	}

	return 0;
}

cp_int32_t stop_app_manager(cp_app_t *app, cp_module_manager_t **mm_array, cp_int32_t mm_size)
{
	cp_int32_t						ret_int = 0;


	//停止子模块管理器信息
	ret_int = stop_app_sub_manager(app);
	if (ret_int) {
		cp_app_log(error, app, "stop_app_sub_manager() error! ");
		return ret_int;
	}

	//停止根模块管理器
	ret_int = stop_app_root_manager(app, mm_array, mm_size);
	if (ret_int) {
		cp_app_log(error, app, "stop_app_root_manager() error! ");
		return ret_int;
	}

	return 0;
}

cp_int32_t destroy_app_manager(cp_app_t *app, cp_module_manager_t **mm_array, cp_int32_t mm_size)
{
	cp_int32_t						ret_int = 0;


	//销毁子模块管理器信息
	ret_int = destroy_app_sub_manager(app);
	if (ret_int) {
		cp_app_log(error, app, "destroy_app_sub_manager() error! ");
		return ret_int;
	}

	//销毁根模块管理器
	ret_int = destroy_app_root_manager(app, mm_array, mm_size);
	if (ret_int) {
		cp_app_log(error, app, "destroy_app_root_manager() error! ");
		return ret_int;
	}

	return 0;
}

cp_int32_t start_daemon_signal_thread(cp_app_t *app)
{
	cp_int32_t			tmp_ret_int = 0;
	cp_char_t			tmp_buf[CP_APP_DEFAULT_BUFFER_LENGTH] = { 0, };


	if (cp_global_daemon_info) {
		cp_global_daemon_info->signal_thread = cp_create_thread(app, cp_global_daemon_info->signal_thread_cb, app);
		if (!cp_global_daemon_info->signal_thread) {
			cp_app_log(fatal, app, "cp_create_thread() error!");

#if defined(__linux__)
			tmp_ret_int = kill(cp_global_daemon_info->master_pid, SIGQUIT);
			if (tmp_ret_int < 0) {
				cp_app_log(fatal, app,
					"start_daemon_signal_thread() failed. stop cp_app[%s]. master process[%d] is exit. worker process[%d] is exit. kill() return[%d] failed",
					cp_print_app_info(app->app_info, tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH),
					cp_global_daemon_info->master_pid,
					cp_global_daemon_info->work_pid,
					tmp_ret_int
					);
			}
			exit(0);
#endif

			return -1;
		}
	}
	return 0;
}
