/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/

#ifndef	_CP_ECAM_FILTER_INCLUDE_H_
#define _CP_ECAM_FILTER_INCLUDE_H_

#include "cp_ecam_filter_core.h"
#include "cp_socket.h"



//typedef struct cp_ecam_filter_s					cp_ecam_filter_t;




#pragma pack(1)


#define CP_ECAM_FILTER_FIELDS											\
		CP_FILTER_FIELDS												\



/************************************************************************/
/*                                                                      */
/************************************************************************/
struct cp_ecam_filter_s {
	CP_ECAM_FILTER_FIELDS												/*��ʾʱ��ģ����Ϣ*/
};


#pragma pack()



cp_ecam_filter_t* create_ecam_filter(cp_module_register_t *register_info, cp_socket_manager_t *manager, cp_ecam_filter_info_t *info);
cp_int32_t destroy_ecam_filter(cp_ecam_filter_manager_t *manager, cp_ecam_filter_t* ecam_filter);


#endif

