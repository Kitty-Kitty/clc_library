/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/


#ifndef	_CP_FUSION_PLAYER_PROCESS_INFO_INCLUDE_H_
#define _CP_FUSION_PLAYER_PROCESS_INFO_INCLUDE_H_

#include "cp_fusion_player_process_core.h"





//typedef	struct cp_fusion_player_process_info_s			cp_fusion_player_process_info_t;
typedef void(*cp_fusion_player_process_cb)(cp_fusion_player_process_t* th);



#pragma pack(1)


#define CP_FUSION_PLAYER_PROCESS_INFO_FIELDS										\
		CP_PROCESS_INFO_FIELDS												\



/************************************************************************/
/*                                                                      */
/************************************************************************/
struct cp_fusion_player_process_info_s {
	CP_FUSION_PLAYER_PROCESS_INFO_FIELDS
};



#pragma pack()


#endif





