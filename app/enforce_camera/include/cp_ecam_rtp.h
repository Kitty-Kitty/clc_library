/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-12-26

Description:

**************************************************************************/

#ifndef _CP_ECAM_RTP_INCLUDE_H_
#define _CP_ECAM_RTP_INCLUDE_H_


#include"cp_core.h"
#include "cp_socket_core.h"
#include "cp_ecam_h264.h"



//#define CP_ECAM_USED_ORTP_LIBRARY											1
#define		CP_ECAM_USED_NATIVE_SOCKET										1


#define		CP_ECAM_CODEC_SEND_RTP											1


#if defined(CP_ECAM_USED_ORTP_LIBRARY)
#include "ortp/ortp.h"
#endif


//#define CP_ECAM_BIGENDIAN													1

#define CP_ECAM_RTP_VERSION													2
#define CP_ECAM_IPMAXLEN														20
#define CP_ECAM_UDP_MAX_SIZE													1500
#define CP_ECAM_RTP_FIXED_HEADER_SIZE										12
#define CP_ECAM_RTP_DEFAULT_JITTER_TIME										80				/*miliseconds*/
#define CP_ECAM_RTP_DEFAULT_MULTICAST_TTL									5				/*hops*/
#define CP_ECAM_RTP_DEFAULT_MULTICAST_LOOPBACK								0				/*false*/
#define CP_ECAM_RTP_DEFAULT_DSCP												0x00			/*best effort*/
#define CP_ECAM_RTP_PLOAD_TYPE												96				//H.264
#define CP_ECAM_RTP_MAX_PKT_LENGTH											1400
#define CP_ECAM_RTP_DEFAULT_TIMESTAMP_INCREMENT								90000/30		//(90000/25)



typedef	struct cp_ecam_rtp_header_s											cp_ecam_rtp_header_t;
typedef union cp_ecam_rtp_payload_s											cp_ecam_rtp_payload_u;
typedef	struct cp_ecam_rtp_session_s											cp_ecam_rtp_session_t;



typedef	enum cp_ecam_rtp_payload_type_enum									cp_ecam_rtp_payload_type_e;



#pragma pack(1)



/************************************************************************/
/* ����payload ����                                                     */
/************************************************************************/
enum cp_ecam_rtp_payload_type_enum
{
	cp_ecam_rtp_payload_type_h264
};


/************************************************************************/
/* ����rtp header��Ϣ                                                   */
/************************************************************************/
struct cp_ecam_rtp_header_s
{
#ifdef CP_ECAM_BIGENDIAN
	cp_uint16_t version : 2;
	cp_uint16_t padbit : 1;
	cp_uint16_t extbit : 1;
	cp_uint16_t cc : 4;
	cp_uint16_t markbit : 1;
	cp_uint16_t paytype : 7;
#else
	cp_uint16_t cc : 4;
	cp_uint16_t extbit : 1;
	cp_uint16_t padbit : 1;
	cp_uint16_t version : 2;
	cp_uint16_t paytype : 7;
	cp_uint16_t markbit : 1;
#endif
	cp_uint16_t seq_number;
	cp_uint32_t timestamp;
	cp_uint32_t ssrc;
	//cp_uint32_t csrc[16];
};




/************************************************************************/
/* ����payload����                                                       */
/************************************************************************/
union cp_ecam_rtp_payload_s
{
	cp_ecam_rtp_payload_h264_nalu_header_t		*h264_nalu;
};


/************************************************************************/
/* ����session����                                                      */
/************************************************************************/
struct cp_ecam_rtp_session_s
{
	cp_log_t							*logger;						//��־
	cp_pool_t							*pool;							//�ڴ��
	cp_ecam_rtp_header_t					*rtp_header;					//rtpͷ
	cp_ecam_rtp_payload_u				*payload;						//����
	cp_uchar_t							*data_buf;						//����
	cp_socket_t							*socket;						//����
 #if defined(CP_ECAM_USED_ORTP_LIBRARY)
	RtpSession							*rtp_session;					//��ʾrtp���ͻỰ
	SessionSet							*session_set;
#endif
	cp_int32_t							nav_socket;						//��������
	cp_int32_t							ts;								//��ʾ��ʼʱ��
	cp_ecam_rtp_payload_type_e			payload_type;					//��������
	cp_int32_t							mtu_size;						//������С
	cp_uint16_t							seq_number;						//���к�
	cp_sockaddr_in						remote_addr;					//Զ�̵�ַ
};

#pragma pack()


/************************************************************************/
/* rtp����api                                                            */
/************************************************************************/
cp_ecam_rtp_session_t* create_ecam_rtp_session(cp_pool_t *pool, cp_ecam_rtp_payload_type_e payload_type, cp_int32_t mtu_size);
cp_int32_t destroy_ecam_rtp_session(cp_ecam_rtp_session_t *rtp_session);

//����Զ�̵�ַ
cp_int32_t init_ecam_rtp_session(cp_ecam_rtp_session_t *rtp_session);
cp_int32_t ecam_rtp_session_set_logger(cp_ecam_rtp_session_t *rtp_session, cp_log_t *logger);
cp_int32_t ecam_rtp_session_set_remote_addr(cp_ecam_rtp_session_t *rtp_session, cp_socket_t *socket, cp_char_t *remote_ip, cp_int32_t port);
cp_int32_t ecam_rtp_session_set_ssrc(cp_ecam_rtp_session_t *rtp_session, cp_int32_t ssrc);
cp_int32_t exit_ecam_rtp_session(cp_ecam_rtp_session_t *rtp_session);

//����h264 rtp����
cp_int32_t  ecam_func_send_rtp_h264_cycle(cp_ecam_rtp_session_t *rtp_session, const cp_buf_t *buf, cp_int32_t nwrite);
cp_int32_t	ecam_func_send_rtp_h264(cp_ecam_rtp_session_t *rtp_session, const cp_buf_t *buf, cp_int32_t nwrite, cp_uint32_t ts);



#endif


