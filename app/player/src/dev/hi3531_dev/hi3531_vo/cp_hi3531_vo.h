/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/

#ifndef	_CP_HI3531_VO_INCLUDE_H_
#define _CP_HI3531_VO_INCLUDE_H_



#include "cp_lockfree_queue.h"
#include "cp_hi3531_vo_core.h"
#include "cp_hi3531_vo_conf.h"



#define		CP_HI3531_VO_CHANNEL_NUMBER					64							//��ʾ��ǰhi3531 vo���֧�ֵ�ͨ������
//typedef struct cp_hi3531_vo_s							cp_hi3531_vo_t;




#pragma pack(1)

#define CP_HI3531_VO_FIELDS																										\
		CP_PLAYER_DEV_FIELDS																									\
		cp_hi3531_dev_vo_configure_t					*vo_conf;									/*��ʾ�豸������Ϣ*/			\
		cp_hi3531_vo_channel_configure_t				vo_channels[CP_HI3531_VO_CHANNEL_NUMBER];	/*��ʾ�豸ͨ���б�*/			\


/************************************************************************/
/*                                                                      */
/************************************************************************/
struct cp_hi3531_vo_s {
	CP_HI3531_VO_FIELDS																/*��ʾʱ��ģ����Ϣ*/

#if defined(CP_HI3531_DEV_MODE)
	MPP_CHN_S										vo_mpp_channel;					/*vo mppͨ����Ϣ*/
	VO_PUB_ATTR_S									vo_pub_attr;					/*��Ƶ����������Խṹ��*/
	VO_VIDEO_LAYER_ATTR_S							vo_video_layer_attr;			/*��ʾvo����Ƶ����Ϣ*/
#endif
};

#pragma pack()



cp_hi3531_vo_t* create_hi3531_vo(cp_module_register_t *register_info, cp_codec_manager_t *manager, cp_hi3531_vo_info_t *info);
cp_int32_t destroy_hi3531_vo(cp_codec_manager_t *manager, cp_hi3531_vo_t* hi3531_vo);

#endif


