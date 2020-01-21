/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/


#include "cp_css_encrypt.h"
#include "cp_process_core.h"
#include "cp_css_encrypt_module_list.h"
#include "cp_css_encrypt_proc.h"




extern cp_module_manager_register_t m_module_manager_list[];
extern cp_int32_t m_module_manager_size;




cp_int32_t init_css_encrypt(cp_css_encrypt_t *css_encrypt, cp_app_info_t *app_info);
cp_int32_t start_css_encrypt(cp_css_encrypt_t *css_encrypt, cp_app_info_t *app_info);
cp_int32_t stop_css_encrypt(cp_css_encrypt_t *css_encrypt);


cp_css_encrypt_t* cp_css_encrypt_create(cp_app_info_t *app_info) {
	cp_css_encrypt_t		*css_encrypt = CP_NULL;


	css_encrypt = cp_malloc(sizeof(cp_css_encrypt_t));
	if (css_encrypt) {
		cp_memset(css_encrypt, 0, sizeof(cp_css_encrypt_t));
	}
	else{
		printf("cp_css_encrypt_create () error reason: malloc failed!");
	}
	//分配一个内存池
	css_encrypt->mpool = cp_create_mpool(CP_APP_DEFAULT_BUFFER_LENGTH);
	if (!css_encrypt->mpool) {
		cp_log_printf("cp_app_create () error reason: cp_create_mpool() failed!");
		return CP_NULL;
	}
	//创建一个信息结构内容
	css_encrypt->app_info = (cp_app_info_t *)cp_mpalloc(css_encrypt->mpool, sizeof(cp_css_encrypt_info_t));
	if (!css_encrypt->app_info) {
		cp_log_fatal(css_encrypt->logger, "malloc css_encrypt info error!\r\n");
		return CP_NULL;
	}
	else{
		memset(css_encrypt->app_info, 0, sizeof(cp_css_encrypt_info_t));
		*(css_encrypt->app_info) = *app_info;
	}
	//设置app的几个句柄函数
	CP_APP_SET_HANDLERS(css_encrypt, css_encrypt);
	//创建保存模块管理器注册器的空间
	create_app_root_register_memory((cp_app_t*)css_encrypt, CP_GET_LIBRARY_REAL_MODULE_TYPE(cp_module_manager_type_end));

	return css_encrypt;
}

cp_int32_t init_css_encrypt(cp_css_encrypt_t *css_encrypt, cp_app_info_t *app_info) {
	cp_int32_t			ret_int = 0;
	cp_bool_t			ret_bool = cp_false;




	//初始化根模块管理器注册器信息
	CP_ROOT_MODULE_MANAGER_DEPENDENT(css_encrypt, css_encrypt);
	//初始化app部分内容
	ret_int = cp_init_app(css_encrypt, app_info);
	if (ret_int) {
		cp_log_printf("init_css_encrypt() error. init_app() error.");
		return ret_int;
	}

	//初始化子模块管理器注册器信息
	CP_SUB_MODULE_MANAGER_DEPENDENT(css_encrypt, css_encrypt);
	ret_int = init_app_manager((cp_app_t*)css_encrypt,
		css_encrypt->root_module_manager_array.elts, css_encrypt->root_module_manager_array.nelts);
	if (ret_int) {
		cp_log_printf("init_css_encrypt() error. init_app_manager() error.");
		return ret_int;
	}

	//初始化模块注册器信息
	CP_MODULE_DEPENDENT(css_encrypt, css_encrypt);

	//将app info信息保存
	*css_encrypt->app_info = *app_info;
	//初始化css_encrypt 相关的信息
	ret_bool = init_css_encrypt_info(css_encrypt, (cp_css_encrypt_info_t *)(css_encrypt->app_info));
	if (!ret_bool) {
		cp_app_log(error, css_encrypt, "init_css_encrypt() error. init_css_encrypt_info() error.");
		return ret_int;
	}
	//初始化css_encrypt其他信息
	ret_int = init_css_encrypt_other(css_encrypt, css_encrypt->app_info);
	if (ret_int) {
		cp_app_log(error, css_encrypt, "init_css_encrypt() error. init_css_encrypt_other() error.");
		return ret_int;
	}
	cp_app_log(notice, css_encrypt, "hello world!");

	return 0;
}

cp_int32_t start_css_encrypt(cp_css_encrypt_t *css_encrypt, cp_app_info_t *app_info) {
	cp_int32_t			ret_int = 0;



	ret_int = cp_start_app(css_encrypt, css_encrypt->app_info);
	if (ret_int) {
		cp_log_printf("start_css_encrypt() error. start_app() error.");
		return ret_int;
	}
	ret_int = start_css_encrypt_other(css_encrypt, css_encrypt->app_info);
	if (ret_int) {
		cp_log_printf("start_css_encrypt() error. start_css_encrypt_other() error.");
		return ret_int;
	}

	cp_app_log(notice, css_encrypt, "hello world!");
	
	return 0;
}

cp_int32_t stop_css_encrypt(cp_css_encrypt_t *css_encrypt) {
	cp_int32_t			ret_int = 0;


	ret_int = css_encrypt->logger->log_stop(css_encrypt->logger, 0, CP_NULL);
	if (ret_int) {
		printf("log stop error");
		return 0;
	}

	return 0;
}

cp_int32_t cp_css_encrypt_destroy(cp_css_encrypt_t *css_encrypt) {
	cp_int32_t			ret_int = 0;


	ret_int = cp_conf_destroy(css_encrypt->conf);
	if (ret_int) {
		printf("cp_conf_destroy error!\r\n");
		return -1;
	}

	ret_int = cp_log_destroy(css_encrypt->logger);
	if (ret_int) {
		printf("cp_log_destroy error!\r\n");
		return -1;
	}

	return 0;
}




