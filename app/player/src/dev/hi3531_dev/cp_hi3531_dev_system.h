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



#define		CP_HI3531_SYSTEM_INFO_BUFFER_LENGTH					128				//hi3531系统信息保存的缴存长度



typedef struct cp_hi3531_dev_system_info_s						cp_hi3531_dev_system_info_t;


/************************************************************************/
/* hi3531系统配置信息                                                   */
/************************************************************************/
struct cp_hi3531_dev_system_info_s
{
	cp_module_manager_t											*manager;
	cp_char_t													version[CP_HI3531_SYSTEM_INFO_BUFFER_LENGTH];				//hi3531的版本信息
#if defined(CP_HI3531_DEV_MODE)
	MPP_VERSION_S												mpp_version;
	MPP_SYS_CONF_S												sys_conf;
	MPP_CHN_S													mpp_chn;
	VB_CONF_S													vb_conf;
#endif
};


//获取hi3531信息
cp_char_t *get_hi3531_version_info(const cp_module_manager_t *manager);

//打印hi3531信息
cp_char_t *print_hi3531_dev_system_info(const cp_module_manager_t *manager, cp_char_t *buf, cp_int32_t len);

/*更新hi3531 配置信息*/
cp_int32_t update_hi3531_dev_system_info(const cp_module_manager_t *manager, cp_hi3531_dev_system_info_t *sys_info);




/*初始化hi3531 系统信息*/
cp_int32_t init_hi3531_dev_system(const cp_module_manager_t *manager, cp_hi3531_dev_system_info_t *sys_info);

/*初始化hi3531 vb 配置信息*/
cp_int32_t init_hi3531_vb_conf(const cp_module_manager_t *manager, cp_hi3531_dev_system_info_t *sys_info);

/*初始化hi3531 vdec 内存配置信息*/
cp_int32_t init_hi3531_vdec_mem_conf(const cp_module_manager_t *manager, cp_hi3531_dev_system_info_t *sys_info);




/*启动hi3531 系统信息*/
cp_int32_t start_hi3531_dev_system(const cp_module_manager_t *manager, cp_hi3531_dev_system_info_t *sys_info);




/*停止hi3531 系统信息*/
cp_int32_t stop_hi3531_dev_system(const cp_module_manager_t *manager);


#endif