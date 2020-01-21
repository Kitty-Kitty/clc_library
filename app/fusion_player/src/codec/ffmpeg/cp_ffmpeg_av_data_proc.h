/*******************************************************************************
*
*Copyright:novigo
*
*File name: cp_ffmpeg_av_data_proc.h
*
*Author:fangzhenmu@novigo.com.cn
*
*Version: 1.0
*
*Date:2017/08/06
*
*Description: create (cp_ffmpeg_av_data_proc.h)
*
*Others:
*
*History:
*******************************************************************************/

#ifndef _CP_FFMPEG_AV_DATA_PROC_H_
#define _CP_FFMPEG_AV_DATA_PROC_H_



#include "cp_ffmpeg_av_codec_core.h"



//创建file info信息
cp_int32_t create_ffmpeg_av_data_proc(cp_ffmpeg_av_codec_t *ffmpeg_av_codec);

//初始化file info信息
cp_int32_t init_ffmpeg_av_data_proc(cp_ffmpeg_av_codec_t *ffmpeg_av_codec);

//打开file info信息
cp_int32_t open_ffmpeg_av_data_proc(cp_ffmpeg_av_codec_t *ffmpeg_av_codec, cp_media_description_t *md);

//读取模块数据，flag为读取模式的扩展标志。默认为0，其他为预留
cp_int32_t read_ffmpeg_av_data_stream(cp_ffmpeg_av_codec_t *ffmpeg_av_codec,
	cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag);

//写模块数据，flag为写模式的扩展标志。默认为0，其他为预留
cp_int32_t write_ffmpeg_av_data_stream(cp_ffmpeg_av_codec_t *ffmpeg_av_codec,
	const cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag);

//关闭file info信息
cp_int32_t close_ffmpeg_av_data_proc(cp_ffmpeg_av_codec_t *ffmpeg_av_codec);

//退出file info信息
cp_int32_t exit_ffmpeg_av_data_proc(cp_ffmpeg_av_codec_t *ffmpeg_av_codec);

//消毁file info
cp_int32_t destroy_ffmpeg_av_data_proc(cp_ffmpeg_av_codec_t *ffmpeg_av_codec);




/*打开解码器信息*/
cp_int32_t open_ffmpeg_av_codec_data(cp_ffmpeg_av_codec_t *ffmpeg_av_codec, cp_media_description_t *md);

/*关闭解码器信息*/
cp_int32_t close_ffmpeg_av_codec_data(cp_ffmpeg_av_codec_t *ffmpeg_av_codec);




//打开测试文件
cp_bool_t open_test_file(cp_ffmpeg_av_codec_t *ffmpeg_av_codec);

//关闭测试文件
cp_bool_t close_test_file(cp_ffmpeg_av_codec_t *ffmpeg_av_codec);




#endif //_CP_FFMPEG_AV_DATA_PROC_H_


