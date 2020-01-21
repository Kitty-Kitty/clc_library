/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-11-28

Description:

**************************************************************************/
#include "cp_ecam_socket_data.h"


//#define			CP_USED_POOL_MEMORY							1



//初始化socket data
cp_int32_t	init_socket_data(cp_void_t *socket_data_p);
cp_int32_t	init_rtp_socket_data(cp_rtp_socket_data_t *socket_data_p);

cp_socket_buffer_data_t* create_a_socket_buffer(cp_pool_t *pool, cp_int32_t size);


cp_void_t* create_socket_data(cp_pool_t *pool, cp_socket_data_type_e type)
{
	cp_void_t					*tmp_p = CP_NULL;


	if (!pool) {
		return CP_NULL;
	}

	switch (type)
	{
	case cp_socket_data_rtp:
	{
		tmp_p = cp_palloc(pool, cp_sizeof(cp_rtp_socket_data_t));
		if (!tmp_p) {
			return CP_NULL;
		}
		//cp_memset(tmp_p, 0, cp_sizeof(cp_rtp_socket_data_t));
		((cp_rtp_socket_data_t*)tmp_p)->type = cp_socket_data_rtp;
	}
	break;
	default:
		return CP_NULL;
		break;
	}

	//初始化socket data
	if (tmp_p && init_socket_data(tmp_p)) {
		cp_pfree(pool, tmp_p);
		return CP_NULL;
	}

	return tmp_p;
}

cp_rtp_socket_data_t*	create_rtp_socket_data(cp_pool_t *pool)
{
	return create_socket_data(pool, cp_socket_data_rtp);
}

cp_int32_t destroy_socket_data(cp_pool_t *pool, cp_void_t *socket_data)
{
	if (!pool || !socket_data) {
		return -1;
	}

	switch (((cp_rtp_socket_data_t*)socket_data)->type)
	{
	case cp_socket_data_rtp:
	{
		cp_lockfree_queue_destroy(&((cp_rtp_socket_data_t*)socket_data)->cache_lq);
		cp_lockfree_queue_destroy(&((cp_rtp_socket_data_t*)socket_data)->data_lq);
	}
	break;
	default:
		break;
	}

	cp_pfree(pool, socket_data);
	return 0;
}


cp_int32_t	init_socket_data(cp_void_t *socket_data_p)
{
	if (!socket_data_p) {
		return -1;
	}
	switch (((cp_rtp_socket_data_t*)socket_data_p)->type)
	{
	case cp_socket_data_rtp:
	{
		return init_rtp_socket_data((cp_rtp_socket_data_t*)socket_data_p);
	}
	break;
	default:
		break;
	}

	return -2;
}

cp_int32_t	init_rtp_socket_data(cp_rtp_socket_data_t *socket_data_p)
{
	int								tmp_queue_bound_size = CP_ECAM_SOCKET_DATA_QUEUE_LENGTH;



	if (!socket_data_p) {
		return -1;
	}
	cp_memset(socket_data_p, 0, cp_sizeof(cp_rtp_socket_data_t));
	socket_data_p->type = cp_socket_data_rtp;
	cp_lockfree_queue_init(&socket_data_p->cache_lq, cp_lockfree_queue_mode_qbss);
	cp_lockfree_queue_init(&socket_data_p->data_lq, cp_lockfree_queue_mode_qbss);

	cp_lockfree_queue_set_option(&socket_data_p->cache_lq, cp_lockfree_queue_option_bounded, &tmp_queue_bound_size);
	cp_lockfree_queue_set_option(&socket_data_p->data_lq, cp_lockfree_queue_option_bounded, &tmp_queue_bound_size);

	cp_lockfree_queue_start(&socket_data_p->cache_lq);
	cp_lockfree_queue_start(&socket_data_p->data_lq);

	return 0;
}

cp_socket_buffer_data_t* create_a_socket_buffer(cp_pool_t *pool, cp_int32_t size)
{
	cp_void_t						*tmp_p = CP_NULL;


	if (!pool) {
		return CP_NULL;
	}
#if defined(CP_USED_POOL_MEMORY)
	tmp_p = cp_palloc(pool, cp_sizeof(cp_socket_buffer_data_t) + size);
#else
	tmp_p = cp_malloc(cp_sizeof(cp_socket_buffer_data_t) + size);
#endif
	if (!tmp_p) {
		return CP_NULL;
	}
	cp_memset(tmp_p, 0, cp_sizeof(cp_socket_buffer_data_t) + size);
	/************************************************************************/
	/* 这里内存模型：                                                        */
	/* |cp_socket_buffer_data_t| data buffer|								*/
	/* |cp_socket_buffer_data_t|中buf指向data buffer							*/
	/************************************************************************/
	cp_buf_assemble((&((cp_socket_buffer_data_t*)tmp_p)->buf),
		(((cp_char_t*)tmp_p) + cp_sizeof(cp_socket_buffer_data_t)),
		size);

	//printf("create_a_socket_buffer() [%d] 0x%x\r\n", (cp_sizeof(cp_socket_buffer_data_t) + size), tmp_p);
	return (cp_socket_buffer_data_t*)tmp_p;
}

cp_buf_t* create_a_rtp_socket_buffer(cp_pool_t *pool, cp_rtp_socket_data_t *ssd, cp_int32_t size)
{
	cp_socket_buffer_data_t						*tmp_sbd = CP_NULL;


	tmp_sbd = create_a_socket_buffer(pool, size);
	if (!tmp_sbd) {
		return CP_NULL;
	}

	return &tmp_sbd->buf;
}

cp_int32_t destroy_a_rtp_socket_buffer(cp_pool_t *pool, cp_rtp_socket_data_t *ssd, cp_buf_t *buf)
{
	cp_socket_buffer_data_t						*tmp_sbd = CP_NULL;



	if (!ssd || !buf) {
		return -1;
	}

	tmp_sbd = (cp_socket_buffer_data_t*)(((cp_char_t*)buf) - cp_offsetof(cp_socket_buffer_data_t, buf));
	if (!tmp_sbd) {
		return -1;
	}
	//printf("destroy_a_rtp_socket_buffer() 0x%x\r\n", tmp_sbd);
#if defined(CP_USED_POOL_MEMORY)
	cp_pfree(pool, tmp_sbd);
#else
	cp_free(tmp_sbd);
#endif
	return 0;
}

cp_int32_t push_a_rtp_socket_buffer(cp_rtp_socket_data_t *ssd, cp_buf_t *buf)
{
	cp_socket_buffer_data_t						*tmp_sbd = CP_NULL;


	if (!ssd || !buf) {
		return -1;
	}

	tmp_sbd = (cp_socket_buffer_data_t*)(((cp_char_t*)buf) - cp_offsetof(cp_socket_buffer_data_t, buf));
	if (!tmp_sbd) {
		return -1;
	}

	ssd->length += cp_buf_get_length(buf);
	cp_lockfree_queue_element_init(&ssd->data_lq, (cp_lockfree_queue_element_t*)tmp_sbd, tmp_sbd, tmp_sbd);
	cp_lockfree_queue_push(&ssd->data_lq, (cp_lockfree_queue_element_t*)tmp_sbd, 0, CP_NULL);
	return 0;
}

cp_buf_t* pop_a_rtp_socket_buffer(cp_rtp_socket_data_t *ssd)
{
	cp_lockfree_queue_element_t					*lq_elem = CP_NULL;
	cp_socket_buffer_data_t						*tmp_sbd = CP_NULL;


	if (!ssd) {
		return CP_NULL;
	}

	if (cp_lockfree_queue_pop(&ssd->data_lq, &lq_elem)) {
		return CP_NULL;
	}

	if (!lq_elem || !lq_elem->value) {
		return CP_NULL;
	}
	tmp_sbd = (cp_socket_buffer_data_t*)(lq_elem->value);
	ssd->length -= cp_buf_get_length(&tmp_sbd->buf);

	return &tmp_sbd->buf;
}

cp_int64_t get_rtp_socket_buffer_length(cp_rtp_socket_data_t *ssd)
{
	return ssd->length;
}
