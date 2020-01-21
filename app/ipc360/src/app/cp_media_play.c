#include "cp_media_play.h"
#include "cp_ipc_include.h"



cp_int32_t create_media_play(cp_ipc_t *ipc, cp_play_channel_info_t *cp_info)
{
	cp_int32_t							i = 0;
	cp_media_channel_info_t				*tmp_mci = CP_NULL;
	cp_module_t							*tmp_module = CP_NULL;
	cp_ipc_info_t					*tmp_ipc_info = (cp_ipc_info_t *)(ipc->app_info);


	for (i = 0; i < (cp_int32_t)cp_array_max_size(&cp_info->mci_array); i++) {
		if (!cp_array_get(&cp_info->mci_array, i)) {
			continue;
		}

		tmp_mci = (cp_media_channel_info_t*)cp_array_get(&cp_info->mci_array, i);

		//����ͬһ���飬��������
		if (tmp_mci->group_id != tmp_ipc_info->device_info->host.group) {
			continue;
		}

		//���ݲ�ͬ��ý�����ʹ������ִ������
		switch (cp_info->mpy)
		{
		 case cp_media_process_type_audio:
		{
			tmp_module = create_audio_media_play(ipc, tmp_mci);
		}
		break;
		 case cp_media_process_type_video:
		{
			tmp_module = create_video_media_play(ipc, tmp_mci);
		}
		break;
		default:
		{
			cp_app_log(error, ipc, "create_media_play() error. unknow media type[%d]", tmp_mci->media_info.type);
		}
		break;
		}
	}

	//ֻҪ����һ��һ�����Ŷ���Ϊ�ǳɹ���
	if (tmp_module) {
		return 0;
	}
	return -1;
}

cp_int32_t destroy_media_play(cp_ipc_t *ipc, cp_play_channel_info_t *cp_info)
{
	return stop_media_play(ipc, cp_info);
}

cp_int32_t init_media_play(cp_ipc_t *ipc, cp_play_channel_info_t *cp_info)
{
	return 0;
}

cp_int32_t start_media_play(cp_ipc_t *ipc, cp_play_channel_info_t *cp_info)
{
	return 0;
}

cp_int32_t stop_media_play(cp_ipc_t *ipc, cp_play_channel_info_t *cp_info)
{
	cp_int32_t							i = 0;
	cp_int32_t							ret_int = 0;
	cp_int32_t							tmp_successed = 0;
	cp_media_channel_info_t				*tmp_mci = CP_NULL;
	cp_module_t							*tmp_module = CP_NULL;
	cp_ipc_info_t					*tmp_ipc_info = (cp_ipc_info_t *)(ipc->app_info);


	for (i = 0; i < (cp_int32_t)cp_array_max_size(&cp_info->mci_array); i++) {
		if (!cp_array_get(&cp_info->mci_array, i)) {
			continue;
		}

		tmp_mci = (cp_media_channel_info_t*)cp_array_get(&cp_info->mci_array, i);

		//����ͬһ���飬��������
		if (tmp_mci->group_id != tmp_ipc_info->device_info->host.group) {
			continue;
		}

		//���ݲ�ͬ��ý�����ʹ������ִ������
		ret_int = stop_av_media_play_module(ipc, tmp_mci);
		if (ret_int) {
			cp_app_log(error, ipc, "stop_av_media_play_module() error. unknow media type[%d]", tmp_mci->media_info.type);
			continue;
		}

		++tmp_successed;
	}

	//ֻҪ����һ��һ�����Ŷ���Ϊ�ǳɹ���
	if (tmp_successed) {
		return 0;
	}
	return -1;
}

//����һ����Ƶ����ģ��
cp_module_t* create_audio_media_play(cp_ipc_t *ipc, cp_media_channel_info_t *mci)
{
	return create_av_media_play_module(ipc, mci, cp_ipc_manager_type_audio_func, cp_ipc_module_type_audio_func);
}

//����һ����Ƶ����ģ��
cp_module_t* create_video_media_play(cp_ipc_t *ipc, cp_media_channel_info_t *mci)
{
	return create_av_media_play_module(ipc, mci, cp_ipc_manager_type_video_func, cp_ipc_module_type_video_func);
}

//������Ҫ������Ƶģ��
cp_module_t* create_av_media_play_module(cp_ipc_t *ipc, cp_media_channel_info_t *mci,
	cp_int32_t manager_type, cp_int32_t module_type)
{
	cp_module_t									*tmp_module = CP_NULL;
	cp_module_manager_t							*tmp_manager = CP_NULL;
	cp_ipc_info_t							*tmp_ipc_info = (cp_ipc_info_t *)(ipc->app_info);
	cp_module_manager_info_t					tmp_manager_info = { 0, };
	cp_module_info_t							tmp_module_info = { 0, };
	cp_channel_t								tmp_channel = { 0, };
	cp_int32_t									ret_int = 0;
	cp_char_t									tmp_buf[CP_APP_DEFAULT_BUFFER_LENGTH] = { 0, };




	CP_MODULE_MANAGER_INFO_SET_TYPE(&tmp_manager_info, manager_type);

	//��ȡ��Ƶ���������
	tmp_manager = cp_get_manager(ipc, &tmp_manager_info);
	if (!tmp_manager) {
		cp_app_log(error, ipc, "create_av_media_play() error. not found manager_type[%d] error.",
			manager_type);
		return CP_NULL;
	}

	//����һ������ģ��
	CP_MODULE_INFO_SET_TYPE(&tmp_module_info, module_type);
	CP_MODULE_INFO_SET_DATA(&tmp_module_info, mci);

	//�Ȳ���һ��ģ���Ƿ����
	tmp_module = cp_manager_get_module(tmp_manager, &tmp_module_info);
	if (!tmp_module) {
		//��������ʼ����
		tmp_module = cp_manager_create_module(tmp_manager, &tmp_module_info);
		if (!tmp_module) {
			cp_app_log(error, ipc, "create_av_media_play() error. create module_type[%d] error.",
				module_type);
			return CP_NULL;
		}
	}
	else {
		//�����������������
		cp_app_log(warn, ipc, "create_av_media_play() warning. create module_type[%d] existed.",
			module_type);
		//return CP_NULL;
	}

	//��ʼ��ģ��ʧ��
	ret_int = cp_init_module(tmp_module, &tmp_module_info);
	if (ret_int) {
		//��ʼ��ʧ�ܣ�������ģ������
		cp_manager_destroy_module(tmp_manager, tmp_module);
		cp_app_log(error, ipc, "create_av_media_play() error. init %s error.",
			print_module_register_info(&tmp_module->register_info, tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH));
		return CP_NULL;
	}

	//����ģ��ʧ��
	ret_int = cp_open_module(tmp_module, &tmp_module_info);
	if (ret_int) {
		//��ʼ��ʧ�ܣ�������ģ������
		cp_manager_destroy_module(tmp_manager, tmp_module);
		cp_app_log(error, ipc, "create_av_media_play() error. open %s error.",
			print_module_register_info(&tmp_module->register_info, tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH));
		return CP_NULL;
	}

	//����ͨ��
	set_channel(&tmp_channel, mci->channel_info.index, mci->channel_info.play_session, tmp_module, CP_NULL);
	insert_channel(&tmp_ipc_info->channel_manager, &tmp_channel);

	return tmp_module;
}

//ֹͣһ������
cp_int32_t stop_av_media_play_module(cp_ipc_t *ipc, cp_media_channel_info_t *mci)
{
	cp_module_info_t							tmp_module_info = { 0, };
	cp_channel_t								tmp_channel = { 0, };
	cp_channel_t								*tmp_ret_channel = CP_NULL;
	cp_ipc_info_t							*tmp_ipc_info = (cp_ipc_info_t *)(ipc->app_info);
	cp_int32_t									ret_int = 0;



	//����һ������ģ��
	CP_MODULE_INFO_SET_DATA(&tmp_module_info, mci);

	//�Ȳ���һ��ģ���Ƿ����
	tmp_ret_channel = find_channel(&tmp_ipc_info->channel_manager, mci->channel_info.index);
	if (!tmp_ret_channel) {
		cp_app_log(error, ipc, "find_channel() warning. not found module index[%d].",
			mci->channel_info.index);
		return -2;
	}
	tmp_channel = *tmp_ret_channel;
	remove_channel(&tmp_ipc_info->channel_manager, mci->channel_info.index);

	//ͨ��set_option_module�ӿڹرղ���
	ret_int = cp_set_option_module(tmp_channel.module,
		cp_ipc_func_set_option_stop_media_play, &tmp_module_info);
	if (ret_int) {
		cp_app_log(error, ipc, "cp_set_option_module() warning. module[%p].",
			tmp_channel.module);
		return -3;
	}

	return ret_int;
}