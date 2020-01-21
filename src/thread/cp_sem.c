
#include "cp_sem.h"




int cp_sem_init(cp_sem_t* sem, unsigned int value)
{
	return uv_sem_init(sem, value);
}

void cp_sem_destroy(cp_sem_t* sem)
{
	uv_sem_destroy(sem);
}

void cp_sem_post(cp_sem_t* sem)
{
	uv_sem_post(sem);
}

void cp_sem_wait(cp_sem_t* sem)
{
	uv_sem_wait(sem);
}

int cp_sem_trywait(cp_sem_t* sem)
{
	return uv_sem_trywait(sem);
}



