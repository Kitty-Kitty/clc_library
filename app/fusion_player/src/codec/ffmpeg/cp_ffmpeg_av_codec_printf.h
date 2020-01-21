/*******************************************************************************
*
*Copyright:novigo
*
*File name: cp_ffmpeg_av_codec_printf.h
*
*Author:fangzhenmu@novigo.com.cn
*
*Version: 1.0
*
*Date:2017/08/05
*
*Description: create (cp_ffmpeg_av_codec_printf.h)
*
*Others:
*
*History:
*******************************************************************************/

#ifndef _CP_FFMPEG_AV_CODEC_PRINTF_H_
#define _CP_FFMPEG_AV_CODEC_PRINTF_H_



#include "libavformat/avformat.h"




//这里重新包装了打印信息的格式
#define	 cp_ffmepg_av_codec_log(level, ffmepg_av_codec, format, ...)								\
	do {																							\
			cp_module_log(level, (ffmepg_av_codec), "ffmepg[%d] " format,							\
				avformat_version(),																	\
				##__VA_ARGS__)																		\
	;} while (0)			



#endif //_CP_FFMPEG_AV_CODEC_PRINTF_H_


