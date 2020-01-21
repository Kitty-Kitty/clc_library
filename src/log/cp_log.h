/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/

#ifndef	_CP_LOG_INCLUDE_H_
#define _CP_LOG_INCLUDE_H_






#include "cp_core.h"
#include "zlog.h"




//#define CP_LOG_USED_FILE						1
//#define CP_LOG_USED_NULL						1



/************************************************************************/
/* 表示日志级别                                                          */
/************************************************************************/
enum cp_log_level_enum
{
	debug,
	info,
	notice,
	warn,
	error,
	fatal
};


/************************************************************************/
/*                                                                      */
/************************************************************************/
struct cp_log_s {
	void *data;															//日志信息洗信息
	int(*log_init)(cp_log_t *logger, int argc, char ** argv);
	int(*log_start)(cp_log_t *logger, int argc, char ** argv);
	int(*log_stop)(cp_log_t *logger, int argc, char ** argv);
// 	void(*log_fatal)(cp_log_t *logger, char *fmt, ...);
// 	void(*log_error)(cp_log_t *logger, char *fmt, ...);
// 	void(*log_warn)(cp_log_t *logger, char *fmt, ...);
// 	void(*log_notice)(cp_log_t *logger, char *fmt, ...);
// 	void(*log_info)(cp_log_t *logger, char *fmt, ...);
// 	void(*log_debug)(cp_log_t *logger, char *fmt, ...);
};


cp_log_t* cp_log_create();
int cp_log_init(cp_log_t *logger, cp_conf_t *conf);
int cp_log_destroy(cp_log_t *logger);


/************************************************************************/
/*                                                                      */
/************************************************************************/
#include "zlog/cp_zlog.h"

#define CP_LOAD_LOG_MODUE(logger) do{					\
	logger->data = NULL;								\
	logger->log_init = cp_zlog_init;					\
	logger->log_start = cp_zlog_start;					\
	logger->log_stop = cp_zlog_stop;					\
	} while (0)											\


#define cp_log_printf(fmt, ...)		do {printf(fmt "\r\n", ##__VA_ARGS__);} while (0)

#ifdef CP_LOG_USED_FILE

#define cp_log_fatal(logger, ...)	do {if(logger){zlog_fatal(((zlog_category_t *)(logger->data)), ##__VA_ARGS__);}} while (0)

#define cp_log_error(logger, ...)	do {if(logger){zlog_error(((zlog_category_t *)(logger->data)), ##__VA_ARGS__);}} while (0)

#define cp_log_warn(logger, ...)	do {if(logger){zlog_warn(((zlog_category_t *)(logger->data)), ##__VA_ARGS__);}} while (0)

#define cp_log_notice(logger, ...)	do {if(logger){zlog_notice(((zlog_category_t *)(logger->data)), ##__VA_ARGS__);}} while (0)

#define cp_log_info(logger, ...)	do {if(logger){zlog_info(((zlog_category_t *)(logger->data)), ##__VA_ARGS__);}} while (0)

#define cp_log_debug(logger, ...)	do {if(logger){zlog_debug(((zlog_category_t *)(logger->data)), ##__VA_ARGS__);}} while (0)

#elif defined(CP_LOG_USED_NULL)
#define cp_log_fatal(logger, fmt, ...)	

#define cp_log_error(logger, fmt, ...)	

#define cp_log_warn(logger, fmt, ...)	

#define cp_log_notice(logger, fmt, ...)	

#define cp_log_info(logger, fmt, ...)	

#define cp_log_debug(logger, fmt, ...)	

#else

#define cp_log_fatal(logger, fmt, ...)	do {printf("FATAL\t - " fmt "\r\n", ##__VA_ARGS__);} while (0)

#define cp_log_error(logger, fmt, ...)	do {printf("ERROR\t - " fmt "\r\n", ##__VA_ARGS__);} while (0)

#define cp_log_warn(logger, fmt, ...)	do {printf("WARN\t - " fmt "\r\n", ##__VA_ARGS__);} while (0)

#define cp_log_notice(logger, fmt, ...)	do {printf("NOTICE\t - " fmt "\r\n", ##__VA_ARGS__);} while (0)

#define cp_log_info(logger, fmt, ...)	do {printf("INFO\t - " fmt "\r\n", ##__VA_ARGS__);} while (0)

#define cp_log_debug(logger, fmt, ...)	do {printf("DEBUG\t - " fmt "\r\n", ##__VA_ARGS__);} while (0)

#endif
	



#endif


