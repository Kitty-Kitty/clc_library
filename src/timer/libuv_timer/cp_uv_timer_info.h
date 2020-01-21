/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/


#ifndef	_CP_UV_TIMER_INFO_INCLUDE_H_
#define _CP_UV_TIMER_INFO_INCLUDE_H_




//typedef	struct cp_uv_timer_info_s			cp_uv_timer_info_t;




#pragma pack(1)



#define CP_UV_TIMER_INFO_FIELDS																						\
		CP_TIMER_INFO_FIELDS																						

/************************************************************************/
/*                                                                      */
/************************************************************************/
struct cp_uv_timer_info_s {
	CP_UV_TIMER_INFO_FIELDS
};


#pragma pack()


enum cp_uv_timer_option_enum
{
	cp_uv_timer_option_again = 0x01,
	cp_uv_timer_option_set_repeat = 0x02,
	cp_uv_timer_option_get_repeat = 0x03,
};


#endif





