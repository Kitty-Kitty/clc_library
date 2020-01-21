/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-12-20

Description:

**************************************************************************/

#ifndef _CP_CSS_ENCRYPT_DEV_MANAGER_CONF_INCLUDE_H_
#define _CP_CSS_ENCRYPT_DEV_MANAGER_CONF_INCLUDE_H_


#include "cp_core.h"
#include "cp_module_core.h"
#include "cp_css_encrypt_dev_manager_conf.h"




//定义配置数量
#define		CP_CSS_ENCRYPT_DEV_TYPE_NAME_SIZE					32			//表示css encrypt 类型名称
#define		CP_CSS_ENCRYPT_DEV_CONFIGURE_STRING_LENGTH			1024		//表示css encrypt 配置字符的长度



typedef struct	cp_css_encrypt_dev_configure_s					cp_css_encrypt_dev_configure_t;



/************************************************************************/
/* hi3531系统相关配置                                                      */
/************************************************************************/
struct cp_css_encrypt_dev_configure_s
{
	cp_char_t								type[CP_CSS_ENCRYPT_DEV_TYPE_NAME_SIZE];							//表示css encrypt 类型名称
	cp_char_t								source_file[CP_CSS_ENCRYPT_DEV_CONFIGURE_STRING_LENGTH];			//表示需要被加密的文件
	cp_char_t								destination_file[CP_CSS_ENCRYPT_DEV_CONFIGURE_STRING_LENGTH];		//表示加密后保存的文件
};



/************************************************************************/
/*解析配置文件                                                           */
/************************************************************************/
cp_int32_t	css_encrypt_dev_manager_parse_configure(const cp_module_manager_t *manager, cp_css_encrypt_dev_configure_t *cedc);

#endif