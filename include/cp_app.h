
/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-23

Description:css_player main include file 

**************************************************************************/


#ifndef _CP_APP_INCLUDE_H_
#define _CP_APP_INCLUDE_H_

#include <stdio.h>
#include <stdlib.h>





#include "cp_core.h"
#include "cp_include.h"
#include "cp_conf.h"
#include "cp_socket.h"
#include "cp_app_info.h"




typedef struct cp_app_handlers_s			cp_app_handlers_t;




/************************************************************************/
/*表示app的处理函数定义                                                  */
/************************************************************************/
struct cp_app_handlers_s {
	int(*init)(cp_app_t *app, cp_app_info_t *app_info);
	int(*start)(cp_app_t *app, cp_app_info_t *app_info);
	int(*stop)(cp_app_t *app);
};



/************************************************************************/
/* 表示app 信息定义                                                      */
/************************************************************************/

#define CP_APP_FIELDS																\
		cp_char_t					*name;				/*表示模块名称*/				\
		cp_int32_t					version;			/*表示模块版本号*/			\
		cp_char_t					*description;		/*表示模块的描述*/			\
		cp_log_t					*logger;			/*日志信息*/					\
		cp_conf_t					*conf;				/*配置文件信息*/				\
		cp_socket_manager_t			*socket_manager;	/*网络通信管理*/				\
		cp_thread_manager_t			*thread_manager;	/*线程管理*/					\
		cp_timer_t					*timer_task;		/*定时器管理*/				\
		cp_app_info_t				*app_info;			/*设备附加信息*/				\
		cp_void_t					*data;				/*表示设备其他的数据*/		\
		cp_app_handlers_t			handlers;			/*表示app的处理函数*/		\
		cp_atomic64_t				sec;				/*表示当前时间的秒部分*/		\
		cp_atomic_t					nsec;				/*表示当前时间的纳秒部分*/	\





 /************************************************************************/
 /*表示app结构体                                                          */
 /************************************************************************/
 struct cp_app_s {
	 CP_APP_FIELDS
};





cp_app_t	*cp_app_create();

int cp_app_init(cp_app_t *app, cp_app_info_t *app_info);
int cp_app_start(cp_app_t *app, cp_app_info_t *app_info);
int cp_app_stop(cp_app_t *app);
int cp_app_destory(cp_app_t *app);




#endif