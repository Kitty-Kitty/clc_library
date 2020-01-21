/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/
#include "cp_include.h"
#include "cp_video_func_manager.h"



cp_int32_t	check_video_module(cp_video_func_t *func, cp_media_channel_info_t *mci)
{
	if (!func || !mci) {
		return -1;
	}

	//�ж�ý��ID�Ƿ���ͬ
#if 0
	if (func->mci.channel_info.index == mci->channel_info.index &&
		func->mci.group_id == mci->group_id &&
		!cp_strncmp(func->mci.channel_info.play_session, mci->channel_info.play_session, CP_APP_DEFAULT_SESSION_ID_LENGTH) &&
		!cp_strncmp(func->mci.media_info.id, mci->media_info.id, CP_APP_DEFAULT_ID_LENGTH)) {

		return 0;
	}
#endif
	if (!cp_strncmp(func->mci.media_info.id, mci->media_info.id, CP_APP_DEFAULT_ID_LENGTH)) {
		return 0;
	}

	return -1;
}



//ģ���ʼ���ӿڣ���ģ��create֮�󣬻ᱻ����
cp_int32_t init_video_func_manager(cp_video_func_manager_t *manager, const cp_video_func_manager_info_t *info);
//ģ������нӿڣ���ģ��init֮�󣬻ᱻ����
cp_int32_t start_video_func_manager(cp_video_func_manager_t *manager, const cp_video_func_manager_info_t *info);
//��ȡģ�����ݣ�flagΪ��ȡģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��
cp_int32_t stop_video_func_manager(cp_video_func_manager_t *manager);
//����ģ�����
cp_int32_t ctrl_video_func_manager(cp_video_func_manager_t *manager, cp_int32_t optname, const cp_void_t* optval);
//ģ���ʼ���ӿڣ���ģ��create֮�󣬻ᱻ����
cp_video_func_t* create_video_func_module(cp_video_func_manager_t *manager, const cp_video_func_info_t *info);
//ģ���ѯ�ӿڣ���ʾ�ӹ������в�ѯһ��ģ��
cp_video_func_t* get_video_func_module(cp_video_func_manager_t *manager, const cp_video_func_info_t *info);
//дģ�����ݣ�flagΪдģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��
cp_int32_t register_video_func_module(cp_video_func_manager_t *manager, cp_video_func_t *func);
//�ر�ģ��
cp_int32_t cancel_video_func_module(cp_video_func_manager_t *manager, cp_video_func_t *func);
//�˳�ģ��
cp_int32_t destroy_video_func_module(cp_video_func_manager_t *manager, cp_video_func_t *func);
//����ģ�����
cp_int32_t ctrl_video_func_module(cp_video_func_manager_t *manager, cp_video_func_t *func, cp_int32_t optname, const cp_void_t* optval);




cp_video_func_manager_t* create_video_func_manager(cp_module_manager_register_t *register_info, cp_app_t *app, cp_video_func_manager_info_t *info)
{
	cp_video_func_manager_t			*tmp_manager = CP_NULL;


	if (!app || !info) {
		return tmp_manager;
	}

	//����һ��manager �ڴ�ռ�
	CP_MODULE_MANAGER_MALLOC(tmp_manager, app, cp_video_func_manager_t);

	if (tmp_manager) {
		//����manager��Ϣ
		tmp_manager->register_info = *register_info;
		//Ϊ�豸����ռ�
		tmp_manager->pool = cp_create_pool();
		//���ø��ֲ������
		CP_MODULE_MANAGER_SET_HANDLERS(tmp_manager, video_func);
		//��ʼ��ģ���е����ж���
		cp_manager_create_register_memory(tmp_manager, CP_LIBRARY_MODULE_MANAGER_MAX_SIZE,
			CP_LIBRARY_MODULE_MANAGER_MAX_SIZE, CP_LIBRARY_MODULE_MAX_SIZE);
	}
	return tmp_manager;
}

cp_int32_t destroy_video_func_manager(cp_app_t *app, cp_video_func_manager_t* manager)
{
	if (manager) {
		cp_free(manager);
	}
	return 0;
}



//ģ���ʼ���ӿڣ���ģ��create֮�󣬻ᱻ����
cp_int32_t init_video_func_manager(cp_video_func_manager_t *manager, const cp_video_func_manager_info_t *info)
{
	cp_void_t						*tmp_p = CP_NULL;


	tmp_p = cp_palloc(manager->pool, cp_sizeof(cp_video_func_t*) * CP_VIDEO_FUNC_MAX_NUMBER);
	if (!tmp_p) {
		cp_manager_log(error, manager, "init_video_func_manager() error. cp_palloc() size[%d] failed!",
			cp_sizeof(cp_video_func_t*) * CP_VIDEO_FUNC_MAX_NUMBER);
		return -1;
	}
	cp_memset(tmp_p, 0, cp_sizeof(cp_video_func_t*) * CP_VIDEO_FUNC_MAX_NUMBER);
	cp_array_init(&manager->video_modules, tmp_p, cp_sizeof(cp_video_func_t*), CP_VIDEO_FUNC_MAX_NUMBER);
	cp_mutex_init(&manager->vm_mutex);

	return 0;
}
//ģ������нӿڣ���ģ��init֮�󣬻ᱻ����
cp_int32_t start_video_func_manager(cp_video_func_manager_t *manager, const cp_video_func_manager_info_t *info)
{
#if 0
	cp_int32_t							i = 0;
	cp_module_register_t				*tmp_module_register = CP_NULL;


	//����ģ��ע��������������ģ��
	for (i = 0; i < cp_array_max_size(&manager->module_register); i++) {
		tmp_module_register = *(cp_module_register_t**)cp_array_get(&manager->module_register, i);
		if (!tmp_module_register) {
			continue;
		}
		cp_create_module(tmp_module_register, manager, info);
	}
#endif
	return 0;
}
//��ȡģ�����ݣ�flagΪ��ȡģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��
cp_int32_t stop_video_func_manager(cp_video_func_manager_t *manager)
{
	return 0;
}
//����ģ�����
cp_int32_t ctrl_video_func_manager(cp_video_func_manager_t *manager, cp_int32_t optname, const cp_void_t* optval)
{
	return 0;
}
//ģ���ʼ���ӿڣ���ģ��create֮�󣬻ᱻ����
cp_video_func_t* create_video_func_module(cp_video_func_manager_t *manager, const cp_video_func_info_t *info)
{
	return CP_NULL;
}
//ģ���ѯ�ӿڣ���ʾ�ӹ������в�ѯһ��ģ��
cp_video_func_t* get_video_func_module(cp_video_func_manager_t *manager, const cp_video_func_info_t *info)
{
	cp_int32_t						i = 0;
	cp_int32_t						tmp_find_number = 0;
	cp_int32_t						tmp_number = 0;
	cp_int32_t						tmp_max_size = 0;
	cp_video_func_t					**tmp_vf = CP_NULL;
	cp_video_func_t					*tmp_ret_vf = CP_NULL;



	if (!manager || !info || !info->data) {
		return CP_NULL;
	}

	//������ñ������ҷ�ʽ���д���
	//�����Ҫ�Ż����ܿ���
	cp_mutex_lock(&manager->vm_mutex);
	tmp_number = cp_array_length(&manager->video_modules);
	tmp_max_size = cp_array_max_size(&manager->video_modules);
	for (i = 0; i < tmp_max_size && tmp_find_number < tmp_number; i++) {
		if (!cp_array_get(&manager->video_modules, i)) {
			continue;
		}
		tmp_vf = (cp_video_func_t**)cp_array_get(&manager->video_modules, i);
		if (!(*tmp_vf)) {
			continue;
		}
		++tmp_find_number;
		if (!check_video_module((cp_video_func_t*)(*tmp_vf), (cp_media_channel_info_t*)info->data)) {
			tmp_ret_vf = (*tmp_vf);
			break;
		}
	}
	cp_mutex_unlock(&manager->vm_mutex);
	return tmp_ret_vf;
}
//дģ�����ݣ�flagΪдģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��
cp_int32_t register_video_func_module(cp_video_func_manager_t *manager, cp_video_func_t *module)
{
	cp_int32_t						i = 0;
	cp_int32_t						tmp_number = 0;
	cp_int32_t						tmp_max_size = 0;
	cp_int32_t						tmp_ret_int = -1;
	cp_video_func_t					**tmp_vf = CP_NULL;


	if (!manager || !module) {
		return -1;
	}

	//������ñ������ҷ�ʽ���д���
	//�����Ҫ�Ż����ܿ���
	cp_mutex_lock(&manager->vm_mutex);
	tmp_number = cp_array_length(&manager->video_modules);
	tmp_max_size = cp_array_max_size(&manager->video_modules);
	for (i = 0; i < tmp_max_size; i++) {
		if (!cp_array_get(&manager->video_modules, i)) {
			continue;
		}
		tmp_vf = (cp_video_func_t**)cp_array_get(&manager->video_modules, i);
		if (!(*tmp_vf)) {
			cp_array_set(&manager->video_modules, &module, i);
			tmp_ret_int = 0;
			break;
		}
	}
	cp_mutex_unlock(&manager->vm_mutex);
	return tmp_ret_int;
}
//�ر�ģ��
cp_int32_t cancel_video_func_module(cp_video_func_manager_t *manager, cp_video_func_t *module)
{
	cp_int32_t						i = 0;
	cp_int32_t						tmp_number = 0;
	cp_int32_t						tmp_max_size = 0;
	cp_int32_t						tmp_ret_int = -1;
	cp_video_func_t					**tmp_vf = CP_NULL;


	if (!manager || !module) {
		return -1;
	}

	//������ñ������ҷ�ʽ���д���
	//�����Ҫ�Ż����ܿ���
	cp_mutex_lock(&manager->vm_mutex);
	tmp_number = cp_array_length(&manager->video_modules);
	tmp_max_size = cp_array_max_size(&manager->video_modules);
	for (i = 0; i < tmp_max_size; i++) {
		if (!cp_array_get(&manager->video_modules, i)) {
			continue;
		}
		tmp_vf = (cp_video_func_t**)cp_array_get(&manager->video_modules, i);
		if (module == (*tmp_vf)) {
			tmp_vf = CP_NULL;
			cp_array_set(&manager->video_modules, &tmp_vf, i);
			tmp_ret_int = 0;
			break;
		}
	}
	cp_mutex_unlock(&manager->vm_mutex);
	return tmp_ret_int;
}
//�˳�ģ��
cp_int32_t destroy_video_func_module(cp_video_func_manager_t *manager, cp_video_func_t *module)
{
	return 0;
}
//����ģ�����
cp_int32_t ctrl_video_func_module(cp_video_func_manager_t *manager, cp_video_func_t *module, cp_int32_t optname, const cp_void_t* optval)
{
	return 0;
}





