/*******************************************************************************
*
*Copyright:novigo
*
*File name: cp_vdu_process_struct.c
*
*Author:fangzhenmu@novigo.com.cn
*
*Version: 1.0
*
*Date:2018/02/02
*
*Description: create (cp_vdu_process_struct.c)
*
*Others:
*
*History:
*******************************************************************************/
#include "cp_vdu_process_struct_proc.h"




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
cp_int32_t fill_vdu_to_process_struct(cp_vdu_process_t *process_struct, cp_vdu_t *vdu)
{
	if (!process_struct) {
		return -1;
	}

	cp_memset(process_struct, 0, cp_sizeof(cp_vdu_process_t));
	process_struct->type = cp_vdu_process_struct_type_process;
	process_struct->vdu = vdu;

	return 0;
}

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
cp_int32_t fill_process_struct_to_vdu(cp_vdu_t *vdu, cp_vdu_process_t *process_struct)
{
	return 0;
}










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
	cp_vdu_channel_process_t *channel_process_struct, cp_vdu_channel_t *vdu_channel)
{
	if (!channel_process_struct || !vdu_channel) {
		return -1;
	}

	cp_memset(channel_process_struct, 0, cp_sizeof(cp_vdu_channel_process_t));
	channel_process_struct->type = cp_vdu_process_struct_type_channel;
	channel_process_struct->index = vdu_channel->index;
	channel_process_struct->channel = vdu_channel->channel;

	return 0;
}

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
	cp_vdu_channel_t *vdu_channel, cp_vdu_channel_process_t *channel_process_struct)
{
	return 0;
}

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
cp_int32_t fill_process_struct_set_image_rect(cp_vdu_channel_process_t *channel_process_struct, cp_vdu_rect_t *image_rect)
{
	convert_vdu_rect_to_cp_rect(&channel_process_struct->image_rect, image_rect);
	return 0;
}

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
cp_void_t convert_vdu_rect_to_cp_rect(cp_rect_t *cp_rect, cp_vdu_rect_t *vdu_rect)
{
	cp_rect->left = vdu_rect->x;
	cp_rect->top = vdu_rect->y;
	cp_rect->right = vdu_rect->x + vdu_rect->width;
	cp_rect->bottom = vdu_rect->y + vdu_rect->height;
}

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
cp_void_t convert_cp_rect_to_vdu_rect(cp_vdu_rect_t *vdu_rect, cp_rect_t *cp_rect)
{
	vdu_rect->x = cp_rect->left;
	vdu_rect->y = cp_rect->top;
	vdu_rect->width = cp_rect->right - cp_rect->left;
	vdu_rect->height = cp_rect->bottom - cp_rect->top;
}

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
cp_codec_pixel_format_e convert_vdu_pf_to_cp_pf(cp_vdu_pixel_format_e vpf)
{
	switch (vpf)
	{
	case cp_vdu_pixel_format_argb8888:
	{
		return cp_codec_pixel_format_argb;
	}
	break;
	case cp_vdu_pixel_format_rgba8888:
	{
		return cp_codec_pixel_format_rgba;
	}
	break;
	default:
	{
		return cp_codec_pixel_format_none;
	}
	break;
	}

	return cp_codec_pixel_format_none;
}