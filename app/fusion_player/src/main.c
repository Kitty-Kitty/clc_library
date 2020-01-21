/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-23

Description:

**************************************************************************/
#include "cp_core.h"
#include "cp_include.h"
#include "cp_daemon.h"
#include "cp_fusion_player.h"




/************************************************************************/
/* 引入app info变量                                                      */
/************************************************************************/
CP_EXTERN_GLOBAL_APP_INFO();




int main(int argc, char** argv) {
	cp_char_t				*tmp_str_env_daemon_mode = CP_NULL;
	cp_int32_t				is_used_daemon = 1;									//表示默认使用守护模式




	/********************************************************************************************************************/
	/* 这里定义一些全局变量，大致内容如下：																				*/
	/*cp_app_t		           *cp_app;																					*/
	/*cp_app_info_t		        cp_global_app_info = { type, name, version, description, NULL, 0, NULL };						*/
	/*cp_app_create_handle	    app_create_handle = create_handle;												     	*/
	/*cp_app_destroy_handle	app_destroy_handle = destroy_handle;													    */
	/********************************************************************************************************************/
	cp_app_register(CP_FUSION_PLAYER_TYPE, CP_FUSION_PLAYER_VAR, cp_fusion_player_version, CP_FUSION_PLAYER_VER,
		(cp_app_create_handle)cp_fusion_player_create, (cp_app_destroy_handle)cp_fusion_player_destroy);

#if defined WIN32
	CP_APP_ENTRY_CONFIG_PATH("E:\\project_work\\project\\css_workspace\\cp_player\\app\\fusion_player\\configs\\css.conf");
// #else
// 	CP_APP_ENTRY_CONFIG_PATH("/home/pi/Project/cp_player/build/debug/cp_fusion_player/configs/css.conf");
#endif 

	tmp_str_env_daemon_mode = cp_get_set_null_env(CP_DEFAULT_ENV_CP_DAEMON_MODE, CP_DEFAULT_ENV_CP_DAEMON_MODE_YES);
	if (tmp_str_env_daemon_mode) {
		if (!cp_strcmp(tmp_str_env_daemon_mode, CP_DEFAULT_ENV_CP_DAEMON_MODE_NO)) {
			is_used_daemon = 0;
			cp_log_printf("app[%s] no used daemon mode. [%s=%s]",
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