/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-12-20

Description:

**************************************************************************/
#include "cp_log.h"
#include "cp_conf.h"
#include "cp_video_func_conf.h"




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

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: video_func_parse_configure
*
* 函数说明: 解析配置文件
*
* 参    数: cp_module_t * module						[in]参数说明
* 参    数: cp_video_func_configure_t * afc						[in]参数说明
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
cp_int32_t	video_func_parse_configure(cp_module_t *module, cp_video_func_configure_t *afc)
{
	cp_int32_t						tmp_ret_int = 0;
	cp_int32_t						tmp_value = 0;



	if (!module || !afc) {
		return -1;
	}

	//解析buffer_size
	if (!get_module_conf_xml_int_prop(&tmp_value, module, module->conf->conf_xml,
		CP_VIDEO_FUNC_CONF_STRING_VIDEO_CONFIGURE, CP_VIDEO_FUNC_CONF_STRING_BUFFER_SIZE, 0)) {
		return -4;
	}
	afc->buffer_size = tmp_value;

	//解析each_buffer_length
	if (!get_module_conf_xml_int_prop(&tmp_value, module, module->conf->conf_xml,
		CP_VIDEO_FUNC_CONF_STRING_VIDEO_CONFIGURE, CP_VIDEO_FUNC_CONF_STRING_EACH_BUFFER_LENGTH, 0)) {
		return -4;
	}
	afc->each_buffer_length = tmp_value;

	//解析video sources部分内容
	tmp_ret_int = video_func_parse_video_sources(module, afc);
	if (tmp_ret_int) {
		cp_module_log(error, module, "video_func_parse_video_sources() error.");
		return tmp_ret_int;
	}


	return 0;
}

/*******************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: video_func_parse_video_sources
*
* 函数全名: video_func_parse_video_sources
*
* 函数访问: public
*
* 函数说明: 函数说明
*
* 参    数: const cp_module_t *module						[in/out]参数说明
* 参    数: cp_video_func_configure_t *afc							[in/out]参数说明
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
cp_int32_t	video_func_parse_video_sources(const cp_module_t *module, cp_video_func_configure_t *afc)
{
	cp_int32_t									tmp_value = 0;
	cp_int32_t									tmp_ret_int = 0;
	cp_int32_t									i = 0;
	cp_conf_xml_t								tmp_conf_xml = { 0, };



	if (!module || !afc) {
		return -1;
	}

	tmp_ret_int = cp_conf_xml_get_conf(module->conf->conf_xml,
		CP_VIDEO_FUNC_CONF_STRING_VIDEO_SOURCES,
		CP_VIDEO_FUNC_CONF_STRING_VIDEO_SOURCE,
		&tmp_conf_xml);
	if (tmp_ret_int) {
		cp_manager_log(error, module, "get [%s:%s] warning!",
			CP_VIDEO_FUNC_CONF_STRING_VIDEO_SOURCES,
			CP_VIDEO_FUNC_CONF_STRING_VIDEO_SOURCE);
		return tmp_ret_int;
	}

	for (i = 0; !tmp_ret_int; tmp_ret_int = cp_conf_xml_getnext_conf(&tmp_conf_xml,
		CP_VIDEO_FUNC_CONF_STRING_VIDEO_SOURCE, &tmp_conf_xml), i++) {

		afc->video_sources[i].is_used = cp_false;

		//解析url
		if (!get_module_conf_xml_string_prop(afc->video_sources[i].url,
			cp_sizeof(afc->video_sources[i].url), module, &tmp_conf_xml,
			CP_VIDEO_FUNC_CONF_STRING_VIDEO_SOURCE, CP_VIDEO_FUNC_CONF_STRING_URL, CP_NULL)) {
			continue;
		}

		afc->video_sources[i].is_used = cp_true;
	}

	return 0;
}
