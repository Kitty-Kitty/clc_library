/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2017-04-24

Description:

**************************************************************************/
#include "cp_module_message.h"





/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: create_module_message_manager
*
* ����˵��: ����һ����Ϣ������
*
* ��    ��: cp_module_manager_t * manager						[in]����˵��
*
* �� �� ֵ: cp_module_message_manager_t *
*           0  : �ɹ� 
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2017-04-26 13:56:17
******************************************************************************************************/
cp_module_message_manager_t *create_module_message_manager(cp_module_manager_t	*manager)
{
	cp_module_message_manager_t						*tmp_mmm = CP_NULL;



	if (!manager || !manager->pool) {
		return CP_NULL;
	}

	tmp_mmm = (cp_module_message_manager_t*)cp_palloc(manager->pool, cp_sizeof(cp_module_message_manager_t));
	if (tmp_mmm) {
		cp_memset(tmp_mmm, 0, cp_sizeof(cp_module_message_manager_t));
		tmp_mmm->manager = manager;
	}

	return tmp_mmm;
}


/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: destroy_module_message_manager
*
* ����˵��: ����һ����Ϣ������
*
* ��    ��: cp_module_message_manager_t * mmm						[in]����˵��
*
* �� �� ֵ: cp_int32_t
*           0  : �ɹ� 
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2017-04-26 13:56:37
******************************************************************************************************/
cp_int32_t destroy_module_message_manager(cp_module_message_manager_t *mmm)
{
	if (!mmm || !mmm->manager) {
		return -1;
	}

	cp_pfree(mmm->manager->pool, mmm);

	return 0;
}

/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: init_module_message_manager
*
* ����˵��: ��ʼ��ͨ����������Ϣ
*
* ��    ��: cp_module_manager_t	*manager						[in]����˵��
* ��    ��: cp_module_message_manager_t * mmm						[in]����˵��
*
* �� �� ֵ: cp_int32_t
*           0  : �ɹ�
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2016-12-13 17:42:23
******************************************************************************************************/
cp_int32_t init_module_message_manager(cp_module_manager_t	*manager, cp_module_message_manager_t *mmm)
{
	cp_int32_t								tmp_queue_bound_size = CP_MODULE_MESSAGE_DEFAULT_NUMBER;
	cp_int32_t								i = 0;
	cp_module_message_process_t				tmp_mmp[] = {
		{ cp_module_message_type_none, module_message_general_handle },
		{ cp_module_message_type_init, module_message_general_handle },
		{ cp_module_message_type_start, module_message_general_handle },
		{ cp_module_message_type_stop, module_message_general_handle },
		{ cp_module_message_type_create, module_message_general_handle },
		{ cp_module_message_type_destory, module_message_general_handle },
		{ cp_module_message_type_open, module_message_general_handle },
		{ cp_module_message_type_read, module_message_general_handle },
		{ cp_module_message_type_write, module_message_general_handle },
		{ cp_module_message_type_close, module_message_close_handle },
		{ cp_module_message_type_exit, module_message_general_handle },
	};

	if (!manager || !mmm) {
		return -1;
	}

	cp_memset(mmm, 0, cp_sizeof(cp_module_message_manager_t));

	mmm->manager = manager;
	mmm->logger = manager->logger;

	//����һ���ڴ��
	mmm->mpool = cp_create_mpool(CP_APP_DEFAULT_BUFFER_LENGTH);
	if (!mmm->mpool) {
		cp_manager_log(error, mmm->manager, 
			"init_module_message_manager () error reason: cp_create_mpool() failed!");
		return -2;
	}

	//������Ϣ�����б�
	mmm->mmp_list = cp_mpalloc(mmm->mpool, (cp_module_message_type_end * cp_sizeof(cp_module_message_process_t)));
	if (!mmm->mmp_list) {
		cp_manager_log(error, mmm->manager, 
			"init_module_message_manager () error reason: cp_mpalloc() failed!");
		return -2;
	}
	else {
		cp_memset(mmm->mmp_list, 0, (cp_module_message_type_end * cp_sizeof(cp_module_message_process_t)));
	}

	for (i = 0; i < cp_ary_size(tmp_mmp); i++) {
		mmm->mmp_list[tmp_mmp[i].mm_type] = tmp_mmp[i];
	}

	//������Ϣ�б�
	mmm->mes_sq = cp_create_general_safe_queue(cp_safe_queue_mode_qbss, tmp_queue_bound_size);
	if (!mmm->mes_sq) {
		cp_manager_log(error, mmm->manager, "cp_create_general_safe_queue() failed!");
		return -3;
	}

	return 0;
}


/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: start_module_message_manager
*
* ����˵��: ��ʼͨ��������
*
* ��    ��: cp_module_message_manager_t * hm						[in]����˵��
*
* �� �� ֵ: cp_int32_t
*           0  : �ɹ�
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2016-11-03 18:07:03
******************************************************************************************************/
cp_int32_t start_module_message_manager(cp_module_message_manager_t *mmm)
{
	if (!mmm) {
		return -1;
	}

	mmm->thread_status = cp_thread_status_start;
	mmm->thread = cp_create_thread(mmm->manager->app, (cp_thread_cb)module_message_thread_cb_proc, mmm);
	if (!mmm->thread) {
		cp_manager_log(error, mmm->manager, "cp_create_thread() failed!");
		return -3;
	}
	else {
		cp_manager_log(notice, mmm->manager, "cp_create_thread() thread[0x%x]!", mmm->thread);
	}

	return 0;
}


/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: stop_module_message_manager
*
* ����˵��: ֹͣͨ��������
*
* ��    ��: cp_module_message_manager_t * hm						[in]����˵��
*
* �� �� ֵ: cp_int32_t
*           0  : �ɹ�
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2016-11-03 18:07:19
******************************************************************************************************/
cp_int32_t stop_module_message_manager(cp_module_message_manager_t *mmm)
{
	cp_module_message_t				*tmp_ret_mm = CP_NULL;



	//�߳�ָ��
	if (mmm->thread) {
		mmm->thread_status = cp_thread_status_stop;
		cp_thread_join(mmm->thread);
		cp_destroy_thread(mmm->thread);
		mmm->thread = CP_NULL;
	}

	//ɾ��������Ϣ
	tmp_ret_mm = pop_module_message(mmm);
	while (tmp_ret_mm) {
		destroy_module_message(mmm, tmp_ret_mm);
		tmp_ret_mm = pop_module_message(mmm);
	}

	//���ٰ�ȫ����
	if (mmm->mes_sq) {
		cp_destroy_safe_queue(mmm->mes_sq);
	}

	//�ͷ��ڴ�
	if (mmm->mpool) {
		cp_destroy_mpool(mmm->mpool);
		mmm->mpool = CP_NULL;
	}

	return 0;
}



/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: set_module_message_process
*
* ����˵��: ����ģ�鴦��ӿ�
*
* ��    ��: cp_module_message_manager_t * mmm						[in]����˵��
* ��    ��: cp_module_message_process_t * mmp						[in]����˵��
*
* �� �� ֵ: cp_int32_t
*           0  : �ɹ� 
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2017-04-25 21:41:25
******************************************************************************************************/
cp_int32_t set_module_message_process(cp_module_message_manager_t *mmm, cp_module_message_process_t *mmp)
{
	if (!mmm || !mmp || !mmp->handle) {
		return -1;
	}

	if (mmp->mm_type < cp_module_message_type_none ||
		mmp->mm_type > cp_module_message_type_end) {
		return -2;
	}

	mmm->mmp_list[mmp->mm_type] = *mmp;

	return 0;
}


/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: create_module_message
*
* ����˵��: ����ģ����Ϣ
*
* ��    ��: cp_module_message_manager_t * mmm						[in]����˵��
*
* �� �� ֵ: cp_module_message_t *
*           0  : �ɹ�
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2017-04-24 21:18:37
******************************************************************************************************/
cp_module_message_t *create_module_message(cp_module_message_manager_t *mmm)
{
	cp_module_message_t				*tmp_ret_mm = CP_NULL;



	if (!mmm) {
		return CP_NULL;
	}

	tmp_ret_mm = (cp_module_message_t*)cp_malloc(cp_sizeof(cp_module_message_t));
	if (tmp_ret_mm) {
		cp_memset(tmp_ret_mm, 0, cp_sizeof(cp_module_message_t));
		tmp_ret_mm->mmm = mmm;
	}
	return tmp_ret_mm;
}


/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: destroy_module_message
*
* ����˵��: ��Ϣͨ����Ϣ
*
* ��    ��: cp_module_message_manager_t * mmm						[in]����˵��
* ��    ��: cp_module_message_t *mm					[in]����˵��
*
* �� �� ֵ: cp_int32_t
*           0  : �ɹ�
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2016-12-13 18:19:54
******************************************************************************************************/
cp_int32_t destroy_module_message(cp_module_message_manager_t *mmm, cp_module_message_t *mm)
{
	if (!mmm || !mm) {
		return -1;
	}

	cp_free(mm);

	return 0;
}


/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: init_module_message
*
* ����˵��: ��ʼ���豸��ͨ����Ϣ
*
* ��    ��: cp_module_message_manager_t * hm						[in]����˵��
* ��    ��: cp_module_message_t * mm						[in]����˵��
*
* �� �� ֵ: cp_int32_t
*           0  : �ɹ�
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2016-11-03 18:07:30
******************************************************************************************************/
cp_int32_t init_module_message(cp_module_message_manager_t *mmm, cp_module_message_t *mm)
{
	if (!mmm || !mm) {
		return -1;
	}

	mm->mmm = mmm;

	return 0;
}


/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: set_module_message
*
* ����˵��: ����ͨ����Ϣ
*
* ��    ��: cp_module_message_t * mm						[in]����˵��
* ��    ��: cp_module_t * module						[in]����˵��
* ��    ��: cp_void_t * data						[in]����˵��
* ��    ��: cp_int32_t index						[in]����˵��
* ��    ��: cp_module_message_type_e mm_type						[in]����˵��
* ��    ��: module_message_handle	handle						[in]����˵��
*
* �� �� ֵ: cp_int32_t
*           0  : �ɹ�
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2017-04-24 20:55:48
******************************************************************************************************/
cp_int32_t set_module_message(cp_module_message_t *mm, cp_module_t *module,
	cp_void_t *data, cp_int32_t index, cp_module_message_type_e mm_type, module_message_handle handle)
{
	if (!mm) {
		return -1;
	}
	mm->module = module;
	mm->data = data;
	mm->index = index;
	mm->mmp.mm_type = mm_type;
	mm->mmp.handle = handle;
	return 0;
}


/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: push_module_message
*
* ����˵��: ������Ϣ
*
* ��    ��: cp_module_message_manager_t * mmm						[in]����˵��
* ��    ��: cp_module_message_t * src						[in]����˵��
*
* �� �� ֵ: cp_module_message_t *
*           0  : �ɹ�
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2017-04-24 21:05:36
******************************************************************************************************/
cp_int32_t push_module_message(cp_module_message_manager_t *mmm, cp_module_message_t *src)
{
	return cp_safe_queue_push(mmm->mes_sq, src);
}


/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: pop_module_message
*
* ����˵��: ɾ��ģ����Ϣ
*
* ��    ��: cp_module_message_manager_t * mmm						[in]����˵��
*
* �� �� ֵ: cp_module_message_t *
*           0  : �ɹ�
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2017-04-24 21:06:58
******************************************************************************************************/
cp_module_message_t *pop_module_message(cp_module_message_manager_t *mmm)
{
	cp_module_message_t				*tmp_ret_mm = CP_NULL;



	tmp_ret_mm = cp_safe_queue_pop(mmm->mes_sq);
	if (!tmp_ret_mm) {
		return CP_NULL;
	}

	return tmp_ret_mm;
}


/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: module_message_thread_cb_proc
*
* ����˵��: ����module message��Ϣ
*
* ��    ��: cp_module_message_manager_t * mmm						[in]����˵��
*
* �� �� ֵ: cp_void_t
*           0  : �ɹ�
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2017-04-24 22:13:22
******************************************************************************************************/
cp_void_t module_message_thread_cb_proc(cp_module_message_manager_t *mmm)
{
	cp_int32_t						tmp_ret_int = 0;
	cp_module_message_t				*tmp_ret_mm = CP_NULL;



	while (cp_thread_status_start == mmm->thread_status)
	{
		tmp_ret_mm = pop_module_message(mmm);
		if (!tmp_ret_mm) {
			cp_sleep_ns(0, CP_MODULE_MESSAGE_SLEEP_INTERVAL);
			continue;
		}

		if (tmp_ret_mm->mmp.mm_type < cp_module_message_type_none || 
			tmp_ret_mm->mmp.mm_type > cp_module_message_type_end) {
			cp_manager_log(error, mmm->manager,
				"module message type[%d] nonsupport",
				tmp_ret_mm->mmp.mm_type);
			continue;
		}

		if (tmp_ret_mm->mmp.handle) {
			tmp_ret_int = tmp_ret_mm->mmp.handle(mmm, tmp_ret_mm, CP_NULL);
		}
		else {
			if (mmm->mmp_list && mmm->mmp_list[tmp_ret_mm->mmp.mm_type].handle &&
				mmm->mmp_list[tmp_ret_mm->mmp.mm_type].mm_type == tmp_ret_mm->mmp.mm_type) {
				tmp_ret_int = mmm->mmp_list[tmp_ret_mm->mmp.mm_type].handle(mmm, tmp_ret_mm, CP_NULL);
			}
		}

		destroy_module_message(mmm, tmp_ret_mm);
	}
}


/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: module_message_general_handle
*
* ����˵��: ��ϸ��Ϣ
*
* ��    ��: cp_module_message_manager_t * mmm						[in]����˵��
* ��    ��: cp_module_message_t * src						[in]����˵��
* ��    ��: cp_void_t * data						[in]����˵��
*
* �� �� ֵ: cp_int32_t
*           0  : �ɹ�
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2017-04-25 16:05:59
******************************************************************************************************/
cp_int32_t	module_message_general_handle(cp_module_message_manager_t *mmm, cp_module_message_t *src, cp_void_t *data)
{
	return 0;
}


/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: module_message_addr_handle
*
* ����˵��: ģ����Ӵ�����Ϣ
*
* ��    ��: cp_module_message_manager_t * mmm						[in]����˵��
* ��    ��: cp_module_message_t * src						[in]����˵��
* ��    ��: cp_void_t * data						[in]����˵��
*
* �� �� ֵ: cp_int32_t
*           0  : �ɹ�
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2017-04-25 20:19:55
******************************************************************************************************/
cp_int32_t	module_message_addr_handle(cp_module_message_manager_t *mmm, cp_module_message_t *src, cp_void_t *data)
{
	return 0;
}


/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: module_message_remove_handle
*
* ����˵��: ģ��رմ�����Ϣ
*
* ��    ��: cp_module_message_manager_t * mmm						[in]����˵��
* ��    ��: cp_module_message_t * src						[in]����˵��
* ��    ��: cp_void_t * data						[in]����˵��
*
* �� �� ֵ: cp_int32_t
*           0  : �ɹ�
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2017-04-25 20:20:24
******************************************************************************************************/
cp_int32_t	module_message_close_handle(cp_module_message_manager_t *mmm, cp_module_message_t *src, cp_void_t *data)
{
	if (!mmm || !src) {
		return -1;
	}

	if (!mmm->manager || !src->module) {
		return -2;
	}

	//cp_manager_close_module(mmm->manager, src->module);
	cp_close_module(src->module);

	return 0;
}