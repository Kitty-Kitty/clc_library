/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-12-26

Description:

**************************************************************************/

#ifndef _CP_IPC_FUNC_CONF_INCLUDE_H_
#define _CP_IPC_FUNC_CONF_INCLUDE_H_




#include "css_core.h"
#include "cp_module_core.h"



typedef		struct cp_ipc_rtp_config_s					cp_ipc_rtp_config_t;
typedef		struct cp_ipc_func_conf_s						cp_ipc_func_conf_t;




/************************************************************************/
/* ��ʾrtp������                                                         */
/************************************************************************/
struct cp_ipc_rtp_config_s
{
	cp_int32_t		ts;														//��ʾ��ʼʱ��
	cp_int32_t		ssrc;													//��ʾrtp ssrc��־ֵ
	cp_int32_t		port;													//��ʾ�˿ں�
	cp_char_t		ip[CP_APP_DEFAULT_STRING_LENGTH];						//��ʾip��ַ

};


/************************************************************************/
/* ipc func conf������Ϣ                                                 */
/************************************************************************/
struct cp_ipc_func_conf_s
{
	cp_ipc_rtp_config_t					rtp_conf;					//��ʾrtp��������Ϣ
};


//��ʼ��������Ϣ
cp_int32_t	init_ipc_func_conf(cp_module_t *module, cp_ipc_func_conf_t *ipc_conf);

//����������Ϣ
cp_int32_t	set_ipc_func_conf(cp_module_t *module, cp_ipc_func_conf_t *ipc_conf);

#endif