/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/

#ifndef	_CP_PTP_FILTER_INCLUDE_H_
#define _CP_PTP_FILTER_INCLUDE_H_



#include "cp_ptp_filter_core.h"
#include "cp_socket.h"



//typedef struct cp_ptp_filter_s					cp_ptp_filter_t;




#pragma pack(1)


#define CP_PTP_FILTER_FIELDS											\
		CP_FILTER_FIELDS												\



/************************************************************************/
/*                                                                      */
/************************************************************************/
struct cp_ptp_filter_s {
	CP_PTP_FILTER_FIELDS												/*表示时间模块信息*/
};


#pragma pack()



cp_ptp_filter_t* create_ptp_filter(cp_module_register_t *register_info, cp_socket_manager_t *manager, cp_ptp_filter_info_t *info);
cp_int32_t destroy_ptp_filter(cp_filter_manager_t *manager, cp_ptp_filter_t* ptp_filter);


#endif


