/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-12-20

Description:

**************************************************************************/

#ifndef _CP_PTP_FUNC_CONF_INCLUDE_H_
#define _CP_PTP_FUNC_CONF_INCLUDE_H_


#include "cp_core.h"
#include "cp_module_core.h"
#include "cp_ptp_func_conf_string.h"



#define		CP_PTP_FUNC_IP_ADDRESS_LENGTH				16
#define		CP_PTP_DEFAULT_BUFFER_LENGTH				256


typedef struct cp_ptp_func_configure_s					cp_ptp_func_configure_t;



#pragma pack(1)

/************************************************************************/
/* ��Ƶ�����������                                                      */
/************************************************************************/
struct cp_ptp_func_configure_s
{
	cp_char_t						address[CP_PTP_FUNC_IP_ADDRESS_LENGTH];			//��ʾptp�鲥��ַ
	cp_char_t						debug_path[CP_PTP_DEFAULT_BUFFER_LENGTH];		//��ʾptp ������Ϣ����λ��
	cp_int32_t						port;											//��ʾptp�鲥�˿�
	cp_bool_t						is_debug;										//��ʾ�Ƿ����
	cp_bool_t						is_use;
};

#pragma pack()


/************************************************************************/
/*���������ļ�                                                           */
/************************************************************************/
cp_int32_t	ptp_func_parse_configure(cp_module_t *module, cp_ptp_func_configure_t *fc);


#endif