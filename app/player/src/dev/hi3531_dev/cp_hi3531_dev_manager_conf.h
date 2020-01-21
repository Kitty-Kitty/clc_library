/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-12-20

Description:

**************************************************************************/

#ifndef _CP_HI3531_DEV_MANAGER_CONF_INCLUDE_H_
#define _CP_HI3531_DEV_MANAGER_CONF_INCLUDE_H_


#include "cp_core.h"
#include "cp_module_core.h"
#include "cp_hi3531_dev_manager_conf_string.h"




//������������
#define		CP_HI3531_DEV_VDEC_MEMORY_NAME_SIZE											16				//��ʾvdec�ڴ����Ƴ���
#define		CP_HI3531_DEV_VO_BACK_COLOR_STRING_SIZE										16				//��ʾvo����ɫ�ֽڳ���
#define		CP_HI3531_DEV_VO_MEM_NAME_STRING_SIZE										16				//��ʾvo�ڴ����Ƴ���
#define		CP_HI3531_DEV_VO_DEVICE_SIZE												8				//��ʾvo�豸���������


typedef struct	cp_hi3531_dev_system_configure_s										cp_hi3531_dev_system_configure_t;
typedef struct	cp_hi3531_dev_vdec_configure_s											cp_hi3531_dev_vdec_configure_t;
typedef struct cp_hi3531_dev_vo_configure_s												cp_hi3531_dev_vo_configure_t;
typedef struct cp_hi3531_dev_hdmi_configure_s											cp_hi3531_dev_hdmi_configure_t;
typedef struct	cp_hi3531_dev_configure_s												cp_hi3531_dev_configure_t;



/************************************************************************/
/* hi3531ϵͳ�������                                                      */
/************************************************************************/
struct cp_hi3531_dev_system_configure_s
{
	cp_int32_t								max_pool_count;												//��ʾ�����ڴ������
	cp_int32_t								align_width;												//��ʾ������
};


/************************************************************************/
/* hi3531�����������                                                      */
/************************************************************************/
struct cp_hi3531_dev_vdec_configure_s
{
	cp_int32_t								vdec_mpp_dev_id;											//��ʾģ���豸��
	cp_int32_t								vdec_mpp_channel_number;									//��ʾģ���豸ͨ��ʹ���ڴ�DDR����
	cp_char_t								vdec_mmz_name[CP_HI3531_DEV_VDEC_MEMORY_NAME_SIZE];			//��ʾ�ڴ�����DDR������
};


/************************************************************************/
/* hi3531vo�������                                                      */
/************************************************************************/
struct cp_hi3531_dev_vo_configure_s
{
	cp_int32_t								dev_id;														//��ʾ�豸���,ȡֵ[0, 7]
	cp_int32_t								channel_id;													//��ʾͨ�����,ȡֵ[0, 7]
	cp_int32_t								source_frame_rate;											//��ʾ��ʾԴ֡����Ϣ
	cp_int32_t								dest_frame_rate;											//��ʾ��ʾĿ��֡����Ϣ
	cp_int32_t								intf_type;													//�ӿ�����,ȡֵ[0, 8]
	cp_int32_t								intf_sync;													//�ӿ�ʱ���������,ȡֵ[0, 24]
	cp_bool_t								enable_double_frame;										//�Ƿ���Ҫ��֡,ȡֵ[0, 1]��0:��ʾ����ʹ�ܣ�1:��ʾʹ��
	cp_bool_t								is_used;													//����Ƿ�ʹ��
	cp_char_t								back_color[CP_HI3531_DEV_VO_BACK_COLOR_STRING_SIZE];		//��ʾ����ɫ�ֽ�
	cp_char_t								mem_name[CP_HI3531_DEV_VO_MEM_NAME_STRING_SIZE];			//��ʾ�ڴ�����DDR������
};


/************************************************************************/
/* hi3531 hdmi �������                                                  */
/************************************************************************/
struct cp_hi3531_dev_hdmi_configure_s
{
	cp_int32_t								dev_id;														//��ʾ�豸���,ȡֵ[0, 7]
	cp_bool_t								enable_hdmi;												//�Ƿ�ǿ��HDMI���,ȡֵ[0, 1]��0:��ʾ����HDMI��ʹ��DVI��1:��ʾ��HDMI
	cp_bool_t								enable_video;												//�Ƿ������Ƶ,ȡֵ[0, 1]��0:��ʾ����ʹ�ܣ�1:��ʾʹ��
	cp_int32_t								video_out_mode;												//HDMI�����Ƶģʽ,ȡֵ[1, 2, 3]��1:��ʾVIDEO_MODE_YCBCR444; 2:��ʾVIDEO_MODE_YCBCR422; 3:��ʾVIDEO_MODE_RGB444
	cp_bool_t								enable_xvycc_mode;											//�Ƿ�ʹ��xvYCC���ģʽ,ȡֵ[0, 1]��0:��ʾ����ʹ�ܣ�1:��ʾʹ��
	cp_bool_t								enable_audio;												//�Ƿ�ʹ����Ƶ,ȡֵ[0, 1]��0:��ʾ����ʹ�ܣ�1:��ʾʹ��
	cp_bool_t								enable_multi_channel;										//����������������,ȡֵ[0, 1]��0:��ʾ��������1:��ʾ������,�̶�Ϊ8 ����
};


/************************************************************************/
/* ��Ƶ�����������                                                      */
/************************************************************************/
struct cp_hi3531_dev_configure_s
{
	cp_hi3531_dev_system_configure_t		system_conf;											//��ʾϵͳ����������
	cp_hi3531_dev_vdec_configure_t			vdec_conf;												//��ʾhi3531 vdec������Ϣ
	cp_hi3531_dev_vo_configure_t			vo_conf[CP_HI3531_DEV_VO_DEVICE_SIZE];					//��ʾvo������Ϣ
	cp_hi3531_dev_hdmi_configure_t			hdmi_conf;												//��ʾhdmi������Ϣ
};


/************************************************************************/
/*���������ļ�                                                           */
/************************************************************************/
cp_int32_t	hi3531_dev_manager_parse_configure(const cp_module_manager_t *manager, cp_hi3531_dev_configure_t *hacc);

/************************************************************************/
/*����system�����ļ�                                                     */
/************************************************************************/
cp_int32_t	hi3531_dev_manager_parse_system_configure(const cp_module_manager_t *manager, cp_hi3531_dev_configure_t *hacc);

/************************************************************************/
/*����vdec�����ļ�                                                     */
/************************************************************************/
cp_int32_t	hi3531_dev_manager_parse_vdec_configure(const cp_module_manager_t *manager, cp_hi3531_dev_configure_t *hacc);

/************************************************************************/
/*����vo�����ļ�                                                     */
/************************************************************************/
cp_int32_t	hi3531_dev_manager_parse_vo_configure(const cp_module_manager_t *manager, cp_hi3531_dev_configure_t *hacc);

/************************************************************************/
/*����hdmi�����ļ�                                                     */
/************************************************************************/
cp_int32_t	hi3531_dev_manager_parse_hdmi_configure(const cp_module_manager_t *manager, cp_hi3531_dev_configure_t *hacc);

#endif