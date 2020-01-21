/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-11-29

Description:

**************************************************************************/

#ifndef _CP_DEMO_FUNC_THREAD_INCLUDE_H_
#define _CP_DEMO_FUNC_THREAD_INCLUDE_H_



#include "cp_lockfree_queue.h"
#include "cp_demo_func_manager_core.h"




#define		CP_DEMO_FUNC_DEFAULT_THREAD_NUMBER						3					//表示定义的最大线程数量
#define		CP_DEMO_FUNC_DEFAULT_INTERVAL_MS							10LL				//表示定义线程默认的休眠时间
#define		CP_DEMO_FUNC_DEFAULT_QUEUE_SIZE							1024				//表示定义默认的队列大小



//这里重新包装了打印信息的格式
#define	 cp_pftm_log(level, dftm, format, ...)								\
	do {																	\
		cp_module_log(level, (dftm)->func, format, __VA_ARGS__)				\
	;} while (0)															\



//这里重新包装了打印信息的格式
#define	 cp_pft_log(level, dft, format, ...)								\
	do {																	\
			cp_module_log(level, (dft)->dftm->func, format, __VA_ARGS__)	\
	;} while (0)															\



typedef struct cp_demo_func_chunk_s									cp_demo_func_chunk_t;
typedef enum cp_demo_func_thread_status_enum							cp_demo_func_thread_status_e;
typedef void(*cp_demo_func_thread_cb)(cp_demo_func_thread_t* dft);



#pragma pack(1)

enum cp_demo_func_thread_status_enum
{
	cp_demo_func_thread_status_init = 1,
	cp_demo_func_thread_status_start,
	cp_demo_func_thread_status_stop,
};

/************************************************************************/
/* 定义func线程管理器                                                    */
/************************************************************************/
struct cp_demo_func_thread_manager_s
{
	cp_int32_t							thread_number;					//表示线程数量
	cp_func_t							*func;							//表示该处理对应的func结构
	cp_array_t							thread_group;					//线程组
	cp_int64_t							interval_ms;					//表示休眠时间，单位微秒（ms）
	cp_pool_t							*pool;							//表示管理器使用的内存空间
	cp_lockfree_queue_t					lq;								//表示请的
	cp_mutex_t							pfc_mutex;						//表示创建请
	cp_mutex_t							pool_mutex;						//表示创建的内存空间锁
};


/************************************************************************/
/* 定义func线程                                                         */
/************************************************************************/
struct cp_demo_func_thread_s
{
	cp_int32_t							index;							//表示处理线程索引号
	cp_demo_func_thread_status_e		status;							//表示线程运进状态
	cp_demo_func_thread_manager_t		*dftm;							//表示处理线程管理器
	cp_thread_t							*thread;						//表示当前线程
	cp_int64_t							interval_ms;					//表示休眠时间，单位微秒（ms）
	cp_demo_func_thread_cb			pft_cb;							//表示处理线程的处理
};


/************************************************************************/
/* 定义处理内容结构                                                      */
/************************************************************************/
struct cp_demo_func_chunk_s
{
	cp_lockfree_queue_element_t			lq_elem;						//队列节点数据
	cp_socket_t							*socket;						//当前请
	cp_int32_t							nread;							//当前接 的数据
	cp_buf_t							*buf;							//
	cp_int32_t							status;
};

#pragma pack()

/************************************************************************/
/* 创建                                                                 */
/************************************************************************/
cp_demo_func_thread_manager_t* make_demo_func_thread_manager(cp_func_t *func);
cp_int32_t unmake_demo_func_thread_manager(cp_demo_func_thread_manager_t *dftm);

/************************************************************************/
/* 创建ipc func chunk内容                                             */
/************************************************************************/
cp_int32_t push_semh_demo_func_chunk(cp_demo_func_thread_manager_t *dftm, cp_socket_t *socket, gmp_gmph_semh_t *semh);
cp_demo_func_chunk_t* pop_semh_demo_func_chunk(cp_demo_func_thread_manager_t *dftm);


#endif