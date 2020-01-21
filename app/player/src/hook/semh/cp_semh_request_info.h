/**************************************************************************

* Copyright: novigo

* Author: tianhuiming@novigo.com.cn

* Date：2016-4-29
        
* Description:

**************************************************************************/



#ifndef	_CP_SEMH_REQUEST_INFO_INCLUDE_H_
#define _CP_SEMH_REQUEST_INFO_INCLUDE_H_

#include "cp_core.h"
#include "css_core.h"
#include "cp_player_core.h"



typedef cp_bool_t(*request_handle_cb)(cp_player_t *player, void *data, cp_sockaddr_in *addr, cp_int32_t flags);



/************************************************************************/
/*业务指令                                                              */
/************************************************************************/
enum cp_request_command_s
{
	center_register,
	center_cancel_register,
	center_life_heart,
	meida_life_heart,
	player_background_life_heart,
	client_background_life_heart,
	center_exception,
}cp_request_command_t;


/************************************************************************/
/*业务请求信息                                                          */
/************************************************************************/
typedef struct cp_request_info_s
{
	void				*data;
	cp_socket_t			*s;
	cp_int32_t			flags;
	cp_int32_t			command;
	cp_sockaddr_in		sa;
	cp_exception_info_t exp_info;
	request_handle_cb	handle;
}cp_request_info_t;









#endif