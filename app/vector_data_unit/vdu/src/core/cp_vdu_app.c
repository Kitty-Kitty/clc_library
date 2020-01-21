/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/


#include "cp_vdu_app.h"
#include "cp_process_core.h"
#include "cp_vdu_module_list.h"
#include "cp_vdu_proc.h"




extern cp_module_manager_register_t m_module_manager_list[];
extern cp_int32_t m_module_manager_size;




cp_int32_t init_vdu_app(cp_vdu_app_t *vdu_app, cp_app_info_t *app_info);
cp_int32_t start_vdu_app(cp_vdu_app_t *vdu_app, cp_app_info_t *app_info);
cp_int32_t stop_vdu_app(cp_vdu_app_t *vdu_app);


cp_vdu_app_t* cp_vdu_app_create(cp_app_info_t *app_info) {
	cp_vdu_app_t		*vdu_app = CP_NULL;


	vdu_app = cp_malloc(sizeof(cp_vdu_app_t));
	if (vdu_app) {
		cp_memset(vdu_app, 0, sizeof(cp_vdu_app_t));
	}
	else {
		printf("cp_vdu_app_create () error reason: malloc failed!");
	}

	//分配一个内存池
	vdu_app->mpool = cp_create_mpool(CP_APP_DEFAULT_BUFFER_LENGTH);
	if (!vdu_app->mpool) {
		cp_log_printf("cp_app_create () error reason: cp_create_mpool() failed!");
		return CP_NULL;
	}

	//创建一个信息结构内容
	vdu_app->app_info = (cp_app_info_t *)cp_mpalloc(vdu_app->mpool, sizeof(cp_vdu_app_info_t));
	if (!vdu_app->app_info) {
		cp_log_fatal(vdu_app->logger, "malloc vdu_app info error!\r\n");
		return CP_NULL;
	}
	else {
		memset(vdu_app->app_info, 0, sizeof(cp_vdu_app_info_t));
		*(vdu_app->app_info) = *app_info;
	}

	//设置app的几个句柄函数
	CP_APP_SET_HANDLERS(vdu_app, vdu_app);

	//创建保存模块管理器注册器的空间
	create_app_root_register_memory((cp_app_t*)vdu_app, CP_GET_LIBRARY_REAL_MODULE_TYPE(cp_module_manager_type_end));

	return vdu_app;
}

cp_int32_t init_vdu_app(cp_vdu_app_t *vdu_app, cp_app_info_t *app_info) {
	cp_int32_t			ret_int = 0;
	cp_bool_t			ret_bool = cp_false;



	//初始化根模块管理器注册器信息
	CP_ROOT_MODULE_MANAGER_DEPENDENT(vdu_app, vdu_app);

	//这里定义宏来表示是否启动日志
#ifdef CP_VDU_USED_LOG_SYSTEM
	//初始化app部分内容
	ret_int = cp_init_app(vdu_app, app_info);
	if (ret_int) {
		cp_log_printf("init_vdu_app() error. init_app() error.");
		return ret_int;
	}
#else
	//创建模块
	ret_int = create_app_root_manager((cp_app_t *)vdu_app,
		vdu_app->root_module_manager_register.elts, cp_array_max_size(&vdu_app->root_module_manager_register));
	if (ret_int) {
		cp_app_log(error, vdu_app, "init_vdu_app() error! create_app_root_manager() error!");
		return ret_int;
	}

#endif

	//初始化子模块管理器注册器信息
	CP_SUB_MODULE_MANAGER_DEPENDENT(vdu_app, vdu_app);
	ret_int = init_app_manager((cp_app_t*)vdu_app,
		vdu_app->root_module_manager_array.elts, vdu_app->root_module_manager_array.nelts);
	if (ret_int) {
		cp_app_log(error, vdu_app, "init_vdu_app() error. init_app_manager() error.");
		return ret_int;
	}

	//初始化模块注册器信息
	CP_MODULE_DEPENDENT(vdu_app, vdu_app);

	//将app info信息保存
	*vdu_app->app_info = *app_info;

	//初始化vdu_app 相关的信息
	ret_bool = init_vdu_info(vdu_app, (cp_vdu_app_info_t *)(vdu_app->app_info));
	if (!ret_bool) {
		cp_app_log(error, vdu_app, "init_vdu_app() error. init_vdu_info() error.");
		return ret_int;
	}

	//初始化vdu_app其他信息
	ret_int = init_vdu_other(vdu_app, vdu_app->app_info);
	if (ret_int) {
		cp_app_log(error, vdu_app, "init_vdu_app() error. init_vdu_other() error.");
		return ret_int;
	}
	cp_app_log(notice, vdu_app, "hello world!");

	return 0;
}

cp_int32_t start_vdu_app(cp_vdu_app_t *vdu_app, cp_app_info_t *app_info) {
	cp_int32_t			ret_int = 0;



	//启动app
	ret_int = cp_start_app(vdu_app, vdu_app->app_info);
	if (ret_int) {
		cp_log_printf("start_vdu_app() error. start_app() error.");
		return ret_int;
	}

	//启动other内容
	ret_int = start_vdu_other(vdu_app, vdu_app->app_info);
	if (ret_int) {
		cp_log_printf("start_vdu_app() error. start_vdu_other() error.");
		return ret_int;
	}

	cp_app_log(notice, vdu_app, "hello world!");

	return 0;
}

cp_int32_t stop_vdu_app(cp_vdu_app_t *vdu_app) {
	cp_int32_t			ret_int = 0;



//这里定义宏来表示是否启动日志
#ifdef CP_VDU_USED_LOG_SYSTEM
	ret_int = cp_stop_app(vdu_app);
	if (ret_int) {
		cp_log_printf("stop_vdu_app() error. cp_stop_app() error.");
		return ret_int;
	}
#else
	ret_int = stop_app_manager((cp_app_t*)vdu_app,
		vdu_app->root_module_manager_array.elts, vdu_app->root_module_manager_array.nelts);
	if (ret_int) {
		cp_log_printf("stop_vdu_app() error. stop_app_manager() error.");
		return ret_int;
	}
#endif

	//停止other内容
	ret_int = stop_vdu_other(vdu_app, vdu_app->app_info);
	if (ret_int) {
		cp_log_printf("stop_vdu_app() error. stop_vdu_other() error.");
		return ret_int;
	}

	//销毁管理器
	ret_int = destroy_app_manager((cp_app_t*)vdu_app,
		vdu_app->root_module_manager_array.elts, vdu_app->root_module_manager_array.nelts);
	if (ret_int) {
		cp_log_printf("stop_vdu_app() error. destroy_app_manager() error.");
		return ret_int;
	}

	return 0;
}

cp_int32_t cp_vdu_app_destroy(cp_vdu_app_t *vdu_app) {
	cp_int32_t			ret_int = 0;



	//销毁根注册管理器
	ret_int = destroy_app_root_register_memory((cp_app_t*)vdu_app);
	if (ret_int) {
		cp_log_printf("stop_vdu_app() error. destroy_app_root_register_memory() error.");
		return ret_int;
	}

//这里定义宏来表示是否启动日志
#ifdef CP_VDU_USED_LOG_SYSTEM
	ret_int = cp_conf_destroy(vdu_app->conf);
	if (ret_int) {
		printf("cp_conf_destroy error!\r\n");
		return -1;
	}

	ret_int = cp_log_destroy(vdu_app->logger);
	if (ret_int) {
		printf("cp_log_destroy error!\r\n");
		return -1;
	}
#endif

	if (vdu_app->mpool) {
		cp_destroy_mpool(vdu_app->mpool);
	}
	
	if (vdu_app) {
		cp_free(vdu_app);
	}

	return 0;
}




