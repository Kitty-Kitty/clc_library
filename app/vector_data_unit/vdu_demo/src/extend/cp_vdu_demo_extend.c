/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/
#include "cp_vdu_demo_extend.h"
#include "cp_third_party.h"
#include "cp_include.h"
#include "css_status.h"



cp_vdu_demo_extend_t *cp_vdu_demo_extend_create();
/*模块创建接口，表示创建一个模块*/
cp_int32_t init_vdu_demo_extend(cp_vdu_demo_extend_t *vdu_demo_extend, const cp_vdu_demo_extend_info_t *vdu_demo_extend_info);
/*模块打开运行接口，在模块init之后，会被调用*/
cp_int32_t open_vdu_demo_extend(cp_vdu_demo_extend_t *vdu_demo_extend, const cp_vdu_demo_extend_info_t *vdu_demo_extend_info);
/*读取模块数据，flag为读取模式的扩展标志。默认为0，其他为预留*/
cp_int32_t read_vdu_demo_extend(cp_vdu_demo_extend_t *vdu_demo_extend, cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag);
/*写模块数据，flag为写模式的扩展标志。默认为0，其他为预留*/
cp_int32_t write_vdu_demo_extend(cp_vdu_demo_extend_t *vdu_demo_extend, const cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag);
/*关闭模块*/
cp_int32_t close_vdu_demo_extend(cp_vdu_demo_extend_t *vdu_demo_extend);
/*退出模块*/
cp_int32_t exit_vdu_demo_extend(cp_vdu_demo_extend_t *vdu_demo_extend);
/*设置模块参数*/
cp_int32_t set_option_vdu_demo_extend(cp_vdu_demo_extend_t *vdu_demo_extend, cp_int32_t optname, const cp_void_t* optval);
cp_int32_t get_option_vdu_demo_extend(cp_vdu_demo_extend_t *vdu_demo_extend, cp_int32_t optname, cp_void_t* optval);



cp_vdu_demo_extend_t* create_vdu_demo_extend(cp_module_register_t *register_info, cp_socket_manager_t *manager, cp_vdu_demo_extend_info_t *info)
{
	cp_int32_t							ret_int = 0;
	cp_vdu_demo_extend_t					*tmp_module = CP_NULL;
	cp_pool_info_t						tmp_pool_info = { 0, };


	if (!register_info || !manager || !info) {
		return CP_NULL;
	}

	tmp_module = cp_malloc_module(manager, cp_vdu_demo_extend_t, &tmp_pool_info);
	if (!tmp_module) {
		return CP_NULL;
	}

	return tmp_module;
}

cp_int32_t destroy_vdu_demo_extend(cp_vdu_demo_extend_manager_t *manager, cp_vdu_demo_extend_t* vdu_demo_extend)
{
	if (!manager || !vdu_demo_extend) {
		return -1;
	}
	cp_free_module(vdu_demo_extend);
	return 0;
}

/*模块创建接口，表示创建一个模块*/
cp_int32_t init_vdu_demo_extend(cp_vdu_demo_extend_t *vdu_demo_extend, const cp_vdu_demo_extend_info_t *vdu_demo_extend_info)
{
	return 0;
}
/*模块打开运行接口，在模块init之后，会被调用*/
cp_int32_t open_vdu_demo_extend(cp_vdu_demo_extend_t *vdu_demo_extend, const cp_vdu_demo_extend_info_t *vdu_demo_extend_info)
{
	return 0;
}
/*读取模块数据，flag为读取模式的扩展标志。默认为0，其他为预留*/
cp_int32_t read_vdu_demo_extend(cp_vdu_demo_extend_t *vdu_demo_extend, cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag)
{
	return 0;
}
/*写模块数据，flag为写模式的扩展标志。默认为0，其他为预留*/
cp_int32_t write_vdu_demo_extend(cp_vdu_demo_extend_t *vdu_demo_extend, const cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag)
{
	return 0;
}
/*关闭模块*/
cp_int32_t close_vdu_demo_extend(cp_vdu_demo_extend_t *vdu_demo_extend)
{
	return 0;
}
/*退出模块*/
cp_int32_t exit_vdu_demo_extend(cp_vdu_demo_extend_t *vdu_demo_extend)
{
	return 0;
}
/*设置模块参数*/
cp_int32_t set_option_vdu_demo_extend(cp_vdu_demo_extend_t *vdu_demo_extend, cp_int32_t optname, const cp_void_t* optval)
{
	return 0;
}

cp_int32_t get_option_vdu_demo_extend(cp_vdu_demo_extend_t *vdu_demo_extend, cp_int32_t optname, cp_void_t* optval)
{
	return 0;
}


