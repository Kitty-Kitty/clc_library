/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/
#include "cp_vdu_demo_session_manager.h"
#include "cp_include.h"






//ģ�鴴���ӿڣ���ʾ����һ��ģ��
cp_int32_t init_vdu_demo_session_manager(cp_vdu_demo_session_manager_t *manager, const cp_vdu_demo_session_manager_info_t *info);
//ģ������нӿڣ���ģ��init֮�󣬻ᱻ����
cp_int32_t start_vdu_demo_session_manager(cp_vdu_demo_session_manager_t *manager, const cp_vdu_demo_session_manager_info_t *info);
//��ȡģ�����ݣ�flagΪ��ȡģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��
cp_int32_t stop_vdu_demo_session_manager(cp_vdu_demo_session_manager_t *manager);
//����ģ�����
cp_int32_t ctrl_vdu_demo_session_manager(cp_vdu_demo_session_manager_t *manager, cp_int32_t optname, const cp_void_t* optval);
//ģ�鴴���ӿڣ���ʾ����һ��ģ��
cp_vdu_demo_session_t* create_vdu_demo_session_module(cp_vdu_demo_session_manager_t *manager, const cp_vdu_demo_session_info_t *info);
//ģ���ѯ�ӿڣ���ʾ�ӹ������в�ѯһ��ģ��
cp_vdu_demo_session_t* get_vdu_demo_session_module(cp_vdu_demo_session_manager_t *manager, const cp_vdu_demo_session_info_t *info);
//дģ�����ݣ�flagΪдģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��
cp_int32_t register_vdu_demo_session_module(cp_vdu_demo_session_manager_t *manager, cp_vdu_demo_session_t *vdu_demo_session);
//�ر�ģ��
cp_int32_t cancel_vdu_demo_session_module(cp_vdu_demo_session_manager_t *manager, cp_vdu_demo_session_t *vdu_demo_session);
//�˳�ģ��
cp_int32_t destroy_vdu_demo_session_module(cp_vdu_demo_session_manager_t *manager, cp_vdu_demo_session_t *vdu_demo_session);
//����ģ�����
cp_int32_t ctrl_vdu_demo_session_module(cp_vdu_demo_session_manager_t *manager, cp_vdu_demo_session_t *vdu_demo_session, cp_int32_t optname, const cp_void_t* optval);




cp_vdu_demo_session_manager_t* create_vdu_demo_session_manager(cp_module_manager_register_t *register_info, cp_app_t *app, cp_vdu_demo_session_manager_info_t *info)
{
	cp_vdu_demo_session_manager_t			*tmp_manager = CP_NULL;


	if (!app || !info) {
		return tmp_manager;
	}

	//����һ��manager �ڴ�ռ�
	CP_MODULE_MANAGER_MALLOC(tmp_manager, app, cp_vdu_demo_session_manager_t);

	if (tmp_manager) {
		//����manager��Ϣ
		tmp_manager->register_info = *register_info;
		//Ϊ�豸����ռ�
		tmp_manager->pool = cp_create_pool(app);
		//���ø��ֲ������
		CP_MODULE_MANAGER_SET_HANDLERS(tmp_manager, vdu_demo_session);
		//��ʼ��ģ���е����ж���
		cp_manager_create_register_memory(tmp_manager, CP_LIBRARY_MODULE_MANAGER_MAX_SIZE,
			CP_LIBRARY_MODULE_MANAGER_MAX_SIZE, CP_LIBRARY_MODULE_MAX_SIZE);
	}

	return tmp_manager;
}

cp_int32_t destroy_vdu_demo_session_manager(cp_app_t *app, cp_vdu_demo_session_manager_t* manager)
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
cp_int32_t init_vdu_demo_session_manager(cp_vdu_demo_session_manager_t *manager, const cp_vdu_demo_session_manager_info_t *info)
{

#if 0
	cp_session_t							*module;
	cp_int32_t								i = 0;
	cp_int32_t								ret_int = 0;
	cp_session_info_t						tmp_session_info;
	cp_char_t								tmp_buf[CP_APP_DEFAULT_BUFFER_LENGTH] = { 0, };


	//����ģ���������moduleע����Ϣ
// 	cp_manager_set_module_register(tmp_manager, &session_module_list,
// 		session_module_list_size, cp_sizeof(cp_module_register_t));


	for (i = 0; i < session_module_list_size; i++) {
		module = (cp_session_t*)cp_create_module(&session_module_list[i], manager, info);
		if (!module) {
			cp_log_error(manager->logger, "create %s error. return null handle.",
				print_module_register_info(&session_module_list[i], tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH));
			continue;
		}
		cp_memset(&tmp_session_info, 0, cp_sizeof(cp_session_info_t));
		ret_int = cp_init_module(module, &tmp_session_info);
		if (ret_int) {
			cp_log_error(manager->logger, "init %s error. return [%d].",
				print_module_register_info(&session_module_list[i], tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH),
				ret_int);
			continue;
		}
	}
#endif
	return 0;
}
//ģ������нӿڣ���ģ��init֮�󣬻ᱻ����
cp_int32_t start_vdu_demo_session_manager(cp_vdu_demo_session_manager_t *manager, const cp_vdu_demo_session_manager_info_t *info)
{
	return 0;
}
//��ȡģ�����ݣ�flagΪ��ȡģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��
cp_int32_t stop_vdu_demo_session_manager(cp_vdu_demo_session_manager_t *manager)
{
	return 0;
}
//����ģ�����
cp_int32_t ctrl_vdu_demo_session_manager(cp_vdu_demo_session_manager_t *manager, cp_int32_t optname, const cp_void_t* optval)
{
	return 0;
}
//ģ�鴴���ӿڣ���ʾ����һ��ģ��
cp_vdu_demo_session_t* create_vdu_demo_session_module(cp_vdu_demo_session_manager_t *manager, const cp_vdu_demo_session_info_t *info)
{
	cp_int32_t								i = 0;
	cp_module_register_t					*tmp_mr = CP_NULL;




	tmp_mr = cp_manager_get_module_register(manager, info->type);
	if (!tmp_mr) {
		return CP_NULL;
	}
	return (cp_vdu_demo_session_t*)cp_create_module(tmp_mr, manager, info);
}
//ģ���ѯ�ӿڣ���ʾ�ӹ������в�ѯһ��ģ��
cp_vdu_demo_session_t* get_vdu_demo_session_module(cp_vdu_demo_session_manager_t *manager, const cp_vdu_demo_session_info_t *info)
{
	return CP_NULL;
}
//дģ�����ݣ�flagΪдģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��
cp_int32_t register_vdu_demo_session_module(cp_vdu_demo_session_manager_t *manager, cp_vdu_demo_session_t *module)
{
	return 0;
}
//�ر�ģ��
cp_int32_t cancel_vdu_demo_session_module(cp_vdu_demo_session_manager_t *manager, cp_vdu_demo_session_t *module)
{
	return 0;
}
//�˳�ģ��
cp_int32_t destroy_vdu_demo_session_module(cp_vdu_demo_session_manager_t *manager, cp_vdu_demo_session_t *module)
{
	return cp_destroy_module(manager, module);
}
//����ģ�����
cp_int32_t ctrl_vdu_demo_session_module(cp_vdu_demo_session_manager_t *manager, cp_vdu_demo_session_t *module, cp_int32_t optname, const cp_void_t* optval)
{
	return 0;
}





