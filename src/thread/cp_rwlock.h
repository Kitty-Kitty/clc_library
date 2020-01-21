/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/

#ifndef	_CP_RWLOCK_INCLUDE_H_
#define _CP_RWLOCK_INCLUDE_H_



#include "uv.h"



typedef uv_rwlock_t						cp_rwlock_t;



int cp_rwlock_init(cp_rwlock_t* rwlock);
void cp_rwlock_destroy(cp_rwlock_t* rwlock);
void cp_rwlock_rdlock(cp_rwlock_t* rwlock);
int cp_rwlock_tryrdlock(cp_rwlock_t* rwlock);
void cp_rwlock_rdunlock(cp_rwlock_t* rwlock);
void cp_rwlock_wrlock(cp_rwlock_t* rwlock);
int cp_rwlock_trywrlock(cp_rwlock_t* rwlock);
void cp_rwlock_wrunlock(cp_rwlock_t* rwlock);



#endif

