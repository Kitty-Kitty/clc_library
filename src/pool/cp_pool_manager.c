/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/
#include "cp_include.h"
#include "cp_pool_manager.h"




extern cp_module_register_t  pool_module_list[];




//ģ�鴴���ӿڣ���ʾ����һ��ģ��
cp_int32_t init_pool_manager(cp_pool_manager_t *manager, const cp_pool_manager_info_t *info);
//ģ������нӿڣ���ģ��init֮�󣬻ᱻ����
cp_int32_t start_pool_manager(cp_pool_manager_t *manager, const cp_pool_manager_info_t *info);
//��ȡģ�����ݣ�flagΪ��ȡģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��
cp_int32_t stop_pool_manager(cp_pool_manager_t *manager);
//����ģ�����
cp_int32_t ctrl_pool_manager(cp_pool_manager_t *manager, cp_int32_t optname, const cp_void_t* optval);
//ģ�鴴���ӿڣ���ʾ����һ��ģ��
cp_pool_t* create_pool_module(cp_pool_manager_t *manager, const cp_pool_info_t *info);
//ģ���ѯ�ӿڣ���ʾ�ӹ������в�ѯһ��ģ��
cp_pool_t* get_pool_module(cp_pool_manager_t *manager, const cp_pool_info_t *info);
//дģ�����ݣ�flagΪдģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��
cp_int32_t register_pool_module(cp_pool_manager_t *manager, cp_pool_t *pool);
//�ر�ģ��
cp_int32_t cancel_pool_module(cp_pool_manager_t *manager, cp_pool_t *pool);
//�˳�ģ��
cp_int32_t destroy_pool_module(cp_pool_manager_t *manager, cp_pool_t *pool);
//����ģ�����
cp_int32_t ctrl_pool_module(cp_pool_manager_t *manager, cp_pool_t *pool, cp_int32_t optname, const cp_void_t* optval);




cp_pool_manager_t* create_pool_manager(cp_module_manager_register_t *register_info, cp_app_t *app, cp_pool_manager_info_t *info)
{
	cp_pool_manager_t				*tmp_manager = CP_NULL;
	cp_module_manager_register_t	*tmp_register_info = CP_NULL;
	cp_pool_info_t					tmp_pool_info;



	if (!app || !info) {
		return tmp_manager;
	}

	//����һ��manager �ڴ�ռ�
	CP_MODULE_MANAGER_MALLOC(tmp_manager, app, cp_pool_manager_t);

	if (tmp_manager) {
		//����manager��Ϣ
		tmp_manager->register_info = *register_info;

		cp_memset(&tmp_pool_info, 0, cp_sizeof(tmp_pool_info));
		tmp_pool_info.size = CP_APP_DEFAULT_BUFFER_LENGTH;

		//Ϊ�豸����ռ�
		//tmp_manager->pool = cp_create_pool(app);
		tmp_manager->pool = (cp_pool_t *)(pool_module_list[0].module_create(&pool_module_list[0],
			(cp_module_manager_t *)tmp_manager, (cp_module_info_t *)&tmp_pool_info));

		//���ø��ֲ������
		CP_MODULE_MANAGER_SET_HANDLERS(tmp_manager, pool);

		//��ʼ��ģ���е����ж���
		cp_manager_create_register_memory(tmp_manager, CP_LIBRARY_MODULE_MANAGER_MAX_SIZE,
			CP_LIBRARY_MODULE_MANAGER_MAX_SIZE, CP_LIBRARY_MODULE_MAX_SIZE);
	}

	return tmp_manager;
}

cp_int32_t destroy_pool_manager(cp_app_t *app, cp_pool_manager_t* manager)
{
	if (!manager) {
		return 0;
	}

	if (manager->pool) {
		pool_module_list[0].module_destroy((cp_module_manager_t *)manager, (cp_module_t *)(manager->pool));
	}

	CP_MODULE_MANAGER_FREE(manager);

	return 0;
}



//ģ�鴴���ӿڣ���ʾ����һ��ģ��
cp_int32_t init_pool_manager(cp_pool_manager_t *manager, const cp_pool_manager_info_t *info)
{
	cp_int32_t						ret_int = 0;


	//����һ��ģ��ע����
	ret_int = cp_manager_set_module_register(manager, pool_module_list, 1, cp_sizeof(cp_module_register_t*));
	if (ret_int) {
		return -1;
	}
	return 0;
}
//ģ������нӿڣ���ģ��init֮�󣬻ᱻ����
cp_int32_t start_pool_manager(cp_pool_manager_t *manager, const cp_pool_manager_info_t *info)
{
	return 0;
}
//��ȡģ�����ݣ�flagΪ��ȡģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��
cp_int32_t stop_pool_manager(cp_pool_manager_t *manager)
{
	return 0;
}
//����ģ�����
cp_int32_t ctrl_pool_manager(cp_pool_manager_t *manager, cp_int32_t optname, const cp_void_t* optval)
{
	return 0;
}
//ģ�鴴���ӿڣ���ʾ����һ��ģ��
cp_pool_t* create_pool_module(cp_pool_manager_t *manager, const cp_pool_info_t *info)
{
	return CP_NULL;
}
//ģ���ѯ�ӿڣ���ʾ�ӹ������в�ѯһ��ģ��
cp_pool_t* get_pool_module(cp_pool_manager_t *manager, const cp_pool_info_t *info)
{
	return CP_NULL;
}
//дģ�����ݣ�flagΪдģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��
cp_int32_t register_pool_module(cp_pool_manager_t *manager, cp_pool_t *module)
{
	return 0;
}
//�ر�ģ��
cp_int32_t cancel_pool_module(cp_pool_manager_t *manager, cp_pool_t *module)
{
	return 0;
}
//�˳�ģ��
cp_int32_t destroy_pool_module(cp_pool_manager_t *manager, cp_pool_t *module)
{
	return 0;
}
//����ģ�����
cp_int32_t ctrl_pool_module(cp_pool_manager_t *manager, cp_pool_t *module, cp_int32_t optname, const cp_void_t* optval)
{
	switch (optname)
	{
	case CP_POOL_OPTION_ALLOC:
	case CP_POOL_OPTION_FREE:
	{
		return cp_manager_ctrl_module(manager, module, optname, optval);
	}
	break;
	default:
		return -1;
		break;
	}
	return 0;
}





