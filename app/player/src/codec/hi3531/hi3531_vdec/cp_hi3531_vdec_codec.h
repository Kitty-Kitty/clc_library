/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/

#ifndef	_CP_HI3531_VDEC_CODEC_INCLUDE_H_
#define _CP_HI3531_VDEC_CODEC_INCLUDE_H_

#include "cp_hi3531_vdec_codec_core.h"






#pragma pack(1)


#define CP_HI3531_VDEC_CODEC_FIELDS																\
		CP_PLAYER_CODEC_FIELDS																	\



/************************************************************************/
/*                                                                      */
/************************************************************************/
struct cp_hi3531_vdec_codec_s {
	CP_HI3531_VDEC_CODEC_FIELDS													/*��ʾʱ��ģ����Ϣ*/

#if defined(CP_HI3531_VDEC_CODEC_FILE_DEBUG)
		FILE													*file;			/*ý���ļ�*/
		cp_int32_t												index;
#endif

	cp_video_description_t										vd;				/*��ʾý��������Ϣ*/
	cp_hi3531_vdec_info_t										*vdec_info;		/*��ʾ����������Ϣ*/
	cp_hi3531_vdec_codec_configure_t							hacc;			/*��ʾ��ǰ�ı�����������Ϣ*/

};


#pragma pack()



cp_hi3531_vdec_codec_t* create_hi3531_vdec_codec(cp_module_register_t *register_info, cp_codec_manager_t *manager, cp_hi3531_vdec_codec_info_t *info);
cp_int32_t destroy_hi3531_vdec_codec(cp_codec_manager_t *manager, cp_hi3531_vdec_codec_t* hi3531_vdec_codec);

#endif


