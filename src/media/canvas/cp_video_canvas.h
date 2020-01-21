/*******************************************************************************
*
*Copyright:novigo
*
*File name: cp_video_canvas.h
*
*Author:fangzhenmu@novigo.com.cn
*
*Version: 1.0
*
*Date:2017/08/20
*
*Description: create (cp_video_canvas.h)
*
*Others:
*
*History:
*******************************************************************************/

#ifndef _CP_VIDEO_CANVAS_H_
#define _CP_VIDEO_CANVAS_H_



#include "cp_media_canvas.h"




//typedef		struct cp_video_canvas_s					cp_video_canvas_t;




#pragma pack(1)




/************************************************************************/
/* 表示最终的输出图片                                                    */
/************************************************************************/
struct cp_video_canvas_s
{
	CP_MEDIA_CANVAS_FIELDS												//表示媒体基础信息

	//fpp表示媒体数据中需要被处理的宏块位置信息。
	//其中source表示媒体本身的全图位置信息；dest表示需要用于处理的图像区域；因此，source数据所表示的区域包含dest的数据所表示的区域；
	/************************************************************************/
	/* fpp数据使用说明                                                       */
	/*        .      __________________________________       .             */
	/*        .     | xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx |      .             */
	/*        .     | xxxxxxxx  fpp->source  xxxxxxxxx |      .             */
	/*        .     | xxxxxxx ________________ xxxxxxx |      .             */
	/*        .     | xxxxxx |                | xxxxxx |      .             */
	/*        .     | xxxxxx |   fpp->dest    | xxxxxx |      .             */
	/*        .     | xxxxxx |________________| xxxxxx |      .             */
	/*        .     | xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx |      .             */
	/*        .     | xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx |      .             */
	/*        .     | ________________________________ |      .             */
	/*                                                                      */
	/************************************************************************/
	cp_frame_play_position_t				fpp;

};

#pragma pack()


#endif //_CP_VIDEO_CANVAS_H_


