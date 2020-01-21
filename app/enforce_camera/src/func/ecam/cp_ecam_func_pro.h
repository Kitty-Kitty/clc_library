/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-12-26

Description:

**************************************************************************/

#ifndef _CP_ECAM_FUNC_PRO_INCLUDE_H_
#define _CP_ECAM_FUNC_PRO_INCLUDE_H_


#include "cp_ecam_func_core.h"



#define		CP_ECAM_FUNC_VIDEO_PROCESS_DEFAULT_INTERVAL_NS					20000			//默认间
#define		CP_ECAM_FUNC_RTP_PLOAD_TYPE										96				//H.264
#define		CP_ECAM_FUNC_RTP_MAX_PKT_LENGTH									1400


/*创建编码器*/
cp_module_t* create_video_codec_module(cp_ecam_func_t* ecam_func);
cp_int32_t init_video_codec_module(cp_ecam_func_t* ecam_func, cp_module_t* video_module);
cp_int32_t start_video_codec_module(cp_ecam_func_t* ecam_func, cp_module_t* video_module);
cp_int32_t stop_video_codec_module(cp_ecam_func_t* ecam_func, cp_module_t* video_module);
cp_int32_t destroy_video_codec_module(cp_ecam_func_t* ecam_func, cp_module_t* video_module);

/*视频处理相关*/
cp_ecam_rtp_session_t *create_ecam_rtp_send_session(cp_ecam_func_t* ecam_func);

cp_thread_t* create_video_process_thread(cp_ecam_func_t* ecam_func);
cp_void_t video_process_proc(cp_void_t *arg);
cp_int32_t video_process_proc_general_cb_handle(cp_ecam_func_t* ecam_func,
	cp_codec_callback_info_t *ccb_info_p, cp_media_packet_t *mp);				/*常规回调函数*/

#if 0
int  video_process_proc_rtp_send(cp_ecam_func_t* ecam_func, char *buffer, int  len);
#endif
cp_int32_t destroy_rtp_send_session(cp_ecam_func_t* ecam_func);


#endif