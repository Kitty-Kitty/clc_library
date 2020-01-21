/*******************************************************************************
*
*Copyright:novigo
*
*File name: cp_hi3536_dev_conf.c
*
*Author:fangzhenmu@novigo.com.cn
*
*Version: 1.0
*
*Date:2017/08/17
*
*Description: create (cp_hi3536_dev_conf.c)
*
*Others:
*
*History:
*******************************************************************************/
#include "cp_log.h"
#include "cp_conf.h"
#include "cp_hi3536_dev_conf.h"



cp_inline cp_static cp_bool_t get_module_conf_xml_int_prop(cp_int32_t *dest, const cp_module_t *module,
	const cp_conf_xml_t *conf_xml, const char *context, const char *key, int def)
{
	cp_int32_t							tmp_value = 0;



	if (!conf_xml || !module) {
		return cp_false;
	}
	tmp_value = cp_conf_xml_getint(conf_xml, context, key, def);
	if (tmp_value < 0) {
		cp_module_log(notice, module, "get [%s:%s] warning!", context, key);
		//return cp_false;
	}
	*dest = tmp_value;
	return cp_true;
}

cp_inline cp_static cp_bool_t get_module_conf_xml_bool_prop(cp_bool_t *dest, const cp_module_t *module,
	const cp_conf_xml_t *conf_xml, const char *context, const char *key, int def)
{
	cp_int32_t							tmp_value = 0;



	if (!get_module_conf_xml_int_prop(&tmp_value, module, conf_xml, context, key, def)) {
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

cp_inline cp_static cp_bool_t get_module_conf_xml_string_prop(cp_char_t *dest, cp_int32_t len, const cp_module_t *module,
	const cp_conf_xml_t *conf_xml, const char *context, const char *key, const char* def)
{
	cp_char_t							*tmp_value = 0;



	tmp_value = (cp_char_t *)cp_conf_xml_getstring(conf_xml, context, key, def);
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

/************************************************************************/
/*解析配置文件                                                           */
/************************************************************************/
cp_int32_t	hi3536_dev_parse_configure(cp_module_t *module, cp_hi3536_dev_configure_t *hdc)
{
	cp_int32_t						tmp_value = 0;




	//解析key
	if (!get_module_conf_xml_string_prop(hdc->key,
		cp_sizeof(hdc->key), module, module->conf->conf_xml,
		CP_HI3531_DEV_CONF_STRING_HI3536_ENCRYPT_CONFIGURE, CP_HI3531_DEV_CONF_STRING_KEY, CP_NULL)) {
		return -2;
	}

	//解析iv
	if (!get_module_conf_xml_string_prop(hdc->iv,
		cp_sizeof(hdc->iv), module, module->conf->conf_xml,
		CP_HI3531_DEV_CONF_STRING_HI3536_ENCRYPT_CONFIGURE, CP_HI3531_DEV_CONF_STRING_IV, CP_NULL)) {
		return -2;
	}

	//解析alg
	if (!get_module_conf_xml_int_prop(&tmp_value, module, module->conf->conf_xml,
		CP_HI3531_DEV_CONF_STRING_HI3536_ENCRYPT_CONFIGURE, CP_HI3531_DEV_CONF_STRING_ALG, 0)) {
		return -2;
	}
	hdc->alg = tmp_value;

	//解析bit_width
	if (!get_module_conf_xml_int_prop(&tmp_value, module, module->conf->conf_xml,
		CP_HI3531_DEV_CONF_STRING_HI3536_ENCRYPT_CONFIGURE, CP_HI3531_DEV_CONF_STRING_BIT_WIDTH, 0)) {
		return -2;
	}
	hdc->bit_width = tmp_value;

	//解析work_mode
	if (!get_module_conf_xml_int_prop(&tmp_value, module, module->conf->conf_xml,
		CP_HI3531_DEV_CONF_STRING_HI3536_ENCRYPT_CONFIGURE, CP_HI3531_DEV_CONF_STRING_WORK_MODE, 0)) {
		return -2;
	}
	hdc->work_mode = tmp_value;

	//解析key_length
	if (!get_module_conf_xml_int_prop(&tmp_value, module, module->conf->conf_xml,
		CP_HI3531_DEV_CONF_STRING_HI3536_ENCRYPT_CONFIGURE, CP_HI3531_DEV_CONF_STRING_KEY_LENGTH, 0)) {
		return -2;
	}
	hdc->key_length = tmp_value;

	//解析change_flag_iv
	if (!get_module_conf_xml_int_prop(&tmp_value, module, module->conf->conf_xml,
		CP_HI3531_DEV_CONF_STRING_HI3536_ENCRYPT_CONFIGURE, CP_HI3531_DEV_CONF_STRING_CHANGE_FLAG_IV, 0)) {
		return -2;
	}
	hdc->change_flag_iv = tmp_value;

	return 0;
}


