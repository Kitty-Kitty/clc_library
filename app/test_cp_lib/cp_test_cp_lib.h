
/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-23

Description:css_test_cp_lib main include file 

**************************************************************************/


#ifndef _CP_PLAYER_INCLUDE_H_
#define _CP_PLAYER_INCLUDE_H_

#include <stdio.h>
#include <stdlib.h>





#include "cp_core.h"
#include "cp_include.h"
#include "cp_test_cp_lib_info.h"





typedef  struct cp_test_cp_lib_s						 cp_test_cp_lib_t;





 /************************************************************************/
 /*定义一个test_cp_lib app内容                                                 */
 /************************************************************************/
 struct cp_test_cp_lib_s {
	 CP_APP_FIELDS
	cp_char_t						center_addr[CP_APP_DEFAULT_LENGTH];		//中心地址
	cp_int32_t						center_port;							//中心端口
 };



 cp_test_cp_lib_t* cp_test_cp_lib_create(cp_app_info_t *app_info);
int cp_test_cp_lib_destroy(cp_test_cp_lib_t *test_cp_lib);




#endif