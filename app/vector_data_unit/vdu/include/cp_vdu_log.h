/*******************************************************************************
*
*Copyright:novigo
*
*File name: cp_vdu_log.h
*
*Author:fangzhenmu@novigo.com.cn
*
*Version: 1.0
*
*Date:2018/02/05
*
*Description: create (cp_vdu_log.h)
*
*Others:
*
*History:
*******************************************************************************/

#ifndef _CP_VDU_LOG_H_
#define _CP_VDU_LOG_H_




//表示是否使用日志


//#ifdef CP_LOG_USED_NULL

#ifndef _CP_LOG_INCLUDE_H_
#define _CP_LOG_INCLUDE_H_							1
#endif // _CP_LOG_INCLUDE_H_


#ifdef cp_log_printf
#undef cp_log_printf
#define cp_log_printf(fmt, ...)		
#else
#define cp_log_printf(fmt, ...)		
#endif // cp_log_printf


#ifdef cp_log_fatal
#undef cp_log_fatal
#define cp_log_fatal(logger, ...)		
#else
#define cp_log_fatal(logger, ...)		
#endif // cp_log_fatal


#ifdef cp_log_error
#undef cp_log_error
#define cp_log_error(logger, ...)		
#else
#define cp_log_error(logger, ...)		
#endif // cp_log_error


#ifdef cp_log_warn
#undef cp_log_warn
#define cp_log_warn(logger, ...)		
#else
#define cp_log_warn(logger, ...)	
#endif // cp_log_warn



#ifdef cp_log_notice
#undef cp_log_notice
#define cp_log_notice(logger, ...)		
#else
#define cp_log_notice(logger, ...)		
#endif // cp_log_notice



#ifdef cp_log_info
#undef cp_log_info
#define cp_log_info(logger, ...)		
#else
#define cp_log_info(logger, ...)		
#endif // cp_log_info



#ifdef cp_log_debug
#undef cp_log_debug
#define cp_log_debug(logger, ...)		
#else
#define cp_log_debug(logger, ...)		
#endif // cp_log_debug


//#endif // CP_LOG_USED_NULL




#endif //_CP_VDU_LOG_H_


