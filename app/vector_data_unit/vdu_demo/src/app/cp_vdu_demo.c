/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/


#include "cp_vdu_demo.h"
#include "cp_process_core.h"
#include "cp_vdu_demo_module_list.h"
#include "cp_vdu_demo_proc.h"




extern cp_module_manager_register_t m_module_manager_list[];
extern cp_int32_t m_module_manager_size;




cp_int32_t init_vdu_demo(cp_vdu_demo_t *vdu_demo, cp_app_info_t *app_info);
cp_int32_t start_vdu_demo(cp_vdu_demo_t *vdu_demo, cp_app_info_t *app_info);
cp_int32_t stop_vdu_demo(cp_vdu_demo_t *vdu_demo);


cp_vdu_demo_t* cp_vdu_demo_create(cp_app_info_t *app_info) {
	cp_vdu_demo_t		*vdu_demo = CP_NULL;


	vdu_demo = cp_malloc(sizeof(cp_vdu_demo_t));
	if (vdu_demo) {
		cp_memset(vdu_demo, 0, sizeof(cp_vdu_demo_t));
	}
	else{
		printf("cp_vdu_demo_create () error reason: malloc failed!");
	}
	//分配一个内存池
	vdu_demo->mpool = cp_create_mpool(CP_APP_DEFAULT_BUFFER_LENGTH);
	if (!vdu_demo->mpool) {
		cp_log_printf("cp_app_create () error reason: cp_create_mpool() failed!");
		return CP_NULL;
	}
	//创建一个信息结构内容
	vdu_demo->app_info = (cp_app_info_t *)cp_mpalloc(vdu_demo->mpool, sizeof(cp_vdu_demo_info_t));
	if (!vdu_demo->app_info) {
		cp_log_fatal(vdu_demo->logger, "malloc vdu_demo info error!\r\n");
		return CP_NULL;
	}
	else{
		memset(vdu_demo->app_info, 0, sizeof(cp_vdu_demo_info_t));
		*(vdu_demo->app_info) = *app_info;
	}
	//设置app的几个句柄函数
	CP_APP_SET_HANDLERS(vdu_demo, vdu_demo);
	//创建保存模块管理器注册器的空间
	create_app_root_register_memory((cp_app_t*)vdu_demo, CP_GET_LIBRARY_REAL_MODULE_TYPE(cp_module_manager_type_end));

	return vdu_demo;
}

cp_int32_t init_vdu_demo(cp_vdu_demo_t *vdu_demo, cp_app_info_t *app_info) {
	cp_int32_t			ret_int = 0;
	cp_bool_t			ret_bool = cp_false;




	//初始化根模块管理器注册器信息
	CP_ROOT_MODULE_MANAGER_DEPENDENT(vdu_demo, vdu_demo);
	//初始化app部分内容
	ret_int = cp_init_app(vdu_demo, app_info);
	if (ret_int) {
		cp_log_printf("init_vdu_demo() error. init_app() error.");
		return ret_int;
	}

	//初始化子模块管理器注册器信息
	CP_SUB_MODULE_MANAGER_DEPENDENT(vdu_demo, vdu_demo);
	ret_int = init_app_manager((cp_app_t*)vdu_demo,
		vdu_demo->root_module_manager_array.elts, vdu_demo->root_module_manager_array.nelts);
	if (ret_int) {
		cp_log_printf("init_vdu_demo() error. init_app_manager() error.");
		return ret_int;
	}

	//初始化模块注册器信息
	CP_MODULE_DEPENDENT(vdu_demo, vdu_demo);

	//将app info信息保存
	*vdu_demo->app_info = *app_info;
	//初始化vdu_demo 相关的信息
	ret_bool = init_vdu_demo_info(vdu_demo, (cp_vdu_demo_info_t *)(vdu_demo->app_info));
	if (!ret_bool) {
		cp_app_log(error, vdu_demo, "init_vdu_demo() error. init_vdu_demo_info() error.");
		return ret_int;
	}
	//初始化vdu_demo其他信息
	ret_int = init_vdu_demo_other(vdu_demo, vdu_demo->app_info);
	if (ret_int) {
		cp_app_log(error, vdu_demo, "init_vdu_demo() error. init_vdu_demo_other() error.");
		return ret_int;
	}
	cp_app_log(notice, vdu_demo, "hello world!");

	return 0;
}

cp_int32_t start_vdu_demo(cp_vdu_demo_t *vdu_demo, cp_app_info_t *app_info) {
	cp_int32_t			ret_int = 0;



	ret_int = cp_start_app(vdu_demo, vdu_demo->app_info);
	if (ret_int) {
		cp_log_printf("start_vdu_demo() error. start_app() error.");
		return ret_int;
	}
	ret_int = start_vdu_demo_other(vdu_demo, vdu_demo->app_info);
	if (ret_int) {
		cp_log_printf("start_vdu_demo() error. start_vdu_demo_other() error.");
		return ret_int;
	}

	cp_app_log(notice, vdu_demo, "hello world!");
	
	return 0;
}

cp_int32_t stop_vdu_demo(cp_vdu_demo_t *vdu_demo) {
	cp_int32_t			ret_int = 0;


	ret_int = vdu_demo->logger->log_stop(vdu_demo->logger, 0, CP_NULL);
	if (ret_int) {
		printf("log stop error");
		return 0;
	}

	return 0;
}

cp_int32_t cp_vdu_demo_destroy(cp_vdu_demo_t *vdu_demo) {
	cp_int32_t			ret_int = 0;


	ret_int = cp_conf_destroy(vdu_demo->conf);
	if (ret_int) {
		printf("cp_conf_destroy error!\r\n");
		return -1;
	}

	ret_int = cp_log_destroy(vdu_demo->logger);
	if (ret_int) {
		printf("cp_log_destroy error!\r\n");
		return -1;
	}

	return 0;
}




