/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2017-01-20

Description:

**************************************************************************/

#ifndef _CP_FFMPEG_AV_MEDIA_PROBE_INCLUDE_H_
#define _CP_FFMPEG_AV_MEDIA_PROBE_INCLUDE_H_



#include "cp_ffmpeg_av_codec_core.h"
#include "libavcodec/avcodec.h"
#include "libswscale/swscale.h"
#include "libavformat/avformat.h"
#include "cp_safe_queue.h"



/*是否启动debug file*/
//#define		CP_FFMPEG_AV_PROBE_FILE_DEBUG								1
#define		CP_FFMPEG_AV_PROBE_FILE_NAME_LENGTH							1024

/* media probe safe queue bufferf size缓存大小 */
#define		CP_FFMPEG_AV_CODEC_SAFE_QUEUE_BUFFER_SIZE					1024

/*probe buffer size*/
#define		CP_FFMPEG_AV_CODEC_PROBE_BUFFER_SIZE						4096 * 500

//表示默认的休眠间隔
#define		CP_FFMPEG_AV_CODEC_PROBE_INTERVAL_NS						1000000



//表示probe状态信息
typedef		enum cp_ffmepg_av_probe_status_enum							cp_ffmepg_av_probe_status_e;


/************************************************************************/
/* ffmpeg 状态信息                                                       */
/************************************************************************/
enum cp_ffmepg_av_probe_status_enum
{
	cp_ffmepg_av_probe_status_none,										//
	cp_ffmepg_av_probe_status_init,
	cp_ffmepg_av_probe_status_probe,
	cp_ffmepg_av_probe_status_unprobe,
	cp_ffmepg_av_probe_status_start,
	cp_ffmepg_av_probe_status_stop,
	cp_ffmepg_av_probe_status_exit,
};

/************************************************************************/
/* ffmpeg 测试信息                                                      */
/************************************************************************/
struct cp_ffmepg_av_probe_info_s
{
	cp_ffmpeg_av_codec_t			*codec;								/*表示codec信息*/
	cp_safe_queue_t					*sq;								/*数据缓存队列*/
	cp_thread_t						*thread;							/*probe修理线程*/
	AVFormatContext					*format_ctx;						/*格式上不文*/
	AVIOContext						*pb;
	AVCodec							*media_codec;						/*解码器*/
	AVCodecContext					*media_codec_context;				/*解码器描述信息*/
	cp_uchar_t						*buf;								/*表示临时缓存地址*/
	cp_int32_t						faile_times;						/*表示decode错误次数*/
	cp_int32_t						successed_times;					/*表示decode成功的次数*/

	cp_ffmepg_av_probe_status_e		status;								/*表示状态信息*/

#if defined CP_FFMPEG_AV_PROBE_FILE_DEBUG
	FILE							*file;								/*表示debug文件*/
#endif
};



/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: cp_ffmpeg_av_codec_init_media_probe
*
* 函数说明: 初始化media probe
*
* 参    数: cp_ffmpeg_av_codec_t * ffmpeg_av_codec						[in]参数说明
*
* 返 回 值: cp_int32_t
*           0  : 成功 
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2017-01-20 14:35:49
******************************************************************************************************/
cp_int32_t cp_ffmpeg_av_codec_init_media_probe(cp_ffmpeg_av_codec_t *ffmpeg_av_codec);

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: cp_ffmpeg_av_codec_start_media_probe
*
* 函数说明: 启动media probe
*
* 参    数: cp_ffmpeg_av_codec_t * ffmpeg_av_codec						[in]参数说明
*
* 返 回 值: cp_int32_t
*           0  : 成功 
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2017-01-20 16:33:54
******************************************************************************************************/
cp_int32_t cp_ffmpeg_av_codec_start_media_probe(cp_ffmpeg_av_codec_t *ffmpeg_av_codec);

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: cp_ffmpeg_av_codec_stop_media_probe
*
* 函数说明: 停止media probe
*
* 参    数: cp_ffmpeg_av_codec_t * ffmpeg_av_codec						[in]参数说明
*
* 返 回 值: cp_int32_t
*           0  : 成功 
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2017-01-20 16:34:10
******************************************************************************************************/
cp_int32_t cp_ffmpeg_av_codec_stop_media_probe(cp_ffmpeg_av_codec_t *ffmpeg_av_codec);

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: cp_ffmpeg_av_codec_exit_media_probe
*
* 函数说明: 退出media probe
*
* 参    数: cp_ffmpeg_av_codec_t * ffmpeg_av_codec						[in]参数说明
*
* 返 回 值: cp_int32_t
*           0  : 成功 
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2017-01-20 14:36:46
******************************************************************************************************/
cp_int32_t cp_ffmpeg_av_codec_exit_media_probe(cp_ffmpeg_av_codec_t *ffmpeg_av_codec);

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: cp_ffmpeg_av_codec_probe_media_data
*
* 函数说明: 测试媒体的编码方式
*
* 参    数: cp_ffmpeg_av_codec_t * ffmpeg_av_codec						[in]参数说明
* 参    数: const cp_uchar_t * * buf						[in]参数说明
* 参    数: cp_int32_t len						[in]参数说明
* 参    数: cp_int32_t flag						[in]参数说明
*
* 返 回 值: cp_int32_t
*           0  : 成功 
*         非 0  :失败
*
* 备    注:当不确定媒体的编码方式时，可以使用这个方法测试媒体源的编码类型
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2017-01-20 14:27:25
******************************************************************************************************/
cp_int32_t cp_ffmpeg_av_codec_probe_media_data(cp_ffmpeg_av_codec_t *ffmpeg_av_codec,
	const cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag);

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: cp_ffmpeg_av_codec_probe_read_frame
*
* 函数说明: 读取一帧数据
*
* 参    数: AVPacket * pkt						[in]参数说明
* 参    数: cp_ffmpeg_av_codec_t * ffmpeg_av_codec						[in]参数说明
* 参    数: const cp_uchar_t * * buf						[in]参数说明
* 参    数: cp_int32_t len						[in]参数说明
* 参    数: cp_int32_t flag						[in]参数说明
*
* 返 回 值: cp_int32_t
*           0  : 成功 
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2017-02-10 15:55:08
******************************************************************************************************/
cp_int32_t cp_ffmpeg_av_codec_probe_read_frame(AVPacket *pkt, cp_ffmpeg_av_codec_t *ffmpeg_av_codec,
	const cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag);

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: cp_ffmpeg_av_codec_probe_read_meida_packet
*
* 函数说明: probe读取数据
*
* 参    数: void * opaque						[in]参数说明
* 参    数: uint8_t * buf						[in]参数说明
* 参    数: int buf_size						[in]参数说明
*
* 返 回 值: int
*           0  : 成功 
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2017-01-20 15:15:20
******************************************************************************************************/
int cp_ffmpeg_av_codec_probe_read_meida_packet(void *opaque, uint8_t *buf, int buf_size);

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: cp_ffmpeg_av_codec_probe_thread_cb
*
* 函数说明: 媒体探测处理线程
*
* 参    数: cp_ffmpeg_av_codec_t *ffmpeg_av_codec						[in]参数说明
*
* 返 回 值: void
*           0  : 成功 
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2017-01-21 09:53:03
******************************************************************************************************/
void cp_ffmpeg_av_codec_probe_thread_cb(cp_ffmpeg_av_codec_t *ffmpeg_av_codec);


/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: cp_ffmpeg_av_codec_probe_open_debug_file
*
* 函数说明: 打开debug文件
*
* 参    数: cp_ffmpeg_av_codec_t * ffmpeg_av_codec						[in]参数说明
*
* 返 回 值: cp_int32_t
*           0  : 成功 
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2017-02-10 15:02:31
******************************************************************************************************/
cp_int32_t cp_ffmpeg_av_codec_probe_open_debug_file(cp_ffmpeg_av_codec_t *ffmpeg_av_codec);


/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: cp_ffmpeg_av_codec_probe_write_debug_file
*
* 函数说明: debug文件
*
* 参    数: cp_ffmpeg_av_codec_t * ffmpeg_av_codec						[in]参数说明
* 参    数: cp_uchar_t * buf						[in]参数说明
* 参    数: cp_int32_t len						[in]参数说明
*
* 返 回 值: cp_int32_t
*           0  : 成功 
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2017-02-10 15:03:36
******************************************************************************************************/
cp_int32_t cp_ffmpeg_av_codec_probe_write_debug_file(cp_ffmpeg_av_codec_t *ffmpeg_av_codec, cp_uchar_t *buf, cp_int32_t len);


/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: cp_ffmpeg_av_codec_probe_close_debug_file
*
* 函数说明: 关闭debug文件
*
* 参    数: cp_ffmpeg_av_codec_t * ffmpeg_av_codec						[in]参数说明
*
* 返 回 值: cp_int32_t
*           0  : 成功 
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2017-02-10 15:04:25
******************************************************************************************************/
cp_int32_t cp_ffmpeg_av_codec_probe_close_debug_file(cp_ffmpeg_av_codec_t *ffmpeg_av_codec);

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: cp_ffmpeg_av_codec_probe_successed_test
*
* 函数说明: 测试probe是否成功
*
* 参    数: cp_ffmpeg_av_codec_t * ffmpeg_av_codec						[in]参数说明
*
* 返 回 值: cp_int32_t
*           0  : 成功 
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2017-02-10 15:04:53
******************************************************************************************************/
cp_int32_t cp_ffmpeg_av_codec_probe_successed_test(cp_ffmpeg_av_codec_t *ffmpeg_av_codec);

#endif


