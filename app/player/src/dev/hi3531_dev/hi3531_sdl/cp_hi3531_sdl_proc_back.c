/*******************************************************************************
*
*Copyright:novigo
*
*File name: cp_hi3531_sdl_proc.c
*
*Author:fangzhenmu@novigo.com.cn
*
*Version: 1.0
*
*Date:2017/07/28
*
*Description: create (cp_hi3531_sdl_proc.c)
*
*Others:
*
*History:
*******************************************************************************/

#include "cp_hi3531_sdl_core.h"
#include "cp_hi3531_dev_info.h"
#include "cp_hi3531_tde_core.h"




/*******************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: create_hi3531_vo_dev_list
*
* 函数全名: create_hi3531_vo_dev_list
*
* 函数访问: public
*
* 函数说明: 初始化hi3531 vo 设备列表
*
* 参    数: cp_hi3531_sdl_t * dev						[in/out]参数说明
* 参    数: cp_hi3531_dev_configure_t *conf						[in/out]参数说明
*
* 返 回 值: cp_int32_t
*           0  : 成功
*         非0  : 失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2017-7-28 10:22:20
********************************************************************************/
cp_int32_t	create_hi3531_vo_dev_list(cp_hi3531_sdl_t *dev, cp_hi3531_dev_configure_t *conf)
{
	cp_int32_t								tmp_ret_int = 0;
	cp_int32_t								i = 0;
	cp_hi3531_dev_info_t					tmp_info = { 0, };
	cp_module_register_t					*tmp_module_register = CP_NULL;
	cp_dev_t								*tmp_vo = CP_NULL;
	cp_char_t								tmp_buf[CP_APP_DEFAULT_BUFFER_LENGTH] = { 0, };



	for (i = 0; i < cp_ary_size(conf->vo_conf); i++) {
		if (!conf->vo_conf[i].is_used) {
			//如果不使用，则返回
			continue;
		}

		//配置模块信息
		cp_memset(&tmp_info, 0, cp_sizeof(tmp_info));
		CP_MODULE_INFO_SET_DATA(&tmp_info, &(conf->vo_conf[i]));

		//获取模块注册信息
		tmp_module_register = cp_manager_get_module_register(dev->manager, cp_player_module_type_hi3531_dev_vo);
		if (!tmp_module_register) {
			cp_hi3531_dev_log(warn, dev,
				"create hi3531_vo failed! not found dev_vo[type:%d] register.",
				cp_player_module_type_hi3531_dev_vo);
			continue;
		}

		//根据模块注册信息更新模块信息
		CP_MODULE_INFO_SET_FROM_REGISTER(&tmp_info, tmp_module_register);
		tmp_vo = (cp_dev_t*)cp_create_module(tmp_module_register, dev->manager, &tmp_info);
		if (!tmp_vo) {
			cp_hi3531_dev_log(warn, dev,
				"create hi3531_vo[%s] failed! ",
				print_module_register_info(tmp_module_register, tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH));
			continue;
		}
		else {
			cp_hi3531_dev_log(notice, dev,
				"create hi3531_vo[%s] successed! ",
				print_module_register_info(tmp_module_register, tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH));
		}

		//初始化模块
		tmp_ret_int = cp_init_module(tmp_vo, &tmp_info);
		if (tmp_ret_int) {
			cp_hi3531_dev_log(warn, dev,
				"init hi3531_vo[module:%p register:%s] failed! ",
				tmp_vo,
				print_module_register_info(tmp_module_register, tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH));
			continue;
		}
		else {
			cp_hi3531_dev_log(notice, dev,
				"init hi3531_vo[module:%p register:%s] successed! ",
				tmp_vo,
				print_module_register_info(tmp_module_register, tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH));
		}

		dev->m_hi3531_vo[i] = tmp_vo;
	}

	return 0;
}

/*******************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: start_hi3531_vo_dev_list
*
* 函数全名: start_hi3531_vo_dev_list
*
* 函数访问: public
*
* 函数说明: 启动hi3531 vo 设备列表
*
* 参    数: cp_hi3531_sdl_t * dev						[in/out]参数说明
* 参    数: cp_hi3531_dev_configure_t *conf						[in/out]参数说明
*
* 返 回 值: cp_int32_t
*           0  : 成功
*         非0  : 失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2017-7-28 10:22:31
********************************************************************************/
cp_int32_t	start_hi3531_vo_dev_list(cp_hi3531_sdl_t *dev, cp_hi3531_dev_configure_t *conf)
{
	cp_int32_t								tmp_ret_int = 0;
	cp_int32_t								i = 0;
	cp_hi3531_dev_info_t					tmp_info = { 0, };
	cp_char_t								tmp_buf[CP_APP_DEFAULT_BUFFER_LENGTH] = { 0, };



	for (i = 0; i < cp_ary_size(dev->m_hi3531_vo); i++) {
		if (!dev->m_hi3531_vo[i]) {
			//如果不使用，则返回
			continue;
		}

		//配置模块信息
		cp_memset(&tmp_info, 0, cp_sizeof(tmp_info));
		CP_MODULE_INFO_SET_DATA(&tmp_info, &(conf->vo_conf[i]));

		//启动模块
		tmp_ret_int = cp_open_module(dev->m_hi3531_vo[i], &tmp_info);
		if (tmp_ret_int) {
			cp_hi3531_dev_log(warn, dev,
				"open hi3531_vo[module:%p register:%s] failed! ",
				dev->m_hi3531_vo[i],
				print_module_register_info(&(dev->m_hi3531_vo[i]->register_info), tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH));
			continue;
		}
		else {
			cp_hi3531_dev_log(notice, dev,
				"open hi3531_vo[module:%p register:%s] successed! ",
				dev->m_hi3531_vo[i],
				print_module_register_info(&(dev->m_hi3531_vo[i]->register_info), tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH));
		}
	}

	return 0;
}

/*******************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: stop_hi3531_vo_dev_list
*
* 函数全名: stop_hi3531_vo_dev_list
*
* 函数访问: public
*
* 函数说明: 停止hi3531 vo 设备列表
*
* 参    数: cp_hi3531_sdl_t * dev						[in/out]参数说明
* 参    数: cp_hi3531_dev_configure_t *conf						[in/out]参数说明
*
* 返 回 值: cp_int32_t
*           0  : 成功
*         非0  : 失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2017-7-28 10:22:39
********************************************************************************/
cp_int32_t	stop_hi3531_vo_dev_list(cp_hi3531_sdl_t *dev, cp_hi3531_dev_configure_t *conf)
{
	cp_int32_t								tmp_ret_int = 0;
	cp_int32_t								i = 0;
	cp_char_t								tmp_buf[CP_APP_DEFAULT_BUFFER_LENGTH] = { 0, };



	for (i = 0; i < cp_ary_size(dev->m_hi3531_vo); i++) {
		if (!dev->m_hi3531_vo[i]) {
			//如果不使用，则返回
			continue;
		}

		//启动模块
		tmp_ret_int = cp_close_module(dev->m_hi3531_vo[i]);
		if (tmp_ret_int) {
			cp_hi3531_dev_log(warn, dev,
				"close hi3531_vo[module:%p register:%s] failed! ",
				dev->m_hi3531_vo[i],
				print_module_register_info(&(dev->m_hi3531_vo[i]->register_info), tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH));
			continue;
		}
		else {
			cp_hi3531_dev_log(notice, dev,
				"close hi3531_vo[module:%p register:%s] successed! ",
				dev->m_hi3531_vo[i],
				print_module_register_info(&(dev->m_hi3531_vo[i]->register_info), tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH));
		}
	}

	return 0;
}

/*******************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: destory_hi3531_vo_dev_list
*
* 函数全名: destory_hi3531_vo_dev_list
*
* 函数访问: public
*
* 函数说明: 销毁hi3531 vo 设备列表
*
* 参    数: cp_hi3531_sdl_t * dev						[in/out]参数说明
* 参    数: cp_hi3531_dev_configure_t * conf						[in/out]参数说明
*
* 返 回 值: cp_int32_t
*           0  : 成功
*         非0  : 失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2017-7-28 14:07:27
********************************************************************************/
cp_int32_t	destory_hi3531_vo_dev_list(cp_hi3531_sdl_t *dev, cp_hi3531_dev_configure_t *conf)
{
	cp_int32_t								tmp_ret_int = 0;
	cp_int32_t								i = 0;



	for (i = 0; i < cp_ary_size(dev->m_hi3531_vo); i++) {
		if (!dev->m_hi3531_vo[i]) {
			//如果不使用，则返回
			continue;
		}

		//销毁模块
		tmp_ret_int = cp_destroy_module(dev->manager, dev->m_hi3531_vo[i]);
		if (tmp_ret_int) {
			cp_hi3531_dev_log(warn, dev,
				"destroy hi3531_vo[module:%p] failed! ",
				dev->m_hi3531_vo[i]);
			continue;
		}
		else {
			cp_hi3531_dev_log(notice, dev,
				"destroy hi3531_vo[module:%p] successed! ",
				dev->m_hi3531_vo[i]);
		}
	}

	return 0;
}


/*******************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: create_hi3531_tde_dev
*
* 函数全名: create_hi3531_tde_dev
*
* 函数访问: public
*
* 函数说明: 初始化hi3531 tde 设备列表
*
* 参    数: cp_hi3531_sdl_t * dev						[in/out]参数说明
* 参    数: cp_hi3531_dev_configure_t * conf						[in/out]参数说明
*
* 返 回 值: cp_int32_t
*           0  : 成功
*         非0  : 失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2017-7-28 14:20:09
********************************************************************************/
cp_int32_t	create_hi3531_tde_dev(cp_hi3531_sdl_t *dev, cp_hi3531_dev_configure_t *conf)
{
	cp_int32_t								tmp_ret_int = 0;
	cp_int32_t								i = 0;
	cp_hi3531_dev_info_t					tmp_info = { 0, };
	cp_module_register_t					*tmp_module_register = CP_NULL;
	cp_dev_t								*tmp_tde = CP_NULL;
	cp_char_t								tmp_buf[CP_APP_DEFAULT_BUFFER_LENGTH] = { 0, };



	//获取模块注册信息
	tmp_module_register = cp_manager_get_module_register(dev->manager, cp_player_module_type_hi3531_dev_tde);
	if (!tmp_module_register) {
		cp_hi3531_dev_log(warn, dev,
			"create hi3531_tde failed! not found dev_tde[type:%d] register.",
			cp_player_module_type_hi3531_dev_tde);
		return -1;
	}

	//根据模块注册信息更新模块信息
	CP_MODULE_INFO_SET_FROM_REGISTER(&tmp_info, tmp_module_register);
	tmp_tde = (cp_dev_t*)cp_create_module(tmp_module_register, dev->manager, &tmp_info);
	if (!tmp_tde) {
		cp_hi3531_dev_log(warn, dev,
			"create hi3531_tde[%s] failed! ",
			print_module_register_info(tmp_module_register, tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH));
		return -2;
	}
	else {
		cp_hi3531_dev_log(notice, dev,
			"create hi3531_tde[%s] successed! ",
			print_module_register_info(tmp_module_register, tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH));
	}

	//初始化模块
	tmp_ret_int = cp_init_module(tmp_tde, &tmp_info);
	if (tmp_ret_int) {
		cp_hi3531_dev_log(warn, dev,
			"init hi3531_tde[module:%p register:%s] failed! ",
			tmp_tde,
			print_module_register_info(tmp_module_register, tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH));
		return -3;
	}
	else {
		cp_hi3531_dev_log(notice, dev,
			"init hi3531_tde[module:%p register:%s] successed! ",
			tmp_tde,
			print_module_register_info(tmp_module_register, tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH));
	}

	dev->m_hi3531_tde = tmp_tde;

	return 0;
}

/*******************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: start_hi3531_tde_dev
*
* 函数全名: start_hi3531_tde_dev
*
* 函数访问: public
*
* 函数说明: 启动hi3531 tde 设备列表
*
* 参    数: cp_hi3531_sdl_t * dev						[in/out]参数说明
* 参    数: cp_hi3531_dev_configure_t * conf						[in/out]参数说明
*
* 返 回 值: cp_int32_t
*           0  : 成功
*         非0  : 失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2017-7-28 14:20:20
********************************************************************************/
cp_int32_t	start_hi3531_tde_dev(cp_hi3531_sdl_t *dev, cp_hi3531_dev_configure_t *conf)
{
	cp_int32_t								tmp_ret_int = 0;
	cp_int32_t								i = 0;
	cp_hi3531_dev_info_t					tmp_info = { 0, };
	cp_char_t								tmp_buf[CP_APP_DEFAULT_BUFFER_LENGTH] = { 0, };



	if (!dev->m_hi3531_tde) {
		//如果不使用，则返回
		return -1;
	}

	//启动模块
	tmp_ret_int = cp_open_module(dev->m_hi3531_tde, &tmp_info);
	if (tmp_ret_int) {
		cp_hi3531_dev_log(warn, dev,
			"open hi3531_tde[module:%p register:%s] failed! ",
			dev->m_hi3531_tde,
			print_module_register_info(&(dev->m_hi3531_tde->register_info), tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH));
		return -2;
	}
	else {
		cp_hi3531_dev_log(notice, dev,
			"open hi3531_tde[module:%p register:%s] successed! ",
			dev->m_hi3531_tde,
			print_module_register_info(&(dev->m_hi3531_tde->register_info), tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH));
	}

	return 0;
}

/*******************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: stop_hi3531_tde_dev
*
* 函数全名: stop_hi3531_tde_dev
*
* 函数访问: public
*
* 函数说明: 停止hi3531 tde 设备列表
*
* 参    数: cp_hi3531_sdl_t * dev						[in/out]参数说明
* 参    数: cp_hi3531_dev_configure_t * conf						[in/out]参数说明
*
* 返 回 值: cp_int32_t
*           0  : 成功
*         非0  : 失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2017-7-28 14:20:30
********************************************************************************/
cp_int32_t	stop_hi3531_tde_dev(cp_hi3531_sdl_t *dev, cp_hi3531_dev_configure_t *conf)
{
	cp_int32_t								tmp_ret_int = 0;
	cp_int32_t								i = 0;
	cp_char_t								tmp_buf[CP_APP_DEFAULT_BUFFER_LENGTH] = { 0, };



	if (!dev->m_hi3531_tde) {
		//如果不使用，则返回
		return -1;
	}

	//启动模块
	tmp_ret_int = cp_close_module(dev->m_hi3531_tde);
	if (tmp_ret_int) {
		cp_hi3531_dev_log(warn, dev,
			"close hi3531_tde[module:%p register:%s] failed! ",
			dev->m_hi3531_tde,
			print_module_register_info(&(dev->m_hi3531_tde->register_info), tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH));
		return -2;
	}
	else {
		cp_hi3531_dev_log(notice, dev,
			"close hi3531_tde[module:%p register:%s] successed! ",
			dev->m_hi3531_tde,
			print_module_register_info(&(dev->m_hi3531_tde->register_info), tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH));
	}

	return 0;
}

/*******************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: destory_hi3531_tde_dev
*
* 函数全名: destory_hi3531_tde_dev
*
* 函数访问: public
*
* 函数说明: 销毁hi3531 tde 设备列表
*
* 参    数: cp_hi3531_sdl_t * dev						[in/out]参数说明
* 参    数: cp_hi3531_dev_configure_t * conf						[in/out]参数说明
*
* 返 回 值: cp_int32_t
*           0  : 成功
*         非0  : 失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2017-7-28 14:20:39
********************************************************************************/
cp_int32_t	destory_hi3531_tde_dev(cp_hi3531_sdl_t *dev, cp_hi3531_dev_configure_t *conf)
{
	cp_int32_t								tmp_ret_int = 0;
	cp_int32_t								i = 0;



	if (!dev->m_hi3531_tde) {
		//如果不使用，则返回
		return -1;
	}

	//销毁模块
	tmp_ret_int = cp_destroy_module(dev->manager, dev->m_hi3531_tde);
	if (tmp_ret_int) {
		cp_hi3531_dev_log(warn, dev,
			"destroy hi3531_tde[module:%p] failed! ",
			dev->m_hi3531_tde);
		return -2;
	}
	else {
		cp_hi3531_dev_log(notice, dev,
			"destroy hi3531_tde[module:%p] successed! ",
			dev->m_hi3531_tde);
	}

	return 0;
}

/*******************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: write_hi3531_frame_data
*
* 函数全名: write_hi3531_frame_data
*
* 函数访问: public
*
* 函数说明: 写hi3531数据
*
* 参    数: cp_hi3531_sdl_t * hi3531_sdl						[in/out]参数说明
* 参    数: const cp_uchar_t * * buf						[in/out]参数说明
* 参    数: cp_int32_t len						[in/out]参数说明
* 参    数: cp_int32_t flag						[in/out]参数说明
*
* 返 回 值: cp_int32_t
*           0  : 成功
*         非0  : 失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2017-8-20 11:47:08
********************************************************************************/
cp_int32_t write_hi3531_frame_data(cp_hi3531_sdl_t *hi3531_sdl,
	const cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag)
{
	cp_int32_t						tmp_ret_int = 0;
	cp_video_frame_packet_t			*tmp_vfp = CP_NULL;



	if (!buf || !*buf || !len) {
		return -1;
	}

	//转换媒体数据，并校验数据合法性
	tmp_vfp = *((cp_video_frame_packet_t**)buf);
	if (cp_media_packet_type_video != tmp_vfp->mp.type) {
		cp_module_log(error, hi3531_sdl,
			"unknow media pakcet type[%d] error.",
			tmp_vfp->mp.type);
		return -2;
	}

	//循环处理视频帧数据
	return cycle_hi3531_frame_data(hi3531_sdl, CP_NULL, tmp_vfp);
}

/*******************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: cycle_hi3531_frame_data
*
* 函数全名: cycle_hi3531_frame_data
*
* 函数访问: public
*
* 函数说明: 循环处理hi3531数据
*
* 参    数: cp_hi3531_sdl_t * hi3531_sdl						[in/out]参数说明
* 参    数: cp_media_surface_t * surfact						[in/out]参数说明
* 参    数: cp_video_frame_packet_t * vfp						[in/out]参数说明
*
* 返 回 值: cp_int32_t
*           0  : 成功
*         非0  : 失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2017-8-20 14:15:20
********************************************************************************/
cp_int32_t cycle_hi3531_frame_data(cp_hi3531_sdl_t *hi3531_sdl,
	cp_media_surface_t *surfact,
	cp_video_frame_packet_t	*vfp)
{
	cp_int32_t								tmp_ret_int = 0;
	cp_queue_t								*tmp_queue = CP_NULL;
	cp_queue_t								*tmp_current = CP_NULL;
	cp_frame_play_position_t				*tmp_fpp = CP_NULL;
	cp_video_frame_process_t				tmp_vfp = { 0, };



	//处理cycle_hi3531_frame_data部分内容
	tmp_queue = &vfp->fpp_queue;
	for (tmp_current = cp_queue_next(tmp_queue); tmp_current != tmp_queue;
		tmp_current = cp_queue_next(tmp_current)) {
		tmp_fpp = cp_queue_data(tmp_current, cp_frame_play_position_t, vfpp_queue);
		if (!tmp_fpp) {
			continue;
		}

		//初始化video frame process
		cp_memset(&tmp_vfp, 0, cp_sizeof(cp_video_frame_process_t));

		tmp_vfp.mpro->ms = surfact;
		tmp_vfp.mpro->mp = (cp_media_packet_t*)vfp;
		tmp_vfp.vfpp = tmp_vfpp;
		tmp_vfp.vfp_type = cp_video_frame_process_type_resize;

		//处理图像内容
		tmp_ret_int = cp_get_option_module(hi3531_sdl->m_hi3531_tde, cp_hi3531_tde_option_get_resize, &tmp_vfp);
		if (tmp_ret_int) {
			continue;
		}

		//显示图像内容
		tmp_ret_int = cp_write_module(hi3531_sdl->m_hi3531_vo, &tmp_vfp, cp_sizeof(cp_video_frame_process_t*), 0);
		if (tmp_ret_int) {
			continue;
		}
	}

	return 0;
}

/*******************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: write_ffmpeg_frame_data
*
* 函数全名: write_ffmpeg_frame_data
*
* 函数访问: public
*
* 函数说明: 写ffmpeg数据
*
* 参    数: cp_hi3531_sdl_t * hi3531_sdl						[in/out]参数说明
* 参    数: const cp_uchar_t * * buf						[in/out]参数说明
* 参    数: cp_int32_t len						[in/out]参数说明
* 参    数: cp_int32_t flag						[in/out]参数说明
*
* 返 回 值: cp_int32_t
*           0  : 成功
*         非0  : 失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2017-8-20 11:47:18
********************************************************************************/
cp_int32_t write_ffmpeg_frame_data(cp_hi3531_sdl_t *hi3531_sdl,
	const cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag)
{
	return 0;
}












