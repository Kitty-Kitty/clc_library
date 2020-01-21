/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-12-26

Description:

**************************************************************************/

#ifndef _CP_ECAM_FUNC_CONF_INCLUDE_H_
#define _CP_ECAM_FUNC_CONF_INCLUDE_H_




#include "css_core.h"
#include "cp_module_core.h"



typedef		struct cp_ecam_rtp_config_s					cp_ecam_rtp_config_t;
typedef		struct cp_ecam_func_conf_s						cp_ecam_func_conf_t;




/************************************************************************/
/* 表示rtp的配置                                                         */
/************************************************************************/
struct cp_ecam_rtp_config_s
{
	cp_int32_t		ts;														//表示起始时间
	cp_int32_t		ssrc;													//表示rtp ssrc标志值
	cp_int32_t		port;													//表示端口号
	cp_char_t		ip[CP_APP_DEFAULT_STRING_LENGTH];						//表示ip地址

};


/************************************************************************/
/* ecam func conf配置信息                                                 */
/************************************************************************/
struct cp_ecam_func_conf_s
{
	cp_ecam_rtp_config_t					rtp_conf;					//表示rtp的配置信息
};


//初始化配置信息
cp_int32_t	init_ecam_func_conf(cp_module_t *module, cp_ecam_func_conf_t *ecam_conf);

//设置配置信息
cp_int32_t	set_ecam_func_conf(cp_module_t *module, cp_ecam_func_conf_t *ecam_conf);

#endif