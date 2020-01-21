/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-12-25

Description:

**************************************************************************/


#include "cp_hi3531_vdec.h"
#include "cp_hi3531_vdec_codec_info.h"


/*创建hi3531 信息*/
cp_int32_t create_hi3531_vdec_info(cp_hi3531_vdec_codec_t *hi3531_vdec_codec, cp_hi3531_vdec_codec_info_t *hi3531_vdec_codec_info)
{
	if (!hi3531_vdec_codec || !hi3531_vdec_codec_info || !hi3531_vdec_codec_info->md) {
		return -1;
	}

	if (hi3531_vdec_codec->vdec_info) {
		return 0;
	}

	hi3531_vdec_codec->vdec_info = (cp_hi3531_vdec_info_t*)cp_palloc(hi3531_vdec_codec->pool, cp_sizeof(cp_hi3531_vdec_info_t));
	if (!hi3531_vdec_codec->vdec_info) {
		return -2;
	}
	else {
		hi3531_vdec_codec->vdec_info->vd = &hi3531_vdec_codec->vd;
	}

#if defined(CP_HI3531_VDEC_MODE)

	hi3531_vdec_codec->vdec_info->vdec_channel = hi3531_vdec_codec_info->md->channel;

#endif

	return 0;
}

/*销毁hi3531 信息*/
cp_int32_t destroy_hi3531_vdec_info(cp_hi3531_vdec_codec_t *hi3531_vdec_codec)
{
	if (!hi3531_vdec_codec || !hi3531_vdec_codec->vdec_info) {
		return -1;
	}

	cp_pfree(hi3531_vdec_codec->pool, hi3531_vdec_codec->vdec_info);

	return 0;
}

/*初始化hi3531 信息*/
cp_int32_t init_hi3531_vdec(cp_hi3531_vdec_codec_t *hi3531_vdec_codec, cp_hi3531_vdec_info_t *hi3531_vdec_info)
{

#if defined(CP_HI3531_VDEC_MODE)
	HI_S32									tmp_ret_int = 0;
	HI_S32									tmp_bufsize_int = 0;
	PAYLOAD_TYPE_E							tmp_payload_type;


	if (!hi3531_vdec_info || !hi3531_vdec_info->vd) {
		return -1;
	}

	memset(&hi3531_vdec_info->vdec_channel_attr, 0, sizeof(VDEC_CHN_ATTR_S));

	//获取vdec payload 类型
	tmp_payload_type = get_hi3531_vdec_payload_type(hi3531_vdec_codec, hi3531_vdec_info);
	if (PT_BUTT == tmp_payload_type) {
		cp_module_log(error, hi3531_vdec_codec,
			"get_hi3531_vdec_payload_type() error. unspport media type[%d]", tmp_payload_type);
		return -1;
	}

	tmp_bufsize_int = hi3531_vdec_info->vd->width * hi3531_vdec_info->vd->height;

	//更新priorit部分内容
	if (hi3531_vdec_info->vd->md.priority > CP_HI3531_VIDEO_VDEC_CONF_VDEC_DEFAULT_PRIORITY_MIN_VALUE &&
		hi3531_vdec_info->vd->md.priority < CP_HI3531_VIDEO_VDEC_CONF_VDEC_DEFAULT_PRIORITY_MAX_VALUE) {

		hi3531_vdec_info->vdec_channel_attr.u32Priority = hi3531_vdec_info->vd->md.priority;	//此处必须大于0

	} else {

		hi3531_vdec_info->vdec_channel_attr.u32Priority = hi3531_vdec_codec->hacc.vdec_video_conf.vdec_default_priority;	//此处必须大于0

		cp_module_log(warn, hi3531_vdec_codec,
			"media description priority[%d] invalid. priority valid value[%d, %d]. used default priority[%d] now.",
			hi3531_vdec_info->vd->md.priority,
			CP_HI3531_VIDEO_VDEC_CONF_VDEC_DEFAULT_PRIORITY_MIN_VALUE,
			CP_HI3531_VIDEO_VDEC_CONF_VDEC_DEFAULT_PRIORITY_MAX_VALUE,
			hi3531_vdec_codec->hacc.vdec_video_conf.vdec_default_priority
			);
	}

	//更新其他信息
	hi3531_vdec_info->vdec_channel_attr.enType = tmp_payload_type;
	hi3531_vdec_info->vdec_channel_attr.u32BufSize = tmp_bufsize_int;
	hi3531_vdec_info->vdec_channel_attr.u32PicWidth = hi3531_vdec_info->vd->width;
	hi3531_vdec_info->vdec_channel_attr.u32PicHeight = hi3531_vdec_info->vd->height;

	switch (tmp_payload_type)
	{
		case PT_H264:
		{
			hi3531_vdec_info->vdec_channel_attr.stVdecVideoAttr.u32RefFrameNum = hi3531_vdec_codec->hacc.vdec_video_conf.vdec_ref_frame_number;
			hi3531_vdec_info->vdec_channel_attr.stVdecVideoAttr.enMode = hi3531_vdec_codec->hacc.vdec_video_conf.vdec_stream_mode;
			hi3531_vdec_info->vdec_channel_attr.stVdecVideoAttr.s32SupportBFrame = hi3531_vdec_codec->hacc.vdec_video_conf.vdec_support_bframe;
		}
		break;
		case PT_JPEG:
		{
			hi3531_vdec_info->vdec_channel_attr.stVdecJpegAttr.enMode = hi3531_vdec_codec->hacc.vdec_video_conf.vdec_stream_mode;
		}
		break;
		default:
			cp_module_log(error, hi3531_vdec_codec,
				"init_hi3531_vdec() error. unspport payload type[%d]", tmp_payload_type);
			return -2;
	}

#endif

	return 0;
}

#if defined(CP_HI3531_VDEC_MODE)
/*获取hi3531 payload 类型*/
PAYLOAD_TYPE_E get_hi3531_vdec_payload_type(cp_hi3531_vdec_codec_t *hi3531_vdec_codec, cp_hi3531_vdec_info_t *hi3531_vdec_info)
{
	if (!hi3531_vdec_info || !hi3531_vdec_info->vd) {
		return PT_BUTT;
	}

	switch (hi3531_vdec_info->vd->md.encodec_type)
	{
		case cp_media_type_video_h264:
		{
			return PT_H264;
		}
		break;
		default:
		{
			return PT_BUTT;
		}
		break;
	}
	return PT_BUTT;
}

//将VIDEO_FRAME_INFO_S中部分数据保存到cp_media_packet_t中
cp_int32_t hi3531_vdec_convert_vfi2mp(cp_media_packet_t *mp, VIDEO_FRAME_INFO_S *vfi)
{
	cp_video_description_t					*tmp_vd = CP_NULL;
	cp_int32_t								i = 0;



	if (!mp || !mp->md_p || !vfi) {
		return -1;
	}

	//判断是否为视频描述信息
	if (cp_media_description_type_video != mp->md_p->type) {
		return -2;
	}

	//转换数据类型并赋值
	tmp_vd = (cp_video_description_t*)mp->md_p;
	tmp_vd->width = vfi->stVFrame.u32Width;
	tmp_vd->height = vfi->stVFrame.u32Height;

	//定义像素格式
	tmp_vd->md.pix_fmt = hi3531_vdec_convert_pf2cpf(vfi->stVFrame.enPixelFormat);

	//获取地址信息
	for (i = 0; i < cp_ary_size(vfi->stVFrame.u32PhyAddr); i++) {
		if (!vfi->stVFrame.u32PhyAddr[i]) {
			continue;
		}

		//这里进行数据地址的处理
	}

	return 0;
}

//将hi3531中PIXEL_FORMAT_E 类型转换为 cp_codec_pixel_format_e类型数值
cp_codec_pixel_format_e hi3531_vdec_convert_pf2cpf(PIXEL_FORMAT_E pf)
{
	cp_pixel_format_contrast_t				tmp_pf_contrast[] = {
		{PIXEL_FORMAT_RGB_1BPP, cp_codec_pixel_format_rgb48be},
		{PIXEL_FORMAT_RGB_2BPP, cp_codec_pixel_format_rgb48be},
		{PIXEL_FORMAT_RGB_4BPP, cp_codec_pixel_format_rgb4},
		{PIXEL_FORMAT_RGB_8BPP, cp_codec_pixel_format_rgb8},
		{PIXEL_FORMAT_RGB_444, cp_codec_pixel_format_rgb444le},
		{PIXEL_FORMAT_RGB_4444, cp_codec_pixel_format_rgb444be},
		{PIXEL_FORMAT_RGB_555, cp_codec_pixel_format_rgb555le},
		{PIXEL_FORMAT_RGB_565, cp_codec_pixel_format_rgb565le},
		{PIXEL_FORMAT_RGB_1555, cp_codec_pixel_format_rgb555le},
		{PIXEL_FORMAT_RGB_888, cp_codec_pixel_format_rgb24},
		{PIXEL_FORMAT_RGB_8888, cp_codec_pixel_format_argb},
		{PIXEL_FORMAT_RGB_PLANAR_888, cp_codec_pixel_format_rgb0},
		{PIXEL_FORMAT_RGB_BAYER, cp_codec_pixel_format_bayer_bggr8},
		{PIXEL_FORMAT_YUV_A422, cp_codec_pixel_format_yuva422p},
		{PIXEL_FORMAT_YUV_A444, cp_codec_pixel_format_yuva444p},
		{PIXEL_FORMAT_YUV_PLANAR_422, cp_codec_pixel_format_yuv422p},
		{PIXEL_FORMAT_YUV_PLANAR_420, cp_codec_pixel_format_yuv420p},
		{PIXEL_FORMAT_YUV_PLANAR_444, cp_codec_pixel_format_yuv444p},
		{PIXEL_FORMAT_YUV_SEMIPLANAR_422, cp_codec_pixel_format_yuv422p},
		{PIXEL_FORMAT_YUV_SEMIPLANAR_420, cp_codec_pixel_format_yuv420p},
		{PIXEL_FORMAT_YUV_SEMIPLANAR_444, cp_codec_pixel_format_yuv444p},
		{PIXEL_FORMAT_UYVY_PACKAGE_422, cp_codec_pixel_format_uyvy422},
		{PIXEL_FORMAT_YUYV_PACKAGE_422, cp_codec_pixel_format_yuyv422},
		{PIXEL_FORMAT_VYUY_PACKAGE_422, cp_codec_pixel_format_yvyu422},
		//{PIXEL_FORMAT_YCbCr_PLANAR, cp_codec_pixel_format_rgb72be},
		{PIXEL_FORMAT_BUTT, cp_codec_pixel_format_none},
	};

	if (pf < 0 | pf > cp_ary_size(tmp_pf_contrast)) {
		return cp_codec_pixel_format_none;
	}
	
	return tmp_pf_contrast[pf].cpf;
}
#endif


/*启动hi3531 信息*/
cp_int32_t start_hi3531_vdec(cp_hi3531_vdec_codec_t *hi3531_vdec_codec, cp_hi3531_vdec_info_t *hi3531_vdec_info)
{
#if defined(CP_HI3531_VDEC_MODE)
	HI_S32									tmp_ret_int = 0;


	if (!hi3531_vdec_info || !hi3531_vdec_info->vd) {
		return -1;
	}

	tmp_ret_int = HI_MPI_VDEC_CreateChn(hi3531_vdec_info->vdec_channel, &hi3531_vdec_info->vdec_channel_attr);
	if (HI_SUCCESS != tmp_ret_int) {
		cp_module_log(error, hi3531_vdec_codec,
			"HI_MPI_VDEC_CreateChn() channel[%d] failed. error_code[0x%x]", 
			hi3531_vdec_info->vdec_channel,
			tmp_ret_int);
		return tmp_ret_int;
	}

	tmp_ret_int = hi3531_vdec_set_prtcl_param(hi3531_vdec_codec, hi3531_vdec_info);
	if (tmp_ret_int) {
		cp_module_log(error, hi3531_vdec_codec,
			"hi3531_vdec_set_prtcl_param() failed. return[%d]",
			tmp_ret_int);
		return -2;
	}

	tmp_ret_int = hi3531_vdec_set_channel_param(hi3531_vdec_codec, hi3531_vdec_info);
	if (tmp_ret_int) {
		cp_module_log(error, hi3531_vdec_codec,
			"hi3531_vdec_set_channel_param() failed. return[%d]",
			tmp_ret_int);
		return -3;
	}

	tmp_ret_int = HI_MPI_VDEC_StartRecvStream(hi3531_vdec_info->vdec_channel);
	if (HI_SUCCESS != tmp_ret_int) {
		cp_module_log(error, hi3531_vdec_codec,
			"HI_MPI_VDEC_StartRecvStream() channel[%d] failed. error_code[0x%x]", 
			hi3531_vdec_info->vdec_channel,
			tmp_ret_int);
		return tmp_ret_int;
	}

#endif
	return 0;
}

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: hi3531_vdec_set_prtcl_param
*
* 函数说明: 设置hi3531 定义与协议相关的内存分配参数
*
* 参    数: cp_hi3531_vdec_codec_t * hi3531_vdec_codec						[in]参数说明
* 参    数: const cp_hi3531_vdec_info_t * hi3531_vdec_info						[in]参数说明
*
* 返 回 值: cp_int32_t
*           0  : 成功
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2017-07-01 13:04:00
******************************************************************************************************/
cp_int32_t hi3531_vdec_set_prtcl_param(cp_hi3531_vdec_codec_t *hi3531_vdec_codec, cp_hi3531_vdec_info_t *hi3531_vdec_info)
{
#if defined(CP_HI3531_VDEC_MODE)
	HI_S32									tmp_ret_int = 0;


	if (!hi3531_vdec_info || !hi3531_vdec_info->vd) {
		return -1;
	}

	tmp_ret_int = HI_MPI_VDEC_GetPrtclParam(hi3531_vdec_info->vdec_channel, &hi3531_vdec_info->vdec_prtcl_param);
	if (HI_SUCCESS != tmp_ret_int) {
		cp_module_log(error, hi3531_vdec_codec,
			"HI_MPI_VDEC_GetPrtclParam() channel[%d] failed. error_code[0x%x]", 
			hi3531_vdec_info->vdec_channel,
			tmp_ret_int);
		return -1;
	}

	hi3531_vdec_info->vdec_prtcl_param.s32MaxSliceNum = hi3531_vdec_codec->hacc.vdec_prtcl_param.max_slice_number;
	hi3531_vdec_info->vdec_prtcl_param.s32MaxSpsNum = hi3531_vdec_codec->hacc.vdec_prtcl_param.max_sps_number;
	hi3531_vdec_info->vdec_prtcl_param.s32MaxPpsNum = hi3531_vdec_codec->hacc.vdec_prtcl_param.max_pps_number;
	hi3531_vdec_info->vdec_prtcl_param.s32SCDBufSize = hi3531_vdec_codec->hacc.vdec_prtcl_param.scd_buffer_size;
	hi3531_vdec_info->vdec_prtcl_param.s32DisplayFrameNum = hi3531_vdec_codec->hacc.vdec_prtcl_param.display_frame_number;

	tmp_ret_int = HI_MPI_VDEC_SetPrtclParam(hi3531_vdec_info->vdec_channel, &hi3531_vdec_info->vdec_prtcl_param);
	if (HI_SUCCESS != tmp_ret_int) {
		cp_module_log(error, hi3531_vdec_codec,
			"HI_MPI_VDEC_SetPrtclParam() channel[%d] failed. error_code[0x%x]", 
			hi3531_vdec_info->vdec_channel,
			tmp_ret_int);
		return -2;
	}

#endif
	return 0;
}

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: hi3531_vdec_set_channel_param
*
* 函数说明: 设置hi3531 定义解码通道参数
*
* 参    数: cp_hi3531_vdec_codec_t * hi3531_vdec_codec						[in]参数说明
* 参    数: const cp_hi3531_vdec_info_t * hi3531_vdec_info						[in]参数说明
*
* 返 回 值: cp_int32_t
*           0  : 成功
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2017-07-01 13:04:13
******************************************************************************************************/
cp_int32_t hi3531_vdec_set_channel_param(cp_hi3531_vdec_codec_t *hi3531_vdec_codec, cp_hi3531_vdec_info_t *hi3531_vdec_info)
{
#if defined(CP_HI3531_VDEC_MODE)
	HI_S32									tmp_ret_int = 0;


	if (!hi3531_vdec_info || !hi3531_vdec_info->vd) {
		return -1;
	}

	tmp_ret_int = HI_MPI_VDEC_GetChnParam(hi3531_vdec_info->vdec_channel, &hi3531_vdec_info->vdec_channel_param);
	if (HI_SUCCESS != tmp_ret_int) {
		cp_module_log(error, hi3531_vdec_codec,
			"HI_MPI_VDEC_GetChnParam() channel[%d] failed. error_code[0x%x]", 
			hi3531_vdec_info->vdec_channel,
			tmp_ret_int);
		return tmp_ret_int;
	}

	hi3531_vdec_info->vdec_channel_param.s32ChanErrThr = hi3531_vdec_codec->hacc.vdec_channle_param.channel_err_thr;
	hi3531_vdec_info->vdec_channel_param.s32ChanStrmOFThr = hi3531_vdec_codec->hacc.vdec_channle_param.channel_stream_of_thr;
	hi3531_vdec_info->vdec_channel_param.s32DecMode = hi3531_vdec_codec->hacc.vdec_channle_param.decode_mode;
	hi3531_vdec_info->vdec_channel_param.s32DecOrderOutput = hi3531_vdec_codec->hacc.vdec_channle_param.decode_order_output;

	tmp_ret_int = HI_MPI_VDEC_SetChnParam(hi3531_vdec_info->vdec_channel, &hi3531_vdec_info->vdec_channel_param);
	if (HI_SUCCESS != tmp_ret_int) {
		cp_module_log(error, hi3531_vdec_codec,
			"HI_MPI_VDEC_SetChnParam() channel[%d] failed. error_code[0x%x]",
			hi3531_vdec_info->vdec_channel,
			tmp_ret_int);
		return tmp_ret_int;
	}

#endif
	return 0;
}

/*读取模块数据，flag为读取模式的扩展标志。默认为0，其他为预留*/
cp_int32_t read_hi3531_vdec_data(cp_hi3531_vdec_codec_t *hi3531_vdec_codec, cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag)
{
#if defined(CP_HI3531_VDEC_MODE)
	HI_S32									tmp_ret_int = 0;
	cp_media_packet_t						*tmp_mp = CP_NULL;
	VIDEO_FRAME_INFO_S						*tmp_frame_info = CP_NULL;



	if (!buf || !*buf || !len) {
		return -1;
	}

	//转换媒体数据，并校验数据合法性
	tmp_mp = *((cp_media_packet_t**)buf);
	if (cp_media_packet_type_data_and_timestamp != tmp_mp->type) {
		return -2;
	}

	//分配一个内存空间
	tmp_frame_info = cp_pcalloc(hi3531_vdec_codec->pool, cp_sizeof(VIDEO_FRAME_INFO_S));
	if (!tmp_frame_info) {
		return -3;
	}

	//获取解码后图像数据
	tmp_ret_int = HI_MPI_VDEC_GetImage(hi3531_vdec_codec->vdec_info->vdec_channel, tmp_frame_info, HI_IO_NOBLOCK);
	if (HI_SUCCESS != tmp_ret_int) {
		cp_pfree(hi3531_vdec_codec->pool, tmp_frame_info);
		cp_module_log(error, hi3531_vdec_codec,
			"HI_MPI_VDEC_GetImage() channel[%d] failed. error_code[0x%x]",
			hi3531_vdec_codec->vdec_info->vdec_channel,
			tmp_ret_int);
		return -1;
	}

	//将VIDEO_FRAME_INFO_S数据保存
	tmp_mp->mp_buf.data = tmp_frame_info;

	//下面进行数据的保存操作
	if (hi3531_vdec_convert_vfi2mp(tmp_mp, tmp_frame_info)) {
		cp_pfree(hi3531_vdec_codec->pool, tmp_frame_info);
		cp_module_log(error, hi3531_vdec_codec,
			"hi3531_vdec_convert_vfi2mp() channel[%d] failed. return_code[%d]",
			hi3531_vdec_codec->vdec_info->vdec_channel,
			tmp_ret_int);
		return -1;
	}

#if 0
	//释放视频解码通道的图像
	//tmp_frame_info.stVFrame.u32Field
	tmp_ret_int = HI_MPI_VDEC_ReleaseImage(hi3531_vdec_codec->vdec_info->vdec_channel, &tmp_frame_info);
	if (HI_SUCCESS != tmp_ret_int) {
		cp_module_log(error, hi3531_vdec_codec,
			"HI_MPI_VDEC_ReleaseImage() channel[%d] failed. error_code[0x%x]",
			hi3531_vdec_codec->vdec_info->vdec_channel,
			tmp_ret_int);
		return -1;
	}
#endif


#endif
	return 0;
}

/*写模块数据，flag为写模式的扩展标志。默认为0，其他为预留*/
cp_int32_t write_hi3531_vdec_data(cp_hi3531_vdec_codec_t *hi3531_vdec_codec, const cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag)
{
#if defined(CP_HI3531_VDEC_MODE)
	HI_S32									tmp_ret_int = 0;
	cp_media_packet_t						*tmp_mp = CP_NULL;
	VDEC_STREAM_S							tmp_stream = {0, };



	if (!buf || !*buf || !len) {
		return -1;
	}

	//转换媒体数据，并校验数据合法性
	tmp_mp = *((cp_media_packet_t**)buf);
	if (cp_media_packet_type_data_and_timestamp != tmp_mp->type) {
		return -2;
	}

	tmp_stream.pu8Addr = cp_buf_get_pos(&tmp_mp->mp_buf.buf[0]);
	tmp_stream.u32Len = cp_buf_get_length(&tmp_mp->mp_buf.buf[0]);
	tmp_stream.u64PTS = (HI_U64)(tmp_mp->ts.tv_sec) * CP_TIME_SEC_TO_NSEC + tmp_mp->ts.tv_nsec;
	//tmp_ret_int = HI_MPI_VDEC_SendStream(hi3531_vdec_codec->vdec_info->vdec_channel, &tmp_stream, HI_IO_BLOCK);
	tmp_ret_int = HI_MPI_VDEC_SendStream(hi3531_vdec_codec->vdec_info->vdec_channel, &tmp_stream, HI_IO_NOBLOCK);
	if (HI_SUCCESS != tmp_ret_int) {
		cp_module_log(error, hi3531_vdec_codec,
			"HI_MPI_VDEC_SendStream() channel[%d] failed. error_code[0x%x]",
			hi3531_vdec_codec->vdec_info->vdec_channel,
			tmp_ret_int);
		return -1;
	}

#endif

	return 0;
}




/*停止hi3531 信息*/
cp_int32_t stop_hi3531_vdec(cp_hi3531_vdec_codec_t *hi3531_vdec_codec, cp_hi3531_vdec_info_t *hi3531_vdec_info)
{
#if defined(CP_HI3531_VDEC_MODE)
	HI_S32									tmp_ret_int = 0;


	if (!hi3531_vdec_info || !hi3531_vdec_info->vd) {
		return -1;
	}

	tmp_ret_int = HI_MPI_VDEC_StopRecvStream(hi3531_vdec_info->vdec_channel);
	if (HI_SUCCESS != tmp_ret_int) {
		cp_module_log(error, hi3531_vdec_codec,
			"HI_MPI_VDEC_StopRecvStream() channel[%d] failed. error_code[0x%x]", 
			hi3531_vdec_info->vdec_channel,
			tmp_ret_int);
		return tmp_ret_int;
	}

	tmp_ret_int = HI_MPI_VDEC_DestroyChn(hi3531_vdec_info->vdec_channel);
	if (HI_SUCCESS != tmp_ret_int) {
		cp_module_log(error, hi3531_vdec_codec,
			"HI_MPI_VDEC_DestroyChn() channel[%d] failed. error_code[0x%x]", 
			hi3531_vdec_info->vdec_channel,
			tmp_ret_int);
		return tmp_ret_int;
	}	

#endif

	return 0;
}









