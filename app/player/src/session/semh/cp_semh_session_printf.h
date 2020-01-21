/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-11-07

Description:

**************************************************************************/

#ifndef _CP_SEMH_SESSION_PRINTF_INCLUDE_H_
#define _CP_SEMH_SESSION_PRINTF_INCLUDE_H_


#include "cp_semh_session_core.h"



/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: print_session_information
*
* ����˵��: ��ӡsession������Ϣ
*
* ��    ��: cp_semh_session_t * session						[in]����˵��
*
* �� �� ֵ: cp_char_t *
*           0  : �ɹ� 
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2016-11-07 18:42:40
******************************************************************************************************/
cp_char_t *print_session_information(cp_semh_session_t *session);



//�������°�װ�˴�ӡ��Ϣ�ĸ�ʽ
#define	 cp_semh_session_log(level, session, format, ...)					\
	do {																	\
			cp_log_##level((session)->logger, "process %s " #format, (session)->semh_si, ##__VA_ARGS__)	\
	;} while (0)															\


#endif