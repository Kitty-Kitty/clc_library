/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-11-28

Description:

**************************************************************************/
#include "cp_fusion_player_socket_data.h"


//初始化socket data
cp_int32_t	init_socket_data(cp_void_t *socket_data_p);
cp_int32_t	init_semh_socket_data(cp_semh_socket_data_t *socket_data_p);
cp_int32_t	init_memh_socket_data(cp_memh_socket_data_t *socket_data_p);

cp_socket_buffer_data_t* create_a_socket_buffer(cp_pool_t *pool, cp_int32_t size);
cp_socket_buffer_data_t* get_a_socket_buffer(cp_pool_t *pool, cp_void_t *socket_data_p, cp_int32_t size);


cp_void_t* create_socket_data(cp_pool_t *pool, cp_socket_data_type_e type)
{
	cp_void_t					*tmp_p = CP_NULL;


	if (!pool) {
		return CP_NULL;
	}

	switch (type)
	{
	case cp_socket_data_semh:
	{
		tmp_p = cp_palloc(pool, cp_sizeof(cp_semh_socket_data_t));
		if (!tmp_p) {
			return CP_NULL;
		}
		cp_memset(tmp_p, 0, cp_sizeof(cp_semh_socket_data_t));
	}
	break;
	case cp_socket_data_memh:
	{
		tmp_p = cp_palloc(pool, cp_sizeof(cp_memh_socket_data_t));
		if (!tmp_p) {
			return CP_NULL;
		}
		cp_memset(tmp_p, 0, cp_sizeof(cp_memh_socket_data_t));
	}
	break;
	default:
		return CP_NULL;
		break;
	}

	((cp_css_socket_data_t*)tmp_p)->type = type;

	//初始化socket data
	if (tmp_p && init_socket_data(tmp_p)) {
		cp_pfree(pool, tmp_p);
		return CP_NULL;
	}

	return tmp_p;
}

cp_semh_socket_data_t*	create_semh_socket_data(cp_pool_t *pool)
{
	return create_socket_data(pool, cp_socket_data_semh);
}

cp_memh_socket_data_t*	create_memh_socket_data(cp_pool_t *pool)
{
	return create_socket_data(pool, cp_socket_data_memh);
}

cp_int32_t destroy_socket_data(cp_pool_t *pool, cp_void_t *socket_data)
{
	if (!pool || !socket_data) {
		return -1;
	}

	switch (((cp_css_socket_data_t*)socket_data)->type)
	{
	case cp_socket_data_semh:
	case cp_socket_data_memh:
	{
		cp_destroy_safe_queue(((cp_css_socket_data_t*)socket_data)->cache_sq);
		cp_destroy_safe_queue(((cp_css_socket_data_t*)socket_data)->data_sq);
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
	switch (((cp_css_socket_data_t*)socket_data_p)->type)
	{
	case cp_socket_data_semh:
	{
		return init_semh_socket_data((cp_semh_socket_data_t*)socket_data_p);
	}
	break;
	case cp_socket_data_memh:
	{
		return init_memh_socket_data((cp_memh_socket_data_t*)socket_data_p);
	}
	break;
	default:
		break;
	}

	return -2;
}

cp_int32_t	init_css_socket_data(cp_css_socket_data_t *socket_data_p)
{
	int								tmp_queue_bound_size = CP_FUSION_PLAYER_SOCKET_DATA_QUEUE_LENGTH;



	if (!socket_data_p) {
		return -1;
	}

	cp_memset(socket_data_p, 0, cp_sizeof(cp_css_socket_data_t));
	socket_data_p->type = cp_socket_data_semh;
	socket_data_p->cache_sq = cp_create_general_safe_queue(cp_safe_queue_mode_qbss, tmp_queue_bound_size);
	socket_data_p->data_sq = cp_create_general_safe_queue(cp_safe_queue_mode_qbss, tmp_queue_bound_size);

	return 0;
}

cp_int32_t	init_semh_socket_data(cp_semh_socket_data_t *socket_data_p)
{
	return init_css_socket_data((cp_css_socket_data_t*)socket_data_p);
}

cp_int32_t	init_memh_socket_data(cp_memh_socket_data_t *socket_data_p)
{
	if (init_css_socket_data((cp_css_socket_data_t*)socket_data_p)) {
		return -1;
	}

	cp_min_heap_init(&socket_data_p->data_mh);

	return 0;
}

cp_socket_buffer_data_t* create_a_socket_buffer(cp_pool_t *pool, cp_int32_t size)
{
	cp_void_t						*tmp_p = CP_NULL;


	if (!pool) {
		return CP_NULL;
	}
	tmp_p = cp_palloc(pool, cp_sizeof(cp_socket_buffer_data_t) + size);
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

	return (cp_socket_buffer_data_t*)tmp_p;
}

cp_socket_buffer_data_t* get_a_socket_buffer(cp_pool_t *pool, cp_void_t *socket_data_p, cp_int32_t size)
{
	return CP_NULL;
}

cp_buf_t* create_a_semh_socket_buffer(cp_pool_t *pool, cp_semh_socket_data_t *ssd, cp_int32_t size)
{
	cp_socket_buffer_data_t						*tmp_sbd = CP_NULL;


	tmp_sbd = create_a_socket_buffer(pool, size);
	if (!tmp_sbd) {
		return CP_NULL;
	}
	else {
		tmp_sbd->mh_elemn.sbd = tmp_sbd;
	}

	return &tmp_sbd->buf;
}

cp_buf_t* create_a_memh_socket_buffer(cp_pool_t *pool, cp_memh_socket_data_t *msd, cp_int32_t size)
{
	cp_socket_buffer_data_t						*tmp_sbd = CP_NULL;


	tmp_sbd = create_a_socket_buffer(pool, size);
	if (!tmp_sbd) {
		return CP_NULL;
	}
	else {
		tmp_sbd->mh_elemn.sbd = tmp_sbd;
	}

	return &tmp_sbd->buf;
}

cp_int32_t destroy_a_semh_socket_buffer(cp_pool_t *pool, cp_semh_socket_data_t *ssd, cp_buf_t *buf)
{
	cp_socket_buffer_data_t						*tmp_sbd = CP_NULL;



	if (!ssd || !buf) {
		return -1;
	}

	tmp_sbd = (cp_socket_buffer_data_t*)(((cp_char_t*)buf) - cp_offsetof(cp_socket_buffer_data_t, buf));
	if (!tmp_sbd) {
		return -1;
	}
	cp_pfree(pool, tmp_sbd);
	return 0;
}

cp_int32_t destroy_a_memh_socket_buffer(cp_pool_t *pool, cp_memh_socket_data_t *ssd, cp_buf_t *buf)
{
	cp_socket_buffer_data_t						*tmp_sbd = CP_NULL;



	if (!ssd || !buf) {
		return -1;
	}

	tmp_sbd = (cp_socket_buffer_data_t*)(((cp_char_t*)buf) - cp_offsetof(cp_socket_buffer_data_t, buf));
	if (!tmp_sbd) {
		return -1;
	}
	cp_pfree(pool, tmp_sbd);
	return 0;
}

cp_int32_t push_a_semh_socket_buffer(cp_semh_socket_data_t *ssd, cp_buf_t *buf)
{
	cp_socket_buffer_data_t						*tmp_sbd = CP_NULL;



	if (!ssd || !buf) {
		return -1;
	}

	tmp_sbd = (cp_socket_buffer_data_t*)(((cp_char_t*)buf) - cp_offsetof(cp_socket_buffer_data_t, buf));
	if (!tmp_sbd) {
		return -2;
	}
	
	ssd->sd.length += cp_buf_get_length(buf);
	cp_safe_queue_push(ssd->sd.data_sq, tmp_sbd);

	return 0;
}

cp_int32_t push_a_memh_socket_buffer(cp_memh_socket_data_t *msd, cp_buf_t *buf)
{
	cp_socket_buffer_data_t						*tmp_sbd = CP_NULL;


	if (!msd || !buf) {
		return -1;
	}

	tmp_sbd = (cp_socket_buffer_data_t*)(((cp_char_t*)buf) - cp_offsetof(cp_socket_buffer_data_t, buf));
	if (!tmp_sbd) {
		return -1;
	}

	//tmp_sbd->mh_elemn.sbd = tmp_sbd;
	msd->sd.length += cp_buf_get_length(buf);
	cp_safe_queue_push(msd->sd.data_sq, tmp_sbd);

	return 0;
}

cp_buf_t* pop_a_semh_socket_buffer(cp_semh_socket_data_t *ssd)
{
	cp_socket_buffer_data_t						*tmp_sbd = CP_NULL;



	if (!ssd) {
		return CP_NULL;
	}

	tmp_sbd = cp_safe_queue_pop(ssd->sd.data_sq);
	if (!tmp_sbd) {
		return CP_NULL;
	}

	ssd->sd.length -= cp_buf_get_length(&tmp_sbd->buf);
	return &tmp_sbd->buf;
}

cp_buf_t* pop_a_memh_socket_buffer(cp_memh_socket_data_t *msd)
{
	cp_socket_buffer_data_t						*tmp_sbd = CP_NULL;



	if (!msd) {
		return CP_NULL;
	}

	tmp_sbd = cp_safe_queue_pop(msd->sd.data_sq);
	if (!tmp_sbd) {
		return CP_NULL;
	}

	msd->sd.length -= cp_buf_get_length(&tmp_sbd->buf);
	return &tmp_sbd->buf;
}

cp_int64_t get_semh_socket_buffer_length(cp_semh_socket_data_t *ssd)
{
	return ssd->sd.length;
}

cp_int64_t get_memh_socket_buffer_length(cp_memh_socket_data_t *msd)
{
	return msd->sd.length;
}

cp_func_t *get_memh_socket_buffer_func(cp_memh_socket_data_t *msd)
{
	if (!msd || !msd->sd.data) {
		return CP_NULL;
	}

	return (cp_func_t *)(msd->sd.data);
}

cp_int32_t set_memh_socket_buffer_func(cp_memh_socket_data_t *msd, cp_func_t *func)
{
	if (!msd || !func) {
		return -1;
	}

	msd->sd.data = func;
	msd->sd.module_type = func->register_info.type;
	return 0;
}