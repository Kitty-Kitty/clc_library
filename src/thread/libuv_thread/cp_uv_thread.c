
/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/
#include "cp_include.h"
#include "cp_uv_thread_core.h"





/*模块创建接口，表示创建一个模块*/
cp_int32_t init_uv_thread(cp_uv_thread_t *uv_thread, const cp_uv_thread_info_t *info);
/*模块打开运行接口，在模块init之后，会被调用*/
cp_int32_t open_uv_thread(cp_uv_thread_t *uv_thread, const cp_uv_thread_info_t *info);
/*读取模块数据，flag为读取模式的扩展标志。默认为0，其他为预留*/
cp_int32_t read_uv_thread(cp_uv_thread_t *uv_thread, cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag);
/*写模块数据，flag为写模式的扩展标志。默认为0，其他为预留*/
cp_int32_t write_uv_thread(cp_uv_thread_t *uv_thread, const cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag);
/*关闭模块*/
cp_int32_t close_uv_thread(cp_uv_thread_t *uv_thread);
/*退出模块*/
cp_int32_t exit_uv_thread(cp_uv_thread_t *uv_thread);
/*设置模块参数*/
cp_int32_t set_option_uv_thread(cp_uv_thread_t *uv_thread, cp_int32_t optname, const cp_void_t* optval);
cp_int32_t get_option_uv_thread(cp_uv_thread_t *uv_thread, cp_int32_t optname, cp_void_t* optval);





cp_uv_thread_t* create_uv_thread(cp_module_register_t *register_info, cp_thread_manager_t *manager, cp_uv_thread_info_t *info)
{
	cp_int32_t							ret_int = 0;
	cp_uv_thread_t						*tmp_module = CP_NULL;
	cp_pool_info_t						tmp_pool_info = { 0, };


	if (!register_info || !manager || !info) {
		return CP_NULL;
	}

	tmp_module = cp_malloc_module(manager, cp_uv_thread_t, &tmp_pool_info);
	if (!tmp_module) {
		return CP_NULL;
	}

	ret_int = uv_thread_create(&tmp_module->thread, info->thread_cb, info->args);
	if (ret_int) {
		cp_log_error(manager->logger, "create_uv_thread() error. uv_thread_create() error.");
		cp_free_module(tmp_module);
		return CP_NULL;
	}
	CP_MODULE_SET_HANDLERS(tmp_module, uv_thread);
	return tmp_module;
}

cp_int32_t destroy_uv_thread(cp_thread_manager_t *manager, cp_uv_thread_t* uv_thread)
{
	if (!manager || !uv_thread) {
		return -1;
	}
	cp_free_module(uv_thread);
	return 0;
}

/*模块创建接口，表示创建一个模块*/
cp_int32_t init_uv_thread(cp_uv_thread_t *uv_thread, const cp_uv_thread_info_t *info)
{
	return 0;
}
/*模块打开运行接口，在模块init之后，会被调用*/
cp_int32_t open_uv_thread(cp_uv_thread_t *uv_thread, const cp_uv_thread_info_t *info)
{

	return 0;
}
/*读取模块数据，flag为读取模式的扩展标志。默认为0，其他为预留*/
cp_int32_t read_uv_thread(cp_uv_thread_t *uv_thread, cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag)
{
	return 0;
}
/*写模块数据，flag为写模式的扩展标志。默认为0，其他为预留*/
cp_int32_t write_uv_thread(cp_uv_thread_t *uv_thread, const cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag)
{
	return 0;
}
/*关闭模块*/
cp_int32_t close_uv_thread(cp_uv_thread_t *uv_thread)
{
	return 0;
}
/*退出模块*/
cp_int32_t exit_uv_thread(cp_uv_thread_t *uv_thread)
{
	return 0;
}
/*设置模块参数*/
cp_int32_t set_option_uv_thread(cp_uv_thread_t *uv_thread, cp_int32_t optname, const cp_void_t* optval)
{
	switch (optname) {
		case cp_thread_set_option_join:
		{
			return uv_thread_join(&uv_thread->thread);
		}
		break;
		default:
		{
			return -1;
		}
	}
	return 0;
}

cp_int32_t get_option_uv_thread(cp_uv_thread_t *uv_thread, cp_int32_t optname, cp_void_t* optval)
{
	switch (optname) {
		case cp_thread_get_option_self:
		{
			cp_uv_thread_t *uv_thread = (cp_uv_thread_t*)optval;
			uv_thread->thread = uv_thread_self();
		}
		break;
		default:
		{
			return -1;
		}
	}
	return 0;
}



#if 0

/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/

#include <assert.h>
#include "cp_uv_thread.h"



cp_thread_t cp_uv_thread_self(void){
	return uv_thread_self();
}
int cp_uv_thread_create(cp_thread_manager_t *tm, cp_thread_t* tid, cp_thread_cb entry, void* arg){
	return uv_thread_create(tid, entry, arg);
}

int cp_uv_thread_join(cp_thread_manager_t *tm, cp_thread_t *tid){
	return uv_thread_join(tid);
}

int cp_uv_thread_equal(cp_thread_manager_t *tm, const cp_thread_t* t1, const cp_thread_t* t2){
	return uv_thread_equal(t1, t2);
}


int cp_uv_create_thread_pool(cp_thread_manager_t *tm){
	return 0;
}
int cp_uv_join_thread_pool(cp_thread_manager_t *tm){


	return 0;
}
int cp_uv_start_thread_pool(cp_thread_manager_t *tm){

	return 0;
}
int cp_uv_cancle_thread_pool(cp_thread_manager_t *tm){


	return 0;
}

cp_uv_thread_t* create_uv_thread(cp_module_register_t *register_info, cp_thread_manager_t *manager, cp_uv_thread_info_t *info)
{

	return CP_NULL;
}

cp_int32_t destroy_uv_thread(cp_thread_manager_t *manager, cp_uv_thread_t* thread)
{
	return 0;
}

#endif
