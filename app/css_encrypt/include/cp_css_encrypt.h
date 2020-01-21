
/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-23

Description:css_css_encrypt main include file 

**************************************************************************/


#ifndef _CP_CSS_ENCRYPT_INCLUDE_H_
#define _CP_CSS_ENCRYPT_INCLUDE_H_

#include <stdio.h>
#include <stdlib.h>





#include "cp_core.h"
#include "cp_include.h"
#include "cp_css_encrypt_info.h"





//typedef  struct cp_css_encrypt_s						 cp_css_encrypt_t;




//#pragma pack(1)


 /************************************************************************/
 /*定义一个css_encrypt app内容                                                 */
 /************************************************************************/
 struct cp_css_encrypt_s {
	 CP_APP_FIELDS
	 cp_timer_t						*timer_task;						/*表示定时任务*/
 };


// #pragma pack()



cp_css_encrypt_t *cp_css_encrypt_create(cp_app_info_t *app_info);
int cp_css_encrypt_destroy(cp_css_encrypt_t *css_encrypt);




#endif