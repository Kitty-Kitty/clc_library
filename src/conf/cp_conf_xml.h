/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-11-10

Description:

**************************************************************************/

#ifndef _CP_CONF_XML_INCLUDE_H_
#define _CP_CONF_XML_INCLUDE_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <libxml/xmlmemory.h>
#include <libxml/parser.h>



#include "cp_core.h"



#define			CP_CONF_XML_MAX_FILES							32		//表示最多支持的xml配置文件数量
//定义1024数值
#define			CP_CONF_XML_SIZE_KB								1024LL
#define			CP_CONF_XML_TIME_SECOND							60LL
#define			CP_CONF_XML_TIME_HOUR							24LL
#define			CP_CONF_XML_TIME_THOUND							1000LL



typedef		struct cp_conf_xml_s					cp_conf_xml_t;




/************************************************************************/
/*                                                                      */
/************************************************************************/
struct cp_conf_xml_s {
	cp_app_t				*app;
	cp_char_t				*path;
	cp_char_t				*type;
	xmlDocPtr				root_doc;
	xmlNodePtr				root_node;
	xmlNodePtr				current_node;
	cp_array_t				config_array;
};



cp_conf_xml_t * cp_conf_xml_create(cp_app_t *app);
int cp_conf_xml_init(cp_conf_xml_t *conf, cp_app_t *app, const char* root_xml_file);
int cp_conf_xml_destroy(cp_conf_xml_t *conf);




int cp_conf_xml_getint(cp_conf_xml_t *conf, const char *context, const char *key, int def);
double cp_conf_xml_getdouble(cp_conf_xml_t *conf, const char *context, const char *key, double def);
const char *cp_conf_xml_getstring(cp_conf_xml_t *conf, const char *context, const char *key, const char* def);
cp_int32_t cp_conf_xml_setstring(cp_conf_xml_t *conf, const char *context, const char *key, const char *val);
cp_int64_t cp_conf_xml_getsize(cp_conf_xml_t *conf, const char *context, const char *key, int def);
cp_int64_t cp_conf_xml_gettime_ns(cp_conf_xml_t *conf, const char *context, const char *key, int def);

//获取指定节点
cp_int32_t cp_conf_xml_get_conf(cp_conf_xml_t *conf, const char *context, const char *key, cp_conf_xml_t *ret_conf);
//获取下一个兄弟节点
cp_int32_t cp_conf_xml_getnext_conf(cp_conf_xml_t *conf, const char *context, cp_conf_xml_t *ret_conf);
//获取子节点
cp_int32_t cp_conf_xml_getchild_conf(cp_conf_xml_t *conf, const char *context, cp_conf_xml_t *ret_conf);
//重置
cp_int32_t cp_conf_xml_reset_conf(cp_conf_xml_t *conf);

#endif