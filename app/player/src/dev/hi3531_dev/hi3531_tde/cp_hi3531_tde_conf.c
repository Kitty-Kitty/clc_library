/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-12-20

Description:

**************************************************************************/
#include "cp_log.h"
#include "cp_conf.h"
#include "cp_hi3531_tde_conf.h"



cp_inline cp_static cp_bool_t get_module_conf_xml_int_prop(cp_int32_t *dest, cp_module_t *module,
	cp_conf_t *conf, const char *context, const char *key, int def)
{
	cp_int32_t							tmp_value = 0;



	if (!conf || !module) {
		return cp_false;
	}
	tmp_value = cp_conf_xml_getint(conf->conf_xml, context, key, def);
	if (tmp_value < 0) {
		cp_module_log(notice, module, "get [%s:%s] warning!", context, key);
		//return cp_false;
	}
	*dest = tmp_value;
	return cp_true;
}

/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: hi3531_tde_parse_configure
*
* ����˵��: ���������ļ�
*
* ��    ��: cp_module_t * module						[in]����˵��
* ��    ��: cp_hi3531_tde_configure_t * hacc						[in]����˵��
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
cp_int32_t	hi3531_tde_parse_configure(cp_module_t *module, cp_hi3531_tde_configure_t *hacc)
{

	return 0;
}
