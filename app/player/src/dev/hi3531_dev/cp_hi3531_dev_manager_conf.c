/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-12-20

Description:

**************************************************************************/
#include "cp_log.h"
#include "cp_conf.h"
#include "cp_hi3531_dev_manager_conf.h"


cp_inline cp_static cp_bool_t get_module_conf_xml_int_prop(cp_int32_t *dest, const cp_module_manager_t *manager,
	const cp_conf_xml_t *conf_xml, const char *context, const char *key, int def)
{
	cp_int32_t							tmp_value = 0;



	if (!conf_xml || !manager) {
		return cp_false;
	}
	tmp_value = cp_conf_xml_getint(conf_xml, context, key, def);
	if (tmp_value < 0) {
		cp_manager_log(notice, manager, "get [%s:%s] warning!", context, key);
		//return cp_false;
	}
	*dest = tmp_value;
	return cp_true;
}

cp_inline cp_static cp_bool_t get_module_conf_xml_bool_prop(cp_bool_t *dest, const cp_module_manager_t *manager,
	const cp_conf_xml_t *conf_xml, const char *context, const char *key, int def)
{
	cp_int32_t							tmp_value = 0;



	if (!get_module_conf_xml_int_prop(&tmp_value, manager, conf_xml, context, key, def)) {
		return -1;
	}

	if (0 == tmp_value) {
		*dest = cp_false;
	}
	else {
		*dest = cp_true;
	}

	return cp_true;
}

cp_inline cp_static cp_bool_t get_module_conf_xml_string_prop(cp_char_t *dest, cp_int32_t len, const cp_module_manager_t *manager,
	const cp_conf_xml_t *conf_xml, const char *context, const char *key, const char* def)
{
	cp_char_t							*tmp_value = 0;



	tmp_value = (cp_char_t *)cp_conf_xml_getstring(conf_xml, context, key, def);
	if (!tmp_value) {
		cp_manager_log(error, manager, "get [%s:%s] failed!", context, key);
		return cp_false;
	}
	if ((cp_int32_t)cp_strlen(tmp_value) > len) {
		cp_manager_log(error, manager, "get [%s:%s] failed! dest buffer length[%d] error.",
			context, key, cp_strlen(tmp_value));
		return cp_false;
	}
	cp_strncpy(dest, tmp_value, cp_strlen(tmp_value));
	return cp_true;
}

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: hi3531_dev_manager_parse_configure
*
* 函数说明: 解析配置文件
*
* 参    数: cp_module_t * manager						[in]参数说明
* 参    数: cp_hi3531_dev_configure_t * hacc						[in]参数说明
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
cp_int32_t	hi3531_dev_manager_parse_configure(const cp_module_manager_t *manager, cp_hi3531_dev_configure_t *hacc)
{
	cp_int32_t						tmp_ret_int = 0;



	//解析system部分内容
	tmp_ret_int = hi3531_dev_manager_parse_system_configure(manager, hacc);
	if (tmp_ret_int) {
		cp_manager_log(error, manager, "hi3531_dev_manager_parse_system_configure() error.");
		return tmp_ret_int;
	}

	// 	//解析vdec部分内容
	// 	tmp_ret_int = hi3531_dev_manager_parse_vdec_configure(manager, hacc);
	// 	if (tmp_ret_int) {
	// 		cp_manager_log(error, manager, "hi3531_dev_manager_parse_vdec_configure() error.");
	// 		return tmp_ret_int;
	// 	}

	//解析vo部分内容
	tmp_ret_int = hi3531_dev_manager_parse_vo_configure(manager, hacc);
	if (tmp_ret_int) {
		cp_manager_log(error, manager, "hi3531_dev_manager_parse_vo_configure() error.");
		return tmp_ret_int;
	}

	//解析hdmi部分内容
	tmp_ret_int = hi3531_dev_manager_parse_hdmi_configure(manager, hacc);
	if (tmp_ret_int) {
		cp_manager_log(error, manager, "hi3531_dev_manager_parse_hdmi_configure() error.");
		return tmp_ret_int;
	}

	return 0;
}

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: hi3531_dev_manager_parse_system_configure
*
* 函数说明: 解析system配置文件
*
* 参    数: cp_module_manager_t * manager						[in]参数说明
* 参    数: cp_hi3531_dev_configure_t * hacc						[in]参数说明
*
* 返 回 值: cp_int32_t
*           0  : 成功
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2017-06-29 19:02:48
******************************************************************************************************/
cp_int32_t	hi3531_dev_manager_parse_system_configure(const cp_module_manager_t *manager, cp_hi3531_dev_configure_t *hacc)
{
	cp_int32_t						tmp_value = 0;
	cp_int32_t						tmp_ret_int = 0;



	if (!manager || !hacc) {
		return -1;
	}

	//解析max_pool_count
	if (!get_module_conf_xml_int_prop(&tmp_value, manager, manager->conf->conf_xml,
		CP_HI3531_DEV_MANAGER_CONF_STRING_HI3531_SYSTEM, CP_HI3531_DEV_MANAGER_CONF_STRING_MAX_POOL_COUNT, 0)) {
		return -1;
	}
	hacc->system_conf.max_pool_count = tmp_value;

	//解析align_width
	if (!get_module_conf_xml_int_prop(&tmp_value, manager, manager->conf->conf_xml,
		CP_HI3531_DEV_MANAGER_CONF_STRING_HI3531_SYSTEM, CP_HI3531_DEV_MANAGER_CONF_STRING_ALIGN_WIDTH, 0)) {
		return -2;
	}
	hacc->system_conf.align_width = tmp_value;

	return 0;
}

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: hi3531_dev_manager_parse_vdec_configure
*
* 函数说明: 解析vdec配置文件
*
* 参    数: cp_module_manager_t * manager						[in]参数说明
* 参    数: cp_hi3531_dev_configure_t * hacc						[in]参数说明
*
* 返 回 值: cp_int32_t
*           0  : 成功
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2017-06-29 19:03:11
******************************************************************************************************/
cp_int32_t	hi3531_dev_manager_parse_vdec_configure(const cp_module_manager_t *manager, cp_hi3531_dev_configure_t *hacc)
{
	cp_int32_t						tmp_value = 0;
	cp_int32_t						tmp_ret_int = 0;



	if (!manager || !hacc) {
		return -1;
	}

	//解析vdec_mpp_dev_id
	if (!get_module_conf_xml_int_prop(&tmp_value, manager, manager->conf->conf_xml,
		CP_HI3531_DEV_MANAGER_CONF_STRING_HI3531_DEV_VDEC, CP_HI3531_DEV_MANAGER_CONF_STRING_VDEC_MPP_DEV_ID, 0)) {
		return -1;
	}
	hacc->vdec_conf.vdec_mpp_dev_id = tmp_value;

	//解析vdec_mpp_channel_number
	if (!get_module_conf_xml_int_prop(&tmp_value, manager, manager->conf->conf_xml,
		CP_HI3531_DEV_MANAGER_CONF_STRING_HI3531_DEV_VDEC, CP_HI3531_DEV_MANAGER_CONF_STRING_VDEC_MPP_CHANNEL_NUMBER, 0)) {
		return -1;
	}
	hacc->vdec_conf.vdec_mpp_channel_number = tmp_value;

	//解析vdec_mmz_name
	if (!get_module_conf_xml_string_prop(hacc->vdec_conf.vdec_mmz_name,
		cp_sizeof(hacc->vdec_conf.vdec_mmz_name), manager, manager->conf->conf_xml,
		CP_HI3531_DEV_MANAGER_CONF_STRING_HI3531_DEV_VDEC, CP_HI3531_DEV_MANAGER_CONF_STRING_VDEC_MMZ_NAME, CP_NULL)) {
		return -2;
	}

	return 0;
}

/*******************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: hi3531_dev_manager_parse_vo_configure
*
* 函数全名: hi3531_dev_manager_parse_vo_configure
*
* 函数访问: public
*
* 函数说明: 函数说明
*
* 参    数: const cp_module_manager_t * manager						[in/out]参数说明
* 参    数: cp_hi3531_dev_configure_t * hacc						[in/out]参数说明
*
* 返 回 值: cp_int32_t
*           0  : 成功
*         非0  : 失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2017-7-27 14:04:37
********************************************************************************/
cp_int32_t	hi3531_dev_manager_parse_vo_configure(const cp_module_manager_t *manager, cp_hi3531_dev_configure_t *hacc)
{
	cp_int32_t									tmp_value = 0;
	cp_int32_t									tmp_ret_int = 0;
	cp_int32_t									i = 0;
	cp_conf_xml_t								tmp_conf_xml = { 0, };



	if (!manager || !hacc) {
		return -1;
	}

	tmp_ret_int = cp_conf_xml_get_conf(manager->conf->conf_xml,
		CP_HI3531_DEV_MANAGER_CONF_STRING_HI3531_VO_ITEMS,
		CP_HI3531_DEV_MANAGER_CONF_STRING_HI3531_VO_ITEM,
		&tmp_conf_xml);
	if (tmp_ret_int) {
		cp_manager_log(error, manager, "get [%s:%s] warning!",
			CP_HI3531_DEV_MANAGER_CONF_STRING_HI3531_VO_ITEMS,
			CP_HI3531_DEV_MANAGER_CONF_STRING_HI3531_VO_ITEM);
		return tmp_ret_int;
	}

	for (i = 0; !tmp_ret_int; tmp_ret_int = cp_conf_xml_getnext_conf(&tmp_conf_xml,
		CP_HI3531_DEV_MANAGER_CONF_STRING_HI3531_VO_ITEM, &tmp_conf_xml), i++) {

		hacc->vo_conf[i].is_used = cp_false;

		//解析dev_id
		if (!get_module_conf_xml_int_prop(&tmp_value, manager, &tmp_conf_xml,
			CP_HI3531_DEV_MANAGER_CONF_STRING_HI3531_VO_ITEM, CP_HI3531_DEV_MANAGER_CONF_STRING_DEV_ID, 0)) {
			continue;
		}
		hacc->vo_conf[i].dev_id = tmp_value;

		//解析channel_id
		if (!get_module_conf_xml_int_prop(&tmp_value, manager, &tmp_conf_xml,
			CP_HI3531_DEV_MANAGER_CONF_STRING_HI3531_VO_ITEM, CP_HI3531_DEV_MANAGER_CONF_STRING_CHANNEL_ID, 0)) {
			continue;
		}
		hacc->vo_conf[i].channel_id = tmp_value;

		//解析source_frame_rate
		if (!get_module_conf_xml_int_prop(&tmp_value, manager, &tmp_conf_xml,
			CP_HI3531_DEV_MANAGER_CONF_STRING_HI3531_VO_ITEM, CP_HI3531_DEV_MANAGER_CONF_STRING_SOURCE_FRAME_RATE, 0)) {
			continue;
		}
		hacc->vo_conf[i].source_frame_rate = tmp_value;

		//解析back_color
		if (!get_module_conf_xml_string_prop(hacc->vo_conf[i].back_color,
			cp_sizeof(hacc->vo_conf[i].back_color), manager, &tmp_conf_xml,
			CP_HI3531_DEV_MANAGER_CONF_STRING_HI3531_VO_ITEM, CP_HI3531_DEV_MANAGER_CONF_STRING_BACK_COLOR, CP_NULL)) {
			continue;
		}

		//解析mem_name
		if (!get_module_conf_xml_string_prop(hacc->vo_conf[i].mem_name,
			cp_sizeof(hacc->vo_conf[i].mem_name), manager, &tmp_conf_xml,
			CP_HI3531_DEV_MANAGER_CONF_STRING_HI3531_VO_ITEM, CP_HI3531_DEV_MANAGER_CONF_STRING_MEM_NAME, CP_NULL)) {
			continue;
		}

		//解析intf_type
		if (!get_module_conf_xml_int_prop(&tmp_value, manager, &tmp_conf_xml,
			CP_HI3531_DEV_MANAGER_CONF_STRING_HI3531_VO_ITEM, CP_HI3531_DEV_MANAGER_CONF_STRING_INTF_TYPE, 0)) {
			continue;
		}
		hacc->vo_conf[i].intf_type = tmp_value;

		//解析intf_sync
		if (!get_module_conf_xml_int_prop(&tmp_value, manager, &tmp_conf_xml,
			CP_HI3531_DEV_MANAGER_CONF_STRING_HI3531_VO_ITEM, CP_HI3531_DEV_MANAGER_CONF_STRING_INTF_SYNC, 0)) {
			continue;
		}
		hacc->vo_conf[i].intf_sync = tmp_value;

		//解析enable_double_frame
		if (!get_module_conf_xml_bool_prop(&hacc->vo_conf[i].enable_double_frame, manager, &tmp_conf_xml,
			CP_HI3531_DEV_MANAGER_CONF_STRING_HI3531_VO_ITEM, CP_HI3531_DEV_MANAGER_CONF_STRING_ENABLE_DOUBLE_FRAME, 0)) {
			continue;
		}

		hacc->vo_conf[i].is_used = cp_true;
	}

	return 0;
}

/*******************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: hi3531_dev_manager_parse_hdmi_configure
*
* 函数全名: hi3531_dev_manager_parse_hdmi_configure
*
* 函数访问: public
*
* 函数说明: 解析hdmi配置文件
*
* 参    数: const cp_module_manager_t * manager					[in]参数说明
* 参    数: cp_hi3531_dev_configure_t * hacc						[in]参数说明
*
* 返 回 值: cp_int32_t
*           0  : 成功
*         非0  : 失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2017-7-27 14:35:12
********************************************************************************/
cp_int32_t	hi3531_dev_manager_parse_hdmi_configure(const cp_module_manager_t *manager, cp_hi3531_dev_configure_t *hacc)
{
	cp_int32_t						tmp_value = 0;
	cp_int32_t						tmp_ret_int = 0;



	if (!manager || !hacc) {
		return -1;
	}

	//解析enable_hdmi
	if (!get_module_conf_xml_bool_prop(&hacc->hdmi_conf.enable_hdmi, manager, manager->conf->conf_xml,
		CP_HI3531_DEV_MANAGER_CONF_STRING_HI3531_HDMI, CP_HI3531_DEV_MANAGER_CONF_STRING_ENABLE_HDMI, 0)) {
		return -1;
	}

	//解析enable_video
	if (!get_module_conf_xml_bool_prop(&hacc->hdmi_conf.enable_video, manager, manager->conf->conf_xml,
		CP_HI3531_DEV_MANAGER_CONF_STRING_HI3531_HDMI, CP_HI3531_DEV_MANAGER_CONF_STRING_ENABLE_VIDEO, 0)) {
		return -1;
	}

	//解析video_out_mode
	if (!get_module_conf_xml_int_prop(&tmp_value, manager, manager->conf->conf_xml,
		CP_HI3531_DEV_MANAGER_CONF_STRING_HI3531_HDMI, CP_HI3531_DEV_MANAGER_CONF_STRING_VIDEO_OUT_MODE, 0)) {
		return -1;
	}
	hacc->hdmi_conf.video_out_mode = tmp_value;

	//解析enable_xvycc_mode
	if (!get_module_conf_xml_bool_prop(&hacc->hdmi_conf.enable_xvycc_mode, manager, manager->conf->conf_xml,
		CP_HI3531_DEV_MANAGER_CONF_STRING_HI3531_HDMI, CP_HI3531_DEV_MANAGER_CONF_STRING_ENABLE_XVYCC_MODE, 0)) {
		return -1;
	}

	//解析enable_audio
	if (!get_module_conf_xml_bool_prop(&hacc->hdmi_conf.enable_audio, manager, manager->conf->conf_xml,
		CP_HI3531_DEV_MANAGER_CONF_STRING_HI3531_HDMI, CP_HI3531_DEV_MANAGER_CONF_STRING_ENABLE_AUDIO, 0)) {
		return -1;
	}

	//解析enable_multi_channel
	if (!get_module_conf_xml_bool_prop(&hacc->hdmi_conf.enable_multi_channel, manager, manager->conf->conf_xml,
		CP_HI3531_DEV_MANAGER_CONF_STRING_HI3531_HDMI, CP_HI3531_DEV_MANAGER_CONF_STRING_ENABLE_MULTI_CHANNEL, 0)) {
		return -1;
	}

	return 0;
}