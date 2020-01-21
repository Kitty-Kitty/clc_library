/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-11-29

Description:

**************************************************************************/
#include "cp_player_func_thread.h"




/************************************************************************/
/* 处理线程管理器的                                                      */
/************************************************************************/
cp_player_func_thread_manager_t* create_player_func_thread_manager(cp_func_t *func);
cp_int32_t init_player_func_thread_manager(cp_player_func_thread_manager_t *pftm);
cp_int32_t start_player_func_thread_manager(cp_player_func_thread_manager_t *pftm);
cp_int32_t stop_player_func_thread_manager(cp_player_func_thread_manager_t *pftm);
cp_int32_t destroy_player_func_thread_manager(cp_player_func_thread_manager_t *pftm);

/************************************************************************/
/* 处理线程的                                                            */
/************************************************************************/
cp_player_func_thread_t* create_player_func_thread(cp_player_func_thread_manager_t *pftm);
cp_int32_t init_player_func_thread(cp_player_func_thread_t *pft);
cp_int32_t start_player_func_thread(cp_player_func_thread_t *pft, cp_player_func_thread_cb pft_cb);
cp_int32_t stop_player_func_thread(cp_player_func_thread_t *pft);
cp_int32_t destroy_player_func_thread(cp_player_func_thread_t *pft);

/************************************************************************/
/* 线程处理                                                          */
/************************************************************************/
cp_int32_t proc_player_func_chunk(cp_player_func_thread_t* pft, cp_player_func_chunk_t *pfc);

/************************************************************************/
/* 默认的处理                                                            */
/************************************************************************/
void cp_player_func_thread_cb_proc(cp_player_func_thread_t* pft);

cp_player_func_chunk_t* create_semh_player_func_chunk(cp_player_func_thread_manager_t *pftm, cp_int32_t size);
cp_int32_t destroy_semh_player_func_chunk(cp_player_func_thread_manager_t *pftm, cp_player_func_chunk_t *pfc);
cp_player_func_chunk_t* make_semh_player_func_chunk(cp_player_func_thread_manager_t *pftm, cp_socket_t *socket, gmp_gmph_semh_t *semh);


cp_player_func_thread_manager_t* create_player_func_thread_manager(cp_func_t *func)
{
	cp_player_func_thread_manager_t				*tmp_pftm = CP_NULL;



	if (!func) {
		return CP_NULL;
	}

	//创建一个manager
	tmp_pftm = cp_palloc(func->pool, cp_sizeof(cp_player_func_thread_manager_t));
	if (!tmp_pftm) {
		cp_module_log(error, func, "create_player_func_thread_manager() error. cp_palloc() size[%d] failed!",
			cp_sizeof(cp_player_func_thread_manager_t));
		return CP_NULL;
	}
	cp_memset(tmp_pftm, 0, cp_sizeof(cp_player_func_thread_manager_t));

	//创建pool内容
	tmp_pftm->pool = cp_create_pool(func->manager->app);
	if (!tmp_pftm->pool) {
		cp_pfree(func->pool, tmp_pftm);
		cp_module_log(error, func, "create_player_func_thread_manager() error. cp_create_pool() failed!");
		return CP_NULL;
	}
	tmp_pftm->func = func;
	return tmp_pftm;
}

cp_int32_t init_player_func_thread_manager(cp_player_func_thread_manager_t *pftm)
{
	cp_int32_t						tmp_ret_int = 0;
	cp_int64_t						tmp_interval_ns = 0;
	cp_void_t						*tmp_p = CP_NULL;
	cp_int32_t						tmp_queue_bound_size = CP_PLAYER_FUNC_DEFAULT_QUEUE_SIZE;


	if (!pftm) {
		return -1;
	}

	//获取配处理间隔
	tmp_interval_ns = cp_conf_xml_gettime_ns(pftm->func->manager->conf->conf_xml,
		CP_PLAYER_CONF_STRING_FUNC_CONFIGURE, CP_PLAYER_CONF_STRING_THREAD_INTERVAL, 0);
	if (tmp_interval_ns <= 0) {
		cp_pftm_log(warn, pftm,
			"init_player_func_thread_manager() warning. cp_conf_xml_gettime_ns() element[%s : %s] value[%d ns] failed! used default[%d ms]",
			CP_PLAYER_CONF_STRING_FUNC_CONFIGURE,
			CP_PLAYER_CONF_STRING_THREAD_INTERVAL,
			tmp_interval_ns,
			CP_PLAYER_FUNC_DEFAULT_INTERVAL_MS);
		tmp_interval_ns = CP_PLAYER_FUNC_DEFAULT_INTERVAL_MS * CP_CONF_XML_TIME_THOUND * CP_CONF_XML_TIME_THOUND;
	}
	pftm->interval_ms = tmp_interval_ns / (CP_CONF_XML_TIME_THOUND * CP_CONF_XML_TIME_THOUND);
	if (pftm->interval_ms <= 0) {
		cp_pftm_log(warn, pftm,
			"init_player_func_thread_manager() warning. cp_conf_xml_gettime_ns() element[%s : %s] value[%d ms] too small! used default[%d ms]",
			CP_PLAYER_CONF_STRING_FUNC_CONFIGURE,
			CP_PLAYER_CONF_STRING_THREAD_INTERVAL,
			pftm->interval_ms,
			CP_PLAYER_FUNC_DEFAULT_INTERVAL_MS);
		pftm->interval_ms = CP_PLAYER_FUNC_DEFAULT_INTERVAL_MS;
	}

	//获取线程数量
	pftm->thread_number = cp_conf_xml_getint(pftm->func->manager->conf->conf_xml,
		CP_PLAYER_CONF_STRING_FUNC_CONFIGURE, CP_PLAYER_CONF_STRING_THREAD_NUMBER, 0);
	if (pftm->thread_number <= 0) {
		cp_pftm_log(warn, pftm,
			"init_player_func_thread_manager() error. cp_conf_xml_gettime_ns() element[%s : %s] value[%d] failed! used default[%d]",
			CP_PLAYER_CONF_STRING_FUNC_CONFIGURE,
			CP_PLAYER_CONF_STRING_THREAD_NUMBER,
			pftm->thread_number,
			CP_PLAYER_FUNC_DEFAULT_THREAD_NUMBER);
		pftm->thread_number = CP_PLAYER_FUNC_DEFAULT_THREAD_NUMBER;
	}

	//创
	tmp_p = cp_palloc(pftm->pool, cp_sizeof(cp_player_func_thread_t*) * pftm->thread_number);
	if (!tmp_p) {
		cp_pftm_log(error, pftm, "init_player_func_thread_manager() error. cp_palloc() size[%d] failed!",
			cp_sizeof(cp_player_func_thread_t*) * pftm->thread_number);
		return -2;
	}
	cp_array_init(&pftm->thread_group, tmp_p, cp_sizeof(cp_player_func_thread_t*), pftm->thread_number);

	//初始化队列
	if (cp_lockfree_queue_init(&pftm->lq, cp_lockfree_queue_mode_qbss)) {
		cp_pftm_log(error, pftm, "init_player_func_thread_manager() error. cp_lockfree_queue_init() failed!");
		return -3;
	}
	else {
		//启动队列
		cp_lockfree_queue_set_option(&pftm->lq, cp_lockfree_queue_option_bounded, &tmp_queue_bound_size);
		cp_lockfree_queue_start(&pftm->lq);
	}

	//初始化请
	tmp_ret_int = cp_mutex_init(&pftm->pfc_mutex);
	if (tmp_ret_int) {
		cp_pftm_log(error, pftm, "init_player_func_thread_manager() error. cp_mutex_init() (pfc_mutex) failed!");
		return -3;
	}

	//初始化请
	tmp_ret_int = cp_mutex_init(&pftm->pool_mutex);
	if (tmp_ret_int) {
		cp_pftm_log(error, pftm, "init_player_func_thread_manager() error. cp_mutex_init() (pool_mutex) failed!");
		return -3;
	}

	return 0;
}

cp_int32_t start_player_func_thread_manager(cp_player_func_thread_manager_t *pftm)
{
	return 0;
}

cp_int32_t stop_player_func_thread_manager(cp_player_func_thread_manager_t *pftm)
{
	cp_int32_t								i = 0;
	cp_int32_t								ret_int = 0;
	cp_player_func_thread_t					**tmp_pft = CP_NULL;


	for (i = 0; i < (cp_int32_t)cp_array_max_size(&pftm->thread_group); i++) {
		tmp_pft = (cp_player_func_thread_t**)cp_array_get(&pftm->thread_group, i);
		if (!*tmp_pft) {
			continue;
		}
		ret_int = stop_player_func_thread(*tmp_pft);
		if (ret_int) {
			cp_pftm_log(error, pftm, "stop_player_func_thread() error. index[%d] thread[%p]!",
				i,
				*tmp_pft);
			continue;
		}
	}
	return 0;
}

cp_int32_t destroy_player_func_thread_manager(cp_player_func_thread_manager_t *pftm)
{
	cp_int32_t								i = 0;
	cp_int32_t								ret_int = 0;
	cp_player_func_thread_t					**tmp_pft = CP_NULL;



	for (i = 0; i < (cp_int32_t)cp_array_max_size(&pftm->thread_group); i++) {
		tmp_pft = (cp_player_func_thread_t**)cp_array_get(&pftm->thread_group, i);
		if (!*tmp_pft) {
			continue;
		}
		ret_int = destroy_player_func_thread(*tmp_pft);
		if (ret_int) {
			cp_pftm_log(error, pftm, "destroy_player_func_thread() error. index[%d] thread[%p]!",
				i,
				*tmp_pft);
			continue;
		}
	}

	if (pftm->pool) {
		cp_destroy_pool(pftm->pool);
	}

	cp_mutex_destroy(&pftm->pfc_mutex);
	cp_mutex_destroy(&pftm->pool_mutex);
	cp_pfree(pftm->func->pool, pftm);

	return 0;
}


cp_player_func_thread_t* create_player_func_thread(cp_player_func_thread_manager_t *pftm)
{
	cp_player_func_thread_t					*tmp_pft = CP_NULL;



	if (!pftm) {
		return CP_NULL;
	}

	if (cp_array_length(&pftm->thread_group) >= cp_array_max_size(&pftm->thread_group)) {
		cp_pftm_log(error, pftm, "array(thread_group) [%d >= %d] not space to insert a new one!",
			cp_array_length(&pftm->thread_group),
			cp_array_max_size(&pftm->thread_group));
		return CP_NULL;
	}
	tmp_pft = cp_palloc(pftm->pool, cp_sizeof(cp_player_func_thread_t));
	if (!tmp_pft) {
		cp_pftm_log(error, pftm, "cp_palloc() size[%d] failed!", cp_sizeof(cp_player_func_thread_t*));
		return CP_NULL;
	}
	cp_memset(tmp_pft, 0, cp_sizeof(cp_player_func_thread_t));

	tmp_pft->pftm = pftm;
	tmp_pft->interval_ms = pftm->interval_ms;
	tmp_pft->index = cp_array_length(&pftm->thread_group);
	cp_array_set(&pftm->thread_group, &tmp_pft, tmp_pft->index);

	return tmp_pft;
}

cp_int32_t init_player_func_thread(cp_player_func_thread_t *pft)
{
	if (!pft) {
		return -1;
	}

	pft->status = cp_player_func_thread_status_init;
	return 0;
}

cp_int32_t start_player_func_thread(cp_player_func_thread_t *pft, cp_player_func_thread_cb pft_cb)
{
	if (!pft || !pft_cb) {
		return -1;
	}

	pft->status = cp_player_func_thread_status_start;
	pft->thread = cp_create_thread(pft->pftm->func->manager->app, pft_cb, pft);
	if (!pft->thread) {
		return -2;
	}

	return 0;
}

cp_int32_t stop_player_func_thread(cp_player_func_thread_t *pft)
{
	if (!pft) {
		return -1;
	}

	pft->status = cp_player_func_thread_status_stop;
	cp_thread_join(pft->thread);

	return 0;
}

cp_int32_t destroy_player_func_thread(cp_player_func_thread_t *pft)
{
	if (!pft) {
		return -1;
	}

	if (!pft->thread) {
		cp_destroy_thread(pft->thread);
	}

	if (pft->pftm) {
		cp_array_remove(&pft->pftm->thread_group, pft->index);
		cp_pfree(pft->pftm->pool, pft);
	}

	return 0;
}

cp_player_func_thread_manager_t* make_player_func_thread_manager(cp_func_t *func)
{
	cp_int32_t										i = 0;
	cp_int32_t										ret_int = 0;
	cp_player_func_thread_manager_t					*tmp_pftm = CP_NULL;
	cp_player_func_thread_t							*tmp_pft = CP_NULL;



	if (!func) {
		return CP_NULL;
	}
	tmp_pftm = create_player_func_thread_manager(func);
	if (!tmp_pftm) {
		cp_module_log(error, func, "create_player_func_thread_manager() error.");
		return CP_NULL;
	}
	//初始化thread manager
	ret_int = init_player_func_thread_manager(tmp_pftm);
	if (ret_int) {
		cp_module_log(error, func, "init_player_func_thread_manager() error.");
		return CP_NULL;
	}
	//运行thrad manager
	ret_int = start_player_func_thread_manager(tmp_pftm);
	if (ret_int) {
		cp_module_log(error, func, "start_player_func_thread_manager() error.");
		return CP_NULL;
	}
	//创建各各线程
	for (i = 0; i < tmp_pftm->thread_number; i++) {
		tmp_pft = create_player_func_thread(tmp_pftm);
		if (!tmp_pft) {
			cp_module_log(warn, func, "create_player_func_thread() index[%d] error.", i);
			continue;
		}
		ret_int = init_player_func_thread(tmp_pft);
		if (ret_int) {
			cp_module_log(warn, func, "init_player_func_thread() index[%d] thread[%p] error.",
				i, tmp_pft->thread);
			continue;
		}
		ret_int = start_player_func_thread(tmp_pft, cp_player_func_thread_cb_proc);
		if (ret_int) {
			cp_module_log(warn, func, "start_player_func_thread() index[%d] thread[%p] error.",
				i, tmp_pft->thread);
			continue;
		}
	}

	return tmp_pftm;
}

cp_int32_t unmake_player_func_thread_manager(cp_player_func_thread_manager_t *pftm)
{
	cp_int32_t							ret_int = 0;


	ret_int = stop_player_func_thread_manager(pftm);
	if (ret_int) {
		cp_pftm_log(error, pftm, "stop_player_func_thread_manager() error.");
		return -1;
	}

	ret_int = destroy_player_func_thread_manager(pftm);
	if (ret_int) {
		cp_pftm_log(error, pftm, "destroy_player_func_thread_manager() error.");
		return -1;
	}
	return 0;
}


// #include <crtdbg.h>

void cp_player_func_thread_cb_proc(cp_player_func_thread_t* pft)
{
	cp_player_func_chunk_t						*tmp_pfc = CP_NULL;
	cp_uint32_t									tmp_interval_ns = (cp_uint32_t)(pft->interval_ms * CP_TIME_MSEC_TO_NSEC);
// 	_CrtMemState								s1, s2, s3;



	while (cp_player_func_thread_status_start == pft->status)
	{
		//获取完整指令
 		tmp_pfc = pop_semh_player_func_chunk(pft->pftm);
 		if (!tmp_pfc) {
 			cp_sleep_ns(0, tmp_interval_ns);
 			//cp_sleep_msec((cp_int32_t)(pft->interval_ms));
 			continue;
 		}

// 		_CrtMemCheckpoint(&s1);

		//处理指令
		proc_player_func_chunk(pft, tmp_pfc);

// 		_CrtMemCheckpoint(&s2);
// 		if (_CrtMemDifference(&s3, &s1, &s2)) {
// 			_CrtMemDumpStatistics(&s3);
// 			cp_pftm_log(warn, pft->pftm, "proc_player_func_chunk() !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
// 		}
// 		else {
// 			cp_pftm_log(warn, pft->pftm, "proc_player_func_chunk() ================================================");
// 		}
// 
		//消毁指令
		destroy_semh_player_func_chunk(pft->pftm, tmp_pfc);
	}
}

cp_player_func_chunk_t* create_semh_player_func_chunk(cp_player_func_thread_manager_t *pftm, cp_int32_t size)
{
	cp_player_func_chunk_t				*tmp_pfc = CP_NULL;


	cp_mutex_lock(&pftm->pool_mutex);
	tmp_pfc = cp_palloc(pftm->pool, cp_sizeof(cp_player_func_chunk_t) + cp_sizeof(cp_buf_t) + size);
	if (!tmp_pfc) {
		cp_mutex_unlock(&pftm->pool_mutex);
		cp_pftm_log(warn, pftm, "create_semh_player_func_chunk() error. cp_palloc() size[%d] failed!",
			cp_sizeof(cp_player_func_chunk_t));
		return CP_NULL;
	}
	cp_mutex_unlock(&pftm->pool_mutex);

	tmp_pfc->buf = (cp_buf_t *)(((cp_char_t*)tmp_pfc) + cp_sizeof(cp_player_func_chunk_t));
	tmp_pfc->nread = size;
	cp_buf_assemble(tmp_pfc->buf, ((cp_char_t*)tmp_pfc->buf) + cp_sizeof(cp_buf_t), size);

	return tmp_pfc;
}

cp_int32_t destroy_semh_player_func_chunk(cp_player_func_thread_manager_t *pftm, cp_player_func_chunk_t *pfc)
{
	if (!pftm || !pfc || !pfc->socket || !pfc->lq_elem.lf_queue) {
		return -1;
	}

	cp_mutex_lock(&pftm->pool_mutex);

	if (pftm->pool) {
		cp_pfree(pftm->pool, pfc);
	}

	cp_mutex_unlock(&pftm->pool_mutex);

	return 0;
}

//
cp_player_func_chunk_t* make_semh_player_func_chunk(cp_player_func_thread_manager_t *pftm, cp_socket_t *socket, gmp_gmph_semh_t *semh)
{
	cp_buf_t							*tmp_buf = CP_NULL;
	gmp_gmph_bmh_t						*tmp_root_bmh = CP_NULL;
	gmp_gmph_bmh_t						*tmp_bmh = CP_NULL;
	gmp_gmph_semh_t						*tmp_semh = CP_NULL;
	gmp_gmph_semh_t						*tmp_root_semh = CP_NULL;
	cp_player_func_chunk_t				*tmp_pfc = CP_NULL;
	cp_int32_t							tmp_command_len = 0;



	if (!pftm || !socket) {
		return CP_NULL;
	}

	if (pftm->precv_buf) {
		tmp_buf = pftm->precv_buf;
		pftm->precv_buf = CP_NULL;
	}
	else {
		//获取第一个包
		tmp_buf = pop_a_semh_socket_buffer(socket->data);
		if (!tmp_buf) {
			return CP_NULL;
		}
	}

	//取出semh包头，判断semh最小长度
	tmp_root_bmh = (gmp_gmph_bmh_t*)cp_buf_get_pos(tmp_buf);
	tmp_root_semh = (gmp_gmph_semh_t*)tmp_root_bmh;
	if (gmp_gmph_emh_type_semh != tmp_root_bmh->emht || tmp_root_semh->length <= 0) {
		destroy_a_semh_socket_buffer(socket->pool, socket->data, tmp_buf);
		return CP_NULL;
	}

	tmp_command_len = (cp_int32_t)(CSS_GMP_GMPH_SEMH_LEN + tmp_root_semh->length);
	tmp_pfc = create_semh_player_func_chunk(pftm, tmp_command_len);
	if (!tmp_pfc) {
		destroy_a_semh_socket_buffer(socket->pool, socket->data, tmp_buf);
		return CP_NULL;
	}
	cp_buf_strcat(tmp_pfc->buf, tmp_root_bmh, cp_buf_get_length(tmp_buf));

	destroy_a_semh_socket_buffer(socket->pool, socket->data, tmp_buf);
	if (cp_buf_get_length(tmp_pfc->buf) >= tmp_command_len) {
		//如果长度够，则返回
		tmp_pfc->socket = socket;
		tmp_pfc->nread = cp_buf_get_length(tmp_pfc->buf);
		tmp_pfc->status = socket->status;
		return tmp_pfc;
	}

	//获取其他包
	do{
		tmp_buf = pop_a_semh_socket_buffer(socket->data);
		if (!tmp_buf) {
			break;
		}

		//取出semh包头，判断semh最小长度
		tmp_bmh = (gmp_gmph_bmh_t*)cp_buf_get_pos(tmp_buf);
		tmp_semh = (gmp_gmph_semh_t*)tmp_bmh;
		if (gmp_gmph_emh_type_semh != tmp_bmh->emht || tmp_semh->length <= 0) {
			destroy_a_semh_socket_buffer(socket->pool, socket->data, tmp_buf);
			break;
		}

		if (tmp_semh->command != semh->command) {
			pftm->precv_buf = tmp_buf;
			break;
		}

		cp_buf_strcat(tmp_pfc->buf, ((cp_char_t*)tmp_bmh) + CSS_GMP_GMPH_SEMH_LEN, (cp_int32_t)(cp_buf_get_length(tmp_buf) - CSS_GMP_GMPH_SEMH_LEN));
		destroy_a_semh_socket_buffer(socket->pool, socket->data, tmp_buf);
		if (cp_buf_get_length(tmp_pfc->buf) >= tmp_command_len) {
			tmp_pfc->socket = socket;
			tmp_pfc->nread = cp_buf_get_length(tmp_pfc->buf);
			tmp_pfc->status = socket->status;
			return tmp_pfc;
		}
	} while (tmp_buf);

	if (tmp_pfc) {
		destroy_semh_player_func_chunk(pftm, tmp_pfc);
	}

	return CP_NULL;
}

cp_int32_t push_semh_player_func_chunk(cp_player_func_thread_manager_t *pftm, cp_socket_t *socket, gmp_gmph_semh_t *semh)
{
	cp_player_func_chunk_t				*tmp_pfc = CP_NULL;


	tmp_pfc = make_semh_player_func_chunk(pftm, socket, semh);
	if (!tmp_pfc) {
		return -1;
	}

	cp_mutex_lock(&pftm->pfc_mutex);

	cp_lockfree_queue_element_init(&(pftm->lq), &(tmp_pfc->lq_elem), tmp_pfc, tmp_pfc);
	cp_lockfree_queue_push(&pftm->lq, &tmp_pfc->lq_elem, 0, CP_NULL);

	cp_mutex_unlock(&pftm->pfc_mutex);

	return 0;
}

cp_player_func_chunk_t* pop_semh_player_func_chunk(cp_player_func_thread_manager_t *pftm)
{
	cp_player_func_chunk_t				*tmp_pfc = CP_NULL;
	cp_lockfree_queue_element_t			*lq_elem = CP_NULL;



	cp_mutex_lock(&pftm->pfc_mutex);

	if (!cp_lockfree_queue_pop(&pftm->lq, &lq_elem) && lq_elem && lq_elem->value) {
		tmp_pfc = (cp_player_func_chunk_t *)(lq_elem->value);
	}

	cp_mutex_unlock(&pftm->pfc_mutex);

	return tmp_pfc;
}

cp_int32_t proc_player_func_chunk(cp_player_func_thread_t *pft, cp_player_func_chunk_t *pfc)
{
	if (!pft || !pft->pftm || !pft->pftm->func || !pfc) {
		return -1;
	}

	if (pft->pftm->func->read_cb) {
		pft->pftm->func->read_cb(pfc->socket, pfc->buf, pfc->nread, pfc->status);
	}

	return 0;
}