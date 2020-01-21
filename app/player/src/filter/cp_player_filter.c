/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/
#include "cp_player_filter.h"
#include "cp_third_party.h"
#include "cp_include.h"
#include "css_status.h"



cp_player_filter_t *cp_player_filter_create();
/*ģ�鴴���ӿڣ���ʾ����һ��ģ��*/
cp_int32_t init_player_filter(cp_player_filter_t *player_filter, const cp_player_filter_info_t *player_filter_info);
/*ģ������нӿڣ���ģ��init֮�󣬻ᱻ����*/
cp_int32_t open_player_filter(cp_player_filter_t *player_filter, const cp_player_filter_info_t *player_filter_info);
/*��ȡģ�����ݣ�flagΪ��ȡģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��*/
cp_int32_t read_player_filter(cp_player_filter_t *player_filter, cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag);
/*дģ�����ݣ�flagΪдģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��*/
cp_int32_t write_player_filter(cp_player_filter_t *player_filter, const cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag);
/*�ر�ģ��*/
cp_int32_t close_player_filter(cp_player_filter_t *player_filter);
/*�˳�ģ��*/
cp_int32_t exit_player_filter(cp_player_filter_t *player_filter);
/*����ģ�����*/
cp_int32_t set_option_player_filter(cp_player_filter_t *player_filter, cp_int32_t optname, const cp_void_t* optval);
cp_int32_t get_option_player_filter(cp_player_filter_t *player_filter, cp_int32_t optname, cp_void_t* optval);


#if 0
cp_int32_t listen_player_filter(cp_socket_t *socket, cp_sockaddr_in *addr);											/*�򿪼���*/
cp_int32_t connect_player_filter(cp_socket_t *socket, cp_sockaddr_in *addr);										/*��ʼ����*/
cp_int32_t read_s_player_filter(cp_player_filter_t *cp_s, const cp_buf_t *buf, cp_int32_t nread, cp_int32_t flags);	/*������*/
cp_int32_t write_s_player_filter(cp_socket_t *socket, const cp_buf_t *buf, cp_int32_t nread, const cp_sockaddr_in *remote_addr, cp_int32_t flags);
cp_int32_t close_s_player_filter(cp_socket_t *socket);																/*�ر�����*/
#endif

cp_int32_t connect_cb_player_filter(cp_socket_t *socket, cp_int32_t status);										/*���ӻص�����*/
cp_int32_t close_cb_player_filter(cp_socket_t *socket, cp_int32_t status);											/*�رջص�����*/
cp_int32_t read_cb_player_filter(cp_socket_t *socket, const cp_buf_t *buf, cp_int32_t nread, cp_int32_t status);	/*���ص�����*/
cp_int32_t write_cb_player_filter(cp_socket_t *socket, cp_int32_t status);											/*д�ص�����*/
cp_int32_t error_cb_player_filter(cp_socket_t *socket, cp_int32_t status);											/*����ص�����*/

/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: player_filter_tcp_data_integrity
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
cp_filter_status_e player_filter_tcp_data_integrity(cp_socket_t *socket, const cp_buf_t *buf, cp_int32_t nread, cp_int32_t status);


cp_filter_status_e player_filter_udp_data_integrity(cp_socket_t *socket, const cp_buf_t *buf, cp_int32_t nread, cp_int32_t status);


/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: player_filter_process_func
*
* ����˵��: ����func��������
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
* �������ڣ�2016-07-01 15:32:56
******************************************************************************************************/
cp_int32_t player_filter_process_func(cp_socket_t *socket, const cp_buf_t *buf, cp_int32_t nread, cp_int32_t status);



cp_player_filter_t* create_player_filter(cp_module_register_t *register_info, cp_socket_manager_t *manager, cp_player_filter_info_t *info)
{
	cp_int32_t							ret_int = 0;
	cp_player_filter_t					*tmp_module = CP_NULL;
	cp_pool_info_t						tmp_pool_info = { 0, };


	if (!register_info || !manager || !info) {
		return CP_NULL;
	}

	tmp_module = cp_malloc_module(manager, cp_player_filter_t, &tmp_pool_info);
	if (!tmp_module) {
		return CP_NULL;
	}
	CP_FILTER_MODULE_SET_HANDLERS(tmp_module, player_filter);
	return tmp_module;
}

cp_int32_t destroy_player_filter(cp_player_filter_manager_t *manager, cp_player_filter_t* player_filter)
{
	if (!manager || !player_filter) {
		return -1;
	}
	cp_free_module(player_filter);
	return 0;
}

/*ģ�鴴���ӿڣ���ʾ����һ��ģ��*/
cp_int32_t init_player_filter(cp_player_filter_t *player_filter, const cp_player_filter_info_t *player_filter_info)
{
	return 0;
}
/*ģ������нӿڣ���ģ��init֮�󣬻ᱻ����*/
cp_int32_t open_player_filter(cp_player_filter_t *player_filter, const cp_player_filter_info_t *player_filter_info)
{
	return 0;
}
/*��ȡģ�����ݣ�flagΪ��ȡģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��*/
cp_int32_t read_player_filter(cp_player_filter_t *player_filter, cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag)
{
	return 0;
}
/*дģ�����ݣ�flagΪдģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��*/
cp_int32_t write_player_filter(cp_player_filter_t *player_filter, const cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag)
{
	return 0;
}
/*�ر�ģ��*/
cp_int32_t close_player_filter(cp_player_filter_t *player_filter)
{
	return 0;
}
/*�˳�ģ��*/
cp_int32_t exit_player_filter(cp_player_filter_t *player_filter)
{
	return 0;
}
/*����ģ�����*/
cp_int32_t set_option_player_filter(cp_player_filter_t *player_filter, cp_int32_t optname, const cp_void_t* optval)
{
	return 0;
}

cp_int32_t get_option_player_filter(cp_player_filter_t *player_filter, cp_int32_t optname, cp_void_t* optval)
{
	return 0;
}

#if 0
cp_int32_t listen_player_filter(cp_socket_t *socket, cp_sockaddr_in *addr)
{
	return 0;
}

cp_int32_t connect_player_filter(cp_socket_t *socket, cp_sockaddr_in *addr)
{
	return 0;
}

cp_int32_t read_s_player_filter(cp_player_filter_t *cp_s, const cp_buf_t *buf, cp_int32_t nread, cp_int32_t flags)
{
	return 0;
}

cp_int32_t write_s_player_filter(cp_socket_t *socket, const cp_buf_t *buf, cp_int32_t nread, const cp_sockaddr_in *remote_addr, cp_int32_t flags)
{
	return 0;
}

cp_int32_t close_s_player_filter(cp_socket_t *socket)
{
	return 0;
}
#endif

cp_int32_t connect_cb_player_filter(cp_socket_t *socket, cp_int32_t status)
{
	return 0;
}

cp_int32_t close_cb_player_filter(cp_socket_t *socket, cp_int32_t status)
{
	return 0;
}

cp_int32_t read_cb_player_filter(cp_socket_t *socket, const cp_buf_t *buf, cp_int32_t nread, cp_int32_t status)
{
	cp_int32_t					ret_int = 0;



	if (cp_socket_type_tcp == socket->socket_type) {
		//���ﴦ�����ݵ�������
		ret_int = player_filter_tcp_data_integrity(socket, buf, nread, status);
	} else {
		ret_int = player_filter_udp_data_integrity(socket, buf, nread, status);
	}
	
	if ((ret_int & cp_filter_status_match) && (ret_int & cp_filter_status_successorerror) 
		&& (ret_int & cp_filter_status_get_func)) {
		//���ݴ���ɹ�����func
		return player_filter_process_func(socket, buf, cp_buf_get_length(buf), status);
	}
	return ret_int;
}

cp_int32_t write_cb_player_filter(cp_socket_t *socket, cp_int32_t status)
{
	return 0;
}

cp_int32_t error_cb_player_filter(cp_socket_t *socket, cp_int32_t status)
{
	return 0;
}

cp_filter_status_e player_filter_tcp_data_integrity
	(cp_socket_t *socket, const cp_buf_t *buf, cp_int32_t nread, cp_int32_t status)
{
	gmp_gmph_bmh_t						*tmp_bmh = CP_NULL;
	gmp_gmph_semh_t						*tmp_semh = CP_NULL;
	cp_buf_t							*tmp_buf = (cp_buf_t *)buf;
	cp_int32_t							tmp_len = 0;


	//Э��ͷ��û����ȫ
	if (cp_buf_get_length(tmp_buf) < CSS_GMP_GMPH_SEMH_LEN) {
#if 0
		if (cp_buf_get_size(tmp_buf) < CSS_GMP_GMPH_SEMH_LEN) {
			tmp_buf = cp_palloc(socket->pool, cp_sizeof(cp_buf_t) + CSS_GMP_GMPH_SEMH_LEN);
			if (!tmp_buf) {
				return 0;
			}
			cp_buf_assemble(tmp_buf, (cp_uchar_t*)tmp_buf + CSS_GMP_GMPH_SEMH_LEN, CSS_GMP_GMPH_SEMH_LEN);
		}
		//���²������
		CP_SOCKET_MODULE_SET_CALLBACK_HANDLERS(socket, player_filter);
		cp_read_socket(socket, CSS_GMP_GMPH_SEMH_LEN, tmp_buf, 0);
		return cp_filter_status_match | cp_filter_status_read_again;
#endif
		return 0;
	}

	//��������û������
	tmp_bmh = (gmp_gmph_bmh_t*)cp_buf_get_pos(tmp_buf);
	if (gmp_gmph_emh_type_semh == tmp_bmh->emht) {
		tmp_semh = (gmp_gmph_semh_t*)tmp_bmh;
		tmp_len = cp_buf_get_length(tmp_buf);
		//������ճɹ��򷵻�
		if (tmp_len >= (cp_int32_t)(tmp_semh->length + CSS_GMP_GMPH_SEMH_LEN)) {
			//��������Ѿ������꣬�򷵻سɹ�
			return cp_filter_status_match | cp_filter_status_successorerror | cp_filter_status_get_func;
		}
		//�ж�buf�ռ��С��������������´���һ��
		if (cp_buf_get_size(tmp_buf) < (cp_int32_t)(tmp_semh->length + CSS_GMP_GMPH_SEMH_LEN)) {
			tmp_buf = cp_palloc(socket->pool, cp_sizeof(cp_buf_t) + CSS_GMP_GMPH_SEMH_LEN + tmp_semh->length);
			if (!tmp_buf) {
				return 0;
			}
			cp_buf_assemble(tmp_buf, (cp_uchar_t*)tmp_buf + cp_sizeof(cp_buf_t), 
				CSS_GMP_GMPH_SEMH_LEN + tmp_semh->length);
			cp_buf_strcat(tmp_buf, cp_buf_get_pos(buf), cp_buf_get_length(buf));
		}
		//���²������
		CP_SOCKET_MODULE_SET_CALLBACK_HANDLERS(socket, player_filter);
		cp_read_socket(socket, tmp_buf, cp_buf_get_free_size(tmp_buf), 0);
		return cp_filter_status_match | cp_filter_status_read_again;
	}
	return 0;
}

cp_filter_status_e player_filter_udp_data_integrity
	(cp_socket_t *socket, const cp_buf_t *buf, cp_int32_t nread, cp_int32_t status)
{
	gmp_gmph_bmh_t						*tmp_bmh = CP_NULL;
	gmp_gmph_semh_t						*tmp_semh = CP_NULL;
	cp_int32_t							tmp_len = 0;



	//ȡ��semh��ͷ���ж�semh��С����
	tmp_bmh = (gmp_gmph_bmh_t*)cp_buf_get_pos(buf);
	if (gmp_gmph_emh_type_semh == tmp_bmh->emht) {
		tmp_semh = (gmp_gmph_semh_t*)tmp_bmh;
		tmp_len = cp_buf_get_length(buf);
		//������ճɹ��򷵻�
		if (tmp_len >= (cp_int32_t)(tmp_semh->length + CSS_GMP_GMPH_SEMH_LEN)) {
			//��������Ѿ������꣬�򷵻سɹ�
			return cp_filter_status_match | cp_filter_status_successorerror | cp_filter_status_get_func;
		}
		//ָ����롢ָ��ȡ����ı�š���״̬
		if (tmp_semh->status == CSS_NETWORK_STATUS_600) {
			if (socket->cache_buf) {
				cp_pfree(socket->pool, cp_buf_get_start(socket->cache_buf));
			}
			//���·���ָ��ռ��С
			socket->cache_buf = cp_palloc(socket->pool, cp_sizeof(cp_buf_t) + CSS_GMP_GMPH_SEMH_LEN + tmp_semh->length);
			if (!socket->cache_buf) {
				return 0;
			}
			cp_buf_strcat(socket->cache_buf, cp_buf_get_pos(buf), cp_buf_get_length(buf));
			return cp_filter_status_match | cp_filter_status_read_again;
		}

		if (tmp_semh->status == CSS_NETWORK_STATUS_601) {
			if (socket->cache_buf) {
				cp_buf_strcat(socket->cache_buf, cp_buf_get_pos(buf), cp_buf_get_length(buf));
			}
			return cp_filter_status_match | cp_filter_status_read_again;
		}

		if (tmp_semh->status == CSS_NETWORK_STATUS_602) {
			if (socket->cache_buf) {
				cp_buf_strcat(socket->cache_buf, cp_buf_get_pos(buf), cp_buf_get_length(buf));
			}
			return cp_filter_status_match | cp_filter_status_successorerror | cp_filter_status_get_func;
		}
		//���²������
		CP_SOCKET_MODULE_SET_CALLBACK_HANDLERS(socket, player_filter);
		return cp_filter_status_successorerror;
	}

	return 0;
}

cp_int32_t player_filter_process_func(cp_socket_t *socket, const cp_buf_t *buf, cp_int32_t nread, cp_int32_t status)
{
	cp_queue_t								*modules;
	cp_queue_t								*current;
	cp_func_t								*func;
	cp_func_manager_t						*func_manager;
	cp_int32_t								ret_int = 0;
	cp_module_manager_info_t				tmp_module_manager_info;



	//����func managet��������
	CP_MODULE_MANAGER_INFO_SET_TYPE(&tmp_module_manager_info, cp_module_manager_type_func);
	func_manager = (cp_func_manager_t*)cp_get_manager(CP_NULL, &tmp_module_manager_info);
	if (func_manager) {
		modules = &func_manager->modules;
		for (current = cp_queue_next(modules); current != modules;
			current = cp_queue_next(current)) {
			func = cp_queue_data(current, cp_func_t, queue);
			if (func->read_cb) {
				ret_int = func->read_cb(socket, buf, nread, status);
				if (!(ret_int & cp_func_status_match)) {
					continue;
				}
				if ((ret_int & cp_func_status_successorerror) ||
					(ret_int & cp_func_status_read_again)) {
					return 0;
				}
				break;
			}
		}
	}
	return 0;
}

