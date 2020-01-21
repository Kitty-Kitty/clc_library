/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/

#ifndef	_CP_BARRIER_INCLUDE_H_
#define _CP_BARRIER_INCLUDE_H_


#include "uv.h"




typedef uv_barrier_t						cp_barrier_t;




int cp_barrier_init(cp_barrier_t* barrier, unsigned int count);
void cp_barrier_destroy(cp_barrier_t* barrier);
int cp_barrier_wait(cp_barrier_t* barrier);






#endif

