/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/

#ifndef	_CP_HI3519_AV_CODEC_INCLUDE_H_
#define _CP_HI3519_AV_CODEC_INCLUDE_H_

#include "cp_hi3519_av_codec_core.h"



//typedef struct cp_hi3519_av_codec_s					cp_hi3519_av_codec_t;




#pragma pack(1)


#define CP_HI3519_AV_CODEC_FIELDS																	\
		CP_DEMO_CODEC_FIELDS																			\



/************************************************************************/
/*                                                                      */
/************************************************************************/
struct cp_hi3519_av_codec_s {
	CP_HI3519_AV_CODEC_FIELDS									/*��ʾʱ��ģ����Ϣ*/

#if defined(CP_HI3519_AV_CODEC_FILE_DEBUG)
		FILE											*file;	/*ý���ļ�*/
#endif

};


#pragma pack()



cp_hi3519_av_codec_t* create_hi3519_av_codec(cp_module_register_t *register_info, cp_codec_manager_t *manager, cp_hi3519_av_codec_info_t *info);
cp_int32_t destroy_hi3519_av_codec(cp_codec_manager_t *manager, cp_hi3519_av_codec_t* hi3519_av_codec);

#endif


