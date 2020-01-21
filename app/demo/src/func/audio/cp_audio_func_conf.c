/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-12-20

Description:

**************************************************************************/
#include "cp_log.h"
#include "cp_conf.h"
#include "cp_audio_func_conf.h"



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

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: audio_func_parse_configure
*
* 函数说明: 解析配置文件
*
* 参    数: cp_module_t * module						[in]参数说明
* 参    数: cp_audio_func_configure_t * afc						[in]参数说明
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
cp_int32_t	audio_func_parse_configure(cp_module_t *module, cp_audio_func_configure_t *afc)
{
	cp_int32_t						tmp_value = 0;



	if (!module || !afc) {
		return -1;
	}

	//解析convert_flag
	if (!get_module_conf_xml_int_prop(&tmp_value, module, module->conf,
		CP_AUDIO_FUNC_CONF_STRING_AUDIO_CONFIGURE, CP_AUDIO_FUNC_CONF_STRING_CONVERT_FLAG, 0)) {
		return -1;
	}
	afc->convert_flag = tmp_value;

	//解析channel_layout
	if (!get_module_conf_xml_int_prop(&tmp_value, module, module->conf,
		CP_AUDIO_FUNC_CONF_STRING_AUDIO_CONFIGURE, CP_AUDIO_FUNC_CONF_STRING_CHANNEL_LAYOUT, 0)) {
		return -2;
	}
	afc->channel_layout = tmp_value;

	//解析sample_format
	if (!get_module_conf_xml_int_prop(&tmp_value, module, module->conf,
		CP_AUDIO_FUNC_CONF_STRING_AUDIO_CONFIGURE, CP_AUDIO_FUNC_CONF_STRING_SAMPLE_FORMAT, 0)) {
		return -3;
	}
	afc->sample_format = tmp_value;

	//解析sample_rate
	if (!get_module_conf_xml_int_prop(&tmp_value, module, module->conf,
		CP_AUDIO_FUNC_CONF_STRING_AUDIO_CONFIGURE, CP_AUDIO_FUNC_CONF_STRING_SAMPLE_RATE, 0)) {
		return -4;
	}
	afc->sample_rate = tmp_value;
	
	//解析buffer_size
	if (!get_module_conf_xml_int_prop(&tmp_value, module, module->conf,
		CP_AUDIO_FUNC_CONF_STRING_AUDIO_CONFIGURE, CP_AUDIO_FUNC_CONF_STRING_BUFFER_SIZE, 0)) {
		return -4;
	}
	afc->buffer_size = tmp_value;

	//解析samples
	if (!get_module_conf_xml_int_prop(&tmp_value, module, module->conf,
		CP_AUDIO_FUNC_CONF_STRING_AUDIO_CONFIGURE, CP_AUDIO_FUNC_CONF_STRING_SAMPLES, 0)) {
		return -4;
	}
	afc->samples = tmp_value;

	return 0;
}