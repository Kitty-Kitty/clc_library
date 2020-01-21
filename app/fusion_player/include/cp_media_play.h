/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-11-23

Description:��Ҫʵ��ý�岥����ص�����

**************************************************************************/

#ifndef _CP_MEDIA_PLAY_INCLUDE_H_
#define _CP_MEDIA_PLAY_INCLUDE_H_



#include "cp_fusion_player_core.h"



/************************************************************************/
/* ������Ϣ                                                              */
/************************************************************************/
cp_int32_t create_media_play(cp_fusion_player_t *player, cp_play_channel_info_t *cp_info);
cp_int32_t destroy_media_play(cp_fusion_player_t *player, cp_play_channel_info_t *cp_info);

cp_int32_t init_media_play(cp_fusion_player_t *player, cp_play_channel_info_t *cp_info);
cp_int32_t start_media_play(cp_fusion_player_t *player, cp_play_channel_info_t *cp_info);
cp_int32_t stop_media_play(cp_fusion_player_t *player, cp_play_channel_info_t *cp_info);

cp_int32_t update_media_play(cp_fusion_player_t *player, cp_play_channel_info_t *cp_info);


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
* ��    ��: cp_fusion_player_t * player						[in]����˵��
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
cp_module_t* create_audio_media_play(cp_fusion_player_t *player, cp_media_channel_info_t *mci);

/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: create_video_media_play
*
* ����˵��: ����һ����Ƶ����ģ��
*
* ��    ��: cp_fusion_player_t * player						[in]����˵��
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
cp_module_t* create_video_media_play(cp_fusion_player_t *player, cp_media_channel_info_t *mci);

/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: create_av_media_play_module
*
* ����˵��: ��������Ƶģ��
*
* ��    ��: cp_fusion_player_t * player						[in]����˵��
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
cp_module_t* create_av_media_play_module(cp_fusion_player_t *player, cp_media_channel_info_t *mci, cp_int32_t manager_type, cp_int32_t module_type);

/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: update_audio_media_play
*
* ����˵��: ����һ����Ƶ����ģ��
*
* ��    ��: cp_fusion_player_t * player						[in]����˵��
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
cp_module_t* update_audio_media_play(cp_fusion_player_t *player, cp_media_channel_info_t *mci);

/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: update_audio_media_play
*
* ����˵��: ����һ����Ƶ����ģ��
*
* ��    ��: cp_fusion_player_t * player						[in]����˵��
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
cp_module_t* update_video_media_play(cp_fusion_player_t *player, cp_media_channel_info_t *mci);

/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: update_av_media_play_module
*
* ����˵��: ��������Ƶģ��
*
* ��    ��: cp_fusion_player_t * player						[in]����˵��
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
cp_module_t* update_av_media_play_module(cp_fusion_player_t *player, cp_media_channel_info_t *mci, cp_int32_t manager_type, cp_int32_t module_type);

/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: stop_audio_media_play
*
* ����˵��: ֹͣ��Ƶmedia play
*
* ��    ��: cp_fusion_player_t * player						[in]����˵��
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
* �������ڣ�2017-04-05 19:17:26
******************************************************************************************************/
cp_int32_t stop_audio_media_play(cp_fusion_player_t *player, cp_media_channel_info_t *mci);

/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: stop_all_audio_media_play
*
* ����˵��: ֹͣ������Ƶ����
*
* ��    ��: cp_fusion_player_t * player						[in]����˵��
*
* �� �� ֵ: cp_int32_t
*           0  : �ɹ� 
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2017-04-12 17:19:33
******************************************************************************************************/
cp_int32_t stop_all_audio_media_play(cp_fusion_player_t *player);

/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: stop_video_media_play
*
* ����˵��: ֹͣ��Ƶmedia play
*
* ��    ��: cp_fusion_player_t * player						[in]����˵��
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
* �������ڣ�2017-04-05 19:17:51
******************************************************************************************************/
cp_int32_t stop_video_media_play(cp_fusion_player_t *player, cp_media_channel_info_t *mci);

/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: stop_all_video_media_play
*
* ����˵��: ֹͣ������Ƶ����
*
* ��    ��: cp_fusion_player_t * player						[in]����˵��
*
* �� �� ֵ: cp_int32_t
*           0  : �ɹ� 
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2017-04-14 14:16:47
******************************************************************************************************/
cp_int32_t stop_all_video_media_play(cp_fusion_player_t *player);

/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: stop_av_media_play_module
*
* ����˵��: ֹͣһ������
*
* ��    ��: cp_fusion_player_t * player						[in]����˵��
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
cp_int32_t stop_av_media_play_module(cp_fusion_player_t *player, cp_media_channel_info_t *mci);

/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: stop_all_av_media_play_module
*
* ����˵��: �ر����в���ý��
*
* ��    ��: cp_fusion_player_t * player						[in]����˵��
*
* �� �� ֵ: cp_int32_t
*           0  : �ɹ� 
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2017-04-14 14:14:44
******************************************************************************************************/
cp_int32_t stop_all_av_media_play_module(cp_fusion_player_t *player);

#endif



