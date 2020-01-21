/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/


#include "cp_ecam.h"
#include "cp_process_core.h"
#include "cp_ecam_module_list.h"
#include "cp_ecam_proc.h"




extern cp_module_manager_register_t m_module_manager_list[];
extern cp_int32_t m_module_manager_size;




cp_int32_t init_ecam(cp_ecam_t *ecam, cp_app_info_t *app_info);
cp_int32_t start_ecam(cp_ecam_t *ecam, cp_app_info_t *app_info);
cp_int32_t stop_ecam(cp_ecam_t *ecam);


cp_ecam_t* cp_ecam_create(cp_app_info_t *app_info) {
	cp_ecam_t		*ecam = CP_NULL;


	ecam = cp_malloc(sizeof(cp_ecam_t));
	if (ecam) {
		cp_memset(ecam, 0, sizeof(cp_ecam_t));
	}
	else{
		printf("cp_ecam_create () error reason: malloc failed!");
	}
	//分配一个内存池
	ecam->mpool = cp_create_mpool(CP_APP_DEFAULT_BUFFER_LENGTH);
	if (!ecam->mpool) {
		cp_log_printf("cp_app_create () error reason: cp_create_mpool() failed!");
		return CP_NULL;
	}
	//创建一个信息结构内容
	ecam->app_info = (cp_app_info_t *)cp_mpalloc(ecam->mpool, sizeof(cp_ecam_info_t));
	if (!ecam->app_info) {
		cp_log_fatal(ecam->logger, "malloc ecam info error!\r\n");
		return CP_NULL;
	}
	else{
		memset(ecam->app_info, 0, sizeof(cp_ecam_info_t));
		*(ecam->app_info) = *app_info;
	}
	//设置app的几个句柄函数
	CP_APP_SET_HANDLERS(ecam, ecam);
	//创建保存模块管理器注册器的空间
	create_app_root_register_memory((cp_app_t*)ecam, CP_GET_LIBRARY_REAL_MODULE_TYPE(cp_module_manager_type_end));

	return ecam;
}

cp_int32_t init_ecam(cp_ecam_t *ecam, cp_app_info_t *app_info) {
	cp_int32_t			ret_int = 0;
	cp_bool_t			ret_bool = cp_false;




	//初始化根模块管理器注册器信息
	CP_ROOT_MODULE_MANAGER_DEPENDENT(ecam, ecam);
	//初始化app部分内容
	ret_int = cp_init_app(ecam, app_info);
	if (ret_int) {
		cp_log_printf("init_ecam() error. init_app() error.");
		return ret_int;
	}

	//初始化子模块管理器注册器信息
	CP_SUB_MODULE_MANAGER_DEPENDENT(ecam, ecam);
	ret_int = init_app_manager((cp_app_t*)ecam,
		ecam->root_module_manager_array.elts, ecam->root_module_manager_array.nelts);
	if (ret_int) {
		cp_log_printf("init_ecam() error. init_app_manager() error.");
		return ret_int;
	}

	//初始化模块注册器信息
	CP_MODULE_DEPENDENT(ecam, ecam);

	//将app info信息保存
	*ecam->app_info = *app_info;
	//初始化ecam 相关的信息
	ret_bool = init_ecam_info(ecam, (cp_ecam_info_t *)(ecam->app_info));
	if (!ret_bool) {
		cp_log_error(ecam->logger, "init_ecam() error. init_ecam_info() error.");
		return ret_int;
	}
	//初始化ecam其他信息
	ret_int = init_ecam_other(ecam, ecam->app_info);
	if (ret_int) {
		cp_log_error(ecam->logger, "init_ecam() error. init_ecam_other() error.");
		return ret_int;
	}

	return 0;
}

cp_int32_t start_ecam(cp_ecam_t *ecam, cp_app_info_t *app_info) {
	cp_int32_t			ret_int = 0;



	ret_int = cp_start_app(ecam, ecam->app_info);
	if (ret_int) {
		cp_log_printf("start_ecam() error. start_app() error.");
		return ret_int;
	}
	ret_int = start_ecam_other(ecam, ecam->app_info);
	if (ret_int) {
		cp_log_printf("start_ecam() error. start_ecam_other() error.");
		return ret_int;
	}

	cp_log_notice(ecam->logger, "hello world!");
	
	return 0;
}

cp_int32_t stop_ecam(cp_ecam_t *ecam) {
	cp_int32_t			ret_int = 0;


	ret_int = ecam->logger->log_stop(ecam->logger, 0, CP_NULL);
	if (ret_int) {
		printf("log stop error");
		return 0;
	}

	return 0;
}

cp_int32_t cp_ecam_destroy(cp_ecam_t *ecam) {
	cp_int32_t			ret_int = 0;


	ret_int = cp_conf_destroy(ecam->conf);
	if (ret_int) {
		printf("cp_conf_destroy error!\r\n");
		return -1;
	}

	ret_int = cp_log_destroy(ecam->logger);
	if (ret_int) {
		printf("cp_log_destroy error!\r\n");
		return -1;
	}

	return 0;
}




