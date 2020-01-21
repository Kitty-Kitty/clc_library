/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/
#include "cp_qt_svg_unit.h"




/*******************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: check_rect_valid
*
* ����ȫ��: check_rect_valid
*
* ��������: public 
*
* ����˵��: �ж�rect����Ч��
*
* ��    ��: cp_rect_t *rect						[in/out]����˵��
*
* �� �� ֵ: cp_bool_t
*           cp_true : �ɹ�
*         cp_false  : ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2018-1-29 16:39:47
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
* ��Ȩ����: fz & novigo
*
* ��������: create_a_rect
*
* ����ȫ��: create_a_rect
*
* ��������: public 
*
* ����˵��: ����һ��rect
*
* ��    ��: int x						[in/out]����˵��
* ��    ��: int y						[in/out]����˵��
* ��    ��: int width						[in/out]����˵��
* ��    ��: int height						[in/out]����˵��
*
* �� �� ֵ: cp_rect_t
*           0  : �ɹ�
*         ��0  : ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2018-1-29 17:04:21
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
* ��Ȩ����: fz & novigo
*
* ��������: convert_cpf_to_qimage_format
*
* ����ȫ��: convert_cpf_to_qimage_format
*
* ��������: public
*
* ����˵��: ��css��ʽ����ת��ΪQImage�ĸ�ʽ
*
* ��    ��: cp_codec_pixel_format_e cpf						[in/out]����˵��
*
* �� �� ֵ: QImage::Format
*           0  : �ɹ�
*         ��0  : ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2018-1-29 16:20:51
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




