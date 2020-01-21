/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/

#ifndef	_CP_QT_SVG_INCLUDE_INCLUDE_H_
#define _CP_QT_SVG_INCLUDE_INCLUDE_H_

#include "cp_qt_svg_codec_core.h"


#include "QtCore/QBuffer"
#include "QtWidgets/QApplication"
#include "QtCore/QCommandLineOption"
#include "QtCore/QCommandLineParser"
#include "QtWidgets/QGraphicsView"
#include "QtWidgets/QGraphicsRectItem"
#include "QtOpenGL/QGLWidget"
#include "QtSvg/QGraphicsSvgItem"
#include "QtSvg/QSvgRenderer"
#include "QtGui/QOpenGLContext"
#include "QtGui/QOpenGLPaintDevice"


QT_BEGIN_NAMESPACE
class QGraphicsSvgItem;
class QSvgRenderer;
QT_END_NAMESPACE


typedef struct cp_qt_svg_process_info_s				cp_qt_svg_process_info_t;
typedef	struct cp_qt_svg_process_debug_info_s		cp_qt_svg_process_debug_info_t;
typedef struct cp_qt_svg_channel_info_s				cp_qt_svg_channel_info_t;
typedef struct cp_qt_svg_channel_scene_s			cp_qt_svg_channel_scene_t;
typedef struct cp_qt_svg_channel_s					cp_qt_svg_channel_t;


#include "cp_qt_svg_process.h"
#include "cp_qt_svg_channel.h"


#endif


