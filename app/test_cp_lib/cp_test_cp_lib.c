/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/

#include "cp_core.h"
#include "cp_test_cp_lib.h"
#include "cp_utils.h"
#include "prot_core.h"





extern cp_module_manager_register_t m_module_manager_list[];
extern cp_int32_t m_module_manager_size;




cp_int32_t init_test_cp_lib(cp_test_cp_lib_t *test_cp_lib, cp_app_info_t *app_info);
cp_int32_t start_test_cp_lib(cp_test_cp_lib_t *test_cp_lib, cp_app_info_t *app_info);
cp_int32_t stop_test_cp_lib(cp_test_cp_lib_t *test_cp_lib);

cp_test_cp_lib_t* cp_test_cp_lib_create(cp_app_info_t *app_info) {
	cp_test_cp_lib_t		*test_cp_lib = CP_NULL;


	test_cp_lib = cp_malloc(sizeof(cp_test_cp_lib_t));

	if (test_cp_lib){
		cp_memset(test_cp_lib, 0, sizeof(cp_test_cp_lib_t));
	}
	else{
		printf("cp_test_cp_lib_create () error reason: malloc failed!");
	}
	//分配一个内存池
	test_cp_lib->mpool = cp_create_mpool(CP_APP_DEFAULT_BUFFER_LENGTH);
	if (!test_cp_lib->mpool) {
		cp_log_printf("cp_app_create () error reason: cp_create_mpool() failed!");
		return CP_NULL;
	}
	//设置app的几个句柄函数
	CP_APP_SET_HANDLERS(test_cp_lib, test_cp_lib);
	//设置app_info的信息
	//CP_APP_INFO_SET_MODULE_MANAGER_INFO(app_info, m_module_manager_list, m_module_manager_size);
	return test_cp_lib;
}

cp_int32_t init_test_cp_lib(cp_test_cp_lib_t *test_cp_lib, cp_app_info_t *app_info) {
	cp_int32_t			ret_int = 0;


	
	ret_int = cp_init_app(test_cp_lib, app_info);
	if (ret_int) {
		cp_log_printf("init_test_cp_lib() error. init_app() error.");
		return ret_int;
	}

	cp_log_notice(test_cp_lib->logger, "hello world!");

	return 0;
}

cp_int32_t start_test_cp_lib(cp_test_cp_lib_t *test_cp_lib, cp_app_info_t *app_info) {
	cp_int32_t			ret_int = 0;



	ret_int = cp_start_app(test_cp_lib, app_info);
	if (ret_int) {
		cp_log_printf("start_test_cp_lib() error. start_app() error.");
		return ret_int;
	}

	cp_log_notice(test_cp_lib->logger, "hello world!");
	
	return 0;
}

cp_int32_t stop_test_cp_lib(cp_test_cp_lib_t *test_cp_lib) {
	cp_int32_t			ret_int = 0;


	ret_int = test_cp_lib->logger->log_stop(test_cp_lib->logger, 0, CP_NULL);
	if (ret_int) {
		printf("log stop error");
		return 0;
	}

	return 0;
}

cp_int32_t cp_test_cp_lib_destroy(cp_test_cp_lib_t *test_cp_lib) {
	cp_int32_t			ret_int = 0;


	ret_int = cp_conf_destroy(test_cp_lib->conf);
	if (ret_int) {
		printf("cp_conf_destroy error!\r\n");
		return -1;
	}

	ret_int = cp_log_destroy(test_cp_lib->logger);
	if (ret_int) {
		printf("cp_log_destroy error!\r\n");
		return -1;
	}

	return 0;
}







