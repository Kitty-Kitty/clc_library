/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-12-20

Description:

**************************************************************************/
#include "cp_log.h"
#include "cp_conf.h"
#include "cp_hi3531_manager_conf.h"



cp_inline cp_static cp_bool_t get_module_conf_xml_int_prop(cp_int32_t *dest, const cp_module_manager_t *manager,
	const cp_conf_t *conf, const char *context, const char *key, int def)
{
	cp_int32_t							tmp_value = 0;



	if (!conf || !manager) {
		return cp_false;
	}
	tmp_value = cp_conf_xml_getint(conf->conf_xml, context, key, def);
	if (tmp_value < 0) {
		cp_manager_log(notice, manager, "get [%s:%s] warning!", context, key);
		//return cp_false;
	}
	*dest = tmp_value;
	return cp_true;
}

cp_inline cp_static cp_bool_t get_module_conf_xml_string_prop(cp_char_t *dest, cp_int32_t len, const cp_module_manager_t *manager,
	const cp_conf_t *conf, const char *context, const char *key, const char* def)
{
	cp_char_t							*tmp_value = 0;



	tmp_value = (cp_char_t *)cp_conf_xml_getstring(conf->conf_xml, context, key, def);
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
* 函数名称: hi3531_manager_parse_configure
*
* 函数说明: 解析配置文件
*
* 参    数: cp_module_t * manager						[in]参数说明
* 参    数: cp_hi3531_configure_t * hacc						[in]参数说明
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
cp_int32_t	hi3531_manager_parse_configure(const cp_module_manager_t *manager, cp_hi3531_configure_t *hacc)
{
	cp_int32_t						tmp_ret_int = 0;



// 	//解析system部分内容
// 	tmp_ret_int = hi3531_manager_parse_system_configure(manager, hacc);
// 	if (tmp_ret_int) {
// 		cp_manager_log(error, manager, "hi3531_manager_parse_system_configure() error.");
// 		return tmp_ret_int;
// 	}

	//解析vdec部分内容
	tmp_ret_int = hi3531_manager_parse_vdec_configure(manager, hacc);
	if (tmp_ret_int) {
		cp_manager_log(error, manager, "hi3531_manager_parse_vdec_configure() error.");
		return tmp_ret_int;
	}

	return 0;
}

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: hi3531_manager_parse_system_configure
*
* 函数说明: 解析system配置文件
*
* 参    数: cp_module_manager_t * manager						[in]参数说明
* 参    数: cp_hi3531_configure_t * hacc						[in]参数说明
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
cp_int32_t	hi3531_manager_parse_system_configure(const cp_module_manager_t *manager, cp_hi3531_configure_t *hacc)
{
	cp_int32_t						tmp_value = 0;
	cp_int32_t						tmp_ret_int = 0;



	if (!manager || !hacc) {
		return -1;
	}

	//解析max_pool_count
	if (!get_module_conf_xml_int_prop(&tmp_value, manager, manager->conf,
		CP_HI3531_MANAGER_CONF_STRING_HI3531_SYSTEM, CP_HI3531_MANAGER_CONF_STRING_MAX_POOL_COUNT, 0)) {
		return -1;
	}
	hacc->system_conf.max_pool_count = tmp_value;

	//解析align_width
	if (!get_module_conf_xml_int_prop(&tmp_value, manager, manager->conf,
		CP_HI3531_MANAGER_CONF_STRING_HI3531_SYSTEM, CP_HI3531_MANAGER_CONF_STRING_ALIGN_WIDTH, 0)) {
		return -2;
	}
	hacc->system_conf.align_width = tmp_value;

	return 0;
}

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: hi3531_manager_parse_vdec_configure
*
* 函数说明: 解析vdec配置文件
*
* 参    数: cp_module_manager_t * manager						[in]参数说明
* 参    数: cp_hi3531_configure_t * hacc						[in]参数说明
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
cp_int32_t	hi3531_manager_parse_vdec_configure(const cp_module_manager_t *manager, cp_hi3531_configure_t *hacc)
{
	cp_int32_t						tmp_value = 0;
	cp_int32_t						tmp_ret_int = 0;



	if (!manager || !hacc) {
		return -1;
	}

	//解析vdec_mpp_dev_id
	if (!get_module_conf_xml_int_prop(&tmp_value, manager, manager->conf,
		CP_HI3531_MANAGER_CONF_STRING_HI3531_VDEC, CP_HI3531_MANAGER_CONF_STRING_VDEC_MPP_DEV_ID, 0)) {
		return -1;
	}
	hacc->vdec_conf.vdec_mpp_dev_id = tmp_value;

	//解析vdec_mpp_channel_number
	if (!get_module_conf_xml_int_prop(&tmp_value, manager, manager->conf,
		CP_HI3531_MANAGER_CONF_STRING_HI3531_VDEC, CP_HI3531_MANAGER_CONF_STRING_VDEC_MPP_CHANNEL_NUMBER, 0)) {
		return -1;
	}
	hacc->vdec_conf.vdec_mpp_channel_number = tmp_value;

	//解析vdec_mmz_name
	if (!get_module_conf_xml_string_prop(hacc->vdec_conf.vdec_mmz_name, 
		cp_sizeof(hacc->vdec_conf.vdec_mmz_name), manager, manager->conf,
		CP_HI3531_MANAGER_CONF_STRING_HI3531_VDEC, CP_HI3531_MANAGER_CONF_STRING_VDEC_MMZ_NAME, CP_NULL)) {
		return -2;
	}

	return 0;
}


