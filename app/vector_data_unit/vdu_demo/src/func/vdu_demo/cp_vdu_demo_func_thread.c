/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-11-29

Description:

**************************************************************************/
#include "cp_vdu_demo_func_thread.h"




/************************************************************************/
/* 处理线程管理器的                                                      */
/************************************************************************/
cp_vdu_demo_func_thread_manager_t* create_vdu_demo_func_thread_manager(cp_func_t *func);
cp_int32_t init_vdu_demo_func_thread_manager(cp_vdu_demo_func_thread_manager_t *dftm);
cp_int32_t start_vdu_demo_func_thread_manager(cp_vdu_demo_func_thread_manager_t *dftm);
cp_int32_t stop_vdu_demo_func_thread_manager(cp_vdu_demo_func_thread_manager_t *dftm);
cp_int32_t destroy_vdu_demo_func_thread_manager(cp_vdu_demo_func_thread_manager_t *dftm);

/************************************************************************/
/* 处理线程的                                                            */
/************************************************************************/
cp_vdu_demo_func_thread_t* create_vdu_demo_func_thread(cp_vdu_demo_func_thread_manager_t *dftm);
cp_int32_t init_vdu_demo_func_thread(cp_vdu_demo_func_thread_t *dft);
cp_int32_t start_vdu_demo_func_thread(cp_vdu_demo_func_thread_t *dft, cp_vdu_demo_func_thread_cb pft_cb);
cp_int32_t stop_vdu_demo_func_thread(cp_vdu_demo_func_thread_t *dft);
cp_int32_t destroy_vdu_demo_func_thread(cp_vdu_demo_func_thread_t *dft);

/************************************************************************/
/* 线程处理                                                          */
/************************************************************************/
cp_int32_t proc_vdu_demo_func_chunk(cp_vdu_demo_func_thread_t* dft, cp_vdu_demo_func_chunk_t *pfc);

/************************************************************************/
/* 默认的处理                                                            */
/************************************************************************/
void cp_vdu_demo_func_thread_cb_proc(cp_vdu_demo_func_thread_t* dft);

cp_vdu_demo_func_chunk_t* create_semh_vdu_demo_func_chunk(cp_vdu_demo_func_thread_manager_t *dftm, cp_int32_t size);
cp_int32_t destroy_semh_vdu_demo_func_chunk(cp_vdu_demo_func_thread_manager_t *dftm, cp_vdu_demo_func_chunk_t *pfc);
cp_vdu_demo_func_chunk_t* make_semh_vdu_demo_func_chunk(cp_vdu_demo_func_thread_manager_t *dftm, cp_socket_t *socket, gmp_gmph_semh_t *semh);


cp_vdu_demo_func_thread_manager_t* create_vdu_demo_func_thread_manager(cp_func_t *func)
{
	cp_vdu_demo_func_thread_manager_t				*tmp_pftm = CP_NULL;



	if (!func) {
		return CP_NULL;
	}

	//创建一个manager
	tmp_pftm = cp_palloc(func->pool, cp_sizeof(cp_vdu_demo_func_thread_manager_t));
	if (!tmp_pftm) {
		cp_module_log(error, func, "create_vdu_demo_func_thread_manager() error. cp_palloc() size[%d] failed!",
			cp_sizeof(cp_vdu_demo_func_thread_manager_t));
		return CP_NULL;
	}
	cp_memset(tmp_pftm, 0, cp_sizeof(cp_vdu_demo_func_thread_manager_t));

	//创建pool内容
	tmp_pftm->pool = cp_create_pool(func->manager->app);
	if (!tmp_pftm->pool) {
		cp_pfree(func->pool, tmp_pftm);
		cp_module_log(error, func, "create_vdu_demo_func_thread_manager() error. cp_create_pool() failed!");
		return CP_NULL;
	}
	tmp_pftm->func = func;
	return tmp_pftm;
}

cp_int32_t init_vdu_demo_func_thread_manager(cp_vdu_demo_func_thread_manager_t *dftm)
{
	cp_int32_t						tmp_ret_int = 0;
	cp_int64_t						tmp_interval_ns = 0;
	cp_void_t						*tmp_p = CP_NULL;
	cp_int32_t						tmp_queue_bound_size = CP_VDU_DEMO_FUNC_DEFAULT_QUEUE_SIZE;


	if (!dftm) {
		return -1;
	}

	//获取配处理间隔
	tmp_interval_ns = cp_conf_xml_gettime_ns(dftm->func->manager->conf->conf_xml, 
		CP_VDU_DEMO_CONF_STRING_FUNC_CONFIGURE, CP_VDU_DEMO_CONF_STRING_THREAD_INTERVAL, 0);
	if (tmp_interval_ns <= 0) {
		cp_pftm_log(warn, dftm, 
			"init_vdu_demo_func_thread_manager() warning. cp_conf_xml_gettime_ns() element[%s : %s] value[%d ns] failed! used default[%d ms]",
			CP_VDU_DEMO_CONF_STRING_FUNC_CONFIGURE,
			CP_VDU_DEMO_CONF_STRING_THREAD_INTERVAL,
			tmp_interval_ns,
			CP_VDU_DEMO_FUNC_DEFAULT_INTERVAL_MS);
		tmp_interval_ns = CP_VDU_DEMO_FUNC_DEFAULT_INTERVAL_MS * CP_CONF_XML_TIME_THOUND * CP_CONF_XML_TIME_THOUND;
	}
	dftm->interval_ms = tmp_interval_ns / (CP_CONF_XML_TIME_THOUND * CP_CONF_XML_TIME_THOUND);
	if (dftm->interval_ms <= 0) {
		cp_pftm_log(warn, dftm,
			"init_vdu_demo_func_thread_manager() warning. cp_conf_xml_gettime_ns() element[%s : %s] value[%d ms] too small! used default[%d ms]",
			CP_VDU_DEMO_CONF_STRING_FUNC_CONFIGURE,
			CP_VDU_DEMO_CONF_STRING_THREAD_INTERVAL,
			dftm->interval_ms,
			CP_VDU_DEMO_FUNC_DEFAULT_INTERVAL_MS);
		dftm->interval_ms = CP_VDU_DEMO_FUNC_DEFAULT_INTERVAL_MS;
	}

	//获取线程数量
	dftm->thread_number = cp_conf_xml_getint(dftm->func->manager->conf->conf_xml,
		CP_VDU_DEMO_CONF_STRING_FUNC_CONFIGURE, CP_VDU_DEMO_CONF_STRING_THREAD_NUMBER, 0);
	if (dftm->thread_number <= 0) {
		cp_pftm_log(warn, dftm,
			"init_vdu_demo_func_thread_manager() error. cp_conf_xml_gettime_ns() element[%s : %s] value[%d] failed! used default[%d]",
			CP_VDU_DEMO_CONF_STRING_FUNC_CONFIGURE,
			CP_VDU_DEMO_CONF_STRING_THREAD_NUMBER,
			dftm->thread_number,
			CP_VDU_DEMO_FUNC_DEFAULT_THREAD_NUMBER);
		dftm->thread_number = CP_VDU_DEMO_FUNC_DEFAULT_THREAD_NUMBER;
	}

	//创
	tmp_p = cp_palloc(dftm->pool, cp_sizeof(cp_vdu_demo_func_thread_t*) * dftm->thread_number);
	if (!tmp_p) {
		cp_pftm_log(error, dftm, "init_vdu_demo_func_thread_manager() error. cp_palloc() size[%d] failed!", 
			cp_sizeof(cp_vdu_demo_func_thread_t*) * dftm->thread_number);
		return -2;
	}
	cp_array_init(&dftm->thread_group, tmp_p, cp_sizeof(cp_vdu_demo_func_thread_t*), dftm->thread_number);
	
	//初始化队列
	if (cp_lockfree_queue_init(&dftm->lq, cp_lockfree_queue_mode_qbss)) {
		cp_pftm_log(error, dftm, "init_vdu_demo_func_thread_manager() error. cp_lockfree_queue_init() failed!");
		return -3;
	}
	else {
		//启动队列
		cp_lockfree_queue_set_option(&dftm->lq, cp_lockfree_queue_option_bounded, &tmp_queue_bound_size);
		cp_lockfree_queue_start(&dftm->lq);
	}

	//初始化请
	tmp_ret_int = cp_mutex_init(&dftm->pfc_mutex);
	if (tmp_ret_int) {
		cp_pftm_log(error, dftm, "init_vdu_demo_func_thread_manager() error. cp_mutex_init() (pfc_mutex) failed!");
		return -3;
	}

	//初始化请
	tmp_ret_int = cp_mutex_init(&dftm->pool_mutex);
	if (tmp_ret_int) {
		cp_pftm_log(error, dftm, "init_vdu_demo_func_thread_manager() error. cp_mutex_init() (pool_mutex) failed!");
		return -3;
	}

	return 0;
}

cp_int32_t start_vdu_demo_func_thread_manager(cp_vdu_demo_func_thread_manager_t *dftm)
{
	return 0;
}

cp_int32_t stop_vdu_demo_func_thread_manager(cp_vdu_demo_func_thread_manager_t *dftm)
{
	cp_int32_t								i = 0;
	cp_int32_t								ret_int = 0;
	cp_vdu_demo_func_thread_t					**tmp_pft = CP_NULL;


	for (i = 0; i < (cp_int32_t)cp_array_max_size(&dftm->thread_group); i++) {
		tmp_pft = (cp_vdu_demo_func_thread_t**)cp_array_get(&dftm->thread_group, i);
		if (!*tmp_pft) {
			continue;
		}
		ret_int = stop_vdu_demo_func_thread(*tmp_pft);
		if (ret_int) {
			cp_pftm_log(error, dftm, "stop_vdu_demo_func_thread() error. index[%d] thread[%p]!",
				i,
				*tmp_pft);
			continue;
		}
	}
	return 0;
}

cp_int32_t destroy_vdu_demo_func_thread_manager(cp_vdu_demo_func_thread_manager_t *dftm)
{
	cp_int32_t								i = 0;
	cp_int32_t								ret_int = 0;
	cp_vdu_demo_func_thread_t					**tmp_pft = CP_NULL;



	for (i = 0; i < (cp_int32_t)cp_array_max_size(&dftm->thread_group); i++) {
		tmp_pft = (cp_vdu_demo_func_thread_t**)cp_array_get(&dftm->thread_group, i);
		if (!*tmp_pft) {
			continue;
		}
		ret_int = destroy_vdu_demo_func_thread(*tmp_pft);
		if (ret_int) {
			cp_pftm_log(error, dftm, "destroy_vdu_demo_func_thread() error. index[%d] thread[%p]!",
				i,
				*tmp_pft);
			continue;
		}
	}

	if (dftm->pool) {
		cp_destroy_pool(dftm->pool);
	}

	cp_mutex_destroy(&dftm->pfc_mutex);
	cp_mutex_destroy(&dftm->pool_mutex);
	cp_pfree(dftm->func->pool, dftm);

	return 0;
}


cp_vdu_demo_func_thread_t* create_vdu_demo_func_thread(cp_vdu_demo_func_thread_manager_t *dftm)
{
	cp_vdu_demo_func_thread_t					*tmp_pft = CP_NULL;



	if (!dftm) {
		return CP_NULL;
	}

	if (cp_array_length(&dftm->thread_group) >= cp_array_max_size(&dftm->thread_group)) {
		cp_pftm_log(error, dftm, "array(thread_group) [%d >= %d] not space to insert a new one!",
			cp_array_length(&dftm->thread_group),
			cp_array_max_size(&dftm->thread_group));
		return CP_NULL;
	}
	tmp_pft = cp_palloc(dftm->pool, cp_sizeof(cp_vdu_demo_func_thread_t));
	if (!tmp_pft) {
		cp_pftm_log(error, dftm, "cp_palloc() size[%d] failed!", cp_sizeof(cp_vdu_demo_func_thread_t*));
		return CP_NULL;
	}
	cp_memset(tmp_pft, 0, cp_sizeof(cp_vdu_demo_func_thread_t));

	tmp_pft->dftm = dftm;
	tmp_pft->interval_ms = dftm->interval_ms;
	tmp_pft->index = cp_array_length(&dftm->thread_group);
	cp_array_set(&dftm->thread_group, &tmp_pft, tmp_pft->index);

	return tmp_pft;
}

cp_int32_t init_vdu_demo_func_thread(cp_vdu_demo_func_thread_t *dft)
{
	if (!dft) {
		return -1;
	}

	dft->status = cp_vdu_demo_func_thread_status_init;
	return 0;
}

cp_int32_t start_vdu_demo_func_thread(cp_vdu_demo_func_thread_t *dft, cp_vdu_demo_func_thread_cb pft_cb)
{
	if (!dft || !pft_cb) {
		return -1;
	}

	dft->status = cp_vdu_demo_func_thread_status_start;
	dft->thread = cp_create_thread(dft->dftm->func->manager->app, pft_cb, dft);
	if (!dft->thread) {
		return -2;
	}

	return 0;
}

cp_int32_t stop_vdu_demo_func_thread(cp_vdu_demo_func_thread_t *dft)
{
	if (!dft) {
		return -1;
	}

	dft->status = cp_vdu_demo_func_thread_status_stop;
	cp_thread_join(dft->thread);

	return 0;
}

cp_int32_t destroy_vdu_demo_func_thread(cp_vdu_demo_func_thread_t *dft)
{
	if (!dft) {
		return -1;
	}

	if (!dft->thread) {
		cp_destroy_thread(dft->thread);
	}
	
	if (dft->dftm) {
		cp_array_remove(&dft->dftm->thread_group, dft->index);
		cp_pfree(dft->dftm->pool, dft);
	}

	return 0;
}

cp_vdu_demo_func_thread_manager_t* make_vdu_demo_func_thread_manager(cp_func_t *func)
{
	cp_int32_t										i = 0;
	cp_int32_t										ret_int = 0;
	cp_vdu_demo_func_thread_manager_t					*tmp_pftm = CP_NULL;
	cp_vdu_demo_func_thread_t							*tmp_pft = CP_NULL;



	if (!func) {
		return CP_NULL;
	}
	tmp_pftm = create_vdu_demo_func_thread_manager(func);
	if (!tmp_pftm) {
		cp_module_log(error, func, "create_vdu_demo_func_thread_manager() error.");
		return CP_NULL;
	}
	//初始化thread manager
	ret_int = init_vdu_demo_func_thread_manager(tmp_pftm);
	if (ret_int) {
		cp_module_log(error, func, "init_vdu_demo_func_thread_manager() error.");
		return CP_NULL;
	}
	//运行thrad manager
	ret_int = start_vdu_demo_func_thread_manager(tmp_pftm);
	if (ret_int) {
		cp_module_log(error, func, "start_vdu_demo_func_thread_manager() error.");
		return CP_NULL;
	}
	//创建各各线程
	for (i = 0; i < tmp_pftm->thread_number; i++) {
		tmp_pft = create_vdu_demo_func_thread(tmp_pftm);
		if (!tmp_pft) {
			cp_module_log(warn, func, "create_vdu_demo_func_thread() index[%d] error.", i);
			continue;
		}
		ret_int = init_vdu_demo_func_thread(tmp_pft);
		if (ret_int) {
			cp_module_log(warn, func, "init_vdu_demo_func_thread() index[%d] thread[%p] error.", 
				i, tmp_pft->thread);
			continue;
		}
		ret_int = start_vdu_demo_func_thread(tmp_pft, cp_vdu_demo_func_thread_cb_proc);
		if (ret_int) {
			cp_module_log(warn, func, "start_vdu_demo_func_thread() index[%d] thread[%p] error.",
				i, tmp_pft->thread);
			continue;
		}
	}

	return tmp_pftm;
}

cp_int32_t unmake_vdu_demo_func_thread_manager(cp_vdu_demo_func_thread_manager_t *dftm)
{
	cp_int32_t							ret_int = 0;


	ret_int = stop_vdu_demo_func_thread_manager(dftm);
	if (ret_int) {
		cp_pftm_log(error, dftm, "stop_vdu_demo_func_thread_manager() error.");
		return -1;
	}

	ret_int = destroy_vdu_demo_func_thread_manager(dftm);
	if (ret_int) {
		cp_pftm_log(error, dftm, "destroy_vdu_demo_func_thread_manager() error.");
		return -1;
	}
	return 0;
}

void cp_vdu_demo_func_thread_cb_proc(cp_vdu_demo_func_thread_t* dft)
{
	cp_vdu_demo_func_chunk_t						*tmp_dfc = CP_NULL;



	while (cp_true)
	{
		if (cp_vdu_demo_func_thread_status_start != dft->status) {
			break;
		}

		//获取完整指令
		tmp_dfc = pop_semh_vdu_demo_func_chunk(dft->dftm);
		if (!tmp_dfc) {
			cp_sleep_msec((cp_int32_t)(dft->interval_ms));
			continue;
		}
		
		//处理指令
		proc_vdu_demo_func_chunk(dft, tmp_dfc);

		//消毁指令
		destroy_semh_vdu_demo_func_chunk(dft->dftm, tmp_dfc);
	}
}

cp_vdu_demo_func_chunk_t* create_semh_vdu_demo_func_chunk(cp_vdu_demo_func_thread_manager_t *dftm, cp_int32_t size)
{
	cp_vdu_demo_func_chunk_t				*tmp_dfc = CP_NULL;


	cp_mutex_lock(&dftm->pool_mutex);
	tmp_dfc = cp_palloc(dftm->pool, cp_sizeof(cp_vdu_demo_func_chunk_t) + cp_sizeof(cp_buf_t) + size);
	if (!tmp_dfc) {
		cp_mutex_unlock(&dftm->pool_mutex);
		cp_pftm_log(warn, dftm, "create_semh_vdu_demo_func_chunk() error. cp_palloc() size[%d] failed!",
			cp_sizeof(cp_vdu_demo_func_chunk_t));
		return CP_NULL;
	}
	cp_mutex_unlock(&dftm->pool_mutex);

	tmp_dfc->buf = (cp_buf_t *)(((cp_char_t*)tmp_dfc) + cp_sizeof(cp_vdu_demo_func_chunk_t));
	tmp_dfc->nread = size;
	cp_buf_assemble(tmp_dfc->buf, ((cp_char_t*)tmp_dfc->buf) + cp_sizeof(cp_buf_t), size);

	return tmp_dfc;
}

cp_int32_t destroy_semh_vdu_demo_func_chunk(cp_vdu_demo_func_thread_manager_t *dftm, cp_vdu_demo_func_chunk_t *pfc)
{
	if (!dftm || !pfc) {
		return -1;
	}

	cp_mutex_lock(&dftm->pool_mutex);

	cp_pfree(dftm->pool, pfc);

	cp_mutex_unlock(&dftm->pool_mutex);

	return 0;
}

//
cp_vdu_demo_func_chunk_t* make_semh_vdu_demo_func_chunk(cp_vdu_demo_func_thread_manager_t *dftm, cp_socket_t *socket, gmp_gmph_semh_t *semh)
{
	cp_buf_t							*tmp_buf = CP_NULL;
	gmp_gmph_bmh_t						*tmp_bmh = CP_NULL;
	gmp_gmph_semh_t						*tmp_semh = CP_NULL;
	cp_vdu_demo_func_chunk_t				*tmp_dfc = CP_NULL;
	cp_int32_t							tmp_command_len = 0;


	if (!dftm || !socket) {
		return CP_NULL;
	}

	do{
		tmp_buf = pop_a_semh_socket_buffer(socket->data);
		if (!tmp_buf) {
			break;
		}

		//取出semh包头，判断semh最小长度
		tmp_bmh = (gmp_gmph_bmh_t*)cp_buf_get_pos(tmp_buf);
		if (gmp_gmph_emh_type_semh != tmp_bmh->emht) {
			destroy_a_semh_socket_buffer(socket->pool, socket->data, tmp_buf);
			continue;
		} else {
			//将数据
			tmp_semh = (gmp_gmph_semh_t*)tmp_bmh;
			if (tmp_semh->length <= 0) {
				destroy_a_semh_socket_buffer(socket->pool, socket->data, tmp_buf);
				continue;
			}

			if (!tmp_dfc) {
				tmp_command_len = (cp_int32_t)(CSS_GMP_GMPH_SEMH_LEN + tmp_semh->length);
				tmp_dfc = create_semh_vdu_demo_func_chunk(dftm, tmp_command_len);
				if (!tmp_dfc) {
					destroy_a_semh_socket_buffer(socket->pool, socket->data, tmp_buf);
					break;
				}
				cp_buf_strcat(tmp_dfc->buf, tmp_bmh, CSS_GMP_GMPH_SEMH_LEN);
			}
				
			if (tmp_dfc && tmp_semh->command == semh->command) {
				cp_buf_strcat(tmp_dfc->buf, ((cp_char_t*)tmp_bmh) + CSS_GMP_GMPH_SEMH_LEN, cp_buf_get_length(tmp_buf) - CSS_GMP_GMPH_SEMH_LEN);
			}
			destroy_a_semh_socket_buffer(socket->pool, socket->data, tmp_buf);
			if (cp_buf_get_length(tmp_dfc->buf) >= tmp_command_len) {
				tmp_dfc->socket = socket;
				tmp_dfc->nread = cp_buf_get_length(tmp_dfc->buf);
				tmp_dfc->status = socket->status;
				return tmp_dfc;
			}
		}
	} while (tmp_buf);

	if (tmp_dfc) {
		destroy_semh_vdu_demo_func_chunk(dftm, tmp_dfc);
	}
	
	return CP_NULL;
}

cp_int32_t push_semh_vdu_demo_func_chunk(cp_vdu_demo_func_thread_manager_t *dftm, cp_socket_t *socket, gmp_gmph_semh_t *semh)
{
	cp_vdu_demo_func_chunk_t				*tmp_dfc = CP_NULL;


	tmp_dfc = make_semh_vdu_demo_func_chunk(dftm, socket, semh);
	if (!tmp_dfc) {
		return -1;
	}

	cp_mutex_lock(&dftm->pfc_mutex);

	cp_lockfree_queue_element_init(&dftm->lq, &tmp_dfc->lq_elem, tmp_dfc, tmp_dfc);
	cp_lockfree_queue_push(&dftm->lq, &tmp_dfc->lq_elem, 0, CP_NULL);

	cp_mutex_unlock(&dftm->pfc_mutex);

	return 0;
}

cp_vdu_demo_func_chunk_t* pop_semh_vdu_demo_func_chunk(cp_vdu_demo_func_thread_manager_t *dftm)
{
	cp_vdu_demo_func_chunk_t				*tmp_dfc = CP_NULL;
	cp_lockfree_queue_element_t			*lq_elem = CP_NULL;



	cp_mutex_lock(&dftm->pfc_mutex);

	if (!cp_lockfree_queue_pop(&dftm->lq, &lq_elem) && lq_elem) {
		tmp_dfc = (cp_vdu_demo_func_chunk_t *)lq_elem->value;
	}

	cp_mutex_unlock(&dftm->pfc_mutex);

	return tmp_dfc;
}

cp_int32_t proc_vdu_demo_func_chunk(cp_vdu_demo_func_thread_t *dft, cp_vdu_demo_func_chunk_t *pfc)
{
	if (!dft || !dft->dftm || !dft->dftm->func || !pfc) {
		return -1;
	}
	
	if (dft->dftm->func->read_cb) {
		dft->dftm->func->read_cb(pfc->socket, pfc->nread, pfc->buf, pfc->status);
	}
	
	return 0;
}