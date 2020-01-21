/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-12-20

Description:

**************************************************************************/

#ifndef _CP_HI3531_MANAGER_CONF_INCLUDE_H_
#define _CP_HI3531_MANAGER_CONF_INCLUDE_H_


#include "cp_core.h"
#include "cp_module_core.h"
#include "cp_hi3531_manager_conf_string.h"




//定义配置数量
#define		CP_HI3531_VDEC_MEMORY_NAME_SIZE											16



typedef struct	cp_hi3531_system_configure_s										cp_hi3531_system_configure_t;
typedef struct	cp_hi3531_vdec_configure_s											cp_hi3531_vdec_configure_t;
typedef struct	cp_hi3531_configure_s												cp_hi3531_configure_t;



/************************************************************************/
/* hi3531系统相关配置                                                      */
/************************************************************************/
struct cp_hi3531_system_configure_s
{
	cp_int32_t							max_pool_count;											//表示最大的内存池数量
	cp_int32_t							align_width;											//表示对齐宽度
};


/************************************************************************/
/* hi3531解码相关配置                                                      */
/************************************************************************/
struct cp_hi3531_vdec_configure_s
{
	cp_int32_t							vdec_mpp_dev_id;										//表示模块设备号
	cp_int32_t							vdec_mpp_channel_number;								//表示模块设备通道使用内存DDR数量
	cp_char_t							vdec_mmz_name[CP_HI3531_VDEC_MEMORY_NAME_SIZE];			//表示内存所在DDR的名字
};

/************************************************************************/
/* 音频处理相关配置                                                      */
/************************************************************************/
struct cp_hi3531_configure_s
{
	cp_hi3531_system_configure_t		system_conf;											//表示系统配置项内容
	cp_hi3531_vdec_configure_t			vdec_conf;												//表示hi3531 vdec配置信息
};


/************************************************************************/
/*解析配置文件                                                           */
/************************************************************************/
cp_int32_t	hi3531_manager_parse_configure(const cp_module_manager_t *manager, cp_hi3531_configure_t *hacc);

/************************************************************************/
/*解析system配置文件                                                     */
/************************************************************************/
cp_int32_t	hi3531_manager_parse_system_configure(const cp_module_manager_t *manager, cp_hi3531_configure_t *hacc);

/************************************************************************/
/*解析vdec配置文件                                                     */
/************************************************************************/
cp_int32_t	hi3531_manager_parse_vdec_configure(const cp_module_manager_t *manager, cp_hi3531_configure_t *hacc);



#endif