/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/
#include "cp_audio_func.h"
#include "cp_audio_func_proc.h"



cp_audio_func_t *cp_audio_func_create();
/*ģ���ʼ���ӿڣ���ģ��create֮�󣬻ᱻ����*/
cp_int32_t init_audio_func(cp_audio_func_t *audio_func, const cp_audio_func_info_t *audio_func_info);
/*ģ������нӿڣ���ģ��init֮�󣬻ᱻ����*/
cp_int32_t open_audio_func(cp_audio_func_t *audio_func, const cp_audio_func_info_t *audio_func_info);
/*��ȡģ�����ݣ�flagΪ��ȡģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��*/
cp_int32_t read_audio_func(cp_audio_func_t *audio_func, cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag);
/*дģ�����ݣ�flagΪдģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��*/
cp_int32_t write_audio_func(cp_audio_func_t *audio_func, const cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag);
/*�ر�ģ��*/
cp_int32_t close_audio_func(cp_audio_func_t *audio_func);
/*�˳�ģ��*/
cp_int32_t exit_audio_func(cp_audio_func_t *audio_func);
/*����ģ�����*/
cp_int32_t set_option_audio_func(cp_audio_func_t *audio_func, cp_int32_t optname, const cp_void_t* optval);
cp_int32_t get_option_audio_func(cp_audio_func_t *audio_func, cp_int32_t optname, cp_void_t* optval);


#if 0
cp_int32_t listen_audio_func(cp_socket_t *socket, cp_sockaddr_in *addr);											/*�򿪼���*/
cp_int32_t connect_audio_func(cp_socket_t *socket, cp_sockaddr_in *addr);										/*��ʼ����*/
cp_int32_t read_s_audio_func(cp_audio_func_t *cp_s, const cp_buf_t *buf, cp_int32_t nread, cp_int32_t flags);	/*������*/
cp_int32_t write_s_audio_func(cp_socket_t *socket, const cp_buf_t *buf, cp_int32_t nread, const cp_sockaddr_in *remote_addr, cp_int32_t flags);
cp_int32_t close_s_audio_func(cp_socket_t *socket);																/*�ر�����*/
#endif

cp_int32_t connect_cb_audio_func(cp_socket_t *socket, cp_int32_t status);										/*���ӻص�����*/
cp_int32_t close_cb_audio_func(cp_socket_t *socket, cp_int32_t status);											/*�رջص�����*/
cp_int32_t read_cb_audio_func(cp_socket_t *socket, const cp_buf_t *buf, cp_int32_t nread, cp_int32_t status);	/*���ص�����*/
cp_int32_t write_cb_audio_func(cp_socket_t *socket, cp_int32_t status);											/*д�ص�����*/
cp_int32_t error_cb_audio_func(cp_socket_t *socket, cp_int32_t status);											/*����ص�����*/

//����Ƶ�� socket
cp_int32_t open_audio_multicast_socket(cp_audio_func_t *audio_func, cp_char_t *buf, cp_int32_t len);

cp_audio_func_t* create_audio_func(cp_module_register_t *register_info, cp_socket_manager_t *manager, cp_audio_func_info_t *info)
{
	cp_int32_t							ret_int = 0;
	cp_audio_func_t						*tmp_module = CP_NULL;
	cp_pool_info_t						tmp_pool_info = { 0, };


	if (!register_info || !manager || !info) {
		return CP_NULL;
	}

	tmp_module = cp_malloc_module(manager, cp_audio_func_t, &tmp_pool_info);
	if (!tmp_module) {
		return CP_NULL;
	}
	CP_FUNC_MODULE_SET_HANDLERS(tmp_module, audio_func);

	return tmp_module;
}

cp_int32_t destroy_audio_func(cp_audio_func_manager_t *manager, cp_audio_func_t* audio_func)
{
	if (!manager || !audio_func) {
		return -1;
	}
	cp_free_module(audio_func);
	return 0;
}

/*ģ���ʼ���ӿڣ���ģ��create֮�󣬻ᱻ����*/
cp_int32_t init_audio_func(cp_audio_func_t *audio_func, const cp_audio_func_info_t *audio_func_info)
{
	cp_int32_t									ret_int = 0;
	cp_void_t									*tmp_void_p = CP_NULL;
	cp_player_t									*tmp_player = (cp_player_t*)audio_func->manager->app;
	cp_player_info_t							*tmp_player_info = (cp_player_info_t *)(tmp_player->app_info);


	if (!audio_func || !audio_func_info || !audio_func_info->data) {
		return -1;
	}

	//�����ж��Ƿ��Ѿ���ʼ��
	if (CP_MODULE_GET_STATUS(audio_func, cp_module_status_init)) {
		return 0;
	}

	//������Ƶ�����ļ�
	ret_int = audio_func_parse_configure((cp_module_t*)audio_func, &audio_func->afc);
	if (ret_int) {
		cp_module_log(error, audio_func, "init_audio_func() error. audio_func_parse_configure() error.");
		return -2;
	}

	//�豸media_channel ��Ϣ
	audio_func->mci = *((cp_media_channel_info_t *)(audio_func_info->data));

	//��ʼ��������������
	audio_func->mp_info.decode_mp = create_media_packet(audio_func->pool, 0, cp_media_packet_type_data_and_timestamp);
	if (!audio_func->mp_info.decode_mp) {
		cp_module_log(error, audio_func, "init_audio_func() error. create_media_packet() error.");
		return -2;
	}
	//����
	audio_func->mp_info.decode_mp->orgin_module = (cp_module_t*)audio_func;
	//��ʼ�����ݰ�������Ϣ
	ret_int = create_media_packet_description(audio_func->pool, audio_func->mp_info.decode_mp, cp_media_description_type_audio);
	if (ret_int) {
		cp_module_log(error, audio_func, "init_audio_func() error. create_media_packet_description() error.");
		return -2;
	}

	//��ʼý�������Ϣ
	ret_int = init_audio_media_description_info(audio_func);
	if (ret_int) {
		cp_module_log(error, audio_func, "init_audio_func() error. init_audio_media_description_info() error.");
		return -2;
	}

	//��ʼ�����������Ϣ
	ret_int = init_audio_codec_callback_info(audio_func);
	if (ret_int) {
		cp_module_log(error, audio_func, "init_audio_func() error. init_audio_codec_callback_info() error.");
		return -2;
	}

	//��ʼ��merge
	ret_int = init_audio_merge_safe_queue(audio_func);
	if (ret_int) {
		cp_module_log(error, audio_func, "init_audio_func() error. init_audio_merge_safe_queue() error.");
		return -3;
	}

	open_audio_test_file(audio_func);

	return 0;
}

/*ģ������нӿڣ���ģ��init֮�󣬻ᱻ����*/
cp_int32_t open_audio_func(cp_audio_func_t *audio_func, const cp_audio_func_info_t *audio_func_info)
{
	cp_int32_t							tmp_ret_int = 0;
	cp_char_t							tmp_buf[CP_APP_DEFAULT_BUFFER_LENGTH] = { 0, };



	//�����ж��Ƿ��Ѿ���ʼ��
	if (!CP_MODULE_GET_STATUS(audio_func, cp_module_status_open)) {
		//�������
		tmp_ret_int = open_audio_multicast_socket(audio_func, tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH);
		if (tmp_ret_int) {
			cp_module_log(error, audio_func, "open_audio_func() error. open_audio_multicast_socket() error. reason:%s",
				tmp_buf);
			return -2;
		}

		start_audio_thread_process(audio_func);		
	}

	return 0;
}

/*��ȡģ�����ݣ�flagΪ��ȡģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��*/
cp_int32_t read_audio_func(cp_audio_func_t *audio_func, cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag)
{
	return 0;
}

/*дģ�����ݣ�flagΪдģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��*/
cp_int32_t write_audio_func(cp_audio_func_t *audio_func, const cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag)
{
#if 0
	cp_int32_t							ret_int = 0;
	cp_int32_t							tmp_css_av_type = 0;
	gmp_gmph_bmh_t						*tmp_bmh = CP_NULL;
	gmp_gmph_memh_t						*tmp_memh = CP_NULL;
	cp_socket_t							*tmp_socket = CP_NULL;


	if (audio_func->is_open_codec) {
		return 0;
	}

	if (cp_player_func_flag_socket_point != flag ||
		len != cp_sizeof(cp_socket_t*)) {
		return 0;
	}

	tmp_socket = (cp_socket_t *)(*buf);
	if (tmp_socket) {
		//ȡ��semh��ͷ���ж�semh��С����
		tmp_bmh = (gmp_gmph_bmh_t*)cp_buf_get_pos(tmp_socket->buf);

		if (gmp_gmph_emh_type_memh == tmp_bmh->emht) {
			tmp_memh = (gmp_gmph_memh_t*)tmp_bmh;
			//����
			if (!audio_func->is_open_codec && audio_func->codec &&
				(css_media_network_begin == tmp_memh->packet_type ||
				css_media_network_other == tmp_memh->packet_type ||
				css_media_network_end == tmp_memh->packet_type)) {
				//
				tmp_css_av_type = tmp_memh->media_type;
				ret_int = cp_set_option_module(audio_func->codec, cp_player_codec_set_option_codec_info, &tmp_css_av_type);
				if (ret_int) {
					cp_module_log(error, audio_func, "module(audio_func) set codec type[%d] error.", tmp_css_av_type);
				}
				else {
					audio_func->is_open_codec = cp_true;
				}
			}
		}
	}
#endif
	return 0;
}

/*�ر�ģ��*/
cp_int32_t close_audio_func(cp_audio_func_t *audio_func)
{
	//�ر��鲥
	close_audio_multicast_socket(audio_func);

	//�ر���Ƶ������
	close_audio_codec_info(audio_func);

	//�ر��߳�
	stop_audio_thread_process(audio_func);

	//������Ƶ��������Ϣ
	unset_audio_codec_info(audio_func);

	//������Ƶ������Ϣ
	unset_audio_dev_info(audio_func);

	//����merge
	destory_audio_merge_safe_queue(audio_func);

	if (audio_func->mp_info.decode_mp) {
		//����ý���������Ϣ
		destroy_media_packet_description(audio_func->pool, audio_func->mp_info.decode_mp);

		//����ý���
		destroy_media_packet(audio_func->mp_info.decode_mp);
		audio_func->mp_info.decode_mp = CP_NULL;
	}

	close_audio_test_file(audio_func);

	return 0;
}

/*�˳�ģ��*/
cp_int32_t exit_audio_func(cp_audio_func_t *audio_func)
{
	return 0;
}

/*����ģ�����*/
cp_int32_t set_option_audio_func(cp_audio_func_t *audio_func, cp_int32_t optname, const cp_void_t* optval)
{
	cp_module_info_t					*module_info;



	if (cp_player_func_set_option_stop_media_play & optname) {
		if (!optval) {
			return -1;
		}
		module_info = (cp_module_info_t *)optval;
		return stop_audio_func_media_play(audio_func, (cp_media_channel_info_t*)(module_info->data));
	}

	if (cp_player_func_set_option_update_media_info & optname) {
		if (!optval) {
			return -1;
		}
		module_info = (cp_module_info_t *)optval;
		return update_audio_func_media_play(audio_func, (cp_media_channel_info_t*)(module_info->data));
	}

	cp_module_log(error, audio_func,
		"set_option_audio_func() error. unsupport optname[%d]", optname);
	return -1;
}

cp_int32_t get_option_audio_func(cp_audio_func_t *audio_func, cp_int32_t optname, cp_void_t* optval)
{
	cp_media_channel_info_t					**tmp_mci = CP_NULL;



	if (cp_player_func_get_option_media_channel_info == optname) {
		if (!optval) {
			return -1;
		}
		tmp_mci = (cp_media_channel_info_t **)optval;

		*tmp_mci = &(audio_func->mci);
		return 0;
	}

	cp_module_log(error, audio_func,
		"set_option_audio_func() error. unsupport optname[%d]", optname);
	return -1;
}

#if 0
cp_int32_t listen_audio_func(cp_socket_t *socket, cp_sockaddr_in *addr)
{
	return 0;
}

cp_int32_t connect_audio_func(cp_socket_t *socket, cp_sockaddr_in *addr)
{
	return 0;
}

cp_int32_t read_s_audio_func(cp_audio_func_t *cp_s, const cp_buf_t *buf, cp_int32_t nread, cp_int32_t flags)
{
	return 0;
}

cp_int32_t write_s_audio_func(cp_socket_t *socket, const cp_buf_t *buf, cp_int32_t nread, const cp_sockaddr_in *remote_addr, cp_int32_t flags)
{
	return 0;
}

cp_int32_t close_s_audio_func(cp_socket_t *socket)
{
	return 0;
}
#endif

cp_int32_t connect_cb_audio_func(cp_socket_t *socket, cp_int32_t status)
{
	cp_buf_t				*buf;
	cp_int32_t				tmp_read_length = 0;


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

	//CP_SOCKET_MODULE_SET_CALLBACK_HANDLERS(socket, audio_func);
	cp_read_socket(socket, buf, tmp_read_length, 0);
	return 0;
}

cp_int32_t close_cb_audio_func(cp_socket_t *socket, cp_int32_t status)
{
	return 0;
}

cp_int32_t read_cb_audio_func(cp_socket_t *socket, const cp_buf_t *buf, cp_int32_t nread, cp_int32_t status)
{
	cp_int32_t					ret_int = 0;
	cp_audio_func_t*			tmp_audio_func = CP_NULL;


	//����� ���ݲ���filter����
	if (!socket->data || !((cp_audio_func_t*)(socket->data))->filter ||
		!((cp_audio_func_t*)(socket->data))->filter->read_cb) {
		return -1;
	}

	((cp_audio_func_t*)(socket->data))->filter->read_cb(socket, buf, nread, status);

	return ret_int;
}

cp_int32_t write_cb_audio_func(cp_socket_t *socket, cp_int32_t status)
{
	return connect_cb_audio_func(socket, status);
}

cp_int32_t error_cb_audio_func(cp_socket_t *socket, cp_int32_t status)
{
	return 0;
}

/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: open_audio_multicast_socket
*
* ����˵��: ����Ƶ�� socket
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
* �������ڣ�2016-11-25 15:18:29
******************************************************************************************************/
cp_int32_t open_audio_multicast_socket(cp_audio_func_t *audio_func, cp_char_t *buf, cp_int32_t len)
{
	cp_int32_t							tmp_ret_int = 0;
	cp_char_t							tmp_buf[CP_APP_DEFAULT_BUFFER_LENGTH] = { 0, };
	cp_sockaddr_in						tmp_multicast_addr = { 0, };


	cp_memset(buf, 0, len);
	if (!audio_func->mci.channel_info.multicast_info.port ||
		!cp_strlen(audio_func->mci.channel_info.multicast_info.ip)) {
		cp_snprintf(buf, len, "url address [%s:%d] error.",
			audio_func->mci.channel_info.multicast_info.ip,
			audio_func->mci.channel_info.multicast_info.port);
		return -1;
	}
	//��
	audio_func->socket = cp_create_socket(audio_func->manager->app, cp_socket_type_multicast);
	if (!audio_func->socket) {
		cp_snprintf(buf, len, "cp_create_socket() error.");
		return -2;
	}

	CP_SOCKET_MODULE_SET_CALLBACK_HANDLERS(audio_func->socket, audio_func);
	tmp_ret_int = set_audio_multicast_data_filter(audio_func, tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH);
	if (tmp_ret_int) {
		cp_snprintf(buf, len, "set_audio_multicast_data_filter() error. %s", tmp_buf);
		return -2;
	}

	cp_ip4_addr(audio_func->mci.channel_info.multicast_info.ip,
		audio_func->mci.channel_info.multicast_info.port, &tmp_multicast_addr);

	//����multicast����
	tmp_ret_int = cp_listen_socket(audio_func->socket, &tmp_multicast_addr);
	if (tmp_ret_int) {
		cp_snprintf(buf, len, "cp_listen_socket() [%s:%d] error.",
			audio_func->mci.channel_info.multicast_info.ip,
			audio_func->mci.channel_info.multicast_info.port);
		return -2;
	}

	return 0;
}
