/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/
#include "cp_video_func.h"
#include "cp_player_codec_core.h"




cp_video_func_t *cp_video_func_create();
/*ģ���ʼ���ӿڣ���ģ��create֮�󣬻ᱻ����*/
cp_int32_t init_video_func(cp_video_func_t *video_func, const cp_video_func_info_t *video_func_info);
/*ģ������нӿڣ���ģ��init֮�󣬻ᱻ����*/
cp_int32_t open_video_func(cp_video_func_t *video_func, const cp_video_func_info_t *video_func_info);
/*��ȡģ�����ݣ�flagΪ��ȡģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��*/
cp_int32_t read_video_func(cp_video_func_t *video_func, cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag);
/*дģ�����ݣ�flagΪдģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��*/
cp_int32_t write_video_func(cp_video_func_t *video_func, const cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag);
/*�ر�ģ��*/
cp_int32_t close_video_func(cp_video_func_t *video_func);
/*�˳�ģ��*/
cp_int32_t exit_video_func(cp_video_func_t *video_func);
/*����ģ�����*/
cp_int32_t set_option_video_func(cp_video_func_t *video_func, cp_int32_t optname, const cp_void_t* optval);
cp_int32_t get_option_video_func(cp_video_func_t *video_func, cp_int32_t optname, cp_void_t* optval);


#if 0
cp_int32_t listen_video_func(cp_socket_t *socket, cp_sockaddr_in *addr);											/*�򿪼���*/
cp_int32_t connect_video_func(cp_socket_t *socket, cp_sockaddr_in *addr);										/*��ʼ����*/
cp_int32_t read_s_video_func(cp_video_func_t *cp_s, const cp_buf_t *buf, cp_int32_t nread, cp_int32_t flags);	/*������*/
cp_int32_t write_s_video_func(cp_socket_t *socket, const cp_buf_t *buf, cp_int32_t nread, const cp_sockaddr_in *remote_addr, cp_int32_t flags);
cp_int32_t close_s_video_func(cp_socket_t *socket);																/*�ر�����*/
#endif

cp_int32_t connect_cb_video_func(cp_socket_t *socket, cp_int32_t status);										/*���ӻص�����*/
cp_int32_t close_cb_video_func(cp_socket_t *socket, cp_int32_t status);											/*�رջص�����*/
cp_int32_t read_cb_video_func(cp_socket_t *socket, const cp_buf_t *buf, cp_int32_t nread, cp_int32_t status);	/*���ص�����*/
cp_int32_t write_cb_video_func(cp_socket_t *socket, cp_int32_t status);											/*д�ص�����*/
cp_int32_t error_cb_video_func(cp_socket_t *socket, cp_int32_t status);											/*����ص�����*/

cp_int32_t video_func_data_integrity
(cp_socket_t *socket, const cp_buf_t *buf, cp_int32_t nread, cp_int32_t status);

cp_int32_t video_func_process_socket_data(cp_socket_t *socket, const cp_buf_t *buf, cp_int32_t nread, cp_int32_t status);

void video_func_thread_cb_proc(cp_video_func_t *video_func);

/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: set_video_multicast_data_filter
*
* ����˵��: ����multicast socket
*
* ��    ��: cp_video_func_t * video_func			[in]����˵��
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
cp_int32_t set_video_multicast_data_filter(cp_video_func_t *video_func, cp_char_t *buf, cp_int32_t len);

//����Ƶ�� socket
cp_int32_t open_video_multicast_socket(cp_video_func_t *video_func, cp_char_t *buf, cp_int32_t len);

//�ر���Ƶ socket
cp_int32_t close_video_multicast_socket(cp_video_func_t *video_func);

//����memh��socket����
cp_int32_t set_video_memh_socket_data(cp_video_func_t *video_func, cp_char_t *buf, cp_int32_t len);

//����memh socket����
cp_int32_t unset_video_memh_socket_data(cp_video_func_t *video_func);

//У�������Ƿ��
cp_inline cp_static cp_bool_t check_is_end(cp_buf_t *buf);

//�򿪲����ļ�
cp_inline cp_static cp_bool_t open_test_file(cp_video_func_t *video_func);

//�رղ����ļ�
cp_inline cp_static cp_bool_t close_test_file(cp_video_func_t *video_func);

//���ý�������Ϣ
cp_inline cp_static cp_int32_t set_video_codec_info(cp_video_func_t *video_func, cp_array_t *ary);

//������Ƶ��������Ϣ
cp_inline cp_static cp_int32_t unset_codec_info(cp_video_func_t *video_func);

//���ò�����Ϣ
cp_inline cp_static cp_int32_t set_video_dev_info(cp_video_func_t *video_func, cp_video_description_t *vd);

//������Ƶ������Ϣ
cp_inline cp_static cp_int32_t unset_video_dev_info(cp_video_func_t *video_func);

//����ý������
cp_inline cp_static cp_media_packet_t* merge_media_data(cp_video_func_t *video_func, cp_array_t *ary);

//��ȡһ֡��
cp_inline cp_static cp_int32_t get_a_frame_data(cp_video_func_t *video_func, cp_array_t *ary);

//����ý������
cp_inline cp_static cp_int32_t decode_media_data(cp_video_func_t *video_func, cp_media_packet_t	*mp);

//��ý������
cp_inline cp_static cp_int32_t play_media_data(cp_video_func_t *video_func, cp_media_packet_t	*mp);

//ֹͣһ��ý�岥��
cp_inline cp_static cp_int32_t stop_video_func_media_play(cp_video_func_t *video_func, cp_media_channel_info_t *mci);

//���ý��ͨ��
cp_inline cp_static cp_int32_t insert_media_channel_info(cp_video_func_t *video_func, cp_media_channel_info_t *mci);

//ɾ��ý��ͨ��
cp_inline cp_static cp_int32_t remove_media_channel_info(cp_video_func_t *video_func, cp_media_channel_info_t *mci);

//������������
cp_inline cp_static cp_int32_t destroy_tmp_data(cp_video_func_t *video_func, cp_media_packet_t *mp, cp_array_t *ary);

//��ʼ��ý����Ϣ
cp_inline cp_static cp_int32_t init_media_description_info(cp_video_func_t *video_func);

//��ʼ��������Ϣ
cp_inline cp_static cp_int32_t init_codec_callback_info(cp_video_func_t *video_func);

//ֹͣ�����߳�
cp_inline cp_static cp_int32_t stop_thread_process(cp_video_func_t *video_func);

cp_video_func_t* create_video_func(cp_module_register_t *register_info, cp_socket_manager_t *manager, cp_video_func_info_t *info)
{
	cp_int32_t							ret_int = 0;
	cp_video_func_t						*tmp_module = CP_NULL;
	cp_pool_info_t						tmp_pool_info = { 0, };


	if (!register_info || !manager || !info) {
		return CP_NULL;
	}

	tmp_module = cp_malloc_module(manager, cp_video_func_t, &tmp_pool_info);
	if (!tmp_module) {
		return CP_NULL;
	}
	CP_FUNC_MODULE_SET_HANDLERS(tmp_module, video_func);

	return tmp_module;
}

cp_int32_t destroy_video_func(cp_video_func_manager_t *manager, cp_video_func_t* video_func)
{
	if (!manager || video_func) {
		return -1;
	}
	cp_free_module(video_func);
	return 0;
}

/*ģ���ʼ���ӿڣ���ģ��create֮�󣬻ᱻ����*/
cp_int32_t init_video_func(cp_video_func_t *video_func, const cp_video_func_info_t *video_func_info)
{
	cp_int32_t									ret_int = 0;
	cp_void_t									*tmp_void_p = CP_NULL;
	cp_player_t									*tmp_player = (cp_player_t*)video_func->manager->app;
	cp_player_info_t							*tmp_player_info = (cp_player_info_t *)(tmp_player->app_info);


	if (!video_func || !video_func_info || !video_func_info->data) {
		return -1;
	}

	//�����ж��Ƿ��Ѿ���ʼ��
	if (CP_MODULE_GET_STATUS(video_func, cp_module_status_init)) {
		return 0;
	}

	//�豸media_channel ��Ϣ
	video_func->mci = *((cp_media_channel_info_t *)(video_func_info->data));

	//��ʼ��������������
	video_func->decode_mp = create_media_packet(video_func->pool, 0, cp_media_packet_type_data_and_timestamp);
	if (!video_func->decode_mp) {
		cp_module_log(error, video_func, "init_video_func() error. create_media_packet() error.");
		return -2;
	}
	//����
	video_func->decode_mp->orgin_module = (cp_module_t*)video_func;
	//��ʼ�����ݰ�������Ϣ
	ret_int = create_media_packet_description(video_func->pool, video_func->decode_mp, cp_media_description_type_video);
	if (ret_int) {
		cp_module_log(error, video_func, "init_video_func() error. create_media_packet_description() error.");
		return -2;
	}

	//��ʼý�������Ϣ
	ret_int = init_media_description_info(video_func);
	if (ret_int) {
		cp_module_log(error, video_func, "init_video_func() error. init_media_description_info() error.");
		return -2;
	}

	//��ʼ�����������Ϣ
	ret_int = init_codec_callback_info(video_func);
	if (ret_int) {
		cp_module_log(error, video_func, "init_video_func() error. init_codec_callback_info() error.");
		return -2;
	}

	//��ʼ��ͨ��������
	ret_int = init_channel_manager(video_func->manager->app, &video_func->cm,
		tmp_player_info->device_info->hardware.limit_play_count);
	if (ret_int) {
		cp_module_log(error, video_func, "init_video_func() error. init_channel_manager() error.");
		return -2;
	}

	open_test_file(video_func);

	return 0;
}
/*ģ������нӿڣ���ģ��init֮�󣬻ᱻ����*/
cp_int32_t open_video_func(cp_video_func_t *video_func, const cp_video_func_info_t *video_func_info)
{
	cp_media_channel_info_t				*tmp_mci = CP_NULL;
	cp_channel_info_t					*tmp_chl_info = CP_NULL;
	cp_int32_t							tmp_ret_int = 0;
	cp_char_t							tmp_buf[CP_APP_DEFAULT_BUFFER_LENGTH] = { 0, };
	cp_channel_t						tmp_chl = { 0, };



	//�����ж��Ƿ��Ѿ���ʼ��
	if (!CP_MODULE_GET_STATUS(video_func, cp_module_status_open)) {

		//����ͨ��������
		tmp_ret_int = start_channel_manager(&video_func->cm);
		if (tmp_ret_int) {
			cp_module_log(error, video_func, "open_video_func() error. start_channel_manager() error.");
			return -2;
		}

		//�������
		tmp_ret_int = open_video_multicast_socket(video_func, tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH);
		if (tmp_ret_int) {
			cp_module_log(error, video_func, "open_video_func() error. open_video_multicast_socket() error. reason:%s",
				tmp_buf);
			return -2;
		}

		//���ﴴ��һ���߳�ͳһ����ý��
		video_func->thread_status = cp_video_func_thread_status_start;
		video_func->thread = cp_create_thread(video_func_thread_cb_proc, video_func);
		if (!video_func->thread) {
			cp_module_log(error, video_func, "open_video_func() error, make_player_func_thread_manager() failed");
			return -1;
		}
	}

	//���ͨ����Ϣ
	tmp_ret_int = insert_media_channel_info(video_func, (cp_media_channel_info_t *)video_func_info->data);
	if (tmp_ret_int) {
		cp_module_log(error, video_func, "open_video_func() error. insert_media_channel_info() error.");
		return -1;
	}

	return 0;
}
/*��ȡģ�����ݣ�flagΪ��ȡģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��*/
cp_int32_t read_video_func(cp_video_func_t *video_func, cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag)
{
	return 0;
}
/*дģ�����ݣ�flagΪдģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��*/
cp_int32_t write_video_func(cp_video_func_t *video_func, const cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag)
{
#if 0
	cp_int32_t							ret_int = 0;
	cp_int32_t							tmp_css_av_type = 0;
	gmp_gmph_bmh_t						*tmp_bmh = CP_NULL;
	gmp_gmph_memh_t						*tmp_memh = CP_NULL;
	cp_socket_t							*tmp_socket = CP_NULL;


	if (video_func->is_open_codec) {
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
			if (!video_func->is_open_codec && video_func->codec &&
				(css_media_network_begin == tmp_memh->packet_type ||
				css_media_network_other == tmp_memh->packet_type ||
				css_media_network_end == tmp_memh->packet_type)) {
				//
				tmp_css_av_type = tmp_memh->media_type;
				ret_int = cp_set_option_module(video_func->codec, cp_player_codec_set_option_codec_info, &tmp_css_av_type);
				if (ret_int) {
					cp_module_log(error, video_func, "module(video_func) set codec type[%d] error.", tmp_css_av_type);
				}
				else {
					video_func->is_open_codec = cp_true;
				}
			}
		}
	}
#endif
	return 0;
}
/*�ر�ģ��*/
cp_int32_t close_video_func(cp_video_func_t *video_func)
{
	//�ر��鲥
	close_video_multicast_socket(video_func);

	//�ر��߳�
	stop_thread_process(video_func);

	//������Ƶ��������Ϣ
	unset_codec_info(video_func);

	//������Ƶ������Ϣ
	unset_video_dev_info(video_func);

	//�ر�ͨ��������
	stop_channel_manager(&video_func->cm);

	if (video_func->decode_mp) {
		//����ý���������Ϣ
		destroy_media_packet_description(video_func->pool, video_func->decode_mp);

		//����ý���
		destroy_media_packet(video_func->decode_mp);
		video_func->decode_mp = CP_NULL;
	}

	close_test_file(video_func);

	return 0;
}
/*�˳�ģ��*/
cp_int32_t exit_video_func(cp_video_func_t *video_func)
{
	return 0;
}
/*����ģ�����*/
cp_int32_t set_option_video_func(cp_video_func_t *video_func, cp_int32_t optname, const cp_void_t* optval)
{
	cp_module_info_t					*module_info;



	if (cp_player_func_set_option_stop_media_play & optname) {
		if (!optval) {
			return -1;
		}
		module_info = (cp_module_info_t *)optval;
		return stop_video_func_media_play(video_func, (cp_media_channel_info_t*)(module_info->data));
	}

	cp_module_log(error, video_func, "%s unsupport optname[%d]", __FUNCTION__, optname);
	return -1;
}

cp_int32_t get_option_video_func(cp_video_func_t *video_func, cp_int32_t optname, cp_void_t* optval)
{
	cp_media_channel_info_t					**tmp_mci = CP_NULL;



	if (cp_player_func_get_option_media_channel_info == optname) {
		if (!optval) {
			return -1;
		}
		tmp_mci = (cp_media_channel_info_t **)optval;

		*tmp_mci = &(video_func->mci);
		return 0;
	}

	cp_module_log(error, video_func, "%s unsupport optname[%d]", __FUNCTION__, optname);
	return -1;
}

#if 0
cp_int32_t listen_video_func(cp_socket_t *socket, cp_sockaddr_in *addr)
{
	return 0;
}

cp_int32_t connect_video_func(cp_socket_t *socket, cp_sockaddr_in *addr)
{
	return 0;
}

cp_int32_t read_s_video_func(cp_video_func_t *cp_s, const cp_buf_t *buf, cp_int32_t nread, cp_int32_t flags)
{
	return 0;
}

cp_int32_t write_s_video_func(cp_socket_t *socket, const cp_buf_t *buf, cp_int32_t nread, const cp_sockaddr_in *remote_addr, cp_int32_t flags)
{
	return 0;
}

cp_int32_t close_s_video_func(cp_socket_t *socket)
{
	return 0;
}
#endif

cp_int32_t connect_cb_video_func(cp_socket_t *socket, cp_int32_t status)
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

	//CP_SOCKET_MODULE_SET_CALLBACK_HANDLERS(socket, video_func);
	cp_read_socket(socket, buf, tmp_read_length, 0);
	return 0;
}

cp_int32_t close_cb_video_func(cp_socket_t *socket, cp_int32_t status)
{
	return 0;
}

cp_int32_t read_cb_video_func(cp_socket_t *socket, const cp_buf_t *buf, cp_int32_t nread, cp_int32_t status)
{
	cp_int32_t					ret_int = 0;
	cp_video_func_t*			tmp_video_func = CP_NULL;


	//����� ���ݲ���filter����
	if (!socket->data || !((cp_video_func_t*)(socket->data))->filter ||
		!((cp_video_func_t*)(socket->data))->filter->read_cb) {
		return -1;
	}

	((cp_video_func_t*)(socket->data))->filter->read_cb(socket, buf, nread, status);

	return ret_int;
}

cp_int32_t write_cb_video_func(cp_socket_t *socket, cp_int32_t status)
{
	return connect_cb_video_func(socket, status);
}

cp_int32_t error_cb_video_func(cp_socket_t *socket, cp_int32_t status)
{
	return 0;
}

cp_int32_t video_func_data_integrity
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

cp_int32_t video_func_process_socket_data(cp_socket_t *socket, const cp_buf_t *buf, cp_int32_t nread, cp_int32_t status)
{
	cp_session_t				*tmp_session;
	cp_session_manager_t		*tmp_sm = CP_NULL;
	cp_session_info_t			tmp_session_info = { 0, };
	cp_module_manager_info_t	tmp_mm_info = { 0, };
	cp_int32_t					ret_int = 0;



	//�ж������Ƿ������ȫ
	ret_int = video_func_data_integrity(socket, buf, nread, status);
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
* ��������: set_video_multicast_data_filter
*
* ����˵��: ����multicast socket
*
* ��    ��: cp_video_func_t * video_func			[in]����˵��
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
cp_int32_t set_video_multicast_data_filter(cp_video_func_t *video_func, cp_char_t *buf, cp_int32_t len)
{
	cp_module_t								*tmp_module = CP_NULL;
	cp_int32_t								ret_int = 0;
	cp_char_t								tmp_buf[CP_APP_DEFAULT_BUFFER_LENGTH] = { 0, };



	cp_memset(buf, 0, len);

	tmp_module = cp_manager_get_sub_module(video_func->manager->app,
		cp_player_manager_type_filter, cp_player_module_type_memh_filter);
	if (!tmp_module) {
		cp_snprintf(buf, len, "not found filter[memh]");
		return -1;
	}
	video_func->filter = (cp_filter_t *)tmp_module;
	CP_MODULE_UPDATE_SINGLE_HANDLER_AND_TYPE(video_func->filter, video_func->socket, read_cb, cp_socket_read_cb_handle);

	ret_int = set_video_memh_socket_data(video_func, tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH);
	if (ret_int) {
		cp_snprintf(buf, len, "%s", tmp_buf);
		return -2;
	}

	return 0;
}

/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: open_video_multicast_socket
*
* ����˵��: ����Ƶ�� socket
*
* ��    ��: cp_video_func_t * video_func						[in]����˵��
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
cp_int32_t open_video_multicast_socket(cp_video_func_t *video_func, cp_char_t *buf, cp_int32_t len)
{
	cp_int32_t							tmp_ret_int = 0;
	cp_char_t							tmp_buf[CP_APP_DEFAULT_BUFFER_LENGTH] = { 0, };
	cp_sockaddr_in						tmp_multicast_addr = { 0, };


	cp_memset(buf, 0, len);
	if (!video_func->mci.channel_info.multicast_info.port ||
		!cp_strlen(video_func->mci.channel_info.multicast_info.ip)) {
		cp_snprintf(buf, len, "url address [%s:%d] error.",
			video_func->mci.channel_info.multicast_info.ip,
			video_func->mci.channel_info.multicast_info.port);
		return -1;
	}
	//��
	video_func->socket = cp_create_socket(cp_socket_type_multicast);
	if (!video_func->socket) {
		cp_snprintf(buf, len, "cp_create_socket() error.");
		return -2;
	}

	CP_SOCKET_MODULE_SET_CALLBACK_HANDLERS(video_func->socket, video_func);
	tmp_ret_int = set_video_multicast_data_filter(video_func, tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH);
	if (tmp_ret_int) {
		cp_snprintf(buf, len, "set_video_multicast_data_filter() error. %s", tmp_buf);
		return -2;
	}

	cp_ip4_addr(video_func->mci.channel_info.multicast_info.ip,
		video_func->mci.channel_info.multicast_info.port, &tmp_multicast_addr);

	//����multicast����
	tmp_ret_int = cp_listen_socket(video_func->socket, &tmp_multicast_addr);
	if (tmp_ret_int) {
		cp_snprintf(buf, len, "cp_listen_socket() [%s:%d] error.",
			video_func->mci.channel_info.multicast_info.ip,
			video_func->mci.channel_info.multicast_info.port);
		return -2;
	}

	return 0;
}

/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: close_video_multicast_socket
*
* ����˵��: �ر��鲥
*
* ��    ��: cp_video_func_t * video_func						[in]����˵��
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
cp_int32_t close_video_multicast_socket(cp_video_func_t *video_func)
{
	if (video_func->socket) {
		cp_close_socket(video_func->socket);
		unset_video_memh_socket_data(video_func);
		cp_destroy_module(video_func->socket->manager, video_func->socket);
	}
	return 0;
}

/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: set_video_memh_socket_data
*
* ����˵��: ����memh socket����
*
* ��    ��: cp_video_func_t * video_func						[in]����˵��
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
cp_int32_t set_video_memh_socket_data(cp_video_func_t *video_func, cp_char_t *buf, cp_int32_t len)
{
	cp_memh_socket_data_t				*tmp_memh_socket_data = CP_NULL;



	if (!video_func || !video_func->socket) {
		cp_module_log(error, video_func, "set_video_memh_socket_data() error. video_func[%p] socket is null.",
			video_func);
		return -1;
	}
	//�� memh socket ����
	tmp_memh_socket_data = create_memh_socket_data(video_func->socket->pool);
	if (!tmp_memh_socket_data) {
		cp_module_log(error, video_func, "set_video_memh_socket_data() error. create_memh_socket_data() error.");
		return -2;
	}
	set_memh_socket_buffer_func(tmp_memh_socket_data, (cp_func_t*)video_func);
	//����memh socket data
	video_func->socket->data = tmp_memh_socket_data;

	return 0;
}

/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: unset_video_memh_socket_data
*
* ����˵��: ����memh socket����
*
* ��    ��: cp_video_func_t * video_func						[in]����˵��
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
cp_int32_t unset_video_memh_socket_data(cp_video_func_t *video_func)
{
	if (video_func->socket->data) {
		destroy_socket_data(video_func->socket->pool, video_func->socket->data);
		video_func->socket->data = CP_NULL;
	}
	return 0;
}

/*�����������ݻص�������*/
cp_int32_t video_func_codec_read_cb_handle(cp_video_func_t *video_func, cp_codec_callback_info_t *ccb_info_p, cp_media_packet_t *mp)
{
	if (!video_func) {
		return -1;
	}

	//��ʼ��������
	if (!set_video_dev_info(video_func, (cp_video_description_t *)mp->md_p)) {
		//������Ƶ����
		cp_write_module(video_func->dev, &mp, cp_sizeof(cp_media_packet_t**), 0);
	}

	return 0;
}

/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: video_func_thread_cb_proc
*
* ����˵��: ý�崦���߳�
*
* ��    ��: cp_video_func_t * video_func						[in]����˵��
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
void video_func_thread_cb_proc(cp_video_func_t *video_func)
{
	cp_int32_t				ret_int = 0;
	cp_buf_t				*tmp_buf_array[CP_VIDEO_FUNC_MEDIA_ARRAY_SIZE] = { 0, };
	cp_array_t				tmp_array = { 0, };
	cp_media_packet_t		*tmp_mp = CP_NULL;



	//��ʼ������
	cp_array_init(&tmp_array, tmp_buf_array, cp_sizeof(cp_buf_t*), CP_VIDEO_FUNC_MEDIA_ARRAY_SIZE);

	while (cp_true)
	{
		if (video_func->thread_status != cp_video_func_thread_status_start) {
			break;
		}

		//��ȡend��־��һ֡����
		ret_int = get_a_frame_data(video_func, &tmp_array);
		if (ret_int) {
			//cp_sleep_ns(0, 1000000);
			continue;
		}

		//����ָ��
		set_video_codec_info(video_func, &tmp_array);
		tmp_mp = merge_media_data(video_func, &tmp_array);
		if (tmp_mp) {
#if defined(CP_VIDEO_FILE_DEBUG)
			if (video_func->file) {
				fwrite(cp_buf_get_pos(&tmp_mp->buf[0]), 1, cp_buf_get_length(&tmp_mp->buf[0]), video_func->file);
			}
#endif
			ret_int = decode_media_data(video_func, tmp_mp);
			if (!ret_int) {
				play_media_data(video_func, video_func->decode_mp);
			}
		}
		//�������ݻ���
		//destroy_tmp_data(video_func, tmp_mp, &tmp_array);
		cp_array_clear(&tmp_array);
	}
}

/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: check_is_end
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
cp_bool_t check_is_end(cp_buf_t *buf)
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
* ��������: open_test_file
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
cp_bool_t open_test_file(cp_video_func_t *video_func)
{
#if defined(CP_VIDEO_FILE_DEBUG)
	cp_char_t									tmp_buf[CP_APP_DEFAULT_BUFFER_LENGTH] = { 0, };


	cp_snprintf(tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH, "%s_%d_%s",
		video_func->register_info.name,
		video_func->mci.channel_info.index,
		video_func->mci.media_info.id);

	video_func->file = fopen(tmp_buf, "wb");
#endif

	return cp_true;
}


/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: close_test_file
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
cp_bool_t close_test_file(cp_video_func_t *video_func)
{
#if defined(CP_AUDIO_FILE_DEBUG)

	if (video_func->file) {
		fclose(video_func->file);
		video_func->file = CP_NULL;
	}
#endif
	return cp_true;
}

//������Ҫ������Ƶ����ģ��
cp_module_t* create_video_codec_module(cp_player_t *player, cp_media_description_t *md, cp_int32_t manager_type, cp_int32_t module_type)
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
		cp_app_log(error, player, "create_video_codec_module() error. not found manager_type[%d] error.",
			manager_type);
		return CP_NULL;
	}
	//����һ������ģ��
	CP_MODULE_INFO_SET_TYPE(&tmp_codec_info, module_type);
	CP_CODEC_INFO_SET_MEDIA_DESCRIPTION(&tmp_codec_info, md);
	//�Ȳ���һ��ģ���Ƿ����
	tmp_module = cp_manager_get_module(tmp_manager, &tmp_codec_info);
	if (tmp_module) {
		cp_app_log(warn, player, "create_video_codec_module() warning. create module_type[%d] existed.",
			module_type);
		return CP_NULL;
	}
	//��������ʼ����
	tmp_module = cp_manager_create_module(tmp_manager, &tmp_codec_info);
	if (!tmp_module) {
		cp_app_log(error, player, "create_video_codec_module() error. create module_type[%d] error.",
			module_type);
		return CP_NULL;
	}
	//��ʼ��ģ��ʧ��
	ret_int = cp_init_module(tmp_module, &tmp_codec_info);
	if (ret_int) {
		//��ʼ��ʧ�ܣ�������ģ������
		cp_manager_destroy_module(tmp_manager, tmp_module);
		cp_app_log(error, player, "create_video_codec_module() error. init %s error.",
			print_module_register_info(&tmp_module->register_info, tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH));
		return CP_NULL;
	}
	//����ģ��ʧ��
	ret_int = cp_open_module(tmp_module, &tmp_codec_info);
	if (ret_int) {
		//��ʼ��ʧ�ܣ�������ģ������
		cp_manager_destroy_module(tmp_manager, tmp_module);
		cp_app_log(error, player, "create_video_codec_module() error. open %s error.",
			print_module_register_info(&tmp_module->register_info, tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH));
		return CP_NULL;
	}

	return tmp_module;
}

//������Ҫ������Ƶ����ģ��
cp_module_t* create_video_dev_module(cp_player_t *player, cp_dev_description_t *dd,
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
		cp_app_log(error, player, "create_video_dev_module() error. not found manager_type[%d] error.",
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
		cp_app_log(warn, player, "create_video_dev_module() warning. create module_type[%d] existed.",
			module_type);
		return CP_NULL;
	}
	//��������ʼ����
	tmp_module = cp_manager_create_module(tmp_manager, &tmp_dev_info);
	if (!tmp_module) {
		cp_app_log(error, player, "create_video_dev_module() error. create module_type[%d] error.",
			module_type);
		return CP_NULL;
	}
	//��ʼ��ģ��ʧ��
	ret_int = cp_init_module(tmp_module, &tmp_dev_info);
	if (ret_int) {
		//��ʼ��ʧ�ܣ�������ģ������
		cp_manager_destroy_module(tmp_manager, tmp_module);
		cp_app_log(error, player, "create_video_dev_module() error. init %s error.",
			print_module_register_info(&tmp_module->register_info, tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH));
		return CP_NULL;
	}
	//����ģ��ʧ��
	ret_int = cp_open_module(tmp_module, &tmp_dev_info);
	if (ret_int) {
		//��ʼ��ʧ�ܣ�������ģ������
		cp_manager_destroy_module(tmp_manager, tmp_module);
		cp_app_log(error, player, "create_video_dev_module() error. open %s error.",
			print_module_register_info(&tmp_module->register_info, tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH));
		return CP_NULL;
	}

	return tmp_module;
}

/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: set_video_codec_info
*
* ����˵��: ���ý�������Ϣ
*
* ��    ��: cp_video_func_t * video_func						[in]����˵��
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
cp_int32_t set_video_codec_info(cp_video_func_t *video_func, cp_array_t *ary)
{
	cp_uint32_t							i = 0;
	cp_buf_t							**tmp_buf = 0;
	gmp_gmph_bmh_t						*tmp_bmh = CP_NULL;
	gmp_gmph_memh_t						*tmp_memh = CP_NULL;
	cp_module_t							*tmp_codec_module = CP_NULL;



	if (!video_func || !ary) {
		return -1;
	}

	if (video_func->is_open_codec) {
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
			if (!video_func->is_open_codec && !video_func->codec &&
				(css_media_network_begin == tmp_memh->packet_type ||
				css_media_network_other == tmp_memh->packet_type ||
				css_media_network_end == tmp_memh->packet_type)) {
				//
				video_func->decode_md.md.encodec_type = tmp_memh->media_type;

				//��ʼ��������
				tmp_codec_module = create_video_codec_module((cp_player_t*)(video_func->manager->app),
					(cp_media_description_t *)&video_func->decode_md,
					cp_player_manager_type_codec, cp_player_module_type_ffmpeg_codec);
				if (!tmp_codec_module) {
					cp_module_log(error, video_func, "set_video_codec_info() error. create_video_codec_module() error.");
					return -2;
				}
				video_func->codec = (cp_codec_t *)tmp_codec_module;
				video_func->is_open_codec = cp_true;
				return 0;
			}
		}

		if (check_is_end((*tmp_buf))) {
			break;
		}
	}

	return -2;
}

/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: unset_codec_info
*
* ����˵��: ������Ƶ��������Ϣ
*
* ��    ��: cp_video_func_t * video_func						[in]����˵��
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
cp_int32_t unset_codec_info(cp_video_func_t *video_func)
{
	if (video_func->is_open_codec && video_func->codec) {
		//�رս�����
		cp_close_module(video_func->codec);
		//���ٽ�����
		cp_destroy_module(video_func->codec->manager, video_func->codec);
		//���ý���״̬
		video_func->is_open_codec = cp_true;
		video_func->codec = CP_NULL;
	}

	return 0;
}

//���ò�����Ϣ
cp_int32_t set_video_dev_info(cp_video_func_t *video_func, cp_video_description_t *vd)
{
	cp_module_t									*tmp_dev_module = CP_NULL;
	cp_player_info_t							*tmp_player_info = (cp_player_info_t *)(video_func->manager->app->app_info);
	cp_dev_video_description_t					tmp_vdd = { 0, };



	if (!video_func || !vd) {
		return -1;
	}

	if (video_func->dev) {
		return 0;
	}

	//��ʼ��������
	tmp_vdd.dd.type = cp_dev_description_type_video;
	tmp_vdd.width = tmp_player_info->device_info->hardware.resolution_width;
	tmp_vdd.height = tmp_player_info->device_info->hardware.resolution_height;
	tmp_vdd.fps = vd->fps;
	tmp_dev_module = create_video_dev_module((cp_player_t*)(video_func->manager->app),
		(cp_dev_description_t *)&tmp_vdd,
		(cp_media_description_t *)vd,
		cp_player_manager_type_dev, cp_player_module_type_sdl_dev);
	if (!tmp_dev_module) {
		cp_module_log(error, video_func, "set_video_dev_info() error. create_video_codec_module() error.");
		return -2;
	}
	video_func->dev = (cp_dev_t *)tmp_dev_module;

	return 0;
}

/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: unset_video_dev_info
*
* ����˵��: ������Ƶ������Ϣ
*
* ��    ��: cp_video_func_t * video_func						[in]����˵��
* ��    ��: cp_video_description_t * vd						[in]����˵��
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
cp_int32_t unset_video_dev_info(cp_video_func_t *video_func)
{
	if (video_func->dev) {
		//�رղ�����
		cp_close_module(video_func->dev);
		//���ٲ�����
		cp_destroy_module(video_func->dev->manager, video_func->dev);
		//���ò���״̬
		video_func->dev = CP_NULL;
	}
	return 0;
}

/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: merge_media_data
*
* ����˵��: ����ý������
*
* ��    ��: cp_video_func_t * video_func						[in]����˵��
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
cp_media_packet_t* merge_media_data(cp_video_func_t *video_func, cp_array_t *ary)
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

		if (check_is_end((*tmp_buf))) {
			break;
		}
	}

	if (tmp_total <= 0) {
		return CP_NULL;
	}

	//create media packet
	tmp_mp = create_media_packet(video_func->pool, tmp_total,
		cp_media_packet_type_data_and_timestamp);
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
			cp_buf_strcat(&tmp_mp->buf[0], cp_buf_get_pos((*tmp_buf)) + cp_sizeof(gmp_gmph_memh_t), tmp_memh->body_size);

			//�����ȡʱ��
			if ((css_media_network_begin == tmp_memh->packet_type ||
				css_media_network_other == tmp_memh->packet_type ||
				css_media_network_end == tmp_memh->packet_type)) {
				tmp_ts.tv_sec = tmp_memh->time_stamp_s;
				tmp_ts.tv_nsec = tmp_memh->time_stamp_ns;
			}
		}

		if (check_is_end((*tmp_buf))) {
			break;
		}
	}

	tmp_mp->ts = tmp_ts;
	return tmp_mp;
}

/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: get_a_frame_data
*
* ����˵��: ���������Ĺ�����Ϣ
*
* ��    ��: cp_video_func_t * video_func						[in]����˵��
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
cp_int32_t get_a_frame_data(cp_video_func_t *video_func, cp_array_t *ary)
{
	cp_buf_t				*tmp_buf = CP_NULL;


	while (cp_true)
	{
		//�����ȡ���ݾ�
		tmp_buf = pop_a_memh_socket_buffer(video_func->socket->data);
		if (!tmp_buf) {
			break;
		}

		cp_array_set_back(ary, &tmp_buf);
		if (check_is_end(tmp_buf)) {
			return 0;
		}
	}
	return -1;
}

/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: decode_media_data
*
* ����˵��: ����ý������
*
* ��    ��: cp_video_func_t * video_func						[in]����˵��
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
cp_int32_t decode_media_data(cp_video_func_t *video_func, cp_media_packet_t	*mp)
{
	if (!video_func || !mp || !video_func->codec) {
		return -1;
	}

	return cp_write_module(video_func->codec, &mp, cp_sizeof(cp_media_packet_t**), 0);
}

/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: play_media_data
*
* ����˵��: ����ý��
*
* ��    ��: cp_video_func_t * video_func						[in]����˵��
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
cp_int32_t play_media_data(cp_video_func_t *video_func, cp_media_packet_t *mp)
{
	cp_int32_t								tmp_ret_int = 0;



	if (!video_func || !mp) {
		return -1;
	}

	//��ȡ����������
	mp->md_p = (cp_media_description_t *)&video_func->decode_md;
	mp->type = cp_media_packet_type_data_and_timestamp;
	tmp_ret_int = cp_read_module(video_func->codec, &mp, cp_sizeof(cp_media_packet_t**), 0);
	if (!tmp_ret_int) {
		return -2;
	}
	return 0;
}

/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: stop_video_func_media_play
*
* ����˵��: ֹͣһ��ý�岥��
*
* ��    ��: cp_video_func_t * video_func						[in]����˵��
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
cp_int32_t stop_video_func_media_play(cp_video_func_t *video_func, cp_media_channel_info_t *mci)
{
	cp_int32_t							tmp_ret_int = 0;



	if (!video_func || !mci) {
		return -1;
	}

	//ɾ��ͨ����Ϣ
	tmp_ret_int = remove_media_channel_info(video_func, mci);
	if (tmp_ret_int) {
		cp_module_log(error, video_func, "open_video_func() error. remove_media_channel_info() error.");
		return -1;
	}

	//�������ͨ����ʹ���򷵻�
	if (video_func->cm.size > 0) {
		return 0;
	}

	//���û����ֹͣ
	close_video_func(video_func);

	//����ģ��
	cp_destroy_module(video_func->manager, video_func);

	return 0;
}

/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: insert_media_channel_info
*
* ����˵��: ���ý��ͨ��
*
* ��    ��: cp_video_func_t * video_func						[in]����˵��
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
cp_int32_t insert_media_channel_info(cp_video_func_t *video_func, cp_media_channel_info_t *mci)
{
	cp_channel_info_t					*tmp_chl_info = CP_NULL;
	cp_channel_t						*tmp_find_chl = CP_NULL;
	cp_channel_t						tmp_chl = { 0, };



	if (!video_func || !mci) {
		return -1;
	}

	//�����Ƿ��Ѿ�����
	tmp_find_chl = find_channel(&video_func->cm, mci->channel_info.index);
	if (tmp_find_chl) {
		cp_module_log(warn, video_func,
			"insert_media_channel_info() error, channel[%d] exist now!",
			mci->channel_info.index);
		return 0;
	}

	//����ý��ͨ��
	tmp_chl_info = cp_palloc(video_func->pool, cp_sizeof(cp_channel_info_t));
	if (!tmp_chl_info) {
		cp_module_log(error, video_func, "insert_media_channel_info() error, cp_palloc() make media channel information failed");
		return -1;
	}
	*tmp_chl_info = mci->channel_info;

	set_channel(&tmp_chl, mci->channel_info.index, mci->channel_info.play_session, (cp_module_t*)video_func, tmp_chl_info);
	insert_channel(&video_func->cm, &tmp_chl);

	return 0;
}

/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: remove_media_channel_info
*
* ����˵��: ɾ��ý��ͨ��
*
* ��    ��: cp_video_func_t * video_func						[in]����˵��
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
cp_int32_t remove_media_channel_info(cp_video_func_t *video_func, cp_media_channel_info_t *mci)
{
	cp_channel_info_t					*tmp_chl_info = CP_NULL;
	cp_channel_t						*tmp_chl = { 0, };



	tmp_chl = find_channel(&video_func->cm, mci->channel_info.index);
	if (!tmp_chl) {
		cp_module_log(error, video_func,
			"remove_media_channel_info() error, not found channel[%d]",
			mci->channel_info.index);
		return -1;
	}
	if (tmp_chl->data) {
		cp_pfree(video_func->pool, tmp_chl->data);
	}

	remove_channel(&video_func->cm, mci->channel_info.index);
	return 0;
}

/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: destroy_tmp_data
*
* ����˵��: ������������
*
* ��    ��: cp_video_func_t * video_func						[in]����˵��
* ��    ��: cp_media_packet_t * mp						[in]����˵��
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
cp_int32_t destroy_tmp_data(cp_video_func_t *video_func, cp_media_packet_t	*mp, cp_array_t *ary)
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
		destroy_a_memh_socket_buffer(video_func->socket->pool, video_func->socket->data, (*tmp_buf));
	}

	destroy_media_packet(mp);
	return 0;
}

/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: init_media_description_info
*
* ����˵��: ��ʼ��ý����Ϣ
*
* ��    ��: cp_video_func_t * video_func						[in]����˵��
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
cp_int32_t init_media_description_info(cp_video_func_t *video_func)
{
	if (!video_func) {
		return -1;
	}
	video_func->decode_md.md.type = cp_media_description_type_video;
	return 0;
}

/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: init_codec_callback_info
*
* ����˵��: ���������Ĺ�����Ϣ
*
* ��    ��: cp_video_func_t * video_func						[in]����˵��
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
cp_int32_t init_codec_callback_info(cp_video_func_t *video_func)
{
	cp_memset(&video_func->cc_info.handle, 0, cp_sizeof(cp_codec_callback_handle_t));
	video_func->cc_info.handle.read_cb = (cp_codec_general_cb_handle)video_func_codec_read_cb_handle;
	video_func->decode_mp->ccb_info_p = &video_func->cc_info;
	return 0;
}

/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: stop_thread_process
*
* ����˵��: ֹͣ�����߳�
*
* ��    ��: cp_video_func_t * video_func						[in]����˵��
*
* �� �� ֵ: cp_int32_t
*           0  : �ɹ�
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2016-12-14 16:38:27
******************************************************************************************************/
cp_int32_t stop_thread_process(cp_video_func_t *video_func)
{
	if (video_func->thread) {
		video_func->thread_status = cp_video_func_thread_status_stop;
		cp_thread_join(video_func->thread);
		cp_destroy_thread(video_func->thread);
		video_func->thread = CP_NULL;
	}
	return 0;
}