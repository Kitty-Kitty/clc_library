/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-12-28

Description:

**************************************************************************/
#if defined(__linux__)
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#endif


#include "cp_ipc_rtp.h"
#include "cp_ipc_core.h"
#include "cp_log.h"


//获取h264的信息
cp_inline cp_static cp_int32_t	ipc_func_h264_nal_info(const cp_buf_t *buf,
	cp_uint8_t *nal_flag_len, cp_uint8_t *nal_type, cp_uint8_t *flag_type, cp_bool_t *is_picture);

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: create_ipc_rtp_session
*
* 函数说明: 创建rtp_session
*
* 参    数: cp_pool_t * pool						[in]参数说明
* 参    数: cp_ipc_rtp_payload_type_e payload_type						[in]参数说明
* 参    数: cp_int32_t mtu_size						[in]参数说明
*
* 返 回 值: cp_ipc_rtp_session_t*
*           0  : 成功
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2016-12-28 11:27:04
******************************************************************************************************/
cp_ipc_rtp_session_t* create_ipc_rtp_session(cp_pool_t *pool, cp_ipc_rtp_payload_type_e payload_type, cp_int32_t mtu_size)
{
	cp_void_t										*tmp_p = CP_NULL;
	cp_ipc_rtp_session_t						*tmp_rtp_session = CP_NULL;
	cp_int32_t										tmp_len = 0;



	if (!pool || !mtu_size) {
		return CP_NULL;
	}
	if (cp_ipc_rtp_payload_type_h264 != payload_type) {
		return CP_NULL;
	}
	tmp_p = (cp_void_t *)cp_palloc(pool, cp_sizeof(cp_ipc_rtp_session_t) + mtu_size);
	if (!tmp_p) {
		return CP_NULL;
	}
	cp_memset(tmp_p, 0, cp_sizeof(cp_ipc_rtp_session_t) + mtu_size);
	tmp_rtp_session = (cp_ipc_rtp_session_t *)tmp_p;
	tmp_rtp_session->rtp_header = (cp_ipc_rtp_header_t *)(((cp_uchar_t*)tmp_rtp_session) + cp_sizeof(cp_ipc_rtp_session_t));
	tmp_rtp_session->payload = (cp_ipc_rtp_payload_u *)(((cp_uchar_t*)tmp_rtp_session->rtp_header) + cp_sizeof(cp_ipc_rtp_header_t));
	tmp_rtp_session->data_buf = ((cp_uchar_t*)tmp_rtp_session->payload) + cp_sizeof(cp_ipc_rtp_payload_h264_nalu_header_t);
	tmp_rtp_session->payload_type = payload_type;
	tmp_rtp_session->mtu_size = mtu_size;

	//为rtp负初值
	tmp_rtp_session->rtp_header->version = CP_IPC_RTP_VERSION;
	tmp_rtp_session->rtp_header->paytype = CP_IPC_RTP_PLOAD_TYPE;

	return tmp_rtp_session;
}
cp_int32_t destroy_ipc_rtp_session(cp_ipc_rtp_session_t *rtp_session)
{
	if (!rtp_session || !rtp_session->pool) {
		return -1;
	}

	cp_pfree(rtp_session->pool, rtp_session);
	return 0;
}


/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: init_ipc_rtp_session
*
* 函数说明: 初始化ipc_rtp_session
*
* 参    数: cp_ipc_rtp_session_t * rtp_session						[in]参数说明
*
* 返 回 值: cp_int32_t
*           0  : 成功
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2017-01-08 21:18:29
******************************************************************************************************/
cp_int32_t init_ipc_rtp_session(cp_ipc_rtp_session_t *rtp_session)
{
#if defined(CP_IPC_USED_ORTP_LIBRARY)
	RtpSession							*tmp_session = CP_NULL;
#endif


#if defined(CP_IPC_USED_NATIVE_SOCKET)
#else

	ortp_init();
	ortp_scheduler_init();
	//ortp_set_log_level_mask(ORTP_MESSAGE|ORTP_WARNING|ORTP_ERROR);

	tmp_session = rtp_session_new(RTP_SESSION_SENDONLY);
	if (!tmp_session) {
		cp_log_error(rtp_session->logger,
			"init_ipc_rtp_session() error. rtp_session_new() error.");
		return -1;
	}

	rtp_session_set_scheduling_mode(tmp_session, FALSE);
	rtp_session_set_blocking_mode(tmp_session, FALSE);
	rtp_session_set_connected_mode(tmp_session, FALSE);
	rtp_session_set_payload_type(tmp_session, CP_IPC_RTP_PLOAD_TYPE);

	rtp_session->rtp_session = tmp_session;
	rtp_session->session_set = session_set_new();

#endif
	return 0;
}

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: ipc_rtp_session_set_logger
*
* 函数说明: 设置logger
*
* 参    数: cp_ipc_rtp_session_t * rtp_session						[in]参数说明
* 参    数: cp_log_t * logger						[in]参数说明
*
* 返 回 值: cp_int32_t
*           0  : 成功
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2016-12-28 11:58:57
******************************************************************************************************/
cp_int32_t ipc_rtp_session_set_logger(cp_ipc_rtp_session_t *rtp_session, cp_log_t *logger)
{
	if (!rtp_session || !logger) {
		return -1;
	}
	rtp_session->logger = logger;
	return 0;
}

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: ipc_rtp_session_set_remote_addr
*
* 函数说明: 设置远程地址
*
* 参    数: cp_ipc_rtp_session_t * rtp_session						[in]参数说明
* 参    数: cp_socket_t * socket						[in]参数说明
* 参    数: cp_char_t * remote_ip						[in]参数说明
* 参    数: cp_int32_t port						[in]参数说明
*
* 返 回 值: cp_int32_t
*           0  : 成功
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2016-12-28 11:45:35
******************************************************************************************************/
cp_int32_t ipc_rtp_session_set_remote_addr(cp_ipc_rtp_session_t *rtp_session,
	cp_socket_t *in_socket, cp_char_t *remote_ip, cp_int32_t port)
{
	cp_int32_t							len = cp_sizeof(rtp_session->remote_addr);


	if (!rtp_session || !in_socket || !remote_ip) {
		return -1;
	}

	rtp_session->socket = in_socket;
	cp_ip4_addr(remote_ip, port, &rtp_session->remote_addr);

#if defined(CP_IPC_USED_NATIVE_SOCKET)
	rtp_session->remote_addr.sin_family = AF_INET;
	rtp_session->remote_addr.sin_port = htons(port);
	rtp_session->remote_addr.sin_addr.s_addr = inet_addr(remote_ip);
	rtp_session->nav_socket = socket(AF_INET, SOCK_DGRAM, 0);

	connect(rtp_session->nav_socket,
		(const struct sockaddr *)&rtp_session->remote_addr, len);//申请UDP套接字
#else
	rtp_session_set_remote_addr(rtp_session->rtp_session, remote_ip, port);
#endif
	return 0;

	return 0;
}


/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: ipc_rtp_session_set_ssrc
*
* 函数说明: 设置ssrc
*
* 参    数: cp_ipc_rtp_session_t * rtp_session						[in]参数说明
* 参    数: cp_int32_t ssrc						[in]参数说明
*
* 返 回 值: cp_int32_t
*           0  : 成功
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2016-12-28 11:46:17
******************************************************************************************************/
cp_int32_t ipc_rtp_session_set_ssrc(cp_ipc_rtp_session_t *rtp_session, cp_int32_t ssrc)
{
	cp_ipc_rtp_payload_h264_nalu_header_t		*tmp_h264_nalu = CP_NULL;



	if (!rtp_session || !rtp_session->rtp_header) {
		return -1;
	}

#if defined(CP_IPC_USED_NATIVE_SOCKET)
	rtp_session->rtp_header->ssrc = htonl(ssrc);
#else
	rtp_session_set_ssrc(rtp_session->rtp_session, ssrc);
#endif
	return 0;
}


/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: exit_ipc_rtp_session
*
* 函数说明: 描述方法的功能信息
*
* 参    数: cp_ipc_rtp_session_t * rtp_session						[in]参数说明
*
* 返 回 值: cp_int32_t
*           0  : 成功
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2017-01-08 21:23:50
******************************************************************************************************/
cp_int32_t exit_ipc_rtp_session(cp_ipc_rtp_session_t *rtp_session)
{
#if defined(CP_IPC_USED_ORTP_LIBRARY)
	rtp_session_destroy(rtp_session->rtp_session);
	ortp_exit();
	ortp_global_stats_display();
#endif

	return 0;
}

/*循环发送数据*/

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: ipc_func_send_rtp_h264_cycle
*
* 函数说明: 循环发送数据，主要解决一个buf内存在多个00000001的nalu数据包，这种数据必须循环处理
*
* 参    数: cp_ipc_rtp_session_t * rtp_session						[in]参数说明
* 参    数: const cp_buf_t * buf						[in]参数说明
* 参    数: cp_int32_t nwrite						[in]参数说明
* 参    数: cp_uint32_t ts						[in]参数说明
*
* 返 回 值: cp_int32_t
*           0  : 成功
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2016-12-28 22:00:33
******************************************************************************************************/
cp_int32_t  ipc_func_send_rtp_h264_cycle(cp_ipc_rtp_session_t *rtp_session, const cp_buf_t *buf, cp_int32_t nwrite)
{
	cp_buf_t						tmp_buf = { 0, };
	cp_buf_t						tmp_process_buf = { 0, };
	cp_uint8_t						tmp_nal_flag_len = 0;
	cp_uint8_t						tmp_nal_type = 0;
	cp_uint8_t						tmp_flag_type = 0;
	cp_uint32_t						tmp_ret_int = 0;
	cp_bool_t						tmp_is_picture = cp_false;
	cp_uchar_t						*pos = CP_NULL;



	tmp_buf = *buf;
	cp_buf_clear(&tmp_buf);
	cp_buf_position(&tmp_buf, nwrite);
	tmp_process_buf = tmp_buf;

	//设置起始位置，并跳flag长度进行处理，避免一直停留在00000001位置
	pos = cp_buf_get_pos(&tmp_buf);
	tmp_ret_int = ipc_func_h264_nal_info(&tmp_buf, &tmp_nal_flag_len,
		&tmp_nal_type, &tmp_flag_type, &tmp_is_picture);
	if (tmp_ret_int) {
		return -2;
	}
	pos += tmp_nal_flag_len;

	for (pos; pos < tmp_buf.last; pos++) {
		if (CP_IPC_RTP_H264_NAL_LONG_FLAG == *((cp_uint32_t*)pos) ||
			(0x00 == pos[0] && 0x00 == pos[1] && 0x01 == pos[2])) {
			tmp_process_buf.last = pos;

			tmp_is_picture = cp_false;
			tmp_ret_int = ipc_func_h264_nal_info(&tmp_process_buf, &tmp_nal_flag_len,
				&tmp_nal_type, &tmp_flag_type, &tmp_is_picture);
			if (tmp_ret_int) {
				continue;;
			}

			ipc_func_send_rtp_h264(rtp_session, &tmp_process_buf, cp_buf_get_length(&tmp_process_buf), rtp_session->ts);
			tmp_process_buf.pos = pos;
			pos += tmp_nal_flag_len;

			if (tmp_is_picture) {
				rtp_session->ts += CP_IPC_RTP_DEFAULT_TIMESTAMP_INCREMENT;
			}
		}
	}

	//结尾没有00000001,需要判断长度是否还有最后一个包
	if (tmp_buf.last - tmp_process_buf.pos > 0) {
		tmp_process_buf.last = tmp_buf.last;

		tmp_is_picture = cp_false;
		tmp_ret_int = ipc_func_h264_nal_info(&tmp_process_buf, &tmp_nal_flag_len,
			&tmp_nal_type, &tmp_flag_type, &tmp_is_picture);
		if (tmp_ret_int) {
			return 0;
		}

		ipc_func_send_rtp_h264(rtp_session, &tmp_process_buf, cp_buf_get_length(&tmp_process_buf), rtp_session->ts);

		if (tmp_is_picture) {
			rtp_session->ts += CP_IPC_RTP_DEFAULT_TIMESTAMP_INCREMENT;
		}
	}

	return 0;
}

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: ipc_func_send_rtp_h264
*
* 函数说明: 发送h264 rtp数据
*
* 参    数: cp_ipc_rtp_session_t * ipc_rtp_session						[in]参数说明
* 参    数: const cp_buf_t * buf						[in]参数说明
* 参    数: cp_int32_t nwrite						[in]参数说明
* 参    数: cp_uint32_t ts						[in]参数说明
*
* 返 回 值: cp_int32_t
*           0  : 成功
*         非 0  :失败
*
* 备    注:返回发送数据的长度
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2016-12-28 15:06:17
******************************************************************************************************/
cp_int32_t	ipc_func_send_rtp_h264(cp_ipc_rtp_session_t *ipc_rtp_session,
	const cp_buf_t *buf, cp_int32_t nwrite, cp_uint32_t ts)
{
	cp_int32_t					i = 0;
	cp_int32_t					tmp_ret_int = 0;
	cp_int32_t					tmp_max_packet_length = CP_IPC_RTP_MAX_PKT_LENGTH;
	cp_int32_t					tmp_send_length = 0;
	cp_int32_t					tmp_rtp_packet_length = 0;
	cp_int32_t					tmp_seq_num = 0;
	cp_uint8_t					tmp_nal_flag_len = 0;
	cp_uint8_t					tmp_nal_type = 0;
	cp_uint8_t					tmp_flag_type = 0;
	cp_uint8_t					tmp_offset = 0;
	cp_bool_t					tmp_is_picture = cp_false;
	cp_uchar_t					*tmp_buf = CP_NULL;
	cp_buf_t					tmp_rtp_buf = { 0, };
	cp_buf_t					tmp_current_buf = { 0, };
	cp_ipc_rtp_payload_h264_nalu_header_t			*tmp_h264_nalu = CP_NULL;
	cp_ipc_rtp_h264_fu_indicator_t					*tmp_h264_fu_indicator = CP_NULL;
	cp_ipc_rtp_h264_fu_header_t					*tmp_h264_fu_header = CP_NULL;



	if (!ipc_rtp_session || !buf || !nwrite) {
		return -1;
	}

	tmp_ret_int = ipc_func_h264_nal_info(buf, &tmp_nal_flag_len,
		&tmp_nal_type, &tmp_flag_type, &tmp_is_picture);
	if (tmp_ret_int) {
		return -2;
	}

	tmp_buf = cp_buf_get_pos(buf) + tmp_nal_flag_len;
	tmp_current_buf = *buf;
	tmp_current_buf.pos += (1 + tmp_nal_flag_len);
	tmp_max_packet_length = ipc_rtp_session->mtu_size;
	tmp_offset = cp_sizeof(cp_ipc_rtp_payload_h264_nalu_header_t) + cp_sizeof(cp_ipc_rtp_h264_fu_header_t);

	if (nwrite < tmp_max_packet_length) {
		//如果发的包小于mtu_size,则一次发子出
		ipc_rtp_session->rtp_header->seq_number = htons(++(ipc_rtp_session->seq_number) % UINT16_MAX);
		ipc_rtp_session->rtp_header->timestamp = htonl(ts);
		cp_memset(ipc_rtp_session->data_buf, 0, ipc_rtp_session->mtu_size - 14);

		//设置nalu内容
		tmp_h264_nalu = (cp_ipc_rtp_payload_h264_nalu_header_t*)ipc_rtp_session->payload;
		tmp_h264_nalu->f = (*tmp_buf & 0x80) >> 7;
		tmp_h264_nalu->nri = (*tmp_buf & 0x60) >> 5;
		tmp_h264_nalu->type = (*tmp_buf & 0x1f);
		//tmp_offset = cp_sizeof(cp_ipc_rtp_payload_h264_nalu_header_t);


		cp_memcpy(((cp_uchar_t*)ipc_rtp_session->payload) +
			cp_sizeof(cp_ipc_rtp_payload_h264_nalu_header_t),
			cp_buf_get_pos(&tmp_current_buf),
			cp_buf_get_length(&tmp_current_buf));
		tmp_rtp_packet_length = cp_sizeof(cp_ipc_rtp_header_t) + tmp_offset + cp_buf_get_length(&tmp_current_buf);

		cp_buf_assemble(&tmp_rtp_buf, ipc_rtp_session->rtp_header, tmp_rtp_packet_length);
		cp_buf_position(&tmp_rtp_buf, tmp_rtp_packet_length);

#if defined(CP_IPC_USED_NATIVE_SOCKET)
		send(ipc_rtp_session->nav_socket, cp_buf_get_pos(&tmp_rtp_buf), tmp_rtp_packet_length, 0);//发送rtp包
#else
#if defined(CP_IPC_USED_ORTP_LIBRARY)			
		// 		session_set_set(ipc_rtp_session->session_set, ipc_rtp_session->rtp_session);
		// 		session_set_select(NULL, ipc_rtp_session->session_set, NULL);
		// 		if (session_set_is_set(ipc_rtp_session->session_set, ipc_rtp_session->rtp_session)) {
		tmp_ret_int = rtp_session_send_with_ts(ipc_rtp_session->rtp_session,
			cp_buf_get_pos(&tmp_rtp_buf) + cp_sizeof(cp_ipc_rtp_header_t),
			tmp_rtp_packet_length - cp_sizeof(cp_ipc_rtp_header_t),
			ts);
		// 		}
#else
		tmp_ret_int = cp_write_socket(ipc_rtp_session->socket, &tmp_rtp_buf,
			tmp_rtp_packet_length, &(ipc_rtp_session->remote_addr), 0);
		if (tmp_ret_int) {
			cp_log_error(ipc_rtp_session->logger, "send rtp to [%p] failed.", ipc_rtp_session);
			return 0;
		}
#endif
#endif
		//cp_sleep_ns(0, 200000);
		return (cp_sizeof(cp_ipc_rtp_header_t) + cp_buf_get_length(buf));
	}
	else {
		tmp_send_length = tmp_max_packet_length;

		ipc_rtp_session->rtp_header->timestamp = htonl(ts);

		cp_buf_assemble(&tmp_rtp_buf, ipc_rtp_session->rtp_header, tmp_rtp_packet_length);
		cp_buf_position(&tmp_rtp_buf, tmp_rtp_packet_length);

		for (; cp_buf_get_length(&tmp_current_buf) > 0; tmp_current_buf.pos += tmp_send_length) {
			//设置rtp头信息
			ipc_rtp_session->rtp_header->seq_number = htons(++(ipc_rtp_session->seq_number) % UINT16_MAX);
			cp_memset(ipc_rtp_session->data_buf, 0, ipc_rtp_session->mtu_size - 14);
			//设置h264相关内容
			tmp_h264_fu_indicator = (cp_ipc_rtp_h264_fu_indicator_t*)ipc_rtp_session->payload;
			tmp_h264_fu_indicator->f = (*tmp_buf & 0x80) >> 7;
			tmp_h264_fu_indicator->nri = (*tmp_buf & 0x60) >> 5;
			tmp_h264_fu_indicator->type = 28;

			tmp_h264_fu_header = (cp_ipc_rtp_h264_fu_header_t *)((cp_uchar_t*)tmp_h264_fu_indicator + 1);
			tmp_h264_fu_header->s = 1;
			tmp_h264_fu_header->e = 0;
			tmp_h264_fu_header->r = 0;
			tmp_h264_fu_header->type = *tmp_buf & 0x1f;


			//计算发送数据长度
			tmp_send_length = cp_buf_get_length(&tmp_current_buf) > tmp_max_packet_length ? tmp_max_packet_length : cp_buf_get_length(&tmp_current_buf);

			if (1 == ++tmp_seq_num) {
				//这里表示第一个包
				//tmp_send_length -= 1;
				tmp_h264_fu_header->s = 1;
				tmp_h264_fu_header->e = 0;
				tmp_h264_fu_header->r = 0;
			}
			else {
				if (tmp_send_length == tmp_max_packet_length) {
					//表示中间包
					tmp_h264_fu_header->s = 0;
					tmp_h264_fu_header->e = 0;
					tmp_h264_fu_header->r = 0;
				}
				else {
					tmp_h264_fu_header->s = 0;
					tmp_h264_fu_header->e = 1;
					tmp_h264_fu_header->r = 0;
				}
			}

			tmp_rtp_packet_length = cp_sizeof(cp_ipc_rtp_header_t) + tmp_offset + tmp_send_length;

			cp_memcpy(((cp_uchar_t*)ipc_rtp_session->payload) + tmp_offset,
				cp_buf_get_pos(&tmp_current_buf),
				tmp_send_length);

			cp_buf_clear(&tmp_rtp_buf);
			cp_buf_position(&tmp_rtp_buf, tmp_rtp_packet_length);

#if defined(CP_IPC_USED_NATIVE_SOCKET)
			send(ipc_rtp_session->nav_socket, cp_buf_get_pos(&tmp_rtp_buf), tmp_rtp_packet_length, 0);//发送rtp包
#else
#if defined(CP_IPC_USED_ORTP_LIBRARY)
			// 			session_set_set(ipc_rtp_session->session_set, ipc_rtp_session->rtp_session);
			// 			session_set_select(NULL, ipc_rtp_session->session_set, NULL);
			// 			if (session_set_is_set(ipc_rtp_session->session_set, ipc_rtp_session->rtp_session)) {
			tmp_ret_int = rtp_session_send_with_ts(ipc_rtp_session->rtp_session,
				cp_buf_get_pos(&tmp_rtp_buf) + cp_sizeof(cp_ipc_rtp_header_t),
				tmp_rtp_packet_length - cp_sizeof(cp_ipc_rtp_header_t),
				ts);
			// 			}
#else
			tmp_ret_int = cp_write_socket(ipc_rtp_session->socket, &tmp_rtp_buf,
				tmp_rtp_packet_length, &(ipc_rtp_session->remote_addr), 0);
			if (tmp_ret_int) {
				cp_log_error(ipc_rtp_session->logger, "send rtp to [%p] failed.", ipc_rtp_session);
				//return 0;
			}
#endif
#endif
			//cp_sleep_ns(0, 200000);
		}
	}

	return 0;
}

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: ipc_func_h264_nal_info
*
* 函数说明: 获取h264的信息
*
* 参    数: const cp_buf_t * buf						[in]参数说明
* 参    数: cp_uint8_t * nal_flag_len						[in]参数说明
* 参    数: cp_uint8_t * nal_type						[in]参数说明
* 参    数: cp_uint8_t * flag_type						[in]参数说明
* 参    数: cp_bool_t * is_picture						[in]参数说明
*
* 返 回 值: cp_int32_t
*           0  : 成功
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2016-12-28 13:53:22
******************************************************************************************************/
cp_int32_t	ipc_func_h264_nal_info(const cp_buf_t *buf, cp_uint8_t *nal_flag_len,
	cp_uint8_t *nal_type, cp_uint8_t *flag_type, cp_bool_t *is_picture)
{
	cp_uchar_t								*tmp_buf = CP_NULL;



	if (!buf) {
		return -1;
	}

	if (cp_buf_get_length(buf) < CP_IPC_RTP_H264_NAL_MIN_LENGTH) {
		return -2;
	}

	tmp_buf = cp_buf_get_pos(buf);
	*nal_flag_len = 0;
	*is_picture = cp_false;

	//更新帧信息来决定需要更新时间的方式
	if (0x00 == tmp_buf[0] && 0x00 == tmp_buf[1] && 0x01 == tmp_buf[2])	{
		*nal_flag_len = 3;
	}
	else if (CP_IPC_RTP_H264_NAL_LONG_FLAG == *((cp_uint32_t*)tmp_buf)) {
		*nal_flag_len = 4;
	}

	*nal_type = tmp_buf[*nal_flag_len] & 0x1f;
	*flag_type = tmp_buf[*nal_flag_len + 1] & 0x80;

	if (CP_IPC_RTP_H264NT_NAL < *nal_type &&
		CP_IPC_RTP_H264NT_SEI > *nal_type && *flag_type > 0)				//每个图像打时间戳
	{
		//表示为图像帧数据
		*is_picture = cp_true;
	}
	return 0;
}




