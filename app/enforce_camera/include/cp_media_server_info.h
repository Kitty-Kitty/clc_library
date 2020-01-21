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
	cp_device_info_t				*dev_info;							/*��ʾ�豸��Ϣ*/
	cp_multicast_addr_t				multicast_addr;						/*�鲥��ַ��Ϣ*/
	cp_socket_t						*multicast_socket;					/*��ʾmulticast����*/

};

#pragma pack()

#endif