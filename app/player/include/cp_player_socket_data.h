/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-11-28

Description:

**************************************************************************/

#ifndef _CP_PLAYER_SOCKET_DATA_INCLUDE_H_
#define _CP_PLAYER_SOCKET_DATA_INCLUDE_H_


#include "cp_player_core.h"
#include "cp_min_heap.h"
#include "cp_safe_queue.h"




typedef struct	cp_min_heap											cp_min_heap_t;
typedef struct	cp_min_heap_node									cp_min_heap_node_t;
typedef enum	cp_socket_data_type_enum							cp_socket_data_type_e;


typedef struct	cp_css_socket_data_s								cp_css_socket_data_t;
typedef struct	cp_semh_socket_data_s								cp_semh_socket_data_t;
typedef struct	cp_memh_socket_data_s								cp_memh_socket_data_t;


typedef struct	cp_min_heap_socket_data_s							cp_min_heap_socket_data_t;
typedef struct	cp_socket_buffer_data_s								cp_socket_buffer_data_t;



/************************************************************************/
/* 表示默认的队列大小                                                    */
/************************************************************************/
#define CP_PLAYER_SOCKET_DATA_QUEUE_LENGTH							1024



#pragma pack(1)


/************************************************************************/
/*表示socket data的类型                                                  */
/************************************************************************/
enum cp_socket_data_type_enum
{
	cp_socket_data_semh = 1,
	cp_socket_data_memh,
};


/************************************************************************/
/* 表示css socket data                                                  */
/************************************************************************/
struct cp_css_socket_data_s
{
	cp_int32_t							module_type;			//表示模块类型
	cp_socket_data_type_e				type;					//表示数据类型
	cp_void_t							*data;					//表示其他信息
	cp_int32_t							max_cache_size;			//表示最大缓存数量
	cp_atomic64_t						length;					//表示数据总
	cp_safe_queue_t						*cache_sq;				//表示数据缓存队列信息
	cp_safe_queue_t						*data_sq;				//表示数据队列信息
};


/************************************************************************/
/* 表示socket semh data                                                 */
/************************************************************************/
struct cp_semh_socket_data_s
{
	cp_css_socket_data_t				sd;						//表示css基础数据块内容
};


/************************************************************************/
/* 表示socket memh data                                                 */
/************************************************************************/
struct cp_memh_socket_data_s
{
	cp_css_socket_data_t				sd;						//表示css基础数据块内容
	cp_min_heap_t						data_mh;				//表示数据最小堆
};


/************************************************************************/
/* 最小堆使用的节构数据                                                  */
/************************************************************************/
struct cp_min_heap_socket_data_s
{
	cp_min_heap_node_t					node;
	cp_int32_t							index;
	cp_socket_buffer_data_t				*sbd;
};


/************************************************************************/
/*                                                                      */
/************************************************************************/
struct cp_socket_buffer_data_s
{
	cp_min_heap_socket_data_t			mh_elemn;				//最小堆节构
	cp_buf_t							buf;					//申请的内存描述
};


#pragma pack()


//创建socket data
cp_void_t*	create_socket_data(cp_pool_t *pool, cp_socket_data_type_e type);
cp_semh_socket_data_t*	create_semh_socket_data(cp_pool_t *pool);
cp_memh_socket_data_t*	create_memh_socket_data(cp_pool_t *pool);

//消毁socket data
cp_int32_t destroy_socket_data(cp_pool_t *pool, cp_void_t *socket_data);


/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: create_a_semh_socket_buffer
*
* 函数说明: 创建一个
*
* 参    数: cp_pool_t * pool						[in]参数说明
* 参    数: cp_semh_socket_data_t * ssd						[in]参数说明
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
cp_buf_t* create_a_semh_socket_buffer(cp_pool_t *pool, cp_semh_socket_data_t *ssd, cp_int32_t size);
cp_buf_t* create_a_memh_socket_buffer(cp_pool_t *pool, cp_memh_socket_data_t *msd, cp_int32_t size);


cp_int32_t destroy_a_semh_socket_buffer(cp_pool_t *pool, cp_semh_socket_data_t *ssd, cp_buf_t *buf);
cp_int32_t destroy_a_memh_socket_buffer(cp_pool_t *pool, cp_memh_socket_data_t *ssd, cp_buf_t *buf);

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: push_a_semh_socket_buffer
*
* 函数说明: 插入一个get_a_xxxx_socket_buffer创建的buffer
*
* 参    数: cp_semh_socket_data_t * ssd						[in]参数说明
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
cp_int32_t push_a_semh_socket_buffer(cp_semh_socket_data_t *ssd, cp_buf_t *buf);
cp_int32_t push_a_memh_socket_buffer(cp_memh_socket_data_t *msd, cp_buf_t *buf);

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: pop_a_semh_socket_buffer
*
* 函数说明: 从队列中弹出一个socket buffer
*
* 参    数: cp_semh_socket_data_t * ssd						[in]参数说明
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
cp_buf_t* pop_a_semh_socket_buffer(cp_semh_socket_data_t *ssd);
cp_buf_t* pop_a_memh_socket_buffer(cp_memh_socket_data_t *msd);

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: get_semh_socket_buffer_length
*
* 函数说明: 
*
* 参    数: cp_semh_socket_data_t * ssd						[in]参数说明
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
cp_int64_t get_semh_socket_buffer_length(cp_semh_socket_data_t *ssd);
cp_int64_t get_memh_socket_buffer_length(cp_memh_socket_data_t *msd);



/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: get_memh_socket_buffer_func
*
* 函数说明: 获取处理func句柄
*
* 参    数: cp_memh_socket_data_t * msd						[in]参数说明
*
* 返 回 值: cp_func_t *
*           0  : 成功 
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2016-12-05 15:14:01
******************************************************************************************************/
cp_func_t *get_memh_socket_buffer_func(cp_memh_socket_data_t *msd);
cp_int32_t set_memh_socket_buffer_func(cp_memh_socket_data_t *msd, cp_func_t *func);

#endif