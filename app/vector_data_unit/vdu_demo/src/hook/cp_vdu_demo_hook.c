/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/
#include "cp_pool_core.h"
#include "cp_vdu_demo_hook.h"



cp_vdu_demo_hook_t *cp_vdu_demo_hook_create();

/*ģ�鴴���ӿڣ���ʾ����һ��ģ��*/
cp_int32_t init_vdu_demo_hook(cp_vdu_demo_hook_t *vdu_demo_hook, const cp_vdu_demo_hook_info_t *vdu_demo_hook_info);
/*ģ������нӿڣ���ģ��init֮�󣬻ᱻ����*/
cp_int32_t open_vdu_demo_hook(cp_vdu_demo_hook_t *vdu_demo_hook, const cp_vdu_demo_hook_info_t *vdu_demo_hook_info);
/*��ȡģ�����ݣ�flagΪ��ȡģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��*/
cp_int32_t read_vdu_demo_hook(cp_vdu_demo_hook_t *vdu_demo_hook, cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag);
/*дģ�����ݣ�flagΪдģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��*/
cp_int32_t write_vdu_demo_hook(cp_vdu_demo_hook_t *vdu_demo_hook, const cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag);
/*�ر�ģ��*/
cp_int32_t close_vdu_demo_hook(cp_vdu_demo_hook_t *vdu_demo_hook);
/*�˳�ģ��*/
cp_int32_t exit_vdu_demo_hook(cp_vdu_demo_hook_t *vdu_demo_hook);
/*����ģ�����*/
cp_int32_t set_option_vdu_demo_hook(cp_vdu_demo_hook_t *vdu_demo_hook, cp_int32_t optname, const cp_void_t* optval);
cp_int32_t get_option_vdu_demo_hook(cp_vdu_demo_hook_t *vdu_demo_hook, cp_int32_t optname, cp_void_t* optval);

cp_int32_t connect_cb_vdu_demo_hook(cp_socket_t *socket, cp_int32_t status);										/*���ӻص�����*/
cp_int32_t close_cb_vdu_demo_hook(cp_socket_t *socket, cp_int32_t status);											/*�رջص�����*/
cp_int32_t read_cb_vdu_demo_hook(cp_socket_t *socket, const cp_buf_t *buf, cp_int32_t nread, cp_int32_t status);	/*���ص�����*/
cp_int32_t write_cb_vdu_demo_hook(cp_socket_t *socket, cp_int32_t status);											/*д�ص�����*/
cp_int32_t error_cb_vdu_demo_hook(cp_socket_t *socket, cp_int32_t status);											/*����ص�����*/

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
	//��ȡĿ���ڴ����Ϣ
	if (dest->pool) {
		dest_pool = dest->pool;
	} else {
		dest_pool = dest->manager->pool;
	}
	//��Ŀ�ĵ�cp_hook_t��Ϣ���³�ʼ��
	CP_INIT_HANDLE_SLAB_FILES(dest);
	//������ڶ�����Ϣ
	cp_copy_queue(dest_pool, &dest->entry, &src->entry);
	//������ȷ���ض�����Ϣ
	cp_copy_queue(dest_pool, &dest->right, &src->right);
	//�������󷵻ض�����Ϣ
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


/*ģ�鴴���ӿڣ���ʾ����һ��ģ��*/
cp_int32_t init_vdu_demo_hook(cp_vdu_demo_hook_t *vdu_demo_hook, const cp_vdu_demo_hook_info_t *vdu_demo_hook_info)
{
	return 0;
}
/*ģ������нӿڣ���ģ��init֮�󣬻ᱻ����*/
cp_int32_t open_vdu_demo_hook(cp_vdu_demo_hook_t *vdu_demo_hook, const cp_vdu_demo_hook_info_t *vdu_demo_hook_info)
{

	return 0;
}
/*��ȡģ�����ݣ�flagΪ��ȡģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��*/
cp_int32_t read_vdu_demo_hook(cp_vdu_demo_hook_t *vdu_demo_hook, cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag)
{
	return 0;
}
/*дģ�����ݣ�flagΪдģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��*/
cp_int32_t write_vdu_demo_hook(cp_vdu_demo_hook_t *vdu_demo_hook, const cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag)
{
	return 0;
}
/*�ر�ģ��*/
cp_int32_t close_vdu_demo_hook(cp_vdu_demo_hook_t *vdu_demo_hook)
{
	return 0;
}
/*�˳�ģ��*/
cp_int32_t exit_vdu_demo_hook(cp_vdu_demo_hook_t *vdu_demo_hook)
{
	return 0;
}
/*����ģ�����*/
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




