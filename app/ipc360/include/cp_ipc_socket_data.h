/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-11-28

Description:

**************************************************************************/

#ifndef _CP_IPC_SOCKET_DATA_INCLUDE_H_
#define _CP_IPC_SOCKET_DATA_INCLUDE_H_


#include "cp_ipc_core.h"
#include "cp_min_heap.h"
#include "cp_lockfree_queue.h"




typedef struct	cp_min_heap											cp_min_heap_t;
typedef struct	cp_min_heap_node									cp_min_heap_node_t;
typedef enum	cp_socket_data_type_enum							cp_socket_data_type_e;
typedef struct	cp_rtp_socket_data_s								cp_rtp_socket_data_t;
typedef struct cp_min_heap_socket_data_s							cp_min_heap_socket_data_t;
typedef struct	cp_socket_buffer_data_s								cp_socket_buffer_data_t;



/************************************************************************/
/* 表示默认的队列大小                                                    */
/************************************************************************/
#define CP_IPC_SOCKET_DATA_QUEUE_LENGTH								512



#pragma pack(1)

/************************************************************************/
/*表示socket data的类型                                                  */
/************************************************************************/
enum cp_socket_data_type_enum
{
	cp_socket_data_rtp = 1,
};


/************************************************************************/
/* 表示socket rtp data                                                 */
/************************************************************************/
struct cp_rtp_socket_data_s
{
	cp_int32_t							module_type;			//表示模块类型
	cp_socket_data_type_e				type;					//表示数据类型
	cp_void_t							*data;					//表示其他信息
	cp_int32_t							max_cache_size;			//表示最大缓存数量
	cp_int64_t							length;					//表示数据总
	cp_lockfree_queue_t					cache_lq;				//表示数据缓存队列信息
	cp_lockfree_queue_t					data_lq;				//表示数据队列信息
};


/************************************************************************/
/* 最小堆使用的节构数据                                                  */
/************************************************************************/
struct cp_min_heap_socket_data_s
{
	cp_min_heap_node_t					node;
	int									index;
	cp_socket_buffer_data_t				*sbd;
};


/************************************************************************/
/*                                                                      */
/************************************************************************/
struct cp_socket_buffer_data_s
{
	cp_lockfree_queue_element_t			lq_elem;				//队列节点数据
	cp_min_heap_socket_data_t			mh_elemn;				//最小堆节构
	cp_buf_t							buf;					//申请的内存描述
};


#pragma pack()


//创建socket data
cp_void_t*	create_socket_data(cp_pool_t *pool, cp_socket_data_type_e type);
cp_rtp_socket_data_t*	create_rtp_socket_data(cp_pool_t *pool);

//消毁socket data
cp_int32_t destroy_socket_data(cp_pool_t *pool, cp_void_t *socket_data);


/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: create_a_rtp_socket_buffer
*
* 函数说明: 创建一个
*
* 参    数: cp_pool_t * pool						[in]参数说明
* 参    数: cp_rtp_socket_data_t * ssd						[in]参数说明
* 参    数: cp_int32_t size						[in]参数说明
*
* 返 回 值: cp_buf_t*
*           0  : 成功 
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2016-11-28 15:11:32
******************************************************************************************************/
cp_buf_t* create_a_rtp_socket_buffer(cp_pool_t *pool, cp_rtp_socket_data_t *ssd, cp_int32_t size);


cp_int32_t destroy_a_rtp_socket_buffer(cp_pool_t *pool, cp_rtp_socket_data_t *ssd, cp_buf_t *buf);

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: push_a_rtp_socket_buffer
*
* 函数说明: 插入一个get_a_xxxx_socket_buffer创建的buffer
*
* 参    数: cp_rtp_socket_data_t * ssd						[in]参数说明
* 参    数: cp_buf_t * buf						[in]参数说明
*
* 返 回 值: cp_int32_t
*           0  : 成功 
*         非 0  :失败
*
* 备    注:这里的插入仅支持get_a_xxxx_socket_buffer创建的buffer
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2016-11-28 15:14:45
******************************************************************************************************/
cp_int32_t push_a_rtp_socket_buffer(cp_rtp_socket_data_t *ssd, cp_buf_t *buf);

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: pop_a_rtp_socket_buffer
*
* 函数说明: 从队列中弹出一个socket buffer
*
* 参    数: cp_rtp_socket_data_t * ssd						[in]参数说明
*
* 返 回 值: cp_buf_t*
*           0  : 成功 
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2016-11-28 15:26:58
******************************************************************************************************/
cp_buf_t* pop_a_rtp_socket_buffer(cp_rtp_socket_data_t *ssd);

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: get_rtp_socket_buffer_length
*
* 函数说明: 
*
* 参    数: cp_rtp_socket_data_t * ssd						[in]参数说明
*
* 返 回 值: cp_int64_t
*           0  : 成功 
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2016-11-28 18:44:57
******************************************************************************************************/
cp_int64_t get_rtp_socket_buffer_length(cp_rtp_socket_data_t *ssd);


#endif