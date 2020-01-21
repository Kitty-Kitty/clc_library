/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/
#include "cp_include.h"
#include "cp_socket_manager.h"
#include "cp_socket_module_list.h"





//ģ�鴴���ӿڣ���ʾ����һ��ģ��
cp_int32_t init_socket_manager(cp_socket_manager_t *manager, const cp_socket_manager_info_t *info);
//ģ������нӿڣ���ģ��init֮�󣬻ᱻ����
cp_int32_t start_socket_manager(cp_socket_manager_t *manager, const cp_socket_manager_info_t *info);
//��ȡģ�����ݣ�flagΪ��ȡģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��
cp_int32_t stop_socket_manager(cp_socket_manager_t *manager);
//����ģ�����
cp_int32_t ctrl_socket_manager(cp_socket_manager_t *manager, cp_int32_t optname, const cp_void_t* optval);
//ģ�鴴���ӿڣ���ʾ����һ��ģ��
cp_socket_t* create_socket_module(cp_socket_manager_t *manager, const cp_socket_info_t *info);
//ģ���ѯ�ӿڣ���ʾ�ӹ������в�ѯһ��ģ��
cp_socket_t* get_socket_module(cp_socket_manager_t *manager, const cp_socket_info_t *info);
//дģ�����ݣ�flagΪдģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��
cp_int32_t register_socket_module(cp_socket_manager_t *manager, cp_socket_t *socket);
//�ر�ģ��
cp_int32_t cancel_socket_module(cp_socket_manager_t *manager, cp_socket_t *socket);
//�˳�ģ��
cp_int32_t destroy_socket_module(cp_socket_manager_t *manager, cp_socket_t *socket);
//����ģ�����
cp_int32_t ctrl_socket_module(cp_socket_manager_t *manager, cp_socket_t *socket, cp_int32_t optname, const cp_void_t* optval);




cp_socket_manager_t* create_socket_manager(cp_module_manager_register_t *register_info, cp_app_t *app, cp_socket_info_t *info)
{
	cp_socket_manager_t			*tmp_manager = CP_NULL;
	cp_module_manager_register_t *tmp_register_info = CP_NULL;



	if (!app || !info) {
		return tmp_manager;
	}

	//����һ��manager �ڴ�ռ�
	CP_MODULE_MANAGER_MALLOC(tmp_manager, app, cp_socket_manager_t);

	if (tmp_manager) {
		//����manager��Ϣ
		tmp_manager->register_info = *register_info;

		//Ϊ�豸����ռ�
		tmp_manager->pool = cp_create_pool(app);

		//���ø��ֲ������
		CP_MODULE_MANAGER_SET_HANDLERS(tmp_manager, socket);

		//��ʼ��ģ���е����ж���
		cp_manager_create_register_memory(tmp_manager, CP_LIBRARY_MODULE_MANAGER_MAX_SIZE, 
			CP_LIBRARY_MODULE_MANAGER_MAX_SIZE, CP_LIBRARY_MODULE_MAX_SIZE);
	}

	return tmp_manager;
}

cp_int32_t destroy_socket_manager(cp_app_t *app, cp_socket_manager_t* manager)
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
cp_int32_t init_socket_manager(cp_socket_manager_t *manager, const cp_socket_manager_info_t *info)
{
	//���������ģ���������ע�������������������ģ��������Ĵ���
	CP_SUB_MODULE_MANAGER_DEPENDENT(socket, manager->app);

	return 0;
}
//ģ������нӿڣ���ģ��init֮�󣬻ᱻ����
cp_int32_t start_socket_manager(cp_socket_manager_t *manager, const cp_socket_manager_info_t *info)
{
	return 0;
}
//��ȡģ�����ݣ�flagΪ��ȡģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��
cp_int32_t stop_socket_manager(cp_socket_manager_t *manager)
{
	return 0;
}
//����ģ�����
cp_int32_t ctrl_socket_manager(cp_socket_manager_t *manager, cp_int32_t optname, const cp_void_t* optval)
{
	return 0;
}
//ģ�鴴���ӿڣ���ʾ����һ��ģ��
cp_socket_t* create_socket_module(cp_socket_manager_t *manager, const cp_socket_info_t *info)
{
	return CP_NULL;
}
//ģ���ѯ�ӿڣ���ʾ�ӹ������в�ѯһ��ģ��
cp_socket_t* get_socket_module(cp_socket_manager_t *manager, const cp_socket_info_t *info)
{
	return CP_NULL;
}
//дģ�����ݣ�flagΪдģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��
cp_int32_t register_socket_module(cp_socket_manager_t *manager, cp_socket_t *socket)
{
	return 0;
}
//�ر�ģ��
cp_int32_t cancel_socket_module(cp_socket_manager_t *manager, cp_socket_t *socket)
{
	return 0;
}
//�˳�ģ��
cp_int32_t destroy_socket_module(cp_socket_manager_t *manager, cp_socket_t *socket)
{
	return 0;
}
//����ģ�����
cp_int32_t ctrl_socket_module(cp_socket_manager_t *manager, cp_socket_t *socket, cp_int32_t optname, const cp_void_t* optval)
{
	return 0;
}

