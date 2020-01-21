/*******************************************************************************
*
*Copyright:novigo
*
*File name: cp_qt_svg_unit.h
*
*Author:fangzhenmu@novigo.com.cn
*
*Version: 1.0
*
*Date:2018/01/31
*
*Description: create (cp_qt_svg_unit.h)
*
*Others:
*
*History:
*******************************************************************************/

#ifndef _CP_QT_SVG_UNIT_H_
#define _CP_QT_SVG_UNIT_H_



#include "cp_qt_svg_include.h"


cp_bool_t check_rect_valid(cp_rect_t *rect);
cp_rect_t create_a_rect(int x, int y, int width, int height);

QImage::Format convert_cpf_to_qimage_format(cp_codec_pixel_format_e cpf);


#endif //_CP_QT_SVG_UNIT_H_



