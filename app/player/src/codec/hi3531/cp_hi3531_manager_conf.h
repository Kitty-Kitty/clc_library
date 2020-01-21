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




//������������
#define		CP_HI3531_VDEC_MEMORY_NAME_SIZE											16



typedef struct	cp_hi3531_system_configure_s										cp_hi3531_system_configure_t;
typedef struct	cp_hi3531_vdec_configure_s											cp_hi3531_vdec_configure_t;
typedef struct	cp_hi3531_configure_s												cp_hi3531_configure_t;



/************************************************************************/
/* hi3531ϵͳ�������                                                      */
/************************************************************************/
struct cp_hi3531_system_configure_s
{
	cp_int32_t							max_pool_count;											//��ʾ�����ڴ������
	cp_int32_t							align_width;											//��ʾ������
};


/************************************************************************/
/* hi3531�����������                                                      */
/************************************************************************/
struct cp_hi3531_vdec_configure_s
{
	cp_int32_t							vdec_mpp_dev_id;										//��ʾģ���豸��
	cp_int32_t							vdec_mpp_channel_number;								//��ʾģ���豸ͨ��ʹ���ڴ�DDR����
	cp_char_t							vdec_mmz_name[CP_HI3531_VDEC_MEMORY_NAME_SIZE];			//��ʾ�ڴ�����DDR������
};

/************************************************************************/
/* ��Ƶ�����������                                                      */
/************************************************************************/
struct cp_hi3531_configure_s
{
	cp_hi3531_system_configure_t		system_conf;											//��ʾϵͳ����������
	cp_hi3531_vdec_configure_t			vdec_conf;												//��ʾhi3531 vdec������Ϣ
};


/************************************************************************/
/*���������ļ�                                                           */
/************************************************************************/
cp_int32_t	hi3531_manager_parse_configure(const cp_module_manager_t *manager, cp_hi3531_configure_t *hacc);

/************************************************************************/
/*����system�����ļ�                                                     */
/************************************************************************/
cp_int32_t	hi3531_manager_parse_system_configure(const cp_module_manager_t *manager, cp_hi3531_configure_t *hacc);

/************************************************************************/
/*����vdec�����ļ�                                                     */
/************************************************************************/
cp_int32_t	hi3531_manager_parse_vdec_configure(const cp_module_manager_t *manager, cp_hi3531_configure_t *hacc);



#endif