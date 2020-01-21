/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-12-25

Description:

**************************************************************************/


#include "cp_hi3519_av_sample.h"
#include "cp_ipc_rtp.h"





#if defined(CP_HI3519_MODE)
void hi3519_av_signal_handle(HI_S32 signo)
{
	SAMPLE_COMM_ISP_Stop();
	SAMPLE_COMM_SYS_Exit();
	printf("\033[0;31mprogram termination abnormally!\033[0;39m\n");
	exit(-1);
}
#endif

/*初始化hi3519 信息*/
cp_int32_t hi3519_av_init_info(cp_hi3519_av_codec_t *hi3519_av_codec, cp_hi3519_av_conf_t *hi3519_av_conf)
{
	cp_int32_t					tmp_ret_int = 0;



	switch (hi3519_av_codec->hacc.mode) {
	case cp_hi3519_av_codec_mode_vi_venc:
	{
		tmp_ret_int = init_hi3519_av_info_mode_vi_venc(hi3519_av_codec, hi3519_av_conf);
		if (tmp_ret_int) {
			cp_module_log(error, hi3519_av_codec, "init_hi3519_av_info_mode_vi_venc() error.");
			return tmp_ret_int;
		}
	}
	break;
	case cp_hi3519_av_codec_mode_vi_stitch_vpss_venc:
	{
		tmp_ret_int = init_hi3519_av_info_mode_vi_stitch_vpss_venc(hi3519_av_codec, hi3519_av_conf);
		if (tmp_ret_int) {
			cp_module_log(error, hi3519_av_codec, "init_hi3519_av_info_mode_vi_stitch_vpss_venc() error.");
			return tmp_ret_int;
		}
	}
	break;
	case cp_hi3519_av_codec_mode_vi_fisheye_stitch_vpss_venc:
	{
		tmp_ret_int = init_hi3519_av_info_mode_vi_fisheye_stitch_vpss_venc(hi3519_av_codec, hi3519_av_conf);
		if (tmp_ret_int) {
			cp_module_log(error, hi3519_av_codec, "init_hi3519_av_info_mode_vi_fisheye_stitch_vpss_venc() error.");
			return tmp_ret_int;
		}
	}
	break;
	case cp_hi3519_av_codec_mode_vi_fisheye_process_vpss_venc:
	{
		tmp_ret_int = init_hi3519_av_info_mode_vi_fisheye_process_vpss_venc(hi3519_av_codec, hi3519_av_conf);
		if (tmp_ret_int) {
			cp_module_log(error, hi3519_av_codec, "init_hi3519_av_info_mode_vi_fisheye_process_vpss_venc() error.");
			return tmp_ret_int;
		}
	}
	break;
	case cp_hi3519_av_codec_mode_vi_fisheye_process_vpss_stitch_vpss_venc:
	{
		tmp_ret_int = init_hi3519_av_info_mode_vi_fisheye_process_vpss_stitch_vpss_venc(hi3519_av_codec, hi3519_av_conf);
		if (tmp_ret_int) {
			cp_module_log(error, hi3519_av_codec, "init_hi3519_av_info_mode_vi_fisheye_process_vpss_stitch_vpss_venc() error.");
			return tmp_ret_int;
		}
	}
	break;
	case cp_hi3519_av_codec_mode_vi_process_vpss_fisheye_stitch_vpss_venc:
	{
		tmp_ret_int = init_hi3519_av_info_mode_vi_process_vpss_fisheye_stitch_vpss_venc(hi3519_av_codec, hi3519_av_conf);
		if (tmp_ret_int) {
			cp_module_log(error, hi3519_av_codec, "init_hi3519_av_info_mode_vi_process_vpss_fisheye_stitch_vpss_venc() error.");
			return tmp_ret_int;
		}
	}
	break;
	default:
	{
		cp_module_log(error, hi3519_av_codec, "hi3519_av_init_info() error. unknow process mode[%d] error.", hi3519_av_codec->hacc.mode);
		tmp_ret_int = -1;
	}
	}

	return tmp_ret_int;
}

cp_int32_t hi3519_av_system_init(cp_hi3519_av_codec_t *hi3519_av_codec, cp_hi3519_av_conf_t *hi3519_av_conf)
{
#if defined(CP_HI3519_MODE)
	HI_S32									tmp_ret_int = HI_FAILURE;
	cp_hi3519_av_conf_t						*tmp_conf = hi3519_av_codec->av_conf;
	SIZE_S									tmp_size = { CP_HI3519_AV_CODEC_VI_WIDTH, CP_HI3519_AV_CODEC_VI_HEIGHT };
	HI_U32									tmp_blk_size;



	if (!tmp_conf) {
		return -1;
	}

	if (!hi3519_av_codec || !hi3519_av_conf) {
		return -1;
	}

#ifndef __HuaweiLite__
	signal(SIGINT, hi3519_av_signal_handle);
	signal(SIGTERM, hi3519_av_signal_handle);
	signal(SIGSEGV, hi3519_av_signal_handle);
	signal(SIGHUP, hi3519_av_signal_handle);
	signal(SIGCHLD, hi3519_av_signal_handle);
#endif

	if (SAMPLE_COMM_IsViVpssOnline())
	{
		cp_module_log(error, hi3519_av_codec,
			"SAMPLE_VIO_DoubleSensor_Preview only supports offline!\n");
		return HI_FAILURE;
	}

	HI_MPI_SYS_Exit();
	HI_MPI_VB_Exit();

	switch (SENSOR_TYPE) {
	case OMNIVISION_OV4689_MIPI_1080P_30FPS:
	{
		hi3519_av_conf->sensor_size.u32Width = 1920;
		hi3519_av_conf->sensor_size.u32Height = 1080;

		//设置
		tmp_conf->pic_size = PIC_HD1080;
		tmp_ret_int = HI_MPI_SYS_SetProfile(PROFILE_1080P_30);
		if (tmp_ret_int) {
			cp_module_log(error, hi3519_av_codec,
				"HI_MPI_SYS_SetProfile() [PROFILE_1080P_30] failed. error_code[0x%x]",
				tmp_ret_int);
		}
		tmp_blk_size = (hi3519_av_conf->sensor_size.u32Width * hi3519_av_conf->sensor_size.u32Height * 3) / 2;
	}
	break;
	case OMNIVISION_OV4689_MIPI_4M_30FPS:
	{
		//hi3519_av_conf->sensor_size.u32Width = 1920;
		hi3519_av_conf->sensor_size.u32Width = 2592;
		hi3519_av_conf->sensor_size.u32Height = 1520;

		//设置
		tmp_conf->pic_size = PIC_2592x1520;
		tmp_ret_int = HI_MPI_SYS_SetProfile(PROFILE_5M_30);
		if (tmp_ret_int) {
			cp_module_log(error, hi3519_av_codec,
				"HI_MPI_SYS_SetProfile() [PROFILE_5M_30] failed. error_code[0x%x]",
				tmp_ret_int);
		}
		tmp_blk_size = (hi3519_av_conf->sensor_size.u32Width + 16) * hi3519_av_conf->sensor_size.u32Height * 2;
	}
	break;
	default:
	{
		cp_module_log(error, hi3519_av_codec,
			"unknow sensor_type[%d] failed!",
			SENSOR_TYPE);
		return HI_FAILURE;
	}
	break;
	}

	tmp_conf->vi_output_pic_size = hi3519_av_conf->sensor_size;
	tmp_conf->vpss_output_pst_size = hi3519_av_conf->sensor_size;
	tmp_conf->stitch_input_pst_size = hi3519_av_conf->sensor_size;

	//设置
	tmp_conf->video_norm = VIDEO_ENCODING_MODE_PAL;

	//初始化视频缓存池属性结构体
	tmp_conf->vb_conf.u32MaxPoolCnt = VB_MAX_POOLS;

	//获取block_size大小
	// 	tmp_blk_size = SAMPLE_COMM_SYS_CalcPicVbBlkSize2(&tmp_size,
	// 		SAMPLE_PIXEL_FORMAT, SAMPLE_SYS_ALIGN_WIDTH);

	/* comm video buffer */
	// 	tmp_conf->vb_conf.astCommPool[0].u32BlkSize = tmp_blk_size * 2;
	// 	tmp_conf->vb_conf.astCommPool[0].u32BlkCnt = CP_HI3519_AV_CODEC_MAX_CHANNEL_NUMBER * 10;
	// 	tmp_conf->vb_conf.astCommPool[1].u32BlkSize = tmp_blk_size * 2;
	// 	tmp_conf->vb_conf.astCommPool[1].u32BlkCnt = CP_HI3519_AV_CODEC_MAX_CHANNEL_NUMBER * 10;
	tmp_conf->vb_conf.astCommPool[0].u32BlkSize = tmp_blk_size;
	tmp_conf->vb_conf.astCommPool[0].u32BlkCnt = CP_HI3519_AV_CODEC_MAX_CHANNEL_NUMBER * 2;
	tmp_conf->vb_conf.astCommPool[1].u32BlkSize = tmp_blk_size;
	tmp_conf->vb_conf.astCommPool[1].u32BlkCnt = CP_HI3519_AV_CODEC_MAX_CHANNEL_NUMBER * 17;
	// 	tmp_conf->vb_conf.astCommPool[2].u32BlkSize = tmp_blk_size;
	// 	tmp_conf->vb_conf.astCommPool[2].u32BlkCnt = CP_HI3519_AV_CODEC_MAX_CHANNEL_NUMBER * 10;
	// 	tmp_conf->vb_conf.astCommPool[3].u32BlkSize = tmp_blk_size;
	// 	tmp_conf->vb_conf.astCommPool[3].u32BlkCnt = CP_HI3519_AV_CODEC_MAX_CHANNEL_NUMBER * 4;
	// 	tmp_conf->vb_conf.astCommPool[4].u32BlkSize = tmp_blk_size;
	// 	tmp_conf->vb_conf.astCommPool[4].u32BlkCnt = CP_HI3519_AV_CODEC_MAX_CHANNEL_NUMBER * 4;

	cp_module_log(notice, hi3519_av_codec,
		"sensor_type[%d] vb block_size[%d]!",
		SENSOR_TYPE,
		tmp_blk_size);	

	tmp_ret_int = HI_MPI_VB_SetConf(&hi3519_av_conf->vb_conf);
	if (HI_SUCCESS != tmp_ret_int)
	{
		cp_module_log(error, hi3519_av_codec,
			"HI_MPI_VB_SetConf failed. error_code[0x%x]",
			tmp_ret_int);
		return HI_FAILURE;
	}

	tmp_ret_int = HI_MPI_VB_Init();
	if (HI_SUCCESS != tmp_ret_int)
	{
		cp_module_log(error, hi3519_av_codec,
			"HI_MPI_VB_Init failed. error_code[0x%x]",
			tmp_ret_int);
		return HI_FAILURE;
	}

	hi3519_av_conf->mpp_sys_conf.u32AlignWidth = SAMPLE_SYS_ALIGN_WIDTH;
	tmp_ret_int = HI_MPI_SYS_SetConf(&hi3519_av_conf->mpp_sys_conf);
	if (HI_SUCCESS != tmp_ret_int)
	{
		cp_module_log(error, hi3519_av_codec,
			"HI_MPI_SYS_SetConf failed. error_code[0x%x]",
			tmp_ret_int);
		return HI_FAILURE;
	}

	tmp_ret_int = HI_MPI_SYS_Init();
	if (HI_SUCCESS != tmp_ret_int)
	{
		cp_module_log(error, hi3519_av_codec,
			"HI_MPI_SYS_Init failed. error_code[0x%x]",
			tmp_ret_int);
		return HI_FAILURE;
	}
#endif
	return 0;
}

/*初始化hi3519 信息*/
cp_int32_t hi3519_av_init_info_bak(cp_hi3519_av_codec_t *hi3519_av_codec, cp_hi3519_av_conf_t *hi3519_av_conf)
{
	cp_int32_t						tmp_ret_int = 0;



	//初始化系统信息
	tmp_ret_int = hi3519_av_system_init(hi3519_av_codec, hi3519_av_codec->av_conf);
	if (tmp_ret_int) {
		cp_module_log(error, hi3519_av_codec, "hi3519_av_system_init() error.");
		return -1;
	}

	//初始化VI配置信息
	tmp_ret_int = init_hi3519_av_vi_conf(hi3519_av_codec, hi3519_av_codec->av_conf);
	if (tmp_ret_int) {
		cp_module_log(error, hi3519_av_codec, "init_hi3519_av_vi_conf() error.");
		return -1;
	}

#if 0
	//初始化vi fisheye配置信息
	tmp_ret_int = init_hi3519_av_fisheye_conf(hi3519_av_codec, hi3519_av_codec->av_conf);
#endif
	//初始化vi fisheye配置信息
	tmp_ret_int = init_hi3519_av_fisheye_conf_from_config(hi3519_av_codec, hi3519_av_codec->av_conf, cp_fisheye_type_vi);
	if (tmp_ret_int) {
		cp_module_log(error, hi3519_av_codec, "init_hi3519_av_fisheye_conf_from_config() error.");
		return -1;
	}

	//初始化EXT VPSS配置信息
	tmp_ret_int = init_hi3519_av_process_vpss_conf(hi3519_av_codec, hi3519_av_codec->av_conf);
	if (tmp_ret_int) {
		cp_module_log(error, hi3519_av_codec, "init_hi3519_av_process_vpss_conf() error.");
		return -1;
	}

	//初始化VPSS配置信息
	tmp_ret_int = init_hi3519_av_stitch_vpss_conf(hi3519_av_codec, hi3519_av_codec->av_conf);
	if (tmp_ret_int) {
		cp_module_log(error, hi3519_av_codec, "init_hi3519_av_stitch_vpss_conf() error.");
		return -1;
	}

	//初始化VENC配置信息
	tmp_ret_int = init_hi3519_av_venc_conf(hi3519_av_codec, hi3519_av_codec->av_conf);
	if (tmp_ret_int) {
		cp_module_log(error, hi3519_av_codec, "init_hi3519_av_venc_conf() error.");
		return -1;
	}

	return 0;
}

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: create_hi3519_av_codec_conf
*
* 函数说明: 表示创建conf信息
*
* 参    数: cp_hi3519_av_codec_t * hi3519_av_codec						[in]参数说明
*
* 返 回 值: cp_int32_t
*           0  : 成功
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2016-12-24 14:34:16
******************************************************************************************************/
cp_int32_t create_hi3519_av_codec_conf(cp_hi3519_av_codec_t *hi3519_av_codec, cp_hi3519_av_conf_t *hi3519_av_conf)
{
	cp_int32_t								i = 0;
	cp_hi3519_av_conf_t						*tmp_conf = CP_NULL;


	tmp_conf = cp_palloc(hi3519_av_codec->pool, cp_sizeof(cp_hi3519_av_conf_t));
	if (!tmp_conf) {
		cp_module_log(error, hi3519_av_codec, "cp_palloc() create conf failed!");
		return -1;
	}
	cp_memset(tmp_conf, 0, cp_sizeof(cp_hi3519_av_conf_t));

	hi3519_av_codec->av_conf = tmp_conf;
	tmp_conf->hi3519_av_codec = hi3519_av_codec;

	return 0;
}

/*初始化vi配置信息*/
cp_int32_t init_hi3519_av_vi_conf(cp_hi3519_av_codec_t *hi3519_av_codec, cp_hi3519_av_conf_t *hi3519_av_conf)
{
#if defined(CP_HI3519_MODE)
	cp_int32_t					i = 0;
	cp_int32_t					j = 0;
	HI_S32						tmp_ret_int = HI_FAILURE;
	HI_S32						tmp_crop_x_int = 0;


	hi3519_av_conf->is_used_vi_rotate = cp_false;

	for (i = 0; i < cp_ary_size(hi3519_av_conf->channel_list); i++) {
		hi3519_av_conf->channel_list[i].index = i;
		hi3519_av_conf->channel_list[i].ext_index = CP_HI3519_AV_CODEC_BEGIN_EXT_VI_CHANNEL_NUMBER + i;
		hi3519_av_conf->channel_list[i].dev = i;

		hi3519_av_conf->channel_list[i].is_used_fisheye = HI_TRUE;
		hi3519_av_conf->channel_list[i].is_used_crop = HI_FALSE;
		//hi3519_av_conf->channel_list[i].channel_config.enViMode = OMNIVISION_OV4689_MIPI_1080P_30FPS;
		//hi3519_av_conf->channel_list[i].channel_config.enViMode = OMNIVISION_OV4689_MIPI_4M_30FPS;
		hi3519_av_conf->channel_list[i].channel_config.enViMode = SENSOR_TYPE;
		hi3519_av_conf->channel_list[i].channel_config.enNorm = VIDEO_ENCODING_MODE_AUTO;
		hi3519_av_conf->channel_list[i].channel_config.enRotate = ROTATE_NONE;
		hi3519_av_conf->channel_list[i].channel_config.enViChnSet = VI_CHN_SET_NORMAL;
		hi3519_av_conf->channel_list[i].channel_config.enWDRMode = WDR_MODE_NONE;
		hi3519_av_conf->channel_list[i].channel_config.enFrmRate = SAMPLE_FRAMERATE_30FPS;
		hi3519_av_conf->channel_list[i].channel_config.enSnsNum = SAMPLE_SENSOR_DOUBLE;
		hi3519_av_conf->channel_list[i].pst_size.u32Width = hi3519_av_conf->sensor_size.u32Width;
		hi3519_av_conf->channel_list[i].pst_size.u32Height = hi3519_av_conf->sensor_size.u32Height;

		hi3519_av_conf->channel_list[i].is_flip = hi3519_av_codec->hacc.camera_configs[i].is_flip;
		hi3519_av_conf->channel_list[i].is_mirror = hi3519_av_codec->hacc.camera_configs[i].is_mirror;

		//这里计算旋转类型，计算方是：（角度值 / 90） % 4。 取值：0表示[0, 90)度；1表示[90, 180);2表示[180, 270);3表示[270, 360)
		hi3519_av_conf->channel_list[i].rotate = (ROTATE_E)((hi3519_av_codec->hacc.camera_configs[i].rotate / 90) % 4);
		hi3519_av_conf->stitch_vpss_info.vpss_list[i].rotate = ROTATE_90;

		for (j = 0; j < cp_ary_size(hi3519_av_conf->process_vpss_info[i].vpss_list); j++) {
			hi3519_av_conf->process_vpss_info[i].vpss_list[j].rotate = hi3519_av_conf->channel_list[i].rotate;
			if (ROTATE_90 == hi3519_av_conf->process_vpss_info[i].vpss_list[j].rotate ||
				ROTATE_270 == hi3519_av_conf->process_vpss_info[i].vpss_list[j].rotate) {
				hi3519_av_conf->is_process_angle = cp_true;
			}
		}

#if 0
		if (SENSOR_TYPE == OMNIVISION_OV4689_MIPI_4M_30FPS) {
			hi3519_av_conf->channel_list[i].is_used_crop = HI_TRUE;

			//因为vpss stitch是存在最大值4096 * 4096的限制，所以stitch时单个图像不能大于4096 / 2
			//这里使用高度值,形成一个正方形图像
			tmp_crop_x_int = (hi3519_av_conf->channel_list[i].pst_size.u32Width - 1920) / 2;
			hi3519_av_conf->channel_list[i].cap_rect.s32X = ALIGN_BACK(tmp_crop_x_int, 2);
			hi3519_av_conf->channel_list[i].cap_rect.s32Y = ALIGN_BACK(0, 4);
			//hi3519_av_conf->channel_list[i].cap_rect.u32Width = ALIGN_BACK(hi3519_av_conf->channel_list[i].pst_size.u32Height, 2);
			hi3519_av_conf->channel_list[i].cap_rect.u32Width = ALIGN_BACK(1920, 2);
			hi3519_av_conf->channel_list[i].cap_rect.u32Height = ALIGN_BACK(hi3519_av_conf->channel_list[i].pst_size.u32Height, 4);

			hi3519_av_conf->channel_list[i].pst_size.u32Width = hi3519_av_conf->channel_list[i].cap_rect.u32Width;
			hi3519_av_conf->channel_list[i].pst_size.u32Height = hi3519_av_conf->channel_list[i].cap_rect.u32Height;
		}
#endif

	}

	//双路拼接时stitching 校正时的结构体
	tmp_ret_int = init_hi3519_av_stitch_correction_attr(hi3519_av_codec, hi3519_av_conf);
	if (tmp_ret_int) {
		cp_module_log(error, hi3519_av_codec, "init_hi3519_av_stitch_correction_attr() failed!");
		return -1;
	}

#endif

	return 0;
}

/*初始化vi fisheye配置信息*/
cp_int32_t init_hi3519_av_fisheye_conf(cp_hi3519_av_codec_t *hi3519_av_codec, cp_hi3519_av_conf_t *hi3519_av_conf, cp_fisheye_type_e fisheye_type)
{
#if defined(CP_HI3519_MODE)
	cp_int32_t					i = 0;
	HI_S32						tmp_ret_int = HI_FAILURE;
	HI_S32						tmp_vi_number = 1;
	//HI_S32						tmp_ret_height = CP_HI3519_AV_CODEC_VI_HEIGHT;
	//HI_S32						tmp_ret_width = 1920;
	//HI_S32						tmp_ret_height = 1080;
	// 	HI_U16						temp_fisheye_config[CP_HI3519_AV_CODEC_VI_FISHEYE_CONFIG_LMF_LENGTH] =
	// 	{ 0, 15, 31, 47, 63, 79, 95, 111, 127, 143, 159, 175,
	// 	191, 207, 223, 239, 255, 271, 286, 302, 318, 334, 350, 365, 381, 397, 412,
	// 	428, 443, 459, 474, 490, 505, 520, 536, 551, 566, 581, 596, 611, 626, 641,
	// 	656, 670, 685, 699, 713, 728, 742, 756, 769, 783, 797, 810, 823, 836, 848,
	// 	861, 873, 885, 896, 908, 919, 929, 940, 950, 959, 969, 984, 998, 1013, 1027,
	// 	1042, 1056, 1071, 1085, 1100, 1114, 1129, 1143, 1158, 1172, 1187, 1201, 1215,
	// 	1230, 1244, 1259, 1273, 1288, 1302, 1317, 1331, 1346, 1360, 1375, 1389, 1404,
	// 	1418, 1433, 1447, 1462, 1476, 1491, 1505, 1519, 1534, 1548, 1563, 1577, 1592,
	// 	1606, 1621, 1635, 1650, 1664, 1679, 1693, 1708, 1722, 1737, 1751, 1766, 1780, 1795, 1809, 1823, 1838 };

	HI_U16						temp_fisheye_config[CP_HI3519_AV_CODEC_VI_FISHEYE_CONFIG_LMF_LENGTH] =
	{0, 9, 26, 43, 51, 69, 77, 94, 111, 120,
	137, 145, 163, 180, 188, 205, 214, 231, 248, 256,
	273, 281, 298, 315, 324, 340, 349, 366, 382, 391,
	407, 416, 432, 449, 457, 473, 482, 498, 515, 523, 
	539, 547, 563, 580, 588, 604, 612, 628, 644, 651,
	667, 675, 691, 706, 714, 730, 738, 753, 768, 776, 
	791, 799, 814, 829, 836, 851, 858, 873, 888, 895,
	909, 916, 931, 945, 952, 966, 973, 987, 995, 1000, 
	1007, 1021, 1027, 1041, 1054, 1060, 1073, 1080, 1093, 1105,
	1112, 1124, 1130, 1142, 1154, 1160, 1172, 1178, 1189, 1201,
	1206, 1217, 1223, 1233, 1244, 1249, 1259, 1265, 1275, 1284,
	1289, 1298, 1303, 1312, 1325, 1338, 1350, 1357, 1368, 1379,
	1385, 1394, 1403, 1408, 1415, 1422, 1427, 1434};



	for (i = 0; i < cp_ary_size(hi3519_av_conf->fisheye_info); i++) {
		memcpy(hi3519_av_conf->fisheye_info[i].fisheye_config.au16LMFCoef,
			temp_fisheye_config, CP_HI3519_AV_CODEC_VI_FISHEYE_CONFIG_LMF_LENGTH * cp_sizeof(HI_U16));

		hi3519_av_conf->fisheye_info[i].fisheye_type = fisheye_type;
		hi3519_av_conf->fisheye_info[i].fisheye_attr.bEnable = HI_TRUE;
		//hi3519_av_conf->fisheye_info[i].fisheye_attr.bLMF = HI_FALSE;
		hi3519_av_conf->fisheye_info[i].fisheye_attr.bLMF = HI_TRUE;
		hi3519_av_conf->fisheye_info[i].fisheye_attr.bBgColor = HI_FALSE;
		//hi3519_av_conf->fisheye_info[i].fisheye_attr.u32BgColor = 0x0fFC;
		hi3519_av_conf->fisheye_info[i].fisheye_attr.u32BgColor = 0xFF0000;
		hi3519_av_conf->fisheye_info[i].fisheye_attr.s32HorOffset = 0;
		hi3519_av_conf->fisheye_info[i].fisheye_attr.s32VerOffset = 0;
		hi3519_av_conf->fisheye_info[i].fisheye_attr.u32TrapezoidCoef = 0;
		hi3519_av_conf->fisheye_info[i].fisheye_attr.s32FanStrength = 0;
		//hi3519_av_conf->fisheye_info[i].fisheye_attr.enMountMode = FISHEYE_CEILING_MOUNT;
		hi3519_av_conf->fisheye_info[i].fisheye_attr.enMountMode = FISHEYE_WALL_MOUNT;
		hi3519_av_conf->fisheye_info[i].fisheye_attr.u32RegionNum = 2;

		//hi3519_av_conf->fisheye_info[i].fisheye_attr.astFisheyeRegionAttr[0].enViewMode				= FISHEYE_VIEW_360_PANORAMA;
		hi3519_av_conf->fisheye_info[i].fisheye_attr.astFisheyeRegionAttr[0].enViewMode = FISHEYE_VIEW_180_PANORAMA;
		hi3519_av_conf->fisheye_info[i].fisheye_attr.astFisheyeRegionAttr[0].u32InRadius = 0;
		hi3519_av_conf->fisheye_info[i].fisheye_attr.astFisheyeRegionAttr[0].u32OutRadius = ALIGN_BACK(hi3519_av_conf->channel_list[i].pst_size.u32Height / 2 + 100, 2);
		//hi3519_av_conf->fisheye_info[i].fisheye_attr.astFisheyeRegionAttr[0].u32OutRadius = ALIGN_BACK(tmp_ret_height / 2 + 100, 2);
		hi3519_av_conf->fisheye_info[i].fisheye_attr.astFisheyeRegionAttr[0].u32Pan = 180;
		hi3519_av_conf->fisheye_info[i].fisheye_attr.astFisheyeRegionAttr[0].u32Tilt = 180;
		hi3519_av_conf->fisheye_info[i].fisheye_attr.astFisheyeRegionAttr[0].u32HorZoom = 4095;
		hi3519_av_conf->fisheye_info[i].fisheye_attr.astFisheyeRegionAttr[0].u32VerZoom = 4095;
		hi3519_av_conf->fisheye_info[i].fisheye_attr.astFisheyeRegionAttr[0].stOutRect.s32X = 0;
		hi3519_av_conf->fisheye_info[i].fisheye_attr.astFisheyeRegionAttr[0].stOutRect.s32Y = 0;
		hi3519_av_conf->fisheye_info[i].fisheye_attr.astFisheyeRegionAttr[0].stOutRect.u32Width = ALIGN_BACK(hi3519_av_conf->channel_list[i].pst_size.u32Width, 2);
		//hi3519_av_conf->fisheye_info[i].fisheye_attr.astFisheyeRegionAttr[0].stOutRect.u32Width = ALIGN_BACK(tmp_ret_width, 2);
		hi3519_av_conf->fisheye_info[i].fisheye_attr.astFisheyeRegionAttr[0].stOutRect.u32Height = ALIGN_BACK(hi3519_av_conf->channel_list[i].pst_size.u32Height, 2);
		//hi3519_av_conf->fisheye_info[i].fisheye_attr.astFisheyeRegionAttr[0].stOutRect.u32Height = ALIGN_BACK(tmp_ret_height, 2);

		//hi3519_av_conf->fisheye_info[i].fisheye_attr.astFisheyeRegionAttr[1].enViewMode				= FISHEYE_VIEW_360_PANORAMA;
		hi3519_av_conf->fisheye_info[i].fisheye_attr.astFisheyeRegionAttr[1].enViewMode = FISHEYE_VIEW_180_PANORAMA;
		hi3519_av_conf->fisheye_info[i].fisheye_attr.astFisheyeRegionAttr[1].u32InRadius = 0;
		hi3519_av_conf->fisheye_info[i].fisheye_attr.astFisheyeRegionAttr[1].u32OutRadius = ALIGN_BACK(hi3519_av_conf->channel_list[i].pst_size.u32Height / 2 + 100, 2);
		//hi3519_av_conf->fisheye_info[i].fisheye_attr.astFisheyeRegionAttr[1].u32OutRadius = ALIGN_BACK(tmp_ret_height / 2 + 100, 2);
		hi3519_av_conf->fisheye_info[i].fisheye_attr.astFisheyeRegionAttr[1].u32Pan = 180;
		hi3519_av_conf->fisheye_info[i].fisheye_attr.astFisheyeRegionAttr[1].u32Tilt = 180;
		hi3519_av_conf->fisheye_info[i].fisheye_attr.astFisheyeRegionAttr[1].u32HorZoom = 4095;
		hi3519_av_conf->fisheye_info[i].fisheye_attr.astFisheyeRegionAttr[1].u32VerZoom = 4095;
		hi3519_av_conf->fisheye_info[i].fisheye_attr.astFisheyeRegionAttr[1].stOutRect.s32X = 0;
		hi3519_av_conf->fisheye_info[i].fisheye_attr.astFisheyeRegionAttr[1].stOutRect.s32Y = 0;
		hi3519_av_conf->fisheye_info[i].fisheye_attr.astFisheyeRegionAttr[1].stOutRect.u32Width = ALIGN_BACK(hi3519_av_conf->channel_list[i].pst_size.u32Width, 2);
		//hi3519_av_conf->fisheye_info[i].fisheye_attr.astFisheyeRegionAttr[1].stOutRect.u32Width = ALIGN_BACK(tmp_ret_width, 2);;
		hi3519_av_conf->fisheye_info[i].fisheye_attr.astFisheyeRegionAttr[1].stOutRect.u32Height = ALIGN_BACK(hi3519_av_conf->channel_list[i].pst_size.u32Height, 2);
		//hi3519_av_conf->fisheye_info[i].fisheye_attr.astFisheyeRegionAttr[1].stOutRect.u32Height = ALIGN_BACK(tmp_ret_height, 2);
	}

#endif

	return 0;
}

/*初始化vi fisheye配置信息*/
cp_int32_t init_hi3519_av_fisheye_conf_from_config(cp_hi3519_av_codec_t *hi3519_av_codec, cp_hi3519_av_conf_t *hi3519_av_conf, cp_fisheye_type_e fisheye_type)
{
#if defined(CP_HI3519_MODE)
	cp_int32_t					i = 0;
	HI_S32						tmp_ret_int = HI_FAILURE;
	//HI_S32						tmp_ret_height = CP_HI3519_AV_CODEC_VI_HEIGHT;
	//HI_S32						tmp_ret_width = 1920;
	//HI_S32						tmp_ret_height = 1080;
	// 	HI_U16						temp_fisheye_config[CP_HI3519_AV_CODEC_VI_FISHEYE_CONFIG_LMF_LENGTH] =
	// 	{ 0, 15, 31, 47, 63, 79, 95, 111, 127, 143, 159, 175,
	// 	191, 207, 223, 239, 255, 271, 286, 302, 318, 334, 350, 365, 381, 397, 412,
	// 	428, 443, 459, 474, 490, 505, 520, 536, 551, 566, 581, 596, 611, 626, 641,
	// 	656, 670, 685, 699, 713, 728, 742, 756, 769, 783, 797, 810, 823, 836, 848,
	// 	861, 873, 885, 896, 908, 919, 929, 940, 950, 959, 969, 984, 998, 1013, 1027,
	// 	1042, 1056, 1071, 1085, 1100, 1114, 1129, 1143, 1158, 1172, 1187, 1201, 1215,
	// 	1230, 1244, 1259, 1273, 1288, 1302, 1317, 1331, 1346, 1360, 1375, 1389, 1404,
	// 	1418, 1433, 1447, 1462, 1476, 1491, 1505, 1519, 1534, 1548, 1563, 1577, 1592,
	// 	1606, 1621, 1635, 1650, 1664, 1679, 1693, 1708, 1722, 1737, 1751, 1766, 1780, 1795, 1809, 1823, 1838 };

	HI_U16						temp_fisheye_config[CP_HI3519_AV_CODEC_VI_FISHEYE_CONFIG_LMF_LENGTH] =
	{0, 9, 26, 43, 51, 69, 77, 94, 111, 120,
	137, 145, 163, 180, 188, 205, 214, 231, 248, 256,
	273, 281, 298, 315, 324, 340, 349, 366, 382, 391,
	407, 416, 432, 449, 457, 473, 482, 498, 515, 523, 
	539, 547, 563, 580, 588, 604, 612, 628, 644, 651,
	667, 675, 691, 706, 714, 730, 738, 753, 768, 776, 
	791, 799, 814, 829, 836, 851, 858, 873, 888, 895,
	909, 916, 931, 945, 952, 966, 973, 987, 995, 1000, 
	1007, 1021, 1027, 1041, 1054, 1060, 1073, 1080, 1093, 1105,
	1112, 1124, 1130, 1142, 1154, 1160, 1172, 1178, 1189, 1201,
	1206, 1217, 1223, 1233, 1244, 1249, 1259, 1265, 1275, 1284,
	1289, 1298, 1303, 1312, 1325, 1338, 1350, 1357, 1368, 1379,
	1385, 1394, 1403, 1408, 1415, 1422, 1427, 1434};



	for (i = 0; i < cp_ary_size(hi3519_av_conf->fisheye_info); i++) {
		memcpy(hi3519_av_conf->fisheye_info[i].fisheye_config.au16LMFCoef,
			temp_fisheye_config, CP_HI3519_AV_CODEC_VI_FISHEYE_CONFIG_LMF_LENGTH * cp_sizeof(HI_U16));

		hi3519_av_conf->fisheye_info[i].fisheye_type = fisheye_type;
		hi3519_av_conf->fisheye_info[i].fisheye_attr.bEnable = HI_TRUE;
		//hi3519_av_conf->fisheye_info[i].fisheye_attr.bLMF = HI_FALSE;
		hi3519_av_conf->fisheye_info[i].fisheye_attr.bLMF = HI_TRUE;
		hi3519_av_conf->fisheye_info[i].fisheye_attr.bBgColor = HI_FALSE;
		//hi3519_av_conf->fisheye_info[i].fisheye_attr.u32BgColor = 0x0fFC;
		hi3519_av_conf->fisheye_info[i].fisheye_attr.u32BgColor = 0xFF0000;
		hi3519_av_conf->fisheye_info[i].fisheye_attr.s32HorOffset = hi3519_av_codec->hacc.camera_configs[i].hor_offset;
		hi3519_av_conf->fisheye_info[i].fisheye_attr.s32VerOffset = hi3519_av_codec->hacc.camera_configs[i].ver_offset;
		hi3519_av_conf->fisheye_info[i].fisheye_attr.u32TrapezoidCoef = hi3519_av_codec->hacc.camera_configs[i].trapezoid_coef;
		hi3519_av_conf->fisheye_info[i].fisheye_attr.s32FanStrength = hi3519_av_codec->hacc.camera_configs[i].fan_strength;
		//hi3519_av_conf->fisheye_info[i].fisheye_attr.enMountMode = FISHEYE_WALL_MOUNT;
		hi3519_av_conf->fisheye_info[i].fisheye_attr.enMountMode = hi3519_av_codec->hacc.camera_configs[i].mount_mode;
		hi3519_av_conf->fisheye_info[i].fisheye_attr.u32RegionNum = 2;

		//hi3519_av_conf->fisheye_info[i].fisheye_attr.astFisheyeRegionAttr[0].enViewMode = FISHEYE_VIEW_180_PANORAMA;
		hi3519_av_conf->fisheye_info[i].fisheye_attr.astFisheyeRegionAttr[0].enViewMode = hi3519_av_codec->hacc.camera_configs[i].view_mode;
		hi3519_av_conf->fisheye_info[i].fisheye_attr.astFisheyeRegionAttr[0].u32InRadius = hi3519_av_codec->hacc.camera_configs[i].in_radius;
		hi3519_av_conf->fisheye_info[i].fisheye_attr.astFisheyeRegionAttr[0].u32OutRadius = ALIGN_BACK(hi3519_av_codec->hacc.camera_configs[i].out_radius, 2);
		hi3519_av_conf->fisheye_info[i].fisheye_attr.astFisheyeRegionAttr[0].u32Pan = hi3519_av_codec->hacc.camera_configs[i].pan;
		hi3519_av_conf->fisheye_info[i].fisheye_attr.astFisheyeRegionAttr[0].u32Tilt = hi3519_av_codec->hacc.camera_configs[i].tilt;
		hi3519_av_conf->fisheye_info[i].fisheye_attr.astFisheyeRegionAttr[0].u32HorZoom = hi3519_av_codec->hacc.camera_configs[i].hor_zoom;
		hi3519_av_conf->fisheye_info[i].fisheye_attr.astFisheyeRegionAttr[0].u32VerZoom = hi3519_av_codec->hacc.camera_configs[i].ver_zoom;
		hi3519_av_conf->fisheye_info[i].fisheye_attr.astFisheyeRegionAttr[0].stOutRect.s32X = hi3519_av_codec->hacc.camera_configs[i].outrect_x;
		hi3519_av_conf->fisheye_info[i].fisheye_attr.astFisheyeRegionAttr[0].stOutRect.s32Y = hi3519_av_codec->hacc.camera_configs[i].outrect_y;
		hi3519_av_conf->fisheye_info[i].fisheye_attr.astFisheyeRegionAttr[0].stOutRect.u32Width = ALIGN_BACK(hi3519_av_codec->hacc.camera_configs[i].outrect_width, 2);
		hi3519_av_conf->fisheye_info[i].fisheye_attr.astFisheyeRegionAttr[0].stOutRect.u32Height = ALIGN_BACK(hi3519_av_codec->hacc.camera_configs[i].outrect_height, 2);

		//hi3519_av_conf->fisheye_info[i].fisheye_attr.astFisheyeRegionAttr[1].enViewMode = FISHEYE_VIEW_180_PANORAMA;
		hi3519_av_conf->fisheye_info[i].fisheye_attr.astFisheyeRegionAttr[1].enViewMode = hi3519_av_codec->hacc.camera_configs[i].view_mode;
		hi3519_av_conf->fisheye_info[i].fisheye_attr.astFisheyeRegionAttr[1].u32InRadius = hi3519_av_codec->hacc.camera_configs[i].in_radius;
		hi3519_av_conf->fisheye_info[i].fisheye_attr.astFisheyeRegionAttr[1].u32OutRadius = ALIGN_BACK(hi3519_av_codec->hacc.camera_configs[i].out_radius, 2);
		hi3519_av_conf->fisheye_info[i].fisheye_attr.astFisheyeRegionAttr[1].u32Pan = hi3519_av_codec->hacc.camera_configs[i].pan;
		hi3519_av_conf->fisheye_info[i].fisheye_attr.astFisheyeRegionAttr[1].u32Tilt = hi3519_av_codec->hacc.camera_configs[i].tilt;
		hi3519_av_conf->fisheye_info[i].fisheye_attr.astFisheyeRegionAttr[1].u32HorZoom = hi3519_av_codec->hacc.camera_configs[i].hor_zoom;
		hi3519_av_conf->fisheye_info[i].fisheye_attr.astFisheyeRegionAttr[1].u32VerZoom = hi3519_av_codec->hacc.camera_configs[i].ver_zoom;
		hi3519_av_conf->fisheye_info[i].fisheye_attr.astFisheyeRegionAttr[1].stOutRect.s32X = hi3519_av_codec->hacc.camera_configs[i].outrect_x;
		hi3519_av_conf->fisheye_info[i].fisheye_attr.astFisheyeRegionAttr[1].stOutRect.s32Y = hi3519_av_codec->hacc.camera_configs[i].outrect_y;
		hi3519_av_conf->fisheye_info[i].fisheye_attr.astFisheyeRegionAttr[1].stOutRect.u32Width = ALIGN_BACK(hi3519_av_codec->hacc.camera_configs[i].outrect_width, 2);
		hi3519_av_conf->fisheye_info[i].fisheye_attr.astFisheyeRegionAttr[1].stOutRect.u32Height = ALIGN_BACK(hi3519_av_codec->hacc.camera_configs[i].outrect_height, 2);
	}

#endif

	return 0;
}

/*初始化编码器配置信息*/
cp_int32_t init_hi3519_av_venc_conf(cp_hi3519_av_codec_t *hi3519_av_codec, cp_hi3519_av_conf_t *hi3519_av_conf)
{
#if defined(CP_HI3519_MODE)
	cp_int32_t					i = 0;
	HI_S32						tmp_ret_int = HI_FAILURE;



	for (i = 0; i < cp_ary_size(hi3519_av_conf->venc_list); i++) {
		hi3519_av_conf->venc_list[i].index = i;
		hi3519_av_conf->venc_list[i].payload = PT_H264;
		hi3519_av_conf->venc_list[i].gop_mode = VENC_GOPMODE_DUALP;
		hi3519_av_conf->venc_list[i].profile = 0;
		//hi3519_av_conf->venc_list[i].pic_size = PIC_HD1080;

		if (cp_hi3519_av_codec_mode_vi_venc == hi3519_av_codec->hacc.mode) {
			switch (SENSOR_TYPE) {
			case OMNIVISION_OV4689_MIPI_1080P_30FPS:
			{
				hi3519_av_conf->venc_list[i].pic_size = PIC_HD1080;
			}
			break;
			case OMNIVISION_OV4689_MIPI_4M_30FPS:
			{
				hi3519_av_conf->venc_list[i].pic_size = PIC_2592x1520;
			}
			break;
			default:
			{
				cp_module_log(error, hi3519_av_codec,
					"unknow sensor_type[%d] failed!",
					SENSOR_TYPE);
				return HI_FAILURE;
			}
			break;
			}
		}
		else {
			hi3519_av_conf->venc_list[i].pic_size = PIC_HD1080;
		}

		hi3519_av_conf->venc_list[i].rc = SAMPLE_RC_CBR;
		hi3519_av_conf->venc_list[i].video_norm = VIDEO_ENCODING_MODE_NTSC;

		tmp_ret_int = SAMPLE_COMM_VENC_GetGopAttr(hi3519_av_conf->venc_list[i].gop_mode,
			&hi3519_av_conf->venc_list[i].gop_attr, hi3519_av_conf->venc_list[i].video_norm);
		if (HI_SUCCESS != tmp_ret_int)
		{
			cp_module_log(error, hi3519_av_codec, "SAMPLE_COMM_VENC_GetGopAttr() error");
			return -1;
		}

		hi3519_av_conf->venc_list[i].rtp_sd = create_rtp_socket_data(hi3519_av_codec->pool);
		if (!hi3519_av_conf->venc_list[i].rtp_sd) {
			cp_module_log(error, hi3519_av_codec,
				"create_rtp_socket_data() socket_data[%d] failed!",
				i);
			return -1;
		}
	}

#endif

	return 0;
}

/*初始化vpss配置信息*/
cp_int32_t init_hi3519_av_stitch_vpss_conf(cp_hi3519_av_codec_t *hi3519_av_codec, cp_hi3519_av_conf_t *hi3519_av_conf)
{
#if defined(CP_HI3519_MODE)
	cp_int32_t					i = 0;
	cp_int32_t					tmp_sub_width = 0;
	HI_S32						tmp_ret_int = HI_FAILURE;
	SIZE_S						tmp_size = { CP_HI3519_AV_CODEC_VI_WIDTH, CP_HI3519_AV_CODEC_VI_HEIGHT };



	if (cp_hi3519_av_codec_mode_vi_fisheye_process_vpss_stitch_vpss_venc == hi3519_av_codec->hacc.mode) {
		tmp_size.u32Width = hi3519_av_conf->process_vpss_info[0].vpss_list[CP_HI3519_AV_CODEC_USED_VPSS_CHANNEL_NUMBER].mode.u32Width;
		tmp_size.u32Height = hi3519_av_conf->process_vpss_info[0].vpss_list[CP_HI3519_AV_CODEC_USED_VPSS_CHANNEL_NUMBER].mode.u32Height;
	}
	else {
		tmp_size.u32Width = hi3519_av_conf->channel_list[0].pst_size.u32Width;
		tmp_size.u32Height = hi3519_av_conf->channel_list[0].pst_size.u32Height;
	}

	hi3519_av_conf->stitch_vpss_info.attr.u32MaxW = tmp_size.u32Width * 2;
	hi3519_av_conf->stitch_vpss_info.attr.u32MaxH = tmp_size.u32Height;

	if (hi3519_av_conf->is_process_angle) {
		hi3519_av_conf->stitch_vpss_info.attr.u32MaxW = tmp_size.u32Height * 2;
		hi3519_av_conf->stitch_vpss_info.attr.u32MaxH = tmp_size.u32Width;
	}

	hi3519_av_conf->stitch_vpss_info.attr.u32MaxW = hi3519_av_conf->vi_output_pic_size.u32Width * 2;
	hi3519_av_conf->stitch_vpss_info.attr.u32MaxH = hi3519_av_conf->vi_output_pic_size.u32Width;

	hi3519_av_conf->stitch_vpss_info.index = 0;
	hi3519_av_conf->stitch_vpss_info.attr.bIeEn = HI_FALSE;
	hi3519_av_conf->stitch_vpss_info.attr.bNrEn = HI_TRUE;
	hi3519_av_conf->stitch_vpss_info.attr.stNrAttr.u32RefFrameNum = 2;
	hi3519_av_conf->stitch_vpss_info.attr.enDieMode = VPSS_DIE_MODE_NODIE;
	hi3519_av_conf->stitch_vpss_info.attr.enPixFmt = PIXEL_FORMAT_YUV_SEMIPLANAR_420;

	//配置stitch属性
	//	tmp_ret_int = init_hi3519_av_stitch_vpss_stitch_conf(hi3519_av_codec, hi3519_av_conf);
	if (hi3519_av_codec->hacc.stitch_config.auto_config.is_auto) {
		tmp_ret_int = init_hi3519_av_stitch_vpss_stitch_auto_conf(hi3519_av_codec, hi3519_av_conf);
	}
	else {
		tmp_ret_int = init_hi3519_av_stitch_vpss_stitch_detail_conf(hi3519_av_codec, hi3519_av_conf);
	}

	//拼接融合高级属性结构体
	hi3519_av_conf->stitch_vpss_info.stitch_blend_param.stAdjustParam.u32BldRange = 10;
	hi3519_av_conf->stitch_vpss_info.stitch_blend_param.stAdjustParam.u32BldPosition = 30;

	for (i = 0; i < cp_ary_size(hi3519_av_conf->stitch_vpss_info.vpss_list); i++) {
		hi3519_av_conf->stitch_vpss_info.vpss_list[i].mode.enChnMode = VPSS_CHN_MODE_USER;
		hi3519_av_conf->stitch_vpss_info.vpss_list[i].mode.enPixelFormat = SAMPLE_PIXEL_FORMAT;
		hi3519_av_conf->stitch_vpss_info.vpss_list[i].index = CP_HI3519_AV_CODEC_BEGIN_VPSS_CHANNEL_NUMBER + i;
		hi3519_av_conf->stitch_vpss_info.vpss_list[i].ext_index = CP_HI3519_AV_CODEC_BEGIN_EXT_VPSS_CHANNEL_NUMBER + i;
		// 		hi3519_av_conf->stitch_vpss_info.vpss_list[i].mode.u32Width = hi3519_av_codec->hacc.width;
		// 		hi3519_av_conf->stitch_vpss_info.vpss_list[i].mode.u32Height = hi3519_av_codec->hacc.heigth;

		hi3519_av_conf->stitch_vpss_info.vpss_list[i].mode.u32Width = ALIGN_BACK(hi3519_av_codec->hacc.width, 4);
		hi3519_av_conf->stitch_vpss_info.vpss_list[i].mode.u32Height = ALIGN_BACK(hi3519_av_codec->hacc.heigth, 4);

		if (ROTATE_90 == hi3519_av_conf->process_vpss_info[0].vpss_list[CP_HI3519_AV_CODEC_USED_VPSS_CHANNEL_NUMBER].rotate ||
			ROTATE_270 == hi3519_av_conf->process_vpss_info[0].vpss_list[CP_HI3519_AV_CODEC_USED_VPSS_CHANNEL_NUMBER].rotate) {
			hi3519_av_conf->stitch_vpss_info.vpss_list[i].mode.u32Width = ALIGN_BACK(hi3519_av_codec->hacc.heigth, 4);
			hi3519_av_conf->stitch_vpss_info.vpss_list[i].mode.u32Height = ALIGN_BACK(hi3519_av_codec->hacc.width, 4);

			if (hi3519_av_conf->stitch_vpss_info.vpss_list[i].mode.u32Width < hi3519_av_codec->hacc.heigth) {
				hi3519_av_conf->stitch_vpss_info.vpss_list[i].mode.u32Width += 4;
			}
		}

		// 		hi3519_av_conf->stitch_vpss_info.vpss_list[i].mode.u32Width = hi3519_av_conf->stitch_vpss_info.attr.u32MaxW;
		//  		hi3519_av_conf->stitch_vpss_info.vpss_list[i].mode.u32Height = hi3519_av_conf->stitch_vpss_info.attr.u32MaxH;

		hi3519_av_conf->stitch_vpss_info.vpss_list[i].attr.s32SrcFrameRate = hi3519_av_codec->hacc.fps;
		hi3519_av_conf->stitch_vpss_info.vpss_list[i].attr.s32DstFrameRate = hi3519_av_codec->hacc.fps;		hi3519_av_conf->stitch_vpss_info.vpss_list[i].crop_info.bEnable = HI_FALSE;	}

#endif

	return 0;
}

/*初始化图像处理器sttich配置信息*/
cp_int32_t init_hi3519_av_stitch_vpss_stitch_conf(cp_hi3519_av_codec_t *hi3519_av_codec, cp_hi3519_av_conf_t *hi3519_av_conf)
{
#if defined(CP_HI3519_MODE)
	SIZE_S						tmp_size = { CP_HI3519_AV_CODEC_VI_WIDTH, CP_HI3519_AV_CODEC_VI_HEIGHT };




	// 	tmp_size.u32Width = hi3519_av_conf->sensor_size.u32Width;
	// 	tmp_size.u32Height = hi3519_av_conf->sensor_size.u32Height;
	tmp_size.u32Width = hi3519_av_conf->channel_list[0].pst_size.u32Width;
	tmp_size.u32Height = hi3519_av_conf->channel_list[0].pst_size.u32Height;

	//配置stitch属性ALIGN_BACK(tmp_size.u32Width - 100, 2);
	hi3519_av_conf->stitch_vpss_info.attr.bStitchBlendEn = HI_TRUE;
	hi3519_av_conf->stitch_vpss_info.attr.enStitchBlendMode = VPSS_STITCH_BLEND_ADJUST;
	hi3519_av_conf->stitch_vpss_info.attr.stStitchBlendAttr.u32OutWidth = ALIGN_BACK(tmp_size.u32Width * 2 - 100, 4);
	hi3519_av_conf->stitch_vpss_info.attr.stStitchBlendAttr.u32OutHeight = ALIGN_BACK(tmp_size.u32Height, 4);
	hi3519_av_conf->stitch_vpss_info.attr.stStitchBlendAttr.stOverlapPoint[0].s32X = ALIGN_BACK(tmp_size.u32Width - 100, 2);
	hi3519_av_conf->stitch_vpss_info.attr.stStitchBlendAttr.stOverlapPoint[0].s32Y = 0;
	hi3519_av_conf->stitch_vpss_info.attr.stStitchBlendAttr.stOverlapPoint[1].s32X = ALIGN_BACK(tmp_size.u32Width - 100, 2);
	hi3519_av_conf->stitch_vpss_info.attr.stStitchBlendAttr.stOverlapPoint[1].s32Y = 0;
	hi3519_av_conf->stitch_vpss_info.attr.stStitchBlendAttr.stOverlapPoint[2].s32X = ALIGN_BACK(tmp_size.u32Width - 100, 2);
	hi3519_av_conf->stitch_vpss_info.attr.stStitchBlendAttr.stOverlapPoint[2].s32Y = tmp_size.u32Height - 1;
	hi3519_av_conf->stitch_vpss_info.attr.stStitchBlendAttr.stOverlapPoint[3].s32X = ALIGN_BACK(tmp_size.u32Width - 100, 2);
	hi3519_av_conf->stitch_vpss_info.attr.stStitchBlendAttr.stOverlapPoint[3].s32Y = tmp_size.u32Height - 1;

#endif

	return 0;
}

/*初始化图像处理器sttich auto配置信息*/
cp_int32_t init_hi3519_av_stitch_vpss_stitch_auto_conf(cp_hi3519_av_codec_t *hi3519_av_codec, cp_hi3519_av_conf_t *hi3519_av_conf)
{
#if defined(CP_HI3519_MODE)
	SIZE_S						tmp_size = { CP_HI3519_AV_CODEC_VI_WIDTH, CP_HI3519_AV_CODEC_VI_HEIGHT };
	cp_int32_t					tmp_int = 0;



	if (cp_hi3519_av_codec_mode_vi_fisheye_process_vpss_stitch_vpss_venc == hi3519_av_codec->hacc.mode) {
		tmp_size.u32Width = hi3519_av_conf->process_vpss_info[0].vpss_list[CP_HI3519_AV_CODEC_USED_VPSS_CHANNEL_NUMBER].mode.u32Width;
		tmp_size.u32Height = hi3519_av_conf->process_vpss_info[0].vpss_list[CP_HI3519_AV_CODEC_USED_VPSS_CHANNEL_NUMBER].mode.u32Height;
	}
	else {
		tmp_size.u32Width = hi3519_av_conf->channel_list[0].pst_size.u32Width;
		tmp_size.u32Height = hi3519_av_conf->channel_list[0].pst_size.u32Height;
	}

	tmp_size.u32Width = hi3519_av_conf->vpss_output_pst_size.u32Width;
	tmp_size.u32Height = hi3519_av_conf->vpss_output_pst_size.u32Height;

	//如果有直角，则宽高
	if (hi3519_av_conf->is_process_angle) {
		tmp_int = tmp_size.u32Width;
		tmp_size.u32Width = tmp_size.u32Height;
		tmp_size.u32Height = tmp_int;
	}

	//配置stitch属性ALIGN_BACK(tmp_size.u32Width - 100, 2);
	hi3519_av_conf->stitch_vpss_info.attr.bStitchBlendEn = HI_TRUE;
	hi3519_av_conf->stitch_vpss_info.attr.enStitchBlendMode = VPSS_STITCH_BLEND_ADJUST;
	hi3519_av_conf->stitch_vpss_info.attr.stStitchBlendAttr.u32OutWidth = ALIGN_BACK(tmp_size.u32Width * 2 - hi3519_av_codec->hacc.stitch_config.auto_config.auto_size, 4);
	hi3519_av_conf->stitch_vpss_info.attr.stStitchBlendAttr.u32OutHeight = ALIGN_BACK(tmp_size.u32Height, 4);
	hi3519_av_conf->stitch_vpss_info.attr.stStitchBlendAttr.stOverlapPoint[0].s32X = ALIGN_BACK(tmp_size.u32Width - hi3519_av_codec->hacc.stitch_config.auto_config.auto_size, 2);
	hi3519_av_conf->stitch_vpss_info.attr.stStitchBlendAttr.stOverlapPoint[0].s32Y = 0;
	hi3519_av_conf->stitch_vpss_info.attr.stStitchBlendAttr.stOverlapPoint[1].s32X = ALIGN_BACK(tmp_size.u32Width - hi3519_av_codec->hacc.stitch_config.auto_config.auto_size, 2);
	hi3519_av_conf->stitch_vpss_info.attr.stStitchBlendAttr.stOverlapPoint[1].s32Y = 0;
	hi3519_av_conf->stitch_vpss_info.attr.stStitchBlendAttr.stOverlapPoint[2].s32X = ALIGN_BACK(tmp_size.u32Width - hi3519_av_codec->hacc.stitch_config.auto_config.auto_size, 2);
	hi3519_av_conf->stitch_vpss_info.attr.stStitchBlendAttr.stOverlapPoint[2].s32Y = tmp_size.u32Height - 1;
	hi3519_av_conf->stitch_vpss_info.attr.stStitchBlendAttr.stOverlapPoint[3].s32X = ALIGN_BACK(tmp_size.u32Width - hi3519_av_codec->hacc.stitch_config.auto_config.auto_size, 2);
	hi3519_av_conf->stitch_vpss_info.attr.stStitchBlendAttr.stOverlapPoint[3].s32Y = tmp_size.u32Height - 1;

#endif

	return 0;
}

/*初始化图像处理器sttich detail配置信息*/
cp_int32_t init_hi3519_av_stitch_vpss_stitch_detail_conf(cp_hi3519_av_codec_t *hi3519_av_codec, cp_hi3519_av_conf_t *hi3519_av_conf)
{
#if defined(CP_HI3519_MODE)

	//配置stitch属性ALIGN_BACK(tmp_size.u32Width - 100, 2);
	hi3519_av_conf->stitch_vpss_info.attr.bStitchBlendEn = HI_TRUE;
	hi3519_av_conf->stitch_vpss_info.attr.enStitchBlendMode = VPSS_STITCH_BLEND_ADJUST;
	hi3519_av_conf->stitch_vpss_info.attr.stStitchBlendAttr.u32OutWidth = ALIGN_BACK(hi3519_av_codec->hacc.stitch_config.out_width - hi3519_av_codec->hacc.stitch_config.auto_config.auto_size, 4);
	hi3519_av_conf->stitch_vpss_info.attr.stStitchBlendAttr.u32OutHeight = ALIGN_BACK(hi3519_av_codec->hacc.stitch_config.out_height, 4);
	hi3519_av_conf->stitch_vpss_info.attr.stStitchBlendAttr.stOverlapPoint[0].s32X = ALIGN_BACK(hi3519_av_codec->hacc.stitch_config.overlap_points[0].x, 2);
	hi3519_av_conf->stitch_vpss_info.attr.stStitchBlendAttr.stOverlapPoint[0].s32Y = ALIGN_BACK(hi3519_av_codec->hacc.stitch_config.overlap_points[0].y, 2);
	hi3519_av_conf->stitch_vpss_info.attr.stStitchBlendAttr.stOverlapPoint[1].s32X = ALIGN_BACK(hi3519_av_codec->hacc.stitch_config.overlap_points[1].x, 2);
	hi3519_av_conf->stitch_vpss_info.attr.stStitchBlendAttr.stOverlapPoint[1].s32Y = ALIGN_BACK(hi3519_av_codec->hacc.stitch_config.overlap_points[1].y, 2);
	hi3519_av_conf->stitch_vpss_info.attr.stStitchBlendAttr.stOverlapPoint[2].s32X = ALIGN_BACK(hi3519_av_codec->hacc.stitch_config.overlap_points[2].x, 2);
	hi3519_av_conf->stitch_vpss_info.attr.stStitchBlendAttr.stOverlapPoint[2].s32Y = ALIGN_BACK(hi3519_av_codec->hacc.stitch_config.overlap_points[2].y, 2);
	hi3519_av_conf->stitch_vpss_info.attr.stStitchBlendAttr.stOverlapPoint[3].s32X = ALIGN_BACK(hi3519_av_codec->hacc.stitch_config.overlap_points[3].x, 2);
	hi3519_av_conf->stitch_vpss_info.attr.stStitchBlendAttr.stOverlapPoint[3].s32Y = ALIGN_BACK(hi3519_av_codec->hacc.stitch_config.overlap_points[3].y, 2);

#endif

	return 0;
}

/*初始化图像处理器配置信息*/
cp_int32_t init_hi3519_av_process_vpss_conf(cp_hi3519_av_codec_t *hi3519_av_codec, cp_hi3519_av_conf_t *hi3519_av_conf)
{

#if defined(CP_HI3519_MODE)
	cp_int32_t					i = 0;
	cp_int32_t					j = 0;
	cp_int32_t					tmp_sub_width = 0;
	HI_S32						tmp_ret_int = HI_FAILURE;



	for (i = 0; i < cp_ary_size(hi3519_av_conf->process_vpss_info); i++) {
		//启用扩展通道的处理
		// 		hi3519_av_conf->process_vpss_info[i].attr.u32MaxW = hi3519_av_conf->vi_output_pic_size.u32Width;
		// 		hi3519_av_conf->process_vpss_info[i].attr.u32MaxH = hi3519_av_conf->vi_output_pic_size.u32Height;

		hi3519_av_conf->process_vpss_info[i].attr.u32MaxW = hi3519_av_conf->vi_output_pic_size.u32Width;
		hi3519_av_conf->process_vpss_info[i].attr.u32MaxH = hi3519_av_conf->vi_output_pic_size.u32Width;

		if (ROTATE_90 == hi3519_av_conf->process_vpss_info[i].vpss_list[CP_HI3519_AV_CODEC_USED_VPSS_CHANNEL_NUMBER].rotate ||
			ROTATE_270 == hi3519_av_conf->process_vpss_info[i].vpss_list[CP_HI3519_AV_CODEC_USED_VPSS_CHANNEL_NUMBER].rotate) {
			//hi3519_av_conf->process_vpss_info[i].attr.u32MaxH = hi3519_av_conf->vi_output_pic_size.u32Width;
			hi3519_av_conf->process_vpss_info[i].attr.u32MaxH = hi3519_av_conf->vi_output_pic_size.u32Width;
		}

		hi3519_av_conf->process_vpss_info[i].attr.bIeEn = HI_FALSE;
		hi3519_av_conf->process_vpss_info[i].attr.bNrEn = HI_TRUE;
		hi3519_av_conf->process_vpss_info[i].attr.stNrAttr.u32RefFrameNum = 1;
		hi3519_av_conf->process_vpss_info[i].attr.enDieMode = VPSS_DIE_MODE_NODIE;
		hi3519_av_conf->process_vpss_info[i].attr.enPixFmt = PIXEL_FORMAT_YUV_SEMIPLANAR_420;
		hi3519_av_conf->process_vpss_info[i].attr.bStitchBlendEn = HI_FALSE;
		hi3519_av_conf->process_vpss_info[i].index = i + 1;
		for (j = 0; j < cp_ary_size(hi3519_av_conf->process_vpss_info[i].vpss_list); j++) {
			hi3519_av_conf->process_vpss_info[i].vpss_list[j].index = CP_HI3519_AV_CODEC_BEGIN_VPSS_CHANNEL_NUMBER + j;
			hi3519_av_conf->process_vpss_info[i].vpss_list[j].mode.enChnMode = VPSS_CHN_MODE_USER;
			hi3519_av_conf->process_vpss_info[i].vpss_list[j].mode.enPixelFormat = PIXEL_FORMAT_YUV_SEMIPLANAR_420;
			hi3519_av_conf->process_vpss_info[i].vpss_list[j].ext_index = CP_HI3519_AV_CODEC_BEGIN_EXT_VPSS_CHANNEL_NUMBER + j;
			hi3519_av_conf->process_vpss_info[i].vpss_list[j].mode.u32Width = hi3519_av_conf->vpss_output_pst_size.u32Width;
			hi3519_av_conf->process_vpss_info[i].vpss_list[j].mode.u32Height = hi3519_av_conf->vpss_output_pst_size.u32Height;
			hi3519_av_conf->process_vpss_info[i].vpss_list[j].attr.s32SrcFrameRate = hi3519_av_codec->hacc.fps;
			hi3519_av_conf->process_vpss_info[i].vpss_list[j].attr.s32DstFrameRate = hi3519_av_codec->hacc.fps;			hi3519_av_conf->process_vpss_info[i].vpss_list[j].crop_info.bEnable = HI_FALSE;		}
	}

#endif

	return 0;
}

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: init_hi3519_av_stitch_correction_attr
*
* 函数说明: 设置拼接前校正属性
*
* 参    数: cp_hi3519_av_codec_t * hi3519_av_codec						[in]参数说明
*
* 返 回 值: cp_int32_t
*           0  : 成功
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2016-12-24 16:03:15
******************************************************************************************************/
cp_int32_t	init_hi3519_av_stitch_correction_attr(cp_hi3519_av_codec_t *hi3519_av_codec, cp_hi3519_av_conf_t *hi3519_av_conf)
{
#if defined(CP_HI3519_MODE)
	HI_S32									tmp_ret_int = 0;



	tmp_ret_int = init_hi3519_av_stitch_correction_attr_ldc(hi3519_av_codec, hi3519_av_conf);
	if (tmp_ret_int)
	{
		cp_module_log(error, hi3519_av_codec,
			"init_hi3519_av_stitch_correction_attr_ldc() failed.");
		return -1;
	}

	tmp_ret_int = init_hi3519_av_stitch_correction_attr_cylind(hi3519_av_codec, hi3519_av_conf);
	if (tmp_ret_int)
	{
		cp_module_log(error, hi3519_av_codec,
			"init_hi3519_av_stitch_correction_attr_cylind() failed.");
		return -1;
	}

#endif
	return 0;
}

/*双路拼接时stitching LDC桶形校正时的结构体*/
cp_int32_t init_hi3519_av_stitch_correction_attr_ldc(cp_hi3519_av_codec_t *hi3519_av_codec, cp_hi3519_av_conf_t *hi3519_av_conf)
{
#if defined(CP_HI3519_MODE)
	cp_int32_t								i = 0;
	HI_BOOL									tmp_ret_bool = HI_FALSE;
	HI_S32									tmp_ret_int = 0;
	cp_hi3519_av_conf_t						*tmp_conf = hi3519_av_codec->av_conf;


	if (SAMPLE_SENSOR_DOUBLE != hi3519_av_codec->av_conf->channel_list[0].channel_config.enSnsNum) {
		return 0;
	}

	//配置所有通道1
	for (i = 0; i < cp_ary_size(tmp_conf->channel_list); i++) {
		tmp_conf->channel_list[i].stitch_attr.stLdcAttr.bEnable = HI_FALSE;
		tmp_conf->channel_list[i].stitch_attr.stLdcAttr.stAttr.s32Ratio = 100;
		tmp_conf->channel_list[i].stitch_attr.stLdcAttr.stAttr.enViewType = LDC_VIEW_TYPE_ALL;
		tmp_conf->channel_list[i].stitch_attr.stLdcAttr.stAttr.s32CenterXOffset = 0;
		tmp_conf->channel_list[i].stitch_attr.stLdcAttr.stAttr.s32CenterYOffset = 0;
		tmp_conf->channel_list[i].stitch_attr.stLdcAttr.stAttr.s32MinRatio = -150;

		tmp_conf->channel_list[i].stitch_attr.stPMFAttr.bEnable = HI_TRUE;
		tmp_conf->channel_list[i].stitch_attr.stPMFAttr.as32PMFCoef[0] = 524288;
		tmp_conf->channel_list[i].stitch_attr.stPMFAttr.as32PMFCoef[1] = 0;
		tmp_conf->channel_list[i].stitch_attr.stPMFAttr.as32PMFCoef[2] = 0;
		tmp_conf->channel_list[i].stitch_attr.stPMFAttr.as32PMFCoef[3] = 0;
		tmp_conf->channel_list[i].stitch_attr.stPMFAttr.as32PMFCoef[4] = 524288;
		tmp_conf->channel_list[i].stitch_attr.stPMFAttr.as32PMFCoef[5] = 0;
		tmp_conf->channel_list[i].stitch_attr.stPMFAttr.as32PMFCoef[6] = 0;
		tmp_conf->channel_list[i].stitch_attr.stPMFAttr.as32PMFCoef[7] = 0;
		tmp_conf->channel_list[i].stitch_attr.stPMFAttr.as32PMFCoef[8] = 524288;
		//tmp_conf->channel_list[i].stitch_attr.stPMFAttr.stDestSize.u32Width = tmp_conf->channel_list[i].pst_size.u32Width;
		//tmp_conf->channel_list[i].stitch_attr.stPMFAttr.stDestSize.u32Height = tmp_conf->channel_list[i].pst_size.u32Height;
		tmp_conf->channel_list[i].stitch_attr.stPMFAttr.stDestSize.u32Width = 2592;
		tmp_conf->channel_list[i].stitch_attr.stPMFAttr.stDestSize.u32Height = 1520;
	}

#endif
	return 0;
}

/*双路拼接时stitching CYLIND柱面校正时的结构体*/
cp_int32_t init_hi3519_av_stitch_correction_attr_cylind(cp_hi3519_av_codec_t *hi3519_av_codec, cp_hi3519_av_conf_t *hi3519_av_conf)
{
#if defined(CP_HI3519_MODE)
	cp_int32_t								i = 0;
	HI_BOOL									tmp_ret_bool = HI_FALSE;
	HI_S32									tmp_ret_int = 0;
	cp_hi3519_av_conf_t						*tmp_conf = hi3519_av_codec->av_conf;



	//配置所有通道1
	for (i = 0; i < cp_ary_size(tmp_conf->channel_list); i++) {
		if (!hi3519_av_codec->hacc.stitch_config.csc[i].is_used) {
			continue;
		}
		tmp_conf->channel_list[i].stitch_attr.stCylindAttr.bEnable = HI_TRUE;
		tmp_conf->channel_list[i].stitch_attr.stCylindAttr.stFisheyeCylindAttr.s32CenterXOffset = 
			hi3519_av_codec->hacc.stitch_config.csc[i].center_horizontal_offset;
		tmp_conf->channel_list[i].stitch_attr.stCylindAttr.stFisheyeCylindAttr.s32CenterYOffset = 
			hi3519_av_codec->hacc.stitch_config.csc[i].center_vertical_offset;
		tmp_conf->channel_list[i].stitch_attr.stCylindAttr.stFisheyeCylindAttr.s32Ratio =
			hi3519_av_codec->hacc.stitch_config.csc[i].ratio;
	}

#endif
	return 0;

}

/*初始化hi3519 info 设备*/
cp_int32_t init_hi3519_av_info_mode_vi_venc(cp_hi3519_av_codec_t *hi3519_av_codec, cp_hi3519_av_conf_t *hi3519_av_conf)
{
	cp_int32_t						tmp_ret_int = 0;



	//初始化系统信息
	tmp_ret_int = hi3519_av_system_init(hi3519_av_codec, hi3519_av_codec->av_conf);
	if (tmp_ret_int) {
		cp_module_log(error, hi3519_av_codec, "hi3519_av_system_init() error.");
		return -1;
	}

	//初始化VI配置信息
	tmp_ret_int = init_hi3519_av_vi_conf(hi3519_av_codec, hi3519_av_codec->av_conf);
	if (tmp_ret_int) {
		cp_module_log(error, hi3519_av_codec, "init_hi3519_av_vi_conf() error.");
		return -1;
	}

#if defined(CP_HI3519_MODE)

	hi3519_av_conf->vi_output_pic_size.u32Width = hi3519_av_conf->sensor_size.u32Width;
	hi3519_av_conf->vi_output_pic_size.u32Height = hi3519_av_conf->sensor_size.u32Height;;
	hi3519_av_conf->vpss_output_pst_size.u32Width = hi3519_av_conf->sensor_size.u32Width;
	hi3519_av_conf->vpss_output_pst_size.u32Height = hi3519_av_conf->sensor_size.u32Height;
	hi3519_av_conf->stitch_input_pst_size.u32Width = hi3519_av_conf->sensor_size.u32Width;
	hi3519_av_conf->stitch_input_pst_size.u32Height = hi3519_av_conf->sensor_size.u32Height;
#endif

#if 0
	//初始化vi fisheye配置信息
	tmp_ret_int = init_hi3519_av_fisheye_conf(hi3519_av_codec, hi3519_av_codec->av_conf);
#endif
	//初始化vi fisheye配置信息
	tmp_ret_int = init_hi3519_av_fisheye_conf_from_config(hi3519_av_codec, hi3519_av_codec->av_conf, cp_fisheye_type_vi);
	if (tmp_ret_int) {
		cp_module_log(error, hi3519_av_codec, "init_hi3519_av_fisheye_conf_from_config() error.");
		return -1;
	}

	//初始化EXT VPSS配置信息
	tmp_ret_int = init_hi3519_av_process_vpss_conf(hi3519_av_codec, hi3519_av_codec->av_conf);
	if (tmp_ret_int) {
		cp_module_log(error, hi3519_av_codec, "init_hi3519_av_process_vpss_conf() error.");
		return -1;
	}

	//初始化VPSS配置信息
	tmp_ret_int = init_hi3519_av_stitch_vpss_conf(hi3519_av_codec, hi3519_av_codec->av_conf);
	if (tmp_ret_int) {
		cp_module_log(error, hi3519_av_codec, "init_hi3519_av_stitch_vpss_conf() error.");
		return -1;
	}

	//初始化VENC配置信息
	tmp_ret_int = init_hi3519_av_venc_conf(hi3519_av_codec, hi3519_av_codec->av_conf);
	if (tmp_ret_int) {
		cp_module_log(error, hi3519_av_codec, "init_hi3519_av_venc_conf() error.");
		return -1;
	}

	return 0;
}

/*初始化hi3519 info 设备*/
cp_int32_t init_hi3519_av_info_mode_vi_stitch_vpss_venc(cp_hi3519_av_codec_t *hi3519_av_codec, cp_hi3519_av_conf_t *hi3519_av_conf)
{
	cp_int32_t						tmp_ret_int = 0;



	//初始化系统信息
	tmp_ret_int = hi3519_av_system_init(hi3519_av_codec, hi3519_av_codec->av_conf);
	if (tmp_ret_int) {
		cp_module_log(error, hi3519_av_codec, "hi3519_av_system_init() error.");
		return -1;
	}

	//初始化VI配置信息
	tmp_ret_int = init_hi3519_av_vi_conf(hi3519_av_codec, hi3519_av_codec->av_conf);
	if (tmp_ret_int) {
		cp_module_log(error, hi3519_av_codec, "init_hi3519_av_vi_conf() error.");
		return -1;
	}

#if defined(CP_HI3519_MODE)

	hi3519_av_conf->vi_output_pic_size.u32Width = hi3519_av_conf->sensor_size.u32Width;
	hi3519_av_conf->vi_output_pic_size.u32Height = hi3519_av_conf->sensor_size.u32Height;;
	hi3519_av_conf->vpss_output_pst_size.u32Width = hi3519_av_conf->sensor_size.u32Width;
	hi3519_av_conf->vpss_output_pst_size.u32Height = hi3519_av_conf->sensor_size.u32Height;
	hi3519_av_conf->stitch_input_pst_size.u32Width = hi3519_av_conf->sensor_size.u32Width;
	hi3519_av_conf->stitch_input_pst_size.u32Height = hi3519_av_conf->sensor_size.u32Height;
#endif

#if 0
	//初始化vi fisheye配置信息
	tmp_ret_int = init_hi3519_av_fisheye_conf(hi3519_av_codec, hi3519_av_codec->av_conf);
#endif
	//初始化vi fisheye配置信息
	tmp_ret_int = init_hi3519_av_fisheye_conf_from_config(hi3519_av_codec, hi3519_av_codec->av_conf, cp_fisheye_type_vi);
	if (tmp_ret_int) {
		cp_module_log(error, hi3519_av_codec, "init_hi3519_av_fisheye_conf_from_config() error.");
		return -1;
	}

	//初始化EXT VPSS配置信息
	tmp_ret_int = init_hi3519_av_process_vpss_conf(hi3519_av_codec, hi3519_av_codec->av_conf);
	if (tmp_ret_int) {
		cp_module_log(error, hi3519_av_codec, "init_hi3519_av_process_vpss_conf() error.");
		return -1;
	}

	//初始化VPSS配置信息
	tmp_ret_int = init_hi3519_av_stitch_vpss_conf(hi3519_av_codec, hi3519_av_codec->av_conf);
	if (tmp_ret_int) {
		cp_module_log(error, hi3519_av_codec, "init_hi3519_av_stitch_vpss_conf() error.");
		return -1;
	}

	//初始化VENC配置信息
	tmp_ret_int = init_hi3519_av_venc_conf(hi3519_av_codec, hi3519_av_codec->av_conf);
	if (tmp_ret_int) {
		cp_module_log(error, hi3519_av_codec, "init_hi3519_av_venc_conf() error.");
		return -1;
	}

	return 0;
}

/*初始化hi3519 info 设备*/
cp_int32_t init_hi3519_av_info_mode_vi_fisheye_stitch_vpss_venc(cp_hi3519_av_codec_t *hi3519_av_codec, cp_hi3519_av_conf_t *hi3519_av_conf)
{
	cp_int32_t						i = 0;
	cp_int32_t						tmp_ret_int = 0;
	cp_int32_t						tmp_crop_x_int = 0;



	//初始化系统信息
	tmp_ret_int = hi3519_av_system_init(hi3519_av_codec, hi3519_av_codec->av_conf);
	if (tmp_ret_int) {
		cp_module_log(error, hi3519_av_codec, "hi3519_av_system_init() error.");
		return -1;
	}

	//初始化VI配置信息
	tmp_ret_int = init_hi3519_av_vi_conf(hi3519_av_codec, hi3519_av_codec->av_conf);
	if (tmp_ret_int) {
		cp_module_log(error, hi3519_av_codec, "init_hi3519_av_vi_conf() error.");
		return -1;
	}

#if defined(CP_HI3519_MODE)

	hi3519_av_conf->vi_output_pic_size.u32Width = 1920;
	hi3519_av_conf->vi_output_pic_size.u32Height = 1520;
	hi3519_av_conf->vpss_output_pst_size.u32Width = 1920;
	hi3519_av_conf->vpss_output_pst_size.u32Height = 1520;
	hi3519_av_conf->stitch_input_pst_size.u32Width = 1920;
	hi3519_av_conf->stitch_input_pst_size.u32Height = 1520;

	if (SENSOR_TYPE == OMNIVISION_OV4689_MIPI_4M_30FPS) {
		for (i = 0; i < cp_ary_size(hi3519_av_conf->channel_list); i++) {
			hi3519_av_conf->channel_list[i].is_used_crop = HI_TRUE;

			//因为vpss stitch是存在最大值4096 * 4096的限制，所以stitch时单个图像不能大于4096 / 2
			//这里使用高度值,形成一个正方形图像
			tmp_crop_x_int = (hi3519_av_conf->channel_list[i].pst_size.u32Width - 1920) / 2;
			hi3519_av_conf->channel_list[i].cap_rect.s32X = ALIGN_BACK(tmp_crop_x_int, 2);
			hi3519_av_conf->channel_list[i].cap_rect.s32Y = ALIGN_BACK(0, 4);
			hi3519_av_conf->channel_list[i].cap_rect.u32Width = ALIGN_BACK(1920, 2);
			hi3519_av_conf->channel_list[i].cap_rect.u32Height = ALIGN_BACK(hi3519_av_conf->channel_list[i].pst_size.u32Height, 4);

			hi3519_av_conf->channel_list[i].pst_size.u32Width = hi3519_av_conf->vi_output_pic_size.u32Width;
			hi3519_av_conf->channel_list[i].pst_size.u32Height = hi3519_av_conf->vi_output_pic_size.u32Height;
		}
	}

#endif

#if 0
	//初始化vi fisheye配置信息
	tmp_ret_int = init_hi3519_av_fisheye_conf(hi3519_av_codec, hi3519_av_codec->av_conf);
#endif
	//初始化vi fisheye配置信息
	tmp_ret_int = init_hi3519_av_fisheye_conf_from_config(hi3519_av_codec, hi3519_av_codec->av_conf, cp_fisheye_type_vi);
	if (tmp_ret_int) {
		cp_module_log(error, hi3519_av_codec, "init_hi3519_av_fisheye_conf_from_config() error.");
		return -1;
	}

	//初始化EXT VPSS配置信息
	tmp_ret_int = init_hi3519_av_process_vpss_conf(hi3519_av_codec, hi3519_av_codec->av_conf);
	if (tmp_ret_int) {
		cp_module_log(error, hi3519_av_codec, "init_hi3519_av_process_vpss_conf() error.");
		return -1;
	}

	//初始化VPSS配置信息
	tmp_ret_int = init_hi3519_av_stitch_vpss_conf(hi3519_av_codec, hi3519_av_codec->av_conf);
	if (tmp_ret_int) {
		cp_module_log(error, hi3519_av_codec, "init_hi3519_av_stitch_vpss_conf() error.");
		return -1;
	}

	//初始化VENC配置信息
	tmp_ret_int = init_hi3519_av_venc_conf(hi3519_av_codec, hi3519_av_codec->av_conf);
	if (tmp_ret_int) {
		cp_module_log(error, hi3519_av_codec, "init_hi3519_av_venc_conf() error.");
		return -1;
	}

	return 0;
}

/*初始化hi3519 info 设备*/
cp_int32_t init_hi3519_av_info_mode_vi_fisheye_process_vpss_venc(cp_hi3519_av_codec_t *hi3519_av_codec, cp_hi3519_av_conf_t *hi3519_av_conf)
{
	cp_int32_t						i = 0;
	cp_int32_t						tmp_ret_int = 0;
	cp_int32_t						tmp_crop_x_int = 0;



	//初始化系统信息
	tmp_ret_int = hi3519_av_system_init(hi3519_av_codec, hi3519_av_codec->av_conf);
	if (tmp_ret_int) {
		cp_module_log(error, hi3519_av_codec, "hi3519_av_system_init() error.");
		return -1;
	}

	//初始化VI配置信息
	tmp_ret_int = init_hi3519_av_vi_conf(hi3519_av_codec, hi3519_av_codec->av_conf);
	if (tmp_ret_int) {
		cp_module_log(error, hi3519_av_codec, "init_hi3519_av_vi_conf() error.");
		return -1;
	}

#if defined(CP_HI3519_MODE)

	hi3519_av_conf->vi_output_pic_size.u32Width = 1920;
	hi3519_av_conf->vi_output_pic_size.u32Height = 1520;
	hi3519_av_conf->vpss_output_pst_size.u32Width = 1920;
	hi3519_av_conf->vpss_output_pst_size.u32Height = 1520;
	hi3519_av_conf->stitch_input_pst_size.u32Width = 1920;
	hi3519_av_conf->stitch_input_pst_size.u32Height = 1520;

	if (SENSOR_TYPE == OMNIVISION_OV4689_MIPI_4M_30FPS) {
		for (i = 0; i < cp_ary_size(hi3519_av_conf->channel_list); i++) {
			hi3519_av_conf->channel_list[i].is_used_crop = HI_TRUE;

			//因为vpss stitch是存在最大值4096 * 4096的限制，所以stitch时单个图像不能大于4096 / 2
			//这里使用高度值,形成一个正方形图像
			tmp_crop_x_int = (hi3519_av_conf->channel_list[i].pst_size.u32Width - 1920) / 2;
			hi3519_av_conf->channel_list[i].cap_rect.s32X = ALIGN_BACK(tmp_crop_x_int, 2);
			hi3519_av_conf->channel_list[i].cap_rect.s32Y = ALIGN_BACK(0, 4);
			hi3519_av_conf->channel_list[i].cap_rect.u32Width = ALIGN_BACK(1920, 2);
			hi3519_av_conf->channel_list[i].cap_rect.u32Height = ALIGN_BACK(hi3519_av_conf->channel_list[i].pst_size.u32Height, 4);

			hi3519_av_conf->channel_list[i].pst_size.u32Width = hi3519_av_conf->vi_output_pic_size.u32Width;
			hi3519_av_conf->channel_list[i].pst_size.u32Height = hi3519_av_conf->vi_output_pic_size.u32Height;
		}
	}

	for (i = 0; i < cp_ary_size(hi3519_av_conf->process_vpss_info); i++) {
		if (ROTATE_90 == hi3519_av_conf->process_vpss_info[i].vpss_list[CP_HI3519_AV_CODEC_USED_VPSS_CHANNEL_NUMBER].rotate ||
			ROTATE_270 == hi3519_av_conf->process_vpss_info[i].vpss_list[CP_HI3519_AV_CODEC_USED_VPSS_CHANNEL_NUMBER].rotate) {
			//  			hi3519_av_conf->vpss_output_pst_size.u32Width = 1920;
			//  			hi3519_av_conf->vpss_output_pst_size.u32Height = 1520;
			//  			hi3519_av_conf->stitch_input_pst_size.u32Width = 1520;
			//  			hi3519_av_conf->stitch_input_pst_size.u32Height = 1920;

			hi3519_av_conf->vpss_output_pst_size.u32Width = 1520;
			hi3519_av_conf->vpss_output_pst_size.u32Height = 1520;
			hi3519_av_conf->stitch_input_pst_size.u32Width = 1520;
			hi3519_av_conf->stitch_input_pst_size.u32Height = 1520;

			hi3519_av_conf->vpss_output_pst_size.u32Width = hi3519_av_codec->hacc.width;
			hi3519_av_conf->vpss_output_pst_size.u32Height = hi3519_av_codec->hacc.heigth / 2;
			hi3519_av_conf->stitch_input_pst_size.u32Width = hi3519_av_codec->hacc.heigth / 2;
			hi3519_av_conf->stitch_input_pst_size.u32Height = hi3519_av_codec->hacc.width;
		}
	}

#endif

#if 0
	//初始化vi fisheye配置信息
	tmp_ret_int = init_hi3519_av_fisheye_conf(hi3519_av_codec, hi3519_av_codec->av_conf);
#endif
	//初始化vi fisheye配置信息
	tmp_ret_int = init_hi3519_av_fisheye_conf_from_config(hi3519_av_codec, hi3519_av_codec->av_conf, cp_fisheye_type_vi);
	if (tmp_ret_int) {
		cp_module_log(error, hi3519_av_codec, "init_hi3519_av_fisheye_conf_from_config() error.");
		return -1;
	}

	//初始化EXT VPSS配置信息
	tmp_ret_int = init_hi3519_av_process_vpss_conf(hi3519_av_codec, hi3519_av_codec->av_conf);
	if (tmp_ret_int) {
		cp_module_log(error, hi3519_av_codec, "init_hi3519_av_process_vpss_conf() error.");
		return -1;
	}

	//初始化VPSS配置信息
	tmp_ret_int = init_hi3519_av_stitch_vpss_conf(hi3519_av_codec, hi3519_av_codec->av_conf);
	if (tmp_ret_int) {
		cp_module_log(error, hi3519_av_codec, "init_hi3519_av_stitch_vpss_conf() error.");
		return -1;
	}

	//初始化VENC配置信息
	tmp_ret_int = init_hi3519_av_venc_conf(hi3519_av_codec, hi3519_av_codec->av_conf);
	if (tmp_ret_int) {
		cp_module_log(error, hi3519_av_codec, "init_hi3519_av_venc_conf() error.");
		return -1;
	}

	return 0;
}

/*初始化hi3519 info 设备*/
cp_int32_t init_hi3519_av_info_mode_vi_fisheye_process_vpss_stitch_vpss_venc(cp_hi3519_av_codec_t *hi3519_av_codec, cp_hi3519_av_conf_t *hi3519_av_conf)
{
	cp_int32_t						i = 0;
	cp_int32_t						tmp_ret_int = 0;
	cp_int32_t						tmp_crop_x_int = 0;
	cp_int32_t						tmp_width_int = 1920;
	cp_int32_t						tmp_height_int = 1520;
	cp_int32_t						tmp_stitch_width = 0;



	//初始化系统信息
	tmp_ret_int = hi3519_av_system_init(hi3519_av_codec, hi3519_av_codec->av_conf);
	if (tmp_ret_int) {
		cp_module_log(error, hi3519_av_codec, "hi3519_av_system_init() error.");
		return -1;
	}

	//初始化VI配置信息
	tmp_ret_int = init_hi3519_av_vi_conf(hi3519_av_codec, hi3519_av_codec->av_conf);
	if (tmp_ret_int) {
		cp_module_log(error, hi3519_av_codec, "init_hi3519_av_vi_conf() error.");
		return -1;
	}

#if defined(CP_HI3519_MODE)


	tmp_width_int = hi3519_av_codec->hacc.width > tmp_width_int ? hi3519_av_codec->hacc.width : tmp_width_int;
	hi3519_av_conf->vi_output_pic_size.u32Width = tmp_width_int;
	hi3519_av_conf->vi_output_pic_size.u32Height = tmp_height_int;
	hi3519_av_conf->vpss_output_pst_size.u32Width = tmp_width_int;
	hi3519_av_conf->vpss_output_pst_size.u32Height = tmp_height_int;
	hi3519_av_conf->stitch_input_pst_size.u32Width = tmp_width_int;
	hi3519_av_conf->stitch_input_pst_size.u32Height = tmp_height_int;

	if (SENSOR_TYPE == OMNIVISION_OV4689_MIPI_4M_30FPS) {
		for (i = 0; i < cp_ary_size(hi3519_av_conf->channel_list); i++) {
			hi3519_av_conf->channel_list[i].is_used_crop = HI_TRUE;

			//因为vpss stitch是存在最大值4096 * 4096的限制，所以stitch时单个图像不能大于4096 / 2
			//这里使用高度值,形成一个正方形图像
			tmp_crop_x_int = (hi3519_av_conf->channel_list[i].pst_size.u32Width - tmp_width_int) / 2;
			hi3519_av_conf->channel_list[i].cap_rect.s32X = ALIGN_BACK(tmp_crop_x_int, 2);
			hi3519_av_conf->channel_list[i].cap_rect.s32Y = ALIGN_BACK(0, 4);
			hi3519_av_conf->channel_list[i].cap_rect.u32Width = ALIGN_BACK(tmp_width_int, 2);
			hi3519_av_conf->channel_list[i].cap_rect.u32Height = ALIGN_BACK(hi3519_av_conf->channel_list[i].pst_size.u32Height, 4);

			hi3519_av_conf->channel_list[i].pst_size.u32Width = hi3519_av_conf->vi_output_pic_size.u32Width;
			hi3519_av_conf->channel_list[i].pst_size.u32Height = hi3519_av_conf->vi_output_pic_size.u32Height;
		}
	}

	for (i = 0; i < cp_ary_size(hi3519_av_conf->process_vpss_info); i++) {
		if (ROTATE_90 == hi3519_av_conf->process_vpss_info[i].vpss_list[CP_HI3519_AV_CODEC_USED_VPSS_CHANNEL_NUMBER].rotate ||
			ROTATE_270 == hi3519_av_conf->process_vpss_info[i].vpss_list[CP_HI3519_AV_CODEC_USED_VPSS_CHANNEL_NUMBER].rotate) {
			//hi3519_av_conf->vpss_output_pst_size.u32Width = 1920;
			//hi3519_av_conf->vpss_output_pst_size.u32Height = 1520;
			//hi3519_av_conf->stitch_input_pst_size.u32Width = 1520;
			//hi3519_av_conf->stitch_input_pst_size.u32Height = 1920;

			// 			hi3519_av_conf->vpss_output_pst_size.u32Width = 1280;
			// 			hi3519_av_conf->vpss_output_pst_size.u32Height = 1280;
			// 			hi3519_av_conf->stitch_input_pst_size.u32Width = 1280;
			// 			hi3519_av_conf->stitch_input_pst_size.u32Height = 1280;

			hi3519_av_conf->vpss_output_pst_size.u32Width = ALIGN_BACK(hi3519_av_codec->hacc.width, 4);
			hi3519_av_conf->vpss_output_pst_size.u32Height = ALIGN_BACK(hi3519_av_codec->hacc.heigth / 2, 4);
			hi3519_av_conf->stitch_input_pst_size.u32Width = ALIGN_BACK(hi3519_av_codec->hacc.heigth / 2, 4);
			hi3519_av_conf->stitch_input_pst_size.u32Height = ALIGN_BACK(hi3519_av_codec->hacc.width, 4);

			if (hi3519_av_codec->hacc.stitch_config.auto_config.is_auto) {
				tmp_stitch_width = ALIGN_BACK(((hi3519_av_codec->hacc.heigth + hi3519_av_codec->hacc.stitch_config.auto_config.auto_size ) / 2), 4);
				if (tmp_stitch_width != ((hi3519_av_codec->hacc.heigth + hi3519_av_codec->hacc.stitch_config.auto_config.auto_size ) / 2)) {
					tmp_stitch_width += 4;
				}
			} else {

			}
		} else {
			if (hi3519_av_codec->hacc.stitch_config.auto_config.is_auto) {
				tmp_stitch_width = ALIGN_BACK(((hi3519_av_codec->hacc.width + hi3519_av_codec->hacc.stitch_config.auto_config.auto_size ) / 2), 4);
				if (tmp_stitch_width != ((hi3519_av_codec->hacc.width + hi3519_av_codec->hacc.stitch_config.auto_config.auto_size ) / 2)) {
					tmp_stitch_width += 4;
				}
			} else {

			}
		}
	}

	hi3519_av_conf->vpss_output_pst_size.u32Height = tmp_stitch_width;
	hi3519_av_conf->stitch_input_pst_size.u32Width = tmp_stitch_width;

#endif

#if 0
	//初始化vi fisheye配置信息
	tmp_ret_int = init_hi3519_av_fisheye_conf(hi3519_av_codec, hi3519_av_codec->av_conf);
#endif
	//初始化vi fisheye配置信息
	tmp_ret_int = init_hi3519_av_fisheye_conf_from_config(hi3519_av_codec, hi3519_av_codec->av_conf, cp_fisheye_type_vi);
	if (tmp_ret_int) {
		cp_module_log(error, hi3519_av_codec, "init_hi3519_av_fisheye_conf_from_config() error.");
		return -1;
	}

	//初始化EXT VPSS配置信息
	tmp_ret_int = init_hi3519_av_process_vpss_conf(hi3519_av_codec, hi3519_av_codec->av_conf);
	if (tmp_ret_int) {
		cp_module_log(error, hi3519_av_codec, "init_hi3519_av_process_vpss_conf() error.");
		return -1;
	}

	//初始化VPSS配置信息
	tmp_ret_int = init_hi3519_av_stitch_vpss_conf(hi3519_av_codec, hi3519_av_codec->av_conf);
	if (tmp_ret_int) {
		cp_module_log(error, hi3519_av_codec, "init_hi3519_av_stitch_vpss_conf() error.");
		return -1;
	}

	//初始化VENC配置信息
	tmp_ret_int = init_hi3519_av_venc_conf(hi3519_av_codec, hi3519_av_codec->av_conf);
	if (tmp_ret_int) {
		cp_module_log(error, hi3519_av_codec, "init_hi3519_av_venc_conf() error.");
		return -1;
	}

	return 0;
}

/*初始化hi3519 info 设备*/
cp_int32_t init_hi3519_av_info_mode_vi_process_vpss_fisheye_stitch_vpss_venc(cp_hi3519_av_codec_t *hi3519_av_codec, cp_hi3519_av_conf_t *hi3519_av_conf)
{
	cp_int32_t						i = 0;
	cp_int32_t						j = 0;
	cp_int32_t						tmp_sub_width = 0;
	cp_int32_t						tmp_ret_int = 0;
	cp_int32_t						tmp_crop_x_int = 0;



	//初始化系统信息
	tmp_ret_int = hi3519_av_system_init(hi3519_av_codec, hi3519_av_codec->av_conf);
	if (tmp_ret_int) {
		cp_module_log(error, hi3519_av_codec, "hi3519_av_system_init() error.");
		return -1;
	}

	//初始化VI配置信息
	tmp_ret_int = init_hi3519_av_vi_conf(hi3519_av_codec, hi3519_av_codec->av_conf);
	if (tmp_ret_int) {
		cp_module_log(error, hi3519_av_codec, "init_hi3519_av_vi_conf() error.");
		return -1;
	}

#if defined(CP_HI3519_MODE)

	hi3519_av_conf->vi_output_pic_size.u32Width = 1920;
	hi3519_av_conf->vi_output_pic_size.u32Height = 1080;
	hi3519_av_conf->vpss_output_pst_size.u32Width = 1920;
	hi3519_av_conf->vpss_output_pst_size.u32Height = 1080;
	hi3519_av_conf->stitch_input_pst_size.u32Width = 1920;
	hi3519_av_conf->stitch_input_pst_size.u32Height = 1080;

	// 	if (SENSOR_TYPE == OMNIVISION_OV4689_MIPI_4M_30FPS) {
	// 		for (i = 0; i < cp_ary_size(hi3519_av_conf->channel_list); i++) {
	// 			hi3519_av_conf->channel_list[i].is_used_crop = HI_TRUE;
	// 
	// 			//因为vpss stitch是存在最大值4096 * 4096的限制，所以stitch时单个图像不能大于4096 / 2
	// 			//这里使用高度值,形成一个正方形图像
	// 			tmp_crop_x_int = (hi3519_av_conf->channel_list[i].pst_size.u32Width - 1920) / 2;
	// 			hi3519_av_conf->channel_list[i].cap_rect.s32X = ALIGN_BACK(tmp_crop_x_int, 2);
	// 			hi3519_av_conf->channel_list[i].cap_rect.s32Y = ALIGN_BACK(0, 4);
	// 			hi3519_av_conf->channel_list[i].cap_rect.u32Width = ALIGN_BACK(1920, 2);
	// 			hi3519_av_conf->channel_list[i].cap_rect.u32Height = ALIGN_BACK(hi3519_av_conf->channel_list[i].pst_size.u32Height, 4);
	// 
	// 			hi3519_av_conf->channel_list[i].pst_size.u32Width = hi3519_av_conf->vi_output_pic_size.u32Width;
	// 			hi3519_av_conf->channel_list[i].pst_size.u32Height = hi3519_av_conf->vi_output_pic_size.u32Height;
	// 		}
	// 	}
#endif

#if 0
	//初始化vi fisheye配置信息
	tmp_ret_int = init_hi3519_av_fisheye_conf(hi3519_av_codec, hi3519_av_codec->av_conf);
#endif

	//初始化vi fisheye配置信息
	tmp_ret_int = init_hi3519_av_fisheye_conf_from_config(hi3519_av_codec, hi3519_av_codec->av_conf, cp_fisheye_type_vpss);
	if (tmp_ret_int) {
		cp_module_log(error, hi3519_av_codec, "init_hi3519_av_fisheye_conf_from_config() error.");
		return -1;
	}

	//初始化EXT VPSS配置信息
	tmp_ret_int = init_hi3519_av_process_vpss_conf(hi3519_av_codec, hi3519_av_codec->av_conf);
	if (tmp_ret_int) {
		cp_module_log(error, hi3519_av_codec, "init_hi3519_av_process_vpss_conf() error.");
		return -1;
	}

#if defined(CP_HI3519_MODE)
	for (i = 0; i < cp_ary_size(hi3519_av_conf->process_vpss_info); i++) {
		//启用扩展通道的处理
		// 		hi3519_av_conf->process_vpss_info[i].vpss_list[j].mode.u32Width = hi3519_av_conf->channel_list[j].pst_size.u32Width;
		// 		hi3519_av_conf->process_vpss_info[i].vpss_list[j].mode.u32Height = hi3519_av_conf->channel_list[j].pst_size.u32Height;

		hi3519_av_conf->process_vpss_info[i].vpss_list[j].mode.u32Width = hi3519_av_conf->vi_output_pic_size.u32Width;
		hi3519_av_conf->process_vpss_info[i].vpss_list[j].mode.u32Height = hi3519_av_conf->vi_output_pic_size.u32Height;

	}
#endif

	//初始化VPSS配置信息
	tmp_ret_int = init_hi3519_av_stitch_vpss_conf(hi3519_av_codec, hi3519_av_codec->av_conf);
	if (tmp_ret_int) {
		cp_module_log(error, hi3519_av_codec, "init_hi3519_av_stitch_vpss_conf() error.");
		return -1;
	}

	//初始化VENC配置信息
	tmp_ret_int = init_hi3519_av_venc_conf(hi3519_av_codec, hi3519_av_codec->av_conf);
	if (tmp_ret_int) {
		cp_module_log(error, hi3519_av_codec, "init_hi3519_av_venc_conf() error.");
		return -1;
	}

	return 0;
}




/*启动hi3519 info 设备*/
cp_int32_t	start_hi3519_av_info(cp_hi3519_av_codec_t *hi3519_av_codec, cp_hi3519_av_conf_t *hi3519_av_conf)
{
	cp_int32_t					tmp_ret_int = 0;



	switch (hi3519_av_codec->hacc.mode) {
	case cp_hi3519_av_codec_mode_vi_venc:
	{
		tmp_ret_int = start_hi3519_av_info_mode_vi_venc(hi3519_av_codec, hi3519_av_conf);
		if (tmp_ret_int) {
			cp_module_log(error, hi3519_av_codec, "start_hi3519_av_info_mode_vi_venc() error.");
			return tmp_ret_int;
		}
	}
	break;
	case cp_hi3519_av_codec_mode_vi_stitch_vpss_venc:
	{
		tmp_ret_int = start_hi3519_av_info_mode_vi_stitch_vpss_venc(hi3519_av_codec, hi3519_av_conf);
		if (tmp_ret_int) {
			cp_module_log(error, hi3519_av_codec, "start_hi3519_av_info_mode_vi_stitch_vpss_venc() error.");
			return tmp_ret_int;
		}
	}
	break;
	case cp_hi3519_av_codec_mode_vi_fisheye_stitch_vpss_venc:
	{
		tmp_ret_int = start_hi3519_av_info_mode_vi_fisheye_stitch_vpss_venc(hi3519_av_codec, hi3519_av_conf);
		if (tmp_ret_int) {
			cp_module_log(error, hi3519_av_codec, "start_hi3519_av_info_mode_vi_fisheye_stitch_vpss_venc() error.");
			return tmp_ret_int;
		}
	}
	break;
	case cp_hi3519_av_codec_mode_vi_fisheye_process_vpss_venc:
	{
		tmp_ret_int = start_hi3519_av_info_mode_vi_fisheye_process_vpss_venc(hi3519_av_codec, hi3519_av_conf);
		if (tmp_ret_int) {
			cp_module_log(error, hi3519_av_codec, "start_hi3519_av_info_mode_vi_fisheye_process_vpss_venc() error.");
			return tmp_ret_int;
		}
	}
	break;
	case cp_hi3519_av_codec_mode_vi_fisheye_process_vpss_stitch_vpss_venc:
	{
		tmp_ret_int = start_hi3519_av_info_mode_vi_fisheye_process_vpss_stitch_vpss_venc(hi3519_av_codec, hi3519_av_conf);
		if (tmp_ret_int) {
			cp_module_log(error, hi3519_av_codec, "start_hi3519_av_info_mode_vi_fisheye_process_vpss_stitch_vpss_venc() error.");
			return tmp_ret_int;
		}
	}
	break;
	case cp_hi3519_av_codec_mode_vi_process_vpss_fisheye_stitch_vpss_venc:
	{
		tmp_ret_int = start_hi3519_av_info_mode_vi_process_vpss_fisheye_stitch_vpss_venc(hi3519_av_codec, hi3519_av_conf);
		if (tmp_ret_int) {
			cp_module_log(error, hi3519_av_codec, "start_hi3519_av_info_mode_vi_process_vpss_fisheye_stitch_vpss_venc() error.");
			return tmp_ret_int;
		}
	}
	break;
	default:
	{
		cp_module_log(error, hi3519_av_codec, "start_hi3519_av_info() error. unknow process mode[%d] error.", hi3519_av_codec->hacc.mode);
		tmp_ret_int = -1;
	}
	}

	return tmp_ret_int;
}

/*启动hi3519 info 设备*/
cp_int32_t	start_hi3519_av_info_bak(cp_hi3519_av_codec_t *hi3519_av_codec, cp_hi3519_av_conf_t *hi3519_av_conf)
{
	cp_int32_t					tmp_ret_int = 0;


	/*启动hi3519 vi 设备*/
	tmp_ret_int = start_hi3519_av_vi(hi3519_av_codec, hi3519_av_codec->av_conf);
	if (tmp_ret_int) {
		cp_module_log(error, hi3519_av_codec, "start_hi3519_av_vi() error.");
		return -1;
	}
	cp_module_log(notice, hi3519_av_codec, "start_hi3519_av_vi() successed.");

	/*启动hi3519 vi 设备*/
	tmp_ret_int = start_hi3519_av_vi_ext_channel(hi3519_av_codec, hi3519_av_codec->av_conf);
	if (tmp_ret_int) {
		cp_module_log(error, hi3519_av_codec, "start_hi3519_av_vi_ext_channel() error.");
		return -1;
	}
	cp_module_log(notice, hi3519_av_codec, "start_hi3519_av_vi_ext_channel() successed.");

	if (cp_hi3519_av_codec_mode_vi_venc != hi3519_av_codec->hacc.mode ||
		hi3519_av_codec->hacc.vi_channel >= CP_HI3519_AV_CODEC_BEGIN_EXT_VI_CHANNEL_NUMBER) {
		/*启动hi3519 vi fisheye 设备*/
		tmp_ret_int = start_hi3519_av_fisheye(hi3519_av_codec, hi3519_av_codec->av_conf);
		if (tmp_ret_int) {
			cp_module_log(error, hi3519_av_codec, "start_hi3519_av_fisheye() error.");
			return -1;
		}
		cp_module_log(notice, hi3519_av_codec, "start_hi3519_av_fisheye() successed.");
	}

	if (cp_hi3519_av_codec_mode_vi_stitch_vpss_venc == hi3519_av_codec->hacc.mode ||
		cp_hi3519_av_codec_mode_vi_fisheye_stitch_vpss_venc == hi3519_av_codec->hacc.mode ||
		cp_hi3519_av_codec_mode_vi_fisheye_process_vpss_stitch_vpss_venc == hi3519_av_codec->hacc.mode ||
		cp_hi3519_av_codec_mode_vi_fisheye_process_vpss_venc == hi3519_av_codec->hacc.mode) {

		if (cp_hi3519_av_codec_mode_vi_fisheye_process_vpss_venc != hi3519_av_codec->hacc.mode) {
			/*启动hi3519 vpss 设备*/
			tmp_ret_int = start_hi3519_av_stitch_vpss(hi3519_av_codec, hi3519_av_codec->av_conf);
			if (tmp_ret_int) {
				cp_module_log(error, hi3519_av_codec, "start_hi3519_av_stitch_vpss() error.");
				return -1;
			}
			cp_module_log(notice, hi3519_av_codec, "start_hi3519_av_stitch_vpss() successed.");
		}

		if (cp_hi3519_av_codec_mode_vi_fisheye_process_vpss_stitch_vpss_venc == hi3519_av_codec->hacc.mode ||
			cp_hi3519_av_codec_mode_vi_fisheye_process_vpss_venc == hi3519_av_codec->hacc.mode) {
			/*启动hi3519 extvpss 设备*/
			tmp_ret_int = start_hi3519_av_process_vpss(hi3519_av_codec, hi3519_av_codec->av_conf);
			if (tmp_ret_int) {
				cp_module_log(error, hi3519_av_codec, "start_hi3519_av_process_vpss() error.");
				return -1;
			}
			cp_module_log(notice, hi3519_av_codec, "start_hi3519_av_process_vpss() successed.");
		}
	}

	/*启动hi3519 config venc 设备*/
	tmp_ret_int = start_hi3519_av_config_venc(hi3519_av_codec, hi3519_av_codec->av_conf);
	if (tmp_ret_int) {
		cp_module_log(error, hi3519_av_codec, "start_hi3519_av_config_venc() error.");
		return -1;
	}
	cp_module_log(notice, hi3519_av_codec, "start_hi3519_av_config_venc() successed.");

#if 0
	else {
		/*启动hi3519 general venc 设备*/
		tmp_ret_int = start_hi3519_av_general_venc(hi3519_av_codec, hi3519_av_codec->av_conf);
		if (tmp_ret_int) {
			cp_module_log(error, hi3519_av_codec, "start_hi3519_av_general_venc() error.");
			return -1;
		}
		cp_module_log(notice, hi3519_av_codec, "start_hi3519_av_general_venc() successed.");
	}
#endif

	/*邦定信息*/
	tmp_ret_int = hi3519_av_bind_info(hi3519_av_codec, hi3519_av_conf);
	if (tmp_ret_int) {
		cp_module_log(error, hi3519_av_codec, "hi3519_av_bind_info() error.");
		return -1;
	}
	cp_module_log(notice, hi3519_av_codec, "hi3519_av_bind_info() successed.");

	/*绑定vpss 和 venc*/
	tmp_ret_int = start_hi3519_av_get_stream(hi3519_av_codec, hi3519_av_codec->av_conf);
	if (tmp_ret_int) {
		cp_module_log(error, hi3519_av_codec, "start_hi3519_av_get_stream() error.");
		return -1;
	}

	return 0;
}

/*启动hi3519 info 设备*/
cp_int32_t start_hi3519_av_info_mode_vi_venc(cp_hi3519_av_codec_t *hi3519_av_codec, cp_hi3519_av_conf_t *hi3519_av_conf)
{
	cp_int32_t					tmp_ret_int = 0;


	/*启动hi3519 vi 设备*/
	tmp_ret_int = start_hi3519_av_vi(hi3519_av_codec, hi3519_av_codec->av_conf);
	if (tmp_ret_int) {
		cp_module_log(error, hi3519_av_codec, "start_hi3519_av_vi() error.");
		return -1;
	}
	cp_module_log(notice, hi3519_av_codec, "start_hi3519_av_vi() successed.");

	/*启动hi3519 vi 设备*/
	tmp_ret_int = start_hi3519_av_vi_ext_channel(hi3519_av_codec, hi3519_av_codec->av_conf);
	if (tmp_ret_int) {
		cp_module_log(error, hi3519_av_codec, "start_hi3519_av_vi_ext_channel() error.");
		return -1;
	}
	cp_module_log(notice, hi3519_av_codec, "start_hi3519_av_vi_ext_channel() successed.");

	if (cp_hi3519_av_codec_mode_vi_venc != hi3519_av_codec->hacc.mode ||
		hi3519_av_codec->hacc.vi_channel >= CP_HI3519_AV_CODEC_BEGIN_EXT_VI_CHANNEL_NUMBER) {
		/*启动hi3519 vi fisheye 设备*/
		tmp_ret_int = start_hi3519_av_fisheye(hi3519_av_codec, hi3519_av_codec->av_conf);
		if (tmp_ret_int) {
			cp_module_log(error, hi3519_av_codec, "start_hi3519_av_fisheye() error.");
			return -1;
		}
		cp_module_log(notice, hi3519_av_codec, "start_hi3519_av_fisheye() successed.");
	}

	/*启动hi3519 config venc 设备*/
	tmp_ret_int = start_hi3519_av_config_venc(hi3519_av_codec, hi3519_av_codec->av_conf);
	if (tmp_ret_int) {
		cp_module_log(error, hi3519_av_codec, "start_hi3519_av_config_venc() error.");
		return -1;
	}
	cp_module_log(notice, hi3519_av_codec, "start_hi3519_av_config_venc() successed.");

	/*绑定vi fisheye 和 venc*/
	tmp_ret_int = hi3519_av_bind_vi_fisheye_venc(hi3519_av_codec, hi3519_av_codec->av_conf);
	if (tmp_ret_int) {
		cp_module_log(error, hi3519_av_codec, "hi3519_av_bind_vi_fisheye_venc() error.");
		return -1;
	}
	cp_module_log(notice, hi3519_av_codec, "hi3519_av_bind_vi_fisheye_venc() successed.");

	/*绑定vpss 和 venc*/
	tmp_ret_int = start_hi3519_av_get_stream(hi3519_av_codec, hi3519_av_codec->av_conf);
	if (tmp_ret_int) {
		cp_module_log(error, hi3519_av_codec, "start_hi3519_av_get_stream() error.");
		return -1;
	}

	return 0;
}

/*启动hi3519 info 设备*/
cp_int32_t start_hi3519_av_info_mode_vi_stitch_vpss_venc(cp_hi3519_av_codec_t *hi3519_av_codec, cp_hi3519_av_conf_t *hi3519_av_conf)
{
	cp_int32_t					tmp_ret_int = 0;


	/*启动hi3519 vi 设备*/
	tmp_ret_int = start_hi3519_av_vi(hi3519_av_codec, hi3519_av_codec->av_conf);
	if (tmp_ret_int) {
		cp_module_log(error, hi3519_av_codec, "start_hi3519_av_vi() error.");
		return -1;
	}
	cp_module_log(notice, hi3519_av_codec, "start_hi3519_av_vi() successed.");

	/*启动hi3519 vi 设备*/
	tmp_ret_int = start_hi3519_av_vi_ext_channel(hi3519_av_codec, hi3519_av_codec->av_conf);
	if (tmp_ret_int) {
		cp_module_log(error, hi3519_av_codec, "start_hi3519_av_vi_ext_channel() error.");
		return -1;
	}
	cp_module_log(notice, hi3519_av_codec, "start_hi3519_av_vi_ext_channel() successed.");

#if 0
	if (cp_hi3519_av_codec_mode_vi_venc != hi3519_av_codec->hacc.mode ||
		hi3519_av_codec->hacc.vi_channel >= CP_HI3519_AV_CODEC_BEGIN_EXT_VI_CHANNEL_NUMBER) {
		/*启动hi3519 vi fisheye 设备*/
		tmp_ret_int = start_hi3519_av_fisheye(hi3519_av_codec, hi3519_av_codec->av_conf);
		if (tmp_ret_int) {
			cp_module_log(error, hi3519_av_codec, "start_hi3519_av_fisheye() error.");
			return -1;
		}
		cp_module_log(notice, hi3519_av_codec, "start_hi3519_av_fisheye() successed.");
	}
#endif

	/*启动hi3519 vpss 设备*/
	tmp_ret_int = start_hi3519_av_stitch_vpss(hi3519_av_codec, hi3519_av_codec->av_conf);
	if (tmp_ret_int) {
		cp_module_log(error, hi3519_av_codec, "start_hi3519_av_stitch_vpss() error.");
		return -1;
	}
	cp_module_log(notice, hi3519_av_codec, "start_hi3519_av_stitch_vpss() successed.");

	/*启动hi3519 config venc 设备*/
	tmp_ret_int = start_hi3519_av_config_venc(hi3519_av_codec, hi3519_av_codec->av_conf);
	if (tmp_ret_int) {
		cp_module_log(error, hi3519_av_codec, "start_hi3519_av_config_venc() error.");
		return -1;
	}
	cp_module_log(notice, hi3519_av_codec, "start_hi3519_av_config_venc() successed.");

	/*邦定信息*/
	tmp_ret_int = hi3519_av_bind_vi_vpss(hi3519_av_codec, hi3519_av_codec->av_conf);
	if (tmp_ret_int) {
		cp_module_log(error, hi3519_av_codec, "hi3519_av_bind_vi_vpss() error.");
		return -1;
	}
	cp_module_log(notice, hi3519_av_codec, "hi3519_av_bind_vi_vpss() successed.");

	/*绑定vpss 和 venc*/
	tmp_ret_int = hi3519_av_bind_stitch_vpss_venc(hi3519_av_codec, hi3519_av_codec->av_conf);
	if (tmp_ret_int) {
		cp_module_log(error, hi3519_av_codec, "hi3519_av_bind_stitch_vpss_venc() error.");
		return -1;
	}
	cp_module_log(notice, hi3519_av_codec, "hi3519_av_bind_stitch_vpss_venc() successed.");

	/*绑定vpss 和 venc*/
	tmp_ret_int = start_hi3519_av_get_stream(hi3519_av_codec, hi3519_av_codec->av_conf);
	if (tmp_ret_int) {
		cp_module_log(error, hi3519_av_codec, "start_hi3519_av_get_stream() error.");
		return -1;
	}

	return 0;
}

/*启动hi3519 info 设备*/
cp_int32_t start_hi3519_av_info_mode_vi_fisheye_stitch_vpss_venc(cp_hi3519_av_codec_t *hi3519_av_codec, cp_hi3519_av_conf_t *hi3519_av_conf)
{
	cp_int32_t					tmp_ret_int = 0;


	/*启动hi3519 vi 设备*/
	tmp_ret_int = start_hi3519_av_vi(hi3519_av_codec, hi3519_av_codec->av_conf);
	if (tmp_ret_int) {
		cp_module_log(error, hi3519_av_codec, "start_hi3519_av_vi() error.");
		return -1;
	}
	cp_module_log(notice, hi3519_av_codec, "start_hi3519_av_vi() successed.");

	/*启动hi3519 vi 设备*/
	tmp_ret_int = start_hi3519_av_vi_ext_channel(hi3519_av_codec, hi3519_av_codec->av_conf);
	if (tmp_ret_int) {
		cp_module_log(error, hi3519_av_codec, "start_hi3519_av_vi_ext_channel() error.");
		return -1;
	}
	cp_module_log(notice, hi3519_av_codec, "start_hi3519_av_vi_ext_channel() successed.");

	/*启动hi3519 vi fisheye 设备*/
	tmp_ret_int = start_hi3519_av_fisheye(hi3519_av_codec, hi3519_av_codec->av_conf);
	if (tmp_ret_int) {
		cp_module_log(error, hi3519_av_codec, "start_hi3519_av_fisheye() error.");
		return -1;
	}
	cp_module_log(notice, hi3519_av_codec, "start_hi3519_av_fisheye() successed.");

	/*启动hi3519 vpss 设备*/
	tmp_ret_int = start_hi3519_av_stitch_vpss(hi3519_av_codec, hi3519_av_codec->av_conf);
	if (tmp_ret_int) {
		cp_module_log(error, hi3519_av_codec, "start_hi3519_av_stitch_vpss() error.");
		return -1;
	}
	cp_module_log(notice, hi3519_av_codec, "start_hi3519_av_stitch_vpss() successed.");

	/*启动hi3519 config venc 设备*/
	tmp_ret_int = start_hi3519_av_config_venc(hi3519_av_codec, hi3519_av_codec->av_conf);
	if (tmp_ret_int) {
		cp_module_log(error, hi3519_av_codec, "start_hi3519_av_config_venc() error.");
		return -1;
	}
	cp_module_log(notice, hi3519_av_codec, "start_hi3519_av_config_venc() successed.");

	/*邦定信息*/
	tmp_ret_int = hi3519_av_bind_vi_fisheye_vpss(hi3519_av_codec, hi3519_av_codec->av_conf);
	if (tmp_ret_int) {
		cp_module_log(error, hi3519_av_codec, "hi3519_av_bind_vi_vpss() error.");
		return -1;
	}
	cp_module_log(notice, hi3519_av_codec, "hi3519_av_bind_vi_vpss() successed.");

	/*绑定vpss 和 venc*/
	tmp_ret_int = hi3519_av_bind_stitch_vpss_venc(hi3519_av_codec, hi3519_av_codec->av_conf);
	if (tmp_ret_int) {
		cp_module_log(error, hi3519_av_codec, "hi3519_av_bind_stitch_vpss_venc() error.");
		return -1;
	}
	cp_module_log(notice, hi3519_av_codec, "hi3519_av_bind_stitch_vpss_venc() successed.");

	/*绑定vpss 和 venc*/
	tmp_ret_int = start_hi3519_av_get_stream(hi3519_av_codec, hi3519_av_codec->av_conf);
	if (tmp_ret_int) {
		cp_module_log(error, hi3519_av_codec, "start_hi3519_av_get_stream() error.");
		return -1;
	}

	return 0;
}

/*启动hi3519 info 设备*/
cp_int32_t start_hi3519_av_info_mode_vi_fisheye_process_vpss_venc(cp_hi3519_av_codec_t *hi3519_av_codec, cp_hi3519_av_conf_t *hi3519_av_conf)
{
	cp_int32_t					tmp_ret_int = 0;


	/*启动hi3519 vi 设备*/
	tmp_ret_int = start_hi3519_av_vi(hi3519_av_codec, hi3519_av_codec->av_conf);
	if (tmp_ret_int) {
		cp_module_log(error, hi3519_av_codec, "start_hi3519_av_vi() error.");
		return -1;
	}
	cp_module_log(notice, hi3519_av_codec, "start_hi3519_av_vi() successed.");

	/*启动hi3519 vi 设备*/
	tmp_ret_int = start_hi3519_av_vi_ext_channel(hi3519_av_codec, hi3519_av_codec->av_conf);
	if (tmp_ret_int) {
		cp_module_log(error, hi3519_av_codec, "start_hi3519_av_vi_ext_channel() error.");
		return -1;
	}
	cp_module_log(notice, hi3519_av_codec, "start_hi3519_av_vi_ext_channel() successed.");

	/*启动hi3519 vi fisheye 设备*/
	tmp_ret_int = start_hi3519_av_fisheye(hi3519_av_codec, hi3519_av_codec->av_conf);
	if (tmp_ret_int) {
		cp_module_log(error, hi3519_av_codec, "start_hi3519_av_fisheye() error.");
		return -1;
	}
	cp_module_log(notice, hi3519_av_codec, "start_hi3519_av_fisheye() successed.");

	/*启动hi3519 extvpss 设备*/
	tmp_ret_int = start_hi3519_av_process_vpss(hi3519_av_codec, hi3519_av_codec->av_conf);
	if (tmp_ret_int) {
		cp_module_log(error, hi3519_av_codec, "start_hi3519_av_process_vpss() error.");
		return -1;
	}
	cp_module_log(notice, hi3519_av_codec, "start_hi3519_av_process_vpss() successed.");

	/*启动hi3519 config venc 设备*/
	tmp_ret_int = start_hi3519_av_config_venc(hi3519_av_codec, hi3519_av_codec->av_conf);
	if (tmp_ret_int) {
		cp_module_log(error, hi3519_av_codec, "start_hi3519_av_config_venc() error.");
		return -1;
	}
	cp_module_log(notice, hi3519_av_codec, "start_hi3519_av_config_venc() successed.");

	/*绑定vi 和 vpss*/
	tmp_ret_int = hi3519_av_bind_vi_process_vpss(hi3519_av_codec, hi3519_av_codec->av_conf);
	if (tmp_ret_int) {
		cp_module_log(error, hi3519_av_codec, "hi3519_av_bind_vi_process_vpss() error.");
		return -1;
	}
	cp_module_log(notice, hi3519_av_codec, "hi3519_av_bind_vi_process_vpss() successed.");

	/*绑定vpss 和 venc*/
	tmp_ret_int = hi3519_av_bind_process_vpss_venc(hi3519_av_codec, hi3519_av_codec->av_conf);
	if (tmp_ret_int) {
		cp_module_log(error, hi3519_av_codec, "hi3519_av_bind_process_vpss_venc() error.");
		return -1;
	}
	cp_module_log(notice, hi3519_av_codec, "hi3519_av_bind_process_vpss_venc() successed.");

	/*绑定vpss 和 venc*/
	tmp_ret_int = start_hi3519_av_get_stream(hi3519_av_codec, hi3519_av_codec->av_conf);
	if (tmp_ret_int) {
		cp_module_log(error, hi3519_av_codec, "start_hi3519_av_get_stream() error.");
		return -1;
	}

	return 0;
}

/*启动hi3519 info 设备*/
cp_int32_t start_hi3519_av_info_mode_vi_fisheye_process_vpss_stitch_vpss_venc(cp_hi3519_av_codec_t *hi3519_av_codec, cp_hi3519_av_conf_t *hi3519_av_conf)
{
	cp_int32_t					tmp_ret_int = 0;


	/*启动hi3519 vi 设备*/
	tmp_ret_int = start_hi3519_av_vi(hi3519_av_codec, hi3519_av_codec->av_conf);
	if (tmp_ret_int) {
		cp_module_log(error, hi3519_av_codec, "start_hi3519_av_vi() error.");
		return -1;
	}
	cp_module_log(notice, hi3519_av_codec, "start_hi3519_av_vi() successed.");

	/*启动hi3519 vi 设备*/
	tmp_ret_int = start_hi3519_av_vi_ext_channel(hi3519_av_codec, hi3519_av_codec->av_conf);
	if (tmp_ret_int) {
		cp_module_log(error, hi3519_av_codec, "start_hi3519_av_vi_ext_channel() error.");
		return -1;
	}
	cp_module_log(notice, hi3519_av_codec, "start_hi3519_av_vi_ext_channel() successed.");

	/*启动hi3519 vi fisheye 设备*/
	tmp_ret_int = start_hi3519_av_fisheye(hi3519_av_codec, hi3519_av_codec->av_conf);
	if (tmp_ret_int) {
		cp_module_log(error, hi3519_av_codec, "start_hi3519_av_fisheye() error.");
		return -1;
	}
	cp_module_log(notice, hi3519_av_codec, "start_hi3519_av_fisheye() successed.");

	/*启动hi3519 extvpss 设备*/
	tmp_ret_int = start_hi3519_av_process_vpss(hi3519_av_codec, hi3519_av_codec->av_conf);
	if (tmp_ret_int) {
		cp_module_log(error, hi3519_av_codec, "start_hi3519_av_process_vpss() error.");
		return -1;
	}
	cp_module_log(notice, hi3519_av_codec, "start_hi3519_av_process_vpss() successed.");

	//  	/*启动hi3519 extvpss ext channel设备*/
	//  	tmp_ret_int = start_hi3519_av_process_vpss_ext_channel(hi3519_av_codec, hi3519_av_codec->av_conf);
	//  	if (tmp_ret_int) {
	//  		cp_module_log(error, hi3519_av_codec, "start_hi3519_av_process_vpss_ext_channel() error.");
	//  		return -1;
	//  	}
	//  	cp_module_log(notice, hi3519_av_codec, "start_hi3519_av_process_vpss_ext_channel() successed.");

	/*启动hi3519 vpss 设备*/
	tmp_ret_int = start_hi3519_av_stitch_vpss(hi3519_av_codec, hi3519_av_codec->av_conf);
	if (tmp_ret_int) {
		cp_module_log(error, hi3519_av_codec, "start_hi3519_av_stitch_vpss() error.");
		return -1;
	}
	cp_module_log(notice, hi3519_av_codec, "start_hi3519_av_stitch_vpss() successed.");

	/*启动hi3519 config venc 设备*/
	tmp_ret_int = start_hi3519_av_config_venc(hi3519_av_codec, hi3519_av_codec->av_conf);
	if (tmp_ret_int) {
		cp_module_log(error, hi3519_av_codec, "start_hi3519_av_config_venc() error.");
		return -1;
	}
	cp_module_log(notice, hi3519_av_codec, "start_hi3519_av_config_venc() successed.");

	/*绑定vi 和 vpss*/
	tmp_ret_int = hi3519_av_bind_vi_fisheye_process_vpss(hi3519_av_codec, hi3519_av_codec->av_conf);
	if (tmp_ret_int) {
		cp_module_log(error, hi3519_av_codec, "hi3519_av_bind_vi_process_vpss() error.");
		return -1;
	}
	cp_module_log(notice, hi3519_av_codec, "hi3519_av_bind_vi_process_vpss() successed.");

	//  	/*绑定vi 和 vpss*/
	//  	tmp_ret_int = hi3519_av_bind_process_vpss_ext_channel_stitch_vpss(hi3519_av_codec, hi3519_av_codec->av_conf);
	//  	if (tmp_ret_int) {
	//  		cp_module_log(error, hi3519_av_codec, "hi3519_av_bind_process_vpss_ext_channel_stitch_vpss() error.");
	//  		return -1;
	//  	}
	//  	cp_module_log(notice, hi3519_av_codec, "hi3519_av_bind_process_vpss_ext_channel_stitch_vpss() successed.");

	/*绑定vi 和 vpss*/
	tmp_ret_int = hi3519_av_bind_process_vpss_stitch_vpss(hi3519_av_codec, hi3519_av_codec->av_conf);
	if (tmp_ret_int) {
		cp_module_log(error, hi3519_av_codec, "hi3519_av_bind_process_vpss_stitch_vpss() error.");
		return -1;
	}
	cp_module_log(notice, hi3519_av_codec, "hi3519_av_bind_process_vpss_stitch_vpss() successed.");

	/*绑定vpss 和 venc*/
	tmp_ret_int = hi3519_av_bind_stitch_vpss_venc(hi3519_av_codec, hi3519_av_codec->av_conf);
	if (tmp_ret_int) {
		cp_module_log(error, hi3519_av_codec, "hi3519_av_bind_stitch_vpss_venc() error.");
		return -1;
	}
	cp_module_log(notice, hi3519_av_codec, "hi3519_av_bind_stitch_vpss_venc() successed.");

	/*绑定vpss 和 venc*/
	tmp_ret_int = start_hi3519_av_get_stream(hi3519_av_codec, hi3519_av_codec->av_conf);
	if (tmp_ret_int) {
		cp_module_log(error, hi3519_av_codec, "start_hi3519_av_get_stream() error.");
		return -1;
	}

	return 0;
}

/*启动hi3519 info 设备*/
cp_int32_t start_hi3519_av_info_mode_vi_process_vpss_fisheye_stitch_vpss_venc(cp_hi3519_av_codec_t *hi3519_av_codec, cp_hi3519_av_conf_t *hi3519_av_conf)
{
	cp_int32_t					tmp_ret_int = 0;


	/*启动hi3519 vi 设备*/
	tmp_ret_int = start_hi3519_av_vi(hi3519_av_codec, hi3519_av_codec->av_conf);
	if (tmp_ret_int) {
		cp_module_log(error, hi3519_av_codec, "start_hi3519_av_vi() error.");
		return -1;
	}
	cp_module_log(notice, hi3519_av_codec, "start_hi3519_av_vi() successed.");

	/*启动hi3519 vi 设备*/
	tmp_ret_int = start_hi3519_av_vi_ext_channel(hi3519_av_codec, hi3519_av_codec->av_conf);
	if (tmp_ret_int) {
		cp_module_log(error, hi3519_av_codec, "start_hi3519_av_vi_ext_channel() error.");
		return -1;
	}
	cp_module_log(notice, hi3519_av_codec, "start_hi3519_av_vi_ext_channel() successed.");

	/*启动hi3519 extvpss 设备*/
	tmp_ret_int = start_hi3519_av_process_vpss(hi3519_av_codec, hi3519_av_codec->av_conf);
	if (tmp_ret_int) {
		cp_module_log(error, hi3519_av_codec, "start_hi3519_av_process_vpss() error.");
		return -1;
	}
	cp_module_log(notice, hi3519_av_codec, "start_hi3519_av_process_vpss() successed.");

	/*启动hi3519 extvpss ext channel设备*/
	tmp_ret_int = start_hi3519_av_process_vpss_ext_channel(hi3519_av_codec, hi3519_av_codec->av_conf);
	if (tmp_ret_int) {
		cp_module_log(error, hi3519_av_codec, "start_hi3519_av_process_vpss_ext_channel() error.");
		return -1;
	}
	cp_module_log(notice, hi3519_av_codec, "start_hi3519_av_process_vpss_ext_channel() successed.");

	/*启动hi3519 vi fisheye 设备*/
	tmp_ret_int = start_hi3519_av_fisheye(hi3519_av_codec, hi3519_av_codec->av_conf);
	if (tmp_ret_int) {
		cp_module_log(error, hi3519_av_codec, "start_hi3519_av_fisheye() error.");
		return -1;
	}
	cp_module_log(notice, hi3519_av_codec, "start_hi3519_av_fisheye() successed.");

	/*启动hi3519 vpss 设备*/
	tmp_ret_int = start_hi3519_av_stitch_vpss(hi3519_av_codec, hi3519_av_codec->av_conf);
	if (tmp_ret_int) {
		cp_module_log(error, hi3519_av_codec, "start_hi3519_av_stitch_vpss() error.");
		return -1;
	}
	cp_module_log(notice, hi3519_av_codec, "start_hi3519_av_stitch_vpss() successed.");

	/*启动hi3519 config venc 设备*/
	tmp_ret_int = start_hi3519_av_config_venc(hi3519_av_codec, hi3519_av_codec->av_conf);
	if (tmp_ret_int) {
		cp_module_log(error, hi3519_av_codec, "start_hi3519_av_config_venc() error.");
		return -1;
	}
	cp_module_log(notice, hi3519_av_codec, "start_hi3519_av_config_venc() successed.");

	/*绑定vi 和 vpss*/
	//tmp_ret_int = hi3519_av_bind_vi_process_vpss(hi3519_av_codec, hi3519_av_codec->av_conf);
	tmp_ret_int = hi3519_av_bind_vi_fisheye_process_vpss(hi3519_av_codec, hi3519_av_codec->av_conf);
	if (tmp_ret_int) {
		cp_module_log(error, hi3519_av_codec, "hi3519_av_bind_vi_process_vpss() error.");
		return -1;
	}
	cp_module_log(notice, hi3519_av_codec, "hi3519_av_bind_vi_process_vpss() successed.");

	/*绑定vi 和 vpss*/
	tmp_ret_int = hi3519_av_bind_process_vpss_ext_channel_stitch_vpss(hi3519_av_codec, hi3519_av_codec->av_conf);
	if (tmp_ret_int) {
		cp_module_log(error, hi3519_av_codec, "hi3519_av_bind_process_vpss_ext_channel_stitch_vpss() error.");
		return -1;
	}
	cp_module_log(notice, hi3519_av_codec, "hi3519_av_bind_process_vpss_ext_channel_stitch_vpss() successed.");

	/*绑定vpss 和 venc*/
	tmp_ret_int = hi3519_av_bind_stitch_vpss_venc(hi3519_av_codec, hi3519_av_codec->av_conf);
	if (tmp_ret_int) {
		cp_module_log(error, hi3519_av_codec, "hi3519_av_bind_stitch_vpss_venc() error.");
		return -1;
	}
	cp_module_log(notice, hi3519_av_codec, "hi3519_av_bind_stitch_vpss_venc() successed.");

	/*绑定vpss 和 venc*/
	tmp_ret_int = start_hi3519_av_get_stream(hi3519_av_codec, hi3519_av_codec->av_conf);
	if (tmp_ret_int) {
		cp_module_log(error, hi3519_av_codec, "start_hi3519_av_get_stream() error.");
		return -1;
	}

	return 0;
}

/*启动hi3519 vi 设备*/
cp_int32_t	start_hi3519_av_vi(cp_hi3519_av_codec_t *hi3519_av_codec, cp_hi3519_av_conf_t *hi3519_av_conf)
{
#if defined(CP_HI3519_MODE)
	cp_int32_t					i = 0;
	HI_S32						tmp_ret_int = HI_FAILURE;
	HI_BOOL						tmp_is_vi_vpss_online = HI_FALSE;
	VI_CHN_ATTR_S 				tmp_chn_attr = { 0, };
	VI_EXT_CHN_ATTR_S			tmp_ext_chn_attr = { 0, };




	tmp_ret_int = SAMPLE_COMM_VI_StartVi(&hi3519_av_conf->channel_list[i].channel_config);
	if (HI_SUCCESS != tmp_ret_int) {
		cp_module_log(error, hi3519_av_codec,
			"SAMPLE_COMM_VI_StartVi() channel[%d] error.", i);
		return -1;
	}

	//vi进行csc校正
	tmp_ret_int = update_hi3519_av_vi_set_csc_attr(hi3519_av_codec, hi3519_av_conf);
	if (tmp_ret_int) {
		cp_module_log(error, hi3519_av_codec, "update_hi3519_av_vi_set_csc_attr() error.");
		return -1;
	}
	else {
		cp_module_log(notice, hi3519_av_codec, "update_hi3519_av_vi_set_csc_attr() successed.");
	}

#if 0
	tmp_ret_int = update_hi3519_av_vi_set_spread_attr(hi3519_av_codec, hi3519_av_conf);
	if (tmp_ret_int) {
		cp_module_log(error, hi3519_av_codec, "update_hi3519_av_vi_set_spread_attr() error.");
		return -1;
	}
	else {
		cp_module_log(notice, hi3519_av_codec, "update_hi3519_av_vi_set_spread_attr() successed.");
	}
#endif

	tmp_ret_int = update_hi3519_av_vi_attr(hi3519_av_codec, hi3519_av_conf);
	if (tmp_ret_int) {
		cp_module_log(error, hi3519_av_codec, "update_hi3519_av_vi_attr() error.");
		return -1;
	}
	else {
		cp_module_log(notice, hi3519_av_codec, "update_hi3519_av_vi_attr() successed.");
	}

	//vi进行垂直翻转
	tmp_ret_int = update_hi3519_av_vi_flip(hi3519_av_codec, hi3519_av_conf);
	if (tmp_ret_int) {
		cp_module_log(error, hi3519_av_codec, "update_hi3519_av_vi_flip() error.");
		return -1;
	}
	else {
		cp_module_log(notice, hi3519_av_codec, "update_hi3519_av_vi_flip() successed.");
	}

#if 0

	//vi进行ldc校正
	tmp_ret_int = update_hi3519_av_vi_set_ldc_attr(hi3519_av_codec, hi3519_av_conf);
	if (tmp_ret_int) {
		cp_module_log(error, hi3519_av_codec, "update_hi3519_av_vi_set_ldc_attr() error.");
		return -1;
	}
	else {
		cp_module_log(notice, hi3519_av_codec, "update_hi3519_av_vi_set_ldc_attr() successed.");
	}

	tmp_ret_int = update_hi3519_av_vi_rotate(hi3519_av_codec, hi3519_av_conf);
	if (tmp_ret_int) {
		cp_module_log(error, hi3519_av_codec, "update_hi3519_av_vi_rotate() error.");
		return -1;
	}
	else {
		cp_module_log(notice, hi3519_av_codec, "update_hi3519_av_vi_rotate() successed.");
	}

	//update_hi3519_av_stitch_correction_attr_ldc
	tmp_ret_int = update_hi3519_av_stitch_correction_attr_ldc(hi3519_av_codec, hi3519_av_conf);
	if (tmp_ret_int) {
		cp_module_log(error, hi3519_av_codec, "update_hi3519_av_stitch_correction_attr_ldc() error.");
		return -2;
	}
	else {
		cp_module_log(notice, hi3519_av_codec, "update_hi3519_av_stitch_correction_attr_ldc() successed.");
	}
#endif


#endif

	return 0;
}

/*启动hi3519 vi _ext_channel设备*/
cp_int32_t	start_hi3519_av_vi_ext_channel(cp_hi3519_av_codec_t *hi3519_av_codec, cp_hi3519_av_conf_t *hi3519_av_conf)
{
#if defined(CP_HI3519_MODE)
	cp_int32_t					i = 0;
	HI_S32						tmp_ret_int = HI_FAILURE;
	HI_BOOL						tmp_is_vi_vpss_online = HI_FALSE;
	VI_CHN_ATTR_S 				tmp_chn_attr = { 0, };
	VI_EXT_CHN_ATTR_S			tmp_ext_chn_attr = { 0, };



	for (i = 0; i < cp_ary_size(hi3519_av_conf->channel_list); i++) {
		if (!hi3519_av_conf->channel_list[i].is_used_fisheye) {
			continue;
		}

		tmp_ret_int = HI_MPI_VI_GetChnAttr(hi3519_av_conf->channel_list[i].index, &tmp_chn_attr);
		if (HI_SUCCESS != tmp_ret_int) {
			cp_module_log(error, hi3519_av_codec,
				"HI_MPI_VI_GetChnAttr() channel[%d] failed.error_code[0x%x]",
				hi3519_av_conf->channel_list[i].index, tmp_ret_int);
			return tmp_ret_int;
		}

		tmp_ext_chn_attr.s32BindChn = hi3519_av_conf->channel_list[i].index;
		tmp_ext_chn_attr.enCompressMode = tmp_chn_attr.enCompressMode;
		tmp_ext_chn_attr.enPixFormat = tmp_chn_attr.enPixFormat;
		tmp_ext_chn_attr.s32SrcFrameRate = tmp_chn_attr.s32SrcFrameRate;
		tmp_ext_chn_attr.s32DstFrameRate = tmp_chn_attr.s32DstFrameRate;

		//tmp_ext_chn_attr.stDestSize.u32Width = tmp_chn_attr.stDestSize.u32Width;
		tmp_ext_chn_attr.stDestSize.u32Width = hi3519_av_conf->vi_output_pic_size.u32Width;
		//tmp_ext_chn_attr.stDestSize.u32Height = tmp_chn_attr.stDestSize.u32Height;
		tmp_ext_chn_attr.stDestSize.u32Height = hi3519_av_conf->vi_output_pic_size.u32Height;

		tmp_is_vi_vpss_online = SAMPLE_COMM_IsViVpssOnline();
		if (HI_FALSE == tmp_is_vi_vpss_online) {
			/* start vi dev extern chn */
			tmp_ret_int = HI_MPI_VI_SetExtChnAttr(hi3519_av_conf->channel_list[i].ext_index, &tmp_ext_chn_attr);
			if (HI_SUCCESS != tmp_ret_int) {
				cp_module_log(error, hi3519_av_codec,
					"HI_MPI_VI_SetExtChnAttr() channel[%d] failed.error_code[0x%x]",
					hi3519_av_conf->channel_list[i].ext_index, tmp_ret_int);
				return tmp_ret_int;
			}
			else {
				cp_module_log(notice, hi3519_av_codec,
					"HI_MPI_VI_SetExtChnAttr() channel[%d] successed.",
					hi3519_av_conf->channel_list[i].ext_index);
			}

			tmp_ret_int = HI_MPI_VI_EnableChn(hi3519_av_conf->channel_list[i].ext_index);
			if (HI_SUCCESS != tmp_ret_int) {
				cp_module_log(error, hi3519_av_codec,
					"HI_MPI_VI_EnableChn() channel[%d] failed.error_code[0x%x]",
					hi3519_av_conf->channel_list[i].ext_index, tmp_ret_int);
				return tmp_ret_int;
			}
			else {
				cp_module_log(notice, hi3519_av_codec,
					"HI_MPI_VI_EnableChn() channel[%d] successed.",
					hi3519_av_conf->channel_list[i].ext_index);
			}
		}
	}
#endif

	return 0;
}

/*更新vi的属性*/
cp_int32_t update_hi3519_av_vi_attr(cp_hi3519_av_codec_t *hi3519_av_codec, cp_hi3519_av_conf_t *hi3519_av_conf)
{
#if defined(CP_HI3519_MODE)
	cp_int32_t					i = 0;
	HI_S32						tmp_ret_int = HI_FAILURE;
	VI_CHN_ATTR_S 				tmp_chn_attr = { 0, };



	for (i = 0; i < cp_ary_size(hi3519_av_conf->channel_list); i++) {

		if (HI_TRUE == hi3519_av_conf->channel_list[i].is_used_crop) {
			tmp_ret_int = HI_MPI_VI_GetChnAttr(hi3519_av_conf->channel_list[i].index, &tmp_chn_attr);
			if (HI_SUCCESS != tmp_ret_int) {
				cp_module_log(error, hi3519_av_codec,
					"HI_MPI_VI_GetChnAttr() channel[%d] failed.error_code[0x%x]",
					hi3519_av_conf->channel_list[i].index, tmp_ret_int);
				return tmp_ret_int;
			}

			tmp_ret_int = HI_MPI_VI_DisableChn(hi3519_av_conf->channel_list[i].index);
			if (HI_SUCCESS != tmp_ret_int) {
				cp_module_log(error, hi3519_av_codec,
					"HI_MPI_VI_DisableChn() channel[%d] failed. disable chn failed with error code.error_code[0x%x]",
					hi3519_av_conf->channel_list[i].index, tmp_ret_int);
				return tmp_ret_int;
			}

			tmp_chn_attr.stCapRect = hi3519_av_conf->channel_list[i].cap_rect;
			tmp_chn_attr.stDestSize.u32Width = hi3519_av_conf->vi_output_pic_size.u32Width;
			tmp_chn_attr.stDestSize.u32Height = hi3519_av_conf->vi_output_pic_size.u32Height;
			tmp_chn_attr.s32SrcFrameRate = hi3519_av_codec->hacc.fps;
			tmp_chn_attr.s32DstFrameRate = hi3519_av_codec->hacc.fps;

			tmp_ret_int = HI_MPI_VI_SetChnAttr(hi3519_av_conf->channel_list[i].index, &tmp_chn_attr);
			if (HI_SUCCESS != tmp_ret_int) {
				cp_module_log(error, hi3519_av_codec,
					"HI_MPI_VI_SetChnAttr() channel[%d] failed.error_code[0x%x]",
					hi3519_av_conf->channel_list[i].index, tmp_ret_int);
				return tmp_ret_int;
			}

			tmp_ret_int = HI_MPI_VI_EnableChn(hi3519_av_conf->channel_list[i].index);
			if (HI_SUCCESS != tmp_ret_int) {
				cp_module_log(error, hi3519_av_codec,
					"HI_MPI_VI_EnableChn() channel[%d] failed.error_code[0x%x]",
					hi3519_av_conf->channel_list[i].index, tmp_ret_int);
				return tmp_ret_int;
			}

			cp_module_log(notice, hi3519_av_codec,
				"update_hi3519_av_vi_attr() successed! rect[pos(%d, %d) width:%d height:%d]. dest_size[width:%d height:%d].",
				tmp_chn_attr.stCapRect.s32X,
				tmp_chn_attr.stCapRect.s32Y,
				tmp_chn_attr.stCapRect.u32Width,
				tmp_chn_attr.stCapRect.u32Height,
				tmp_chn_attr.stDestSize.u32Width,
				tmp_chn_attr.stDestSize.u32Height);
		}
	}

#endif

	return 0;
}

/*更新vi的rotate属性*/
cp_int32_t update_hi3519_av_vi_rotate(cp_hi3519_av_codec_t *hi3519_av_codec, cp_hi3519_av_conf_t *hi3519_av_conf)
{
#if defined(CP_HI3519_MODE)
	cp_int32_t					i = 0;
	HI_S32						tmp_ret_int = HI_FAILURE;
	VI_CHN_ATTR_S 				tmp_chn_attr = { 0, };



	for (i = 0; i < cp_ary_size(hi3519_av_conf->channel_list); i++) {
		if (hi3519_av_conf->channel_list[i].rotate && hi3519_av_conf->is_used_vi_rotate) {
			tmp_ret_int = HI_MPI_VI_DisableChn(hi3519_av_conf->channel_list[i].index);
			if (HI_SUCCESS != tmp_ret_int) {
				cp_module_log(error, hi3519_av_codec,
					"HI_MPI_VI_DisableChn() channel[%d] failed. disable chn failed with error code.error_code[0x%x]",
					hi3519_av_conf->channel_list[i].index, tmp_ret_int);
				return tmp_ret_int;
			}

			tmp_ret_int = HI_MPI_VI_SetRotate(hi3519_av_conf->channel_list[i].index, hi3519_av_conf->channel_list[i].rotate);
			if (HI_SUCCESS != tmp_ret_int) {
				cp_module_log(error, hi3519_av_codec,
					"HI_MPI_VI_SetRotate() channel[%d] failed.error_code[0x%x]",
					hi3519_av_conf->channel_list[i].index, tmp_ret_int);
				return tmp_ret_int;
			}

			tmp_ret_int = HI_MPI_VI_EnableChn(hi3519_av_conf->channel_list[i].index);
			if (HI_SUCCESS != tmp_ret_int) {
				cp_module_log(error, hi3519_av_codec,
					"HI_MPI_VI_EnableChn() channel[%d] failed.error_code[0x%x]",
					hi3519_av_conf->channel_list[i].index, tmp_ret_int);
				return tmp_ret_int;
			}

			cp_module_log(notice, hi3519_av_codec,
				"update_hi3519_av_vi_rotate() successed! channel[%d] rotate[%d].",
				hi3519_av_conf->channel_list[i].index, hi3519_av_conf->channel_list[i].rotate);
		}
	}

#endif

	return 0;
}

/*更新vi的垂直翻转flip属性*/
cp_int32_t update_hi3519_av_vi_flip(cp_hi3519_av_codec_t *hi3519_av_codec, cp_hi3519_av_conf_t *hi3519_av_conf)
{
#if defined(CP_HI3519_MODE)
	cp_int32_t					i = 0;
	HI_S32						tmp_ret_int = HI_FAILURE;
	VI_CHN_ATTR_S 				tmp_chn_attr = { 0, };



	for (i = 0; i < cp_ary_size(hi3519_av_conf->channel_list); i++) {
		if (hi3519_av_conf->channel_list[i].is_flip || hi3519_av_conf->channel_list[i].is_mirror) {
			tmp_ret_int = HI_MPI_VI_GetChnAttr(hi3519_av_conf->channel_list[i].index, &tmp_chn_attr);
			if (HI_SUCCESS != tmp_ret_int) {
				cp_module_log(error, hi3519_av_codec,
					"HI_MPI_VI_GetChnAttr() channel[%d] failed.error_code[0x%x]",
					hi3519_av_conf->channel_list[i].index, tmp_ret_int);
				return tmp_ret_int;
			}

			tmp_ret_int = HI_MPI_VI_DisableChn(hi3519_av_conf->channel_list[i].index);
			if (HI_SUCCESS != tmp_ret_int) {
				cp_module_log(error, hi3519_av_codec,
					"HI_MPI_VI_DisableChn() channel[%d] failed. disable chn failed with error code.error_code[0x%x]",
					hi3519_av_conf->channel_list[i].index, tmp_ret_int);
				return tmp_ret_int;
			}

			tmp_chn_attr.bFlip = hi3519_av_conf->channel_list[i].is_flip;
			tmp_chn_attr.bMirror = hi3519_av_conf->channel_list[i].is_mirror;

			tmp_ret_int = HI_MPI_VI_SetChnAttr(hi3519_av_conf->channel_list[i].index, &tmp_chn_attr);
			if (HI_SUCCESS != tmp_ret_int) {
				cp_module_log(error, hi3519_av_codec,
					"HI_MPI_VI_SetChnAttr() channel[%d] failed.error_code[0x%x]",
					hi3519_av_conf->channel_list[i].index, tmp_ret_int);
				return tmp_ret_int;
			}

			tmp_ret_int = HI_MPI_VI_EnableChn(hi3519_av_conf->channel_list[i].index);
			if (HI_SUCCESS != tmp_ret_int) {
				cp_module_log(error, hi3519_av_codec,
					"HI_MPI_VI_EnableChn() channel[%d] failed.error_code[0x%x]",
					hi3519_av_conf->channel_list[i].index, tmp_ret_int);
				return tmp_ret_int;
			}

			cp_module_log(notice, hi3519_av_codec,
				"update_hi3519_av_vi_flip() successed! rect[pos(%d, %d) width:%d height:%d]. dest_size[width:%d height:%d].",
				tmp_chn_attr.stCapRect.s32X,
				tmp_chn_attr.stCapRect.s32Y,
				tmp_chn_attr.stCapRect.u32Width,
				tmp_chn_attr.stCapRect.u32Height,
				tmp_chn_attr.stDestSize.u32Width,
				tmp_chn_attr.stDestSize.u32Height);
		}
	}

#endif

	return 0;
}

/*更新vi的 SetSpreadAttr属性*/
cp_int32_t update_hi3519_av_vi_set_spread_attr(cp_hi3519_av_codec_t *hi3519_av_codec, cp_hi3519_av_conf_t *hi3519_av_conf)
{
#if defined(CP_HI3519_MODE)
	cp_int32_t					i = 0;
	HI_S32						tmp_ret_int = HI_FAILURE;
	SPREAD_ATTR_S				tmp_pst_spread_attr = { 0, };



	tmp_pst_spread_attr.bEnable = HI_TRUE;
	tmp_pst_spread_attr.u32SpreadCoef = 0;
	tmp_pst_spread_attr.stDestSize.u32Width = 2592;
	tmp_pst_spread_attr.stDestSize.u32Height = 2100;

	for (i = 0; i < cp_ary_size(hi3519_av_conf->channel_list); i++) {
		tmp_ret_int = HI_MPI_VI_SetSpreadAttr(hi3519_av_conf->channel_list[i].index,
			&tmp_pst_spread_attr);
		if (HI_SUCCESS != tmp_ret_int) {
			cp_module_log(error, hi3519_av_codec,
				"HI_MPI_VI_SetSpreadAttr() channel[%d] failed.error_code[0x%x]",
				hi3519_av_conf->channel_list[i].index, tmp_ret_int);
			return tmp_ret_int;
		}
		else {
			cp_module_log(notice, hi3519_av_codec,
				"HI_MPI_VI_SetSpreadAttr() channel[%d] successed.",
				hi3519_av_conf->channel_list[i].index);
		}
	}
#endif

	return 0;
}

/*更新vi的 ldc属性*/
cp_int32_t update_hi3519_av_vi_set_ldc_attr(cp_hi3519_av_codec_t *hi3519_av_codec, cp_hi3519_av_conf_t *hi3519_av_conf)
{
#if defined(CP_HI3519_MODE)
	cp_int32_t					i = 0;
	HI_S32						tmp_ret_int = HI_FAILURE;
	VI_LDC_ATTR_S				tmp_vi_ldc_attr = { 0, };



	for (i = 0; i < cp_ary_size(hi3519_av_conf->channel_list); i++) {

		tmp_ret_int = HI_MPI_VI_GetLDCAttr(hi3519_av_conf->channel_list[i].index,
			&tmp_vi_ldc_attr);
		if (HI_SUCCESS != tmp_ret_int) {
			cp_module_log(error, hi3519_av_codec,
				"HI_MPI_VI_GetLDCAttr() channel[%d] failed.error_code[0x%x]",
				hi3519_av_conf->channel_list[i].index, tmp_ret_int);
			return tmp_ret_int;
		}

		//if (0 == i) {
		tmp_vi_ldc_attr.bEnable = HI_TRUE;
		tmp_vi_ldc_attr.stAttr.enViewType = LDC_VIEW_TYPE_CROP;
		tmp_vi_ldc_attr.stAttr.s32CenterXOffset = -20;
		tmp_vi_ldc_attr.stAttr.s32CenterYOffset = 31;
		tmp_vi_ldc_attr.stAttr.s32Ratio = 100;
		//}

		tmp_ret_int = HI_MPI_VI_SetLDCAttr(hi3519_av_conf->channel_list[i].index,
			&tmp_vi_ldc_attr);
		if (HI_SUCCESS != tmp_ret_int) {
			cp_module_log(error, hi3519_av_codec,
				"HI_MPI_VI_SetLDCAttr() channel[%d] failed.error_code[0x%x]",
				hi3519_av_conf->channel_list[i].index, tmp_ret_int);
			return tmp_ret_int;
		}
		else {
			cp_module_log(notice, hi3519_av_codec,
				"HI_MPI_VI_SetLDCAttr() channel[%d] successed.",
				hi3519_av_conf->channel_list[i].index);
		}
	}
#endif

	return 0;
}

/*更新vi的 csc属性*/
cp_int32_t update_hi3519_av_vi_set_csc_attr(cp_hi3519_av_codec_t *hi3519_av_codec, cp_hi3519_av_conf_t *hi3519_av_conf)
{
#if defined(CP_HI3519_MODE)
	cp_int32_t					i = 0;
	HI_S32						tmp_ret_int = HI_FAILURE;
	VI_CSC_ATTR_S				tmp_vi_csc_attr = { 0, };



	for (i = 0; i < cp_ary_size(hi3519_av_conf->channel_list); i++) {

		tmp_ret_int = HI_MPI_VI_GetCSCAttr(hi3519_av_conf->channel_list[i].index,
			&tmp_vi_csc_attr);
		if (HI_SUCCESS != tmp_ret_int) {
			cp_module_log(error, hi3519_av_codec,
				"HI_MPI_VI_GetCSCAttr() channel[%d] failed.error_code[0x%x]",
				hi3519_av_conf->channel_list[i].index, tmp_ret_int);
			return tmp_ret_int;
		}

		tmp_vi_csc_attr.u32LumaVal = hi3519_av_codec->hacc.camera_configs[i].luminance;
		tmp_vi_csc_attr.u32ContrVal = hi3519_av_codec->hacc.camera_configs[i].contrast;
		tmp_vi_csc_attr.u32HueVal = hi3519_av_codec->hacc.camera_configs[i].hue;
		tmp_vi_csc_attr.u32SatuVal = hi3519_av_codec->hacc.camera_configs[i].satuature;

		tmp_ret_int = HI_MPI_VI_SetCSCAttr(hi3519_av_conf->channel_list[i].index,
			&tmp_vi_csc_attr);
		if (HI_SUCCESS != tmp_ret_int) {
			cp_module_log(error, hi3519_av_codec,
				"HI_MPI_VI_SetCSCAttr() channel[%d] failed.error_code[0x%x]",
				hi3519_av_conf->channel_list[i].index, tmp_ret_int);
			return tmp_ret_int;
		}
		else {
			cp_module_log(notice, hi3519_av_codec,
				"HI_MPI_VI_SetLDCAttr() channel[%d] successed.",
				hi3519_av_conf->channel_list[i].index);
		}
	}
#endif

	return 0;
}

/*双路拼接时stitching 校正时的结构体*/
cp_int32_t	update_hi3519_av_stitch_correction_attr_cylink(cp_hi3519_av_codec_t *hi3519_av_codec, cp_hi3519_av_conf_t *hi3519_av_conf)
{
#if defined(CP_HI3519_MODE)
	cp_int32_t								i = 0;
	HI_BOOL									tmp_ret_bool = HI_FALSE;
	HI_S32									tmp_ret_int = 0;
	cp_hi3519_av_conf_t						*tmp_conf = hi3519_av_codec->av_conf;
	VI_STITCH_CORRECTION_ATTR_S				tmp_stitch_attr = { 0, };						//双路拼接时stitching 校正时的结构体


	if (SAMPLE_SENSOR_DOUBLE != hi3519_av_codec->av_conf->channel_list[0].channel_config.enSnsNum) {
		return 0;
	}

	//配置所有通道1
	for (i = 0; i < cp_ary_size(tmp_conf->channel_list); i++) {

		if (!tmp_conf->channel_list[i].stitch_attr.stCylindAttr.bEnable) {
			continue;
		}
		tmp_ret_int = HI_MPI_VI_GetStitchCorrectionAttr(tmp_conf->channel_list[i].index, &tmp_stitch_attr);
		if (HI_SUCCESS != tmp_ret_int)
		{
			cp_module_log(error, hi3519_av_codec,
				"HI_MPI_VI_GetStitchCorrectionAttr() channel[%d] failed. error_code[0x%x]",
				tmp_conf->channel_list[i].index,
				tmp_ret_int);
			return HI_FAILURE;
		}
		else {
			cp_module_log(notice, hi3519_av_codec,
				"HI_MPI_VI_GetStitchCorrectionAttr() channel[%d] successed.", 
				tmp_conf->channel_list[i].index);
		}

		// 		tmp_stitch_attr.stLdcAttr.bEnable = HI_FALSE;
		// 		tmp_stitch_attr.stPMFAttr.bEnable = HI_FALSE;
		//tmp_stitch_attr.stCylindAttr = tmp_conf->channel_list[i].stitch_attr.stCylindAttr;
		//tmp_stitch_attr.stCylindAttr.stFisheyeCylindAttr.s32Ratio = tmp_conf->channel_list[i].stitch_attr.stCylindAttr.stFisheyeCylindAttr.s32Ratio;
		tmp_stitch_attr.stCylindAttr.stFisheyeCylindAttr.s32Ratio = 100;
		tmp_stitch_attr.stCylindAttr.bEnable = HI_TRUE;

		tmp_ret_int = HI_MPI_VI_SetStitchCorrectionAttr(tmp_conf->channel_list[i].index, &tmp_stitch_attr);
		if (HI_SUCCESS != tmp_ret_int)
		{
			cp_module_log(error, hi3519_av_codec,
				"HI_MPI_VI_SetStitchCorrectionAttr() channel[%d] failed. error_code[0x%x]",
				tmp_conf->channel_list[i].index,
				tmp_ret_int);
			return HI_FAILURE;
		}
		else {
			cp_module_log(notice, hi3519_av_codec,
				"HI_MPI_VI_SetStitchCorrectionAttr() channel[%d] successed.", 
				tmp_conf->channel_list[i].index);
		}
	}

#endif

	return 0;
}

/*双路拼接时stitching 校正时的结构体*/
cp_int32_t	update_hi3519_av_stitch_correction_attr_ldc(cp_hi3519_av_codec_t *hi3519_av_codec, cp_hi3519_av_conf_t *hi3519_av_conf)
{
#if defined(CP_HI3519_MODE)
	cp_int32_t								i = 0;
	HI_BOOL									tmp_ret_bool = HI_FALSE;
	HI_S32									tmp_ret_int = 0;
	cp_hi3519_av_conf_t						*tmp_conf = hi3519_av_codec->av_conf;
	VI_STITCH_CORRECTION_ATTR_S				tmp_stitch_attr = { 0, };						//双路拼接时stitching 校正时的结构体


	if (SAMPLE_SENSOR_DOUBLE != hi3519_av_codec->av_conf->channel_list[0].channel_config.enSnsNum) {
		return 0;
	}

	//配置所有通道1
	for (i = 0; i < cp_ary_size(tmp_conf->channel_list); i++) {

		if (!tmp_conf->channel_list[i].stitch_attr.stCylindAttr.bEnable) {
			continue;
		}
		tmp_ret_int = HI_MPI_VI_GetStitchCorrectionAttr(tmp_conf->channel_list[i].index, &tmp_stitch_attr);
		if (HI_SUCCESS != tmp_ret_int)
		{
			cp_module_log(error, hi3519_av_codec,
				"HI_MPI_VI_GetStitchCorrectionAttr() channel[%d] failed. error_code[0x%x]",
				tmp_conf->channel_list[i].index,
				tmp_ret_int);
			return HI_FAILURE;
		}
		else {
			cp_module_log(notice, hi3519_av_codec,
				"HI_MPI_VI_GetStitchCorrectionAttr() channel[%d] successed.",
				tmp_conf->channel_list[i].index);
		}

		tmp_stitch_attr = tmp_conf->channel_list[i].stitch_attr;
		tmp_stitch_attr.stCylindAttr.bEnable = HI_FALSE;

		tmp_ret_int = HI_MPI_VI_SetStitchCorrectionAttr(tmp_conf->channel_list[i].index, &tmp_stitch_attr);
		if (HI_SUCCESS != tmp_ret_int)
		{
			cp_module_log(error, hi3519_av_codec,
				"HI_MPI_VI_SetStitchCorrectionAttr() channel[%d] failed. error_code[0x%x]",
				tmp_conf->channel_list[i].index,
				tmp_ret_int);
			return HI_FAILURE;
		}
		else {
			cp_module_log(notice, hi3519_av_codec,
				"HI_MPI_VI_SetStitchCorrectionAttr() channel[%d] successed.",
				tmp_conf->channel_list[i].index);
		}
	}

#endif

	return 0;
}

/*设置hi3519 vi fisheye设备*/
cp_int32_t	start_hi3519_av_fisheye(cp_hi3519_av_codec_t *hi3519_av_codec, cp_hi3519_av_conf_t *hi3519_av_conf)
{
#if defined(CP_HI3519_MODE)
	cp_int32_t					i = 0;
	cp_bool_t					tmp_is_used_fisheye = cp_false;
	HI_S32						tmp_ret_int = HI_FAILURE;
	HI_U32						tmp_vi_vpss_mode = HI_FALSE;



	tmp_ret_int = HI_MPI_SYS_GetViVpssMode(&tmp_vi_vpss_mode);
	if (HI_SUCCESS != tmp_ret_int) {
		cp_module_log(error, hi3519_av_codec,
			"get vi/vpss mode failed.error_code[0x%x]", tmp_ret_int);
		return -2;
	}


	for (i = 0; i < cp_ary_size(hi3519_av_conf->fisheye_info); i++) {
		switch (hi3519_av_conf->fisheye_info[i].fisheye_type)
		{
		case cp_fisheye_type_vi:
		{
			tmp_ret_int = HI_MPI_VI_SetFisheyeDevConfig(hi3519_av_conf->channel_list[i].dev, 
				&hi3519_av_conf->fisheye_info[i].fisheye_config);
			if (HI_SUCCESS != tmp_ret_int) {
				cp_module_log(error, hi3519_av_codec,
					"HI_MPI_VI_SetFisheyeDevConfig() vi dev[%d] error.error_code[0x%x]",
					hi3519_av_conf->channel_list[i].dev,
					tmp_ret_int);
				return -3;
			} else {
				cp_module_log(notice, hi3519_av_codec,
					"HI_MPI_VI_SetFisheyeDevConfig() vi dev[%d] successed.",
					hi3519_av_conf->channel_list[i].dev);
			}

			tmp_ret_int = HI_MPI_VI_SetFisheyeAttr(hi3519_av_conf->channel_list[i].ext_index, 
				&hi3519_av_conf->fisheye_info[i].fisheye_attr);
			if (HI_SUCCESS != tmp_ret_int) {
				cp_module_log(error, hi3519_av_codec,
					"HI_MPI_VI_SetFisheyeAttr() vi dev[%d] channel[%d] failed.error_code[0x%x]",
					hi3519_av_conf->channel_list[i].dev,
					hi3519_av_conf->channel_list[i].ext_index,
					tmp_ret_int);
				return -4;
			} else {
				cp_module_log(notice, hi3519_av_codec,
					"HI_MPI_VI_SetFisheyeAttr() vi dev[%d] channel[%d] successed.",
					hi3519_av_conf->channel_list[i].dev,
					hi3519_av_conf->channel_list[i].ext_index);
			}
		}
		break;
		case cp_fisheye_type_vpss:
		{
			tmp_ret_int = HI_MPI_VPSS_SetFisheyeConfig(hi3519_av_conf->process_vpss_info[i].index, 
				&hi3519_av_conf->fisheye_info[i].fisheye_config);
			if (HI_SUCCESS != tmp_ret_int) {
				cp_module_log(error, hi3519_av_codec,
					"HI_MPI_VPSS_SetFisheyeConfig() channel[%d] error.error_code[0x%x]",
					hi3519_av_conf->process_vpss_info[i].index,
					tmp_ret_int);
				return -3;
			} else {
				cp_module_log(notice, hi3519_av_codec,
					"HI_MPI_VPSS_SetFisheyeConfig() channel[%d] successed.",
					hi3519_av_conf->process_vpss_info[i].index);
			}
			tmp_ret_int = HI_MPI_VPSS_SetFisheyeAttr(hi3519_av_conf->process_vpss_info[i].index,
				hi3519_av_conf->process_vpss_info[i].vpss_list[CP_HI3519_AV_CODEC_USED_VPSS_CHANNEL_NUMBER].ext_index,
				&hi3519_av_conf->fisheye_info[i].fisheye_attr);
			if (HI_SUCCESS != tmp_ret_int) {
				cp_module_log(error, hi3519_av_codec,
					"HI_MPI_VPSS_SetFisheyeAttr() group[%d] channel[%d] error.error_code[0x%x]",
					hi3519_av_conf->process_vpss_info[i].index,
					hi3519_av_conf->process_vpss_info[i].vpss_list[CP_HI3519_AV_CODEC_USED_VPSS_CHANNEL_NUMBER].ext_index,
					tmp_ret_int);
				return -4;
			} else {
				cp_module_log(notice, hi3519_av_codec,
					"HI_MPI_VPSS_SetFisheyeAttr() group[%d] channel[%d] successed.",
					hi3519_av_conf->process_vpss_info[i].index,
					hi3519_av_conf->process_vpss_info[i].vpss_list[CP_HI3519_AV_CODEC_USED_VPSS_CHANNEL_NUMBER].ext_index);
			}
		}
		break;
		default:
		{
			cp_module_log(error, hi3519_av_codec,
				"unknow fisheye type[%d]", hi3519_av_conf->fisheye_info[i].fisheye_type);
		}
		break;
		}
	}

#endif

	return 0;
}

/*启动hi3519 vpss_list 设备*/
cp_int32_t	start_hi3519_av_stitch_vpss(cp_hi3519_av_codec_t *hi3519_av_codec, cp_hi3519_av_conf_t *hi3519_av_conf)
{
#if defined(CP_HI3519_MODE)
	cp_int32_t								i = 0;
	HI_S32									tmp_ret_int = HI_FAILURE;
	VPSS_STITCH_BLEND_PARAM_S				tmp_stitch_blend_param = { 0, };



	tmp_ret_int = HI_MPI_VPSS_CreateGrp(hi3519_av_conf->stitch_vpss_info.index,
		&hi3519_av_conf->stitch_vpss_info.attr);
	if (tmp_ret_int != HI_SUCCESS) {
		cp_module_log(error, hi3519_av_codec,
			"HI_MPI_VPSS_CreateGrp() group[%d]. error.error_code[0x%x]",
			hi3519_av_conf->stitch_vpss_info.index,
			tmp_ret_int);
		return tmp_ret_int;
	}

	for (i = 0; i < cp_ary_size(hi3519_av_conf->stitch_vpss_info.vpss_list); i++) {
		tmp_ret_int = HI_MPI_VPSS_SetChnAttr(hi3519_av_conf->stitch_vpss_info.index,
			hi3519_av_conf->stitch_vpss_info.vpss_list[i].index,
			&hi3519_av_conf->stitch_vpss_info.vpss_list[i].attr);
		if (HI_SUCCESS != tmp_ret_int) {
			cp_module_log(error, hi3519_av_codec,
				"HI_MPI_VPSS_SetChnAttr() group[%d] channel[%d] error.error_code[0x%x]",
				hi3519_av_conf->stitch_vpss_info.index,
				hi3519_av_conf->stitch_vpss_info.vpss_list[i].index,
				tmp_ret_int);
			return -1;
		}

		tmp_ret_int = HI_MPI_VPSS_SetChnMode(hi3519_av_conf->stitch_vpss_info.index,
			hi3519_av_conf->stitch_vpss_info.vpss_list[i].index,
			&hi3519_av_conf->stitch_vpss_info.vpss_list[i].mode);
		if (HI_SUCCESS != tmp_ret_int) {
			cp_module_log(error, hi3519_av_codec,
				"HI_MPI_VPSS_SetChnMode() group[%d] channel[%d] error.error_code[0x%x]",
				hi3519_av_conf->stitch_vpss_info.index,
				hi3519_av_conf->stitch_vpss_info.vpss_list[i].index,
				tmp_ret_int);
			return -1;
		}

		if (hi3519_av_conf->channel_list[i].rotate && !hi3519_av_conf->is_used_vi_rotate) {
			tmp_ret_int = HI_MPI_VPSS_SetRotate(hi3519_av_conf->stitch_vpss_info.index,
				hi3519_av_conf->stitch_vpss_info.vpss_list[i].index,
				hi3519_av_conf->stitch_vpss_info.vpss_list[i].rotate);
			if (HI_SUCCESS != tmp_ret_int) {
				cp_module_log(error, hi3519_av_codec,
					"HI_MPI_VPSS_SetRotate() group[%d] channel[%d] rotate[%d] error.error_code[0x%x]",
					hi3519_av_conf->stitch_vpss_info.index,
					hi3519_av_conf->stitch_vpss_info.vpss_list[i].index,
					hi3519_av_conf->stitch_vpss_info.vpss_list[i].rotate,
					tmp_ret_int);
				return tmp_ret_int;
			}
		}

		tmp_ret_int = HI_MPI_VPSS_EnableChn(hi3519_av_conf->stitch_vpss_info.index,
			hi3519_av_conf->stitch_vpss_info.vpss_list[i].index);
		if (HI_SUCCESS != tmp_ret_int) {
			cp_module_log(error, hi3519_av_codec,
				"HI_MPI_VPSS_EnableChn() group[%d] channel[%d] error.error_code[0x%x]",
				hi3519_av_conf->stitch_vpss_info.index,
				hi3519_av_conf->stitch_vpss_info.vpss_list[i].index,
				tmp_ret_int);
			return -1;
		}
	}

	tmp_ret_int = HI_MPI_VPSS_GetStitchBlendParam(hi3519_av_conf->stitch_vpss_info.index,
		&tmp_stitch_blend_param);
	if (HI_SUCCESS != tmp_ret_int) {
		cp_module_log(error, hi3519_av_codec,
			"HI_MPI_VPSS_GetStitchBlendParam() Get VPSS[%d] StitchBlendParam failed witfh.error_code[0x%x]", 
			hi3519_av_conf->stitch_vpss_info.index,
			tmp_ret_int);
		return -2;
	}

	tmp_stitch_blend_param.stAdjustParam.u32BldPosition = 0;
	tmp_stitch_blend_param.stAdjustParam.u32BldRange = 0;
	hi3519_av_conf->stitch_vpss_info.stitch_blend_param = tmp_stitch_blend_param;

	tmp_ret_int = HI_MPI_VPSS_SetStitchBlendParam(hi3519_av_conf->stitch_vpss_info.index,
		&hi3519_av_conf->stitch_vpss_info.stitch_blend_param);
	if (HI_SUCCESS != tmp_ret_int) {
		cp_module_log(error, hi3519_av_codec,
			"HI_MPI_VPSS_GetStitchBlendParam() Set VPSS[%d] StitchBlendParam failed witfh.error_code[0x%x]",
			hi3519_av_conf->stitch_vpss_info.index,
			tmp_ret_int);
		return -3;
	}

	tmp_ret_int = HI_MPI_VPSS_StartGrp(hi3519_av_conf->stitch_vpss_info.index);
	if (HI_SUCCESS != tmp_ret_int) {
		cp_module_log(error, hi3519_av_codec,
			"HI_MPI_VPSS_StartGrp() group[%d] error.error_code[0x%x]",
			hi3519_av_conf->stitch_vpss_info.index,
			tmp_ret_int);
		return -1;
	}


#endif

	return 0;
}

/*启动hi3519 ext vpss 设备*/
cp_int32_t	start_hi3519_av_process_vpss(cp_hi3519_av_codec_t *hi3519_av_codec, cp_hi3519_av_conf_t *hi3519_av_conf)
{

#if defined(CP_HI3519_MODE)
	cp_int32_t								i = 0;
	cp_int32_t								j = 0;
	HI_S32									tmp_ret_int = HI_FAILURE;
	VPSS_STITCH_BLEND_PARAM_S				tmp_stitch_blend_param = { 0, };



	for (i = 0; i < cp_ary_size(hi3519_av_conf->process_vpss_info); i++) {
		tmp_ret_int = HI_MPI_VPSS_CreateGrp(hi3519_av_conf->process_vpss_info[i].index,
			&hi3519_av_conf->process_vpss_info[i].attr);
		if (tmp_ret_int != HI_SUCCESS) {
			cp_module_log(error, hi3519_av_codec,
				"HI_MPI_VPSS_CreateGrp() group[%d] error.error_code[0x%x]",
				hi3519_av_conf->process_vpss_info[i].index,
				tmp_ret_int);
			return tmp_ret_int;
		} else {
			cp_module_log(notice, hi3519_av_codec,
				"HI_MPI_VPSS_CreateGrp() group[%d] successed.",
				hi3519_av_conf->process_vpss_info[i].index);
		}

		/*启动hi3519 vi 设备*/
		tmp_ret_int = update_hi3519_av_vpss_flip(hi3519_av_codec, hi3519_av_codec->av_conf);
		if (tmp_ret_int) {
			cp_module_log(error, hi3519_av_codec, "update_hi3519_av_vpss_flip() error.");
			return -1;
		} else {
			cp_module_log(notice, hi3519_av_codec, "update_hi3519_av_vpss_flip() successed.");
		}

		for (j = 0; j < cp_ary_size(hi3519_av_conf->process_vpss_info[i].vpss_list); j++) {
			tmp_ret_int = HI_MPI_VPSS_SetChnAttr(hi3519_av_conf->process_vpss_info[i].index,
				hi3519_av_conf->process_vpss_info[i].vpss_list[j].index,
				&hi3519_av_conf->process_vpss_info[i].vpss_list[j].attr);
			if (HI_SUCCESS != tmp_ret_int) {
				cp_module_log(error, hi3519_av_codec,
					"HI_MPI_VPSS_SetChnAttr() group[%d] channel[%d] error.error_code[0x%x]",
					hi3519_av_conf->process_vpss_info[i].index,
					hi3519_av_conf->process_vpss_info[i].vpss_list[j].index,
					tmp_ret_int);
				return -1;
			}

			tmp_ret_int = HI_MPI_VPSS_SetChnMode(hi3519_av_conf->process_vpss_info[i].index,
				hi3519_av_conf->process_vpss_info[i].vpss_list[j].index,
				&hi3519_av_conf->process_vpss_info[i].vpss_list[j].mode);
			if (HI_SUCCESS != tmp_ret_int) {
				cp_module_log(error, hi3519_av_codec,
					"HI_MPI_VPSS_SetChnMode() group[%d] channel[%d] error.error_code[0x%x]",
					hi3519_av_conf->process_vpss_info[i].index,
					hi3519_av_conf->process_vpss_info[i].vpss_list[j].index,
					tmp_ret_int);
				return -1;
			}

#if 0
			/*设置hi3519 vpss rotate*/
			tmp_ret_int = update_hi3519_av_vpss_rotate(hi3519_av_codec, hi3519_av_codec->av_conf);
			if (tmp_ret_int) {
				cp_module_log(error, hi3519_av_codec, "update_hi3519_av_vpss_rotate() error.");
				return -1;
			} else {
				cp_module_log(notice, hi3519_av_codec, "update_hi3519_av_vpss_rotate() successed.");
			}
#endif

			if (hi3519_av_conf->channel_list[i].rotate && !hi3519_av_conf->is_used_vi_rotate) {
				tmp_ret_int = HI_MPI_VPSS_SetRotate(hi3519_av_conf->process_vpss_info[i].index,
					hi3519_av_conf->process_vpss_info[i].vpss_list[j].index,
					hi3519_av_conf->process_vpss_info[i].vpss_list[j].rotate);
				if (HI_SUCCESS != tmp_ret_int) {
					cp_module_log(error, hi3519_av_codec,
						"HI_MPI_VPSS_SetRotate() group[%d] channel[%d] rotate[%d] error.error_code[0x%x]",
						hi3519_av_conf->process_vpss_info[i].index,
						hi3519_av_conf->process_vpss_info[i].vpss_list[j].index,
						hi3519_av_conf->process_vpss_info[i].vpss_list[j].rotate,
						tmp_ret_int);
					return tmp_ret_int;
				}
				else {
					cp_module_log(notice, hi3519_av_codec,
						"HI_MPI_VPSS_SetRotate() group[%d] channel[%d] rotate[%d] successed.",
						hi3519_av_conf->process_vpss_info[i].index,
						hi3519_av_conf->process_vpss_info[i].vpss_list[j].index,
						hi3519_av_conf->process_vpss_info[i].vpss_list[j].rotate);
				}
			}

			tmp_ret_int = HI_MPI_VPSS_EnableChn(hi3519_av_conf->process_vpss_info[i].index,
				hi3519_av_conf->process_vpss_info[i].vpss_list[j].index);
			if (HI_SUCCESS != tmp_ret_int) {
				cp_module_log(error, hi3519_av_codec,
					"HI_MPI_VPSS_EnableChn() group[%d] channel[%d] error.error_code[0x%x]",
					hi3519_av_conf->process_vpss_info[i].index,
					hi3519_av_conf->process_vpss_info[i].vpss_list[j].index,
					tmp_ret_int);
				return -1;
			}
		}

		tmp_ret_int = HI_MPI_VPSS_StartGrp(hi3519_av_conf->process_vpss_info[i].index);
		if (HI_SUCCESS != tmp_ret_int) {
			cp_module_log(error, hi3519_av_codec,
				"HI_MPI_VPSS_StartGrp() group[%d] error.error_code[0x%x]",
				hi3519_av_conf->process_vpss_info[i].index,
				tmp_ret_int);
			return -1;
		}
		else {
			cp_module_log(notice, hi3519_av_codec,
				"HI_MPI_VPSS_StartGrp() group[%d] successed.",
				hi3519_av_conf->process_vpss_info[i].index,
				tmp_ret_int);
		}
	}

#endif

	return 0;
}

/*启动hi3519 ext vpss channel设备*/
cp_int32_t	start_hi3519_av_process_vpss_ext_channel(cp_hi3519_av_codec_t *hi3519_av_codec, cp_hi3519_av_conf_t *hi3519_av_conf)
{
#if defined(CP_HI3519_MODE)
	cp_int32_t					i = 0;
	HI_S32						tmp_ret_int = HI_FAILURE;
	HI_BOOL						tmp_is_vi_vpss_online = HI_FALSE;
	VI_CHN_ATTR_S 				tmp_chn_attr = { 0, };
	VPSS_EXT_CHN_ATTR_S			tmp_ext_chn_attr = { 0, };



	for (i = 0; i < cp_ary_size(hi3519_av_conf->process_vpss_info); i++) {

		tmp_ret_int = HI_MPI_VI_GetChnAttr(hi3519_av_conf->channel_list[i].index, &tmp_chn_attr);
		if (HI_SUCCESS != tmp_ret_int) {
			cp_module_log(error, hi3519_av_codec,
				"HI_MPI_VI_GetChnAttr() channel[%d] failed.error_code[0x%x]",
				hi3519_av_conf->channel_list[i].index, 
				tmp_ret_int);
			return tmp_ret_int;
		}

		tmp_ext_chn_attr.s32BindChn = hi3519_av_conf->process_vpss_info[i].vpss_list[CP_HI3519_AV_CODEC_USED_VPSS_CHANNEL_NUMBER].index;
		tmp_ext_chn_attr.enCompressMode = tmp_chn_attr.enCompressMode;
		tmp_ext_chn_attr.enPixelFormat = tmp_chn_attr.enPixFormat;
		tmp_ext_chn_attr.s32SrcFrameRate = tmp_chn_attr.s32SrcFrameRate;
		tmp_ext_chn_attr.s32DstFrameRate = tmp_chn_attr.s32DstFrameRate;
		//  		tmp_ext_chn_attr.u32Width = tmp_chn_attr.stDestSize.u32Width;
		//  		tmp_ext_chn_attr.u32Height = tmp_chn_attr.stDestSize.u32Height;
		tmp_ext_chn_attr.u32Width = hi3519_av_conf->vpss_output_pst_size.u32Width;;
		tmp_ext_chn_attr.u32Height = hi3519_av_conf->vpss_output_pst_size.u32Height;

		tmp_is_vi_vpss_online = SAMPLE_COMM_IsViVpssOnline();
		if (HI_FALSE == tmp_is_vi_vpss_online) {
			/* start vi dev extern chn */
			tmp_ret_int = HI_MPI_VPSS_SetExtChnAttr(hi3519_av_conf->process_vpss_info[i].index,
				hi3519_av_conf->process_vpss_info[i].vpss_list[CP_HI3519_AV_CODEC_USED_VPSS_CHANNEL_NUMBER].ext_index,
				&tmp_ext_chn_attr);
			if (HI_SUCCESS != tmp_ret_int) {
				cp_module_log(error, hi3519_av_codec,
					"HI_MPI_VPSS_SetExtChnAttr() group[%d] channel[%d] failed.error_code[0x%x]",
					hi3519_av_conf->process_vpss_info[i].index,
					hi3519_av_conf->process_vpss_info[i].vpss_list[CP_HI3519_AV_CODEC_USED_VPSS_CHANNEL_NUMBER].ext_index,
					tmp_ret_int);
				return tmp_ret_int;
			}
			else {
				cp_module_log(notice, hi3519_av_codec,
					"HI_MPI_VPSS_SetExtChnAttr() group[%d] channel[%d] successed.",
					hi3519_av_conf->process_vpss_info[i].index,
					hi3519_av_conf->process_vpss_info[i].vpss_list[CP_HI3519_AV_CODEC_USED_VPSS_CHANNEL_NUMBER].ext_index);
			}

			tmp_ret_int = HI_MPI_VPSS_EnableChn(hi3519_av_conf->process_vpss_info[i].index,
				hi3519_av_conf->process_vpss_info[i].vpss_list[CP_HI3519_AV_CODEC_USED_VPSS_CHANNEL_NUMBER].ext_index);
			if (HI_SUCCESS != tmp_ret_int) {
				cp_module_log(error, hi3519_av_codec,
					"HI_MPI_VPSS_EnableChn() group[%d] channel[%d] failed.error_code[0x%x]",
					hi3519_av_conf->process_vpss_info[i].index,
					hi3519_av_conf->process_vpss_info[i].vpss_list[CP_HI3519_AV_CODEC_USED_VPSS_CHANNEL_NUMBER].ext_index,
					tmp_ret_int);
				return tmp_ret_int;
			}
			else {
				cp_module_log(notice, hi3519_av_codec,
					"HI_MPI_VPSS_EnableChn() group[%d] channel[%d] successed.",
					hi3519_av_conf->process_vpss_info[i].index,
					hi3519_av_conf->process_vpss_info[i].vpss_list[CP_HI3519_AV_CODEC_USED_VPSS_CHANNEL_NUMBER].ext_index);
			}
		}
	}
#endif

	return 0;
}

/*更新vi的rotate属性实现垂直翻转*/
cp_int32_t update_hi3519_av_vpss_rotate(cp_hi3519_av_codec_t *hi3519_av_codec, cp_hi3519_av_conf_t *hi3519_av_conf)
{

#if defined(CP_HI3519_MODE)
	cp_int32_t					i = 0;
	HI_S32						tmp_ret_int = HI_FAILURE;



	for (i = 0; i < cp_ary_size(hi3519_av_conf->process_vpss_info); i++) {
		if (hi3519_av_conf->channel_list[i].rotate && !hi3519_av_conf->is_used_vi_rotate) {
			tmp_ret_int = HI_MPI_VPSS_SetRotate(hi3519_av_conf->process_vpss_info[i].index,
				hi3519_av_conf->process_vpss_info[i].vpss_list[CP_HI3519_AV_CODEC_USED_VPSS_CHANNEL_NUMBER].index,
				hi3519_av_conf->process_vpss_info[i].vpss_list[CP_HI3519_AV_CODEC_USED_VPSS_CHANNEL_NUMBER].rotate);
			if (HI_SUCCESS != tmp_ret_int) {
				cp_module_log(error, hi3519_av_codec,
					"HI_MPI_VPSS_SetRotate() group[%d] channel[%d] rotate[%d] error.error_code[0x%x]",
					hi3519_av_conf->process_vpss_info[i].index,
					hi3519_av_conf->process_vpss_info[i].vpss_list[CP_HI3519_AV_CODEC_USED_VPSS_CHANNEL_NUMBER].index,
					hi3519_av_conf->process_vpss_info[i].vpss_list[CP_HI3519_AV_CODEC_USED_VPSS_CHANNEL_NUMBER].rotate,
					tmp_ret_int);
				return tmp_ret_int;
			} else {
				cp_module_log(notice, hi3519_av_codec,
					"HI_MPI_VPSS_SetRotate() group[%d] channel[%d] rotate[%d] successed.",
					hi3519_av_conf->process_vpss_info[i].index,
					hi3519_av_conf->process_vpss_info[i].vpss_list[CP_HI3519_AV_CODEC_USED_VPSS_CHANNEL_NUMBER].index,
					hi3519_av_conf->process_vpss_info[i].vpss_list[CP_HI3519_AV_CODEC_USED_VPSS_CHANNEL_NUMBER].rotate);
			}
		}
	}

#endif

	return 0;
}

/*更新vi的垂直翻转flip属性*/
cp_int32_t update_hi3519_av_vpss_flip(cp_hi3519_av_codec_t *hi3519_av_codec, cp_hi3519_av_conf_t *hi3519_av_conf)
{
#if defined(CP_HI3519_MODE)
	cp_int32_t					i = 0;
	cp_int32_t					j = 0;
	HI_S32						tmp_ret_int = HI_FAILURE;


	for (i = 0; i < cp_ary_size(hi3519_av_conf->process_vpss_info); i++) {
		if (hi3519_av_conf->channel_list[i].is_flip || hi3519_av_conf->channel_list[i].is_mirror) {

			for (j = 0; j < cp_ary_size(hi3519_av_conf->process_vpss_info[i].vpss_list); j++) {
				hi3519_av_conf->process_vpss_info[i].vpss_list[j].attr.bFlip = hi3519_av_conf->channel_list[i].is_flip;
				hi3519_av_conf->process_vpss_info[i].vpss_list[j].attr.bMirror = hi3519_av_conf->channel_list[i].is_mirror;

				cp_module_log(notice, hi3519_av_codec,
					"update_hi3519_av_vpss_flip() successed! flip[%d] mirror[%d].",
					hi3519_av_conf->process_vpss_info[i].vpss_list[j].attr.bFlip,
					hi3519_av_conf->process_vpss_info[i].vpss_list[j].attr.bMirror);
			}	
		}
	}

#endif

	return 0;
}

/*启动hi3519 venc_list 设备*/
cp_int32_t	start_hi3519_av_general_venc(cp_hi3519_av_codec_t *hi3519_av_codec, cp_hi3519_av_conf_t *hi3519_av_conf)
{
#if defined(CP_HI3519_MODE)
	cp_int32_t					i = 0;
	HI_S32						tmp_ret_int = HI_FAILURE;


	for (i = 0; i < cp_ary_size(hi3519_av_conf->venc_list); i++) {
		tmp_ret_int = SAMPLE_COMM_VENC_Start(hi3519_av_conf->venc_list[i].index,
			hi3519_av_conf->venc_list[i].payload,
			hi3519_av_conf->venc_list[i].video_norm,
			hi3519_av_conf->venc_list[i].pic_size,
			hi3519_av_conf->venc_list[i].rc,
			hi3519_av_conf->venc_list[i].profile,
			&hi3519_av_conf->venc_list[i].gop_attr);
		if (HI_SUCCESS != tmp_ret_int)
		{
			cp_module_log(error, hi3519_av_codec,
				"SAMPLE_COMM_VENC_Start() channel[%d] error.error_code[0x%x]",
				i,
				tmp_ret_int);
			return -1;
		}
		hi3519_av_conf->venc_list[i].is_enc = cp_true;
	}

#endif

	return 0;
}

/*启动hi3519 配置的 venc 设备*/
cp_int32_t	start_hi3519_av_config_venc(cp_hi3519_av_codec_t *hi3519_av_codec, cp_hi3519_av_conf_t *hi3519_av_conf)
{
#if defined(CP_HI3519_MODE)
	cp_int32_t					i = 0;
	HI_S32						tmp_ret_int = HI_FAILURE;


	for (i = 0; i < cp_ary_size(hi3519_av_conf->venc_list); i++) {
		tmp_ret_int = start_hi3519_av_one_venc(hi3519_av_codec,
			hi3519_av_conf,
			&hi3519_av_conf->venc_list[i]);
		if (HI_SUCCESS != tmp_ret_int)
		{
			cp_module_log(error, hi3519_av_codec,
				"start_hi3519_av_one_venc() channel[%d] error.error_code[0x%x]",
				hi3519_av_conf->venc_list[i].index,
				tmp_ret_int);
			return -1;
		}
		hi3519_av_conf->venc_list[i].is_enc = cp_true;
	}

#endif

	return 0;
}

/*启动一个hi3519 venc 设备*/
cp_int32_t	start_hi3519_av_one_venc(cp_hi3519_av_codec_t *hi3519_av_codec,
	cp_hi3519_av_conf_t *hi3519_av_conf, cp_hi3519_av_venc_info_t *venc_info)
{
#if defined(CP_HI3519_MODE)
	HI_S32							tmp_ret_int;
	VENC_CHN_ATTR_S					stVencChnAttr;
	VENC_ATTR_H264_S				stH264Attr;
	VENC_ATTR_H264_CBR_S			stH264Cbr;
	VENC_ATTR_H264_VBR_S			stH264Vbr;
	VENC_ATTR_H264_FIXQP_S			stH264FixQp;
	VENC_ATTR_H265_S				stH265Attr;
	VENC_ATTR_H265_CBR_S			stH265Cbr;
	VENC_ATTR_H265_VBR_S			stH265Vbr;
	VENC_ATTR_H265_FIXQP_S			stH265FixQp;
	VENC_ATTR_MJPEG_S				stMjpegAttr;
	VENC_ATTR_MJPEG_FIXQP_S			stMjpegeFixQp;
	VENC_ATTR_JPEG_S				stJpegAttr;
	SIZE_S							stPicSize;
	VENC_CHN						VencChn = venc_info->index;
	PAYLOAD_TYPE_E					enType = venc_info->payload;
	VIDEO_NORM_E					enNorm = venc_info->video_norm;
	SAMPLE_RC_E						enRcMode = venc_info->rc;
	HI_U32							u32Profile = venc_info->profile;
	VENC_GOP_ATTR_S					*pstGopAttr = &venc_info->gop_attr;
	HI_U32							u32Bitrate = hi3519_av_codec->hacc.bitrate;



	stPicSize.u32Width = hi3519_av_codec->hacc.width;
	stPicSize.u32Height = hi3519_av_codec->hacc.heigth;

	/******************************************
	step 1:  Create Venc Channel
	******************************************/
	stVencChnAttr.stVeAttr.enType = enType;
	switch (enType)
	{
	case PT_H264:
	{
		stH264Attr.u32MaxPicWidth = stPicSize.u32Width;
		stH264Attr.u32MaxPicHeight = stPicSize.u32Height;
		stH264Attr.u32PicWidth = stPicSize.u32Width;/*the picture width*/
		stH264Attr.u32PicHeight = stPicSize.u32Height;/*the picture height*/
		stH264Attr.u32BufSize = stPicSize.u32Width * stPicSize.u32Height * 2;/*stream buffer size*/
		stH264Attr.u32Profile = u32Profile;/*0: baseline; 1:MP; 2:HP;  3:svc_t */
		stH264Attr.bByFrame = HI_TRUE;/*get stream mode is slice mode or frame mode?*/
		//stH264Attr.u32BFrameNum = 0;/* 0: not support B frame; >=1: number of B frames */
		//stH264Attr.u32RefNum = 1;/* 0: default; number of refrence frame*/
		memcpy(&stVencChnAttr.stVeAttr.stAttrH264e, &stH264Attr, sizeof(VENC_ATTR_H264_S));
		if (SAMPLE_RC_CBR == enRcMode)
		{
			stVencChnAttr.stRcAttr.enRcMode = VENC_RC_MODE_H264CBR;
			stH264Cbr.u32Gop = (VIDEO_ENCODING_MODE_PAL == enNorm) ? 25 : 30;
			stH264Cbr.u32StatTime = 1; /* stream rate statics time(s) */
			stH264Cbr.u32SrcFrmRate = (VIDEO_ENCODING_MODE_PAL == enNorm) ? 25 : 30; /* input (vi) frame rate */
			stH264Cbr.fr32DstFrmRate = (VIDEO_ENCODING_MODE_PAL == enNorm) ? 25 : 30; /* target frame rate */
			stH264Cbr.u32BitRate = u32Bitrate;
			stH264Cbr.u32FluctuateLevel = 1; /* average bit rate */
			memcpy(&stVencChnAttr.stRcAttr.stAttrH264Cbr, &stH264Cbr, sizeof(VENC_ATTR_H264_CBR_S));
		}
		else if (SAMPLE_RC_FIXQP == enRcMode)
		{
			stVencChnAttr.stRcAttr.enRcMode = VENC_RC_MODE_H264FIXQP;
			stH264FixQp.u32Gop = (VIDEO_ENCODING_MODE_PAL == enNorm) ? 25 : 30;
			stH264FixQp.u32SrcFrmRate = (VIDEO_ENCODING_MODE_PAL == enNorm) ? 25 : 30;
			stH264FixQp.fr32DstFrmRate = (VIDEO_ENCODING_MODE_PAL == enNorm) ? 25 : 30;
			stH264FixQp.u32IQp = 20;
			stH264FixQp.u32PQp = 23;
			stH264FixQp.u32BQp = 23;
			memcpy(&stVencChnAttr.stRcAttr.stAttrH264FixQp, &stH264FixQp, sizeof(VENC_ATTR_H264_FIXQP_S));
		}
		else if (SAMPLE_RC_VBR == enRcMode)
		{
			stVencChnAttr.stRcAttr.enRcMode = VENC_RC_MODE_H264VBR;
			stH264Vbr.u32Gop = (VIDEO_ENCODING_MODE_PAL == enNorm) ? 25 : 30;
			stH264Vbr.u32StatTime = 1;
			stH264Vbr.u32SrcFrmRate = (VIDEO_ENCODING_MODE_PAL == enNorm) ? 25 : 30;
			stH264Vbr.fr32DstFrmRate = (VIDEO_ENCODING_MODE_PAL == enNorm) ? 25 : 30;
			stH264Vbr.u32MinQp = 10;
			stH264Vbr.u32MinIQp = 10;
			stH264Vbr.u32MaxQp = 50;
			stH264Vbr.u32MaxBitRate = u32Bitrate;
			memcpy(&stVencChnAttr.stRcAttr.stAttrH264Vbr, &stH264Vbr, sizeof(VENC_ATTR_H264_VBR_S));
		}
		else
		{
			return HI_FAILURE;
		}
	}
	break;
	case PT_MJPEG:
	{
		stMjpegAttr.u32MaxPicWidth = stPicSize.u32Width;
		stMjpegAttr.u32MaxPicHeight = stPicSize.u32Height;
		stMjpegAttr.u32PicWidth = stPicSize.u32Width;
		stMjpegAttr.u32PicHeight = stPicSize.u32Height;
		stMjpegAttr.u32BufSize = stPicSize.u32Width * stPicSize.u32Height * 3;
		stMjpegAttr.bByFrame = HI_TRUE;  /*get stream mode is field mode  or frame mode*/
		memcpy(&stVencChnAttr.stVeAttr.stAttrMjpege, &stMjpegAttr, sizeof(VENC_ATTR_MJPEG_S));
		if (SAMPLE_RC_FIXQP == enRcMode)
		{
			stVencChnAttr.stRcAttr.enRcMode = VENC_RC_MODE_MJPEGFIXQP;
			stMjpegeFixQp.u32Qfactor = 90;
			stMjpegeFixQp.u32SrcFrmRate = (VIDEO_ENCODING_MODE_PAL == enNorm) ? 25 : 30;
			stMjpegeFixQp.fr32DstFrmRate = (VIDEO_ENCODING_MODE_PAL == enNorm) ? 25 : 30;
			memcpy(&stVencChnAttr.stRcAttr.stAttrMjpegeFixQp, &stMjpegeFixQp,
				sizeof(VENC_ATTR_MJPEG_FIXQP_S));
		}
		else if (SAMPLE_RC_CBR == enRcMode)
		{
			stVencChnAttr.stRcAttr.enRcMode = VENC_RC_MODE_MJPEGCBR;
			stVencChnAttr.stRcAttr.stAttrMjpegeCbr.u32StatTime = 1;
			stVencChnAttr.stRcAttr.stAttrMjpegeCbr.u32SrcFrmRate = (VIDEO_ENCODING_MODE_PAL == enNorm) ? 25 : 30;
			stVencChnAttr.stRcAttr.stAttrMjpegeCbr.fr32DstFrmRate = (VIDEO_ENCODING_MODE_PAL == enNorm) ? 25 : 30;
			stVencChnAttr.stRcAttr.stAttrMjpegeCbr.u32FluctuateLevel = 1;
			stVencChnAttr.stRcAttr.stAttrMjpegeCbr.u32BitRate = u32Bitrate * 3;
		}
		else if (SAMPLE_RC_VBR == enRcMode)
		{
			stVencChnAttr.stRcAttr.enRcMode = VENC_RC_MODE_MJPEGVBR;
			stVencChnAttr.stRcAttr.stAttrMjpegeVbr.u32StatTime = 1;
			stVencChnAttr.stRcAttr.stAttrMjpegeVbr.u32SrcFrmRate = (VIDEO_ENCODING_MODE_PAL == enNorm) ? 25 : 30;
			stVencChnAttr.stRcAttr.stAttrMjpegeVbr.fr32DstFrmRate = 5;
			stVencChnAttr.stRcAttr.stAttrMjpegeVbr.u32MinQfactor = 50;
			stVencChnAttr.stRcAttr.stAttrMjpegeVbr.u32MaxQfactor = 95;
			stVencChnAttr.stRcAttr.stAttrMjpegeVbr.u32MaxBitRate = u32Bitrate * 3;
		}
		else
		{
			SAMPLE_PRT("cann't support other mode in this version!\n");
			return HI_FAILURE;
		}
	}
	break;

	case PT_JPEG:
		stJpegAttr.u32PicWidth = stPicSize.u32Width;
		stJpegAttr.u32PicHeight = stPicSize.u32Height;
		stJpegAttr.u32MaxPicWidth = stPicSize.u32Width;
		stJpegAttr.u32MaxPicHeight = stPicSize.u32Height;
		stJpegAttr.u32BufSize = stPicSize.u32Width * stPicSize.u32Height * 3;
		stJpegAttr.bByFrame = HI_TRUE;/*get stream mode is field mode  or frame mode*/
		stJpegAttr.bSupportDCF = HI_FALSE;
		memcpy(&stVencChnAttr.stVeAttr.stAttrJpege, &stJpegAttr, sizeof(VENC_ATTR_JPEG_S));
		break;

	case PT_H265:
	{
		stH265Attr.u32MaxPicWidth = stPicSize.u32Width;
		stH265Attr.u32MaxPicHeight = stPicSize.u32Height;
		stH265Attr.u32PicWidth = stPicSize.u32Width;/*the picture width*/
		stH265Attr.u32PicHeight = stPicSize.u32Height;/*the picture height*/
		stH265Attr.u32BufSize = stPicSize.u32Width * stPicSize.u32Height * 2;/*stream buffer size*/
		if (u32Profile >= 1)
		{
			stH265Attr.u32Profile = 0;
		}/*0:MP; */
		else
		{
			stH265Attr.u32Profile = u32Profile;
		}/*0:MP*/
		stH265Attr.bByFrame = HI_TRUE;/*get stream mode is slice mode or frame mode?*/
		//stH265Attr.u32BFrameNum = 0;/* 0: not support B frame; >=1: number of B frames */
		//stH265Attr.u32RefNum = 1;/* 0: default; number of refrence frame*/
		memcpy(&stVencChnAttr.stVeAttr.stAttrH265e, &stH265Attr, sizeof(VENC_ATTR_H265_S));

		if (SAMPLE_RC_CBR == enRcMode)
		{
			stVencChnAttr.stRcAttr.enRcMode = VENC_RC_MODE_H265CBR;
			stH265Cbr.u32Gop = (VIDEO_ENCODING_MODE_PAL == enNorm) ? 25 : 30;
			stH265Cbr.u32StatTime = 1; /* stream rate statics time(s) */
			stH265Cbr.u32SrcFrmRate = (VIDEO_ENCODING_MODE_PAL == enNorm) ? 25 : 30; /* input (vi) frame rate */
			stH265Cbr.fr32DstFrmRate = (VIDEO_ENCODING_MODE_PAL == enNorm) ? 25 : 30; /* target frame rate */
			stH265Cbr.u32BitRate = u32Bitrate;
			stH265Cbr.u32FluctuateLevel = 1; /* average bit rate */
			memcpy(&stVencChnAttr.stRcAttr.stAttrH265Cbr, &stH265Cbr, sizeof(VENC_ATTR_H265_CBR_S));
		}
		else if (SAMPLE_RC_FIXQP == enRcMode)
		{
			stVencChnAttr.stRcAttr.enRcMode = VENC_RC_MODE_H265FIXQP;
			stH265FixQp.u32Gop = (VIDEO_ENCODING_MODE_PAL == enNorm) ? 25 : 30;
			stH265FixQp.u32SrcFrmRate = (VIDEO_ENCODING_MODE_PAL == enNorm) ? 25 : 30;
			stH265FixQp.fr32DstFrmRate = (VIDEO_ENCODING_MODE_PAL == enNorm) ? 25 : 30;
			stH265FixQp.u32IQp = 20;
			stH265FixQp.u32PQp = 23;
			stH265FixQp.u32BQp = 25;
			memcpy(&stVencChnAttr.stRcAttr.stAttrH265FixQp, &stH265FixQp, sizeof(VENC_ATTR_H265_FIXQP_S));
		}
		else if (SAMPLE_RC_VBR == enRcMode)
		{
			stVencChnAttr.stRcAttr.enRcMode = VENC_RC_MODE_H265VBR;
			stH265Vbr.u32Gop = (VIDEO_ENCODING_MODE_PAL == enNorm) ? 25 : 30;
			stH265Vbr.u32StatTime = 1;
			stH265Vbr.u32SrcFrmRate = (VIDEO_ENCODING_MODE_PAL == enNorm) ? 25 : 30;
			stH265Vbr.fr32DstFrmRate = (VIDEO_ENCODING_MODE_PAL == enNorm) ? 25 : 30;
			stH265Vbr.u32MinQp = 10;
			stH265Vbr.u32MinIQp = 10;
			stH265Vbr.u32MaxQp = 50;
			stH265Vbr.u32MaxBitRate = u32Bitrate * 3;
			memcpy(&stVencChnAttr.stRcAttr.stAttrH265Vbr, &stH265Vbr, sizeof(VENC_ATTR_H265_VBR_S));
		}
		else
		{
			return HI_FAILURE;
		}
	}
	break;
	default:
		return HI_ERR_VENC_NOT_SUPPORT;
	}

	if (PT_MJPEG == enType || PT_JPEG == enType)
	{
		stVencChnAttr.stGopAttr.enGopMode = VENC_GOPMODE_NORMALP;
		stVencChnAttr.stGopAttr.stNormalP.s32IPQpDelta = 0;
	}
	else
	{
		memcpy(&stVencChnAttr.stGopAttr, pstGopAttr, sizeof(VENC_GOP_ATTR_S));
	}

	tmp_ret_int = HI_MPI_VENC_CreateChn(VencChn, &stVencChnAttr);
	if (HI_SUCCESS != tmp_ret_int)
	{
		SAMPLE_PRT("HI_MPI_VENC_CreateChn [%d] faild with %#x! ===\n", \
			VencChn, tmp_ret_int);
		return tmp_ret_int;
	}


	/******************************************
	step 2:  Start Recv Venc Pictures
	******************************************/
	tmp_ret_int = HI_MPI_VENC_StartRecvPic(VencChn);
	if (HI_SUCCESS != tmp_ret_int)
	{
		SAMPLE_PRT("HI_MPI_VENC_StartRecvPic faild with%#x! \n", tmp_ret_int);
		return HI_FAILURE;
	}

#endif
	return 0;
}

/*绑定信息*/
cp_int32_t	hi3519_av_bind_info(cp_hi3519_av_codec_t *hi3519_av_codec, cp_hi3519_av_conf_t *hi3519_av_conf)
{
	cp_int32_t					tmp_ret_int = 0;



	if (cp_hi3519_av_codec_mode_vi_stitch_vpss_venc == hi3519_av_codec->hacc.mode ||
		cp_hi3519_av_codec_mode_vi_fisheye_stitch_vpss_venc == hi3519_av_codec->hacc.mode ||
		cp_hi3519_av_codec_mode_vi_fisheye_process_vpss_venc == hi3519_av_codec->hacc.mode ||
		cp_hi3519_av_codec_mode_vi_fisheye_process_vpss_stitch_vpss_venc == hi3519_av_codec->hacc.mode) {

		if (cp_hi3519_av_codec_mode_vi_stitch_vpss_venc == hi3519_av_codec->hacc.mode) {
			/*绑定vi和 vpss*/
			tmp_ret_int = hi3519_av_bind_vi_vpss(hi3519_av_codec, hi3519_av_codec->av_conf);
			if (tmp_ret_int) {
				cp_module_log(error, hi3519_av_codec, "hi3519_av_bind_vi_vpss() error.");
				return -1;
			}
			cp_module_log(notice, hi3519_av_codec, "hi3519_av_bind_vi_vpss() successed.");
		}
		else if (cp_hi3519_av_codec_mode_vi_fisheye_stitch_vpss_venc == hi3519_av_codec->hacc.mode) {
			/*绑定vi fisheye和 vpss*/
			tmp_ret_int = hi3519_av_bind_vi_fisheye_vpss(hi3519_av_codec, hi3519_av_codec->av_conf);
			if (tmp_ret_int) {
				cp_module_log(error, hi3519_av_codec, "hi3519_av_bind_vi_fisheye_vpss() error.");
				return -1;
			}
			cp_module_log(notice, hi3519_av_codec, "hi3519_av_bind_vi_fisheye_vpss() successed.");
		}
		else {
			/*绑定vi 和 vpss*/
			tmp_ret_int = hi3519_av_bind_vi_process_vpss(hi3519_av_codec, hi3519_av_codec->av_conf);
			if (tmp_ret_int) {
				cp_module_log(error, hi3519_av_codec, "hi3519_av_bind_vi_process_vpss() error.");
				return -1;
			}
			cp_module_log(notice, hi3519_av_codec, "hi3519_av_bind_vi_process_vpss() successed.");

			if (cp_hi3519_av_codec_mode_vi_fisheye_process_vpss_stitch_vpss_venc == hi3519_av_codec->hacc.mode) {
				/*绑定vi 和 vpss*/
				tmp_ret_int = hi3519_av_bind_process_vpss_stitch_vpss(hi3519_av_codec, hi3519_av_codec->av_conf);
				if (tmp_ret_int) {
					cp_module_log(error, hi3519_av_codec, "hi3519_av_bind_process_vpss_stitch_vpss() error.");
					return -1;
				}
				cp_module_log(notice, hi3519_av_codec, "hi3519_av_bind_process_vpss_stitch_vpss() successed.");
			}
		}

		if (cp_hi3519_av_codec_mode_vi_fisheye_process_vpss_venc == hi3519_av_codec->hacc.mode) {
			/*绑定vpss 和 venc*/
			tmp_ret_int = hi3519_av_bind_process_vpss_venc(hi3519_av_codec, hi3519_av_codec->av_conf);
			if (tmp_ret_int) {
				cp_module_log(error, hi3519_av_codec, "hi3519_av_bind_process_vpss_venc() error.");
				return -1;
			}
			cp_module_log(notice, hi3519_av_codec, "hi3519_av_bind_process_vpss_venc() successed.");
		}
		else {
			/*绑定vpss 和 venc*/
			tmp_ret_int = hi3519_av_bind_stitch_vpss_venc(hi3519_av_codec, hi3519_av_codec->av_conf);
			if (tmp_ret_int) {
				cp_module_log(error, hi3519_av_codec, "hi3519_av_bind_stitch_vpss_venc() error.");
				return -1;
			}
			cp_module_log(notice, hi3519_av_codec, "hi3519_av_bind_stitch_vpss_venc() successed.");
		}
	}
	else {
		/*绑定vi fisheye 和 venc*/
		tmp_ret_int = hi3519_av_bind_vi_fisheye_venc(hi3519_av_codec, hi3519_av_codec->av_conf);
		if (tmp_ret_int) {
			cp_module_log(error, hi3519_av_codec, "hi3519_av_bind_vi_fisheye_venc() error.");
			return -1;
		}
		cp_module_log(notice, hi3519_av_codec, "hi3519_av_bind_vi_fisheye_venc() successed.");
	}
	return 0;
}


/*绑定vi 和 vpss*/
cp_int32_t	hi3519_av_bind_vi_vpss(cp_hi3519_av_codec_t *hi3519_av_codec, cp_hi3519_av_conf_t *hi3519_av_conf)
{
#if defined(CP_HI3519_MODE)
	cp_int32_t					i = 0;
	HI_S32						tmp_ret_int = HI_FAILURE;
	MPP_CHN_S					tmp_src_channel = { 0, };
	MPP_CHN_S					tmp_dest_channel = { 0, };




	tmp_src_channel.enModId = HI_ID_VIU;
	tmp_src_channel.s32DevId = 0;
	tmp_src_channel.s32ChnId = 1;
	tmp_dest_channel.enModId = HI_ID_VPSS;
	tmp_dest_channel.s32DevId = hi3519_av_conf->stitch_vpss_info.index;
	tmp_dest_channel.s32ChnId = hi3519_av_conf->stitch_vpss_info.vpss_list[1].index;

	tmp_ret_int = HI_MPI_SYS_Bind(&tmp_src_channel, &tmp_dest_channel);
	if (tmp_ret_int != HI_SUCCESS)
	{
		cp_module_log(error, hi3519_av_codec,
			"HI_MPI_SYS_Bind() dev[%d] vi[%d] bind group[%d] vpss[%d] failed. witherror_code[0x%x]",
			tmp_src_channel.s32DevId,
			tmp_src_channel.s32ChnId,
			tmp_dest_channel.s32DevId,
			tmp_dest_channel.s32ChnId,
			tmp_ret_int);
		return HI_FAILURE;
	} else {
		cp_module_log(notice, hi3519_av_codec,
			"HI_MPI_SYS_Bind() dev[%d] vi[%d] bind group[%d] vpss[%d] sucessed.",
			tmp_src_channel.s32DevId,
			tmp_src_channel.s32ChnId,
			tmp_dest_channel.s32DevId,
			tmp_dest_channel.s32ChnId);
	}

	tmp_src_channel.enModId = HI_ID_VIU;
	tmp_src_channel.s32DevId = 0;
	tmp_src_channel.s32ChnId = 0;
	tmp_dest_channel.enModId = HI_ID_VPSS;
	tmp_dest_channel.s32DevId = hi3519_av_conf->stitch_vpss_info.index;
	tmp_dest_channel.s32ChnId = hi3519_av_conf->stitch_vpss_info.vpss_list[CP_HI3519_AV_CODEC_USED_VPSS_CHANNEL_NUMBER].index;

	tmp_ret_int = HI_MPI_SYS_Bind(&tmp_src_channel, &tmp_dest_channel);
	if (tmp_ret_int != HI_SUCCESS)
	{
		cp_module_log(error, hi3519_av_codec,
			"HI_MPI_SYS_Bind() dev[%d] vi[%d] bind group[%d] vpss[%d] failed. witherror_code[0x%x]",
			tmp_src_channel.s32DevId,
			tmp_src_channel.s32ChnId,
			tmp_dest_channel.s32DevId,
			tmp_dest_channel.s32ChnId,
			tmp_ret_int);
		return HI_FAILURE;
	} else {
		cp_module_log(notice, hi3519_av_codec,
			"HI_MPI_SYS_Bind() dev[%d] vi[%d] bind group[%d] vpss[%d] successed.",
			tmp_src_channel.s32DevId,
			tmp_src_channel.s32ChnId,
			tmp_dest_channel.s32DevId,
			tmp_dest_channel.s32ChnId);
	}

#if 0
	for (i = 0; i < cp_ary_size(hi3519_av_conf->channel_list); i++) {
		tmp_ret_int = SAMPLE_COMM_VI_BindVpss(hi3519_av_conf->channel_list[i].channel_config.enViMode);
		if (HI_SUCCESS != tmp_ret_int)
		{
			cp_module_log(error, hi3519_av_codec, "SAMPLE_COMM_VI_BindVpss() error");
			return -1;
		}
	}
#endif

#endif

	return 0;
}

/*绑定vi fisheye和 vpss*/
cp_int32_t	hi3519_av_bind_vi_fisheye_vpss(cp_hi3519_av_codec_t *hi3519_av_codec, cp_hi3519_av_conf_t *hi3519_av_conf)
{
#if defined(CP_HI3519_MODE)
	cp_int32_t					i = 0;
	HI_S32						tmp_ret_int = HI_FAILURE;
	MPP_CHN_S					tmp_src_channel = { 0, };
	MPP_CHN_S					tmp_dest_channel = { 0, };




	tmp_src_channel.enModId = HI_ID_VIU;
	tmp_src_channel.s32DevId = 0;
	tmp_src_channel.s32ChnId = CP_HI3519_AV_CODEC_BEGIN_EXT_VI_CHANNEL_NUMBER + 1;
	tmp_dest_channel.enModId = HI_ID_VPSS;
	tmp_dest_channel.s32DevId = hi3519_av_conf->stitch_vpss_info.index;
	tmp_dest_channel.s32ChnId = hi3519_av_conf->stitch_vpss_info.vpss_list[1].index;

	tmp_ret_int = HI_MPI_SYS_Bind(&tmp_src_channel, &tmp_dest_channel);
	if (tmp_ret_int != HI_SUCCESS)
	{
		cp_module_log(error, hi3519_av_codec,
			"HI_MPI_SYS_Bind() dev[%d] vi[%d] bind group[%d] vpss[%d] failed. witherror_code[0x%x]",
			tmp_src_channel.s32DevId,
			tmp_src_channel.s32ChnId,
			tmp_dest_channel.s32DevId,
			tmp_dest_channel.s32ChnId,
			tmp_ret_int);
		return HI_FAILURE;
	} else {
		cp_module_log(notice, hi3519_av_codec,
			"HI_MPI_SYS_Bind() dev[%d] vi[%d] bind group[%d] vpss[%d] successed.",
			tmp_src_channel.s32DevId,
			tmp_src_channel.s32ChnId,
			tmp_dest_channel.s32DevId,
			tmp_dest_channel.s32ChnId);
	}

	tmp_src_channel.enModId = HI_ID_VIU;
	tmp_src_channel.s32DevId = 0;
	tmp_src_channel.s32ChnId = CP_HI3519_AV_CODEC_BEGIN_EXT_VI_CHANNEL_NUMBER + 0;
	tmp_dest_channel.enModId = HI_ID_VPSS;
	tmp_dest_channel.s32DevId = hi3519_av_conf->stitch_vpss_info.index;
	tmp_dest_channel.s32ChnId = hi3519_av_conf->stitch_vpss_info.vpss_list[CP_HI3519_AV_CODEC_USED_VPSS_CHANNEL_NUMBER].index;

	tmp_ret_int = HI_MPI_SYS_Bind(&tmp_src_channel, &tmp_dest_channel);
	if (tmp_ret_int != HI_SUCCESS)
	{
		cp_module_log(error, hi3519_av_codec,
			"HI_MPI_SYS_Bind() dev[%d] vi[%d] bind group[%d] vpss[%d] failed. witherror_code[0x%x]",
			tmp_src_channel.s32DevId,
			tmp_src_channel.s32ChnId,
			tmp_dest_channel.s32DevId,
			tmp_dest_channel.s32ChnId,
			tmp_ret_int);
		return HI_FAILURE;
	} else {
		cp_module_log(notice, hi3519_av_codec,
			"HI_MPI_SYS_Bind() dev[%d] vi[%d] bind group[%d] vpss[%d] successed.",
			tmp_src_channel.s32DevId,
			tmp_src_channel.s32ChnId,
			tmp_dest_channel.s32DevId,
			tmp_dest_channel.s32ChnId);
	}

#endif

	return 0;
}

/*绑定vi 和 process_vpss*/
cp_int32_t	hi3519_av_bind_vi_process_vpss(cp_hi3519_av_codec_t *hi3519_av_codec, cp_hi3519_av_conf_t *hi3519_av_conf)
{
#if defined(CP_HI3519_MODE)
	cp_int32_t					i = 0;
	HI_S32						tmp_ret_int = HI_FAILURE;
	MPP_CHN_S					tmp_src_channel = { 0, };
	MPP_CHN_S					tmp_dest_channel = { 0, };




	tmp_src_channel.enModId = HI_ID_VIU;
	tmp_src_channel.s32DevId = 0;
	tmp_src_channel.s32ChnId = 1;
	tmp_dest_channel.enModId = HI_ID_VPSS;
	tmp_dest_channel.s32DevId = hi3519_av_conf->process_vpss_info[0].index;
	tmp_dest_channel.s32ChnId = hi3519_av_conf->process_vpss_info[0].vpss_list[CP_HI3519_AV_CODEC_USED_VPSS_CHANNEL_NUMBER].index;

	tmp_ret_int = HI_MPI_SYS_Bind(&tmp_src_channel, &tmp_dest_channel);
	if (tmp_ret_int != HI_SUCCESS)
	{
		cp_module_log(error, hi3519_av_codec,
			"HI_MPI_SYS_Bind() dev[%d] vi[%d] bind group[%d] vpss[%d] failed. witherror_code[0x%x]",
			tmp_src_channel.s32DevId,
			tmp_src_channel.s32ChnId,
			tmp_dest_channel.s32DevId,
			tmp_dest_channel.s32ChnId,
			tmp_ret_int);
		return HI_FAILURE;
	}
	else {
		cp_module_log(notice, hi3519_av_codec,
			"HI_MPI_SYS_Bind() dev[%d] vi[%d] bind group[%d] vpss[%d] successed.",
			tmp_src_channel.s32DevId,
			tmp_src_channel.s32ChnId,
			tmp_dest_channel.s32DevId,
			tmp_dest_channel.s32ChnId,
			tmp_ret_int);
	}

	tmp_src_channel.enModId = HI_ID_VIU;
	tmp_src_channel.s32DevId = 0;
	tmp_src_channel.s32ChnId = 0;
	tmp_dest_channel.enModId = HI_ID_VPSS;
	tmp_dest_channel.s32DevId = hi3519_av_conf->process_vpss_info[1].index;
	tmp_dest_channel.s32ChnId = hi3519_av_conf->process_vpss_info[1].vpss_list[CP_HI3519_AV_CODEC_USED_VPSS_CHANNEL_NUMBER].index;

	tmp_ret_int = HI_MPI_SYS_Bind(&tmp_src_channel, &tmp_dest_channel);
	if (tmp_ret_int != HI_SUCCESS)
	{
		cp_module_log(error, hi3519_av_codec,
			"HI_MPI_SYS_Bind() dev[%d] vi[%d] bind group[%d] vpss[%d] failed. witherror_code[0x%x]",
			tmp_src_channel.s32DevId,
			tmp_src_channel.s32ChnId,
			tmp_dest_channel.s32DevId,
			tmp_dest_channel.s32ChnId,
			tmp_ret_int);
		return HI_FAILURE;
	}
	else {
		cp_module_log(notice, hi3519_av_codec,
			"HI_MPI_SYS_Bind() dev[%d] vi[%d] bind group[%d] vpss[%d] successed.",
			tmp_src_channel.s32DevId,
			tmp_src_channel.s32ChnId,
			tmp_dest_channel.s32DevId,
			tmp_dest_channel.s32ChnId,
			tmp_ret_int);
	}

#endif

	return 0;
}

/*绑定vi 和 process_vpss*/
cp_int32_t	hi3519_av_bind_vi_fisheye_process_vpss(cp_hi3519_av_codec_t *hi3519_av_codec, cp_hi3519_av_conf_t *hi3519_av_conf)
{
#if defined(CP_HI3519_MODE)
	cp_int32_t					i = 0;
	HI_S32						tmp_ret_int = HI_FAILURE;
	MPP_CHN_S					tmp_src_channel = { 0, };
	MPP_CHN_S					tmp_dest_channel = { 0, };




	tmp_src_channel.enModId = HI_ID_VIU;
	tmp_src_channel.s32DevId = 0;
	tmp_src_channel.s32ChnId = CP_HI3519_AV_CODEC_BEGIN_EXT_VI_CHANNEL_NUMBER + 1;
	tmp_dest_channel.enModId = HI_ID_VPSS;
	tmp_dest_channel.s32DevId = hi3519_av_conf->process_vpss_info[0].index;
	tmp_dest_channel.s32ChnId = hi3519_av_conf->process_vpss_info[0].vpss_list[CP_HI3519_AV_CODEC_USED_VPSS_CHANNEL_NUMBER].index;

	tmp_ret_int = HI_MPI_SYS_Bind(&tmp_src_channel, &tmp_dest_channel);
	if (tmp_ret_int != HI_SUCCESS)
	{
		cp_module_log(error, hi3519_av_codec,
			"HI_MPI_SYS_Bind() dev[%d] vi[%d] bind group[%d] vpss[%d] failed. witherror_code[0x%x]",
			tmp_src_channel.s32DevId,
			tmp_src_channel.s32ChnId,
			tmp_dest_channel.s32DevId,
			tmp_dest_channel.s32ChnId,
			tmp_ret_int);
		return HI_FAILURE;
	}
	else {
		cp_module_log(notice, hi3519_av_codec,
			"HI_MPI_SYS_Bind() dev[%d] vi[%d] bind group[%d] vpss[%d] successed.",
			tmp_src_channel.s32DevId,
			tmp_src_channel.s32ChnId,
			tmp_dest_channel.s32DevId,
			tmp_dest_channel.s32ChnId,
			tmp_ret_int);
	}

	tmp_src_channel.enModId = HI_ID_VIU;
	tmp_src_channel.s32DevId = 0;
	tmp_src_channel.s32ChnId = CP_HI3519_AV_CODEC_BEGIN_EXT_VI_CHANNEL_NUMBER + 0;
	tmp_dest_channel.enModId = HI_ID_VPSS;
	tmp_dest_channel.s32DevId = hi3519_av_conf->process_vpss_info[1].index;
	tmp_dest_channel.s32ChnId = hi3519_av_conf->process_vpss_info[1].vpss_list[CP_HI3519_AV_CODEC_USED_VPSS_CHANNEL_NUMBER].index;

	tmp_ret_int = HI_MPI_SYS_Bind(&tmp_src_channel, &tmp_dest_channel);
	if (tmp_ret_int != HI_SUCCESS)
	{
		cp_module_log(error, hi3519_av_codec,
			"HI_MPI_SYS_Bind() dev[%d] vi[%d] bind group[%d] vpss[%d] failed. witherror_code[0x%x]",
			tmp_src_channel.s32DevId,
			tmp_src_channel.s32ChnId,
			tmp_dest_channel.s32DevId,
			tmp_dest_channel.s32ChnId,
			tmp_ret_int);
		return HI_FAILURE;
	}
	else {
		cp_module_log(notice, hi3519_av_codec,
			"HI_MPI_SYS_Bind() dev[%d] vi[%d] bind group[%d] vpss[%d] successed.",
			tmp_src_channel.s32DevId,
			tmp_src_channel.s32ChnId,
			tmp_dest_channel.s32DevId,
			tmp_dest_channel.s32ChnId,
			tmp_ret_int);
	}

#endif

	return 0;
}

/*绑定vpss 和 process_vpss*/
cp_int32_t	hi3519_av_bind_process_vpss_stitch_vpss(cp_hi3519_av_codec_t *hi3519_av_codec, cp_hi3519_av_conf_t *hi3519_av_conf)
{
#if defined(CP_HI3519_MODE)
	cp_int32_t					i = 0;
	HI_S32						tmp_ret_int = HI_FAILURE;
	MPP_CHN_S					tmp_src_channel = { 0, };
	MPP_CHN_S					tmp_dest_channel = { 0, };




	tmp_src_channel.enModId = HI_ID_VPSS;
	tmp_src_channel.s32DevId = hi3519_av_conf->process_vpss_info[0].index;
	tmp_src_channel.s32ChnId = hi3519_av_conf->process_vpss_info[0].vpss_list[CP_HI3519_AV_CODEC_USED_VPSS_CHANNEL_NUMBER + 1].index;
	tmp_dest_channel.enModId = HI_ID_VPSS;
	tmp_dest_channel.s32DevId = hi3519_av_conf->stitch_vpss_info.index;
	tmp_dest_channel.s32ChnId = hi3519_av_conf->stitch_vpss_info.vpss_list[0].index;

	tmp_ret_int = HI_MPI_SYS_Bind(&tmp_src_channel, &tmp_dest_channel);
	if (tmp_ret_int != HI_SUCCESS)
	{
		cp_module_log(error, hi3519_av_codec,
			"HI_MPI_SYS_Bind() group[%d] vpss[%d] bind group[%d] vpss[%d] failed witherror_code[0x%x]",
			tmp_src_channel.s32DevId,
			tmp_src_channel.s32ChnId,
			tmp_dest_channel.s32DevId,
			tmp_dest_channel.s32ChnId,
			tmp_ret_int);
		return HI_FAILURE;
	}
	else {
		cp_module_log(notice, hi3519_av_codec,
			"HI_MPI_SYS_Bind() group[%d] vpss[%d] bind group[%d] vpss[%d] successed.",
			tmp_src_channel.s32DevId,
			tmp_src_channel.s32ChnId,
			tmp_dest_channel.s32DevId,
			tmp_dest_channel.s32ChnId);
	}

	tmp_src_channel.enModId = HI_ID_VPSS;
	tmp_src_channel.s32DevId = hi3519_av_conf->process_vpss_info[1].index;
	tmp_src_channel.s32ChnId = hi3519_av_conf->process_vpss_info[1].vpss_list[CP_HI3519_AV_CODEC_USED_VPSS_CHANNEL_NUMBER + 1].index;
	tmp_dest_channel.enModId = HI_ID_VPSS;
	tmp_dest_channel.s32DevId = hi3519_av_conf->stitch_vpss_info.index;
	tmp_dest_channel.s32ChnId = hi3519_av_conf->stitch_vpss_info.vpss_list[1].index;

	tmp_ret_int = HI_MPI_SYS_Bind(&tmp_src_channel, &tmp_dest_channel);
	if (tmp_ret_int != HI_SUCCESS)
	{
		cp_module_log(error, hi3519_av_codec,
			"HI_MPI_SYS_Bind() group[%d] vpss[%d] bind group[%d] vpss[%d] failed witherror_code[0x%x]",
			tmp_src_channel.s32DevId,
			tmp_src_channel.s32ChnId,
			tmp_dest_channel.s32DevId,
			tmp_dest_channel.s32ChnId,
			tmp_ret_int);
		return HI_FAILURE;
	}
	else {
		cp_module_log(notice, hi3519_av_codec,
			"HI_MPI_SYS_Bind() group[%d] vpss[%d] bind group[%d] vpss[%d] successed.",
			tmp_src_channel.s32DevId,
			tmp_src_channel.s32ChnId,
			tmp_dest_channel.s32DevId,
			tmp_dest_channel.s32ChnId);
	}

#endif
	return 0;
}

/*绑定vpss 和 process_vpss*/
cp_int32_t	hi3519_av_bind_process_vpss_ext_channel_stitch_vpss(cp_hi3519_av_codec_t *hi3519_av_codec, cp_hi3519_av_conf_t *hi3519_av_conf)
{
#if defined(CP_HI3519_MODE)
	cp_int32_t					i = 0;
	HI_S32						tmp_ret_int = HI_FAILURE;
	MPP_CHN_S					tmp_src_channel = { 0, };
	MPP_CHN_S					tmp_dest_channel = { 0, };




	tmp_src_channel.enModId = HI_ID_VPSS;
	tmp_src_channel.s32DevId = hi3519_av_conf->process_vpss_info[0].index;
	tmp_src_channel.s32ChnId = hi3519_av_conf->process_vpss_info[0].vpss_list[CP_HI3519_AV_CODEC_USED_VPSS_CHANNEL_NUMBER].ext_index;
	tmp_dest_channel.enModId = HI_ID_VPSS;
	tmp_dest_channel.s32DevId = hi3519_av_conf->stitch_vpss_info.index;
	tmp_dest_channel.s32ChnId = hi3519_av_conf->stitch_vpss_info.vpss_list[CP_HI3519_AV_CODEC_USED_VPSS_CHANNEL_NUMBER].index;

	tmp_ret_int = HI_MPI_SYS_Bind(&tmp_src_channel, &tmp_dest_channel);
	if (tmp_ret_int != HI_SUCCESS)
	{
		cp_module_log(error, hi3519_av_codec,
			"HI_MPI_SYS_Bind() group[%d] vpss[%d] bind group[%d] vpss[%d] failed witherror_code[0x%x]",
			tmp_src_channel.s32DevId,
			tmp_src_channel.s32ChnId,
			tmp_dest_channel.s32DevId,
			tmp_dest_channel.s32ChnId,
			tmp_ret_int);
		return HI_FAILURE;
	}
	else {
		cp_module_log(notice, hi3519_av_codec,
			"HI_MPI_SYS_Bind() group[%d] vpss[%d] bind group[%d] vpss[%d] successed.",
			tmp_src_channel.s32DevId,
			tmp_src_channel.s32ChnId,
			tmp_dest_channel.s32DevId,
			tmp_dest_channel.s32ChnId);
	}

	tmp_src_channel.enModId = HI_ID_VPSS;
	tmp_src_channel.s32DevId = hi3519_av_conf->process_vpss_info[1].index;
	tmp_src_channel.s32ChnId = hi3519_av_conf->process_vpss_info[1].vpss_list[CP_HI3519_AV_CODEC_USED_VPSS_CHANNEL_NUMBER].ext_index;
	tmp_dest_channel.enModId = HI_ID_VPSS;
	tmp_dest_channel.s32DevId = hi3519_av_conf->stitch_vpss_info.index;
	tmp_dest_channel.s32ChnId = hi3519_av_conf->stitch_vpss_info.vpss_list[1].index;

	tmp_ret_int = HI_MPI_SYS_Bind(&tmp_src_channel, &tmp_dest_channel);
	if (tmp_ret_int != HI_SUCCESS)
	{
		cp_module_log(error, hi3519_av_codec,
			"HI_MPI_SYS_Bind() group[%d] vpss[%d] bind group[%d] vpss[%d] failed witherror_code[0x%x]",
			tmp_src_channel.s32DevId,
			tmp_src_channel.s32ChnId,
			tmp_dest_channel.s32DevId,
			tmp_dest_channel.s32ChnId,
			tmp_ret_int);
		return HI_FAILURE;
	}
	else {
		cp_module_log(notice, hi3519_av_codec,
			"HI_MPI_SYS_Bind() group[%d] vpss[%d] bind group[%d] vpss[%d] successed.",
			tmp_src_channel.s32DevId,
			tmp_src_channel.s32ChnId,
			tmp_dest_channel.s32DevId,
			tmp_dest_channel.s32ChnId);
	}

#endif
	return 0;
}

/*绑定process vpss 和 venc*/
cp_int32_t	hi3519_av_bind_process_vpss_venc(cp_hi3519_av_codec_t *hi3519_av_codec, cp_hi3519_av_conf_t *hi3519_av_conf)
{
#if defined(CP_HI3519_MODE)
	cp_int32_t					i = 0;
	HI_S32						tmp_ret_int = HI_FAILURE;



	for (i = 0; i < cp_ary_size(hi3519_av_conf->venc_list); i++) {
		tmp_ret_int = SAMPLE_COMM_VENC_BindVpss(hi3519_av_conf->venc_list[i].index,
			hi3519_av_conf->process_vpss_info[hi3519_av_codec->hacc.vi_channel].index,
			hi3519_av_conf->process_vpss_info[hi3519_av_codec->hacc.vi_channel].vpss_list[CP_HI3519_AV_CODEC_USED_VPSS_CHANNEL_NUMBER].index);
		if (HI_SUCCESS != tmp_ret_int)
		{
			cp_module_log(error, hi3519_av_codec,
				"SAMPLE_COMM_VENC_BindVpss() error. venc[%d] vpss group[%d] channel[%d].error_code[0x%x].",
				hi3519_av_conf->venc_list[i].index,
				hi3519_av_conf->process_vpss_info[hi3519_av_codec->hacc.vi_channel].index,
				hi3519_av_conf->process_vpss_info[hi3519_av_codec->hacc.vi_channel].vpss_list[CP_HI3519_AV_CODEC_USED_VPSS_CHANNEL_NUMBER].index,
				tmp_ret_int);
			return -1;
		}
		else {
			cp_module_log(notice, hi3519_av_codec,
				"SAMPLE_COMM_VENC_BindVpss() successed. venc[%d] vpss group[%d] channel[%d].",
				hi3519_av_conf->venc_list[i].index,
				hi3519_av_conf->process_vpss_info[hi3519_av_codec->hacc.vi_channel].index,
				hi3519_av_conf->process_vpss_info[hi3519_av_codec->hacc.vi_channel].vpss_list[CP_HI3519_AV_CODEC_USED_VPSS_CHANNEL_NUMBER].index);
		}
	}

#endif

	return 0;
}

/*绑定vpss 和 venc*/
cp_int32_t	hi3519_av_bind_stitch_vpss_venc(cp_hi3519_av_codec_t *hi3519_av_codec, cp_hi3519_av_conf_t *hi3519_av_conf)
{
#if defined(CP_HI3519_MODE)
	cp_int32_t					i = 0;
	HI_S32						tmp_ret_int = HI_FAILURE;



	for (i = 0; i < cp_ary_size(hi3519_av_conf->venc_list); i++) {
		tmp_ret_int = SAMPLE_COMM_VENC_BindVpss(hi3519_av_conf->venc_list[i].index,
			hi3519_av_conf->stitch_vpss_info.index,
			hi3519_av_conf->stitch_vpss_info.vpss_list[1].index);
		if (HI_SUCCESS != tmp_ret_int)
		{
			cp_module_log(error, hi3519_av_codec,
				"SAMPLE_COMM_VENC_BindVpss() error.error_code[0x%x]",
				tmp_ret_int);
			return -1;
		}
		else {
			cp_module_log(notice, hi3519_av_codec,
				"SAMPLE_COMM_VENC_BindVpss() successed. venc[%d] vpss group[%d] channel[%d].",
				hi3519_av_conf->venc_list[i].index,
				hi3519_av_conf->stitch_vpss_info.index,
				hi3519_av_conf->stitch_vpss_info.vpss_list[1].index);
		}
	}

#endif

	return 0;
}

/*绑定vi 和 venc*/
cp_int32_t	hi3519_av_bind_vi_fisheye_venc(cp_hi3519_av_codec_t *hi3519_av_codec, cp_hi3519_av_conf_t *hi3519_av_conf)
{
#if defined(CP_HI3519_MODE)
	cp_int32_t					i = 0;
	HI_S32						tmp_ret_int = HI_FAILURE;
	MPP_CHN_S					tmp_src_channel = { 0, };
	MPP_CHN_S					tmp_dest_channel = { 0, };




	tmp_src_channel.enModId = HI_ID_VIU;
	tmp_src_channel.s32DevId = 0;
	tmp_src_channel.s32ChnId = hi3519_av_codec->hacc.vi_channel;
	tmp_dest_channel.enModId = HI_ID_VENC;
	tmp_dest_channel.s32DevId = 0;
	tmp_dest_channel.s32ChnId = hi3519_av_conf->venc_list[0].index;

	tmp_ret_int = HI_MPI_SYS_Bind(&tmp_src_channel, &tmp_dest_channel);
	if (tmp_ret_int != HI_SUCCESS)
	{
		cp_module_log(error, hi3519_av_codec,
			"HI_MPI_SYS_Bind() vi[%d] bind venc[%d] failed witherror_code[0x%x]",
			tmp_src_channel.s32ChnId,
			tmp_dest_channel.s32ChnId,
			tmp_ret_int);
		return HI_FAILURE;
	}
	else {
		cp_module_log(notice, hi3519_av_codec,
			"HI_MPI_SYS_Bind() vi[%d] bind venc[%d] successed",
			tmp_src_channel.s32ChnId,
			tmp_dest_channel.s32ChnId);
	}

#endif

	return 0;
}

/*开始获取数据hi3519 venc */
cp_int32_t	start_hi3519_av_get_stream(cp_hi3519_av_codec_t *hi3519_av_codec, cp_hi3519_av_conf_t *hi3519_av_conf)
{
#if defined(CP_HI3519_MODE)
	cp_int32_t					i = 0;
	cp_int32_t					tmp_venc_channels = 0;
	HI_S32						tmp_ret_int = HI_FAILURE;


	for (i = 0; i < cp_ary_size(hi3519_av_conf->venc_list); i++) {
		if (!hi3519_av_conf->venc_list[i].is_enc) {
			continue;
		}
		tmp_ret_int = HI_MPI_VENC_GetChnAttr(hi3519_av_conf->venc_list[i].index, &hi3519_av_conf->venc_list[i].attr);
		if (tmp_ret_int != HI_SUCCESS) {
			cp_module_log(error, hi3519_av_codec,
				"HI_MPI_VENC_GetChnAttr channel[%d] failed.error_code[0x%x]",
				hi3519_av_conf->venc_list[i].index,
				tmp_ret_int);
			return -1;
		}
		hi3519_av_conf->venc_list[i].payload = hi3519_av_conf->venc_list[i].attr.stVeAttr.enType;

		tmp_ret_int = SAMPLE_COMM_VENC_GetFilePostfix(hi3519_av_conf->venc_list[i].payload, hi3519_av_conf->venc_list[i].file_post_fix);
		if (tmp_ret_int != HI_SUCCESS) {
			cp_module_log(error, hi3519_av_codec,
				"SAMPLE_COMM_VENC_GetFilePostfix channel[%d] failed.error_code[0x%x]",
				hi3519_av_conf->venc_list[i].index,
				tmp_ret_int);
			return -2;
		}

		hi3519_av_conf->venc_list[i].fd = HI_MPI_VENC_GetFd(hi3519_av_conf->venc_list[i].index);
		if (hi3519_av_conf->venc_list[i].fd < 0) {
			cp_module_log(error, hi3519_av_codec,
				"HI_MPI_VENC_GetFd channel[%d] failed.",
				hi3519_av_conf->venc_list[i].index);
			return -3;
		}

		tmp_ret_int = HI_MPI_VENC_GetStreamBufInfo(hi3519_av_conf->venc_list[i].index, &hi3519_av_conf->venc_list[i].stream_buf_info);
		if (HI_SUCCESS != tmp_ret_int) {
			cp_module_log(error, hi3519_av_codec,
				"HI_MPI_VENC_GetStreamBufInfo channel[%d] failed.error_code[0x%x]",
				hi3519_av_conf->venc_list[i].index,
				tmp_ret_int);
			return -4;
		}

		++tmp_venc_channels;
	}

	//如果存在需要编码的设备，则开启线程处理
	if (tmp_venc_channels > 0) {
		hi3519_av_conf->is_process_stream = cp_true;
		tmp_ret_int = start_hi3519_av_get_stream_thread(hi3519_av_codec, hi3519_av_conf);
		if (tmp_ret_int) {
			cp_module_log(error, hi3519_av_codec, "start_hi3519_av_get_stream_thread() error.");
			return -4;
		}
	}

#endif
	return 0;
}

/*开始获取数据hi3519 venc 线程*/
cp_int32_t	start_hi3519_av_get_stream_thread(cp_hi3519_av_codec_t *hi3519_av_codec, cp_hi3519_av_conf_t *hi3519_av_conf)
{
	hi3519_av_conf->thread = cp_create_thread(hi3519_av_codec->manager->app, hi3519_av_stream_proc, hi3519_av_codec);
	if (!hi3519_av_conf->thread) {
		cp_module_log(error, hi3519_av_codec, "cp_create_thread() hi3519_av_stream_proc() failed!");
		return -1;
	}
	return 0;
}

/*处理媒体流数据*/
cp_void_t	hi3519_av_stream_proc(cp_void_t* codec)
{
#if defined(CP_HI3519_MODE)
	cp_int32_t						i = 0;
	cp_int32_t						tmp_ret_int = 0;
	cp_int32_t						tmp_max_fd = 0;
	cp_void_t						*tmp_max_buf = CP_NULL;
	cp_void_t						*tmp_buf = CP_NULL;
	fd_set							tmp_read_fds;
	struct timeval					tmp_time_val;
	VENC_CHN_STAT_S					tmp_stat = { 0, };
	VENC_STREAM_S					tmp_stream = { 0, };
	cp_hi3519_av_codec_t			*tmp_hi3519_av_codec = (cp_hi3519_av_codec_t*)codec;
	cp_hi3519_av_conf_t				*tmp_hi3519_av_conf = tmp_hi3519_av_codec->av_conf;



	tmp_time_val.tv_sec = 2;
	tmp_time_val.tv_usec = 0;

	tmp_max_buf = malloc(sizeof(VENC_PACK_S) * CP_HI3519_AV_CODEC_MAX_PACKS_SIZE);
	if (NULL == tmp_max_buf) {
		cp_module_log(error, tmp_hi3519_av_codec,
			"malloc memory[%d] failed!",
			sizeof(VENC_PACK_S) * CP_HI3519_AV_CODEC_MAX_PACKS_SIZE);
		return;
	}
	tmp_buf = tmp_max_buf;

	while (cp_true == tmp_hi3519_av_conf->is_process_stream)
	{
		FD_ZERO(&tmp_read_fds);
		for (i = 0; i < cp_ary_size(tmp_hi3519_av_conf->venc_list); i++) {
			if (!tmp_hi3519_av_conf->venc_list[i].is_enc) {
				continue;
			}
			FD_SET(tmp_hi3519_av_conf->venc_list[i].fd, &tmp_read_fds);

			if (tmp_max_fd < tmp_hi3519_av_conf->venc_list[i].fd) {
				tmp_max_fd = tmp_hi3519_av_conf->venc_list[i].fd;
			}
		}

		tmp_ret_int = select(tmp_max_fd + 1, &tmp_read_fds, NULL, NULL, &tmp_time_val);
		if (tmp_ret_int < 0) {
			cp_module_log(error, tmp_hi3519_av_codec, "select failed!error_code[0x%x]", tmp_ret_int);
			cp_sleep_ns(0, CP_HI3519_AV_CODEC_ERROR_SLEEP_INTERVAL_NS);
			continue;
		}
		else if (tmp_ret_int == 0) {
			//cp_module_log(error, tmp_hi3519_av_codec, "get venc stream time out, exit thread");
			continue;
		}
		else {
			for (i = 0; i < cp_ary_size(tmp_hi3519_av_conf->venc_list); i++) {

				if (FD_ISSET(tmp_hi3519_av_conf->venc_list[i].fd, &tmp_read_fds)) {
					/*******************************************************
					step 2.1 : query how many packs in one-frame stream.
					*******************************************************/
					cp_memset(&tmp_stream, 0, cp_sizeof(tmp_stream));
					tmp_ret_int = HI_MPI_VENC_Query(tmp_hi3519_av_conf->venc_list[i].index, &tmp_stat);
					if (HI_SUCCESS != tmp_ret_int) {
#if defined(CP_HI3519_PRINT_LOG)
						cp_module_log(error, tmp_hi3519_av_codec,
							"HI_MPI_VENC_Query channel[%d] failed.error_code[0x%x]\n",
							tmp_hi3519_av_conf->venc_list[i].index,
							tmp_ret_int);
#endif
						continue;
					}

					/*******************************************************
					step 2.2 :suggest to check both u32CurPacks and u32LeftStreamFrames at the same time,for example:
					if(0 == stStat.u32CurPacks || 0 == stStat.u32LeftStreamFrames)
					{
					cp_module_log(error, hi3519_av_codec, "NOTE: Current  frame is NULL!\n");
					continue;
					}
					*******************************************************/
					if (0 == tmp_stat.u32CurPacks || 0 == tmp_stat.u32LeftStreamFrames) {
#if defined(CP_HI3519_PRINT_LOG)
						cp_module_log(error, tmp_hi3519_av_codec,
							"note: channel[%d] current frame is null!",
							tmp_hi3519_av_conf->venc_list[i].index);
#endif
						continue;
					}
					/*******************************************************
					step 2.3 : malloc corresponding number of pack nodes.
					*******************************************************/
					if (tmp_stat.u32CurPacks > CP_HI3519_AV_CODEC_MAX_PACKS_SIZE) {
						tmp_buf = malloc(sizeof(VENC_PACK_S) * tmp_stat.u32CurPacks);
						if (NULL == tmp_buf)	{
							cp_module_log(error, tmp_hi3519_av_codec,
								"malloc stream pack failed channel[%d]!",
								tmp_hi3519_av_conf->venc_list[i].index);
							continue;
						}
					}
					else {
						tmp_buf = tmp_max_buf;
					}
					memset(tmp_buf, 0, sizeof(VENC_PACK_S) * tmp_stat.u32CurPacks);
					tmp_stream.pstPack = (VENC_PACK_S*)tmp_buf;

					/*******************************************************
					step 2.4 : call mpi to get one-frame stream
					*******************************************************/
					tmp_stream.u32PackCount = tmp_stat.u32CurPacks;
					tmp_ret_int = HI_MPI_VENC_GetStream(tmp_hi3519_av_conf->venc_list[i].index,
						&tmp_stream, -1);
					if (HI_SUCCESS != tmp_ret_int) {
						if (tmp_stat.u32CurPacks > CP_HI3519_AV_CODEC_MAX_PACKS_SIZE) {
							free(tmp_buf);
						}
						cp_module_log(error, tmp_hi3519_av_codec,
							"HI_MPI_VENC_GetStream() failed channel[%d]!error_code[0x%x]",
							tmp_hi3519_av_conf->venc_list[i].index,
							tmp_ret_int);
						continue;
					}

					/*******************************************************
					step 2.5 : save frame to file
					*******************************************************/
#ifndef __HuaweiLite__
#if defined(CP_IPC_CODEC_SEND_RTP)
					tmp_ret_int = hi3519_av_send_memory_stream(tmp_hi3519_av_codec, &tmp_hi3519_av_conf->venc_list[i], &tmp_stream);
#else
					tmp_ret_int = hi3519_av_save_memory_stream(tmp_hi3519_av_codec, &tmp_hi3519_av_conf->venc_list[i], &tmp_stream);
#endif
					if (HI_SUCCESS != tmp_ret_int) {
						cp_module_log(error, tmp_hi3519_av_codec,
							"hi3519_av_save_memory_stream() failed channel[%d]!error_code[0x%x]",
							tmp_hi3519_av_conf->venc_list[i].index,
							tmp_ret_int);
					}
#else
#if defined(CP_IPC_CODEC_SEND_RTP)
					tmp_ret_int = hi3519_av_send_physical_stream(tmp_hi3519_av_codec, &tmp_hi3519_av_conf->venc_list[i], &tmp_stream);
#else
					tmp_ret_int = hi3519_av_save_physical_stream(tmp_hi3519_av_codec, &tmp_hi3519_av_conf->venc_list[i], &tmp_stream);

#endif
					if (HI_SUCCESS != tmp_ret_int) {
						cp_module_log(error, tmp_hi3519_av_codec,
							"hi3519_av_save_physical_stream() failed channel[%d]!error_code[0x%x]",
							tmp_hi3519_av_conf->venc_list[i].index,
							tmp_ret_int);
					}
#endif
					/*******************************************************
					step 2.6 : release stream
					*******************************************************/
					tmp_ret_int = HI_MPI_VENC_ReleaseStream(tmp_hi3519_av_conf->venc_list[i].index, &tmp_stream);
					if (HI_SUCCESS != tmp_ret_int) {
#if defined(CP_HI3519_PRINT_LOG)
						cp_module_log(error, tmp_hi3519_av_codec,
							"HI_MPI_VENC_ReleaseStream() failed channel[%d]!error_code[0x%x]",
							tmp_hi3519_av_conf->venc_list[i].index,
							tmp_ret_int);
#endif
					}
					/*******************************************************
					step 2.7 : free pack nodes
					*******************************************************/
					if (tmp_stat.u32CurPacks > CP_HI3519_AV_CODEC_MAX_PACKS_SIZE) {
						free(tmp_buf);
					}
				}
			}
		}
	}
#endif
	return;
}

#if defined(CP_HI3519_MODE)
cp_int32_t hi3519_av_save_memory_stream(cp_hi3519_av_codec_t *hi3519_av_codec,
	cp_hi3519_av_venc_info_t *venc_info, VENC_STREAM_S *stream)
{
	cp_int32_t						tmp_ret_int = 0;



	if (PT_H264 == venc_info->payload) {
		tmp_ret_int = hi3519_av_save_memory_h264(hi3519_av_codec, venc_info, stream);
	}
	else {
		cp_module_log(error, hi3519_av_codec, "unsupport payload[%d].", venc_info->payload);
	}
	return 0;
}

cp_int32_t hi3519_av_save_memory_h264(cp_hi3519_av_codec_t *hi3519_av_codec,
	cp_hi3519_av_venc_info_t *venc_info, VENC_STREAM_S *stream)
{
	cp_buf_t						*tmp_buf = CP_NULL;
	cp_int32_t						tmp_packe_length = 0;
	cp_int32_t						tmp_sum_length = 0;
	cp_int32_t						i = 0;



	for (i = 0; i < stream->u32PackCount; i++)
	{
		tmp_sum_length += (stream->pstPack[i].u32Len - stream->pstPack[i].u32Offset);
	}

	if (tmp_sum_length <= 0) {
		return -1;
	}

	tmp_buf = create_a_rtp_socket_buffer(hi3519_av_codec->pool, venc_info->rtp_sd, tmp_sum_length);
	if (!tmp_buf) {
		return -1;
	}

	for (i = 0; i < stream->u32PackCount; i++)
	{
		tmp_packe_length = stream->pstPack[i].u32Len - stream->pstPack[i].u32Offset;
		cp_buf_strcat(tmp_buf, (void *)(stream->pstPack[i].pu8Addr + stream->pstPack[i].u32Offset),
			tmp_packe_length);
	}

	push_a_rtp_socket_buffer(venc_info->rtp_sd, tmp_buf);

	return 0;
}

cp_int32_t hi3519_av_save_physical_stream(cp_hi3519_av_codec_t *hi3519_av_codec,
	cp_hi3519_av_venc_info_t *venc_info, VENC_STREAM_S *stream)
{
	HI_U32							i;
	HI_U32							tmp_phy_addr;
	HI_U32							tmp_left;
	cp_buf_t						*tmp_buf = CP_NULL;
	cp_int32_t						tmp_packe_length = 0;
	cp_int32_t						tmp_sum_length = 0;



	for (i = 0; i < stream->u32PackCount; i++)
	{
		if (stream->pstPack[i].u32PhyAddr + stream->pstPack[i].u32Len >=
			venc_info->stream_buf_info.u32PhyAddr + venc_info->stream_buf_info.u32BufSize)
		{
			if (stream->pstPack[i].u32PhyAddr + stream->pstPack[i].u32Offset >=
				venc_info->stream_buf_info.u32PhyAddr + venc_info->stream_buf_info.u32BufSize)
			{
				/* physical address retrace in offset segment */
				tmp_phy_addr = venc_info->stream_buf_info.u32PhyAddr +
					((stream->pstPack[i].u32PhyAddr + stream->pstPack[i].u32Offset) -
					(venc_info->stream_buf_info.u32PhyAddr + venc_info->stream_buf_info.u32BufSize));

				tmp_sum_length += (stream->pstPack[i].u32Len - stream->pstPack[i].u32Offset);
			}
			else
			{
				/* physical address retrace in data segment */
				tmp_left = (venc_info->stream_buf_info.u32PhyAddr + venc_info->stream_buf_info.u32BufSize) - stream->pstPack[i].u32PhyAddr;
				tmp_sum_length += (tmp_left - stream->pstPack[i].u32Offset) + (stream->pstPack[i].u32Len - tmp_left);
			}
		}
		else
		{
			/* physical address retrace does not happen */
			tmp_sum_length += (stream->pstPack[i].u32Len - stream->pstPack[i].u32Offset);
		}
	}

	if (tmp_sum_length <= 0) {
		return -1;
	}

	tmp_buf = create_a_rtp_socket_buffer(hi3519_av_codec->pool, venc_info->rtp_sd, tmp_sum_length);
	if (!tmp_buf) {
		return -1;
	}

	for (i = 0; i < stream->u32PackCount; i++)
	{
		if (stream->pstPack[i].u32PhyAddr + stream->pstPack[i].u32Len >=
			venc_info->stream_buf_info.u32PhyAddr + venc_info->stream_buf_info.u32BufSize)
		{
			if (stream->pstPack[i].u32PhyAddr + stream->pstPack[i].u32Offset >=
				venc_info->stream_buf_info.u32PhyAddr + venc_info->stream_buf_info.u32BufSize)
			{
				/* physical address retrace in offset segment */
				tmp_phy_addr = venc_info->stream_buf_info.u32PhyAddr +
					((stream->pstPack[i].u32PhyAddr + stream->pstPack[i].u32Offset) -
					(venc_info->stream_buf_info.u32PhyAddr + venc_info->stream_buf_info.u32BufSize));

				tmp_packe_length = stream->pstPack[i].u32Len - stream->pstPack[i].u32Offset;
				cp_buf_strcat(tmp_buf, (void *)tmp_phy_addr, tmp_packe_length);
			}
			else
			{
				/* physical address retrace in data segment */
				tmp_left = (venc_info->stream_buf_info.u32PhyAddr + venc_info->stream_buf_info.u32BufSize) - stream->pstPack[i].u32PhyAddr;


				tmp_packe_length = (tmp_left - stream->pstPack[i].u32Offset) + (stream->pstPack[i].u32Len - tmp_left);
				cp_buf_strcat(tmp_buf, (void *)(stream->pstPack[i].u32PhyAddr + stream->pstPack[i].u32Offset),
					tmp_left - stream->pstPack[i].u32Offset);
				cp_buf_strcat(tmp_buf, (void *)venc_info->stream_buf_info.u32PhyAddr,
					stream->pstPack[i].u32Len - tmp_left);
			}
		}
		else
		{
			/* physical address retrace does not happen */
			tmp_packe_length = stream->pstPack[i].u32Len - stream->pstPack[i].u32Offset;
			cp_buf_strcat(tmp_buf, (void *)(stream->pstPack[i].u32PhyAddr + stream->pstPack[i].u32Offset),
				tmp_packe_length);
		}
	}

	push_a_rtp_socket_buffer(venc_info->rtp_sd, tmp_buf);

	return 0;
}

cp_int32_t hi3519_av_send_memory_stream(cp_hi3519_av_codec_t *hi3519_av_codec,
	cp_hi3519_av_venc_info_t *venc_info, VENC_STREAM_S *stream)
{
	cp_int32_t						tmp_ret_int = 0;



	if (PT_H264 == venc_info->payload) {
		tmp_ret_int = hi3519_av_send_memory_h264(hi3519_av_codec, venc_info, stream);
	}
	else {
		cp_module_log(error, hi3519_av_codec, "unsupport payload[%d].", venc_info->payload);
	}
	return 0;
}

cp_int32_t hi3519_av_send_memory_h264(cp_hi3519_av_codec_t *hi3519_av_codec,
	cp_hi3519_av_venc_info_t *venc_info, VENC_STREAM_S *stream)
{
	//cp_buf_t						*tmp_buf = CP_NULL;
	cp_int32_t						tmp_packe_length = 0;
	cp_int32_t						tmp_sum_length = 0;
	cp_int32_t						i = 0;
	cp_buf_t						tmp_buf = { 0, };



	// 	for (i = 0; i < stream->u32PackCount; i++)
	// 	{
	// 		tmp_sum_length += (stream->pstPack[i].u32Len - stream->pstPack[i].u32Offset);
	// 	}
	// 
	// 	if (tmp_sum_length <= 0) {
	// 		return -1;
	// 	}

	// 	tmp_buf = create_a_rtp_socket_buffer(hi3519_av_codec->pool, venc_info->rtp_sd, tmp_sum_length);
	// 	if (!tmp_buf) {
	// 		return -1;
	// 	}

	for (i = 0; i < stream->u32PackCount; i++)
	{
		tmp_packe_length = stream->pstPack[i].u32Len - stream->pstPack[i].u32Offset;
		// 		cp_buf_strcat(tmp_buf, (void *)(stream->pstPack[i].pu8Addr + stream->pstPack[i].u32Offset),
		// 			tmp_packe_length);

		cp_buf_assemble(&tmp_buf, (void *)(stream->pstPack[i].pu8Addr + stream->pstPack[i].u32Offset), tmp_packe_length);
		ipc_func_send_rtp_h264_cycle(hi3519_av_codec->rtp_session, &tmp_buf, tmp_packe_length);
	}

	//	ipc_func_send_rtp_h264_cycle(hi3519_av_codec->rtp_session, tmp_buf, tmp_sum_length);
	// 	destroy_a_rtp_socket_buffer(hi3519_av_codec->pool, venc_info->rtp_sd, tmp_buf);

	return 0;
}

cp_int32_t hi3519_av_send_physical_stream(cp_hi3519_av_codec_t *hi3519_av_codec,
	cp_hi3519_av_venc_info_t *venc_info, VENC_STREAM_S *stream)
{
	HI_U32							i;
	HI_U32							tmp_phy_addr;
	HI_U32							tmp_left;
	cp_buf_t						*tmp_buf = CP_NULL;
	cp_int32_t						tmp_packe_length = 0;
	cp_int32_t						tmp_sum_length = 0;



	for (i = 0; i < stream->u32PackCount; i++)
	{
		if (stream->pstPack[i].u32PhyAddr + stream->pstPack[i].u32Len >=
			venc_info->stream_buf_info.u32PhyAddr + venc_info->stream_buf_info.u32BufSize)
		{
			if (stream->pstPack[i].u32PhyAddr + stream->pstPack[i].u32Offset >=
				venc_info->stream_buf_info.u32PhyAddr + venc_info->stream_buf_info.u32BufSize)
			{
				/* physical address retrace in offset segment */
				tmp_phy_addr = venc_info->stream_buf_info.u32PhyAddr +
					((stream->pstPack[i].u32PhyAddr + stream->pstPack[i].u32Offset) -
					(venc_info->stream_buf_info.u32PhyAddr + venc_info->stream_buf_info.u32BufSize));

				tmp_sum_length += (stream->pstPack[i].u32Len - stream->pstPack[i].u32Offset);
			}
			else
			{
				/* physical address retrace in data segment */
				tmp_left = (venc_info->stream_buf_info.u32PhyAddr + venc_info->stream_buf_info.u32BufSize) - stream->pstPack[i].u32PhyAddr;
				tmp_sum_length += (tmp_left - stream->pstPack[i].u32Offset) + (stream->pstPack[i].u32Len - tmp_left);
			}
		}
		else
		{
			/* physical address retrace does not happen */
			tmp_sum_length += (stream->pstPack[i].u32Len - stream->pstPack[i].u32Offset);
		}
	}

	if (tmp_sum_length <= 0) {
		return -1;
	}

	tmp_buf = create_a_rtp_socket_buffer(hi3519_av_codec->pool, venc_info->rtp_sd, tmp_sum_length);
	if (!tmp_buf) {
		return -1;
	}

	for (i = 0; i < stream->u32PackCount; i++)
	{
		if (stream->pstPack[i].u32PhyAddr + stream->pstPack[i].u32Len >=
			venc_info->stream_buf_info.u32PhyAddr + venc_info->stream_buf_info.u32BufSize)
		{
			if (stream->pstPack[i].u32PhyAddr + stream->pstPack[i].u32Offset >=
				venc_info->stream_buf_info.u32PhyAddr + venc_info->stream_buf_info.u32BufSize)
			{
				/* physical address retrace in offset segment */
				tmp_phy_addr = venc_info->stream_buf_info.u32PhyAddr +
					((stream->pstPack[i].u32PhyAddr + stream->pstPack[i].u32Offset) -
					(venc_info->stream_buf_info.u32PhyAddr + venc_info->stream_buf_info.u32BufSize));

				tmp_packe_length = stream->pstPack[i].u32Len - stream->pstPack[i].u32Offset;
				cp_buf_strcat(tmp_buf, (void *)tmp_phy_addr, tmp_packe_length);
			}
			else
			{
				/* physical address retrace in data segment */
				tmp_left = (venc_info->stream_buf_info.u32PhyAddr + venc_info->stream_buf_info.u32BufSize) - stream->pstPack[i].u32PhyAddr;


				tmp_packe_length = (tmp_left - stream->pstPack[i].u32Offset) + (stream->pstPack[i].u32Len - tmp_left);
				cp_buf_strcat(tmp_buf, (void *)(stream->pstPack[i].u32PhyAddr + stream->pstPack[i].u32Offset),
					tmp_left - stream->pstPack[i].u32Offset);
				cp_buf_strcat(tmp_buf, (void *)venc_info->stream_buf_info.u32PhyAddr,
					stream->pstPack[i].u32Len - tmp_left);
			}
		}
		else
		{
			/* physical address retrace does not happen */
			tmp_packe_length = stream->pstPack[i].u32Len - stream->pstPack[i].u32Offset;
			cp_buf_strcat(tmp_buf, (void *)(stream->pstPack[i].u32PhyAddr + stream->pstPack[i].u32Offset),
				tmp_packe_length);
		}
	}

	ipc_func_send_rtp_h264_cycle(hi3519_av_codec->rtp_session, tmp_buf, tmp_sum_length);
	destroy_a_rtp_socket_buffer(hi3519_av_codec->pool, venc_info->rtp_sd, tmp_buf);

	return 0;
}
#endif

/*停止获取数据hi3519 venc 线程*/
cp_int32_t	stop_hi3519_av_get_stream_thread(cp_hi3519_av_codec_t *hi3519_av_codec, cp_hi3519_av_conf_t *hi3519_av_conf)
{
	hi3519_av_conf->is_process_stream = cp_false;
	cp_thread_join(hi3519_av_conf->thread);
	return 0;
}


/*停止获取数据hi3519 venc */
cp_int32_t	stop_hi3519_av_get_stream(cp_hi3519_av_codec_t *hi3519_av_codec, cp_hi3519_av_conf_t *hi3519_av_conf)
{
	return 0;
}

/*解除绑定vpss 和 venc*/
cp_int32_t	hi3519_av_unbind_vpss_venc(cp_hi3519_av_codec_t *hi3519_av_codec, cp_hi3519_av_conf_t *hi3519_av_conf)
{
#if defined(CP_HI3519_MODE)
	cp_int32_t					i = 0;
	HI_S32						tmp_ret_int = HI_FAILURE;



	for (i = 0; i < cp_ary_size(hi3519_av_conf->venc_list); i++) {
		tmp_ret_int = SAMPLE_COMM_VENC_UnBindVpss(hi3519_av_conf->venc_list[i].index,
			hi3519_av_conf->stitch_vpss_info.index,
			hi3519_av_conf->stitch_vpss_info.vpss_list[i].index);
		if (HI_SUCCESS != tmp_ret_int)
		{
			cp_module_log(error, hi3519_av_codec, "SAMPLE_COMM_VENC_BindVpss() error");
			return -1;
		}
	}

#endif

	return 0;
}

/*解除绑定vi 和 vpss*/
cp_int32_t	hi3519_av_unbind_vi_vpss(cp_hi3519_av_codec_t *hi3519_av_codec, cp_hi3519_av_conf_t *hi3519_av_conf)
{
#if defined(CP_HI3519_MODE)
	cp_int32_t					i = 0;
	HI_S32						tmp_ret_int = HI_FAILURE;


	for (i = 0; i < cp_ary_size(hi3519_av_conf->channel_list); i++) {
		tmp_ret_int = SAMPLE_COMM_VI_UnBindVpss(hi3519_av_conf->channel_list[i].channel_config.enViMode);
		if (HI_SUCCESS != tmp_ret_int)
		{
			cp_module_log(error, hi3519_av_codec, "SAMPLE_COMM_VI_UnBindVpss() error");
			return -1;
		}
	}

#endif

	return 0;
}

/*解除绑定vi 和 process_vpss*/
cp_int32_t	hi3519_av_unbind_vi_process_vpss(cp_hi3519_av_codec_t *hi3519_av_codec, cp_hi3519_av_conf_t *hi3519_av_conf)
{
#if defined(CP_HI3519_MODE)
	cp_int32_t					i = 0;
	HI_S32						tmp_ret_int = HI_FAILURE;
	MPP_CHN_S					tmp_src_channel = { 0, };
	MPP_CHN_S					tmp_dest_channel = { 0, };



	for (i = 0; i < cp_ary_size(hi3519_av_conf->process_vpss_info); i++) {
		cp_memset(&tmp_src_channel, 0, cp_sizeof(tmp_src_channel));
		cp_memset(&tmp_dest_channel, 0, cp_sizeof(tmp_dest_channel));

		tmp_src_channel.enModId = HI_ID_VIU;
		tmp_src_channel.s32DevId = 0;
		tmp_src_channel.s32ChnId = CP_HI3519_AV_CODEC_BEGIN_EXT_VI_CHANNEL_NUMBER + i;
		tmp_dest_channel.enModId = HI_ID_VPSS;
		tmp_dest_channel.s32DevId = hi3519_av_conf->process_vpss_info[i].index;
		tmp_dest_channel.s32ChnId = hi3519_av_conf->process_vpss_info[i].vpss_list[CP_HI3519_AV_CODEC_USED_VPSS_CHANNEL_NUMBER].index;

		tmp_ret_int = HI_MPI_SYS_UnBind(&tmp_src_channel, &tmp_dest_channel);
		if (tmp_ret_int != HI_SUCCESS)
		{
			cp_module_log(error, hi3519_av_codec,
				"HI_MPI_SYS_UnBind() vi[%d] bind group[%d] vpss[%d] failed witherror_code[0x%x]",
				tmp_src_channel.s32ChnId,
				tmp_dest_channel.s32DevId,
				tmp_dest_channel.s32ChnId,
				tmp_ret_int);
			return HI_FAILURE;
		}
	}

#endif

	return 0;
}

/*解除绑定process_vpss 和 vpss*/
cp_int32_t	hi3519_av_unbind_process_vpss_vpss(cp_hi3519_av_codec_t *hi3519_av_codec, cp_hi3519_av_conf_t *hi3519_av_conf)
{
#if defined(CP_HI3519_MODE)
	cp_int32_t					i = 0;
	HI_S32						tmp_ret_int = HI_FAILURE;
	MPP_CHN_S					tmp_src_channel = { 0, };
	MPP_CHN_S					tmp_dest_channel = { 0, };




	tmp_src_channel.enModId = HI_ID_VPSS;
	tmp_src_channel.s32DevId = hi3519_av_conf->process_vpss_info[0].index;
	tmp_src_channel.s32ChnId = hi3519_av_conf->process_vpss_info[0].vpss_list[CP_HI3519_AV_CODEC_USED_VPSS_CHANNEL_NUMBER].index;
	tmp_dest_channel.enModId = HI_ID_VPSS;
	tmp_dest_channel.s32DevId = hi3519_av_conf->stitch_vpss_info.index;
	tmp_dest_channel.s32ChnId = hi3519_av_conf->stitch_vpss_info.vpss_list[CP_HI3519_AV_CODEC_USED_VPSS_CHANNEL_NUMBER].index;

	tmp_ret_int = HI_MPI_SYS_UnBind(&tmp_src_channel, &tmp_dest_channel);
	if (tmp_ret_int != HI_SUCCESS)
	{
		cp_module_log(error, hi3519_av_codec,
			"HI_MPI_SYS_UnBind() group[%d] vpss[%d] bind group[%d] vpss[%d] failed witherror_code[0x%x]",
			tmp_src_channel.s32DevId,
			tmp_src_channel.s32ChnId,
			tmp_dest_channel.s32DevId,
			tmp_dest_channel.s32ChnId,
			tmp_ret_int);
		return HI_FAILURE;
	}

	tmp_src_channel.enModId = HI_ID_VPSS;
	tmp_src_channel.s32DevId = hi3519_av_conf->process_vpss_info[1].index;
	tmp_src_channel.s32ChnId = hi3519_av_conf->process_vpss_info[1].vpss_list[1].index;
	tmp_dest_channel.enModId = HI_ID_VPSS;
	tmp_dest_channel.s32DevId = hi3519_av_conf->stitch_vpss_info.index;
	tmp_dest_channel.s32ChnId = hi3519_av_conf->stitch_vpss_info.vpss_list[1].index;

	tmp_ret_int = HI_MPI_SYS_UnBind(&tmp_src_channel, &tmp_dest_channel);
	if (tmp_ret_int != HI_SUCCESS)
	{
		cp_module_log(error, hi3519_av_codec,
			"HI_MPI_SYS_UnBind() group[%d] vpss[%d] bind group[%d] vpss[%d] failed witherror_code[0x%x]",
			tmp_src_channel.s32DevId,
			tmp_src_channel.s32ChnId,
			tmp_dest_channel.s32DevId,
			tmp_dest_channel.s32ChnId,
			tmp_ret_int);
		return HI_FAILURE;
	}
#endif
	return 0;
}

/*解除绑定vi 和 venc*/
cp_int32_t	hi3519_av_unbind_vi_fisheye_venc(cp_hi3519_av_codec_t *hi3519_av_codec, cp_hi3519_av_conf_t *hi3519_av_conf)
{
#if defined(CP_HI3519_MODE)
	cp_int32_t					i = 0;
	HI_S32						tmp_ret_int = HI_FAILURE;
	MPP_CHN_S					tmp_src_channel = { 0, };
	MPP_CHN_S					tmp_dest_channel = { 0, };




	tmp_src_channel.enModId = HI_ID_VIU;
	tmp_src_channel.s32DevId = 0;
	tmp_src_channel.s32ChnId = CP_HI3519_AV_CODEC_BEGIN_EXT_VI_CHANNEL_NUMBER + 0;
	tmp_dest_channel.enModId = HI_ID_VENC;
	tmp_dest_channel.s32DevId = 0;
	tmp_dest_channel.s32ChnId = hi3519_av_conf->venc_list[0].index;

	tmp_ret_int = HI_MPI_SYS_UnBind(&tmp_src_channel, &tmp_dest_channel);
	if (tmp_ret_int != HI_SUCCESS)
	{
		cp_module_log(error, hi3519_av_codec,
			"HI_MPI_SYS_UnBind() vi[%d] bind venc[%d] failed witherror_code[0x%x]",
			tmp_src_channel.s32ChnId,
			tmp_dest_channel.s32ChnId,
			tmp_ret_int);
		return HI_FAILURE;
	}

#endif
	return 0;
}

/*解除绑定信息*/
cp_int32_t	hi3519_av_unbind_info(cp_hi3519_av_codec_t *hi3519_av_codec, cp_hi3519_av_conf_t *hi3519_av_conf)
{
	cp_int32_t					tmp_ret_int = 0;



	if (cp_hi3519_av_codec_mode_vi_stitch_vpss_venc == hi3519_av_codec->hacc.mode ||
		cp_hi3519_av_codec_mode_vi_fisheye_stitch_vpss_venc == hi3519_av_codec->hacc.mode ||
		cp_hi3519_av_codec_mode_vi_fisheye_process_vpss_stitch_vpss_venc == hi3519_av_codec->hacc.mode) {
		/*解除绑定vpss 和 venc*/
		tmp_ret_int = hi3519_av_unbind_vpss_venc(hi3519_av_codec, hi3519_av_codec->av_conf);
		if (tmp_ret_int) {
			cp_module_log(error, hi3519_av_codec, "hi3519_av_unbind_vpss_venc() error.");
			return -1;
		}

		if (cp_hi3519_av_codec_mode_vi_stitch_vpss_venc == hi3519_av_codec->hacc.mode ||
			cp_hi3519_av_codec_mode_vi_fisheye_stitch_vpss_venc == hi3519_av_codec->hacc.mode) {
			/*解除绑定vi 和 vpss*/
			tmp_ret_int = hi3519_av_unbind_vi_vpss(hi3519_av_codec, hi3519_av_codec->av_conf);
			if (tmp_ret_int) {
				cp_module_log(error, hi3519_av_codec, "hi3519_av_unbind_vi_vpss() error.");
				return -1;
			}
		}
		else {
			/*解除绑定vi 和 process_vpss*/
			tmp_ret_int = hi3519_av_unbind_vi_process_vpss(hi3519_av_codec, hi3519_av_codec->av_conf);
			if (tmp_ret_int) {
				cp_module_log(error, hi3519_av_codec, "hi3519_av_unbind_vi_process_vpss() error.");
				return -1;
			}

			/*解除绑定ext vpss 和 vpss*/
			tmp_ret_int = hi3519_av_unbind_process_vpss_vpss(hi3519_av_codec, hi3519_av_codec->av_conf);
			if (tmp_ret_int) {
				cp_module_log(error, hi3519_av_codec, "hi3519_av_unbind_process_vpss_vpss() error.");
				return -1;
			}
		}
	}
	else {
		/*解除绑定vi 和 venc*/
		tmp_ret_int = hi3519_av_unbind_vi_fisheye_venc(hi3519_av_codec, hi3519_av_codec->av_conf);
		if (tmp_ret_int) {
			cp_module_log(error, hi3519_av_codec, "hi3519_av_unbind_vi_fisheye_venc() error.");
			return -1;
		}
	}
	return 0;
}

/*停止hi3519 venc_list 设备*/
cp_int32_t	stop_hi3519_av_venc(cp_hi3519_av_codec_t *hi3519_av_codec, cp_hi3519_av_conf_t *hi3519_av_conf)
{
#if defined(CP_HI3519_MODE)
	cp_int32_t					i = 0;
	HI_S32						tmp_ret_int = HI_FAILURE;



	for (i = 0; i < cp_ary_size(hi3519_av_conf->venc_list); i++) {
		tmp_ret_int = SAMPLE_COMM_VENC_Stop(hi3519_av_conf->venc_list[i].index);
		if (HI_SUCCESS != tmp_ret_int)
		{
			cp_module_log(error, hi3519_av_codec, "SAMPLE_COMM_VENC_Stop() channel[%d] error.", i);
			return -1;
		}
		// 		hi3519_av_conf->venc_list[i].is_enc = cp_false;
		// 		if (hi3519_av_conf->venc_list[i].rtp_sd) {
		// 			destroy_socket_data(hi3519_av_codec->pool, hi3519_av_conf->venc_list[i].rtp_sd);
		// 		}
	}

#endif

	return 0;
}

/*停止hi3519 vpss_list 设备*/
cp_int32_t	stop_hi3519_av_stitch_vpss(cp_hi3519_av_codec_t *hi3519_av_codec, cp_hi3519_av_conf_t *hi3519_av_conf)
{
#if defined(CP_HI3519_MODE)
	cp_int32_t					i = 0;
	HI_S32						tmp_ret_int = HI_FAILURE;



	for (i = 0; i < cp_ary_size(hi3519_av_conf->stitch_vpss_info.vpss_list); i++) {
		tmp_ret_int = SAMPLE_COMM_VPSS_DisableChn(hi3519_av_conf->stitch_vpss_info.index,
			hi3519_av_conf->stitch_vpss_info.vpss_list[i].index);
		if (HI_SUCCESS != tmp_ret_int)
		{
			cp_module_log(error, hi3519_av_codec, "SAMPLE_COMM_VPSS_DisableChn() channel[%d] error.", i);
			return -1;
		}
	}
	tmp_ret_int = SAMPLE_COMM_VPSS_StopGroup(hi3519_av_conf->stitch_vpss_info.index);
	if (HI_SUCCESS != tmp_ret_int) {
		cp_module_log(error, hi3519_av_codec, "SAMPLE_COMM_VPSS_StartGroup() error.");
		return -1;
	}

#endif

	return 0;
}

/*停止hi3519 vi 设备*/
cp_int32_t	stop_hi3519_av_vi(cp_hi3519_av_codec_t *hi3519_av_codec, cp_hi3519_av_conf_t *hi3519_av_conf)
{
#if defined(CP_HI3519_MODE)
	cp_int32_t					i = 0;
	HI_S32						tmp_ret_int = HI_FAILURE;



	for (i = 0; i < cp_ary_size(hi3519_av_conf->channel_list); i++) {
		tmp_ret_int = SAMPLE_COMM_VI_StopVi(&hi3519_av_conf->channel_list[i].channel_config);
		if (HI_SUCCESS != tmp_ret_int)
		{
			cp_module_log(error, hi3519_av_codec, "SAMPLE_COMM_VI_StartVi() channel[%d] error.", i);
			return -1;
		}
	}

#endif

	return 0;
}

/*停止hi3519 设备*/
cp_int32_t	stop_hi3519_av_info(cp_hi3519_av_codec_t *hi3519_av_codec, cp_hi3519_av_conf_t *hi3519_av_conf)
{
	cp_int32_t					tmp_ret_int = 0;




	/*解除绑定信息*/
	tmp_ret_int = hi3519_av_unbind_info(hi3519_av_codec, hi3519_av_codec->av_conf);
	if (tmp_ret_int) {
		cp_module_log(error, hi3519_av_codec, "hi3519_av_unbind_info() error.");
		return -1;
	}

	/*停止hi3519 venc 设备*/
	tmp_ret_int = stop_hi3519_av_venc(hi3519_av_codec, hi3519_av_codec->av_conf);
	if (tmp_ret_int) {
		cp_module_log(error, hi3519_av_codec, "stop_hi3519_av_venc() error.");
		return -1;
	}

	if (cp_hi3519_av_codec_mode_vi_stitch_vpss_venc == hi3519_av_codec->hacc.mode ||
		cp_hi3519_av_codec_mode_vi_fisheye_stitch_vpss_venc == hi3519_av_codec->hacc.mode) {
		/*停止hi3519 venc 设备*/
		tmp_ret_int = stop_hi3519_av_stitch_vpss(hi3519_av_codec, hi3519_av_codec->av_conf);
		if (tmp_ret_int) {
			cp_module_log(error, hi3519_av_codec, "stop_hi3519_av_vi() error.");
			return -1;
		}
	}

	/*停止hi3519 vi 设备*/
	tmp_ret_int = stop_hi3519_av_vi(hi3519_av_codec, hi3519_av_codec->av_conf);
	if (tmp_ret_int) {
		cp_module_log(error, hi3519_av_codec, "stop_hi3519_av_vi() error.");
		return -1;
	}
	return 0;
}

cp_int32_t hi3519_av_system_destroy(cp_hi3519_av_codec_t *hi3519_av_codec, cp_hi3519_av_conf_t *hi3519_av_conf)
{
#if defined(CP_HI3519_MODE)
	HI_MPI_SYS_Exit();
	HI_MPI_VB_Exit();
#endif
	return 0;
}

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: destroy_hi3519_av_codec_conf
*
* 函数说明: 表示消毁conf信息
*
* 参    数: cp_hi3519_av_codec_t * hi3519_av_codec						[in]参数说明
*
* 返 回 值: cp_int32_t
*           0  : 成功
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2016-12-24 14:34:28
******************************************************************************************************/
cp_int32_t destroy_hi3519_av_codec_conf(cp_hi3519_av_codec_t *hi3519_av_codec)
{
	if (!hi3519_av_codec || !hi3519_av_codec->av_conf) {
		return -1;
	}

	cp_pfree(hi3519_av_codec->pool, hi3519_av_codec->av_conf);
	hi3519_av_codec->av_conf = CP_NULL;

	return 0;
}


/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: stop_hi3519_all
*
* 函数说明: 停止所有
*
* 参    数: cp_hi3519_av_codec_t * hi3519_av_codec						[in]参数说明
* 参    数: cp_hi3519_av_conf_t * hi3519_av_conf						[in]参数说明
*
* 返 回 值: cp_int32_t
*           0  : 成功
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2017-01-10 20:15:45
******************************************************************************************************/
cp_int32_t stop_hi3519_all(cp_hi3519_av_codec_t *hi3519_av_codec, cp_hi3519_av_conf_t *hi3519_av_conf)
{
	hi3519_av_unbind_vpss_venc(hi3519_av_codec, hi3519_av_conf);
	hi3519_av_unbind_vi_vpss(hi3519_av_codec, hi3519_av_conf);
	stop_hi3519_av_venc(hi3519_av_codec, hi3519_av_conf);
	stop_hi3519_av_stitch_vpss(hi3519_av_codec, hi3519_av_conf);
	stop_hi3519_av_vi(hi3519_av_codec, hi3519_av_conf);

	return 0;
}
