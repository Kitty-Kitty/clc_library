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
* 版权所有: fz & novigo
*
* 函数名称: print_session_information
*
* 函数说明: 打印session部分信息
*
* 参    数: cp_semh_session_t * session						[in]参数说明
*
* 返 回 值: cp_char_t *
*           0  : 成功 
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2016-11-07 18:42:40
******************************************************************************************************/
cp_char_t *print_session_information(cp_semh_session_t *session);



//这里重新包装了打印信息的格式
#define	 cp_semh_session_log(level, session, format, ...)					\
	do {																	\
			cp_log_##level((session)->logger, "process %s " #format, (session)->semh_si, ##__VA_ARGS__)	\
	;} while (0)															\


#endif