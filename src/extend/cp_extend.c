/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/
#include "cp_extend.h"
#include "cp_include.h"



/*模块创建接口，表示创建一个模块*/
cp_int32_t init_extend(cp_extend_t *extend, const cp_extend_info_t *extend_info);
/*模块打开运行接口，在模块init之后，会被调用*/
cp_int32_t open_extend(cp_extend_t *extend, const cp_extend_info_t *extend_info);
/*读取模块数据，flag为读取模式的扩展标志。默认为0，其他为预留*/
cp_int32_t read_extend(cp_extend_t *extend, cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag);
/*写模块数据，flag为写模式的扩展标志。默认为0，其他为预留*/
cp_int32_t write_extend(cp_extend_t *extend, const cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag);
/*关闭模块*/
cp_int32_t close_extend(cp_extend_t *extend);
/*退出模块*/
cp_int32_t exit_extend(cp_extend_t *extend);
/*设置模块参数*/
cp_int32_t set_option_extend(cp_extend_t *extend, cp_int32_t optname, const cp_void_t* optval);
cp_int32_t get_option_extend(cp_extend_t *extend, cp_int32_t optname, cp_void_t* optval);



/*模块创建接口，表示创建一个模块*/
cp_int32_t init_extend(cp_extend_t *extend, const cp_extend_info_t *extend_info)
{
	return 0;
}
/*模块打开运行接口，在模块init之后，会被调用*/
cp_int32_t open_extend(cp_extend_t *extend, const cp_extend_info_t *extend_info)
{
	return 0;
}
/*读取模块数据，flag为读取模式的扩展标志。默认为0，其他为预留*/
cp_int32_t read_extend(cp_extend_t *extend, cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag)
{
	return 0;
}
/*写模块数据，flag为写模式的扩展标志。默认为0，其他为预留*/
cp_int32_t write_extend(cp_extend_t *extend, const cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag)
{
	return 0;
}
/*关闭模块*/
cp_int32_t close_extend(cp_extend_t *extend)
{
	return 0;
}
/*退出模块*/
cp_int32_t exit_extend(cp_extend_t *extend)
{
	return 0;
}
/*设置模块参数*/
cp_int32_t set_option_extend(cp_extend_t *extend, cp_int32_t optname, const cp_void_t* optval)
{
	return 0;
}
cp_int32_t get_option_extend(cp_extend_t *extend, cp_int32_t optname, cp_void_t* optval)
{
	return 0;
}


