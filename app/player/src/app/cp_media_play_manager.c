/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2017-04-05

Description:

**************************************************************************/


#include "cp_media_play_manager.h"




/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: create_media_play_manager
*
* ����˵��: ����media play manager
*
* ��    ��: cp_app_t * app						[in]����˵��
*
* �� �� ֵ: cp_media_play_manager_t*
*           0  : �ɹ� 
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2017-04-05 18:51:19
******************************************************************************************************/
cp_media_play_manager_t* create_media_play_manager(cp_app_t *app)
{
	cp_media_play_manager_t					*tmp_mpm = CP_NULL;
	cp_mpool_t								*tmp_mpool = CP_NULL;



	if (!app) {
		return CP_NULL;
	}

	//����һ���ڴ��
	tmp_mpool = cp_create_mpool(CP_APP_DEFAULT_BUFFER_LENGTH);
	if (!tmp_mpool) {
		cp_app_log(error, app, "create_media_play_manager () error reason: cp_create_mpool() failed!");
		return CP_NULL;
	}

	tmp_mpm = cp_mpalloc(tmp_mpool, cp_sizeof(cp_media_play_manager_t));
	if (tmp_mpm) {
		cp_memset(tmp_mpm, 0, cp_sizeof(cp_media_play_manager_t));
		tmp_mpm->app = app;
		tmp_mpm->mpool = tmp_mpool;
		return tmp_mpm;
	}

	return CP_NULL;
}


/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: destroy_media_play_manager
*
* ����˵��: �ͷ�media play manager
*
* ��    ��: cp_app_t * app						[in]����˵��
* ��    ��: cp_media_play_manager_t * mpm						[in]����˵��
*
* �� �� ֵ: int
*           0  : �ɹ� 
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2017-04-05 18:51:36
******************************************************************************************************/
int destroy_media_play_manager(cp_app_t *app, cp_media_play_manager_t* mpm)
{
	if (!app || !mpm) {
		return -1;
	}

	stop_media_play_manager(mpm);

	cp_destroy_mpool(mpm->mpool);

	return 0;
}

/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: init_media_play_manager
*
* ����˵��: ��ʼ��media play manager
*
* ��    ��: cp_app_t * app						[in]����˵��
* ��    ��: cp_media_play_manager_t * mpm						[in]����˵��
* ��    ��: cp_int32_t max_size						[in]����˵��
*
* �� �� ֵ: int
*           0  : �ɹ� 
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2017-04-05 18:58:35
******************************************************************************************************/
int init_media_play_manager(cp_app_t *app, cp_media_play_manager_t *mpm, cp_int32_t max_size)
{
	cp_int32_t							ret_int = 0;



	if (!app || !mpm) {
		return -1;
	}

	cp_mutex_init(&mpm->audio_play_mutex);
	cp_mutex_init(&mpm->video_play_mutex);

	//��ʼ�����Ź�������Ϣ
	ret_int = init_channel_manager(app, &(mpm->channel_manager), max_size);
	if (ret_int) {
		cp_app_log(error, app, "init_media_play_manager() error. init_channel_manager() error.");
		return -1;
	}

	return 0;
}

/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: start_media_play_manager
*
* ����˵��: ����media play manager
*
* ��    ��: cp_media_play_manager_t * mpm						[in]����˵��
*
* �� �� ֵ: int
*           0  : �ɹ� 
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2017-04-05 18:40:01
******************************************************************************************************/
int start_media_play_manager(cp_media_play_manager_t *mpm)
{
	cp_int32_t							ret_int = 0;



	//�������Ź�������Ϣ
	ret_int = start_channel_manager(&(mpm->channel_manager));
	if (ret_int) {
		cp_app_log(error, mpm->app, "start_media_play_manager() error. start_channel_manager() error.");
		return -1;
	}

	return 0;
}


/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: stop_media_play_manager
*
* ����˵��: ֹͣmedia play manager
*
* ��    ��: cp_media_play_manager_t * mpm						[in]����˵��
*
* �� �� ֵ: int
*           0  : �ɹ� 
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2017-04-05 18:40:32
******************************************************************************************************/
int stop_media_play_manager(cp_media_play_manager_t *mpm)
{
	if (mpm) {
		stop_channel_manager(&mpm->channel_manager);
	}
	return 0;
}


