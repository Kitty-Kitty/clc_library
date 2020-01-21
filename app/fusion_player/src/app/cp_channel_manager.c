/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-12-13

Description:

**************************************************************************/
#include "cp_channel_manager.h"




/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: rb_channel_compare
*
* 函数说明: 通道对比函数
*
* 参    数: cp_channel_t * rb_chl1						[in]参数说明
* 参    数: cp_channel_t * rb_chl2						[in]参数说明
*
* 返 回 值: int
*           0  : 成功 
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2016-12-13 17:13:32
******************************************************************************************************/
static int rb_channel_compare(cp_channel_t* rb_chl1, cp_channel_t* rb_chl2) {
	if (rb_chl1->index < rb_chl2->index) {
		return -1;
	}
	if (rb_chl1->index > rb_chl2->index) {
		return 1;
	}

	return 0;
}

/************************************************************************/
/* 初始化红黑树操作                                                      */
/************************************************************************/
CP_RB_GENERATE_STATIC(cp_channel_rb_tree_s, cp_channel_s, tree_entry, rb_channel_compare);


/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: init_channel_manager
*
* 函数说明: 初始化通道管理器信息
*
* 参    数: cp_app_t * app						[in]参数说明
* 参    数: cp_channel_manager_t * cm						[in]参数说明
* 参    数: cp_int32_t max_size						[in]参数说明
*
* 返 回 值: int
*           0  : 成功 
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2016-12-13 17:42:23
******************************************************************************************************/
int init_channel_manager(cp_app_t *app, cp_channel_manager_t *cm, cp_int32_t max_size)
{
	cp_void_t				*tmp_mem = CP_NULL;
	cp_int32_t				tmp_max_size = CP_CHANNEL_MANAGER_DEFAULT_NUMBER;


	if (!cm) {
		return -1;
	}

	cp_memset(cm, 0, cp_sizeof(cp_channel_manager_t));

	cm->app = app;
	cm->logger = app->logger;

	//设置播放数量
	if (max_size <= 0) {
		cm->max_size = CP_CHANNEL_MANAGER_DEFAULT_NUMBER;
	}
	else {
		cm->max_size = max_size;
	}
	tmp_max_size = cm->max_size;

	//分配一个内存池
	cm->mpool = cp_create_mpool(CP_APP_DEFAULT_BUFFER_LENGTH);
	if (!cm->mpool) {
		cp_log_error(cm->logger, "init_channel_manager () error reason: cp_create_mpool() failed!");
		return -2;
	}

	//为通道指针创建存储空间
	tmp_mem = cp_mpalloc(cm->mpool, (cp_sizeof(cp_channel_t) * (tmp_max_size)));
	if (!tmp_mem) {
		cp_log_error(cm->logger, "init_channel_manager() error! malloc device channel buffer error. manager_size[%d]",
			tmp_max_size);
		return -3;
	}
	cp_memset(tmp_mem, 0, cp_sizeof(cp_channel_t) * (tmp_max_size));
	cp_array_init(&(cm->channels), tmp_mem, cp_sizeof(cp_channel_t), (tmp_max_size));

	cp_mutex_init(&cm->chl_mutex);

	return 0;
}

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: start_channel_manager
*
* 函数说明: 开始通道管理器
*
* 参    数: cp_channel_manager_t * hm						[in]参数说明
*
* 返 回 值: int
*           0  : 成功
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2016-11-03 18:07:03
******************************************************************************************************/
int start_channel_manager(cp_channel_manager_t *cm)
{
	if (!cm) {
		return -1;
	}
	return 0;
}

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: stop_channel_manager
*
* 函数说明: 停止通道管理器
*
* 参    数: cp_channel_manager_t * hm						[in]参数说明
*
* 返 回 值: int
*           0  : 成功
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2016-11-03 18:07:19
******************************************************************************************************/
int stop_channel_manager(cp_channel_manager_t *cm)
{
	if (cm->mpool) {
		cp_destroy_mpool(cm->mpool);
		cm->mpool = CP_NULL;
	}
	return 0;
}

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: init_channel
*
* 函数说明: 初始化设备的通道信息
*
* 参    数: cp_channel_manager_t * hm						[in]参数说明
* 参    数: cp_channel_t * chl						[in]参数说明
*
* 返 回 值: int
*           0  : 成功
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2016-11-03 18:07:30
******************************************************************************************************/
int init_channel(cp_channel_manager_t *cm, cp_channel_t *chl)
{
	if (!chl) {
		return -1;
	}

	chl->cm = cm;

	return 0;
}

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: set_channel
*
* 函数说明: 设置通道信息
*
* 参    数: cp_channel_t * chl						[in]参数说明
* 参    数: cp_int32_t index						[in]参数说明
* 参    数: cp_char_t * session						[in]参数说明
* 参    数: cp_module_t * module						[in]参数说明
* 参    数: cp_void_t	*data					[in]参数说明
*
* 返 回 值: int
*           0  : 成功 
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2016-12-13 18:24:08
******************************************************************************************************/
int set_channel(cp_channel_t *chl, cp_int32_t index, 
	cp_char_t *session, cp_module_t *module, cp_void_t *data)
{
	if (!chl) {
		return -1;
	}
	chl->index = index;
	cp_strcpy(chl->session, session);
	chl->module = module;
	chl->data = data;
	return 0;
}

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: insert_channel
*
* 函数说明: 添加通道信息
*
* 参    数: cp_channel_manager_t * cm						[in]参数说明
* 参    数: cp_channel_t * src						[in]参数说明
*
* 返 回 值: cp_channel_t *
*           0  : 成功 
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2016-12-13 18:03:30
******************************************************************************************************/
cp_channel_t *insert_channel(cp_channel_manager_t *cm, cp_channel_t *src)
{
	cp_channel_t				tmp_chl = { 0, };
	cp_channel_t				*tmp_ret_chl = CP_NULL;
	cp_int32_t					i = 0;


	tmp_ret_chl = find_channel(cm, src->index);
	if (tmp_ret_chl) {
		return tmp_ret_chl;
	}
	set_channel(&tmp_chl, src->index, src->session, src->module, src->data);

	cp_mutex_lock(&cm->chl_mutex);

	for (i = 0; i < (cp_int32_t)cp_array_max_size(&cm->channels); i++) {
		tmp_ret_chl = cp_array_get(&cm->channels, i);
		if (!tmp_ret_chl->index) {
			*tmp_ret_chl = tmp_chl;
			tmp_ret_chl->cm = cm;
			break;
		}
	}

	if (tmp_ret_chl) {
		CP_RB_INSERT(cp_channel_rb_tree_s, &cm->chl_rb_root, tmp_ret_chl);
		++(cm->size);
	}

	cp_mutex_unlock(&cm->chl_mutex);

	return tmp_ret_chl;
}

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: find_channel
*
* 函数说明: 查找指定通道
*
* 参    数: cp_channel_manager_t * cm						[in]参数说明
* 参    数: cp_int32_t index						[in]参数说明
*
* 返 回 值: cp_channel_t *
*           0  : 成功 
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2016-12-13 18:03:59
******************************************************************************************************/
cp_channel_t *find_channel(cp_channel_manager_t *cm, cp_int32_t index)
{
	cp_channel_t				tmp_chl = { 0, };
	cp_channel_t				*tmp_ret_chl = CP_NULL;


	tmp_chl.index = index;

	cp_mutex_lock(&cm->chl_mutex);

	tmp_ret_chl = CP_RB_FIND(cp_channel_rb_tree_s, &cm->chl_rb_root, &tmp_chl);

	cp_mutex_unlock(&cm->chl_mutex);

	return tmp_ret_chl;
}

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: find_next_channel
*
* 函数说明: 查找下一个通道
*
* 参    数: cp_channel_manager_t * cm						[in]参数说明
* 参    数: cp_int32_t index						[in]参数说明
*
* 返 回 值: cp_channel_t *
*           0  : 成功 
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2017-04-14 13:54:23
******************************************************************************************************/
cp_channel_t *find_next_channel(cp_channel_manager_t *cm, cp_int32_t index)
{
	cp_channel_t				tmp_chl = { 0, };
	cp_channel_t				*tmp_ret_chl = CP_NULL;


	tmp_chl.index = index;

	cp_mutex_lock(&cm->chl_mutex);

	tmp_ret_chl = CP_RB_NEXT(cp_channel_rb_tree_s, &cm->chl_rb_root, &tmp_chl);

	cp_mutex_unlock(&cm->chl_mutex);

	return tmp_ret_chl;
}


/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: find_prev_channel
*
* 函数说明: 查找上一个通道
*
* 参    数: cp_channel_manager_t * cm						[in]参数说明
* 参    数: cp_int32_t index						[in]参数说明
*
* 返 回 值: cp_channel_t *
*           0  : 成功 
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2017-04-14 13:57:11
******************************************************************************************************/
cp_channel_t *find_prev_channel(cp_channel_manager_t *cm, cp_int32_t index)
{
	cp_channel_t				tmp_chl = { 0, };
	cp_channel_t				*tmp_ret_chl = CP_NULL;


	tmp_chl.index = index;

	cp_mutex_lock(&cm->chl_mutex);

	tmp_ret_chl = CP_RB_PREV(cp_channel_rb_tree_s, &cm->chl_rb_root, &tmp_chl);

	cp_mutex_unlock(&cm->chl_mutex);

	return tmp_ret_chl;
}

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: find_min_channel
*
* 函数说明: 描述方法的功能信息
*
* 参    数: cp_channel_manager_t * cm						[in]参数说明
*
* 返 回 值: cp_channel_t *
*           0  : 成功 
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2017-04-14 11:46:16
******************************************************************************************************/
cp_channel_t *find_min_channel(cp_channel_manager_t *cm)
{
	cp_channel_t				*tmp_ret_chl = CP_NULL;


	cp_mutex_lock(&cm->chl_mutex);

	tmp_ret_chl = CP_RB_MIN(cp_channel_rb_tree_s, &cm->chl_rb_root);

	cp_mutex_unlock(&cm->chl_mutex);

	return tmp_ret_chl;
}


/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: find_max_channel
*
* 函数说明: 描述方法的功能信息
*
* 参    数: cp_channel_manager_t * cm						[in]参数说明
*
* 返 回 值: cp_channel_t *
*           0  : 成功 
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2017-04-14 11:46:23
******************************************************************************************************/
cp_channel_t *find_max_channel(cp_channel_manager_t *cm)
{
	cp_channel_t				*tmp_ret_chl = CP_NULL;


	cp_mutex_lock(&cm->chl_mutex);

	tmp_ret_chl = CP_RB_MAX(cp_channel_rb_tree_s, &cm->chl_rb_root);

	cp_mutex_unlock(&cm->chl_mutex);

	return tmp_ret_chl;
}

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: remove_channel
*
* 函数说明: 删除通道信息
*
* 参    数: cp_channel_manager_t * cm						[in]参数说明
* 参    数: cp_int32_t index						[in]参数说明
*
* 返 回 值: int
*           0  : 成功 
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2016-12-13 18:19:54
******************************************************************************************************/
int remove_channel(cp_channel_manager_t *cm, cp_int32_t index)
{
	cp_channel_t				tmp_chl = { 0, };
	cp_channel_t				*tmp_ret_chl = CP_NULL;


	tmp_chl.index = index;

	cp_mutex_lock(&cm->chl_mutex);

	tmp_ret_chl = CP_RB_FIND(cp_channel_rb_tree_s, &cm->chl_rb_root, &tmp_chl);
	if (tmp_ret_chl) {
		CP_RB_REMOVE(cp_channel_rb_tree_s, &cm->chl_rb_root, tmp_ret_chl);

		cp_memset(tmp_ret_chl, 0, cp_sizeof(cp_channel_t));
		tmp_ret_chl->cm = cm;
		--(cm->size);
	}

	cp_mutex_unlock(&cm->chl_mutex);

	return 0;
}