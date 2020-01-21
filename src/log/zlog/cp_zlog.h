/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/

#ifndef	_CP_ZLOG_INCLUDE_H_
#define _CP_ZLOG_INCLUDE_H_


#include "cp_log.h"




int cp_zlog_init(cp_log_t *logger, int argc, char ** argv);
int cp_zlog_start(cp_log_t *logger, int argc, char ** argv);
int cp_zlog_stop(cp_log_t *logger, int argc, char ** argv);






#endif


