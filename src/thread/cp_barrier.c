
#include "cp_barrier.h"



int cp_barrier_init(cp_barrier_t* barrier, unsigned int count)
{
	return uv_barrier_init(barrier, count);
}

void cp_barrier_destroy(cp_barrier_t* barrier)
{
	uv_barrier_destroy(barrier);
}

int cp_barrier_wait(cp_barrier_t* barrier)
{
	return uv_barrier_wait(barrier);
}





