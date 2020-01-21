/*******************************************************************************
*
*Copyright:novigo
*
*File name: cp_hi3531_dev_manager.c
*
*Author:fangzhenmu@novigo.com.cn
*
*Version: 1.0
*
*Date:2017/07/27
*
*Description: create (cp_hi3531_dev_manager.c)
*
*Others:
*
*History:
*******************************************************************************/

#include "cp_hi3531_dev_manager.h"
#include "cp_include.h"
#include "cp_hi3531_dev_system.h"



extern cp_module_register_t  hi3531_dev_module_list[];
extern cp_int32_t hi3531_dev_module_list_size;



//ģ�鴴���ӿڣ���ʾ����һ��ģ��
cp_int32_t init_hi3531_dev_manager(cp_hi3531_dev_manager_t *manager, const cp_hi3531_dev_manager_info_t *info);
//ģ������нӿڣ���ģ��init֮�󣬻ᱻ����
cp_int32_t start_hi3531_dev_manager(cp_hi3531_dev_manager_t *manager, const cp_hi3531_dev_manager_info_t *info);
//��ȡģ�����ݣ�flagΪ��ȡģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��
cp_int32_t stop_hi3531_dev_manager(cp_hi3531_dev_manager_t *manager);
//����ģ�����
cp_int32_t ctrl_hi3531_dev_manager(cp_hi3531_dev_manager_t *manager, cp_int32_t optname, const cp_void_t* optval);
//ģ�鴴���ӿڣ���ʾ����һ��ģ��
cp_codec_t* create_hi3531_dev_module(cp_hi3531_dev_manager_t *manager, const cp_codec_info_t *info);
//ģ���ѯ�ӿڣ���ʾ�ӹ������в�ѯһ��ģ��
cp_codec_t* get_hi3531_dev_module(cp_hi3531_dev_manager_t *manager, const cp_codec_info_t *info);
//дģ�����ݣ�flagΪдģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��
cp_int32_t register_hi3531_dev_module(cp_hi3531_dev_manager_t *manager, cp_codec_t *codec);
//�ر�ģ��
cp_int32_t cancel_hi3531_dev_module(cp_hi3531_dev_manager_t *manager, cp_codec_t *codec);
//�˳�ģ��
cp_int32_t destroy_hi3531_dev_module(cp_hi3531_dev_manager_t *manager, cp_codec_t *codec);
//����ģ�����
cp_int32_t ctrl_hi3531_dev_module(cp_hi3531_dev_manager_t *manager, cp_codec_t *codec, cp_int32_t optname, const cp_void_t* optval);




cp_hi3531_dev_manager_t* create_hi3531_dev_manager(cp_module_manager_register_t *register_info, cp_app_t *app, cp_hi3531_dev_manager_info_t *info)
{
	cp_hi3531_dev_manager_t			*tmp_manager = CP_NULL;


	if (!app || !info) {
		return tmp_manager;
	}

	//����һ��manager �ڴ�ռ�
	CP_MODULE_MANAGER_MALLOC(tmp_manager, app, cp_hi3531_dev_manager_t);

	if (tmp_manager) {
		//����manager��Ϣ
		tmp_manager->register_info = *register_info;
		//Ϊ�豸����ռ�
		tmp_manager->pool = cp_create_pool(app);
		//���ø��ֲ������
		CP_MODULE_MANAGER_SET_HANDLERS(tmp_manager, hi3531_dev);
		//��ʼ��ģ���е����ж���
		cp_manager_create_register_memory(tmp_manager, CP_LIBRARY_MODULE_MANAGER_MAX_SIZE,
			CP_LIBRARY_MODULE_MANAGER_MAX_SIZE, CP_LIBRARY_MODULE_MAX_SIZE);
	}

	return tmp_manager;
}

cp_int32_t destroy_hi3531_dev_manager(cp_app_t *app, cp_hi3531_dev_manager_t* manager)
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
cp_int32_t init_hi3531_dev_manager(cp_hi3531_dev_manager_t *manager, const cp_hi3531_dev_manager_info_t *info)
{
	cp_int32_t										i = 0;
	cp_int32_t										tmp_ret_int = 0;
	cp_char_t										tmp_buf[CP_APP_DEFAULT_BUFFER_LENGTH] = { 0, };
	cp_hi3531_dev_manager_info_t						*tmp_info = CP_NULL;
	cp_hi3531_dev_manager_info_t						tmp_info_value = {0, };



	for (i = 0; i < hi3531_dev_module_list_size; i++) {
		//����һ��ģ��ע����
		tmp_ret_int = cp_manager_set_module_register(manager, &hi3531_dev_module_list[i], 1, cp_sizeof(cp_module_register_t));
		if (tmp_ret_int) {
			cp_manager_log(error, manager,
				"init_hi3531_dev_manager() error. cp_manager_set_module_register() error of [%s] register_struct_size[%d].",
				cp_print_manager_register_info(&hi3531_dev_module_list[i], tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH),
				cp_sizeof(cp_module_register_t));
			return -1;
		}
	}

	//��ʼ��������Ϣ
	tmp_ret_int = hi3531_dev_manager_parse_configure((cp_module_manager_t*)manager, &manager->conf_info);
	if (tmp_ret_int) {
		cp_manager_log(error, manager, "hi3531_dev_manager_parse_configure() error.");
		return tmp_ret_int;
	}

	//����ģ����Ϣ
	if (info) {
		tmp_info_value = *info;
	}
	tmp_info_value.manager = manager;

	//����һ��ģ����Ϣ�ڴ�
	tmp_info = create_hi3531_dev_manager_info(manager, &tmp_info_value);
	if (!tmp_info) {
		cp_manager_log(error, manager, "create_hi3531_dev_manager_info() error.");
		return -1;
	} else {
		manager->info = (cp_module_manager_info_t*)tmp_info;
	}

	//��ʼ��hi3531ϵͳ
	tmp_ret_int = init_hi3531_dev_system((cp_module_manager_t*)manager, &tmp_info->sys_info);
	if (tmp_ret_int) {
		stop_hi3531_dev_system((cp_module_manager_t*)manager);
		cp_manager_log(error, manager, "init_hi3531_dev_system() error.");
		return tmp_ret_int;
	}

	return 0;
}

//ģ������нӿڣ���ģ��init֮�󣬻ᱻ����
cp_int32_t start_hi3531_dev_manager(cp_hi3531_dev_manager_t *manager, const cp_hi3531_dev_manager_info_t *info)
{
	cp_int32_t						tmp_ret_int = 0;



	//����hi3531ϵͳ
	tmp_ret_int = start_hi3531_dev_system((cp_module_manager_t*)manager, (cp_hi3531_dev_system_info_t *)&(info->sys_info));
	if (tmp_ret_int) {
		stop_hi3531_dev_system((cp_module_manager_t*)manager);
		cp_manager_log(error, manager, "start_hi3531_dev_system() error.");
		return tmp_ret_int;
	}

	return 0;
}

//��ȡģ�����ݣ�flagΪ��ȡģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��
cp_int32_t stop_hi3531_dev_manager(cp_hi3531_dev_manager_t *manager)
{
	cp_int32_t						tmp_ret_int = 0;



	//ֹͣhi3531ϵͳ
	tmp_ret_int = stop_hi3531_dev_system((cp_module_manager_t*)manager);
	if (tmp_ret_int) {
		cp_manager_log(error, manager, "stop_hi3531_dev_system() error.");
		return tmp_ret_int;
	}

	//����һ��ģ����Ϣ�ڴ�
	tmp_ret_int = destroy_hi3531_dev_manager_info(manager, (cp_hi3531_dev_manager_info_t *)(manager->info));
	if (!tmp_ret_int) {
		cp_manager_log(error, manager, "destroy_hi3531_dev_manager_info() error.");
		return -1;
	}

	return 0;
}



//����ģ�����
cp_int32_t ctrl_hi3531_dev_manager(cp_hi3531_dev_manager_t *manager, cp_int32_t optname, const cp_void_t* optval)
{
	return 0;
}
//ģ�鴴���ӿڣ���ʾ����һ��ģ��
cp_codec_t* create_hi3531_dev_module(cp_hi3531_dev_manager_t *manager, const cp_codec_info_t *info)
{
	cp_codec_info_t									tmp_codec = { 0, };
	cp_video_description_t							tmp_vd = { 0, };



	if (!manager || !info) {
		return CP_NULL;
	}
	
	switch (info->type)
	{
		case cp_player_module_type_hi3531_dev_vo:
		case cp_player_module_type_hi3531_dev_vpss:
		case cp_player_module_type_hi3531_dev_tde:
		case cp_player_module_type_hi3531_dev_sdl:
		{
			//���ڴ���hi3531�Ľ�����ʱ����Ҫ�豸�豸ͨ����
			tmp_codec = *info;
			if (tmp_codec.md) {
				if (cp_media_description_type_video == tmp_codec.md->type) {
					cp_memcpy(&tmp_vd, tmp_codec.md, cp_sizeof(cp_video_description_t));
				}
				else {
					cp_memcpy(&tmp_vd, tmp_codec.md, cp_sizeof(cp_media_description_t));
				}
			}
			else {
				tmp_vd.type = cp_media_description_type_video;
			}

			tmp_vd.channel = 0;
			tmp_codec.md = (cp_media_description_t*)&tmp_vd;

			return (cp_codec_t*)cp_manager_create_module_by_register(manager, &tmp_codec);;
		}
		break;
		default:
		{
			return (cp_codec_t*)cp_manager_create_module_by_register(manager, info);;
		}
		break;
	}
}

//ģ���ѯ�ӿڣ���ʾ�ӹ������в�ѯһ��ģ��
cp_codec_t* get_hi3531_dev_module(cp_hi3531_dev_manager_t *manager, const cp_codec_info_t *info)
{
	return CP_NULL;
}

//дģ�����ݣ�flagΪдģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��
cp_int32_t register_hi3531_dev_module(cp_hi3531_dev_manager_t *manager, cp_codec_t *module)
{
	return 0;
}
//�ر�ģ��
cp_int32_t cancel_hi3531_dev_module(cp_hi3531_dev_manager_t *manager, cp_codec_t *module)
{
	return 0;
}
//�˳�ģ��
cp_int32_t destroy_hi3531_dev_module(cp_hi3531_dev_manager_t *manager, cp_codec_t *module)
{
	return 0;
}
//����ģ�����
cp_int32_t ctrl_hi3531_dev_module(cp_hi3531_dev_manager_t *manager, cp_codec_t *module, cp_int32_t optname, const cp_void_t* optval)
{
	return 0;
}

