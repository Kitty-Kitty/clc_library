/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/
#include "cp_include.h"
#include "cp_hook_manager.h"





extern cp_module_register_t  hook_module_manager_list[];
extern cp_int32_t hook_module_manager_list_size;
extern cp_module_register_t  hook_handle_list[];
extern cp_int32_t hook_handle_list_size;




//ģ�鴴���ӿڣ���ʾ����һ��ģ��
cp_int32_t init_hook_manager(cp_hook_manager_t *manager, const cp_hook_manager_info_t *info);
//ģ������нӿڣ���ģ��init֮�󣬻ᱻ����
cp_int32_t start_hook_manager(cp_hook_manager_t *manager, const cp_hook_manager_info_t *info);
//��ȡģ�����ݣ�flagΪ��ȡģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��
cp_int32_t stop_hook_manager(cp_hook_manager_t *manager);
//����ģ�����
cp_int32_t ctrl_hook_manager(cp_hook_manager_t *manager, cp_int32_t optname, const cp_void_t* optval);
//ģ�鴴���ӿڣ���ʾ����һ��ģ��
cp_hook_t* create_hook_module(cp_hook_manager_t *manager, const cp_hook_info_t *info);
//ģ���ѯ�ӿڣ���ʾ�ӹ������в�ѯһ��ģ��
cp_hook_t* get_hook_module(cp_hook_manager_t *manager, const cp_hook_info_t *info);
//дģ�����ݣ�flagΪдģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��
cp_int32_t register_hook_module(cp_hook_manager_t *manager, cp_hook_t *hook);
//�ر�ģ��
cp_int32_t cancel_hook_module(cp_hook_manager_t *manager, cp_hook_t *hook);
//�˳�ģ��
cp_int32_t destroy_hook_module(cp_hook_manager_t *manager, cp_hook_t *hook);
//����ģ�����
cp_int32_t ctrl_hook_module(cp_hook_manager_t *manager, cp_hook_t *hook, cp_int32_t optname, const cp_void_t* optval);




cp_hook_manager_t* create_hook_manager(cp_module_manager_register_t *register_info, cp_app_t *app, cp_hook_manager_info_t *info)
{
	cp_hook_manager_t			*tmp_manager = CP_NULL;
	cp_module_manager_register_t *tmp_register_info = CP_NULL;



	if (!app || !info) {
		return tmp_manager;
	}

	//����һ��manager �ڴ�ռ�
	CP_MODULE_MANAGER_MALLOC(tmp_manager, app, cp_hook_manager_t);

	if (tmp_manager) {
		//����manager��Ϣ
		tmp_manager->register_info = *register_info;

		//Ϊ�豸����ռ�
		tmp_manager->pool = cp_create_pool(app);

		//���ø��ֲ������
		CP_MODULE_MANAGER_SET_HANDLERS(tmp_manager, hook);

		//��ʼ��ģ���е����ж���
		cp_manager_create_register_memory(tmp_manager, CP_LIBRARY_MODULE_MANAGER_MAX_SIZE,
			CP_LIBRARY_MODULE_MANAGER_MAX_SIZE, CP_LIBRARY_MODULE_MAX_SIZE);
	}

	return tmp_manager;
}

cp_int32_t destroy_hook_manager(cp_app_t *app, cp_hook_manager_t* manager)
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
cp_int32_t init_hook_manager(cp_hook_manager_t *manager, const cp_hook_manager_info_t *info)
{
	return 0;
}
//ģ������нӿڣ���ģ��init֮�󣬻ᱻ����
cp_int32_t start_hook_manager(cp_hook_manager_t *manager, const cp_hook_manager_info_t *info)
{
	return 0;
}
//��ȡģ�����ݣ�flagΪ��ȡģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��
cp_int32_t stop_hook_manager(cp_hook_manager_t *manager)
{
	return 0;
}
//����ģ�����
cp_int32_t ctrl_hook_manager(cp_hook_manager_t *manager, cp_int32_t optname, const cp_void_t* optval)
{
	return 0;
}
//ģ�鴴���ӿڣ���ʾ����һ��ģ��
cp_hook_t* create_hook_module(cp_hook_manager_t *manager, const cp_hook_info_t *info)
{
	return CP_NULL;
}
//ģ���ѯ�ӿڣ���ʾ�ӹ������в�ѯһ��ģ��
cp_hook_t* get_hook_module(cp_hook_manager_t *manager, const cp_hook_info_t *info)
{
	if (!manager || !info) {
		return CP_NULL;
	}

	return manager->hook_array[CP_GET_LIBRARY_SUB_MODULE_TYPE(info->type)];
}
//дģ�����ݣ�flagΪдģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��
cp_int32_t register_hook_module(cp_hook_manager_t *manager, cp_hook_t *module)
{
	return 0;
}
//�ر�ģ��
cp_int32_t cancel_hook_module(cp_hook_manager_t *manager, cp_hook_t *module)
{
	return 0;
}
//�˳�ģ��
cp_int32_t destroy_hook_module(cp_hook_manager_t *manager, cp_hook_t *module)
{
	return 0;
}
//����ģ�����
cp_int32_t ctrl_hook_module(cp_hook_manager_t *manager, cp_hook_t *module, cp_int32_t optname, const cp_void_t* optval)
{
	return 0;
}





