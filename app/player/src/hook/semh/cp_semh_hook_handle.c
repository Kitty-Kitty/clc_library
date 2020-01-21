/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-11-07

Description:

**************************************************************************/
#include "cp_semh_hook_handle.h"

/******************************************************************************************************
* ��Ȩ����:thm & novigo
* ��������:proc_semh_center_register_return
* ��    ��:����ע�᷵��
*
* ��    ��:
*				1��cp_css_hook_t			*hook				ָ�������CSS
*				2��cp_semh_session_t		*session			ָ��session
*				3��cp_void_t				*arg				ָ�����
* �� �� ֵ:
*			���سɹ����true��ʾ�ɹ�;false��ʾʧ��;
* ��    ע:
* ��    ��: thm
* ��������:tianhuiming@novigo.com.cn
* ��������:2016-7-11
******************************************************************************************************/
cp_int32_t proc_semh_center_register_return(cp_css_hook_t *hook, cp_semh_session_t *session, cp_void_t *arg)
{
	cp_int32_t							tmp_ret_int = 0;
	cp_int32_t							tmp_device_info_size = 0;
	cp_char_t							buf[CP_APP_DEFAULT_BUFFER_LENGTH] = { 0, };
	cp_return_info_t					return_info = { 0, };
	cp_device_info_t					tmp_device_info = { 0, };
	cp_sync_info_t						sync_info = { 0, };
	cp_array_t							device_info_array = { 0, };
	list_node							*device_info_list = CP_NULL;
	list_node							*media_channel_list = CP_NULL;
	list_node							*tmp_device_node = CP_NULL;
	cp_socket_t							*s = session->socket;
	gmp_gmdu_t							*gmdu = CP_NULL;
	gmp_gmdu_t							*info_gmdu = CP_NULL;
	gmp_gmdt_t							*gmdt = CP_NULL;
	gmdt_string_p_t						*str = CP_NULL;
	gmp_gmph_semh_t						*semh_p = session->semh_p;
	gmp_gmf_t							*gmf = session->gmf;
	cp_player_t							*tmp_player = (cp_player_t*)session->manager->app;
	cp_player_info_t					*tmp_player_info = (cp_player_info_t *)(tmp_player->app_info);
	cp_device_info_t					*tmp_player_device_info = ((cp_player_info_t*)(tmp_player->app_info))->device_info;
	cp_device_info_t					*tmp_media_server = CP_NULL;
	cp_play_channel_info_t				*tmp_pc_info = CP_NULL;



	//����object
	gmp_into_gmdu(gmf);

	//�ж�semh״̬��
	if (!gmp_is_normal_status(semh_p->status)) {
		cp_semh_session_log(error, session, "register_return error status error");
		return -1;
	}

	//������������ 
	if (!parse_gmf_return(gmf, &return_info, buf, CP_APP_DEFAULT_BUFFER_LENGTH)) {
		cp_semh_session_log(error, session, "register_return error [%s]", buf);
		return -1;
	}

	//����Return�ڵ�
	gmdt = gmp_create_gmdt(gmf, "%T%p%d", GMP_GMDT_ST, CP_APP_STR_RETURN, cp_strlen(CP_APP_STR_RETURN));
	gmdu = gmp_find_gmdu(gmf, gmdt);
	if (!gmdu) {
		cp_semh_session_log(error, session, "register_return error not "CP_APP_STR_RETURN" element ");
		return -1;
	}

	//����return�ڵ�
	gmp_reset_gmdu(gmf, gmdu);

	//����return�ڵ�
	gmp_into_gmdu(gmf);

	//����Host�ڵ�
	gmdt = gmp_create_gmdt(gmf, "%T%p%d", GMP_GMDT_ST, CP_APP_STR_HOST, cp_strlen(CP_APP_STR_HOST));
	gmdu = gmp_find_gmdu(gmf, gmdt);
	if (!gmdu) {
		cp_semh_session_log(error, session, "register_return error. not "CP_APP_STR_HOST" element error.");
		return -1;
	}

	//����Host�ڵ�
	gmp_reset_gmdu(gmf, gmdu);

	//����Host�ڵ�
	gmp_into_gmdu(gmf);

	//����Host�ڵ�����
	if (!parse_gmf_device_host(gmf, &(tmp_device_info.host), buf, CP_APP_DEFAULT_BUFFER_LENGTH)) {
		cp_semh_session_log(error, session, "register_return error. parse_gmf_device_host() error [%s]", buf);
		return -1;
	}

	//����Information�ڵ�
	gmdt = gmp_create_gmdt(gmf, "%T%p%d", GMP_GMDT_ST, CP_APP_STR_INFORMATION, cp_strlen(CP_APP_STR_INFORMATION));
	info_gmdu = gmp_find_gmdu(gmf, gmdt);
	if (!info_gmdu) {
		cp_semh_session_log(error, session, "register_return error. parse_gmf_device_host() error [%s]", buf);
		return -1;
	}

	//����Information�ڵ�
	gmp_reset_gmdu(gmf, info_gmdu);

	//����Information�ڵ�
	gmp_into_gmdu(gmf);

	//��ȡӲ����Ϣ
	if (!get_gmf_hardware_info(gmf, &(tmp_device_info.host), &(tmp_device_info.hardware), buf, CP_APP_DEFAULT_BUFFER_LENGTH)) {
		cp_semh_session_log(error, session, "register_return error. get gmf hardware info error. reason: [%s]", buf);
		return -1;
	}

	//��ȡ�豸����Ϣ
	if (!get_gmf_device_groups_info(gmf, &(tmp_device_info.host), buf, CP_APP_DEFAULT_BUFFER_LENGTH)) {
		cp_semh_session_log(warn, session, "get gmf device group error. reason: [%s]", buf);
	}

	//////////////////////////////////////////////////////////////////////////
	//��ȡ��ǰ�豸�б������
	tmp_device_info_size = get_gmf_devices_info_size(gmf, buf, CP_APP_DEFAULT_BUFFER_LENGTH);
	if (tmp_device_info_size < 0 || tmp_device_info_size > CP_PLAYER_MAX_DEVICE_NUMBER) {
		cp_semh_session_log(error, session,
			"register_return error. device info size[%d] not in [0 ~ %d]. reason: [%s]",
			tmp_device_info_size,
			CP_PLAYER_MAX_DEVICE_NUMBER,
			buf);
		return -1;
	}

	//ע��ɹ�����������Ѿ����ڵ��豸��Ϣ
	remove_all_device_info(tmp_player);

	if (!tmp_device_info_size) {
		cp_semh_session_log(warn, session, "register_return warning. devices size[%d]", tmp_device_info_size);
	}
	else {
		//��ʼ���豸��Ϣ����
		if (cp_array_malloc_init(&device_info_array,
			cp_sizeof(cp_device_info_t), tmp_device_info_size)) {
			cp_semh_session_log(error, session, "cp_array_malloc_init() error");
			return -1;
		}

		//��ȡ�豸��Ϣ
		if (!get_gmf_devices_info_array(gmf, &device_info_array, buf, CP_APP_DEFAULT_BUFFER_LENGTH)) {
			cp_semh_session_log(error, session, "register_return error. get gmf devices info error. reason: [%s]", buf);
			cp_array_malloc_destroy(&device_info_array);
			return -1;
		}

		//�����豸��Ϣ
		update_device_info(tmp_player, &device_info_array);

		//�ͷŷ���Ŀռ�
		cp_array_malloc_destroy(&device_info_array);
	}

	//�������豸��Ϣ
	cp_update_host_info(&tmp_player_device_info->host, &tmp_device_info.host);

	//�����豸��Ϣ
	cp_save_host_info(tmp_player, &tmp_player_device_info->host);

	//����ע��ɹ�״̬
	tmp_player_info->registered_flag = cp_true;

	//����Information�ڵ�
	gmp_reset_gmdu(gmf, info_gmdu);

	//����Information�ڵ�
	gmp_into_gmdu(gmf);

	//��ȡ��Ҫ��ý����Ϣ
	tmp_pc_info = get_semh_play_information_play_info(hook, session, arg, buf, CP_APP_DEFAULT_BUFFER_LENGTH);
	if (tmp_pc_info) {
		//����ý����Ϣ
		switch (tmp_player_device_info->host.type)
		{
		case css_device_type_css_video_player:
		{
			tmp_pc_info->mpy = cp_media_process_type_video;
			tmp_ret_int = create_media_play(tmp_player, tmp_pc_info);
			if (tmp_ret_int) {
				cp_semh_hook_log(warn, hook, session, "create_media_play() warning");
			}
		}
		break;
		case css_device_type_css_audio_player:
		{
			tmp_pc_info->mpy = cp_media_process_type_audio;
			tmp_ret_int = create_media_play(tmp_player, tmp_pc_info);
			if (tmp_ret_int) {
				cp_semh_hook_log(warn, hook, session, "create_media_play() warning");
			}
		}
		break;
		default:
		{
			cp_semh_hook_log(warn, hook, session, "unknow device_type[%d] warning",
				tmp_player_device_info->host.type);
		}
		break;
		}
	}
	else {
		cp_semh_hook_log(warn, hook, session, "get_semh_play_information_play_info() warning. reason: [%s]", buf);
	}

	cp_semh_hook_log(notice, hook, session, "register process successed!");

	/*
	//////////////////////////////////////////////////////////////////////////
	//��ȡ������Ϣ
	if (!get_gmf_play_information(gmf, &media_channel_list, buf, CP_APP_DEFAULT_BUFFER_LENGTH)) {
	cp_log_warn(session->logger, "register_return error. get gmf play infomation error. reason: [%s]", buf);
	}

	//��ȡͬ����Ϣ
	if (!get_gmf_sync_info(gmf, &sync_info, buf, CP_APP_DEFAULT_BUFFER_LENGTH)) {
	cp_log_warn(session->logger, "register_return error. get gmf sync info error. reason: [%s]", buf);
	}
	*/
	/*
	//��ȡ����ͼƬ��Ϣ
	if (!get_gmf_background_info(gmf, tmp_device_info.host.id, &player_background_info, buf, CP_APP_DEFAULT_BUFFER_LENGTH)) {
	cp_log_warn(session->logger, "register_return error. get gmf background info error. reason: %s", buf);
	}

	//��ȡ��ĻͼƬ��Ϣ
	if (!get_gmf_words_info(gmf, tmp_device_info.host.id, &player_words_info_info, buf, CP_APP_DEFAULT_BUFFER_LENGTH)) {
	cp_log_warn(session->logger, "register_return error. get gmf sync info error. reason: %s", buf);
	}
	*/

	return 0;
}

/******************************************************************************************************
* ��Ȩ����:thm & novigo
* ��������:proc_semh_center_cancel_register_return
* ��    ��:����ȡ��ע�᷵��
*
* ��    ��:
*				1��cp_css_hook_t			*hook				ָ�������CSS
*				2��cp_semh_session_t		*session			ָ��session
*				3��cp_void_t				*arg				ָ�����
* �� �� ֵ:
*			���سɹ����true��ʾ�ɹ�;false��ʾʧ��;
* ��    ע:
* ��    ��: thm
* ��������:tianhuiming@novigo.com.cn
* ��������:2016-7-11
******************************************************************************************************/
cp_int32_t proc_semh_center_cancel_register_return(cp_css_hook_t *hook, cp_semh_session_t *session, cp_void_t *arg)
{
	cp_host_t							host = { 0, };
	cp_bool_t							ret_bool = cp_false;
	cp_char_t							buf[CP_APP_DEFAULT_GMPH_BUFFER_LEN] = { 0, };
	cp_socket_t							*s = session->socket;
	gmp_gmph_semh_t						*semh_p = session->semh_p;
	gmp_gmf_t							*gmf = session->gmf;
	cp_player_t							*tmp_player = (cp_player_t*)session->manager->app;
	cp_player_info_t					*tmp_player_info = (cp_player_info_t *)(tmp_player->app_info);
	cp_device_info_t					*tmp_player_device_info = ((cp_player_info_t*)(tmp_player->app_info))->device_info;
	const cp_char_t						*id = tmp_player_device_info->host.id;



	//��ȡhost
	parse_gmf_host(gmf, &host, buf, CP_APP_DEFAULT_GMPH_BUFFER_LEN);
	if (cp_strlen(host.id) != CP_APP_DEFAULT_ID_LENGTH - 1) {
		func_error_response(hook, session, arg, "set log error. parse_gmf_host() error. reason: [%s]", buf);
		return -1;
	}

	return 0;
}

// #include <crtdbg.h>

/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: proc_semh_all_life_heart
*
* ����˵��: �������е�������Ϣ
*
* ��    ��: cp_css_hook_t * hook						[in]����˵��
* ��    ��: cp_semh_session_t * session						[in]����˵��
* ��    ��: cp_void_t * arg						[in]����˵��
*
* �� �� ֵ: cp_int32_t
*           0  : �ɹ�
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2016-11-07 14:08:20
******************************************************************************************************/
cp_int32_t proc_semh_all_life_heart(cp_css_hook_t *hook, cp_semh_session_t *session, cp_void_t *arg)
{
	cp_char_t							buf[CP_APP_DEFAULT_GMPH_BUFFER_LEN] = { 0, };
	cp_char_t							*flag = CP_APP_STR_NULL_FLAG;
	cp_int32_t							ret_int = 0;
	cp_bool_t							ret_bool = cp_false;
	cp_socket_t							*s = session->socket;
	gmp_gmph_semh_t						*semh_p = session->semh_p;
	gmp_gmf_t							*gmf = session->gmf;
	const cp_sockaddr_in				*remote_addr = &(session->socket->remote_addr);
	cp_player_t							*tmp_player = (cp_player_t*)session->manager->app;
	cp_player_info_t					*tmp_player_info = (cp_player_info_t *)(tmp_player->app_info);
	cp_device_info_t					*tmp_player_device_info = ((cp_player_info_t*)(tmp_player->app_info))->device_info;
	cp_device_info_t					tmp_device_info = { 0, };
// 	_CrtMemState								s1, s2, s3;



	//arg��������ϢΪ�����豸������Ϣ
	if (arg) {
		flag = (cp_char_t *)arg;
	}
	//��ȡ�豸��Ϣ
	ret_bool = get_gmf_host_device_info(gmf, &tmp_device_info, buf, CP_APP_DEFAULT_GMPH_BUFFER_LEN);
	if (!ret_bool) {
		func_error_response(hook, session, arg,
			"error. get_gmf_host_device_info() error. reason: [%s]",
			flag,
			buf);
		return -1;
	}

// 	_CrtMemCheckpoint(&s1);

	//�����豸��Ϣ
	ret_int = update_a_device_info(tmp_player, &tmp_device_info);
	if (ret_int) {
		func_error_response(hook, session, arg,
			"error. update_a_device_info() error. ",
			flag);
		return -1;
	}

// 	_CrtMemCheckpoint(&s2);
// 	if (_CrtMemDifference(&s3, &s1, &s2)) {
// 		_CrtMemDumpStatistics(&s3);
// 		cp_semh_hook_log(warn, hook, session, "update_a_device_info() !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
// 	}
// 	else {
// 		cp_semh_hook_log(warn, hook, session, "update_a_device_info() ================================================");
// 	}

	return 0;
}

/******************************************************************************************************
* ��Ȩ����:thm & novigo
* ��������:proc_semh_center_life_heart
* ��    ��:������������
*
* ��    ��:
*				1��cp_css_hook_t			*hook				ָ�������CSS
*				2��cp_semh_session_t		*session			ָ��session
*				3��cp_void_t				*arg				ָ�����
* �� �� ֵ:
*			���سɹ����true��ʾ�ɹ�;false��ʾʧ��;
* ��    ע:
* ��    ��: thm
* ��������:tianhuiming@novigo.com.cn
* ��������:2016-7-11
******************************************************************************************************/
cp_int32_t proc_semh_center_life_heart(cp_css_hook_t *hook, cp_semh_session_t *session, cp_void_t *arg)
{
	cp_char_t				*flag = "center";
	return proc_semh_all_life_heart(hook, session, flag);
}

/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: proc_semh_accessed_server_life_heart
*
* ����˵��: �����м��������Ϣ
*
* ��    ��: cp_css_hook_t * hook						[in]����˵��
* ��    ��: cp_semh_session_t * session						[in]����˵��
* ��    ��: cp_void_t * arg						[in]����˵��
*
* �� �� ֵ: cp_int32_t
*           0  : �ɹ�
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2016-11-07 14:08:33
******************************************************************************************************/
cp_int32_t proc_semh_accessed_server_life_heart(cp_css_hook_t *hook, cp_semh_session_t *session, cp_void_t *arg)
{
	//�м�����������Բ��ô���
	return 0;
}

/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: proc_semh_media_server_life_heart
*
* ����˵��: ����ý�������������Ϣ
*
* ��    ��: cp_css_hook_t * hook						[in]����˵��
* ��    ��: cp_semh_session_t * session						[in]����˵��
* ��    ��: cp_void_t * arg						[in]����˵��
*
* �� �� ֵ: cp_int32_t
*           0  : �ɹ�
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2016-11-07 14:08:47
******************************************************************************************************/
cp_int32_t proc_semh_media_server_life_heart(cp_css_hook_t *hook, cp_semh_session_t *session, cp_void_t *arg)
{
	cp_char_t				*flag = "media_server";
	return proc_semh_all_life_heart(hook, session, flag);
}

/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: proc_semh_player_life_heart
*
* ����˵��: �����������Ƶ�������Ϣ
*
* ��    ��: cp_css_hook_t * hook						[in]����˵��
* ��    ��: cp_semh_session_t * session						[in]����˵��
* ��    ��: cp_void_t * arg						[in]����˵��
*
* �� �� ֵ: cp_int32_t
*           0  : �ɹ�
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2016-11-07 14:10:47
******************************************************************************************************/
cp_int32_t proc_semh_player_life_heart(cp_css_hook_t *hook, cp_semh_session_t *session, cp_void_t *arg)
{
	return 0;
}

/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: proc_semh_client_background_server_life_heart
*
* ����˵��: ������Է�����������Ϣ
*
* ��    ��: cp_css_hook_t * hook						[in]����˵��
* ��    ��: cp_semh_session_t * session						[in]����˵��
* ��    ��: cp_void_t * arg						[in]����˵��
*
* �� �� ֵ: cp_int32_t
*           0  : �ɹ�
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2016-11-07 14:08:58
******************************************************************************************************/
cp_int32_t proc_semh_client_background_server_life_heart(cp_css_hook_t *hook, cp_semh_session_t *session, cp_void_t *arg)
{
	cp_char_t				*flag = "client_background_server";
	return proc_semh_all_life_heart(hook, session, flag);
}

/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: proc_semh_player_background_server_life_heart
*
* ����˵��: ������������������Ϣ
*
* ��    ��: cp_css_hook_t * hook						[in]����˵��
* ��    ��: cp_semh_session_t * session						[in]����˵��
* ��    ��: cp_void_t * arg						[in]����˵��
*
* �� �� ֵ: cp_int32_t
*           0  : �ɹ�
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2016-11-07 14:09:12
******************************************************************************************************/
cp_int32_t proc_semh_player_background_server_life_heart(cp_css_hook_t *hook, cp_semh_session_t *session, cp_void_t *arg)
{
	cp_char_t				*flag = "player_background_server";
	return proc_semh_all_life_heart(hook, session, flag);
}

/******************************************************************************************************
* ��Ȩ����:thm & novigo
* ��������:proc_semh_center_life_heart_return
* ��    ��:����������������
*
* ��    ��:
*				1��cp_css_hook_t			*hook				ָ�������CSS
*				2��cp_semh_session_t		*session			ָ��session
*				3��cp_void_t				*arg				ָ�����
* �� �� ֵ:
*			���سɹ����true��ʾ�ɹ�;false��ʾʧ��;
* ��    ע:
* ��    ��: thm
* ��������:tianhuiming@novigo.com.cn
* ��������:2016-7-11
******************************************************************************************************/
cp_int32_t proc_semh_player_heart_return(cp_css_hook_t *hook, cp_semh_session_t *session, cp_void_t *arg)
{
	cp_host_t							host = { 0, };
	cp_bool_t							ret_bool = cp_false;
	cp_char_t							buf[CP_APP_DEFAULT_GMPH_BUFFER_LEN] = { 0, };
	cp_socket_t							*s = session->socket;
	gmp_gmph_semh_t						*semh_p = session->semh_p;
	gmp_gmf_t							*gmf = session->gmf;
	cp_player_t							*tmp_player = (cp_player_t*)session->manager->app;
	cp_player_info_t					*tmp_player_info = (cp_player_info_t *)(tmp_player->app_info);
	cp_device_info_t					*tmp_player_device_info = ((cp_player_info_t*)(tmp_player->app_info))->device_info;
	const cp_char_t						*id = tmp_player_device_info->host.id;



	//��ȡhost
	parse_gmf_host(gmf, &host, buf, CP_APP_DEFAULT_GMPH_BUFFER_LEN);
	if (cp_strlen(host.id) != CP_APP_DEFAULT_ID_LENGTH - 1) {
		func_error_response(hook, session, arg, "set log error. parse_gmf_host() error. reason: [%s]", buf);
		return -1;
	}

	return 0;
}

/******************************************************************************************************
* ��Ȩ����:thm & novigo
* ��������:proc_semh_player_software_update
* ��    ��:�����豸�������
*
* ��    ��:
*				1��cp_css_hook_t			*hook				ָ�������CSS
*				2��cp_semh_session_t		*session			ָ��session
*				3��cp_void_t				*arg				ָ�����
* �� �� ֵ:
*			���سɹ����true��ʾ�ɹ�;false��ʾʧ��;
* ��    ע:
* ��    ��: thm
* ��������:tianhuiming@novigo.com.cn
* ��������:2016-7-11
******************************************************************************************************/
cp_int32_t proc_semh_player_software_update(cp_css_hook_t *hook, cp_semh_session_t *session, cp_void_t *arg)
{
	cp_host_t							host = { 0, };
	cp_update_info_t					update_info = { 0, };
	cp_bool_t							ret_bool = cp_false;
	cp_char_t							buf[CP_APP_DEFAULT_GMPH_BUFFER_LEN] = { 0, };
	cp_socket_t							*s = session->socket;
	gmp_gmph_semh_t						*semh_p = session->semh_p;
	gmp_gmf_t							*gmf = session->gmf;
	cp_player_t							*tmp_player = (cp_player_t*)session->manager->app;
	cp_player_info_t					*tmp_player_info = (cp_player_info_t *)(tmp_player->app_info);
	cp_device_info_t					*tmp_player_device_info = ((cp_player_info_t*)(tmp_player->app_info))->device_info;
	const cp_char_t						*id = tmp_player_device_info->host.id;



	parse_gmf_host(gmf, &host, buf, CP_APP_DEFAULT_GMPH_BUFFER_LEN);
	if (cp_strlen(host.id) != CP_APP_DEFAULT_ID_LENGTH - 1) {
		func_error_response(hook, session, arg, "software update error. parse_gmf_host() error. reason: [%s]", buf);
		return -1;
	}

	ret_bool = get_gmf_update_info_by_id(gmf, id, &update_info, buf, CP_APP_DEFAULT_GMPH_BUFFER_LEN);
	if (!ret_bool) {
		func_error_response(hook, session, arg, "software update error. get_gmf_update_info_id_exist(). reason: [%s]", buf);
		return -1;
	}

	//TODO���������������Ϣ

	send_semh_response(tmp_player, s, CP_NULL, semh_p, GMP_NORMAL_STATUS_200, GMP_RETURN_SUCCESSED, cp_strlen(GMP_RETURN_SUCCESSED));

	return 0;
}

/******************************************************************************************************
* ��Ȩ����:thm & novigo
* ��������:proc_semh_player_set_log
* ��    ��:�����豸������־
*
* ��    ��:
*				1��cp_css_hook_t			*hook				ָ�������CSS
*				2��cp_semh_session_t		*session			ָ��session
*				3��cp_void_t				*arg				ָ�����
* �� �� ֵ:
*			���سɹ����true��ʾ�ɹ�;false��ʾʧ��;
* ��    ע:
* ��    ��: thm
* ��������:tianhuiming@novigo.com.cn
* ��������:2016-7-11
******************************************************************************************************/
cp_int32_t proc_semh_player_set_log(cp_css_hook_t *hook, cp_semh_session_t *session, cp_void_t *arg)
{
	cp_host_t							host = { 0, };
	cp_log_info_t						log_info = { 0, };
	cp_bool_t							ret_bool = cp_false;
	cp_char_t							buf[CP_APP_DEFAULT_GMPH_BUFFER_LEN] = { 0, };
	cp_socket_t							*s = session->socket;
	gmp_gmph_semh_t						*semh_p = session->semh_p;
	gmp_gmf_t							*gmf = session->gmf;
	cp_player_t							*tmp_player = (cp_player_t*)session->manager->app;
	cp_player_info_t					*tmp_player_info = (cp_player_info_t *)(tmp_player->app_info);
	cp_device_info_t					*tmp_player_device_info = ((cp_player_info_t*)(tmp_player->app_info))->device_info;
	const cp_char_t						*id = tmp_player_device_info->host.id;



	//��ȡhost
	parse_gmf_host(gmf, &host, buf, CP_APP_DEFAULT_GMPH_BUFFER_LEN);
	if (cp_strlen(host.id) != CP_APP_DEFAULT_ID_LENGTH - 1) {
		func_error_response(hook, session, arg, "set log error. parse_gmf_host() error. reason: [%s]", buf);
		return -1;
	}

	ret_bool = get_gmf_log_info_by_id(gmf, id, &log_info, buf, CP_APP_DEFAULT_GMPH_BUFFER_LEN);
	if (!ret_bool) {
		func_error_response(hook, session, arg, "set log error. get_gmf_log_info_by_id() error. reason: [%s]", buf);
		return -1;
	}

	//TODO:������־��������

	return 0;
}

/******************************************************************************************************
* ��Ȩ����:thm & novigo
* ��������:proc_semh_player_get_log
* ��    ��:�����豸��ȡ��־
*
* ��    ��:
*				1��cp_css_hook_t			*hook				ָ�������CSS
*				2��cp_semh_session_t		*session			ָ��session
*				3��cp_void_t				*arg				ָ�����
* �� �� ֵ:
*			���سɹ����true��ʾ�ɹ�;false��ʾʧ��;
* ��    ע:
* ��    ��: thm
* ��������:tianhuiming@novigo.com.cn
* ��������:2016-7-11
******************************************************************************************************/
cp_int32_t proc_semh_player_get_log(cp_css_hook_t *hook, cp_semh_session_t *session, cp_void_t *arg)
{
	cp_host_t							host = { 0, };
	cp_log_info_t						log_info = { 0, };
	cp_bool_t							ret_bool = cp_false;
	cp_char_t							buf[CP_APP_DEFAULT_GMPH_BUFFER_LEN] = { 0, };
	cp_socket_t							*s = session->socket;
	gmp_gmph_semh_t						*semh_p = session->semh_p;
	gmp_gmf_t							*gmf = session->gmf;
	cp_player_t							*tmp_player = (cp_player_t*)session->manager->app;
	cp_player_info_t					*tmp_player_info = (cp_player_info_t *)(tmp_player->app_info);
	cp_device_info_t					*tmp_player_device_info = ((cp_player_info_t*)(tmp_player->app_info))->device_info;
	const cp_char_t						*id = tmp_player_device_info->host.id;



	//��ȡhost
	parse_gmf_host(gmf, &host, buf, CP_APP_DEFAULT_GMPH_BUFFER_LEN);
	if (cp_strlen(host.id) != CP_APP_DEFAULT_ID_LENGTH - 1) {
		func_error_response(hook, session, arg, "get log error. parse_gmf_host() error. reason: [%s]", buf);
		return -1;
	}

	ret_bool = get_gmf_log_info_by_id(gmf, id, &log_info, buf, CP_APP_DEFAULT_GMPH_BUFFER_LEN);
	if (!ret_bool) {
		func_error_response(hook, session, arg, "get log error. get_gmf_log_info_by_id() error. reason: [%s]", buf);
		return -1;
	}

	//TODO:������־����ָ��

	return 0;
}

/******************************************************************************************************
* ��Ȩ����:thm & novigo
* ��������:proc_semh_player_delete_log
* ��    ��:�����豸ɾ����־
*
* ��    ��:
*				1��cp_css_hook_t			*hook				ָ�������CSS
*				2��cp_semh_session_t		*session			ָ��session
*				3��cp_void_t				*arg				ָ�����
* �� �� ֵ:
*			���سɹ����true��ʾ�ɹ�;false��ʾʧ��;
* ��    ע:
* ��    ��: thm
* ��������:tianhuiming@novigo.com.cn
* ��������:2016-7-11
******************************************************************************************************/
cp_int32_t proc_semh_player_delete_log(cp_css_hook_t *hook, cp_semh_session_t *session, cp_void_t *arg)
{
	cp_host_t							host = { 0, };
	cp_log_info_t						log_info = { 0, };
	cp_bool_t							ret_bool = cp_false;
	cp_char_t							buf[CP_APP_DEFAULT_GMPH_BUFFER_LEN] = { 0, };
	cp_socket_t							*s = session->socket;
	gmp_gmph_semh_t						*semh_p = session->semh_p;
	gmp_gmf_t							*gmf = session->gmf;
	cp_player_t							*tmp_player = (cp_player_t*)session->manager->app;
	cp_player_info_t					*tmp_player_info = (cp_player_info_t *)(tmp_player->app_info);
	cp_device_info_t					*tmp_player_device_info = ((cp_player_info_t*)(tmp_player->app_info))->device_info;
	const cp_char_t						*id = tmp_player_device_info->host.id;



	//��ȡhost
	parse_gmf_host(gmf, &host, buf, CP_APP_DEFAULT_GMPH_BUFFER_LEN);
	if (cp_strlen(host.id) != CP_APP_DEFAULT_ID_LENGTH - 1) {
		func_error_response(hook, session, arg, "get log error. parse_gmf_host() error. reason: [%s]", buf);
		return -1;
	}

	ret_bool = get_gmf_log_info_by_id(gmf, id, &log_info, buf, CP_APP_DEFAULT_GMPH_BUFFER_LEN);
	if (!ret_bool) {
		func_error_response(hook, session, arg, "get log error. get_gmf_log_info_by_id() error. reason: [%s]", buf);
		return -1;
	}

	//TODO:����ɾ����־ָ��

	return 0;
}

/******************************************************************************************************
* ��Ȩ����:thm & novigo
* ��������:proc_semh_player_delete_log
* ��    ��:�����豸��ѯ��־
*
* ��    ��:
*				1��cp_css_hook_t			*hook				ָ�������CSS
*				2��cp_semh_session_t		*session			ָ��session
*				3��cp_void_t				*arg				ָ�����
* �� �� ֵ:
*			���سɹ����true��ʾ�ɹ�;false��ʾʧ��;
* ��    ע:
* ��    ��: thm
* ��������:tianhuiming@novigo.com.cn
* ��������:2016-7-11
******************************************************************************************************/
cp_int32_t proc_semh_player_query_log(cp_css_hook_t *hook, cp_semh_session_t *session, cp_void_t *arg)
{
	cp_host_t							host = { 0, };
	cp_log_info_t						log_info = { 0, };
	cp_bool_t							ret_bool = cp_false;
	cp_char_t							buf[CP_APP_DEFAULT_GMPH_BUFFER_LEN] = { 0, };
	cp_socket_t							*s = session->socket;
	gmp_gmph_semh_t						*semh_p = session->semh_p;
	gmp_gmf_t							*gmf = session->gmf;
	cp_player_t							*tmp_player = (cp_player_t*)session->manager->app;
	cp_player_info_t					*tmp_player_info = (cp_player_info_t *)(tmp_player->app_info);
	cp_device_info_t					*tmp_player_device_info = ((cp_player_info_t*)(tmp_player->app_info))->device_info;
	const cp_char_t						*id = tmp_player_device_info->host.id;



	//��ȡhost
	parse_gmf_host(gmf, &host, buf, CP_APP_DEFAULT_GMPH_BUFFER_LEN);
	if (cp_strlen(host.id) != CP_APP_DEFAULT_ID_LENGTH - 1) {
		func_error_response(hook, session, arg, "get log error. parse_gmf_host() error. reason: [%s]", buf);
		return -1;
	}

	ret_bool = get_gmf_log_info_by_id(gmf, id, &log_info, buf, CP_APP_DEFAULT_GMPH_BUFFER_LEN);
	if (!ret_bool) {
		func_error_response(hook, session, arg, "get log error. get_gmf_log_info_by_id() error. reason: [%s]", buf);
		return -1;
	}

	//TODO:�����ѯ��־ָ��

	return 0;
}

/******************************************************************************************************
* ��Ȩ����:thm & novigo
* ��������:proc_semh_player_set_dev_info
* ��    ��:���������豸��Ϣ
*
* ��    ��:
*				1��cp_css_hook_t			*hook				ָ�������CSS
*				2��cp_semh_session_t		*session			ָ��session
*				3��cp_void_t				*arg				ָ�����
* �� �� ֵ:
*			���سɹ����true��ʾ�ɹ�;false��ʾʧ��;
* ��    ע:
* ��    ��: thm
* ��������:tianhuiming@novigo.com.cn
* ��������:2016-7-11
******************************************************************************************************/
cp_int32_t proc_semh_player_set_dev_info(cp_css_hook_t *hook, cp_semh_session_t *session, cp_void_t *arg)
{
	cp_char_t							buf[CP_APP_DEFAULT_GMPH_BUFFER_LEN] = { 0, };
	cp_device_info_t					tmp_device_info = { 0, };
	cp_socket_t							*s = session->socket;
	gmp_gmph_semh_t						*semh_p = session->semh_p;
	gmp_gmf_t							*gmf = session->gmf;
	cp_player_t							*tmp_player = (cp_player_t*)session->manager->app;
	cp_player_info_t					*tmp_player_info = (cp_player_info_t *)(tmp_player->app_info);
	cp_device_info_t					*tmp_player_device_info = ((cp_player_info_t*)(tmp_player->app_info))->device_info;



	//����object�ڵ�
	gmp_into_gmdu(gmf);

	//��ȡdevice id
	if (!get_gmf_device_info(gmf, &tmp_device_info, buf, CP_APP_DEFAULT_GMPH_BUFFER_LEN)) {
		cp_semh_session_log(error, session, "proc semh tmp_player set dev info error. get gmf devices id error. reason: %s.", buf);
		return -1;
	}

	gmp_outof_gmdu(gmf);

	//����豸�뿪�飬��ر����в���
	if (tmp_player_device_info->host.group != tmp_device_info.host.group) {
		if (css_device_type_css_video_player == tmp_player_device_info->host.type) {
			stop_all_video_media_play(tmp_player);
		}

		if (css_device_type_css_audio_player == tmp_player_device_info->host.type) {
			stop_all_audio_media_play(tmp_player);
		}
	}

	//����host��Ϣ
	cp_update_host_info(&tmp_player_device_info->host, &tmp_device_info.host);

	//����host��Ϣ
	cp_save_host_info(tmp_player, &tmp_player_device_info->host);

	//���ͷ���
	send_semh_response(tmp_player, s, CP_NULL, semh_p, GMP_NORMAL_STATUS_200, GMP_RETURN_SUCCESSED, cp_strlen(GMP_RETURN_SUCCESSED));

	return cp_true;
}

/******************************************************************************************************
* ��Ȩ����:thm & novigo
* ��������:proc_semh_player_get_dev_info
* ��    ��:������ȡ�豸��Ϣ
*
* ��    ��:
*				1��cp_css_hook_t			*hook				ָ�������CSS
*				2��cp_semh_session_t		*session			ָ��session
*				3��cp_void_t				*arg				ָ�����
* �� �� ֵ:
*			���سɹ����true��ʾ�ɹ�;false��ʾʧ��;
* ��    ע:
* ��    ��: thm
* ��������:tianhuiming@novigo.com.cn
* ��������:2016-7-11
******************************************************************************************************/
cp_int32_t proc_semh_player_get_dev_info(cp_css_hook_t *hook, cp_semh_session_t *session, cp_void_t *arg)
{
	cp_char_t							buf[CP_APP_DEFAULT_GMPH_BUFFER_LEN] = { 0, };
	cp_bool_t							is_found = cp_false;
	cp_request_info_t					request_info;
	cp_socket_t							*s = session->socket;
	gmp_gmph_semh_t						*semh_p = session->semh_p;
	gmp_gmf_t							*gmf = session->gmf;
	cp_player_t							*tmp_player = (cp_player_t*)session->manager->app;
	cp_player_info_t					*tmp_player_info = (cp_player_info_t *)(tmp_player->app_info);
	cp_device_info_t					*tmp_player_device_info = ((cp_player_info_t*)(tmp_player->app_info))->device_info;
	const cp_char_t						*device_id = tmp_player_device_info->host.id;



	//����object�ڵ�
	gmp_into_gmdu(gmf);

	//��ѯ�豸�б��Ƿ�����豸
	if (!get_gmf_devices_id_exist(gmf, device_id, buf, CP_APP_DEFAULT_GMPH_BUFFER_LEN)) {
		func_error_response(hook, session, arg, "get dev info error. get_gmf_devices_id_exist() error. reason: [%s]", buf);
		return -1;
	}
	else{
		is_found = cp_true;
	}

	//�����ȡ�豸��Ϣָ��
	if (is_found) {
		send_semh_player_get_dev_info_return(tmp_player, s, semh_p, &request_info, CP_NULL, 0);
	}
	else{
		send_semh_response(tmp_player, s, CP_NULL, semh_p, GMP_ERROR_STATUS_400, GMP_RETURN_FAILED, cp_strlen(GMP_RETURN_FAILED));
	}

	return 0;
}

/******************************************************************************************************
* ��Ȩ����:thm & novigo
* ��������:proc_semh_player_start_dev
* ��    ��:�����豸����
*
* ��    ��:
*				1��cp_css_hook_t			*hook				ָ�������CSS
*				2��cp_semh_session_t		*session			ָ��session
*				3��cp_void_t				*arg				ָ�����
* �� �� ֵ:
*			���سɹ����true��ʾ�ɹ�;false��ʾʧ��;
* ��    ע:
* ��    ��: thm
* ��������:tianhuiming@novigo.com.cn
* ��������:2016-7-11
******************************************************************************************************/
cp_int32_t proc_semh_player_start_dev(cp_css_hook_t *hook, cp_semh_session_t *session, cp_void_t *arg)
{
	cp_char_t							buf[CP_APP_DEFAULT_GMPH_BUFFER_LEN] = { 0, };
	cp_bool_t							is_found = cp_false;
	cp_socket_t							*s = session->socket;
	gmp_gmph_semh_t						*semh_p = session->semh_p;
	gmp_gmf_t							*gmf = session->gmf;
	cp_player_t							*tmp_player = (cp_player_t*)session->manager->app;
	cp_player_info_t					*tmp_player_info = (cp_player_info_t *)(tmp_player->app_info);
	cp_device_info_t					*tmp_player_device_info = ((cp_player_info_t*)(tmp_player->app_info))->device_info;
	const cp_char_t						*id = tmp_player_device_info->host.id;



	//����object�ڵ�
	gmp_into_gmdu(gmf);

	//��ѯ�豸�б��Ƿ�����豸
	if (!get_gmf_devices_id_exist(gmf, id, buf, CP_APP_DEFAULT_GMPH_BUFFER_LEN)) {
		func_error_response(hook, session, arg, "start dev error. get_gmf_devices_id_exist() error. reason: [%s]", buf);
		return -1;
	}
	else{
		is_found = cp_true;
	}

	if (is_found) {
		send_semh_response(tmp_player, s, CP_NULL, semh_p, GMP_NORMAL_STATUS_200, GMP_RETURN_SUCCESSED, cp_strlen(GMP_RETURN_SUCCESSED));
	}
	else{
		send_semh_response(tmp_player, s, CP_NULL, semh_p, GMP_ERROR_STATUS_400, GMP_RETURN_FAILED, cp_strlen(GMP_RETURN_FAILED));
	}

	//TODO,�����豸ָ��

	return 0;
}

/******************************************************************************************************
* ��Ȩ����:thm & novigo
* ��������:proc_semh_player_stop_dev
* ��    ��:�����豸ֹͣ
*
* ��    ��:
*				1��cp_css_hook_t			*hook				ָ�������CSS
*				2��cp_semh_session_t		*session			ָ��session
*				3��cp_void_t				*arg				ָ�����
* �� �� ֵ:
*			���سɹ����true��ʾ�ɹ�;false��ʾʧ��;
* ��    ע:
* ��    ��: thm
* ��������:tianhuiming@novigo.com.cn
* ��������:2016-7-11
******************************************************************************************************/
cp_int32_t proc_semh_player_stop_dev(cp_css_hook_t *hook, cp_semh_session_t *session, cp_void_t *arg)
{
	cp_char_t							buf[CP_APP_DEFAULT_GMPH_BUFFER_LEN] = { 0, };
	cp_bool_t							is_found = cp_false;
	cp_socket_t							*s = session->socket;
	gmp_gmph_semh_t						*semh_p = session->semh_p;
	gmp_gmf_t							*gmf = session->gmf;
	cp_player_t							*tmp_player = (cp_player_t*)session->manager->app;
	cp_player_info_t					*tmp_player_info = (cp_player_info_t *)(tmp_player->app_info);
	cp_device_info_t					*tmp_player_device_info = ((cp_player_info_t*)(tmp_player->app_info))->device_info;
	const cp_char_t						*id = tmp_player_device_info->host.id;



	//����object�ڵ�
	gmp_into_gmdu(gmf);

	//��ѯ�豸�б��Ƿ���ڱ��豸
	if (!get_gmf_devices_id_exist(gmf, id, buf, CP_APP_DEFAULT_GMPH_BUFFER_LEN)) {
		func_error_response(hook, session, arg, "start dev error. get_gmf_devices_id_exist() error. reason: [%s]", buf);
		return -1;
	}
	else{
		is_found = cp_true;
	}

	//����ֹͣ�豸ָ��
	if (is_found) {
		send_semh_response(tmp_player, s, CP_NULL, semh_p, GMP_NORMAL_STATUS_200, GMP_RETURN_SUCCESSED, cp_strlen(GMP_RETURN_SUCCESSED));
	}
	else{
		send_semh_response(tmp_player, s, CP_NULL, semh_p, GMP_ERROR_STATUS_400, GMP_RETURN_FAILED, cp_strlen(GMP_RETURN_FAILED));
	}

	//TODO:ֹͣ�豸ָ��

	return 0;
}

/******************************************************************************************************
* ��Ȩ����:thm & novigo
* ��������:proc_semh_player_test_dev
* ��    ��:�����豸����
*
* ��    ��:
*				1��cp_css_hook_t			*hook				ָ�������CSS
*				2��cp_semh_session_t		*session			ָ��session
*				3��cp_void_t				*arg				ָ�����
* �� �� ֵ:
*			���سɹ����true��ʾ�ɹ�;false��ʾʧ��;
* ��    ע:
* ��    ��: thm
* ��������:tianhuiming@novigo.com.cn
* ��������:2016-7-11
******************************************************************************************************/
cp_int32_t proc_semh_player_test_dev(cp_css_hook_t *hook, cp_semh_session_t *session, cp_void_t *arg)
{
	cp_char_t							buf[CP_APP_DEFAULT_GMPH_BUFFER_LEN] = { 0, };
	cp_bool_t							is_found = cp_false;
	cp_socket_t							*s = session->socket;
	gmp_gmph_semh_t						*semh_p = session->semh_p;
	gmp_gmf_t							*gmf = session->gmf;
	list_node							*device_info_list = CP_NULL;
	cp_player_t							*tmp_player = (cp_player_t*)session->manager->app;
	cp_player_info_t					*tmp_player_info = (cp_player_info_t *)(tmp_player->app_info);
	cp_device_info_t					*tmp_player_device_info = ((cp_player_info_t*)(tmp_player->app_info))->device_info;
	const cp_char_t						*id = tmp_player_device_info->host.id;



	//����object�ڵ�
	gmp_into_gmdu(gmf);

	//��ȡ�豸���б�
	if (!get_gmf_devices_info(gmf, &device_info_list, buf, CP_APP_DEFAULT_BUFFER_LENGTH)) {
		func_error_response(hook, session, arg, "test dev error. get_gmf_devices_info() error. reason: [%s]", buf);
		return -1;
	}

	gmp_outof_gmdu(gmf);

	send_semh_response(tmp_player, s, CP_NULL, semh_p, GMP_NORMAL_STATUS_200, GMP_RETURN_SUCCESSED, cp_strlen(GMP_RETURN_SUCCESSED));

	return 0;
}

/******************************************************************************************************
* ��Ȩ����:thm & novigo
* ��������:proc_semh_player_set_network
* ��    ��:���������豸����
*
* ��    ��:
*				1��cp_css_hook_t			*hook				ָ�������CSS
*				2��cp_semh_session_t		*session			ָ��session
*				3��cp_void_t				*arg				ָ�����
* �� �� ֵ:
*			���سɹ����true��ʾ�ɹ�;false��ʾʧ��;
* ��    ע:
* ��    ��: thm
* ��������:tianhuiming@novigo.com.cn
* ��������:2016-7-11
******************************************************************************************************/
cp_int32_t proc_semh_player_set_network(cp_css_hook_t *hook, cp_semh_session_t *session, cp_void_t *arg)
{
	cp_host_t							host = { 0, };
	cp_interface_t						network = { 0, };
	cp_int32_t							golbal_chunk_size = 0;
	cp_int32_t							chunk_size = 0;
	cp_char_t							buf[CP_APP_DEFAULT_GMPH_BUFFER_LEN] = { 0, };
	cp_bool_t							ret_bool = cp_false;
	cp_bool_t							is_found = cp_false;
	cp_socket_t							*s = session->socket;
	gmp_gmph_semh_t						*semh_p = session->semh_p;
	gmp_gmf_t							*gmf = session->gmf;
	cp_player_t							*tmp_player = (cp_player_t*)session->manager->app;
	cp_player_info_t					*tmp_player_info = (cp_player_info_t *)(tmp_player->app_info);
	cp_device_info_t					*tmp_player_device_info = ((cp_player_info_t*)(tmp_player->app_info))->device_info;
	const cp_char_t						*id = tmp_player_device_info->host.id;



	//��ȡHost�ڵ���Ϣ
	parse_gmf_host_network(gmf, &host, &network, buf, CP_APP_DEFAULT_GMPH_BUFFER_LEN);
	if (cp_strlen(host.id) != CP_APP_DEFAULT_LENGTH - 1) {
		func_error_response(hook, session, arg, "set network error. parse_gmf_host_network() error. reason: [%s]", buf);
		return -1;
	}

	ret_bool = get_gmf_chunk_size(gmf, &golbal_chunk_size, buf, CP_APP_DEFAULT_GMPH_BUFFER_LEN);

	//��ѯ�����豸�Ƿ����
	ret_bool = get_gmf_chunk_size_by_id(gmf, id, &chunk_size, buf, CP_APP_DEFAULT_GMPH_BUFFER_LEN);
	if (ret_bool) {
		is_found = cp_true;
	}

	//TODO:�������÷����������ݰ���С

	send_semh_response(tmp_player, s, CP_NULL, semh_p, GMP_NORMAL_STATUS_200, GMP_RETURN_SUCCESSED, cp_strlen(GMP_RETURN_SUCCESSED));

	return 0;
}

/******************************************************************************************************
* ��Ȩ����:thm & novigo
* ��������:proc_semh_player_set_focus
* ��    ��:���������豸����
*
* ��    ��:
*				1��cp_css_hook_t			*hook				ָ�������CSS
*				2��cp_semh_session_t		*session			ָ��session
*				3��cp_void_t				*arg				ָ�����
* �� �� ֵ:
*			���سɹ����true��ʾ�ɹ�;false��ʾʧ��;
* ��    ע:
* ��    ��: thm
* ��������:tianhuiming@novigo.com.cn
* ��������:2016-7-11
******************************************************************************************************/
cp_int32_t proc_semh_player_set_focus(cp_css_hook_t *hook, cp_semh_session_t *session, cp_void_t *arg)
{
#if 0
	cp_char_t							buf[CP_APP_DEFAULT_GMPH_BUFFER_LEN] = { 0, };
	cp_bool_t							is_found = cp_false;
	cp_socket_t							*s = session->socket;
	list_node							*devices_focus_list = CP_NULL;
	list_node							*device_focus_node = CP_NULL;
	gmp_gmph_semh_t						*semh_p = session->semh_p;
	gmp_gmf_t							*gmf = session->gmf;
	cp_player_t							*tmp_player = (cp_player_t*)session->manager->app;
	cp_player_info_t					*tmp_player_info = (cp_player_info_t *)(tmp_player->app_info);
	cp_device_info_t					*tmp_player_device_info = ((cp_player_info_t*)(tmp_player->app_info))->device_info;
	cp_char_t							*id = tmp_player_device_info->host.id;



	//����object�ڵ�
	gmp_into_gmdu(gmf);

	//�豸�����б�
	if (!get_gmf_devices_focus_list(gmf, &devices_focus_list, buf, CP_APP_DEFAULT_GMPH_BUFFER_LEN)) {
		func_error_response(hook, session, arg, "set focus error. get_gmf_devices_focus_list() error. reason: [%s]", buf);
		return -1;
	}

	device_focus_node = list_find(devices_focus_list, cp_list_find_device_focus_by_id, id);
	if (device_focus_node) {
		(cp_focus_info_t *)device_focus_node->data;
	}

	send_semh_response(tmp_player, s, CP_NULL, semh_p, GMP_NORMAL_STATUS_200, GMP_RETURN_SUCCESSED, cp_strlen(GMP_RETURN_SUCCESSED));

	//TODO ���ý���
#endif
	return 0;
}

/******************************************************************************************************
* ��Ȩ����:thm & novigo
* ��������:proc_semh_player_set_background
* ��    ��:���������豸����ͼ
*
* ��    ��:
*				1��cp_css_hook_t			*hook				ָ�������CSS
*				2��cp_semh_session_t		*session			ָ��session
*				3��cp_void_t				*arg				ָ�����
* �� �� ֵ:
*			���سɹ����true��ʾ�ɹ�;false��ʾʧ��;
* ��    ע:
* ��    ��: thm
* ��������:tianhuiming@novigo.com.cn
* ��������:2016-7-11
******************************************************************************************************/
cp_int32_t proc_semh_player_set_background(cp_css_hook_t *hook, cp_semh_session_t *session, cp_void_t *arg)
{
	cp_host_t							host = { 0, };
	cp_char_t							buf[CP_APP_DEFAULT_GMPH_BUFFER_LEN] = { 0, };
	cp_socket_t							*s = session->socket;
	gmp_gmph_semh_t						*semh_p = session->semh_p;
	gmp_gmf_t							*gmf = session->gmf;
	cp_player_t							*tmp_player = (cp_player_t*)session->manager->app;
	cp_player_info_t					*tmp_player_info = (cp_player_info_t *)(tmp_player->app_info);
	cp_device_info_t					*tmp_player_device_info = ((cp_player_info_t*)(tmp_player->app_info))->device_info;
	cp_player_background_info_t			background_device_media_info = { 0, };



	parse_gmf_host(gmf, &host, buf, CP_APP_DEFAULT_GMPH_BUFFER_LEN);
	if (cp_strlen(host.id) != CP_APP_DEFAULT_ID_LENGTH - 1) {
		func_error_response(hook, session, arg, "set background error. parse_gmf_host() error. reason: [%s]", buf);
		return -1;
	}

	//��ȡý����Ϣ�б�----<û��ý���б� ��Э�鲻��>
#if 0
	if (!get_gmf_background_medias_info(gmf, &background_medias_info_list, buf, CP_APP_DEFAULT_GMPH_BUFFER_LEN)) {
		cp_snprintf(buf, CP_APP_DEFAULT_GMPH_BUFFER_LEN, "set background info error get_gmf_background_medias_info() failed");
		return cp_false;
	}
#endif

	//��ȡ�豸��ý���б�
	if (!get_gmf_background_player_info(gmf, &background_device_media_info, buf, CP_APP_DEFAULT_GMPH_BUFFER_LEN)) {
		func_error_response(hook, session, arg, "set background error. get_gmf_background_player_info() error. reason: [%s]", buf);
		return -1;
	}

	//TODO:������ͼƬ

	return -1;
}

/******************************************************************************************************
* ��Ȩ����:thm & novigo
* ��������:proc_semh_player_clear_background
* ��    ��:��������豸����ͼ
*
* ��    ��:
*				1��cp_css_hook_t			*hook				ָ�������CSS
*				2��cp_semh_session_t		*session			ָ��session
*				3��cp_void_t				*arg				ָ�����
* �� �� ֵ:
*			���سɹ����true��ʾ�ɹ�;false��ʾʧ��;
* ��    ע:
* ��    ��: thm
* ��������:tianhuiming@novigo.com.cn
* ��������:2016-7-11
******************************************************************************************************/
cp_int32_t proc_semh_player_clear_background(cp_css_hook_t *hook, cp_semh_session_t *session, cp_void_t *arg)
{
	cp_host_t							host = { 0, };
	cp_char_t							buf[CP_APP_DEFAULT_GMPH_BUFFER_LEN] = { 0, };
	cp_bool_t							is_found = cp_false;
	cp_socket_t							*s = session->socket;
	gmp_gmph_semh_t						*semh_p = session->semh_p;
	gmp_gmf_t							*gmf = session->gmf;
	cp_player_t							*tmp_player = (cp_player_t*)session->manager->app;
	cp_player_info_t					*tmp_player_info = (cp_player_info_t *)(tmp_player->app_info);
	cp_device_info_t					*tmp_player_device_info = ((cp_player_info_t*)(tmp_player->app_info))->device_info;
	const cp_char_t						*id = tmp_player_device_info->host.id;



	parse_gmf_host(gmf, &host, buf, CP_APP_DEFAULT_GMPH_BUFFER_LEN);
	if (cp_strlen(host.id) != CP_APP_DEFAULT_ID_LENGTH - 1) {
		func_error_response(hook, session, arg, "set background error. parse_gmf_host() error. reason: [%s]", buf);
		return -1;
	}

	//��ѯ�豸�ڵ��б��豸�Ƿ����
	if (!get_gmf_devices_id_exist(gmf, id, buf, CP_APP_DEFAULT_GMPH_BUFFER_LEN)) {
		is_found = cp_false;
	}
	else{
		is_found = cp_true;
	}

	//TODO:�����������ָ��
	if (is_found) {

	}

	send_semh_response(tmp_player, s, CP_NULL, semh_p, GMP_NORMAL_STATUS_200, GMP_RETURN_SUCCESSED, cp_strlen(GMP_RETURN_SUCCESSED));

	return 0;
}

/******************************************************************************************************
* ��Ȩ����:thm & novigo
* ��������:proc_semh_player_set_word
* ��    ��:���������豸��Ļ
*
* ��    ��:
*				1��cp_css_hook_t			*hook				ָ�������CSS
*				2��cp_semh_session_t		*session			ָ��session
*				3��cp_void_t				*arg				ָ�����
* �� �� ֵ:
*			���سɹ����true��ʾ�ɹ�;false��ʾʧ��;
* ��    ע:
* ��    ��: thm
* ��������:tianhuiming@novigo.com.cn
* ��������:2016-7-11
******************************************************************************************************/
cp_int32_t proc_semh_player_set_word(cp_css_hook_t *hook, cp_semh_session_t *session, cp_void_t *arg)
{
	cp_host_t							host = { 0, };
	cp_char_t							buf[CP_APP_DEFAULT_GMPH_BUFFER_LEN] = { 0, };
	cp_socket_t							*s = session->socket;
	gmp_gmph_semh_t						*semh_p = session->semh_p;
	gmp_gmf_t							*gmf = session->gmf;
	cp_player_t							*tmp_player = (cp_player_t*)session->manager->app;
	cp_player_info_t					*tmp_player_info = (cp_player_info_t *)(tmp_player->app_info);
	cp_device_info_t					*tmp_player_device_info = ((cp_player_info_t*)(tmp_player->app_info))->device_info;
	cp_player_background_info_t			background_device_media_info = { 0, };



	parse_gmf_host(gmf, &host, buf, CP_APP_DEFAULT_GMPH_BUFFER_LEN);
	if (cp_strlen(host.id) != CP_APP_DEFAULT_ID_LENGTH - 1) {
		func_error_response(hook, session, arg, "set background error. parse_gmf_host() error. reason: [%s]", buf);
		return -1;
	}

	//��ȡý����Ϣ�б�----<û��ý���б� ��Э�鲻��>
#if 0
	if (!get_gmf_background_medias_info(gmf, &background_medias_info_list, buf, CP_APP_DEFAULT_GMPH_BUFFER_LEN)) {
		cp_snprintf(buf, CP_APP_DEFAULT_GMPH_BUFFER_LEN, "set background info error get_gmf_background_medias_info() failed");
		return cp_false;
	}
#endif

	//��ȡ�豸��ý���б�
	if (!get_gmf_background_player_info(gmf, &background_device_media_info, buf, CP_APP_DEFAULT_GMPH_BUFFER_LEN)) {
		func_error_response(hook, session, arg, "set background error. get_gmf_background_player_info() error. reason: [%s]", buf);
		return -1;
	}

	//TODO:����������Ļָ��

	return 0;
}

/******************************************************************************************************
* ��Ȩ����:thm & novigo
* ��������:proc_semh_player_clear_word
* ��    ��:��������豸��Ļ
*
* ��    ��:
*				1��cp_css_hook_t			*hook				ָ�������CSS
*				2��cp_semh_session_t		*session			ָ��session
*				3��cp_void_t				*arg				ָ�����
* �� �� ֵ:
*			���سɹ����true��ʾ�ɹ�;false��ʾʧ��;
* ��    ע:
* ��    ��: thm
* ��������:tianhuiming@novigo.com.cn
* ��������:2016-7-11
******************************************************************************************************/
cp_int32_t proc_semh_player_clear_word(cp_css_hook_t *hook, cp_semh_session_t *session, cp_void_t *arg)
{
	cp_host_t							host = { 0, };
	cp_char_t							buf[CP_APP_DEFAULT_GMPH_BUFFER_LEN] = { 0, };
	cp_bool_t							is_found = cp_false;
	cp_socket_t							*s = session->socket;
	gmp_gmph_semh_t						*semh_p = session->semh_p;
	gmp_gmf_t							*gmf = session->gmf;
	cp_player_t							*tmp_player = (cp_player_t*)session->manager->app;
	cp_player_info_t					*tmp_player_info = (cp_player_info_t *)(tmp_player->app_info);
	cp_device_info_t					*tmp_player_device_info = ((cp_player_info_t*)(tmp_player->app_info))->device_info;
	const cp_char_t						*id = tmp_player_device_info->host.id;



	parse_gmf_host(gmf, &host, buf, CP_APP_DEFAULT_GMPH_BUFFER_LEN);
	if (cp_strlen(host.id) != CP_APP_DEFAULT_ID_LENGTH - 1) {
		func_error_response(hook, session, arg, "set background error. parse_gmf_host() error. reason: [%s]", buf);
		return -1;
	}

	//�豸�б��б��豸�Ƿ����
	if (!get_gmf_devices_id_exist(gmf, id, buf, CP_APP_DEFAULT_GMPH_BUFFER_LEN)) {
		is_found = cp_false;
	}
	else{
		is_found = cp_true;
	}

	//TODO:�������������Ļָ��
	if (is_found) {

	}

	send_semh_response(tmp_player, s, CP_NULL, semh_p, GMP_NORMAL_STATUS_200, GMP_RETURN_SUCCESSED, cp_strlen(GMP_RETURN_SUCCESSED));

	return -1;
}

/******************************************************************************************************
* ��Ȩ����:thm & novigo
* ��������:proc_semh_player_reflesh_picture
* ��    ��:����ˢ���豸��Ļ\����
*
* ��    ��:
*				1��cp_css_hook_t			*hook				ָ�������CSS
*				2��cp_semh_session_t		*session			ָ��session
*				3��cp_void_t				*arg				ָ�����
* �� �� ֵ:
*			���سɹ����true��ʾ�ɹ�;false��ʾʧ��;
* ��    ע:
* ��    ��: thm
* ��������:tianhuiming@novigo.com.cn
* ��������:2016-7-11
******************************************************************************************************/
cp_int32_t proc_semh_player_reflesh_picture(cp_css_hook_t *hook, cp_semh_session_t *session, cp_void_t *arg)
{
	cp_socket_t							*s = session->socket;
	gmp_gmph_semh_t						*semh_p = session->semh_p;
	gmp_gmf_t							*gmf = session->gmf;
	cp_char_t							buf[CP_APP_DEFAULT_GMPH_BUFFER_LEN] = { 0, };
	cp_host_t							host = { 0, };
	cp_player_background_info_t			background_devices_medias = { 0, };



	parse_gmf_host(gmf, &host, buf, CP_APP_DEFAULT_GMPH_BUFFER_LEN);
	if (cp_strlen(host.id) != CP_APP_DEFAULT_ID_LENGTH - 1) {
		func_error_response(hook, session, arg, "reflesh picture error. parse_gmf_host() error. reason: [%s]", buf);
		return -1;
	}

	if (!get_gmf_background_player_reflesh_info(gmf, &background_devices_medias, buf, CP_APP_DEFAULT_GMPH_BUFFER_LEN)) {
		func_error_response(hook, session, arg, "reflesh picture error. get_gmf_background_player_reflesh_info() error. reason: [%s]", buf);
		return -1;
	}

	//TODO ����ˢ��ָ��

	return 0;
}

/******************************************************************************************************
* ��Ȩ����:thm & novigo
* ��������:proc_semh_player_offline_get_passwd
* ��    ��:�������߻�ȡ����
*
* ��    ��:
*				1��cp_css_hook_t			*hook				ָ�������CSS
*				2��cp_semh_session_t		*session			ָ��session
*				3��cp_void_t				*arg				ָ�����
* �� �� ֵ:
*			���سɹ����true��ʾ�ɹ�;false��ʾʧ��;
* ��    ע:
* ��    ��: thm
* ��������:tianhuiming@novigo.com.cn
* ��������:2016-7-11
******************************************************************************************************/
cp_int32_t proc_semh_player_offline_get_passwd(cp_css_hook_t *hook, cp_semh_session_t *session, cp_void_t *arg)
{
	cp_host_t							host = { 0, };
	cp_return_info_t					return_info = { 0, };
	cp_bool_t							ret_bool = cp_false;
	cp_char_t							buf[CP_APP_DEFAULT_GMPH_BUFFER_LEN] = { 0, };
	cp_socket_t							*s = session->socket;
	cp_sockaddr_in						*remote_addr = &session->socket->remote_addr;
	cp_player_t							*tmp_player = (cp_player_t*)session->manager->app;
	cp_player_info_t					*tmp_player_info = (cp_player_info_t *)(tmp_player->app_info);
	cp_device_info_t					*tmp_player_device_info = ((cp_player_info_t*)(tmp_player->app_info))->device_info;
	gmp_gmph_semh_t						*semh_p = session->semh_p;
	gmp_gmf_t							*gmf = session->gmf;
	gmp_gmf_t							*new_gmf = CP_NULL;
	gmp_gmdu_t							*object_gmdu = CP_NULL;
	list_node							*offline_info_list = CP_NULL;



	//��ȡhost
	parse_gmf_host(gmf, &host, buf, CP_APP_DEFAULT_GMPH_BUFFER_LEN);
	if (cp_strlen(host.id) != CP_APP_DEFAULT_ID_LENGTH - 1) {
		func_error_response(hook, session, arg, "offline get passwd error. parse_gmf_host() error. reason: [%s]", buf);
		return -1;
	}

	//����object�ڵ�
	gmp_into_gmdu(gmf);

	//��ȡ�����豸��Ϣ-----<���Բ��ý���,����Ϊ��>
	if (!get_gmf_offline_info_list(gmf, &offline_info_list, buf, CP_APP_DEFAULT_GMPH_BUFFER_LEN)) {
		func_error_response(hook, session, arg, "offline get passwd error. get_gmf_offline_info_list() error. reason: [%s]", buf);
		return -1;
	}

	//���÷�����Ϣ
	cp_snprintf(return_info.host_id, cp_sizeof(return_info.host_id), "%s", tmp_player_device_info->host.id);
	cp_snprintf(return_info.passwd, cp_sizeof(return_info.passwd), "%s", "1234");
	cp_snprintf(return_info.reason, cp_sizeof(return_info.reason), "%s", GMP_RETURN_SUCCESSED);
	return_info.status = GMP_NORMAL_STATUS_200;

	new_gmf = gmp_create_gmf();
	if (!new_gmf) {
		func_error_response(hook, session, arg, "offline get passwd error. create gmf error.");
		return -1;
	}

	//����gmf���߷�����Ϣ
	object_gmdu = make_gmf_offline_passwd_return(new_gmf, tmp_player_device_info, &return_info, buf, CP_APP_DEFAULT_GMPH_BUFFER_LEN);
	if (!object_gmdu) {
		gmp_destroy_gmf(new_gmf);
		func_error_response(hook, session, arg, "offline get passwd error. make_gmf_offline_passwd_return() error. reason: [%s]", buf);
		return -1;
	}

	gmp_add_gmdu(new_gmf, object_gmdu);

	ret_bool = send_semh_response_data(tmp_player, s, remote_addr, semh_p, new_gmf, GMP_NORMAL_STATUS_200, GMP_RETURN_SUCCESSED, sizeof(GMP_RETURN_SUCCESSED));
	if (!ret_bool) {
		cp_log_error(tmp_player->logger, "send semh tmp_player get dev info return error! send_semh_request_data() failed.");
	}

	gmp_destroy_gmf(new_gmf);

	return 0;
}

/******************************************************************************************************
* ��Ȩ����:thm & novigo
* ��������:proc_semh_player_offline_set_passwd
* ��    ��:����������������
*
* ��    ��:
*				1��cp_css_hook_t			*hook				ָ�������CSS
*				2��cp_semh_session_t		*session			ָ��session
*				3��cp_void_t				*arg				ָ�����
* �� �� ֵ:
*			���سɹ����true��ʾ�ɹ�;false��ʾʧ��;
* ��    ע:
* ��    ��: thm
* ��������:tianhuiming@novigo.com.cn
* ��������:2016-7-11
******************************************************************************************************/
cp_int32_t proc_semh_player_offline_set_passwd(cp_css_hook_t *hook, cp_semh_session_t *session, cp_void_t *arg)
{
	cp_host_t							host = { 0, };
	cp_char_t							buf[CP_APP_DEFAULT_GMPH_BUFFER_LEN] = { 0, };
	cp_bool_t							is_found = cp_false;
	cp_socket_t							*s = session->socket;
	gmp_gmph_semh_t						*semh_p = session->semh_p;
	gmp_gmf_t							*gmf = session->gmf;
	cp_player_t							*tmp_player = (cp_player_t*)session->manager->app;
	cp_player_info_t					*tmp_player_info = (cp_player_info_t *)(tmp_player->app_info);
	cp_device_info_t					*tmp_player_device_info = ((cp_player_info_t*)(tmp_player->app_info))->device_info;
	const cp_char_t						*device_id = tmp_player_device_info->host.id;



	//��ȡhost�ڵ���Ϣ
	parse_gmf_host(gmf, &host, buf, CP_APP_DEFAULT_GMPH_BUFFER_LEN);
	if (cp_strlen(host.id) != CP_APP_DEFAULT_ID_LENGTH - 1) {
		func_error_response(hook, session, arg, "offline set passwd error. parse_gmf_host() error. reason: [%s]", buf);
		return -1;
	}

	//����object�ڵ�
	gmp_into_gmdu(gmf);

	//��ȡdevice id
	if (!get_gmf_devices_id_exist(gmf, device_id, buf, CP_APP_DEFAULT_GMPH_BUFFER_LEN)) {
		func_error_response(hook, session, arg, "offline set passwd error. get_gmf_devices_id_exist() error. reason: [%s]", buf);
		return -1;
	}
	else{
		is_found = cp_true;
	}

	//TODO:�������߻�ȡ�豸ָ��
	if (is_found) {

	}

	send_semh_response(tmp_player, s, CP_NULL, semh_p, GMP_NORMAL_STATUS_200, GMP_RETURN_SUCCESSED, cp_strlen(GMP_RETURN_SUCCESSED));

	return 0;
}

/******************************************************************************************************
* ��Ȩ����:thm & novigo
* ��������:proc_semh_player_reflesh_picture
* ��    ��:�������߸�������
*
* ��    ��:
*				1��cp_css_hook_t			*hook				ָ�������CSS
*				2��cp_semh_session_t		*session			ָ��session
*				3��cp_void_t				*arg				ָ�����
* �� �� ֵ:
*			���سɹ����true��ʾ�ɹ�;false��ʾʧ��;
* ��    ע:
* ��    ��: thm
* ��������:tianhuiming@novigo.com.cn
* ��������:2016-7-11
******************************************************************************************************/
cp_int32_t proc_semh_player_offline_update_passwd(cp_css_hook_t *hook, cp_semh_session_t *session, cp_void_t *arg)
{
	cp_host_t							host = { 0, };
	cp_char_t							buf[CP_APP_DEFAULT_GMPH_BUFFER_LEN] = { 0, };
	cp_bool_t							is_found = cp_false;
	cp_socket_t							*s = session->socket;
	gmp_gmph_semh_t						*semh_p = session->semh_p;
	gmp_gmf_t							*gmf = session->gmf;
	cp_player_t							*tmp_player = (cp_player_t*)session->manager->app;
	cp_player_info_t					*tmp_player_info = (cp_player_info_t *)(tmp_player->app_info);
	cp_device_info_t					*tmp_player_device_info = ((cp_player_info_t*)(tmp_player->app_info))->device_info;
	const cp_char_t						*id = tmp_player_device_info->host.id;



	//��ȡhost�ڵ���Ϣ
	parse_gmf_host(gmf, &host, buf, CP_APP_DEFAULT_GMPH_BUFFER_LEN);
	if (cp_strlen(host.id) != CP_APP_DEFAULT_ID_LENGTH - 1) {
		func_error_response(hook, session, arg, "offline set passwd error. parse_gmf_host() error. reason: [%s]", buf);
		return -1;
	}

	//����object�ڵ�
	gmp_into_gmdu(gmf);

	//��ѯ�豸�б����Ƿ���ڱ��豸
	if (!get_gmf_devices_id_exist(gmf, id, buf, CP_APP_DEFAULT_GMPH_BUFFER_LEN)) {
		func_error_response(hook, session, arg, "offline set passwd error. get_gmf_devices_id_exist() error. reason: [%s]", buf);
		return cp_false;
	}
	else{
		is_found = cp_true;
	}

	//TODO:�������߻�ȡ�豸ָ��
	if (is_found) {

	}

	send_semh_response(tmp_player, s, CP_NULL, semh_p, GMP_NORMAL_STATUS_200, GMP_RETURN_SUCCESSED, cp_strlen(GMP_RETURN_SUCCESSED));

	return 0;
}

/******************************************************************************************************
* ��Ȩ����:thm & novigo
* ��������:proc_semh_player_offline_get_information
* ��    ��:�������߻�ȡ�豸��Ϣ
*
* ��    ��:
*				1��cp_css_hook_t			*hook				ָ�������CSS
*				2��cp_semh_session_t		*session			ָ��session
*				3��cp_void_t				*arg				ָ�����
* �� �� ֵ:
*			���سɹ����true��ʾ�ɹ�;false��ʾʧ��;
* ��    ע:
* ��    ��: thm
* ��������:tianhuiming@novigo.com.cn
* ��������:2016-7-11
******************************************************************************************************/
cp_int32_t proc_semh_player_offline_get_information(cp_css_hook_t *hook, cp_semh_session_t *session, cp_void_t *arg)
{
	cp_host_t							host = { 0, };
	cp_center_addr_t					center_addr = { 0, };
	cp_return_info_t					return_info = { 0, };
	list_node							*offline_info_list;
	cp_char_t							buf[CP_APP_DEFAULT_GMPH_BUFFER_LEN] = { 0, };
	cp_bool_t							is_found = cp_false;
	cp_socket_t							*s = session->socket;
	cp_sockaddr_in						*remote_addr = &s->remote_addr;
	gmp_gmph_semh_t						*semh_p = session->semh_p;
	gmp_gmf_t							*gmf = session->gmf;
	gmp_gmf_t							*new_gmf = CP_NULL;
	gmp_gmdu_t							*object_gmdu = CP_NULL;
	cp_player_t							*tmp_player = (cp_player_t*)session->manager->app;
	cp_player_info_t					*tmp_player_info = (cp_player_info_t *)(tmp_player->app_info);
	cp_device_info_t					*tmp_player_device_info = ((cp_player_info_t*)(tmp_player->app_info))->device_info;
	cp_bool_t							ret_bool = cp_false;
	gmdt_string_p_t						*gmp_str = CP_NULL;



	//��ȡhost�ڵ���Ϣ
	parse_gmf_host(gmf, &host, buf, CP_APP_DEFAULT_GMPH_BUFFER_LEN);
	if (cp_strlen(host.id) != CP_APP_DEFAULT_ID_LENGTH - 1) {
		func_error_response(hook, session, arg, "offline get information error. parse_gmf_host() error. reason: [%s]", buf);
		return -1;
	}

	//����object�ڵ�
	gmp_into_gmdu(gmf);

	//��ȡ�����豸��Ϣ
	if (!get_gmf_offline_info_list(gmf, &offline_info_list, buf, CP_APP_DEFAULT_GMPH_BUFFER_LEN)) {
		func_error_response(hook, session, arg, "offline get information error. get_gmf_offline_info_list() error. reason: [%s]", buf);
		return -1;
	}

	cp_snprintf(center_addr.ip, cp_sizeof(center_addr.ip), "%s", tmp_player_info->center_addr);
	center_addr.tcp_port = tmp_player_info->center_port;

	//���÷�����Ϣ
	cp_snprintf(return_info.host_id, cp_sizeof(return_info.host_id), "%s", tmp_player_device_info->host.id);
	cp_snprintf(return_info.reason, cp_sizeof(return_info.reason), "%s", GMP_RETURN_SUCCESSED);
	return_info.status = GMP_NORMAL_STATUS_200;

	new_gmf = gmp_create_gmf();
	if (!new_gmf) {
		func_error_response(hook, session, arg, "offline get information error. create gmf error.");
		return -1;
	}

	//����gmf���߷�����Ϣ
	object_gmdu = make_gmf_offline_information_return(new_gmf, tmp_player_device_info, &return_info, &center_addr, buf, CP_APP_DEFAULT_GMPH_BUFFER_LEN);
	if (object_gmdu) {
		gmp_add_gmdu(new_gmf, object_gmdu);
	}

	gmp_gmf_printf(new_gmf, &gmp_str, NULL, 0, gmp_print_style_pretty);

	ret_bool = send_semh_response_data(tmp_player, s, remote_addr, semh_p, new_gmf, GMP_NORMAL_STATUS_200, GMP_RETURN_SUCCESSED, sizeof(GMP_RETURN_SUCCESSED));
	if (!ret_bool) {
		cp_log_error(tmp_player->logger, "player offline get information error! send_semh_request_data() failed.");
	}

	gmp_destroy_gmf(new_gmf);

	return 0;
}

/******************************************************************************************************
* ��Ȩ����:thm & novigo
* ��������:proc_semh_player_offline_set_information
* ��    ��:�������������豸��Ϣ
*
* ��    ��:
*				1��cp_css_hook_t			*hook				ָ�������CSS
*				2��cp_semh_session_t		*session			ָ��session
*				3��cp_void_t				*arg				ָ�����
* �� �� ֵ:
*			���سɹ����true��ʾ�ɹ�;false��ʾʧ��;
* ��    ע:
* ��    ��: thm
* ��������:tianhuiming@novigo.com.cn
* ��������:2016-7-11
******************************************************************************************************/
cp_int32_t proc_semh_player_offline_set_information(cp_css_hook_t *hook, cp_semh_session_t *session, cp_void_t *arg)
{
	cp_host_t							host = { 0, };
	cp_char_t							buf[CP_APP_DEFAULT_GMPH_BUFFER_LEN] = { 0, };
	cp_char_t							id[CP_APP_DEFAULT_ID_LENGTH] = { 0, };
	cp_device_info_t					tmp_device_info = { 0, };
	cp_center_addr_t					center_addr = { 0, };
	cp_socket_t							*s = session->socket;
	gmp_gmph_semh_t						*semh_p = session->semh_p;
	gmp_gmf_t							*gmf = session->gmf;
	cp_player_t							*tmp_player = (cp_player_t*)session->manager->app;
	cp_player_info_t					*tmp_player_info = (cp_player_info_t *)(tmp_player->app_info);
	cp_device_info_t					*tmp_player_device_info = ((cp_player_info_t*)(tmp_player->app_info))->device_info;
	gmp_gmdu_t							*gmdu = CP_NULL;
	gmp_gmdt_t							*gmdt = CP_NULL;
	cp_bool_t							ret_bool = cp_false;



	//��ȡhost�ڵ���Ϣ
	parse_gmf_host(gmf, &host, buf, CP_APP_DEFAULT_GMPH_BUFFER_LEN);
	if (cp_strlen(host.id) != CP_APP_DEFAULT_ID_LENGTH - 1) {
		func_error_response(hook, session, arg, "offline get information error. parse_gmf_host() error. reason: [%s]", buf);
		return -1;
	}

	//����Device�ڵ�
	gmdt = gmp_create_gmdt(gmf, "%T%p%d", GMP_GMDT_ST, CP_APP_STR_DEVICE, cp_strlen(CP_APP_STR_DEVICE));
	gmdu = gmp_find_gmdu(gmf, gmdt);
	if (!gmdu) {
		func_error_response(hook, session, arg, "offline set information error. find device element error.");
		return -1;
	}

	//����Device�ڵ�
	gmp_reset_gmdu(gmf, gmdu);

	//����Device�ڵ�
	gmp_into_gmdu(gmf);

	//��ȡID����
	ret_bool = get_gmf_element(gmf, id, CP_APP_DEFAULT_ID_LENGTH, GMP_GMDT_ST, CP_APP_STR_ID, buf, CP_APP_DEFAULT_GMPH_BUFFER_LEN);

	ret_bool = get_gmf_player_info(gmf, &tmp_device_info, &center_addr, buf, CP_APP_DEFAULT_GMPH_BUFFER_LEN);

	//TODO ���������豸
	send_semh_response(tmp_player, s, CP_NULL, semh_p, GMP_NORMAL_STATUS_200, GMP_RETURN_SUCCESSED, cp_strlen(GMP_RETURN_SUCCESSED));

	return 0;
}

/******************************************************************************************************
* ��Ȩ����:thm & novigo
* ��������:proc_semh_player_media_play
* ��    ��:����ý�岥��
*
* ��    ��:
*				1��cp_css_hook_t			*hook				ָ�������CSS
*				2��cp_semh_session_t		*session			ָ��session
*				3��cp_void_t				*arg				ָ�����
* �� �� ֵ:
*			���سɹ����true��ʾ�ɹ�;false��ʾʧ��;
* ��    ע:
* ��    ��: thm
* ��������:tianhuiming@novigo.com.cn
* ��������:2016-7-11
******************************************************************************************************/
cp_int32_t proc_semh_player_media_play(cp_css_hook_t *hook, cp_semh_session_t *session, cp_void_t *arg)
{
	cp_host_t							host = { 0, };
	cp_bool_t							ret_bool = cp_false;
	cp_int32_t							ret_int = 0;
	cp_char_t							buf[CP_APP_DEFAULT_GMPH_BUFFER_LEN] = { 0, };
	cp_socket_t							*s = session->socket;
	gmp_gmph_semh_t						*semh_p = session->semh_p;
	gmp_gmf_t							*gmf = session->gmf;
	cp_player_t							*tmp_player = (cp_player_t*)session->manager->app;
	cp_player_info_t					*tmp_player_info = (cp_player_info_t *)(tmp_player->app_info);
	cp_device_info_t					*tmp_player_device_info = ((cp_player_info_t*)(tmp_player->app_info))->device_info;
	cp_play_channel_info_t				*tmp_pc_info = CP_NULL;



	//��ȡhost�ڵ���Ϣ
	parse_gmf_host(gmf, &host, buf, CP_APP_DEFAULT_GMPH_BUFFER_LEN);
	if (cp_strlen(host.id) != CP_APP_DEFAULT_ID_LENGTH - 1) {
		cp_semh_hook_log(error, hook, session, "parse_gmf_host() error. reason: [%s]", buf);
		return -1;
	}

	//���õ�ǰ�ڵ�Ϊobject
	gmp_top_gmdu(gmf);

	//����object
	gmp_into_gmdu(gmf);

	//��ȡ��Ҫ��ý����Ϣ
	tmp_pc_info = get_semh_play_info(hook, session, arg, buf, CP_APP_DEFAULT_GMPH_BUFFER_LEN);
	if (!tmp_pc_info) {
		cp_semh_hook_log(error, hook, session, "get_semh_play_info() error. reason: [%s]", buf);
		return -1;
	}

	//����ý����Ϣ
	tmp_pc_info->mpy = cp_media_process_type_video;
	if (css_device_type_css_video_player == tmp_player_device_info->host.type) {
		ret_int = create_media_play(tmp_player, tmp_pc_info);
		if (ret_int) {
			cp_semh_hook_log(error, hook, session, "create_media_play() error");
			return -1;
		}
	}
	else {
		cp_semh_hook_log(error, hook, session,
			"proc_semh_player_media_play() error. device_type[%d] error. not video player.",
			tmp_player_device_info->host.type);
	}

	//TODO:����ý��ͨ������
	//send_semh_response(tmp_player, s, CP_NULL, semh_p, GMP_NORMAL_STATUS_200, GMP_RETURN_SUCCESSED, cp_strlen(GMP_RETURN_SUCCESSED));
	cp_semh_hook_log(notice, hook, session, "successed!");

	return 0;
}

/******************************************************************************************************
* ��Ȩ����:thm & novigo
* ��������:proc_semh_player_media_play_update
* ��    ��:����ý�����
*
* ��    ��:
*				1��cp_css_hook_t			*hook				ָ�������CSS
*				2��cp_semh_session_t		*session			ָ��session
*				3��cp_void_t				*arg				ָ�����
* �� �� ֵ:
*			���سɹ����true��ʾ�ɹ�;false��ʾʧ��;
* ��    ע:
* ��    ��: thm
* ��������:tianhuiming@novigo.com.cn
* ��������:2016-7-11
******************************************************************************************************/
cp_int32_t proc_semh_player_media_play_update(cp_css_hook_t *hook, cp_semh_session_t *session, cp_void_t *arg)
{
	cp_host_t							host = { 0, };
	cp_cmd_info_t						cmd_info = { 0, };
	cp_bool_t							ret_bool = cp_false;
	cp_char_t							buf[CP_APP_DEFAULT_GMPH_BUFFER_LEN] = { 0, };
	cp_socket_t							*s = session->socket;
	gmp_gmph_semh_t						*semh_p = session->semh_p;
	gmp_gmf_t							*gmf = session->gmf;
	cp_player_t							*tmp_player = (cp_player_t*)session->manager->app;
	cp_player_info_t					*tmp_player_info = (cp_player_info_t *)(tmp_player->app_info);
	cp_device_info_t					*tmp_player_device_info = ((cp_player_info_t*)(tmp_player->app_info))->device_info;
	cp_play_channel_info_t				*tmp_pc_info = CP_NULL;


	//��ȡhost�ڵ���Ϣ
	parse_gmf_host(gmf, &host, buf, CP_APP_DEFAULT_GMPH_BUFFER_LEN);
	if (cp_strlen(host.id) != CP_APP_DEFAULT_ID_LENGTH - 1) {
		cp_semh_hook_log(error, hook, session, "parse_gmf_host() error. reason: [%s]", buf);
		return -1;
	}

	//��ȡ��Ҫ��ý����Ϣ
	tmp_pc_info = get_semh_play_info(hook, session, arg, buf, CP_APP_DEFAULT_GMPH_BUFFER_LEN);
	if (!tmp_pc_info) {
		cp_semh_hook_log(error, hook, session, "get_semh_play_info() error. reason: [%s]", buf);
		return cp_false;
	}

	//����ý����Ϣ
	destroy_play_info(session, tmp_pc_info);

	//��ʼ����ý��Դ��Ϣ

	//TODO:����ý��ͨ������
	//send_semh_response(tmp_player, s, CP_NULL, semh_p, GMP_NORMAL_STATUS_200, GMP_RETURN_SUCCESSED, cp_strlen(GMP_RETURN_SUCCESSED));
	cp_semh_hook_log(notice, hook, session, "successed!");

	return 0;
}

/******************************************************************************************************
* ��Ȩ����:thm & novigo
* ��������:proc_semh_player_media_layer_update
* ��    ��:����ý���θ���
*
* ��    ��:
*				1��cp_css_hook_t			*hook				ָ�������CSS
*				2��cp_semh_session_t		*session			ָ��session
*				3��cp_void_t				*arg				ָ�����
* �� �� ֵ:
*			���سɹ����true��ʾ�ɹ�;false��ʾʧ��;
* ��    ע:
* ��    ��: thm
* ��������:tianhuiming@novigo.com.cn
* ��������:2016-7-11
******************************************************************************************************/
cp_int32_t proc_semh_player_media_layer_update(cp_css_hook_t *hook, cp_semh_session_t *session, cp_void_t *arg)
{
	cp_host_t							host = { 0, };
	cp_bool_t							ret_bool = cp_false;
	cp_char_t							buf[CP_APP_DEFAULT_GMPH_BUFFER_LEN] = { 0, };
	cp_socket_t							*s = session->socket;
	gmp_gmph_semh_t						*semh_p = session->semh_p;
	gmp_gmf_t							*gmf = session->gmf;
	cp_player_t							*tmp_player = (cp_player_t*)session->manager->app;
	cp_player_info_t					*tmp_player_info = (cp_player_info_t *)(tmp_player->app_info);
	cp_device_info_t					*tmp_player_device_info = ((cp_player_info_t*)(tmp_player->app_info))->device_info;
	cp_int32_t							no = tmp_player_device_info->host.no;
	cp_play_channel_info_t				*tmp_pc_info = CP_NULL;



	//��ȡhost�ڵ���Ϣ
	parse_gmf_host(gmf, &host, buf, CP_APP_DEFAULT_GMPH_BUFFER_LEN);
	if (cp_strlen(host.id) != CP_APP_DEFAULT_ID_LENGTH - 1) {
		cp_semh_hook_log(error, hook, session, "parse_gmf_host() error. reason: [%s]", buf);
		return -1;
	}

	//��ȡ��Ҫ��ý����Ϣ
	tmp_pc_info = get_semh_play_info(hook, session, arg, buf, CP_APP_DEFAULT_GMPH_BUFFER_LEN);
	if (!tmp_pc_info) {
		cp_semh_hook_log(error, hook, session, "get_semh_play_info() error. reason: [%s]", buf);
		return cp_false;
	}

	//group_list->rects_list->rect_pair(���ο���Ϣ)

	//TODO:����ý��ͨ������
	//send_semh_response(tmp_player, s, CP_NULL, semh_p, GMP_NORMAL_STATUS_200, GMP_RETURN_SUCCESSED, cp_strlen(GMP_RETURN_SUCCESSED));

	cp_semh_hook_log(notice, hook, session, "successed!");

	return 0;
}

/******************************************************************************************************
* ��Ȩ����:thm & novigo
* ��������:proc_semh_player_media_stop
* ��    ��:����ý��ֹͣ
*
* ��    ��:
*				1��cp_css_hook_t			*hook				ָ�������CSS
*				2��cp_semh_session_t		*session			ָ��session
*				3��cp_void_t				*arg				ָ�����
* �� �� ֵ:
*			���سɹ����true��ʾ�ɹ�;false��ʾʧ��;
* ��    ע:
* ��    ��: thm
* ��������:tianhuiming@novigo.com.cn
* ��������:2016-7-11
******************************************************************************************************/
cp_int32_t proc_semh_player_media_stop(cp_css_hook_t *hook, cp_semh_session_t *session, cp_void_t *arg)
{
	cp_host_t							host = { 0, };
	cp_bool_t							ret_bool = cp_false;
	cp_int32_t							ret_int = 0;
	cp_char_t							buf[CP_APP_DEFAULT_GMPH_BUFFER_LEN] = { 0, };
	cp_socket_t							*s = session->socket;
	gmp_gmph_semh_t						*semh_p = session->semh_p;
	gmp_gmf_t							*gmf = session->gmf;
	cp_player_t							*tmp_player = (cp_player_t*)session->manager->app;
	cp_player_info_t					*tmp_player_info = (cp_player_info_t *)(tmp_player->app_info);
	cp_device_info_t					*tmp_player_device_info = ((cp_player_info_t*)(tmp_player->app_info))->device_info;
	cp_int32_t							no = tmp_player_device_info->host.no;
	cp_play_channel_info_t				*tmp_pc_info = CP_NULL;



	//��ȡhost�ڵ���Ϣ
	parse_gmf_host(gmf, &host, buf, CP_APP_DEFAULT_GMPH_BUFFER_LEN);
	if (cp_strlen(host.id) != CP_APP_DEFAULT_ID_LENGTH - 1) {
		cp_semh_hook_log(error, hook, session, "parse_gmf_host() error. reason: [%s]", buf);
		return -1;
	}

	//��ȡ��Ҫ��ý����Ϣ
	tmp_pc_info = get_semh_play_info(hook, session, arg, buf, CP_APP_DEFAULT_GMPH_BUFFER_LEN);
	if (!tmp_pc_info) {
		cp_semh_hook_log(error, hook, session, "get_semh_play_info() error. reason: [%s]", buf);
		return cp_false;
	}

	//����ý����Ϣ
	tmp_pc_info->mpy = cp_media_process_type_video;
	ret_int = destroy_media_play(tmp_player, tmp_pc_info);
	if (ret_int) {
		cp_semh_hook_log(error, hook, session, "destroy_media_play() error.");
		return -1;
	}

	//����ý����Ϣ
	destroy_play_info(session, tmp_pc_info);
	//TODO:����ý��ͨ��ֹͣ
	//send_semh_response(tmp_player, s, CP_NULL, semh_p, GMP_NORMAL_STATUS_200, GMP_RETURN_SUCCESSED, cp_strlen(GMP_RETURN_SUCCESSED));

	cp_semh_hook_log(notice, hook, session, "successed!");

	return 0;
}

/******************************************************************************************************
* ��Ȩ����:thm & novigo
* ��������:proc_semh_player_media_close
* ��    ��:����ý��ر�
*
* ��    ��:
*				1��cp_css_hook_t			*hook				ָ�������CSS
*				2��cp_semh_session_t		*session			ָ��session
*				3��cp_void_t				*arg				ָ�����
* �� �� ֵ:
*			���سɹ����true��ʾ�ɹ�;false��ʾʧ��;
* ��    ע:
* ��    ��: thm
* ��������:tianhuiming@novigo.com.cn
* ��������:2016-7-11
******************************************************************************************************/
cp_int32_t proc_semh_player_media_close(cp_css_hook_t *hook, cp_semh_session_t *session, cp_void_t *arg)
{
	cp_host_t							host;
	cp_interface_t						network;
	cp_bool_t							ret_bool = cp_false;
	cp_bool_t							is_found = cp_false;
	cp_int32_t							tmp_group_id = 0;
	cp_char_t							buf[CP_APP_DEFAULT_GMPH_BUFFER_LEN] = { 0, };
	list_node							*media_channel_list;
	cp_socket_t							*s = session->socket;
	gmp_gmph_semh_t						*semh_p = session->semh_p;
	gmp_gmf_t							*gmf = session->gmf;
	cp_player_t							*tmp_player = (cp_player_t*)session->manager->app;
	cp_player_info_t					*tmp_player_info = (cp_player_info_t *)(tmp_player->app_info);
	cp_device_info_t					*tmp_player_device_info = ((cp_player_info_t*)(tmp_player->app_info))->device_info;
	cp_int32_t							no = tmp_player_device_info->host.no;


	//��ȡhost�ڵ���Ϣ
	parse_gmf_host_network(gmf, &host, &network, buf, CP_APP_DEFAULT_GMPH_BUFFER_LEN);
	if (cp_strlen(host.id) != CP_APP_DEFAULT_ID_LENGTH - 1) {
		func_error_response(hook, session, arg, "media close error. parse_gmf_host_network() error. reason: [%s]", buf);
		return -1;
	}

	//���õ�ǰ�ڵ�Ϊobject
	gmp_top_gmdu(gmf);

	//����object
	gmp_into_gmdu(gmf);

	if (!get_gmf_play_media_channel_info(gmf, &media_channel_list, buf, CP_APP_DEFAULT_GMPH_BUFFER_LEN)) {
		func_error_response(hook, session, arg, "media close error. get_gmf_play_media_channel_info() error. reason: [%s]", buf);
		return -1;
	}

	//TODO:����ý��ͨ���ر�
	//send_semh_response(tmp_player, s, CP_NULL, semh_p, GMP_NORMAL_STATUS_200, GMP_RETURN_SUCCESSED, cp_strlen(GMP_RETURN_SUCCESSED));

	return cp_true;
}

/******************************************************************************************************
* ��Ȩ����:thm & novigo
* ��������:proc_semh_player_media_get_channel_info
* ��    ��:������ȡý��ͨ��
*
* ��    ��:
*				1��cp_css_hook_t			*hook				ָ�������CSS
*				2��cp_semh_session_t		*session			ָ��session
*				3��cp_void_t				*arg				ָ�����
* �� �� ֵ:
*			���سɹ����true��ʾ�ɹ�;false��ʾʧ��;
* ��    ע:
* ��    ��: thm
* ��������:tianhuiming@novigo.com.cn
* ��������:2016-7-11
******************************************************************************************************/
cp_int32_t proc_semh_player_media_get_channel_info(cp_css_hook_t *hook, cp_semh_session_t *session, cp_void_t *arg)
{
	cp_host_t							host = { 0, };
	cp_bool_t							ret_bool = cp_false;
	cp_char_t							buf[CP_APP_DEFAULT_GMPH_BUFFER_LEN] = { 0, };
	cp_socket_t							*s = session->socket;
	gmp_gmph_semh_t						*semh_p = session->semh_p;
	gmp_gmf_t							*gmf = session->gmf;
	cp_player_t							*tmp_player = (cp_player_t*)session->manager->app;
	cp_player_info_t					*tmp_player_info = (cp_player_info_t *)(tmp_player->app_info);
	cp_device_info_t					*tmp_player_device_info = ((cp_player_info_t*)(tmp_player->app_info))->device_info;
	cp_int32_t							no = tmp_player_device_info->host.no;
	cp_cmd_info_t						command_info = { 0, };



	//��ȡhost�ڵ���Ϣ
	parse_gmf_host(gmf, &host, buf, CP_APP_DEFAULT_GMPH_BUFFER_LEN);
	if (cp_strlen(host.id) != CP_APP_DEFAULT_ID_LENGTH - 1) {
		func_error_response(hook, session, arg, "media stop error. parse_gmf_host() error. reason: [%s]", buf);
		return -1;
	}

	return 0;
}

/******************************************************************************************************
* ��Ȩ����:thm & novigo
* ��������:proc_semh_player_audio_play
* ��    ��:����ý�岥��
*
* ��    ��:
*				1��cp_css_hook_t			*hook				ָ�������CSS
*				2��cp_semh_session_t		*session			ָ��session
*				3��cp_void_t				*arg				ָ�����
* �� �� ֵ:
*			���سɹ����true��ʾ�ɹ�;false��ʾʧ��;
* ��    ע:
* ��    ��: thm
* ��������:tianhuiming@novigo.com.cn
* ��������:2016-7-11
******************************************************************************************************/
cp_int32_t proc_semh_player_audio_play(cp_css_hook_t *hook, cp_semh_session_t *session, cp_void_t *arg)
{
	cp_host_t							host = { 0, };
	cp_bool_t							ret_bool = cp_false;
	cp_int32_t							ret_int = 0;
	cp_char_t							buf[CP_APP_DEFAULT_GMPH_BUFFER_LEN] = { 0, };
	cp_socket_t							*s = session->socket;
	gmp_gmph_semh_t						*semh_p = session->semh_p;
	gmp_gmf_t							*gmf = session->gmf;
	cp_player_t							*tmp_player = (cp_player_t*)session->manager->app;
	cp_player_info_t					*tmp_player_info = (cp_player_info_t *)(tmp_player->app_info);
	cp_device_info_t					*tmp_player_device_info = ((cp_player_info_t*)(tmp_player->app_info))->device_info;
	cp_play_channel_info_t				*tmp_pc_info = CP_NULL;



	//��ȡhost�ڵ���Ϣ
	parse_gmf_host(gmf, &host, buf, CP_APP_DEFAULT_GMPH_BUFFER_LEN);
	if (cp_strlen(host.id) != CP_APP_DEFAULT_ID_LENGTH - 1) {
		cp_semh_hook_log(error, hook, session, "parse_gmf_host() error. reason: [%s]", buf);
		return -1;
	}

	//���õ�ǰ�ڵ�Ϊobject
	gmp_top_gmdu(gmf);

	//����object
	gmp_into_gmdu(gmf);

	//��ȡ��Ҫ��ý����Ϣ
	tmp_pc_info = get_semh_play_info(hook, session, arg, buf, CP_APP_DEFAULT_GMPH_BUFFER_LEN);
	if (!tmp_pc_info) {
		cp_semh_hook_log(error, hook, session, "get_semh_play_info() error. reason: [%s]", buf);
		return -1;
	}

	//����ý����Ϣ
	tmp_pc_info->mpy = cp_media_process_type_audio;
	if (css_device_type_css_audio_player == tmp_player_device_info->host.type) {
		ret_int = create_media_play(tmp_player, tmp_pc_info);
		if (ret_int) {
			cp_semh_hook_log(error, hook, session, "create_media_play() error");
			return -1;
		}
	}
	else {
		cp_semh_hook_log(error, hook, session,
			"proc_semh_player_audio_play() error. device_type[%d] error. not audio player.",
			tmp_player_device_info->host.type);
	}

	//TODO:����ý��ͨ������
	//send_semh_response(tmp_player, s, CP_NULL, semh_p, GMP_NORMAL_STATUS_200, GMP_RETURN_SUCCESSED, cp_strlen(GMP_RETURN_SUCCESSED));
	cp_semh_hook_log(notice, hook, session, "paly audio successed!");

	return 0;
}

/******************************************************************************************************
* ��Ȩ����:thm & novigo
* ��������:proc_semh_player_audio_play_update
* ��    ��:����ý�����
*
* ��    ��:
*				1��cp_css_hook_t			*hook				ָ�������CSS
*				2��cp_semh_session_t		*session			ָ��session
*				3��cp_void_t				*arg				ָ�����
* �� �� ֵ:
*			���سɹ����true��ʾ�ɹ�;false��ʾʧ��;
* ��    ע:
* ��    ��: thm
* ��������:tianhuiming@novigo.com.cn
* ��������:2016-7-11
******************************************************************************************************/
cp_int32_t proc_semh_player_audio_play_update(cp_css_hook_t *hook, cp_semh_session_t *session, cp_void_t *arg)
{
	cp_host_t							host = { 0, };
	cp_cmd_info_t						cmd_info = { 0, };
	cp_bool_t							ret_bool = cp_false;
	cp_int32_t							ret_int = 0;
	cp_char_t							buf[CP_APP_DEFAULT_GMPH_BUFFER_LEN] = { 0, };
	cp_socket_t							*s = session->socket;
	gmp_gmph_semh_t						*semh_p = session->semh_p;
	gmp_gmf_t							*gmf = session->gmf;
	cp_player_t							*tmp_player = (cp_player_t*)session->manager->app;
	cp_player_info_t					*tmp_player_info = (cp_player_info_t *)(tmp_player->app_info);
	cp_device_info_t					*tmp_player_device_info = ((cp_player_info_t*)(tmp_player->app_info))->device_info;
	cp_play_channel_info_t				*tmp_pc_info = CP_NULL;


	//��ȡhost�ڵ���Ϣ
	parse_gmf_host(gmf, &host, buf, CP_APP_DEFAULT_GMPH_BUFFER_LEN);
	if (cp_strlen(host.id) != CP_APP_DEFAULT_ID_LENGTH - 1) {
		cp_semh_hook_log(error, hook, session, "parse_gmf_host() error. reason: [%s]", buf);
		return -1;
	}

	//��ȡ��Ҫ��ý����Ϣ
	tmp_pc_info = get_semh_play_info(hook, session, arg, buf, CP_APP_DEFAULT_GMPH_BUFFER_LEN);
	if (!tmp_pc_info) {
		cp_semh_hook_log(error, hook, session, "get_semh_play_info() error. reason: [%s]", buf);
		return cp_false;
	}

	//����ý����Ϣ
	tmp_pc_info->mpy = cp_media_process_type_audio;
	if (css_device_type_css_audio_player == tmp_player_device_info->host.type) {
		ret_int = update_media_play(tmp_player, tmp_pc_info);
		if (ret_int) {
			cp_semh_hook_log(error, hook, session, "update_media_play() error");
			return -1;
		}
	}
	else {
		cp_semh_hook_log(error, hook, session,
			"proc_semh_player_audio_play() error. device_type[%d] error. not audio player.",
			tmp_player_device_info->host.type);
	}
	//����ý����Ϣ
	//destroy_play_info(session, tmp_pc_info);

	//��ʼ����ý��Դ��Ϣ

	//TODO:����ý��ͨ������
	//send_semh_response(tmp_player, s, CP_NULL, semh_p, GMP_NORMAL_STATUS_200, GMP_RETURN_SUCCESSED, cp_strlen(GMP_RETURN_SUCCESSED));
	cp_semh_hook_log(notice, hook, session, "audio update successed!");

	return 0;
}

/******************************************************************************************************
* ��Ȩ����:thm & novigo
* ��������:proc_semh_player_audio_stop
* ��    ��:����ý��ֹͣ
*
* ��    ��:
*				1��cp_css_hook_t			*hook				ָ�������CSS
*				2��cp_semh_session_t		*session			ָ��session
*				3��cp_void_t				*arg				ָ�����
* �� �� ֵ:
*			���سɹ����true��ʾ�ɹ�;false��ʾʧ��;
* ��    ע:
* ��    ��: thm
* ��������:tianhuiming@novigo.com.cn
* ��������:2016-7-11
******************************************************************************************************/
cp_int32_t proc_semh_player_audio_stop(cp_css_hook_t *hook, cp_semh_session_t *session, cp_void_t *arg)
{
	cp_host_t							host = { 0, };
	cp_bool_t							ret_bool = cp_false;
	cp_int32_t							ret_int = 0;
	cp_char_t							buf[CP_APP_DEFAULT_GMPH_BUFFER_LEN] = { 0, };
	cp_socket_t							*s = session->socket;
	gmp_gmph_semh_t						*semh_p = session->semh_p;
	gmp_gmf_t							*gmf = session->gmf;
	cp_player_t							*tmp_player = (cp_player_t*)session->manager->app;
	cp_player_info_t					*tmp_player_info = (cp_player_info_t *)(tmp_player->app_info);
	cp_device_info_t					*tmp_player_device_info = ((cp_player_info_t*)(tmp_player->app_info))->device_info;
	cp_int32_t							no = tmp_player_device_info->host.no;
	cp_play_channel_info_t				*tmp_pc_info = CP_NULL;



	//��ȡhost�ڵ���Ϣ
	parse_gmf_host(gmf, &host, buf, CP_APP_DEFAULT_GMPH_BUFFER_LEN);
	if (cp_strlen(host.id) != CP_APP_DEFAULT_ID_LENGTH - 1) {
		cp_semh_hook_log(error, hook, session, "parse_gmf_host() error. reason: [%s]", buf);
		return -1;
	}

	//��ȡ��Ҫ��ý����Ϣ
	tmp_pc_info = get_semh_play_info(hook, session, arg, buf, CP_APP_DEFAULT_GMPH_BUFFER_LEN);
	if (!tmp_pc_info) {
		cp_semh_hook_log(error, hook, session, "get_semh_play_info() error. reason: [%s]", buf);
		return cp_false;
	}

	//����ý����Ϣ
	tmp_pc_info->mpy = cp_media_process_type_audio;
	ret_int = destroy_media_play(tmp_player, tmp_pc_info);
	if (ret_int) {
		cp_semh_hook_log(error, hook, session, "destroy_media_play() error.");
		return -1;
	}

	//����ý����Ϣ
	destroy_play_info(session, tmp_pc_info);
	//TODO:����ý��ͨ��ֹͣ
	//send_semh_response(tmp_player, s, CP_NULL, semh_p, GMP_NORMAL_STATUS_200, GMP_RETURN_SUCCESSED, cp_strlen(GMP_RETURN_SUCCESSED));

	cp_semh_hook_log(notice, hook, session, "audio stop successed!");

	return 0;
}

/******************************************************************************************************
* ��Ȩ����:thm & novigo
* ��������:send_semh_player_get_dev_info_return
* ��    ��:��ȡ�豸��Ϣ����
*
* ��    ��:
*			1��cp_player_t				*player,
*			2��cp_socket_t				*s,
*			3��gmp_gmph_semh_t			*semh,
*			4��cp_request_info_t		*request_info,
*			5��cp_sockaddr_in			*addr,
*			6��cp_int32_t				flags
* �� �� ֵ:
*			���سɹ����true��ʾ�ɹ�;false��ʾʧ��;
* ��    ע:
* ��    ��: thm
* ��������:tianhuiming@novigo.com.cn
* ��������:2016-7-11
******************************************************************************************************/
cp_int32_t send_semh_player_get_dev_info_return(cp_player_t *player, cp_socket_t *s, gmp_gmph_semh_t *semh, cp_request_info_t *request_info,
	cp_sockaddr_in *addr, cp_int32_t flags)
{
	gmp_gmf_t							*new_gmf = CP_NULL;
	gmp_gmdu_t							*object_gmdu = CP_NULL;
	cp_player_t							*tmp_player = player;
	cp_player_info_t					*tmp_player_info = (cp_player_info_t *)(player->app_info);
	cp_device_info_t					*tmp_player_device_info = ((cp_player_info_t*)(player->app_info))->device_info;
	cp_bool_t							ret_bool = cp_false;
	cp_char_t							buf[CP_APP_DEFAULT_BUFFER_LENGTH] = { 0, };


	new_gmf = gmp_create_gmf();
	if (!new_gmf) {
		cp_log_error(tmp_player->logger, "player get dev infor return error. gmp_create_gmf() error.");
		return cp_false;
	}

	//make dev info return 
	object_gmdu = make_gmf_get_dev_info_return(new_gmf, tmp_player_device_info, buf, CP_APP_DEFAULT_BUFFER_LENGTH);
	if (!object_gmdu) {
		gmp_destroy_gmf(new_gmf);
		cp_log_error(tmp_player->logger, "player get dev infor return error. make_gmf_get_dev_info_return() error. [%s]", buf);
		return cp_false;
	}
	gmp_add_gmdu(new_gmf, object_gmdu);

	ret_bool = send_semh_response_data(tmp_player, request_info->s, addr, semh, new_gmf, GMP_NORMAL_STATUS_200, GMP_RETURN_SUCCESSED,
		sizeof(GMP_RETURN_SUCCESSED));
	if (ret_bool) {
		cp_log_error(tmp_player->logger, "player get dev infor return error. send_semh_response_data() error.");
	}

	gmp_destroy_gmf(new_gmf);

	return cp_true;
}

/******************************************************************************************************
* ��Ȩ����:thm & novigo
* ��������:send_semh_player_get_log_info_return
* ��    ��:������ȡ��־��Ϣ����
*
* ��    ��:
*			1��cp_player_t				*player,
*			2��cp_socket_t				*s,
*			3��gmp_gmph_semh_t			*semh,
*			4��cp_request_info_t		*request_info,
*			5��cp_sockaddr_in			*addr,
*			6��cp_int32_t				flags
* �� �� ֵ:
*			���سɹ����true��ʾ�ɹ�;false��ʾʧ��;
* ��    ע:
* ��    ��: thm
* ��������:tianhuiming@novigo.com.cn
* ��������:2016-7-11
******************************************************************************************************/
cp_int32_t send_semh_player_get_log_info_return(cp_player_t *player, cp_socket_t *s, gmp_gmph_semh_t *semh, cp_request_info_t *request_info,
	cp_sockaddr_in *addr, cp_int32_t flags)
{
	gmp_gmf_t							*new_gmf = CP_NULL;
	gmp_gmdu_t							*object_gmdu = CP_NULL;
	cp_player_t							*tmp_player = player;
	cp_player_info_t					*tmp_player_info = (cp_player_info_t *)(player->app_info);
	cp_device_info_t					*tmp_player_device_info = ((cp_player_info_t*)(player->app_info))->device_info;
	cp_bool_t							ret_bool = cp_false;
	cp_char_t							buf[CP_APP_DEFAULT_BUFFER_LENGTH] = { 0, };
	cp_log_info_t						log_info;



	new_gmf = gmp_create_gmf();
	if (!new_gmf) {
		cp_log_error(tmp_player->logger, "player get log info return error. gmp_create_gmf() error");
		return cp_false;
	}

	//make dev info return 
	object_gmdu = make_gmf_get_log_info_return(new_gmf, tmp_player_device_info, &log_info, buf, CP_APP_DEFAULT_BUFFER_LENGTH);
	if (!object_gmdu) {
		gmp_destroy_gmf(new_gmf);
		cp_log_error(tmp_player->logger, "player get log info return error.make_gmf_get_log_info_return() error.[%s]", buf);
		return cp_false;
	}
	gmp_add_gmdu(new_gmf, object_gmdu);

	ret_bool = send_semh_response_data(tmp_player, request_info->s, addr, semh, new_gmf, GMP_NORMAL_STATUS_200, GMP_RETURN_SUCCESSED,
		sizeof(GMP_RETURN_SUCCESSED));
	if (ret_bool) {
		cp_log_error(tmp_player->logger, "player get log info return error. send_semh_response_data() error.");
	}

	gmp_destroy_gmf(new_gmf);

	return cp_true;
}

cp_int32_t func_global(cp_css_hook_t *hook, cp_semh_session_t *session, cp_void_t *arg)
{
	return 0;
}

cp_int32_t func_global_destroy(cp_css_hook_t *hook, cp_semh_session_t *session, cp_void_t *arg)
{
	if (!session || !session->gmf) {
		return 0;
	}

	gmp_destroy_gmf(session->gmf);

	return 0;
}

cp_int32_t func_check_semh_command(cp_css_hook_t *hook, cp_semh_session_t *session, cp_void_t *arg)
{
	cp_hook_t								*tmp_hook = CP_NULL;
	cp_hook_manager_t						*tmp_manager = CP_NULL;
	gmp_gmph_semh_t							*tmp_semh = CP_NULL;
	cp_css_hook_info_t						tmp_css_hoot_info = { 0, };



	//��ȡhook������д���
	//CP_MODULE_MANAGER_INFO_SET_TYPE(&tmp_css_hoot_info, cp_module_manager_type_hook);

	CP_MODULE_MANAGER_INFO_SET_TYPE(&tmp_css_hoot_info, CP_MODULE_MANAGER_TYPE_HOOK(1));
	tmp_manager = (cp_hook_manager_t*)cp_get_manager(CP_NULL, &tmp_css_hoot_info);
	tmp_semh = (gmp_gmph_semh_t*)cp_buf_get_pos(session->buf);
	tmp_css_hoot_info.command = tmp_semh->command;
	tmp_hook = (cp_hook_t*)cp_manager_get_module(tmp_manager, &tmp_css_hoot_info);
	if (!tmp_hook) {
		cp_semh_session_log(error, session,
			"func_check_semh_command() error. get module error.");
		return -2;
	}
	return 0;
}

cp_int32_t func_get_semh_hook(cp_css_hook_t *hook, cp_semh_session_t *session, cp_void_t *arg)
{
	cp_hook_t								*tmp_hook = CP_NULL;
	cp_hook_manager_t						*tmp_manager = CP_NULL;
	gmp_gmph_semh_t							*tmp_semh = CP_NULL;
	cp_css_hook_info_t						tmp_css_hoot_info = { 0, };
	cp_module_manager_info_t				tmp_module_manager_info = { 0, };



	//��ȫ�ֵ�handle���ص�session��
	//CP_MODULE_MANAGER_INFO_SET_TYPE(&tmp_module_manager_info, cp_module_manager_type_hook);
	CP_MODULE_MANAGER_INFO_SET_TYPE(&tmp_module_manager_info, CP_MODULE_MANAGER_TYPE_HOOK(1));
	tmp_manager = (cp_hook_manager_t*)cp_get_manager(CP_NULL, &tmp_module_manager_info);
	if (!tmp_manager) {
		cp_semh_session_log(error, session,
			"func_get_semh_hook() error. get manager error.");
		return -1;
	}
	//��ȡhook������д���
	tmp_semh = (gmp_gmph_semh_t*)cp_buf_get_pos(session->buf);
	tmp_css_hoot_info.command = tmp_semh->command;
	tmp_hook = (cp_hook_t*)cp_manager_get_module(tmp_manager, &tmp_css_hoot_info);
	if (!tmp_hook) {
		cp_semh_session_log(error, session,
			"func_get_semh_hook() error. get module error.");
		return -2;
	}
	CP_HOOK_SET_NEXT_HOOK_INFO(hook, tmp_hook);
	return 0;
}

cp_int32_t func_parse_gmf_data(cp_css_hook_t *hook, cp_semh_session_t *session, cp_void_t *arg)
{
	cp_bool_t						ret_bool = cp_false;
	const cp_char_t					*p = CP_NULL;
	gmp_gmf_t						*gmf = CP_NULL;
	gmdt_string_p_t					*gmp_str = CP_NULL;
	gmp_gmph_semh_t					*semh_p = CP_NULL;
	cp_char_t						emh_buf[CP_APP_DEFAULT_GMPH_BUFFER_LEN] = { 0, };


	p = cp_buf_get_pos(session->buf);
	semh_p = (gmp_gmph_semh_t*)p;
	//����gmf��������
	gmf = gmp_create_gmf();
	if (!gmf) {
		cp_semh_session_log(error, session, "func_parse_gmf_data() error. get module error.");
		return -1;
	}
	//���ù����ڴ淽ʽ
	gmp_set_work_mode(gmf, gmf_work_mode_shared_memory);

	//gmf decode
	if (!gmp_gmf_decode(gmf, (cp_char_t*)(p + CSS_GMP_GMPH_SEMH_LEN), semh_p->length)) {
		gmp_gmf_printf(gmf, &gmp_str, CP_NULL, 0, gmp_print_style_pretty);

		if (gmp_str && gmp_str->data) {
			cp_semh_session_log(error, session,
				"func parse gmf data error. gmp_gmf_decode() error. gmf error_no[%d] reason[%s]. gmf:%s.",
				gmp_get_error_no(gmf),
				gmp_get_error_text(gmf),
				gmp_str->data);
		}
		else{
			cp_semh_session_log(error, session, "func parse gmf data error. gmp_gmf_decode() error.");
		}
		return -1;
	}
	else{
		if (gmp_gmf_printf(gmf, &gmp_str, CP_NULL, 0, gmp_print_style_pretty)) {
			cp_semh_session_log(info, session, "func parse gmf data gmp_gmf_printf() successed. %s", gmp_str->data);
		}
		else{
			cp_semh_session_log(info, session, "func parse gmf data error gmp_gmf_printf() error.");
		}
	}

	session->semh_p = semh_p;
	session->gmf = gmf;

	return 0;
}

cp_int32_t func_gmf_error_data(cp_css_hook_t *hook, cp_semh_session_t *session, cp_void_t *arg)
{
	return 0;
}

cp_int32_t func_error_response(cp_css_hook_t *hook, cp_semh_session_t *session, cp_void_t *arg, cp_char_t *fmt, ...)
{
	gmp_gmph_semh_t						*semh_p = CP_NULL;
	cp_player_t							*tmp_player = (cp_player_t*)session->manager->app;
	cp_sockaddr_in						*remote = &(session->socket->remote_addr);
	cp_char_t							tmp_error_buf[CP_APP_DEFAULT_ERROR_TEXT_BUFFER_LEN] = { 0, };
	va_list								marker;


	va_start(marker, fmt);

	cp_snprintf(tmp_error_buf, CP_APP_DEFAULT_ERROR_TEXT_BUFFER_LEN, fmt, marker);

	va_end(marker);

	semh_p = session->semh_p;

	send_semh_response(tmp_player, session->socket, remote, semh_p, GMP_ERROR_STATUS_400, tmp_error_buf, cp_strlen(tmp_error_buf));

	cp_semh_session_log(error, session, "%s", tmp_error_buf);

	return cp_true;
}

cp_bool_t func_join_media_multicast(cp_player_t *player, const cp_char_t *ip, const cp_int32_t port)
{
	cp_player_info_t			*tmp_player_info = (cp_player_info_t *)player->app_info;
	cp_sockaddr_in				tmp_multicast_addr;
	cp_int32_t					ret_int;


	cp_ip4_addr(ip, port, &tmp_multicast_addr);

	player->multicast_listen = cp_create_socket(player, cp_socket_type_multicast);
	if (!player->multicast_listen) {
		cp_log_error(player->logger, "join media multicast error. cp_create_socket() error.");
		return -1;
	}

	ret_int = cp_listen_socket(player->multicast_listen, &tmp_multicast_addr);
	if (ret_int) {
		cp_log_error(player->logger, "join media multicast error. cp_listen_socket(multicast) error.[%s:%d]", ip, port);
	}

	return cp_true;
}

cp_bool_t send_semh_response_data(cp_player_t *player, cp_socket_t *s, const cp_sockaddr_in *remote_addr,
	gmp_gmph_semh_t *semh, gmp_gmf_t *src_gmf, cp_int32_t status, cp_char_t *reason, cp_int32_t nreason)
{
	cp_int32_t							len = 0;
	cp_char_t							*p;
	gmp_gmph_semh_t						ret_semh = *semh;
	gmdt_string_p_t						*gmp_str = CP_NULL;
	gmdt_iobuffer_p_t					*iob = CP_NULL;
	cp_buf_t							*gmf_data = CP_NULL;
	cp_player_t							*tmp_player = player;
	cp_player_info_t					*tmp_player_info = (cp_player_info_t *)(player->app_info);
	cp_device_info_t					*tmp_player_device_info = ((cp_player_info_t*)(player->app_info))->device_info;
	cp_return_info_t					ret;
	cp_char_t							buf[CP_APP_DEFAULT_BUFFER_LENGTH] = { 0, };




	//��֯�ظ�����ͷ
	if (ret_semh.command > 0 && !(ret_semh.command % 2)) {
		ret_semh.command += 1;
	}
	else{
		cp_log_error(tmp_player->logger, "send semh response data error. command [%d] error.", ret_semh.command);

		return cp_false;
	}

	ret_semh.packet_no += 1;
	ret_semh.status = status;

	cp_strcpy(ret.host_id, tmp_player_device_info->host.id);
	cp_strcpy(ret.reason, reason);
	ret.status = status;

	//ת���ʹ���gmf����
	if (src_gmf) {
		gmp_gmf_encode(src_gmf, &iob, CP_NULL, 0);
		if (iob) {
			len = *(iob->len);
			p = iob->data;

			if (!gmp_gmf_printf(src_gmf, &gmp_str, CP_NULL, 0, gmp_print_style_pretty)) {
				gmp_str = CP_NULL;
			}
		}
		else{
			cp_log_error(tmp_player->logger, "send semh response data error. gmp_gmf_encode() error.");
		}
	}
	else{
		ret_semh.status = CSS_ERROR_STATUS_400;
	}

	//����semh��Ϣͷ
	ret_semh.length = len;

	cp_buf_create(gmf_data, (len + sizeof(gmp_gmph_semh_t)));

	cp_buf_strcat(gmf_data, &ret_semh, sizeof(gmp_gmph_semh_t));

	cp_buf_strcat(gmf_data, p, len);

	cp_write_socket(s, gmf_data, len, remote_addr, 0);

	return cp_true;
}

cp_bool_t send_semh_response(cp_player_t *player, cp_socket_t *s, const cp_sockaddr_in *remote_addr,
	gmp_gmph_semh_t *semh, cp_int32_t status, cp_char_t *reason, cp_int32_t nreason)
{
	cp_int32_t							len = 0;
	cp_char_t							*p;
	gmp_gmf_t							*gmf;
	gmp_gmdu_t							*object_gmdu;
	gmp_gmph_semh_t						ret_semh = *semh;
	gmdt_string_p_t						*gmp_str = CP_NULL;
	gmdt_iobuffer_p_t					*iob = CP_NULL;
	cp_buf_t							*gmf_data = CP_NULL;
	cp_player_t							*tmp_player = player;
	cp_player_info_t					*tmp_player_info = (cp_player_info_t *)(player->app_info);
	cp_device_info_t					*tmp_player_device_info = ((cp_player_info_t*)(player->app_info))->device_info;
	cp_return_info_t					return_info = { 0, };
	cp_char_t							buf[CP_APP_DEFAULT_BUFFER_LENGTH] = { 0, };



	//��֯�ظ�����ͷ
	if (ret_semh.command > 0 && !(ret_semh.command % 2)) {
		ret_semh.command += 1;
	}
	else{
		cp_log_error(tmp_player->logger, "send semh response error. command [%d] error.", ret_semh.command);
		return cp_false;
	}

	ret_semh.packet_no += 1;
	ret_semh.status = status;

	cp_strcpy(return_info.host_id, tmp_player_device_info->host.id);
	cp_strcpy(return_info.reason, reason);
	return_info.status = status;

	gmf = gmp_create_gmf();
	if (!gmf) {
		cp_log_error(tmp_player->logger, "send semh response error. gmp_create_gmf() command [%d] error.", ret_semh.command);
		return cp_false;
	}

	object_gmdu = make_gmf_return(gmf, &return_info, buf, CP_APP_DEFAULT_BUFFER_LENGTH);
	if (!object_gmdu) {
		cp_log_error(tmp_player->logger, "send semh response error. make_gmf_return() command [%d] error. ", ret_semh.command);
		gmp_destroy_gmf(gmf);
		return cp_false;
	}

	//��return ��object�������gmf��
	gmp_add_gmdu(gmf, object_gmdu);

	//ת���ʹ���gmf����
	if (gmf) {
		gmp_gmf_encode(gmf, &iob, CP_NULL, 0);
		if (iob) {
			len = *(iob->len);
			p = iob->data;
			if (!gmp_gmf_printf(gmf, &gmp_str, CP_NULL, 0, gmp_print_style_pretty)) {
				gmp_str = CP_NULL;
			}
		}
		else{
			cp_log_error(tmp_player->logger, "send semh response error. gmp_gmf_encode() error.");
		}
	}
	else{
		ret_semh.status = CSS_ERROR_STATUS_400;
	}

	//����semh��Ϣͷ
	ret_semh.length = len;

	cp_buf_create(gmf_data, (len + sizeof(gmp_gmph_semh_t)));
	cp_buf_strcat(gmf_data, &ret_semh, sizeof(gmp_gmph_semh_t));
	cp_buf_strcat(gmf_data, p, len);

	cp_write_socket(s, gmf_data, len, remote_addr, 0);

	gmp_destroy_gmf(gmf);

	return cp_true;
}

cp_int32_t cp_list_find_device_info_by_type(list_node *device_node, void *type)
{
	cp_device_info_t *device_info = (cp_device_info_t *)device_node->data;

	if ((device_info->host.type) == *((unsigned char *)type)) {
		return 1;
	}

	return 0;
}

cp_int32_t cp_list_find_device_focus_by_id(list_node *focus_node, char *id)
{
	cp_focus_info_t *focus_info = (cp_focus_info_t *)focus_node->data;

	if (!cp_strcmp(focus_info->id, id)) {
		return 1;
	}

	return 0;
}

cp_int32_t	cp_update_host_info(cp_host_t *dest, cp_host_t *src)
{
	if (!dest || !src) {
		return -1;
	}

	cp_strncpy(dest->id, src->id, CP_APP_DEFAULT_ID_LENGTH);

	dest->group = src->group;
	dest->row = src->row;
	dest->column = src->column;
	dest->no = src->no;

	cp_memset(dest->number, 0, cp_sizeof(dest->number));
	cp_snprintf(dest->number, cp_sizeof(dest->number), "%02d-%02d-%02d", dest->group, dest->row, dest->column);

	return 0;
}

cp_int32_t	cp_save_host_info(cp_player_t *player, cp_host_t *src)
{
	cp_int32_t					ret_int = 0;



	//�����豸��Ϣ�������ļ�
	ret_int = cp_conf_setstring(player->conf, CP_PLAYER_CONF_STRING_OTHER, CP_PLAYER_CONF_STRING_NVG_ID, src->id);
	if (ret_int) {
		cp_app_log(error, player, "register_return error. conf set entry: "CP_PLAYER_CONF_STRING_OTHER":"CP_PLAYER_CONF_STRING_NVG_ID" string. error");
	}

	ret_int = cp_conf_setstring(player->conf, CP_PLAYER_CONF_STRING_OTHER, CP_PLAYER_CONF_STRING_NVG_POSTION, src->number);
	if (ret_int) {
		cp_app_log(error, player, "register_return error. conf set entry: "CP_PLAYER_CONF_STRING_OTHER":"CP_PLAYER_CONF_STRING_NVG_POSTION" string. error");
	}

	// 	ret_int = cp_conf_setstring(player->conf, CP_PLAYER_CONF_STRING_OTHER, CP_PLAYER_CONF_STRING_SN, src->sn);
	// 	if (ret_int) {
	// 		cp_app_log(error, player, "register_return error. conf set entry: "CP_PLAYER_CONF_STRING_OTHER":"CP_PLAYER_CONF_STRING_SN" string. error");
	// 	}

	cp_conf_dump_ini(player->conf, (cp_app_t*)player);
	return 0;
}
