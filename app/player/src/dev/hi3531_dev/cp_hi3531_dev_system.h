/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2017-06-29

Description:

**************************************************************************/

#ifndef _CP_HI3531_DEV_DEV_SYSTEM_INCLUDE_H_
#define _CP_HI3531_DEV_DEV_SYSTEM_INCLUDE_H_



#include "cp_core.h"
#include "cp_hi3531_dev_include.h"



#define		CP_HI3531_SYSTEM_INFO_BUFFER_LENGTH					128				//hi3531ϵͳ��Ϣ����Ľɴ泤��



typedef struct cp_hi3531_dev_system_info_s						cp_hi3531_dev_system_info_t;


/************************************************************************/
/* hi3531ϵͳ������Ϣ                                                   */
/************************************************************************/
struct cp_hi3531_dev_system_info_s
{
	cp_module_manager_t											*manager;
	cp_char_t													version[CP_HI3531_SYSTEM_INFO_BUFFER_LENGTH];				//hi3531�İ汾��Ϣ
#if defined(CP_HI3531_DEV_MODE)
	MPP_VERSION_S												mpp_version;
	MPP_SYS_CONF_S												sys_conf;
	MPP_CHN_S													mpp_chn;
	VB_CONF_S													vb_conf;
#endif
};


//��ȡhi3531��Ϣ
cp_char_t *get_hi3531_version_info(const cp_module_manager_t *manager);

//��ӡhi3531��Ϣ
cp_char_t *print_hi3531_dev_system_info(const cp_module_manager_t *manager, cp_char_t *buf, cp_int32_t len);

/*����hi3531 ������Ϣ*/
cp_int32_t update_hi3531_dev_system_info(const cp_module_manager_t *manager, cp_hi3531_dev_system_info_t *sys_info);




/*��ʼ��hi3531 ϵͳ��Ϣ*/
cp_int32_t init_hi3531_dev_system(const cp_module_manager_t *manager, cp_hi3531_dev_system_info_t *sys_info);

/*��ʼ��hi3531 vb ������Ϣ*/
cp_int32_t init_hi3531_vb_conf(const cp_module_manager_t *manager, cp_hi3531_dev_system_info_t *sys_info);

/*��ʼ��hi3531 vdec �ڴ�������Ϣ*/
cp_int32_t init_hi3531_vdec_mem_conf(const cp_module_manager_t *manager, cp_hi3531_dev_system_info_t *sys_info);




/*����hi3531 ϵͳ��Ϣ*/
cp_int32_t start_hi3531_dev_system(const cp_module_manager_t *manager, cp_hi3531_dev_system_info_t *sys_info);




/*ֹͣhi3531 ϵͳ��Ϣ*/
cp_int32_t stop_hi3531_dev_system(const cp_module_manager_t *manager);


#endif