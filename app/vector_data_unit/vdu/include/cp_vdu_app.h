
/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-23

Description:css_vdu main include file 

**************************************************************************/


#ifndef _CP_VDU_APP_INCLUDE_H_
#define _CP_VDU_APP_INCLUDE_H_

#include <stdio.h>
#include <stdlib.h>





#include "cp_core.h"
#include "cp_include.h"
#include "cp_vdu_info.h"





//typedef  struct cp_vdu_app_s						 cp_vdu_app_t;




//#pragma pack(1)


 /************************************************************************/
 /*定义一个vdu app内容                                                 */
 /************************************************************************/
 struct cp_vdu_app_s {
	 CP_APP_FIELDS
	 cp_timer_t						*timer_task;						/*表示定时任务*/
	 cp_func_t						*vdu_func;							/*表示vdu处理模块*/
 };


// #pragma pack()



cp_vdu_app_t *cp_vdu_app_create(cp_app_info_t *app_info);
int cp_vdu_app_destroy(cp_vdu_app_t *vdu);




#endif