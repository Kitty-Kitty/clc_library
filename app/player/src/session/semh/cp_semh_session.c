/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/
#include "cp_semh_session.h"
#include "cp_semh_hook_core.h"




cp_semh_session_t *cp_semh_session_create();

/*ģ�鴴���ӿڣ���ʾ����һ��ģ��*/
cp_int32_t init_semh_session(cp_semh_session_t *semh_session, const cp_semh_session_info_t *semh_session_info);
/*ģ������нӿڣ���ģ��init֮�󣬻ᱻ����*/
cp_int32_t open_semh_session(cp_semh_session_t *semh_session, const cp_semh_session_info_t *semh_session_info);
/*��ȡģ�����ݣ�flagΪ��ȡģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��*/
cp_int32_t read_semh_session(cp_semh_session_t *semh_session, cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag);
/*дģ�����ݣ�flagΪдģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��*/
cp_int32_t write_semh_session(cp_semh_session_t *semh_session, const cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag);
/*�ر�ģ��*/
cp_int32_t close_semh_session(cp_semh_session_t *semh_session);
/*�˳�ģ��*/
cp_int32_t exit_semh_session(cp_semh_session_t *semh_session);
/*����ģ�����*/
cp_int32_t set_option_semh_session(cp_semh_session_t *semh_session, cp_int32_t optname, const cp_void_t* optval);
cp_int32_t get_option_semh_session(cp_semh_session_t *semh_session, cp_int32_t optname, cp_void_t* optval);

cp_int32_t connect_cb_semh_session(cp_socket_t *socket, cp_int32_t status);										/*���ӻص�����*/
cp_int32_t close_cb_semh_session(cp_socket_t *socket, cp_int32_t status);											/*�رջص�����*/
cp_int32_t read_cb_semh_session(cp_socket_t *socket, const cp_buf_t *buf, cp_int32_t nread, cp_int32_t status);	/*���ص�����*/
cp_int32_t write_cb_semh_session(cp_socket_t *socket, cp_int32_t status);											/*д�ص�����*/
cp_int32_t error_cb_semh_session(cp_socket_t *socket, cp_int32_t status);											/*����ص�����*/

//���ֲ���ѡ��Ĵ���
cp_char_t *option_semh_set_print_information(cp_void_t *emh, cp_char_t *buf, cp_int32_t len);


/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: semh_session_get_semh_hook
*
* ����˵��: semh session�ӹ������в�ѯ��Ҫ��hook
*
* ��    ��: cp_semh_session_t * semh_session						[in]����˵��
* ��    ��: const cp_semh_session_info_t * semh_session_info						[in]����˵��
* ��    ��: cp_int32_t command									[in]����˵��
*
* �� �� ֵ: cp_hook_t *
*           0  : �ɹ�
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2016-07-01 16:32:34
******************************************************************************************************/
cp_hook_t *semh_session_get_semh_hook
(cp_semh_session_t *semh_session, const cp_semh_session_info_t *semh_session_info, cp_int32_t command);


/*����ģ��*/
cp_semh_session_t* create_semh_session(cp_module_register_t *register_info, cp_socket_manager_t *manager, cp_semh_session_info_t *info)
{
	cp_int32_t							ret_int = 0;
	cp_semh_session_t					*tmp_module = CP_NULL;
	cp_pool_info_t						tmp_pool_info = { 0, };

	

	if (!register_info || !manager || !info) {
		return CP_NULL;
	}

	tmp_module = cp_malloc_module(manager, cp_semh_session_t, &tmp_pool_info);
	if (!tmp_module) {
		return CP_NULL;
	}
	CP_MODULE_SET_HANDLERS(tmp_module, semh_session);
	CP_SOCKET_MODULE_SET_CALLBACK_HANDLERS(tmp_module, semh_session);
	return tmp_module;
}
/*����ģ��*/
cp_int32_t destroy_semh_session(cp_css_session_manager_t *manager, cp_semh_session_t* semh_session)
{
	if (!manager || !semh_session) {
		return -1;
	}
	cp_free_module(semh_session);
	return 0;
}


/*ģ�鴴���ӿڣ���ʾ����һ��ģ��*/
cp_int32_t init_semh_session(cp_semh_session_t *semh_session, const cp_semh_session_info_t *semh_session_info)
{
	cp_css_hook_t							*tmp_hook;
	cp_css_hook_manager_t					*tmp_manager;
	cp_char_t								tmp_buf[CP_APP_DEFAULT_BUFFER_LENGTH] = { 0, };
	cp_module_info_t						tmp_module_info;
	cp_module_manager_info_t				tmp_module_manager_info;



	//��ʼ��slab����
	CP_INIT_HANDLE_SLAB_FILES(semh_session);
	//��ȫ�ֵ�handle���ص�session��
	//CP_MODULE_MANAGER_INFO_SET_TYPE(&tmp_module_manager_info, cp_module_manager_type_hook);
	CP_MODULE_MANAGER_INFO_SET_TYPE(&tmp_module_manager_info, CP_MODULE_MANAGER_TYPE_HOOK(1));
	tmp_manager = (cp_css_hook_manager_t*)cp_get_manager(CP_NULL, &tmp_module_manager_info);
	if (!tmp_manager) {
		cp_log_error(semh_session->logger, "init session %s error. not found hook manager.",
			print_module_register_info(&semh_session->register_info, tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH));
		return -1;
	}

	CP_MODULE_INFO_SET_TYPE(&tmp_module_info, cp_css_semh_hook_type_global);
	tmp_hook = (cp_css_hook_t*)cp_manager_get_module(tmp_manager, &tmp_module_info);
	if (!tmp_hook) {
		cp_log_error(semh_session->logger, "init session %s error. ",
			print_module_register_info(&semh_session->register_info, tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH));
		return -1;
	}
	semh_session->global_hook = (cp_hook_t *)tmp_hook;
	//��hookmanager�и���handle����handle����
	//cp_copy_hook(semh_session, tmp_hook);

	return 0;
}
/*ģ������нӿڣ���ģ��init֮�󣬻ᱻ����*/
cp_int32_t open_semh_session(cp_semh_session_t *semh_session, const cp_semh_session_info_t *semh_session_info)
{
	cp_int32_t							ret_int = 0;
	gmp_gmph_semh_t						*tmp_semh = CP_NULL;
	cp_hook_t							*tmp_current_hook = CP_NULL;
	cp_hook_info_t						tmp_hook_info = { 0, };


	//У������������
	if (!semh_session || !semh_session->socket || !semh_session->buf
		|| !cp_buf_get_length(semh_session->buf)) {
		return -1;
	}
	//У�������Ƿ�Ϸ�
	tmp_semh = (gmp_gmph_semh_t*)(cp_buf_get_pos(semh_session->buf));
	if (gmp_gmph_emh_type_semh != tmp_semh->bmh.emht) {
		return -2;
	} else {
		//����ǺϷ��ģ�������session��Ϣ�����Ҹ�ʽ����ӡ��Ϣ
		semh_session->semh_p = tmp_semh;
		set_option_semh_session(semh_session, cp_module_option_set_print_information, CP_NULL);
	}
	CP_HOOK_INFO_SET_SESSION_INFO(&tmp_hook_info, semh_session, &(semh_session->hhsq));

	//��һ�β�����ʱ������ִ��ȫ�ֵ�hook
	if (semh_session->global_hook) {
		//������ڵ�һ��ȫ�ֺ�������˵����ں���������ָ��������Ҫ����ʵ��
		semh_session->current_hook = semh_session->global_hook;
	} else {
		semh_session->current_hook = semh_session_get_semh_hook(semh_session, semh_session_info, tmp_semh->command);
	}
	//����semhָ����Ҷ�Ӧ��hook
	//һֱѭ��ִ��hook
	while (1)
	{
		tmp_current_hook = semh_session->current_hook;
		semh_session->current_hook = CP_NULL;
		if (!tmp_current_hook) {
			break;
		}
		ret_int = cp_open_module(tmp_current_hook, &tmp_hook_info);
		if (ret_int || !semh_session->current_hook) {
			//semh_session->current_hook == tmp_current_hook
			//���ִ��ʧ�ܡ���һ��hookΪ�����˳�
			break;
		}
	}
	return 0;
}
/*��ȡģ�����ݣ�flagΪ��ȡģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��*/
cp_int32_t read_semh_session(cp_semh_session_t *semh_session, cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag)
{
	return 0;
}
/*дģ�����ݣ�flagΪдģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��*/
cp_int32_t write_semh_session(cp_semh_session_t *semh_session, const cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag)
{
	return 0;
}
/*�ر�ģ��*/
cp_int32_t close_semh_session(cp_semh_session_t *semh_session)
{
	return 0;
}
/*�˳�ģ��*/
cp_int32_t exit_semh_session(cp_semh_session_t *semh_session)
{
	return 0;
}
/*����ģ�����*/
cp_int32_t set_option_semh_session(cp_semh_session_t *semh_session, cp_int32_t optname, const cp_void_t* optval)
{
	cp_char_t						*tmp_socket_info_buf = CP_APP_STR_NULL_FLAG;
	cp_char_t						tmp_semh_info_buf[CP_SEMH_SESSION_BUFFER_LENGTH] = { 0, };



	if (!semh_session) {
		return -1;
	}

	switch (optname)
	{
	case cp_module_option_set_print_information:
	{
		//��������semh������Ϣ
		option_semh_set_print_information(semh_session->semh_p, 
			tmp_semh_info_buf, cp_sizeof(tmp_semh_info_buf));

		//�����ȡsocket������Ϣ
		if (!cp_set_option_module(semh_session->socket, cp_module_option_set_print_information, CP_NULL)) {
			cp_get_option_module(semh_session->socket, cp_module_option_get_print_information, &tmp_socket_info_buf);
		}
		cp_snprintf(semh_session->semh_si, cp_sizeof(semh_session->semh_si),
			"%s %s",
			tmp_semh_info_buf,
			tmp_socket_info_buf);
	}
	break;
	default:
	{
		cp_log_error(semh_session->logger, "unknow option[%d] type!", optname);
		return -1;
	}
	break;
	}
	return 0;
}
/*��ȡģ�����*/
cp_int32_t get_option_semh_session(cp_semh_session_t *semh_session, cp_int32_t optname, cp_void_t* optval)
{
	if (!semh_session) {
		return -1;
	}

	switch (optname)
	{
	case cp_module_option_get_print_information:
	{
		*((cp_char_t**)optval) = semh_session->semh_si;
	}
	break;
	default:
	{
		cp_log_error(semh_session->logger, "unknow option[%d] type!", optname);
		return -1;
	}
	break;
	}
	return 0;
}


cp_int32_t connect_cb_semh_session(cp_socket_t *socket, cp_int32_t status)
{
	return 0;
}

cp_int32_t close_cb_semh_session(cp_socket_t *socket, cp_int32_t status)
{
	return 0;
}

cp_int32_t read_cb_semh_session(cp_socket_t *socket, const cp_buf_t *buf, cp_int32_t nread, cp_int32_t status)
{
	return 0;
}

cp_int32_t write_cb_semh_session(cp_socket_t *socket, cp_int32_t status)
{
	return 0;
}

cp_int32_t error_cb_semh_session(cp_socket_t *socket, cp_int32_t status)
{
	return 0;
}

cp_hook_t *semh_session_get_semh_hook(cp_semh_session_t *semh_session, const cp_semh_session_info_t *semh_session_info, cp_int32_t command)
{
	cp_hook_manager_t				*tmp_manager = CP_NULL;
	cp_css_hook_info_t				tmp_css_hoot_info = { 0, };
	cp_module_manager_info_t		tmp_module_manager_info = { 0, };


	if (!semh_session || !semh_session_info) {
		return CP_NULL;
	}

	CP_MODULE_MANAGER_INFO_SET_TYPE(&tmp_module_manager_info, cp_module_manager_type_hook);
	tmp_manager = (cp_hook_manager_t*)cp_get_manager(CP_NULL, &tmp_module_manager_info);
	if (!tmp_manager) {
		return CP_NULL;
	}
	tmp_css_hoot_info.command = command;
	return (cp_hook_t*)cp_manager_get_module(tmp_manager, &tmp_css_hoot_info);
}

cp_char_t *option_semh_set_print_information(cp_void_t *emh, cp_char_t *buf, cp_int32_t len)
{
	return print_gmph_emh(emh, buf, len, cp_true);
}

