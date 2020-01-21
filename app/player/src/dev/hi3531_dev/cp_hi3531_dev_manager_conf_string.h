/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-12-20

Description:

**************************************************************************/

#ifndef _CP_HI3531_DEV_MANAGER_CONF_STRING_INCLUDE_H_
#define _CP_HI3531_DEV_MANAGER_CONF_STRING_INCLUDE_H_



#define CP_HI3531_DEV_MANAGER_CONF_STRING_HI3531_CONFIGURE						"hi3531_configure"							//��ʾhi3531������


#define CP_HI3531_DEV_MANAGER_CONF_STRING_HI3531_SYSTEM							"hi3531_system"								//��ʾhi3531ϵͳ����
#define CP_HI3531_DEV_MANAGER_CONF_STRING_MAX_POOL_COUNT						"max_pool_count"							//��ʾ�����ڴ������
#define CP_HI3531_DEV_MANAGER_CONF_STRING_ALIGN_WIDTH							"align_width"								//��ʾ������


#define CP_HI3531_DEV_MANAGER_CONF_STRING_HI3531_DEV_VDEC						"hi3531_dev_vdec"							//��ʾhi3531 vdec������Ϣ
#define CP_HI3531_DEV_MANAGER_CONF_STRING_VDEC_MPP_DEV_ID						"vdec_mpp_dev_id"							//��ʾģ���豸��
#define CP_HI3531_DEV_MANAGER_CONF_STRING_VDEC_MPP_CHANNEL_NUMBER				"vdec_mpp_channel_number"					//��ʾģ���豸ͨ��ʹ���ڴ�DDR����
#define CP_HI3531_DEV_MANAGER_CONF_STRING_VDEC_MMZ_NAME							"vdec_mmz_name"								//��ʾ�ڴ�����DDR������


#define CP_HI3531_DEV_MANAGER_CONF_STRING_VDEC_VIDEO_ATTR						"vdec_video_attr"							//��ʾ��Ƶ���������Ϣ
#define CP_HI3531_DEV_MANAGER_CONF_STRING_VDEC_MAX_WIDTH						"vdec_max_width"							//��ʾ���֧�ֱַ��ʿ��
#define CP_HI3531_DEV_MANAGER_CONF_STRING_VDEC_MAX_HEIGHT						"vdec_max_height"							//��ʾ���֧�ֱַ��ʸ߶�
#define CP_HI3531_DEV_MANAGER_CONF_STRING_VDEC_REF_FRAME_NUMBER					"vdec_ref_frame_number"						//��ʾ�ο�֡����Ŀ,ȡֵ��Χ[1, 16],��֡Ϊ��λ
#define CP_HI3531_DEV_MANAGER_CONF_STRING_VDEC_STREAM_MODE						"vdec_stream_mode"							//��ʾ�������ͷ�ʽ, 0:��ʾStream������ʽ��1��ʾframe��֡Ϊ��λ
#define CP_HI3531_DEV_MANAGER_CONF_STRING_VDEC_SUPPORT_BFRAME					"vdec_support_bframe"						//��ʾ�Ƿ�֧��B֡����, ȡֵ��Χ[0, 1]


#define CP_HI3531_DEV_MANAGER_CONF_STRING_HI3531_VO								"hi3531_vo"									//���õ�hi3531vo����
#define CP_HI3531_DEV_MANAGER_CONF_STRING_HI3531_VO_ITEMS						"hi3531_vo_items"							//���õ�hi3531vo����
#define CP_HI3531_DEV_MANAGER_CONF_STRING_HI3531_VO_ITEM						"hi3531_vo_item"							//���õ�hi3531vo����
#define CP_HI3531_DEV_MANAGER_CONF_STRING_DEV_ID								"dev_id"									//��ʾģ���豸��
#define CP_HI3531_DEV_MANAGER_CONF_STRING_CHANNEL_ID							"channel_id"								//��ʾģ��ͨ����
#define CP_HI3531_DEV_MANAGER_CONF_STRING_SOURCE_FRAME_RATE						"source_frame_rate"							//��ʾԴ֡����Ϣ
#define CP_HI3531_DEV_MANAGER_CONF_STRING_DEST_FRAME_RATE						"dest_frame_rate"							//��ʾĿ��֡����Ϣ
#define CP_HI3531_DEV_MANAGER_CONF_STRING_BACK_COLOR							"back_color"								//��ʾ�豸����ɫRGB888,��ʽ:XXXXXX,����:001122
#define CP_HI3531_DEV_MANAGER_CONF_STRING_MEM_NAME								"mem_name"									//��ʾ�ڴ�����DDR������
#define CP_HI3531_DEV_MANAGER_CONF_STRING_INTF_TYPE								"intf_type"									//��ʾ�ӿ�����,ȡֵ[0, 8]
#define CP_HI3531_DEV_MANAGER_CONF_STRING_INTF_SYNC								"intf_sync"									//��ʾ�ӿ�ʱ���������,ȡֵ[0, 24]
#define CP_HI3531_DEV_MANAGER_CONF_STRING_ENABLE_DOUBLE_FRAME					"enable_double_frame"						//��ʾ�Ƿ���Ҫ��֡,ȡֵ[0, 1]��0:��ʾ����ʹ�ܣ�1:��ʾʹ��


#define CP_HI3531_DEV_MANAGER_CONF_STRING_HI3531_HDMI							"hi3531_hdmi"								//��ʾHDMI���������Ϣ
#define CP_HI3531_DEV_MANAGER_CONF_STRING_ENABLE_HDMI							"enable_hdmi"								//��ʾ�Ƿ�ǿ��HDMI���,ȡֵ[0, 1]��0:��ʾ����HDMI��ʹ��DVI��1:��ʾ��HDMI
#define CP_HI3531_DEV_MANAGER_CONF_STRING_ENABLE_VIDEO							"enable_video"								//��ʾ�Ƿ������Ƶ,ȡֵ[0, 1]��0:��ʾ����ʹ�ܣ�1:��ʾʹ��
#define CP_HI3531_DEV_MANAGER_CONF_STRING_VIDEO_OUT_MODE						"video_out_mode"							//��ʾHDMI�����Ƶģʽ,ȡֵ[1, 2, 3]��1:��ʾVIDEO_MODE_YCBCR444; 2:��ʾVIDEO_MODE_YCBCR422; 3:��ʾVIDEO_MODE_RGB444
#define CP_HI3531_DEV_MANAGER_CONF_STRING_ENABLE_XVYCC_MODE						"enable_xvycc_mode"							//��ʾ�Ƿ�ʹ��xvYCC���ģʽ,ȡֵ[0, 1]��0:��ʾ����ʹ�ܣ�1:��ʾʹ��
#define CP_HI3531_DEV_MANAGER_CONF_STRING_ENABLE_AUDIO							"enable_audio"								//��ʾ�Ƿ�ʹ����Ƶ,ȡֵ[0, 1]��0:��ʾ����ʹ�ܣ�1:��ʾʹ��
#define CP_HI3531_DEV_MANAGER_CONF_STRING_ENABLE_MULTI_CHANNEL					"enable_multi_channel"						//��ʾ����������������,ȡֵ[0, 1]��0:��ʾ��������1:��ʾ������,�̶�Ϊ8 ����



#endif