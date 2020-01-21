/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/


#ifndef	_CP_DEV_INFO_INCLUDE_H_
#define _CP_DEV_INFO_INCLUDE_H_

#include "cp_dev_core.h"





//typedef	struct cp_dev_info_s			cp_dev_info_t;




#pragma pack(1)


#define CP_DEV_INFO_FIELDS																							\
		CP_MODULE_INFO_FIELDS																						\
		cp_dev_description_t			*dd;							/*��ʾ��ǰ�豸������Ϣ*/						\
		cp_media_description_t			*md;							/*��ʾ��ǰý��������Ϣ*/						\


/************************************************************************/
/*                                                                      */
/************************************************************************/
struct cp_dev_info_s {
	CP_DEV_INFO_FIELDS
};


#pragma pack()


/************************************************************************/
/* ����ģ���ý����������													    */
/************************************************************************/
#define CP_DEV_INFO_SET_MEDIA_DESCRIPTION(dev_info, in_dd)	do {													\
		(dev_info)->dd = (in_dd);																					\
	}while(0);																										\


#endif





