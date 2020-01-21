/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/

#ifndef	_CP_THREAD_INCLUDE_H_
#define _CP_THREAD_INCLUDE_H_




//typedef struct cp_thread_s				cp_thread_t;
//typedef enum cp_thread_status_enum			cp_thread_status_e;



#pragma pack(1)



/************************************************************************/
/* 线程状态                                                               */
/************************************************************************/
typedef enum cp_thread_status_enum
{
	cp_thread_status_none = 0,
	cp_thread_status_init,
	cp_thread_status_start,
	cp_thread_status_stop,
	cp_thread_status_end,
}cp_thread_status_e;



#include "cp_thread_core.h"



#define CP_THREAD_FIELDS																\
		CP_MODULE_FIELDS																\




/************************************************************************/
/*                                                                      */
/************************************************************************/
struct cp_thread_s {
	CP_THREAD_FIELDS												/*表示时间模块信息*/
};


#pragma pack()




/************************************************************************/
/*线程的几个功能方法                                                     */
/************************************************************************/
cp_thread_t* cp_create_thread(const cp_app_t *app, cp_thread_cb entry, cp_void_t* arg);
cp_int32_t cp_destroy_thread(cp_thread_t *tid);
//cp_thread_t cp_thread_self();
cp_int32_t cp_thread_join(cp_thread_t *tid);
cp_int32_t cp_thread_equal(const cp_thread_t *t1, const cp_thread_t *t2);


#endif


