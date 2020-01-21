/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/

#ifndef _CP_APP_INFO_INCLUDE_H_
#define _CP_APP_INFO_INCLUDE_H_



#include "cp_app_core.h"





//typedef	struct cp_app_info_s			cp_app_info_t;


#pragma pack(1)


/************************************************************************/
/* 主要描述模块管理器注册的基础信息                                       */
/************************************************************************/
#define CP_APP_INFO_FIELDS																											\
		cp_int32_t						type;															/*表示模块类型信息*/			\
		cp_char_t						name[CP_APP_DEFAULT_STRING_LENGTH];								/*表示模块名称*/				\
		cp_int32_t						version;														/*表示模块版本号*/			\
		cp_char_t						description[CP_APP_DEFAULT_STRING_LENGTH];						/*表示模块的描述*/			\
		cp_void_t						*data;															/*保存其他信息内容*/			\
		cp_char_t						entry_config_path[CP_APP_DEFAULT_CONFIG_FILENAME_LENGTH];		/*保存其他信息内容*/			\




/************************************************************************/
/* 表示模块基础信息，子模块信息必须继承该信息                              */
/************************************************************************/
struct cp_app_info_s
{
	CP_APP_INFO_FIELDS
};


#pragma pack()





#endif