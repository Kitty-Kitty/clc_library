
/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-23

Description:css_player main include file 

**************************************************************************/


#ifndef _CP_APP_INCLUDE_H_
#define _CP_APP_INCLUDE_H_

#include <stdio.h>
#include <stdlib.h>





#include "cp_core.h"
#include "cp_include.h"
#include "cp_conf.h"
#include "cp_socket.h"
#include "cp_app_info.h"




typedef struct cp_app_handlers_s			cp_app_handlers_t;




/************************************************************************/
/*��ʾapp�Ĵ���������                                                  */
/************************************************************************/
struct cp_app_handlers_s {
	int(*init)(cp_app_t *app, cp_app_info_t *app_info);
	int(*start)(cp_app_t *app, cp_app_info_t *app_info);
	int(*stop)(cp_app_t *app);
};



/************************************************************************/
/* ��ʾapp ��Ϣ����                                                      */
/************************************************************************/

#define CP_APP_FIELDS																\
		cp_char_t					*name;				/*��ʾģ������*/				\
		cp_int32_t					version;			/*��ʾģ��汾��*/			\
		cp_char_t					*description;		/*��ʾģ�������*/			\
		cp_log_t					*logger;			/*��־��Ϣ*/					\
		cp_conf_t					*conf;				/*�����ļ���Ϣ*/				\
		cp_socket_manager_t			*socket_manager;	/*����ͨ�Ź���*/				\
		cp_thread_manager_t			*thread_manager;	/*�̹߳���*/					\
		cp_timer_t					*timer_task;		/*��ʱ������*/				\
		cp_app_info_t				*app_info;			/*�豸������Ϣ*/				\
		cp_void_t					*data;				/*��ʾ�豸����������*/		\
		cp_app_handlers_t			handlers;			/*��ʾapp�Ĵ�����*/		\
		cp_atomic64_t				sec;				/*��ʾ��ǰʱ����벿��*/		\
		cp_atomic_t					nsec;				/*��ʾ��ǰʱ������벿��*/	\





 /************************************************************************/
 /*��ʾapp�ṹ��                                                          */
 /************************************************************************/
 struct cp_app_s {
	 CP_APP_FIELDS
};





cp_app_t	*cp_app_create();

int cp_app_init(cp_app_t *app, cp_app_info_t *app_info);
int cp_app_start(cp_app_t *app, cp_app_info_t *app_info);
int cp_app_stop(cp_app_t *app);
int cp_app_destory(cp_app_t *app);




#endif