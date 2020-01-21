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



/*����qt_svg_channel ��Ϣ*/
cp_qt_svg_channel_t* create_qt_svg_channel(cp_qt_svg_process_t *process, cp_qt_svg_channel_info_t *info)
{
	cp_qt_svg_channel_t				*tmp_ret = CP_NULL;



	//����ϵͳ��Դ
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

	//����info��Ϣ
	if (info) {
		tmp_ret->info = *info;
		tmp_ret->channel.index = info->index;
	}	

	//��ʼ�����ֲ���
	if (qt_svg_channel_create_source(tmp_ret)) {
		cp_free(tmp_ret);
		cp_qt_svg_process_log(error, process, "create source error.");
		return CP_NULL;
	}

	return tmp_ret;
}

/*����qt_svg_channel ��Ϣ*/
cp_int32_t destroy_qt_svg_channel(cp_qt_svg_channel_t *channel)
{
	if (!channel) {
		return -1;
	}

	//������Դ
	qt_svg_channel_destroy_source(channel);
	
	cp_free(channel);

	return 0;
}




/*��ʼ��qt_svg_channel ��Ϣ*/
cp_int32_t init_qt_svg_channel(cp_qt_svg_channel_t *channel, cp_qt_svg_channel_info_t *channel_info)
{
	return 0;
}




/*����qt_svg_channel ��Ϣ*/
cp_int32_t start_qt_svg_channel(cp_qt_svg_channel_t *channel, cp_qt_svg_channel_info_t *channel_info)
{

	return 0;
}

/*******************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: qt_svg_channel_create_source
*
* ����ȫ��: qt_svg_channel_create_source
*
* ��������: public 
*
* ����˵��: ����svg������Դ
*
* ��    ��: cp_qt_svg_channel_t * channel						[in/out]����˵��
*
* �� �� ֵ: cp_int32_t
*           0  : �ɹ�
*         ��0  : ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2018-1-29 17:56:36
********************************************************************************/
cp_int32_t qt_svg_channel_create_source(cp_qt_svg_channel_t *channel)
{
	if (!channel) {
		return -1;
	}

	//��������Դ
	qt_svg_channel_destroy_source(channel);

	//�����ͳ�ʼ��svg item
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

	//�����ͳ�ʼ��render
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
* ��Ȩ����: fz & novigo
*
* ��������: qt_svg_channel_destroy_source
*
* ����ȫ��: qt_svg_channel_destroy_source
*
* ��������: public 
*
* ����˵��: ����svg������Դ
*
* ��    ��: cp_qt_svg_channel_t * channel						[in/out]����˵��
*
* �� �� ֵ: cp_int32_t
*           0  : �ɹ�
*         ��0  : ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2018-1-29 17:56:47
********************************************************************************/
cp_int32_t qt_svg_channel_destroy_source(cp_qt_svg_channel_t *channel)
{
	if (!channel) {
		return -1;
	}

	//����render
	if (channel->render) {

		cp_qt_svg_channel_log(notice, channel,
			"destroy QSvgRenderer[0x%x] success.",
			channel->render);

		delete channel->render;
		channel->render = CP_NULL;
	}

	//����svg item
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
* ��Ȩ����: fz & novigo
*
* ��������: qt_svg_channel_check_ready
*
* ����ȫ��: qt_svg_channel_check_ready
*
* ��������: public
*
* ����˵��: У���Ƿ��Ѿ�׼����
*
* ��    ��: cp_qt_svg_channel_t * channel						[in/out]����˵��
*
* �� �� ֵ: cp_int32_t
*           0  : ��ʾ����
*         ��0  : ��ʾ������
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2018-1-29 16:12:20
********************************************************************************/
cp_int32_t qt_svg_channel_check_ready(cp_qt_svg_channel_t *channel)
{
	if (!channel) {
		cp_qt_svg_channel_log(error, channel, "parametes list error.");
		return cp_vdu_status_null_pointer;
	}

	//�ж�channel�Ƿ��Ѿ���ʼ��
#if 0
	if (!channel->render || !channel->item ||
		!channel->render->isValid()) {
		cp_qt_svg_channel_log(error, channel, "channel render module not ready.");
		return cp_vdu_status_module_not_ready;
	}
#endif
	//�ж�channel�Ƿ��Ѿ���ʼ��
	if (!channel->render || !channel->item) {
		cp_qt_svg_channel_log(error, channel, "channel render module not ready.");
		return cp_vdu_status_module_not_ready;
	}

	return 0;
}

/*******************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: qt_svg_channel_clear_roi
*
* ����ȫ��: qt_svg_channel_clear_roi
*
* ��������: public 
*
* ����˵��: ���svgͼƬ�ĸ���Ȥ��������
*
* ��    ��: cp_qt_svg_channel_t * channel						[in/out]����˵��
*
* �� �� ֵ: cp_int32_t
*           0  : �ɹ�
*         ��0  : ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2018-1-29 16:58:47
********************************************************************************/
cp_int32_t qt_svg_channel_clear_roi(cp_qt_svg_channel_t *channel)
{
	//�ж�channel�Ƿ��Ѿ���ʼ��
	if (qt_svg_channel_check_ready(channel)) {
		cp_qt_svg_channel_log(error, channel, "channel render module not ready.");
		return cp_vdu_status_module_not_ready;
	}

	//����rect����
	QSize   tmp_size = channel->render->defaultSize();	
	return qt_svg_channel_set_roi(channel, 
		create_a_rect(0, 0, tmp_size.width(), tmp_size.height()));
}

/*******************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: qt_svg_channel_set_roi
*
* ����ȫ��: qt_svg_channel_set_roi
*
* ��������: public 
*
* ����˵��: ����svgͼƬ�ĸ���Ȥ����
*
* ��    ��: cp_qt_svg_channel_t * channel						[in/out]����˵��
* ��    ��: cp_rect_t rect						[in/out]����˵��
*
* �� �� ֵ: cp_int32_t
*           0  : �ɹ�
*         ��0  : ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2018-1-29 16:37:50
********************************************************************************/
cp_int32_t qt_svg_channel_set_roi(cp_qt_svg_channel_t *channel, cp_rect_t rect)
{
	//�ж�channel�Ƿ��Ѿ���ʼ��
	if (qt_svg_channel_check_ready(channel)) {
		cp_qt_svg_channel_log(error, channel, "channel render module not ready.");
		return cp_vdu_status_module_not_ready;
	}

	//����rect�Ƿ�Ϸ�
	if (check_rect_valid(&rect)) {
		cp_qt_svg_channel_log(error, channel, "rect invalid.");
		return cp_vdu_status_invalid_parametes;
	}

	//����rect����
	QRectF   tmp_rect(rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top);
	channel->render->setViewBox(tmp_rect);

	return 0;
}

/*******************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: qt_svg_channel_get_roi
*
* ����ȫ��: qt_svg_channel_get_roi
*
* ��������: public 
*
* ����˵��: ��ȡsvgͼƬ�ĸ���Ȥ��������
*
* ��    ��: cp_qt_svg_channel_t * channel						[in/out]����˵��
* ��    ��: cp_rect_t * dest_rect						[in/out]����˵��
*
* �� �� ֵ: cp_int32_t
*           0  : �ɹ�
*         ��0  : ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2018-1-29 16:48:05
********************************************************************************/
cp_int32_t qt_svg_channel_get_roi(cp_qt_svg_channel_t *channel, cp_rect_t *dest_rect)
{
	//�ж�channel�Ƿ��Ѿ���ʼ��
	if (qt_svg_channel_check_ready(channel)) {
		cp_qt_svg_channel_log(error, channel, "channel render module not ready.");
		return cp_vdu_status_module_not_ready;
	}

	//��ȡ��ʾ����
	QRectF   tmp_rect = channel->render->viewBoxF();

	//��������
	dest_rect->left = tmp_rect.left();
	dest_rect->top = tmp_rect.top();
	dest_rect->right = tmp_rect.right();
	dest_rect->bottom = tmp_rect.bottom();

	return 0;
}

/*******************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: qt_svg_channel_vector_stream
*
* ����ȫ��: qt_svg_channel_vector_stream
*
* ��������: public
*
* ����˵��: ����svgͼƬ������
*
* ��    ��: cp_qt_svg_channel_t * channel						[in/out]����˵��
* ��    ��: cp_uchar_t * buf						[in/out]����˵��
* ��    ��: cp_uint32_t len						[in/out]����˵��
*
* �� �� ֵ: cp_int32_t
*           0  : �ɹ�
*         ��0  : ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2018-1-26 16:32:05
********************************************************************************/
cp_int32_t qt_svg_channel_vector_stream(cp_qt_svg_channel_t *channel, cp_uchar_t *buf, cp_uint32_t len)
{
	if (!channel || !buf || !len) {
		cp_qt_svg_channel_log(error, channel, "parametes list error.");
		return cp_vdu_status_null_pointer;
	}

	//�ж�channel�Ƿ��Ѿ���ʼ��
	if (qt_svg_channel_check_ready(channel)) {
		cp_qt_svg_channel_log(error, channel, "channel render module not ready.");
		return cp_vdu_status_module_not_ready;
	}

	//����svg�ļ�������
	if (!channel->render->load(QByteArray((const char*)buf, (int)len))) {
		cp_qt_svg_channel_log(error, channel, "load svg stream error.");
		return cp_vdu_status_invalid_parametes;
	}

	//����SvgItem������Ϣ
	channel->item->setSharedRenderer(channel->render);
	channel->item->setFlags(QGraphicsItem::ItemClipsToShape);
	//channel->item->setCacheMode(QGraphicsItem::NoCache);
	channel->item->setCacheMode(QGraphicsItem::ItemCoordinateCache);
	channel->item->setZValue(channel->channel.index);

	return 0;
}

//���ñ����ļ���Ϣ
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
* ��Ȩ����: fz & novigo
*
* ��������: qt_svg_channel_get_roi_pixel
*
* ����ȫ��: qt_svg_channel_get_roi_pixel
*
* ��������: public
*
* ����˵��: ��ȡsvgָ�������ͼƬ����
*
* ��    ��: cp_qt_svg_channel_t * channel				[in]��Ҫ�����channel����
* ��    ��: cp_uchar_t * dest_buf						[out]��ʾĿ�껺���ַ
* ��    ��: cp_uint32_t buf_len							[in]��ʾĿ�껺�泤��
* ��    ��: cp_codec_pixel_format_e cpf					[in]��ʾͼƬ��ʽ
* ��    ��: cp_rect_t *image_rect						[in]��ʾͼƬ��ʽ
*
* �� �� ֵ: cp_int32_t
*           >0  : ���ɵ����ݴ�С
*         <=0  : �������
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2018-1-29 16:16:48
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

	//�ж�channel�Ƿ��Ѿ���ʼ��
	if (qt_svg_channel_check_ready(channel)) {
		cp_qt_svg_channel_log(error, channel, "channel render module not ready.");
		return cp_vdu_status_module_not_ready;
	}

	//�ж��Ƿ�Ϸ�
	if (!channel->render->isValid()) {
		cp_qt_svg_channel_log(error, channel, "render invalid.");
		return cp_vdu_status_system_error;
	}

	//ת��ͼƬ��ʽ
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

	//����rect�Ƿ�Ϸ�
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

	//����painter
	QPainter tmp_painter(&tmp_image);

	//tmp_painter.begin(&tmp_image);
	//channel->render()->render(&painter, QRectF(QPointF(), QSizeF(imageSize)));
	//����ͼƬ,������Ⱦ��ʱ�����ʵ���Զ����Ŵ���
	channel->render->render(&tmp_painter);
	//tmp_painter.end();

	//��ͼƬ���浽�ļ���
	qt_svg_channel_save_file(channel, &tmp_image);

#if CP_QT_SVG_DEBUG_TEST_SAVE_TO_FILE

	//QByteArray tmp_byte_array;
	//QBuffer tmp_buffer(&tmp_byte_array);
	//image.save(&buffer, "PNG"); // writes the image in PNG format inside the buffer
	tmp_image.save("files\\out_channel_svg_file_by_roi.png", "PNG"); // writes the image in PNG format inside the buffer
	//tmp_image.save(&tmp_buffer); // writes the image in PNG format inside the buffer

	//�ж��ڴ��Ƿ���
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
* ��Ȩ����: fz & novigo
*
* ��������: qt_svg_channel_get_rect_pixel
*
* ����ȫ��: qt_svg_channel_get_rect_pixel
*
* ��������: public
*
* ����˵��: ��ȡsvgָ�������ͼƬ����
*
* ��    ��: cp_qt_svg_channel_t * channel				[in]��Ҫ�����channel����
* ��    ��: cp_uchar_t * dest_buf						[out]��ʾĿ�껺���ַ
* ��    ��: cp_uint32_t buf_len							[in]��ʾĿ�껺�泤��
* ��    ��: cp_codec_pixel_format_e cpf					[in]��ʾͼƬ��ʽ
* ��    ��: cp_rect_t rect								[in]��ʾ��ȡ����
* ��    ��: cp_rect_t *image_rect						[in]��ʾ��ȡ����
*
* �� �� ֵ: cp_int32_t
*           >0  : ���ɵ����ݴ�С
*         <=0  : �������
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2018-1-29 16:16:48
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


	//����rect�Ƿ�Ϸ�
	if (check_rect_valid(&rect)) {
		cp_qt_svg_channel_log(error, channel, "rect invalid.");
		return cp_vdu_status_invalid_parametes;
	}

	//ת��ͼƬ��ʽ
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

	//����painter
	QPainter tmp_painter(&tmp_image);

	//��ȡԭ���ĸ���Ȥ������Ϊ����
	tmp_ret_int = qt_svg_channel_get_roi(channel, &tmp_prev_roi_rect);
	if (tmp_ret_int) {
		cp_qt_svg_channel_log(error, channel, "get roi for backup failed.");
		return cp_vdu_status_system_error;
	}

	//��ʼ������Ҫ�ĸ���Ȥ����
	tmp_ret_int = qt_svg_channel_set_roi(channel, rect);
	if (tmp_ret_int) {
		cp_qt_svg_channel_log(error, channel, "set begin roi failed.");
		return cp_vdu_status_system_error;
	}

	//tmp_painter.begin(&tmp_image);
	//channel->render()->render(&painter, QRectF(QPointF(), QSizeF(imageSize)));
	//����ͼƬ,������Ⱦ��ʱ�����ʵ���Զ����Ŵ���
	//channel->render->render(&tmp_painter, 
	//	QRectF(rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top));
	channel->render->render(&tmp_painter);
	//tmp_painter.end();

	//��ԭ����ԭ���ĸ���Ȥ����
	tmp_ret_int = qt_svg_channel_set_roi(channel, tmp_prev_roi_rect);
	if (tmp_ret_int) {
		cp_qt_svg_channel_log(error, channel, "set end roi failed.");
		return cp_vdu_status_system_error;
	}

	//��ͼƬ���浽�ļ���
	qt_svg_channel_save_file(channel, &tmp_image);

#if CP_QT_SVG_DEBUG_TEST_SAVE_TO_FILE

	//QByteArray tmp_byte_array;
	//QBuffer tmp_buffer(&tmp_byte_array);
	//image.save(&buffer, "PNG"); // writes the image in PNG format inside the buffer
	tmp_image.save("files\\out_channel_svg_file_by_rect.png", "PNG"); // writes the image in PNG format inside the buffer
	//tmp_image.save(&tmp_buffer); // writes the image in PNG format inside the buffer

	//�ж��ڴ��Ƿ���
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
* ��Ȩ����: fz & novigo
*
* ��������: qt_svg_channel_insert_scene
*
* ����ȫ��: qt_svg_channel_insert_scene
*
* ��������: public 
*
* ����˵��: ��ʾ���볡��
*
* ��    ��: cp_qt_svg_process_t * process						[in/out]����˵��
* ��    ��: cp_qt_svg_channel_t * channel						[in/out]����˵��
* ��    ��: cp_rect_t rect						[in/out]����˵��
*
* �� �� ֵ: cp_int32_t
*           0  : �ɹ�
*         ��0  : ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2018-1-31 18:27:50
********************************************************************************/
cp_int32_t qt_svg_channel_insert_scene(cp_qt_svg_process_t *process, cp_qt_svg_channel_t *channel, cp_rect_t rect)
{
	//�ж�channel�Ƿ��Ѿ���ʼ��
	if (qt_svg_channel_check_ready(channel)) {
		cp_qt_svg_channel_log(error, channel, "channel render module not ready.");
		return cp_vdu_status_module_not_ready;
	}

	//����rect�Ƿ�Ϸ�
	if (check_rect_valid(&rect)) {
		cp_qt_svg_channel_log(error, channel, "rect invalid.");
		return cp_vdu_status_invalid_parametes;
	}

	//����ͨ����������
	channel->scene.is_render_scene = cp_true;
	channel->scene.rect = rect;
	channel->item->setPos(rect.left, rect.top);
	channel->item->setZValue(channel->channel.index);

	return 0;
}

/*******************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: qt_svg_channel_remove_scene
*
* ����ȫ��: qt_svg_channel_remove_scene
*
* ��������: public 
*
* ����˵��: ����˵��
*
* ��    ��: cp_qt_svg_process_t * process						[in/out]����˵��
* ��    ��: cp_qt_svg_channel_t * channel						[in/out]����˵��
*
* �� �� ֵ: cp_int32_t
*           0  : �ɹ�
*         ��0  : ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2018-1-31 18:28:06
********************************************************************************/
cp_int32_t qt_svg_channel_remove_scene(cp_qt_svg_process_t *process, cp_qt_svg_channel_t *channel)
{
	//�ж�channel�Ƿ��Ѿ���ʼ��
	if (qt_svg_channel_check_ready(channel)) {
		cp_qt_svg_channel_log(error, channel, "channel render module not ready.");
		return cp_vdu_status_module_not_ready;
	}

	//���³����е���Ϣ
	channel->scene.is_render_scene = cp_false;
	channel->item->setPos(0, 0);
	channel->item->setZValue(0);

	return 0;
}

/*��ʾ�޸�ͨ����index����ͼ������*/
cp_int32_t qt_svg_channel_update_index(cp_qt_svg_channel_t *channel, cp_int32_t index)
{
	//�ж�channel�Ƿ��Ѿ���ʼ��
	if (qt_svg_channel_check_ready(channel)) {
		cp_qt_svg_channel_log(error, channel, "channel render module not ready.");
		return cp_vdu_status_module_not_ready;
	}

	//�޸�ͼ���ϵ
	channel->item->setZValue(index);

	return 0;
}


/*ֹͣqt_svg_channel ��Ϣ*/
cp_int32_t stop_qt_svg_channel(cp_qt_svg_channel_t *channel)
{
	return 0;
}







