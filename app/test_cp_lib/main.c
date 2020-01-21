/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-23

Description:

**************************************************************************/
#include "cp_core.h"
#include "cp_include.h"
#include "cp_daemon.h"
#include "cp_test_cp_lib.h"



/************************************************************************/
/* 引入app info变量                                                      */
/************************************************************************/
CP_EXTERN_GLOBAL_APP_INFO();



int main(int argc, char** argv) {
	char			*tmp_str_env_daemon_mode = CP_NULL;
	int				is_used_daemon = 1;									//表示默认使用守护模式


	/********************************************************************************************************************/
	/* 这里定义一些全局变量，大致内容如下：																				*/
	/*cp_app_t		           *cp_app;																					*/
	/*cp_app_info_t		        cp_entry_app_info = { type, name, version, description, NULL, 0, NULL };						*/
	/*cp_app_create_handle	    app_create_handle = create_handle;												     	*/
	/*cp_app_destroy_handle	app_destroy_handle = destroy_handle;													    */
	/********************************************************************************************************************/
	cp_app_register(0, "css_test_cp_lib", 1, "css test_cp_lib", (cp_app_create_handle)cp_test_cp_lib_create, (cp_app_destroy_handle)cp_test_cp_lib_destroy);

	tmp_str_env_daemon_mode = cp_get_set_null_env(CP_DEFAULT_ENV_CP_DAEMON_MODE, CP_DEFAULT_CONF_FILE);
	if (tmp_str_env_daemon_mode) {
		if (!cp_strcmp(tmp_str_env_daemon_mode, CP_DEFAULT_ENV_CP_DAEMON_MODE_NO)) {
			is_used_daemon = 0;
			cp_log_printf("app[%s] no used daemon mode. [%s=%s]\r\n",
				cp_global_app_info.name,
				CP_DEFAULT_ENV_CP_DAEMON_MODE,
				tmp_str_env_daemon_mode);
		}
	}

	if (is_used_daemon) {
		cp_daemon_start_app(&cp_global_app_info);
	}
	else {
		cp_general_start_app(&cp_global_app_info);
	}
	return 0;
}