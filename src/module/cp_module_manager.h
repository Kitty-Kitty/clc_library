/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-05-26

Description: define module

**************************************************************************/


#ifndef	_CP_MODULE_MANAGER_INCLUDE_H_
#define _CP_MODULE_MANAGER_INCLUDE_H_



#include "cp_module_core.h"




//typedef struct cp_module_manager_s				cp_module_manager_t;





#pragma pack(1)



typedef	cp_int32_t(*cp_manager_init_handle)(cp_module_manager_t *cp_manager, const cp_module_manager_info_t *info);												/*ģ�鴴���ӿڣ���ʾ����һ��ģ��*/
typedef	cp_int32_t(*cp_manager_start_handle)(cp_module_manager_t *cp_manager, const cp_module_manager_info_t *info);											/*ģ������нӿڣ���ģ��init֮�󣬻ᱻ����*/
typedef	cp_int32_t(*cp_manager_stop_handle)(cp_module_manager_t *cp_manager);																					/*��ȡģ�����ݣ�flagΪ��ȡģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��*/
typedef	cp_int32_t(*cp_manager_ctrl_handle)(cp_module_manager_t *cp_manager, cp_int32_t optname, const cp_void_t* optval);										/*����ģ�����*/
typedef	cp_module_t*(*cp_manager_create_module_handle)(cp_module_manager_t *cp_manager, const cp_module_info_t *info);											/*ģ�鴴���ӿ�*/
typedef	cp_module_t*(*cp_manager_get_module_handle)(cp_module_manager_t *cp_manager, const cp_module_info_t *info);												/*ģ���ѯ�ӿ�*/
typedef	cp_int32_t(*cp_manager_register_module_handle)(cp_module_manager_t *cp_manager, cp_module_t *module);													/*дģ�����ݣ�flagΪдģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��*/
typedef	cp_int32_t(*cp_manager_cancel_module_handle)(cp_module_manager_t *cp_manager, cp_module_t *module);														/*�ر�ģ��*/
typedef	cp_int32_t(*cp_manager_destroy_module_handle)(cp_module_manager_t *cp_manager, cp_module_t *module);													/*�˳�ģ��*/
typedef	cp_int32_t(*cp_manager_ctrl_module_handle)(cp_module_manager_t *cp_manager, cp_module_t *module, cp_int32_t optname, const cp_void_t* optval);			/*����ģ�����*/



#if 0
/************************************************************************/
/* ��ʾģ�����������ӿ�													*/
/************************************************************************/
#define CP_MODULE_MANAGER_HANDER_FIELDS																																											\
	cp_int32_t(*init)(cp_module_manager_t *manager, const cp_module_manager_info_t *info);												/*ģ�鴴���ӿڣ���ʾ����һ��ģ��*/											\
	cp_int32_t(*start)(cp_module_manager_t *manager, const cp_module_manager_info_t *info);												/*ģ������нӿڣ���ģ��init֮�󣬻ᱻ����*/								\
	cp_int32_t(*stop)(cp_module_manager_t *manager);																					/*��ȡģ�����ݣ�flagΪ��ȡģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��*/				\
	cp_int32_t(*ctrl)(cp_module_manager_t *manager, cp_int32_t optname, const cp_void_t* optval);										/*����ģ�����*/															\
	cp_module_t*(*cp_create_module)(cp_module_manager_t *manager, const cp_module_info_t *info);										/*ģ�鴴���ӿ�*/															\
	cp_module_t*(*get_module)(cp_module_manager_t *manager, const cp_module_info_t *info);												/*ģ���ѯ�ӿ�*/															\
	cp_int32_t(*register_module)(cp_module_manager_t *manager, cp_module_t *module);													/*дģ�����ݣ�flagΪдģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��*/					\
	cp_int32_t(*cancel_module)(cp_module_manager_t *manager, cp_module_t *module);														/*�ر�ģ��*/																\
	cp_int32_t(*destroy_module)(cp_module_manager_t *manager, cp_module_t *module);														/*�˳�ģ��*/																\
	cp_int32_t(*ctrl_module)(cp_module_manager_t *manager, cp_module_t *module, cp_int32_t optname, const cp_void_t* optval);			/*����ģ�����*/															\


#endif

/************************************************************************/
/* ��ʾģ�����������ӿ�													*/
/************************************************************************/
#define CP_MODULE_MANAGER_HANDER_FIELDS																												\
	cp_manager_init_handle					init;							/*ģ�鴴���ӿڣ���ʾ����һ��ģ��*/											\
	cp_manager_start_handle					start;							/*ģ������нӿڣ���ģ��init֮�󣬻ᱻ����*/								\
	cp_manager_stop_handle					stop;							/*��ȡģ�����ݣ�flagΪ��ȡģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��*/				\
	cp_manager_ctrl_handle					ctrl;							/*����ģ�����*/															\
	cp_manager_create_module_handle			create_module;					/*ģ�鴴���ӿ�*/															\
	cp_manager_get_module_handle			get_module;						/*ģ���ѯ�ӿ�*/															\
	cp_manager_register_module_handle		register_module;				/*дģ�����ݣ�flagΪдģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��*/					\
	cp_manager_cancel_module_handle			cancel_module;					/*�ر�ģ��*/																\
	cp_manager_destroy_module_handle		destroy_module;					/*�˳�ģ��*/																\
	cp_manager_ctrl_module_handle			ctrl_module;					/*����ģ�����*/															\





/************************************************************************/
/* ��ʾģ����Ϣ�ṹ��                                                    */
/************************************************************************/
/************************************************************************/
/*ģ�����������,��ģ����Ϣ����̳и���Ϣ                                  */
/************************************************************************/
#define CP_MODULE_MANAGER_FIELDS																		\
			cp_module_manager_register_t	register_info;												\
			cp_app_t						*app;							/*��ʾӦ�ó���ָ��*/			\
			cp_log_t						*logger;						/*��ʾ��־loggerָ��*/		\
			cp_conf_t						*conf;							/*��ʾ�����ļ���Ϣ*/			\
			cp_module_manager_info_t		*info;							/*��ʾģ���������Ϣ*/		\
			cp_void_t						*data;							/*��ʾģ�����������*/		\
			cp_pool_t						*pool;							/*��ʾģ���˽���ڴ��*/		\
			cp_module_message_manager_t		*mmm;							/*��ʾģ����Ϣ������*/		\
			cp_module_manager_t				*decorator;						/*��ʾģ�������װ����*/		\
			cp_atomic_t						status;							/*��ʾģ���״̬��Ϣ*/		\
			cp_array_t						module_manager_register;		/*��ʾ��ģ�������ע������*/							\
			cp_array_t						module_managers;				/*������ģ�������ָ�붼�ڱ��������������*/			\
			cp_array_t						module_register;				/*��ʾģ��ע������*/									\
			cp_queue_t						modules;						/*��ʾģ���б�*/				\
			cp_mutex_t						module_mutex;					/*��ʾ����ģ�黥����*/		\
			CP_MODULE_MANAGER_HANDER_FIELDS									/*��ʾģ��Ĵ�����*/		\




struct cp_module_manager_s																	
{																							
	CP_MODULE_MANAGER_FIELDS
};



#pragma pack()








/************************************************************************/
/* ����ģ��Ľӿ���Ϣ                                                    */
/************************************************************************/

#define  CP_MODULE_MANAGER_SET_SINGLE_HANDLER(manager, handle, name)							\
	(manager)->handle = handle##_##name##_manager;


#define  CP_MODULE_MANAGER_SET_SINGLE_HANDLER_AND_TYPE(manager, handle, type, name)				\
	(manager)->handle = (type)handle##_##name##_manager;




#define  CP_MODULE_MANAGER_SET_SINGLE_MODULE_HANDLER(manager, handle, name)						\
	(manager)->handle##_module = handle##_##name##_module;


#define  CP_MODULE_MANAGER_SET_SINGLE_MODULE_HANDLER_AND_TYPE(manager, handle, type, name)		\
	(manager)->handle##_module = (type)handle##_##name##_module;




#define  CP_MODULE_MANAGER_SET_HANDLERS(manager, name)							do {									\
	CP_MODULE_MANAGER_SET_SINGLE_HANDLER_AND_TYPE(manager, init, cp_manager_init_handle, name)							\
	CP_MODULE_MANAGER_SET_SINGLE_HANDLER_AND_TYPE(manager, start, cp_manager_start_handle, name)						\
	CP_MODULE_MANAGER_SET_SINGLE_HANDLER_AND_TYPE(manager, stop, cp_manager_stop_handle, name)							\
	CP_MODULE_MANAGER_SET_SINGLE_HANDLER_AND_TYPE(manager, ctrl, cp_manager_ctrl_handle, name)							\
	CP_MODULE_MANAGER_SET_SINGLE_MODULE_HANDLER_AND_TYPE(manager, create, cp_manager_create_module_handle, name)		\
	CP_MODULE_MANAGER_SET_SINGLE_MODULE_HANDLER_AND_TYPE(manager, get, cp_manager_get_module_handle, name)				\
	CP_MODULE_MANAGER_SET_SINGLE_MODULE_HANDLER_AND_TYPE(manager, register, cp_manager_register_module_handle, name)	\
	CP_MODULE_MANAGER_SET_SINGLE_MODULE_HANDLER_AND_TYPE(manager, cancel, cp_manager_cancel_module_handle, name)		\
	CP_MODULE_MANAGER_SET_SINGLE_MODULE_HANDLER_AND_TYPE(manager, destroy, cp_manager_destroy_module_handle, name)		\
	CP_MODULE_MANAGER_SET_SINGLE_MODULE_HANDLER_AND_TYPE(manager, ctrl, cp_manager_ctrl_module_handle, name)			\
								} while (0);																			\


/************************************************************************/
/* �������ģ���ڴ�ռ�                                                   */
/************************************************************************/
#define  CP_MODULE_MANAGER_MALLOC(ret, app, type)								do {			\
	ret = (type*)cp_mpalloc(app->mpool, cp_sizeof(type));										\
	cp_memset(ret, 0, cp_sizeof(type));															\
	cp_queue_init(&(ret)->modules);																\
} while (0);																					\


/************************************************************************/
/* �ͷŹ���ģ���ڴ�ռ�                                                   */
/************************************************************************/
#define  CP_MODULE_MANAGER_FREE(manager)														\
	cp_mpfree(manager->app->mpool, manager);													\


#endif


