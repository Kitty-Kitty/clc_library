/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/

#ifndef	_CP_CSS_ENCRYPT_DEV_MANAGER_INCLUDE_H_
#define _CP_CSS_ENCRYPT_DEV_MANAGER_INCLUDE_H_



#include "cp_css_encrypt_dev_core.h"



typedef struct cp_css_encrypt_dev_manager_s					cp_css_encrypt_dev_manager_t;



#pragma pack(1)

struct cp_css_encrypt_dev_manager_s
{
	CP_DEV_MANAGER_FIELDS

	cp_css_encrypt_dev_configure_t				cedc;				//管理器配置内容
	cp_dev_t									*encrypt_dev;		//加密设置
};

#pragma pack()




cp_css_encrypt_dev_manager_t* create_css_encrypt_dev_manager(cp_module_manager_register_t *register_info, cp_app_t *app, cp_css_encrypt_dev_manager_info_t *info);
cp_int32_t destroy_css_encrypt_dev_manager(cp_app_t *app, cp_css_encrypt_dev_manager_t* manager);

#endif


