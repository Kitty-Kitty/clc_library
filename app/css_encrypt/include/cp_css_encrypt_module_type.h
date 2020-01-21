/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-11-24

Description:

**************************************************************************/

#ifndef _CP_CSS_ENCRYPT_MODULE_TYPE_INCLUDE_H_
#define _CP_CSS_ENCRYPT_MODULE_TYPE_INCLUDE_H_


#include "cp_include.h"


enum cp_css_encrypt_manager_type_enum
{
	cp_css_encrypt_manager_type_dev = CP_MODULE_MANAGER_TYPE_DEV(1),
};



enum cp_css_encrypt_module_type_enum
{
	cp_css_encrypt_module_type_hi3531_dev = CP_MODULE_TYPE_DEV(1),
	cp_css_encrypt_module_type_hi3536_dev = CP_MODULE_TYPE_DEV(2),
};



#endif