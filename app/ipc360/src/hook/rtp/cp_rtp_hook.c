/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/
#include "cp_include.h"
#include "cp_rtp_hook.h"




cp_rtp_hook_t *cp_rtp_hook_create();

/*ģ�鴴���ӿڣ���ʾ����һ��ģ��*/
cp_int32_t init_rtp_hook(cp_rtp_hook_t *rtp_hook, const cp_rtp_hook_info_t *rtp_hook_info);
/*ģ������нӿڣ���ģ��init֮�󣬻ᱻ����*/
cp_int32_t open_rtp_hook(cp_rtp_hook_t *rtp_hook, const cp_rtp_hook_info_t *rtp_hook_info);
/*��ȡģ�����ݣ�flagΪ��ȡģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��*/
cp_int32_t read_rtp_hook(cp_rtp_hook_t *rtp_hook, cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag);
/*дģ�����ݣ�flagΪдģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��*/
cp_int32_t write_rtp_hook(cp_rtp_hook_t *rtp_hook, const cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag);
/*�ر�ģ��*/
cp_int32_t close_rtp_hook(cp_rtp_hook_t *rtp_hook);
/*�˳�ģ��*/
cp_int32_t exit_rtp_hook(cp_rtp_hook_t *rtp_hook);
/*����ģ�����*/
cp_int32_t set_option_rtp_hook(cp_rtp_hook_t *rtp_hook, cp_int32_t optname, const cp_void_t* optval);
cp_int32_t get_option_rtp_hook(cp_rtp_hook_t *rtp_hook, cp_int32_t optname, cp_void_t* optval);

cp_int32_t connect_cb_rtp_hook(cp_socket_t *socket, cp_int32_t status);										/*���ӻص�����*/
cp_int32_t close_cb_rtp_hook(cp_socket_t *socket, cp_int32_t status);											/*�رջص�����*/
cp_int32_t read_cb_rtp_hook(cp_socket_t *socket, const cp_buf_t *buf, cp_int32_t nread, cp_int32_t status);	/*���ص�����*/
cp_int32_t write_cb_rtp_hook(cp_socket_t *socket, cp_int32_t status);											/*д�ص�����*/
cp_int32_t error_cb_rtp_hook(cp_socket_t *socket, cp_int32_t status);											/*����ص�����*/

cp_int32_t cp_open_queue_hook(cp_rtp_hook_t *hook, const cp_ipc_hook_info_t *ipc_hook_info, cp_queue_t *queue);



cp_rtp_hook_t* create_rtp_hook(cp_module_register_t *register_info, cp_socket_manager_t *manager, cp_rtp_hook_info_t *info)
{
	cp_int32_t							ret_int = 0;
	cp_rtp_hook_t						*tmp_module = CP_NULL;
	cp_ipc_hook_register_t				*css_register_info = CP_NULL;
	cp_pool_info_t						tmp_pool_info = { 0, };


	if (!register_info || !manager || !info) {
		return CP_NULL;
	}
	css_register_info = (cp_ipc_hook_register_t*)register_info;
	tmp_module = cp_malloc_module(manager, cp_rtp_hook_t, &tmp_pool_info);
	if (!tmp_module) {
		return CP_NULL;
	}
	CP_MODULE_SET_HANDLERS(tmp_module, rtp_hook);
	CP_SOCKET_MODULE_SET_CALLBACK_HANDLERS(tmp_module, rtp_hook);
	CP_INIT_HANDLE_SLAB_FILES(tmp_module);
	tmp_module->command = css_register_info->command;
	tmp_module->hook_handle = css_register_info->hook_hander;
	return tmp_module;
}

cp_int32_t destroy_rtp_hook(cp_ipc_hook_manager_t *manager, cp_rtp_hook_t* rtp_hook)
{
	if (!manager || !rtp_hook) {
		return -1;
	}
	cp_free_module(rtp_hook);
	return 0;
}


/*ģ�鴴���ӿڣ���ʾ����һ��ģ��*/
cp_int32_t init_rtp_hook(cp_rtp_hook_t *rtp_hook, const cp_rtp_hook_info_t *rtp_hook_info)
{
	return 0;
}
/*ģ������нӿڣ���ģ��init֮�󣬻ᱻ����*/
cp_int32_t open_rtp_hook(cp_rtp_hook_t *rtp_hook, const cp_rtp_hook_info_t *rtp_hook_info)
{
	cp_int32_t					ret_int = 0;
	cp_session_t				*tmp_sesssion = rtp_hook_info->session;
	cp_ipc_hook_stack_t			*tmp_stack;
	cp_char_t					tmp_buf[CP_APP_DEFAULT_BUFFER_LENGTH] = { 0, };




	//ִ�е�ǰ�ĺ�������
	if (!rtp_hook || !rtp_hook_info || !rtp_hook->hook_handle) {
		return -1;
	}

	//�ж��Ƿ񳬹����ջ���ݣ���ֹѭ����������
	if (tmp_sesssion) {
		++(tmp_sesssion->stack_count);
		if (tmp_sesssion->stack_count > CP_HOOK_MAX_STACK_COUNT) {
			cp_log_error(rtp_hook->logger, "module %s stack count[%d] more than [%d] error.",
				print_module_register_info(&rtp_hook->register_info, tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH),
				tmp_sesssion->stack_count,
				CP_HOOK_MAX_STACK_COUNT);
			return -1;
		}
	}
	//��ִ����ں���
	ret_int = cp_open_queue_hook(rtp_hook, (const cp_ipc_hook_info_t *)rtp_hook_info, &rtp_hook->entry);
	if (ret_int) {
		cp_log_error(rtp_hook->logger, "module %s process entry queue error.",
			print_module_register_info(&rtp_hook->register_info, tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH));
		return ret_int;
	}
	ret_int = rtp_hook->hook_handle((cp_hook_t *)rtp_hook, tmp_sesssion, tmp_sesssion->arg);
	if (ret_int) {
		//������ش�����ִ�д�������Ĭ�϶���Ϊ����0��ʾ��ȷ����������Ϊ����
		ret_int = cp_open_queue_hook(rtp_hook, (const cp_ipc_hook_info_t *)rtp_hook_info, &rtp_hook->error);
		if (ret_int) {
			cp_log_error(rtp_hook->logger, "module %s process error queue error.",
				print_module_register_info(&rtp_hook->register_info, tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH));
			return ret_int;
		}
	}
	else {
		//���������ȷ����ִ����ȷ������Ĭ�϶���Ϊ����0��ʾ��ȷ����������Ϊ����
		ret_int = cp_open_queue_hook(rtp_hook, (const cp_ipc_hook_info_t *)rtp_hook_info, &rtp_hook->right);
		if (ret_int) {
			cp_log_error(rtp_hook->logger, "module %s process right queue error.",
				print_module_register_info(&rtp_hook->register_info, tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH));
			return ret_int;
		}
	}

	if (tmp_sesssion && (tmp_sesssion->option & CP_SESSION_OPTION_SET_HISTORY)) {
		//������ڴ�ͳһ���ڴ�����룬�ͷ�ʱͳһ�ͷż���
		tmp_stack = cp_palloc(tmp_sesssion->pool, cp_sizeof(cp_ipc_hook_stack_t));
		if (tmp_stack) {
			//��ʼ��������Ϣ����������ʷ������
			CP_CSS_HOOK_STACK_INIT_FIELDS(tmp_stack);
			CP_CSS_HOOK_STACK_SET_VALUE(tmp_stack, (cp_ipc_hook_t *)rtp_hook, tmp_sesssion, tmp_sesssion->arg);
			cp_queue_insert_tail(&tmp_sesssion->hhsq, &tmp_stack->queue);
		}
	}

	return 0;
}
/*��ȡģ�����ݣ�flagΪ��ȡģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��*/
cp_int32_t read_rtp_hook(cp_rtp_hook_t *rtp_hook, cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag)
{
	return 0;
}
/*дģ�����ݣ�flagΪдģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��*/
cp_int32_t write_rtp_hook(cp_rtp_hook_t *rtp_hook, const cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag)
{
	return 0;
}
/*�ر�ģ��*/
cp_int32_t close_rtp_hook(cp_rtp_hook_t *rtp_hook)
{
	return 0;
}
/*�˳�ģ��*/
cp_int32_t exit_rtp_hook(cp_rtp_hook_t *rtp_hook)
{
	return 0;
}
/*����ģ�����*/
cp_int32_t set_option_rtp_hook(cp_rtp_hook_t *rtp_hook, cp_int32_t optname, const cp_void_t* optval)
{
	cp_int32_t							ret_int = 0;
	cp_ipc_t							*tmp_ipc = (cp_ipc_t *)rtp_hook->manager->app;
	cp_ipc_info_t						*tmp_ipc_info = (cp_ipc_info_t *)(tmp_ipc->app_info);



	switch (optname)
	{
	case cp_ipc_hook_set_option_start_heartbeat:
	{
	}
	break;
	case cp_ipc_hook_set_option_stop_heartbeat:
	{

	}
	break;
	case cp_ipc_hook_set_option_send_register:
	{
		
	}
	break;
	default:
		cp_log_error(rtp_hook->manager->app, "set_option_rtp_hook() unknow optname[%d]", optname);
		break;
	}
	return 0;
}
cp_int32_t get_option_rtp_hook(cp_rtp_hook_t *rtp_hook, cp_int32_t optname, cp_void_t* optval)
{
	return 0;
}


cp_int32_t connect_cb_rtp_hook(cp_socket_t *socket, cp_int32_t status)
{
	return 0;
}

cp_int32_t close_cb_rtp_hook(cp_socket_t *socket, cp_int32_t status)
{
	return 0;
}

cp_int32_t read_cb_rtp_hook(cp_socket_t *socket, const cp_buf_t *buf, cp_int32_t nread, cp_int32_t status)
{
	return 0;
}

cp_int32_t write_cb_rtp_hook(cp_socket_t *socket, cp_int32_t status)
{
	return 0;
}

cp_int32_t error_cb_rtp_hook(cp_socket_t *socket, cp_int32_t status)
{
	return 0;
}

cp_int32_t cp_open_queue_hook(cp_rtp_hook_t *hook, const cp_ipc_hook_info_t *ipc_hook_info, cp_queue_t *queue)
{
	cp_int32_t								ret_int = 0;
	cp_queue_t								*current;
	cp_ipc_hook_block_t						*tmp_block;


	for (current = cp_queue_next(queue); current != queue;
		current = cp_queue_next(current)) {
		tmp_block = cp_queue_data(current, cp_ipc_hook_block_t, queue);
		if (!tmp_block || !tmp_block->hook) {
			continue;
		}
		tmp_block->hook->current_hook = CP_NULL;
		ret_int = cp_open_module(tmp_block->hook, (const cp_module_info_t *)ipc_hook_info);
		if (tmp_block->hook->current_hook) {
			ret_int = cp_open_module(tmp_block->hook->current_hook, (const cp_module_info_t *)ipc_hook_info);
		}
	}

	return 0;
}




