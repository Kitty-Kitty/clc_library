/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-11-24

Description:

**************************************************************************/

#ifndef _CP_CSS_STD_INCLUDE_H_
#define _CP_CSS_STD_INCLUDE_H_


#include "cp_core.h"
#include "prot_gmp_core.h"
#include "css_media_info.h"



/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: cp_std_convert_position
*
* 函数说明: 转换位置信息
*
* 参    数: gmdt_rectpair_p_t *gmdt_rp						[in]参数说明
* 参    数: cp_play_position_t * pp						[in]参数说明
*
* 返 回 值: cp_int32_t
*           0  : 成功 
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2016-11-24 14:06:30
******************************************************************************************************/
cp_int32_t	cp_std_convert_position(gmdt_rectpair_p_t *gmdt_rp, cp_play_position_t *pp);

#endif