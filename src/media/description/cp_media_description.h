/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-12-07

Description:

**************************************************************************/

#ifndef _CP_MEDIA_DESCRIPTION_INCLUDE_H_
#define _CP_MEDIA_DESCRIPTION_INCLUDE_H_



//  typedef	struct cp_media_description_s					cp_media_description_t;
//  typedef	struct cp_media_packet_s						cp_media_packet_t;
//  typedef	enum cp_media_description_type_enum				cp_media_description_type_e;



#pragma pack(1)


/************************************************************************/
/* ��ʾ��������                                                          */
/************************************************************************/
typedef	enum cp_media_description_type_enum
{
	cp_media_description_type_none = 0,
	cp_media_description_type_general,
	cp_media_description_type_video,
	cp_media_description_type_audio,
}cp_media_description_type_e;


#include "cp_media_core.h"


/************************************************************************/
/* ��ʾmedia description ��Ա����                                            */
/************************************************************************/
#define CP_MEDIA_DESCRIPTION_FIELDS																									\
	cp_media_description_type_e				type;											/*��ʾ������Ϣ����*/						\
	cp_int32_t								desc_len;										/*ý���������ݳ���*/						\
	cp_codec_pixel_format_e					pix_fmt;										/*ý���������*/							\
	cp_int32_t								channel;										/*ý��ͨ����*/							\
	cp_int32_t								priority;										/*ͨ�����ȼ�*/							\
	cp_media_type_e							encodec_type;									/*ý��������ͱ��*/						\
	cp_char_t								encodec_name[CP_APP_DEFAULT_STRING_LENGTH];		/*ý�����������*/						\



/************************************************************************/
/* ý��������Ϣ                                                          */
/************************************************************************/
struct cp_media_description_s
{
	CP_MEDIA_DESCRIPTION_FIELDS
};



#pragma pack()



/************************************************************************/
/* ����                                                            */
/************************************************************************/
#include "cp_video_description.h"
#include "cp_audio_description.h"



/************************************************************************/
/* ����������Ϣ                                                          */
/************************************************************************/
cp_media_description_t	*create_media_description(cp_pool_t *pool, cp_media_description_type_e type);

/************************************************************************/
/* ����������Ϣ                                                          */
/************************************************************************/
cp_int32_t destroy_media_description(cp_pool_t *pool, cp_media_description_t *md);





#endif