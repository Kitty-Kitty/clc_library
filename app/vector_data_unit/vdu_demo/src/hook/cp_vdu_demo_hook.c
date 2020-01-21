/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/
#include "cp_pool_core.h"
#include "cp_vdu_demo_hook.h"



cp_vdu_demo_hook_t *cp_vdu_demo_hook_create();

/*模块创建接口，表示创建一个模块*/
cp_int32_t init_vdu_demo_hook(cp_vdu_demo_hook_t *vdu_demo_hook, const cp_vdu_demo_hook_info_t *vdu_demo_hook_info);
/*模块打开运行接口，在模块init之后，会被调用*/
cp_int32_t open_vdu_demo_hook(cp_vdu_demo_hook_t *vdu_demo_hook, const cp_vdu_demo_hook_info_t *vdu_demo_hook_info);
/*读取模块数据，flag为读取模式的扩展标志。默认为0，其他为预留*/
cp_int32_t read_vdu_demo_hook(cp_vdu_demo_hook_t *vdu_demo_hook, cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag);
/*写模块数据，flag为写模式的扩展标志。默认为0，其他为预留*/
cp_int32_t write_vdu_demo_hook(cp_vdu_demo_hook_t *vdu_demo_hook, const cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag);
/*关闭模块*/
cp_int32_t close_vdu_demo_hook(cp_vdu_demo_hook_t *vdu_demo_hook);
/*退出模块*/
cp_int32_t exit_vdu_demo_hook(cp_vdu_demo_hook_t *vdu_demo_hook);
/*设置模块参数*/
cp_int32_t set_option_vdu_demo_hook(cp_vdu_demo_hook_t *vdu_demo_hook, cp_int32_t optname, const cp_void_t* optval);
cp_int32_t get_option_vdu_demo_hook(cp_vdu_demo_hook_t *vdu_demo_hook, cp_int32_t optname, cp_void_t* optval);

cp_int32_t connect_cb_vdu_demo_hook(cp_socket_t *socket, cp_int32_t status);										/*连接回调函数*/
cp_int32_t close_cb_vdu_demo_hook(cp_socket_t *socket, cp_int32_t status);											/*关闭回调函数*/
cp_int32_t read_cb_vdu_demo_hook(cp_socket_t *socket, const cp_buf_t *buf, cp_int32_t nread, cp_int32_t status);	/*读回调函数*/
cp_int32_t write_cb_vdu_demo_hook(cp_socket_t *socket, cp_int32_t status);											/*写回调函数*/
cp_int32_t error_cb_vdu_demo_hook(cp_socket_t *socket, cp_int32_t status);											/*错误回调函数*/

cp_int32_t cp_copy_queue(cp_pool_t *pool, cp_queue_t *dest_queue, cp_queue_t *src_queue)
{
	cp_queue_t								*current;
	cp_vdu_demo_hook_block_t						*tmp_block;
	cp_vdu_demo_hook_block_t						*tmp_new_block;


	cp_queue_init(dest_queue);
	for (current = cp_queue_next(src_queue); current != src_queue;
		current = cp_queue_next(current)) {
		tmp_block = cp_queue_data(current, cp_vdu_demo_hook_block_t, queue);
		if (tmp_block) {
			tmp_new_block = (cp_vdu_demo_hook_block_t*)cp_palloc(pool, cp_sizeof(cp_vdu_demo_hook_block_t));
			if (tmp_new_block) {
				*tmp_new_block = *tmp_block;
				cp_queue_init(&tmp_new_block->queue);
				cp_queue_insert_tail(dest_queue, &tmp_new_block->queue);
			}
		}
	}

	return 0;
}

cp_int32_t cp_copy_hook(cp_hook_t *dest, cp_hook_t *src)
{
	cp_pool_t							*dest_pool;



	if (!dest || !src) {
		return -1;
	}
	//获取目的内存池信息
	if (dest->pool) {
		dest_pool = dest->pool;
	} else {
		dest_pool = dest->manager->pool;
	}
	//将目的的cp_hook_t信息重新初始化
	CP_INIT_HANDLE_SLAB_FILES(dest);
	//拷贝入口队列信息
	cp_copy_queue(dest_pool, &dest->entry, &src->entry);
	//拷贝正确返回队列信息
	cp_copy_queue(dest_pool, &dest->right, &src->right);
	//拷贝错误返回队列信息
	cp_copy_queue(dest_pool, &dest->error, &src->error);

	return 0;
}



cp_vdu_demo_hook_t* create_vdu_demo_hook(cp_module_register_t *register_info, cp_socket_manager_t *manager, cp_vdu_demo_hook_info_t *info)
{
	cp_int32_t							ret_int = 0;
	cp_vdu_demo_hook_t						*tmp_module = CP_NULL;
	cp_pool_info_t						tmp_pool_info = { 0, };


	if (!register_info || !manager || !info) {
		return CP_NULL;
	}

	tmp_module = cp_malloc_module(manager, cp_vdu_demo_hook_t, &tmp_pool_info);
	if (!tmp_module) {
		return CP_NULL;
	}
	CP_SOCKET_MODULE_SET_CALLBACK_HANDLERS(tmp_module, vdu_demo_hook);
	return tmp_module;
}

cp_int32_t destroy_vdu_demo_hook(cp_vdu_demo_hook_manager_t *manager, cp_vdu_demo_hook_t* vdu_demo_hook)
{
	if (!manager || !vdu_demo_hook) {
		return -1;
	}
	cp_free_module(vdu_demo_hook);
	return 0;
}


/*模块创建接口，表示创建一个模块*/
cp_int32_t init_vdu_demo_hook(cp_vdu_demo_hook_t *vdu_demo_hook, const cp_vdu_demo_hook_info_t *vdu_demo_hook_info)
{
	return 0;
}
/*模块打开运行接口，在模块init之后，会被调用*/
cp_int32_t open_vdu_demo_hook(cp_vdu_demo_hook_t *vdu_demo_hook, const cp_vdu_demo_hook_info_t *vdu_demo_hook_info)
{

	return 0;
}
/*读取模块数据，flag为读取模式的扩展标志。默认为0，其他为预留*/
cp_int32_t read_vdu_demo_hook(cp_vdu_demo_hook_t *vdu_demo_hook, cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag)
{
	return 0;
}
/*写模块数据，flag为写模式的扩展标志。默认为0，其他为预留*/
cp_int32_t write_vdu_demo_hook(cp_vdu_demo_hook_t *vdu_demo_hook, const cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag)
{
	return 0;
}
/*关闭模块*/
cp_int32_t close_vdu_demo_hook(cp_vdu_demo_hook_t *vdu_demo_hook)
{
	return 0;
}
/*退出模块*/
cp_int32_t exit_vdu_demo_hook(cp_vdu_demo_hook_t *vdu_demo_hook)
{
	return 0;
}
/*设置模块参数*/
cp_int32_t set_option_vdu_demo_hook(cp_vdu_demo_hook_t *vdu_demo_hook, cp_int32_t optname, const cp_void_t* optval)
{
	return 0;
}
cp_int32_t get_option_vdu_demo_hook(cp_vdu_demo_hook_t *vdu_demo_hook, cp_int32_t optname, cp_void_t* optval)
{
	return 0;
}


cp_int32_t connect_cb_vdu_demo_hook(cp_socket_t *socket, cp_int32_t status)
{
	return 0;
}

cp_int32_t close_cb_vdu_demo_hook(cp_socket_t *socket, cp_int32_t status)
{
	return 0;
}

cp_int32_t read_cb_vdu_demo_hook(cp_socket_t *socket, const cp_buf_t *buf, cp_int32_t nread, cp_int32_t status)
{
	return 0;
}

cp_int32_t write_cb_vdu_demo_hook(cp_socket_t *socket, cp_int32_t status)
{
	return 0;
}

cp_int32_t error_cb_vdu_demo_hook(cp_socket_t *socket, cp_int32_t status)
{
	return 0;
}




