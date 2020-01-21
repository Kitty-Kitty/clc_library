/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2017-04-24

Description:

**************************************************************************/

#ifndef _CP_MODULE_MESSAGE_INCLUDE_H_
#define _CP_MODULE_MESSAGE_INCLUDE_H_






#include "cp_core.h"
#include "cp_safe_queue.h"
#include "cp_thread_core.h"


#define CP_MODULE_MESSAGE_DEFAULT_NUMBER						128							//默认的消息队列个数
#define	CP_MODULE_MESSAGE_SLEEP_INTERVAL						100000000					//默认的休眠间隔时间，单位纳秒




typedef enum	cp_module_message_type_enum					cp_module_message_type_e;
typedef struct	cp_module_message_process_s					cp_module_message_process_t;
typedef struct	cp_module_message_s							cp_module_message_t;
//typedef struct	cp_module_message_manager_s					cp_module_message_manager_t;
typedef cp_int32_t(*module_message_handle)(cp_module_message_manager_t *mmm, cp_module_message_t *src, cp_void_t *data);



#pragma pack(1)


/************************************************************************/
/* 消息类型                                                              */
/************************************************************************/
enum cp_module_message_type_enum
{
	cp_module_message_type_none = 0,
	cp_module_message_type_init,
	cp_module_message_type_start,
	cp_module_message_type_stop,
	cp_module_message_type_create,
	cp_module_message_type_destory,
	cp_module_message_type_open,
	cp_module_message_type_read,
	cp_module_message_type_write,
	cp_module_message_type_close,
	cp_module_message_type_exit,
	cp_module_message_type_end,
};


/************************************************************************/
/* 消息处理句柄                                                          */
/************************************************************************/
struct cp_module_message_process_s
{
	cp_module_message_type_e					mm_type;
	module_message_handle						handle;
};


/************************************************************************/
/* 设备通道信息                                                          */
/************************************************************************/
struct cp_module_message_s
{
	cp_module_message_manager_t					*mmm;										//表示通道对应的管理器地址
	cp_module_t									*module;									//表示通道处理模块
	cp_module_register_t						*module_register;							//表示模块注册消息
	cp_module_info_t							*module_info;								//表示模块信息
	cp_void_t									*data;										//表示其他信息
	cp_int32_t									index;										//表示通道数字编号
	cp_module_message_process_t					mmp;										//表示模块处理句柄
};



/************************************************************************/
/* 设备通道管理器                                                        */
/************************************************************************/
struct cp_module_message_manager_s
{
	cp_module_manager_t							*manager;									//表示模块管理器地址
	cp_log_t									*logger;									//表示日志logger指针
	cp_mpool_t									*mpool;										//module_messagemanager自带的简单内存管理
	cp_thread_t									*thread;									//表示消息处理线程
	cp_safe_queue_t								*mes_sq;									//表示数据队列信息
	cp_module_message_process_t					*mmp_list;									//表示红黑树内容
	cp_thread_status_e							thread_status;								//线程状态
};


#pragma pack()



/************************************************************************/
/* 模块消息管理器的处理方法                                                  */
/************************************************************************/
cp_module_message_manager_t *create_module_message_manager(cp_module_manager_t	*manager);
cp_int32_t destroy_module_message_manager(cp_module_message_manager_t *mmm);

cp_int32_t init_module_message_manager(cp_module_manager_t	*manager, cp_module_message_manager_t *mmm);
cp_int32_t start_module_message_manager(cp_module_message_manager_t *mmm);
cp_int32_t stop_module_message_manager(cp_module_message_manager_t *mmm);

cp_int32_t set_module_message_process(cp_module_message_manager_t *mmm, cp_module_message_process_t *mmp);


/************************************************************************/
/* 模块消息的处理方法                                                  */
/************************************************************************/
cp_module_message_t *create_module_message(cp_module_message_manager_t *mmm);
cp_int32_t destroy_module_message(cp_module_message_manager_t *mmm, cp_module_message_t *mm);


cp_int32_t init_module_message(cp_module_message_manager_t *mmm, cp_module_message_t *mm);
cp_int32_t set_module_message(cp_module_message_t *mm, 
	cp_module_t *module, cp_void_t *data, cp_int32_t index, cp_module_message_type_e mm_type, module_message_handle	handle);
cp_int32_t push_module_message(cp_module_message_manager_t *mmm, cp_module_message_t *src);
cp_module_message_t *pop_module_message(cp_module_message_manager_t *mmm);


/************************************************************************/
/* 模块消息处理线程的处理方法                                                  */
/************************************************************************/
cp_void_t	module_message_thread_cb_proc(cp_module_message_manager_t *mmm);
cp_int32_t	module_message_general_handle(cp_module_message_manager_t *mmm, cp_module_message_t *src, cp_void_t *data);
cp_int32_t	module_message_addr_handle(cp_module_message_manager_t *mmm, cp_module_message_t *src, cp_void_t *data);
cp_int32_t	module_message_close_handle(cp_module_message_manager_t *mmm, cp_module_message_t *src, cp_void_t *data);




/************************************************************************/
/* 设置模块消息处理的接口信息                                             */
/************************************************************************/
#define  CP_MODULE_MESSAGE_PROCESS_SET_SINGLE_HANDLER(mmp, handle_name, handle)				\
	(mmp)->handle_name = (handle);															\



/************************************************************************/
/* 设置模块消息管理器的单个接口信息                                       */
/************************************************************************/
#define  CP_MODULE_MESSAGE_MANAGER_SET_SINGLE_HANDLER(mmm, handle_name, handle)				\
	CP_MODULE_MESSAGE_PROCESS_SET_SINGLE_HANDLER(&((mmm)->mmp), handle_name, handle)		\



/************************************************************************/
/* 设置模块消息管理器的单个接口信息                                       */
/************************************************************************/
#define  CP_MODULE_MESSAGE_MANAGER_SET_HANDLER(mmm, none_handle, add_handle, update_handle, ctrl_handle, remove_handle)	do {			\
	CP_MODULE_MESSAGE_MANAGER_SET_SINGLE_HANDLER((mmm), none, (none_handle));															\
	CP_MODULE_MESSAGE_MANAGER_SET_SINGLE_HANDLER((mmm), add, (add_handle));																\
	CP_MODULE_MESSAGE_MANAGER_SET_SINGLE_HANDLER((mmm), update, (update_handle));														\
	CP_MODULE_MESSAGE_MANAGER_SET_SINGLE_HANDLER((mmm), ctrl, (ctrl_handle));															\
	CP_MODULE_MESSAGE_MANAGER_SET_SINGLE_HANDLER((mmm), remove, (remove_handle));														\
} while (0);																															\


#endif

