/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/
#include "cp_vdu_proc.h"
#include "cp_vdu_task.h"


cp_int32_t init_vdu_other(cp_vdu_app_t *vdu, cp_app_info_t *app_info)
{
#if 0
	cp_int32_t					ret_int = 0;
	cp_vdu_app_info_t			*tmp_vdu_info = (cp_vdu_app_info_t *)(vdu->app_info);


	//创建一个timer
	vdu->timer_task = cp_create_timer((const cp_app_t *)vdu);
	if (!vdu->timer_task) {
		cp_log_error(vdu->logger, "init_vdu_other() error. cp_create_timer() error.");
		return -1;
	}
	else {
		CP_MODULE_SET_DATA(vdu->timer_task, vdu);
	}
#endif

	return 0;
}

cp_int32_t start_vdu_other(cp_vdu_app_t *vdu, cp_app_info_t *app_info)
{
#if 0
	cp_int32_t					ret_int = 0;
	cp_vdu_app_info_t			*tmp_vdu_info = (cp_vdu_app_info_t *)vdu->app_info;
	cp_char_t					tmp_buf[CP_APP_DEFAULT_BUFFER_LENGTH] = { 0, };


	//启动定时器
	ret_int = cp_start_timer(vdu->timer_task, cp_vdu_timer_task, 1000, 10000);
	if (ret_int) {
		cp_log_error(vdu->logger, "start_vdu_other() error. cp_start_timer() error.");
		return -1;
	}
#endif

	//这里获取func模块地址，存放在app中
	vdu->vdu_func = (cp_func_t *)cp_app_get_module_by_type(vdu,
		cp_vdu_manager_type_func, cp_vdu_module_type_func);
	if (!vdu->vdu_func)	{
		cp_log_error(vdu->logger, 
			"get module by type[cp_vdu_module_type_qt_svg_codec] error.");
		return -1;
	}

	return 0;
}

cp_int32_t stop_vdu_other(cp_vdu_app_t *vdu, cp_app_info_t *app_info)
{
#if 0
	cp_int32_t					ret_int = 0;
	cp_vdu_app_info_t				*tmp_vdu_info = (cp_vdu_app_info_t *)vdu->app_info;


	//停止定时器
	cp_stop_timer(vdu->timer_task);

	//销毁定时器
	cp_destroy_timer(vdu->timer_task);
#endif
	
	return 0;
}

