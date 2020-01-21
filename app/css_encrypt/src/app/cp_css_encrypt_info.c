/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/


#include "cp_css_encrypt_core.h"
#include "cp_css_encrypt_info.h"




cp_bool_t get_conf_int_prop(cp_int32_t *dest, cp_css_encrypt_t *app,
	cp_conf_t *conf, const char *context, const char *key, int def)
{
	cp_int32_t							tmp_value = 0;



	tmp_value = cp_conf_getint(conf, context, key, def);
	if (!tmp_value) {
		cp_log_error(app->logger, "get [%s:%s] failed!", context, key);
		return cp_false;
	}
	*dest = tmp_value;
	return cp_true;
}

cp_bool_t get_conf_double_prop(cp_double_t *dest, cp_css_encrypt_t *app,
	cp_conf_t *conf, const char *context, const char *key, int def)
{
	cp_double_t							tmp_value = 0;



	tmp_value = cp_conf_getdouble(conf, context, key, def);
	if (!tmp_value) {
		cp_log_error(app->logger, "get [%s:%s] failed!", context, key);
		return cp_false;
	}
	*dest = tmp_value;
	return cp_true;
}

cp_bool_t get_conf_string_prop(cp_char_t *dest, cp_int32_t len, cp_css_encrypt_t *app,
	cp_conf_t *conf, const char *context, const char *key, const char* def)
{
	cp_char_t							*tmp_value = 0;



	tmp_value = (cp_char_t *)cp_conf_getstring(conf, context, key, def);
	if (!tmp_value) {
		cp_log_error(app->logger, "get [%s:%s] failed!", context, key);
		return cp_false;
	}
	if ((cp_int32_t)cp_strlen(tmp_value) > len) {
		cp_log_error(app->logger, "get [%s:%s] failed! dest buffer length[%d] error.",
			context, key, cp_strlen(tmp_value));
		return cp_false;
	}
	cp_strncpy(dest, tmp_value, cp_strlen(tmp_value));
	return cp_true;
}

cp_bool_t get_conf_xml_int_prop(cp_int32_t *dest, cp_css_encrypt_t *app,
	cp_conf_t *conf, const char *context, const char *key, int def)
{
	cp_int32_t							tmp_value = 0;



	if (!conf || !app) {
		return cp_false;
	}
	tmp_value = cp_conf_xml_getint(conf->conf_xml, context, key, def);
	if (!tmp_value) {
		cp_log_error(app->logger, "get [%s:%s] failed!", context, key);
		return cp_false;
	}
	*dest = tmp_value;
	return cp_true;
}

cp_bool_t get_conf_xml_double_prop(cp_double_t *dest, cp_css_encrypt_t *app,
	cp_conf_t *conf, const char *context, const char *key, int def)
{
	cp_double_t							tmp_value = 0;



	if (!conf || !app) {
		return cp_false;
	}
	tmp_value = cp_conf_xml_getdouble(conf->conf_xml, context, key, def);
	if (!tmp_value) {
		cp_log_error(app->logger, "get [%s:%s] failed!", context, key);
		return cp_false;
	}
	*dest = tmp_value;
	return cp_true;
}

cp_bool_t get_conf_xml_size_prop(cp_int64_t *dest, cp_css_encrypt_t *app,
	cp_conf_t *conf, const char *context, const char *key, int def)
{
	cp_int64_t							tmp_value = 0;



	if (!conf || !app) {
		return cp_false;
	}
	tmp_value = cp_conf_xml_getsize(conf->conf_xml, context, key, def);
	if (!tmp_value) {
		cp_log_error(app->logger, "get [%s:%s] failed!", context, key);
		return cp_false;
	}
	*dest = tmp_value;
	return cp_true;
}

cp_bool_t get_conf_xml_string_prop(cp_char_t *dest, cp_int32_t len, cp_css_encrypt_t *app,
	cp_conf_t *conf, const char *context, const char *key, const char* def)
{
	cp_char_t							*tmp_value = 0;



	if (!conf || !app) {
		return cp_false;
	}
	tmp_value = (cp_char_t*)cp_conf_xml_getstring(conf->conf_xml, context, key, def);
	if (!tmp_value) {
		cp_log_error(app->logger, "get [%s:%s] failed!", context, key);
		return cp_false;
	}
	if ((cp_int32_t)cp_strlen(tmp_value) > len) {
		cp_log_error(app->logger, "get [%s:%s] failed! dest buffer length[%d] error.", 
			context, key, cp_strlen(tmp_value));
		return cp_false;
	}
	cp_strncpy(dest, tmp_value, cp_strlen(tmp_value));
	return cp_true;
}

cp_bool_t init_css_encrypt_info(cp_css_encrypt_t *css_encrypt, cp_css_encrypt_info_t *info)
{
	return cp_true;
}






