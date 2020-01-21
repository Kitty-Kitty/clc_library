/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-12-20

Description:

**************************************************************************/
#include "cp_log.h"
#include "cp_conf.h"
#include "cp_css_encrypt_dev_manager_conf.h"
#include "cp_css_encrypt_dev_manager_conf_string.h"


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

/*******************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: css_encrypt_dev_manager_parse_configure
*
* 函数全名: css_encrypt_dev_manager_parse_configure
*
* 函数访问: public
*
* 函数说明: 解析配置文件
*
* 参    数: const cp_module_manager_t * manager						[in/out]参数说明
* 参    数: cp_css_encrypt_dev_configure_t * cedc						[in/out]参数说明
*
* 返 回 值: cp_int32_t
*           0  : 成功
*         非0  : 失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2017-8-21 11:46:04
********************************************************************************/
cp_int32_t	css_encrypt_dev_manager_parse_configure(const cp_module_manager_t *manager, cp_css_encrypt_dev_configure_t *cedc)
{
	cp_int32_t									tmp_value = 0;
	cp_int32_t									tmp_ret_int = 0;
	cp_int32_t									i = 0;
	cp_conf_xml_t								tmp_conf_xml = { 0, };



	if (!manager || !cedc) {
		return -1;
	}

	//解析type
	if (!get_module_conf_xml_string_prop(cedc->type,
		cp_sizeof(cedc->type), manager, manager->conf->conf_xml,
		CP_CSS_ENCRYPT_DEV_MANAGER_CONF_STRING_GENERAL, CP_CSS_ENCRYPT_DEV_MANAGER_CONF_STRING_TYPE, CP_NULL)) {
		return -1;
	}

	//解析source file
	if (!get_module_conf_xml_string_prop(cedc->source_file,
		cp_sizeof(cedc->source_file), manager, manager->conf->conf_xml,
		CP_CSS_ENCRYPT_DEV_CONF_STRING_ENCRYPT_DATA_CONFIGURE, CP_CSS_ENCRYPT_DEV_CONF_STRING_SOURCE_FILE, CP_NULL)) {
		return -1;
	}

	//解析destination file
	if (!get_module_conf_xml_string_prop(cedc->destination_file,
		cp_sizeof(cedc->destination_file), manager, manager->conf->conf_xml,
		CP_CSS_ENCRYPT_DEV_CONF_STRING_ENCRYPT_DATA_CONFIGURE, CP_CSS_ENCRYPT_DEV_CONF_STRING_DESTINATION_FILE, CP_NULL)) {
		return -1;
	}

	return 0;
}
