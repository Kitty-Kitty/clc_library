/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-12-08

Description:

**************************************************************************/

#ifndef _CP_DEV_DESCRIPTION_INCLUDE_H_
#define _CP_DEV_DESCRIPTION_INCLUDE_H_

#include "cp_dev_core.h"



//typedef	enum cp_dev_description_type_enum				cp_dev_description_type_e;
//typedef	struct cp_dev_description_s						cp_dev_description_t;
typedef		struct cp_dev_video_description_s				cp_dev_video_description_t;
typedef		struct cp_dev_audio_description_s				cp_dev_audio_description_t;




#pragma pack(1)


/************************************************************************/
/* ��ʾ��������                                                          */
/************************************************************************/
typedef enum cp_dev_description_type_enum
{
	cp_dev_description_type_none = 0,
	cp_dev_description_type_general,
	cp_dev_description_type_video,
	cp_dev_description_type_audio,
}cp_dev_description_type_e;


/************************************************************************/
/* �豸������Ϣ                                                          */
/************************************************************************/
struct cp_dev_description_s
{
	cp_dev_description_type_e				type;											//��ʾ������Ϣ����
	cp_int32_t								desc_len;										//�豸�������ݳ���
	cp_int32_t								dev_type;										//�豸���ͱ��
	cp_char_t								dev_name[CP_APP_DEFAULT_STRING_LENGTH];			//�豸����������
};


/************************************************************************/
/* ��ʾ��Ƶ������Ϣ                                                      */
/************************************************************************/
struct cp_dev_video_description_s
{
	cp_dev_description_t					dd;												//�豸������Ϣ
	cp_int32_t								height;											//�豸�߶�
	cp_int32_t								width;											//�豸���
	cp_int32_t								fps;											//�豸֡��
	cp_int32_t								bps;											//�豸����������Ϣ
};


/************************************************************************/
/* ��ʾ��Ƶ������Ϣ                                                      */
/************************************************************************/
struct cp_dev_audio_description_s
{
	cp_dev_description_t					dd;												//�豸������Ϣ
	cp_int32_t								volume;											//��Ƶ����
	cp_int32_t								bit_rate;										//��Ƶ�������
	cp_int32_t								sample_rate;									//����Ƶ�ʣ���λ��Hz��
	cp_int32_t								channel_layout;									//������������
	cp_int32_t								sample_format;									//����������������
	cp_int32_t								samples;										//������С
	cp_int32_t								channels;										//ͨ������
};

#pragma pack()





/************************************************************************/
/* ����������Ϣ                                                          */
/************************************************************************/
cp_dev_description_t	*create_dev_description(cp_pool_t *pool, cp_dev_description_type_e type);

/************************************************************************/
/* ����������Ϣ                                                          */
/************************************************************************/
cp_int32_t destroy_dev_description(cp_pool_t *pool, cp_dev_description_t *dd);

#endif