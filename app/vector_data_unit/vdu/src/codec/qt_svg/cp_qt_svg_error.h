/*******************************************************************************
*
*Copyright:novigo
*
*File name: cp_qt_svg_error.h
*
*Author:fangzhenmu@novigo.com.cn
*
*Version: 1.0
*
*Date:2018/01/30
*
*Description: create (cp_qt_svg_error.h)
*
*Others:
*
*History:
*******************************************************************************/

#ifndef _CP_QT_SVG_ERROR_H_
#define _CP_QT_SVG_ERROR_H_



//这里设置错误码
#define	 cp_qt_svg_set_errno(module, input_error_no)													\
	do {																								\
		(module)->error_no = input_error_no;															\
	} while (0)


//这里获取错误码
#define	 cp_qt_svg_get_errno(module)				((module)->error_no)


#endif //_CP_QT_SVG_ERROR_H_


