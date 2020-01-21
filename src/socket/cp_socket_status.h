/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/


#ifndef	_CP_SOCKET_STATUS_INCLUDE_H_
#define _CP_SOCKET_STATUS_INCLUDE_H_




//typedef	enum cp_socket_status_enum					cp_socket_status_e;





/************************************************************************/
/*                                                                      */
/************************************************************************/
typedef	enum cp_socket_status_enum
{
	CP_SOCKET_STATUS_SUCCESS,
	CP_SOCKET_STATUS_AGAIN,
	CP_SOCKET_STATUS_DATA_BROKEN,
	CP_SOCKET_STATUS_DATA_READ_TIMEOUT,
	CP_SOCKET_STATUS_DATA_WRITE_TIMEOUT,
}cp_socket_status_e;




#endif





