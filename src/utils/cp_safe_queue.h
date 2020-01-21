/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2017-01-13

Description:

**************************************************************************/

#ifndef _CP_SAFE_QUEUE_INCLUDE_H_
#define _CP_SAFE_QUEUE_INCLUDE_H_


#include <stdio.h>
#include <stdlib.h>
#include "cp_lockfree_queue.h"



typedef struct cp_safe_queue_struct							cp_safe_queue_t;




#pragma pack(1)

typedef enum cp_safe_queue_mode_enum
{
	cp_safe_queue_mode_none,
	//////////////////////////////////////////////////////////////////////////
	//定义各种队列类型

	cp_safe_queue_mode_qbmm,										/*表示有限制队列，需要注意控制队列的数量，操限制可能导致数据丢失。 该种队列需要set option cp_safe_queue_option_bounded*/
#if defined(_CP_LOCKFREE_QUEUE_SPPORT_UMM_)
	cp_safe_queue_mode_qumm											/*无限制队列，该种队列可能导致内存不断增加*/
#endif
	cp_safe_queue_mode_qbss,										/*表示有限制队列，单生产者单销毁者*/

	//////////////////////////////////////////////////////////////////////////
	cp_safe_queue_mode_tail
}cp_safe_queue_mode_e;



struct cp_safe_queue_struct
{
	cp_safe_queue_mode_e					mode;					//表示队列类型
	cp_lockfree_queue_t						free_lq;				//表示数据缓存队列信息
	cp_lockfree_queue_t						busy_lq;				//表示数据队列信息
	cp_lockfree_queue_element_t				*lq_elem;				//表示数据元素
	int										lq_elem_size;			//表示数据元素数量
	unsigned char							is_genera:1;			//表示常规创建
};


#pragma pack()

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: cp_create_general_safe_queue
*
* 函数说明: 创建一个常规队列
*
* 参    数: cp_safe_queue_mode_e mode						[in]参数说明
* 参    数: int size						[in]参数说明
*
* 返 回 值: cp_safe_queue_t*
*      非 null  : 成功 
*         null  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2017-01-13 14:18:00
******************************************************************************************************/
cp_safe_queue_t* cp_create_general_safe_queue(cp_safe_queue_mode_e mode, int size);

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: cp_create_memory_safe_queue
*
* 函数说明: 用指定内存创建队列
*
* 参    数: void * memory						[in]参数说明
* 参    数: int memory_size						[in]参数说明
* 参    数: cp_safe_queue_mode_e mode			[in]参数说明
* 参    数: int elem_size						[in]参数说明
*
* 返 回 值: cp_safe_queue_t*
*      非 null  : 成功
*         null  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2017-01-13 14:41:46
******************************************************************************************************/
cp_safe_queue_t* cp_create_memory_safe_queue(void *memory, int memory_size, 
	cp_safe_queue_mode_e mode, int elem_size);

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: cp_safe_queue_get_memory_size
*
* 函数说明: 计算safe queue需要的内存大小
*
* 参    数: cp_safe_queue_mode_e mode						[in]参数说明
* 参    数: int size						[in]参数说明
*
* 返 回 值: int
*         大于0：safe queue占用的内存大小
*     小于等于0：失败
*
* 备    注:主要在cp_create_memory_safe_queue()创建safe queue时需要计算memory的大小
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2017-01-13 14:18:58
******************************************************************************************************/
int cp_safe_queue_get_memory_size(cp_safe_queue_mode_e mode, int size);

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: cp_safe_queue_check_mode
*
* 函数说明: 校验mode合法性
*
* 参    数: cp_safe_queue_mode_e mode						[in]参数说明
*
* 返 回 值: int
*           0  : 成功 
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2017-01-13 14:24:03
******************************************************************************************************/
int cp_safe_queue_check_mode(cp_safe_queue_mode_e mode);

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: cp_safe_queue_size
*
* 函数说明: 当前队列中元素数量
*
* 参    数: cp_safe_queue_t * sq						[in]参数说明
*
* 返 回 值: int
*           0  : 成功 
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2017-01-13 14:20:30
******************************************************************************************************/
int cp_safe_queue_size(cp_safe_queue_t* sq);

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: cp_safe_queue_push
*
* 函数说明: 插入数据
*
* 参    数: cp_safe_queue_t * sq						[in]参数说明
* 参    数: void * data						[in]参数说明
*
* 返 回 值: int
*           0  : 成功 
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2017-01-13 14:20:39
******************************************************************************************************/
int cp_safe_queue_push(cp_safe_queue_t* sq, void *data);

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: cp_safe_queue_pop
*
* 函数说明: 弹出数据
*
* 参    数: cp_safe_queue_t * sq						[in]参数说明
*
* 返 回 值: void*
*      非 null  : 成功
*         null  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2017-01-13 14:20:52
******************************************************************************************************/
void* cp_safe_queue_pop(cp_safe_queue_t* sq);

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: cp_destroy_safe_queue
*
* 函数说明: 消毁一个队列
*
* 参    数: cp_safe_queue_t * sq						[in]参数说明
*
* 返 回 值: int
*           0  : 成功 
*         非 0  :失败
*
* 备    注:当用cp_create_memory_safe_queue()创建的队列，该函数不消毁传入的memory内存，需要另外消毁
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2017-01-13 14:21:57
******************************************************************************************************/
int cp_destroy_safe_queue(cp_safe_queue_t* sq);

#endif