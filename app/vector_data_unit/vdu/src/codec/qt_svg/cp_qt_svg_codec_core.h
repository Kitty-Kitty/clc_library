/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/

#ifndef	_CP_QT_SVG_CODEC_CORE_INCLUDE_H_
#define _CP_QT_SVG_CODEC_CORE_INCLUDE_H_




//#define CP_QT_SVG_DEBUG_TEST_SAVE_TO_FILE							1
#define CP_QT_SVG_DEBUG_TEST_SAVE_TO_FILE_PROCESS_FLAG				"qt_svg_process"
#define CP_QT_SVG_DEBUG_TEST_SAVE_TO_FILE_CHANNEL_FLAG				"qt_svg_channel"




typedef struct cp_qt_svg_codec_info_s								cp_qt_svg_codec_info_t;
typedef	struct cp_qt_svg_codec_s									cp_qt_svg_codec_t;
typedef struct cp_qt_svg_process_s									cp_qt_svg_process_t;




#include "cp_core.h"
#include "cp_codec_core.h"
#include "cp_vdu_status.h"
#include "cp_qt_svg_printf.h"
#include "cp_qt_svg_error.h"
#include "cp_vdu_codec_core.h"
#include "cp_qt_svg_codec_info.h"
#include "cp_channel_manager.h"
#include "cp_qt_svg_codec.h"




#endif


