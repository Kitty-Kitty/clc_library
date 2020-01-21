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
#include "cp_ecam_codec_manager.h"
#include "cp_include.h"



extern cp_module_register_t  codec_module_list[];




//ģ�鴴���ӿڣ���ʾ����һ��ģ��
cp_int32_t init_ecam_codec_manager(cp_ecam_codec_manager_t *manager, const cp_ecam_codec_manager_info_t *info);
//ģ������нӿڣ���ģ��init֮�󣬻ᱻ����
cp_int32_t start_ecam_codec_manager(cp_ecam_codec_manager_t *manager, const cp_ecam_codec_manager_info_t *info);
//��ȡģ�����ݣ�flagΪ��ȡģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��
cp_int32_t stop_ecam_codec_manager(cp_ecam_codec_manager_t *manager);
//����ģ�����
cp_int32_t ctrl_ecam_codec_manager(cp_ecam_codec_manager_t *manager, cp_int32_t optname, const cp_void_t* optval);
//ģ�鴴���ӿڣ���ʾ����һ��ģ��
cp_codec_t* create_ecam_codec_module(cp_ecam_codec_manager_t *manager, const cp_codec_info_t *info);
//ģ���ѯ�ӿڣ���ʾ�ӹ������в�ѯһ��ģ��
cp_codec_t* get_ecam_codec_module(cp_ecam_codec_manager_t *manager, const cp_codec_info_t *info);
//дģ�����ݣ�flagΪдģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��
cp_int32_t register_ecam_codec_module(cp_ecam_codec_manager_t *manager, cp_codec_t *codec);
//�ر�ģ��
cp_int32_t cancel_ecam_codec_module(cp_ecam_codec_manager_t *manager, cp_codec_t *codec);
//�˳�ģ��
cp_int32_t destroy_ecam_codec_module(cp_ecam_codec_manager_t *manager, cp_codec_t *codec);
//����ģ�����
cp_int32_t ctrl_ecam_codec_module(cp_ecam_codec_manager_t *manager, cp_codec_t *codec, cp_int32_t optname, const cp_void_t* optval);




cp_ecam_codec_manager_t* create_ecam_codec_manager(cp_module_manager_register_t *register_info, cp_app_t *app, cp_ecam_codec_manager_info_t *info)
{
	cp_ecam_codec_manager_t			*tmp_manager = CP_NULL;


	if (!app || !info) {
		return tmp_manager;
	}

	//����һ��manager �ڴ�ռ�
	CP_MODULE_MANAGER_MALLOC(tmp_manager, app, cp_ecam_codec_manager_t);

	if (tmp_manager) {
		//����manager��Ϣ
		tmp_manager->register_info = *register_info;
		//Ϊ�豸����ռ�
		tmp_manager->pool = cp_create_pool(app);
		//���ø��ֲ������
		CP_MODULE_MANAGER_SET_HANDLERS(tmp_manager, ecam_codec);
		//��ʼ��ģ���е����ж���
		cp_manager_create_register_memory(tmp_manager, CP_LIBRARY_MODULE_MANAGER_MAX_SIZE,
			CP_LIBRARY_MODULE_MANAGER_MAX_SIZE, CP_LIBRARY_MODULE_MAX_SIZE);
	}

	return tmp_manager;
}

cp_int32_t destroy_ecam_codec_manager(cp_app_t *app, cp_ecam_codec_manager_t* manager)
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
cp_int32_t init_ecam_codec_manager(cp_ecam_codec_manager_t *manager, const cp_ecam_codec_manager_info_t *info)
{

	return 0;
}
//ģ������нӿڣ���ģ��init֮�󣬻ᱻ����
cp_int32_t start_ecam_codec_manager(cp_ecam_codec_manager_t *manager, const cp_ecam_codec_manager_info_t *info)
{
	return 0;
}
//��ȡģ�����ݣ�flagΪ��ȡģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��
cp_int32_t stop_ecam_codec_manager(cp_ecam_codec_manager_t *manager)
{
	return 0;
}
//����ģ�����
cp_int32_t ctrl_ecam_codec_manager(cp_ecam_codec_manager_t *manager, cp_int32_t optname, const cp_void_t* optval)
{
	return 0;
}
//ģ�鴴���ӿڣ���ʾ����һ��ģ��
cp_codec_t* create_ecam_codec_module(cp_ecam_codec_manager_t *manager, const cp_codec_info_t *info)
{
	//return CP_NULL;
	return (cp_codec_t*)cp_manager_create_module_by_register(manager, info);;
}

//ģ���ѯ�ӿڣ���ʾ�ӹ������в�ѯһ��ģ��
cp_codec_t* get_ecam_codec_module(cp_ecam_codec_manager_t *manager, const cp_codec_info_t *info)
{
	return CP_NULL;
}

//дģ�����ݣ�flagΪдģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��
cp_int32_t register_ecam_codec_module(cp_ecam_codec_manager_t *manager, cp_codec_t *module)
{
	return 0;
}
//�ر�ģ��
cp_int32_t cancel_ecam_codec_module(cp_ecam_codec_manager_t *manager, cp_codec_t *module)
{
	return 0;
}
//�˳�ģ��
cp_int32_t destroy_ecam_codec_module(cp_ecam_codec_manager_t *manager, cp_codec_t *module)
{
	return 0;
}
//����ģ�����
cp_int32_t ctrl_ecam_codec_module(cp_ecam_codec_manager_t *manager, cp_codec_t *module, cp_int32_t optname, const cp_void_t* optval)
{
	return 0;
}

