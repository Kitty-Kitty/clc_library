/*******************************************************************************
*
*Copyright:novigo
*
*File name: cp_vdu_option.h
*
*Author:fangzhenmu@novigo.com.cn
*
*Version: 1.0
*
*Date:2018/01/29
*
*Description: create (cp_vdu_option.h)
*
*Others:
*
*History:
*******************************************************************************/

#ifndef _CP_VDU_TYPE_H_
#define _CP_VDU_TYPE_H_



//typedef	 enum cp_vdu_type_enum					cp_vdu_type_e;
//typedef	 enum cp_vdu_channel_type_enum			cp_vdu_channel_type_e;


/************************************************************************/
/* 表示vdu的类型                                                         */
/************************************************************************/
typedef	enum cp_vdu_type_enum
{
	cp_vdu_type_none = 0x00,
	cp_vdu_type_svg = 0x01
}cp_vdu_type_e;


/************************************************************************/
/* 表示vdu 通道的类型                                                    */
/************************************************************************/
typedef	enum cp_vdu_channel_type_enum
{
	cp_vdu_channel_type_none = 0x00,
	cp_vdu_channel_type_svg = 0x01
}cp_vdu_channel_type_e;


#endif //_CP_VDU_OPTION_H_


