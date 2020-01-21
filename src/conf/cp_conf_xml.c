/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-11-10

Description:

**************************************************************************/
#include "cp_include.h"
#include "cp_conf_xml.h"
#include "cp_conf_xml_string.h"




cp_int64_t parse_time_value_ns(char *data, int len);
cp_int64_t parse_size_value(char *data, int len);

int cp_conf_xml_cycle(cp_conf_xml_t *conf, cp_app_t *app);
int cp_conf_xml_config_files(cp_conf_xml_t *conf, cp_app_t *app, xmlNodePtr config_files);
cp_conf_xml_t *cp_conf_xml_config_file(cp_app_t *app, xmlNodePtr config_file);
int cp_conf_xml_parse_file(cp_conf_xml_t *conf, const char* xml_file);
int cp_conf_xml_free_file(cp_conf_xml_t *conf);
xmlNodePtr cp_conf_xml_get_node(cp_conf_xml_t *conf, const char *key);
xmlNodePtr cp_conf_xml_get_children_node(cp_conf_xml_t *conf, xmlNodePtr parent, const char *key);
xmlNodePtr cp_conf_xml_get_appoint_node(cp_conf_xml_t *conf, const char *context, const char *key);
xmlNodePtr cp_conf_xml_get_appoint_node_from_all(cp_conf_xml_t *root_conf, const char *context, const char *key);
int cp_conf_xml_set_path_type(cp_conf_xml_t *conf, cp_app_t *app, const char *path, const char *type);


/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: cp_conf_xml_cycle
*
* 函数说明: 处理所有的配置子文件信息
*
* 参    数: cp_conf_xml_t * conf						[in]参数说明
* 参    数: cp_app_t * app						[in]参数说明
*
* 返 回 值: int
*           0  : 成功 
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2016-11-10 18:42:40
******************************************************************************************************/
int cp_conf_xml_cycle(cp_conf_xml_t *conf, cp_app_t *app) {
	xmlNodePtr		tmp_node = CP_NULL;


	if (!conf || !conf->root_node) {
		return -1;
	}

	for (tmp_node = conf->root_node->xmlChildrenNode;
		tmp_node; tmp_node = tmp_node->next) {
		if (!xmlStrcmp(tmp_node->name, (const xmlChar *)CP_CONF_XML_STRING_CONFIG_FILES)) {
			return cp_conf_xml_config_files(conf, app, tmp_node);
		}
	}

	return 0;
}


/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: cp_conf_xml_config_files
*
* 函数说明: 处理配置文件列表
*
* 参    数: cp_conf_xml_t * conf						[in]参数说明
* 参    数: cp_app_t * app						[in]参数说明
* 参    数: xmlNodePtr config_files						[in]参数说明
*
* 返 回 值: int
*           0  : 成功 
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2016-11-10 18:42:58
******************************************************************************************************/
int cp_conf_xml_config_files(cp_conf_xml_t *root_conf, cp_app_t *app, xmlNodePtr config_files) {
	xmlNodePtr				tmp_node = CP_NULL;
	cp_conf_xml_t			*tmp_conf = CP_NULL;
	cp_conf_xml_t			*tmp_new_conf = CP_NULL;



	if (!config_files) {
		return -1;
	}

	for (tmp_node = config_files->xmlChildrenNode;
		tmp_node; tmp_node = tmp_node->next) {
		if (!xmlStrcmp(tmp_node->name, (const xmlChar *)CP_CONF_XML_STRING_CONFIG_FILE)) {
			tmp_new_conf = cp_conf_xml_config_file(app, tmp_node);
			if (!tmp_new_conf) {
				cp_log_printf("cp_conf_xml_config_file() filed!");
				break;
			}
			if (cp_array_set_back(&root_conf->config_array, &tmp_new_conf)) {
				cp_log_printf("cp_conf_xml_config_file() filed! file number more than [%d]", 
					cp_array_max_size(&root_conf->config_array));
			}
		}
	}

	return 0;
}


/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: cp_conf_xml_config_file
*
* 函数说明: 解析配置文件
*
* 参    数: cp_app_t * app						[in]参数说明
* 参    数: xmlNodePtr config_file						[in]参数说明
*
* 返 回 值: cp_conf_xml_t *
*           0  : 成功 
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2016-11-11 10:03:39
******************************************************************************************************/
cp_conf_xml_t *cp_conf_xml_config_file(cp_app_t *app, xmlNodePtr config_file) {
	xmlNodePtr				tmp_node = CP_NULL;
	xmlChar					*tmp_path = CP_NULL;
	xmlChar					*tmp_type = CP_NULL;
	cp_conf_xml_t			*tmp_conf = CP_NULL;



	if (!config_file) {
		return CP_NULL;
	}

	//获取path 和 type属性
	tmp_path = xmlGetProp(config_file, (const xmlChar *)CP_CONF_XML_STRING_PATH);
	tmp_type = xmlGetProp(config_file, (const xmlChar *)CP_CONF_XML_STRING_TYPE);
	if (!tmp_path || !tmp_type) {
		cp_log_printf("config file broken. item[type:%s path:%s] property is null!", tmp_type, tmp_path);
		return CP_NULL;
	}
	if (!cp_strcmp(tmp_type, CP_CONF_XML_STRING_XML)) {
		tmp_conf = cp_conf_xml_create(app);
		if (tmp_conf) {
			if (!cp_conf_xml_parse_file(tmp_conf, tmp_path)) {
				cp_conf_xml_set_path_type(tmp_conf, app, tmp_path, tmp_type);
				cp_log_printf("parse config file [type:%s path:%s] success!", tmp_type, tmp_path);
				return tmp_conf;
			} else {
				cp_log_printf("parse config file [type:%s path:%s] error!", tmp_type, tmp_path);
			}
		}
	}

	return CP_NULL;
}


/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: cp_conf_xml_parse_file
*
* 函数说明: 解析xml文件
*
* 参    数: cp_conf_xml_t * conf						[in]参数说明
* 参    数: char * xml_file						[in]参数说明
*
* 返 回 值: int
*           0  : 成功 
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2016-11-11 10:03:52
******************************************************************************************************/
int cp_conf_xml_parse_file(cp_conf_xml_t *conf, const char* xml_file) {
	if (!conf || !xml_file) {
		return -1;
	}

	//解析配置文件
	conf->root_doc = xmlParseFile(xml_file);
	if (CP_NULL == conf->root_doc) {
		cp_log_printf("xmlParseFile[%s] failed!", xml_file);
		return -2;
	}

	conf->root_node = xmlDocGetRootElement(conf->root_doc);
	conf->current_node = conf->root_node;
	if (NULL == conf->root_doc) {
		cp_log_printf("xmlDocGetRootElement[%s] failed!", xml_file);
		xmlFreeDoc(conf->root_doc);
		return -3;
	}

	return 0;
}


/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: cp_conf_xml_free_file
*
* 函数说明: 释放解析器资源
*
* 参    数: cp_conf_xml_t * conf						[in]参数说明
*
* 返 回 值: int
*           0  : 成功 
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2016-11-11 11:20:16
******************************************************************************************************/
int cp_conf_xml_free_file(cp_conf_xml_t *conf) {
	if (!conf) {
		return -1;
	}

	if (conf->root_doc) {
		xmlFreeDoc(conf->root_doc);
	}

	return 0;
}

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: cp_conf_xml_get_node
*
* 函数说明: 从xml文件中查找需要的xml节点
*
* 参    数: cp_conf_xml_t * conf						[in]参数说明
* 参    数: const char * key						[in]参数说明
*
* 返 回 值: xmlNodePtr
*           0  : 成功 
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2016-11-11 11:47:31
******************************************************************************************************/
xmlNodePtr cp_conf_xml_get_node(cp_conf_xml_t *conf, const char *key) {
	if (!conf || !conf->current_node) {
		return CP_NULL;
	}

	return cp_conf_xml_get_children_node(conf, conf->current_node, key);
}


/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: cp_conf_xml_get_children_node
*
* 函数说明: 获取指定节点的子节点子节点内容
*
* 参    数: cp_conf_xml_t * conf						[in]参数说明
* 参    数: xmlNodePtr parent						[in]参数说明
* 参    数: const char * key						[in]参数说明
*
* 返 回 值: xmlNodePtr
*           0  : 成功 
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2016-11-11 11:48:08
******************************************************************************************************/
xmlNodePtr cp_conf_xml_get_children_node(cp_conf_xml_t *conf, xmlNodePtr parent, const char *key)
{
	xmlNodePtr					tmp_children_node = CP_NULL;
	xmlNodePtr					tmp_node = CP_NULL;


	if (!conf || !parent || !key) {
		return CP_NULL;
	}

	for (tmp_node = parent; tmp_node; tmp_node = tmp_node->next) {
		//如果找到，则返回
		if (!xmlStrcmp(tmp_node->name, (const xmlChar *)key)) {
			return tmp_node;
		}
		if (tmp_node->xmlChildrenNode) {
			tmp_children_node = cp_conf_xml_get_children_node(conf, tmp_node->xmlChildrenNode, key);
			if (tmp_children_node) {
				return tmp_children_node;
			}
		}
	}
	
	return CP_NULL;
}


/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: cp_conf_xml_get_appoint_node
*
* 函数说明: 表示获取指定节点内容
*
* 参    数: cp_conf_xml_t * conf						[in]参数说明
* 参    数: const char * context						[in]参数说明
* 参    数: const char * key						[in]参数说明
*
* 返 回 值: xmlNodePtr
*           0  : 成功 
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2016-11-11 13:32:04
******************************************************************************************************/
xmlNodePtr cp_conf_xml_get_appoint_node(cp_conf_xml_t *conf, const char *context, const char *key)
{
	xmlNodePtr						tmp_parent = CP_NULL;



	tmp_parent = cp_conf_xml_get_node(conf, context);
	if (!tmp_parent) {
		return tmp_parent;
	}

	return cp_conf_xml_get_children_node(conf, tmp_parent, key);
}

xmlNodePtr cp_conf_xml_get_appoint_node_from_all(cp_conf_xml_t *root_conf, const char *context, const char *key)
{
	cp_int32_t					i = 0;
	cp_void_t					*tmp_void = CP_NULL;
	xmlNodePtr					tmp_node = CP_NULL;


	tmp_node = cp_conf_xml_get_appoint_node(root_conf, context, key);
	if (tmp_node) {
		return tmp_node;
	}

	for (i = 0; i < (cp_int32_t)cp_array_max_size(&root_conf->config_array); i++) {
		tmp_void = cp_array_get(&root_conf->config_array, i);
		if (tmp_void) {
			tmp_node = cp_conf_xml_get_appoint_node(*((cp_conf_xml_t**)tmp_void), context, key);
			if (tmp_node) {
				return tmp_node;
			}
		}
	}

	return tmp_node;
}

int cp_conf_xml_set_path_type(cp_conf_xml_t *conf, cp_app_t *app, const char *path, const char *type)
{
	if (!conf || !app || !path || !type) {
		return -1;
	}
	conf->path = cp_mpalloc(app->mpool, cp_strlen(path) + 1);
	if (conf->path) {
		cp_memset(conf->path, 0, cp_strlen(path) + 1);
		cp_strncpy(conf->path, path, cp_strlen(path));
	}

	conf->type = cp_mpalloc(app->mpool, cp_strlen(type) + 1);
	if (conf->type) {
		cp_memset(conf->type, 0, cp_strlen(type) + 1);
		cp_strncpy(conf->type, type, cp_strlen(type));
	}
	return 0;
}

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: cp_conf_xml_create
*
* 函数说明: 创建一个xml conf
*
*
* 返 回 值: cp_conf_xml_t *
*           0  : 成功 
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2016-11-11 10:05:07
******************************************************************************************************/
cp_conf_xml_t * cp_conf_xml_create(cp_app_t *app) {
	cp_conf_xml_t		*tmp_conf = CP_NULL;
	cp_conf_xml_t		**tmp_array_conf = CP_NULL;

	if (!app) {
		return CP_NULL;
	}

	//创建cp_conf_xml
	tmp_conf = cp_mpalloc(app->mpool, cp_sizeof(cp_conf_xml_t));
	if (!tmp_conf) {
		cp_log_printf("cp_conf_xml_create() error. cp_mpalloc(cp_conf_xml_t) error.");
		return CP_NULL;
	}
	cp_memset(tmp_conf, 0, sizeof(cp_conf_xml_t));

	//创建子文件配置数组
	tmp_array_conf = cp_mpalloc(app->mpool, cp_sizeof(cp_conf_xml_t*) * CP_CONF_XML_MAX_FILES);
	if (!tmp_array_conf) {
		cp_log_printf("cp_conf_xml_create() error. cp_mpalloc(cp_conf_xml_t*) error.");
		return CP_NULL;
	}
	cp_memset(tmp_array_conf, 0, cp_sizeof(cp_conf_xml_t*) * CP_CONF_XML_MAX_FILES);
	cp_array_init(&tmp_conf->config_array, tmp_array_conf, cp_sizeof(cp_conf_xml_t*), CP_CONF_XML_MAX_FILES);

	tmp_conf->app;

	return tmp_conf;
}

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: cp_conf_xml_init
*
* 函数说明: 初始化xml解析器
*
* 参    数: cp_conf_xml_t * conf						[in]参数说明
* 参    数: cp_app_t * app						[in]参数说明
* 参    数: char * root_xml_file						[in]参数说明
*
* 返 回 值: int
*           0  : 成功 
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2016-11-11 10:04:55
******************************************************************************************************/
int cp_conf_xml_init(cp_conf_xml_t *conf, cp_app_t *app, const char* root_xml_file) {
	if (!conf || !app) {
		return -1;
	}

	//解析配置文件
	if (cp_conf_xml_parse_file(conf, root_xml_file)) {
		return -2;
	}

	return cp_conf_xml_cycle(conf, app);
}

int cp_conf_xml_destroy(cp_conf_xml_t *conf)
{
	cp_int32_t					i = 0;
	cp_void_t					*tmp_void = CP_NULL;


	for (i = 0; i < (cp_int32_t)cp_array_max_size(&conf->config_array); i++) {
		tmp_void = cp_array_get(&conf->config_array, i);
		if (tmp_void) {
			cp_conf_xml_free_file((cp_conf_xml_t*)tmp_void);
			cp_mpfree(conf->app->mpool, tmp_void);
			cp_array_set(&conf->config_array, CP_NULL, i);
		}
	}

	return 0;
}




int cp_conf_xml_getint(cp_conf_xml_t *conf, const char *context, const char *key, int def) {
	xmlNodePtr						tmp_node = CP_NULL;
	xmlChar							*tmp_value = CP_NULL;


	if (!conf || !context || !key) {
		return def;
	}

	tmp_node = cp_conf_xml_get_appoint_node_from_all(conf, context, key);
	if (!tmp_node) {
		return def;
	}
	if (xmlIsBlankNode(tmp_node)) {
		return def;
	}
	tmp_value = xmlNodeListGetString(conf->root_doc, tmp_node->xmlChildrenNode, 1);
	if (tmp_value) {
		return cp_atoi(tmp_value);
	}
	return def;
}

double cp_conf_xml_getdouble(cp_conf_xml_t *conf, const char *context, const char *key, double def) {
	xmlNodePtr						tmp_node = CP_NULL;
	xmlChar							*tmp_value = CP_NULL;


	if (!conf || !context || !key) {
		return def;
	}

	tmp_node = cp_conf_xml_get_appoint_node_from_all(conf, context, key);
	if (!tmp_node) {
		return def;
	}
	if (xmlIsBlankNode(tmp_node)) {
		return def;
	}
	tmp_value = xmlNodeListGetString(conf->root_doc, tmp_node->xmlChildrenNode, 1);
	if (tmp_value) {
		return cp_atof(tmp_value);
	}
	return def;
}

const char *cp_conf_xml_getstring(cp_conf_xml_t *conf, const char *context, const char *key, const char* def) {
	xmlNodePtr						tmp_node = CP_NULL;
	xmlChar							*tmp_value = CP_NULL;


	if (!conf || !context || !key) {
		return def;
	}

	tmp_node = cp_conf_xml_get_appoint_node_from_all(conf, context, key);
	if (!tmp_node) {
		return def;
	}
	if (xmlIsBlankNode(tmp_node)) {
		return def;
	}
	tmp_value = xmlNodeListGetString(conf->root_doc, tmp_node->xmlChildrenNode, 1);
	if (tmp_value) {
		return tmp_value;
	}
	return def;
}

cp_int32_t cp_conf_xml_setstring(cp_conf_xml_t *conf, const char *context, const char *key, const char *val) {
	xmlNodePtr						tmp_node = CP_NULL;
	xmlChar							*tmp_value = CP_NULL;


	if (!conf || !context || !key) {
		return -1;
	}

	tmp_node = cp_conf_xml_get_appoint_node_from_all(conf, context, key);
	if (!tmp_node) {
		return -2;
	}
	xmlNodeSetContent(tmp_node, val);
	return 0;
}

cp_int64_t cp_conf_xml_getsize(cp_conf_xml_t *conf, const char *context, const char *key, int def)
{
	cp_int64_t				tmp_ret_int = 0;
	char					*tmp_str = NULL;


	tmp_str = (char*)cp_conf_xml_getstring(conf, context, key, NULL);
	if (!tmp_str) {
		return def;
	}

	tmp_ret_int = parse_size_value(tmp_str, cp_strlen(tmp_str));
	if (tmp_ret_int < 0) {
		return def;
	}

	return tmp_ret_int;
}

cp_int64_t parse_size_value(char *data, int len)
{
	char					*beging = NULL;
	char					*pos = NULL;
	char					*end = NULL;
	cp_int64_t				tmp_ret_int = -1;
	char					tmp_number[CP_APP_DEFAULT_LENGTH] = { 0, };
	char					tmp_flag[CP_APP_DEFAULT_LENGTH] = { 0, };


	if (!data || !len) {
		return -1;
	}
	
	beging = data;
	pos = beging;
	end = beging + len;

	for (beging = data; pos < end; pos++) {
		if ('0' > *pos || '9' < *pos) {
			if (end - pos <= 0 || pos - beging <= 0) {
				return -2;
			}
			cp_strncpy(tmp_number, beging, pos - beging);
			cp_strncpy(tmp_flag, pos, end - pos);

			if (!cp_strcmp(tmp_flag, CP_CONF_XML_STRING_SIZE_B)) {
				tmp_ret_int = cp_atoi(tmp_number);
			}
			else if (!cp_strcmp(tmp_flag, CP_CONF_XML_STRING_SIZE_KB)) {
				tmp_ret_int = cp_atoi(tmp_number) * CP_CONF_XML_SIZE_KB;
			}
			else if (!cp_strcmp(tmp_flag, CP_CONF_XML_STRING_SIZE_MB)) {
				tmp_ret_int = cp_atoi(tmp_number) * CP_CONF_XML_SIZE_KB * CP_CONF_XML_SIZE_KB;
			}
			else if (!cp_strcmp(tmp_flag, CP_CONF_XML_STRING_SIZE_GB)) {
				tmp_ret_int = cp_atoi(tmp_number) * CP_CONF_XML_SIZE_KB * CP_CONF_XML_SIZE_KB * CP_CONF_XML_SIZE_KB;
			}
			else {
				tmp_ret_int = -1;
			}
			break;
		}
	}

	return tmp_ret_int;
}

cp_int64_t parse_time_value_ns(char *data, int len)
{
	char					*beging = NULL;
	char					*pos = NULL;
	char					*end = NULL;
	cp_int64_t				tmp_ret_int = -1;
	char					tmp_number[CP_APP_DEFAULT_LENGTH] = { 0, };
	char					tmp_flag[CP_APP_DEFAULT_LENGTH] = { 0, };


	if (!data || !len) {
		return -1;
	}

	beging = data;
	pos = beging;
	end = beging + len;

	for (beging = data; pos < end; pos++) {
		if ('0' > *pos || '9' < *pos) {
			if (end - pos <= 0 || pos - beging <= 0) {
				return -2;
			}
			cp_strncpy(tmp_number, beging, pos - beging);
			cp_strncpy(tmp_flag, pos, end - pos);

			if (!cp_strcmp(tmp_flag, CP_CONF_XML_STRING_TIME_NS)) {
				tmp_ret_int = cp_atoi(tmp_number);
			}
			else if (!cp_strcmp(tmp_flag, CP_CONF_XML_STRING_TIME_US)) {
				tmp_ret_int = cp_atoi(tmp_number) * CP_CONF_XML_TIME_THOUND;
			}
			else if (!cp_strcmp(tmp_flag, CP_CONF_XML_STRING_TIME_MS)) {
				tmp_ret_int = cp_atoi(tmp_number) * 
					CP_CONF_XML_TIME_THOUND * CP_CONF_XML_TIME_THOUND;
			}
			else if (!cp_strcmp(tmp_flag, CP_CONF_XML_STRING_TIME_S)) {
				tmp_ret_int = cp_atoi(tmp_number) * 
					CP_CONF_XML_TIME_THOUND * CP_CONF_XML_TIME_THOUND * 
					CP_CONF_XML_TIME_THOUND;
			}
			else if (!cp_strcmp(tmp_flag, CP_CONF_XML_STRING_TIME_M)) {
				tmp_ret_int = cp_atoi(tmp_number) * CP_CONF_XML_TIME_SECOND * 
					CP_CONF_XML_TIME_THOUND * CP_CONF_XML_TIME_THOUND *
					CP_CONF_XML_TIME_THOUND;
			}
			else if (!cp_strcmp(tmp_flag, CP_CONF_XML_STRING_TIME_H)) {
				tmp_ret_int = cp_atoi(tmp_number) * 
					CP_CONF_XML_TIME_SECOND * CP_CONF_XML_TIME_SECOND *
					CP_CONF_XML_TIME_THOUND * CP_CONF_XML_TIME_THOUND *
					CP_CONF_XML_TIME_THOUND;
			}
			else if (!cp_strcmp(tmp_flag, CP_CONF_XML_STRING_TIME_D)) {
				tmp_ret_int = cp_atoi(tmp_number) * CP_CONF_XML_TIME_HOUR *
					CP_CONF_XML_TIME_SECOND * CP_CONF_XML_TIME_SECOND *
					CP_CONF_XML_TIME_THOUND * CP_CONF_XML_TIME_THOUND *
					CP_CONF_XML_TIME_THOUND;
			}
			else {
				tmp_ret_int = -1;
			}
			break;
		}
	}

	return tmp_ret_int;
}

cp_int64_t cp_conf_xml_gettime_ns(cp_conf_xml_t *conf, const char *context, const char *key, int def)
{
	cp_int64_t				tmp_ret_int = 0;
	char					*tmp_str = NULL;



	tmp_str = (char*)cp_conf_xml_getstring(conf, context, key, NULL);
	if (!tmp_str) {
		return def;
	}

	tmp_ret_int = parse_time_value_ns(tmp_str, cp_strlen(tmp_str));
	if (tmp_ret_int < 0) {
		return def;
	}

	return tmp_ret_int;
}

/*******************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: cp_conf_xml_get_conf
*
* 函数全名: cp_conf_xml_get_conf
*
* 函数访问: public 
*
* 函数说明: 获取指定节点
*
* 参    数: cp_conf_xml_t * conf						[in]需要查询的conf
* 参    数: const char * context						[in]查询的父节点名称
* 参    数: const char * key							[in]参数说明
* 参    数: cp_conf_xml_t * ret_conf					[out]查询返回的节点名称
*
* 返 回 值: cp_int32_t
*           0  : 成功
*         非0  : 失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2017-7-27 15:43:39
********************************************************************************/
cp_int32_t cp_conf_xml_get_conf(cp_conf_xml_t *conf, const char *context, const char *key, cp_conf_xml_t *ret_conf)
{
	xmlNodePtr						tmp_node = CP_NULL;



	if (!conf || !conf->current_node || !context || !ret_conf) {
		return -1;
	}

	tmp_node = cp_conf_xml_get_appoint_node_from_all(conf, context, key);
	if (!tmp_node) {
		return -2;
	}

	*ret_conf = *conf;
	ret_conf->current_node = tmp_node;
	return 0;
}

/*******************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: cp_conf_xml_getnext_conf
*
* 函数全名: cp_conf_xml_getnext_conf
*
* 函数访问: public 
*
* 函数说明: 获取下一个兄弟节点
*
* 参    数: cp_conf_xml_t * conf						[in]需要查询的conf
* 参    数: const char * context						[in]查询的节点名称
* 参    数: cp_conf_xml_t * ret_conf					[out]查询返回的节点名称
*
* 返 回 值: cp_int32_t
*           0  : 成功
*         非0  : 失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2017-7-27 15:25:16
********************************************************************************/
cp_int32_t cp_conf_xml_getnext_conf(cp_conf_xml_t *conf, const char *context, cp_conf_xml_t *ret_conf)
{
	xmlNodePtr				tmp_node = CP_NULL;


	if (!conf || !conf->current_node || !context || !ret_conf) {
		return -1;
	}

	//从下一个节点开始查询
	tmp_node = cp_conf_xml_get_children_node(conf, conf->current_node->next, context);
	if (!tmp_node) {
		return -2;
	}

	*ret_conf = *conf;
	ret_conf->current_node = tmp_node;
	return 0;
}

/*******************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: cp_conf_xml_getchild_conf
*
* 函数全名: cp_conf_xml_getchild_conf
*
* 函数访问: public 
*
* 函数说明: 获取子节点
*
* 参    数: cp_conf_xml_t * conf						[in]需要查询的conf
* 参    数: const char * context						[in]查询的节点名称
* 参    数: cp_conf_xml_t * ret_conf					[out]查询返回的节点名称
*
* 返 回 值: cp_int32_t
*           0  : 成功
*         非0  : 失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2017-7-27 15:45:31
********************************************************************************/
cp_int32_t cp_conf_xml_getchild_conf(cp_conf_xml_t *conf, const char *context, cp_conf_xml_t *ret_conf)
{
	xmlNodePtr				tmp_node = CP_NULL;


	if (!conf || !conf->current_node || !context || !ret_conf) {
		return -1;
	}

	//从下一个节点开始查询
	tmp_node = cp_conf_xml_get_children_node(conf, conf->current_node->xmlChildrenNode, context);
	if (!tmp_node) {
		return -2;
	}

	*ret_conf = *conf;
	ret_conf->current_node = tmp_node;
	return 0;
}

//重置
cp_int32_t cp_conf_xml_reset_conf(cp_conf_xml_t *conf)
{
	if (!conf) {
		return -1;
	}

	conf->current_node = conf->root_node;
	return 0;
}