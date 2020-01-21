/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-12-20

Description:

**************************************************************************/
#include "cp_log.h"
#include "cp_conf.h"
#include "cp_hi3531_vpss_conf.h"



cp_inline cp_static cp_bool_t get_module_conf_xml_int_prop(cp_int32_t *dest, cp_module_t *module,
	cp_conf_t *conf, const char *context, const char *key, int def)
{
	cp_int32_t							tmp_value = 0;



	if (!conf || !module) {
		return cp_false;
	}
	tmp_value = cp_conf_xml_getint(conf->conf_xml, context, key, def);
	if (tmp_value < 0) {
		cp_module_log(notice, module, "get [%s:%s] warning!", context, key);
		//return cp_false;
	}
	*dest = tmp_value;
	return cp_true;
}

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: hi3531_vpss_parse_configure
*
* 函数说明: 解析配置文件
*
* 参    数: cp_module_t * module						[in]参数说明
* 参    数: cp_hi3531_vpss_configure_t * hacc						[in]参数说明
*
* 返 回 值: cp_int32_t
*           0  : 成功
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2016-12-20 15:14:47
******************************************************************************************************/
cp_int32_t	hi3531_vpss_parse_configure(cp_module_t *module, cp_hi3531_vpss_configure_t *hacc)
{
	cp_int32_t						tmp_value = 0;
	cp_int32_t						tmp_ret_int = 0;



	if (!module || !hacc) {
		return -1;
	}

	//解析width
	if (!get_module_conf_xml_int_prop(&tmp_value, module, module->conf,
		CP_HI3531_VPSS_CONF_STRING_CODEC_CONFIGURE, CP_HI3531_VPSS_CONF_STRING_WIDTH, 0)) {
		return -1;
	}
	hacc->width = tmp_value;

	//解析heigth
	if (!get_module_conf_xml_int_prop(&tmp_value, module, module->conf,
		CP_HI3531_VPSS_CONF_STRING_CODEC_CONFIGURE, CP_HI3531_VPSS_CONF_STRING_HEIGTH, 0)) {
		return -2;
	}
	hacc->heigth = tmp_value;

	//解析fps
	if (!get_module_conf_xml_int_prop(&tmp_value, module, module->conf,
		CP_HI3531_VPSS_CONF_STRING_CODEC_CONFIGURE, CP_HI3531_VPSS_CONF_STRING_FPS, 0)) {
		return -2;
	}
	hacc->fps = tmp_value;
	if (tmp_value < 0 || tmp_value > 60) {
		hacc->fps = -1;
	}

	//解析bitrate
	if (!get_module_conf_xml_int_prop(&tmp_value, module, module->conf,
		CP_HI3531_VPSS_CONF_STRING_CODEC_CONFIGURE, CP_HI3531_VPSS_CONF_STRING_BITRATE, 0)) {
		return -3;
	}
	hacc->bitrate = tmp_value;

	//解析mode
	if (!get_module_conf_xml_int_prop(&tmp_value, module, module->conf,
		CP_HI3531_VPSS_CONF_STRING_CODEC_CONFIGURE, CP_HI3531_VPSS_CONF_STRING_MODE, 0)) {
		return -3;
	}
	hacc->mode = tmp_value;

	if (!hacc->width || !hacc->heigth || !hacc->bitrate) {
		cp_module_log(error, module,
			"configure value error. width[%d] heigth[%d] bitrate[%d]",
			hacc->width,
			hacc->heigth,
			hacc->bitrate);
		return -4;
	}

	if (hacc->mode < cp_hi3531_vpss_mode_none ||
		hacc->mode > cp_hi3531_vpss_mode_end) {
		cp_module_log(error, module,
			"configure value error. unsupport mode[%d]",
			hacc->mode);
		return -5;
	}

	//解析vi_venc_channel
	if (!get_module_conf_xml_int_prop(&tmp_value, module, module->conf,
		CP_HI3531_VPSS_CONF_STRING_CODEC_CONFIGURE, CP_HI3531_VPSS_CONF_STRING_VENC_CHANNEL, 0)) {
		return -3;
	}
	hacc->vi_channel = tmp_value;

	//stitch配置信息
	tmp_ret_int = hi3531_vpss_parse_stitch_configure(module, hacc);
	if (tmp_ret_int) {
		cp_module_log(error, module,
			"hi3531_vpss_parse_stitch_configure() error.");
		return -6;
	}

	//camera 配置信息
	tmp_ret_int = hi3531_vpss_parse_camera_configure(module, hacc);
	if (tmp_ret_int) {
		cp_module_log(error, module,
			"hi3531_vpss_parse_camera_configure() error.");
		return -6;
	}

	return 0;
}

/************************************************************************/
/*解析摄像头配置文件                                                           */
/************************************************************************/
cp_int32_t	hi3531_vpss_parse_camera_configure(cp_module_t *module, cp_hi3531_vpss_configure_t *hacc)
{
	cp_int32_t						i = 0;
	cp_int32_t						tmp_value = 0;
	cp_char_t						*tmp_camera_config[CP_HI3531_VPSS_CAMERA_CONFIGURE_SIZE] = {
		CP_HI3531_VPSS_CONF_STRING_LEFT_CAMERA_CONFIGURE,
		CP_HI3531_VPSS_CONF_STRING_RIGHT_CAMERA_CONFIGURE
	};



	for (i = 0; i < CP_HI3531_VPSS_CAMERA_CONFIGURE_SIZE; i++) {
		//解析rotate
		if (!get_module_conf_xml_int_prop(&tmp_value, module, module->conf,
			tmp_camera_config[i], CP_HI3531_VPSS_CONF_STRING_ROTATE, 0)) {
			return -1;
		}
		else {
			hacc->camera_configs[i].rotate = tmp_value;
		}

		//解析is_mirror
		if (!get_module_conf_xml_int_prop(&tmp_value, module, module->conf,
			tmp_camera_config[i], CP_HI3531_VPSS_CONF_STRING_IS_MIRROR, 0)) {
			return -1;
		}
		if (!tmp_value) {
			hacc->camera_configs[i].is_mirror = cp_false;
		}
		else {
			hacc->camera_configs[i].is_mirror = cp_true;
		}

		//解析is_flip
		if (!get_module_conf_xml_int_prop(&tmp_value, module, module->conf,
			tmp_camera_config[i], CP_HI3531_VPSS_CONF_STRING_IS_FLIP, 0)) {
			return -1;
		}
		if (!tmp_value) {
			hacc->camera_configs[i].is_flip = cp_false;
		}
		else {
			hacc->camera_configs[i].is_flip = cp_true;
		}

		//解析mount_mode
		if (!get_module_conf_xml_int_prop(&tmp_value, module, module->conf,
			tmp_camera_config[i], CP_HI3531_VPSS_CONF_STRING_MOUNT_MODE, 0)) {
			return -1;
		}
		if (tmp_value < 0 || tmp_value > 2) {
			cp_module_log(error, module,
				"configure [%s] error. [%d] value not [0, 2].",
				CP_HI3531_VPSS_CONF_STRING_MOUNT_MODE,
				tmp_value);
			return -2;
		}
		hacc->camera_configs[i].mount_mode = tmp_value;

		//解析view_mode
		if (!get_module_conf_xml_int_prop(&tmp_value, module, module->conf,
			tmp_camera_config[i], CP_HI3531_VPSS_CONF_STRING_VIEW_MODE, 0)) {
			return -1;
		}
		if (tmp_value < 0 || tmp_value > 2) {
			cp_module_log(error, module,
				"configure [%s] error. [%d] value not [0, 2].",
				CP_HI3531_VPSS_CONF_STRING_VIEW_MODE,
				tmp_value);
			return -2;
		}
		hacc->camera_configs[i].view_mode = tmp_value;

		//解析hor_offset
		if (!get_module_conf_xml_int_prop(&tmp_value, module, module->conf,
			tmp_camera_config[i], CP_HI3531_VPSS_CONF_STRING_HOR_OFFSET, 0)) {
			return -1;
		}
		if (tmp_value < -127 || tmp_value > 127) {
			cp_module_log(error, module,
				"configure [%s] error. [%d] value not [-127, 127].",
				CP_HI3531_VPSS_CONF_STRING_HOR_OFFSET,
				tmp_value);
			return -2;
		}
		hacc->camera_configs[i].hor_offset = tmp_value;

		//解析ver_offset
		if (!get_module_conf_xml_int_prop(&tmp_value, module, module->conf,
			tmp_camera_config[i], CP_HI3531_VPSS_CONF_STRING_VER_OFFSET, 0)) {
			return -1;
		}
		if (tmp_value < -127 || tmp_value > 127) {
			cp_module_log(error, module,
				"configure [%s] error. [%d] value not [-127, 127].",
				CP_HI3531_VPSS_CONF_STRING_VER_OFFSET,
				tmp_value);
			return -2;
		}
		hacc->camera_configs[i].ver_offset = tmp_value;

		//解析trapezoid_coef
		if (!get_module_conf_xml_int_prop(&tmp_value, module, module->conf,
			tmp_camera_config[i], CP_HI3531_VPSS_CONF_STRING_TRAPEZOID_COEF, 0)) {
			return -1;
		}
		hacc->camera_configs[i].trapezoid_coef = tmp_value;

		//解析fan_strength
		if (!get_module_conf_xml_int_prop(&tmp_value, module, module->conf,
			tmp_camera_config[i], CP_HI3531_VPSS_CONF_STRING_FAN_STRENGTH, 0)) {
			return -1;
		}
		if (tmp_value < -760 || tmp_value > 760) {
			cp_module_log(error, module,
				"configure [%s] error. [%d] value not [-760, 760].",
				CP_HI3531_VPSS_CONF_STRING_FAN_STRENGTH,
				tmp_value);
			return -2;
		}
		hacc->camera_configs[i].fan_strength = tmp_value;

		//解析in_radius
		if (!get_module_conf_xml_int_prop(&tmp_value, module, module->conf,
			tmp_camera_config[i], CP_HI3531_VPSS_CONF_STRING_IN_RADIUS, 0)) {
			return -1;
		}
		hacc->camera_configs[i].in_radius = tmp_value;

		//解析out_radius
		if (!get_module_conf_xml_int_prop(&tmp_value, module, module->conf,
			tmp_camera_config[i], CP_HI3531_VPSS_CONF_STRING_OUT_RADIUS, 0)) {
			return -1;
		}
		if (tmp_value < 1 || tmp_value > 2304) {
			cp_module_log(error, module,
				"configure [%s] error. [%d] value not [1, 2304].",
				CP_HI3531_VPSS_CONF_STRING_OUT_RADIUS,
				tmp_value);
			return -2;
		}
		hacc->camera_configs[i].out_radius = tmp_value;

		//解析pan
		if (!get_module_conf_xml_int_prop(&tmp_value, module, module->conf,
			tmp_camera_config[i], CP_HI3531_VPSS_CONF_STRING_PAN, 0)) {
			return -1;
		}
 		if (tmp_value < -1296 || tmp_value > 1296) {
 			cp_module_log(error, module,
 				"configure [%s] error. [%d] value not [-180, 180].",
 				CP_HI3531_VPSS_CONF_STRING_PAN,
 				tmp_value);
 			return -2;
 		}
		hacc->camera_configs[i].pan = tmp_value;

		//解析tilt
		if (!get_module_conf_xml_int_prop(&tmp_value, module, module->conf,
			tmp_camera_config[i], CP_HI3531_VPSS_CONF_STRING_TILT, 0)) {
			return -1;
		}
		if (tmp_value < -180 || tmp_value > 180) {
			cp_module_log(error, module,
				"configure [%s] error. [%d] value not [-180, 180].",
				CP_HI3531_VPSS_CONF_STRING_TILT,
				tmp_value);
			return -2;
		}
		hacc->camera_configs[i].tilt = tmp_value;

		//解析hor_zoom
		if (!get_module_conf_xml_int_prop(&tmp_value, module, module->conf,
			tmp_camera_config[i], CP_HI3531_VPSS_CONF_STRING_HOR_ZOOM, 0)) {
			return -1;
		}
		if (tmp_value < 0 || tmp_value > 4095) {
			cp_module_log(error, module,
				"configure [%s] error. [%d] value not [0, 4095].",
				CP_HI3531_VPSS_CONF_STRING_HOR_ZOOM,
				tmp_value);
			return -2;
		}
		hacc->camera_configs[i].hor_zoom = tmp_value;

		//解析ver_zoom
		if (!get_module_conf_xml_int_prop(&tmp_value, module, module->conf,
			tmp_camera_config[i], CP_HI3531_VPSS_CONF_STRING_VER_ZOOM, 0)) {
			return -1;
		}
		if (tmp_value < 0 || tmp_value > 4095) {
			cp_module_log(error, module,
				"configure [%s] error. [%d] value not [0, 4095].",
				CP_HI3531_VPSS_CONF_STRING_VER_ZOOM,
				tmp_value);
			return -2;
		}
		hacc->camera_configs[i].ver_zoom = tmp_value;

		//解析outrect_x
		if (!get_module_conf_xml_int_prop(&tmp_value, module, module->conf,
			tmp_camera_config[i], CP_HI3531_VPSS_CONF_STRING_OUTRECT_X, 0)) {
			return -1;
		}
		hacc->camera_configs[i].outrect_x = tmp_value;

		//解析outrect_y
		if (!get_module_conf_xml_int_prop(&tmp_value, module, module->conf,
			tmp_camera_config[i], CP_HI3531_VPSS_CONF_STRING_OUTRECT_Y, 0)) {
			return -1;
		}
		hacc->camera_configs[i].outrect_y = tmp_value;

		//解析outrect_width
		if (!get_module_conf_xml_int_prop(&tmp_value, module, module->conf,
			tmp_camera_config[i], CP_HI3531_VPSS_CONF_STRING_OUTRECT_WIDTH, 0)) {
			return -1;
		}
		hacc->camera_configs[i].outrect_width = tmp_value;

		//解析outrect_height
		if (!get_module_conf_xml_int_prop(&tmp_value, module, module->conf,
			tmp_camera_config[i], CP_HI3531_VPSS_CONF_STRING_OUTRECT_HEIGHT, 0)) {
			return -1;
		}
		hacc->camera_configs[i].outrect_height = tmp_value;

		//解析luminance
		if (!get_module_conf_xml_int_prop(&tmp_value, module, module->conf,
			tmp_camera_config[i], CP_HI3531_VPSS_CONF_STRING_LUMINANCE, 0)) {
			return -1;
		}
		if (tmp_value < 0 || tmp_value > 100) {
			cp_module_log(error, module,
				"configure [%s] error. [%d] value not [0, 100].",
				CP_HI3531_VPSS_CONF_STRING_LUMINANCE,
				tmp_value);
			return -2;
		}
		hacc->camera_configs[i].luminance = tmp_value;

		//解析contrast
		if (!get_module_conf_xml_int_prop(&tmp_value, module, module->conf,
			tmp_camera_config[i], CP_HI3531_VPSS_CONF_STRING_CONTRAST, 0)) {
			return -1;
		}
		if (tmp_value < 0 || tmp_value > 100) {
			cp_module_log(error, module,
				"configure [%s] error. [%d] value not [0, 100].",
				CP_HI3531_VPSS_CONF_STRING_CONTRAST,
				tmp_value);
			return -2;
		}
		hacc->camera_configs[i].contrast = tmp_value;

		//解析hue
		if (!get_module_conf_xml_int_prop(&tmp_value, module, module->conf,
			tmp_camera_config[i], CP_HI3531_VPSS_CONF_STRING_HUE, 0)) {
			return -1;
		}
		if (tmp_value < 0 || tmp_value > 100) {
			cp_module_log(error, module,
				"configure [%s] error. [%d] value not [0, 100].",
				CP_HI3531_VPSS_CONF_STRING_HUE,
				tmp_value);
			return -2;
		}
		hacc->camera_configs[i].hue = tmp_value;

		//解析satuature
		if (!get_module_conf_xml_int_prop(&tmp_value, module, module->conf,
			tmp_camera_config[i], CP_HI3531_VPSS_CONF_STRING_SATUATURE, 0)) {
			return -1;
		}
		if (tmp_value < 0 || tmp_value > 100) {
			cp_module_log(error, module,
				"configure [%s] error. [%d] value not [0, 100].",
				CP_HI3531_VPSS_CONF_STRING_SATUATURE,
				tmp_value);
			return -2;
		}
		hacc->camera_configs[i].satuature = tmp_value;
	}

	return 0;
}

/************************************************************************/
/*解析stitch配置文件                                                     */
/************************************************************************/
cp_int32_t	hi3531_vpss_parse_stitch_configure(cp_module_t *module, cp_hi3531_vpss_configure_t *hacc)
{
	cp_int32_t						i = 0;
	cp_int32_t						tmp_ret_int = 0;
	cp_int32_t						tmp_value = 0;
	cp_char_t						*tmp_overlap_point[CP_HI3531_VPSS_OVERLAP_POINT_SIZE] = {
		CP_HI3531_VPSS_CONF_STRING_OVERLAP_POINT_0,
		CP_HI3531_VPSS_CONF_STRING_OVERLAP_POINT_1,
		CP_HI3531_VPSS_CONF_STRING_OVERLAP_POINT_2,
		CP_HI3531_VPSS_CONF_STRING_OVERLAP_POINT_3
	};



	//解析out_width
	if (!get_module_conf_xml_int_prop(&tmp_value, module, module->conf,
		CP_HI3531_VPSS_CONF_STRING_STITCH_CONFIGURE, CP_HI3531_VPSS_CONF_STRING_OUT_WIDTH, 0)) {
		return -1;
	}
	hacc->stitch_config.out_width = tmp_value;

	//解析out_height
	if (!get_module_conf_xml_int_prop(&tmp_value, module, module->conf,
		CP_HI3531_VPSS_CONF_STRING_STITCH_CONFIGURE, CP_HI3531_VPSS_CONF_STRING_OUT_HEIGHT, 0)) {
		return -1;
	}
	hacc->stitch_config.out_height = tmp_value;

	//解析自动配置内容
	tmp_ret_int = hi3531_vpss_parse_auto_configure(module, hacc);
	if (tmp_ret_int) {
		cp_module_log(error, module, "hi3531_vpss_parse_auto_configure() error.");
		return tmp_ret_int;
	}

	for (i = 0; i < CP_HI3531_VPSS_OVERLAP_POINT_SIZE; i++) {
		//解析overlap_point
		if (!get_module_conf_xml_int_prop(&tmp_value, module, module->conf,
			tmp_overlap_point[i], CP_HI3531_VPSS_CONF_STRING_OVERLAP_POINT_X, 0)) {
			return -1;
		}
		hacc->stitch_config.overlap_points[i].x = tmp_value;

		//解析overlap_point
		if (!get_module_conf_xml_int_prop(&tmp_value, module, module->conf,
			tmp_overlap_point[i], CP_HI3531_VPSS_CONF_STRING_OVERLAP_POINT_Y, 0)) {
			return -1;
		}
		hacc->stitch_config.overlap_points[i].y = tmp_value;
	}

	//解析cylind_stitch_correction配置内容
	tmp_ret_int = hi3531_vpss_parse_cylind_stitch_correction(module, hacc);
	if (tmp_ret_int) {
		cp_module_log(error, module, "hi3531_vpss_parse_cylind_stitch_correction() error.");
		return tmp_ret_int;
	}
	return 0;
}

/************************************************************************/
/*解析stitch 柱面校正配置文件                                            */
/************************************************************************/
cp_int32_t	hi3531_vpss_parse_cylind_stitch_correction(cp_module_t *module, cp_hi3531_vpss_configure_t *hacc)
{
	cp_int32_t						i = 0;
	cp_int32_t						tmp_ret_int = 0;
	cp_int32_t						tmp_value = 0;
	cp_char_t						*tmp_stitch_correction[CP_HI3531_VPSS_CAMERA_CONFIGURE_SIZE] = {
		CP_HI3531_VPSS_CONF_STRING_LEFT_STITCH_CORRECTION,
		CP_HI3531_VPSS_CONF_STRING_RIGHT_STITCH_CORRECTION
	};

	for (i = 0; i < CP_HI3531_VPSS_CAMERA_CONFIGURE_SIZE; i++) {
		//解析is_use_cylind
		if (!get_module_conf_xml_int_prop(&tmp_value, module, module->conf,
			tmp_stitch_correction[i], CP_HI3531_VPSS_CONF_STRING_IS_USE_CYLIND, 0)) {
			return -1;
		}
		if (!tmp_value) {
			hacc->stitch_config.csc[i].is_used = cp_false;
		}
		else {
			hacc->stitch_config.csc[i].is_used = cp_true;
		}

		//解析center_horizontal_offset
		if (!get_module_conf_xml_int_prop(&tmp_value, module, module->conf,
			tmp_stitch_correction[i], CP_HI3531_VPSS_CONF_STRING_CENTER_HORIZONTAL_OFFSET, 0)) {
			return -1;
		}
		if (tmp_value < -127 || tmp_value > 127) {
			cp_module_log(error, module,
				"configure [%s] error. [%d] value not [-127, 127].",
				CP_HI3531_VPSS_CONF_STRING_CENTER_HORIZONTAL_OFFSET,
				tmp_value);
			return -2;
		}
		hacc->stitch_config.csc[i].center_horizontal_offset = tmp_value;

		//解析center_vertical_offset
		if (!get_module_conf_xml_int_prop(&tmp_value, module, module->conf,
			tmp_stitch_correction[i], CP_HI3531_VPSS_CONF_STRING_CENTER_VERTICAL_OFFSET, 0)) {
			return -1;
		}
		if (tmp_value < -127 || tmp_value > 127) {
			cp_module_log(error, module,
				"configure [%s] error. [%d] value not [-127, 127].",
				CP_HI3531_VPSS_CONF_STRING_CENTER_VERTICAL_OFFSET,
				tmp_value);
			return -2;
		}
		hacc->stitch_config.csc[i].center_vertical_offset = tmp_value;

		//解析ratio
		if (!get_module_conf_xml_int_prop(&tmp_value, module, module->conf,
			tmp_stitch_correction[i], CP_HI3531_VPSS_CONF_STRING_RATIO, 0)) {
			return -1;
		}
		if (tmp_value < 0 || tmp_value > 500) {
			cp_module_log(error, module,
				"configure [%s] error. [%d] value not [0, 500].",
				CP_HI3531_VPSS_CONF_STRING_RATIO,
				tmp_value);
			return -2;
		}
		hacc->stitch_config.csc[i].ratio = tmp_value;
	}

	return 0;
}

/************************************************************************/
/*解析auto配置文件                                                     */
/************************************************************************/
cp_int32_t	hi3531_vpss_parse_auto_configure(cp_module_t *module, cp_hi3531_vpss_configure_t *hacc)
{
	cp_int32_t						i = 0;
	cp_int32_t						tmp_value = 0;



	//解析is_auto
	if (!get_module_conf_xml_int_prop(&tmp_value, module, module->conf,
		CP_HI3531_VPSS_CONF_STRING_AUTO_CONFIGURE, CP_HI3531_VPSS_CONF_STRING_IS_AUTO, 0)) {
		return -1;
	}
	if (!tmp_value) {
		hacc->stitch_config.auto_config.is_auto = cp_false;
	}
	else {
		hacc->stitch_config.auto_config.is_auto = cp_true;
	}

	//解析auto_size
	if (!get_module_conf_xml_int_prop(&tmp_value, module, module->conf,
		CP_HI3531_VPSS_CONF_STRING_AUTO_CONFIGURE, CP_HI3531_VPSS_CONF_STRING_AUTO_SIZE, 0)) {
		return -1;
	}
	hacc->stitch_config.auto_config.auto_size = tmp_value;

	return 0;
}