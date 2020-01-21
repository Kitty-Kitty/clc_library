/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-12-13

Description:

**************************************************************************/

#ifndef _CP_SEMH_HOOK_PRINTF_INCLUDE_H_
#define _CP_SEMH_HOOK_PRINTF_INCLUDE_H_


//这里重新包装了打印信息的格式
#define	 cp_semh_hook_log(level, hook, session, format, ...)					\
	do {																	\
			cp_log_##level((hook)->logger, "process %s hook[%s] " #format, (session)->semh_si, (hook)->register_info.name, ##__VA_ARGS__)	\
	;} while (0)															\


#endif