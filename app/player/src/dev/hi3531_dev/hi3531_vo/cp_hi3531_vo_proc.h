/*******************************************************************************
*
*Copyright:novigo
*
*File name: cp_hi3531_vo_proc.h
*
*Author:fangzhenmu@novigo.com.cn
*
*Version: 1.0
*
*Date:2017/07/28
*
*Description: create (cp_hi3531_vo_proc.h)
*
*Others:
*
*History:
*******************************************************************************/

#ifndef _CP_HI3531_VO_PROC_H_
#define _CP_HI3531_VO_PROC_H_


#include "cp_hi3531_vo_core.h"




typedef enum cp_hi3531_vo_intf_sync_enum						cp_hi3531_vo_intf_sync_e;
typedef struct cp_hi3531_vo_resolution_attribute_struct			cp_hi3531_vo_resolution_attribute_t;


//////////////////////////////////////////////////////////////////////////
//vo ͬ������
//////////////////////////////////////////////////////////////////////////
enum cp_hi3531_vo_intf_sync_enum
{
	CP_HI3531_VO_INTF_SYNC_PAL,
	CP_HI3531_VO_INTF_SYNC_NTSC,
	CP_HI3531_VO_INTF_SYNC_800x600_60,
	CP_HI3531_VO_INTF_SYNC_720P50,
	CP_HI3531_VO_INTF_SYNC_1080P24,
	CP_HI3531_VO_INTF_SYNC_720P60,
	CP_HI3531_VO_INTF_SYNC_1080P30,
	CP_HI3531_VO_INTF_SYNC_1080P25,
	CP_HI3531_VO_INTF_SYNC_1080P50,
	CP_HI3531_VO_INTF_SYNC_1080P60,
	CP_HI3531_VO_INTF_SYNC_1024x768_60,
	CP_HI3531_VO_INTF_SYNC_1280x1024_60,
	CP_HI3531_VO_INTF_SYNC_1366x768_60,
	CP_HI3531_VO_INTF_SYNC_1440x900_60,
	CP_HI3531_VO_INTF_SYNC_1280x800_60,
};

struct cp_hi3531_vo_resolution_attribute_struct
{
	cp_hi3531_vo_intf_sync_e				sync;							//��ʾvo sync������Ϣ
	cp_int32_t								width;							//��ʾ�����Ϣ
	cp_int32_t								height;							//��ʾ�߶���Ϣ
	cp_int32_t								frame_rate;						//��ʾ֡����Ϣ
};


//��ȡ�豸�ķֱ�����Ϣ
cp_int32_t hi3531_vo_get_resolution_attribute(cp_int32_t intf_sync, cp_int32_t *width, cp_int32_t *height, cp_int32_t *frame_rate);

//�豸�ڴ���Ϣ
cp_int32_t hi3531_vo_set_mem_conf(cp_hi3531_vo_t *hi3531_vo, cp_hi3531_dev_vo_configure_t *vo_conf);



//��Ƶ����������Խṹ��
cp_int32_t hi3531_vo_set_pub_attr(cp_hi3531_vo_t *hi3531_vo, cp_hi3531_dev_vo_configure_t *vo_conf);

//�����豸ͼ����Ϣ
cp_int32_t hi3531_vo_set_dev_video_layer(cp_hi3531_vo_t *hi3531_vo, cp_hi3531_dev_vo_configure_t *vo_conf);

//����voͨ����Ϣ
cp_int32_t hi3531_vo_set_channels_conf(cp_hi3531_vo_t *hi3531_vo, cp_hi3531_dev_vo_configure_t *vo_conf);





//�����豸ͼ����Ϣ
cp_int32_t hi3531_vo_start_dev_video_layer(cp_hi3531_vo_t *hi3531_vo, cp_hi3531_dev_vo_configure_t *vo_conf);

//�����豸ͨ�����豸��Ϣ
cp_int32_t hi3531_vo_start_dev_channels(cp_hi3531_vo_t *hi3531_vo, cp_hi3531_dev_vo_configure_t *vo_conf);

//�����豸
cp_int32_t hi3531_vo_start_dev(cp_hi3531_vo_t *hi3531_vo, cp_hi3531_dev_vo_configure_t *vo_conf);


//дģ������
cp_int32_t hi3531_vo_write_frame_data(cp_hi3531_vo_t *hi3531_vo, cp_video_frame_process_t *vfp);



//ֹͣ�豸ͼ����Ϣ
cp_int32_t hi3531_vo_stop_dev_video_layer(cp_hi3531_vo_t *hi3531_vo);

//ֹͣ�豸ͨ�����豸��Ϣ
cp_int32_t hi3531_vo_stop_dev_channels(cp_hi3531_vo_t *hi3531_vo);

//ֹͣ�豸
cp_int32_t hi3531_vo_stop_dev(cp_hi3531_vo_t *hi3531_vo);




#endif //_CP_HI3531_VO_PROC_H_


