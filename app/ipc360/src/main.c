/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-23

Description:

**************************************************************************/
#include "cp_core.h"
#include "cp_include.h"
#include "cp_daemon.h"
#include "cp_ipc.h"



/************************************************************************/
/* 引入app info变量                                                      */
/************************************************************************/
CP_EXTERN_GLOBAL_APP_INFO();



int main(int argc, char** argv) {
	char			*tmp_str_env_daemon_mode = CP_NULL;
	int				is_used_daemon = 1;									//表示默认使用守护模式




	/********************************************************************************************************************/
	/* 这里定义一些全局变量，大致内容如下：																				*/
	/*cp_app_info_t		        cp_global_app_info = { type, name, version, description, NULL, 0, NULL };						*/
	/*cp_app_create_handle	    cp_global_app_create_handle = create_handle;												     	*/
	/*cp_app_destroy_handle		cp_global_app_destroy_handle = destroy_handle;													*/
	/********************************************************************************************************************/
	cp_app_register(CP_IPC_TYPE, CP_IPC_VAR, cp_ipc_version, CP_IPC_VER,
		(cp_app_create_handle)cp_ipc_create, (cp_app_destroy_handle)cp_ipc_destroy);

#if defined WIN32
	CP_APP_ENTRY_CONFIG_PATH("E:\\project_work\\project\\css_workspace\\cp_player\\app\\ipc360\\configs\\ipc.conf");
#endif 

	tmp_str_env_daemon_mode = cp_get_set_null_env(CP_DEFAULT_ENV_CP_DAEMON_MODE, CP_DEFAULT_ENV_CP_DAEMON_MODE_YES);
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

#if 0
int main(int argc, char** argv) {
	int					ret_int = 0;
	char				tmp_buf[CP_APP_DEFAULT_BUFFER_LENGTH] = { 0, };



	printf("-------------------------------------------%s / %s (%d)-------------------------------------------\r\n", 
		cp_global_app_info.name, 
		cp_version_itoa(cp_global_app_info.version, tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH), 
		cp_global_app_info.version);

	printf("starting app : \t%s\r\n", cp_print_app_info(&cp_global_app_info, tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH));
	printf("library info : \t%s\r\n", cp_get_format_version(tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH));

	//创建设备
	cp_app = cp_global_app_create_handle(&cp_global_app_info);
	if (!cp_app) {
		printf("create app failed! : \t%s\r\n", cp_print_app_info(&cp_global_app_info, tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH));
		return 0;
	}
	else {
		printf("create app successed! : \t%s\r\n", cp_print_app_info(&cp_global_app_info, tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH));
	}

	/*初始化设备，包括
	 *读取设备配置文件
	 *日志模块
	 *初始化TCP/UDP监听服务
	*/
	ret_int = cp_app->init(cp_app, &cp_global_app_info);
	if (ret_int) {
		printf("init app failed! : \t%s\r\n", cp_print_app_info(&cp_global_app_info, tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH));
		return 0;
	}
	else {
		cp_log_notice(cp_app->logger, "init app successed! : %s", cp_print_app_info(&cp_global_app_info, tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH));
	}

	ret_int = cp_app->start(cp_app, &cp_global_app_info);
	if (ret_int) {
		cp_log_fatal(cp_app->logger, "start app failed! : %s", cp_print_app_info(&cp_global_app_info, tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH));
		return 0;
	}
	else {
		cp_log_notice(cp_app->logger, "start app successed! : %s", cp_print_app_info(&cp_global_app_info, tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH));
	}

	while (1) {
		cp_sleep_msec(10000);
	}

	return 0;
}
#endif