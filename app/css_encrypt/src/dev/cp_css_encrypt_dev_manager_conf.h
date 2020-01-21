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




//������������
#define		CP_CSS_ENCRYPT_DEV_TYPE_NAME_SIZE					32			//��ʾcss encrypt ��������
#define		CP_CSS_ENCRYPT_DEV_CONFIGURE_STRING_LENGTH			1024		//��ʾcss encrypt �����ַ��ĳ���



typedef struct	cp_css_encrypt_dev_configure_s					cp_css_encrypt_dev_configure_t;



/************************************************************************/
/* hi3531ϵͳ�������                                                      */
/************************************************************************/
struct cp_css_encrypt_dev_configure_s
{
	cp_char_t								type[CP_CSS_ENCRYPT_DEV_TYPE_NAME_SIZE];							//��ʾcss encrypt ��������
	cp_char_t								source_file[CP_CSS_ENCRYPT_DEV_CONFIGURE_STRING_LENGTH];			//��ʾ��Ҫ�����ܵ��ļ�
	cp_char_t								destination_file[CP_CSS_ENCRYPT_DEV_CONFIGURE_STRING_LENGTH];		//��ʾ���ܺ󱣴���ļ�
};



/************************************************************************/
/*���������ļ�                                                           */
/************************************************************************/
cp_int32_t	css_encrypt_dev_manager_parse_configure(const cp_module_manager_t *manager, cp_css_encrypt_dev_configure_t *cedc);

#endif