/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/


#ifndef	_CP_SOCKET_TYPE_INCLUDE_H_
#define _CP_SOCKET_TYPE_INCLUDE_H_




//typedef	enum cp_socket_type_enum					cp_socket_type_e;
//typedef	enum cp_socket_type_name_enum				cp_socket_type_name_e;



/************************************************************************/
/*                                                                      */
/************************************************************************/
typedef	enum cp_socket_type_enum
{
	cp_socket_type_udp,
	cp_socket_type_tcp,
	cp_socket_type_multicast
}cp_socket_type_e;



/* Expand this list if necessary. */
#define CP_SOCKET_TYPE_NAME_MAP(CP_SOCKET_TYPE)												\
  CP_SOCKET_TYPE(udp, "udp")																\
  CP_SOCKET_TYPE(tcp, "tcp")																\
  CP_SOCKET_TYPE(multicast, "udp_multicast")												\



#endif





