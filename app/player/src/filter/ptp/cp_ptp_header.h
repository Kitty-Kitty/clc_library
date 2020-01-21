/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2017-01-09

Description:

**************************************************************************/

#ifndef _CP_PTP_HEADER_INCLUDE_H_
#define _CP_PTP_HEADER_INCLUDE_H_



#include "cp_core.h"



/* Values for the messageType field */
#define		CP_SYNC								0x0
#define		CP_DELAY_REQ						0x1
#define		CP_PDELAY_REQ						0x2
#define		CP_PDELAY_RESP						0x3
#define		CP_FOLLOW_UP						0x8
#define		CP_DELAY_RESP						0x9
#define		CP_PDELAY_RESP_FOLLOW_UP			0xA
#define		CP_ANNOUNCE							0xB
#define		CP_SIGNALING						0xC
#define		CP_MANAGEMENT						0xD

/* Bits for flagField[0] */
#define		CP_ALT_MASTER						(1<<0)
#define		CP_TWO_STEP							(1<<1)
#define		CP_UNICAST							(1<<2)

/* Bits for flagField[1] */
#define		CP_LEAP_61							(1<<0)
#define		CP_LEAP_59							(1<<1)
#define		CP_UTC_OFF_VALID					(1<<2)
#define		CP_PTP_TIMESCALE					(1<<3)
#define		CP_TIME_TRACEABLE					(1<<4)
#define		CP_FREQ_TRACEABLE					(1<<5)

#define		CP_PTP_AUTH_SIZE					28
#define		CP_PTP_VERSION_MASK					0x0f
#define		CP_PTP_VERSION						0x02




typedef		struct cp_ptp_header_s				cp_ptp_header_t;
typedef		struct cp_ptp_message_s				cp_ptp_message_t;



#pragma pack(1)


struct cp_clock_identity_s {
	uint8_t										id[8];
};



struct cp_port_identity_s {
	struct cp_clock_identity_s					clockIdentity;
	uint16_t									portNumber;
};



/** On the wire time stamp format. */
struct cp_ptp_timestamp_s {
	uint16_t									seconds_msb; /* 16 bits + */
	uint32_t									seconds_lsb; /* 32 bits = 48 bits*/
	uint32_t									nanoseconds;
};



struct cp_auth_tlv_s {
	uint16_t									type;
	uint16_t									length;
	unsigned char								auth[CP_PTP_AUTH_SIZE];
};



struct cp_ptp_header_s {
	uint8_t										tsmt; /* transportSpecific | messageType */
	uint8_t										ver;  /* reserved          | versionPTP  */
	uint16_t									messageLength;
	uint8_t										domainNumber;
	uint8_t										reserved1;
	uint8_t										flagField[2];
	int64_t										correction;
	uint32_t									reserved2;
	struct cp_port_identity_s					sourcePortIdentity;
	uint16_t									sequenceId;
	uint8_t										control;
	int8_t										logMessageInterval;
};



struct cp_follow_up_msg_s {
	struct cp_ptp_header_s						hdr;
	struct cp_ptp_timestamp_s					preciseOriginTimestamp;
	struct cp_auth_tlv_s						auth_tlv;
	uint8_t										suffix[0];
};


struct cp_ptp_message_s {
	union {
		struct cp_ptp_header_s					header;
		struct cp_follow_up_msg_s				follow_up;
	};
	/**/
} ;


#pragma pack()


#endif