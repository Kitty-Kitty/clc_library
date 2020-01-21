/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/


#include "cp_demo.h"
#include "cp_process_core.h"
#include "cp_demo_module_list.h"
#include "cp_demo_proc.h"




extern cp_module_manager_register_t m_module_manager_list[];
extern cp_int32_t m_module_manager_size;




cp_int32_t init_demo(cp_demo_t *demo, cp_app_info_t *app_info);
cp_int32_t start_demo(cp_demo_t *demo, cp_app_info_t *app_info);
cp_int32_t stop_demo(cp_demo_t *demo);


cp_demo_t* cp_demo_create(cp_app_info_t *app_info) {
	cp_demo_t		*demo = CP_NULL;


	demo = cp_malloc(sizeof(cp_demo_t));
	if (demo) {
		cp_memset(demo, 0, sizeof(cp_demo_t));
	}
	else{
		printf("cp_demo_create () error reason: malloc failed!");
	}
	//分配一个内存池
	demo->mpool = cp_create_mpool(CP_APP_DEFAULT_BUFFER_LENGTH);
	if (!demo->mpool) {
		cp_log_printf("cp_app_create () error reason: cp_create_mpool() failed!");
		return CP_NULL;
	}
	//创建一个信息结构内容
	demo->app_info = (cp_app_info_t *)cp_mpalloc(demo->mpool, sizeof(cp_demo_info_t));
	if (!demo->app_info) {
		cp_log_fatal(demo->logger, "malloc demo info error!\r\n");
		return CP_NULL;
	}
	else{
		memset(demo->app_info, 0, sizeof(cp_demo_info_t));
		*(demo->app_info) = *app_info;
	}
	//设置app的几个句柄函数
	CP_APP_SET_HANDLERS(demo, demo);
	//创建保存模块管理器注册器的空间
	create_app_root_register_memory((cp_app_t*)demo, CP_GET_LIBRARY_REAL_MODULE_TYPE(cp_module_manager_type_end));

	return demo;
}

cp_int32_t init_demo(cp_demo_t *demo, cp_app_info_t *app_info) {
	cp_int32_t			ret_int = 0;
	cp_bool_t			ret_bool = cp_false;




	//初始化根模块管理器注册器信息
	CP_ROOT_MODULE_MANAGER_DEPENDENT(demo, demo);
	//初始化app部分内容
	ret_int = cp_init_app(demo, app_info);
	if (ret_int) {
		cp_log_printf("init_demo() error. init_app() error.");
		return ret_int;
	}

	//初始化子模块管理器注册器信息
	CP_SUB_MODULE_MANAGER_DEPENDENT(demo, demo);
	ret_int = init_app_manager((cp_app_t*)demo,
		demo->root_module_manager_array.elts, demo->root_module_manager_array.nelts);
	if (ret_int) {
		cp_log_printf("init_demo() error. init_app_manager() error.");
		return ret_int;
	}

	//初始化模块注册器信息
	CP_MODULE_DEPENDENT(demo, demo);

	//将app info信息保存
	*demo->app_info = *app_info;
	//初始化demo 相关的信息
	ret_bool = init_demo_info(demo, (cp_demo_info_t *)(demo->app_info));
	if (!ret_bool) {
		cp_app_log(error, demo, "init_demo() error. init_demo_info() error.");
		return ret_int;
	}
	//初始化demo其他信息
	ret_int = init_demo_other(demo, demo->app_info);
	if (ret_int) {
		cp_app_log(error, demo, "init_demo() error. init_demo_other() error.");
		return ret_int;
	}
	cp_app_log(notice, demo, "hello world!");

	return 0;
}

cp_int32_t start_demo(cp_demo_t *demo, cp_app_info_t *app_info) {
	cp_int32_t			ret_int = 0;



	ret_int = cp_start_app(demo, demo->app_info);
	if (ret_int) {
		cp_log_printf("start_demo() error. start_app() error.");
		return ret_int;
	}
	ret_int = start_demo_other(demo, demo->app_info);
	if (ret_int) {
		cp_log_printf("start_demo() error. start_demo_other() error.");
		return ret_int;
	}

	cp_app_log(notice, demo, "hello world!");
	
	return 0;
}

cp_int32_t stop_demo(cp_demo_t *demo) {
	cp_int32_t			ret_int = 0;


	ret_int = demo->logger->log_stop(demo->logger, 0, CP_NULL);
	if (ret_int) {
		printf("log stop error");
		return 0;
	}

	return 0;
}

cp_int32_t cp_demo_destroy(cp_demo_t *demo) {
	cp_int32_t			ret_int = 0;


	ret_int = cp_conf_destroy(demo->conf);
	if (ret_int) {
		printf("cp_conf_destroy error!\r\n");
		return -1;
	}

	ret_int = cp_log_destroy(demo->logger);
	if (ret_int) {
		printf("cp_log_destroy error!\r\n");
		return -1;
	}

	return 0;
}




