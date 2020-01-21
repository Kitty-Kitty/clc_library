/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-12-20

Description:

**************************************************************************/
#include "cp_log.h"
#include "cp_conf.h"
#include "cp_ptp_func_conf.h"



cp_inline cp_static cp_bool_t get_module_conf_xml_int_prop(cp_int32_t *dest, cp_module_t *module, 
	cp_conf_t *conf, const char *context, const char *key, int def)
{
	cp_int32_t							tmp_value = 0;



	if (!conf || !module) {
		return cp_false;
	}
	tmp_value = cp_conf_xml_getint(conf->conf_xml, context, key, def);
	if (tmp_value < 0) {
		cp_module_log(error, module, "get [%s:%s] failed!", context, key);
		return cp_false;
	}
	*dest = tmp_value;
	return cp_true;
}

cp_inline cp_static cp_bool_t get_conf_xml_string_prop(cp_char_t *dest, cp_int32_t len, cp_module_t *module,
	cp_conf_t *conf, const char *context, const char *key, const char* def)
{
	cp_char_t							*tmp_value = 0;



	if (!conf || !module) {
		return cp_false;
	}
	tmp_value = (cp_char_t*)cp_conf_xml_getstring(conf->conf_xml, context, key, def);
	if (!tmp_value) {
		cp_module_log(error, module, "get [%s:%s] failed!", context, key);
		return cp_false;
	}
	if ((cp_int32_t)cp_strlen(tmp_value) > len) {
		cp_module_log(error, module, "get [%s:%s] failed! dest buffer length[%d] error.",
			context, key, cp_strlen(tmp_value));
		return cp_false;
	}
	cp_strncpy(dest, tmp_value, cp_strlen(tmp_value));
	return cp_true;
}


/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: ptp_func_parse_configure
*
* 函数说明: 解析配置文件
*
* 参    数: cp_module_t * module						[in]参数说明
* 参    数: cp_ptp_func_configure_t * fc						[in]参数说明
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
cp_int32_t	ptp_func_parse_configure(cp_module_t *module, cp_ptp_func_configure_t *fc)
{
	cp_int32_t						tmp_value = 0;



	if (!module || !fc) {
		return -1;
	}

	//解析port
	if (!get_module_conf_xml_int_prop(&tmp_value, module, module->conf,
		CP_PTP_FUNC_CONF_STRING_PTP_CONFIGURE, CP_PTP_FUNC_CONF_STRING_MULTICAST_PORT, 0)) {
		return -1;
	}
	fc->port = tmp_value;

	//解析use_ptp
	if (!get_module_conf_xml_int_prop(&tmp_value, module, module->conf,
		CP_PTP_FUNC_CONF_STRING_PTP_CONFIGURE, CP_PTP_FUNC_CONF_STRING_USE_PTP, 0)) {
		return -3;
	}
	if (0 == tmp_value) {
		fc->is_use = cp_false;
	}
	else {
		fc->is_use = cp_true;
	}

	//解析used_debug
	if (!get_module_conf_xml_int_prop(&tmp_value, module, module->conf,
		CP_PTP_FUNC_CONF_STRING_PTP_CONFIGURE, CP_PTP_FUNC_CONF_STRING_USED_DEBUG, 0)) {
		return -3;
	}
	if (0 == tmp_value) {
		fc->is_debug = cp_false;
	}
	else {
		fc->is_debug = cp_true;
	}

	//解析multicast_address
	if (!get_conf_xml_string_prop(fc->address, cp_sizeof(fc->address), module, module->conf,
		CP_PTP_FUNC_CONF_STRING_PTP_CONFIGURE, CP_PTP_FUNC_CONF_STRING_MULTICAST_ADDRESS, 0)) {
		return -4;
	}

	//解析debug_path
	if (!get_conf_xml_string_prop(fc->debug_path, cp_sizeof(fc->debug_path), module, module->conf,
		CP_PTP_FUNC_CONF_STRING_PTP_CONFIGURE, CP_PTP_FUNC_CONF_STRING_DEBUG_PATH, 0)) {
		return -4;
	}

	return 0;
}