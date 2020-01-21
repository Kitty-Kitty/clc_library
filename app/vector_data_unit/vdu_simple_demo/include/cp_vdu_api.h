/*******************************************************************************
*
*Copyright:novigo
*
*File name: cp_vdu_api.h
*
*Author:fangzhenmu@novigo.com.cn
*
*Version: 1.0
*
*Date:2018/02/05
*
*Description: create (cp_vdu_api.h)
*
*Others:
*
*History:
*******************************************************************************/

#ifndef _CP_VDU_API_H_
#define _CP_VDU_API_H_



#include "cp_vdu.h"
#include "cp_vdu_status.h"



#ifdef __cplusplus
extern "C" {
#endif

	//cp_vdu处理函数
	///////////////////////////////////////////////////////////////////////////////

	/*******************************************************************************
	* 版权所有: fz & novigo
	*
	* 函数名称: cp_vdu_create
	*
	* 函数全名: cp_vdu_create
	*
	* 函数访问: public
	*
	* 函数说明: 创建一个cp_vdu_t对象
	*
	*
	* 返 回 值: cp_vdu_t *
	*         非NULL: 成功
	*         NULL  : 失败
	*
	* 备    注:该
	*
	* 作    者：fz
	* 电子邮箱： fangzhenmu@novigo.com.cn
	* 创建日期：2018-2-2 15:10:45
	********************************************************************************/
	cp_extern cp_vdu_t *cp_vdu_create();

	/*******************************************************************************
	* 版权所有: fz & novigo
	*
	* 函数名称: cp_vdu_destroy
	*
	* 函数全名: cp_vdu_destroy
	*
	* 函数访问: public
	*
	* 函数说明: 销毁cp_vdu对象
	*
	* 参    数: cp_vdu_t       *vdu    [in]被处理的vdu对象指针
	*
	* 返 回 值: int
	*           0  : 成功
	*         非0  : 失败
	*
	* 备    注:其他说明内容
	*
	* 作    者：fz
	* 电子邮箱： fangzhenmu@novigo.com.cn
	* 创建日期：2018-2-3 10:56:18
	********************************************************************************/
	cp_extern int cp_vdu_destroy(cp_vdu_t *vdu);

	/*******************************************************************************
	* 版权所有: fz & novigo
	*
	* 函数名称: cp_vdu_get_version
	*
	* 函数全名: cp_vdu_get_version
	*
	* 函数访问: public
	*
	* 函数说明: 获取版本信息
	*
	* 参    数: cp_vdu_t * vdu			[in]被处理的vdu对象指针
	*
	* 返 回 值: cp_vdu_version_t
	*
	* 备    注:其他说明内容
	*
	* 作    者：fz
	* 电子邮箱： fangzhenmu@novigo.com.cn
	* 创建日期：2018-2-5 16:53:47
	********************************************************************************/
	cp_vdu_version_t cp_vdu_get_version(cp_vdu_t *vdu);

	/*******************************************************************************
	* 版权所有: fz & novigo
	*
	* 函数名称: cp_vdu_get_status
	*
	* 函数全名: cp_vdu_get_status
	*
	* 函数访问: public
	*
	* 函数说明: 表示获取当前的状态码
	*
	* 参    数: cp_vdu_t * vdu						[in]参数说明
	*
	* 返 回 值: cp_vdu_status_e
	*
	* 备    注:其他说明内容
	*
	* 作    者：fz
	* 电子邮箱： fangzhenmu@novigo.com.cn
	* 创建日期：2018-2-5 17:10:50
	********************************************************************************/
	cp_vdu_status_e cp_vdu_get_status(cp_vdu_t *vdu);

	/*******************************************************************************
	* 版权所有: fz & novigo
	*
	* 函数名称: cp_vdu_set_coordinate
	*
	* 函数全名: cp_vdu_set_coordinate
	*
	* 函数访问: public
	*
	* 函数说明: 设置坐标信息,该坐标为模块在坐标系中的原点坐标。
	*
	* 参    数: cp_vdu_t				*vdu			[in]被处理的vdu对象指针
	* 参    数: cp_vdu_coordinate_t coordinate		[in]初始坐标信息
	*
	* 返 回 值: int
	*           0  : 成功
	*         非0  : 失败
	*
	* 备    注:
	*			1、该接口可以不使用时，默认位置为(0, 0, 0)
	*			2、如果使用该接口，则所有的roi、rect都使用以此为原点的坐标描述
	*
	* 作    者：fz
	* 电子邮箱： fangzhenmu@novigo.com.cn
	* 创建日期：2018-2-3 10:57:24
	********************************************************************************/
	cp_extern int cp_vdu_set_coordinate(cp_vdu_t *vdu, cp_vdu_coordinate_t coordinate);

	/*******************************************************************************
	* 版权所有: fz & novigo
	*
	* 函数名称: cp_vdu_get_coordinate
	*
	* 函数全名: cp_vdu_get_coordinate
	*
	* 函数访问: public
	*
	* 函数说明: 获取初始坐标信息
	*
	* 参    数: cp_vdu_t				*vdu			[in]被处理的vdu对象指针
	* 参    数: cp_vdu_coordinate_t *coordinate		[out]保存的坐标数据
	*
	* 返 回 值: int
	*           0  : 成功
	*         非0  : 失败
	*
	* 备    注:其他说明内容
	*
	* 作    者：fz
	* 电子邮箱： fangzhenmu@novigo.com.cn
	* 创建日期：2018-2-3 10:57:32
	********************************************************************************/
	cp_extern int cp_vdu_get_coordinate(cp_vdu_t *vdu, cp_vdu_coordinate_t *coordinate);

	/*******************************************************************************
	* 版权所有: fz & novigo
	*
	* 函数名称: cp_vdu_open_debug_mode
	*
	* 函数全名: cp_vdu_open_debug_mode
	*
	* 函数访问: public 
	*
	* 函数说明: 表示是否启动调试模式
	*
	* 参    数: cp_vdu_t		* vdu						[in]被处理的vdu对象指针
	* 参    数: char			* path						[in]表示调试模式下保存信息的目录地址
	*
	* 返 回 值: cp_extern int
	*           0  : 成功
	*         非0  : 失败
	*
	* 备    注:其他说明内容
	*
	* 作    者：fz
	* 电子邮箱： fangzhenmu@novigo.com.cn
	* 创建日期：2018-2-28 17:21:57
	********************************************************************************/
	cp_extern int cp_vdu_open_debug_mode(cp_vdu_t *vdu, char *path);

	/*******************************************************************************
	* 版权所有: fz & novigo
	*
	* 函数名称: cp_vdu_close_debug_mode
	*
	* 函数全名: cp_vdu_close_debug_mode
	*
	* 函数访问: public 
	*
	* 函数说明: 表示关闭调试模式
	*
	* 参    数: cp_vdu_t * vdu							[in]被处理的vdu对象指针
	*
	* 返 回 值: cp_extern int
	*           0  : 成功
	*         非0  : 失败
	*
	* 备    注:其他说明内容
	*
	* 作    者：fz
	* 电子邮箱： fangzhenmu@novigo.com.cn
	* 创建日期：2018-2-28 17:22:20
	********************************************************************************/
	cp_extern int cp_vdu_close_debug_mode(cp_vdu_t *vdu);

	/*******************************************************************************
	* 版权所有: fz & novigo
	*
	* 函数名称: cp_vdu_set_type
	*
	* 函数全名: cp_vdu_set_type
	*
	* 函数访问: public
	*
	* 函数说明: 设备vdu的类型
	*
	* 参    数: cp_vdu_t * vdu							[in]被处理的vdu对象指针
	* 参    数: cp_vdu_type_e type						[in]vdu对象的类型
	*
	* 返 回 值: int
	*           0  : 成功
	*         非0  : 失败
	*
	* 备    注:其他说明内容
	*
	* 作    者：fz
	* 电子邮箱： fangzhenmu@novigo.com.cn
	* 创建日期：2018-2-5 11:17:07
	********************************************************************************/
	cp_extern int cp_vdu_set_type(cp_vdu_t *vdu, cp_vdu_type_e type);

	/*******************************************************************************
	* 版权所有: fz & novigo
	*
	* 函数名称: cp_vdu_get_type
	*
	* 函数全名: cp_vdu_get_type
	*
	* 函数访问: public
	*
	* 函数说明: 获取vdu的类型
	*
	* 参    数: cp_vdu_t * vdu						[in]被处理的vdu对象指针
	*
	* 返 回 值: cp_vdu_type_e
	*
	* 备    注:其他说明内容
	*
	* 作    者：fz
	* 电子邮箱： fangzhenmu@novigo.com.cn
	* 创建日期：2018-2-5 11:17:28
	********************************************************************************/
	cp_vdu_type_e cp_vdu_get_type(cp_vdu_t *vdu);

	/*******************************************************************************
	* 版权所有: fz & novigo
	*
	* 函数名称: cp_vdu_set_roi
	*
	* 函数全名: cp_vdu_set_roi
	*
	* 函数访问: public
	*
	* 函数说明: 设置vdu被处理的感兴趣区域
	*
	* 参    数: cp_vdu_t       *vdu					[in]被处理的vdu对象指针
	* 参    数: cp_vdu_rect_t	rect				[in]设置感兴趣区域位置信息
	*
	* 返 回 值: int
	*           0  : 成功
	*         非0  : 失败
	*
	* 备    注:其他说明内容
	*
	* 作    者：fz
	* 电子邮箱： fangzhenmu@novigo.com.cn
	* 创建日期：2018-2-3 10:57:35
	********************************************************************************/
	cp_extern int cp_vdu_set_roi(cp_vdu_t *vdu, cp_vdu_rect_t rect);

	/*******************************************************************************
	* 版权所有: fz & novigo
	*
	* 函数名称: cp_vdu_set_roi_parameters
	*
	* 函数全名: cp_vdu_set_roi_parameters
	*
	* 函数访问: public 
	*
	* 函数说明: 设置vdu被处理的感兴趣区域的详细参数
	*
	* 参    数: cp_vdu_t * vdu						[in]被处理的vdu对象指针
	* 参    数: int x								[in]设置感兴趣区域位置信息 x 值
	* 参    数: int y								[in]设置感兴趣区域位置信息 y 值
	* 参    数: int width							[in]设置感兴趣区域的宽度
	* 参    数: int height							[in]设置感兴趣区域的高度
	*
	* 返 回 值: cp_extern int
	*           0  : 成功
	*         非0  : 失败
	*
	* 备    注:其他说明内容
	*
	* 作    者：fz
	* 电子邮箱： fangzhenmu@novigo.com.cn
	* 创建日期：2018-2-26 14:19:59
	********************************************************************************/
	cp_extern int cp_vdu_set_roi_parameters(cp_vdu_t *vdu, int x, int y, int width, int height);

	/*******************************************************************************
	* 版权所有: fz & novigo
	*
	* 函数名称: cp_vdu_get_roi
	*
	* 函数全名: cp_vdu_get_roi
	*
	* 函数访问: public
	*
	* 函数说明: 获取感兴趣区域
	*
	* 参    数: cp_vdu_t       *vdu             [in]被处理的vdu对象指针
	* 参    数: cp_vdu_rect_t *rect             [out]保存获取的感兴趣区域位置信息
	*
	* 返 回 值: int
	*           0  : 成功
	*         非0  : 失败
	*
	* 备    注:其他说明内容
	*
	* 作    者：fz
	* 电子邮箱： fangzhenmu@novigo.com.cn
	* 创建日期：2018-2-3 10:57:40
	********************************************************************************/
	cp_extern int cp_vdu_get_roi(cp_vdu_t *vdu, cp_vdu_rect_t *rect);

	/*******************************************************************************
	* 版权所有: fz & novigo
	*
	* 函数名称: cp_vdu_clear_roi
	*
	* 函数全名: cp_vdu_clear_roi
	*
	* 函数访问: public
	*
	* 函数说明: 清除感兴趣区域
	*
	* 参    数: cp_vdu_t       *vdu             [in]被处理的vdu对象指针
	*
	* 返 回 值: int
	*           0  : 成功
	*         非0  : 失败
	*
	* 备    注:其他说明内容
	*
	* 作    者：fz
	* 电子邮箱： fangzhenmu@novigo.com.cn
	* 创建日期：2018-2-3 10:58:00
	********************************************************************************/
	cp_extern int cp_vdu_clear_roi(cp_vdu_t *vdu);

	/*******************************************************************************
	* 版权所有: fz & novigo
	*
	* 函数名称: cp_vdu_get_roi_pixel
	*
	* 函数全名: cp_vdu_get_roi_pixel
	*
	* 函数访问: public
	*
	* 函数说明: 获取感兴趣区域的位图流
	*
	* 参    数: cp_vdu_t       *vdu             [in]被处理的vdu对象指针
	* 参    数: char * buf						[out]保存返回位图数据的内容地址
	* 参    数: int len							[in]保存返回位图数据的内容地址的长度
	* 参    数: cp_vdu_pixel_format_e vpf		[in]返回位图数据的编码方式
	* 参    数: cp_vdu_rect_t *scale_rect		[in]指定返回位图数据的尺寸
	*
	* 返 回 值: int
	*       <= 0  : 失败
	*         >0  : 表示返回位图数据的实际长度
	*
	* 备    注:其他说明内容
	*
	* 作    者：fz
	* 电子邮箱： fangzhenmu@novigo.com.cn
	* 创建日期：2018-2-3 10:58:05
	********************************************************************************/
	cp_extern int cp_vdu_get_roi_pixel(cp_vdu_t *vdu,
		char *buf, int len,
		cp_vdu_pixel_format_e vpf,
		cp_vdu_rect_t *scale_rect);

	/*******************************************************************************
	* 版权所有: fz & novigo
	*
	* 函数名称: cp_vdu_get_rect_pixel
	*
	* 函数全名: cp_vdu_get_rect_pixel
	*
	* 函数访问: public
	*
	* 函数说明: 获取指定区域的位图流
	*
	* 参    数: cp_vdu_t       *vdu             [in]被处理的vdu对象指针
	* 参    数: char * buf						[out]保存返回位图数据的内容地址
	* 参    数: int len							[in]保存返回位图数据的内容地址的长度
	* 参    数: cp_vdu_pixel_format_e vpf		[in]返回位图数据的编码方式
	* 参    数: cp_vdu_rect_t rect				[in]设置指定区域的数值
	* 参    数: cp_vdu_rect_t *scale_rect		[in]指定返回位图数据的尺寸
	*
	* 返 回 值: int
	*       <= 0  : 失败
	*         >0  : 表示返回位图数据的实际长度
	*
	* 备    注:其他说明内容
	*
	* 作    者：fz
	* 电子邮箱： fangzhenmu@novigo.com.cn
	* 创建日期：2018-2-3 10:58:14
	********************************************************************************/
	cp_extern int cp_vdu_get_rect_pixel(cp_vdu_t *vdu,
		char *buf, int len,
		cp_vdu_pixel_format_e vpf,
		cp_vdu_rect_t rect,
		cp_vdu_rect_t *scale_rect);






	//cp_vdu_channel处理函数
	///////////////////////////////////////////////////////////////////////////////

	/*******************************************************************************
	* 版权所有: fz & novigo
	*
	* 函数名称: cp_vdu_create_channel
	*
	* 函数全名: cp_vdu_create_channel
	*
	* 函数访问: public
	*
	* 函数说明: 在vdu中创建一个指定类型的通道。
	*		 * 新创建的通道与所属vdu仅存在逻辑关系，不存处理包含关系。所以不被vdu画布显示处理。
	*		 * 若想在vdu画布显示处理，请调用cp_vdu_insert_channel 函数
	*
	* 参    数: cp_vdu_t       *vdu								 [in]被处理的vdu对象指针
	* 参    数: cp_vdu_channel_type_e channel_type               [in]创建的通道类型
	*
	* 返 回 值: cp_vdu_channel_t*
	*         非NULL  : 成功
	*         NULL  : 失败
	*
	* 备    注:其他说明内容
	*
	* 作    者：fz
	* 电子邮箱： fangzhenmu@novigo.com.cn
	* 创建日期：2018-2-3 10:58:17
	********************************************************************************/
	cp_vdu_channel_t* cp_vdu_create_channel(cp_vdu_t *vdu, cp_vdu_channel_type_e channel_type);

	/*******************************************************************************
	* 版权所有: fz & novigo
	*
	* 函数名称: cp_vdu_destroy_all_channels
	*
	* 函数全名: cp_vdu_destroy_all_channels
	*
	* 函数访问: public
	*
	* 函数说明: 销毁vdu中所有已经创建的通道
	*
	* 参    数: cp_vdu_t       *vdu             [in]被处理的vdu对象指针
	*
	* 返 回 值: int
	*           0  : 成功
	*         非0  : 失败
	*
	* 备    注:其他说明内容
	*
	* 作    者：fz
	* 电子邮箱： fangzhenmu@novigo.com.cn
	* 创建日期：2018-2-3 10:58:23
	********************************************************************************/
	cp_extern int cp_vdu_destroy_all_channels(cp_vdu_t *vdu);

	/*******************************************************************************
	* 版权所有: fz & novigo
	*
	* 函数名称: cp_vdu_destroy_channel
	*
	* 函数全名: cp_vdu_destroy_channel
	*
	* 函数访问: public
	*
	* 函数说明: 销毁vdu中指定的通道
	*
	* 参    数: cp_vdu_channel_t * vdu_channel						[in]表示需要处理的通道
	*
	* 返 回 值: int
	*           0  : 成功
	*         非0  : 失败
	*
	* 备    注:其他说明内容
	*
	* 作    者：fz
	* 电子邮箱： fangzhenmu@novigo.com.cn
	* 创建日期：2018-2-3 10:58:28
	********************************************************************************/
	cp_extern int cp_vdu_destroy_channel(cp_vdu_channel_t *vdu_channel);

	/*******************************************************************************
	* 版权所有: fz & novigo
	*
	* 函数名称: cp_vdu_channel_get_status
	*
	* 函数全名: cp_vdu_channel_get_status
	*
	* 函数访问: public
	*
	* 函数说明: 表示获取当前的状态码
	*
	* 参    数: cp_vdu_t * vdu						[in]表示需要处理的通道
	*
	* 返 回 值: cp_vdu_status_e
	*
	* 备    注:其他说明内容
	*
	* 作    者：fz
	* 电子邮箱： fangzhenmu@novigo.com.cn
	* 创建日期：2018-2-5 17:13:32
	********************************************************************************/
	cp_extern cp_vdu_status_e cp_vdu_channel_get_status(cp_vdu_channel_t *vdu_channel);

	/*******************************************************************************
	* 版权所有: fz & novigo
	*
	* 函数名称: cp_vdu_insert_channel
	*
	* 函数全名: cp_vdu_insert_channel
	*
	* 函数访问: public
	*
	* 函数说明: 将创建的通道插入到vdu画布中处理。
	*
	* 参    数: cp_vdu_t				*vdu               [in]被处理的vdu对象指针
	* 参    数: cp_vdu_channel_t		* vdu_channel      [in]表示需要处理的通道
	*
	* 返 回 值: int
	*           0  : 成功
	*         非0  : 失败
	*
	* 备    注:详细内容可以结合cp_vdu_create_channel接口描述信息
	*
	* 作    者：fz
	* 电子邮箱： fangzhenmu@novigo.com.cn
	* 创建日期：2018-2-3 10:58:34
	********************************************************************************/
	cp_extern int cp_vdu_insert_channel(cp_vdu_t *vdu, cp_vdu_channel_t *vdu_channel);

	/*******************************************************************************
	* 版权所有: fz & novigo
	*
	* 函数名称: cp_vdu_remove_channel
	*
	* 函数全名: cp_vdu_remove_channel
	*
	* 函数访问: public
	*
	* 函数说明: 将通道从vdu画布中移除，即恢复成最原始的初始关系。
	*
	* 参    数: cp_vdu_t       *vdu             [in]被处理的vdu对象指针
	* 参    数: cp_vdu_channel_t * vdu_channel      [in]表示需要处理的通道
	*
	* 返 回 值: int
	*           0  : 成功
	*         非0  : 失败
	*
	* 备    注:详细内容可以结合cp_vdu_create_channel、cp_vdu_insert_channel的接口描述信息
	*
	* 作    者：fz
	* 电子邮箱： fangzhenmu@novigo.com.cn
	* 创建日期：2018-2-3 10:58:39
	********************************************************************************/
	cp_extern int cp_vdu_remove_channel(cp_vdu_t *vdu, cp_vdu_channel_t *vdu_channel);

	/*******************************************************************************
	* 版权所有: fz & novigo
	*
	* 函数名称: cp_vdu_channel_set_index
	*
	* 函数全名: cp_vdu_channel_set_index
	*
	* 函数访问: public
	*
	* 函数说明: 该函数主要用于设备通道索引号，主要实现图层间位置调整
	*
	* 参    数: cp_vdu_channel_t * vdu_channel      [in]表示需要处理的通道
	* 参    数: const int index						[in]表示图层索引号
	*
	* 返 回 值: int
	*           0  : 成功
	*         非0  : 失败
	*
	* 备    注:
	*			1、通道索引号：表示通道在cp_vdu中的层次关系，索引号越大越靠近上层。
	*			2、通道索引号取值：[0, 65535)
	* 作    者：fz
	* 电子邮箱： fangzhenmu@novigo.com.cn
	* 创建日期：2018-2-3 10:58:42
	********************************************************************************/
	cp_extern int cp_vdu_channel_set_index(cp_vdu_channel_t *vdu_channel, const int index);

	/*******************************************************************************
	* 版权所有: fz & novigo
	*
	* 函数名称: cp_vdu_channel_get_index
	*
	* 函数全名: cp_vdu_channel_get_index
	*
	* 函数访问: public
	*
	* 函数说明: 获取通道的索引信息
	*
	* 参    数: cp_vdu_channel_t * vdu_channel      [in]表示需要处理的通道
	*
	* 返 回 值: int
	*           0  : 成功
	*         非0  : 失败
	*
	* 备    注:其他说明内容
	*
	* 作    者：fz
	* 电子邮箱： fangzhenmu@novigo.com.cn
	* 创建日期：2018-2-5 11:07:16
	********************************************************************************/
	cp_extern int cp_vdu_channel_get_index(cp_vdu_channel_t *vdu_channel);

	/*******************************************************************************
	* 版权所有: fz & novigo
	*
	* 函数名称: cp_vdu_channel_set_vector_stream
	*
	* 函数全名: cp_vdu_channel_set_vector_stream
	*
	* 函数访问: public
	*
	* 函数说明: 设置通道需要处理的矢量数据流
	*
	* 参    数: cp_vdu_channel_t * vdu_channel      [in]表示需要处理的通道
	* 参    数: cp_vdu_vector_stream_type_e vs_type	[in]表示矢量数据流数据类型
	* 参    数: const char * buf						[in]表示矢量数据流的地址指针
	* 参    数: const int len						[in]表示矢量数据流的数据长度
	*
	* 返 回 值: int
	*           0  : 成功
	*         非0  : 失败
	*
	* 备    注:其他说明内容
	*
	* 作    者：fz
	* 电子邮箱： fangzhenmu@novigo.com.cn
	* 创建日期：2018-2-5 11:14:51
	********************************************************************************/
	cp_extern int cp_vdu_channel_set_vector_stream(cp_vdu_channel_t *vdu_channel,
		cp_vdu_vector_stream_type_e vs_type, const char *buf, const int len);

	/*******************************************************************************
	* 版权所有: fz & novigo
	*
	* 函数名称: cp_vdu_channel_set_roi
	*
	* 函数全名: cp_vdu_channel_set_roi
	*
	* 函数访问: public
	*
	* 函数说明: 设置通道被处理的感兴趣区域
	*
	* 参    数: cp_vdu_channel_t * vdu_channel			[in]表示需要处理的通道
	* 参    数: cp_vdu_rect_t rect						[in]设置感兴趣区域位置信息
	*
	* 返 回 值: int
	*           0  : 成功
	*         非0  : 失败
	*
	* 备    注:其他说明内容
	*
	* 作    者：fz
	* 电子邮箱： fangzhenmu@novigo.com.cn
	* 创建日期：2018-2-3 10:58:51
	********************************************************************************/
	cp_extern int cp_vdu_channel_set_roi(cp_vdu_channel_t *vdu_channel, cp_vdu_rect_t rect);

	/*******************************************************************************
	* 版权所有: fz & novigo
	*
	* 函数名称: cp_vdu_channel_set_roi_parameters
	*
	* 函数全名: cp_vdu_channel_set_roi_parameters
	*
	* 函数访问: public 
	*
	* 函数说明: 函数说明
	*
	* 参    数: cp_vdu_channel_t *vdu_channel		[in]表示需要处理的通道
	* 参    数: int x								[in]设置感兴趣区域位置信息 x 值
	* 参    数: int y								[in]设置感兴趣区域位置信息 y 值
	* 参    数: int width							[in]设置感兴趣区域的宽度
	* 参    数: int height							[in]设置感兴趣区域的高度
	*
	* 返 回 值: cp_extern int
	*           0  : 成功
	*         非0  : 失败
	*
	* 备    注:其他说明内容
	*
	* 作    者：fz
	* 电子邮箱： fangzhenmu@novigo.com.cn
	* 创建日期：2018-2-26 14:22:23
	********************************************************************************/
	cp_extern int cp_vdu_channel_set_roi_parameters(cp_vdu_channel_t *vdu_channel, int x, int y, int width, int height);

	/*******************************************************************************
	* 版权所有: fz & novigo
	*
	* 函数名称: cp_vdu_channel_get_roi
	*
	* 函数全名: cp_vdu_channel_get_roi
	*
	* 函数访问: public
	*
	* 函数说明: 获取感兴趣区域
	*
	* 参    数: cp_vdu_channel_t * vdu_channel      [in]表示需要处理的通道
	* 参    数: cp_vdu_rect_t *roi_rect				[out]保存获取的感兴趣区域位置信息
	*
	* 返 回 值: cp_vdu_rect_t
	*           0  : 成功
	*         非0  : 失败
	*
	* 备    注:其他说明内容
	*
	* 作    者：fz
	* 电子邮箱： fangzhenmu@novigo.com.cn
	* 创建日期：2018-2-3 10:58:56
	********************************************************************************/
	cp_extern int cp_vdu_channel_get_roi(cp_vdu_channel_t *vdu_channel, cp_vdu_rect_t *roi_rect);

	/*******************************************************************************
	* 版权所有: fz & novigo
	*
	* 函数名称: cp_vdu_channel_clear_roi
	*
	* 函数全名: cp_vdu_channel_clear_roi
	*
	* 函数访问: public
	*
	* 函数说明: 清除感兴趣区域
	*
	* 参    数: cp_vdu_channel_t * vdu_channel      [in]表示需要处理的通道
	*
	* 返 回 值: int
	*           0  : 成功
	*         非0  : 失败
	*
	* 备    注:其他说明内容
	*
	* 作    者：fz
	* 电子邮箱： fangzhenmu@novigo.com.cn
	* 创建日期：2018-2-3 10:59:01
	********************************************************************************/
	cp_extern int cp_vdu_channel_clear_roi(cp_vdu_channel_t *vdu_channel);

	/*******************************************************************************
	* 版权所有: fz & novigo
	*
	* 函数名称: cp_vdu_channel_get_roi_pixel
	*
	* 函数全名: cp_vdu_channel_get_roi_pixel
	*
	* 函数访问: public
	*
	* 函数说明: 获取感兴趣区域的位图流
	*
	* 参    数: cp_vdu_channel_t * vdu_channel	[in]表示需要处理的通道
	* 参    数: char * buf						[out]保存返回位图数据的内容地址
	* 参    数: int len							[in]保存返回位图数据的内容地址的长度
	* 参    数: cp_vdu_pixel_format_e vpf		[in]返回位图数据的编码方式
	* 参    数: cp_vdu_rect_t *scale_rect		[in]指定返回位图数据的尺寸
	*
	* 返 回 值: int
	*       <= 0  : 失败
	*         >0  : 表示返回位图数据的实际长度
	*
	* 备    注:其他说明内容
	*
	* 作    者：fz
	* 电子邮箱： fangzhenmu@novigo.com.cn
	* 创建日期：2018-2-3 10:59:06
	********************************************************************************/
	cp_extern int cp_vdu_channel_get_roi_pixel(cp_vdu_channel_t *vdu_channel,
		char *buf, int len,
		cp_vdu_pixel_format_e vpf,
		cp_vdu_rect_t *scale_rect);

	/*******************************************************************************
	* 版权所有: fz & novigo
	*
	* 函数名称: cp_vdu_channel_get_roi_pixel_by_image_info
	*
	* 函数全名: cp_vdu_channel_get_roi_pixel_by_image_info
	*
	* 函数访问: public
	*
	* 函数说明: 根据image info将感兴趣区域图形生成image图片
	*
	* 参    数: cp_vdu_channel_t * vdu_channel      [in]表示需要处理的通道
	* 参    数: cp_vdu_image_info_t *image_info		[out]保存返回位图数据的内容
	*
	* 返 回 值: int
	*       <= 0  : 失败
	*         >0  : 表示返回位图数据的实际长度
	*
	* 备    注:其他说明内容
	*
	* 作    者：fz
	* 电子邮箱： fangzhenmu@novigo.com.cn
	* 创建日期：2018-2-3 10:59:06
	********************************************************************************/
	cp_extern int cp_vdu_channel_get_roi_pixel_by_image_info(
		cp_vdu_channel_t *vdu_channel,
		cp_vdu_image_info_t *image_info);

	/*******************************************************************************
	* 版权所有: fz & novigo
	*
	* 函数名称: cp_vdu_channel_get_rect_pixel
	*
	* 函数全名: cp_vdu_channel_get_rect_pixel
	*
	* 函数访问: public
	*
	* 函数说明: 获取指定区域的位图流
	*
	* 参    数: cp_vdu_channel_t * vdu_channel	[in]表示需要处理的通道
	* 参    数: char * buf						[out]保存返回位图数据的内容地址
	* 参    数: int len							[in]保存返回位图数据的内容地址的长度
	* 参    数: cp_vdu_pixel_format_e vpf		[in]返回位图数据的编码方式
	* 参    数: cp_vdu_rect_t rect				[in]设置指定区域的数值
	* 参    数: cp_vdu_rect_t *scale_rect		[in]指定返回位图数据的尺寸
	*
	* 返 回 值: int
	*       <= 0  : 失败
	*         >0  : 表示返回位图数据的实际长度
	*
	* 备    注:其他说明内容
	*
	* 作    者：fz
	* 电子邮箱： fangzhenmu@novigo.com.cn
	* 创建日期：2018-2-3 10:59:09
	********************************************************************************/
	cp_extern int cp_vdu_channel_get_rect_pixel(cp_vdu_channel_t *vdu_channel,
		char *buf, int len,
		cp_vdu_pixel_format_e vpf,
		cp_vdu_rect_t rect,
		cp_vdu_rect_t *scale_rect);

	/*******************************************************************************
	* 版权所有: fz & novigo
	*
	* 函数名称: cp_vdu_channel_get_rect_pixel_by_image_info
	*
	* 函数全名: cp_vdu_channel_get_rect_pixel_by_image_info
	*
	* 函数访问: public
	*
	* 函数说明: 根据image info将rect指定的区域图形生成image图片
	*
	* 参    数: cp_vdu_channel_t * vdu_channel      [in]表示需要处理的通道
	* 参    数: cp_vdu_image_info_t *image_info		[out]保存返回位图数据的内容
	*
	* 返 回 值: int
	*       <= 0  : 失败
	*         >0  : 表示返回位图数据的实际长度
	*
	* 备    注:其他说明内容
	*
	* 作    者：fz
	* 电子邮箱： fangzhenmu@novigo.com.cn
	* 创建日期：2018-2-3 10:59:06
	********************************************************************************/
	cp_extern int cp_vdu_channel_get_rect_pixel_by_image_info(
		cp_vdu_channel_t *vdu_channel,
		cp_vdu_image_info_t *image_info);




	//cp_vdu_media_info处理函数
	///////////////////////////////////////////////////////////////////////////////

	/*******************************************************************************
	* 版权所有: fz & novigo
	*
	* 函数名称: cp_vdu_image_info_clear
	*
	* 函数全名: cp_vdu_image_info_clear
	*
	* 函数访问: public 
	*
	* 函数说明: 清除image info信息
	*
	* 参    数: cp_vdu_image_info_t * vdu_image      [out]表示图像描述信息
	*
	* 返 回 值: cp_extern int
	*           0  : 成功
	*         非0  : 失败
	*
	* 备    注:其他说明内容
	*
	* 作    者：fz
	* 电子邮箱： fangzhenmu@novigo.com.cn
	* 创建日期：2018-2-25 11:31:47
	********************************************************************************/
	cp_extern int cp_vdu_image_info_clear(cp_vdu_image_info_t *vdu_image);

	/*******************************************************************************
	* 版权所有: fz & novigo
	*
	* 函数名称: cp_vdu_image_info_set_pixel_format
	*
	* 函数全名: cp_vdu_image_info_set_pixel_format
	*
	* 函数访问: public 
	*
	* 函数说明: 设置图像色彩空间
	*
	* 参    数: cp_vdu_image_info_t * vdu_image      [out]表示图像描述信息
	* 参    数: cp_vdu_pixel_format_e vpf			 [in]位图数据的编码方式
	*
	* 返 回 值: cp_extern int
	*           0  : 成功
	*         非0  : 失败
	*
	* 备    注:其他说明内容
	*
	* 作    者：fz
	* 电子邮箱： fangzhenmu@novigo.com.cn
	* 创建日期：2018-2-25 11:32:10
	********************************************************************************/
	cp_extern int cp_vdu_image_info_set_pixel_format(cp_vdu_image_info_t *vdu_image, cp_vdu_pixel_format_e vpf);

	/*******************************************************************************
	* 版权所有: fz & novigo
	*
	* 函数名称: cp_vdu_image_info_get_pixel_format
	*
	* 函数全名: cp_vdu_image_info_get_pixel_format
	*
	* 函数访问: public 
	*
	* 函数说明: 获取图像色彩空间
	*
	* 参    数: cp_vdu_image_info_t * vdu_image      [in]表示图像描述信息
	*
	* 返 回 值: cp_extern cp_vdu_pixel_format_e
	*
	* 备    注:其他说明内容
	*
	* 作    者：fz
	* 电子邮箱： fangzhenmu@novigo.com.cn
	* 创建日期：2018-2-25 11:33:23
	********************************************************************************/
	cp_extern cp_vdu_pixel_format_e cp_vdu_image_info_get_pixel_format(cp_vdu_image_info_t *vdu_image);

	/*******************************************************************************
	* 版权所有: fz & novigo
	*
	* 函数名称: cp_vdu_image_info_set_vdu_rect
	*
	* 函数全名: cp_vdu_image_info_set_vdu_rect
	*
	* 函数访问: public 
	*
	* 函数说明: 设置需要获取的vdu图像位置
	*
	* 参    数: cp_vdu_image_info_t * vdu_image      [out]表示图像描述信息
	* 参    数: cp_vdu_rect_t rect					[in]设置指定区域的数值
	*
	* 返 回 值: cp_extern int
	*           0  : 成功
	*         非0  : 失败
	*
	* 备    注:其他说明内容
	*
	* 作    者：fz
	* 电子邮箱： fangzhenmu@novigo.com.cn
	* 创建日期：2018-2-25 11:33:31
	********************************************************************************/
	cp_extern int cp_vdu_image_info_set_vdu_rect(cp_vdu_image_info_t *vdu_image, cp_vdu_rect_t vdu_rect);

	/*******************************************************************************
	* 版权所有: fz & novigo
	*
	* 函数名称: cp_vdu_image_info_set_vdu_rect_parameters
	*
	* 函数全名: cp_vdu_image_info_set_vdu_rect_parameters
	*
	* 函数访问: public 
	*
	* 函数说明: 设置需要获取的vdu图像位置的详细
	*
	* 参    数: cp_vdu_image_info_t * vdu_image      [out]表示图像描述信息
	* 参    数: int x								[in]设置区域位置信息 x 值
	* 参    数: int y								[in]设置区域位置信息 y 值
	* 参    数: int width							[in]设置区域的宽度
	* 参    数: int height							[in]设置区域的高度
	*
	* 返 回 值: cp_extern int
	*           0  : 成功
	*         非0  : 失败
	*
	* 备    注:其他说明内容
	*
	* 作    者：fz
	* 电子邮箱： fangzhenmu@novigo.com.cn
	* 创建日期：2018-2-25 11:34:06
	********************************************************************************/
	cp_extern int cp_vdu_image_info_set_vdu_rect_parameters(cp_vdu_image_info_t *vdu_image, int x, int y, int width, int height);

	/*******************************************************************************
	* 版权所有: fz & novigo
	*
	* 函数名称: cp_vdu_image_info_get_vdu_rect
	*
	* 函数全名: cp_vdu_image_info_get_vdu_rect
	*
	* 函数访问: public 
	*
	* 函数说明: 获取需要获取的vdu图像位置
	*
	* 参    数: cp_vdu_image_info_t * vdu_image      [out]表示图像描述信息
	*
	* 返 回 值: cp_extern cp_vdu_rect_t
	*
	* 备    注:其他说明内容
	*
	* 作    者：fz
	* 电子邮箱： fangzhenmu@novigo.com.cn
	* 创建日期：2018-2-25 11:34:29
	********************************************************************************/
	cp_extern cp_vdu_rect_t cp_vdu_image_info_get_vdu_rect(cp_vdu_image_info_t *vdu_image);

	/*******************************************************************************
	* 版权所有: fz & novigo
	*
	* 函数名称: cp_vdu_image_info_set_image_size
	*
	* 函数全名: cp_vdu_image_info_set_image_size
	*
	* 函数访问: public 
	*
	* 函数说明: 设置最终生产的图像尺寸信息
	*
	* 参    数: cp_vdu_image_info_t * vdu_image      [out]表示图像描述信息
	* 参    数: int width							[in]指定返回位图数据的宽度
	* 参    数: int height							[in]指定返回位图数据的高度
	*
	* 返 回 值: cp_extern int
	*           0  : 成功
	*         非0  : 失败
	*
	* 备    注:其他说明内容
	*
	* 作    者：fz
	* 电子邮箱： fangzhenmu@novigo.com.cn
	* 创建日期：2018-2-25 11:37:05
	********************************************************************************/
	cp_extern int cp_vdu_image_info_set_image_size(cp_vdu_image_info_t *vdu_image, int width, int height);

	/*******************************************************************************
	* 版权所有: fz & novigo
	*
	* 函数名称: cp_vdu_image_info_get_image_rect
	*
	* 函数全名: cp_vdu_image_info_get_image_rect
	*
	* 函数访问: public 
	*
	* 函数说明: 获取最终生产的图像尺寸信息
	*
	* 参    数: cp_vdu_image_info_t * vdu_image      [out]表示图像描述信息
	*
	* 返 回 值: cp_extern cp_vdu_rect_t
	*
	* 备    注:其他说明内容
	*
	* 作    者：fz
	* 电子邮箱： fangzhenmu@novigo.com.cn
	* 创建日期：2018-2-25 11:37:12
	********************************************************************************/
	cp_extern cp_vdu_rect_t cp_vdu_image_info_get_image_rect(cp_vdu_image_info_t *vdu_image);



#ifdef __cplusplus
}
#endif


#endif //_CP_VDU_API_H_


