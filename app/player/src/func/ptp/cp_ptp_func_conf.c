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
* ��Ȩ����: fz & novigo
*
* ��������: ptp_func_parse_configure
*
* ����˵��: ���������ļ�
*
* ��    ��: cp_module_t * module						[in]����˵��
* ��    ��: cp_ptp_func_configure_t * fc						[in]����˵��
*
* �� �� ֵ: cp_int32_t
*           0  : �ɹ� 
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2016-12-20 15:14:47
******************************************************************************************************/
cp_int32_t	ptp_func_parse_configure(cp_module_t *module, cp_ptp_func_configure_t *fc)
{
	cp_int32_t						tmp_value = 0;



	if (!module || !fc) {
		return -1;
	}

	//����port
	if (!get_module_conf_xml_int_prop(&tmp_value, module, module->conf,
		CP_PTP_FUNC_CONF_STRING_PTP_CONFIGURE, CP_PTP_FUNC_CONF_STRING_MULTICAST_PORT, 0)) {
		return -1;
	}
	fc->port = tmp_value;

	//����use_ptp
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

	//����used_debug
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

	//����multicast_address
	if (!get_conf_xml_string_prop(fc->address, cp_sizeof(fc->address), module, module->conf,
		CP_PTP_FUNC_CONF_STRING_PTP_CONFIGURE, CP_PTP_FUNC_CONF_STRING_MULTICAST_ADDRESS, 0)) {
		return -4;
	}

	//����debug_path
	if (!get_conf_xml_string_prop(fc->debug_path, cp_sizeof(fc->debug_path), module, module->conf,
		CP_PTP_FUNC_CONF_STRING_PTP_CONFIGURE, CP_PTP_FUNC_CONF_STRING_DEBUG_PATH, 0)) {
		return -4;
	}

	return 0;
}