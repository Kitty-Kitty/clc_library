/*******************************************************************************
*
*Copyright:novigo
*
*File name: cp_qt_svg_printf.h
*
*Author:fangzhenmu@novigo.com.cn
*
*Version: 1.0
*
*Date:2018/01/26
*
*Description: create (cp_qt_svg_printf.h)
*
*Others:
*
*History:
*******************************************************************************/

#ifndef _CP_QT_SVG_PRINTF_H_
#define _CP_QT_SVG_PRINTF_H_



//这里重新包装了打印信息的格式
#define	 cp_qt_svg_log(level, qt_svg, format, ...)													\
	do {																							\
		cp_module_log(level, (qt_svg), format,														\
			##__VA_ARGS__);																			\
	} while (0)



//这里重新包装了打印信息的格式
#define	 cp_qt_svg_process_log(level, qt_svg_process, format, ...)									\
	do {																							\
		if (qt_svg_process && qt_svg_process->codec) {												\
			cp_module_log(level, (qt_svg_process->codec),  "qt_svg_process[0x%x] " format,			\
				qt_svg_process, ##__VA_ARGS__);														\
		}																							\
	} while (0)


//这里重新包装了打印信息的格式
#define	 cp_qt_svg_channel_log(level, qt_svg_channel, format, ...)									\
	do {																							\
		if (qt_svg_channel && qt_svg_channel->process && qt_svg_channel->process->codec) {			\
			cp_module_log(level, (qt_svg_channel->process->codec), "qt_svg_process[0x%x] qt_svg_channel[0x%x] " format,							\
				 qt_svg_channel->process, qt_svg_channel, ##__VA_ARGS__);							\
		}																							\
	} while (0)




#endif //_CP_QT_SVG_PRINTF_H_




