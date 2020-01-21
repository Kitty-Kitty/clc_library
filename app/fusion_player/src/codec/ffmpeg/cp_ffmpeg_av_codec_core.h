/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/

#ifndef	_CP_FFMEPG_AV_CODEC_CORE_INCLUDE_H_
#define _CP_FFMEPG_AV_CODEC_CORE_INCLUDE_H_





typedef	struct cp_ffmepg_av_probe_info_s					cp_ffmepg_av_probe_info_t;
typedef struct cp_ffmpeg_av_codec_info_s					cp_ffmpeg_av_codec_info_t;
typedef	struct cp_ffmpeg_av_codec_s							cp_ffmpeg_av_codec_t;
typedef struct cp_ffmpeg_av_file_info_s						cp_ffmpeg_av_file_info_t;



//#define		CP_FFMPEG_AV_CODEC_FILE_DEBUG					1
#include "libavcodec/avcodec.h"
#include "libswscale/swscale.h"
#include "libavformat/avformat.h"
//#include "libavfilter/avfiltergraph.h"
//#include "libavfilter/buffersink.h"
//#include "libavfilter/buffersrc.h"
//#include "libavutil/avutil.h"
//#include "libavutil/imgutils.h"


#include "cp_core.h"
#include "cp_codec_core.h"
#include "cp_fusion_player_codec_core.h"
#include "cp_ffmpeg_av_codec_printf.h"
#include "cp_ffmpeg_av_codec_conf.h"
#include "cp_ffmpeg_av_audio_format.h"
#include "cp_ffmpeg_av_audio_channel_layout.h"
#include "cp_ffmpeg_av_codec_info.h"
#include "cp_ffmpeg_av_codec.h"
#include "cp_ffmpeg_av_media_probe.h"



#endif


