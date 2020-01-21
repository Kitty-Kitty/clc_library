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
#define	CP_IPC_RTP_H264_NAL_MIN_LENGTH												6						//表示包含帧间隔标志的最小数据长度



typedef	struct cp_ipc_rtp_payload_h264_nalu_header_s								cp_ipc_rtp_payload_h264_nalu_header_t;
typedef struct cp_ipc_rtp_h264_fu_indicator_s										cp_ipc_rtp_h264_fu_indicator_t;
typedef struct cp_ipc_rtp_h264_fu_header_s											cp_ipc_rtp_h264_fu_header_t;


#pragma pack(1)


// H.264 NAL type
typedef enum cp_ipc_rtp_h264_nal_type_enum
{
	CP_IPC_RTP_H264NT_NAL = 0,						//
	CP_IPC_RTP_H264NT_SLICE,						//非IDR图像的编码条带(P 帧)
	CP_IPC_RTP_H264NT_SLICE_DPA,					//编码条带数据分割块A
	CP_IPC_RTP_H264NT_SLICE_DPB,					//编码条带数据分割块B
	CP_IPC_RTP_H264NT_SLICE_DPC,					//编码条带数据分割块C
	CP_IPC_RTP_H264NT_SLICE_IDR,					//IDR图像的编码条带(I 帧)
	CP_IPC_RTP_H264NT_SEI,							//补充增强信息单元
	CP_IPC_RTP_H264NT_SPS,							//序列参考集
	CP_IPC_RTP_H264NT_PPS,							//图象参考集
	CP_IPC_RTP_H264NT_AUD,							//分界符
	CP_IPC_RTP_H264NT_EOSEQ,						//序列结束
	CP_IPC_RTP_H264NT_EOSTREAM,					//码流结束
	CP_IPC_RTP_H264NT_FILL,						//填充
	//13..23											//保留
	//24..31											//未使用
}cp_ipc_rtp_h264_nal_type;


/************************************************************************/
/* 定义nalu header信息                                                  */
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