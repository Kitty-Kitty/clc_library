/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-11-22

Description:

**************************************************************************/
#include "cp_uuid.h"
#include "cp_semh_make_gmf.h"


/******************************************************************************************************
* ��Ȩ����:thm & novigo
* ��������:make_semh_center_register
* ��    ��: ��������ע������
*
* ��    ��:
*			1��cp_player_t		*tmp_player			����ǰ������
* �� �� ֵ:
*			���سɹ����true��ʾ�ɹ�;false��ʾʧ��;
* ��    ע:
* ��    ��: thm
* ��������:tianhuiming@novigo.com.cn
* ��������:2016-4-27
******************************************************************************************************/
cp_int32_t make_semh_center_register(cp_player_t *player, cp_buf_t **gmf_data)
{
	gmp_gmf_t							*new_gmf = CP_NULL;
	gmp_gmdu_t							*object_gmdu = CP_NULL;
	cp_player_t							*tmp_player = player;
	cp_player_info_t					*tmp_player_info = (cp_player_info_t *)(player->app_info);
	cp_device_info_t					*tmp_player_device_info = ((cp_player_info_t*)(player->app_info))->device_info;
	cp_int32_t							gmf_data_len = 0;
	cp_char_t							buf[CP_APP_DEFAULT_BUFFER_LENGTH] = { 0, };



	new_gmf = gmp_create_gmf();
	if (!new_gmf) {
		cp_log_error(tmp_player->logger, "make semh center reigster error.gmp_create_gmf() error.");
		return -1;
	}

	//���ע����Ҫ�Ľڵ���Ϣ
	object_gmdu = make_gmf_register(new_gmf, tmp_player_device_info, buf, CP_APP_DEFAULT_BUFFER_LENGTH);
	if (!object_gmdu) {
		gmp_destroy_gmf(new_gmf);
		cp_log_error(tmp_player->logger, "make semh center reigster error.make_gmf_register() error. [%s]", buf);
		return -1;
	}
	gmp_add_gmdu(new_gmf, object_gmdu);

	gmf_data_len = make_semh_request_data(tmp_player, GMP_SEMH_CENTER_CMD_REGISTER, new_gmf, gmf_data);
	if (!(*gmf_data) || gmf_data_len <= 0) {
		cp_log_error(tmp_player->logger, "make semh center reigster error. make_semh_request_data() error.");
		return -1;
	}

	return gmf_data_len;
}

/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: make_semh_center_cancel_register
*
* ����˵��: ����ȡ��ע����Ϣ
*
* ��    ��: cp_player_t * player						[in]����˵��
* ��    ��: cp_buf_t * * gmf_data						[in]����˵��
*
* �� �� ֵ: cp_int32_t
*           0  : �ɹ�
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2016-11-22 11:37:30
******************************************************************************************************/
cp_int32_t make_semh_center_cancel_register(cp_player_t *player, cp_buf_t **gmf_data)
{
	gmp_gmf_t							*new_gmf = CP_NULL;
	gmp_gmdu_t							*object_gmdu = CP_NULL;
	gmp_gmdu_t							*host_gmdu = CP_NULL;
	cp_player_t							*tmp_player = player;
	cp_player_info_t					*tmp_player_info = (cp_player_info_t *)(player->app_info);
	cp_device_info_t					*tmp_player_device_info = ((cp_player_info_t*)(player->app_info))->device_info;
	cp_int32_t							gmf_data_len = 0;



	//����һ��gmf
	new_gmf = gmp_create_gmf();
	if (!new_gmf) {
		cp_log_error(player->logger, "make semh cancel register error. gmp_create_gmf() error");
		return -1;
	}

	object_gmdu = gmp_create_gmdu(new_gmf, "%T,%T", GMP_GMDT_O, GMP_GMDT_N);
	if (!object_gmdu) {
		gmp_destroy_gmf(new_gmf);
		cp_log_error(player->logger, "make semh cancel register error. gmp_create_gmdu() error.");
		return -1;
	}

	//���host�ڵ���Ϣ
	host_gmdu = make_gmf_host(new_gmf, &(tmp_player_device_info->host));
	if (!host_gmdu) {
		gmp_destroy_gmf(new_gmf);
		cp_log_error(player->logger, "make semh cancel register error. make_gmf_host() error.");
		return -1;
	}

	//��Object�ڵ������Host����
	gmp_add_gmdu_child_gmdu(new_gmf, object_gmdu, host_gmdu);

	//�����ڵ������Oject����
	gmp_add_gmdu(new_gmf, object_gmdu);

	gmf_data_len = make_semh_request_data(tmp_player, GMP_SEMH_CENTER_CMD_REGISTER, new_gmf, gmf_data);
	if (!(*gmf_data) || gmf_data_len <= 0) {
		cp_log_error(tmp_player->logger, "make semh cancel register error. make_semh_request_data() error.");
		return -1;
	}

	return gmf_data_len;
}

/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: make_device_semh_life_heart_data
*
* ����˵��: ��������ָ��
*
* ��    ��: cp_player_t * player						[in]����˵��
* ��    ��: cp_int32_t command						[in]����˵��
* ��    ��: cp_buf_t * out_buf						[in]����˵��
*
* �� �� ֵ: cp_int32_t
*           0  : �ɹ� 
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2017-04-30 16:15:20
******************************************************************************************************/
cp_int32_t make_device_semh_life_heart_data(cp_player_t *player, cp_int32_t command, cp_buf_t *out_buf)
{
	gmp_gmf_t							*new_gmf = CP_NULL;
	gmp_gmdu_t							*object_gmdu = CP_NULL;
	cp_player_t							*tmp_player = player;
	cp_player_info_t					*tmp_player_info = (cp_player_info_t *)(player->app_info);
	cp_device_info_t					*tmp_player_device_info = ((cp_player_info_t*)(player->app_info))->device_info;
	cp_int32_t							gmf_data_len = 0;
	cp_bool_t							ret_bool = cp_false;
	cp_int32_t							data_len = 0;
	cp_char_t							session_id[CP_APP_DEFAULT_SESSION_ID_LENGTH] = { 0, };
	cp_char_t							tmp_buf[CP_APP_DEFAULT_BUFFER_LENGTH] = { 0, };
	cp_void_t							*p = CP_NULL;
	gmdt_iobuffer_p_t					*iob = CP_NULL;
	gmdt_string_p_t						*gmp_str = CP_NULL;
	gmp_gmph_semh_t						semh = { 0, };



	if (!out_buf) {
		return -1;
	}

	//��֯������ͷ
	make_uuid_32(session_id, CP_APP_DEFAULT_SESSION_ID_LENGTH);

	make_semh_header(&semh, command, 0, 0, 0, session_id);

	new_gmf = gmp_create_gmf();
	if (!new_gmf) {
		cp_log_error(tmp_player->logger, "make semh center life heart error. gmp_create_gmf() error.");
		return -1;
	}

	//��������ڵ���Ϣ
	object_gmdu = make_gmf_life_heart(new_gmf, tmp_player_device_info, tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH);
	if (!object_gmdu) {
		gmp_destroy_gmf(new_gmf);
		cp_log_error(tmp_player->logger, "make semh center life heart error. make_gmf_life_heart() error. [%s]", tmp_buf);
		return -1;
	}
	gmp_add_gmdu(new_gmf, object_gmdu);

	gmp_gmf_encode(new_gmf, &iob, CP_NULL, 0);
	if (iob) {
		data_len = *(iob->len);
		p = iob->data;

		if (!gmp_gmf_printf(new_gmf, &gmp_str, NULL, 0, gmp_print_style_pretty)) {
			gmp_str = CP_NULL;
		}
		else {
			cp_log_info(tmp_player->logger, 
				"%s %s", 
				print_gmph_emh(&semh, tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH, cp_true),
				gmp_str->data);
		}
	}
	else{
		gmp_destroy_gmf(new_gmf);
		cp_log_error(tmp_player->logger, "make semh request data error! reason gmp_gmf_encode() error.");
		return -1;
	}

	//����semh��Ϣͷ
	semh.length = data_len;
	gmf_data_len = data_len + cp_sizeof(gmp_gmph_semh_t);

	if (gmf_data_len > cp_buf_get_free_size(out_buf)) {
		gmp_destroy_gmf(new_gmf);
		cp_log_error(tmp_player->logger,
			"make_gmf_life_heart() error. gmf data length[%s] more than buffer[%d]",
			gmf_data_len,
			cp_buf_get_free_size(out_buf));
		return -2;
	}

	cp_buf_strcat(out_buf, &semh, sizeof(gmp_gmph_semh_t));
	cp_buf_strcat(out_buf, p, data_len);

	gmp_destroy_gmf(new_gmf);

	return 0;
}

/******************************************************************************************************
* ��Ȩ����:thm & novigo
* ��������:make_semh_center_exception
* ��    ��:�쳣�ϱ��ӿ�
*
* ��    ��:
*			1��cp_player_t			*tmp_player			����ǰ������
*			2��cp_exception_info_t *ex_info			�쳣��Ϣ
*			3��cp_char_t			*remote_addr	Զ��IP��ַ
*			4��cp_int32_t			port			Զ�˶˿�
* �� �� ֵ:
*			���سɹ����true��ʾ�ɹ�;false��ʾʧ��;
* ��    ע:
* ��    ��: thm
* ��������:tianhuiming@novigo.com.cn
* ��������:2016-4-27
******************************************************************************************************/
cp_int32_t make_semh_center_exception(cp_player_t *player, cp_buf_t **gmf_data, cp_exception_info_t *exp_info)
{
	gmp_gmf_t							*new_gmf = CP_NULL;
	gmp_gmdu_t							*object_gmdu = CP_NULL;
	cp_player_t							*tmp_player = player;
	cp_player_info_t					*tmp_player_info = (cp_player_info_t *)(player->app_info);
	cp_device_info_t					*tmp_player_device_info = ((cp_player_info_t*)(player->app_info))->device_info;
	cp_int32_t							gmf_data_len = 0;
	cp_char_t							buf[CP_APP_DEFAULT_BUFFER_LENGTH] = { 0, };



	new_gmf = gmp_create_gmf();
	if (!new_gmf) {
		cp_log_error(tmp_player->logger, "make semh center exception error.gmp_create_gmf() error");
		return -1;
	}

	//��������ڵ���Ϣ
	object_gmdu = make_gmf_exceptions(new_gmf, tmp_player_device_info, exp_info, buf, CP_APP_DEFAULT_BUFFER_LENGTH);
	if (!object_gmdu) {
		gmp_destroy_gmf(new_gmf);
		cp_log_error(tmp_player->logger, "make semh center exception error. make_gmf_exceptions() error. [%s]", buf);
		return -1;
	}

	gmp_add_gmdu(new_gmf, object_gmdu);

	gmf_data_len = make_semh_request_data(tmp_player, GMP_SEMH_CENTER_CMD_EXCEPTION, new_gmf, gmf_data);
	if (!(*gmf_data) || gmf_data_len <= 0) {
		cp_log_error(tmp_player->logger, "make semh center exception error. make_semh_request_data() error.");
		return -1;
	}

	return gmf_data_len;
}

/******************************************************************************************************
* ��Ȩ����:thm & novigo
* ��������:make_semh_request_data
* ��    ��:����ָ������Զ��
*
* ��    ��:
*			1��cp_player_t		*tmp_player			 ����ǰ������
*			2��cp_int32_t		cmd				 ָ�����
*			3��gmp_gmf_t		*src_gmf	     gmfָ����Ϣ��
* �� �� ֵ:
*			���سɹ����true��ʾ�ɹ�;false��ʾʧ��;
* ��    ע:
* ��    ��: thm
* ��������:tianhuiming@novigo.com.cn
* ��������:2016-4-27
******************************************************************************************************/
cp_int32_t make_semh_request_data(cp_player_t *player, cp_int32_t command, gmp_gmf_t *src_gmf, cp_buf_t **gmf_data)
{
	cp_bool_t							ret_bool = cp_false;
	cp_int32_t							data_len;
	cp_int32_t							gmf_data_len;
	cp_char_t							*p = CP_NULL;
	cp_char_t							session_id[CP_APP_DEFAULT_SESSION_ID_LENGTH] = { 0, };
	cp_player_t							*tmp_player = player;
	gmdt_iobuffer_p_t					*iob = CP_NULL;
	gmdt_string_p_t						*gmp_str = CP_NULL;
	gmp_gmph_semh_t						semh;



	//��֯������ͷ
	make_uuid_32(session_id, CP_APP_DEFAULT_SESSION_ID_LENGTH);

	make_semh_header(&semh, command, 0, 0, 0, session_id);

	//ת���ʹ���gmf����
	if (src_gmf) {
		gmp_gmf_encode(src_gmf, &iob, CP_NULL, 0);
		if (iob) {
			data_len = *(iob->len);
			p = iob->data;

			if (!gmp_gmf_printf(src_gmf, &gmp_str, NULL, 0, gmp_print_style_pretty)) {
				gmp_str = CP_NULL;
			}
			else {
				cp_log_info(tmp_player->logger, "gmf:%s", gmp_str->data);
			}
		}
		else{
			cp_log_error(tmp_player->logger, "make semh request data error! reason gmp_gmf_encode() error.");
		}
	}
	else{
		semh.status = CSS_ERROR_STATUS_400;
	}

	//����semh��Ϣͷ
	semh.length = data_len;

	gmf_data_len = data_len + sizeof(gmp_gmph_semh_t);

	cp_buf_create((*gmf_data), (data_len + sizeof(gmp_gmph_semh_t)));

	cp_buf_strcat((*gmf_data), &semh, sizeof(gmp_gmph_semh_t));

	cp_buf_strcat((*gmf_data), p, data_len);

	return gmf_data_len;
}

/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: make_semh_get_audio_channel_info
*
* ����˵��: ������ȡ��Ƶͨ��������
*
* ��    ��: cp_player_t * player						[in]����˵��
* ��    ��: cp_play_channel_info_t * cp_info						[in]����˵��
* ��    ��: cp_buf_t * * gmf_data						[in]����˵��
*
* �� �� ֵ: cp_int32_t
*           0  : �ɹ�
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2016-12-15 14:42:23
******************************************************************************************************/
cp_int32_t make_semh_get_audio_channel_info(cp_player_t *player, cp_play_channel_info_t *cp_info, cp_buf_t **gmf_data)
{
	gmp_gmf_t							*new_gmf = CP_NULL;
	gmp_gmdu_t							*object_gmdu = CP_NULL;
	cp_player_t							*tmp_player = player;
	cp_player_info_t					*tmp_player_info = (cp_player_info_t *)(player->app_info);
	cp_device_info_t					*tmp_player_device_info = ((cp_player_info_t*)(player->app_info))->device_info;
	cp_int32_t							gmf_data_len = 0;
	cp_char_t							buf[CP_APP_DEFAULT_BUFFER_LENGTH] = { 0, };


#if 0

	new_gmf = gmp_create_gmf();
	if (!new_gmf) {
		cp_log_error(tmp_player->logger, "make semh center exception error.gmp_create_gmf() error");
		return -1;
	}

	//��������ڵ���Ϣ
	object_gmdu = make_gmf_exceptions(new_gmf, tmp_player_device_info, exp_info, buf, CP_APP_DEFAULT_BUFFER_LENGTH);
	if (!object_gmdu) {
		gmp_destroy_gmf(new_gmf);
		cp_log_error(tmp_player->logger, "make semh center exception error. make_gmf_exceptions() error. [%s]", buf);
		return -1;
	}

	gmp_add_gmdu(new_gmf, object_gmdu);

	gmf_data_len = make_semh_request_data(tmp_player, GMP_SEMH_CENTER_CMD_EXCEPTION, new_gmf, gmf_data);
	if (!(*gmf_data) || gmf_data_len <= 0) {
		cp_log_error(tmp_player->logger, "make semh center exception error. make_semh_request_data() error.");
		return -1;
	}

#endif
	return gmf_data_len;

}