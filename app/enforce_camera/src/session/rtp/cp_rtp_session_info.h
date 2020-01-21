/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/


#ifndef	_CP_RTP_SESSION_INFO_INCLUDE_H_
#define _CP_RTP_SESSION_INFO_INCLUDE_H_





typedef	struct cp_rtp_session_info_s			cp_rtp_session_info_t;




#pragma pack(1)


#define CP_RTP_SESSION_INFO_FIELDS																					\
		CP_MODULE_INFO_FIELDS																						\



/************************************************************************/
/*                                                                      */
/************************************************************************/
struct cp_rtp_session_info_s {
	CP_RTP_SESSION_INFO_FIELDS
};


#pragma pack()



#endif





