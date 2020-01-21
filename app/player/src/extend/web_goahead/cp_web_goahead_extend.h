/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/

#ifndef	_CP_WEB_GOAHEAD_EXTEND_INCLUDE_H_
#define _CP_WEB_GOAHEAD_EXTEND_INCLUDE_H_

#include "cp_web_goahead_extend_core.h"
#include "cp_socket.h"



//typedef struct cp_web_goahead_extend_s					cp_web_goahead_extend_t;



#pragma pack(1)


#define CP_WEB_GOAHEAD_EXTEND_FIELDS											\
		CP_EXTEND_FIELDS														\



/************************************************************************/
/*                                                                      */
/************************************************************************/
struct cp_web_goahead_extend_s {
	CP_WEB_GOAHEAD_EXTEND_FIELDS												/*表示时间模块信息*/
};


#pragma pack()



cp_web_goahead_extend_t* create_web_goahead_extend(cp_module_register_t *register_info, cp_socket_manager_t *manager, cp_web_goahead_extend_info_t *info);
cp_int32_t destroy_web_goahead_extend(cp_extend_manager_t *manager, cp_web_goahead_extend_t* web_goahead_extend);


#endif


