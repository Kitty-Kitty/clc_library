/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/
#include "cp_rtp_session.h"
#include "cp_ecam_hook_core.h"




cp_rtp_session_t *cp_rtp_session_create();

/*ģ�鴴���ӿڣ���ʾ����һ��ģ��*/
cp_int32_t init_rtp_session(cp_rtp_session_t *rtp_session, const cp_rtp_session_info_t *rtp_session_info);
/*ģ������нӿڣ���ģ��init֮�󣬻ᱻ����*/
cp_int32_t open_rtp_session(cp_rtp_session_t *rtp_session, const cp_rtp_session_info_t *rtp_session_info);
/*��ȡģ�����ݣ�flagΪ��ȡģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��*/
cp_int32_t read_rtp_session(cp_rtp_session_t *rtp_session, cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag);
/*дģ�����ݣ�flagΪдģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��*/
cp_int32_t write_rtp_session(cp_rtp_session_t *rtp_session, const cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag);
/*�ر�ģ��*/
cp_int32_t close_rtp_session(cp_rtp_session_t *rtp_session);
/*�˳�ģ��*/
cp_int32_t exit_rtp_session(cp_rtp_session_t *rtp_session);
/*����ģ�����*/
cp_int32_t set_option_rtp_session(cp_rtp_session_t *rtp_session, cp_int32_t optname, const cp_void_t* optval);
cp_int32_t get_option_rtp_session(cp_rtp_session_t *rtp_session, cp_int32_t optname, cp_void_t* optval);

cp_int32_t connect_cb_rtp_session(cp_socket_t *socket, cp_int32_t status);										/*���ӻص�����*/
cp_int32_t close_cb_rtp_session(cp_socket_t *socket, cp_int32_t status);											/*�رջص�����*/
cp_int32_t read_cb_rtp_session(cp_socket_t *socket, const cp_buf_t *buf, cp_int32_t nread, cp_int32_t status);	/*���ص�����*/
cp_int32_t write_cb_rtp_session(cp_socket_t *socket, cp_int32_t status);											/*д�ص�����*/
cp_int32_t error_cb_rtp_session(cp_socket_t *socket, cp_int32_t status);											/*����ص�����*/


/*����ģ��*/
cp_rtp_session_t* create_rtp_session(cp_module_register_t *register_info, cp_socket_manager_t *manager, cp_rtp_session_info_t *info)
{
	cp_int32_t							ret_int = 0;
	cp_rtp_session_t					*tmp_module = CP_NULL;
	cp_pool_info_t						tmp_pool_info = { 0, };
	

	if (!register_info || !manager || !info) {
		return CP_NULL;
	}

	tmp_module = cp_malloc_module(manager, cp_rtp_session_t, &tmp_pool_info);
	if (!tmp_module) {
		return CP_NULL;
	}

	CP_MODULE_SET_HANDLERS(tmp_module, rtp_session);
	CP_SOCKET_MODULE_SET_CALLBACK_HANDLERS(tmp_module, rtp_session);

	return tmp_module;
}
/*����ģ��*/
cp_int32_t destroy_rtp_session(cp_ecam_session_manager_t *manager, cp_rtp_session_t* rtp_session)
{
	if (!manager || !rtp_session) {
		return -1;
	}
	cp_free_module(rtp_session);
	return 0;
}


/*ģ�鴴���ӿڣ���ʾ����һ��ģ��*/
cp_int32_t init_rtp_session(cp_rtp_session_t *rtp_session, const cp_rtp_session_info_t *rtp_session_info)
{
	cp_ecam_hook_t							*tmp_hook;
	cp_ecam_hook_manager_t					*tmp_manager;
	cp_char_t								tmp_buf[CP_APP_DEFAULT_BUFFER_LENGTH] = { 0, };
	cp_module_info_t						tmp_module_info;
	cp_module_manager_info_t				tmp_module_manager_info;



	//��ʼ��slab����
	CP_INIT_HANDLE_SLAB_FILES(rtp_session);
	//��ȫ�ֵ�handle���ص�session��
	//CP_MODULE_MANAGER_INFO_SET_TYPE(&tmp_module_manager_info, cp_module_manager_type_hook);
	CP_MODULE_MANAGER_INFO_SET_TYPE(&tmp_module_manager_info, CP_MODULE_MANAGER_TYPE_HOOK(1));
	tmp_manager = (cp_ecam_hook_manager_t*)cp_get_manager(CP_NULL, &tmp_module_manager_info);
	if (!tmp_manager) {
		cp_log_error(rtp_session->logger, "init session %s error. not found hook manager.",
			print_module_register_info(&rtp_session->register_info, tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH));
		return -1;
	}

	CP_MODULE_INFO_SET_TYPE(&tmp_module_info, cp_css_rtp_hook_type_global);
	tmp_hook = (cp_ecam_hook_t*)cp_manager_get_module(tmp_manager, &tmp_module_info);
	if (!tmp_hook) {
		cp_log_error(rtp_session->logger, "init session %s error. ",
			print_module_register_info(&rtp_session->register_info, tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH));
		return -1;
	}
	rtp_session->global_hook = (cp_hook_t *)tmp_hook;
	//��hookmanager�и���handle����handle����
	//cp_copy_hook(rtp_session, tmp_hook);

	return 0;
}
/*ģ������нӿڣ���ģ��init֮�󣬻ᱻ����*/
cp_int32_t open_rtp_session(cp_rtp_session_t *rtp_session, const cp_rtp_session_info_t *rtp_session_info)
{
	cp_int32_t							ret_int = 0;
	cp_hook_t							*tmp_current_hook = CP_NULL;
	cp_hook_info_t						tmp_hook_info = { 0, };


	//У������������
	if (!rtp_session || !rtp_session->socket || !rtp_session->buf
		|| !cp_buf_get_length(rtp_session->buf)) {
		return -1;
	}
	//����ǺϷ��ģ�������session��Ϣ�����Ҹ�ʽ����ӡ��Ϣ
	set_option_rtp_session(rtp_session, cp_module_option_set_print_information, CP_NULL);
	CP_HOOK_INFO_SET_SESSION_INFO(&tmp_hook_info, rtp_session, &(rtp_session->hhsq));

	//��һ�β�����ʱ������ִ��ȫ�ֵ�hook
	if (rtp_session->global_hook) {
		//������ڵ�һ��ȫ�ֺ�������˵����ں���������ָ��������Ҫ����ʵ��
		rtp_session->current_hook = rtp_session->global_hook;
	}
	//����rtpָ����Ҷ�Ӧ��hook
	//һֱѭ��ִ��hook
	while (1)
	{
		tmp_current_hook = rtp_session->current_hook;
		rtp_session->current_hook = CP_NULL;
		if (!tmp_current_hook) {
			break;
		}
		ret_int = cp_open_module(tmp_current_hook, &tmp_hook_info);
		if (ret_int || !rtp_session->current_hook) {
			//rtp_session->current_hook == tmp_current_hook
			//���ִ��ʧ�ܡ���һ��hookΪ�����˳�
			break;
		}
	}
	return 0;
}
/*��ȡģ�����ݣ�flagΪ��ȡģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��*/
cp_int32_t read_rtp_session(cp_rtp_session_t *rtp_session, cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag)
{
	return 0;
}
/*дģ�����ݣ�flagΪдģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��*/
cp_int32_t write_rtp_session(cp_rtp_session_t *rtp_session, const cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag)
{
	return 0;
}
/*�ر�ģ��*/
cp_int32_t close_rtp_session(cp_rtp_session_t *rtp_session)
{
	return 0;
}
/*�˳�ģ��*/
cp_int32_t exit_rtp_session(cp_rtp_session_t *rtp_session)
{
	return 0;
}
/*����ģ�����*/
cp_int32_t set_option_rtp_session(cp_rtp_session_t *rtp_session, cp_int32_t optname, const cp_void_t* optval)
{
	cp_char_t						*tmp_socket_info_buf = CP_APP_STR_NULL_FLAG;
	cp_char_t						tmp_rtp_info_buf[CP_RTP_SESSION_BUFFER_LENGTH] = { 0, };



	if (!rtp_session) {
		return -1;
	}

	switch (optname)
	{
	case cp_module_option_set_print_information:
	{
		
	}
	break;
	default:
	{
		cp_log_error(rtp_session->logger, "unknow option[%d] type!", optname);
		return -1;
	}
	break;
	}
	return 0;
}
/*��ȡģ�����*/
cp_int32_t get_option_rtp_session(cp_rtp_session_t *rtp_session, cp_int32_t optname, cp_void_t* optval)
{
	if (!rtp_session) {
		return -1;
	}

	switch (optname)
	{
	case cp_module_option_get_print_information:
	{
		*((cp_char_t**)optval) = rtp_session->rtp_si;
	}
	break;
	default:
	{
		cp_log_error(rtp_session->logger, "unknow option[%d] type!", optname);
		return -1;
	}
	break;
	}
	return 0;
}


cp_int32_t connect_cb_rtp_session(cp_socket_t *socket, cp_int32_t status)
{
	return 0;
}

cp_int32_t close_cb_rtp_session(cp_socket_t *socket, cp_int32_t status)
{
	return 0;
}

cp_int32_t read_cb_rtp_session(cp_socket_t *socket, const cp_buf_t *buf, cp_int32_t nread, cp_int32_t status)
{
	return 0;
}

cp_int32_t write_cb_rtp_session(cp_socket_t *socket, cp_int32_t status)
{
	return 0;
}

cp_int32_t error_cb_rtp_session(cp_socket_t *socket, cp_int32_t status)
{
	return 0;
}


