/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/
#include "cp_session.h"



cp_session_t *cp_session_create();

/*模块创建接口，表示创建一个模块*/
cp_int32_t init_session(cp_session_t *session, const cp_session_info_t *session_info);
/*模块打开运行接口，在模块init之后，会被调用*/
cp_int32_t open_session(cp_session_t *session, const cp_session_info_t *session_info);
/*读取模块数据，flag为读取模式的扩展标志。默认为0，其他为预留*/
cp_int32_t read_session(cp_session_t *session, cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag);
/*写模块数据，flag为写模式的扩展标志。默认为0，其他为预留*/
cp_int32_t write_session(cp_session_t *session, const cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag);
/*关闭模块*/
cp_int32_t close_session(cp_session_t *session);
/*退出模块*/
cp_int32_t exit_session(cp_session_t *session);
/*设置模块参数*/
cp_int32_t set_option_session(cp_session_t *session, cp_int32_t optname, const cp_void_t* optval);
cp_int32_t get_option_session(cp_session_t *session, cp_int32_t optname, cp_void_t* optval);





cp_session_t* cp_create_session(const cp_app_t *app, cp_session_info_t *info)
{
	cp_session_manager_t			*tmp_manager = CP_NULL;
	cp_module_manager_info_t		tmp_module_manager_info;



	//获取manager
	CP_MODULE_MANAGER_INFO_SET_TYPE(&tmp_module_manager_info, cp_module_manager_type_session);
	tmp_manager = (cp_session_manager_t*)cp_get_manager(app, &tmp_module_manager_info);
	if (!tmp_manager) {
		return CP_NULL;
	}
	//创建session返回
	return (cp_session_t*)cp_manager_create_module(tmp_manager, info);
}

cp_int32_t cp_detory_session(cp_session_t *session)
{
	return cp_manager_destroy_module(session->manager, session);
}

/*模块创建接口，表示创建一个模块*/
cp_int32_t init_session(cp_session_t *session, const cp_session_info_t *session_info)
{
	return 0;
}
/*模块打开运行接口，在模块init之后，会被调用*/
cp_int32_t open_session(cp_session_t *session, const cp_session_info_t *session_info)
{
	return 0;
}
/*读取模块数据，flag为读取模式的扩展标志。默认为0，其他为预留*/
cp_int32_t read_session(cp_session_t *session, cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag)
{
	return 0;
}
/*写模块数据，flag为写模式的扩展标志。默认为0，其他为预留*/
cp_int32_t write_session(cp_session_t *session, const cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag)
{
	return 0;
}
/*关闭模块*/
cp_int32_t close_session(cp_session_t *session)
{
	return 0;
}
/*退出模块*/
cp_int32_t exit_session(cp_session_t *session)
{
	return 0;
}
/*设置模块参数*/
cp_int32_t set_option_session(cp_session_t *session, cp_int32_t optname, const cp_void_t* optval)
{
	return 0;
}
cp_int32_t get_option_session(cp_session_t *session, cp_int32_t optname, cp_void_t* optval)
{
	return 0;
}





