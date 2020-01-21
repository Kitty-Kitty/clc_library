/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/

#ifndef	_CP_UV_TIMER_MANAGER_INCLUDE_H_
#define _CP_UV_TIMER_MANAGER_INCLUDE_H_



#include "cp_uv_timer_core.h"
#include "cp_include.h"



#define	CP_UV_TIMER_MANAGER_BEGIN_INTERVAL				1000			//Ĭ�϶�ʱ����һ������ʱ��
#define	CP_UV_TIMER_MANAGER_DEFAULT_INTERVAL			10000			//Ĭ�϶�ʱ�����ʱ��,���루ms��
#define	CP_UV_TIMER_MANAGER_DEFAULT_PRINT_COUNT			100				//Ĭ�϶�ʱ�����ж��ٴκ��ӡ��Ϣ
//typedef struct cp_uv_timer_manager_s					cp_uv_timer_manager_t;



#pragma pack(1)



/************************************************************************/
/*                                                                      */
/************************************************************************/

struct cp_uv_timer_manager_s
{
	CP_TIMER_MANAGER_FIELDS
	uv_loop_t*							loop;						/*ʱ��ѭ��*/
	cp_thread_t							*thread;					/*����loop�õ��̣߳���������*/
	uv_timer_t							uv_timer;					/*��ʾĬ�ϵĶ�ʱ��*/
	cp_int32_t							times;						/*���д���*/
};


#pragma pack()



cp_uv_timer_manager_t* create_uv_timer_manager(cp_module_manager_register_t *register_info, cp_app_t *app, cp_uv_timer_manager_info_t *info);
cp_int32_t destroy_uv_timer_manager(cp_app_t *app, cp_uv_timer_manager_t* manager);

#endif


