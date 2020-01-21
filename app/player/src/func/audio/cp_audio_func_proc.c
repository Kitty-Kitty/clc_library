/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2017-01-12

Description:

**************************************************************************/
#include "cp_audio_func_proc.h"
#include "cp_player_codec_core.h"
#include "cp_player_dev_core.h"





cp_int32_t audio_func_data_integrity
(cp_socket_t *socket, const cp_buf_t *buf, cp_int32_t nread, cp_int32_t status)
{
	gmp_gmph_bmh_t						*tmp_bmh = CP_NULL;
	gmp_gmph_semh_t						*tmp_semh = CP_NULL;
	cp_session_t						*tmp_session = CP_NULL;
	cp_buf_t							*tmp_buf = (cp_buf_t*)buf;


	//Э��ͷ��û����ȫ
	if (cp_buf_get_length(tmp_buf) < CSS_GMP_GMPH_SEMH_LEN) {
		return cp_func_status_read_again;
	}
	//��������û������
	tmp_bmh = (gmp_gmph_bmh_t*)cp_buf_get_pos(tmp_buf);
	if (gmp_gmph_emh_type_semh == tmp_bmh->emht) {
		tmp_semh = (gmp_gmph_semh_t*)tmp_bmh;
		if (cp_buf_get_length(tmp_buf) < (cp_int32_t)(tmp_semh->length + CSS_GMP_GMPH_SEMH_LEN)) {
			return cp_func_status_match | cp_func_status_read_again;
		}
		//�����ɹ�����
		return cp_func_status_match | cp_func_status_successorerror;
	}
	return 0;
}

cp_int32_t audio_func_process_socket_data(cp_socket_t *socket, const cp_buf_t *buf, cp_int32_t nread, cp_int32_t status)
{
	cp_session_t				*tmp_session;
	cp_session_manager_t		*tmp_sm = CP_NULL;
	cp_session_info_t			tmp_session_info = { 0, };
	cp_module_manager_info_t	tmp_mm_info = { 0, };
	cp_int32_t					ret_int = 0;



	//�ж������Ƿ������ȫ
	ret_int = audio_func_data_integrity(socket, buf, nread, status);
	if ((ret_int & cp_func_status_match) && (ret_int & cp_func_status_successorerror)) {
		//�Ȼ�ȡsession manager ������
		tmp_mm_info.type = CP_MODULE_MANAGER_TYPE_SESSION(1);
		tmp_sm = (cp_session_manager_t*)cp_get_manager(socket->manager->app, &tmp_mm_info);
		if (!tmp_sm) {
			return cp_func_status_match;
		}

		//����һ��session��������
		CP_MODULE_INFO_SET_TYPE(&tmp_session_info, CP_MODULE_TYPE_SESSION(1));
		tmp_session = (cp_session_t*)cp_manager_create_module(tmp_sm, &tmp_session_info);
		if (tmp_session) {
			ret_int = cp_init_module(tmp_session, &tmp_session_info);
			if (!ret_int) {
				CP_SESSION_SET_SOCKET_INFO(tmp_session, socket, buf, nread, status);
				//��ʼ����ҵ����
				ret_int = cp_open_module(tmp_session, &tmp_session_info);
				if (!ret_int) {
					cp_manager_destroy_module(tmp_session->manager, tmp_session);
					return cp_func_status_match | cp_func_status_successorerror;
				}
			}
			cp_manager_destroy_module(tmp_session->manager, tmp_session);
		}
	}
	return cp_func_status_match;
}

/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: set_audio_multicast_data_filter
*
* ����˵��: ����multicast socket
*
* ��    ��: cp_audio_func_t * audio_func			[in]����˵��
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
cp_int32_t set_audio_multicast_data_filter(cp_audio_func_t *audio_func, cp_char_t *buf, cp_int32_t len)
{
	cp_module_t								*tmp_module = CP_NULL;
	cp_int32_t								ret_int = 0;
	cp_char_t								tmp_buf[CP_APP_DEFAULT_BUFFER_LENGTH] = { 0, };



	cp_memset(buf, 0, len);

	tmp_module = cp_manager_get_sub_module(audio_func->manager->app,
		cp_player_manager_type_filter, cp_player_module_type_memh_filter);
	if (!tmp_module) {
		cp_snprintf(buf, len, "not found filter[memh]");
		return -1;
	}
	audio_func->filter = (cp_filter_t *)tmp_module;
	CP_MODULE_UPDATE_SINGLE_HANDLER_AND_TYPE(audio_func->filter, audio_func->socket, read_cb, cp_socket_read_cb_handle);

	ret_int = set_audio_memh_socket_data(audio_func, tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH);
	if (ret_int) {
		cp_snprintf(buf, len, "%s", tmp_buf);
		return -2;
	}

	return 0;
}

/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: close_audio_multicast_socket
*
* ����˵��: �ر��鲥
*
* ��    ��: cp_audio_func_t * audio_func						[in]����˵��
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
cp_int32_t close_audio_multicast_socket(cp_audio_func_t *audio_func)
{
	if (audio_func->socket) {
		cp_close_socket(audio_func->socket);
		unset_audio_memh_socket_data(audio_func);
		cp_destroy_module(audio_func->socket->manager, audio_func->socket);
	}
	return 0;
}

/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: set_audio_memh_socket_data
*
* ����˵��: ����memh socket����
*
* ��    ��: cp_audio_func_t * audio_func						[in]����˵��
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
* �������ڣ�2016-12-14 16:34:00
******************************************************************************************************/
cp_int32_t set_audio_memh_socket_data(cp_audio_func_t *audio_func, cp_char_t *buf, cp_int32_t len)
{
	cp_memh_socket_data_t				*tmp_memh_socket_data = CP_NULL;



	if (!audio_func || !audio_func->socket) {
		cp_module_log(error, audio_func, "set_audio_memh_socket_data() error. audio_func[%p] socket is null.",
			audio_func);
		return -1;
	}
	//�� memh socket ����
	tmp_memh_socket_data = create_memh_socket_data(audio_func->socket->pool);
	if (!tmp_memh_socket_data) {
		cp_module_log(error, audio_func, "set_audio_memh_socket_data() error. create_memh_socket_data() error.");
		return -2;
	}
	set_memh_socket_buffer_func(tmp_memh_socket_data, (cp_func_t*)audio_func);
	//����memh socket data
	audio_func->msd = tmp_memh_socket_data;
	audio_func->socket->data = tmp_memh_socket_data;

	return 0;
}

/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: unset_audio_memh_socket_data
*
* ����˵��: ����memh socket����
*
* ��    ��: cp_audio_func_t * audio_func						[in]����˵��
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
* �������ڣ�2016-12-14 16:33:54
******************************************************************************************************/
cp_int32_t unset_audio_memh_socket_data(cp_audio_func_t *audio_func)
{
	if (audio_func->socket->data) {
		destroy_socket_data(audio_func->socket->pool, audio_func->msd);
		audio_func->socket->data = CP_NULL;
		audio_func->msd = CP_NULL;
	}
	return 0;
}

/*�����������ݻص�������*/
cp_int32_t audio_func_codec_read_cb_handle(cp_audio_func_t *audio_func, cp_codec_callback_info_t *ccb_info_p, cp_media_packet_t *mp)
{
	cp_char_t				tmp_buf[CP_APP_DEFAULT_BUFFER_LENGTH] = { 0, };
	cp_char_t				tmp_media_info_buf[CP_FORMAT_DEFAULT_LONG_BUFFER_LENGTH] = { 0, };



	if (!audio_func) {
		return -1;
	}

	//cp_module_log(warn, audio_func, "decode_audio_end %s", format_audio_frame_timestamp(tmp_buf, cp_sizeof(tmp_buf)));

	//��ʼ��������
	if (!set_audio_dev_info(audio_func, (cp_audio_description_t *)mp->md_p)) {
		//������Ƶ����
		((cp_audio_description_t *)mp->md_p)->volume = audio_func->mci.media_info.audio_source.volume;

		cp_write_module(audio_func->dev, &mp, cp_sizeof(cp_media_packet_t**), 0);
	}
	else {
		//��ӡý����Ϣ
		cp_module_log(error, audio_func,
			"set_audio_dev_info() error. %s",
			format_media_channel_info(&audio_func->mci, tmp_media_info_buf, cp_sizeof(tmp_media_info_buf)));

		//�������codecʧ�������Ƴ�ָ��
		send_remove_module_message(audio_func);
	}

	return 0;
}

/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: audio_func_thread_cb_proc
*
* ����˵��: ý�崦���߳�
*
* ��    ��: cp_audio_func_t * audio_func						[in]����˵��
*
* �� �� ֵ: void
*           0  : �ɹ�
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2016-12-13 10:49:17
******************************************************************************************************/
void audio_func_thread_cb_proc(cp_audio_func_t *audio_func)
{
	cp_int32_t				ret_int = 0;
	cp_buf_t				*tmp_buf_array[CP_AUDIO_FUNC_MEDIA_ARRAY_SIZE] = { 0, };
	cp_array_t				tmp_array = { 0, };
	cp_media_packet_t		*tmp_mp = CP_NULL;
	cp_char_t				tmp_buf[CP_APP_DEFAULT_BUFFER_LENGTH] = { 0, };



	//��ʼ������
	cp_array_init(&tmp_array, tmp_buf_array, cp_sizeof(cp_buf_t*), CP_AUDIO_FUNC_MEDIA_ARRAY_SIZE);

	while (cp_true)
	{
		if (audio_func->mp_info.thread_status != cp_audio_func_thread_status_start) {
			break;
		}

		//��ȡend��־��һ֡����
		ret_int = get_a_audio_frame_data(audio_func, &tmp_array);
		if (ret_int) {
			cp_sleep_ns(0, CP_AUDIO_FUNC_PROC_MERGE_SLEEP_INTERVAL);
			continue;
		}

		//����ָ��
		set_audio_codec_info(audio_func, &tmp_array);
		tmp_mp = merge_audio_media_data(audio_func, &tmp_array);
		if (tmp_mp) {
#if defined(CP_AUDIO_FILE_DEBUG)
			if (audio_func->file) {
				fwrite(cp_buf_get_pos(&tmp_mp->buf[0]), 1, cp_buf_get_length(&tmp_mp->buf[0]), audio_func->file);
			}
#endif
			//cp_module_log(warn, audio_func, "merge_audio %s", format_audio_frame_timestamp(tmp_buf, cp_sizeof(tmp_buf)));
			ret_int = decode_audio_media_data(audio_func, tmp_mp);
			if (!ret_int) {
				//cp_module_log(warn, audio_func, "decode_audio %s", format_audio_frame_timestamp(tmp_buf, cp_sizeof(tmp_buf)));
				audio_func->mp_info.decode_mp->ts = tmp_mp->ts;
				play_audio_media_data(audio_func, audio_func->mp_info.decode_mp);
				//cp_module_log(warn, audio_func, "play_audio %s", format_audio_frame_timestamp(tmp_buf, cp_sizeof(tmp_buf)));
			}
		}
		//�������ݻ���
		destroy_audio_tmp_data(audio_func, &tmp_array);
		cp_array_clear(&tmp_array);
	}
}


// #include <crtdbg.h>

/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: audio_func_decode_thread_cb_proc
*
* ����˵��: �����߳�
*
* ��    ��: cp_audio_func_t * audio_func						[in]����˵��
*
* �� �� ֵ: void
*           0  : �ɹ�
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2017-01-12 15:41:26
******************************************************************************************************/
void audio_func_decode_thread_cb_proc(cp_audio_func_t *audio_func)
{
	cp_int32_t							ret_int = 0;
	cp_array_t							tmp_array = { 0, };
	cp_media_packet_t					*tmp_mp = CP_NULL;
	cp_char_t							tmp_buf[CP_APP_DEFAULT_BUFFER_LENGTH] = { 0, };
// 	_CrtMemState								s1, s2, s3;



	while (cp_audio_func_thread_status_start == audio_func->mp_info.thread_status)
	{
// 		_CrtMemCheckpoint(&s1);

		tmp_mp = cp_safe_queue_pop(audio_func->mp_info.merge_sq);
		if (!tmp_mp) {
			cp_sleep_ns(0, CP_AUDIO_FUNC_PROC_MERGE_SLEEP_INTERVAL);
			continue;
		}

#if defined(CP_AUDIO_FILE_DEBUG)
		if (audio_func->file) {
			fwrite(cp_buf_get_pos(&tmp_mp->buf[0]), 1, cp_buf_get_length(&tmp_mp->buf[0]), audio_func->file);
		}
#endif

		ret_int = decode_audio_media_data(audio_func, tmp_mp);
		if (!ret_int) {
			//cp_module_log(warn, audio_func, "decode_audio %s", format_audio_frame_timestamp(tmp_buf, cp_sizeof(tmp_buf)));
			audio_func->mp_info.decode_mp->ts = tmp_mp->ts;
			play_audio_media_data(audio_func, audio_func->mp_info.decode_mp);
			//cp_module_log(warn, audio_func, "play_audio %s", format_audio_frame_timestamp(tmp_buf, cp_sizeof(tmp_buf)));
		}

#if 0
		while (cp_true)
		{
			//cp_module_log(warn, audio_func, "merge_audio %s", format_audio_frame_timestamp(tmp_buf, cp_sizeof(tmp_buf)));
			ret_int = decode_audio_media_data(audio_func, tmp_mp);
			if (!ret_int) {
				//cp_module_log(warn, audio_func, "decode_audio %s", format_audio_frame_timestamp(tmp_buf, cp_sizeof(tmp_buf)));
				audio_func->mp_info.decode_mp->ts = tmp_mp->ts;
				play_audio_media_data(audio_func, audio_func->mp_info.decode_mp);
				//cp_module_log(warn, audio_func, "play_audio %s", format_audio_frame_timestamp(tmp_buf, cp_sizeof(tmp_buf)));
				continue;
			}
			break;
		}
#endif

		//����media packet
		destroy_a_audio_media_packet(audio_func, tmp_mp);

//  		_CrtMemCheckpoint(&s2);
//  		if (_CrtMemDifference(&s3, &s1, &s2)) {
//  			_CrtMemDumpStatistics(&s3);
// 			//cp_module_log(warn, audio_func, "audio_func_decode_thread_cb_proc() !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
//  		}
//  		else {
// 			//cp_module_log(warn, audio_func, "audio_func_decode_thread_cb_proc() ================================================");
//  		}

	}
}

/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: audio_func_merge_thread_cb_proc
*
* ����˵��: �����߳�
*
* ��    ��: cp_audio_func_t * audio_func						[in]����˵��
*
* �� �� ֵ: void
*           0  : �ɹ�
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2017-01-12 15:38:47
******************************************************************************************************/
void audio_func_merge_thread_cb_proc(cp_audio_func_t *audio_func)
{
	cp_int32_t				ret_int = 0;
	cp_int32_t				tmp_process_count = 0;
	cp_buf_t				*tmp_buf_array[CP_AUDIO_FUNC_MEDIA_ARRAY_SIZE] = { 0, };
	cp_array_t				tmp_array = { 0, };
	cp_media_packet_t		*tmp_mp = CP_NULL;
	cp_char_t				tmp_buf[CP_APP_DEFAULT_BUFFER_LENGTH] = { 0, };
	cp_char_t				tmp_media_info_buf[CP_FORMAT_DEFAULT_LONG_BUFFER_LENGTH] = { 0, };



	//��ʼ������
	cp_array_init(&tmp_array, tmp_buf_array, cp_sizeof(cp_buf_t*), CP_AUDIO_FUNC_MEDIA_ARRAY_SIZE);

	while (cp_audio_func_thread_status_start == audio_func->mp_info.thread_status)
	{
		//��ȡend��־��һ֡����
		ret_int = get_a_audio_frame_data(audio_func, &tmp_array);
		if (ret_int) {
			cp_sleep_ns(0, CP_AUDIO_FUNC_PROC_MERGE_SLEEP_INTERVAL);
			continue;
		}

		//����ָ��
		ret_int = set_audio_codec_info(audio_func, &tmp_array);
		if (ret_int) {
			//��ӡý����Ϣ
			cp_module_log(error, audio_func, 
				"set_audio_codec_info() error. %s",
				format_media_channel_info(&audio_func->mci, tmp_media_info_buf, cp_sizeof(tmp_media_info_buf)));

			//�������codecʧ�������Ƴ�ָ��
			send_remove_module_message(audio_func);
			break;
		}

 		tmp_mp = merge_audio_media_data(audio_func, &tmp_array);
 		if (tmp_mp) {
 			cp_safe_queue_push(audio_func->mp_info.merge_sq, tmp_mp);
 		}

		//�������ݻ���
		destroy_audio_tmp_data(audio_func, &tmp_array);
		cp_array_clear(&tmp_array);
	}
}

/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: check_audio_is_end
*
* ����˵��: У�������Ƿ����
*
* ��    ��: cp_buf_t * buf						[in]����˵��
*
* �� �� ֵ: cp_bool_t
*           0  : �ɹ�
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2016-12-06 10:26:11
******************************************************************************************************/
cp_bool_t check_audio_is_end(cp_buf_t *buf)
{
	gmp_gmph_memh_t						*tmp_memh = CP_NULL;


	//ȡ��semh��ͷ���ж�semh��С����
	tmp_memh = (gmp_gmph_memh_t*)cp_buf_get_pos(buf);
	if (gmp_gmph_emh_type_memh == tmp_memh->bmh.emht &&
		css_media_network_end == tmp_memh->packet_type) {
		return cp_true;
	}

	return cp_false;
}

/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: open_audio_test_file
*
* ����˵��: �򿪲����ļ�
*
* ��    ��: cp_audio_func_t * audio_func						[in]����˵��
*
* �� �� ֵ: cp_bool_t
*           0  : �ɹ�
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2016-12-16 14:05:17
******************************************************************************************************/
cp_bool_t open_audio_test_file(cp_audio_func_t *audio_func)
{
#if defined(CP_AUDIO_FILE_DEBUG)
	cp_char_t									tmp_buf[CP_APP_DEFAULT_BUFFER_LENGTH] = { 0, };


	cp_snprintf(tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH, "%s_%d_%s",
		audio_func->register_info.name,
		audio_func->mci.channel_info.index,
		audio_func->mci.media_info.id);

	audio_func->file = fopen(tmp_buf, "wb");
#endif



	return cp_true;
}

/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: close_audio_test_file
*
* ����˵��: �رղ����ļ�
*
* ��    ��: cp_audio_func_t * audio_func						[in]����˵��
*
* �� �� ֵ: cp_bool_t
*           0  : �ɹ�
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2016-12-16 15:16:02
******************************************************************************************************/
cp_bool_t close_audio_test_file(cp_audio_func_t *audio_func)
{
#if defined(CP_AUDIO_FILE_DEBUG)

	if (audio_func->file) {
		fclose(audio_func->file);
		audio_func->file = CP_NULL;
	}
#endif
	return cp_true;
}

//������Ҫ������Ƶ����ģ��
cp_module_t* create_audio_codec_module(cp_player_t *player, cp_media_description_t *md, cp_int32_t manager_type, cp_int32_t module_type)
{
	cp_module_t									*tmp_module = CP_NULL;
	cp_module_manager_t							*tmp_manager = CP_NULL;
	cp_module_manager_info_t					tmp_manager_info = { 0, };
	cp_codec_info_t								tmp_codec_info = { 0, };
	cp_int32_t									ret_int = 0;
	cp_char_t									tmp_buf[CP_APP_DEFAULT_BUFFER_LENGTH] = { 0, };



	CP_MODULE_MANAGER_INFO_SET_TYPE(&tmp_manager_info, manager_type);
	//��ȡ��Ƶ���������
	tmp_manager = cp_get_manager(player, &tmp_manager_info);
	if (!tmp_manager) {
		cp_app_log(error, player, "create_audio_codec_module() error. not found manager_type[%d] error.",
			manager_type);
		return CP_NULL;
	}
	//����һ������ģ��
	CP_MODULE_INFO_SET_TYPE(&tmp_codec_info, module_type);
	CP_CODEC_INFO_SET_MEDIA_DESCRIPTION(&tmp_codec_info, md);
	//�Ȳ���һ��ģ���Ƿ����
	tmp_module = cp_manager_get_module(tmp_manager, &tmp_codec_info);
	if (tmp_module) {
		cp_app_log(warn, player, "create_audio_codec_module() warning. create module_type[%d] existed.",
			module_type);
		return CP_NULL;
	}
	//��������ʼ����
	tmp_module = cp_manager_create_module(tmp_manager, &tmp_codec_info);
	if (!tmp_module) {
		cp_app_log(error, player, "create_audio_codec_module() error. create module_type[%d] error.",
			module_type);
		return CP_NULL;
	}
	//��ʼ��ģ��ʧ��
	ret_int = cp_init_module(tmp_module, &tmp_codec_info);
	if (ret_int) {
		//��ʼ��ʧ�ܣ�������ģ������
		cp_manager_destroy_module(tmp_manager, tmp_module);
		cp_app_log(error, player, "create_audio_codec_module() error. init %s error.",
			print_module_register_info(&tmp_module->register_info, tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH));
		return CP_NULL;
	}

	//����ģ��ʧ��
	ret_int = cp_open_module(tmp_module, &tmp_codec_info);
	if (ret_int) {
		//��ʼ��ʧ�ܣ�������ģ������
		cp_manager_destroy_module(tmp_manager, tmp_module);
		cp_app_log(error, player, "create_audio_codec_module() error. open %s error.",
			print_module_register_info(&tmp_module->register_info, tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH));
		return CP_NULL;
	}

	return tmp_module;
}

//������Ҫ������Ƶ����ģ��
cp_module_t* create_audio_dev_module(cp_player_t *player, cp_dev_description_t *dd,
	cp_media_description_t *md, cp_int32_t manager_type, cp_int32_t module_type)
{
	cp_module_t									*tmp_module = CP_NULL;
	cp_module_manager_t							*tmp_manager = CP_NULL;
	cp_module_manager_info_t					tmp_manager_info = { 0, };
	cp_dev_info_t								tmp_dev_info = { 0, };
	cp_int32_t									ret_int = 0;
	cp_char_t									tmp_buf[CP_APP_DEFAULT_BUFFER_LENGTH] = { 0, };



	CP_MODULE_MANAGER_INFO_SET_TYPE(&tmp_manager_info, manager_type);
	//��ȡ��Ƶ���������
	tmp_manager = cp_get_manager(player, &tmp_manager_info);
	if (!tmp_manager) {
		cp_app_log(error, player, "create_audio_dev_module() error. not found manager_type[%d] error.",
			manager_type);
		return CP_NULL;
	}
	//����һ������ģ��
	CP_MODULE_INFO_SET_TYPE(&tmp_dev_info, module_type);
	CP_DEV_INFO_SET_MEDIA_DESCRIPTION(&tmp_dev_info, dd);
	CP_CODEC_INFO_SET_MEDIA_DESCRIPTION(&tmp_dev_info, md);
	//�Ȳ���һ��ģ���Ƿ����
	tmp_module = cp_manager_get_module(tmp_manager, &tmp_dev_info);
	if (tmp_module) {
		cp_app_log(warn, player, "create_audio_dev_module() warning. create module_type[%d] existed.",
			module_type);
		return CP_NULL;
	}
	//��������ʼ����
	tmp_module = cp_manager_create_module(tmp_manager, &tmp_dev_info);
	if (!tmp_module) {
		cp_app_log(error, player, "create_audio_dev_module() error. create module_type[%d] error.",
			module_type);
		return CP_NULL;
	}
	//��ʼ��ģ��ʧ��
	ret_int = cp_init_module(tmp_module, &tmp_dev_info);
	if (ret_int) {
		//��ʼ��ʧ�ܣ�������ģ������
		cp_manager_destroy_module(tmp_manager, tmp_module);
		cp_app_log(error, player, "create_audio_dev_module() error. init %s error.",
			print_module_register_info(&tmp_module->register_info, tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH));
		return CP_NULL;
	}
	//����ģ��ʧ��
	ret_int = cp_open_module(tmp_module, &tmp_dev_info);
	if (ret_int) {
		//��ʼ��ʧ�ܣ�������ģ������
		cp_manager_destroy_module(tmp_manager, tmp_module);
		cp_app_log(error, player, "create_audio_dev_module() error. open %s error.",
			print_module_register_info(&tmp_module->register_info, tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH));
		return CP_NULL;
	}

	return tmp_module;
}

/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: set_audio_codec_info
*
* ����˵��: ���ý�������Ϣ
*
* ��    ��: cp_audio_func_t * audio_func						[in]����˵��
* ��    ��: cp_array_t * ary						[in]����˵��
*
* �� �� ֵ: cp_int32_t
*           0  : �ɹ�
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2016-12-13 11:19:33
******************************************************************************************************/
cp_int32_t set_audio_codec_info(cp_audio_func_t *audio_func, cp_array_t *ary)
{
	cp_int32_t							tmp_ret_int = 0;
	cp_uint32_t							i = 0;
	cp_buf_t							**tmp_buf = 0;
	gmp_gmph_bmh_t						*tmp_bmh = CP_NULL;
	gmp_gmph_memh_t						*tmp_memh = CP_NULL;
	cp_module_t							*tmp_codec_module = CP_NULL;



	if (!audio_func || !ary) {
		return -1;
	}

	if (audio_func->mp_info.is_open_codec) {
		return 0;
	}

	//count size
	for (i = 0; i < cp_array_max_size(ary); i++) {
		tmp_buf = (cp_buf_t**)cp_array_get(ary, i);
		if (!(*tmp_buf)) {
			break;
		}
		tmp_bmh = (gmp_gmph_bmh_t*)cp_buf_get_pos((*tmp_buf));
		tmp_memh = (gmp_gmph_memh_t*)tmp_bmh;
		if (gmp_gmph_emh_type_memh == tmp_bmh->emht) {
			if (!audio_func->mp_info.is_open_codec && !audio_func->codec &&
				(css_media_network_begin == tmp_memh->packet_type ||
				css_media_network_other == tmp_memh->packet_type ||
				css_media_network_end == tmp_memh->packet_type)) {

				//����ý����Ϣ
				if (!check_audio_media_type(audio_func, tmp_memh->media_type)) {
					cp_module_log(error, audio_func,
						"set_audio_codec_info() error. unsupport media_type[%d] error.",
						tmp_memh->media_type);
					break;
				}

				audio_func->decode_md.encodec_type = tmp_memh->media_type;

				//��ʼ��������
				tmp_codec_module = create_audio_codec_module((cp_player_t*)(audio_func->manager->app),
					(cp_media_description_t *)&audio_func->decode_md,
					cp_player_manager_type_codec, cp_player_module_type_ffmpeg_codec);
				if (!tmp_codec_module) {
					cp_module_log(error, audio_func,
						"set_audio_codec_info() error. create_audio_codec_module() error.");
					return -2;
				}

				audio_func->codec = (cp_codec_t *)tmp_codec_module;
				audio_func->mp_info.is_open_codec = cp_true;

				//������Ƶ�ز�����Ϣ
				tmp_ret_int = set_audio_codec_convert_info(audio_func);
				if (tmp_ret_int) {
					cp_destroy_module(tmp_codec_module->manager, tmp_codec_module);
					cp_module_log(error, audio_func,
						"set_audio_codec_info() error. set_audio_codec_convert_info() error.");
					return -3;
				}

				return 0;
			}
		}

		if (check_audio_is_end((*tmp_buf))) {
			break;
		}
	}

	return 0;
}

/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: set_audio_codec_convert_info
*
* ����˵��: ������Ƶ�ز�����Ϣ
*
* ��    ��: cp_audio_func_t * audio_func						[in]����˵��
*
* �� �� ֵ: cp_int32_t
*           0  : �ɹ�
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2016-12-20 16:06:41
******************************************************************************************************/
cp_int32_t set_audio_codec_convert_info(cp_audio_func_t *audio_func)
{
	cp_int32_t										tmp_ret_int = 0;
	cp_audio_description_t							tmp_ad = { 0, };



	if (audio_func->afc.convert_flag) {
		tmp_ad.type = cp_media_description_type_audio;
		tmp_ad.channel_layout = audio_func->afc.channel_layout;
		tmp_ad.sample_rate = audio_func->afc.sample_rate;
		tmp_ad.sample_format = audio_func->afc.sample_format;
		tmp_ad.samples = audio_func->afc.samples;

		tmp_ret_int = cp_set_option_module(audio_func->codec, cp_player_codec_set_option_audio_convert_info, &tmp_ad);
		if (tmp_ret_int) {
			cp_module_log(error, audio_func, "set_audio_codec_convert_info() error. set_option_audio_convert_info() error.");
		}

		tmp_ret_int = cp_set_option_module(audio_func->codec, cp_player_codec_set_option_codec_is_used_probe, &(audio_func->afc.is_used_probe));
		if (tmp_ret_int) {
			cp_module_log(error, audio_func, "set_audio_codec_convert_info() error. set_option_codec_is_used_probe() error.");
		}

		return tmp_ret_int;
	}

	return 0;
}

/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: check_audio_media_type
*
* ����˵��: ��ʵý����Ϣ
*
* ��    ��: cp_audio_func_t * audio_func						[in]����˵��
* ��    ��: cp_int32_t type						[in]����˵��
*
* �� �� ֵ: cp_bool_t
*           0  : �ɹ�
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2016-12-16 10:53:22
******************************************************************************************************/
cp_bool_t check_audio_media_type(cp_audio_func_t *audio_func, cp_int32_t type)
{
	if (cp_media_type_audio_begin < type &&
		type < cp_media_type_audio_end) {
		return cp_true;
	}
	return cp_false;
}

/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: unset_audio_codec_info
*
* ����˵��: �ر���Ƶ��������Ϣ
*
* ��    ��: cp_audio_func_t * audio_func						[in]����˵��
*
* �� �� ֵ: cp_int32_t
*           0  : �ɹ�
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2016-12-14 15:14:08
******************************************************************************************************/
cp_int32_t close_audio_codec_info(cp_audio_func_t *audio_func)
{
	if (audio_func->mp_info.is_open_codec && audio_func->codec) {
		//�رս�����
		cp_close_module(audio_func->codec);
	}

	return 0;
}

/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: unset_audio_codec_info
*
* ����˵��: ������Ƶ��������Ϣ
*
* ��    ��: cp_audio_func_t * audio_func						[in]����˵��
*
* �� �� ֵ: cp_int32_t
*           0  : �ɹ�
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2016-12-14 15:14:08
******************************************************************************************************/
cp_int32_t unset_audio_codec_info(cp_audio_func_t *audio_func)
{
	if (audio_func->mp_info.is_open_codec && audio_func->codec) {
		//�رս�����
		cp_exit_module(audio_func->codec);
		//���ٽ�����
		cp_destroy_module(audio_func->codec->manager, audio_func->codec);
		//���ý���״̬
		audio_func->mp_info.is_open_codec = cp_true;
		audio_func->codec = CP_NULL;
	}

	return 0;
}

//���ò�����Ϣ
cp_int32_t set_audio_dev_info(cp_audio_func_t *audio_func, cp_audio_description_t *ad)
{
	cp_int32_t									tmp_ret_int = 0;
	cp_module_t									*tmp_dev_module = CP_NULL;
	cp_player_info_t							*tmp_player_info = (cp_player_info_t *)(audio_func->manager->app->app_info);
	cp_dev_audio_description_t					tmp_vdd = { 0, };



	if (!audio_func || !ad) {
		return -1;
	}

	if (audio_func->dev) {
		return 0;
	}

	//��ʼ��������
	tmp_vdd.dd.type = cp_dev_description_type_audio;
	tmp_vdd.volume = audio_func->mci.media_info.audio_source.volume;
	tmp_vdd.channel_layout = ad->channel_layout;
	tmp_vdd.sample_rate = ad->sample_rate;
	tmp_vdd.sample_format = ad->sample_format;
	tmp_vdd.samples = ad->samples;
	tmp_vdd.channels = ad->channels;
	tmp_dev_module = create_audio_dev_module((cp_player_t*)(audio_func->manager->app),
		(cp_dev_description_t *)&tmp_vdd,
		(cp_media_description_t *)ad,
		cp_player_manager_type_dev, cp_player_module_type_sdl_dev);
	if (!tmp_dev_module) {
		cp_module_log(error, audio_func, "set_audio_dev_info() error. create_audio_codec_module() error.");
		return -2;
	}
	audio_func->dev = (cp_dev_t *)tmp_dev_module;

	//���û�������
	if (audio_func->afc.buffer_size > 0) {
		tmp_ret_int = cp_set_option_module(tmp_dev_module,
			cp_player_dev_set_option_audio_buffer_size,
			&(audio_func->afc.buffer_size));
		if (tmp_ret_int) {
			cp_module_log(error, audio_func,
				"set_audio_dev_info() error. set option buffer_size[%d].",
				audio_func->afc.buffer_size);
			return tmp_ret_int;
		}
		else {
			cp_module_log(notice, audio_func,
				"set_audio_dev_info() success. set option buffer_size[%d].",
				audio_func->afc.buffer_size);
		}
	}

	//������ʱʱ��
	if (audio_func->afc.play_delay_ns > 0) {
		tmp_ret_int = cp_set_option_module(tmp_dev_module,
			cp_player_dev_set_option_audio_delay,
			&(audio_func->afc.play_delay_ns));
		if (tmp_ret_int) {
			cp_module_log(error, audio_func,
				"set_audio_dev_info() error. set option play_delay[%lld ns].",
				audio_func->afc.play_delay_ns);
			return tmp_ret_int;
		}
		else {
			cp_module_log(notice, audio_func,
				"set_audio_dev_info() success. set option play_delay[%lld ns].",
				audio_func->afc.play_delay_ns);
		}
	}

	//������ʱʱ��
	if (audio_func->afc.play_delay_sample_number > 0) {
		tmp_ret_int = cp_set_option_module(tmp_dev_module,
			cp_player_dev_set_option_audio_delay_sample_number,
			&(audio_func->afc.play_delay_sample_number));
		if (tmp_ret_int) {
			cp_module_log(error, audio_func,
				"set_audio_dev_info() error. set option play_delay_sample_number[%d].",
				audio_func->afc.play_delay_sample_number);
			return tmp_ret_int;
		}
		else {
			cp_module_log(notice, audio_func,
				"set_audio_dev_info() success. set option play_delay_sample_number[%d].",
				audio_func->afc.play_delay_sample_number);
		}
	}

	return 0;
}

/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: unset_audio_dev_info
*
* ����˵��: ������Ƶ������Ϣ
*
* ��    ��: cp_audio_func_t * audio_func						[in]����˵��
* ��    ��: cp_audio_description_t * ad						[in]����˵��
*
* �� �� ֵ: cp_int32_t
*           0  : �ɹ�
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2016-12-14 16:08:24
******************************************************************************************************/
cp_int32_t unset_audio_dev_info(cp_audio_func_t *audio_func)
{
	if (audio_func->dev) {
		//�رղ�����
		cp_close_module(audio_func->dev);
		//���ٲ�����
		cp_destroy_module(audio_func->dev->manager, audio_func->dev);
		//���ò���״̬
		audio_func->dev = CP_NULL;
	}
	return 0;
}

/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: merge_audio_media_data
*
* ����˵��: ����ý������
*
* ��    ��: cp_audio_func_t * audio_func						[in]����˵��
* ��    ��: cp_array_t * ary						[in]����˵��
*
* �� �� ֵ: cp_media_packet_t*
*           0  : �ɹ�
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2016-12-13 10:52:45
******************************************************************************************************/
cp_media_packet_t* merge_audio_media_data(cp_audio_func_t *audio_func, cp_array_t *ary)
{
	cp_uint32_t							i = 0;
	cp_int32_t							tmp_total = 0;
	cp_buf_t							**tmp_buf = 0;
	gmp_gmph_bmh_t						*tmp_bmh = CP_NULL;
	gmp_gmph_memh_t						*tmp_memh = CP_NULL;
	cp_media_packet_t					*tmp_mp = CP_NULL;
	cp_timespec_t						tmp_ts = { 0, };



	//count size
	for (i = 0; i < cp_array_max_size(ary); i++) {
		tmp_buf = (cp_buf_t**)cp_array_get(ary, i);
		if (!(*tmp_buf)) {
			break;
		}
		tmp_bmh = (gmp_gmph_bmh_t*)cp_buf_get_pos((*tmp_buf));
		tmp_memh = (gmp_gmph_memh_t*)tmp_bmh;
		if (gmp_gmph_emh_type_memh == tmp_bmh->emht) {
			tmp_total += tmp_memh->body_size;
		}

		if (check_audio_is_end((*tmp_buf))) {
			break;
		}
	}

	if (tmp_total <= 0) {
		return CP_NULL;
	}

	//����ҵ�����󴴽�media packet
	tmp_mp = create_a_audio_media_packet(audio_func, tmp_total);
	if (!tmp_mp) {
		return CP_NULL;
	}

	//copy data
	for (i = 0; i < cp_array_max_size(ary); i++) {
		tmp_buf = (cp_buf_t**)cp_array_get(ary, i);
		if (!(*tmp_buf)) {
			break;
		}
		tmp_bmh = (gmp_gmph_bmh_t*)cp_buf_get_pos((*tmp_buf));
		tmp_memh = (gmp_gmph_memh_t*)tmp_bmh;
		if (gmp_gmph_emh_type_memh == tmp_bmh->emht) {
			cp_buf_strcat(&tmp_mp->mp_buf.buf[0], cp_buf_get_pos((*tmp_buf)) + cp_sizeof(gmp_gmph_memh_t), (cp_int32_t)tmp_memh->body_size);

			//�����ȡʱ��
			if ((css_media_network_begin == tmp_memh->packet_type ||
				css_media_network_other == tmp_memh->packet_type ||
				css_media_network_end == tmp_memh->packet_type)) {
				tmp_ts.tv_sec = tmp_memh->time_stamp_s;
				tmp_ts.tv_nsec = tmp_memh->time_stamp_ns;
			}
		}

		if (check_audio_is_end((*tmp_buf))) {
			break;
		}
	}

	tmp_mp->ts = tmp_ts;
	return tmp_mp;
}

/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: get_a_audio_frame_data
*
* ����˵��: ���������Ĺ�����Ϣ
*
* ��    ��: cp_audio_func_t * audio_func						[in]����˵��
* ��    ��: cp_array_t * ary						[in]����˵��
*
* �� �� ֵ: cp_int32_t
*           0  : �ɹ�
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2016-12-13 10:28:37
******************************************************************************************************/
cp_int32_t get_a_audio_frame_data(cp_audio_func_t *audio_func, cp_array_t *ary)
{
	cp_buf_t				*tmp_buf = CP_NULL;


	while (cp_true)
	{
		//�����ȡ���ݾ�
		tmp_buf = pop_a_memh_socket_buffer(audio_func->msd);
		if (!tmp_buf) {
			break;
		}

		cp_array_set_back(ary, &tmp_buf);
		if (check_audio_is_end(tmp_buf)) {
			return 0;
		}
	}
	return -1;
}

/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: decode_audio_media_data
*
* ����˵��: ����ý������
*
* ��    ��: cp_audio_func_t * audio_func						[in]����˵��
* ��    ��: cp_media_packet_t * mp						[in]����˵��
*
* �� �� ֵ: cp_int32_t
*           0  : �ɹ�
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2016-12-06 10:14:20
******************************************************************************************************/
cp_int32_t decode_audio_media_data(cp_audio_func_t *audio_func, cp_media_packet_t	*mp)
{
	if (!audio_func || !mp || !audio_func->codec) {
		return -1;
	}

	return cp_write_module(audio_func->codec, &mp, cp_sizeof(cp_media_packet_t**), 0);
}

/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: play_audio_media_data
*
* ����˵��: ����ý��
*
* ��    ��: cp_audio_func_t * audio_func						[in]����˵��
* ��    ��: cp_media_packet_t * mp						[in]����˵��
*
* �� �� ֵ: cp_int32_t
*           0  : �ɹ�
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2016-12-13 10:13:34
******************************************************************************************************/
cp_int32_t play_audio_media_data(cp_audio_func_t *audio_func, cp_media_packet_t *mp)
{
	cp_int32_t								tmp_ret_int = 0;



	if (!audio_func || !mp) {
		return -1;
	}

	//��ȡ����������
	mp->md_p = (cp_media_description_t *)&audio_func->decode_md;
	mp->type = cp_media_packet_type_data_and_timestamp;
	tmp_ret_int = cp_read_module(audio_func->codec, &mp, cp_sizeof(cp_media_packet_t**), 0);
	if (!tmp_ret_int) {
		return -2;
	}
	return 0;
}

/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: stop_audio_func_media_play
*
* ����˵��: ֹͣһ��ý�岥��
*
* ��    ��: cp_audio_func_t * audio_func						[in]����˵��
* ��    ��: cp_media_channel_info_t * mci						[in]����˵��
*
* �� �� ֵ: cp_int32_t
*           0  : �ɹ�
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2016-12-13 15:01:08
******************************************************************************************************/
cp_int32_t stop_audio_func_media_play(cp_audio_func_t *audio_func, cp_media_channel_info_t *mci)
{
	cp_int32_t							tmp_ret_int = 0;



	if (!audio_func || !mci) {
		return -1;
	}

	//�������ͨ����ʹ���򷵻�
	if (audio_func->cm.size > 0) {
		return 0;
	}

	//���û����ֹͣ
	cp_close_module(audio_func);

	//����ģ��
	cp_destroy_module(audio_func->manager, audio_func);

	return 0;
}

/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: insert_audio_media_channel_info
*
* ����˵��: ���ý��ͨ��
*
* ��    ��: cp_audio_func_t * audio_func						[in]����˵��
* ��    ��: cp_media_channel_info_t * mci						[in]����˵��
*
* �� �� ֵ: cp_int32_t
*           0  : �ɹ�
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2016-12-14 11:24:52
******************************************************************************************************/
cp_int32_t insert_audio_media_channel_info(cp_audio_func_t *audio_func, cp_media_channel_info_t *mci)
{
	cp_channel_info_t					*tmp_chl_info = CP_NULL;
	cp_channel_t						*tmp_find_chl = CP_NULL;
	cp_channel_t						tmp_chl = { 0, };



	if (!audio_func || !mci) {
		return -1;
	}

	//�����Ƿ��Ѿ�����
	tmp_find_chl = find_channel(&audio_func->cm, mci->channel_info.index);
	if (tmp_find_chl) {
		cp_module_log(warn, audio_func,
			"insert_audio_media_channel_info() error, channel[%d] exist now!",
			mci->channel_info.index);
		return 0;
	}

	//����ý��ͨ��
	tmp_chl_info = cp_palloc(audio_func->pool, cp_sizeof(cp_channel_info_t));
	if (!tmp_chl_info) {
		cp_module_log(error, audio_func, "insert_audio_media_channel_info() error, cp_palloc() make media channel information failed");
		return -1;
	}
	*tmp_chl_info = mci->channel_info;

	set_channel(&tmp_chl, mci->channel_info.index, mci->channel_info.play_session, (cp_module_t*)audio_func, tmp_chl_info);
	insert_channel(&audio_func->cm, &tmp_chl);

	return 0;
}

/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: update_audio_func_media_play
*
* ����˵��: ����һ��ý�岥��
*
* ��    ��: cp_audio_func_t * audio_func						[in]����˵��
* ��    ��: cp_media_channel_info_t * mci						[in]����˵��
*
* �� �� ֵ: cp_int32_t
*           0  : �ɹ� 
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2017-03-06 17:45:54
******************************************************************************************************/
cp_int32_t update_audio_func_media_play(cp_audio_func_t *audio_func, cp_media_channel_info_t *mci)
{
	if (!audio_func || !mci) {
		return -1;
	}
	audio_func->mci.media_info.audio_source.volume = mci->media_info.audio_source.volume;
	audio_func->decode_md.volume = mci->media_info.audio_source.volume;

	cp_module_log(info, audio_func,
		"update_audio_func_media_play() successed, set volume[%d]",
		mci->media_info.audio_source.volume);

	return 0;
}

/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: remove_audio_media_channel_info
*
* ����˵��: ɾ��ý��ͨ��
*
* ��    ��: cp_audio_func_t * audio_func						[in]����˵��
* ��    ��: cp_media_channel_info_t * mci						[in]����˵��
*
* �� �� ֵ: cp_int32_t
*           0  : �ɹ�
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2016-12-14 11:31:00
******************************************************************************************************/
cp_int32_t remove_audio_media_channel_info(cp_audio_func_t *audio_func, cp_media_channel_info_t *mci)
{
	cp_channel_info_t					*tmp_chl_info = CP_NULL;
	cp_channel_t						*tmp_chl = { 0, };



	tmp_chl = find_channel(&audio_func->cm, mci->channel_info.index);
	if (!tmp_chl) {
		cp_module_log(error, audio_func,
			"remove_audio_media_channel_info() error, not found channel[%d]",
			mci->channel_info.index);
		return -1;
	}
	if (tmp_chl->data) {
		cp_pfree(audio_func->pool, tmp_chl->data);
	}

	remove_channel(&audio_func->cm, mci->channel_info.index);
	return 0;
}

/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: destroy_audio_tmp_data
*
* ����˵��: ������������
*
* ��    ��: cp_audio_func_t * audio_func						[in]����˵��
* ��    ��: cp_array_t * ary						[in]����˵��
*
* �� �� ֵ: cp_int32_t
*           0  : �ɹ�
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2016-12-13 11:27:54
******************************************************************************************************/
cp_int32_t destroy_audio_tmp_data(cp_audio_func_t *audio_func, cp_array_t *ary)
{
	cp_uint32_t							i = 0;
	cp_uint32_t							tmp_number = 0;
	cp_buf_t							**tmp_buf = 0;


	//count size
	for (i = 0; i < cp_array_max_size(ary) &&
		tmp_number < cp_array_length(ary); i++) {
		tmp_buf = (cp_buf_t**)cp_array_get(ary, i);
		if (!(*tmp_buf)) {
			break;
		}
		++tmp_number;
		//����ָ��
		destroy_a_memh_socket_buffer(audio_func->socket->pool, audio_func->msd, (*tmp_buf));
	}

	return 0;
}

/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: init_audio_media_description_info
*
* ����˵��: ��ʼ��ý����Ϣ
*
* ��    ��: cp_audio_func_t * audio_func						[in]����˵��
*
* �� �� ֵ: cp_int32_t
*           0  : �ɹ�
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2016-12-08 15:42:41
******************************************************************************************************/
cp_int32_t init_audio_media_description_info(cp_audio_func_t *audio_func)
{
	if (!audio_func) {
		return -1;
	}

	audio_func->decode_md.type = cp_media_description_type_audio;
	audio_func->decode_md.encodec_type = audio_func->mci.media_info.audio_source.encodec_type;
	audio_func->decode_md.volume = audio_func->mci.media_info.audio_source.volume;
	audio_func->decode_md.channel_layout = audio_func->mci.media_info.audio_source.sound_channel_type;
	audio_func->decode_md.sample_rate = audio_func->mci.media_info.audio_source.sample_rate;
	audio_func->decode_md.bit_rate = audio_func->mci.media_info.audio_source.bit_rate;

	init_audio_description(&audio_func->decode_md);

	return 0;
}

/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: init_audio_codec_callback_info
*
* ����˵��: ���������Ĺ�����Ϣ
*
* ��    ��: cp_audio_func_t * audio_func						[in]����˵��
*
* �� �� ֵ: cp_int32_t
*           0  : �ɹ�
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2016-12-08 15:42:52
******************************************************************************************************/
cp_int32_t init_audio_codec_callback_info(cp_audio_func_t *audio_func)
{
	audio_func->cc_info.handle.read_cb = (cp_codec_general_cb_handle)audio_func_codec_read_cb_handle;
	audio_func->mp_info.decode_mp->ccb_info_p = &audio_func->cc_info;
	return 0;
}

/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: init_audio_merge_safe_queue
*
* ����˵��: ��ʼ��merge
*
* ��    ��: cp_audio_func_t * audio_func						[in]����˵��
*
* �� �� ֵ: cp_int32_t
*           0  : �ɹ�
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2017-01-13 17:03:18
******************************************************************************************************/
cp_int32_t init_audio_merge_safe_queue(cp_audio_func_t *audio_func)
{
	cp_void_t						*tmp_buf = CP_NULL;
	cp_int32_t						tmp_ret_int = 0;
	cp_int32_t						i = 0;
	cp_media_packet_t				*tmp_mp = CP_NULL;


	//�����ڴ��С
	tmp_ret_int = cp_safe_queue_get_memory_size(cp_safe_queue_mode_qbss, audio_func->afc.buffer_size);
	if (!tmp_ret_int) {
		cp_module_log(error, audio_func,
			"init_audio_merge_safe_queue() error. cp_safe_queue_get_memory_size() error. size[%d]",
			audio_func->afc.buffer_size);
		return tmp_ret_int;
	}

	//�����ڴ�
	tmp_buf = cp_palloc(audio_func->pool, tmp_ret_int);
	if (!tmp_buf) {
		cp_module_log(error, audio_func,
			"init_audio_merge_safe_queue() error. cp_palloc() error. size[%d]",
			tmp_ret_int);
		return -1;
	}

	//����safe queue
	audio_func->mp_info.merge_sq = cp_create_memory_safe_queue(tmp_buf, tmp_ret_int, cp_safe_queue_mode_qbss, audio_func->afc.buffer_size);
	if (!audio_func->mp_info.merge_sq) {
		cp_module_log(error, audio_func,
			"init_audio_merge_safe_queue() error. cp_create_memory_safe_queue() error. ");
		return -2;
	}

	//�����ڴ�
	tmp_buf = cp_palloc(audio_func->pool, tmp_ret_int);
	if (!tmp_buf) {
		cp_module_log(error, audio_func,
			"init_audio_merge_safe_queue() error. cp_palloc() error. size[%d]",
			tmp_ret_int);
		return -3;
	}

	//����safe queue
	audio_func->mp_info.merge_cache_sq = cp_create_memory_safe_queue(tmp_buf, tmp_ret_int, cp_safe_queue_mode_qbss, audio_func->afc.buffer_size);
	if (!audio_func->mp_info.merge_cache_sq) {
		cp_module_log(error, audio_func,
			"init_audio_merge_safe_queue() error. cp_create_memory_safe_queue() error. ");
		return -4;
	}

	//������������
	tmp_mp = create_number_media_packet(audio_func->pool,
		audio_func->afc.each_buffer_length, audio_func->afc.buffer_size, cp_media_packet_type_data_and_timestamp);
	if (!tmp_mp) {
		cp_module_log(error, audio_func,
			"init_audio_merge_safe_queue() error. create_number_media_packet() size[%d] number[%d] error. ",
			audio_func->afc.buffer_size,
			audio_func->afc.each_buffer_length);
		return -5;
	}
	audio_func->mp_info.merge_cache_mp = tmp_mp;

	//��ʼ������
	for (i = 0; i < audio_func->afc.buffer_size; i++, tmp_mp++) {
		cp_safe_queue_push(audio_func->mp_info.merge_cache_sq, tmp_mp);
	}

	return 0;
}

/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: destory_audio_merge_safe_queue
*
* ����˵��: ����merge
*
* ��    ��: cp_audio_func_t * audio_func						[in]����˵��
*
* �� �� ֵ: cp_int32_t
*           0  : �ɹ�
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2017-01-13 17:03:31
******************************************************************************************************/
cp_int32_t destory_audio_merge_safe_queue(cp_audio_func_t *audio_func)
{
	if (audio_func->mp_info.merge_sq) {
		cp_destroy_safe_queue(audio_func->mp_info.merge_sq);
		audio_func->mp_info.merge_sq = CP_NULL;
	}

	if (audio_func->mp_info.merge_cache_sq) {
		cp_destroy_safe_queue(audio_func->mp_info.merge_cache_sq);
		audio_func->mp_info.merge_cache_sq = CP_NULL;
	}

	if (audio_func->mp_info.merge_cache_mp) {
		cp_pfree(audio_func->pool, audio_func->mp_info.merge_cache_mp);
		audio_func->mp_info.merge_cache_mp = CP_NULL;
	}

	return 0;
}

//����һ��media_packet
cp_media_packet_t *create_a_audio_media_packet(cp_audio_func_t *audio_func, cp_int32_t len)
{
	cp_media_packet_t					*tmp_mp = CP_NULL;



#if defined(CP_AUDIO_FUNC_USED_MULTI_THREAD)
	//�ȴӿ��ж����л��
	if (len < audio_func->afc.each_buffer_length) {
		tmp_mp = cp_safe_queue_pop(audio_func->mp_info.merge_cache_sq);
	}
	if (!tmp_mp) {
		//create media packet
		tmp_mp = cp_malloc(cp_sizeof(cp_media_packet_t) + len);
		if (!tmp_mp) {
			return CP_NULL;
		}
		cp_memset(tmp_mp, 0, cp_sizeof(cp_media_packet_t) + len);
		tmp_mp->type = cp_media_packet_type_data_and_timestamp;
		tmp_mp->pool = CP_NULL;
		cp_buf_assemble(&tmp_mp->mp_buf.buf[0], (cp_uchar_t*)tmp_mp + cp_sizeof(cp_media_packet_t), len);
	}
#else
	tmp_mp = create_media_packet(audio_func->pool, len, cp_media_packet_type_data_and_timestamp);
#endif

	return tmp_mp;
}

//����һ��media_packet
cp_int32_t destroy_a_audio_media_packet(cp_audio_func_t *audio_func, cp_media_packet_t *mp)
{
#if defined(CP_AUDIO_FUNC_USED_MULTI_THREAD)
	if (get_media_packet_data_length(mp) > audio_func->afc.each_buffer_length) {
		cp_free(mp);
	}
	else {
		clear_media_packet(mp);
		cp_safe_queue_push(audio_func->mp_info.merge_cache_sq, mp);
	}
#else
	destroy_media_packet(mp);
#endif
	return 0;
}

//���������߳�
cp_int32_t start_audio_thread_process(cp_audio_func_t *audio_func)
{
#if defined(CP_AUDIO_FUNC_USED_MULTI_THREAD)
	return start_audio_multi_thread_process(audio_func);
#else 
	//���ﴴ��һ���߳�ͳһ����ý��
	return start_audio_single_thread_process(audio_func);
#endif

	return 0;
}

//���������߳�
cp_int32_t start_audio_single_thread_process(cp_audio_func_t *audio_func)
{
	//���ﴴ��һ���߳�ͳһ����ý��
	audio_func->mp_info.thread_status = cp_audio_func_thread_status_start;
	audio_func->mp_info.merge_thread = cp_create_thread(audio_func->manager->app, audio_func_thread_cb_proc, audio_func);
	if (!audio_func->mp_info.merge_thread) {
		cp_module_log(error, audio_func, "open_audio_func() error, make_player_func_thread_manager() failed");
		return -1;
	}
	return 0;
}

//���������߳�
cp_int32_t start_audio_multi_thread_process(cp_audio_func_t *audio_func)
{
	cp_int32_t					tmp_ret_int = 0;


	tmp_ret_int = start_audio_merge_thread_process(audio_func);
	if (tmp_ret_int) {
		return tmp_ret_int;
	}
	tmp_ret_int = start_audio_decode_thread_process(audio_func);
	if (tmp_ret_int) {
		return tmp_ret_int;
	}
	return 0;
}

//���������߳�
cp_int32_t start_audio_merge_thread_process(cp_audio_func_t *audio_func)
{
	//���ﴴ��һ���߳�ͳһ����ý��
	audio_func->mp_info.thread_status = cp_audio_func_thread_status_start;
	audio_func->mp_info.merge_thread = cp_create_thread(audio_func->manager->app, audio_func_merge_thread_cb_proc, audio_func);
	if (!audio_func->mp_info.merge_thread) {
		cp_module_log(error, audio_func, "open_audio_func() error, make_player_func_thread_manager() failed");
		return -1;
	}

	return 0;
}

//���������߳�
cp_int32_t start_audio_decode_thread_process(cp_audio_func_t *audio_func)
{
	//���ﴴ��һ���߳�ͳһ����ý��
	audio_func->mp_info.thread_status = cp_audio_func_thread_status_start;
	audio_func->play_flag = 0;
	audio_func->mp_info.decode_thread = cp_create_thread(audio_func->manager->app, audio_func_decode_thread_cb_proc, audio_func);
	if (!audio_func->mp_info.decode_thread) {
		cp_module_log(error, audio_func, "open_audio_func() error, make_player_func_thread_manager() failed");
		return -1;
	}

	return 0;
}

//ֹͣ�����߳�
cp_int32_t stop_audio_merge_thread_process(cp_audio_func_t *audio_func)
{
	if (audio_func->mp_info.merge_thread) {
		audio_func->mp_info.thread_status = cp_audio_func_thread_status_stop;
		cp_thread_join(audio_func->mp_info.merge_thread);
		cp_destroy_thread(audio_func->mp_info.merge_thread);
		audio_func->mp_info.merge_thread = CP_NULL;
	}
	return 0;
}

/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: stop_audio_decode_thread_process
*
* ����˵��: ֹͣ�����߳�
*
* ��    ��: cp_audio_func_t * audio_func						[in]����˵��
*
* �� �� ֵ: cp_int32_t
*           0  : �ɹ�
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2017-01-12 15:56:22
******************************************************************************************************/
cp_int32_t stop_audio_decode_thread_process(cp_audio_func_t *audio_func)
{
	if (audio_func->mp_info.decode_thread) {
		audio_func->mp_info.thread_status = cp_audio_func_thread_status_stop;
		cp_thread_join(audio_func->mp_info.decode_thread);
		cp_destroy_thread(audio_func->mp_info.decode_thread);
		audio_func->mp_info.decode_thread = CP_NULL;
	}
	return 0;
}

//ֹͣ�����߳�
cp_int32_t stop_audio_thread_process(cp_audio_func_t *audio_func)
{
	stop_audio_merge_thread_process(audio_func);
	stop_audio_decode_thread_process(audio_func);
	return 0;
}

//ֹͣ�����߳�
cp_int32_t stop_audio_single_thread_process(cp_audio_func_t *audio_func)
{
	return stop_audio_thread_process(audio_func);
}

//ֹͣ�����߳�
cp_int32_t stop_audio_multi_thread_process(cp_audio_func_t *audio_func)
{
	return stop_audio_thread_process(audio_func);
}

//��ӡʱ�������
cp_char_t* format_audio_frame_timestamp(cp_char_t *buf, cp_int32_t len)
{
	cp_timeval							tmp_tv = { 0, };
	cp_int64_t							tmp_us = 0;



	if (!buf || !len) {
		return CP_NULL;
	}

	cp_gettimeofday(&tmp_tv, CP_NULL);
	cp_memset(buf, 0, len);
	tmp_us = tmp_tv.tv_sec * CP_TIME_SEC_TO_USEC + tmp_tv.tv_usec;
	cp_snprintf(buf, len, "timestamp:\t%d:%d\t%lld\t", tmp_tv.tv_sec, tmp_tv.tv_usec, tmp_us);
	return buf;
}

//����ɾ����Ϣ
cp_int32_t send_remove_module_message(cp_audio_func_t *audio_func)
{
	cp_module_message_t				*tmp_ret_mm = CP_NULL;
	cp_audio_func_manager_t			*tmp_afm = (cp_audio_func_manager_t *)(audio_func->manager);



	tmp_ret_mm = create_module_message(tmp_afm->mmm);
	if (!tmp_ret_mm) {
		cp_module_log(error, audio_func, "send_remove_module_message() error. create_module_message() error");
		return -1;
	}

	set_module_message(tmp_ret_mm, (cp_module_t*)audio_func, CP_NULL, 0, cp_module_message_type_close, CP_NULL);

	push_module_message(tmp_afm->mmm, tmp_ret_mm);

	cp_module_log(warn, audio_func, "send_remove_module_message() successed.");

	return 0;
}

