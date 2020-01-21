/*******************************************************************************
*
*Copyright:novigo
*
*File name: cp_frame_rect.h
*
*Author:fangzhenmu@novigo.com.cn
*
*Version: 1.0
*
*Date:2017/08/17
*
*Description: create (cp_frame_rect.h)
*
*Others:
*
*History:
*******************************************************************************/

#ifndef _CP_FRAME_RECT_H_
#define _CP_FRAME_RECT_H_



#include "cp_media_core.h"



typedef struct cp_rect_s							cp_rect_t;
typedef	struct cp_frame_box_s						cp_frame_box_t;
typedef struct cp_frame_play_position_s				cp_frame_play_position_t;



#pragma pack(1)


/************************************************************************/
/* frame rect数据                                                       */
/*                                                                      */
/*        .................................................             */
/*        .                                               .             */
/*        .      _ top_______________________________     .             */
/*        .     |                                    |    .             */
/*        .    left                                  |    .             */
/*        .     |                                    |    .             */
/*        .     |                                    |    .             */
/*        .     |                                   right .             */
/*        .     |                                    |    .             */
/*        .     | ____________________________bottom_|    .             */
/*        .                                               .             */
/*        .................................................             */
/*                                                                      */
/************************************************************************/
struct cp_rect_s
{
	cp_uint32_t			left;
	cp_uint32_t			top;
	cp_uint32_t			right;
	cp_uint32_t			bottom;
};


/************************************************************************/
/* frame element数据,参考CSS盒子模型                                     */
/*                                                                      */
/*                                                                      */
/*        .................................................             */
/*        .                    margin                     .             */
/*        .                                               .             */
/*        .      _____________ border _____________       .             */
/*        .     | xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx |      .             */
/*        .     | xxxxxxxxxxx  padding  xxxxxxxxxx |      .             */
/*        .     | xxxxxxx ________________ xxxxxxx |      .             */
/*        .     | xxxxxx |                | xxxxxx |      .             */
/*        .     | xxxxxx |     content    | xxxxxx |      .             */
/*        .     | xxxxxx |________________| xxxxxx |      .             */
/*        .     | xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx |      .             */
/*        .     | xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx |      .             */
/*        .     | ________________________________ |      .             */
/*        .                                               .             */
/*        .                                               .             */
/*        .................................................             */
/*                                                                      */
/*                                                                      */
/************************************************************************/
struct cp_frame_box_s
{
	cp_rect_t								content;			//表示指定矩形框内容
	cp_rect_t								padding;			//表示指定矩形框填充
	cp_rect_t								border;				//表示指定矩形框边框
	cp_rect_t								margin;				//表示指定矩形框边界
};


/************************************************************************/
/* frame 播放位置信息                                                    */
/*                                                                      */
/*                                            ____________________      */
/*        .......................            |                    |     */
/*        .                     .            |                    |     */
/*        .      source         .   ---->    |     destination    |     */
/*        .                     .            |                    |     */
/*        .......................            |____________________|     */
/*                                                                      */
/*                                                                      */
/************************************************************************/
struct cp_frame_play_position_s
{
	cp_frame_box_t							source;				//表示信号帧源位置信息
	cp_frame_box_t							dest;				//表示信号帧目的位置信息
};



#pragma pack()



#endif //_CP_FRAME_RECT_H_


