/*******************************************************************************
*
*Copyright:novigo
*
*File name: cp_vdu_rect.h
*
*Author:fangzhenmu@novigo.com.cn
*
*Version: 1.0
*
*Date:2018/01/29
*
*Description: create (cp_vdu_rect.h)
*
*Others:
*
*History:
*******************************************************************************/

#ifndef _CP_VDU_RECT_H_
#define _CP_VDU_RECT_H_



typedef struct cp_vdu_rect_s						cp_vdu_rect_t;
typedef struct cp_vdu_coordinate_s					cp_vdu_coordinate_t;



#pragma pack(1)


/************************************************************************/
/* vdu rect数据                                                       */
/*                                                                      */
/*        .................................................             */
/*        .                                               .             */
/*        .      _ x____________width________________     .             */
/*        .     |                                    |    .             */
/*        .     y                                    |    .             */
/*        .     |                                    |    .             */
/*        .     |                                    |    .             */
/*        .     |                                   height.             */
/*        .     |                                    |    .             */
/*        .     | ___________________________________|    .             */
/*        .                                               .             */
/*        .................................................             */
/*                                                                      */
/************************************************************************/
struct cp_vdu_rect_s
{
	double				x;									//表示坐标起始位置x轴数值
	double				y;									//表示坐标起始位置y轴数值
	double				width;
	double				height;
};

/************************************************************************/
/* 坐标信息                                                              */
/************************************************************************/
struct cp_vdu_coordinate_s
{
	double				x;
	double				y;
	double				z;
};


#pragma pack()




#endif //_CP_VDU_RECT_H_





