/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/


#include "cp_ipc.h"
#include "cp_process_core.h"
#include "cp_ipc_module_list.h"
#include "cp_ipc_proc.h"




extern cp_module_manager_register_t m_module_manager_list[];
extern cp_int32_t m_module_manager_size;




cp_int32_t init_ipc(cp_ipc_t *ipc, cp_app_info_t *app_info);
cp_int32_t start_ipc(cp_ipc_t *ipc, cp_app_info_t *app_info);
cp_int32_t stop_ipc(cp_ipc_t *ipc);


cp_ipc_t* cp_ipc_create(cp_app_info_t *app_info) {
	cp_ipc_t		*ipc = CP_NULL;


	ipc = cp_malloc(sizeof(cp_ipc_t));
	if (ipc) {
		cp_memset(ipc, 0, sizeof(cp_ipc_t));
	}
	else{
		printf("cp_ipc_create () error reason: malloc failed!");
	}
	//分配一个内存池
	ipc->mpool = cp_create_mpool(CP_APP_DEFAULT_BUFFER_LENGTH);
	if (!ipc->mpool) {
		cp_log_printf("cp_app_create () error reason: cp_create_mpool() failed!");
		return CP_NULL;
	}
	//创建一个信息结构内容
	ipc->app_info = (cp_app_info_t *)cp_mpalloc(ipc->mpool, sizeof(cp_ipc_info_t));
	if (!ipc->app_info) {
		cp_log_fatal(ipc->logger, "malloc ipc info error!\r\n");
		return CP_NULL;
	}
	else{
		memset(ipc->app_info, 0, sizeof(cp_ipc_info_t));
		*(ipc->app_info) = *app_info;
	}
	//设置app的几个句柄函数
	CP_APP_SET_HANDLERS(ipc, ipc);
	//创建保存模块管理器注册器的空间
	create_app_root_register_memory((cp_app_t*)ipc, CP_GET_LIBRARY_REAL_MODULE_TYPE(cp_module_manager_type_end));

	return ipc;
}

cp_int32_t init_ipc(cp_ipc_t *ipc, cp_app_info_t *app_info) {
	cp_int32_t			ret_int = 0;
	cp_bool_t			ret_bool = cp_false;




	//初始化根模块管理器注册器信息
	CP_ROOT_MODULE_MANAGER_DEPENDENT(ipc, ipc);
	//初始化app部分内容
	ret_int = cp_init_app(ipc, app_info);
	if (ret_int) {
		cp_log_printf("init_ipc() error. init_app() error.");
		return ret_int;
	}

	//初始化子模块管理器注册器信息
	CP_SUB_MODULE_MANAGER_DEPENDENT(ipc, ipc);
	ret_int = init_app_manager((cp_app_t*)ipc,
		ipc->root_module_manager_array.elts, ipc->root_module_manager_array.nelts);
	if (ret_int) {
		cp_log_printf("init_ipc() error. init_app_manager() error.");
		return ret_int;
	}

	//初始化模块注册器信息
	CP_MODULE_DEPENDENT(ipc, ipc);

	//将app info信息保存
	*ipc->app_info = *app_info;
	//初始化ipc 相关的信息
	ret_bool = init_ipc_info(ipc, (cp_ipc_info_t *)(ipc->app_info));
	if (!ret_bool) {
		cp_log_error(ipc->logger, "init_ipc() error. init_ipc_info() error.");
		return ret_int;
	}
	//初始化ipc其他信息
	ret_int = init_ipc_other(ipc, ipc->app_info);
	if (ret_int) {
		cp_log_error(ipc->logger, "init_ipc() error. init_ipc_other() error.");
		return ret_int;
	}

	return 0;
}

cp_int32_t start_ipc(cp_ipc_t *ipc, cp_app_info_t *app_info) {
	cp_int32_t			ret_int = 0;



	ret_int = cp_start_app(ipc, ipc->app_info);
	if (ret_int) {
		cp_log_printf("start_ipc() error. start_app() error.");
		return ret_int;
	}
	ret_int = start_ipc_other(ipc, ipc->app_info);
	if (ret_int) {
		cp_log_printf("start_ipc() error. start_ipc_other() error.");
		return ret_int;
	}

	cp_log_notice(ipc->logger, "hello world!");
	
	return 0;
}

cp_int32_t stop_ipc(cp_ipc_t *ipc) {
	cp_int32_t			ret_int = 0;


	ret_int = ipc->logger->log_stop(ipc->logger, 0, CP_NULL);
	if (ret_int) {
		printf("log stop error");
		return 0;
	}

	return 0;
}

cp_int32_t cp_ipc_destroy(cp_ipc_t *ipc) {
	cp_int32_t			ret_int = 0;


	ret_int = cp_conf_destroy(ipc->conf);
	if (ret_int) {
		printf("cp_conf_destroy error!\r\n");
		return -1;
	}

	ret_int = cp_log_destroy(ipc->logger);
	if (ret_int) {
		printf("cp_log_destroy error!\r\n");
		return -1;
	}

	return 0;
}




