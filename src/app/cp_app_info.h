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
/* ��Ҫ����ģ�������ע��Ļ�����Ϣ                                       */
/************************************************************************/
#define CP_APP_INFO_FIELDS																											\
		cp_int32_t						type;															/*��ʾģ��������Ϣ*/			\
		cp_char_t						name[CP_APP_DEFAULT_STRING_LENGTH];								/*��ʾģ������*/				\
		cp_int32_t						version;														/*��ʾģ��汾��*/			\
		cp_char_t						description[CP_APP_DEFAULT_STRING_LENGTH];						/*��ʾģ�������*/			\
		cp_void_t						*data;															/*����������Ϣ����*/			\
		cp_char_t						entry_config_path[CP_APP_DEFAULT_CONFIG_FILENAME_LENGTH];		/*����������Ϣ����*/			\




/************************************************************************/
/* ��ʾģ�������Ϣ����ģ����Ϣ����̳и���Ϣ                              */
/************************************************************************/
struct cp_app_info_s
{
	CP_APP_INFO_FIELDS
};


#pragma pack()





#endif