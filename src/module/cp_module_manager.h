/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-05-26

Description: define module

**************************************************************************/


#ifndef	_CP_MODULE_MANAGER_INCLUDE_H_
#define _CP_MODULE_MANAGER_INCLUDE_H_



#include "cp_module_core.h"




//typedef struct cp_module_manager_s				cp_module_manager_t;





#pragma pack(1)



typedef	cp_int32_t(*cp_manager_init_handle)(cp_module_manager_t *cp_manager, const cp_module_manager_info_t *info);												/*模块创建接口，表示创建一个模块*/
typedef	cp_int32_t(*cp_manager_start_handle)(cp_module_manager_t *cp_manager, const cp_module_manager_info_t *info);											/*模块打开运行接口，在模块init之后，会被调用*/
typedef	cp_int32_t(*cp_manager_stop_handle)(cp_module_manager_t *cp_manager);																					/*读取模块数据，flag为读取模式的扩展标志。默认为0，其他为预留*/
typedef	cp_int32_t(*cp_manager_ctrl_handle)(cp_module_manager_t *cp_manager, cp_int32_t optname, const cp_void_t* optval);										/*设置模块参数*/
typedef	cp_module_t*(*cp_manager_create_module_handle)(cp_module_manager_t *cp_manager, const cp_module_info_t *info);											/*模块创建接口*/
typedef	cp_module_t*(*cp_manager_get_module_handle)(cp_module_manager_t *cp_manager, const cp_module_info_t *info);												/*模块查询接口*/
typedef	cp_int32_t(*cp_manager_register_module_handle)(cp_module_manager_t *cp_manager, cp_module_t *module);													/*写模块数据，flag为写模式的扩展标志。默认为0，其他为预留*/
typedef	cp_int32_t(*cp_manager_cancel_module_handle)(cp_module_manager_t *cp_manager, cp_module_t *module);														/*关闭模块*/
typedef	cp_int32_t(*cp_manager_destroy_module_handle)(cp_module_manager_t *cp_manager, cp_module_t *module);													/*退出模块*/
typedef	cp_int32_t(*cp_manager_ctrl_module_handle)(cp_module_manager_t *cp_manager, cp_module_t *module, cp_int32_t optname, const cp_void_t* optval);			/*设置模块参数*/



#if 0
/************************************************************************/
/* 表示模块管理器处理接口													*/
/************************************************************************/
#define CP_MODULE_MANAGER_HANDER_FIELDS																																											\
	cp_int32_t(*init)(cp_module_manager_t *manager, const cp_module_manager_info_t *info);												/*模块创建接口，表示创建一个模块*/											\
	cp_int32_t(*start)(cp_module_manager_t *manager, const cp_module_manager_info_t *info);												/*模块打开运行接口，在模块init之后，会被调用*/								\
	cp_int32_t(*stop)(cp_module_manager_t *manager);																					/*读取模块数据，flag为读取模式的扩展标志。默认为0，其他为预留*/				\
	cp_int32_t(*ctrl)(cp_module_manager_t *manager, cp_int32_t optname, const cp_void_t* optval);										/*设置模块参数*/															\
	cp_module_t*(*cp_create_module)(cp_module_manager_t *manager, const cp_module_info_t *info);										/*模块创建接口*/															\
	cp_module_t*(*get_module)(cp_module_manager_t *manager, const cp_module_info_t *info);												/*模块查询接口*/															\
	cp_int32_t(*register_module)(cp_module_manager_t *manager, cp_module_t *module);													/*写模块数据，flag为写模式的扩展标志。默认为0，其他为预留*/					\
	cp_int32_t(*cancel_module)(cp_module_manager_t *manager, cp_module_t *module);														/*关闭模块*/																\
	cp_int32_t(*destroy_module)(cp_module_manager_t *manager, cp_module_t *module);														/*退出模块*/																\
	cp_int32_t(*ctrl_module)(cp_module_manager_t *manager, cp_module_t *module, cp_int32_t optname, const cp_void_t* optval);			/*设置模块参数*/															\


#endif

/************************************************************************/
/* 表示模块管理器处理接口													*/
/************************************************************************/
#define CP_MODULE_MANAGER_HANDER_FIELDS																												\
	cp_manager_init_handle					init;							/*模块创建接口，表示创建一个模块*/											\
	cp_manager_start_handle					start;							/*模块打开运行接口，在模块init之后，会被调用*/								\
	cp_manager_stop_handle					stop;							/*读取模块数据，flag为读取模式的扩展标志。默认为0，其他为预留*/				\
	cp_manager_ctrl_handle					ctrl;							/*设置模块参数*/															\
	cp_manager_create_module_handle			create_module;					/*模块创建接口*/															\
	cp_manager_get_module_handle			get_module;						/*模块查询接口*/															\
	cp_manager_register_module_handle		register_module;				/*写模块数据，flag为写模式的扩展标志。默认为0，其他为预留*/					\
	cp_manager_cancel_module_handle			cancel_module;					/*关闭模块*/																\
	cp_manager_destroy_module_handle		destroy_module;					/*退出模块*/																\
	cp_manager_ctrl_module_handle			ctrl_module;					/*设置模块参数*/															\





/************************************************************************/
/* 表示模块信息结构体                                                    */
/************************************************************************/
/************************************************************************/
/*模块管理器内容,子模块信息必须继承该信息                                  */
/************************************************************************/
#define CP_MODULE_MANAGER_FIELDS																		\
			cp_module_manager_register_t	register_info;												\
			cp_app_t						*app;							/*表示应用程序指针*/			\
			cp_log_t						*logger;						/*表示日志logger指针*/		\
			cp_conf_t						*conf;							/*表示配置文件信息*/			\
			cp_module_manager_info_t		*info;							/*表示模块管理器信息*/		\
			cp_void_t						*data;							/*表示模块的其他数据*/		\
			cp_pool_t						*pool;							/*表示模块的私有内存池*/		\
			cp_module_message_manager_t		*mmm;							/*表示模块消息管理器*/		\
			cp_module_manager_t				*decorator;						/*表示模块管理器装饰器*/		\
			cp_atomic_t						status;							/*表示模块的状态信息*/		\
			cp_array_t						module_manager_register;		/*表示子模块管理器注册数组*/							\
			cp_array_t						module_managers;				/*所有子模块管理器指针都在保存在这个数组中*/			\
			cp_array_t						module_register;				/*表示模块注册数组*/									\
			cp_queue_t						modules;						/*表示模块列表*/				\
			cp_mutex_t						module_mutex;					/*表示管理模块互斥量*/		\
			CP_MODULE_MANAGER_HANDER_FIELDS									/*表示模块的处理函数*/		\




struct cp_module_manager_s																	
{																							
	CP_MODULE_MANAGER_FIELDS
};



#pragma pack()








/************************************************************************/
/* 设置模块的接口信息                                                    */
/************************************************************************/

#define  CP_MODULE_MANAGER_SET_SINGLE_HANDLER(manager, handle, name)							\
	(manager)->handle = handle##_##name##_manager;


#define  CP_MODULE_MANAGER_SET_SINGLE_HANDLER_AND_TYPE(manager, handle, type, name)				\
	(manager)->handle = (type)handle##_##name##_manager;




#define  CP_MODULE_MANAGER_SET_SINGLE_MODULE_HANDLER(manager, handle, name)						\
	(manager)->handle##_module = handle##_##name##_module;


#define  CP_MODULE_MANAGER_SET_SINGLE_MODULE_HANDLER_AND_TYPE(manager, handle, type, name)		\
	(manager)->handle##_module = (type)handle##_##name##_module;




#define  CP_MODULE_MANAGER_SET_HANDLERS(manager, name)							do {									\
	CP_MODULE_MANAGER_SET_SINGLE_HANDLER_AND_TYPE(manager, init, cp_manager_init_handle, name)							\
	CP_MODULE_MANAGER_SET_SINGLE_HANDLER_AND_TYPE(manager, start, cp_manager_start_handle, name)						\
	CP_MODULE_MANAGER_SET_SINGLE_HANDLER_AND_TYPE(manager, stop, cp_manager_stop_handle, name)							\
	CP_MODULE_MANAGER_SET_SINGLE_HANDLER_AND_TYPE(manager, ctrl, cp_manager_ctrl_handle, name)							\
	CP_MODULE_MANAGER_SET_SINGLE_MODULE_HANDLER_AND_TYPE(manager, create, cp_manager_create_module_handle, name)		\
	CP_MODULE_MANAGER_SET_SINGLE_MODULE_HANDLER_AND_TYPE(manager, get, cp_manager_get_module_handle, name)				\
	CP_MODULE_MANAGER_SET_SINGLE_MODULE_HANDLER_AND_TYPE(manager, register, cp_manager_register_module_handle, name)	\
	CP_MODULE_MANAGER_SET_SINGLE_MODULE_HANDLER_AND_TYPE(manager, cancel, cp_manager_cancel_module_handle, name)		\
	CP_MODULE_MANAGER_SET_SINGLE_MODULE_HANDLER_AND_TYPE(manager, destroy, cp_manager_destroy_module_handle, name)		\
	CP_MODULE_MANAGER_SET_SINGLE_MODULE_HANDLER_AND_TYPE(manager, ctrl, cp_manager_ctrl_module_handle, name)			\
								} while (0);																			\


/************************************************************************/
/* 申请管理模块内存空间                                                   */
/************************************************************************/
#define  CP_MODULE_MANAGER_MALLOC(ret, app, type)								do {			\
	ret = (type*)cp_mpalloc(app->mpool, cp_sizeof(type));										\
	cp_memset(ret, 0, cp_sizeof(type));															\
	cp_queue_init(&(ret)->modules);																\
} while (0);																					\


/************************************************************************/
/* 释放管理模块内存空间                                                   */
/************************************************************************/
#define  CP_MODULE_MANAGER_FREE(manager)														\
	cp_mpfree(manager->app->mpool, manager);													\


#endif


