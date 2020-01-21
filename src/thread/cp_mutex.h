/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/

#ifndef	_CP_MUTEX_INCLUDE_H_
#define _CP_MUTEX_INCLUDE_H_



#include "uv.h"



typedef uv_mutex_t						cp_mutex_t;
typedef uv_cond_t						cp_cond_t;



// #define cp_mutex_init(handle)		uv_mutex_init((cp_mutex_t*) handle)
// #define cp_mutex_destroy(handle)		uv_mutex_destroy((cp_mutex_t*) handle)
// #define cp_mutex_lock(handle)		uv_mutex_lock((cp_mutex_t*) handle)
// #define cp_mutex_trylock(handle)		uv_mutex_trylock((cp_mutex_t*) handle)
// #define cp_mutex_unlock(handle)		uv_mutex_unlock((cp_mutex_t*) handle)


int cp_mutex_init(cp_mutex_t* handle);
void cp_mutex_destroy(cp_mutex_t* handle);
void cp_mutex_lock(cp_mutex_t* handle);
int cp_mutex_trylock(cp_mutex_t* handle);
void cp_mutex_unlock(cp_mutex_t* handle);



int cp_cond_init(cp_cond_t* cond);
void cp_cond_destroy(cp_cond_t* cond);
void cp_cond_signal(cp_cond_t* cond);
void cp_cond_broadcast(cp_cond_t* cond);
void cp_cond_wait(cp_cond_t* cond, cp_mutex_t* mutex);
int cp_cond_timedwait(cp_cond_t* cond,
	cp_mutex_t* mutex,
	uint64_t timeout);



#endif

