/*******************************************************************************
*
*Copyright:novigo
*
*File name: cp_vdu_process_struct_proc.h
*
*Author:fangzhenmu@novigo.com.cn
*
*Version: 1.0
*
*Date:2018/02/17
*
*Description: create (cp_vdu_process_struct_proc.h)
*
*Others:
*
*History:
*******************************************************************************/

#ifndef _CP_VDU_PROCESS_STRUCT_PROC_H_
#define _CP_VDU_PROCESS_STRUCT_PROC_H_



#include "cp_vdu.h"
#include "cp_vdu_process_struct.h"



//设置process struct的类型
#define cp_vdu_process_struct_set_type(ps)					((ps)->type = cp_vdu_process_struct_type_process);

//设置channel process struct的类型
#define cp_vdu_channel_process_struct_set_type(ps)			((ps)->type = cp_vdu_process_struct_type_channel);




/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: fill_vdu_to_process_struct
*
* 函数说明: 初始化vdu process内容
*
* 参    数: cp_vdu_process_t *process_struct					[in]参数说明
*
* 返 回 值: cp_extern cp_int32_t
*           0  : 成功
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2017-03-26 14:07:54
******************************************************************************************************/
cp_int32_t fill_vdu_to_process_struct(cp_vdu_process_t *process_struct, cp_vdu_t *vdu);

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: fill_process_struct_to_vdu
*
* 函数说明: 初始化vdu process内容
*
* 参    数: cp_vdu_process_t *process_struct					[in]参数说明
*
* 返 回 值: cp_extern cp_int32_t
*           0  : 成功
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2017-03-26 14:07:54
******************************************************************************************************/
cp_int32_t fill_process_struct_to_vdu(cp_vdu_t *vdu, cp_vdu_process_t *process_struct);





/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: fill_vdu_channel_to_process_struct
*
* 函数说明: 初始化channel process struct内容
*
* 参    数: cp_vdu_channel_process_t *channel_process_struct					[in]参数说明
*
* 返 回 值: cp_extern cp_int32_t
*           0  : 成功
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2017-03-26 14:07:54
******************************************************************************************************/
cp_int32_t fill_vdu_channel_to_process_struct(
	cp_vdu_channel_process_t *channel_process_struct, cp_vdu_channel_t *vdu_channel);

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: fill_vdu_channel_to_process_struct
*
* 函数说明: 初始化channel process struct内容
*
* 参    数: cp_vdu_channel_process_t *channel_process_struct					[in]参数说明
*
* 返 回 值: cp_extern cp_int32_t
*           0  : 成功
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2017-03-26 14:07:54
******************************************************************************************************/
cp_int32_t fill_process_struct_to_vdu_channel(
	cp_vdu_channel_t *vdu_channel, cp_vdu_channel_process_t *channel_process_struct);


//设置channel process struct的image rect
/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: fill_process_struct_set_image_rect
*
* 函数说明: 设置image rect
*
* 参    数: cp_vdu_channel_process_t		*channel_process_struct					[in]参数说明
* 参    数: cp_vdu_rect_t				*image_rect								[in]参数说明
*
* 返 回 值: cp_extern cp_int32_t
*           0  : 成功
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2017-03-26 14:07:54
******************************************************************************************************/
cp_int32_t fill_process_struct_set_image_rect(
	cp_vdu_channel_process_t *channel_process_struct, cp_vdu_rect_t *image_rect);

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: convert_vdu_rect_to_cp_rect
*
* 函数说明: 将vdu_rect转化为cp_rect
*
* 参    数: cp_rect_t *cp_rect				[out]参数说明
* 参    数: cp_vdu_rect_t *vdu_rect			[in]参数说明
*
* 返 回 值: cp_extern cp_int32_t
*           0  : 成功
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2017-03-26 14:07:54
******************************************************************************************************/
cp_void_t convert_vdu_rect_to_cp_rect(cp_rect_t *cp_rect, cp_vdu_rect_t *vdu_rect);

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: fill_vdu_channel_to_process_struct
*
* 函数说明: 将cp_rect转化为vdu_rect
*
* 参    数: cp_vdu_rect_t *vdu_rect			[out]参数说明
* 参    数: cp_rect_t *cp_rect				[in]参数说明
*
* 返 回 值: cp_extern cp_int32_t
*           0  : 成功
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2017-03-26 14:07:54
******************************************************************************************************/
cp_void_t convert_cp_rect_to_vdu_rect(cp_vdu_rect_t *vdu_rect, cp_rect_t *cp_rect);

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: convert_vdu_pf_to_cp_pf
*
* 函数说明: 将vdu_pf转化为cp_pf
*
* 参    数: cp_vdu_pixel_format_e vpf			[out]参数说明
*
* 返 回 值: cp_codec_pixel_format_e
*           0  : 成功
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2017-03-26 14:07:54
******************************************************************************************************/
cp_codec_pixel_format_e convert_vdu_pf_to_cp_pf(cp_vdu_pixel_format_e vpf);


#endif