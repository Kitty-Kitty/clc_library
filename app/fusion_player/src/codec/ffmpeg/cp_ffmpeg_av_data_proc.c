/*******************************************************************************
*
*Copyright:novigo
*
*File name: cp_ffmpeg_av_data_proc.c
*
*Author:fangzhenmu@novigo.com.cn
*
*Version: 1.0
*
*Date:2017/08/06
*
*Description: create (cp_ffmpeg_av_data_proc.c)
*
*Others:
*
*History:
*******************************************************************************/
#include "cp_ffmpeg_av_data_proc.h"




/*******************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: create_ffmpeg_av_data_proc
*
* ����ȫ��: create_ffmpeg_av_data_proc
*
* ��������: public 
*
* ����˵��: ����file info��Ϣ
*
* ��    ��: cp_ffmpeg_av_codec_t * ffmpeg_av_codec						[in/out]����˵��
*
* �� �� ֵ: cp_int32_t
*           0  : �ɹ�
*         ��0  : ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2017-8-6 16:07:08
********************************************************************************/
cp_int32_t create_ffmpeg_av_data_proc(cp_ffmpeg_av_codec_t *ffmpeg_av_codec)
{
	return 0;
}

/*******************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: init_ffmpeg_av_data_proc
*
* ����ȫ��: init_ffmpeg_av_data_proc
*
* ��������: public 
*
* ����˵��: ��ʼ��file info��Ϣ
*
* ��    ��: cp_ffmpeg_av_codec_t * ffmpeg_av_codec						[in/out]����˵��
*
* �� �� ֵ: cp_int32_t
*           0  : �ɹ�
*         ��0  : ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2017-8-6 16:07:18
********************************************************************************/
cp_int32_t init_ffmpeg_av_data_proc(cp_ffmpeg_av_codec_t *ffmpeg_av_codec)
{
	return 0;
}

/*******************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: open_ffmpeg_av_data_proc
*
* ����ȫ��: open_ffmpeg_av_data_proc
*
* ��������: public 
*
* ����˵��: ��file info��Ϣ
*
* ��    ��: cp_ffmpeg_av_codec_t * ffmpeg_av_codec						[in/out]����˵��
* ��    ��: cp_media_description_t * md						[in/out]����˵��
*
* �� �� ֵ: cp_int32_t
*           0  : �ɹ�
*         ��0  : ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2017-8-6 16:07:27
********************************************************************************/
cp_int32_t open_ffmpeg_av_data_proc(cp_ffmpeg_av_codec_t *ffmpeg_av_codec, cp_media_description_t *md)
{
	return open_ffmpeg_av_codec_data(ffmpeg_av_codec, md);
}

/*******************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: read_ffmpeg_av_data_stream
*
* ����ȫ��: read_ffmpeg_av_data_stream
*
* ��������: public 
*
* ����˵��: ��ȡģ�����ݣ�flagΪ��ȡģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��
*
* ��    ��: cp_ffmpeg_av_codec_t * ffmpeg_av_codec						[in/out]����˵��
* ��    ��: cp_uchar_t * * buf						[in/out]����˵��
* ��    ��: cp_int32_t len						[in/out]����˵��
* ��    ��: cp_int32_t flag						[in/out]����˵��
*
* �� �� ֵ: cp_int32_t
*           0  : �ɹ�
*         ��0  : ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2017-8-6 16:07:46
********************************************************************************/
cp_int32_t read_ffmpeg_av_data_stream(cp_ffmpeg_av_codec_t *ffmpeg_av_codec,
	cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag)
{
	int								ret_int = 0;
	cp_media_packet_t				*tmp_mp = CP_NULL;
	AVFrame							*tmp_av_frame = CP_NULL;



	if (!buf || !*buf || !len) {
		return -1;
	}

	//ת��ý�����ݣ���У�����ݺϷ���
	tmp_mp = *((cp_media_packet_t**)buf);
	if (cp_media_packet_type_data_and_timestamp != tmp_mp->type) {
		cp_ffmepg_av_codec_log(error, ffmpeg_av_codec, 
			"unsupport media packet type[%d].", tmp_mp->type);
		return -2;
	}
	tmp_av_frame = &ffmpeg_av_codec->decoded_frame;


#if 0

	ret_int = avcodec_receive_frame(ffmpeg_av_codec->codec_context, tmp_av_frame);
	if (ret_int < 0 && ret_int != AVERROR_EOF) {
		//set_ffmpeg_av_codec_error_info(ffmpeg_av_codec, ret_int);
		//cp_ffmepg_av_codec_log(error, ffmpeg_av_codec, "%s", ffmpeg_av_codec->error_text);
		ret_int = -1;
		return ret_int;
	}
	else {
		ffmpeg_av_codec->error_no = 0;
	}

	switch (tmp_mp->md_p->type) {
		case cp_media_description_type_general:
		{
			cp_ffmepg_av_codec_log(error, ffmpeg_av_codec, 
				"unsupport media description type[%d].", tmp_mp->md_p->type);
			return -1;
		}
		break;
		case cp_media_description_type_video:
		{
			//��Ƶ����
			ret_int = read_ffmpeg_video_data(ffmpeg_av_codec, ffmpeg_av_codec->codec_context,
				tmp_av_frame/*&ffmpeg_av_codec->decoded_frame*/, tmp_mp, len, flag);
			return ret_int;
		}
		break;
		case cp_media_description_type_audio:
		{
			//��Ƶ����
			ret_int = read_ffmpeg_audio_data(ffmpeg_av_codec, ffmpeg_av_codec->codec_context,
				tmp_av_frame/*&ffmpeg_av_codec->decoded_frame*/, tmp_mp, len, flag);
		}
		break;
		default:
		{
			cp_ffmepg_av_codec_log(error, ffmpeg_av_codec,
				"unsupport media description type[%d].", tmp_mp->md_p->type);
			ret_int = -3;
		}
		break;
	}
#endif

	while (cp_true) {
		ret_int = avcodec_receive_frame(ffmpeg_av_codec->codec_context, tmp_av_frame);
		if (ret_int < 0 && ret_int != AVERROR_EOF) {
			//set_ffmpeg_av_codec_error_info(ffmpeg_av_codec, ret_int);
			//cp_ffmepg_av_codec_log(error, ffmpeg_av_codec, "%s", ffmpeg_av_codec->error_text);
			ret_int = -1;
			break;
		}
		else {
			ffmpeg_av_codec->error_no = 0;
		}

		switch (tmp_mp->md_p->type) {
			case cp_media_description_type_general:
			{
				cp_ffmepg_av_codec_log(error, ffmpeg_av_codec, 
					"unsupport media description type[%d].", tmp_mp->md_p->type);
				return -1;
			}
			break;
			case cp_media_description_type_video:
			{
				//��Ƶ����
				ret_int = read_ffmpeg_video_data(ffmpeg_av_codec, ffmpeg_av_codec->codec_context,
					tmp_av_frame/*&ffmpeg_av_codec->decoded_frame*/, tmp_mp, len, flag);
				break;
			}
			break;
			case cp_media_description_type_audio:
			{
				//��Ƶ����
				ret_int = read_ffmpeg_audio_data(ffmpeg_av_codec, ffmpeg_av_codec->codec_context,
					tmp_av_frame/*&ffmpeg_av_codec->decoded_frame*/, tmp_mp, len, flag);
			}
			break;
			default:
			{
				cp_ffmepg_av_codec_log(error, ffmpeg_av_codec, 
					"unsupport media description type[%d].", tmp_mp->md_p->type);
				ret_int = -3;
			}
			break;
		}
	}

	return ret_int;
}

/*******************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: write_ffmpeg_av_data_stream
*
* ����ȫ��: write_ffmpeg_av_data_stream
*
* ��������: public 
*
* ����˵��: дģ�����ݣ�flagΪдģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��
*
* ��    ��: cp_ffmpeg_av_codec_t * ffmpeg_av_codec						[in/out]����˵��
* ��    ��: const cp_uchar_t * * buf						[in/out]����˵��
* ��    ��: cp_int32_t len						[in/out]����˵��
* ��    ��: cp_int32_t flag						[in/out]����˵��
*
* �� �� ֵ: cp_int32_t
*           0  : �ɹ�
*         ��0  : ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2017-8-6 16:08:44
********************************************************************************/
cp_int32_t write_ffmpeg_av_data_stream(cp_ffmpeg_av_codec_t *ffmpeg_av_codec,
	const cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag)
{
	int								ret_int = 0;
	cp_media_packet_t				*tmp_mp = CP_NULL;
	AVPacket						tmp_pkt = { 0, };



	if (!buf || !*buf || !len) {
		return -1;
	}

	//ת��ý�����ݣ���У�����ݺϷ���
	tmp_mp = *((cp_media_packet_t**)buf);
	if (cp_media_packet_type_data_and_timestamp != tmp_mp->type) {
		return -2;
	}

	av_init_packet(&ffmpeg_av_codec->avpkt);
	if (cp_media_description_type_audio == ffmpeg_av_codec->md.type) {
		//�������probe�����ԭ���ǣ�mp3����ʱ����head missing,
		//���ǲ���test�е�av_read_frame()���ǳɹ���
		if (ffmpeg_av_codec->audio_info->probe &&
			(ffmpeg_av_codec->audio_info->probe->status >= cp_ffmepg_av_probe_status_unprobe &&
			ffmpeg_av_codec->audio_info->probe->status <= cp_ffmepg_av_probe_status_start)) {
			ret_int = read_frame_by_probe_info(&ffmpeg_av_codec->avpkt, ffmpeg_av_codec, buf, len, flag);
			if (ret_int) {
				cp_ffmepg_av_codec_log(error, ffmpeg_av_codec, "read_frame_by_probe_info() error.");
			}
		}
		else {
			//������Ƶ����
			ffmpeg_av_codec->avpkt.data = cp_buf_get_pos(&tmp_mp->mp_buf.buf[0]);
			ffmpeg_av_codec->avpkt.size = cp_buf_get_length(&tmp_mp->mp_buf.buf[0]);
		}
	}
	else {
		//������Ƶ����
		ffmpeg_av_codec->avpkt.data = cp_buf_get_pos(&tmp_mp->mp_buf.buf[0]);
		ffmpeg_av_codec->avpkt.size = cp_buf_get_length(&tmp_mp->mp_buf.buf[0]);
	}

	ret_int = avcodec_send_packet(ffmpeg_av_codec->codec_context, &ffmpeg_av_codec->avpkt);
	if (ret_int < 0 && ret_int != AVERROR(EAGAIN) && ret_int != AVERROR_EOF) {
		set_ffmpeg_av_codec_error_info(ffmpeg_av_codec, ret_int);
		cp_ffmepg_av_codec_log(error, ffmpeg_av_codec, "%s", ffmpeg_av_codec->error_text);

		if (cp_media_description_type_audio == ffmpeg_av_codec->md.type) {
			proc_decode_failed_data(ffmpeg_av_codec, buf, len, flag);
		}

		return -1;
	}
	else {
		proc_decode_successed_data(ffmpeg_av_codec, buf, len, flag);
	}

	return 0;
}

/*******************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: close_ffmpeg_av_data_proc
*
* ����ȫ��: close_ffmpeg_av_data_proc
*
* ��������: public 
*
* ����˵��: �ر�file info��Ϣ
*
* ��    ��: cp_ffmpeg_av_codec_t * ffmpeg_av_codec						[in/out]����˵��
*
* �� �� ֵ: cp_int32_t
*           0  : �ɹ�
*         ��0  : ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2017-8-6 16:08:54
********************************************************************************/
cp_int32_t close_ffmpeg_av_data_proc(cp_ffmpeg_av_codec_t *ffmpeg_av_codec)
{
	close_test_file(ffmpeg_av_codec);
	unset_ffmpeg_av_audio_convert_context_info(ffmpeg_av_codec);
	destroy_ffmpeg_buf_info(ffmpeg_av_codec);

	if (ffmpeg_av_codec->codec_context) {
		avcodec_close(ffmpeg_av_codec->codec_context);
		avcodec_free_context(&ffmpeg_av_codec->codec_context);
	}

	return 0;
}

/*******************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: exit_ffmpeg_av_data_proc
*
* ����ȫ��: exit_ffmpeg_av_data_proc
*
* ��������: public 
*
* ����˵��: �˳�file info��Ϣ
*
* ��    ��: cp_ffmpeg_av_codec_t * ffmpeg_av_codec						[in/out]����˵��
*
* �� �� ֵ: cp_int32_t
*           0  : �ɹ�
*         ��0  : ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2017-8-6 16:09:04
********************************************************************************/
cp_int32_t exit_ffmpeg_av_data_proc(cp_ffmpeg_av_codec_t *ffmpeg_av_codec)
{
	int								ret_int = 0;



	//�˳�media probe
	ret_int = cp_ffmpeg_av_codec_exit_media_probe(ffmpeg_av_codec);
	if (ret_int) {
		cp_ffmepg_av_codec_log(error, ffmpeg_av_codec,
			"cp_ffmpeg_av_codec_exit_media_probe() error.");
		return -1;
	}

	if (ffmpeg_av_codec->format_ctx) {
		avformat_free_context(ffmpeg_av_codec->format_ctx);
		ffmpeg_av_codec->format_ctx = CP_NULL;
	}

	return 0;
}

/*******************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: destroy_ffmpeg_av_data_proc
*
* ����ȫ��: destroy_ffmpeg_av_data_proc
*
* ��������: public 
*
* ����˵��: ����file info
*
* ��    ��: cp_ffmpeg_av_codec_t * ffmpeg_av_codec						[in/out]����˵��
*
* �� �� ֵ: cp_int32_t
*           0  : �ɹ�
*         ��0  : ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2017-8-6 16:09:13
********************************************************************************/
cp_int32_t destroy_ffmpeg_av_data_proc(cp_ffmpeg_av_codec_t *ffmpeg_av_codec)
{
	return 0;
}




/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: open_ffmpeg_av_codec_data
*
* ����˵��: ����ffmepg av��������
*
* ��    ��: cp_ffmpeg_av_codec_t * ffmpeg_av_codec						[in]����˵��
* ��    ��: cp_media_description_t * md						[in]����˵��
*
* �� �� ֵ: cp_int32_t
*           0  : �ɹ�
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2016-12-22 11:07:37
******************************************************************************************************/
cp_int32_t open_ffmpeg_av_codec_data(cp_ffmpeg_av_codec_t *ffmpeg_av_codec, cp_media_description_t *md)
{
	cp_int32_t									tmp_ret_int = 0;
	cp_ffmpeg_av_codec_conf_t					*tmp_codec_conf = CP_NULL;
	cp_ffmpeg_av_codec_audio_channel_layout_t	*tmp_ffmpeg_channel_layout = CP_NULL;
	cp_audio_description_t						*tmp_ad = CP_NULL;



	if (!ffmpeg_av_codec) {
		return -1;
	}

	if (ffmpeg_av_codec->codec) {
		cp_ffmepg_av_codec_log(error, ffmpeg_av_codec,
			"open_ffmpeg_av_data_proc() warning. repeat operation.");
		return 0;
	}

	tmp_ret_int = init_media_codec_info(ffmpeg_av_codec, md);
	if (tmp_ret_int) {
		cp_ffmepg_av_codec_log(error, ffmpeg_av_codec,
			"init_media_codec_info() error.");
		return -1;
	}

	tmp_codec_conf = get_codec_info(md->encodec_type);
	//tmp_codec_conf = get_codec_info(cp_media_type_audio_mp3);
	if (!tmp_codec_conf) {
		cp_ffmepg_av_codec_log(error, ffmpeg_av_codec,
			"open_ffmpeg_av_data_proc() error. not found ffmpeg av codec information for css type[%d]",
			md->encodec_type);
		return -1;
	}

	//avcodec register
	//avcodec_register_all();
	av_register_all();

	ffmpeg_av_codec->codec = avcodec_find_decoder(tmp_codec_conf->ffmpeg_codec_type);
	if (!ffmpeg_av_codec->codec) {
		cp_ffmepg_av_codec_log(error, ffmpeg_av_codec, 
			"open_ffmpeg_av_data_proc() error. codec not found");
		return -2;
	}
	ffmpeg_av_codec->codec_context = avcodec_alloc_context3(ffmpeg_av_codec->codec);
	if (!ffmpeg_av_codec->codec_context) {
		cp_ffmepg_av_codec_log(error, ffmpeg_av_codec, 
			"open_ffmpeg_av_data_proc() error. could not allocate audio codec context");
		return -3;
	}
	switch (md->type)
	{
		case cp_media_description_type_audio:
		{
			tmp_ad = (cp_audio_description_t*)md;

			tmp_ffmpeg_channel_layout = get_ffmpeg_audio_channel_layout_info(tmp_ad->channel_layout);
			if (!tmp_ffmpeg_channel_layout) {
				cp_ffmepg_av_codec_log(error, ffmpeg_av_codec,
					"open_ffmpeg_av_data_proc() error. get_ffmpeg_audio_channel_layout_info() error. unsupport cp_audio_channel_layout[%d]",
					tmp_ad->channel_layout);
				//return -4;
				ffmpeg_av_codec->codec_context->channels = CP_FFMPEG_AV_CODEC_DEFAULT_CHANNELS;
			}
			else {
				ffmpeg_av_codec->codec_context->channels = av_get_channel_layout_nb_channels(tmp_ffmpeg_channel_layout->ffmpeg_audio_channel_layout_type);
			}

			ffmpeg_av_codec->codec_context->sample_rate = tmp_ad->sample_rate;
			ffmpeg_av_codec->codec_context->bit_rate = tmp_ad->bit_rate;
			ffmpeg_av_codec->codec_context->sample_fmt = AV_SAMPLE_FMT_S16;
		}
		break;
		case cp_media_description_type_video:
			break;
		default:
			break;
	}

	/* open it */
	tmp_ret_int = avcodec_open2(ffmpeg_av_codec->codec_context, ffmpeg_av_codec->codec, NULL);
	if (tmp_ret_int < 0) {
		set_ffmpeg_av_codec_error_info(ffmpeg_av_codec, tmp_ret_int);
		cp_ffmepg_av_codec_log(error, ffmpeg_av_codec,
			"open_ffmpeg_av_data_proc() error. could not open codec! %s",
			ffmpeg_av_codec->error_text);
		return -4;
	}

	av_init_packet(&ffmpeg_av_codec->avpkt);
	ffmpeg_av_codec->css_av_type = md->encodec_type;

	cp_ffmepg_av_codec_log(notice, ffmpeg_av_codec, 
		"init ffmpeg library version[%d] successed.", avformat_version());

	open_test_file(ffmpeg_av_codec);

	return 0;
}

/*******************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: close_ffmpeg_av_codec_data
*
* ����ȫ��: close_ffmpeg_av_codec_data
*
* ��������: public 
*
* ����˵��: �رս�������Ϣ
*
* ��    ��: cp_ffmpeg_av_codec_t * ffmpeg_av_codec						[in/out]����˵��
*
* �� �� ֵ: cp_int32_t
*           0  : �ɹ�
*         ��0  : ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2017-8-6 16:20:59
********************************************************************************/
cp_int32_t close_ffmpeg_av_codec_data(cp_ffmpeg_av_codec_t *ffmpeg_av_codec)
{
	return 0;
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
cp_bool_t open_test_file(cp_ffmpeg_av_codec_t *ffmpeg_av_codec)
{
#if defined(CP_FFMPEG_AV_CODEC_FILE_DEBUG)
	cp_char_t									tmp_buf[CP_APP_DEFAULT_BUFFER_LENGTH] = { 0, };


	cp_snprintf(tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH, "%s_%d",
		ffmpeg_av_codec->register_info.name,
		ffmpeg_av_codec->codec->type);

	ffmpeg_av_codec->file = fopen(tmp_buf, "wb");
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
* ��    ��: cp_audio_func_t * ffmpeg_av_codec						[in]����˵��
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
cp_bool_t close_test_file(cp_ffmpeg_av_codec_t *ffmpeg_av_codec)
{
#if defined(CP_FFMPEG_AV_CODEC_FILE_DEBUG)

	if (ffmpeg_av_codec->file) {
		fclose(ffmpeg_av_codec->file);
		ffmpeg_av_codec->file = CP_NULL;
	}
#endif
	return cp_true;
}


