/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-12-26

Description:

**************************************************************************/
#include "cp_ecam_func_pro.h"



/*创建编码器*/
cp_module_t* create_video_codec_module(cp_ecam_func_t* ecam_func)
{
	cp_module_t									*tmp_module = CP_NULL;
	cp_module_manager_t							*tmp_manager = CP_NULL;
	cp_app_t									*tmp_app = ecam_func->manager->app;
	cp_module_manager_info_t					tmp_manager_info = { 0, };
	cp_module_info_t							tmp_module_info = { 0, };



	CP_MODULE_MANAGER_INFO_SET_TYPE(&tmp_manager_info, cp_ecam_manager_type_codec);

	//获取音频处理管理器
	tmp_manager = cp_get_manager(tmp_app, &tmp_manager_info);
	if (!tmp_manager) {
		cp_module_log(error, ecam_func,
			"create_video_codec_module() error. not found manager_type[%d] error.",
			cp_ecam_manager_type_codec);
		return CP_NULL;
	}

	//创建一个处理模块
	CP_MODULE_INFO_SET_TYPE(&tmp_module_info, cp_ecam_module_type_hi3516c_codec);

	//先查找一个模块是否存在
	tmp_module = cp_manager_get_module(tmp_manager, &tmp_module_info);
	if (tmp_module) {
		//如果存在则正常处理
		cp_module_log(error, ecam_func,
			"create_video_codec_module() warning. create module_type[%d] existed.",
			cp_ecam_module_type_hi3516c_codec);
		return tmp_module;
	}

	//不存在则开始创建
	tmp_module = cp_manager_create_module(tmp_manager, &tmp_module_info);
	if (!tmp_module) {
		cp_module_log(error, ecam_func,
			"create_video_codec_module() error. create module_type[%d] error.",
			cp_ecam_module_type_hi3516c_codec);
		return CP_NULL;
	}
	return tmp_module;
}

cp_int32_t init_video_codec_module(cp_ecam_func_t* ecam_func, cp_module_t* video_module)
{
	cp_int32_t									tmp_ret_int = 0;
	cp_module_info_t							tmp_module_info = { 0, };



	if (!ecam_func || !video_module) {
		return -1;
	}
	tmp_ret_int = cp_init_module(video_module, &tmp_module_info);
	if (tmp_ret_int) {
		cp_module_log(error, ecam_func,
			"init_video_codec_module() error. module[%p] error.",
			video_module);
		return -1;
	}
	return 0;
}

cp_int32_t start_video_codec_module(cp_ecam_func_t* ecam_func, cp_module_t* video_module)
{
	cp_int32_t									tmp_ret_int = 0;
	cp_module_info_t							tmp_module_info = { 0, };



	if (!ecam_func || !video_module) {
		return -1;
	}
	tmp_ret_int = cp_open_module(video_module, &tmp_module_info);
	if (tmp_ret_int) {
		cp_module_log(error, ecam_func,
			"start_video_codec_module() error. module[%p] error.",
			video_module);
		return -1;
	}
	return 0;
}

cp_int32_t stop_video_codec_module(cp_ecam_func_t* ecam_func, cp_module_t* video_module)
{
	cp_int32_t									tmp_ret_int = 0;
	cp_module_info_t							tmp_module_info = { 0, };



	if (!ecam_func || !video_module) {
		return -1;
	}
	tmp_ret_int = cp_close_module(video_module);
	if (tmp_ret_int) {
		cp_module_log(error, ecam_func,
			"stop_video_codec_module() error. module[%p] error.",
			video_module);
		return -1;
	}
	return 0;
}

cp_int32_t destroy_video_codec_module(cp_ecam_func_t* ecam_func, cp_module_t* video_module)
{
	cp_int32_t									tmp_ret_int = 0;
	cp_module_info_t							tmp_module_info = { 0, };



	if (!ecam_func || !video_module) {
		return -1;
	}
	tmp_ret_int = cp_destroy_module(video_module, &tmp_module_info);
	if (tmp_ret_int) {
		cp_module_log(error, ecam_func,
			"destroy_video_codec_module() error. module[%p] error.",
			video_module);
		return -1;
	}
	return 0;
}

cp_ecam_rtp_session_t *create_ecam_rtp_send_session(cp_ecam_func_t* ecam_func)
{
	cp_int32_t							tmp_ret_int = 0;
	cp_ecam_rtp_session_t			*tmp_ecam_rtp_session = CP_NULL;


	tmp_ecam_rtp_session = create_ecam_rtp_session(ecam_func->pool,
		cp_ecam_rtp_payload_type_h264, CP_ECAM_FUNC_RTP_MAX_PKT_LENGTH);
	if (!tmp_ecam_rtp_session) {
		cp_module_log(error, ecam_func,
			"create_ecam_rtp_send_session() error. create_ecam_rtp_session() error.");
		return CP_NULL;
	}
	ecam_rtp_session_set_logger(tmp_ecam_rtp_session, ecam_func->logger);

	tmp_ret_int = init_ecam_rtp_session(tmp_ecam_rtp_session);
	if (tmp_ret_int) {
		cp_module_log(error, ecam_func,
			"create_ecam_rtp_send_session() error. init_ecam_rtp_session() error.");
		return CP_NULL;
	}
	
	tmp_ecam_rtp_session->ts = ecam_func->ecam_conf.rtp_conf.ts;//timestamp increase
	ecam_rtp_session_set_remote_addr(tmp_ecam_rtp_session, ecam_func->rtp_socket,
		ecam_func->ecam_conf.rtp_conf.ip, ecam_func->ecam_conf.rtp_conf.port);
	ecam_rtp_session_set_ssrc(tmp_ecam_rtp_session, ecam_func->ecam_conf.rtp_conf.ssrc);

	return tmp_ecam_rtp_session;
}

cp_thread_t* create_video_process_thread(cp_ecam_func_t* ecam_func)
{
	cp_thread_t					*tmp_thread = CP_NULL;


	ecam_func->is_process_video = cp_true;
	tmp_thread = cp_create_thread(ecam_func->manager->app, video_process_proc, ecam_func);
	if (!tmp_thread) {
		cp_module_log(error, ecam_func, "cp_create_thread() error.");
		return CP_NULL;
	}
	return tmp_thread;
}

cp_void_t video_process_proc(cp_void_t *arg)
{
	cp_ecam_func_t					*tmp_ecam_func = (cp_ecam_func_t*)arg;
	cp_int32_t						tmp_ret_int = 0;
	cp_video_description_t			tmp_vd = { 0, };
	cp_media_packet_t				tmp_mp = { 0, };
	cp_codec_callback_info_t		tmp_cc_info = { 0, };
	cp_media_packet_t				*tmp_mp_p = &tmp_mp;




	//初始化接收数据
	tmp_cc_info.handle.read_cb = (cp_codec_general_cb_handle)video_process_proc_general_cb_handle;

	//表示获取0号通道媒体
	tmp_vd.type = cp_media_description_type_video;
	tmp_vd.channel = 0;

	tmp_mp.type = cp_media_packet_type_data_and_timestamp;
	tmp_mp.md_p = (cp_media_description_t *)&tmp_vd;
	tmp_mp.ccb_info_p = &tmp_cc_info;
	tmp_mp.orgin_module = (cp_module_t *)tmp_ecam_func;

	while (tmp_ecam_func->is_process_video)
	{
		tmp_ret_int = cp_read_module(tmp_ecam_func->video_codec, &tmp_mp_p, cp_sizeof(cp_media_packet_t*), 0);
		if (tmp_ret_int) {
			cp_sleep_ns(0, CP_ECAM_FUNC_VIDEO_PROCESS_DEFAULT_INTERVAL_NS);
			continue;
		}
	}
	return;
}

/*常规回调函数*/
cp_int32_t video_process_proc_general_cb_handle(cp_ecam_func_t* ecam_func,
	cp_codec_callback_info_t *ccb_info_p, cp_media_packet_t *mp)
{
#if defined(CP_ECAM_FUNC_SAVE_FILE)
	fwrite(cp_buf_get_pos(&mp->mp_buf.buf[0]), 1, cp_buf_get_length(&mp->mp_buf.buf[0]), ecam_func->file);
#endif

	ecam_func_send_rtp_h264_cycle(ecam_func->ecam_rtp_session, &mp->mp_buf.buf[0], cp_buf_get_length(&mp->mp_buf.buf[0]));
	//cp_sleep_ns(0, 200000);
// #endif
	return 0;
}

#if 0
int  video_process_proc_rtp_send(cp_ecam_func_t* ecam_func, char  *buffer, int  len)
{
	int							tmp_send_bytes = 0;
	uint32_t					valid_len = len - 4;
	unsigned char				NALU = buffer[4];



	if (!buffer || len < 4) {
		return 0;
	}

	//如果数据小于CP_ECAM_FUNC_RTP_MAX_PKT_LENGTH字节，直接发送：单一NAL单元模式
	if (valid_len <= CP_ECAM_FUNC_RTP_MAX_PKT_LENGTH)
	{
		tmp_send_bytes = rtp_session_send_with_ts(ecam_func->ecam_rtp_session->rtp_session,
			&buffer[4],
			valid_len,
			ecam_func->ecam_conf.rtp_conf.ts);
		return tmp_send_bytes;
	}
	else if (valid_len > CP_ECAM_FUNC_RTP_MAX_PKT_LENGTH)
	{
		//切分为很多个包发送，每个包前要对头进行处理，如第一个包
		valid_len -= 1;
		int k = 0, l = 0;
		k = valid_len / CP_ECAM_FUNC_RTP_MAX_PKT_LENGTH;
		l = valid_len%CP_ECAM_FUNC_RTP_MAX_PKT_LENGTH;
		int t = 0;
		int pos = 5;
		if (l != 0)
		{
			k = k + 1;
		}
		while (t < k)//||(t==k&&l>0))
		{
			if (t < (k - 1))//(t<k&&l!=0)||(t<(k-1))&&(l==0))//(0==t)||(t<k&&0!=l))
			{
				buffer[pos - 2] = (NALU & 0x60) | 28;
				buffer[pos - 1] = (NALU & 0x1f);
				if (0 == t)
				{
					buffer[pos - 1] |= 0x80;
				}
				tmp_send_bytes = rtp_session_send_with_ts(ecam_func->ecam_rtp_session->rtp_session,
					&buffer[pos - 2],
					CP_ECAM_FUNC_RTP_MAX_PKT_LENGTH + 2,
					ecam_func->ecam_conf.rtp_conf.ts);
				t++;
				pos += CP_ECAM_FUNC_RTP_MAX_PKT_LENGTH;
			}
			else //if((k==t&&l>0)||((t==k-1)&&l==0))
			{
				int tmp_send_len;
				if (l > 0)
				{
					tmp_send_len = valid_len - t*CP_ECAM_FUNC_RTP_MAX_PKT_LENGTH;
				}
				else
					tmp_send_len = CP_ECAM_FUNC_RTP_MAX_PKT_LENGTH;
				buffer[pos - 2] = (NALU & 0x60) | 28;
				buffer[pos - 1] = (NALU & 0x1f);
				buffer[pos - 1] |= 0x40;
				tmp_send_bytes = rtp_session_send_with_ts(ecam_func->ecam_rtp_session->rtp_session,
					&buffer[pos - 2],
					tmp_send_len + 2,
					ecam_func->ecam_conf.rtp_conf.ts);
				t++;
			}
		}
	}

	ecam_func->ecam_conf.rtp_conf.ts += CP_ECAM_FUNC_RTP_DEFAULT_TIMESTAMP_INCREMENT;//timestamp increase
	return  len;
}
#endif

cp_int32_t destroy_rtp_send_session(cp_ecam_func_t* ecam_func)
{
	ecam_func->is_process_video = cp_false;
	cp_thread_join(ecam_func->rtp_video_thread);
	cp_destroy_module(ecam_func->rtp_video_thread->manager, ecam_func->rtp_video_thread);

	exit_ecam_rtp_session(ecam_func->ecam_rtp_session);
	destroy_ecam_rtp_session(ecam_func->ecam_rtp_session);
	return 0;
}
