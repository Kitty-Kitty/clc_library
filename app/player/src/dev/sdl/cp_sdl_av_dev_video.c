/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2017-01-04

Description:

**************************************************************************/
#include "cp_sdl_av_dev_video.h"
#include "cp_log.h"



/*打开视频设置*/
cp_int32_t open_sdl_video_dev(cp_sdl_av_dev_t *sdl_av_dev, const cp_sdl_av_dev_info_t *sdl_av_dev_info)
{
	cp_int32_t								tmp_ret_int = 0;
	cp_video_description_t					*tmp_vd = CP_NULL;



	//打印video device信息
	save_video_device_info(sdl_av_dev);

	if (!SDL_WasInit(SDL_INIT_VIDEO)) {
		if (SDL_Init(SDL_INIT_VIDEO)) {
			cp_module_log(error, sdl_av_dev, "could not initialize sdl. %s",
				SDL_GetError());
			return -1;
		}
		else {
			cp_module_log(notice, sdl_av_dev, "initialize sdl[%s] video successed.",
				SDL_GetRevision());
		}
	}

	tmp_vd = (cp_video_description_t*)sdl_av_dev_info->md;

	//创建视频信息
	tmp_ret_int = create_sdl_video_info(sdl_av_dev, sdl_av_dev_info);
	if (tmp_ret_int) {
		cp_module_log(error, sdl_av_dev, "create_sdl_video_info() error.");
		return -2;
	}

	//设置各种
	set_rect_info(sdl_av_dev, sdl_av_dev_info);

	//创建窗口
	sdl_av_dev->video_info->window = SDL_CreateWindow("video",
		sdl_av_dev->video_info->window_rect.x, sdl_av_dev->video_info->window_rect.y, sdl_av_dev->video_info->window_rect.w, sdl_av_dev->video_info->window_rect.h, SDL_WINDOW_SHOWN);
	if (!sdl_av_dev->video_info->window) {
		cp_module_log(error, sdl_av_dev,
			"could not create window. reason:%s", SDL_GetError());
		return -2;
	}

	//创建渲染器
	sdl_av_dev->video_info->renderer = SDL_CreateRenderer(sdl_av_dev->video_info->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!sdl_av_dev->video_info->renderer) {
		cp_module_log(error, sdl_av_dev,
			"could not create renderer. reason:%s", SDL_GetError());
		return -3;
	}

	//创建纹理
	sdl_av_dev->video_info->texture = SDL_CreateTexture(sdl_av_dev->video_info->renderer,
		SDL_PIXELFORMAT_IYUV,
		SDL_TEXTUREACCESS_STREAMING,
		sdl_av_dev->video_info->vedio_rect.w,
		sdl_av_dev->video_info->vedio_rect.h);
	if (!sdl_av_dev->video_info->texture) {
		cp_module_log(error, sdl_av_dev,
			"could not create texture. reason:%s", SDL_GetError());
		return -3;
	}

	return 0;
}

/*写视频数据*/
cp_int32_t write_sdl_video_data(cp_sdl_av_dev_t *sdl_av_dev, cp_media_packet_t *mp)
{

	if (!sdl_av_dev || !mp || !mp->md_p) {
		return -1;
	}

	if (cp_codec_pixel_format_yuv420p != mp->md_p->pix_fmt) {
		return -2;
	}

	SDL_UpdateYUVTexture(sdl_av_dev->video_info->texture, &sdl_av_dev->video_info->vedio_rect,
		cp_buf_get_pos(&mp->mp_buf.buf[0]), cp_buf_get_length(&mp->mp_buf.buf[0]),
		cp_buf_get_pos(&mp->mp_buf.buf[1]), cp_buf_get_length(&mp->mp_buf.buf[1]),
		cp_buf_get_pos(&mp->mp_buf.buf[2]), cp_buf_get_length(&mp->mp_buf.buf[2]));
	SDL_RenderSetViewport(sdl_av_dev->video_info->renderer, NULL);
	SDL_RenderClear(sdl_av_dev->video_info->renderer);
	SDL_RenderCopy(sdl_av_dev->video_info->renderer, sdl_av_dev->video_info->texture, NULL, &sdl_av_dev->video_info->window_rect);
	SDL_RenderPresent(sdl_av_dev->video_info->renderer);

	//sdl_av_dev_print_bmp(sdl_av_dev);
	return 0;
}

/*关闭视频设备*/
cp_int32_t close_sdl_video_dev(cp_sdl_av_dev_t *sdl_av_dev)
{
	return 0;
}

cp_int32_t set_rect_info(cp_sdl_av_dev_t *sdl_av_dev, const cp_sdl_av_dev_info_t *sdl_av_dev_info)
{
	cp_video_description_t					*tmp_vd = (cp_video_description_t*)sdl_av_dev_info->md;



	sdl_av_dev->video_info->window_rect.x = 0;
	sdl_av_dev->video_info->window_rect.y = 0;
	//  sdl_av_dev->video_info->window_rect.w = tmp_vd->width;
	//  sdl_av_dev->video_info->window_rect.h = tmp_vd->height;
	// 	sdl_av_dev->video_info->window_rect.x = 1000;
	// 	sdl_av_dev->video_info->window_rect.y = 600;
	if (!tmp_vd) {
		return -1;
	}

	if (sdl_av_dev_info && sdl_av_dev_info->dd) {
		sdl_av_dev->video_info->window_rect.w = ((cp_dev_video_description_t *)sdl_av_dev_info->dd)->width;
		sdl_av_dev->video_info->window_rect.h = ((cp_dev_video_description_t *)sdl_av_dev_info->dd)->height;
	}

	if (!sdl_av_dev->video_info->window_rect.w) {
		sdl_av_dev->video_info->window_rect.w = CP_SDL_AV_DEV_DEFAULT_WIDTH;
	}

	if (!sdl_av_dev->video_info->window_rect.h) {
		sdl_av_dev->video_info->window_rect.h = CP_SDL_AV_DEV_DEFAULT_HEIGHT;
	}

	sdl_av_dev->video_info->vedio_rect.x = 0;
	sdl_av_dev->video_info->vedio_rect.y = 0;
	sdl_av_dev->video_info->vedio_rect.w = tmp_vd->width;
	sdl_av_dev->video_info->vedio_rect.h = tmp_vd->height;

	return 0;
}

/*创建视频信息*/
cp_int32_t create_sdl_video_info(cp_sdl_av_dev_t *sdl_av_dev, const cp_sdl_av_dev_info_t *sdl_av_dev_info)
{
	cp_sdl_av_dev_video_info_t						*tmp_video_info = CP_NULL;



	if (cp_media_description_type_video != sdl_av_dev_info->md->type) {
		cp_module_log(error, sdl_av_dev,
			"create_sdl_video_info() error. unsupport media description type[%d]",
			sdl_av_dev_info->md->type);
		return -1;
	}

	//创建
	tmp_video_info = cp_palloc(sdl_av_dev->pool, cp_sizeof(cp_sdl_av_dev_video_info_t));
	if (!tmp_video_info) {
		cp_module_log(error, sdl_av_dev,
			"create_sdl_video_info() error. create audio information error.");
		return -2;
	}

	//设置音频信息
	cp_memset(tmp_video_info, 0, cp_sizeof(cp_sdl_av_dev_video_info_t));
	if (sdl_av_dev_info && sdl_av_dev_info->dd) {
		tmp_video_info->dvd = *((cp_dev_video_description_t*)sdl_av_dev_info->dd);
	}

	if (sdl_av_dev_info && sdl_av_dev_info->md) {
		tmp_video_info->vd = *((cp_video_description_t*)sdl_av_dev_info->md);
	}

	sdl_av_dev->video_info = tmp_video_info;

	return 0;
}

/*消毁视频信息*/
cp_int32_t destroy_sdl_video_info(cp_sdl_av_dev_t *sdl_av_dev, const cp_sdl_av_dev_info_t *sdl_av_dev_info)
{
	if (sdl_av_dev->video_info) {
		cp_pfree(sdl_av_dev->pool, sdl_av_dev->video_info);
		sdl_av_dev->video_info = CP_NULL;
	}
	return 0;
}

/*保存视频设备信息*/
cp_int32_t save_video_device_info(cp_sdl_av_dev_t *sdl_av_dev)
{
	cp_int32_t					i = 0;



	for (i = 0; i < SDL_GetNumVideoDrivers(); ++i) {
		cp_module_log(notice, sdl_av_dev, "video device[ %d: %s ]",
			i,
			SDL_GetVideoDriver(i));
	}
	return 0;
}