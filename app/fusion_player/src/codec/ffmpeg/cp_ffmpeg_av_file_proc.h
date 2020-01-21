/*******************************************************************************
*
*Copyright:novigo
*
*File name: cp_ffmpeg_av_file_proc.h
*
*Author:fangzhenmu@novigo.com.cn
*
*Version: 1.0
*
*Date:2017/08/06
*
*Description: create (cp_ffmpeg_av_file_proc.h)
*
*Others:
*
*History:
*******************************************************************************/

#ifndef _CP_FFMPEG_AV_FILE_PROC_H_
#define _CP_FFMPEG_AV_FILE_PROC_H_



#include "cp_ffmpeg_av_codec_core.h"
#include "cp_ffmpeg_av_file_conf.h"



#define	CP_FFMPEG_AV_FILE_SQ_DEFAULT_CACHE_SIZE				64											//表示默认的缓存区数据
#define CP_FFMPEG_AV_FILE_SQ_DEFAULT_SLEEP_INTERVAL			1000000										//默认的休眠间隔时间，单位纳秒


typedef struct cp_ffmpeg_av_file_info_s						cp_ffmpeg_av_file_info_t;



/************************************************************************/
/* ffmpeg 文件信息                                                       */
/************************************************************************/
struct cp_ffmpeg_av_file_info_s
{
	cp_ffmpeg_av_codec_t									*ffmpeg_av_codec;							//解码信息
	cp_int32_t												max_cache_size;								//表示最大缓存数量
	cp_int32_t												min_cache_size;								//表示最小缓存数量
	cp_safe_queue_t											*data_sq;									//表示解码后的媒体数据
	cp_thread_status_e										decode_thread_status;						//表示解码线程状态
	cp_thread_t												*decode_thread;								//表示解码线程
};


//创建file info信息
cp_int32_t create_ffmpeg_av_file_info(cp_ffmpeg_av_codec_t *ffmpeg_av_codec);

//初始化file info信息
cp_int32_t init_ffmpeg_av_file_info(cp_ffmpeg_av_codec_t *ffmpeg_av_codec);

//打开file info信息
cp_int32_t open_ffmpeg_av_file_info(cp_ffmpeg_av_codec_t *ffmpeg_av_codec, cp_media_description_t *md);

//读取模块数据，flag为读取模式的扩展标志。默认为0，其他为预留
cp_int32_t read_ffmpeg_av_file_data(cp_ffmpeg_av_codec_t *ffmpeg_av_codec,
	cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag);

//写模块数据，flag为写模式的扩展标志。默认为0，其他为预留
cp_int32_t write_ffmpeg_av_file_data(cp_ffmpeg_av_codec_t *ffmpeg_av_codec,
	const cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag);

//关闭file info信息
cp_int32_t close_ffmpeg_av_file_info(cp_ffmpeg_av_codec_t *ffmpeg_av_codec);

//退出file info信息
cp_int32_t exit_ffmpeg_av_file_info(cp_ffmpeg_av_codec_t *ffmpeg_av_codec);

//消毁file info
cp_int32_t destroy_ffmpeg_av_file_info(cp_ffmpeg_av_codec_t *ffmpeg_av_codec);

/*打开url指定的媒体源信息*/
cp_int32_t open_ffmpeg_av_file_stream(cp_ffmpeg_av_codec_t *ffmpeg_av_codec, cp_media_description_t *md);

/*关闭url指定的媒体源信息*/
cp_int32_t close_ffmpeg_av_file_stream(cp_ffmpeg_av_codec_t *ffmpeg_av_codec);




//启动解码线程
cp_int32_t start_ffmpeg_av_decode_thread_process(cp_ffmpeg_av_codec_t *ffmpeg_av_codec);

//停止解码线程
cp_int32_t stop_ffmpeg_av_decode_thread_process(cp_ffmpeg_av_codec_t *ffmpeg_av_codec);

//解码线程处理
void ffmpeg_av_decode_thread_cb_proc(cp_ffmpeg_av_codec_t *ffmpeg_av_codec);







#endif //_CP_FFMPEG_AV_FILE_PROC_H_




