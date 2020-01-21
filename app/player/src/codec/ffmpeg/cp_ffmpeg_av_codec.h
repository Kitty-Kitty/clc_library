/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/

#ifndef	_CP_FFMEPG_AV_CODEC_INCLUDE_H_
#define _CP_FFMEPG_AV_CODEC_INCLUDE_H_

#include "cp_ffmpeg_av_codec_core.h"
#include "libavcodec/avcodec.h"
#include "libswscale/swscale.h"
#include "libavformat/avformat.h"
//#include "libavfilter/avfiltergraph.h"
//#include "libavfilter/buffersink.h"
//#include "libavfilter/buffersrc.h"
//#include "libavutil/avutil.h"
//#include "libavutil/imgutils.h"



//typedef struct cp_ffmpeg_av_codec_s									cp_ffmpeg_av_codec_t;
#define		CP_FFMPEG_AV_CODEC_DEFAULT_CHANNELS							2



#pragma pack(1)


#define CP_FFMEPG_AV_CODEC_FIELDS																		\
		CP_PLAYER_CODEC_FIELDS																			\
		cp_bool_t					is_used_probe;					/*��ʾ�Ƿ�ʹ����Ƶ��̽����*/			\
		AVCodec						*codec;							/*������*/							\
		AVCodecContext				*codec_context;					/*������������Ϣ*/					\
		AVPacket					avpkt;							/*av packet��Ϣ*/					\
		AVFrame						decoded_frame;					/*����֡����*/						\
		AVFrame						decoded_convert_frame;			/*����֡yuv����*/					\



/************************************************************************/
/*                                                                      */
/************************************************************************/
struct cp_ffmpeg_av_codec_s {
	CP_FFMEPG_AV_CODEC_FIELDS										/*��ʾʱ��ģ����Ϣ*/

#if defined(CP_FFMPEG_AV_CODEC_FILE_DEBUG)
		FILE											*file;		/*ý���ļ�*/
#endif
	cp_int32_t											decodec_failed_times;							//��ʾ����������
	cp_int32_t											decodec_successed_times;						//��ʾ����ɹ�����
	cp_mutex_t											process_probe_mutex;							/*����ý��̽���״̬�������*/
	cp_media_description_t								md;												/*��ʾý��Դ������Ϣ*/
	cp_ffmpeg_av_dev_video_info_t						*video_info;									/*��ʾ��Ƶ���������Ϣ*/
	cp_ffmpeg_av_dev_audio_info_t						*audio_info;									/*��ʾ��Ƶ���������Ϣ*/

};


#pragma pack()



cp_ffmpeg_av_codec_t* create_ffmpeg_av_codec(cp_module_register_t *register_info, cp_codec_manager_t *manager, cp_ffmpeg_av_codec_info_t *info);
cp_int32_t destroy_ffmpeg_av_codec(cp_codec_manager_t *manager, cp_ffmpeg_av_codec_t* ffmpeg_av_codec);



#endif


