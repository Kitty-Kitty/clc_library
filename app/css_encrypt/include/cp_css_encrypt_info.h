/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/

#ifndef _CP_CSS_ENCRYPT_INFO_INCLUDE_H_
#define _CP_CSS_ENCRYPT_INFO_INCLUDE_H_




#include "cp_css_encrypt_core.h"




//typedef struct cp_css_encrypt_info_s					cp_css_encrypt_info_t;




#pragma pack(1)

/************************************************************************/
/* 前端设备基础信息                                                     */
/************************************************************************/
struct cp_css_encrypt_info_s
{
	CP_APP_INFO_FIELDS
};

#pragma pack()

cp_bool_t init_css_encrypt_info(cp_css_encrypt_t *css_encrypt, cp_css_encrypt_info_t *info);


#endif