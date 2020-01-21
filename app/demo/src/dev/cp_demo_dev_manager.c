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
#include "cp_demo_dev_manager.h"
#include "cp_include.h"



extern cp_module_register_t  codec_module_list[];




//ģ�鴴���ӿڣ���ʾ����һ��ģ��
cp_int32_t init_demo_dev_manager(cp_demo_dev_manager_t *manager, const cp_demo_dev_manager_info_t *info);
//ģ������нӿڣ���ģ��init֮�󣬻ᱻ����
cp_int32_t start_demo_dev_manager(cp_demo_dev_manager_t *manager, const cp_demo_dev_manager_info_t *info);
//��ȡģ�����ݣ�flagΪ��ȡģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��
cp_int32_t stop_demo_dev_manager(cp_demo_dev_manager_t *manager);
//����ģ�����
cp_int32_t ctrl_demo_dev_manager(cp_demo_dev_manager_t *manager, cp_int32_t optname, const cp_void_t* optval);
//ģ�鴴���ӿڣ���ʾ����һ��ģ��
cp_codec_t* create_demo_dev_module(cp_demo_dev_manager_t *manager, const cp_codec_info_t *info);
//ģ���ѯ�ӿڣ���ʾ�ӹ������в�ѯһ��ģ��
cp_codec_t* get_demo_dev_module(cp_demo_dev_manager_t *manager, const cp_codec_info_t *info);
//дģ�����ݣ�flagΪдģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��
cp_int32_t register_demo_dev_module(cp_demo_dev_manager_t *manager, cp_codec_t *codec);
//�ر�ģ��
cp_int32_t cancel_demo_dev_module(cp_demo_dev_manager_t *manager, cp_codec_t *codec);
//�˳�ģ��
cp_int32_t destroy_demo_dev_module(cp_demo_dev_manager_t *manager, cp_codec_t *codec);
//����ģ�����
cp_int32_t ctrl_demo_dev_module(cp_demo_dev_manager_t *manager, cp_codec_t *codec, cp_int32_t optname, const cp_void_t* optval);




cp_demo_dev_manager_t* create_demo_dev_manager(cp_module_manager_register_t *register_info, cp_app_t *app, cp_demo_dev_manager_info_t *info)
{
	cp_demo_dev_manager_t			*tmp_manager = CP_NULL;


	if (!app || !info) {
		return tmp_manager;
	}

	//����һ��manager �ڴ�ռ�
	CP_MODULE_MANAGER_MALLOC(tmp_manager, app, cp_demo_dev_manager_t);

	if (tmp_manager) {
		//����manager��Ϣ
		tmp_manager->register_info = *register_info;
		//Ϊ�豸����ռ�
		tmp_manager->pool = cp_create_pool(app);
		//���ø��ֲ������
		CP_MODULE_MANAGER_SET_HANDLERS(tmp_manager, demo_dev);
		//��ʼ��ģ���е����ж���
		cp_manager_create_register_memory(tmp_manager, CP_LIBRARY_MODULE_MANAGER_MAX_SIZE,
			CP_LIBRARY_MODULE_MANAGER_MAX_SIZE, CP_LIBRARY_MODULE_MAX_SIZE);
	}

	return tmp_manager;
}

cp_int32_t destroy_demo_dev_manager(cp_app_t *app, cp_demo_dev_manager_t* manager)
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
cp_int32_t init_demo_dev_manager(cp_demo_dev_manager_t *manager, const cp_demo_dev_manager_info_t *info)
{

	return 0;
}
//ģ������нӿڣ���ģ��init֮�󣬻ᱻ����
cp_int32_t start_demo_dev_manager(cp_demo_dev_manager_t *manager, const cp_demo_dev_manager_info_t *info)
{
	return 0;
}
//��ȡģ�����ݣ�flagΪ��ȡģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��
cp_int32_t stop_demo_dev_manager(cp_demo_dev_manager_t *manager)
{
	return 0;
}
//����ģ�����
cp_int32_t ctrl_demo_dev_manager(cp_demo_dev_manager_t *manager, cp_int32_t optname, const cp_void_t* optval)
{
	return 0;
}
//ģ�鴴���ӿڣ���ʾ����һ��ģ��
cp_codec_t* create_demo_dev_module(cp_demo_dev_manager_t *manager, const cp_codec_info_t *info)
{
	return CP_NULL;
}

//ģ���ѯ�ӿڣ���ʾ�ӹ������в�ѯһ��ģ��
cp_codec_t* get_demo_dev_module(cp_demo_dev_manager_t *manager, const cp_codec_info_t *info)
{
	return CP_NULL;
}

//дģ�����ݣ�flagΪдģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��
cp_int32_t register_demo_dev_module(cp_demo_dev_manager_t *manager, cp_codec_t *module)
{
	return 0;
}
//�ر�ģ��
cp_int32_t cancel_demo_dev_module(cp_demo_dev_manager_t *manager, cp_codec_t *module)
{
	return 0;
}
//�˳�ģ��
cp_int32_t destroy_demo_dev_module(cp_demo_dev_manager_t *manager, cp_codec_t *module)
{
	return 0;
}
//����ģ�����
cp_int32_t ctrl_demo_dev_module(cp_demo_dev_manager_t *manager, cp_codec_t *module, cp_int32_t optname, const cp_void_t* optval)
{
	return 0;
}
