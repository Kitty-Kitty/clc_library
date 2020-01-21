/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/
#include "cp_include.h"
#include "cp_demo_process.h"



cp_demo_process_t *cp_demo_process_create();
/*ģ�鴴���ӿڣ���ʾ����һ��ģ��*/
cp_int32_t init_demo_process(cp_demo_process_t *demo_process, const cp_demo_process_info_t *info);
/*ģ������нӿڣ���ģ��init֮�󣬻ᱻ����*/
cp_int32_t open_demo_process(cp_demo_process_t *demo_process, const cp_demo_process_info_t *info);
/*��ȡģ�����ݣ�flagΪ��ȡģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��*/
cp_int32_t read_demo_process(cp_demo_process_t *demo_process, cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag);
/*дģ�����ݣ�flagΪдģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��*/
cp_int32_t write_demo_process(cp_demo_process_t *demo_process, const cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag);
/*�ر�ģ��*/
cp_int32_t close_demo_process(cp_demo_process_t *demo_process);
/*�˳�ģ��*/
cp_int32_t exit_demo_process(cp_demo_process_t *demo_process);
/*����ģ�����*/
cp_int32_t set_option_demo_process(cp_demo_process_t *demo_process, cp_int32_t optname, const cp_void_t* optval);
cp_int32_t get_option_demo_process(cp_demo_process_t *demo_process, cp_int32_t optname, cp_void_t* optval);

cp_int32_t listen_demo_process(cp_socket_t *socket, cp_sockaddr_in *addr);											/*�򿪼���*/
cp_int32_t connect_demo_process(cp_socket_t *socket, cp_sockaddr_in *addr);										/*��ʼ����*/
cp_int32_t read_s_demo_process(cp_demo_process_t *cp_s, const cp_buf_t *buf, cp_int32_t nread, cp_int32_t flags);	/*������*/
cp_int32_t write_s_demo_process(cp_socket_t *socket, const cp_buf_t *buf, cp_int32_t nread, const cp_sockaddr_in *remote_addr, cp_int32_t flags);
cp_int32_t close_s_demo_process(cp_socket_t *socket);																/*�ر�����*/
cp_int32_t connect_cb_demo_process(cp_socket_t *socket, cp_int32_t status);										/*���ӻص�����*/
cp_int32_t close_cb_demo_process(cp_socket_t *socket, cp_int32_t status);											/*�رջص�����*/
cp_int32_t read_cb_demo_process(cp_socket_t *socket, const cp_buf_t *buf, cp_int32_t nread, cp_int32_t status);	/*���ص�����*/
cp_int32_t write_cb_demo_process(cp_socket_t *socket, cp_int32_t status);											/*д�ص�����*/
cp_int32_t error_cb_demo_process(cp_socket_t *socket, cp_int32_t status);											/*����ص�����*/




cp_demo_process_t* create_demo_process(cp_module_register_t *register_info, cp_socket_manager_t *manager, cp_demo_process_info_t *info)
{
	cp_demo_process_t					*tmp_module = CP_NULL;
	cp_pool_info_t						tmp_pool_info = { 0, };


	if (!register_info || !manager || !info) {
		return CP_NULL;
	}

	tmp_module = cp_malloc_module(manager, cp_demo_process_t, &tmp_pool_info);
	if (!tmp_module) {
		return CP_NULL;
	}
	CP_SOCKET_MODULE_SET_HANDLERS(tmp_module, demo_process);
	return tmp_module;
}

cp_int32_t destroy_demo_process(cp_demo_process_manager_t *manager, cp_demo_process_t* demo_process)
{
	if (!manager || !demo_process) {
		return -1;
	}
	cp_free_module(demo_process);
	return 0;
}

/*ģ�鴴���ӿڣ���ʾ����һ��ģ��*/
cp_int32_t init_demo_process(cp_demo_process_t *demo_process, const cp_demo_process_info_t *info)
{
	return cp_init_module(demo_process, info);
}
/*ģ������нӿڣ���ģ��init֮�󣬻ᱻ����*/
cp_int32_t open_demo_process(cp_demo_process_t *demo_process, const cp_demo_process_info_t *info)
{
	return cp_open_module(demo_process, info);
}
/*��ȡģ�����ݣ�flagΪ��ȡģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��*/
cp_int32_t read_demo_process(cp_demo_process_t *demo_process, cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag)
{
	return cp_read_module(demo_process, buf, len, flag);
}
/*дģ�����ݣ�flagΪдģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��*/
cp_int32_t write_demo_process(cp_demo_process_t *demo_process, const cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag)
{
	return cp_write_module(demo_process, buf, len, flag);
}
/*�ر�ģ��*/
cp_int32_t close_demo_process(cp_demo_process_t *demo_process)
{
	return cp_close_module(demo_process);
}
/*�˳�ģ��*/
cp_int32_t exit_demo_process(cp_demo_process_t *demo_process)
{
	return cp_exit_module(demo_process);
}
/*����ģ�����*/
cp_int32_t set_option_demo_process(cp_demo_process_t *demo_process, cp_int32_t optname, const cp_void_t* optval)
{
	return cp_set_option_module(demo_process, optname, optval);
}

cp_int32_t get_option_demo_process(cp_demo_process_t *demo_process, cp_int32_t optname, cp_void_t* optval)
{
	return cp_get_option_module(demo_process, optname, optval);
}

cp_int32_t listen_demo_process(cp_socket_t *socket, cp_sockaddr_in *addr)
{
	return 0;
}

cp_int32_t connect_demo_process(cp_socket_t *socket, cp_sockaddr_in *addr)
{
	return 0;
}

cp_int32_t read_s_demo_process(cp_demo_process_t *cp_s, const cp_buf_t *buf, cp_int32_t nread, cp_int32_t flags)
{
	return 0;
}

cp_int32_t write_s_demo_process(cp_socket_t *socket, const cp_buf_t *buf, cp_int32_t nread, const cp_sockaddr_in *remote_addr, cp_int32_t flags)
{
	return 0;
}

cp_int32_t close_s_demo_process(cp_socket_t *socket)
{
	return 0;
}

cp_int32_t connect_cb_demo_process(cp_socket_t *socket, cp_int32_t status)
{
	cp_queue_t								*modules;
	cp_queue_t								*current;
	cp_filter_t								*filter;
	cp_filter_manager_t						*filter_manager;
	cp_func_t								*func;
	cp_func_manager_t						*func_manager;
	cp_int32_t								ret_int = 0;
	cp_module_manager_info_t				tmp_module_manager_info;



	//����filter manager��������
	//CP_MODULE_MANAGER_INFO_SET_TYPE(&tmp_module_manager_info, cp_module_manager_type_filter);
	CP_MODULE_MANAGER_INFO_SET_TYPE(&tmp_module_manager_info, cp_demo_manager_type_filter);
	filter_manager = (cp_filter_manager_t *)cp_get_manager(CP_NULL, &tmp_module_manager_info);
	if (filter_manager) {
		modules = &filter_manager->modules;
		for (current = cp_queue_next(modules); current != modules; 
			current = cp_queue_next(current)) {
			filter = cp_queue_data(current, cp_filter_t, queue);
			if (filter->connect_cb) {
				ret_int = filter->connect_cb(socket, status);
				if (!(ret_int & cp_filter_status_match)) {
					continue;
				}
				if ((ret_int & cp_filter_status_read_again)) {
					return 0;
				}
				break;
			}
		}
	}
	//����func managet��������
	//CP_MODULE_MANAGER_INFO_SET_TYPE(&tmp_module_manager_info, cp_module_manager_type_func);
	CP_MODULE_MANAGER_INFO_SET_TYPE(&tmp_module_manager_info, CP_MODULE_MANAGER_TYPE_FUNC(1));
	func_manager = (cp_func_manager_t*)cp_get_manager(CP_NULL, &tmp_module_manager_info);
	if (func_manager) {
		modules = &func_manager->modules;
		for (current = cp_queue_next(modules); current != modules;
			current = cp_queue_next(current)) {
			func = cp_queue_data(current, cp_func_t, queue);
			if (func->connect_cb) {
				ret_int = func->connect_cb(socket, status);
				if (!(ret_int & cp_func_status_match)) {
					continue;
				}
				if ((ret_int & cp_func_status_successorerror) ||
					(ret_int & cp_func_status_read_again)) {
					return 0;
				}
				break;
			}
		}
	}
	return 0;
}

cp_int32_t close_cb_demo_process(cp_socket_t *socket, cp_int32_t status)
{
	cp_queue_t								*modules;
	cp_queue_t								*current;
	cp_filter_t								*filter;
	cp_filter_manager_t						*filter_manager;
	cp_func_t								*func;
	cp_func_manager_t						*func_manager;
	cp_int32_t								ret_int = 0;
	cp_module_manager_info_t				tmp_module_manager_info;



	//����filter manager��������
	//CP_MODULE_MANAGER_INFO_SET_TYPE(&tmp_module_manager_info, cp_module_manager_type_filter);
	CP_MODULE_MANAGER_INFO_SET_TYPE(&tmp_module_manager_info, cp_demo_manager_type_filter);
	filter_manager = (cp_filter_manager_t*)cp_get_manager(CP_NULL, &tmp_module_manager_info);
	if (filter_manager) {
		modules = &filter_manager->modules;
		for (current = cp_queue_next(modules); current != modules;
			current = cp_queue_next(current)) {
			filter = cp_queue_data(current, cp_filter_t, queue);
			if (filter->close_cb) {
				ret_int = filter->close_cb(socket, status);
				if (!(ret_int & cp_filter_status_match)) {
					continue;
				}
				if ((ret_int & cp_filter_status_read_again)) {
					return 0;
				}
				break;
			}
		}
	}
	//����func managet��������
	//CP_MODULE_MANAGER_INFO_SET_TYPE(&tmp_module_manager_info, cp_module_manager_type_func);
	CP_MODULE_MANAGER_INFO_SET_TYPE(&tmp_module_manager_info, CP_MODULE_MANAGER_TYPE_FUNC(1));
	func_manager = (cp_func_manager_t*)cp_get_manager(CP_NULL, &tmp_module_manager_info);
	if (func_manager) {
		modules = &func_manager->modules;
		for (current = cp_queue_next(modules); current != modules;
			current = cp_queue_next(current)) {
			func = cp_queue_data(current, cp_func_t, queue);
			if (func->close_cb) {
				ret_int = func->close_cb(socket, status);
				if (!(ret_int & cp_func_status_match)) {
					continue;
				}
				if ((ret_int & cp_func_status_successorerror) ||
					(ret_int & cp_func_status_read_again)) {
					return 0;
				}
				break;
			}
		}
	}
	return 0;
}

cp_int32_t read_cb_demo_process(cp_socket_t *socket, const cp_buf_t *buf, cp_int32_t nread, cp_int32_t status)
{
	cp_queue_t								*modules;
	cp_queue_t								*current;
	cp_filter_t								*filter;
	cp_filter_manager_t						*filter_manager;
	cp_func_t								*func;
	cp_func_manager_t						*func_manager;
	cp_int32_t								ret_int = 0;
	cp_module_manager_info_t				tmp_module_manager_info;



	//����filter manager��������
	//CP_MODULE_MANAGER_INFO_SET_TYPE(&tmp_module_manager_info, cp_module_manager_type_filter);
	CP_MODULE_MANAGER_INFO_SET_TYPE(&tmp_module_manager_info, cp_demo_manager_type_filter);
	filter_manager = (cp_filter_manager_t*)cp_get_manager(CP_NULL, &tmp_module_manager_info);
	if (filter_manager) {
		modules = &filter_manager->modules;
		for (current = cp_queue_next(modules); current != modules;
			current = cp_queue_next(current)) {
			filter = cp_queue_data(current, cp_filter_t, queue);
			if (filter->read_cb) {
				ret_int = filter->read_cb(socket, buf, nread, status);
				if (!(ret_int & cp_filter_status_match)) {
					continue;
				}
				if ((ret_int & cp_filter_status_read_again)) {
					return 0;
				}
				break;
			}
		}
	}
	//����func managet��������
	//CP_MODULE_MANAGER_INFO_SET_TYPE(&tmp_module_manager_info, cp_module_manager_type_func);
	CP_MODULE_MANAGER_INFO_SET_TYPE(&tmp_module_manager_info, CP_MODULE_MANAGER_TYPE_FUNC(1));
	func_manager = (cp_func_manager_t*)cp_get_manager(CP_NULL, &tmp_module_manager_info);
	if (func_manager) {
		modules = &func_manager->modules;
		for (current = cp_queue_next(modules); current != modules;
			current = cp_queue_next(current)) {
			func = cp_queue_data(current, cp_func_t, queue);
			if (func->read_cb) {
				ret_int = func->read_cb(socket, buf, nread, status);
				if (!(ret_int & cp_func_status_match)) {
					continue;
				}
				if ((ret_int & cp_func_status_successorerror) ||
					(ret_int & cp_func_status_read_again)) {
					return 0;
				}
				break;
			}
		}
	}
	return 0;
}

cp_int32_t write_cb_demo_process(cp_socket_t *socket, cp_int32_t status)
{
	cp_queue_t								*modules;
	cp_queue_t								*current;
	cp_filter_t								*filter;
	cp_filter_manager_t						*filter_manager;
	cp_func_t								*func;
	cp_func_manager_t						*func_manager;
	cp_int32_t								ret_int = 0;
	cp_module_manager_info_t				tmp_module_manager_info;



	//����filter manager��������
	//CP_MODULE_MANAGER_INFO_SET_TYPE(&tmp_module_manager_info, cp_module_manager_type_filter);
	CP_MODULE_MANAGER_INFO_SET_TYPE(&tmp_module_manager_info, cp_demo_manager_type_filter);
	filter_manager = (cp_filter_manager_t*)cp_get_manager(CP_NULL, &tmp_module_manager_info);
	if (filter_manager) {
		modules = &filter_manager->modules;
		for (current = cp_queue_next(modules); current != modules;
			current = cp_queue_next(current)) {
			filter = cp_queue_data(current, cp_filter_t, queue);
			if (filter->write_cb) {
				ret_int = filter->write_cb(socket, status);
				if (!(ret_int & cp_filter_status_match)) {
					continue;
				}
				if ((ret_int & cp_filter_status_read_again)) {
					return 0;
				}
				break;
			}
		}
	}
	//����func managet��������
	//CP_MODULE_MANAGER_INFO_SET_TYPE(&tmp_module_manager_info, cp_module_manager_type_func);
	CP_MODULE_MANAGER_INFO_SET_TYPE(&tmp_module_manager_info, CP_MODULE_MANAGER_TYPE_FUNC(1));
	func_manager = (cp_func_manager_t*)cp_get_manager(CP_NULL, &tmp_module_manager_info);
	if (func_manager) {
		modules = &func_manager->modules;
		for (current = cp_queue_next(modules); current != modules;
			current = cp_queue_next(current)) {
			func = cp_queue_data(current, cp_func_t, queue);
			if (func->write_cb) {
				ret_int = func->write_cb(socket, status);
				if (!(ret_int & cp_func_status_match)) {
					continue;
				}
				if ((ret_int & cp_func_status_successorerror) ||
					(ret_int & cp_func_status_read_again)) {
					return 0;
				}
				break;
			}
		}
	}
	return 0;
}

cp_int32_t error_cb_demo_process(cp_socket_t *socket, cp_int32_t status)
{
	cp_queue_t								*modules;
	cp_queue_t								*current;
	cp_filter_t								*filter;
	cp_filter_manager_t						*filter_manager;
	cp_func_t								*func;
	cp_func_manager_t						*func_manager;
	cp_int32_t								ret_int = 0;
	cp_module_manager_info_t				tmp_module_manager_info;



	//����filter manager��������
	//CP_MODULE_MANAGER_INFO_SET_TYPE(&tmp_module_manager_info, cp_module_manager_type_filter);
	CP_MODULE_MANAGER_INFO_SET_TYPE(&tmp_module_manager_info, cp_demo_manager_type_filter);
	filter_manager = (cp_filter_manager_t*)cp_get_manager(CP_NULL, &tmp_module_manager_info);
	if (filter_manager) {
		modules = &filter_manager->modules;
		for (current = cp_queue_next(modules); current != modules;
			current = cp_queue_next(current)) {
			filter = cp_queue_data(current, cp_filter_t, queue);
			if (filter->error_cb) {
				ret_int = filter->error_cb(socket, status);
				if (!(ret_int & cp_filter_status_match)) {
					continue;
				}
				if ((ret_int & cp_filter_status_read_again)) {
					return 0;
				}
				break;
			}
		}
	}
	//����func managet��������
	//CP_MODULE_MANAGER_INFO_SET_TYPE(&tmp_module_manager_info, cp_module_manager_type_func);
	CP_MODULE_MANAGER_INFO_SET_TYPE(&tmp_module_manager_info, CP_MODULE_MANAGER_TYPE_FUNC(1));
	func_manager = (cp_func_manager_t*)cp_get_manager(CP_NULL, &tmp_module_manager_info);
	if (func_manager) {
		modules = &func_manager->modules;
		for (current = cp_queue_next(modules); current != modules;
			current = cp_queue_next(current)) {
			func = cp_queue_data(current, cp_func_t, queue);
			if (func->error_cb) {
				ret_int = func->error_cb(socket, status);
				if (!(ret_int & cp_func_status_match)) {
					continue;
				}
				if ((ret_int & cp_func_status_successorerror) ||
					(ret_int & cp_func_status_read_again)) {
					return 0;
				}
				break;
			}
		}
	}
	return 0;
}




