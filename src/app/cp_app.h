
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


#include "cp_app_core.h"


typedef struct cp_app_handles_s			cp_app_handles_t;
typedef cp_app_t* (*cp_app_create_handle)(cp_app_info_t *app_info);
typedef cp_int32_t (*cp_app_destroy_handle)(cp_app_t *app);
typedef int(*cp_app_init_handle)(cp_app_t *app, cp_app_info_t *cp_global_app_info);
typedef int(*cp_app_start_handle)(cp_app_t *app, cp_app_info_t *cp_global_app_info);
typedef int(*cp_app_stop_handle)(cp_app_t *app);



#pragma pack(1)


#if 0
/************************************************************************/
/*��ʾapp�Ĵ���������                                                  */
/************************************************************************/
#define CP_APP_HANDLER_FIELDS											\
	int(*init)(cp_app_t *app, cp_app_info_t *app_info);					\
	int(*start)(cp_app_t *app, cp_app_info_t *app_info);				\
	int(*stop)(cp_app_t *app);											\


#endif


/************************************************************************/
/*��ʾapp�Ĵ���������                                                  */
/************************************************************************/
#define CP_APP_HANDLER_FIELDS											\
	cp_app_init_handle	init;											\
	cp_app_start_handle start;											\
	cp_app_stop_handle	stop;											\






// 		cp_module_manager_register_t	**module_manager_register;		/*��ʾģ��ע����Ϣ����*/							\
// 		cp_int32_t						module_manager_register_size;	/*��ʾģ��ע�������С*/							\
// 		cp_module_manager_t				**module_manager_array;			/*����ģ�������ָ�붼�ڱ��������������*/			\
// 		cp_int32_t						module_manager_size;			/*����ģ����������������ݵ�����*/					\




/************************************************************************/
/* ��ʾapp ��Ϣ����                                                      */
/************************************************************************/

#define CP_APP_FIELDS																									\
		cp_module_manager_register_t	register_info;																	\
		cp_log_t						*logger;						/*��־��Ϣ*/										\
		cp_conf_t						*conf;							/*�����ļ���Ϣ*/									\
		cp_app_info_t					*app_info;						/*�豸������Ϣ*/									\
		cp_daemon_info_t				*daemon_info;					/*�ػ�������Ϣ*/									\
		cp_void_t						*data;							/*��ʾ�豸����������*/							\
		cp_mpool_t						*mpool;							/*app�Դ��ļ��ڴ����*/							\
		cp_array_t						root_module_manager_register;	/*��ʾģ��ע����Ϣ����*/							\
		cp_array_t						root_module_manager_array;		/*����ģ�������ָ�붼�ڱ��������������*/			\
		CP_APP_HANDLER_FIELDS											/*��ʾapp�Ĵ�����*/							\
		cp_timeval						system_tv;						/*��ʾ��ǰϵͳʱ��*/								\


// 		cp_atomic_t						sec;							/*��ʾ��ǰʱ����벿��*/							\
// 		cp_atomic_t						nsec;							/*��ʾ��ǰʱ������벿��*/						\


 /************************************************************************/
 /*��ʾapp�ṹ��                                                          */
 /************************************************************************/
 struct cp_app_s {
	 CP_APP_FIELDS
};

#pragma pack()




 /************************************************************************/
 /* ��������app��������                                                   */
 /************************************************************************/
 cp_app_t	*cp_app_create(cp_app_info_t *app_info);
 cp_int32_t cp_app_destroy(cp_app_t *app);


 /************************************************************************/
 /* ����appע�ắ��                                                                     */
 /************************************************************************/
 cp_int32_t	cp_app_register(cp_int32_t type, cp_char_t *name, cp_int32_t version, cp_char_t *description, cp_app_create_handle para_app_create_handle, cp_app_destroy_handle para_app_destroy_handle);
 cp_int32_t	cp_app_entry_config_path(cp_char_t *config_path);




 /************************************************************************/
 /* ���涨�����þ���ĺ�                                                  */
 /************************************************************************/
#define  CP_APP_SET_SINGLE_HANDLER(app, handle, name)							\
	(app)->handle = handle##_##name;


#define  CP_APP_SET_SINGLE_HANDLER_AND_TYPE(app, handle, name, type)			\
	(app)->handle = (type)handle##_##name;



#define  CP_APP_SET_HANDLERS(app, name)											\
	CP_APP_SET_SINGLE_HANDLER_AND_TYPE(app, init, name, cp_app_init_handle)		\
	CP_APP_SET_SINGLE_HANDLER_AND_TYPE(app, start, name, cp_app_start_handle)	\
	CP_APP_SET_SINGLE_HANDLER_AND_TYPE(app, stop, name, cp_app_stop_handle)		\



#endif




