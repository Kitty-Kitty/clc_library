/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-05-26

Description: define module

**************************************************************************/


#ifndef	_CP_MODULE_INCLUDE_H_
#define _CP_MODULE_INCLUDE_H_



#include "cp_module_core.h"





//typedef struct cp_module_s						cp_module_t;





#pragma pack(1)




typedef cp_int32_t(*module_init_handle)(cp_module_t *module, const cp_module_info_t *module_info);								/*ģ�鴴���ӿڣ���ʾ����һ��ģ��*/
typedef cp_int32_t(*module_open_handle)(cp_module_t *module, const cp_module_info_t *module_info);								/*ģ������нӿڣ���ģ��init֮�󣬻ᱻ����*/
typedef cp_int32_t(*module_read_handle)(cp_module_t *module, cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag);				/*��ȡģ�����ݣ�flagΪ��ȡģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��*/
typedef cp_int32_t(*module_write_handle)(cp_module_t *module, const cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag);			/*дģ�����ݣ�flagΪдģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��*/
typedef cp_int32_t(*module_close_handle)(cp_module_t *module);																	/*�ر�ģ��*/
typedef cp_int32_t(*module_exit_handle)(cp_module_t *module);																	/*�˳�ģ��*/
typedef cp_int32_t(*module_set_option_handle)(cp_module_t *module, cp_int32_t optname, const cp_void_t* optval);				/*����ģ�����*/
typedef cp_int32_t(*module_get_option_handle)(cp_module_t *module, cp_int32_t optname, cp_void_t* optval);						/*��ȡģ�����*/



#if 0
/************************************************************************/
/* ��ʾģ�鴦�����ӿ�													 */
/************************************************************************/

#define CP_MODULE_HANDLER_FIELDS					\
			cp_int32_t(*init)(cp_module_t *module, const cp_module_info_t *module_info);								/*ģ�鴴���ӿڣ���ʾ����һ��ģ��*/										\
			cp_int32_t(*open)(cp_module_t *module, const cp_module_info_t *module_info);								/*ģ������нӿڣ���ģ��init֮�󣬻ᱻ����*/							\
			cp_int32_t(*read)(cp_module_t *module, cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag);					/*��ȡģ�����ݣ�flagΪ��ȡģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��*/			\
			cp_int32_t(*write)(cp_module_t *module, const cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag);			/*дģ�����ݣ�flagΪдģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��*/				\
			cp_int32_t(*close)(cp_module_t *module);																	/*�ر�ģ��*/															\
			cp_int32_t(*exit)(cp_module_t *module);																		/*�˳�ģ��*/															\
			cp_int32_t(*set_option)(cp_module_t *module, cp_int32_t optname, const cp_void_t* optval);					/*����ģ�����*/														\
			cp_int32_t(*get_option)(cp_module_t *module, cp_int32_t optname, cp_void_t* optval);						/*��ȡģ�����*/														\


#endif


/************************************************************************/
/*ģ�������Ϣ                                                           */
/************************************************************************/
#define CP_MODULE_ERROR_FIELDS																				\
			cp_int32_t						error_no;									/*������*/			\
			cp_char_t						error_text[CP_APP_DEFAULT_STRING_LENGTH];	/*��������*/			\



#define CP_MODULE_HANDLER_FIELDS																										\
			module_init_handle init;								/*ģ�鴴���ӿڣ���ʾ����һ��ģ��*/										\
			module_open_handle open;								/*ģ������нӿڣ���ģ��init֮�󣬻ᱻ����*/							\
			module_read_handle read;								/*��ȡģ�����ݣ�flagΪ��ȡģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��*/			\
			module_write_handle write;								/*дģ�����ݣ�flagΪдģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��*/				\
			module_close_handle close;								/*�ر�ģ��*/															\
			module_exit_handle exit;								/*�˳�ģ��*/															\
			module_set_option_handle set_option;					/*����ģ�����*/														\
			module_get_option_handle get_option;					/*��ȡģ�����*/														\




/************************************************************************/
/*ģ������,��ģ����Ϣ����̳и���Ϣ                                       */
/************************************************************************/
#define CP_MODULE_FIELDS																				\
			cp_module_register_t			register_info;												\
			cp_module_manager_t				*manager;				/*ģ���������ַ��Ϣ*/				\
			cp_log_t						*logger;				/*��ʾ��־loggerָ��*/				\
			cp_conf_t						*conf;					/*��ʾ�����ļ���Ϣ*/					\
			cp_module_info_t				*info;					/*��ʾģ����Ϣ*/						\
			cp_void_t						*data;					/*��ʾģ�����������*/				\
			cp_pool_t						*pool;					/*��ʾģ���˽���ڴ��*/				\
			cp_module_message_manager_t		*mmm;					/*��ʾģ����Ϣ������*/				\
			cp_module_t						*decorator;				/*��ʾģ��װ����*/					\
			cp_atomic_t						status;					/*��ʾģ���״̬��Ϣ*/				\
			cp_module_register_t			**module_register;		/*��ʾ��ģ��ע������*/				\
			cp_int32_t						module_register_size;	/*��ʾ��ģ��ע�������С*/			\
			cp_int32_t						flag;					/*��ʾģ��ı�ʶ��Ϣ*/				\
			cp_queue_t						queue;					/*��ʾģ���б�*/											\
			cp_char_t						description[CP_APP_DEFAULT_STRING_LENGTH];			/*��ʾģ�������������Ϣ*/	\
			CP_MODULE_ERROR_FIELDS									/*��ʾģ�������Ϣ*/					\
			CP_MODULE_HANDLER_FIELDS								/*��ʾģ�鴦��Ļ����ӿ�*/			\


/************************************************************************/
/* ��ʾģ����Ϣ�ṹ��                                                    */
/************************************************************************/
struct cp_module_s
{
	CP_MODULE_FIELDS
};


#pragma pack()




/************************************************************************/
/* ����ģ��Ľӿ���Ϣ                                                    */
/************************************************************************/

#define  CP_MODULE_SET_SINGLE_HANDLER(module, handle, name)											\
	(module)->handle = handle##_##name;																\



#define  CP_MODULE_SET_SINGLE_HANDLER_AND_TYPE(module, handle, name, type)							\
	(module)->handle = (type)handle##_##name;														\



/************************************************************************/
/* ����ģ��Ľӿ���Ϣ                                                    */
/************************************************************************/

#define  CP_MODULE_UPDATE_SINGLE_HANDLER(src_module, dest_module, handle)							\
	(dest_module)->handle = (src_module)->handle;													\


#define  CP_MODULE_UPDATE_SINGLE_HANDLER_AND_TYPE(src_module, dest_module, handle, type)			\
	(dest_module)->handle = (type)(src_module)->handle;												\



#ifdef close
#undef close
#endif

/************************************************************************/
/* ����ģ������нӿ�                                                    */
/************************************************************************/
#define  CP_MODULE_SET_HANDLERS(module, name)		do {											\
	CP_MODULE_SET_SINGLE_HANDLER_AND_TYPE(module, init, name, module_init_handle)					\
	CP_MODULE_SET_SINGLE_HANDLER_AND_TYPE(module, open, name, module_open_handle)					\
	CP_MODULE_SET_SINGLE_HANDLER_AND_TYPE(module, read, name, module_read_handle)					\
	CP_MODULE_SET_SINGLE_HANDLER_AND_TYPE(module, write, name, module_write_handle)					\
	CP_MODULE_SET_SINGLE_HANDLER_AND_TYPE(module, close, name, module_close_handle)					\
	CP_MODULE_SET_SINGLE_HANDLER_AND_TYPE(module, exit, name, module_exit_handle)					\
	CP_MODULE_SET_SINGLE_HANDLER_AND_TYPE(module, set_option, name, module_set_option_handle)		\
	CP_MODULE_SET_SINGLE_HANDLER_AND_TYPE(module, get_option, name, module_get_option_handle)		\
} while (0);																						\




/************************************************************************/
/* ����ģ������нӿ�                                                    */
/************************************************************************/
#define  CP_MODULE_UPDATE_HANDLERS(src_module, dest_module)		do {								\
	CP_MODULE_UPDATE_SINGLE_HANDLER(src_module, dest_module, init)									\
	CP_MODULE_UPDATE_SINGLE_HANDLER(src_module, dest_module, open)									\
	CP_MODULE_UPDATE_SINGLE_HANDLER(src_module, dest_module, read)									\
	CP_MODULE_UPDATE_SINGLE_HANDLER(src_module, dest_module, write)									\
	CP_MODULE_UPDATE_SINGLE_HANDLER(src_module, dest_module, close)									\
	CP_MODULE_UPDATE_SINGLE_HANDLER(src_module, dest_module, exit)									\
	CP_MODULE_UPDATE_SINGLE_HANDLER(src_module, dest_module, set_option)							\
	CP_MODULE_UPDATE_SINGLE_HANDLER(src_module, dest_module, get_option)							\
} while (0);																						\


/************************************************************************/
/* ����ģ���data��Ϣ                                                    */
/************************************************************************/
#define CP_MODULE_SET_DATA(module_info, in_data)	(module_info)->data = (in_data)


/************************************************************************/
/* ��ȡģ���data��Ϣ                                                    */
/************************************************************************/
#define CP_MODULE_GET_DATA(module_info)				((module_info)->data)



#endif


