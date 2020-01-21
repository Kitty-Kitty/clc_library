/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/
#include "cp_include.h"
#include "cp_conf.h"
#include "cp_conf_string.h"





cp_conf_t * cp_conf_create(cp_app_t *app) {
	cp_conf_t		*tmp_conf = CP_NULL;


	if (!app) {
		return CP_NULL;
	}

	tmp_conf = cp_mpalloc(app->mpool, sizeof(cp_conf_t));
	if (!tmp_conf) {
		cp_log_printf("cp_conf_create() error. cp_mpalloc() error.");
		return CP_NULL;
	}

	memset(tmp_conf, 0, sizeof(cp_conf_t));
	return tmp_conf;
}

int cp_conf_init(cp_conf_t *conf, cp_app_t *app, char* ini_file) {
	const char		*tmp_work_dir;
	const char		*tmp_log_conf;
	const char		*tmp_config_files;
	cp_int32_t		ret_int = 0;



	cp_strcpy(conf->ini_conf, ini_file);
	conf->app = app;

	//加载配置文件
	conf->ini = iniparser_load(ini_file);
	if (!conf->ini) {
		cp_log_printf("cp_conf_init() failed! iniparser_load() [%s] failed!", ini_file);
		return -1;
	}

	//获取当前工作目录
	tmp_work_dir = cp_conf_getstring(conf, CP_CONF_STRING_SYSTEM, CP_CONF_STRING_NVG_WORK_DIR, CP_NULL);
	if (!tmp_work_dir) {
		cp_log_printf("cp_conf_init() failed! get log configure file[%s][%s] failed!",
			CP_CONF_STRING_SYSTEM, CP_CONF_STRING_NVG_WORK_DIR);
		return -1;
	}
	else {
		//根据配置文件配置工作目录地址
		if (cp_set_work_dir(tmp_work_dir)) {
			cp_log_printf("cp_conf_init() failed! set work direction[%s] failed!",
				tmp_work_dir);
			return -2;
		}
	}

	//获取日志配置文件地址
	tmp_log_conf = cp_conf_getstring(conf, CP_CONF_STRING_SYSTEM, CP_CONF_STRING_NVG_LOG_CONF, CP_NULL);
	if (!tmp_log_conf) {
		cp_log_printf("cp_conf_init() failed! get log configure file[%s][%s] failed!", 
			CP_CONF_STRING_SYSTEM, CP_CONF_STRING_NVG_LOG_CONF);
		return -1;
	}
	cp_strcpy(conf->log_conf, tmp_log_conf);

	//获取其他xml配置文件列表文件
	tmp_config_files = 
		cp_conf_getstring(conf, CP_CONF_STRING_SYSTEM, CP_CONF_STRING_NVG_ROOT_CONF_XML, CP_NULL);
	if (!tmp_config_files) {
		cp_log_printf("cp_conf_init() failed! get config files[%s][%s] failed!",
			CP_CONF_STRING_SYSTEM, CP_CONF_STRING_NVG_ROOT_CONF_XML);
		return -1;
	}
	//初始化xml配置结构体
	conf->conf_xml = cp_conf_xml_create(app);
	if (!conf->conf_xml) {
		cp_log_printf("cp_conf_init() failed! cp_conf_xml_create() error!");
		return -1;
	}
	//初始化xml配置文件结构
	ret_int = cp_conf_xml_init(conf->conf_xml, app, tmp_config_files);
	if (ret_int) {
		cp_log_printf("cp_conf_init() failed! cp_conf_xml_init() error!");
		return -1;
	}
	conf->conf_xml->app = app;

	return 0;
}

int cp_conf_destroy(cp_conf_t *conf) {
	if (conf && conf->ini) {
		iniparser_freedict(conf->ini);
	}
	return 0;
}

int cp_conf_getint(cp_conf_t *conf, const char *context, const char *key, int def) {
	cp_char_t context_key[CP_APP_DEFAULT_STRING_LENGTH] = "";

	cp_sprintf(context_key, "%s:%s", context, key);

	return iniparser_getint(conf->ini, context_key, def);
}

double cp_conf_getdouble(cp_conf_t *conf, const char *context, const char *key, double def) {
	cp_char_t context_key[CP_APP_DEFAULT_STRING_LENGTH] = "";

	cp_sprintf(context_key, "%s:%s", context, key);

	return iniparser_getdouble(conf->ini, context_key, def);
}

const char *cp_conf_getstring(cp_conf_t *conf, const char *context, const char *key, const char* def) {
	cp_char_t context_key[CP_APP_DEFAULT_STRING_LENGTH] = "";

	cp_sprintf(context_key, "%s:%s", context, key);

	return iniparser_getstring(conf->ini, context_key, def);
}
cp_int32_t cp_conf_setstring(cp_conf_t *conf, const char *context, const char *key, const char *val) {	
	cp_char_t context_key[CP_APP_DEFAULT_STRING_LENGTH] = "";

	cp_sprintf(context_key, "%s:%s", context, key);
	return iniparser_set(conf->ini, context_key, val);
}

cp_bool_t cp_conf_dump_ini(cp_conf_t *conf, cp_app_t *app)
{
	FILE  *in = CP_NULL;

	//"D:\\Development\\SVN\\css_player_fix\\configs\\css_bak.conf"
	if ((in = fopen(conf->ini_conf, "w+")) == NULL) {
		fprintf(stderr, "cp conf dump: cannot open %s\n", conf->ini_conf);
		return cp_false;
	}

	iniparser_dump_ini(conf->ini, in);

	if (in){
		fclose(in);
	}

	return cp_true;
}


