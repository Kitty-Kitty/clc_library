/**************************************************************************

* Copyright: novigo

* Author: tianhuiming@novigo.com.cn

* Date£º2016-4-27
        
* Description:

**************************************************************************/


#ifndef	_CP_ATOMIC_INCLUDE_H_
#define _CP_ATOMIC_INCLUDE_H_


#if defined(WIN32)
typedef		volatile int				cp_atomic_t;
typedef		volatile __int64			cp_atomic64_t;
#else
//typedef	atomic_t					cp_atomic_t;
//typedef	atomic64_t					cp_atomic64_t;
typedef		volatile int				cp_atomic_t;
typedef		volatile long long			cp_atomic64_t;
#endif


void atomic_read(cp_atomic_t*v);
void atomic_set(cp_atomic_t*v, int i);
void atomic_add(int i, cp_atomic_t* v);
void atomic_sub(int i, cp_atomic_t* v);
int atomic_sub_and_test(int i, cp_atomic_t* v);
void atomic_inc(cp_atomic_t* v);
void atomic_dec(cp_atomic_t* v);
int atomic_dec_and_test(cp_atomic_t* v);
int atomic_inc_and_test(cp_atomic_t* v);
int atomic_add_negative(int i, cp_atomic_t* v);





#endif