/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/
#include "cp_func.h"



cp_func_t *cp_func_create();
/*模块创建接口，表示创建一个模块*/
cp_int32_t init_func(cp_func_t *func, const cp_func_info_t *func_info);
/*模块打开运行接口，在模块init之后，会被调用*/
cp_int32_t open_func(cp_func_t *func, const cp_func_info_t *func_info);
/*读取模块数据，flag为读取模式的扩展标志。默认为0，其他为预留*/
cp_int32_t read_func(cp_func_t *func, cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag);
/*写模块数据，flag为写模式的扩展标志。默认为0，其他为预留*/
cp_int32_t write_func(cp_func_t *func, const cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag);
/*关闭模块*/
cp_int32_t close_func(cp_func_t *func);
/*退出模块*/
cp_int32_t exit_func(cp_func_t *func);
/*设置模块参数*/
cp_int32_t set_option_func(cp_func_t *func, cp_int32_t optname, const cp_void_t* optval);
cp_int32_t get_option_func(cp_func_t *func, cp_int32_t optname, cp_void_t* optval);




/*模块创建接口，表示创建一个模块*/
cp_int32_t init_func(cp_func_t *func, const cp_func_info_t *func_info)
{
	return 0;
}
/*模块打开运行接口，在模块init之后，会被调用*/
cp_int32_t open_func(cp_func_t *func, const cp_func_info_t *func_info)
{
	return 0;
}
/*读取模块数据，flag为读取模式的扩展标志。默认为0，其他为预留*/
cp_int32_t read_func(cp_func_t *func, cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag)
{
	return 0;
}
/*写模块数据，flag为写模式的扩展标志。默认为0，其他为预留*/
cp_int32_t write_func(cp_func_t *func, const cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag)
{
	return 0;
}
/*关闭模块*/
cp_int32_t close_func(cp_func_t *func)
{
	return 0;
}
/*退出模块*/
cp_int32_t exit_func(cp_func_t *func)
{
	return 0;
}
/*设置模块参数*/
cp_int32_t set_option_func(cp_func_t *func, cp_int32_t optname, const cp_void_t* optval)
{
	return 0;
}
cp_int32_t get_option_func(cp_func_t *func, cp_int32_t optname, cp_void_t* optval)
{
	return 0;
}







