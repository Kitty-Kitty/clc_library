/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-12-05

Description:

**************************************************************************/

#ifndef _CP_MEDIA_PACKET_INCLUDE_H_
#define _CP_MEDIA_PACKET_INCLUDE_H_



#include "cp_media_core.h"
#include "cp_codec_core.h"



#define		CP_MEDIA_PACKET_MAX_BUFFER_NUMBER			8		//��ǰ���ͨ����


//typedef	enum cp_media_packet_type_enum				cp_media_packet_type_e;
//typedef   enum cp_media_packet_buf_type_enum			cp_media_packet_buf_type_e;
typedef		struct cp_media_packet_buf_s				cp_media_packet_buf_t;

//typedef	struct cp_media_packet_s					cp_media_packet_t;



#pragma pack(1)

/************************************************************************/
/* ��ʾ��������                                                          */
/************************************************************************/
typedef enum cp_media_packet_type_enum
{
	cp_media_packet_type_none = 0,
	cp_media_packet_type_audio,
	cp_media_packet_type_video,
	cp_media_packet_type_data_and_timestamp,
}cp_media_packet_type_e;


/* ��ʾ����buf����                                                       */
/************************************************************************/
typedef enum cp_media_packet_buf_type_enum
{
	cp_media_packet_buf_type_none = 0,
	cp_media_packet_buf_type_ffmpeg,							//��ʾffmpeg��ʽ
	cp_media_packet_buf_type_hi,								//��ʾ��ʨ��ʽ
}cp_media_packet_buf_type_e;


/************************************************************************/
/* ý������buf��                                                         */
/************************************************************************/
struct cp_media_packet_buf_s
{
	cp_media_packet_buf_type_e				buf_type;									//����buf����
	cp_buf_t								buf[CP_MEDIA_PACKET_MAX_BUFFER_NUMBER];		//ý�����ݲ���
	cp_void_t								*data;										//��ʾ�޷���buf��ʾ����������
};



/************************************************************************/
/* ��ʾmedia packet ��Ա����                                            */
/************************************************************************/
#define CP_MEDIA_PACKET_FIELDS																				\
  	cp_pool_t								*pool;				/*��ʾ��ǰ�ڴ�*/								\
	cp_media_description_t					*md_p;				/*��ʾ��ǰ���ŵ�ý����Ϣ*/					\
	cp_codec_callback_info_t				*ccb_info_p;		/*��ʾ������������Ϣ*/						\
	cp_module_t								*orgin_module;		/*��ʾ�����ģ��*/							\
	cp_void_t								*data;				/*��ʾ��������*/								\
	cp_media_packet_type_e					type;				/*��������*/									\
	cp_timespec_t							ts;					/*ý��ʱ��*/									\
	cp_media_packet_buf_t					mp_buf;				/*ý������buf����*/							\



/************************************************************************/
/* ý�����ݰ�                                                            */
/************************************************************************/
struct cp_media_packet_s
{
	CP_MEDIA_PACKET_FIELDS
};

#pragma pack()




/************************************************************************/
/* ����                                                            */
/************************************************************************/
#include "cp_video_frame_packet.h"






/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: create_media_packet
*
* ����˵��: ����media packet
*
* ��    ��: cp_pool_t * pool						[in]����˵��
* ��    ��: cp_int32_t size						[in]����˵��
* ��    ��: cp_media_packet_type_e type			[in]����˵��
*
* �� �� ֵ: cp_media_packet_t *
*           0  : �ɹ� 
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2016-12-06 10:46:04
******************************************************************************************************/
cp_media_packet_t *create_media_packet(cp_pool_t *pool, cp_int32_t size, cp_media_packet_type_e type);

/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: create_number_media_packet
*
* ����˵��: �������media packet
*
* ��    ��: cp_pool_t * pool						[in]����˵��
* ��    ��: cp_int32_t size						[in]ÿ��media packet��С
* ��    ��: cp_int32_t number					[in]�����ĸ���
* ��    ��: cp_media_packet_type_e type						[in]����˵��
*
* �� �� ֵ: cp_media_packet_t *
*           0  : �ɹ� 
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2017-01-16 13:44:40
******************************************************************************************************/
cp_media_packet_t *create_number_media_packet(cp_pool_t *pool, cp_int32_t size, cp_int32_t number, cp_media_packet_type_e type);

/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: get_media_packet_data_length
*
* ����˵��: ��ȡý������ݳ���
*
* ��    ��: cp_media_packet_t * mp						[in]����˵��
*
* �� �� ֵ: cp_int32_t
*           0  : �ɹ� 
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2017-01-16 14:38:09
******************************************************************************************************/
cp_int32_t get_media_packet_data_length(cp_media_packet_t *mp);

/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: clear_media_packet
*
* ����˵��: ���media packet����
*
* ��    ��: cp_media_packet_t * mp						[in]����˵��
*
* �� �� ֵ: cp_int32_t
*           0  : �ɹ� 
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2017-01-16 14:59:23
******************************************************************************************************/
cp_int32_t clear_media_packet(cp_media_packet_t *mp);

/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: create_media_packet_channel_buffer
*
* ����˵��: ����ָ��ͨ��
*
* ��    ��: cp_media_packet_t * mp						[in]����˵��
* ��    ��: cp_int32_t channel_number						[in]����˵��
* ��    ��: cp_int32_t size						[in]����˵��
*
* �� �� ֵ: cp_int32_t
*           0  : �ɹ� 
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2016-12-08 13:19:37
******************************************************************************************************/
cp_int32_t create_media_packet_channel_buffer(cp_media_packet_t *mp, cp_int32_t channel_number, cp_int32_t size);

/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: destroy_media_packet
*
* ����˵��: ����ý�����ݰ�
*
* ��    ��: cp_media_packet_t		*mp					[in]����˵��
*
* �� �� ֵ: cp_int32_t
*           0  : �ɹ� 
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2016-12-06 10:32:38
******************************************************************************************************/
cp_int32_t destroy_media_packet(cp_media_packet_t *mp);

/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: create_media_packet_description
*
* ����˵��: ����ý��������Ϣ
*
* ��    ��: cp_pool_t * pool						[in]����˵��
* ��    ��: cp_media_packet_t * mp				[in]����˵��
* ��    ��: cp_media_description_type_e type		[in]����˵��
*
* �� �� ֵ: cp_int32_t
*           0  : �ɹ� 
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2016-12-07 16:43:30
******************************************************************************************************/
cp_int32_t create_media_packet_description(cp_pool_t *pool, cp_media_packet_t *mp, cp_media_description_type_e type);

/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: destroy_media_packet_description
*
* ����˵��: ����ý��������Ϣ
*
* ��    ��: cp_pool_t * pool						[in]����˵��
* ��    ��: cp_media_packet_t * packet						[in]����˵��
*
* �� �� ֵ: cp_int32_t
*           0  : �ɹ� 
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2016-12-07 16:47:00
******************************************************************************************************/
cp_int32_t destroy_media_packet_description(cp_pool_t *pool, cp_media_packet_t *packet);

#endif