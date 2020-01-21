/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-12-13

Description:

**************************************************************************/

#ifndef _CP_CHANNEL_MANAGER_INCLUDE_H_
#define _CP_CHANNEL_MANAGER_INCLUDE_H_


#include "cp_core.h"
#include "cp_include.h"
#include "cp_tree_ex.h"



#define CP_CHANNEL_MANAGER_DEFAULT_NUMBER			256							//表示默认的通道通道数



typedef struct cp_channel_s							cp_channel_t;
typedef struct cp_channel_manager_s					cp_channel_manager_t;


typedef int(*cp_channel_remove_handle)(cp_channel_manager_t *cm, cp_void_t *arg, cp_channel_t *channel);


#pragma pack(1)

/************************************************************************/
/* 设备通道信息                                                          */
/************************************************************************/
struct cp_channel_s
{
	cp_channel_manager_t			*cm;										//表示通道对应的管理器地址
	cp_module_t						*module;									//表示通道处理模块
	cp_void_t						*data;										//表示其他信息
	cp_int32_t						index;										//表示通道数字编号
	cp_char_t						session[CP_APP_DEFAULT_SESSION_ID_LENGTH];	//表示通道播放session
	CP_RB_ENTRY(cp_channel_s)		tree_entry;									//表示红黑树内容
};


/************************************************************************/
/* 初始化红黑树                                                          */
/************************************************************************/
CP_RB_HEAD(cp_channel_rb_tree_s, cp_channel_s);



/************************************************************************/
/* 设备通道管理器                                                        */
/************************************************************************/
struct cp_channel_manager_s
{
	cp_app_t						*app;										//表示通道管理器所属的app地址
	cp_log_t						*logger;									//表示日志logger指针
	cp_mpool_t						*mpool;										//channelmanager自带的简单内存管理
	cp_int32_t						max_size;									//最大播放媒体数
	cp_atomic_t						size;										//表示当前存在的通道数
	cp_array_t						channels;									//主要描述各个服务器对应的通道发送信息
	struct cp_channel_rb_tree_s		chl_rb_root;								//表示红黑根节点
	cp_mutex_t						chl_mutex;									//表示通道处理锁
};

#pragma pack()




#ifdef __cplusplus
extern "C" {
#endif


/************************************************************************/
/* 通道管理器的处理方法                                                  */
/************************************************************************/
int init_channel_manager(cp_app_t *app, cp_channel_manager_t *cm, cp_int32_t max_size);
int start_channel_manager(cp_channel_manager_t *cm);
int stop_channel_manager(cp_channel_manager_t *cm);

int init_channel(cp_channel_manager_t *cm, cp_channel_t *chl);
int set_channel(cp_channel_t *chl, cp_int32_t index, cp_char_t *session, cp_module_t *module, cp_void_t *data);
cp_channel_t *insert_channel(cp_channel_manager_t *cm, cp_channel_t *src);
cp_channel_t *find_channel_by_index(cp_channel_manager_t *cm, cp_int32_t index);
int remove_channel_by_index(cp_channel_manager_t *cm, cp_int32_t index);
int remove_channel(cp_channel_manager_t *cm, cp_channel_t *src);
int remove_all_channel(cp_channel_manager_t *cm, cp_void_t *arg, cp_channel_remove_handle handle);


int find_max_channel_index(cp_channel_manager_t *cm);
int find_min_channel_index(cp_channel_manager_t *cm);
cp_channel_t* find_max_channel(cp_channel_manager_t *cm);
cp_channel_t* find_min_channel(cp_channel_manager_t *cm);


#ifdef __cplusplus
}
#endif



#endif

