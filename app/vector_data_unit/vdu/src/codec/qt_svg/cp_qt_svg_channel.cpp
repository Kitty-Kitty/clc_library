/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/
#include <iostream>
#include "cp_qt_svg_channel.h"
#include "cp_qt_svg_unit.h"



using namespace std;



/*创建qt_svg_channel 信息*/
cp_qt_svg_channel_t* create_qt_svg_channel(cp_qt_svg_process_t *process, cp_qt_svg_channel_info_t *info)
{
	cp_qt_svg_channel_t				*tmp_ret = CP_NULL;



	//分配系统资源
	tmp_ret = (cp_qt_svg_channel_t*)cp_malloc(cp_sizeof(cp_qt_svg_channel_t));
	if (!tmp_ret) {
		cp_qt_svg_process_log(error, process, "malloc memory error.");
		return CP_NULL;
	}
	else {
		cp_memset(tmp_ret, 0, cp_sizeof(cp_qt_svg_channel_t));
	}

	tmp_ret->process = process;
	tmp_ret->channel.data = tmp_ret;

	//更新info信息
	if (info) {
		tmp_ret->info = *info;
		tmp_ret->channel.index = info->index;
	}	

	//初始化各种参数
	if (qt_svg_channel_create_source(tmp_ret)) {
		cp_free(tmp_ret);
		cp_qt_svg_process_log(error, process, "create source error.");
		return CP_NULL;
	}

	return tmp_ret;
}

/*销毁qt_svg_channel 信息*/
cp_int32_t destroy_qt_svg_channel(cp_qt_svg_channel_t *channel)
{
	if (!channel) {
		return -1;
	}

	//销毁资源
	qt_svg_channel_destroy_source(channel);
	
	cp_free(channel);

	return 0;
}




/*初始化qt_svg_channel 信息*/
cp_int32_t init_qt_svg_channel(cp_qt_svg_channel_t *channel, cp_qt_svg_channel_info_t *channel_info)
{
	return 0;
}




/*启动qt_svg_channel 信息*/
cp_int32_t start_qt_svg_channel(cp_qt_svg_channel_t *channel, cp_qt_svg_channel_info_t *channel_info)
{

	return 0;
}

/*******************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: qt_svg_channel_create_source
*
* 函数全名: qt_svg_channel_create_source
*
* 函数访问: public 
*
* 函数说明: 创建svg处理资源
*
* 参    数: cp_qt_svg_channel_t * channel						[in/out]参数说明
*
* 返 回 值: cp_int32_t
*           0  : 成功
*         非0  : 失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2018-1-29 17:56:36
********************************************************************************/
cp_int32_t qt_svg_channel_create_source(cp_qt_svg_channel_t *channel)
{
	if (!channel) {
		return -1;
	}

	//先销毁资源
	qt_svg_channel_destroy_source(channel);

	//创建和初始化svg item
	try
	{
		channel->item = new QGraphicsSvgItem();
		if (channel->item)
		{
			cp_qt_svg_channel_log(notice, channel,
				"create QGraphicsSvgItem[0x%x] success.",
				channel->item);
		}
	}
	catch (std::exception& e)
	{
		cp_qt_svg_channel_log(error, channel,
			"create QGraphicsSvgItem() error. exception[%s]",
			e.what());
		return -2;
	}

	//创建和初始化render
	try
	{
		channel->render = new QSvgRenderer();
		if (channel->render)
		{
			cp_qt_svg_channel_log(notice, channel,
				"create QSvgRenderer[0x%x] success.",
				channel->render);
		}
	}
	catch (std::exception& e)
	{
		cp_qt_svg_channel_log(error, channel,
			"create QSvgRenderer() error. exception[%s]",
			e.what());
		return -2;
	}

	return 0;
}

/*******************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: qt_svg_channel_destroy_source
*
* 函数全名: qt_svg_channel_destroy_source
*
* 函数访问: public 
*
* 函数说明: 销毁svg处理资源
*
* 参    数: cp_qt_svg_channel_t * channel						[in/out]参数说明
*
* 返 回 值: cp_int32_t
*           0  : 成功
*         非0  : 失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2018-1-29 17:56:47
********************************************************************************/
cp_int32_t qt_svg_channel_destroy_source(cp_qt_svg_channel_t *channel)
{
	if (!channel) {
		return -1;
	}

	//销毁render
	if (channel->render) {

		cp_qt_svg_channel_log(notice, channel,
			"destroy QSvgRenderer[0x%x] success.",
			channel->render);

		delete channel->render;
		channel->render = CP_NULL;
	}

	//销毁svg item
	if (channel->item) {

		cp_qt_svg_channel_log(notice, channel,
			"destroy QGraphicsSvgItem[0x%x] success.",
			channel->item);

		delete channel->item;
		channel->item = CP_NULL;
	}

	return 0;
}

/*******************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: qt_svg_channel_check_ready
*
* 函数全名: qt_svg_channel_check_ready
*
* 函数访问: public
*
* 函数说明: 校验是否已经准备好
*
* 参    数: cp_qt_svg_channel_t * channel						[in/out]参数说明
*
* 返 回 值: cp_int32_t
*           0  : 表示存在
*         非0  : 表示不存在
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2018-1-29 16:12:20
********************************************************************************/
cp_int32_t qt_svg_channel_check_ready(cp_qt_svg_channel_t *channel)
{
	if (!channel) {
		cp_qt_svg_channel_log(error, channel, "parametes list error.");
		return cp_vdu_status_null_pointer;
	}

	//判断channel是否已经初始化
#if 0
	if (!channel->render || !channel->item ||
		!channel->render->isValid()) {
		cp_qt_svg_channel_log(error, channel, "channel render module not ready.");
		return cp_vdu_status_module_not_ready;
	}
#endif
	//判断channel是否已经初始化
	if (!channel->render || !channel->item) {
		cp_qt_svg_channel_log(error, channel, "channel render module not ready.");
		return cp_vdu_status_module_not_ready;
	}

	return 0;
}

/*******************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: qt_svg_channel_clear_roi
*
* 函数全名: qt_svg_channel_clear_roi
*
* 函数访问: public 
*
* 函数说明: 清除svg图片的感兴趣区域数据
*
* 参    数: cp_qt_svg_channel_t * channel						[in/out]参数说明
*
* 返 回 值: cp_int32_t
*           0  : 成功
*         非0  : 失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2018-1-29 16:58:47
********************************************************************************/
cp_int32_t qt_svg_channel_clear_roi(cp_qt_svg_channel_t *channel)
{
	//判断channel是否已经初始化
	if (qt_svg_channel_check_ready(channel)) {
		cp_qt_svg_channel_log(error, channel, "channel render module not ready.");
		return cp_vdu_status_module_not_ready;
	}

	//设置rect区域
	QSize   tmp_size = channel->render->defaultSize();	
	return qt_svg_channel_set_roi(channel, 
		create_a_rect(0, 0, tmp_size.width(), tmp_size.height()));
}

/*******************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: qt_svg_channel_set_roi
*
* 函数全名: qt_svg_channel_set_roi
*
* 函数访问: public 
*
* 函数说明: 设置svg图片的感兴趣区域
*
* 参    数: cp_qt_svg_channel_t * channel						[in/out]参数说明
* 参    数: cp_rect_t rect						[in/out]参数说明
*
* 返 回 值: cp_int32_t
*           0  : 成功
*         非0  : 失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2018-1-29 16:37:50
********************************************************************************/
cp_int32_t qt_svg_channel_set_roi(cp_qt_svg_channel_t *channel, cp_rect_t rect)
{
	//判断channel是否已经初始化
	if (qt_svg_channel_check_ready(channel)) {
		cp_qt_svg_channel_log(error, channel, "channel render module not ready.");
		return cp_vdu_status_module_not_ready;
	}

	//核验rect是否合法
	if (check_rect_valid(&rect)) {
		cp_qt_svg_channel_log(error, channel, "rect invalid.");
		return cp_vdu_status_invalid_parametes;
	}

	//设置rect区域
	QRectF   tmp_rect(rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top);
	channel->render->setViewBox(tmp_rect);

	return 0;
}

/*******************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: qt_svg_channel_get_roi
*
* 函数全名: qt_svg_channel_get_roi
*
* 函数访问: public 
*
* 函数说明: 获取svg图片的感兴趣区域数据
*
* 参    数: cp_qt_svg_channel_t * channel						[in/out]参数说明
* 参    数: cp_rect_t * dest_rect						[in/out]参数说明
*
* 返 回 值: cp_int32_t
*           0  : 成功
*         非0  : 失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2018-1-29 16:48:05
********************************************************************************/
cp_int32_t qt_svg_channel_get_roi(cp_qt_svg_channel_t *channel, cp_rect_t *dest_rect)
{
	//判断channel是否已经初始化
	if (qt_svg_channel_check_ready(channel)) {
		cp_qt_svg_channel_log(error, channel, "channel render module not ready.");
		return cp_vdu_status_module_not_ready;
	}

	//获取显示区域
	QRectF   tmp_rect = channel->render->viewBoxF();

	//更新数据
	dest_rect->left = tmp_rect.left();
	dest_rect->top = tmp_rect.top();
	dest_rect->right = tmp_rect.right();
	dest_rect->bottom = tmp_rect.bottom();

	return 0;
}

/*******************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: qt_svg_channel_vector_stream
*
* 函数全名: qt_svg_channel_vector_stream
*
* 函数访问: public
*
* 函数说明: 处理svg图片数据流
*
* 参    数: cp_qt_svg_channel_t * channel						[in/out]参数说明
* 参    数: cp_uchar_t * buf						[in/out]参数说明
* 参    数: cp_uint32_t len						[in/out]参数说明
*
* 返 回 值: cp_int32_t
*           0  : 成功
*         非0  : 失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2018-1-26 16:32:05
********************************************************************************/
cp_int32_t qt_svg_channel_vector_stream(cp_qt_svg_channel_t *channel, cp_uchar_t *buf, cp_uint32_t len)
{
	if (!channel || !buf || !len) {
		cp_qt_svg_channel_log(error, channel, "parametes list error.");
		return cp_vdu_status_null_pointer;
	}

	//判断channel是否已经初始化
	if (qt_svg_channel_check_ready(channel)) {
		cp_qt_svg_channel_log(error, channel, "channel render module not ready.");
		return cp_vdu_status_module_not_ready;
	}

	//加载svg文件流数据
	if (!channel->render->load(QByteArray((const char*)buf, (int)len))) {
		cp_qt_svg_channel_log(error, channel, "load svg stream error.");
		return cp_vdu_status_invalid_parametes;
	}

	//设置SvgItem内容信息
	channel->item->setSharedRenderer(channel->render);
	channel->item->setFlags(QGraphicsItem::ItemClipsToShape);
	//channel->item->setCacheMode(QGraphicsItem::NoCache);
	channel->item->setCacheMode(QGraphicsItem::ItemCoordinateCache);
	channel->item->setZValue(channel->channel.index);

	return 0;
}

//设置保存文件信息
cp_int32_t qt_svg_channel_save_file(cp_qt_svg_channel_t *channel, QImage *image)
{
	cp_char_t							tmp_file_name[CP_APP_DEFAULT_BUFFER_LENGTH] = { 0, };



	if (!channel->process->debug_info.is_save_file) {
		return 0;
	}

	cp_sprintf(tmp_file_name,
		"%s%c%s_%d_output_file.png",
		channel->process->debug_info.path,
		cp_dir_diagonal,
		CP_QT_SVG_DEBUG_TEST_SAVE_TO_FILE_CHANNEL_FLAG,
		channel->info.index);

	image->save(tmp_file_name, "PNG"); // writes the image in PNG format inside the buffer

	return 0;
}

/*******************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: qt_svg_channel_get_roi_pixel
*
* 函数全名: qt_svg_channel_get_roi_pixel
*
* 函数访问: public
*
* 函数说明: 获取svg指定区域的图片数据
*
* 参    数: cp_qt_svg_channel_t * channel				[in]需要处理的channel内容
* 参    数: cp_uchar_t * dest_buf						[out]表示目标缓存地址
* 参    数: cp_uint32_t buf_len							[in]表示目标缓存长度
* 参    数: cp_codec_pixel_format_e cpf					[in]表示图片格式
* 参    数: cp_rect_t *image_rect						[in]表示图片格式
*
* 返 回 值: cp_int32_t
*           >0  : 生成的数据大小
*         <=0  : 错误代码
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2018-1-29 16:16:48
********************************************************************************/
cp_int32_t qt_svg_channel_get_roi_pixel(cp_qt_svg_channel_t *channel,
	cp_uchar_t *dest_buf,
	cp_uint32_t buf_len,
	cp_codec_pixel_format_e cpf,
	cp_rect_t *image_rect)
{
	QImage::Format					tmp_fmt = QImage::Format_Invalid;
	cp_int32_t						tmp_ret_int = 0;
	cp_rect_t						tmp_rect = { 0, };



	if (!channel || !dest_buf || !buf_len) {
		cp_qt_svg_channel_log(error, channel, "parametes list error.");
		return cp_vdu_status_null_pointer;
	}

	//判断channel是否已经初始化
	if (qt_svg_channel_check_ready(channel)) {
		cp_qt_svg_channel_log(error, channel, "channel render module not ready.");
		return cp_vdu_status_module_not_ready;
	}

	//判断是否合法
	if (!channel->render->isValid()) {
		cp_qt_svg_channel_log(error, channel, "render invalid.");
		return cp_vdu_status_system_error;
	}

	//转换图片格式
	tmp_fmt = convert_cpf_to_qimage_format(cpf);
	if (QImage::Format_Invalid == tmp_fmt) {
		cp_qt_svg_channel_log(error, channel, "unsupport pixel format[%d].", cpf);
		return cp_vdu_status_unsupport_pixel_format;
	}

	//QImage image(rect.right - rect.left, rect.bottom - rect.top, QImage::Format_ARGB32);
	if (image_rect) {
		tmp_rect = *image_rect;
	}
	else {
		tmp_ret_int = qt_svg_channel_get_roi(channel, &tmp_rect);
		if (tmp_ret_int) {
			cp_qt_svg_channel_log(error, channel, "get roi failed.");
			return cp_vdu_status_system_error;
		}
	}

	//核验rect是否合法
	if (check_rect_valid(&tmp_rect)) {
		cp_qt_svg_channel_log(error, channel, "rect invalid.");
		return cp_vdu_status_invalid_parametes;
	}

	//QImage image(rect.right - rect.left, rect.bottom - rect.top, QImage::Format_ARGB32);
	//QImage tmp_image(tmp_rect.right - tmp_rect.left, tmp_rect.bottom - tmp_rect.top, tmp_fmt);
	QImage tmp_image(dest_buf, tmp_rect.right - tmp_rect.left, tmp_rect.bottom - tmp_rect.top, tmp_fmt);
	//QImage tmp_image(tmp_rect.right - tmp_rect.left, tmp_rect.bottom - tmp_rect.top, tmp_fmt);
	//QImage tmp_image(dest_buf, tmp_rect.right - tmp_rect.left, tmp_rect.bottom - tmp_rect.top, QImage::Format_RGB888);
	//image.fill(0xaaA08080);  // partly transparent red-ish background
	tmp_image.fill(Qt::transparent);

	//创建painter
	QPainter tmp_painter(&tmp_image);

	//tmp_painter.begin(&tmp_image);
	//channel->render()->render(&painter, QRectF(QPointF(), QSizeF(imageSize)));
	//缩放图片,这里渲染的时候可以实现自动缩放处理
	channel->render->render(&tmp_painter);
	//tmp_painter.end();

	//将图片保存到文件中
	qt_svg_channel_save_file(channel, &tmp_image);

#if CP_QT_SVG_DEBUG_TEST_SAVE_TO_FILE

	//QByteArray tmp_byte_array;
	//QBuffer tmp_buffer(&tmp_byte_array);
	//image.save(&buffer, "PNG"); // writes the image in PNG format inside the buffer
	tmp_image.save("files\\out_channel_svg_file_by_roi.png", "PNG"); // writes the image in PNG format inside the buffer
	//tmp_image.save(&tmp_buffer); // writes the image in PNG format inside the buffer

	//判断内存是否够用
// 	if (tmp_byte_array.count() > (cp_int32_t)buf_len) {
// 		cp_qt_svg_channel_log(error, channel, 
// 			"input buffer len[%d] less than used buffer len[%d].", 
// 			buf_len,
// 			tmp_byte_array.count());
// 		return cp_vdu_status_not_more_buffer;
// 	}
// 
// 	cp_memcpy(dest_buf, tmp_byte_array.data(), tmp_byte_array.count());
// 	tmp_ret_int = tmp_byte_array.count();

#endif

	//cp_uchar_t *tmp_ret_buf = tmp_image.bits();
	//tmp_ret_int = tmp_image.byteCount();
	return tmp_image.byteCount();

}

/*******************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: qt_svg_channel_get_rect_pixel
*
* 函数全名: qt_svg_channel_get_rect_pixel
*
* 函数访问: public
*
* 函数说明: 获取svg指定区域的图片数据
*
* 参    数: cp_qt_svg_channel_t * channel				[in]需要处理的channel内容
* 参    数: cp_uchar_t * dest_buf						[out]表示目标缓存地址
* 参    数: cp_uint32_t buf_len							[in]表示目标缓存长度
* 参    数: cp_codec_pixel_format_e cpf					[in]表示图片格式
* 参    数: cp_rect_t rect								[in]表示获取区域
* 参    数: cp_rect_t *image_rect						[in]表示获取区域
*
* 返 回 值: cp_int32_t
*           >0  : 生成的数据大小
*         <=0  : 错误代码
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2018-1-29 16:16:48
********************************************************************************/
cp_int32_t qt_svg_channel_get_rect_pixel(cp_qt_svg_channel_t *channel,
	cp_uchar_t *dest_buf,
	cp_uint32_t buf_len,
	cp_codec_pixel_format_e cpf,
	cp_rect_t rect,
	cp_rect_t *image_rect)
{
	QImage::Format					tmp_fmt = QImage::Format_Invalid;
	cp_int32_t						tmp_ret_int = 0;
	cp_rect_t						tmp_rect = { 0, };
	cp_rect_t						tmp_prev_roi_rect = { 0, };


	//核验rect是否合法
	if (check_rect_valid(&rect)) {
		cp_qt_svg_channel_log(error, channel, "rect invalid.");
		return cp_vdu_status_invalid_parametes;
	}

	//转换图片格式
	tmp_fmt = convert_cpf_to_qimage_format(cpf);
	if (QImage::Format_Invalid == tmp_fmt) {
		cp_qt_svg_channel_log(error, channel, 
			"unsupport pixel format[%d].", cpf);
		return cp_vdu_status_unsupport_pixel_format;
	}

	if (image_rect) {
		tmp_rect = *image_rect;
	}
	else {
		tmp_rect = rect;
	}

	//QImage image(rect.right - rect.left, rect.bottom - rect.top, QImage::Format_ARGB32);
	//QImage tmp_image(tmp_rect.right - tmp_rect.left, tmp_rect.bottom - tmp_rect.top, tmp_fmt);
	QImage tmp_image(dest_buf, tmp_rect.right - tmp_rect.left, tmp_rect.bottom - tmp_rect.top, tmp_fmt);
	//QImage tmp_image(tmp_rect.right - tmp_rect.left, tmp_rect.bottom - tmp_rect.top, tmp_fmt);
	//image.fill(0xaaA08080);  // partly transparent red-ish background
	tmp_image.fill(Qt::transparent);

	//创建painter
	QPainter tmp_painter(&tmp_image);

	//获取原来的感兴趣区域作为备份
	tmp_ret_int = qt_svg_channel_get_roi(channel, &tmp_prev_roi_rect);
	if (tmp_ret_int) {
		cp_qt_svg_channel_log(error, channel, "get roi for backup failed.");
		return cp_vdu_status_system_error;
	}

	//开始设置需要的感兴趣区域
	tmp_ret_int = qt_svg_channel_set_roi(channel, rect);
	if (tmp_ret_int) {
		cp_qt_svg_channel_log(error, channel, "set begin roi failed.");
		return cp_vdu_status_system_error;
	}

	//tmp_painter.begin(&tmp_image);
	//channel->render()->render(&painter, QRectF(QPointF(), QSizeF(imageSize)));
	//缩放图片,这里渲染的时候可以实现自动缩放处理
	//channel->render->render(&tmp_painter, 
	//	QRectF(rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top));
	channel->render->render(&tmp_painter);
	//tmp_painter.end();

	//还原设置原来的感兴趣区域
	tmp_ret_int = qt_svg_channel_set_roi(channel, tmp_prev_roi_rect);
	if (tmp_ret_int) {
		cp_qt_svg_channel_log(error, channel, "set end roi failed.");
		return cp_vdu_status_system_error;
	}

	//将图片保存到文件中
	qt_svg_channel_save_file(channel, &tmp_image);

#if CP_QT_SVG_DEBUG_TEST_SAVE_TO_FILE

	//QByteArray tmp_byte_array;
	//QBuffer tmp_buffer(&tmp_byte_array);
	//image.save(&buffer, "PNG"); // writes the image in PNG format inside the buffer
	tmp_image.save("files\\out_channel_svg_file_by_rect.png", "PNG"); // writes the image in PNG format inside the buffer
	//tmp_image.save(&tmp_buffer); // writes the image in PNG format inside the buffer

	//判断内存是否够用
	// 	if (tmp_byte_array.count() > (cp_int32_t)buf_len) {
	// 		cp_qt_svg_channel_log(error, channel, 
	// 			"input buffer len[%d] less than used buffer len[%d].", 
	// 			buf_len,
	// 			tmp_byte_array.count());
	// 		return cp_vdu_status_not_more_buffer;
	// 	}
	// 
	// 	cp_memcpy(dest_buf, tmp_byte_array.data(), tmp_byte_array.count());
	// 	tmp_ret_int = tmp_byte_array.count();

#endif

	//cp_uchar_t *tmp_ret_buf = tmp_image.bits();
	//tmp_ret_int = tmp_image.byteCount();
	return tmp_image.byteCount();
}

/*******************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: qt_svg_channel_insert_scene
*
* 函数全名: qt_svg_channel_insert_scene
*
* 函数访问: public 
*
* 函数说明: 表示插入场景
*
* 参    数: cp_qt_svg_process_t * process						[in/out]参数说明
* 参    数: cp_qt_svg_channel_t * channel						[in/out]参数说明
* 参    数: cp_rect_t rect						[in/out]参数说明
*
* 返 回 值: cp_int32_t
*           0  : 成功
*         非0  : 失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2018-1-31 18:27:50
********************************************************************************/
cp_int32_t qt_svg_channel_insert_scene(cp_qt_svg_process_t *process, cp_qt_svg_channel_t *channel, cp_rect_t rect)
{
	//判断channel是否已经初始化
	if (qt_svg_channel_check_ready(channel)) {
		cp_qt_svg_channel_log(error, channel, "channel render module not ready.");
		return cp_vdu_status_module_not_ready;
	}

	//核验rect是否合法
	if (check_rect_valid(&rect)) {
		cp_qt_svg_channel_log(error, channel, "rect invalid.");
		return cp_vdu_status_invalid_parametes;
	}

	//增加通道到场景中
	channel->scene.is_render_scene = cp_true;
	channel->scene.rect = rect;
	channel->item->setPos(rect.left, rect.top);
	channel->item->setZValue(channel->channel.index);

	return 0;
}

/*******************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: qt_svg_channel_remove_scene
*
* 函数全名: qt_svg_channel_remove_scene
*
* 函数访问: public 
*
* 函数说明: 函数说明
*
* 参    数: cp_qt_svg_process_t * process						[in/out]参数说明
* 参    数: cp_qt_svg_channel_t * channel						[in/out]参数说明
*
* 返 回 值: cp_int32_t
*           0  : 成功
*         非0  : 失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2018-1-31 18:28:06
********************************************************************************/
cp_int32_t qt_svg_channel_remove_scene(cp_qt_svg_process_t *process, cp_qt_svg_channel_t *channel)
{
	//判断channel是否已经初始化
	if (qt_svg_channel_check_ready(channel)) {
		cp_qt_svg_channel_log(error, channel, "channel render module not ready.");
		return cp_vdu_status_module_not_ready;
	}

	//更新场景中的信息
	channel->scene.is_render_scene = cp_false;
	channel->item->setPos(0, 0);
	channel->item->setZValue(0);

	return 0;
}

/*表示修改通道的index，即图层属性*/
cp_int32_t qt_svg_channel_update_index(cp_qt_svg_channel_t *channel, cp_int32_t index)
{
	//判断channel是否已经初始化
	if (qt_svg_channel_check_ready(channel)) {
		cp_qt_svg_channel_log(error, channel, "channel render module not ready.");
		return cp_vdu_status_module_not_ready;
	}

	//修改图层关系
	channel->item->setZValue(index);

	return 0;
}


/*停止qt_svg_channel 信息*/
cp_int32_t stop_qt_svg_channel(cp_qt_svg_channel_t *channel)
{
	return 0;
}







