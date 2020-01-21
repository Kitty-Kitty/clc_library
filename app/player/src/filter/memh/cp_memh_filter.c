/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/
#include "cp_memh_filter.h"
#include "cp_player_func_manager_core.h"



cp_memh_filter_t *cp_memh_filter_create();
/*ģ�鴴���ӿڣ���ʾ����һ��ģ��*/
cp_int32_t init_memh_filter(cp_memh_filter_t *memh_filter, const cp_memh_filter_info_t *memh_filter_info);
/*ģ������нӿڣ���ģ��init֮�󣬻ᱻ����*/
cp_int32_t open_memh_filter(cp_memh_filter_t *memh_filter, const cp_memh_filter_info_t *memh_filter_info);
/*��ȡģ�����ݣ�flagΪ��ȡģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��*/
cp_int32_t read_memh_filter(cp_memh_filter_t *memh_filter, cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag);
/*дģ�����ݣ�flagΪдģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��*/
cp_int32_t write_memh_filter(cp_memh_filter_t *memh_filter, const cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag);
/*�ر�ģ��*/
cp_int32_t close_memh_filter(cp_memh_filter_t *memh_filter);
/*�˳�ģ��*/
cp_int32_t exit_memh_filter(cp_memh_filter_t *memh_filter);
/*����ģ�����*/
cp_int32_t set_option_memh_filter(cp_memh_filter_t *memh_filter, cp_int32_t optname, const cp_void_t* optval);
cp_int32_t get_option_memh_filter(cp_memh_filter_t *memh_filter, cp_int32_t optname, cp_void_t* optval);


#if 0
cp_int32_t listen_memh_filter(cp_socket_t *socket, cp_sockaddr_in *addr);											/*�򿪼���*/
cp_int32_t connect_memh_filter(cp_socket_t *socket, cp_sockaddr_in *addr);										/*��ʼ����*/
cp_int32_t read_s_memh_filter(cp_memh_filter_t *cp_s, const cp_buf_t *buf, cp_int32_t nread, cp_int32_t flags);	/*������*/
cp_int32_t write_s_memh_filter(cp_socket_t *socket, const cp_buf_t *buf, cp_int32_t nread, const cp_sockaddr_in *remote_addr, cp_int32_t flags);
cp_int32_t close_s_memh_filter(cp_socket_t *socket);																/*�ر�����*/
#endif

cp_int32_t connect_cb_memh_filter(cp_socket_t *socket, cp_int32_t status);										/*���ӻص�����*/
cp_int32_t close_cb_memh_filter(cp_socket_t *socket, cp_int32_t status);											/*�رջص�����*/
cp_int32_t read_cb_memh_filter(cp_socket_t *socket, const cp_buf_t *buf, cp_int32_t nread, cp_int32_t status);	/*���ص�����*/
cp_int32_t write_cb_memh_filter(cp_socket_t *socket, cp_int32_t status);											/*д�ص�����*/
cp_int32_t error_cb_memh_filter(cp_socket_t *socket, cp_int32_t status);											/*����ص�����*/

/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: memh_filter_tcp_data_integrity
*
* ����˵��: У��������ݵ������ԣ��ж��Ƿ��Ѿ�������ȫ
*
* ��    ��: cp_socket_t * socket						[in]����˵��
* ��    ��: cp_int32_t nread							[in]����˵��
* ��    ��: const cp_buf_t * buf						[in]����˵��
* ��    ��: cp_int32_t status						[in]����˵��
*
* �� �� ֵ: cp_filter_status_e
*           0  : �ɹ�
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2016-06-30 20:32:52
******************************************************************************************************/
cp_filter_status_e memh_filter_tcp_data_integrity(cp_socket_t *socket, const cp_buf_t *buf, cp_int32_t nread, cp_int32_t status);


/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: memh_filter_udp_data_integrity
*
* ����˵��: ����udp����
*
* ��    ��: cp_socket_t * socket						[in]����˵��
* ��    ��: cp_int32_t nread						[in]����˵��
* ��    ��: const cp_buf_t * buf						[in]����˵��
* ��    ��: cp_int32_t status						[in]����˵��
*
* �� �� ֵ: cp_filter_status_e
*           0  : �ɹ� 
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2016-12-05 15:24:40
******************************************************************************************************/
cp_filter_status_e memh_filter_udp_data_integrity(cp_socket_t *socket, const cp_buf_t *buf, cp_int32_t nread, cp_int32_t status);


/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: memh_filter_process_media_func
*
* ����˵��: ����ý������
*
* ��    ��: cp_socket_t * socket						[in]����˵��
* ��    ��: cp_int32_t nread						[in]����˵��
* ��    ��: const cp_buf_t * buf						[in]����˵��
* ��    ��: cp_int32_t status						[in]����˵��
*
* �� �� ֵ: cp_int32_t
*           0  : �ɹ� 
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2016-12-05 15:25:21
******************************************************************************************************/
cp_int32_t memh_filter_process_media_func(cp_socket_t *socket, const cp_buf_t *buf, cp_int32_t nread, cp_int32_t status);

/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: memh_filter_process_player_func
*
* ����˵��: ���˴���memh ����
*
* ��    ��: cp_socket_t * socket						[in]����˵��
* ��    ��: cp_int32_t nread						[in]����˵��
* ��    ��: const cp_buf_t * buf						[in]����˵��
* ��    ��: cp_int32_t status						[in]����˵��
*
* �� �� ֵ: cp_int32_t
*           0  : �ɹ� 
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2016-12-05 11:25:16
******************************************************************************************************/
cp_int32_t memh_filter_process_player_func(cp_socket_t *socket, const cp_buf_t *buf, cp_int32_t nread, cp_int32_t status);




cp_memh_filter_t* create_memh_filter(cp_module_register_t *register_info, cp_socket_manager_t *manager, cp_memh_filter_info_t *info)
{
	cp_memh_filter_t					*tmp_module = CP_NULL;
	cp_pool_info_t						tmp_pool_info = { 0, };


	if (!register_info || !manager || !info) {
		return CP_NULL;
	}

	tmp_module = cp_malloc_module(manager, cp_memh_filter_t, &tmp_pool_info);
	if (!tmp_module) {
		return CP_NULL;
	}
	CP_FILTER_MODULE_SET_HANDLERS(tmp_module, memh_filter);

	return tmp_module;
}

cp_int32_t destroy_memh_filter(cp_memh_filter_manager_t *manager, cp_memh_filter_t* memh_filter)
{
	if (!manager || !memh_filter) {
		return -1;
	}

	cp_free_module(memh_filter);
	return 0;
}

/*ģ�鴴���ӿڣ���ʾ����һ��ģ��*/
cp_int32_t init_memh_filter(cp_memh_filter_t *memh_filter, const cp_memh_filter_info_t *memh_filter_info)
{
	return 0;
}
/*ģ������нӿڣ���ģ��init֮�󣬻ᱻ����*/
cp_int32_t open_memh_filter(cp_memh_filter_t *memh_filter, const cp_memh_filter_info_t *memh_filter_info)
{
	return 0;
}
/*��ȡģ�����ݣ�flagΪ��ȡģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��*/
cp_int32_t read_memh_filter(cp_memh_filter_t *memh_filter, cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag)
{
	return 0;
}
/*дģ�����ݣ�flagΪдģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��*/
cp_int32_t write_memh_filter(cp_memh_filter_t *memh_filter, const cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag)
{
	return 0;
}
/*�ر�ģ��*/
cp_int32_t close_memh_filter(cp_memh_filter_t *memh_filter)
{
	return 0;
}
/*�˳�ģ��*/
cp_int32_t exit_memh_filter(cp_memh_filter_t *memh_filter)
{
	return 0;
}
/*����ģ�����*/
cp_int32_t set_option_memh_filter(cp_memh_filter_t *memh_filter, cp_int32_t optname, const cp_void_t* optval)
{
	return 0;
}

cp_int32_t get_option_memh_filter(cp_memh_filter_t *memh_filter, cp_int32_t optname, cp_void_t* optval)
{
	return 0;
}

#if 0
cp_int32_t listen_memh_filter(cp_socket_t *socket, cp_sockaddr_in *addr)
{
	return 0;
}

cp_int32_t connect_memh_filter(cp_socket_t *socket, cp_sockaddr_in *addr)
{
	return 0;
}

cp_int32_t read_s_memh_filter(cp_memh_filter_t *cp_s, const cp_buf_t *buf, cp_int32_t nread, cp_int32_t flags)
{
	return 0;
}

cp_int32_t write_s_memh_filter(cp_socket_t *socket, const cp_buf_t *buf, cp_int32_t nread, const cp_sockaddr_in *remote_addr, cp_int32_t flags)
{
	return 0;
}

cp_int32_t close_s_memh_filter(cp_socket_t *socket)
{
	return 0;
}
#endif

cp_int32_t connect_cb_memh_filter(cp_socket_t *socket, cp_int32_t status)
{
	return 0;
}

cp_int32_t close_cb_memh_filter(cp_socket_t *socket, cp_int32_t status)
{
	return 0;
}

cp_int32_t read_cb_memh_filter(cp_socket_t *socket, const cp_buf_t *buf, cp_int32_t nread, cp_int32_t status)
{
	cp_int32_t					ret_int = 0;



	if (cp_socket_type_udp == socket->socket_type || 
		cp_socket_type_multicast == socket->socket_type) {
		ret_int = memh_filter_udp_data_integrity(socket, buf, nread, status);
	}
	
	return ret_int;
}

cp_int32_t write_cb_memh_filter(cp_socket_t *socket, cp_int32_t status)
{
	return 0;
}

cp_int32_t error_cb_memh_filter(cp_socket_t *socket, cp_int32_t status)
{
	return 0;
}

cp_filter_status_e memh_filter_tcp_data_integrity
	(cp_socket_t *socket, const cp_buf_t *buf, cp_int32_t nread, cp_int32_t status)
{
	return 0;
}

cp_filter_status_e memh_filter_udp_data_integrity
	(cp_socket_t *socket, const cp_buf_t *buf, cp_int32_t nread, cp_int32_t status)
{
	gmp_gmph_bmh_t						*tmp_bmh = CP_NULL;
	gmp_gmph_memh_t						*tmp_memh = CP_NULL;
	cp_buf_t							*tmp_buf = (cp_buf_t*)buf;
	cp_device_info_t					*tmp_pdi = ((cp_player_info_t*)(socket->manager->app->app_info))->device_info;
	cp_int64_t							tmp_length = 0;
	cp_int32_t							tmp_ret_int = cp_filter_status_successorerror;



	//ȡ��semh��ͷ���ж�semh��С����
	tmp_bmh = (gmp_gmph_bmh_t*)cp_buf_get_pos(tmp_buf);
	if (gmp_gmph_emh_type_memh != tmp_bmh->emht) {
		return cp_filter_status_successorerror;
	}

	//������
	if (push_a_memh_socket_buffer(socket->data, buf)) {
		cp_buf_clear(tmp_buf);
		return tmp_ret_int;
	}
	tmp_memh = (gmp_gmph_memh_t*)tmp_bmh;
	tmp_length = get_memh_socket_buffer_length(socket->data);
	if (css_media_network_metadata == tmp_memh->packet_type || 
		css_media_network_end == tmp_memh->packet_type) {
		//����ʹ����� func���д���
		if (cp_media_type_video_h264 == tmp_memh->media_type || 
			(cp_media_type_audio_begin < tmp_memh->media_type &&
			tmp_memh->media_type < cp_media_type_audio_end)) {
			memh_filter_process_media_func(socket, buf, nread, status);
		}
		else {
			cp_module_log(error, socket, "unsupport memh type[%d].", tmp_memh->media_type);
		}
	}
	tmp_buf = create_a_memh_socket_buffer(socket->pool, socket->data, (cp_int32_t)tmp_pdi->network.packet_length);
	if (!tmp_buf) {
		return tmp_ret_int;
	}

	//���²������
	CP_SOCKET_MODULE_SET_CALLBACK_HANDLERS(socket, memh_filter);
	//cp_read_socket(socket, tmp_buf, cp_buf_get_free_size(tmp_buf), 0);
	socket->buf = tmp_buf;
	return cp_filter_status_match | cp_filter_status_read_again;

	return 0;
}

cp_int32_t memh_filter_process_media_func(cp_socket_t *socket, const cp_buf_t *buf, cp_int32_t nread, cp_int32_t status)
{
	cp_func_t						*tmp_player_func = CP_NULL;
	cp_int32_t						ret_int = 0;



	if (!socket || !socket->data) {
		return -1;
	}
	tmp_player_func = get_memh_socket_buffer_func(socket->data);
	if (!tmp_player_func) {
		cp_module_log(error, socket, "memh_filter_process_media_func() error. not found video func.");
		return -1;
	}
	//��ʼ��ģ��
	ret_int = cp_write_module(tmp_player_func, &socket, cp_sizeof(cp_socket_t *), cp_player_func_flag_socket_point);
	if (ret_int) {
		cp_module_log(error, socket, "memh_filter_process_media_func() error. write video func module error.");
		return -1;
	}

	return 0;
}
