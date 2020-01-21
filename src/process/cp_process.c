/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/
#include "cp_process.h"
#include "cp_include.h"


extern cp_module_register_t  process_module_manager_list[];
extern cp_int32_t process_module_manager_list_size;
extern cp_module_register_t  process_module_list[];
extern cp_int32_t process_module_list_size;



cp_process_t *cp_process_create();
/*ģ�鴴���ӿڣ���ʾ����һ��ģ��*/
cp_int32_t init_process(cp_process_t *process, const cp_process_info_t *info);
/*ģ������нӿڣ���ģ��init֮�󣬻ᱻ����*/
cp_int32_t open_process(cp_process_t *process, const cp_process_info_t *info);
/*��ȡģ�����ݣ�flagΪ��ȡģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��*/
cp_int32_t read_process(cp_process_t *process, cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag);
/*дģ�����ݣ�flagΪдģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��*/
cp_int32_t write_process(cp_process_t *process, const cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag);
/*�ر�ģ��*/
cp_int32_t close_process(cp_process_t *process);
/*�˳�ģ��*/
cp_int32_t exit_process(cp_process_t *process);
/*����ģ�����*/
cp_int32_t set_option_process(cp_process_t *process, cp_int32_t optname, const cp_void_t* optval);
cp_int32_t get_option_process(cp_process_t *process, cp_int32_t optname, cp_void_t* optval);


cp_int32_t cp_process_connect_cb(cp_socket_t *socket, cp_int32_t status)
{
	cp_int32_t								i = 0;
	cp_int32_t								tmp_max_size = 0;
	cp_queue_t								*modules;
	cp_queue_t								*current;
	cp_process_t							*tmp_process = CP_NULL;
	cp_process_manager_t					*tmp_root_manager = CP_NULL;
	cp_process_manager_t					**tmp_manager = CP_NULL;


	tmp_root_manager = (cp_process_manager_t*)cp_manager_get_root_manager(socket->manager->app, cp_module_manager_type_process);
	if (tmp_root_manager) {
		//�ȴ�����������µ���ģ��
		modules = &tmp_root_manager->modules;
		for (current = cp_queue_next(modules); current != modules;
			current = cp_queue_next(current)) {
			tmp_process = cp_queue_data(current, cp_process_t, queue);
			if (tmp_process->connect_cb) {
				tmp_process->connect_cb(socket, status);
			}
		}
		//Ȼ������������µ���ģ���������ģ��
		tmp_max_size = cp_array_max_size(&tmp_root_manager->module_managers);
		for (i = 0; i < tmp_max_size; i++) {
			//ȡ����ģ����д���
			tmp_manager = cp_array_get(&tmp_root_manager->module_managers, i);
			if (*tmp_manager) {
				modules = &((*tmp_manager)->modules);
				for (current = cp_queue_next(modules); current != modules;
					current = cp_queue_next(current)) {
					tmp_process = cp_queue_data(current, cp_process_t, queue);
					if (tmp_process->connect_cb) {
						tmp_process->connect_cb(socket, status);
					}
				}
			}
		}
			
	}
	return 0;
}

cp_int32_t cp_process_close_cb(cp_socket_t *socket, cp_int32_t status)
{
	cp_int32_t								i = 0;
	cp_int32_t								tmp_max_size = 0;
	cp_queue_t								*modules;
	cp_queue_t								*current;
	cp_process_t							*tmp_process = CP_NULL;
	cp_process_manager_t					*tmp_root_manager = CP_NULL;
	cp_process_manager_t					**tmp_manager = CP_NULL;


	tmp_root_manager = (cp_process_manager_t*)cp_manager_get_root_manager(socket->manager->app, cp_module_manager_type_process);
	if (tmp_root_manager) {
		//�ȴ�����������µ���ģ��
		modules = &tmp_root_manager->modules;
		for (current = cp_queue_next(modules); current != modules;
			current = cp_queue_next(current)) {
			tmp_process = cp_queue_data(current, cp_process_t, queue);
			if (tmp_process->close_cb) {
				tmp_process->close_cb(socket, status);
			}
		}
		//Ȼ������������µ���ģ���������ģ��
		tmp_max_size = cp_array_max_size(&tmp_root_manager->module_managers);
		for (i = 0; i < tmp_max_size; i++) {
			//ȡ����ģ����д���
			tmp_manager = cp_array_get(&tmp_root_manager->module_managers, i);
			if (*tmp_manager) {
				modules = &((*tmp_manager)->modules);
				for (current = cp_queue_next(modules); current != modules;
					current = cp_queue_next(current)) {
					tmp_process = cp_queue_data(current, cp_process_t, queue);
					if (tmp_process->close_cb) {
						tmp_process->close_cb(socket, status);
					}
				}
			}
		}

	}
	return 0;
}

cp_int32_t cp_process_read_cb(cp_socket_t *socket, const cp_buf_t *buf, cp_int32_t nread, cp_int32_t status)
{
	cp_int32_t								i = 0;
	cp_int32_t								tmp_max_size = 0;
	cp_queue_t								*modules;
	cp_queue_t								*current;
	cp_process_t							*tmp_process = CP_NULL;
	cp_process_manager_t					*tmp_root_manager = CP_NULL;
	cp_process_manager_t					**tmp_manager = CP_NULL;


	tmp_root_manager = (cp_process_manager_t*)cp_manager_get_root_manager(socket->manager->app, cp_module_manager_type_process);
	if (tmp_root_manager) {
		//�ȴ�����������µ���ģ��
		modules = &tmp_root_manager->modules;
		for (current = cp_queue_next(modules); current != modules;
			current = cp_queue_next(current)) {
			tmp_process = cp_queue_data(current, cp_process_t, queue);
			if (tmp_process->read_cb) {
				tmp_process->read_cb(socket, buf, nread, status);
			}
		}
		//Ȼ������������µ���ģ���������ģ��
		tmp_max_size = cp_array_max_size(&tmp_root_manager->module_managers);
		for (i = 0; i < tmp_max_size; i++) {
			//ȡ����ģ����д���
			tmp_manager = cp_array_get(&tmp_root_manager->module_managers, i);
			if (*tmp_manager) {
				modules = &((*tmp_manager)->modules);
				for (current = cp_queue_next(modules); current != modules;
					current = cp_queue_next(current)) {
					tmp_process = cp_queue_data(current, cp_process_t, queue);
					if (tmp_process->read_cb) {
						tmp_process->read_cb(socket, buf, nread, status);
					}
				}
			}
		}

	}
	return 0;
}

cp_int32_t cp_process_write_cb(cp_socket_t *socket, cp_int32_t status)
{
	cp_int32_t								i = 0;
	cp_int32_t								tmp_max_size = 0;
	cp_queue_t								*modules;
	cp_queue_t								*current;
	cp_process_t							*tmp_process = CP_NULL;
	cp_process_manager_t					*tmp_root_manager = CP_NULL;
	cp_process_manager_t					**tmp_manager = CP_NULL;


	tmp_root_manager = (cp_process_manager_t*)cp_manager_get_root_manager(socket->manager->app, cp_module_manager_type_process);
	if (tmp_root_manager) {
		//�ȴ�����������µ���ģ��
		modules = &tmp_root_manager->modules;
		for (current = cp_queue_next(modules); current != modules;
			current = cp_queue_next(current)) {
			tmp_process = cp_queue_data(current, cp_process_t, queue);
			if (tmp_process->write_cb) {
				tmp_process->write_cb(socket, status);
			}
		}
		//Ȼ������������µ���ģ���������ģ��
		tmp_max_size = cp_array_max_size(&tmp_root_manager->module_managers);
		for (i = 0; i < tmp_max_size; i++) {
			//ȡ����ģ����д���
			tmp_manager = cp_array_get(&tmp_root_manager->module_managers, i);
			if (*tmp_manager) {
				modules = &((*tmp_manager)->modules);
				for (current = cp_queue_next(modules); current != modules;
					current = cp_queue_next(current)) {
					tmp_process = cp_queue_data(current, cp_process_t, queue);
					if (tmp_process->write_cb) {
						tmp_process->write_cb(socket, status);
					}
				}
			}
		}

	}
	return 0;
}

cp_int32_t cp_process_error_cb(cp_socket_t *socket, cp_int32_t status)
{
	cp_int32_t								i = 0;
	cp_int32_t								tmp_max_size = 0;
	cp_queue_t								*modules;
	cp_queue_t								*current;
	cp_process_t							*tmp_process = CP_NULL;
	cp_process_manager_t					*tmp_root_manager = CP_NULL;
	cp_process_manager_t					**tmp_manager = CP_NULL;


	tmp_root_manager = (cp_process_manager_t*)cp_manager_get_root_manager(socket->manager->app, cp_module_manager_type_process);
	if (tmp_root_manager) {
		//�ȴ�����������µ���ģ��
		modules = &tmp_root_manager->modules;
		for (current = cp_queue_next(modules); current != modules;
			current = cp_queue_next(current)) {
			tmp_process = cp_queue_data(current, cp_process_t, queue);
			if (tmp_process->error_cb) {
				tmp_process->error_cb(socket, status);
			}
		}
		//Ȼ������������µ���ģ���������ģ��
		tmp_max_size = cp_array_max_size(&tmp_root_manager->module_managers);
		for (i = 0; i < tmp_max_size; i++) {
			//ȡ����ģ����д���
			tmp_manager = cp_array_get(&tmp_root_manager->module_managers, i);
			if (*tmp_manager) {
				modules = &((*tmp_manager)->modules);
				for (current = cp_queue_next(modules); current != modules;
					current = cp_queue_next(current)) {
					tmp_process = cp_queue_data(current, cp_process_t, queue);
					if (tmp_process->error_cb) {
						tmp_process->error_cb(socket, status);
					}
				}
			}
		}

	}
	return 0;
}


/*ģ�鴴���ӿڣ���ʾ����һ��ģ��*/
cp_int32_t init_process(cp_process_t *process, const cp_process_info_t *info)
{
	return cp_init_module(process, info);
}
/*ģ������нӿڣ���ģ��init֮�󣬻ᱻ����*/
cp_int32_t open_process(cp_process_t *process, const cp_process_info_t *info)
{
	return cp_open_module(process, info);
}
/*��ȡģ�����ݣ�flagΪ��ȡģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��*/
cp_int32_t read_process(cp_process_t *process, cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag)
{
	return cp_read_module(process, buf, len, flag);
}
/*дģ�����ݣ�flagΪдģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��*/
cp_int32_t write_process(cp_process_t *process, const cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag)
{
	return cp_write_module(process, buf, len, flag);
}
/*�ر�ģ��*/
cp_int32_t close_process(cp_process_t *process)
{
	return cp_close_module(process);
}
/*�˳�ģ��*/
cp_int32_t exit_process(cp_process_t *process)
{
	return cp_exit_module(process);
}
/*����ģ�����*/
cp_int32_t set_option_process(cp_process_t *process, cp_int32_t optname, const cp_void_t* optval)
{
	return cp_set_option_module(process, optname, optval);
}
cp_int32_t get_option_process(cp_process_t *process, cp_int32_t optname, cp_void_t* optval)
{
	return cp_get_option_module(process, optname, optval);
}







