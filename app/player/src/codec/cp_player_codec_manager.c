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
#include "cp_player_codec_manager.h"
#include "cp_include.h"




extern cp_module_register_t  player_codec_module_manager_list[];
extern cp_int32_t player_codec_module_manager_list_size;



//ģ�鴴���ӿڣ���ʾ����һ��ģ��
cp_int32_t init_player_codec_manager(cp_player_codec_manager_t *manager, const cp_player_codec_manager_info_t *info);
//ģ������нӿڣ���ģ��init֮�󣬻ᱻ����
cp_int32_t start_player_codec_manager(cp_player_codec_manager_t *manager, const cp_player_codec_manager_info_t *info);
//��ȡģ�����ݣ�flagΪ��ȡģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��
cp_int32_t stop_player_codec_manager(cp_player_codec_manager_t *manager);
//����ģ�����
cp_int32_t ctrl_player_codec_manager(cp_player_codec_manager_t *manager, cp_int32_t optname, const cp_void_t* optval);
//ģ�鴴���ӿڣ���ʾ����һ��ģ��
cp_codec_t* create_player_codec_module(cp_player_codec_manager_t *manager, const cp_codec_info_t *info);
//ģ���ѯ�ӿڣ���ʾ�ӹ������в�ѯһ��ģ��
cp_codec_t* get_player_codec_module(cp_player_codec_manager_t *manager, const cp_codec_info_t *info);
//дģ�����ݣ�flagΪдģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��
cp_int32_t register_player_codec_module(cp_player_codec_manager_t *manager, cp_codec_t *codec);
//�ر�ģ��
cp_int32_t cancel_player_codec_module(cp_player_codec_manager_t *manager, cp_codec_t *codec);
//�˳�ģ��
cp_int32_t destroy_player_codec_module(cp_player_codec_manager_t *manager, cp_codec_t *codec);
//����ģ�����
cp_int32_t ctrl_player_codec_module(cp_player_codec_manager_t *manager, cp_codec_t *codec, cp_int32_t optname, const cp_void_t* optval);




cp_player_codec_manager_t* create_player_codec_manager(cp_module_manager_register_t *register_info, cp_app_t *app, cp_player_codec_manager_info_t *info)
{
	cp_player_codec_manager_t			*tmp_manager = CP_NULL;


	if (!app || !info) {
		return tmp_manager;
	}

	//����һ��manager �ڴ�ռ�
	CP_MODULE_MANAGER_MALLOC(tmp_manager, app, cp_player_codec_manager_t);

	if (tmp_manager) {
		//����manager��Ϣ
		tmp_manager->register_info = *register_info;
		//Ϊ�豸����ռ�
		tmp_manager->pool = cp_create_pool(app);
		//���ø��ֲ������
		CP_MODULE_MANAGER_SET_HANDLERS(tmp_manager, player_codec);
		//��ʼ��ģ���е����ж���
		cp_manager_create_register_memory(tmp_manager, CP_LIBRARY_MODULE_MANAGER_MAX_SIZE,
			CP_LIBRARY_MODULE_MANAGER_MAX_SIZE, CP_LIBRARY_MODULE_MAX_SIZE);
	}

	return tmp_manager;
}

cp_int32_t destroy_player_codec_manager(cp_app_t *app, cp_player_codec_manager_t* manager)
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
cp_int32_t init_player_codec_manager(cp_player_codec_manager_t *manager, const cp_player_codec_manager_info_t *info)
{
	cp_int32_t										i = 0;
	cp_int32_t										tmp_ret_int = 0;
	cp_char_t										tmp_buf[CP_APP_DEFAULT_BUFFER_LENGTH] = { 0, };




	for (i = 0; i < player_codec_module_manager_list_size; i++) {
		//����һ����������ע����
		tmp_ret_int = cp_manager_set_sub_manager_register(manager, &player_codec_module_manager_list[i], 1, cp_sizeof(cp_module_register_t));
		if (tmp_ret_int) {
			cp_manager_log(error, manager,
				"init_player_codec_manager() error. set_sub_manager_register() error of [%s] register_struct_size[%d].",
				cp_print_manager_register_info(&player_codec_module_manager_list[i], tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH),
				cp_sizeof(cp_module_register_t));
			return -1;
		}
	}

	return 0;
}
//ģ������нӿڣ���ģ��init֮�󣬻ᱻ����
cp_int32_t start_player_codec_manager(cp_player_codec_manager_t *manager, const cp_player_codec_manager_info_t *info)
{
	cp_int32_t										tmp_ret_int = 0;



	//����������ע����
	tmp_ret_int = cp_manager_create_all_sub_manager(manager);
	if (tmp_ret_int) {
		cp_manager_log(error, manager,
			"cp_manager_create_all_sub_manager() error. return [%d]",
			tmp_ret_int);
		return -1;
	}

	//��ʼ��������ע����
	tmp_ret_int = cp_manager_init_all_sub_manager(manager);
	if (tmp_ret_int) {
		cp_manager_log(error, manager,
			"cp_manager_init_all_sub_manager() error. return [%d]",
			tmp_ret_int);
		return -1;
	}

	//����������ע����
	tmp_ret_int = cp_manager_start_all_sub_manager(manager);
	if (tmp_ret_int) {
		cp_manager_log(error, manager,
			"cp_manager_start_all_sub_manager() error. return [%d]",
			tmp_ret_int);
		return -1;
	}

	return 0;
}
//��ȡģ�����ݣ�flagΪ��ȡģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��
cp_int32_t stop_player_codec_manager(cp_player_codec_manager_t *manager)
{
	cp_int32_t										tmp_ret_int = 0;



	//����������ע����
	tmp_ret_int = cp_manager_stop_all_sub_manager(manager);
	if (tmp_ret_int) {
		cp_manager_log(error, manager,
			"cp_manager_stop_all_sub_manager() error. return [%d]",
			tmp_ret_int);
		return -1;
	}

	return 0;
}
//����ģ�����
cp_int32_t ctrl_player_codec_manager(cp_player_codec_manager_t *manager, cp_int32_t optname, const cp_void_t* optval)
{
	return 0;
}
//ģ�鴴���ӿڣ���ʾ����һ��ģ��
cp_codec_t* create_player_codec_module(cp_player_codec_manager_t *manager, const cp_codec_info_t *info)
{
	cp_codec_t							*tmp_new_codec = CP_NULL;
	cp_module_manager_t					*tmp_module_manager = CP_NULL;


	if (!manager || !info) {
		return CP_NULL;
	}

	switch (info->type)
	{
		case cp_player_module_type_hi3531_dec_codec:
		{
			//�����hi3531��ģ�飬����hi3531ģ�������
			tmp_module_manager = cp_manager_get_sub_manager(manager, cp_player_manager_type_hi3531_codec);
			if (tmp_module_manager) {
				tmp_new_codec = (cp_codec_t*)cp_manager_create_module(tmp_module_manager, info);
			}
		}
		break;
		default:
		{
			tmp_new_codec = (cp_codec_t*)cp_manager_create_module_by_register(manager, info);
		}
		break;
	}

	return tmp_new_codec;
}

//ģ���ѯ�ӿڣ���ʾ�ӹ������в�ѯһ��ģ��
cp_codec_t* get_player_codec_module(cp_player_codec_manager_t *manager, const cp_codec_info_t *info)
{
	return CP_NULL;
}

//дģ�����ݣ�flagΪдģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��
cp_int32_t register_player_codec_module(cp_player_codec_manager_t *manager, cp_codec_t *module)
{
	return 0;
}
//�ر�ģ��
cp_int32_t cancel_player_codec_module(cp_player_codec_manager_t *manager, cp_codec_t *module)
{
	return 0;
}
//�˳�ģ��
cp_int32_t destroy_player_codec_module(cp_player_codec_manager_t *manager, cp_codec_t *module)
{
	return 0;
}
//����ģ�����
cp_int32_t ctrl_player_codec_module(cp_player_codec_manager_t *manager, cp_codec_t *module, cp_int32_t optname, const cp_void_t* optval)
{
	return 0;
}
