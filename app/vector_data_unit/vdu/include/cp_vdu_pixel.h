/*******************************************************************************
*
*Copyright:novigo
*
*File name: cp_vdu_pixel.h
*
*Author:fangzhenmu@novigo.com.cn
*
*Version: 1.0
*
*Date:2018/02/02
*
*Description: create (cp_vdu_pixel.h)
*
*Others:
*
*History:
*******************************************************************************/

#ifndef _CP_VDU_PIXEL_H_
#define _CP_VDU_PIXEL_H_




//typedef	enum cp_vdu_pixel_format_enum						cp_vdu_pixel_format_e;



/************************************************************************/
/* ∂®“Â¥ÌŒÛ±‡¬Î                                                          */
/************************************************************************/
typedef enum cp_vdu_pixel_format_enum
{
	cp_vdu_pixel_format_none = 0x00000000,
	cp_vdu_pixel_format_argb8888,
	cp_vdu_pixel_format_rgba8888,
	cp_vdu_pixel_format_end = 0x10000000,
}cp_vdu_pixel_format_e;




#endif //_CP_VDU_PIXEL_H_


