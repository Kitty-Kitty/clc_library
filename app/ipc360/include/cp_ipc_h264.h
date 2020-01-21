/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-12-28

Description:

**************************************************************************/

#ifndef _CP_IPC_H264_INCLUDE_H_
#define _CP_IPC_H264_INCLUDE_H_


#include "cp_core.h"



#define	CP_IPC_RTP_H264_NAL_SHORT_FLAG												0x010000
#define	CP_IPC_RTP_H264_NAL_LONG_FLAG												0x01000000
#define	CP_IPC_RTP_H264_NAL_MIN_LENGTH												6						//��ʾ����֡�����־����С���ݳ���



typedef	struct cp_ipc_rtp_payload_h264_nalu_header_s								cp_ipc_rtp_payload_h264_nalu_header_t;
typedef struct cp_ipc_rtp_h264_fu_indicator_s										cp_ipc_rtp_h264_fu_indicator_t;
typedef struct cp_ipc_rtp_h264_fu_header_s											cp_ipc_rtp_h264_fu_header_t;


#pragma pack(1)


// H.264 NAL type
typedef enum cp_ipc_rtp_h264_nal_type_enum
{
	CP_IPC_RTP_H264NT_NAL = 0,						//
	CP_IPC_RTP_H264NT_SLICE,						//��IDRͼ��ı�������(P ֡)
	CP_IPC_RTP_H264NT_SLICE_DPA,					//�����������ݷָ��A
	CP_IPC_RTP_H264NT_SLICE_DPB,					//�����������ݷָ��B
	CP_IPC_RTP_H264NT_SLICE_DPC,					//�����������ݷָ��C
	CP_IPC_RTP_H264NT_SLICE_IDR,					//IDRͼ��ı�������(I ֡)
	CP_IPC_RTP_H264NT_SEI,							//������ǿ��Ϣ��Ԫ
	CP_IPC_RTP_H264NT_SPS,							//���вο���
	CP_IPC_RTP_H264NT_PPS,							//ͼ��ο���
	CP_IPC_RTP_H264NT_AUD,							//�ֽ��
	CP_IPC_RTP_H264NT_EOSEQ,						//���н���
	CP_IPC_RTP_H264NT_EOSTREAM,					//��������
	CP_IPC_RTP_H264NT_FILL,						//���
	//13..23											//����
	//24..31											//δʹ��
}cp_ipc_rtp_h264_nal_type;


/************************************************************************/
/* ����nalu header��Ϣ                                                  */
/************************************************************************/
struct cp_ipc_rtp_payload_h264_nalu_header_s {
	cp_uint8_t			type : 5;						/* bit: 0~4 */
	cp_uint8_t			nri : 2;						/* bit: 5~6 */
	cp_uint8_t			f : 1;							/* bit: 7 */
};														/* 1 bytes */

struct cp_ipc_rtp_h264_fu_indicator_s {
	/* byte 0 */
	cp_uint8_t			type : 5;
	cp_uint8_t			nri : 2;
	cp_uint8_t			f : 1;
} __attribute__((packed));								/* 1 bytes */

struct cp_ipc_rtp_h264_fu_header_s {
	cp_uint8_t			type : 5;
	cp_uint8_t			r : 1;
	cp_uint8_t			e : 1;
	cp_uint8_t			s : 1;
} __attribute__((packed));								/* 1 bytes */


#pragma pack()


#endif