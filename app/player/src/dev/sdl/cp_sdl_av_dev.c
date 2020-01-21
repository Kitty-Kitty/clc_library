/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/
#include "cp_include.h"
#include "cp_sdl_av_dev.h"
#include "cp_sdl_av_dev_audio.h"
#include "cp_sdl_av_dev_video.h"



/*ģ�鴴���ӿڣ���ʾ����һ��ģ��*/
cp_int32_t init_sdl_av_dev(cp_sdl_av_dev_t *sdl_av_dev, const cp_sdl_av_dev_info_t *sdl_av_dev_info);
/*ģ������нӿڣ���ģ��init֮�󣬻ᱻ����*/
cp_int32_t open_sdl_av_dev(cp_sdl_av_dev_t *sdl_av_dev, const cp_sdl_av_dev_info_t *sdl_av_dev_info);
/*��ȡģ�����ݣ�flagΪ��ȡģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��*/
cp_int32_t read_sdl_av_dev(cp_sdl_av_dev_t *sdl_av_dev, cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag);
/*дģ�����ݣ�flagΪдģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��*/
cp_int32_t write_sdl_av_dev(cp_sdl_av_dev_t *sdl_av_dev, const cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag);
/*�ر�ģ��*/
cp_int32_t close_sdl_av_dev(cp_sdl_av_dev_t *sdl_av_dev);
/*�˳�ģ��*/
cp_int32_t exit_sdl_av_dev(cp_sdl_av_dev_t *sdl_av_dev);
/*����ģ�����*/
cp_int32_t set_option_sdl_av_dev(cp_sdl_av_dev_t *sdl_av_dev, cp_int32_t optname, const cp_void_t* optval);
/*��ȡģ�����*/
cp_int32_t get_option_sdl_av_dev(cp_sdl_av_dev_t *sdl_av_dev, cp_int32_t optname, cp_void_t* optval);

/*���Բ���bmp�ļ�*/
cp_inline cp_static cp_int32_t sdl_av_dev_print_bmp(cp_sdl_av_dev_t *sdl_av_dev);

/*����һ��ģ��*/
cp_sdl_av_dev_t* create_sdl_av_dev(cp_module_register_t *register_info, cp_codec_manager_t *manager, cp_sdl_av_dev_info_t *info)
{
	cp_int32_t							ret_int = 0;
	cp_sdl_av_dev_t						*tmp_module = CP_NULL;
	cp_pool_info_t						tmp_pool_info = { 0, };


	if (!register_info || !manager || !info) {
		return CP_NULL;
	}

	tmp_module = cp_malloc_module(manager, cp_sdl_av_dev_t, &tmp_pool_info);
	if (!tmp_module) {
		return CP_NULL;
	}
	CP_MODULE_SET_HANDLERS(tmp_module, sdl_av_dev);
	return tmp_module;
}

/*�ͷ�ģ��*/
cp_int32_t destroy_sdl_av_dev(cp_codec_manager_t *manager, cp_sdl_av_dev_t* sdl_av_dev)
{
	if (!manager || !sdl_av_dev) {
		return -1;
	}
	cp_free_module(sdl_av_dev);
	return 0;
}

/*ģ�鴴���ӿڣ���ʾ����һ��ģ��*/
cp_int32_t init_sdl_av_dev(cp_sdl_av_dev_t *sdl_av_dev,
	const cp_sdl_av_dev_info_t *sdl_av_dev_info)
{
	cp_dev_description_t				*tmp_dd = CP_NULL;


	//��ʼ��sdl��
// 	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER)) {
// 		cp_module_log(error, sdl_av_dev, "could not initialize sdl. %s",
// 			SDL_GetError());
// 		return -1;
// 	}

	//��ʼ��sdl��
// 	if (SDL_Init(SDL_INIT_TIMER)) {
// 		cp_module_log(error, sdl_av_dev, "could not initialize sdl. %s",
// 			SDL_GetError());
// 		return -1;
// 	}
// 	else {
// 		cp_module_log(notice, sdl_av_dev, "initialize sdl[%s] timer successed.",
// 			SDL_GetRevision());
// 	}

	return 0;
}

/*ģ������нӿڣ���ģ��init֮�󣬻ᱻ����*/
cp_int32_t open_sdl_av_dev(cp_sdl_av_dev_t *sdl_av_dev,
	const cp_sdl_av_dev_info_t *sdl_av_dev_info)
{
	if (!sdl_av_dev) {
		return -1;
	}

	if (!sdl_av_dev_info || !sdl_av_dev_info->md) {
		cp_module_log(error, sdl_av_dev,
			"open_sdl_av_dev() error. dev info is null, or media description is null");
		return -1;
	}

	switch (sdl_av_dev_info->md->type)
	{
	case cp_media_description_type_video:
	{
		return open_sdl_video_dev(sdl_av_dev, sdl_av_dev_info);
	}
	break;
	case cp_media_description_type_audio:
	{
		return open_sdl_audio_dev(sdl_av_dev, sdl_av_dev_info);
	}
	break;
	default:
	{
		cp_module_log(error, sdl_av_dev, 
			"open sdl av dev error. unsupport media type[%d]", sdl_av_dev_info->md->type);
		return -1;
	}
	break;
	}

	return -1;
}

/*��ȡģ�����ݣ�flagΪ��ȡģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��*/
cp_int32_t read_sdl_av_dev(cp_sdl_av_dev_t *sdl_av_dev,
	cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag)
{
	return 0;
}
/*дģ�����ݣ�flagΪдģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��*/
cp_int32_t write_sdl_av_dev(cp_sdl_av_dev_t *sdl_av_dev,
	const cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag)
{
	int								ret_int = 0;
	cp_media_packet_t				*tmp_mp = CP_NULL;



	if (!buf || !*buf || !len) {
		return -1;
	}

	//ת��ý�����ݣ���У�����ݺϷ���
	tmp_mp = *((cp_media_packet_t**)buf);
	if (cp_media_packet_type_data_and_timestamp != tmp_mp->type) {
		return -2;
	}

	switch (tmp_mp->md_p->type) {
	case cp_media_description_type_video:
	{
		return write_sdl_video_data(sdl_av_dev, tmp_mp);
	}
	break;
	case cp_media_description_type_audio:
	{
		return write_sdl_audio_data(sdl_av_dev, tmp_mp);
	}
	break;
	default:
	{
		return -1;
	}
	break;
	}

	return 0;
}
/*�ر�ģ��*/
cp_int32_t close_sdl_av_dev(cp_sdl_av_dev_t *sdl_av_dev)
{
	if (sdl_av_dev->audio_info) {
		close_sdl_audio_dev(sdl_av_dev);
	}

	if (sdl_av_dev->video_info) {
		close_sdl_video_dev(sdl_av_dev);
	}
	return 0;
}
/*�˳�ģ��*/
cp_int32_t exit_sdl_av_dev(cp_sdl_av_dev_t *sdl_av_dev)
{
	SDL_Quit();
	return 0;
}
/*����ģ�����*/
cp_int32_t set_option_sdl_av_dev(cp_sdl_av_dev_t *sdl_av_dev, cp_int32_t optname, const cp_void_t* optval)
{
	cp_int32_t					tmp_buffer_size = 0;
	cp_int64_t					tmp_play_delay = 0;



	if (!sdl_av_dev || !optval) {
		return -1;
	}

	if (cp_player_dev_set_option_audio_buffer_size == optname ||
		cp_player_dev_set_option_video_buffer_size == optname) {
		tmp_buffer_size = *((cp_int32_t*)optval);
		if (tmp_buffer_size <= 0) {
			cp_module_log(error, sdl_av_dev,
				"set_option_sdl_av_dev() set audio buffer size[%d] error. ",
				tmp_buffer_size);
			return -2;
		}
		return update_sdl_audio_buffer_queue(sdl_av_dev, tmp_buffer_size);
	}

	if (cp_player_dev_set_option_audio_delay == optname) {
		if (*((cp_int64_t*)optval) <= 0) {
			return -3;
		}
		sdl_av_dev->audio_info->play_delay_ns = *((cp_int64_t*)optval);
		sdl_av_dev->audio_info->play_delay_times = 0;
		sdl_av_dev->audio_info->play_delay_max_times = 1;

		cp_module_log(notice, sdl_av_dev,
			"set_option_sdl_av_dev() set audio play delay [%lld ns] successed. ",
			sdl_av_dev->audio_info->play_delay_ns);
	}

	if (cp_player_dev_set_option_audio_delay_sample_number == optname) {
		if (*((cp_int32_t*)optval) <= 0) {
			return -3;
		}
		sdl_av_dev->audio_info->play_delay_sample_number = *((cp_int32_t*)optval);

		cp_module_log(notice, sdl_av_dev,
			"set_option_sdl_av_dev() set audio play delay sample number[%d] successed. ",
			sdl_av_dev->audio_info->play_delay_sample_number);
	}
	
	return 0;
}

cp_int32_t get_option_sdl_av_dev(cp_sdl_av_dev_t *sdl_av_dev, cp_int32_t optname, cp_void_t* optval)
{
	return 0;
}

/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: sdl_av_dev_print_bmp
*
* ����˵��: ���Բ���bmp�ļ�
*
* ��    ��: cp_sdl_av_dev_t * sdl_av_dev						[in]����˵��
*
* �� �� ֵ: cp_int32_t
*           0  : �ɹ� 
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2016-12-09 09:56:48
******************************************************************************************************/
cp_int32_t	sdl_av_dev_print_bmp(cp_sdl_av_dev_t *sdl_av_dev) 
{
	SDL_Surface *bmp = SDL_LoadBMP("test.bmp");
	if (!bmp)
	{
		return 1;
	}

	SDL_Texture *tex = SDL_CreateTextureFromSurface(sdl_av_dev->video_info->renderer, bmp);
	SDL_FreeSurface(bmp);
	if (!tex)
	{
		return 1;
	}

	SDL_RenderSetViewport(sdl_av_dev->video_info->renderer, NULL);
	SDL_RenderClear(sdl_av_dev->video_info->renderer);
	SDL_RenderCopy(sdl_av_dev->video_info->renderer, tex, NULL, &sdl_av_dev->video_info->window_rect);
	SDL_RenderPresent(sdl_av_dev->video_info->renderer);
	SDL_DestroyTexture(tex);

	return 0;
}

