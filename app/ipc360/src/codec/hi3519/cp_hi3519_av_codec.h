/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/

#ifndef	_CP_HI3519_AV_CODEC_INCLUDE_H_
#define _CP_HI3519_AV_CODEC_INCLUDE_H_

#include "cp_hi3519_av_codec_core.h"



#define	CP_HI3519_AV_CODEC_DEFAULT_VI_CHN_CNT			2						//��ʾĬ�ϵ�ͨ������



#if defined(WIN32)
#define	 CP_HI3519_AV_CODEC_FILE_DEMO					1
#define  CP_HI3519_AV_CODEC_FILE_DEBUG					2
#endif



#if defined(CP_HI3519_AV_CODEC_FILE_DEMO)
#define	CP_HI3519_AV_CODEC_VIDEO_BUFFER_LENGTH			5 * 1024 * 1024			//
#define	CP_HI3519_AV_CODEC_VIDEO_FILE_PATH				"1920x1080_ma_f30_i30.h264"
#endif

#if defined(CP_HI3519_AV_CODEC_FILE_DEBUG)
#define	CP_HI3519_AV_CODEC_VIDEO_DEMO_FILE_PATH			"demo_debug.h264"		//�����ļ�Ŀ¼
#endif


//typedef struct cp_hi3519_av_codec_s					cp_hi3519_av_codec_t;




#pragma pack(1)


#define CP_HI3519_AV_CODEC_FIELDS																	\
		CP_IPC_CODEC_FIELDS																			\



/************************************************************************/
/*                                                                      */
/************************************************************************/
struct cp_hi3519_av_codec_s {
	CP_HI3519_AV_CODEC_FIELDS											/*��ʾʱ��ģ����Ϣ*/

#if defined(CP_HI3519_AV_CODEC_FILE_DEBUG)
		FILE											*file;			/*ý���ļ�*/
	cp_int32_t											index;
#endif

#if defined(CP_HI3519_AV_CODEC_FILE_DEMO)
	FILE												*video_file;	/*��ʾ�����õ��ļ�*/
	cp_buf_t											data_buf;		/*��ʾ���ݻ�����*/
	cp_rtp_socket_data_t								*rtp_sd;							//���������ݶ���
#endif
	cp_hi3519_av_conf_t									*av_conf;		/*��ʾ����������Ϣ*/
	cp_ipc_rtp_session_t								*rtp_session;	/**/
	cp_hi3519_av_codec_configure_t						hacc;			/*��ʾ��ǰ�ı�����������Ϣ*/

};


#pragma pack()



cp_hi3519_av_codec_t* create_hi3519_av_codec(cp_module_register_t *register_info, cp_codec_manager_t *manager, cp_hi3519_av_codec_info_t *info);
cp_int32_t destroy_hi3519_av_codec(cp_codec_manager_t *manager, cp_hi3519_av_codec_t* hi3519_av_codec);

#endif


