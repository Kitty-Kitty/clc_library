/*******************************************************************************
*
*Copyright:novigo
*
*File name: cp_hi3531_tde_proc.c
*
*Author:fangzhenmu@novigo.com.cn
*
*Version: 1.0
*
*Date:2017/07/29
*
*Description: create (cp_hi3531_tde_proc.c)
*
*Others:
*
*History:
*******************************************************************************/
#include "cp_hi3531_tde_proc.h"




//初始化设备
cp_int32_t hi3531_tde_init_dev(cp_hi3531_tde_t *hi3531_tde, cp_hi3531_tde_configure_t *tde_conf)
{
	return 0;
}

//启动设备
cp_int32_t hi3531_tde_start_dev(cp_hi3531_tde_t *hi3531_tde, cp_hi3531_tde_configure_t *tde_conf)
{
	cp_int32_t										tmp_ret_int = 0;



	if (!hi3531_tde || !tde_conf) {
		return -1;
	}

#if defined(CP_HI3531_DEV_MODE)
	/* 1. open tde device */
	tmp_ret_int = HI_TDE2_Open();
	if (HI_SUCCESS != tmp_ret_int) {
		cp_hi3531_dev_log(error, hi3531_tde,	"HI_TDE2_Open() failed!");
		return -1;
	}
	else {
		cp_hi3531_dev_log(notice, hi3531_tde, "HI_TDE2_Open() successed!");
	}
#endif

	return tmp_ret_int;
}





/*******************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: hi3531_tde_video_frame_copy
*
* 函数全名: hi3531_tde_video_frame_copy
*
* 函数访问: public 
*
* 函数说明: 视频帧快速烤备图像
*
* 参    数: cp_hi3531_tde_t * hi3531_tde						[in/out]参数说明
* 参    数: cp_media_surface_t * ms						[in/out]参数说明
* 参    数: cp_media_packet_t * mp						[in/out]参数说明
* 参    数: cp_video_frame_play_position_t * vfpp						[in/out]参数说明
*
* 返 回 值: cp_int32_t
*           0  : 成功
*         非0  : 失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2017-8-20 16:36:14
********************************************************************************/
cp_int32_t hi3531_tde_video_frame_copy(cp_hi3531_tde_t *hi3531_tde,
	cp_media_surface_t *ms,
	cp_media_packet_t *mp,
	cp_video_frame_play_position_t *vfpp)
{
	cp_int32_t										tmp_ret_int = 0;



	if (!hi3531_tde || !ms | !mp || !vfpp) {
		return -1;
	}

#if defined(CP_HI3531_DEV_MODE)
	TDE2_SURFACE_S									tmp_surface_src = { 0, };
	TDE2_SURFACE_S									tmp_surface_dest = { 0, };
	TDE2_RECT_S										tmp_rect_src = { 0, };
	TDE2_RECT_S										tmp_rect_dest = { 0, };


	/* 1. start job */
	hi3531_tde->tde_handle = HI_TDE2_BeginVideoJob();
	if (!hi3531_tde->tde_handle) {
		cp_module_log(error, hi3531_tde, "HI_TDE2_BeginVideoJob() error.");
		return -2;
	}

	//配置源信息
	tmp_surface_src.u32PhyAddr = cp_buf_get_pos(&(ms->mp_buf.buf[0]));
	//tmp_surface_src.enColorFmt 
	tmp_surface_src.u32Width = vfpp->fpp.source.margin.right - vfpp->fpp.source.margin.left;
	tmp_surface_src.u32Height = vfpp->fpp.source.margin.bottom - vfpp->fpp.source.margin.top;

	tmp_rect_src.s32Xpos = vfpp->fpp.source.content.left;
	tmp_rect_src.s32Ypos = vfpp->fpp.source.content.top;
	tmp_rect_src.u32Width = tmp_surface_src.u32Width;
	tmp_rect_src.u32Height = tmp_surface_src.u32Height;


	//配置目的信息
	tmp_surface_dest.u32PhyAddr = cp_buf_get_pos(&(ms->mp_buf.buf[0]));
	//tmp_surface_src.enColorFmt 
	tmp_surface_dest.u32Width = vfpp->fpp.dest.content.right - vfpp->fpp.dest.content.left;
	tmp_surface_dest.u32Height = vfpp->fpp.dest.content.bottom - vfpp->fpp.dest.content.top;

	tmp_rect_dest.s32Xpos = vfpp->fpp.dest.content.left;
	tmp_rect_dest.s32Ypos = vfpp->fpp.dest.content.top;
	tmp_rect_dest.u32Width = tmp_surface_dest.u32Width;
	tmp_rect_dest.u32Height = tmp_surface_dest.u32Height;


	tmp_ret_int = HI_TDE2_QuickCopy(hi3531_tde->tde_handle,
		&tmp_surface_src, &tmp_rect_src,
		&tmp_surface_dest, &tmp_rect_dest);
	if (tmp_ret_int) {
		cp_module_log(error, hi3531_tde,
			"HI_TDE2_QuickResize() error. error_code[0x%x]",
			tmp_ret_int);
		return -2;
	}

	/* 5. submit job */
	tmp_ret_int = HI_TDE2_EndJob(hi3531_tde->tde_handle, HI_FALSE, HI_TRUE, 10);
	if (tmp_ret_int < 0) {
		cp_module_log(error, hi3531_tde,
			"HI_TDE2_EndJob() error. error_code[0x%x]",
			tmp_ret_int);
		HI_TDE2_CancelJob(hi3531_tde->tde_handle);
		return -3;
	}
#endif

	return 0;
}

/*******************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: hi3531_tde_video_frame_fill
*
* 函数全名: hi3531_tde_video_frame_fill
*
* 函数访问: public 
*
* 函数说明: 视频帧填充图像
*
* 参    数: cp_hi3531_tde_t * hi3531_tde						[in]参数说明
* 参    数: cp_media_surface_t * ms						[out]参数说明
* 参    数: cp_media_packet_t * mp						[in]参数说明
* 参    数: cp_video_frame_play_position_t * vfpp						[in]参数说明
*
* 返 回 值: cp_int32_t
*           0  : 成功
*         非0  : 失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2017-8-20 16:30:23
********************************************************************************/
cp_int32_t hi3531_tde_video_frame_fill(cp_hi3531_tde_t *hi3531_tde,
	cp_media_surface_t *ms,
	cp_media_packet_t *mp,
	cp_video_frame_play_position_t *vfpp)
{
	cp_int32_t										tmp_ret_int = 0;



	if (!hi3531_tde || !ms | !mp || !vfpp) {
		return -1;
	}

#if defined(CP_HI3531_DEV_MODE)
	TDE2_SURFACE_S									tmp_surface_dest = { 0, };
	TDE2_RECT_S										tmp_rect_dest = { 0, };


	/* 1. start job */
	hi3531_tde->tde_handle = HI_TDE2_BeginVideoJob();
	if (!hi3531_tde->tde_handle) {
		cp_module_log(error, hi3531_tde, "HI_TDE2_BeginVideoJob() error.");
		return -2;
	}

	//配置目的信息
	tmp_surface_dest.u32PhyAddr = cp_buf_get_pos(&(ms->mp_buf.buf[0]));
	//tmp_surface_src.enColorFmt 
	tmp_surface_dest.u32Width = vfpp->fpp.dest.content.right - vfpp->fpp.dest.content.left;
	tmp_surface_dest.u32Height = vfpp->fpp.dest.content.bottom - vfpp->fpp.dest.content.top;

	tmp_rect_dest.s32Xpos = vfpp->fpp.dest.content.left;
	tmp_rect_dest.s32Ypos = vfpp->fpp.dest.content.top;
	tmp_rect_dest.u32Width = tmp_surface_dest.u32Width;
	tmp_rect_dest.u32Height = tmp_surface_dest.u32Height;


	tmp_ret_int = HI_TDE2_QuickFill(hi3531_tde->tde_handle,
		&tmp_surface_dest, &tmp_rect_dest,
		cp_buf_get_pos(&(ms->mp_buf.buf[0])));
	if (tmp_ret_int) {
		cp_module_log(error, hi3531_tde,
			"HI_TDE2_QuickFill() error. error_code[0x%x]",
			tmp_ret_int);
		return -2;
	}

	/* 5. submit job */
	tmp_ret_int = HI_TDE2_EndJob(hi3531_tde->tde_handle, HI_FALSE, HI_TRUE, 10);
	if (tmp_ret_int < 0) {
		cp_module_log(error, hi3531_tde,
			"HI_TDE2_EndJob() error. error_code[0x%x]",
			tmp_ret_int);
		HI_TDE2_CancelJob(hi3531_tde->tde_handle);
		return -3;
	}
#endif

	return 0;
}

/*******************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: hi3531_tde_video_frame_resize
*
* 函数全名: hi3531_tde_video_frame_resize
*
* 函数访问: public
*
* 函数说明: 视频帧放大缩小
*
* 参    数: cp_hi3531_tde_t * hi3531_tde						[in]参数说明
* 参    数: cp_media_surface_t * ms						[out]参数说明
* 参    数: cp_media_packet_t * mp						[in]参数说明
* 参    数: cp_video_frame_play_position_t * vfpp						[in]参数说明
*
* 返 回 值: cp_int32_t
*           0  : 成功
*         非0  : 失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2017-8-20 15:10:23
********************************************************************************/
cp_int32_t hi3531_tde_video_frame_resize(cp_hi3531_tde_t *hi3531_tde,
	cp_media_surface_t *ms,
	cp_media_packet_t *mp,
	cp_video_frame_play_position_t *vfpp)
{
	cp_int32_t										tmp_ret_int = 0;



	if (!hi3531_tde || !ms | !mp || !vfpp) {
		return -1;
	}

#if defined(CP_HI3531_DEV_MODE)
	TDE2_SURFACE_S									tmp_surface_src = {0, };
	TDE2_SURFACE_S									tmp_surface_dest = {0, };
	TDE2_RECT_S										tmp_rect_src = { 0, };
	TDE2_RECT_S										tmp_rect_dest = { 0, };


	/* 1. start job */
	hi3531_tde->tde_handle = HI_TDE2_BeginVideoJob();
	if (!hi3531_tde->tde_handle) {
		cp_module_log(error, hi3531_tde, "HI_TDE2_BeginVideoJob() error.");
		return -2;
	}

	//配置源信息
	tmp_surface_src.u32PhyAddr = cp_buf_get_pos(&(ms->mp_buf.buf[0]));
	//tmp_surface_src.enColorFmt 
	tmp_surface_src.u32Width = vfpp->fpp.source.margin.right - vfpp->fpp.source.margin.left;
	tmp_surface_src.u32Height = vfpp->fpp.source.margin.bottom - vfpp->fpp.source.margin.top;

	tmp_rect_src.s32Xpos = vfpp->fpp.source.content.left;
	tmp_rect_src.s32Ypos = vfpp->fpp.source.content.top;
	tmp_rect_src.u32Width = tmp_surface_src.u32Width;
	tmp_rect_src.u32Height = tmp_surface_src.u32Height;


	//配置目的信息
	tmp_surface_dest.u32PhyAddr = cp_buf_get_pos(&(ms->mp_buf.buf[0]));
	//tmp_surface_src.enColorFmt 
	tmp_surface_dest.u32Width = vfpp->fpp.dest.content.right - vfpp->fpp.dest.content.left;
	tmp_surface_dest.u32Height = vfpp->fpp.dest.content.bottom - vfpp->fpp.dest.content.top;

	tmp_rect_dest.s32Xpos = vfpp->fpp.dest.content.left;
	tmp_rect_dest.s32Ypos = vfpp->fpp.dest.content.top;
	tmp_rect_dest.u32Width = tmp_surface_dest.u32Width;
	tmp_rect_dest.u32Height = tmp_surface_dest.u32Height;


	tmp_ret_int = HI_TDE2_QuickResize(hi3531_tde->tde_handle,
		&tmp_surface_src, &tmp_rect_src,
		&tmp_surface_dest, &tmp_rect_dest);
	if (tmp_ret_int) {
		cp_module_log(error, hi3531_tde,
			"HI_TDE2_QuickResize() error. error_code[0x%x]",
			tmp_ret_int);
		return -2;
	}

	/* 5. submit job */
	tmp_ret_int = HI_TDE2_EndJob(hi3531_tde->tde_handle, HI_FALSE, HI_TRUE, 10);
	if (tmp_ret_int < 0) {
		cp_module_log(error, hi3531_tde,
			"HI_TDE2_EndJob() error. error_code[0x%x]",
			tmp_ret_int);
		HI_TDE2_CancelJob(hi3531_tde->tde_handle);
		return -3;
	}
#endif

	return 0;
}

/*******************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: hi3531_tde_video_frame_copy_resize
*
* 函数全名: hi3531_tde_video_frame_copy_resize
*
* 函数访问: public
*
* 函数说明: 视频帧拷贝同时放大缩小
*
* 参    数: cp_hi3531_tde_t * hi3531_tde						[in]参数说明
* 参    数: cp_media_surface_t * ms						[out]参数说明
* 参    数: cp_media_packet_t * mp						[in]参数说明
* 参    数: cp_video_frame_play_position_t * vfpp						[in]参数说明
*
* 返 回 值: cp_int32_t
*           0  : 成功
*         非0  : 失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2017-8-20 15:10:23
********************************************************************************/
cp_int32_t hi3531_tde_video_frame_copy_resize(cp_hi3531_tde_t *hi3531_tde,
	cp_media_surface_t *ms,
	cp_media_packet_t *mp,
	cp_video_frame_play_position_t *vfpp)
{
	cp_int32_t										tmp_ret_int = 0;



	if (!hi3531_tde || !ms | !mp || !vfpp) {
		return -1;
	}

#if defined(CP_HI3531_DEV_MODE)
	TDE2_MB_S										tmp_mb_in = { 0, };
	TDE2_MB_S										tmp_mb_out = { 0, };
	TDE2_RECT_S										tmp_rect_in = { 0, };
	TDE2_RECT_S										tmp_rect_out = { 0, };
	TDE2_MBOPT_S									tmp_mb_opt = {0, };


	/* 1. start job */
	hi3531_tde->tde_handle = HI_TDE2_BeginVideoJob();
	if (!hi3531_tde->tde_handle) {
		cp_module_log(error, hi3531_tde, "HI_TDE2_BeginVideoJob() error.");
		return -2;
	}

	//配置源信息
	tmp_mb_in.u32PhyAddr = cp_buf_get_pos(&(ms->mp_buf.buf[0]));
	tmp_mb_in.u32Width = vfpp->fpp.source.margin.right - vfpp->fpp.source.margin.left;
	tmp_mb_in.u32Height = vfpp->fpp.source.margin.bottom - vfpp->fpp.source.margin.top;

	tmp_rect_in.s32Xpos = vfpp->fpp.source.content.left;
	tmp_rect_in.s32Ypos = vfpp->fpp.source.content.top;
	tmp_rect_in.u32Width = tmp_mb_in.u32Width;
	tmp_rect_in.u32Height = tmp_mb_in.u32Height;

	//配置目的信息
	tmp_mb_out.u32PhyAddr = cp_buf_get_pos(&(ms->mp_buf.buf[0]));
	//tmp_surface_src.enColorFmt 
	tmp_mb_out.u32Width = vfpp->fpp.dest.content.right - vfpp->fpp.dest.content.left;
	tmp_mb_out.u32Height = vfpp->fpp.dest.content.bottom - vfpp->fpp.dest.content.top;

	tmp_rect_out.s32Xpos = vfpp->fpp.dest.content.left;
	tmp_rect_out.s32Ypos = vfpp->fpp.dest.content.top;
	tmp_rect_out.u32Width = tmp_mb_out.u32Width;
	tmp_rect_out.u32Height = tmp_mb_out.u32Height;


	tmp_ret_int = HI_TDE2_Mb2Mb(hi3531_tde->tde_handle,
		&tmp_mb_in, &tmp_rect_in,
		&tmp_mb_out, &tmp_rect_out,
		&tmp_mb_opt);
	if (tmp_ret_int) {
		cp_module_log(error, hi3531_tde,
			"HI_TDE2_Mb2Mb() error. error_code[0x%x]",
			tmp_ret_int);
		return -2;
	}

	/* 5. submit job */
	tmp_ret_int = HI_TDE2_EndJob(hi3531_tde->tde_handle, HI_FALSE, HI_TRUE, 10);
	if (tmp_ret_int < 0) {
		cp_module_log(error, hi3531_tde,
			"HI_TDE2_EndJob() error. error_code[0x%x]",
			tmp_ret_int);
		HI_TDE2_CancelJob(hi3531_tde->tde_handle);
		return -3;
	}
#endif

	return tmp_ret_int;
}


//停止设备
cp_int32_t hi3531_tde_stop_dev(cp_hi3531_tde_t *hi3531_tde, cp_hi3531_tde_configure_t *tde_conf)
{
	cp_int32_t										tmp_ret_int = 0;



	if (!hi3531_tde || !tde_conf) {
		return -1;
	}

#if defined(CP_HI3531_DEV_MODE)
	/* 1. open tde device */
	HI_TDE2_Close();
#endif

	return tmp_ret_int;
}
