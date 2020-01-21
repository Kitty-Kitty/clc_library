/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/
#include "cp_include.h"
#include "cp_fusion_player_extend_manager.h"





//ģ�鴴���ӿڣ���ʾ����һ��ģ��
cp_int32_t init_player_extend_manager(cp_fusion_player_extend_manager_t *manager, const cp_fusion_player_extend_manager_info_t *info);
//ģ������нӿڣ���ģ��init֮�󣬻ᱻ����
cp_int32_t start_player_extend_manager(cp_fusion_player_extend_manager_t *manager, const cp_fusion_player_extend_manager_info_t *info);
//��ȡģ�����ݣ�flagΪ��ȡģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��
cp_int32_t stop_player_extend_manager(cp_fusion_player_extend_manager_t *manager);
//����ģ�����
cp_int32_t ctrl_player_extend_manager(cp_fusion_player_extend_manager_t *manager, cp_int32_t optname, const cp_void_t* optval);
//ģ�鴴���ӿڣ���ʾ����һ��ģ��
cp_fusion_player_extend_t* create_player_extend_module(cp_fusion_player_extend_manager_t *manager, const cp_fusion_player_extend_info_t *info);
//ģ���ѯ�ӿ�
cp_fusion_player_extend_t* get_player_extend_module(cp_fusion_player_extend_manager_t *manager, const cp_fusion_player_extend_info_t *info);
//дģ�����ݣ�flagΪдģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��
cp_int32_t register_player_extend_module(cp_fusion_player_extend_manager_t *manager, cp_fusion_player_extend_t *func);
//�ر�ģ��
cp_int32_t cancel_player_extend_module(cp_fusion_player_extend_manager_t *manager, cp_fusion_player_extend_t *func);
//�˳�ģ��
cp_int32_t destroy_player_extend_module(cp_fusion_player_extend_manager_t *manager, cp_fusion_player_extend_t *func);
//����ģ�����
cp_int32_t ctrl_player_extend_module(cp_fusion_player_extend_manager_t *manager, cp_fusion_player_extend_t *func, cp_int32_t optname, const cp_void_t* optval);




cp_fusion_player_extend_manager_t* create_player_extend_manager(cp_module_manager_register_t *register_info, cp_app_t *app, cp_fusion_player_extend_manager_info_t *info)
{
	cp_fusion_player_extend_manager_t			*tmp_manager = CP_NULL;


	if (!app || !info) {
		return tmp_manager;
	}

	//����һ��manager �ڴ�ռ�
	CP_MODULE_MANAGER_MALLOC(tmp_manager, app, cp_fusion_player_extend_manager_t);

	if (tmp_manager) {
		//����manager��Ϣ
		tmp_manager->register_info = *register_info;
		//Ϊ�豸����ռ�
		tmp_manager->pool = cp_create_pool(app);
		//���ø��ֲ������
		CP_MODULE_MANAGER_SET_HANDLERS(tmp_manager, player_extend);
		//��ʼ��ģ���е����ж���
		cp_manager_create_register_memory(tmp_manager, CP_LIBRARY_MODULE_MANAGER_MAX_SIZE,
			CP_LIBRARY_MODULE_MANAGER_MAX_SIZE, CP_LIBRARY_MODULE_MAX_SIZE);
	}

	return tmp_manager;
}

cp_int32_t destroy_player_extend_manager(cp_app_t *app, cp_fusion_player_extend_manager_t* manager)
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
cp_int32_t init_player_extend_manager(cp_fusion_player_extend_manager_t *manager, const cp_fusion_player_extend_manager_info_t *info)
{
	return 0;
}
//ģ������нӿڣ���ģ��init֮�󣬻ᱻ����
cp_int32_t start_player_extend_manager(cp_fusion_player_extend_manager_t *manager, const cp_fusion_player_extend_manager_info_t *info)
{
	return 0;
}
//��ȡģ�����ݣ�flagΪ��ȡģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��
cp_int32_t stop_player_extend_manager(cp_fusion_player_extend_manager_t *manager)
{
	return 0;
}
//����ģ�����
cp_int32_t ctrl_player_extend_manager(cp_fusion_player_extend_manager_t *manager, cp_int32_t optname, const cp_void_t* optval)
{
	return 0;
}
//ģ�鴴���ӿڣ���ʾ����һ��ģ��
cp_fusion_player_extend_t* create_player_extend_module(cp_fusion_player_extend_manager_t *manager, const cp_fusion_player_extend_info_t *info)
{
	return (cp_fusion_player_extend_t*)cp_manager_create_module_by_register(manager, info);
}
//ģ���ѯ�ӿ�
cp_fusion_player_extend_t* get_player_extend_module(cp_fusion_player_extend_manager_t *manager, const cp_fusion_player_extend_info_t *info)
{
	return CP_NULL;
}
//дģ�����ݣ�flagΪдģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��
cp_int32_t register_player_extend_module(cp_fusion_player_extend_manager_t *manager, cp_fusion_player_extend_t *module)
{
	return 0;
}
//�ر�ģ��
cp_int32_t cancel_player_extend_module(cp_fusion_player_extend_manager_t *manager, cp_fusion_player_extend_t *module)
{
	return 0;
}
//�˳�ģ��
cp_int32_t destroy_player_extend_module(cp_fusion_player_extend_manager_t *manager, cp_fusion_player_extend_t *module)
{
	return 0;
}
//����ģ�����
cp_int32_t ctrl_player_extend_module(cp_fusion_player_extend_manager_t *manager, cp_fusion_player_extend_t *module, cp_int32_t optname, const cp_void_t* optval)
{
	return 0;
}





