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
	cp_int32_t						tmp_value = 0;



	if (!module || !afc) {
		return -1;
	}

	//解析buffer_size
	if (!get_module_conf_xml_int_prop(&tmp_value, module, module->conf,
		CP_VIDEO_FUNC_CONF_STRING_VIDEO_CONFIGURE, CP_VIDEO_FUNC_CONF_STRING_BUFFER_SIZE, 0)) {
		return -4;
	}
	afc->buffer_size = tmp_value;

	//解析each_buffer_length
	if (!get_module_conf_xml_int_prop(&tmp_value, module, module->conf,
		CP_VIDEO_FUNC_CONF_STRING_VIDEO_CONFIGURE, CP_VIDEO_FUNC_CONF_STRING_EACH_BUFFER_LENGTH, 0)) {
		return -4;
	}
	afc->each_buffer_length = tmp_value;


	return 0;
}