/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/
#include "cp_qt_svg_unit.h"




/*******************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: check_rect_valid
*
* 函数全名: check_rect_valid
*
* 函数访问: public 
*
* 函数说明: 判断rect的有效性
*
* 参    数: cp_rect_t *rect						[in/out]参数说明
*
* 返 回 值: cp_bool_t
*           cp_true : 成功
*         cp_false  : 失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2018-1-29 16:39:47
********************************************************************************/
cp_bool_t check_rect_valid(cp_rect_t *rect)
{
	if (!rect || rect->top <= 0 || rect->left <= 0) {
		return cp_false;
	}

	if (rect->right - rect->left <= 0 || 
		rect->bottom - rect->top <= 0) {
		return cp_false;
	}

	return cp_true;
}

/*******************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: create_a_rect
*
* 函数全名: create_a_rect
*
* 函数访问: public 
*
* 函数说明: 创建一个rect
*
* 参    数: int x						[in/out]参数说明
* 参    数: int y						[in/out]参数说明
* 参    数: int width						[in/out]参数说明
* 参    数: int height						[in/out]参数说明
*
* 返 回 值: cp_rect_t
*           0  : 成功
*         非0  : 失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2018-1-29 17:04:21
********************************************************************************/
cp_rect_t create_a_rect(int x, int y, int width, int height)
{
	cp_rect_t					tmp_rect = {0, };

	tmp_rect.left = x;
	tmp_rect.top = y;
	tmp_rect.right = x + width;
	tmp_rect.bottom = y + height;

	return tmp_rect;
}





/*******************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: convert_cpf_to_qimage_format
*
* 函数全名: convert_cpf_to_qimage_format
*
* 函数访问: public
*
* 函数说明: 将css格式定义转换为QImage的格式
*
* 参    数: cp_codec_pixel_format_e cpf						[in/out]参数说明
*
* 返 回 值: QImage::Format
*           0  : 成功
*         非0  : 失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2018-1-29 16:20:51
********************************************************************************/
QImage::Format convert_cpf_to_qimage_format(cp_codec_pixel_format_e cpf)
{
	switch (cpf)
	{
	case cp_codec_pixel_format_argb:
	{
		return QImage::Format_ARGB32;
	}
	break;
	case cp_codec_pixel_format_rgba:
	{
		return QImage::Format_RGBA8888;
	}
	break;
	default:
	{

	}
	break;
	}
	return QImage::Format_Invalid;
}




