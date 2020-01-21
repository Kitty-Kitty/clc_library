/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/
#include "cp_ptp_func.h"
#include "cp_ptp_func_proc.h"



cp_ptp_func_t *cp_ptp_func_create();
/*ģ���ʼ���ӿڣ���ģ��create֮�󣬻ᱻ����*/
cp_int32_t init_ptp_func(cp_ptp_func_t *ptp_func, const cp_ptp_func_info_t *ptp_func_info);
/*ģ������нӿڣ���ģ��init֮�󣬻ᱻ����*/
cp_int32_t open_ptp_func(cp_ptp_func_t *ptp_func, const cp_ptp_func_info_t *ptp_func_info);
/*��ȡģ�����ݣ�flagΪ��ȡģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��*/
cp_int32_t read_ptp_func(cp_ptp_func_t *ptp_func, cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag);
/*дģ�����ݣ�flagΪдģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��*/
cp_int32_t write_ptp_func(cp_ptp_func_t *ptp_func, const cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag);
/*�ر�ģ��*/
cp_int32_t close_ptp_func(cp_ptp_func_t *ptp_func);
/*�˳�ģ��*/
cp_int32_t exit_ptp_func(cp_ptp_func_t *ptp_func);
/*����ģ�����*/
cp_int32_t set_option_ptp_func(cp_ptp_func_t *ptp_func, cp_int32_t optname, const cp_void_t* optval);
cp_int32_t get_option_ptp_func(cp_ptp_func_t *ptp_func, cp_int32_t optname, cp_void_t* optval);

//��ptp�� socket
cp_int32_t open_ptp_multicast_socket(cp_ptp_func_t *ptp_func, cp_char_t *buf, cp_int32_t len);

//�ر��鲥
cp_int32_t close_ptp_multicast_socket(cp_ptp_func_t *ptp_func);

//����ptp filter
cp_int32_t set_ptp_multicast_data_filter(cp_ptp_func_t *ptp_func, cp_char_t *buf, cp_int32_t len);


#if 0
cp_int32_t listen_ptp_func(cp_socket_t *socket, cp_sockaddr_in *addr);											/*�򿪼���*/
cp_int32_t connect_ptp_func(cp_socket_t *socket, cp_sockaddr_in *addr);										/*��ʼ����*/
cp_int32_t read_s_ptp_func(cp_ptp_func_t *cp_s, const cp_buf_t *buf, cp_int32_t nread, cp_int32_t flags);	/*������*/
cp_int32_t write_s_ptp_func(cp_socket_t *socket, const cp_buf_t *buf, cp_int32_t nread, const cp_sockaddr_in *remote_addr, cp_int32_t flags);
cp_int32_t close_s_ptp_func(cp_socket_t *socket);																/*�ر�����*/
#endif

cp_int32_t connect_cb_ptp_func(cp_socket_t *socket, cp_int32_t status);										/*���ӻص�����*/
cp_int32_t close_cb_ptp_func(cp_socket_t *socket, cp_int32_t status);											/*�رջص�����*/
cp_int32_t read_cb_ptp_func(cp_socket_t *socket, const cp_buf_t *buf, cp_int32_t nread, cp_int32_t status);	/*���ص�����*/
cp_int32_t write_cb_ptp_func(cp_socket_t *socket, cp_int32_t status);											/*д�ص�����*/
cp_int32_t error_cb_ptp_func(cp_socket_t *socket, cp_int32_t status);											/*����ص�����*/


cp_ptp_func_t* create_ptp_func(cp_module_register_t *register_info, cp_socket_manager_t *manager, cp_ptp_func_info_t *info)
{
	cp_int32_t							ret_int = 0;
	cp_ptp_func_t						*tmp_module = CP_NULL;
	cp_pool_info_t						tmp_pool_info = { 0, };


	if (!register_info || !manager || !info) {
		return CP_NULL;
	}

	tmp_module = cp_malloc_module(manager, cp_ptp_func_t, &tmp_pool_info);
	if (!tmp_module) {
		return CP_NULL;
	}
	CP_FUNC_MODULE_SET_HANDLERS(tmp_module, ptp_func);

	return tmp_module;
}

cp_int32_t destroy_ptp_func(cp_player_func_manager_t *manager, cp_ptp_func_t* ptp_func)
{
	if (!manager || !ptp_func) {
		return -1;
	}
	cp_free_module(ptp_func);
	return 0;
}

/*ģ���ʼ���ӿڣ���ģ��create֮�󣬻ᱻ����*/
cp_int32_t init_ptp_func(cp_ptp_func_t *ptp_func, const cp_ptp_func_info_t *ptp_func_info)
{
	cp_int32_t						tmp_ret_int = 0;


	tmp_ret_int = ptp_func_parse_configure((cp_module_t*)ptp_func, &ptp_func->ptp_conf);
	if (tmp_ret_int) {
		cp_module_log(error, ptp_func, "init_ptp_func() error. ptp_func_parse_configure() error.");
		return -1;
	}

	return 0;
}
/*ģ������нӿڣ���ģ��init֮�󣬻ᱻ����*/
cp_int32_t open_ptp_func(cp_ptp_func_t *ptp_func, const cp_ptp_func_info_t *ptp_func_info)
{
	cp_int32_t							tmp_ret_int = 0;
	cp_char_t							tmp_buf[CP_APP_DEFAULT_BUFFER_LENGTH] = { 0, };


	if (!ptp_func->ptp_conf.is_use) {
		cp_module_log(warn, ptp_func,
			"open_ptp_func() warning. ptp configure set[%s = %d]. do not use ptp.",
			CP_PTP_FUNC_CONF_STRING_USE_PTP,
			ptp_func->ptp_conf.is_use);
		return 0;
	}

	tmp_ret_int = open_ptp_multicast_socket(ptp_func, tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH);
	if (tmp_ret_int) {
		cp_module_log(error, ptp_func, 
			"open_ptp_func() error. open_ptp_multicast_socket() error. reason:%s",
			tmp_buf);
		return -1;
	}
	else {
		cp_module_log(notice, ptp_func, 
			"open_ptp_multicast_socket() successed. listen udp [%s:%d] successed!",
 			ptp_func->ptp_conf.address,
 			ptp_func->ptp_conf.port);
	}

	return 0;
}
/*��ȡģ�����ݣ�flagΪ��ȡģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��*/
cp_int32_t read_ptp_func(cp_ptp_func_t *ptp_func, cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag)
{
	return 0;
}
/*дģ�����ݣ�flagΪдģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��*/
cp_int32_t write_ptp_func(cp_ptp_func_t *ptp_func, const cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag)
{
	cp_int32_t									tmp_ret_int = 0;
	cp_group_timestamp_t						*tmp_group_ts = CP_NULL;
	cp_player_t									*tmp_player = (cp_player_t*)ptp_func->manager->app;
	cp_player_info_t							*tmp_player_info = (cp_player_info_t *)(tmp_player->app_info);
	cp_int64_t									tmp_offset_us = 0;



	if (!ptp_func->ptp_conf.is_use) {
		cp_module_log(warn, ptp_func,
			"write_ptp_func() warning. ptp configure set[%s = %d]. do not use ptp.",
			CP_PTP_FUNC_CONF_STRING_USE_PTP,
			ptp_func->ptp_conf.is_use);
		return 0;
	}

	if (cp_player_func_flag_group_timestamp == flag &&
		len == cp_sizeof(cp_group_timestamp_t*)) {
		tmp_group_ts = (cp_group_timestamp_t *)(*buf);
		if (tmp_group_ts && tmp_group_ts->id == tmp_player_info->device_info->host.group) {
			//��ֵptpʱ��
			cp_player_update_timestamp(&tmp_player_info->player_timestamp, tmp_group_ts);

			//��ptp debug�ļ�
			tmp_ret_int = open_ptp_debug_file(ptp_func, tmp_player_info->device_info->host.group);
			if (tmp_ret_int) {
				cp_module_log(error, ptp_func, "write_ptp_func() error. open_ptp_debug_file() error.");
				return -1;
			}

			//��ӡptp  debug��Ϣ
			print_ptp_debug_info(ptp_func, &tmp_player_info->player_timestamp);
		}
	}
	return 0;
}
/*�ر�ģ��*/
cp_int32_t close_ptp_func(cp_ptp_func_t *ptp_func)
{
	cp_int32_t							tmp_ret_int = 0;


	if (!ptp_func->ptp_conf.is_use) {
		cp_module_log(warn, ptp_func,
			"close_ptp_func() warning. ptp configure set[%s = %d]. do not use ptp.",
			CP_PTP_FUNC_CONF_STRING_USE_PTP,
			ptp_func->ptp_conf.is_use);
		return 0;
	}

	tmp_ret_int = close_ptp_debug_file(ptp_func);
	if (tmp_ret_int) {
		cp_module_log(error, ptp_func, "init_ptp_func() error. close_ptp_debug_file() error.");
		return -1;
	}

	return 0;
}
/*�˳�ģ��*/
cp_int32_t exit_ptp_func(cp_ptp_func_t *ptp_func)
{
	return 0;
}
/*����ģ�����*/
cp_int32_t set_option_ptp_func(cp_ptp_func_t *ptp_func, cp_int32_t optname, const cp_void_t* optval)
{
	
	return 0;
}

cp_int32_t get_option_ptp_func(cp_ptp_func_t *ptp_func, cp_int32_t optname, cp_void_t* optval)
{
	return 0;
}

#if 0
cp_int32_t listen_ptp_func(cp_socket_t *socket, cp_sockaddr_in *addr)
{
	return 0;
}

cp_int32_t connect_ptp_func(cp_socket_t *socket, cp_sockaddr_in *addr)
{
	return 0;
}

cp_int32_t read_s_ptp_func(cp_ptp_func_t *cp_s, const cp_buf_t *buf, cp_int32_t nread, cp_int32_t flags)
{
	return 0;
}

cp_int32_t write_s_ptp_func(cp_socket_t *socket, const cp_buf_t *buf, cp_int32_t nread, const cp_sockaddr_in *remote_addr, cp_int32_t flags)
{
	return 0;
}

cp_int32_t close_s_ptp_func(cp_socket_t *socket)
{
	return 0;
}
#endif

cp_int32_t connect_cb_ptp_func(cp_socket_t *socket, cp_int32_t status)
{
	cp_buf_t				*buf;
	cp_int32_t				tmp_read_length = 0;



	if (!socket->data) {
		return -1;
	}

	if (cp_player_module_type_ptp_func !=
		((cp_ptp_func_t*)(socket->data))->register_info.type) {
		return -2;
	}

	//ֻ��tcp��ͷ�������ı��Ķ�һ������
	if (CP_SOCKET_CHECK_TYPE(socket, cp_socket_type_tcp)) {
		tmp_read_length = CSS_GMP_GMPH_SEMH_LEN;
	}
	else {
		tmp_read_length = 1024;
	}
	//����ռ�
	buf = cp_palloc(socket->pool, cp_sizeof(cp_buf_t) + tmp_read_length);
	if (!buf) {
		return -1;
	}
	cp_buf_assemble(buf, (cp_uchar_t*)buf + cp_sizeof(cp_buf_t), tmp_read_length);
	cp_buf_memzero(buf);

	//CP_SOCKET_MODULE_SET_CALLBACK_HANDLERS(socket, ptp_func);
	cp_read_socket(socket, buf, tmp_read_length, 0);
	return 0;
}

cp_int32_t close_cb_ptp_func(cp_socket_t *socket, cp_int32_t status)
{
	return 0;
}

cp_int32_t read_cb_ptp_func(cp_socket_t *socket, const cp_buf_t *buf, cp_int32_t nread, cp_int32_t status)
{
	cp_int32_t					ret_int = 0;
	cp_ptp_func_t*			tmp_ptp_func = CP_NULL;


	//����� ���ݲ���filter����
	if (!socket->data || !((cp_ptp_func_t*)(socket->data))->filter ||
		!((cp_ptp_func_t*)(socket->data))->filter->read_cb) {
		return -1;
	}

	((cp_ptp_func_t*)(socket->data))->filter->read_cb(socket, buf, nread, status);
	cp_buf_clear(socket->buf);

	return ret_int;
}

cp_int32_t write_cb_ptp_func(cp_socket_t *socket, cp_int32_t status)
{
	return connect_cb_ptp_func(socket, status);
}

cp_int32_t error_cb_ptp_func(cp_socket_t *socket, cp_int32_t status)
{
	return 0;
}



/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: open_ptp_multicast_socket
*
* ����˵��: ��ptp�� socket
*
* ��    ��: cp_ptp_func_t * ptp_func						[in]����˵��
* ��    ��: cp_char_t * buf						[in]����˵��
* ��    ��: cp_int32_t len						[in]����˵��
*
* �� �� ֵ: cp_int32_t
*           0  : �ɹ�
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2016-11-25 15:18:29
******************************************************************************************************/
cp_int32_t open_ptp_multicast_socket(cp_ptp_func_t *ptp_func, cp_char_t *buf, cp_int32_t len)
{
	cp_int32_t							tmp_ret_int = 0;
	cp_char_t							tmp_buf[CP_APP_DEFAULT_BUFFER_LENGTH] = { 0, };
	cp_sockaddr_in						tmp_multicast_addr = { 0, };


	cp_memset(buf, 0, len);
	if (!ptp_func->ptp_conf.port || !cp_strlen(ptp_func->ptp_conf.address)) {
		cp_snprintf(buf, len, "url address [%s:%d] error.",
			ptp_func->ptp_conf.address,
			ptp_func->ptp_conf.port);
		return -1;
	}

	//����socket
	ptp_func->socket = cp_create_socket(ptp_func->manager->app, cp_socket_type_multicast);
	if (!ptp_func->socket) {
		cp_snprintf(buf, len, "cp_create_socket() error.");
		return -2;
	}

	ptp_func->socket->data = ptp_func;
	tmp_ret_int = set_ptp_multicast_data_filter(ptp_func, tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH);
	if (tmp_ret_int) {
		cp_snprintf(buf, len, "set_ptp_multicast_data_filter() error. %s", tmp_buf);
		return -3;
	}

	CP_SOCKET_MODULE_SET_CALLBACK_HANDLERS(ptp_func->socket, ptp_func);

	cp_ip4_addr(ptp_func->ptp_conf.address, ptp_func->ptp_conf.port, &tmp_multicast_addr);

	//����multicast����
	tmp_ret_int = cp_listen_socket(ptp_func->socket, &tmp_multicast_addr);
	if (tmp_ret_int) {
		cp_snprintf(buf, len, "cp_listen_socket() [%s:%d] error.",
			ptp_func->ptp_conf.address,
			ptp_func->ptp_conf.port);
		return -2;
	}

	return 0;
}

/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: close_ptp_multicast_socket
*
* ����˵��: �ر��鲥
*
* ��    ��: cp_ptp_func_t * ptp_func						[in]����˵��
*
* �� �� ֵ: cp_int32_t
*           0  : �ɹ�
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2016-12-14 16:26:50
******************************************************************************************************/
cp_int32_t close_ptp_multicast_socket(cp_ptp_func_t *ptp_func)
{
	if (ptp_func->socket) {
		cp_close_socket(ptp_func->socket);
		cp_destroy_module(ptp_func->socket->manager, ptp_func->socket);
	}
	return 0;
}

/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: set_video_multicast_data_filter
*
* ����˵��: ����multicast socket
*
* ��    ��: cp_ptp_func_t *ptp_func				[in]����˵��
* ��    ��: cp_char_t * buf						[in]����˵��
* ��    ��: cp_int32_t len						[in]����˵��
*
* �� �� ֵ: cp_int32_t
*           0  : �ɹ�
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2016-11-25 15:31:55
******************************************************************************************************/
cp_int32_t set_ptp_multicast_data_filter(cp_ptp_func_t *ptp_func, cp_char_t *buf, cp_int32_t len)
{
	cp_module_t								*tmp_module = CP_NULL;
	cp_int32_t								ret_int = 0;
	cp_char_t								tmp_buf[CP_APP_DEFAULT_BUFFER_LENGTH] = { 0, };



	cp_memset(buf, 0, len);

	tmp_module = cp_manager_get_sub_module(ptp_func->manager->app,
		cp_player_manager_type_filter, cp_player_module_type_ptp_filter);
	if (!tmp_module) {
		cp_snprintf(buf, len, "not found filter[ptp]");
		return -1;
	}
	ptp_func->filter = (cp_filter_t *)tmp_module;
	CP_MODULE_UPDATE_SINGLE_HANDLER_AND_TYPE(ptp_func->filter, ptp_func->socket, read_cb, cp_socket_read_cb_handle);

	return 0;
}
