/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-11-19

Description:

**************************************************************************/

#ifndef _CP_MEDIA_SERVER_INFO_INCLUDE_H_
#define _CP_MEDIA_SERVER_INFO_INCLUDE_H_



#include "cp_ecam_info.h"


#pragma pack(1)


struct cp_media_server_info_s
{
	cp_device_info_t				*dev_info;							/*表示设备信息*/
	cp_multicast_addr_t				multicast_addr;						/*组播地址信息*/
	cp_socket_t						*multicast_socket;					/*表示multicast接收*/

};

#pragma pack()

#endif