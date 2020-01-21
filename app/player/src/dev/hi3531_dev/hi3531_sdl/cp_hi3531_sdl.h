/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/

#ifndef	_CP_HI3531_SDL_INCLUDE_H_
#define _CP_HI3531_SDL_INCLUDE_H_



#include "cp_hi3531_sdl_core.h"





#pragma pack(1)


#define CP_HI3531_SDL_FIELDS																		\
		CP_PLAYER_DEV_FIELDS																		\
		cp_dev_t					*m_hi3531_vo[CP_HI3531_DEV_VO_DEVICE_SIZE];				/*hi3531�������*/					\
		cp_dev_t					*m_hi3531_vpss;				/*hi3531ͼ��������*/				\
		cp_dev_t					*m_hi3531_tde;				/*hi3531ͼ�λ�������*/				\



/************************************************************************/
/*                                                                      */
/************************************************************************/
struct cp_hi3531_sdl_s {
	CP_HI3531_SDL_FIELDS														/*��ʾʱ��ģ����Ϣ*/

#if defined(CP_HI3531_SDL_FILE_DEBUG)
	FILE														*file;			/*ý���ļ�*/
	cp_int32_t													index;
#endif

	cp_hi3531_sdl_configure_t									hacc;			/*��ʾ��ǰ�ı�����������Ϣ*/

};


#pragma pack()



cp_hi3531_sdl_t* create_hi3531_sdl(cp_module_register_t *register_info, cp_codec_manager_t *manager, cp_hi3531_sdl_info_t *info);
cp_int32_t destroy_hi3531_sdl(cp_codec_manager_t *manager, cp_hi3531_sdl_t* hi3531_sdl);

#endif


