/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-12-13

Description:

**************************************************************************/

#ifndef _CP_CHANNEL_MANAGER_INCLUDE_H_
#define _CP_CHANNEL_MANAGER_INCLUDE_H_


#include "cp_core.h"
#include "cp_include.h"
#include "cp_tree_ex.h"



#define CP_CHANNEL_MANAGER_DEFAULT_NUMBER			256							//��ʾĬ�ϵ�ͨ��ͨ����



typedef struct cp_channel_s							cp_channel_t;
typedef struct cp_channel_manager_s					cp_channel_manager_t;


typedef int(*cp_channel_remove_handle)(cp_channel_manager_t *cm, cp_void_t *arg, cp_channel_t *channel);


#pragma pack(1)

/************************************************************************/
/* �豸ͨ����Ϣ                                                          */
/************************************************************************/
struct cp_channel_s
{
	cp_channel_manager_t			*cm;										//��ʾͨ����Ӧ�Ĺ�������ַ
	cp_module_t						*module;									//��ʾͨ������ģ��
	cp_void_t						*data;										//��ʾ������Ϣ
	cp_int32_t						index;										//��ʾͨ�����ֱ��
	cp_char_t						session[CP_APP_DEFAULT_SESSION_ID_LENGTH];	//��ʾͨ������session
	CP_RB_ENTRY(cp_channel_s)		tree_entry;									//��ʾ���������
};


/************************************************************************/
/* ��ʼ�������                                                          */
/************************************************************************/
CP_RB_HEAD(cp_channel_rb_tree_s, cp_channel_s);



/************************************************************************/
/* �豸ͨ��������                                                        */
/************************************************************************/
struct cp_channel_manager_s
{
	cp_app_t						*app;										//��ʾͨ��������������app��ַ
	cp_log_t						*logger;									//��ʾ��־loggerָ��
	cp_mpool_t						*mpool;										//channelmanager�Դ��ļ��ڴ����
	cp_int32_t						max_size;									//��󲥷�ý����
	cp_atomic_t						size;										//��ʾ��ǰ���ڵ�ͨ����
	cp_array_t						channels;									//��Ҫ����������������Ӧ��ͨ��������Ϣ
	struct cp_channel_rb_tree_s		chl_rb_root;								//��ʾ��ڸ��ڵ�
	cp_mutex_t						chl_mutex;									//��ʾͨ��������
};

#pragma pack()




#ifdef __cplusplus
extern "C" {
#endif


/************************************************************************/
/* ͨ���������Ĵ�����                                                  */
/************************************************************************/
int init_channel_manager(cp_app_t *app, cp_channel_manager_t *cm, cp_int32_t max_size);
int start_channel_manager(cp_channel_manager_t *cm);
int stop_channel_manager(cp_channel_manager_t *cm);

int init_channel(cp_channel_manager_t *cm, cp_channel_t *chl);
int set_channel(cp_channel_t *chl, cp_int32_t index, cp_char_t *session, cp_module_t *module, cp_void_t *data);
cp_channel_t *insert_channel(cp_channel_manager_t *cm, cp_channel_t *src);
cp_channel_t *find_channel_by_index(cp_channel_manager_t *cm, cp_int32_t index);
int remove_channel_by_index(cp_channel_manager_t *cm, cp_int32_t index);
int remove_channel(cp_channel_manager_t *cm, cp_channel_t *src);
int remove_all_channel(cp_channel_manager_t *cm, cp_void_t *arg, cp_channel_remove_handle handle);


int find_max_channel_index(cp_channel_manager_t *cm);
int find_min_channel_index(cp_channel_manager_t *cm);
cp_channel_t* find_max_channel(cp_channel_manager_t *cm);
cp_channel_t* find_min_channel(cp_channel_manager_t *cm);


#ifdef __cplusplus
}
#endif



#endif

