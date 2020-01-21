/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-05-26

Description: define module

**************************************************************************/


#ifndef	_CP_MODULE_INCLUDE_H_
#define _CP_MODULE_INCLUDE_H_



#include "cp_module_core.h"





//typedef struct cp_module_s						cp_module_t;





#pragma pack(1)




typedef cp_int32_t(*module_init_handle)(cp_module_t *module, const cp_module_info_t *module_info);								/*模块创建接口，表示创建一个模块*/
typedef cp_int32_t(*module_open_handle)(cp_module_t *module, const cp_module_info_t *module_info);								/*模块打开运行接口，在模块init之后，会被调用*/
typedef cp_int32_t(*module_read_handle)(cp_module_t *module, cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag);				/*读取模块数据，flag为读取模式的扩展标志。默认为0，其他为预留*/
typedef cp_int32_t(*module_write_handle)(cp_module_t *module, const cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag);			/*写模块数据，flag为写模式的扩展标志。默认为0，其他为预留*/
typedef cp_int32_t(*module_close_handle)(cp_module_t *module);																	/*关闭模块*/
typedef cp_int32_t(*module_exit_handle)(cp_module_t *module);																	/*退出模块*/
typedef cp_int32_t(*module_set_option_handle)(cp_module_t *module, cp_int32_t optname, const cp_void_t* optval);				/*设置模块参数*/
typedef cp_int32_t(*module_get_option_handle)(cp_module_t *module, cp_int32_t optname, cp_void_t* optval);						/*获取模块参数*/



#if 0
/************************************************************************/
/* 表示模块处理函数接口													 */
/************************************************************************/

#define CP_MODULE_HANDLER_FIELDS					\
			cp_int32_t(*init)(cp_module_t *module, const cp_module_info_t *module_info);								/*模块创建接口，表示创建一个模块*/										\
			cp_int32_t(*open)(cp_module_t *module, const cp_module_info_t *module_info);								/*模块打开运行接口，在模块init之后，会被调用*/							\
			cp_int32_t(*read)(cp_module_t *module, cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag);					/*读取模块数据，flag为读取模式的扩展标志。默认为0，其他为预留*/			\
			cp_int32_t(*write)(cp_module_t *module, const cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag);			/*写模块数据，flag为写模式的扩展标志。默认为0，其他为预留*/				\
			cp_int32_t(*close)(cp_module_t *module);																	/*关闭模块*/															\
			cp_int32_t(*exit)(cp_module_t *module);																		/*退出模块*/															\
			cp_int32_t(*set_option)(cp_module_t *module, cp_int32_t optname, const cp_void_t* optval);					/*设置模块参数*/														\
			cp_int32_t(*get_option)(cp_module_t *module, cp_int32_t optname, cp_void_t* optval);						/*获取模块参数*/														\


#endif


/************************************************************************/
/*模块错误信息                                                           */
/************************************************************************/
#define CP_MODULE_ERROR_FIELDS																				\
			cp_int32_t						error_no;									/*错误码*/			\
			cp_char_t						error_text[CP_APP_DEFAULT_STRING_LENGTH];	/*错误内容*/			\



#define CP_MODULE_HANDLER_FIELDS																										\
			module_init_handle init;								/*模块创建接口，表示创建一个模块*/										\
			module_open_handle open;								/*模块打开运行接口，在模块init之后，会被调用*/							\
			module_read_handle read;								/*读取模块数据，flag为读取模式的扩展标志。默认为0，其他为预留*/			\
			module_write_handle write;								/*写模块数据，flag为写模式的扩展标志。默认为0，其他为预留*/				\
			module_close_handle close;								/*关闭模块*/															\
			module_exit_handle exit;								/*退出模块*/															\
			module_set_option_handle set_option;					/*设置模块参数*/														\
			module_get_option_handle get_option;					/*获取模块参数*/														\




/************************************************************************/
/*模块内容,子模块信息必须继承该信息                                       */
/************************************************************************/
#define CP_MODULE_FIELDS																				\
			cp_module_register_t			register_info;												\
			cp_module_manager_t				*manager;				/*模块管理器地址信息*/				\
			cp_log_t						*logger;				/*表示日志logger指针*/				\
			cp_conf_t						*conf;					/*表示配置文件信息*/					\
			cp_module_info_t				*info;					/*表示模块信息*/						\
			cp_void_t						*data;					/*表示模块的其他数据*/				\
			cp_pool_t						*pool;					/*表示模块的私有内存池*/				\
			cp_module_message_manager_t		*mmm;					/*表示模块消息管理器*/				\
			cp_module_t						*decorator;				/*表示模块装饰器*/					\
			cp_atomic_t						status;					/*表示模块的状态信息*/				\
			cp_module_register_t			**module_register;		/*表示子模块注册数组*/				\
			cp_int32_t						module_register_size;	/*表示子模块注册数组大小*/			\
			cp_int32_t						flag;					/*表示模块的标识信息*/				\
			cp_queue_t						queue;					/*表示模块列表*/											\
			cp_char_t						description[CP_APP_DEFAULT_STRING_LENGTH];			/*表示模块的其他描述信息*/	\
			CP_MODULE_ERROR_FIELDS									/*表示模块错误信息*/					\
			CP_MODULE_HANDLER_FIELDS								/*表示模块处理的基本接口*/			\


/************************************************************************/
/* 表示模块信息结构体                                                    */
/************************************************************************/
struct cp_module_s
{
	CP_MODULE_FIELDS
};


#pragma pack()




/************************************************************************/
/* 设置模块的接口信息                                                    */
/************************************************************************/

#define  CP_MODULE_SET_SINGLE_HANDLER(module, handle, name)											\
	(module)->handle = handle##_##name;																\



#define  CP_MODULE_SET_SINGLE_HANDLER_AND_TYPE(module, handle, name, type)							\
	(module)->handle = (type)handle##_##name;														\



/************************************************************************/
/* 更新模块的接口信息                                                    */
/************************************************************************/

#define  CP_MODULE_UPDATE_SINGLE_HANDLER(src_module, dest_module, handle)							\
	(dest_module)->handle = (src_module)->handle;													\


#define  CP_MODULE_UPDATE_SINGLE_HANDLER_AND_TYPE(src_module, dest_module, handle, type)			\
	(dest_module)->handle = (type)(src_module)->handle;												\



#ifdef close
#undef close
#endif

/************************************************************************/
/* 设置模块的所有接口                                                    */
/************************************************************************/
#define  CP_MODULE_SET_HANDLERS(module, name)		do {											\
	CP_MODULE_SET_SINGLE_HANDLER_AND_TYPE(module, init, name, module_init_handle)					\
	CP_MODULE_SET_SINGLE_HANDLER_AND_TYPE(module, open, name, module_open_handle)					\
	CP_MODULE_SET_SINGLE_HANDLER_AND_TYPE(module, read, name, module_read_handle)					\
	CP_MODULE_SET_SINGLE_HANDLER_AND_TYPE(module, write, name, module_write_handle)					\
	CP_MODULE_SET_SINGLE_HANDLER_AND_TYPE(module, close, name, module_close_handle)					\
	CP_MODULE_SET_SINGLE_HANDLER_AND_TYPE(module, exit, name, module_exit_handle)					\
	CP_MODULE_SET_SINGLE_HANDLER_AND_TYPE(module, set_option, name, module_set_option_handle)		\
	CP_MODULE_SET_SINGLE_HANDLER_AND_TYPE(module, get_option, name, module_get_option_handle)		\
} while (0);																						\




/************************************************************************/
/* 更新模块的所有接口                                                    */
/************************************************************************/
#define  CP_MODULE_UPDATE_HANDLERS(src_module, dest_module)		do {								\
	CP_MODULE_UPDATE_SINGLE_HANDLER(src_module, dest_module, init)									\
	CP_MODULE_UPDATE_SINGLE_HANDLER(src_module, dest_module, open)									\
	CP_MODULE_UPDATE_SINGLE_HANDLER(src_module, dest_module, read)									\
	CP_MODULE_UPDATE_SINGLE_HANDLER(src_module, dest_module, write)									\
	CP_MODULE_UPDATE_SINGLE_HANDLER(src_module, dest_module, close)									\
	CP_MODULE_UPDATE_SINGLE_HANDLER(src_module, dest_module, exit)									\
	CP_MODULE_UPDATE_SINGLE_HANDLER(src_module, dest_module, set_option)							\
	CP_MODULE_UPDATE_SINGLE_HANDLER(src_module, dest_module, get_option)							\
} while (0);																						\


/************************************************************************/
/* 设置模块的data信息                                                    */
/************************************************************************/
#define CP_MODULE_SET_DATA(module_info, in_data)	(module_info)->data = (in_data)


/************************************************************************/
/* 获取模块的data信息                                                    */
/************************************************************************/
#define CP_MODULE_GET_DATA(module_info)				((module_info)->data)



#endif


