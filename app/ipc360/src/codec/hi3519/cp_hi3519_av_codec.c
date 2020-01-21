/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/
#include "cp_hi3519_av_codec.h"
#include "cp_third_party.h"
#include "cp_include.h"
#include "css_status.h"


#ifndef PIX_FMT_YUV420P
#define PIX_FMT_YUV420P	AV_PIX_FMT_YUV420P
#endif


/*ģ�鴴���ӿڣ���ʾ����һ��ģ��*/
cp_int32_t init_hi3519_av_codec(cp_hi3519_av_codec_t *hi3519_av_codec, const cp_hi3519_av_codec_info_t *hi3519_av_codec_info);
/*ģ������нӿڣ���ģ��init֮�󣬻ᱻ����*/
cp_int32_t open_hi3519_av_codec(cp_hi3519_av_codec_t *hi3519_av_codec, const cp_hi3519_av_codec_info_t *hi3519_av_codec_info);
/*��ȡģ�����ݣ�flagΪ��ȡģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��*/
cp_int32_t read_hi3519_av_codec(cp_hi3519_av_codec_t *hi3519_av_codec, cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag);
/*дģ�����ݣ�flagΪдģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��*/
cp_int32_t write_hi3519_av_codec(cp_hi3519_av_codec_t *hi3519_av_codec, const cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag);
/*�ر�ģ��*/
cp_int32_t close_hi3519_av_codec(cp_hi3519_av_codec_t *hi3519_av_codec);
/*�˳�ģ��*/
cp_int32_t exit_hi3519_av_codec(cp_hi3519_av_codec_t *hi3519_av_codec);
/*����ģ�����*/
cp_int32_t set_option_hi3519_av_codec(cp_hi3519_av_codec_t *hi3519_av_codec, cp_int32_t optname, const cp_void_t* optval);
cp_int32_t get_option_hi3519_av_codec(cp_hi3519_av_codec_t *hi3519_av_codec, cp_int32_t optname, cp_void_t* optval);




/*����һ��ģ��*/
cp_hi3519_av_codec_t* create_hi3519_av_codec(cp_module_register_t *register_info, cp_codec_manager_t *manager, cp_hi3519_av_codec_info_t *info)
{
	cp_int32_t							ret_int = 0;
	cp_hi3519_av_codec_t				*tmp_module = CP_NULL;
	cp_pool_info_t						tmp_pool_info = { 0, };


	if (!register_info || !manager || !info) {
		return CP_NULL;
	}

	tmp_module = cp_malloc_module(manager, cp_hi3519_av_codec_t, &tmp_pool_info);
	if (!tmp_module) {
		return CP_NULL;
	}
	CP_MODULE_SET_HANDLERS(tmp_module, hi3519_av_codec);
	return tmp_module;
}
/*�ͷ�ģ��*/
cp_int32_t destroy_hi3519_av_codec(cp_codec_manager_t *manager, cp_hi3519_av_codec_t* hi3519_av_codec)
{
	if (!manager || !hi3519_av_codec) {
		return -1;
	}
	cp_free_module(hi3519_av_codec);
	return 0;
}

/*ģ�鴴���ӿڣ���ʾ����һ��ģ��*/
cp_int32_t init_hi3519_av_codec(cp_hi3519_av_codec_t *hi3519_av_codec,
	const cp_hi3519_av_codec_info_t *hi3519_av_codec_info)
{
	cp_int32_t						tmp_ret_int = 0;



	//��ȡ�����ļ�
	tmp_ret_int = hi3519_av_codec_parse_configure((cp_module_t*)hi3519_av_codec, &hi3519_av_codec->hacc);
	if (tmp_ret_int) {
		cp_module_log(error, hi3519_av_codec, "hi3519_av_codec_parse_configure() error.");
		return -1;
	}

	//����������Ϣ
	tmp_ret_int = create_hi3519_av_codec_conf(hi3519_av_codec, hi3519_av_codec->av_conf);
	if (tmp_ret_int) {
		cp_module_log(error, hi3519_av_codec, "create_hi3519_av_codec_conf() error.");
		return -1;
	}

	//��ʼ��������Ϣ
	tmp_ret_int = hi3519_av_init_info(hi3519_av_codec, hi3519_av_codec->av_conf);
	if (tmp_ret_int) {
		cp_module_log(error, hi3519_av_codec, "hi3519_av_init_info() error.");
		return -1;
	}

	cp_module_log(notice, hi3519_av_codec, "init() successed.");
	return 0;
}

/*ģ������нӿڣ���ģ��init֮�󣬻ᱻ����*/
cp_int32_t open_hi3519_av_codec(cp_hi3519_av_codec_t *hi3519_av_codec,
	const cp_hi3519_av_codec_info_t *hi3519_av_codec_info)
{
	cp_int32_t					tmp_ret_int = 0;


	/*����hi3519 info �豸*/
	tmp_ret_int = start_hi3519_av_info(hi3519_av_codec, hi3519_av_codec->av_conf);
	if (tmp_ret_int) {
		cp_module_log(error, hi3519_av_codec, "start_hi3519_av_info() error.");
		return -1;
	}
	cp_module_log(notice, hi3519_av_codec, "start_hi3519_av_info() successed.");

#if defined(CP_HI3519_AV_CODEC_FILE_DEBUG)
	if (!hi3519_av_codec->file) {
		hi3519_av_codec->file = fopen(CP_HI3519_AV_CODEC_VIDEO_DEMO_FILE_PATH, "wb");
	}
#endif

#if defined(CP_HI3519_AV_CODEC_FILE_DEMO)
	cp_void_t				*tmp_data = CP_NULL;


	/*��ʾ�򿪲����õ��ļ�*/
	hi3519_av_codec->video_file = fopen(CP_HI3519_AV_CODEC_VIDEO_FILE_PATH, "rb");
	if (!hi3519_av_codec->video_file) {
		cp_module_log(error, hi3519_av_codec,
			"start_hi3519_av_get_stream() error. open file[%s] failed!",
			CP_HI3519_AV_CODEC_VIDEO_FILE_PATH);
		return -1;
	}
	tmp_data = cp_palloc(hi3519_av_codec->pool, CP_HI3519_AV_CODEC_VIDEO_BUFFER_LENGTH);
	if (!tmp_data) {
		cp_module_log(error, hi3519_av_codec,
			"start_hi3519_av_get_stream() error. create buffer failed!");
		return -1;
	}
	cp_buf_assemble(&hi3519_av_codec->data_buf, tmp_data, CP_HI3519_AV_CODEC_VIDEO_BUFFER_LENGTH);

	hi3519_av_codec->rtp_sd = create_rtp_socket_data(hi3519_av_codec->pool);
	if (!hi3519_av_codec->rtp_sd) {
		cp_module_log(error, hi3519_av_codec,
			"create_rtp_socket_data() socket_data[%d] failed!");
		return -1;
	}

#endif
	cp_module_log(notice, hi3519_av_codec, "open() successed.");
	return 0;
}

//����ͨ���ļ���ȡ���ݵķ�ʽ
int hi3519_test_read_video_file(cp_hi3519_av_codec_t * hi3519_av_codec)
{
	cp_int32_t				i = 0;
	cp_int32_t				tmp_index = 0;
	cp_int32_t				tmp_flag_len = 0;
	cp_bool_t				tmp_is_flag = cp_false;
	cp_int32_t				tmp_last_len = 0;
	cp_int32_t				tmp_packet_num = 4;
	cp_char_t				tmp_data_buf[1024] = { 0, };
	cp_int32_t				ret_int;
	cp_buf_t				*tmp_buf = CP_NULL;



#if defined(CP_HI3519_AV_CODEC_FILE_DEMO)

	tmp_last_len = cp_buf_get_free_size(&hi3519_av_codec->data_buf);

	//ret_int = fread(tmp_data_buf, 1, 1024, hi3519_av_codec->video_file);
	ret_int = fread(hi3519_av_codec->data_buf.last, 1, tmp_last_len, hi3519_av_codec->video_file);
	if (ret_int > 0) {
		cp_buf_position(&hi3519_av_codec->data_buf, ret_int);
	}
	else {
		fseek(hi3519_av_codec->video_file, 0, SEEK_SET);
	}

	// 	tmp_buf = create_a_rtp_socket_buffer(hi3519_av_codec->pool, hi3519_av_codec->rtp_sd, (ret_int));
	// 	if (!tmp_buf) {
	// 		return 0;
	// 	}
	// 	cp_buf_strcat(tmp_buf, (void *)((hi3519_av_codec->data_buf.pos)),
	// 		ret_int);
	// 	push_a_rtp_socket_buffer(hi3519_av_codec->rtp_sd, tmp_buf);
	//#if 0
	if (cp_buf_get_length(&hi3519_av_codec->data_buf) > 0) {
		for (i = 0; i < cp_buf_get_length(&hi3519_av_codec->data_buf); i++) {
			if ((hi3519_av_codec->data_buf.pos[i] == 0x00 &&
				hi3519_av_codec->data_buf.pos[i + 1] == 0x00 &&
				hi3519_av_codec->data_buf.pos[i + 2] == 0x00 &&
				hi3519_av_codec->data_buf.pos[i + 3] == 0x01
				)) {
				tmp_is_flag = cp_true;
				if (tmp_flag_len <= 0) {
					tmp_flag_len = 4;
				}
			}
			else {
				if ((hi3519_av_codec->data_buf.pos[i] == 0x00 &&
					hi3519_av_codec->data_buf.pos[i + 1] == 0x00 &&
					hi3519_av_codec->data_buf.pos[i + 2] == 0x01)){
					tmp_is_flag = cp_true;
					if (tmp_flag_len <= 0) {
						tmp_flag_len = 3;
					}
				}
			}

			if (tmp_is_flag) {
				++tmp_index;
				tmp_is_flag = cp_false;
				if (tmp_packet_num != tmp_index) {
					//��һ����־λ
					i += 2;
				}

				if (tmp_packet_num == tmp_index) {
					//�ڶ�����־λ
					tmp_flag_len = 0;

					tmp_buf = create_a_rtp_socket_buffer(hi3519_av_codec->pool, hi3519_av_codec->rtp_sd, (i - tmp_flag_len));
					if (!tmp_buf) {
						continue;
					}
					cp_buf_strcat(tmp_buf, (void *)((hi3519_av_codec->data_buf.pos + tmp_flag_len)),
						(i - tmp_flag_len));
					push_a_rtp_socket_buffer(hi3519_av_codec->rtp_sd, tmp_buf);


					tmp_last_len = cp_buf_get_length(&hi3519_av_codec->data_buf) - i;
					break;
				}
			}
		}
	}
	memmove(hi3519_av_codec->data_buf.start, hi3519_av_codec->data_buf.pos + i, tmp_last_len);
	cp_buf_clear(&hi3519_av_codec->data_buf);
	cp_buf_position(&hi3519_av_codec->data_buf, tmp_last_len);
#endif
	//#endif
	return ret_int;
}

/*��ȡģ�����ݣ�flagΪ��ȡģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��*/
cp_int32_t read_hi3519_av_codec(cp_hi3519_av_codec_t *hi3519_av_codec,
	cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag)
{
	int								ret_int = 0;
	cp_media_packet_t				*tmp_mp = CP_NULL;
	cp_buf_t						*tmp_buf = CP_NULL;
	cp_hi3519_av_venc_info_t		*tmp_venc_info = CP_NULL;
	cp_rtp_socket_data_t			*tmp_rtp_sd = CP_NULL;
	cp_char_t						tmp_file_name[CP_APP_DEFAULT_STRING_LENGTH] = { 0, };


	if (!buf || !*buf || !len) {
		return -1;
	}

	//ת��ý�����ݣ���У�����ݺϷ���
	tmp_mp = *((cp_media_packet_t**)buf);
	if (cp_media_packet_type_data_and_timestamp != tmp_mp->type) {
		cp_module_log(error, hi3519_av_codec, "unsupport media packet type[%d].", tmp_mp->type);
		return -2;
	}

	//
	if (tmp_mp->md_p->type != cp_media_description_type_video) {
		cp_module_log(error, hi3519_av_codec,
			"unsupport media description type[%d].", tmp_mp->md_p->type);
		return -2;
	}

#if defined(CP_HI3519_AV_CODEC_FILE_DEMO)
	ret_int = hi3519_test_read_video_file(hi3519_av_codec);
	tmp_rtp_sd = hi3519_av_codec->rtp_sd;
#else
	if (tmp_mp->md_p->channel < 0 || 
		tmp_mp->md_p->channel >= cp_ary_size(hi3519_av_codec->av_conf->venc_list)) {
		cp_module_log(error, hi3519_av_codec,
			"not found venc channel[%d].", tmp_mp->md_p->channel);
		return -3;
	}

	tmp_venc_info = &(hi3519_av_codec->av_conf->venc_list[tmp_mp->md_p->channel]);
	if (!tmp_venc_info->is_enc) {
		cp_module_log(error, hi3519_av_codec,
			"venc channel[%d] stopped.", tmp_mp->md_p->channel);
		return -4;
	}
	tmp_rtp_sd = tmp_venc_info->rtp_sd;
#endif
	tmp_buf = pop_a_rtp_socket_buffer(tmp_rtp_sd);
	if (!tmp_buf) {
		return -5;
	}
	else {
		cp_buf_assemble(&tmp_mp->mp_buf.buf[0], cp_buf_get_pos(tmp_buf), cp_buf_get_length(tmp_buf));
		cp_buf_position(&tmp_mp->mp_buf.buf[0], cp_buf_get_length(tmp_buf));

		if (tmp_mp->ccb_info_p) {
			tmp_mp->ccb_info_p->status_info.status = 0;
		}
	}

#if defined(CP_HI3519_AV_CODEC_FILE_DEBUG)
	// 	FILE							*tmp_file = CP_NULL;

	if (hi3519_av_codec->file && cp_buf_get_length(&tmp_mp->mp_buf.buf[0]) > 0) {
		fwrite(cp_buf_get_pos(&tmp_mp->mp_buf.buf[0]), 1, cp_buf_get_length(&tmp_mp->mp_buf.buf[0]), hi3519_av_codec->file);
	}

	// 	cp_snprintf(tmp_file_name, CP_APP_DEFAULT_STRING_LENGTH, "vedio_packet_%d.h264", (hi3519_av_codec->index)++);
	// 	tmp_file = fopen(tmp_file_name, "wb");
	// 	if (tmp_file) {
	// 		fwrite(cp_buf_get_pos(&tmp_mp->mp_buf.buf[0]), 1, cp_buf_get_length(&tmp_mp->mp_buf.buf[0]), tmp_file);
	// 		fclose(tmp_file);
	// 	}
#endif

	//���ﴦ��ͬ������
	if (tmp_mp->ccb_info_p) {
		//�������ûص�����
		tmp_mp->ccb_info_p->module = (cp_module_t *)hi3519_av_codec;
		tmp_mp->ccb_info_p->buf = (cp_uchar_t**)&tmp_mp;
		tmp_mp->ccb_info_p->len = len;
		tmp_mp->ccb_info_p->flag = flag;

		//������ڻص�������ֱ�Ӵ���
		if (tmp_mp->ccb_info_p->handle.read_cb) {
			ret_int = tmp_mp->ccb_info_p->handle.read_cb(tmp_mp->orgin_module, tmp_mp->ccb_info_p, tmp_mp);
			//return ret_int;
		}
	}

	//�ͷ�����
	if (tmp_buf) {
		destroy_a_rtp_socket_buffer(hi3519_av_codec->pool, tmp_rtp_sd, tmp_buf);
	}

	return 0;
}

/*дģ�����ݣ�flagΪдģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��*/
cp_int32_t write_hi3519_av_codec(cp_hi3519_av_codec_t *hi3519_av_codec,
	const cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag)
{
	return 0;
}

/*�ر�ģ��*/
cp_int32_t close_hi3519_av_codec(cp_hi3519_av_codec_t *hi3519_av_codec)
{
	cp_int32_t					tmp_ret_int = 0;



	/*ֹͣhi3519 �豸*/
	tmp_ret_int = stop_hi3519_av_info(hi3519_av_codec, hi3519_av_codec->av_conf);
	if (tmp_ret_int) {
		cp_module_log(error, hi3519_av_codec, "stop_hi3519_av_info() error.");
		return -1;
	}

	/*����hi3519 ��Դ*/
	hi3519_av_system_destroy(hi3519_av_codec, hi3519_av_codec->av_conf);

#if defined(CP_HI3519_AV_CODEC_FILE_DEBUG)
	if (hi3519_av_codec->file) {
		fclose(hi3519_av_codec->file);
	}
#endif

#if defined(CP_HI3519_AV_CODEC_FILE_DEMO)
	if (hi3519_av_codec->video_file) {
		fclose(hi3519_av_codec->video_file);
	}
#endif

	return 0;
}

/*�˳�ģ��*/
cp_int32_t exit_hi3519_av_codec(cp_hi3519_av_codec_t *hi3519_av_codec)
{
	cp_int32_t					tmp_ret_int = 0;


	/*ֹͣhi3519 vi �豸*/
	tmp_ret_int = hi3519_av_system_destroy(hi3519_av_codec, hi3519_av_codec->av_conf);
	if (tmp_ret_int) {
		cp_module_log(error, hi3519_av_codec, "hi3519_av_system_destroy() error.");
		return -1;
	}

	/*��ʾ����conf��Ϣ*/
	tmp_ret_int = destroy_hi3519_av_codec_conf(hi3519_av_codec);
	if (tmp_ret_int) {
		cp_module_log(error, hi3519_av_codec, "destroy_hi3519_av_codec_conf() error.");
		return -1;
	}
	return 0;
}

/*����ģ�����*/
cp_int32_t set_option_hi3519_av_codec(cp_hi3519_av_codec_t *hi3519_av_codec, cp_int32_t optname, const cp_void_t* optval)
{
	if (!hi3519_av_codec || !optval) {
		return -1;
	}

	if (cp_ipc_codec_set_option_rtp_session == optname) {
		hi3519_av_codec->rtp_session = (cp_ipc_rtp_session_t*)optval;
		cp_module_log(notice, hi3519_av_codec, "set rtp session successed");
		return 0;
	}
	cp_module_log(notice, hi3519_av_codec, "set_option_hi3519_av_codec() failed");

	return -2;
}

cp_int32_t get_option_hi3519_av_codec(cp_hi3519_av_codec_t *hi3519_av_codec, cp_int32_t optname, cp_void_t* optval)
{
	return 0;
}
