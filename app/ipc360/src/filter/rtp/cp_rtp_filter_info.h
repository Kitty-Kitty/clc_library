/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/


#ifndef	_CP_RTP_FILTER_INFO_INCLUDE_H_
#define _CP_RTP_FILTER_INFO_INCLUDE_H_

#include "cp_rtp_filter_core.h"





//typedef	struct cp_rtp_filter_info_s			cp_rtp_filter_info_t;
typedef void(*cp_rtp_filter_cb)(cp_rtp_filter_t* th);




#pragma pack(1)


#define CP_RTP_FILTER_INFO_FIELDS										\
		CP_FILTER_INFO_FIELDS											\



/************************************************************************/
/*                                                                      */
/************************************************************************/
struct cp_rtp_filter_info_s {
	CP_RTP_FILTER_INFO_FIELDS
};

#pragma pack()




#endif





