#include "cp_media_play.h"
#include "cp_fusion_player_include.h"



cp_int32_t create_media_play(cp_fusion_player_t *player, cp_play_channel_info_t *cp_info)
{
	cp_int32_t							i = 0;
	cp_media_channel_info_t				*tmp_mci = CP_NULL;
	cp_module_t							*tmp_module = CP_NULL;
	cp_fusion_player_info_t					*tmp_player_info = (cp_fusion_player_info_t *)(player->app_info);


	for (i = 0; i < (cp_int32_t)cp_array_max_size(&cp_info->mci_array); i++) {
		if (!cp_array_get(&cp_info->mci_array, i)) {
			continue;
		}

		tmp_mci = (cp_media_channel_info_t*)cp_array_get(&cp_info->mci_array, i);

		//不在同一个组，则不做处理
		if (tmp_mci->group_id != tmp_player_info->device_info->host.group) {
			continue;
		}

		//根据不同的媒体类型创建各种处理过程
		switch (cp_info->mpy)
		{
		 case cp_media_process_type_audio:
		{
			//创建一个音频播放需要先关闭所有已经播放的音频
			stop_all_audio_media_play(player);

			cp_mutex_lock(&(tmp_player_info->media_play_manager->audio_play_mutex));
			tmp_module = create_audio_media_play(player, tmp_mci);
			cp_mutex_unlock(&(tmp_player_info->media_play_manager->audio_play_mutex));
		}
		break;
		 case cp_media_process_type_video:
		{
			cp_mutex_lock(&(tmp_player_info->media_play_manager->video_play_mutex));
			tmp_module = create_video_media_play(player, tmp_mci);
			cp_mutex_unlock(&(tmp_player_info->media_play_manager->video_play_mutex));
		}
		break;
		default:
		{
			cp_app_log(error, player, "create_media_play() error. unknow media type[%d]", tmp_mci->media_info.type);
		}
		break;
		}
	}

	//只要创建一个一个播放都认为是成功的
	if (tmp_module) {
		return 0;
	}
	return -1;
}

cp_int32_t destroy_media_play(cp_fusion_player_t *player, cp_play_channel_info_t *cp_info)
{
	return stop_media_play(player, cp_info);
}

cp_int32_t init_media_play(cp_fusion_player_t *player, cp_play_channel_info_t *cp_info)
{
	return 0;
}

cp_int32_t start_media_play(cp_fusion_player_t *player, cp_play_channel_info_t *cp_info)
{
	return 0;
}

cp_int32_t stop_media_play(cp_fusion_player_t *player, cp_play_channel_info_t *cp_info)
{
	cp_int32_t							i = 0;
	cp_int32_t							ret_int = 0;
	cp_int32_t							tmp_successed = 0;
	cp_media_channel_info_t				*tmp_mci = CP_NULL;
	cp_module_t							*tmp_module = CP_NULL;
	cp_fusion_player_info_t					*tmp_player_info = (cp_fusion_player_info_t *)(player->app_info);


	for (i = 0; i < (cp_int32_t)cp_array_max_size(&cp_info->mci_array); i++) {
		if (!cp_array_get(&cp_info->mci_array, i)) {
			continue;
		}

		tmp_mci = (cp_media_channel_info_t*)cp_array_get(&cp_info->mci_array, i);

		//不在同一个组，则不做处理
		if (tmp_mci->group_id != tmp_player_info->device_info->host.group) {
			continue;
		}

		ret_int = 0;

		//根据不同的媒体类型创建各种处理过程

		switch (cp_info->mpy)
		{
		case cp_media_process_type_audio:
		{
			//stop_all_audio_media_play(player);
			cp_mutex_lock(&(tmp_player_info->media_play_manager->audio_play_mutex));
			ret_int = stop_audio_media_play(player, tmp_mci);
			cp_mutex_unlock(&(tmp_player_info->media_play_manager->audio_play_mutex));
		}
		break;
		case cp_media_process_type_video:
		{
			cp_mutex_lock(&(tmp_player_info->media_play_manager->video_play_mutex));
			ret_int = stop_video_media_play(player, tmp_mci);
			cp_mutex_unlock(&(tmp_player_info->media_play_manager->video_play_mutex));
		}
		break;
		default:
		{
			cp_app_log(error, player, "stop_media_play() error. unknow media type[%d]", tmp_mci->media_info.type);
		}
		break;
		}

		if (ret_int) {
			cp_app_log(error, player, "stop_media_play() error. unknow media type[%d]", tmp_mci->media_info.type);
			continue;
		}

		++tmp_successed;
	}

	//只要创建一个一个播放都认为是成功的
	if (tmp_successed) {
		return 0;
	}
	return -1;
}

cp_int32_t update_media_play(cp_fusion_player_t *player, cp_play_channel_info_t *cp_info)
{
	cp_int32_t							i = 0;
	cp_media_channel_info_t				*tmp_mci = CP_NULL;
	cp_module_t							*tmp_module = CP_NULL;
	cp_fusion_player_info_t					*tmp_player_info = (cp_fusion_player_info_t *)(player->app_info);


	for (i = 0; i < (cp_int32_t)cp_array_max_size(&cp_info->mci_array); i++) {
		if (!cp_array_get(&cp_info->mci_array, i)) {
			continue;
		}

		tmp_mci = (cp_media_channel_info_t*)cp_array_get(&cp_info->mci_array, i);

		//不在同一个组，则不做处理
		if (tmp_mci->group_id != tmp_player_info->device_info->host.group) {
			continue;
		}

		//根据不同的媒体类型创建各种处理过程
		switch (cp_info->mpy)
		{
		case cp_media_process_type_audio:
		{
			cp_mutex_lock(&(tmp_player_info->media_play_manager->audio_play_mutex));
			tmp_module = update_audio_media_play(player, tmp_mci);
			cp_mutex_unlock(&(tmp_player_info->media_play_manager->audio_play_mutex));
		}
		break;
		case cp_media_process_type_video:
		{
			cp_mutex_lock(&(tmp_player_info->media_play_manager->video_play_mutex));
			tmp_module = update_video_media_play(player, tmp_mci);
			cp_mutex_unlock(&(tmp_player_info->media_play_manager->video_play_mutex));
		}
		break;
		default:
		{
			cp_app_log(error, player, "update_media_play() error. unknow media type[%d]", tmp_mci->media_info.type);
		}
		break;
		}
	}

	//只要创建一个一个播放都认为是成功的
	if (tmp_module) {
		return 0;
	}
	return -1;
}

//创建一个音频处理模块
cp_module_t* create_audio_media_play(cp_fusion_player_t *player, cp_media_channel_info_t *mci)
{
	return create_av_media_play_module(player, mci, cp_fusion_player_manager_type_audio_func, cp_fusion_player_module_type_audio_func);
}

//创建一个视频处理模块
cp_module_t* create_video_media_play(cp_fusion_player_t *player, cp_media_channel_info_t *mci)
{
	return create_av_media_play_module(player, mci, cp_fusion_player_manager_type_video_func, cp_fusion_player_module_type_video_func);
}

//创建需要的音视频模块
cp_module_t* create_av_media_play_module(cp_fusion_player_t *player, cp_media_channel_info_t *mci,
	cp_int32_t manager_type, cp_int32_t module_type)
{
	cp_module_t									*tmp_module = CP_NULL;
	cp_module_manager_t							*tmp_manager = CP_NULL;
	cp_fusion_player_info_t							*tmp_player_info = (cp_fusion_player_info_t *)(player->app_info);
	cp_module_manager_info_t					tmp_manager_info = { 0, };
	cp_module_info_t							tmp_module_info = { 0, };
	cp_channel_t								tmp_channel = { 0, };
	cp_int32_t									ret_int = 0;
	cp_char_t									tmp_buf[CP_APP_DEFAULT_BUFFER_LENGTH] = { 0, };




	CP_MODULE_MANAGER_INFO_SET_TYPE(&tmp_manager_info, manager_type);

	//获取音频处理管理器
	tmp_manager = cp_get_manager(player, &tmp_manager_info);
	if (!tmp_manager) {
		cp_app_log(error, player, "create_av_media_play() error. not found manager_type[%d] error.",
			manager_type);
		return CP_NULL;
	}

	//创建一个处理模块
	CP_MODULE_INFO_SET_TYPE(&tmp_module_info, module_type);
	CP_MODULE_INFO_SET_DATA(&tmp_module_info, mci);

	//先查找一个模块是否存在
	tmp_module = cp_manager_get_module(tmp_manager, &tmp_module_info);
	if (!tmp_module) {
		//不存在则开始创建
		tmp_module = cp_manager_create_module(tmp_manager, &tmp_module_info);
		if (!tmp_module) {
			cp_app_log(error, player, "create_av_media_play() error. create module_type[%d] error.",
				module_type);
			return CP_NULL;
		}
	}
	else {
		//如果存在则正常处理
		cp_app_log(warn, player, "create_av_media_play() warning. create module_type[%d] existed.",
			module_type);
		//return CP_NULL;
	}

	//初始化模块失败
	ret_int = cp_init_module(tmp_module, &tmp_module_info);
	if (ret_int) {
		//初始化失败，则销毁模块内容
		cp_manager_destroy_module(tmp_manager, tmp_module);
		cp_app_log(error, player, "create_av_media_play() error. init %s error.",
			print_module_register_info(&tmp_module->register_info, tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH));
		return CP_NULL;
	}

	//启动模块失败
	ret_int = cp_open_module(tmp_module, &tmp_module_info);
	if (ret_int) {
		//初始化失败，则销毁模块内容
		cp_manager_destroy_module(tmp_manager, tmp_module);
		cp_app_log(error, player, "create_av_media_play() error. open %s error.",
			print_module_register_info(&tmp_module->register_info, tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH));
		return CP_NULL;
	}

	//设置通道
	set_channel(&tmp_channel, mci->channel_info.index, mci->channel_info.play_session, tmp_module, CP_NULL);
	insert_channel(&tmp_player_info->media_play_manager->channel_manager, &tmp_channel);

	return tmp_module;
}

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: update_audio_media_play
*
* 函数说明: 更新一个音频处理模块
*
* 参    数: cp_fusion_player_t * player						[in]参数说明
* 参    数: cp_media_channel_info_t * mci						[in]参数说明
*
* 返 回 值: cp_module_t*
*           0  : 成功
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2016-11-24 14:58:52
******************************************************************************************************/
cp_module_t* update_audio_media_play(cp_fusion_player_t *player, cp_media_channel_info_t *mci)
{
	return update_av_media_play_module(player, mci, cp_fusion_player_manager_type_audio_func, cp_fusion_player_module_type_audio_func);
}

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: update_audio_media_play
*
* 函数说明: 更新一个视频处理模块
*
* 参    数: cp_fusion_player_t * player						[in]参数说明
* 参    数: cp_media_channel_info_t * mci						[in]参数说明
*
* 返 回 值: cp_module_t*
*           0  : 成功
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2016-11-24 14:58:52
******************************************************************************************************/
cp_module_t* update_video_media_play(cp_fusion_player_t *player, cp_media_channel_info_t *mci)
{
	return update_av_media_play_module(player, mci, cp_fusion_player_manager_type_video_func, cp_fusion_player_module_type_video_func);
}

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: update_av_media_play_module
*
* 函数说明: 更新音视频模块
*
* 参    数: cp_fusion_player_t * player						[in]参数说明
* 参    数: cp_media_channel_info_t * mci						[in]参数说明
* 参    数: cp_int32_t manager_type						[in]参数说明
* 参    数: cp_int32_t module_type						[in]参数说明
*
* 返 回 值: cp_module_t*
*           0  : 成功
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2016-11-24 15:46:54
******************************************************************************************************/
cp_module_t* update_av_media_play_module(cp_fusion_player_t *player, cp_media_channel_info_t *mci, cp_int32_t manager_type, cp_int32_t module_type)
{
	cp_module_t									*tmp_module = CP_NULL;
	cp_module_manager_t							*tmp_manager = CP_NULL;
	cp_fusion_player_info_t							*tmp_player_info = (cp_fusion_player_info_t *)(player->app_info);
	cp_module_manager_info_t					tmp_manager_info = { 0, };
	cp_module_info_t							tmp_module_info = { 0, };
	cp_int32_t									ret_int = 0;
	cp_char_t									tmp_buf[CP_APP_DEFAULT_BUFFER_LENGTH] = { 0, };




	CP_MODULE_MANAGER_INFO_SET_TYPE(&tmp_manager_info, manager_type);

	//获取音频处理管理器
	tmp_manager = cp_get_manager(player, &tmp_manager_info);
	if (!tmp_manager) {
		cp_app_log(error, player, "update_av_media_play_module() error. not found manager_type[%d] error.",
			manager_type);
		return CP_NULL;
	}

	//创建一个处理模块
	CP_MODULE_INFO_SET_TYPE(&tmp_module_info, module_type);
	CP_MODULE_INFO_SET_DATA(&tmp_module_info, mci);

	//先查找一个模块是否存在
	tmp_module = cp_manager_get_module(tmp_manager, &tmp_module_info);
	if (!tmp_module) {
		//不存在则开始创建
		cp_app_log(error, player, "update_av_media_play_module() error. update module_type[%d] error.",
			module_type);
		return CP_NULL;
	}

	//通过set_option_module接口关闭播放
	ret_int = cp_set_option_module(tmp_module,
		cp_fusion_player_func_set_option_update_media_info, &tmp_module_info);
	if (ret_int) {
		cp_app_log(error, player, "cp_set_option_module() warning. module[%p].",
			tmp_module);
		return CP_NULL;
	}

	return tmp_module;
}

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: stop_audio_media_play
*
* 函数说明: 停止音频media play
*
* 参    数: cp_fusion_player_t * player						[in]参数说明
* 参    数: cp_media_channel_info_t * mci						[in]参数说明
*
* 返 回 值: cp_int32_t
*           0  : 成功 
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2017-04-05 19:17:26
******************************************************************************************************/
cp_int32_t stop_audio_media_play(cp_fusion_player_t *player, cp_media_channel_info_t *mci)
{
	return stop_av_media_play_module(player, mci);
}

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: stop_all_audio_media_play
*
* 函数说明: 停止所有音频播放
*
* 参    数: cp_fusion_player_t * player						[in]参数说明
*
* 返 回 值: cp_int32_t
*           0  : 成功
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2017-04-12 17:19:33
******************************************************************************************************/
cp_int32_t stop_all_audio_media_play(cp_fusion_player_t *player)
{
	cp_fusion_player_info_t							*tmp_player_info = (cp_fusion_player_info_t *)(player->app_info);

	cp_mutex_lock(&(tmp_player_info->media_play_manager->audio_play_mutex));

	stop_all_av_media_play_module(player);
	
	cp_mutex_unlock(&(tmp_player_info->media_play_manager->audio_play_mutex));

	return 0;
}

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: stop_video_media_play
*
* 函数说明: 停止视频media play
*
* 参    数: cp_fusion_player_t * player						[in]参数说明
* 参    数: cp_media_channel_info_t * mci						[in]参数说明
*
* 返 回 值: cp_int32_t
*           0  : 成功 
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2017-04-05 19:17:51
******************************************************************************************************/
cp_int32_t stop_video_media_play(cp_fusion_player_t *player, cp_media_channel_info_t *mci)
{
	return stop_av_media_play_module(player, mci);
}

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: stop_all_video_media_play
*
* 函数说明: 停止所有视频播放
*
* 参    数: cp_fusion_player_t * player						[in]参数说明
*
* 返 回 值: cp_int32_t
*           0  : 成功
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2017-04-14 14:16:47
******************************************************************************************************/
cp_int32_t stop_all_video_media_play(cp_fusion_player_t *player)
{
	cp_fusion_player_info_t							*tmp_player_info = (cp_fusion_player_info_t *)(player->app_info);

	cp_mutex_lock(&(tmp_player_info->media_play_manager->video_play_mutex));

	stop_all_av_media_play_module(player);

	cp_mutex_unlock(&(tmp_player_info->media_play_manager->video_play_mutex));

	return 0;
}

//停止一个播放
cp_int32_t stop_av_media_play_module(cp_fusion_player_t *player, cp_media_channel_info_t *mci)
{
	cp_module_info_t							tmp_module_info = { 0, };
	cp_channel_t								tmp_channel = { 0, };
	cp_channel_t								*tmp_ret_channel = CP_NULL;
	cp_fusion_player_info_t							*tmp_player_info = (cp_fusion_player_info_t *)(player->app_info);
	cp_int32_t									ret_int = 0;



	//创建一个处理模块
	CP_MODULE_INFO_SET_DATA(&tmp_module_info, mci);

	//先查找一个模块是否存在
	tmp_ret_channel = find_channel(&tmp_player_info->media_play_manager->channel_manager, mci->channel_info.index);
	if (!tmp_ret_channel) {
		cp_app_log(error, player,
			"find_channel() warning. not found module index[%d].",
			mci->channel_info.index);
		return -2;
	}
	tmp_channel = *tmp_ret_channel;
	remove_channel(&tmp_player_info->media_play_manager->channel_manager, mci->channel_info.index);

	//通过set_option_module接口关闭播放
	ret_int = cp_set_option_module(tmp_channel.module,
		cp_fusion_player_func_set_option_stop_media_play, &tmp_module_info);
	if (ret_int) {
		cp_app_log(error, player,
			"cp_set_option_module() warning. module[%p].",
			tmp_channel.module);
		return -3;
	}

	return ret_int;
}

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: stop_all_av_media_play_module
*
* 函数说明: 关闭所有播放媒体
*
* 参    数: cp_fusion_player_t * player						[in]参数说明
*
* 返 回 值: cp_int32_t
*           0  : 成功
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2017-04-14 14:14:44
******************************************************************************************************/
cp_int32_t stop_all_av_media_play_module(cp_fusion_player_t *player)
{
	cp_channel_t								*tmp_ret_channel = CP_NULL;
	cp_fusion_player_info_t							*tmp_player_info = (cp_fusion_player_info_t *)(player->app_info);
	cp_media_channel_info_t						*tmp_mci = CP_NULL;
	cp_int32_t									tmp_index = 0;
	cp_int32_t									ret_int = 0;


	tmp_ret_channel = find_min_channel(&tmp_player_info->media_play_manager->channel_manager);
	if (!tmp_ret_channel) {
		return 0;
	}

	while (tmp_ret_channel)	{
		tmp_index = tmp_ret_channel->index;
		if (tmp_ret_channel->module) {
			tmp_mci = CP_NULL;
			ret_int = cp_get_option_module(tmp_ret_channel->module,
				cp_fusion_player_func_get_option_media_channel_info, &tmp_mci);
			if (!ret_int && tmp_mci) {
				stop_av_media_play_module(player, tmp_mci);
			}
		}
		remove_channel(&tmp_player_info->media_play_manager->channel_manager, tmp_index);
		tmp_ret_channel = find_next_channel(&tmp_player_info->media_play_manager->channel_manager, tmp_index);
	}

	return 0;
}
