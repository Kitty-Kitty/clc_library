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
* ��Ȩ����: fz & novigo
*
* ��������: audio_func_parse_configure
*
* ����˵��: ���������ļ�
*
* ��    ��: cp_module_t * module						[in]����˵��
* ��    ��: cp_audio_func_configure_t * afc						[in]����˵��
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
cp_int32_t	audio_func_parse_configure(cp_module_t *module, cp_audio_func_configure_t *afc)
{
	cp_int32_t						tmp_value = 0;



	if (!module || !afc) {
		return -1;
	}

	//����convert_flag
	if (!get_module_conf_xml_int_prop(&tmp_value, module, module->conf,
		CP_AUDIO_FUNC_CONF_STRING_AUDIO_CONFIGURE, CP_AUDIO_FUNC_CONF_STRING_CONVERT_FLAG, 0)) {
		return -1;
	}
	afc->convert_flag = tmp_value;

	//����channel_layout
	if (!get_module_conf_xml_int_prop(&tmp_value, module, module->conf,
		CP_AUDIO_FUNC_CONF_STRING_AUDIO_CONFIGURE, CP_AUDIO_FUNC_CONF_STRING_CHANNEL_LAYOUT, 0)) {
		return -2;
	}
	afc->channel_layout = tmp_value;

	//����sample_format
	if (!get_module_conf_xml_int_prop(&tmp_value, module, module->conf,
		CP_AUDIO_FUNC_CONF_STRING_AUDIO_CONFIGURE, CP_AUDIO_FUNC_CONF_STRING_SAMPLE_FORMAT, 0)) {
		return -3;
	}
	afc->sample_format = tmp_value;

	//����sample_rate
	if (!get_module_conf_xml_int_prop(&tmp_value, module, module->conf,
		CP_AUDIO_FUNC_CONF_STRING_AUDIO_CONFIGURE, CP_AUDIO_FUNC_CONF_STRING_SAMPLE_RATE, 0)) {
		return -4;
	}
	afc->sample_rate = tmp_value;
	
	//����buffer_size
	if (!get_module_conf_xml_int_prop(&tmp_value, module, module->conf,
		CP_AUDIO_FUNC_CONF_STRING_AUDIO_CONFIGURE, CP_AUDIO_FUNC_CONF_STRING_BUFFER_SIZE, 0)) {
		return -4;
	}
	afc->buffer_size = tmp_value;

	//����samples
	if (!get_module_conf_xml_int_prop(&tmp_value, module, module->conf,
		CP_AUDIO_FUNC_CONF_STRING_AUDIO_CONFIGURE, CP_AUDIO_FUNC_CONF_STRING_SAMPLES, 0)) {
		return -4;
	}
	afc->samples = tmp_value;

	return 0;
}