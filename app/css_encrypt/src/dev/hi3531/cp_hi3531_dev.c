/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/
#include "cp_hi3531_dev.h"
#include "cp_third_party.h"
#include "cp_include.h"
#include "css_status.h"




/*模块创建接口，表示创建一个模块*/
cp_int32_t init_hi3531_dev(cp_hi3531_dev_t *hi3531_dev, const cp_hi3531_dev_info_t *hi3531_dev_info);
/*模块打开运行接口，在模块init之后，会被调用*/
cp_int32_t open_hi3531_dev(cp_hi3531_dev_t *hi3531_dev, const cp_hi3531_dev_info_t *hi3531_dev_info);
/*读取模块数据，flag为读取模式的扩展标志。默认为0，其他为预留*/
cp_int32_t read_hi3531_dev(cp_hi3531_dev_t *hi3531_dev, cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag);
/*写模块数据，flag为写模式的扩展标志。默认为0，其他为预留*/
cp_int32_t write_hi3531_dev(cp_hi3531_dev_t *hi3531_dev, const cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag);
/*关闭模块*/
cp_int32_t close_hi3531_dev(cp_hi3531_dev_t *hi3531_dev);
/*退出模块*/
cp_int32_t exit_hi3531_dev(cp_hi3531_dev_t *hi3531_dev);
/*设置模块参数*/
cp_int32_t set_option_hi3531_dev(cp_hi3531_dev_t *hi3531_dev, cp_int32_t optname, const cp_void_t* optval);
/*获取模块参数*/
cp_int32_t get_option_hi3531_dev(cp_hi3531_dev_t *hi3531_dev, cp_int32_t optname, cp_void_t* optval);




/*创建一个模块*/
cp_hi3531_dev_t* create_hi3531_dev(cp_module_register_t *register_info, cp_codec_manager_t *manager, cp_hi3531_dev_info_t *info)
{
	cp_int32_t							ret_int = 0;
	cp_hi3531_dev_t						*tmp_module = CP_NULL;
	cp_pool_info_t						tmp_pool_info = { 0, };


	if (!register_info || !manager || !info) {
		return CP_NULL;
	}

	tmp_module = cp_malloc_module(manager, cp_hi3531_dev_t, &tmp_pool_info);
	if (!tmp_module) {
		return CP_NULL;
	}
	CP_MODULE_SET_HANDLERS(tmp_module, hi3531_dev);
	return tmp_module;
}

/*释放模块*/
cp_int32_t destroy_hi3531_dev(cp_codec_manager_t *manager, cp_hi3531_dev_t* hi3531_dev)
{
	if (!manager || !hi3531_dev) {
		return -1;
	}
	cp_free_module(hi3531_dev);
	return 0;
}

/*模块创建接口，表示创建一个模块*/
cp_int32_t init_hi3531_dev(cp_hi3531_dev_t *hi3531_dev,
	const cp_hi3531_dev_info_t *hi3531_dev_info)
{
	return 0;
}

/*模块打开运行接口，在模块init之后，会被调用*/
cp_int32_t open_hi3531_dev(cp_hi3531_dev_t *hi3531_dev,
	const cp_hi3531_dev_info_t *hi3531_dev_info)
{
	if (!hi3531_dev) {
		return -1;
	}

	return 0;
}

/*读取模块数据，flag为读取模式的扩展标志。默认为0，其他为预留*/
cp_int32_t read_hi3531_dev(cp_hi3531_dev_t *hi3531_dev,
	cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag)
{
	return 0;
}

/*写模块数据，flag为写模式的扩展标志。默认为0，其他为预留*/
cp_int32_t write_hi3531_dev(cp_hi3531_dev_t *hi3531_dev,
	const cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag)
{
	return 0;
}

/*关闭模块*/
cp_int32_t close_hi3531_dev(cp_hi3531_dev_t *hi3531_dev)
{
	return 0;
}

/*退出模块*/
cp_int32_t exit_hi3531_dev(cp_hi3531_dev_t *hi3531_dev)
{
	return 0;
}

/*设置模块参数*/
cp_int32_t set_option_hi3531_dev(cp_hi3531_dev_t *hi3531_dev, cp_int32_t optname, const cp_void_t* optval)
{
	return 0;
}

cp_int32_t get_option_hi3531_dev(cp_hi3531_dev_t *hi3531_dev, cp_int32_t optname, cp_void_t* optval)
{
	return 0;
}
