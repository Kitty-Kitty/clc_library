/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-12-26

Description:

**************************************************************************/
#include "cp_ipc_func_conf.h"
#include "cp_ipc_func_conf_string.h"




cp_static cp_bool_t get_module_conf_xml_int_prop(cp_int32_t *dest, cp_module_t *module,
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

cp_static cp_bool_t get_conf_xml_string_prop(cp_char_t *dest, cp_int32_t len, cp_module_t *module,
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


cp_int32_t	init_ipc_func_conf(cp_module_t *module, cp_ipc_func_conf_t *ipc_conf)
{
	cp_memset(ipc_conf, 0, cp_sizeof(cp_ipc_func_conf_t));
	return 0;
}

cp_int32_t	set_ipc_func_conf(cp_module_t *module, cp_ipc_func_conf_t *ipc_conf)
{
	cp_int32_t						tmp_value = 0;



	if (!module || !ipc_conf) {
		return -1;
	}

	//½âÎöip
	if (!get_conf_xml_string_prop(ipc_conf->rtp_conf.ip, 
		cp_sizeof(ipc_conf->rtp_conf.ip), module, module->conf,
		CP_IPC_FUNC_CONF_STRING_RTP_CONFIGURE, CP_IPC_FUNC_CONF_STRING_IP, CP_NULL)) {
		return -2;
	}

	//½âÎöport
	if (!get_module_conf_xml_int_prop(&tmp_value, module, module->conf,
		CP_IPC_FUNC_CONF_STRING_RTP_CONFIGURE, CP_IPC_FUNC_CONF_STRING_PORT, 0)) {
		return -3;
	}
	ipc_conf->rtp_conf.port = tmp_value;

	//½âÎössrc
	if (!get_module_conf_xml_int_prop(&tmp_value, module, module->conf,
		CP_IPC_FUNC_CONF_STRING_RTP_CONFIGURE, CP_IPC_FUNC_CONF_STRING_SSRC, 0)) {
		return -3;
	}
	ipc_conf->rtp_conf.ssrc = tmp_value;
	
	return 0;
}

