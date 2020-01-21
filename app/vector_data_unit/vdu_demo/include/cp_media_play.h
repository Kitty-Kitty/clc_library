/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-11-23

Description:��Ҫʵ��ý�岥����ص�����

**************************************************************************/

#ifndef _CP_MEDIA_PLAY_INCLUDE_H_
#define _CP_MEDIA_PLAY_INCLUDE_H_



#include "cp_vdu_demo_core.h"



/************************************************************************/
/* ������Ϣ                                                              */
/************************************************************************/
cp_int32_t create_media_play(cp_vdu_demo_t *vdu_demo, cp_play_channel_info_t *cp_info);
cp_int32_t destroy_media_play(cp_vdu_demo_t *vdu_demo, cp_play_channel_info_t *cp_info);

cp_int32_t init_media_play(cp_vdu_demo_t *vdu_demo, cp_play_channel_info_t *cp_info);
cp_int32_t start_media_play(cp_vdu_demo_t *vdu_demo, cp_play_channel_info_t *cp_info);
cp_int32_t stop_media_play(cp_vdu_demo_t *vdu_demo, cp_play_channel_info_t *cp_info);


/************************************************************************/
/* ��������Ϣ                                                          */
/************************************************************************/

/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: create_audio_media_play
*
* ����˵��: ����һ����Ƶ����ģ��
*
* ��    ��: cp_vdu_demo_t * vdu_demo						[in]����˵��
* ��    ��: cp_media_channel_info_t * mci						[in]����˵��
*
* �� �� ֵ: cp_module_t*
*           0  : �ɹ� 
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2016-11-24 14:58:52
******************************************************************************************************/
cp_module_t* create_audio_media_play(cp_vdu_demo_t *vdu_demo, cp_media_channel_info_t *mci);


/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: create_video_media_play
*
* ����˵��: ����һ����Ƶ����ģ��
*
* ��    ��: cp_vdu_demo_t * vdu_demo						[in]����˵��
* ��    ��: cp_media_channel_info_t * mci						[in]����˵��
*
* �� �� ֵ: cp_module_t*
*           0  : �ɹ� 
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2016-11-24 14:59:20
******************************************************************************************************/
cp_module_t* create_video_media_play(cp_vdu_demo_t *vdu_demo, cp_media_channel_info_t *mci);


/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: create_av_media_play_module
*
* ����˵��: ��������Ƶģ��
*
* ��    ��: cp_vdu_demo_t * vdu_demo						[in]����˵��
* ��    ��: cp_media_channel_info_t * mci						[in]����˵��
* ��    ��: cp_int32_t manager_type						[in]����˵��
* ��    ��: cp_int32_t module_type						[in]����˵��
*
* �� �� ֵ: cp_module_t*
*           0  : �ɹ� 
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2016-11-24 15:46:54
******************************************************************************************************/
cp_module_t* create_av_media_play_module(cp_vdu_demo_t *vdu_demo, cp_media_channel_info_t *mci, cp_int32_t manager_type, cp_int32_t module_type);

/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: stop_av_media_play_module
*
* ����˵��: ֹͣһ������
*
* ��    ��: cp_vdu_demo_t * vdu_demo						[in]����˵��
* ��    ��: cp_media_channel_info_t * mci						[in]����˵��
*
* �� �� ֵ: cp_int32_t
*           0  : �ɹ� 
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2016-12-13 19:38:11
******************************************************************************************************/
cp_int32_t stop_av_media_play_module(cp_vdu_demo_t *vdu_demo, cp_media_channel_info_t *mci);

#endif



