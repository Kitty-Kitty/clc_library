/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-12-13

Description:

**************************************************************************/
#include "cp_channel_manager.h"




/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: rb_channel_compare
*
* ����˵��: ͨ���ԱȺ���
*
* ��    ��: cp_channel_t * rb_chl1						[in]����˵��
* ��    ��: cp_channel_t * rb_chl2						[in]����˵��
*
* �� �� ֵ: int
*           0  : �ɹ� 
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2016-12-13 17:13:32
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
/* ��ʼ�����������                                                      */
/************************************************************************/
CP_RB_GENERATE_STATIC(cp_channel_rb_tree_s, cp_channel_s, tree_entry, rb_channel_compare);


/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: init_channel_manager
*
* ����˵��: ��ʼ��ͨ����������Ϣ
*
* ��    ��: cp_app_t * app						[in]����˵��
* ��    ��: cp_channel_manager_t * cm						[in]����˵��
* ��    ��: cp_int32_t max_size						[in]����˵��
*
* �� �� ֵ: int
*           0  : �ɹ� 
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2016-12-13 17:42:23
******************************************************************************************************/
int init_channel_manager(cp_app_t *app, cp_channel_manager_t *cm, cp_int32_t max_size)
{
	cp_void_t				*tmp_mem = CP_NULL;
	cp_int32_t				tmp_max_size = CP_CHANNEL_MANAGER_DEFAULT_NUMBER;


	if (!cm) {
		return -1;
	}

	cm->app = app;
	cm->logger = app->logger;

	//���ò�������
	if (max_size <= 0) {
		cm->max_size = CP_CHANNEL_MANAGER_DEFAULT_NUMBER;
	}
	else {
		cm->max_size = max_size;
	}
	tmp_max_size = cm->max_size;

	//����һ���ڴ��
	cm->mpool = cp_create_mpool(CP_APP_DEFAULT_BUFFER_LENGTH);
	if (!cm->mpool) {
		cp_log_error(cm->logger, "init_channel_manager () error reason: cp_create_mpool() failed!");
		return -2;
	}

	//Ϊͨ��ָ�봴���洢�ռ�
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
* ��Ȩ����: fz & novigo
*
* ��������: start_channel_manager
*
* ����˵��: ��ʼͨ��������
*
* ��    ��: cp_channel_manager_t * hm						[in]����˵��
*
* �� �� ֵ: int
*           0  : �ɹ�
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2016-11-03 18:07:03
******************************************************************************************************/
int start_channel_manager(cp_channel_manager_t *cm)
{
	if (!cm) {
		return -1;
	}
	return 0;
}

/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: stop_channel_manager
*
* ����˵��: ֹͣͨ��������
*
* ��    ��: cp_channel_manager_t * hm						[in]����˵��
*
* �� �� ֵ: int
*           0  : �ɹ�
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2016-11-03 18:07:19
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
* ��Ȩ����: fz & novigo
*
* ��������: init_channel
*
* ����˵��: ��ʼ���豸��ͨ����Ϣ
*
* ��    ��: cp_channel_manager_t * hm						[in]����˵��
* ��    ��: cp_channel_t * chl						[in]����˵��
*
* �� �� ֵ: int
*           0  : �ɹ�
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2016-11-03 18:07:30
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
* ��Ȩ����: fz & novigo
*
* ��������: set_channel
*
* ����˵��: ����ͨ����Ϣ
*
* ��    ��: cp_channel_t * chl						[in]����˵��
* ��    ��: cp_int32_t index						[in]����˵��
* ��    ��: cp_char_t * session						[in]����˵��
* ��    ��: cp_module_t * module						[in]����˵��
* ��    ��: cp_void_t	*data					[in]����˵��
*
* �� �� ֵ: int
*           0  : �ɹ� 
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2016-12-13 18:24:08
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
* ��Ȩ����: fz & novigo
*
* ��������: insert_channel
*
* ����˵��: ���ͨ����Ϣ
*
* ��    ��: cp_channel_manager_t * cm						[in]����˵��
* ��    ��: cp_channel_t * src						[in]����˵��
*
* �� �� ֵ: cp_channel_t *
*           0  : �ɹ� 
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2016-12-13 18:03:30
******************************************************************************************************/
cp_channel_t *insert_channel(cp_channel_manager_t *cm, cp_channel_t *src)
{
	cp_channel_t				tmp_chl = { 0, };
	cp_channel_t				*tmp_ret_chl = CP_NULL;
	cp_int32_t					i = 0;


	tmp_ret_chl = find_channel_by_index(cm, src->index);
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
* ��Ȩ����: fz & novigo
*
* ��������: find_channel_by_index
*
* ����˵��: ����ָ��ͨ��
*
* ��    ��: cp_channel_manager_t * cm						[in]����˵��
* ��    ��: cp_int32_t index						[in]����˵��
*
* �� �� ֵ: cp_channel_t *
*           0  : �ɹ� 
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2016-12-13 18:03:59
******************************************************************************************************/
cp_channel_t *find_channel_by_index(cp_channel_manager_t *cm, cp_int32_t index)
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
* ��Ȩ����: fz & novigo
*
* ��������: remove_channel_by_index
*
* ����˵��: ɾ��ͨ����Ϣ
*
* ��    ��: cp_channel_manager_t * cm						[in]����˵��
* ��    ��: cp_int32_t index						[in]����˵��
*
* �� �� ֵ: int
*           0  : �ɹ� 
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2016-12-13 18:19:54
******************************************************************************************************/
int remove_channel_by_index(cp_channel_manager_t *cm, cp_int32_t index)
{
	cp_channel_t				tmp_chl = { 0, };
	cp_channel_t				*tmp_ret_chl = CP_NULL;


	tmp_chl.index = index;

	cp_mutex_lock(&cm->chl_mutex);

	tmp_ret_chl = CP_RB_FIND(cp_channel_rb_tree_s, &cm->chl_rb_root, &tmp_chl);

	cp_mutex_unlock(&cm->chl_mutex);

	if (tmp_ret_chl) {
		return remove_channel(cm, tmp_ret_chl);
	}

	return 0;
}

/*******************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: remove_channel
*
* ����ȫ��: remove_channel
*
* ��������: public 
*
* ����˵��: ɾ��ָ��ͨ��
*
* ��    ��: cp_channel_manager_t * cm						[in/out]����˵��
* ��    ��: cp_channel_t * src						[in/out]����˵��
*
* �� �� ֵ: int
*           0  : �ɹ�
*         ��0  : ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2018-1-30 12:09:27
********************************************************************************/
int remove_channel(cp_channel_manager_t *cm, cp_channel_t *src)
{
	if (!cm || !src) {
		return -1;
	}

	cp_mutex_lock(&cm->chl_mutex);

	if (src) {
		CP_RB_REMOVE(cp_channel_rb_tree_s, &cm->chl_rb_root, src);

		cp_memset(src, 0, cp_sizeof(cp_channel_t));
		src->cm = cm;
		--(cm->size);
	}

	cp_mutex_unlock(&cm->chl_mutex);

	return 0;
}

/*******************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: remove_all_channel
*
* ����ȫ��: remove_all_channel
*
* ��������: public 
*
* ����˵��: ɾ������ͨ��
*
* ��    ��: cp_channel_manager_t * cm						[in/out]����˵��
* ��    ��: cp_void_t * arg						[in/out]����˵��
* ��    ��: cp_channel_remove_handle handle						[in/out]����˵��
*
* �� �� ֵ: int
*           0  : �ɹ�
*         ��0  : ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2018-1-30 12:09:15
********************************************************************************/
int remove_all_channel(cp_channel_manager_t *cm, cp_void_t *arg, cp_channel_remove_handle handle)
{
	cp_channel_t				*tmp_ret_chl = CP_NULL;


	if (!cm || !handle) {
		return -1;
	}

//����ȫ��ɾ����Ĵ���ʽ����ҪΪ�˷�ֹ����cp_channel_remove_handleδ���ض����µ���������
//������ƿ��ܴ���ģ��������
// 	cp_mutex_lock(&cm->chl_mutex);
// 
// 	CP_RB_FOREACH(tmp_ret_chl, cp_channel_rb_tree_s, &cm->chl_rb_root) {
// 
// 	}
// 
// 	cp_mutex_unlock(&cm->chl_mutex);

	do 
	{
		tmp_ret_chl = find_min_channel(cm);
		if (tmp_ret_chl) {
			//������ûص����������ǲ��жϷ��ء�
			//��ô�����Ŀ�صı�֤�÷����ܹ�ɾ������ͨ��
			handle(cm, arg, tmp_ret_chl);
			remove_channel(cm, tmp_ret_chl);
		}

		tmp_ret_chl = CP_NULL;
	} while (cm->size > 0);

	return 0;
}

/*******************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: find_max_channel_index
*
* ����ȫ��: find_max_channel_index
*
* ��������: public 
*
* ����˵��: �������ͨ��������
*
* ��    ��: cp_channel_manager_t * cm						[in/out]����˵��
*
* �� �� ֵ: int
*           0  : �ɹ�
*         ��0  : ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2018-1-30 11:16:40
********************************************************************************/
int find_max_channel_index(cp_channel_manager_t *cm)
{
	cp_channel_t				*tmp_ret_chl = CP_NULL;


	tmp_ret_chl = find_max_channel(cm);
	if (!tmp_ret_chl) {
		return 0;
	}

	return tmp_ret_chl->index;
}

/*******************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: find_min_channel_index
*
* ����ȫ��: find_min_channel_index
*
* ��������: public 
*
* ����˵��: ������Сͨ��������
*
* ��    ��: cp_channel_manager_t * cm						[in/out]����˵��
*
* �� �� ֵ: int
*           0  : �ɹ�
*         ��0  : ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2018-1-30 11:22:46
********************************************************************************/
int find_min_channel_index(cp_channel_manager_t *cm)
{
	cp_channel_t				*tmp_ret_chl = CP_NULL;


	tmp_ret_chl = find_min_channel(cm);
	if (!tmp_ret_chl) {
		return 0;
	}

	return tmp_ret_chl->index;
}

/*******************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: find_max_channel
*
* ����ȫ��: find_max_channel
*
* ��������: public 
*
* ����˵��: �������ͨ��
*
* ��    ��: cp_channel_manager_t * cm						[in/out]����˵��
*
* �� �� ֵ: cp_channel_t *
*           0  : �ɹ�
*         ��0  : ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2018-1-30 11:19:40
********************************************************************************/
cp_channel_t* find_max_channel(cp_channel_manager_t *cm)
{
	cp_channel_t				*tmp_ret_chl = CP_NULL;


	cp_mutex_lock(&cm->chl_mutex);

	tmp_ret_chl = CP_RB_MAX(cp_channel_rb_tree_s, &cm->chl_rb_root);

	cp_mutex_unlock(&cm->chl_mutex);

	return tmp_ret_chl;
}

/*******************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: find_min_channel
*
* ����ȫ��: find_min_channel
*
* ��������: public 
*
* ����˵��: ������Сͨ��
*
* ��    ��: cp_channel_manager_t * cm						[in/out]����˵��
*
* �� �� ֵ: cp_channel_t*
*           0  : �ɹ�
*         ��0  : ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2018-1-30 11:23:36
********************************************************************************/
cp_channel_t* find_min_channel(cp_channel_manager_t *cm)
{
	cp_channel_t				*tmp_ret_chl = CP_NULL;


	cp_mutex_lock(&cm->chl_mutex);

	tmp_ret_chl = CP_RB_MIN(cp_channel_rb_tree_s, &cm->chl_rb_root);

	cp_mutex_unlock(&cm->chl_mutex);

	return tmp_ret_chl;
}