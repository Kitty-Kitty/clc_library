/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2017-01-04

Description:

**************************************************************************/
#include "cp_sdl_av_dev_audio.h"
#include "cp_log.h"
#include "cp_fusion_player_core.h"




#define			CP_SDL_AV_DEV_AUDIO_MAX_AUDIO_BUFFER_DELAY										32						//表示音频的最大延时数量，操作该数值采用2倍速度播放



/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: audio_pause_ns
*
* 函数说明: 等待播放时间
*
* 参    数: cp_sdl_av_dev_t * sdl_av_dev						[in]参数说明
* 参    数: cp_sdl_av_dev_data_element_t * de						[in]参数说明
*
* 返 回 值: cp_int32_t
*           0  : 成功
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2017-01-10 18:00:22
******************************************************************************************************/
cp_inline cp_static cp_int32_t audio_pause_ns(cp_sdl_av_dev_t *sdl_av_dev, cp_sdl_av_dev_data_element_t *de)
{
	cp_timespec_t								tmp_ts = { 0, };
	cp_fusion_player_t									*tmp_player = (cp_fusion_player_t*)sdl_av_dev->manager->app;
	cp_fusion_player_info_t							*tmp_player_info = (cp_fusion_player_info_t *)(tmp_player->app_info);


	tmp_ts = cp_fusion_player_ptp_offset(&tmp_player_info->player_timestamp, &de->data.ts);
	if (tmp_ts.tv_sec >= 0 && tmp_ts.tv_nsec > 0) {
		cp_sleep_ns(0, tmp_ts.tv_nsec);
	}
	return 0;
}


/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: audio_play_delay
*
* 函数说明: 音频播放暂停次数
*
* 参    数: cp_sdl_av_dev_t * sdl_av_dev						[in]参数说明
* 参    数: cp_sdl_av_dev_data_element_t * de						[in]参数说明
*
* 返 回 值: cp_inline cp_static cp_int32_t
*           0  : 成功 
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2017-06-10 20:10:23
******************************************************************************************************/
cp_inline cp_static cp_int32_t audio_play_delay(cp_sdl_av_dev_t *sdl_av_dev, cp_sdl_av_dev_data_element_t *de)
{
	if (!sdl_av_dev) {
		return 0;
	}

	if (sdl_av_dev->audio_info->play_delay_ns > 0 && 
		sdl_av_dev->audio_info->play_delay_max_times > 0 && 
		sdl_av_dev->audio_info->play_delay_times < sdl_av_dev->audio_info->play_delay_max_times) {
		cp_sleep_ns(0, sdl_av_dev->audio_info->play_delay_ns);
		++(sdl_av_dev->audio_info->play_delay_times);
	}

	return 0;
}

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: sdl_av_dev_audio_callback
*
* 函数说明: 播放声音的返回函数，主要是写数据使用
*
* 参    数: void * udata						[in]参数说明
* 参    数: Uint8 * stream					[in]参数说明
* 参    数: int len							[in]参数说明
*
* 返 回 值: void
*           0  : 成功
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2016-11-18 14:42:42
******************************************************************************************************/
void  sdl_av_dev_audio_callback(void *udata, Uint8 *stream, int len)
{
	cp_int32_t								tmp_volume = SDL_MIX_MAXVOLUME;
	cp_int32_t								tmp_play_delay_sample_number = 0;
	cp_sdl_av_dev_t							*tmp_sdl_av_dev = CP_NULL;
	cp_lockfree_queue_element_t				*tmp_lfq_elem = CP_NULL;
	cp_sdl_av_dev_data_element_t			*tmp_sdl_elem = CP_NULL;


 	if (len > 0) {
 		SDL_memset(stream, 0, len);
 	}

	if (!udata) {
		cp_log_printf("sdl_av_dev_audio_callback() error. udata is null error.");
		return;
	}
	tmp_sdl_av_dev = (cp_sdl_av_dev_t*)udata;

	//音频暂停时间
	audio_play_delay(tmp_sdl_av_dev, tmp_sdl_elem);

#if 0
	while (tmp_sdl_av_dev->audio_info->used_queue.size > 40)
	{
		if (cp_lockfree_queue_pop(&tmp_sdl_av_dev->audio_info->used_queue, &tmp_lfq_elem)) {
			return;
		}
		if (!tmp_lfq_elem) {
			//cp_module_log(error, tmp_sdl_av_dev, "sdl_av_dev_audio_callback() error. lockfree_queue_element is null.");
			continue;
		}
		if (tmp_lfq_elem->value) {
			tmp_sdl_elem = (cp_sdl_av_dev_data_element_t*)tmp_lfq_elem->value;

			//如果缓存数量太多,则删除
			if (tmp_sdl_av_dev->audio_info->max_buffer_size > tmp_sdl_av_dev->audio_info->current_buffer_size) {
				destroy_sdl_av_dev_data_element(tmp_sdl_av_dev->pool, tmp_sdl_elem);
				--(tmp_sdl_av_dev->audio_info->max_buffer_size);
				continue;
			}

			//清空数据
			cp_clear_sdl_av_dev_data(&tmp_sdl_elem->data);

			//插入空闲队列
			cp_lockfree_queue_push(&tmp_sdl_av_dev->audio_info->free_queue,
				&tmp_sdl_elem->lfq_elem,
				tmp_sdl_elem->data.index,
				CP_NULL);
		}
	}
#endif

	if (tmp_sdl_av_dev->audio_info->play_delay_sample_number > 0) {
		tmp_play_delay_sample_number = tmp_sdl_av_dev->audio_info->play_delay_sample_number;
	}
	else {
		tmp_play_delay_sample_number = CP_SDL_AV_DEV_AUDIO_MAX_AUDIO_BUFFER_DELAY;
	}
	//如果操作最大延时时间采用两倍速度过度
	if (tmp_sdl_av_dev->audio_info->used_queue.size > tmp_play_delay_sample_number)
	{
		if (cp_lockfree_queue_pop(&tmp_sdl_av_dev->audio_info->used_queue, &tmp_lfq_elem)) {
			return;
		}
		if (tmp_lfq_elem) {
			//cp_module_log(error, tmp_sdl_av_dev, "sdl_av_dev_audio_callback() error. lockfree_queue_element is null.");
			if (tmp_lfq_elem->value) {
				tmp_sdl_elem = (cp_sdl_av_dev_data_element_t*)tmp_lfq_elem->value;

				//如果缓存数量太多,则删除
				if (tmp_sdl_av_dev->audio_info->max_buffer_size > tmp_sdl_av_dev->audio_info->current_buffer_size) {
					destroy_sdl_av_dev_data_element(tmp_sdl_av_dev->pool, tmp_sdl_elem);
					--(tmp_sdl_av_dev->audio_info->max_buffer_size);
				}
				else {
					//清空数据
					cp_clear_sdl_av_dev_data(&tmp_sdl_elem->data);

					//插入空闲队列
					cp_lockfree_queue_push(&tmp_sdl_av_dev->audio_info->free_queue,
						&tmp_sdl_elem->lfq_elem,
						tmp_sdl_elem->data.index,
						CP_NULL);
				}
			}
		}
	}

	if (cp_lockfree_queue_pop(&tmp_sdl_av_dev->audio_info->used_queue, &tmp_lfq_elem)) {
		return;
	}
	if (!tmp_lfq_elem) {
		//cp_module_log(error, tmp_sdl_av_dev, "sdl_av_dev_audio_callback() error. lockfree_queue_element is null.");
		return;
	}

	if (tmp_lfq_elem->value) {
		tmp_sdl_elem = (cp_sdl_av_dev_data_element_t*)tmp_lfq_elem->value;
		tmp_volume = (cp_int32_t)(((cp_float_t)SDL_MIX_MAXVOLUME / 100.0f) * (tmp_sdl_elem->data.volume));
		//设置播放数据
		len = (len > cp_buf_get_length(&tmp_sdl_elem->data.buf) ? cp_buf_get_length(&tmp_sdl_elem->data.buf) : len);

		//休眠等待
		//audio_pause_ns(tmp_sdl_av_dev, tmp_sdl_elem);

		SDL_MixAudio(stream, cp_buf_get_pos(&tmp_sdl_elem->data.buf), len, tmp_volume);
		//SDL_MixAudio(stream, cp_buf_get_pos(&tmp_sdl_elem->data.buf), len, SDL_MIX_MAXVOLUME);
		//SDL_Delay(1);

		//如果缓存数量太多,则删除
		if (tmp_sdl_av_dev->audio_info->max_buffer_size > tmp_sdl_av_dev->audio_info->current_buffer_size) {
			destroy_sdl_av_dev_data_element(tmp_sdl_av_dev->pool, tmp_sdl_elem);
			--(tmp_sdl_av_dev->audio_info->max_buffer_size);
			return;
		}

		//清空数据
		cp_clear_sdl_av_dev_data(&tmp_sdl_elem->data);
	}

	//插入空闲队列
	cp_lockfree_queue_push(&tmp_sdl_av_dev->audio_info->free_queue,
		&tmp_sdl_elem->lfq_elem,
		tmp_sdl_elem->data.index,
		CP_NULL);
}


/*打开音频设置*/
cp_int32_t open_sdl_audio_dev(cp_sdl_av_dev_t *sdl_av_dev, const cp_sdl_av_dev_info_t *sdl_av_dev_info)
{
	cp_int32_t						tmp_ret_int = 0;



	//打印audio device信息
	save_audio_device_info(sdl_av_dev);

	if (!SDL_WasInit(SDL_INIT_AUDIO)) {
		if (SDL_Init(SDL_INIT_AUDIO)) {
			cp_module_log(error, sdl_av_dev, "could not initialize sdl[%s]. %s",
				SDL_GetRevision(),
				SDL_GetError());
			return -1;
		}
		else {
			cp_module_log(notice, sdl_av_dev, "initialize sdl[%s] audio successed.",
				SDL_GetRevision());
		}
	}
	
	//创建音频信息
	tmp_ret_int = create_sdl_audio_info(sdl_av_dev, sdl_av_dev_info);
	if (tmp_ret_int) {
		cp_module_log(error, sdl_av_dev, "create_sdl_audio_info() error.");
		return -2;
	}

	//初始化音频信息
	tmp_ret_int = init_sdl_audio_buffer_queue(sdl_av_dev, sdl_av_dev_info);
	if (tmp_ret_int) {
		cp_module_log(error, sdl_av_dev, "init_sdl_audio_buffer_queue() error.");
		return -1;
	}

	//设置音频信息
	tmp_ret_int = set_audio_spec(sdl_av_dev, sdl_av_dev->audio_info);
	if (tmp_ret_int) {
		cp_module_log(error, sdl_av_dev, "set_audio_spec() error.");
		return -1;
	}

	//打开音频开始播放
	if (SDL_OpenAudio(&sdl_av_dev->audio_info->wanted_spec, NULL) < 0) {
		cp_module_log(error, sdl_av_dev, "can't open audio. %s", SDL_GetError());
		return -1;
	}

	//开始进行播放
	SDL_PauseAudio(0);
	return 0;
}

/*写音频数据*/
cp_int32_t write_sdl_audio_data(cp_sdl_av_dev_t *sdl_av_dev, cp_media_packet_t *mp)
{
	cp_lockfree_queue_element_t				*tmp_lfq_elem = CP_NULL;
	cp_sdl_av_dev_data_element_t			*tmp_sdl_elem = CP_NULL;
	cp_audio_description_t					*tmp_ad = CP_NULL;


	if (cp_buf_get_length(&mp->mp_buf.buf[0]) <= 0 || !mp || !mp->md_p) {
		return -1;
	}

	//这里
	if (sdl_av_dev->audio_info->current_buffer_size > sdl_av_dev->audio_info->max_buffer_size) {
		if (!add_sdl_audio_buffer_queue(sdl_av_dev,
			sdl_av_dev->audio_info->current_buffer_size - sdl_av_dev->audio_info->max_buffer_size)) {
			sdl_av_dev->audio_info->max_buffer_size = sdl_av_dev->audio_info->current_buffer_size;
		}
	}

	if (cp_lockfree_queue_pop(&sdl_av_dev->audio_info->free_queue, &tmp_lfq_elem)) {
		cp_module_log(error, sdl_av_dev, "write_sdl_audio_data() error. cp_lockfree_queue_pop() failed!");
		return -1;
	}

	if (!tmp_lfq_elem) {
		cp_module_log(error, sdl_av_dev, "write_sdl_audio_data() not found dev_data_element");
		return -2;
	}

	tmp_sdl_elem = (cp_sdl_av_dev_data_element_t*)tmp_lfq_elem->value;

	if (cp_buf_get_length(&mp->mp_buf.buf[0]) > cp_buf_get_size(&tmp_sdl_elem->data.buf)) {
		//插入空闲队列
		cp_lockfree_queue_push(&sdl_av_dev->audio_info->used_queue,
			&tmp_sdl_elem->lfq_elem,
			tmp_sdl_elem->data.index,
			CP_NULL);

		cp_module_log(error, sdl_av_dev,
			"write_sdl_audio_data() data length error. data[%d] more than [%d]",
			cp_buf_get_length(&mp->mp_buf.buf[0]),
			cp_buf_get_size(&tmp_sdl_elem->data.buf));

		return -2;
	}
	tmp_ad = (cp_audio_description_t*)(mp->md_p);
	tmp_sdl_elem->data.type = mp->type;
	tmp_sdl_elem->data.ts = mp->ts;
	tmp_sdl_elem->data.volume = tmp_ad->volume;
	cp_buf_clear(&tmp_sdl_elem->data.buf);
	cp_buf_strcat(&tmp_sdl_elem->data.buf, cp_buf_get_pos(&mp->mp_buf.buf[0]), cp_buf_get_length(&mp->mp_buf.buf[0]));

	//插入空闲队列
	cp_lockfree_queue_push(&sdl_av_dev->audio_info->used_queue,
		&tmp_sdl_elem->lfq_elem,
		tmp_sdl_elem->data.index,
		CP_NULL);

	return 0;
}

/*关闭音频设备*/
cp_int32_t close_sdl_audio_dev(cp_sdl_av_dev_t *sdl_av_dev)
{
	//关闭音频设备
	SDL_CloseAudio();
	return 0;
}

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: init_sdl_audio_buffer_queue
*
* 函数说明: 初始化音频信息
*
* 参    数: cp_sdl_av_dev_t * sdl_av_dev						[in]参数说明
* 参    数: cp_int32_t * i						[in]参数说明
* 参    数: const cp_sdl_av_dev_info_t * sdl_av_dev_info						[in]参数说明
*
* 返 回 值: cp_int32_t
*           0  : 成功
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2016-12-20 11:28:42
******************************************************************************************************/
cp_int32_t init_sdl_audio_buffer_queue(cp_sdl_av_dev_t * sdl_av_dev, const cp_sdl_av_dev_info_t * sdl_av_dev_info)
{
	cp_int32_t										tmp_buffer_length = 0;
	cp_int32_t										tmp_buffer_size = 0;
	cp_sdl_av_dev_data_element_t					*tmp_data_elem = CP_NULL;



	if (sdl_av_dev->audio_info->ad.samples_buffer_size <= 0) {
		cp_module_log(error, sdl_av_dev, "init_sdl_audio_buffer_queue() error. audio temp buffer length[%d] error.",
			sdl_av_dev->audio_info->ad.samples_buffer_size);
		return -1;
	}
	else {
		tmp_buffer_length = sdl_av_dev->audio_info->ad.samples_buffer_size;
	}

	//创建最大缓存数量
	sdl_av_dev->audio_info->max_buffer_size = CP_SDL_AV_DEV_MAX_BUFFER_SIZE;
	if (sdl_av_dev->audio_info->max_buffer_size <= 0) {
		cp_module_log(error, sdl_av_dev, "init_sdl_audio_buffer_queue() error. max buffer size[%d] error.",
			sdl_av_dev->audio_info->max_buffer_size);
		return -2;
	}
	tmp_buffer_size = sdl_av_dev->audio_info->max_buffer_size;
	sdl_av_dev->audio_info->current_buffer_size = sdl_av_dev->audio_info->max_buffer_size;

	//初始化无所队列
	cp_lockfree_queue_init(&sdl_av_dev->audio_info->free_queue, cp_lockfree_queue_mode_qbss);
	cp_lockfree_queue_init(&sdl_av_dev->audio_info->used_queue, cp_lockfree_queue_mode_qbss);

	cp_lockfree_queue_set_option(&sdl_av_dev->audio_info->free_queue,
		cp_lockfree_queue_option_bounded, &tmp_buffer_size);
	cp_lockfree_queue_set_option(&sdl_av_dev->audio_info->used_queue,
		cp_lockfree_queue_option_bounded, &tmp_buffer_size);

	cp_lockfree_queue_start(&sdl_av_dev->audio_info->free_queue);
	cp_lockfree_queue_start(&sdl_av_dev->audio_info->used_queue);

	//初始化缓存内容
	add_sdl_audio_buffer_queue(sdl_av_dev, tmp_buffer_size);

	return 0;
}

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: update_sdl_audio_buffer_queue
*
* 函数说明: 更新音频缓存大小
*
* 参    数: cp_sdl_av_dev_t * sdl_av_dev						[in]参数说明
* 参    数: cp_int32_t size						[in]参数说明
*
* 返 回 值: cp_int32_t
*           0  : 成功
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2016-12-21 10:07:10
******************************************************************************************************/
cp_int32_t update_sdl_audio_buffer_queue(cp_sdl_av_dev_t * sdl_av_dev, cp_int32_t size)
{
	cp_int32_t										i = 0;
	cp_int32_t										tmp_num = 0;
	cp_sdl_av_dev_data_element_t					*tmp_data_elem = CP_NULL;



	if (sdl_av_dev->audio_info) {
		sdl_av_dev->audio_info->current_buffer_size = size;
		return 0;
	}
	cp_module_log(warn, sdl_av_dev, "sdl device not found audio information!");
	return -1;
}

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: add_sdl_audio_buffer_queue
*
* 函数说明: 表示添加缓存大小
*
* 参    数: cp_sdl_av_dev_t * sdl_av_dev						[in]参数说明
* 参    数: cp_int32_t size						[in]参数说明
*
* 返 回 值: cp_int32_t
*           0  : 成功
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2016-12-21 17:57:21
******************************************************************************************************/
cp_int32_t add_sdl_audio_buffer_queue(cp_sdl_av_dev_t * sdl_av_dev, cp_int32_t size)
{
	cp_int32_t										i = 0;
	cp_sdl_av_dev_data_element_t					*tmp_data_elem = CP_NULL;



	if (sdl_av_dev->audio_info && size > 0) {
		//创建缺少的缓存
		for (i = 0; i < size; i++) {
			tmp_data_elem = create_sdl_av_dev_data_element_and_buufer(sdl_av_dev->pool,
				sdl_av_dev->audio_info->ad.samples_buffer_size);
			if (!tmp_data_elem) {
				continue;
			}

			//设置索引
			tmp_data_elem->data.index = i + sdl_av_dev->audio_info->max_buffer_size;

			//清空数据
			cp_clear_sdl_av_dev_data(&tmp_data_elem->data);

			//初始化队列节点数据
			cp_lockfree_queue_element_init(&sdl_av_dev->audio_info->free_queue,
				&tmp_data_elem->lfq_elem,
				&tmp_data_elem->data.index,
				tmp_data_elem);

			//插入空闲队列
			cp_lockfree_queue_push(&sdl_av_dev->audio_info->free_queue,
				&tmp_data_elem->lfq_elem,
				tmp_data_elem->data.index,
				CP_NULL);
		}
	}
	return 0;
}

/*创建音频信息*/
cp_int32_t create_sdl_audio_info(cp_sdl_av_dev_t *sdl_av_dev, const cp_sdl_av_dev_info_t *sdl_av_dev_info)
{
	cp_sdl_av_dev_audio_info_t						*tmp_audio_info = CP_NULL;



	if (cp_media_description_type_audio != sdl_av_dev_info->md->type) {
		cp_module_log(error, sdl_av_dev,
			"create_sdl_audio_info() error. unsupport media description type[%d]",
			sdl_av_dev_info->md->type);
		return -1;
	}

	//创建
	tmp_audio_info = cp_palloc(sdl_av_dev->pool, cp_sizeof(cp_sdl_av_dev_audio_info_t));
	if (!tmp_audio_info) {
		cp_module_log(error, sdl_av_dev,
			"create_sdl_audio_info() error. create audio information error.");
		return -2;
	}

	//设置音频信息
	cp_memset(tmp_audio_info, 0, cp_sizeof(cp_sdl_av_dev_audio_info_t));
	if (sdl_av_dev_info && sdl_av_dev_info->dd) {
		tmp_audio_info->dad = *((cp_dev_audio_description_t*)sdl_av_dev_info->dd);
	}

	//设置媒体信息
	if (sdl_av_dev_info && sdl_av_dev_info->md) {
		tmp_audio_info->ad = *((cp_audio_description_t*)sdl_av_dev_info->md);
	}

	sdl_av_dev->audio_info = tmp_audio_info;

	return 0;
}

/*消毁音频信息*/
cp_int32_t destroy_sdl_audio_info(cp_sdl_av_dev_t *sdl_av_dev, const cp_sdl_av_dev_info_t *sdl_av_dev_info)
{
	if (sdl_av_dev->audio_info) {
		cp_pfree(sdl_av_dev->pool, sdl_av_dev->audio_info);
		sdl_av_dev->audio_info = CP_NULL;
	}
	return 0;
}

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: set_audio_spec
*
* 函数说明: 设置音频信息
*
* 参    数: cp_sdl_av_dev_t * sdl_av_dev						[in]参数说明
* 参    数: cp_sdl_av_dev_audio_info_t * audio_info						[in]参数说明
*
* 返 回 值: cp_int32_t
*           0  : 成功
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2016-12-21 09:12:15
******************************************************************************************************/
cp_int32_t set_audio_spec(cp_sdl_av_dev_t *sdl_av_dev, cp_sdl_av_dev_audio_info_t *audio_info)
{
	cp_sdl_av_dev_audio_format_t					*tmp_af = CP_NULL;



	if (!sdl_av_dev || !audio_info) {
		return -1;
	}

	tmp_af = get_sdl_audio_format_info(audio_info->dad.sample_format);
	if (!tmp_af) {
		cp_module_log(error, sdl_av_dev,
			"not found sdl_audio_format. css_audio_type[%d]",
			audio_info->dad.sample_format);
		return -2;
	}
	audio_info->wanted_spec.freq = audio_info->ad.sample_rate;
	audio_info->wanted_spec.format = tmp_af->sdl_audio_format_type;
	audio_info->wanted_spec.channels = (Uint8)(audio_info->ad.channels);
	audio_info->wanted_spec.silence = audio_info->ad.silence;
	audio_info->wanted_spec.samples = audio_info->ad.samples;
	audio_info->wanted_spec.callback = sdl_av_dev_audio_callback;
	audio_info->wanted_spec.size = audio_info->ad.samples_buffer_size;
	audio_info->wanted_spec.userdata = sdl_av_dev;

	return 0;
}

/*保存音频设备信息*/
cp_int32_t save_audio_device_info(cp_sdl_av_dev_t *sdl_av_dev)
{
	cp_int32_t					i = 0;



	for (i = 0; i < SDL_GetNumAudioDrivers(); ++i) {
		cp_module_log(notice, sdl_av_dev, "audio device[ %d: %s ]",
			i,
			SDL_GetAudioDriver(i));
	}
	return 0;
}

