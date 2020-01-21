/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-09-19

Description:

**************************************************************************/
#include "cp_include.h"
#include "cp_player_default.h"
#include "cp_player_heartbeat.h"
#include "cp_player_conf_string.h"




/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: get_heartbeat_configure_info
*
* ����˵��: ��ȡ�������ʱ��
*
* ��    ��: cp_app_t * app						[in]����˵��
* ��    ��: cp_heartbeat_manager_t * hm						[in]����˵��
*
* �� �� ֵ: cp_int64_t
*           0  : �ɹ� 
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2016-12-02 16:01:37
******************************************************************************************************/
cp_int32_t	get_heartbeat_configure_info(cp_app_t	*app, cp_heartbeat_manager_t *hm)
{
	cp_int64_t					tmp_interval = CP_PLAYER_HEARTBEAT_DEFAULT_INTERVAL_NS;
	cp_int64_t					tmp_lost_times = CP_PLAYER_MAX_HEARTBEAT_LOST_TIMES;
	cp_char_t					tmp_buf[CP_APP_DEFAULT_BUFFER_LENGTH] = { 0, };




	//��ȡ�䴦����
	tmp_interval = cp_conf_xml_gettime_ns(app->conf->conf_xml,
		CP_PLAYER_CONF_STRING_GENERAL, CP_PLAYER_CONF_STRING_HEARTBEAT_INTERVAL, 0);
	if (tmp_interval <= 0) {
		cp_app_log(warn, app,
			"get_heartbeat_configure_info() warning. cp_conf_xml_gettime_ns() element[%s : %s] value[%d ns] failed! used default[%d ns]",
			CP_PLAYER_CONF_STRING_GENERAL,
			CP_PLAYER_CONF_STRING_HEARTBEAT_INTERVAL,
			tmp_interval,
			CP_PLAYER_HEARTBEAT_DEFAULT_INTERVAL_NS);

		tmp_interval = CP_PLAYER_HEARTBEAT_DEFAULT_INTERVAL_NS;
	}
	if (tmp_interval <= CP_PLAYER_HEARTBEAT_MIN_INTERVAL_NS) {
		tmp_interval = CP_PLAYER_HEARTBEAT_DEFAULT_INTERVAL_NS;
	}

	hm->heartbeat_interval_ms = tmp_interval / (CP_CONF_XML_TIME_THOUND * CP_CONF_XML_TIME_THOUND);

	//��ȡ�䴦����
	tmp_lost_times = cp_conf_xml_getint(app->conf->conf_xml,
		CP_PLAYER_CONF_STRING_GENERAL, CP_PLAYER_CONF_STRING_HEARTBEAT_LOST_TIMES, CP_PLAYER_MAX_HEARTBEAT_LOST_TIMES);
	if (tmp_lost_times < CP_PLAYER_MAX_HEARTBEAT_LOST_TIMES) {
		cp_app_log(warn, app,
			"get_heartbeat_configure_info() warning. cp_conf_xml_gettime_ns() element[%s : %s] value[%d] failed! used default[%d]",
			CP_PLAYER_CONF_STRING_GENERAL,
			CP_PLAYER_CONF_STRING_HEARTBEAT_LOST_TIMES,
			tmp_lost_times,
			CP_PLAYER_MAX_HEARTBEAT_LOST_TIMES);

		tmp_lost_times = CP_PLAYER_MAX_HEARTBEAT_LOST_TIMES;
	}
	hm->heartbeat_interval_lost_times = tmp_lost_times;

	return 0;
}

/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: init_heartbeat_manager
*
* ����˵��: ��ʼ��������������Ϣ
*
* ��    ��: cp_app_t					*app					[in]����˵��
* ��    ��: cp_heartbeat_manager_t * hm						[in]����˵��
*
* �� �� ֵ: int
*           0  : �ɹ� 
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2016-11-03 18:06:45
******************************************************************************************************/
int init_heartbeat_manager(cp_app_t	*app, cp_heartbeat_manager_t *hm)
{
	cp_void_t				*tmp_mem = CP_NULL;
	int						element_size = CP_PLAYER_MAX_DEVICE_NUMBER;


	if (!hm) {
		return -1;
	}

	hm->app = app;
	hm->logger = app->logger;

	//����һ���ڴ��
	hm->mpool = cp_create_mpool(CP_APP_DEFAULT_BUFFER_LENGTH);
	if (!hm->mpool) {
		cp_log_error(hm->logger, "init_heartbeat_manager () error reason: cp_create_mpool() failed!");
		return -2;
	}

	//Ϊ����ָ�봴���洢�ռ�
	tmp_mem = cp_mpalloc(hm->mpool, (cp_sizeof(cp_device_heartbeat_t*) * (CP_PLAYER_MAX_DEVICE_NUMBER)));
	if (!tmp_mem) {
		cp_log_error(hm->logger, "init_heartbeat_manager() error! malloc device heartbeat buffer error. manager_size[%d]",
			CP_PLAYER_MAX_DEVICE_NUMBER);
		return -3;
	}
	cp_memset(tmp_mem, 0, cp_sizeof(cp_device_heartbeat_t*) * (CP_PLAYER_MAX_DEVICE_NUMBER));
	cp_array_init(&(hm->device_heartbeats), tmp_mem, cp_sizeof(cp_device_heartbeat_t*), (CP_PLAYER_MAX_DEVICE_NUMBER));

	//Ϊ�����豸����ָ�봴���洢�ռ�
	tmp_mem = cp_mpalloc(hm->mpool, (cp_sizeof(cp_device_heartbeat_t*) * (CP_PLAYER_MAX_DEVICE_NUMBER)));
	if (!tmp_mem) {
		cp_log_error(hm->logger, "init_heartbeat_manager() error! malloc failed device heartbeat buffer error. manager_size[%d]",
			CP_PLAYER_MAX_DEVICE_NUMBER);
		return -3;
	}
	cp_memset(tmp_mem, 0, cp_sizeof(cp_device_heartbeat_t*) * (CP_PLAYER_MAX_DEVICE_NUMBER));
	cp_array_init(&(hm->failed_device_heartbeats), tmp_mem, cp_sizeof(cp_device_heartbeat_t*), (CP_PLAYER_MAX_DEVICE_NUMBER));
	
	//��ʼ��������Ϣ������������Ƶĵ������ߵ������߶���
	cp_lockfree_queue_init(&hm->lockfree_queue, cp_lockfree_queue_mode_qbss);
	cp_lockfree_queue_set_option(&hm->lockfree_queue, cp_lockfree_queue_option_bounded, &element_size);

	//����һ���������ͻ���
	tmp_mem = cp_mpalloc(hm->mpool, (cp_sizeof(cp_char_t) * CP_PLAYER_HEARTBEAT_DEFAULT_DATA_LENGTH));
	if (!tmp_mem) {
		cp_log_error(hm->logger, "init_heartbeat_manager() error! malloc heartbeat data buffer error. manager_size[%d]",
			CP_PLAYER_HEARTBEAT_DEFAULT_DATA_LENGTH);
		return -3;
	}
	cp_buf_assemble(&hm->heartbeat_data, tmp_mem, (cp_sizeof(cp_char_t) * CP_PLAYER_HEARTBEAT_DEFAULT_DATA_LENGTH));

	//�����������ʱ��
	get_heartbeat_configure_info(app, hm);

	return 0;
}


/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: start_heartbeat_manager
*
* ����˵��: ��ʼ����������
*
* ��    ��: cp_heartbeat_manager_t * hm						[in]����˵��
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
int start_heartbeat_manager(cp_heartbeat_manager_t *hm)
{
	if (!hm) {
		return -1;
	}
	//��������
	cp_lockfree_queue_start(&hm->lockfree_queue);
	return 0;
}


/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: stop_heartbeat_manager
*
* ����˵��: ֹͣ����������
*
* ��    ��: cp_heartbeat_manager_t * hm						[in]����˵��
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
int stop_heartbeat_manager(cp_heartbeat_manager_t *hm)
{

	return 0;
}


/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: init_device_heartbeat
*
* ����˵��: ��ʼ���豸��������Ϣ
*
* ��    ��: cp_heartbeat_manager_t * hm						[in]����˵��
* ��    ��: cp_device_heartbeat_t * dhb						[in]����˵��
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
int init_device_heartbeat(cp_heartbeat_manager_t *hm, cp_device_heartbeat_t *dhb)
{
	if (!dhb) {
		return -1;
	}

	dhb->heartbeat_manager = hm;

	cp_lockfree_queue_element_init(&hm->lockfree_queue, 
		&dhb->lf_queue_element, &dhb->di, dhb);
	return 0;
}


/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: send_device_heartbeat
*
* ����˵��: �����豸������Ϣ
*
* ��    ��: cp_heartbeat_manager_t * hm						[in]����˵��
* ��    ��: cp_device_heartbeat_t * dhb						[in]����˵��
*
* �� �� ֵ: int
*           0  : �ɹ� 
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2016-11-03 18:07:47
******************************************************************************************************/
int send_device_heartbeat(cp_heartbeat_manager_t *hm, cp_device_heartbeat_t *dhb)
{
	if (!dhb) {
		return -1;
	}
	
	cp_lockfree_queue_push(&hm->lockfree_queue, &dhb->lf_queue_element, 0, CP_NULL);
	return 0;
}

cp_device_heartbeat_t *get_device_heartbeat(cp_heartbeat_manager_t *hm)
{
	cp_lockfree_queue_element_t	*tmp_fl_queue_elem = CP_NULL;


	if (!hm) {
		return CP_NULL;
	}

	cp_lockfree_queue_pop(&hm->lockfree_queue, &tmp_fl_queue_elem);
	if (!tmp_fl_queue_elem) {
		return CP_NULL;
	}

	return (cp_device_heartbeat_t*)(tmp_fl_queue_elem->value);
}
