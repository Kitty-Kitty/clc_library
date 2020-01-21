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



/*�Ƿ�����debug file*/
//#define		CP_FFMPEG_AV_PROBE_FILE_DEBUG								1
#define		CP_FFMPEG_AV_PROBE_FILE_NAME_LENGTH							1024

/* media probe safe queue bufferf size�����С */
#define		CP_FFMPEG_AV_CODEC_SAFE_QUEUE_BUFFER_SIZE					1024

/*probe buffer size*/
#define		CP_FFMPEG_AV_CODEC_PROBE_BUFFER_SIZE						4096 * 500

//��ʾĬ�ϵ����߼��
#define		CP_FFMPEG_AV_CODEC_PROBE_INTERVAL_NS						1000000



//��ʾprobe״̬��Ϣ
typedef		enum cp_ffmepg_av_probe_status_enum							cp_ffmepg_av_probe_status_e;


/************************************************************************/
/* ffmpeg ״̬��Ϣ                                                       */
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
/* ffmpeg ������Ϣ                                                      */
/************************************************************************/
struct cp_ffmepg_av_probe_info_s
{
	cp_ffmpeg_av_codec_t			*codec;								/*��ʾcodec��Ϣ*/
	cp_safe_queue_t					*sq;								/*���ݻ������*/
	cp_thread_t						*thread;							/*probe�����߳�*/
	AVFormatContext					*format_ctx;						/*��ʽ�ϲ���*/
	AVIOContext						*pb;
	AVCodec							*media_codec;						/*������*/
	AVCodecContext					*media_codec_context;				/*������������Ϣ*/
	cp_uchar_t						*buf;								/*��ʾ��ʱ�����ַ*/
	cp_int32_t						faile_times;						/*��ʾdecode�������*/
	cp_int32_t						successed_times;					/*��ʾdecode�ɹ��Ĵ���*/

	cp_ffmepg_av_probe_status_e		status;								/*��ʾ״̬��Ϣ*/

#if defined CP_FFMPEG_AV_PROBE_FILE_DEBUG
	FILE							*file;								/*��ʾdebug�ļ�*/
#endif
};



/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: cp_ffmpeg_av_codec_init_media_probe
*
* ����˵��: ��ʼ��media probe
*
* ��    ��: cp_ffmpeg_av_codec_t * ffmpeg_av_codec						[in]����˵��
*
* �� �� ֵ: cp_int32_t
*           0  : �ɹ� 
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2017-01-20 14:35:49
******************************************************************************************************/
cp_int32_t cp_ffmpeg_av_codec_init_media_probe(cp_ffmpeg_av_codec_t *ffmpeg_av_codec);

/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: cp_ffmpeg_av_codec_start_media_probe
*
* ����˵��: ����media probe
*
* ��    ��: cp_ffmpeg_av_codec_t * ffmpeg_av_codec						[in]����˵��
*
* �� �� ֵ: cp_int32_t
*           0  : �ɹ� 
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2017-01-20 16:33:54
******************************************************************************************************/
cp_int32_t cp_ffmpeg_av_codec_start_media_probe(cp_ffmpeg_av_codec_t *ffmpeg_av_codec);

/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: cp_ffmpeg_av_codec_stop_media_probe
*
* ����˵��: ֹͣmedia probe
*
* ��    ��: cp_ffmpeg_av_codec_t * ffmpeg_av_codec						[in]����˵��
*
* �� �� ֵ: cp_int32_t
*           0  : �ɹ� 
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2017-01-20 16:34:10
******************************************************************************************************/
cp_int32_t cp_ffmpeg_av_codec_stop_media_probe(cp_ffmpeg_av_codec_t *ffmpeg_av_codec);

/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: cp_ffmpeg_av_codec_exit_media_probe
*
* ����˵��: �˳�media probe
*
* ��    ��: cp_ffmpeg_av_codec_t * ffmpeg_av_codec						[in]����˵��
*
* �� �� ֵ: cp_int32_t
*           0  : �ɹ� 
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2017-01-20 14:36:46
******************************************************************************************************/
cp_int32_t cp_ffmpeg_av_codec_exit_media_probe(cp_ffmpeg_av_codec_t *ffmpeg_av_codec);

/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: cp_ffmpeg_av_codec_probe_media_data
*
* ����˵��: ����ý��ı��뷽ʽ
*
* ��    ��: cp_ffmpeg_av_codec_t * ffmpeg_av_codec						[in]����˵��
* ��    ��: const cp_uchar_t * * buf						[in]����˵��
* ��    ��: cp_int32_t len						[in]����˵��
* ��    ��: cp_int32_t flag						[in]����˵��
*
* �� �� ֵ: cp_int32_t
*           0  : �ɹ� 
*         �� 0  :ʧ��
*
* ��    ע:����ȷ��ý��ı��뷽ʽʱ������ʹ�������������ý��Դ�ı�������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2017-01-20 14:27:25
******************************************************************************************************/
cp_int32_t cp_ffmpeg_av_codec_probe_media_data(cp_ffmpeg_av_codec_t *ffmpeg_av_codec,
	const cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag);

/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: cp_ffmpeg_av_codec_probe_read_frame
*
* ����˵��: ��ȡһ֡����
*
* ��    ��: AVPacket * pkt						[in]����˵��
* ��    ��: cp_ffmpeg_av_codec_t * ffmpeg_av_codec						[in]����˵��
* ��    ��: const cp_uchar_t * * buf						[in]����˵��
* ��    ��: cp_int32_t len						[in]����˵��
* ��    ��: cp_int32_t flag						[in]����˵��
*
* �� �� ֵ: cp_int32_t
*           0  : �ɹ� 
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2017-02-10 15:55:08
******************************************************************************************************/
cp_int32_t cp_ffmpeg_av_codec_probe_read_frame(AVPacket *pkt, cp_ffmpeg_av_codec_t *ffmpeg_av_codec,
	const cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag);

/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: cp_ffmpeg_av_codec_probe_read_meida_packet
*
* ����˵��: probe��ȡ����
*
* ��    ��: void * opaque						[in]����˵��
* ��    ��: uint8_t * buf						[in]����˵��
* ��    ��: int buf_size						[in]����˵��
*
* �� �� ֵ: int
*           0  : �ɹ� 
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2017-01-20 15:15:20
******************************************************************************************************/
int cp_ffmpeg_av_codec_probe_read_meida_packet(void *opaque, uint8_t *buf, int buf_size);

/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: cp_ffmpeg_av_codec_probe_thread_cb
*
* ����˵��: ý��̽�⴦���߳�
*
* ��    ��: cp_ffmpeg_av_codec_t *ffmpeg_av_codec						[in]����˵��
*
* �� �� ֵ: void
*           0  : �ɹ� 
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2017-01-21 09:53:03
******************************************************************************************************/
void cp_ffmpeg_av_codec_probe_thread_cb(cp_ffmpeg_av_codec_t *ffmpeg_av_codec);


/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: cp_ffmpeg_av_codec_probe_open_debug_file
*
* ����˵��: ��debug�ļ�
*
* ��    ��: cp_ffmpeg_av_codec_t * ffmpeg_av_codec						[in]����˵��
*
* �� �� ֵ: cp_int32_t
*           0  : �ɹ� 
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2017-02-10 15:02:31
******************************************************************************************************/
cp_int32_t cp_ffmpeg_av_codec_probe_open_debug_file(cp_ffmpeg_av_codec_t *ffmpeg_av_codec);


/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: cp_ffmpeg_av_codec_probe_write_debug_file
*
* ����˵��: debug�ļ�
*
* ��    ��: cp_ffmpeg_av_codec_t * ffmpeg_av_codec						[in]����˵��
* ��    ��: cp_uchar_t * buf						[in]����˵��
* ��    ��: cp_int32_t len						[in]����˵��
*
* �� �� ֵ: cp_int32_t
*           0  : �ɹ� 
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2017-02-10 15:03:36
******************************************************************************************************/
cp_int32_t cp_ffmpeg_av_codec_probe_write_debug_file(cp_ffmpeg_av_codec_t *ffmpeg_av_codec, cp_uchar_t *buf, cp_int32_t len);


/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: cp_ffmpeg_av_codec_probe_close_debug_file
*
* ����˵��: �ر�debug�ļ�
*
* ��    ��: cp_ffmpeg_av_codec_t * ffmpeg_av_codec						[in]����˵��
*
* �� �� ֵ: cp_int32_t
*           0  : �ɹ� 
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2017-02-10 15:04:25
******************************************************************************************************/
cp_int32_t cp_ffmpeg_av_codec_probe_close_debug_file(cp_ffmpeg_av_codec_t *ffmpeg_av_codec);

/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: cp_ffmpeg_av_codec_probe_successed_test
*
* ����˵��: ����probe�Ƿ�ɹ�
*
* ��    ��: cp_ffmpeg_av_codec_t * ffmpeg_av_codec						[in]����˵��
*
* �� �� ֵ: cp_int32_t
*           0  : �ɹ� 
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2017-02-10 15:04:53
******************************************************************************************************/
cp_int32_t cp_ffmpeg_av_codec_probe_successed_test(cp_ffmpeg_av_codec_t *ffmpeg_av_codec);

#endif


