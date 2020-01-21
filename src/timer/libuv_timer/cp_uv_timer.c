/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/

#include <assert.h>
#include "cp_uv_timer.h"



/*模块创建接口，表示创建一个模块*/
cp_int32_t init_uv_timer(cp_uv_timer_t *uv_timer, const cp_uv_timer_info_t *info);
/*模块打开运行接口，在模块init之后，会被调用*/
cp_int32_t open_uv_timer(cp_uv_timer_t *uv_timer, const cp_uv_timer_info_t *info);
/*读取模块数据，flag为读取模式的扩展标志。默认为0，其他为预留*/
cp_int32_t read_uv_timer(cp_uv_timer_t *uv_timer, cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag);
/*写模块数据，flag为写模式的扩展标志。默认为0，其他为预留*/
cp_int32_t write_uv_timer(cp_uv_timer_t *uv_timer, const cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag);
/*关闭模块*/
cp_int32_t close_uv_timer(cp_uv_timer_t *uv_timer);
/*退出模块*/
cp_int32_t exit_uv_timer(cp_uv_timer_t *uv_timer);
/*设置模块参数*/
cp_int32_t set_option_uv_timer(cp_uv_timer_t *uv_timer, cp_int32_t optname, const cp_void_t* optval);
cp_int32_t get_option_uv_timer(cp_uv_timer_t *uv_timer, cp_int32_t optname, cp_void_t* optval);
/*设置uv_timer的回调函数*/
void uv_timer_callback(uv_timer_t* handle);

cp_uv_timer_t* create_uv_timer(cp_module_register_t *register_info, cp_timer_manager_t *manager, cp_uv_timer_info_t *info)
{
	cp_int32_t							ret_int = 0;
	cp_uv_timer_t						*tmp_module = CP_NULL;
	cp_pool_info_t						tmp_pool_info = { 0, };


	if (!register_info || !manager || !info) {
		return CP_NULL;
	}
	tmp_module = cp_malloc_module(manager, cp_uv_timer_t, &tmp_pool_info);
	if (!tmp_module) {
		return CP_NULL;
	}

	tmp_module->timer_cb = info->timer_cb;
	tmp_module->uv_timer.data = tmp_module;
	CP_MODULE_SET_HANDLERS(tmp_module, uv_timer);
	return tmp_module;
}

cp_int32_t destroy_uv_timer(cp_timer_manager_t *manager, cp_uv_timer_t* timer)
{
	if (!manager || !timer) {
		return -1;
	}

	cp_free_module(timer);
	return 0;
}



/*模块创建接口，表示创建一个模块*/
cp_int32_t init_uv_timer(cp_uv_timer_t *uv_timer, const cp_uv_timer_info_t *info)
{
	cp_uv_timer_manager_t				*manager = (cp_uv_timer_manager_t*)uv_timer->manager;

	uv_timer->timer_cb = info->timer_cb;
	uv_timer_init(manager->loop, &(uv_timer->uv_timer));

	return 0;
}
/*模块打开运行接口，在模块init之后，会被调用*/
cp_int32_t open_uv_timer(cp_uv_timer_t *uv_timer, const cp_uv_timer_info_t *info)
{
	uv_timer->timer_cb = info->timer_cb;
	uv_timer_start(&(uv_timer->uv_timer), uv_timer_callback, info->timeout, info->repeat);
	return 0;
}
/*读取模块数据，flag为读取模式的扩展标志。默认为0，其他为预留*/
cp_int32_t read_uv_timer(cp_uv_timer_t *uv_timer, cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag)
{
	return 0;
}
/*写模块数据，flag为写模式的扩展标志。默认为0，其他为预留*/
cp_int32_t write_uv_timer(cp_uv_timer_t *uv_timer, const cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag)
{
	return 0;
}
/*关闭模块*/
cp_int32_t close_uv_timer(cp_uv_timer_t *uv_timer)
{
	cp_int32_t ret;
	ret = uv_timer_stop(&(uv_timer->uv_timer));

	return ret;
}
/*退出模块*/
cp_int32_t exit_uv_timer(cp_uv_timer_t *uv_timer)
{
	return 0;
}
/*设置模块参数*/
cp_int32_t set_option_uv_timer(cp_uv_timer_t *uv_timer, cp_int32_t optname, const cp_void_t* optval)
{
	switch (optname) {
		case cp_uv_timer_option_again:
		{
			return uv_timer_again(&(uv_timer->uv_timer));
		}
		break;
		case cp_uv_timer_option_set_repeat:
		{
			cp_uint64_t repeat = *(cp_uint64_t*)optval;
			uv_timer_set_repeat(&(uv_timer->uv_timer), repeat);
		}
		break;
		default:
		{
			return -1;
		}
	}
	return 0;
}

cp_int32_t get_option_uv_timer(cp_uv_timer_t *uv_timer, cp_int32_t optname, cp_void_t* optval)
{
	switch (optname) {
		case cp_uv_timer_option_get_repeat:
		{
			*(cp_uint64_t*)optval = uv_timer_get_repeat(&(uv_timer->uv_timer));
		}
		break;
		default:
		{
			return -1;
		}
	}
	return 0;
}

void uv_timer_callback(uv_timer_t* handle)
{
	cp_uv_timer_t *uv_timer = handle->data;
	uv_timer->timer_cb((cp_timer_t *)uv_timer);
}

