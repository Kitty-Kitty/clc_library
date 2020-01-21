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
/* frame rect����                                                       */
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
/* frame element����,�ο�CSS����ģ��                                     */
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
	cp_rect_t								content;			//��ʾָ�����ο�����
	cp_rect_t								padding;			//��ʾָ�����ο����
	cp_rect_t								border;				//��ʾָ�����ο�߿�
	cp_rect_t								margin;				//��ʾָ�����ο�߽�
};


/************************************************************************/
/* frame ����λ����Ϣ                                                    */
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
	cp_frame_box_t							source;				//��ʾ�ź�֡Դλ����Ϣ
	cp_frame_box_t							dest;				//��ʾ�ź�֡Ŀ��λ����Ϣ
};



#pragma pack()



#endif //_CP_FRAME_RECT_H_


