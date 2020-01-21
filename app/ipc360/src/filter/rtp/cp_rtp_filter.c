/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/
#include "cp_rtp_filter.h"
#include "cp_ipc_func_manager_core.h"



cp_rtp_filter_t *cp_rtp_filter_create();
/*ģ�鴴���ӿڣ���ʾ����һ��ģ��*/
cp_int32_t init_rtp_filter(cp_rtp_filter_t *rtp_filter, const cp_rtp_filter_info_t *rtp_filter_info);
/*ģ������нӿڣ���ģ��init֮�󣬻ᱻ����*/
cp_int32_t open_rtp_filter(cp_rtp_filter_t *rtp_filter, const cp_rtp_filter_info_t *rtp_filter_info);
/*��ȡģ�����ݣ�flagΪ��ȡģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��*/
cp_int32_t read_rtp_filter(cp_rtp_filter_t *rtp_filter, cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag);
/*дģ�����ݣ�flagΪдģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��*/
cp_int32_t write_rtp_filter(cp_rtp_filter_t *rtp_filter, const cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag);
/*�ر�ģ��*/
cp_int32_t close_rtp_filter(cp_rtp_filter_t *rtp_filter);
/*�˳�ģ��*/
cp_int32_t exit_rtp_filter(cp_rtp_filter_t *rtp_filter);
/*����ģ�����*/
cp_int32_t set_option_rtp_filter(cp_rtp_filter_t *rtp_filter, cp_int32_t optname, const cp_void_t* optval);
cp_int32_t get_option_rtp_filter(cp_rtp_filter_t *rtp_filter, cp_int32_t optname, cp_void_t* optval);


#if 0
cp_int32_t listen_rtp_filter(cp_socket_t *socket, cp_sockaddr_in *addr);											/*�򿪼���*/
cp_int32_t connect_rtp_filter(cp_socket_t *socket, cp_sockaddr_in *addr);										/*��ʼ����*/
cp_int32_t read_s_rtp_filter(cp_rtp_filter_t *cp_s, const cp_buf_t *buf, cp_int32_t nread, cp_int32_t flags);	/*������*/
cp_int32_t write_s_rtp_filter(cp_socket_t *socket, const cp_buf_t *buf, cp_int32_t nread, const cp_sockaddr_in *remote_addr, cp_int32_t flags);
cp_int32_t close_s_rtp_filter(cp_socket_t *socket);																/*�ر�����*/
#endif

cp_int32_t connect_cb_rtp_filter(cp_socket_t *socket, cp_int32_t status);										/*���ӻص�����*/
cp_int32_t close_cb_rtp_filter(cp_socket_t *socket, cp_int32_t status);											/*�رջص�����*/
cp_int32_t read_cb_rtp_filter(cp_socket_t *socket, const cp_buf_t *buf, cp_int32_t nread, cp_int32_t status);	/*���ص�����*/
cp_int32_t write_cb_rtp_filter(cp_socket_t *socket, cp_int32_t status);											/*д�ص�����*/
cp_int32_t error_cb_rtp_filter(cp_socket_t *socket, cp_int32_t status);											/*����ص�����*/

cp_rtp_filter_t* create_rtp_filter(cp_module_register_t *register_info, cp_socket_manager_t *manager, cp_rtp_filter_info_t *info)
{
	cp_int32_t							ret_int = 0;
	cp_rtp_filter_t						*tmp_module = CP_NULL;
	cp_pool_info_t						tmp_pool_info = { 0, };


	if (!register_info || !manager || !info) {
		return CP_NULL;
	}

	tmp_module = cp_malloc_module(manager, cp_rtp_filter_t, &tmp_pool_info);
	if (!tmp_module) {
		return CP_NULL;
	}
	CP_FILTER_MODULE_SET_HANDLERS(tmp_module, rtp_filter);

	return tmp_module;
}

cp_int32_t destroy_rtp_filter(cp_rtp_filter_manager_t *manager, cp_rtp_filter_t* rtp_filter)
{
	if (!manager || !rtp_filter) {
		return -1;
	}
	cp_free_module(rtp_filter);
	return 0;
}

/*ģ�鴴���ӿڣ���ʾ����һ��ģ��*/
cp_int32_t init_rtp_filter(cp_rtp_filter_t *rtp_filter, const cp_rtp_filter_info_t *rtp_filter_info)
{
	return 0;
}
/*ģ������нӿڣ���ģ��init֮�󣬻ᱻ����*/
cp_int32_t open_rtp_filter(cp_rtp_filter_t *rtp_filter, const cp_rtp_filter_info_t *rtp_filter_info)
{
	return 0;
}
/*��ȡģ�����ݣ�flagΪ��ȡģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��*/
cp_int32_t read_rtp_filter(cp_rtp_filter_t *rtp_filter, cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag)
{
	return 0;
}
/*дģ�����ݣ�flagΪдģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��*/
cp_int32_t write_rtp_filter(cp_rtp_filter_t *rtp_filter, const cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag)
{
	return 0;
}
/*�ر�ģ��*/
cp_int32_t close_rtp_filter(cp_rtp_filter_t *rtp_filter)
{
	return 0;
}
/*�˳�ģ��*/
cp_int32_t exit_rtp_filter(cp_rtp_filter_t *rtp_filter)
{
	return 0;
}
/*����ģ�����*/
cp_int32_t set_option_rtp_filter(cp_rtp_filter_t *rtp_filter, cp_int32_t optname, const cp_void_t* optval)
{
	return 0;
}

cp_int32_t get_option_rtp_filter(cp_rtp_filter_t *rtp_filter, cp_int32_t optname, cp_void_t* optval)
{
	return 0;
}

#if 0
cp_int32_t listen_rtp_filter(cp_socket_t *socket, cp_sockaddr_in *addr)
{
	return 0;
}

cp_int32_t connect_rtp_filter(cp_socket_t *socket, cp_sockaddr_in *addr)
{
	return 0;
}

cp_int32_t read_s_rtp_filter(cp_rtp_filter_t *cp_s, const cp_buf_t *buf, cp_int32_t nread, cp_int32_t flags)
{
	return 0;
}

cp_int32_t write_s_rtp_filter(cp_socket_t *socket, const cp_buf_t *buf, cp_int32_t nread, const cp_sockaddr_in *remote_addr, cp_int32_t flags)
{
	return 0;
}

cp_int32_t close_s_rtp_filter(cp_socket_t *socket)
{
	return 0;
}
#endif

cp_int32_t connect_cb_rtp_filter(cp_socket_t *socket, cp_int32_t status)
{
	return 0;
}

cp_int32_t close_cb_rtp_filter(cp_socket_t *socket, cp_int32_t status)
{
	return 0;
}

cp_int32_t read_cb_rtp_filter(cp_socket_t *socket, const cp_buf_t *buf, cp_int32_t nread, cp_int32_t status)
{
	cp_int32_t					ret_int = 0;



	return ret_int;
}

cp_int32_t write_cb_rtp_filter(cp_socket_t *socket, cp_int32_t status)
{
	return 0;
}

cp_int32_t error_cb_rtp_filter(cp_socket_t *socket, cp_int32_t status)
{
	return 0;
}

