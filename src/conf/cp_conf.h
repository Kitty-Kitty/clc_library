/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/

#ifndef	_CP_CONF_INCLUDE_H_
#define _CP_CONF_INCLUDE_H_



#include "cp_core.h"
#include "dictionary.h"
#include "iniparser.h"
#include "cp_conf_string.h"
#include "cp_conf_xml.h"



/************************************************************************/
/*                                                                      */
/************************************************************************/
struct cp_conf_s {
	char					abc;
	cp_char_t				name[CP_APP_DEFAULT_STRING_LENGTH];
	cp_char_t				log_conf[CP_APP_DEFAULT_STRING_LENGTH];
	cp_char_t				ini_conf[CP_APP_DEFAULT_STRING_LENGTH];
	dictionary				*ini;						//ini file
	cp_app_t				*app;						//app information
	cp_log_t				*logger;					//logger
	cp_conf_xml_t			*conf_xml;					//xml configure
};



/************************************************************************/
/*                                                                      */
/************************************************************************/
cp_conf_t * cp_conf_create(cp_app_t *app);
int cp_conf_init(cp_conf_t *conf, cp_app_t *app, char* ini_file);
int cp_conf_destroy(cp_conf_t *conf);



/************************************************************************/
/*                                                                      */
/************************************************************************/
int cp_conf_getint(cp_conf_t *conf, const char *context, const char *key, int def);

double cp_conf_getdouble(cp_conf_t *conf, const char *context, const char *key, double def);

const char *cp_conf_getstring(cp_conf_t *conf, const char *context, const char *key, const char* def);

cp_int32_t cp_conf_setstring(cp_conf_t *conf, const char *context, const char *key, const char *val);

cp_bool_t cp_conf_dump_ini(cp_conf_t *conf, cp_app_t *app);

#endif


