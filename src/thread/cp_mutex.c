#include "cp_mutex.h"

int cp_mutex_init(cp_mutex_t* handle)
{
	return uv_mutex_init(handle);
}

void cp_mutex_destroy(cp_mutex_t* handle)
{
	uv_mutex_unlock(handle);
	uv_mutex_destroy(handle);
}

void cp_mutex_lock(cp_mutex_t* handle)
{
	uv_mutex_lock(handle);
}

int cp_mutex_trylock(cp_mutex_t* handle)
{
	return uv_mutex_trylock(handle);
}

void cp_mutex_unlock(cp_mutex_t* handle)
{
	uv_mutex_unlock(handle);
}



int cp_cond_init(cp_cond_t* cond)
{
	return uv_cond_init(cond);
}

void cp_cond_destroy(cp_cond_t* cond)
{
	uv_cond_destroy(cond);
}

void cp_cond_signal(cp_cond_t* cond)
{
	uv_cond_signal(cond);
}

void cp_cond_broadcast(cp_cond_t* cond)
{
	uv_cond_broadcast(cond);
}

void cp_cond_wait(cp_cond_t* cond, cp_mutex_t* mutex)
{
	uv_cond_wait(cond, mutex);
}

int cp_cond_timedwait(cp_cond_t* cond,
	cp_mutex_t* mutex,
	uint64_t timeout)
{
	return uv_cond_timedwait(cond, mutex, timeout);
}






