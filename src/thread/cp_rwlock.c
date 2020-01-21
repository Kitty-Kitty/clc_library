
#include "cp_rwlock.h"




int cp_rwlock_init(cp_rwlock_t* rwlock)
{
	return uv_rwlock_init(rwlock);
}

void cp_rwlock_destroy(cp_rwlock_t* rwlock)
{
	uv_rwlock_destroy(rwlock);
}

void cp_rwlock_rdlock(cp_rwlock_t* rwlock)
{
	uv_rwlock_rdlock(rwlock);
}

int cp_rwlock_tryrdlock(cp_rwlock_t* rwlock)
{
	return uv_rwlock_tryrdlock(rwlock);
}

void cp_rwlock_rdunlock(cp_rwlock_t* rwlock)
{
	uv_rwlock_rdunlock(rwlock);
}

void cp_rwlock_wrlock(cp_rwlock_t* rwlock)
{
	uv_rwlock_wrlock(rwlock);
}

int cp_rwlock_trywrlock(cp_rwlock_t* rwlock)
{
	return uv_rwlock_trywrlock(rwlock);
}

void cp_rwlock_wrunlock(cp_rwlock_t* rwlock)
{
	uv_rwlock_wrunlock(rwlock);
}





