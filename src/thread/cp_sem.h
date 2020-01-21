/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/

#ifndef	_CP_SEM_INCLUDE_H_
#define _CP_SEM_INCLUDE_H_


#include "uv.h"


typedef uv_sem_t						cp_sem_t;



int cp_sem_init(cp_sem_t* sem, unsigned int value);
void cp_sem_destroy(cp_sem_t* sem);
void cp_sem_post(cp_sem_t* sem);
void cp_sem_wait(cp_sem_t* sem);
int cp_sem_trywait(cp_sem_t* sem);



#endif

