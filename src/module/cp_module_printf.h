/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-11-18

Description:

**************************************************************************/

#ifndef _CP_MODULE_PRINTF_INCLUDE_H_
#define _CP_MODULE_PRINTF_INCLUDE_H_



//定义是否采用调试模式的日志格式，调式模式添加了函数的打印
#define	CP_MODULE_PRINTF_DEBUG_FORMAT										1




#if defined(CP_MODULE_PRINTF_DEBUG_FORMAT)

//这里重新包装了打印信息的格式
#define	 cp_module_log(level, module, format, ...)							\
	do {																	\
			cp_log_##level((module)->logger, "module[%s(0x%x)] func[%s:%d] " format, (module)->register_info.name, (module), __FUNCTION__, __LINE__, ##__VA_ARGS__)			\
	;} while (0)															\


//这里重新包装了打印信息的格式
#define	 cp_manager_log(level, manager, format, ...)						\
	do {																	\
			cp_log_##level((manager)->logger, "manager[%s(0x%x)] func[%s:%d] " format, (manager)->register_info.name, (manager), __FUNCTION__, __LINE__, ##__VA_ARGS__)		\
	;} while (0)															\

#else

//这里重新包装了打印信息的格式
#define	 cp_module_log(level, module, format, ...)							\
	do {																	\
			cp_log_##level((module)->logger, "module[%s(0x%x)] " format, (module)->register_info.name, (module), ##__VA_ARGS__)			\
	;} while (0)															\


//这里重新包装了打印信息的格式
#define	 cp_manager_log(level, manager, format, ...)						\
	do {																	\
			cp_log_##level((manager)->logger, "manager[%s(0x%x)] " format, (manager)->register_info.name, (manager), ##__VA_ARGS__)		\
	;} while (0)	

#endif


#endif