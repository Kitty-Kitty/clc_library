/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/
#include "cp_memh_session.h"



cp_memh_session_t *cp_memh_session_create();

/*模块初始化接口，在模块create之后，会被调用*/
cp_int32_t init_memh_session(cp_memh_session_t *memh_session, const cp_memh_session_info_t *memh_session_info);
/*模块打开运行接口，在模块init之后，会被调用*/
cp_int32_t open_memh_session(cp_memh_session_t *memh_session, const cp_memh_session_info_t *memh_session_info);
/*读取模块数据，flag为读取模式的扩展标志。默认为0，其他为预留*/
cp_int32_t read_memh_session(cp_memh_session_t *memh_session, cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag);
/*写模块数据，flag为写模式的扩展标志。默认为0，其他为预留*/
cp_int32_t write_memh_session(cp_memh_session_t *memh_session, const cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag);
/*关闭模块*/
cp_int32_t close_memh_session(cp_memh_session_t *memh_session);
/*退出模块*/
cp_int32_t exit_memh_session(cp_memh_session_t *memh_session);
/*设置模块参数*/
cp_int32_t set_option_memh_session(cp_memh_session_t *memh_session, cp_int32_t optname, const cp_void_t* optval);
cp_int32_t get_option_memh_session(cp_memh_session_t *memh_session, cp_int32_t optname, cp_void_t* optval);




/*模块初始化接口，在模块create之后，会被调用*/
cp_int32_t init_memh_session(cp_memh_session_t *memh_session, const cp_memh_session_info_t *memh_session_info)
{
	return 0;
}
/*模块打开运行接口，在模块init之后，会被调用*/
cp_int32_t open_memh_session(cp_memh_session_t *memh_session, const cp_memh_session_info_t *memh_session_info)
{
	return 0;
}
/*读取模块数据，flag为读取模式的扩展标志。默认为0，其他为预留*/
cp_int32_t read_memh_session(cp_memh_session_t *memh_session, cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag)
{
	return 0;
}
/*写模块数据，flag为写模式的扩展标志。默认为0，其他为预留*/
cp_int32_t write_memh_session(cp_memh_session_t *memh_session, const cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag)
{
	return 0;
}
/*关闭模块*/
cp_int32_t close_memh_session(cp_memh_session_t *memh_session)
{
	return 0;
}
/*退出模块*/
cp_int32_t exit_memh_session(cp_memh_session_t *memh_session)
{
	return 0;
}
/*设置模块参数*/
cp_int32_t set_option_memh_session(cp_memh_session_t *memh_session, cp_int32_t optname, const cp_void_t* optval)
{
	return 0;
}
cp_int32_t get_option_memh_session(cp_memh_session_t *memh_session, cp_int32_t optname, cp_void_t* optval)
{
	return 0;
}







