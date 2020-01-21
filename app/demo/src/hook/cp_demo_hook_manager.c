/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/
#include "cp_demo_hook_manager.h"
#include "cp_include.h"



//����ģ��ע����������������
#define CP_LIBRARY_CSS_HOOK_MODULE_MANAGER_MAX_SIZE				8

//����ģ��ע�������������
#define CP_LIBRARY_CSS_HOOK_MODULE_MAX_SIZE						128


//ģ�鴴���ӿڣ���ʾ����һ��ģ��
cp_int32_t init_demo_hook_manager(cp_demo_hook_manager_t *manager, const cp_demo_hook_manager_info_t *info);
//ģ������нӿڣ���ģ��init֮�󣬻ᱻ����
cp_int32_t start_demo_hook_manager(cp_demo_hook_manager_t *manager, const cp_demo_hook_manager_info_t *info);
//��ȡģ�����ݣ�flagΪ��ȡģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��
cp_int32_t stop_demo_hook_manager(cp_demo_hook_manager_t *manager);
//����ģ�����
cp_int32_t ctrl_demo_hook_manager(cp_demo_hook_manager_t *manager, cp_int32_t optname, const cp_void_t* optval);
//ģ�鴴���ӿڣ���ʾ����һ��ģ��
cp_demo_hook_t* create_demo_hook_module(cp_demo_hook_manager_t *manager, const cp_demo_hook_info_t *info);
//ģ���ѯ�ӿڣ���ʾ�ӹ������в�ѯһ��ģ��
cp_demo_hook_t* get_demo_hook_module(cp_demo_hook_manager_t *manager, const cp_demo_hook_info_t *info);
//дģ�����ݣ�flagΪдģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��
cp_int32_t register_demo_hook_module(cp_demo_hook_manager_t *manager, cp_demo_hook_t *demo_hook);
//�ر�ģ��
cp_int32_t cancel_demo_hook_module(cp_demo_hook_manager_t *manager, cp_demo_hook_t *demo_hook);
//�˳�ģ��
cp_int32_t destroy_demo_hook_module(cp_demo_hook_manager_t *manager, cp_demo_hook_t *demo_hook);
//����ģ�����
cp_int32_t ctrl_demo_hook_module(cp_demo_hook_manager_t *manager, cp_demo_hook_t *demo_hook, cp_int32_t optname, const cp_void_t* optval);
//����ģ��ĸ���������ϵ
cp_int32_t demo_hook_dependent(cp_demo_hook_manager_t *manager);



cp_demo_hook_manager_t* create_demo_hook_manager(cp_module_manager_register_t *register_info, cp_app_t *app, cp_demo_hook_manager_info_t *info)
{
	cp_demo_hook_manager_t			*tmp_manager = CP_NULL;


	if (!app || !info) {
		return tmp_manager;
	}

	//����һ��manager �ڴ�ռ�
	CP_MODULE_MANAGER_MALLOC(tmp_manager, app, cp_demo_hook_manager_t);

	if (tmp_manager) {
		//����manager��Ϣ
		tmp_manager->register_info = *register_info;
		//Ϊ�豸����ռ�
		tmp_manager->pool = cp_create_pool(app);
		//���ø��ֲ������
		CP_MODULE_MANAGER_SET_HANDLERS(tmp_manager, demo_hook);
		//��ʼ��ģ���е����ж���
		cp_manager_create_register_memory(tmp_manager, CP_LIBRARY_MODULE_MANAGER_MAX_SIZE,
			CP_LIBRARY_CSS_HOOK_MODULE_MANAGER_MAX_SIZE, CP_LIBRARY_CSS_HOOK_MODULE_MAX_SIZE);
	}

	return tmp_manager;
}

cp_int32_t destroy_demo_hook_manager(cp_app_t *app, cp_demo_hook_manager_t* manager)
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
cp_int32_t init_demo_hook_manager(cp_demo_hook_manager_t *manager, const cp_demo_hook_manager_info_t *info)
{
	cp_int32_t								ret_int = 0;
	cp_int32_t								i = 0;
	cp_demo_hook_t							*hook;
	cp_demo_hook_register_t					*tmp_chr = CP_NULL;
	cp_demo_hook_info_t						tmp_hook_info;
	cp_char_t								tmp_buf[CP_APP_DEFAULT_BUFFER_LENGTH] = { 0, };


	//������ģ���������moduleע����Ϣ
	CP_MODULE_DEPENDENT(demo_hook, manager->app);

	//��ʼ��handleģ���ڴ�ռ�
	manager->hook_array = cp_palloc(manager->pool, cp_sizeof(cp_demo_hook_t*) *
		CP_GET_LIBRARY_SUB_MODULE_TYPE(cp_css_rtp_hook_type_end));
	if (!manager->hook_array) {
		return -1;
	}
	cp_memset(&tmp_hook_info, 0, cp_sizeof(tmp_hook_info));
	cp_memset(manager->hook_array, 0, cp_sizeof(cp_demo_hook_t*) * 
		CP_GET_LIBRARY_SUB_MODULE_TYPE(cp_css_rtp_hook_type_end));
	//��������hookģ��
	for (i = 0; i < (cp_int32_t)cp_array_max_size(&manager->module_register); i++) {
		tmp_chr = *(cp_demo_hook_register_t**)cp_array_get(&manager->module_register, i);
		if (!tmp_chr) {
			continue;
		}
		//�ж������Ƿ�Ϸ�
		if (tmp_chr->type < 0 ||
			tmp_chr->type > cp_css_rtp_hook_type_end) {
			cp_log_error(manager->logger, "create %s error. unknow handle type[%d].",
				cp_print_module_register_info(&hook->register_info, tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH),
				tmp_chr->type);
			continue;
		}
		//���ָ�����͵�handle�Ѿ����ڣ���������
		//ϵͳĬ��ȡ��һ��handle��Ϊ��Чhandle
		if (manager->hook_array[CP_GET_LIBRARY_SUB_MODULE_TYPE(tmp_chr->type)]) {
			cp_log_error(manager->logger, "create %s error. handle exist.",
				cp_print_module_register_info(tmp_chr, tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH));
			continue;
		}
		//����ע�����ݴ���һ��handle
		hook = (cp_demo_hook_t*)cp_create_module(tmp_chr, manager, info);
		//����ģ��λ�ô洢
		if (hook) {
			manager->hook_array[CP_GET_LIBRARY_SUB_MODULE_TYPE(hook->register_info.type)] = (cp_hook_t *)hook;
		} else {
			cp_log_error(manager->logger, "create %s error.", 
				cp_print_module_register_info(tmp_chr, tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH));
		}
	}
	//��ʼ������hookģ��
	for (i = 0; i < CP_GET_LIBRARY_SUB_MODULE_TYPE(cp_css_rtp_hook_type_end); i++) {
		if (manager->hook_array[i]) {
			ret_int = cp_init_module(manager->hook_array[i], &tmp_hook_info);
			if (ret_int) {
				cp_log_error(manager->logger, "init %s error. handle init error.",
					cp_print_module_register_info(&manager->hook_array[i]->register_info, tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH));
				//��ʼ��ʧ�ܣ�������ģ��
				cp_destroy_module(manager, manager->hook_array[i]);
				//��λ�����
				manager->hook_array[i] = CP_NULL;
			}
		}
	}
	//�������ģ���������ϵ
	ret_int = demo_hook_dependent(manager);
	return 0;
}

//ģ������нӿڣ���ģ��init֮�󣬻ᱻ����
cp_int32_t start_demo_hook_manager(cp_demo_hook_manager_t *manager, const cp_demo_hook_manager_info_t *info)
{
	return 0;
}

//��ȡģ�����ݣ�flagΪ��ȡģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��
cp_int32_t stop_demo_hook_manager(cp_demo_hook_manager_t *manager)
{
	return 0;
}

//����ģ�����
cp_int32_t ctrl_demo_hook_manager(cp_demo_hook_manager_t *manager, cp_int32_t optname, const cp_void_t* optval)
{

	return 0;
}

//ģ�鴴���ӿڣ���ʾ����һ��ģ��
cp_demo_hook_t* create_demo_hook_module(cp_demo_hook_manager_t *manager, const cp_demo_hook_info_t *info)
{
	return CP_NULL;
}

//ģ���ѯ�ӿڣ���ʾ�ӹ������в�ѯһ��ģ��
cp_demo_hook_t* get_demo_hook_module(cp_demo_hook_manager_t *manager, const cp_demo_hook_info_t *info)
{
	cp_queue_t								*modules;
	cp_queue_t								*current;
	cp_demo_hook_t							*tmp_hook;


	//����filter manager��������
	modules = &manager->modules;
	for (current = cp_queue_next(modules); current != modules;
		current = cp_queue_next(current)) {
		tmp_hook = cp_queue_data(current, cp_demo_hook_t, queue);
		if (tmp_hook->command == info->command) {
			return tmp_hook;
		}
	}
	return CP_NULL;
}

//дģ�����ݣ�flagΪдģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��
cp_int32_t register_demo_hook_module(cp_demo_hook_manager_t *manager, cp_demo_hook_t *module)
{
	return 0;
}

//�ر�ģ��
cp_int32_t cancel_demo_hook_module(cp_demo_hook_manager_t *manager, cp_demo_hook_t *module)
{
	return 0;
}

//�˳�ģ��
cp_int32_t destroy_demo_hook_module(cp_demo_hook_manager_t *manager, cp_demo_hook_t *module)
{
	return 0;
}
//����ģ�����
cp_int32_t ctrl_demo_hook_module(cp_demo_hook_manager_t *manager, cp_demo_hook_t *module, cp_int32_t optname, const cp_void_t* optval)
{
	return 0;
}
//����ģ��ĸ���������ϵ
cp_int32_t demo_hook_dependent(cp_demo_hook_manager_t *manager)
{
	//������ں�����������ϵ
	cp_demo_hook_entry_dependent(manager);

	//������ȷ���ص�������ϵ
	cp_demo_hook_right_dependent(manager);

	//������󷵻ص�������ϵ
	cp_demo_hook_error_dependent(manager);

	return 0;
}



