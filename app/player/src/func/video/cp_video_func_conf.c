/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-12-20

Description:

**************************************************************************/
#include "cp_log.h"
#include "cp_conf.h"
#include "cp_video_func_conf.h"



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
* ��������: video_func_parse_configure
*
* ����˵��: ���������ļ�
*
* ��    ��: cp_module_t * module						[in]����˵��
* ��    ��: cp_video_func_configure_t * afc						[in]����˵��
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
cp_int32_t	video_func_parse_configure(cp_module_t *module, cp_video_func_configure_t *afc)
{
	cp_int32_t						tmp_value = 0;



	if (!module || !afc) {
		return -1;
	}

	//����buffer_size
	if (!get_module_conf_xml_int_prop(&tmp_value, module, module->conf,
		CP_VIDEO_FUNC_CONF_STRING_VIDEO_CONFIGURE, CP_VIDEO_FUNC_CONF_STRING_BUFFER_SIZE, 0)) {
		return -4;
	}
	afc->buffer_size = tmp_value;

	//����each_buffer_length
	if (!get_module_conf_xml_int_prop(&tmp_value, module, module->conf,
		CP_VIDEO_FUNC_CONF_STRING_VIDEO_CONFIGURE, CP_VIDEO_FUNC_CONF_STRING_EACH_BUFFER_LENGTH, 0)) {
		return -4;
	}
	afc->each_buffer_length = tmp_value;


	return 0;
}