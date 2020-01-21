/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/


/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/
#include "cp_include.h"
#include "cp_uv_socket_manager.h"
#include "cp_socket_module_list.h"






//ģ�鴴���ӿڣ���ʾ����һ��ģ��
cp_int32_t init_uv_socket_manager(cp_uv_socket_manager_t *manager, const cp_uv_socket_manager_info_t *info);
//ģ������нӿڣ���ģ��init֮�󣬻ᱻ����
cp_int32_t start_uv_socket_manager(cp_uv_socket_manager_t *manager, const cp_uv_socket_manager_info_t *info);
//��ȡģ�����ݣ�flagΪ��ȡģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��
cp_int32_t stop_uv_socket_manager(cp_uv_socket_manager_t *manager);
//����ģ�����
cp_int32_t ctrl_uv_socket_manager(cp_uv_socket_manager_t *manager, cp_int32_t optname, const cp_void_t* optval);
//ģ�鴴���ӿڣ���ʾ����һ��ģ��
cp_socket_t* create_uv_socket_module(cp_uv_socket_manager_t *manager, const cp_socket_info_t *info);
//ģ���ѯ�ӿڣ���ʾ�ӹ������в�ѯһ��ģ��
cp_socket_t* get_uv_socket_module(cp_uv_socket_manager_t *manager, const cp_socket_info_t *info);
//дģ�����ݣ�flagΪдģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��
cp_int32_t register_uv_socket_module(cp_uv_socket_manager_t *manager, cp_socket_t *socket);
//�ر�ģ��
cp_int32_t cancel_uv_socket_module(cp_uv_socket_manager_t *manager, cp_socket_t *socket);
//�˳�ģ��
cp_int32_t destroy_uv_socket_module(cp_uv_socket_manager_t *manager, cp_socket_t *socket);
//����ģ�����
cp_int32_t ctrl_uv_socket_module(cp_uv_socket_manager_t *manager, cp_socket_t *socket, cp_int32_t optname, const cp_void_t* optval);
//��������loop
cp_void_t start_uv_socket_manager_loop(cp_void_t *manager);

void uv_socket_manager_timer_callback(uv_timer_t* handle);




cp_uv_socket_manager_t* create_uv_socket_manager(cp_module_manager_register_t *register_info,
	cp_app_t *app, cp_uv_socket_manager_info_t *info)
{
	cp_uv_socket_manager_t			*tmp_manager = CP_NULL;


	if (!app || !info) {
		return tmp_manager;
	}

	//����һ��manager �ڴ�ռ�
	CP_MODULE_MANAGER_MALLOC(tmp_manager, app, cp_uv_socket_manager_t);

	if (tmp_manager) {
		//����manager��Ϣ
		tmp_manager->register_info = *register_info;
		//Ϊ�豸����ռ�
		tmp_manager->pool = cp_create_pool(app);
		//���ø��ֲ������
		CP_MODULE_MANAGER_SET_HANDLERS(tmp_manager, uv_socket);
		//��ʼ��ģ���е����ж���
		cp_manager_create_register_memory(tmp_manager, CP_LIBRARY_MODULE_MANAGER_MAX_SIZE,
			CP_LIBRARY_MODULE_MANAGER_MAX_SIZE, CP_LIBRARY_MODULE_MAX_SIZE);
	}

	return tmp_manager;
}

cp_int32_t destroy_uv_socket_manager(cp_app_t *app, cp_uv_socket_manager_t* manager)
{
	if (!manager) {
		return 0;
	}

	if (manager->pool) {
		cp_destroy_pool(manager->pool);
	}

	CP_MODULE_MANAGER_FREE(manager);
	return 0;
}



//ģ�鴴���ӿڣ���ʾ����һ��ģ��
cp_int32_t init_uv_socket_manager(cp_uv_socket_manager_t *manager, const cp_uv_socket_manager_info_t *info)
{
	//������ģ���������moduleע����Ϣ
	CP_MODULE_DEPENDENT(socket, manager->app);

	uv_loop_init(&(manager->loop));
	uv_timer_init(&(manager->loop), &(manager->uv_timer));
	manager->uv_timer.data = manager;

	return 0;
}
//ģ������нӿڣ���ģ��init֮�󣬻ᱻ����
cp_int32_t start_uv_socket_manager(cp_uv_socket_manager_t *manager, const cp_uv_socket_manager_info_t *info)
{
	cp_int32_t					tmp_interval = CP_UV_SOCKET_MANAGER_DEFAULT_INTERVAL;
	cp_char_t					tmp_buf[CP_APP_DEFAULT_BUFFER_LENGTH] = { 0, };


// 	if (info->timer_interval_ms && info->timer_interval_ms > 0) {
// 		tmp_interval = info->timer_interval_ms;
// 	}
	uv_timer_start(&(manager->uv_timer), uv_socket_manager_timer_callback, tmp_interval, tmp_interval);
	manager->thread = cp_create_thread(manager->app, start_uv_socket_manager_loop, manager);
	if (!manager->thread) {
		cp_log_error(manager->logger, "start %s error!", 
			cp_print_manager_register_info(&manager->register_info, tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH));
		return -1;
	}
	return 0;
}
//��ȡģ�����ݣ�flagΪ��ȡģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��
cp_int32_t stop_uv_socket_manager(cp_uv_socket_manager_t *manager)
{
	uv_stop(&(manager->loop));
	return 0;
}
//����ģ�����
cp_int32_t ctrl_uv_socket_manager(cp_uv_socket_manager_t *manager, cp_int32_t optname, const cp_void_t* optval)
{
	return 0;
}
//ģ�鴴���ӿڣ���ʾ����һ��ģ��
cp_socket_t* create_uv_socket_module(cp_uv_socket_manager_t *manager, const cp_socket_info_t *info)
{
	return CP_NULL;
}
//ģ���ѯ�ӿڣ���ʾ�ӹ������в�ѯһ��ģ��
cp_socket_t* get_uv_socket_module(cp_uv_socket_manager_t *manager, const cp_socket_info_t *info)
{
	return CP_NULL;
}
//дģ�����ݣ�flagΪдģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��
cp_int32_t register_uv_socket_module(cp_uv_socket_manager_t *manager, cp_socket_t *module)
{
	return 0;
}
//�ر�ģ��
cp_int32_t cancel_uv_socket_module(cp_uv_socket_manager_t *manager, cp_socket_t *module)
{
	return 0;
}
//�˳�ģ��
cp_int32_t destroy_uv_socket_module(cp_uv_socket_manager_t *manager, cp_socket_t *module)
{
	return cp_destroy_module(manager, module);
}
//����ģ�����
cp_int32_t ctrl_uv_socket_module(cp_uv_socket_manager_t *manager, cp_socket_t *module, cp_int32_t optname, const cp_void_t* optval)
{
	return 0;
}

cp_void_t start_uv_socket_manager_loop(cp_void_t *manager)
{
	cp_uv_socket_manager_t		*tmp_manager = (cp_uv_socket_manager_t *)manager;
	uv_run(&(tmp_manager->loop), UV_RUN_DEFAULT);
	//return 0;
}

void uv_socket_manager_timer_callback(uv_timer_t* handle)
{
	cp_char_t					tmp_buf[CP_APP_DEFAULT_BUFFER_LENGTH] = { 0, };


	cp_uv_socket_manager_t *tmp_manager = (cp_uv_socket_manager_t *)handle->data;
// 	cp_log_notice(manager->logger, "%s timer!",
// 		cp_print_manager_register_info(&manager->register_info, tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH));
	uv_update_time(&(tmp_manager->loop));
}

