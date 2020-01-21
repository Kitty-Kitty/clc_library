
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


#include "cp_app_core.h"


typedef struct cp_app_handles_s			cp_app_handles_t;
typedef cp_app_t* (*cp_app_create_handle)(cp_app_info_t *app_info);
typedef cp_int32_t (*cp_app_destroy_handle)(cp_app_t *app);
typedef int(*cp_app_init_handle)(cp_app_t *app, cp_app_info_t *cp_global_app_info);
typedef int(*cp_app_start_handle)(cp_app_t *app, cp_app_info_t *cp_global_app_info);
typedef int(*cp_app_stop_handle)(cp_app_t *app);



#pragma pack(1)


#if 0
/************************************************************************/
/*表示app的处理函数定义                                                  */
/************************************************************************/
#define CP_APP_HANDLER_FIELDS											\
	int(*init)(cp_app_t *app, cp_app_info_t *app_info);					\
	int(*start)(cp_app_t *app, cp_app_info_t *app_info);				\
	int(*stop)(cp_app_t *app);											\


#endif


/************************************************************************/
/*表示app的处理函数定义                                                  */
/************************************************************************/
#define CP_APP_HANDLER_FIELDS											\
	cp_app_init_handle	init;											\
	cp_app_start_handle start;											\
	cp_app_stop_handle	stop;											\






// 		cp_module_manager_register_t	**module_manager_register;		/*表示模块注册信息数组*/							\
// 		cp_int32_t						module_manager_register_size;	/*表示模块注册数组大小*/							\
// 		cp_module_manager_t				**module_manager_array;			/*所有模块管理器指针都在保存在这个数组中*/			\
// 		cp_int32_t						module_manager_size;			/*所有模块管理器数组中内容的数量*/					\




/************************************************************************/
/* 表示app 信息定义                                                      */
/************************************************************************/

#define CP_APP_FIELDS																									\
		cp_module_manager_register_t	register_info;																	\
		cp_log_t						*logger;						/*日志信息*/										\
		cp_conf_t						*conf;							/*配置文件信息*/									\
		cp_app_info_t					*app_info;						/*设备附加信息*/									\
		cp_daemon_info_t				*daemon_info;					/*守护附加信息*/									\
		cp_void_t						*data;							/*表示设备其他的数据*/							\
		cp_mpool_t						*mpool;							/*app自带的简单内存管理*/							\
		cp_array_t						root_module_manager_register;	/*表示模块注册信息数组*/							\
		cp_array_t						root_module_manager_array;		/*所有模块管理器指针都在保存在这个数组中*/			\
		CP_APP_HANDLER_FIELDS											/*表示app的处理函数*/							\
		cp_timeval						system_tv;						/*表示当前系统时间*/								\


// 		cp_atomic_t						sec;							/*表示当前时间的秒部分*/							\
// 		cp_atomic_t						nsec;							/*表示当前时间的纳秒部分*/						\


 /************************************************************************/
 /*表示app结构体                                                          */
 /************************************************************************/
 struct cp_app_s {
	 CP_APP_FIELDS
};

#pragma pack()




 /************************************************************************/
 /* 定义两个app基本函数                                                   */
 /************************************************************************/
 cp_app_t	*cp_app_create(cp_app_info_t *app_info);
 cp_int32_t cp_app_destroy(cp_app_t *app);


 /************************************************************************/
 /* 定义app注册函数                                                                     */
 /************************************************************************/
 cp_int32_t	cp_app_register(cp_int32_t type, cp_char_t *name, cp_int32_t version, cp_char_t *description, cp_app_create_handle para_app_create_handle, cp_app_destroy_handle para_app_destroy_handle);
 cp_int32_t	cp_app_entry_config_path(cp_char_t *config_path);




 /************************************************************************/
 /* 下面定义设置句柄的宏                                                  */
 /************************************************************************/
#define  CP_APP_SET_SINGLE_HANDLER(app, handle, name)							\
	(app)->handle = handle##_##name;


#define  CP_APP_SET_SINGLE_HANDLER_AND_TYPE(app, handle, name, type)			\
	(app)->handle = (type)handle##_##name;



#define  CP_APP_SET_HANDLERS(app, name)											\
	CP_APP_SET_SINGLE_HANDLER_AND_TYPE(app, init, name, cp_app_init_handle)		\
	CP_APP_SET_SINGLE_HANDLER_AND_TYPE(app, start, name, cp_app_start_handle)	\
	CP_APP_SET_SINGLE_HANDLER_AND_TYPE(app, stop, name, cp_app_stop_handle)		\



#endif




