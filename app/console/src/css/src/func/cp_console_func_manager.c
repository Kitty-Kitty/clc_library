/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/
#include "cp_include.h"
#include "cp_player_func_manager.h"




extern cp_module_register_t  func_module_manager_list[];
extern cp_int32_t func_module_manager_list_size;
extern cp_module_register_t  func_module_list[];
extern cp_int32_t func_module_list_size;




//ģ���ʼ���ӿڣ���ģ��create֮�󣬻ᱻ����
cp_int32_t init_player_func_manager(cp_player_func_manager_t *manager, const cp_player_func_manager_info_t *info);
//ģ������нӿڣ���ģ��init֮�󣬻ᱻ����
cp_int32_t start_player_func_manager(cp_player_func_manager_t *manager, const cp_player_func_manager_info_t *info);
//��ȡģ�����ݣ�flagΪ��ȡģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��
cp_int32_t stop_player_func_manager(cp_player_func_manager_t *manager);
//����ģ�����
cp_int32_t ctrl_player_func_manager(cp_player_func_manager_t *manager, cp_int32_t optname, const cp_void_t* optval);
//ģ���ʼ���ӿڣ���ģ��create֮�󣬻ᱻ����
cp_player_func_t* create_player_func_module(cp_player_func_manager_t *manager, const cp_player_func_info_t *info);
//ģ���ѯ�ӿڣ���ʾ�ӹ������в�ѯһ��ģ��
cp_player_func_t* get_player_func_module(cp_player_func_manager_t *manager, const cp_player_func_info_t *info);
//дģ�����ݣ�flagΪдģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��
cp_int32_t register_player_func_module(cp_player_func_manager_t *manager, cp_player_func_t *func);
//�ر�ģ��
cp_int32_t cancel_player_func_module(cp_player_func_manager_t *manager, cp_player_func_t *func);
//�˳�ģ��
cp_int32_t destory_player_func_module(cp_player_func_manager_t *manager, cp_player_func_t *func);
//����ģ�����
cp_int32_t ctrl_player_func_module(cp_player_func_manager_t *manager, cp_player_func_t *func, cp_int32_t optname, const cp_void_t* optval);




cp_player_func_manager_t* create_player_func_manager(cp_module_manager_register_t *register_info, cp_app_t *app, cp_player_func_manager_info_t *info)
{
	cp_player_func_manager_t			*tmp_manager = CP_NULL;


	if (!app || !info) {
		return tmp_manager;
	}

	//����һ��manager �ڴ�ռ�
	CP_MODULE_MANAGER_MALLOC(tmp_manager, app, cp_player_func_manager_t);

	if (tmp_manager) {
		//����manager��Ϣ
		tmp_manager->register_info = *register_info;
		//Ϊ�豸����ռ�
		tmp_manager->pool = cp_create_pool();
		//���ø��ֲ������
		CP_MODULE_MANAGER_SET_HANDLERS(tmp_manager, player_func);
		//����ģ���������moduleע����Ϣ
		CP_MODULE_MANAGER_SET_REGISTER(tmp_manager, func_module_list, func_module_list_size);
	}
	return tmp_manager;
}

cp_int32_t destory_player_func_manager(cp_app_t *app, cp_player_func_manager_t* manager)
{
	if (manager) {
		cp_free(manager);
	}
	return 0;
}



//ģ���ʼ���ӿڣ���ģ��create֮�󣬻ᱻ����
cp_int32_t init_player_func_manager(cp_player_func_manager_t *manager, const cp_player_func_manager_info_t *info)
{
	cp_int32_t						i = 0;


	for (i = 0; i < func_module_list_size; i++) {
		cp_create_module(&func_module_list[i], manager, info);
	}
	return 0;
}
//ģ������нӿڣ���ģ��init֮�󣬻ᱻ����
cp_int32_t start_player_func_manager(cp_player_func_manager_t *manager, const cp_player_func_manager_info_t *info)
{
	return 0;
}
//��ȡģ�����ݣ�flagΪ��ȡģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��
cp_int32_t stop_player_func_manager(cp_player_func_manager_t *manager)
{
	return 0;
}
//����ģ�����
cp_int32_t ctrl_player_func_manager(cp_player_func_manager_t *manager, cp_int32_t optname, const cp_void_t* optval)
{
	return 0;
}
//ģ���ʼ���ӿڣ���ģ��create֮�󣬻ᱻ����
cp_player_func_t* create_player_func_module(cp_player_func_manager_t *manager, const cp_player_func_info_t *info)
{
	return CP_NULL;
}
//ģ���ѯ�ӿڣ���ʾ�ӹ������в�ѯһ��ģ��
cp_player_func_t* get_player_func_module(cp_player_func_manager_t *manager, const cp_player_func_info_t *info)
{
	return CP_NULL;
}
//дģ�����ݣ�flagΪдģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��
cp_int32_t register_player_func_module(cp_player_func_manager_t *manager, cp_player_func_t *module)
{
	return 0;
}
//�ر�ģ��
cp_int32_t cancel_player_func_module(cp_player_func_manager_t *manager, cp_player_func_t *module)
{
	return 0;
}
//�˳�ģ��
cp_int32_t destory_player_func_module(cp_player_func_manager_t *manager, cp_player_func_t *module)
{
	return 0;
}
//����ģ�����
cp_int32_t ctrl_player_func_module(cp_player_func_manager_t *manager, cp_player_func_t *module, cp_int32_t optname, const cp_void_t* optval)
{
	return 0;
}





