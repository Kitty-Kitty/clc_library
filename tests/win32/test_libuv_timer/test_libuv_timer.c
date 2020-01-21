#include <assert.h>
#include "uv.h"

static void timer_cb(uv_timer_t *handle, int status)
{
	static int count;
	printf("count %d now %d\n", count++, time(NULL));
}

int main()
{
	int r;
	uv_timer_t timer;
	r = uv_timer_init(uv_default_loop(), &timer);
	assert(r == 0);

	assert(!uv_is_active((uv_handle_t *)&timer));
	assert(!uv_is_closing((uv_handle_t *)&timer));
	printf("start %d\n", time(NULL));
	r = uv_timer_start(&timer, timer_cb, 1000, 1000);
	r = uv_run(uv_default_loop(), UV_RUN_DEFAULT);
	assert(r == 0);

	return 0;
}