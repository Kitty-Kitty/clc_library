/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2017-04-24

Description:

**************************************************************************/

#ifndef _CP_MODULE_MESSAGE_INCLUDE_H_
#define _CP_MODULE_MESSAGE_INCLUDE_H_






#include "cp_core.h"
#include "cp_safe_queue.h"
#include "cp_thread_core.h"


#define CP_MODULE_MESSAGE_DEFAULT_NUMBER						128							//Ĭ�ϵ���Ϣ���и���
#define	CP_MODULE_MESSAGE_SLEEP_INTERVAL						100000000					//Ĭ�ϵ����߼��ʱ�䣬��λ����




typedef enum	cp_module_message_type_enum					cp_module_message_type_e;
typedef struct	cp_module_message_process_s					cp_module_message_process_t;
typedef struct	cp_module_message_s							cp_module_message_t;
//typedef struct	cp_module_message_manager_s					cp_module_message_manager_t;
typedef cp_int32_t(*module_message_handle)(cp_module_message_manager_t *mmm, cp_module_message_t *src, cp_void_t *data);



#pragma pack(1)


/************************************************************************/
/* ��Ϣ����                                                              */
/************************************************************************/
enum cp_module_message_type_enum
{
	cp_module_message_type_none = 0,
	cp_module_message_type_init,
	cp_module_message_type_start,
	cp_module_message_type_stop,
	cp_module_message_type_create,
	cp_module_message_type_destory,
	cp_module_message_type_open,
	cp_module_message_type_read,
	cp_module_message_type_write,
	cp_module_message_type_close,
	cp_module_message_type_exit,
	cp_module_message_type_end,
};


/************************************************************************/
/* ��Ϣ������                                                          */
/************************************************************************/
struct cp_module_message_process_s
{
	cp_module_message_type_e					mm_type;
	module_message_handle						handle;
};


/************************************************************************/
/* �豸ͨ����Ϣ                                                          */
/************************************************************************/
struct cp_module_message_s
{
	cp_module_message_manager_t					*mmm;										//��ʾͨ����Ӧ�Ĺ�������ַ
	cp_module_t									*module;									//��ʾͨ������ģ��
	cp_module_register_t						*module_register;							//��ʾģ��ע����Ϣ
	cp_module_info_t							*module_info;								//��ʾģ����Ϣ
	cp_void_t									*data;										//��ʾ������Ϣ
	cp_int32_t									index;										//��ʾͨ�����ֱ��
	cp_module_message_process_t					mmp;										//��ʾģ�鴦����
};



/************************************************************************/
/* �豸ͨ��������                                                        */
/************************************************************************/
struct cp_module_message_manager_s
{
	cp_module_manager_t							*manager;									//��ʾģ���������ַ
	cp_log_t									*logger;									//��ʾ��־loggerָ��
	cp_mpool_t									*mpool;										//module_messagemanager�Դ��ļ��ڴ����
	cp_thread_t									*thread;									//��ʾ��Ϣ�����߳�
	cp_safe_queue_t								*mes_sq;									//��ʾ���ݶ�����Ϣ
	cp_module_message_process_t					*mmp_list;									//��ʾ���������
	cp_thread_status_e							thread_status;								//�߳�״̬
};


#pragma pack()



/************************************************************************/
/* ģ����Ϣ�������Ĵ�����                                                  */
/************************************************************************/
cp_module_message_manager_t *create_module_message_manager(cp_module_manager_t	*manager);
cp_int32_t destroy_module_message_manager(cp_module_message_manager_t *mmm);

cp_int32_t init_module_message_manager(cp_module_manager_t	*manager, cp_module_message_manager_t *mmm);
cp_int32_t start_module_message_manager(cp_module_message_manager_t *mmm);
cp_int32_t stop_module_message_manager(cp_module_message_manager_t *mmm);

cp_int32_t set_module_message_process(cp_module_message_manager_t *mmm, cp_module_message_process_t *mmp);


/************************************************************************/
/* ģ����Ϣ�Ĵ�����                                                  */
/************************************************************************/
cp_module_message_t *create_module_message(cp_module_message_manager_t *mmm);
cp_int32_t destroy_module_message(cp_module_message_manager_t *mmm, cp_module_message_t *mm);


cp_int32_t init_module_message(cp_module_message_manager_t *mmm, cp_module_message_t *mm);
cp_int32_t set_module_message(cp_module_message_t *mm, 
	cp_module_t *module, cp_void_t *data, cp_int32_t index, cp_module_message_type_e mm_type, module_message_handle	handle);
cp_int32_t push_module_message(cp_module_message_manager_t *mmm, cp_module_message_t *src);
cp_module_message_t *pop_module_message(cp_module_message_manager_t *mmm);


/************************************************************************/
/* ģ����Ϣ�����̵߳Ĵ�����                                                  */
/************************************************************************/
cp_void_t	module_message_thread_cb_proc(cp_module_message_manager_t *mmm);
cp_int32_t	module_message_general_handle(cp_module_message_manager_t *mmm, cp_module_message_t *src, cp_void_t *data);
cp_int32_t	module_message_addr_handle(cp_module_message_manager_t *mmm, cp_module_message_t *src, cp_void_t *data);
cp_int32_t	module_message_close_handle(cp_module_message_manager_t *mmm, cp_module_message_t *src, cp_void_t *data);




/************************************************************************/
/* ����ģ����Ϣ����Ľӿ���Ϣ                                             */
/************************************************************************/
#define  CP_MODULE_MESSAGE_PROCESS_SET_SINGLE_HANDLER(mmp, handle_name, handle)				\
	(mmp)->handle_name = (handle);															\



/************************************************************************/
/* ����ģ����Ϣ�������ĵ����ӿ���Ϣ                                       */
/************************************************************************/
#define  CP_MODULE_MESSAGE_MANAGER_SET_SINGLE_HANDLER(mmm, handle_name, handle)				\
	CP_MODULE_MESSAGE_PROCESS_SET_SINGLE_HANDLER(&((mmm)->mmp), handle_name, handle)		\



/************************************************************************/
/* ����ģ����Ϣ�������ĵ����ӿ���Ϣ                                       */
/************************************************************************/
#define  CP_MODULE_MESSAGE_MANAGER_SET_HANDLER(mmm, none_handle, add_handle, update_handle, ctrl_handle, remove_handle)	do {			\
	CP_MODULE_MESSAGE_MANAGER_SET_SINGLE_HANDLER((mmm), none, (none_handle));															\
	CP_MODULE_MESSAGE_MANAGER_SET_SINGLE_HANDLER((mmm), add, (add_handle));																\
	CP_MODULE_MESSAGE_MANAGER_SET_SINGLE_HANDLER((mmm), update, (update_handle));														\
	CP_MODULE_MESSAGE_MANAGER_SET_SINGLE_HANDLER((mmm), ctrl, (ctrl_handle));															\
	CP_MODULE_MESSAGE_MANAGER_SET_SINGLE_HANDLER((mmm), remove, (remove_handle));														\
} while (0);																															\


#endif

