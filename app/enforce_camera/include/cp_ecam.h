
/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-23

Description:css_ecam main include file 

**************************************************************************/


#ifndef _CP_ECAM_INCLUDE_H_
#define _CP_ECAM_INCLUDE_H_

#include <stdio.h>
#include <stdlib.h>





#include "cp_core.h"
#include "cp_include.h"
#include "cp_ecam_info.h"
#include "cp_ecam_hook_core.h"





//typedef  struct cp_ecam_s						 cp_ecam_t;




//#pragma pack(1)


 /************************************************************************/
 /*����һ��ecam app����                                                 */
 /************************************************************************/
 struct cp_ecam_s {
	 CP_APP_FIELDS
	 cp_timer_t						*timer_task;						/*��ʾ��ʱ����*/
	 cp_socket_t					*tcp_listen;						/*��ʾTCP������ַ*/
	 cp_socket_t					*udp_listen;						/*��ʾUDP����*/
	 cp_socket_t					*multicast_listen;					/*��ʾmulticast����*/
	 cp_ecam_hook_t					*request_hook;						/*��ʾ����ʹ�õ�hook*/
 };


// #pragma pack()



cp_ecam_t *cp_ecam_create(cp_app_info_t *app_info);
int cp_ecam_destroy(cp_ecam_t *ecam);




#endif