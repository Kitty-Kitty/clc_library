/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/

#ifndef	_CP_ECAM_PROCESS_INCLUDE_H_
#define _CP_ECAM_PROCESS_INCLUDE_H_

#include "cp_ecam_process_core.h"
#include "cp_socket.h"



//typedef struct cp_ecam_process_s					cp_ecam_process_t;



#pragma pack(1)



#define CP_ECAM_PROCESS_FIELDS											\
		CP_PROCESS_FIELDS													\


/************************************************************************/
/*                                                                      */
/************************************************************************/
struct cp_ecam_process_s {
	CP_ECAM_PROCESS_FIELDS												/*��ʾʱ��ģ����Ϣ*/
};


#pragma pack()


cp_ecam_process_t* create_ecam_process(cp_module_register_t *register_info, cp_socket_manager_t *manager, cp_ecam_process_info_t *info);
cp_int32_t destroy_ecam_process(cp_ecam_process_manager_t *manager, cp_ecam_process_t* ecam_process);


#endif


