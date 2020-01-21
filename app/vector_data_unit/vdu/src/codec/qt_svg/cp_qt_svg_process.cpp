/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/
#include <iostream>
#include "cp_qt_svg_process.h"
#include "cp_qt_svg_unit.h"



using namespace std;



/*创建qt_svg_process 信息*/
cp_qt_svg_process_t* create_qt_svg_process(
	cp_qt_svg_codec_t *codec,
	cp_qt_svg_process_info_t *info)
{
	cp_qt_svg_process_t				*tmp_ret = CP_NULL;



	//分配系统资源
	tmp_ret = (cp_qt_svg_process_t*)cp_malloc(cp_sizeof(cp_qt_svg_process_t));
	if (!tmp_ret) {
		cp_module_log(error, codec, "malloc memory error.");
		return CP_NULL;
	}
	else {
		cp_memset(tmp_ret, 0, cp_sizeof(cp_qt_svg_process_t));
	}

	//初始化各种参数
	tmp_ret->codec = codec;
	tmp_ret->debug_info.is_save_file = cp_false;

	//更新info信息
	if (info) {
		tmp_ret->info = *info;
	}

	return tmp_ret;
}

/*销毁qt_svg_process 信息*/
cp_int32_t destroy_svg_process(cp_qt_svg_process_t *process)
{
	if (!process) {
		return 0;
	}

	//销毁资源
	stop_qt_svg_process(process);

	cp_free(process);

	return 0;
}


/*初始化qt_svg_process 信息*/
cp_int32_t init_qt_svg_process(
	cp_qt_svg_process_t *process,
	cp_qt_svg_process_info_t *info)
{
	cp_int32_t							ret_int = 0;
	cp_int32_t							tmp_max_size = CP_CHANNEL_MANAGER_DEFAULT_NUMBER;



	//更新信息
	if (info) {
		process->info = *info;
	}

	//初始化process的资源
	ret_int = qt_svg_process_create_source(process, info);
	if (ret_int) {
		return -1;
	}

	//初始化播放管理器信息
	ret_int = init_channel_manager(process->codec->manager->app,
		&(process->channel_manager), tmp_max_size);
	if (ret_int) {
		cp_qt_svg_process_log(error, process, "init_qt_svg_process() error.");
		return -1;
	}
	else {
		cp_qt_svg_process_log(notice, process,
			"init_qt_svg_process() succeed. channel size[%d].", tmp_max_size);
	}

	return 0;
}





/*启动qt_svg_process 信息*/
cp_int32_t start_qt_svg_process(
	cp_qt_svg_process_t *process,
	cp_qt_svg_process_info_t *info)
{
	cp_int32_t							ret_int = 0;



	//启动播放管理器信息
	ret_int = start_channel_manager(&(process->channel_manager));
	if (ret_int) {
		cp_qt_svg_process_log(error, process, "start_qt_svg_process() error.");
		return -1;
	}
	else {
		cp_qt_svg_process_log(notice, process, "start_qt_svg_process() succeed.");
	}

	return 0;
}

//创建svg处理资源
cp_int32_t qt_svg_process_create_source(
	cp_qt_svg_process_t *process,
	cp_qt_svg_process_info_t *info)
{
	int							tmp_argc = 0;
	char						*tmp_argv = CP_NULL;
	//QSurfaceFormat				tmp_format;
	QGLWidget					*tmp_qgl_widget = CP_NULL;
	QGLFormat					tmp_format;
	QString						tmp_gl_type;
	QString						tmp_gl_version;
	//QString						tmp_gl_profile;

	if (!process) {
		return -1;
	}

	//先销毁资源
	qt_svg_process_destroy_source(process);

	//创建application
	try
	{		
		process->qt_app = new QApplication(tmp_argc, CP_NULL);
		if (process->qt_app) {
			cp_qt_svg_process_log(notice, process,
				"create QApplication[0x%x] succeed.", 
				process->qt_app);
		}

#ifdef WIN32
		// 设置 OpenGL 版本信息
		// 注意: format 必须在 show() 调用前设置
		//tmp_format.setRenderableType(QSurfaceFormat::OpenGL);
		//tmp_format.setProfile(QSurfaceFormat::CoreProfile);
		tmp_format.setProfile(QGLFormat::CoreProfile);
		//tmp_format.setProfile(QSurfaceFormat::CompatibilityProfile);
		tmp_format.setVersion(4, 3);
#else
		// 设置 OpenGL 版本信息
		// 注意: format 必须在 show() 调用前设置
		//tmp_format.setRenderableType(QSurfaceFormat::OpenGLES);
		//tmp_format.setProfile(QSurfaceFormat::CoreProfile);
		tmp_format.setProfile(QGLFormat::CoreProfile);
		//tmp_format.setProfile(QSurfaceFormat::CompatibilityProfile);
		tmp_format.setVersion(2, 0);
#endif

// 		QCommandLineParser parser;
// 		parser.addPositionalArgument("graphicssystem", "opengl", "opengl", "opengl");
// 		parser.process(*(process->qt_app));
	}
	catch (std::exception& e)
	{
		cp_qt_svg_process_log(error, process,
			"create QApplication() error. exception[%s]", e.what());
		return -2;
	}

	//创建和初始化view视图对象
	try
	{
		process->view = new QGraphicsView();
		if (process->view) {
			cp_qt_svg_process_log(notice, process,
				"create QGraphicsView[0x%x] succeed.",
				process->view);

			//QOpenGLPaintDevice *qopenglpaintdevice = new QOpenGLPaintDevice();
			//QGLContext *qgl_context = new QGLContext(QGLFormat(QGL::Rgba | QGL::SampleBuffers | QGL::DirectRendering), new QOpenGLPaintDevice());
			//QGLWidget *tmp_qgl_widget = new QGLWidget(qgl_context);
			QGLWidget *tmp_qgl_widget = new QGLWidget(QGLFormat(QGL::Rgba | QGL::SampleBuffers | QGL::DirectRendering));
			tmp_qgl_widget->setFormat(tmp_format);
			process->view->setViewport(tmp_qgl_widget);
			process->view->setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);
			process->view->update();

			// Get Version Information
			tmp_gl_type = (tmp_qgl_widget->context()->contextHandle()->isOpenGLES()) ? "OpenGL ES" : "OpenGL";
			//tmp_gl_version = reinterpret_cast<const char*>(glGetString(GL_VERSION));

			if (tmp_qgl_widget->context()->isValid()) {
				cp_qt_svg_process_log(notice, process,
					"QGLWidget opengl[%s 0x%x %d] valid succeed."
					, tmp_gl_type.toLatin1().data()
					, tmp_format.openGLVersionFlags()
					, tmp_format.profile());
// 				cp_qt_svg_process_log(notice, process,
// 					"QGLWidget opengl[%s %s %d] valid succeed."
// 					, tmp_gl_type.toLatin1().data()
// 					, tmp_gl_version.toLatin1().data()
// 					, tmp_format.profile());

			}
			else {
				cp_qt_svg_process_log(notice, process,
					"QGLWidget opengl[%s 0x%x %d] invalid failed!"
					, tmp_gl_type.toLatin1().data()
					, tmp_format.openGLVersionFlags()
					, tmp_format.profile());
			}
		}
	}
	catch (std::exception& e)
	{
		cp_qt_svg_process_log(error, process,
			"create QGraphicsView() error. exception[%s]", e.what());
		return -2;
	}

	//创建和初始化scene场景对象
	try
	{
		if (info && check_rect_valid(&info->rect)) {
			process->scene = new QGraphicsScene(info->rect.left, info->rect.top,
				info->rect.right - info->rect.left,
				info->rect.bottom - info->rect.top,
				process->view);
		}
		else {
			process->scene = new QGraphicsScene(process->view);
		}

		if (process->scene) {
			cp_qt_svg_process_log(notice, process,
				"create QGraphicsScene[0x%x] succeed.",
				process->scene);
		}
	}
	catch (std::exception& e)
	{
		cp_qt_svg_process_log(error, process,
			"create QGraphicsScene() error. exception[%s]", e.what());
		return -2;
	}

	return 0;
}
//销毁svg处理资源
cp_int32_t qt_svg_process_destroy_source(cp_qt_svg_process_t *process)
{
	if (!process) {
		return -1;
	}

	//销毁场景
	if (process->scene) {

		cp_qt_svg_process_log(notice, process,
			"destroy QGraphicsScene[0x%x] succeed.",
			process->scene);

		process->scene->clear();
		delete process->scene;
		process->scene = CP_NULL;
	}

	//销毁视图
	if (process->view) {

		cp_qt_svg_process_log(notice, process,
			"destroy QGraphicsView[0x%x] succeed.",
			process->view);

		process->view->resetTransform();
		delete process->view;
		process->view = CP_NULL;
	}

	//销毁qt app内容
	if (process->qt_app) {

		cp_qt_svg_process_log(notice, process,
			"destroy QApplication[0x%x] succeed.",
			process->qt_app);

		process->qt_app->exit();
		process->qt_app->quit();
		delete process->qt_app;
		process->qt_app = CP_NULL;
	}

	return 0;
}

//校验是否已经准备好
/*******************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: qt_svg_process_check_ready
*
* 函数全名: qt_svg_process_check_ready
*
* 函数访问: public
*
* 函数说明: 校验是否已经准备好
*
* 参    数: cp_qt_svg_process_t * process						[in/out]参数说明
*
* 返 回 值: cp_int32_t
*           0  : 表示存在
*         非0  : 表示不存在
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2018-1-31 16:05:17
********************************************************************************/
cp_int32_t qt_svg_process_check_ready(cp_qt_svg_process_t *process)
{
	if (!process) {
		cp_qt_svg_process_log(error, process, "parametes list error.");
		return cp_vdu_status_null_pointer;
	}

	//判断process是否已经初始化
	if (!process->scene) {
		cp_qt_svg_process_log(error, process, "process render module not ready.");
		return cp_vdu_status_module_not_ready;
	}

	return 0;
}

/*******************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: qt_svg_process_check_svg_channel_index_is_exist
*
* 函数全名: qt_svg_process_check_svg_channel_index_is_exist
*
* 函数访问: public
*
* 函数说明: 判断channel index是否存在
*
* 参    数: cp_qt_svg_process_t * process						[in/out]参数说明
* 参    数: cp_int32_t index						[in/out]参数说明
*
* 返 回 值: cp_bool_t
*           cp_true  : 成功,表示存在
*           cp_false  : 失败,表示不存在
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2018-1-31 11:01:03
********************************************************************************/
inline cp_bool_t qt_svg_process_check_svg_channel_index_is_exist(
	cp_qt_svg_process_t *process,
	cp_int32_t index)
{
	if (!find_channel_by_index(&process->channel_manager, index)) {
		return cp_false;
	}
	return cp_true;
}

//创建channel
/*******************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: qt_svg_process_create_svg_channel
*
* 函数全名: qt_svg_process_create_svg_channel
*
* 函数访问: public
*
* 函数说明: 创建channel
*
* 参    数: cp_qt_svg_process_t * process						[in/out]参数说明
* 参    数: cp_int32_t index						[in/out]参数说明
*
* 返 回 值: cp_qt_svg_channel_t*
*           0  : 成功
*         非0  : 失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2018-1-30 11:44:05
********************************************************************************/
cp_qt_svg_channel_t* qt_svg_process_create_svg_channel(
	cp_qt_svg_process_t *process,
	cp_int32_t index)
{
	cp_int32_t								ret_int = 0;
	cp_channel_t							*tmp_general_channel = CP_NULL;
	cp_qt_svg_channel_t						*tmp_channel = CP_NULL;
	cp_qt_svg_channel_info_t				tmp_channel_info = { 0, };



	//检验是否已经存在
	if (qt_svg_process_check_svg_channel_index_is_exist(process, index)) {
		cp_qt_svg_set_errno(process, cp_vdu_status_channel_index_existed);
		cp_qt_svg_process_log(error, process, "channel index[%d] is exist.", index);
		return CP_NULL;
	}

	//创建一个媒体通道
	tmp_channel_info.index = index;
	tmp_channel = create_qt_svg_channel(process, &tmp_channel_info);
	if (!tmp_channel) {
		cp_qt_svg_process_log(error, process, "create_qt_svg_channel() error.");
		return CP_NULL;
	}
	else {
		tmp_channel->channel.index = index;
	}

	//初始化通道信息
	ret_int = init_qt_svg_channel(tmp_channel, &tmp_channel_info);
	if (ret_int) {
		cp_qt_svg_set_errno(process, ret_int);
		destroy_qt_svg_channel(tmp_channel);
		cp_qt_svg_process_log(error, process, "init_qt_svg_channel() error.");
		return CP_NULL;
	}

	//启动通道信息
	ret_int = start_qt_svg_channel(tmp_channel, &tmp_channel_info);
	if (ret_int) {
		cp_qt_svg_set_errno(process, ret_int);
		destroy_qt_svg_channel(tmp_channel);
		cp_qt_svg_process_log(error, process, "start_qt_svg_channel() error.");
		return CP_NULL;
	}

	//初始化通道信息
	ret_int = init_channel(&process->channel_manager, &tmp_channel->channel);
	if (ret_int) {
		destroy_qt_svg_channel(tmp_channel);
		cp_qt_svg_process_log(error, process, "init_channel() error.");
		return CP_NULL;
	}

	//插入通道到管理器中
	tmp_general_channel = insert_channel(&process->channel_manager, &tmp_channel->channel);
	if (!tmp_general_channel) {
		destroy_qt_svg_channel(tmp_channel);
		cp_qt_svg_process_log(error, process, "insert_channel() error.");
		return CP_NULL;
	}

	return tmp_channel;
}

//创建最大的channel通道
/*******************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: qt_svg_process_create_max_svg_channel
*
* 函数全名: qt_svg_process_create_max_svg_channel
*
* 函数访问: public
*
* 函数说明: 创建最大的channel通道
*
* 参    数: cp_qt_svg_process_t * process						[in/out]参数说明
*
* 返 回 值: cp_qt_svg_channel_t*
*           0  : 成功
*         非0  : 失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2018-1-31 10:56:14
********************************************************************************/
cp_qt_svg_channel_t* qt_svg_process_create_max_svg_channel(cp_qt_svg_process_t *process)
{
	//这里通过查找最大通道号后加1处理
	return qt_svg_process_create_svg_channel(process, 
		find_max_channel_index(&process->channel_manager) + 1);
}

//销毁svg_channel
/*******************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: qt_svg_process_destroy_svg_channel
*
* 函数全名: qt_svg_process_destroy_svg_channel
*
* 函数访问: public
*
* 函数说明: 销毁svg_channel
*
* 参    数: cp_qt_svg_process_t * process						[in/out]参数说明
* 参    数: cp_qt_svg_channel_t * svg_channel						[in/out]参数说明
*
* 返 回 值: cp_int32_t
*           0  : 成功
*         非0  : 失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2018-1-30 11:44:18
********************************************************************************/
cp_int32_t qt_svg_process_destroy_svg_channel(
	cp_qt_svg_process_t *process,
	cp_qt_svg_channel_t *svg_channel)
{
	cp_int32_t								ret_int = 0;



	if (!process || !svg_channel) {
		return -1;
	}

	//删除通道信息
	remove_channel(&process->channel_manager, &svg_channel->channel);

	//停止通道信息
	ret_int = stop_qt_svg_channel(svg_channel);
	if (ret_int) {
		cp_qt_svg_process_log(warn, process, "stop_qt_svg_channel() warning.");
	}

	//销毁通道信息
	destroy_qt_svg_channel(svg_channel);

	return 0;
}

//通过index销毁channel
cp_int32_t qt_svg_process_destroy_svg_channel_by_index(
	cp_qt_svg_process_t *process,
	cp_int32_t index)
{
	cp_channel_t					*tmp_channel = CP_NULL;
	cp_qt_svg_channel_t				*tmp_svg_channel = CP_NULL;


	//通过index查找通道信息
	tmp_channel = find_channel_by_index(&process->channel_manager, index);
	if (!tmp_channel) {
		cp_qt_svg_process_log(error, process,
			"find_channel_by_index() error. not found channel by index[%d]", index);
		return -1;
	}

	//通道绑定的数据为空则错误
	if (!tmp_channel->data) {
		cp_qt_svg_process_log(error, process, "channel data is null error");
		return -2;
	}

	return qt_svg_process_destroy_svg_channel(process,
		(cp_qt_svg_channel_t *)(tmp_channel->data));
}

//销毁all_channel
/*******************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: qt_svg_process_destroy_all_svg_channel
*
* 函数全名: qt_svg_process_destroy_all_svg_channel
*
* 函数访问: public
*
* 函数说明: 销毁all_channel
*
* 参    数: cp_qt_svg_process_t * process						[in/out]参数说明
*
* 返 回 值: cp_int32_t
*           0  : 成功
*         非0  : 失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2018-1-30 11:44:27
********************************************************************************/
cp_int32_t qt_svg_process_destroy_all_svg_channel(cp_qt_svg_process_t *process)
{
	return remove_all_channel(&process->channel_manager, 
		process, qt_svg_process_remove_svg_channel_callback);
}

/*******************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: qt_svg_process_remove_svg_channel_callback
*
* 函数全名: qt_svg_process_remove_svg_channel_callback
*
* 函数访问: public
*
* 函数说明: 删除所有通道的
*
* 参    数: cp_channel_manager_t * cm						[in/out]参数说明
* 参    数: cp_void_t * arg						[in/out]参数说明
* 参    数: cp_channel_t * channel						[in/out]参数说明
*
* 返 回 值: int
*           0  : 成功
*         非0  : 失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2018-1-30 12:27:31
********************************************************************************/
int qt_svg_process_remove_svg_channel_callback(
	cp_channel_manager_t *cm,
	cp_void_t *arg,
	cp_channel_t *channel)
{
	if (!cm || !channel || !channel->data) {
		return -1;
	}

	return qt_svg_process_destroy_svg_channel((cp_qt_svg_process_t*)arg,
		(cp_qt_svg_channel_t *)(channel->data));
}

//设置coordinate数值
cp_int32_t qt_svg_process_set_coordinate(cp_qt_svg_process_t *process,
	cp_coordinate_t coordinate)
{
	return 0;
}

//获取coordinate数值
cp_int32_t qt_svg_process_get_coordinate(cp_qt_svg_process_t *process,
	cp_coordinate_t *coordinate)
{
	return 0;
}

//设置debug info数值
cp_int32_t qt_svg_process_set_debug_info(cp_qt_svg_process_t *process,
	cp_qt_svg_process_debug_info_t debug_info)
{
	if (!process) {
		return -1;
	}

	if (debug_info.is_save_file) {
		cp_mkdir_simple(debug_info.path);
	}

	process->debug_info = debug_info;

	return 0;
}

//设置保存文件信息
cp_int32_t qt_svg_process_save_file(cp_qt_svg_process_t *process, QImage *image)
{
	cp_char_t							tmp_file_name[CP_APP_DEFAULT_BUFFER_LENGTH] = { 0, };



	if (!process->debug_info.is_save_file) {
		return 0;
	}

	cp_sprintf(tmp_file_name,
		"%s%c%s_output_file.png",
		process->debug_info.path,
		cp_dir_diagonal,
		CP_QT_SVG_DEBUG_TEST_SAVE_TO_FILE_PROCESS_FLAG);

	image->save(tmp_file_name, "PNG"); // writes the image in PNG format inside the buffer

	return 0;
}

/*清除svg图片的感兴趣区域数据*/
cp_int32_t qt_svg_process_clear_roi(cp_qt_svg_process_t *process)
{
	//判断process是否已经初始化
	if (qt_svg_process_check_ready(process)) {
		cp_qt_svg_process_log(error, process, "process render module not ready.");
		return cp_vdu_status_module_not_ready;
	}

	//设置rect区域
	if (check_rect_valid(&process->info.rect)) {
		process->scene->setSceneRect(
			process->info.rect.left, process->info.rect.top,
			process->info.rect.right - process->info.rect.left,
			process->info.rect.bottom - process->info.rect.top);
	}
	else {
		qt_svg_process_create_source(process, &process->info);
	}

	return 0;
}

/*设置svg图片的感兴趣区域数据*/
cp_int32_t qt_svg_process_set_roi(cp_qt_svg_process_t *process, cp_rect_t rect)
{
	//判断process是否已经初始化
	if (qt_svg_process_check_ready(process)) {
		cp_qt_svg_process_log(error, process, "process render module not ready.");
		return cp_vdu_status_module_not_ready;
	}

	//核验rect是否合法
	if (check_rect_valid(&rect)) {
		cp_qt_svg_process_log(error, process, "rect invalid.");
		return cp_vdu_status_invalid_parametes;
	}

	//设置rect区域
	process->scene->setSceneRect(rect.left, rect.top,
		rect.right - rect.left,
		rect.bottom - rect.top);

	return 0;
}

/*获取svg图片的感兴趣区域数据*/
cp_int32_t qt_svg_process_get_roi(cp_qt_svg_process_t *process, cp_rect_t *dest_rect)
{
	//判断process是否已经初始化
	if (qt_svg_process_check_ready(process)) {
		cp_qt_svg_process_log(error, process, "process render module not ready.");
		return cp_vdu_status_module_not_ready;
	}

	//获取显示区域
	QRectF   tmp_rect = process->scene->sceneRect();

	//更新数据
	dest_rect->left = tmp_rect.left();
	dest_rect->top = tmp_rect.top();
	dest_rect->right = tmp_rect.right();
	dest_rect->bottom = tmp_rect.bottom();

	return 0;
}

/*获取svg感兴趣区域数据的图片数据*/
cp_int32_t qt_svg_process_get_roi_pixel(cp_qt_svg_process_t *process,
	cp_uchar_t *dest_buf,
	cp_uint32_t buf_len,
	cp_codec_pixel_format_e cpf,
	cp_rect_t *image_rect)
{
	QImage::Format					tmp_fmt = QImage::Format_Invalid;
	cp_int32_t						tmp_ret_int = 0;
	cp_rect_t						tmp_rect = { 0, };



	if (!process || !dest_buf || !buf_len) {
		cp_qt_svg_process_log(error, process, "parametes list error.");
		return cp_vdu_status_null_pointer;
	}

	//判断process是否已经初始化
	if (qt_svg_process_check_ready(process)) {
		cp_qt_svg_process_log(error, process, "process render module not ready.");
		return cp_vdu_status_module_not_ready;
	}

	//转换图片格式
	tmp_fmt = convert_cpf_to_qimage_format(cpf);
	if (QImage::Format_Invalid == tmp_fmt) {
		cp_qt_svg_process_log(error, process, "unsupport pixel format[%d].", cpf);
		return cp_vdu_status_unsupport_pixel_format;
	}

	//QImage image(rect.right - rect.left, rect.bottom - rect.top, QImage::Format_ARGB32);
	if (image_rect) {
		tmp_rect = *image_rect;
	}
	else {
		tmp_ret_int = qt_svg_process_get_roi(process, &tmp_rect);
		if (tmp_ret_int) {
			cp_qt_svg_process_log(error, process, "get roi failed.");
			return cp_vdu_status_system_error;
		}
	}

	//核验rect是否合法
	if (check_rect_valid(&tmp_rect)) {
		cp_qt_svg_process_log(error, process, "rect invalid.");
		return cp_vdu_status_invalid_parametes;
	}

	//QImage image(rect.right - rect.left, rect.bottom - rect.top, QImage::Format_ARGB32);
	//QImage tmp_image(tmp_rect.right - tmp_rect.left, tmp_rect.bottom - tmp_rect.top, tmp_fmt);
	QImage tmp_image(dest_buf, tmp_rect.right - tmp_rect.left, tmp_rect.bottom - tmp_rect.top, tmp_fmt);
	//QImage tmp_image(tmp_rect.right - tmp_rect.left, tmp_rect.bottom - tmp_rect.top, tmp_fmt);
	//image.fill(0xaaA08080);  // partly transparent red-ish background
	tmp_image.fill(Qt::transparent);

	//创建painter
	QPainter tmp_painter(&tmp_image);

	//tmp_painter.begin(&tmp_image);
	//process->render()->render(&painter, QRectF(QPointF(), QSizeF(imageSize)));
	//缩放图片,这里渲染的时候可以实现自动缩放处理
	process->scene->render(&tmp_painter);
	//tmp_painter.end();

	//将图片保存在文件中
	qt_svg_process_save_file(process, &tmp_image);

#if CP_QT_SVG_DEBUG_TEST_SAVE_TO_FILE

	//QByteArray tmp_byte_array;
	//QBuffer tmp_buffer(&tmp_byte_array);
	//image.save(&buffer, "PNG"); // writes the image in PNG format inside the buffer
	tmp_image.save("files\\out_process_svg_file_by_roi.png", "PNG"); // writes the image in PNG format inside the buffer
	//tmp_image.save(&tmp_buffer); // writes the image in PNG format inside the buffer

	//判断内存是否够用
	// 	if (tmp_byte_array.count() > (cp_int32_t)buf_len) {
	// 		cp_qt_svg_process_log(error, process, 
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

/*获取svg指定区域的图片数据*/
cp_int32_t qt_svg_process_get_rect_pixel(
	cp_qt_svg_process_t *process,
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
		cp_qt_svg_process_log(error, process, "rect invalid.");
		return cp_vdu_status_invalid_parametes;
	}

	//转换图片格式
	tmp_fmt = convert_cpf_to_qimage_format(cpf);
	if (QImage::Format_Invalid == tmp_fmt) {
		cp_qt_svg_process_log(error, process,
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
	tmp_ret_int = qt_svg_process_get_roi(process, &tmp_prev_roi_rect);
	if (tmp_ret_int) {
		cp_qt_svg_process_log(error, process, "get roi for backup failed.");
		return cp_vdu_status_system_error;
	}

	//开始设置需要的感兴趣区域
	tmp_ret_int = qt_svg_process_set_roi(process, rect);
	if (tmp_ret_int) {
		cp_qt_svg_process_log(error, process, "set begin roi failed.");
		return cp_vdu_status_system_error;
	}

	//tmp_painter.begin(&tmp_image);
	//process->render()->render(&painter, QRectF(QPointF(), QSizeF(imageSize)));
	//缩放图片,这里渲染的时候可以实现自动缩放处理
	//process->render->render(&tmp_painter, 
	//	QRectF(rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top));
	process->scene->render(&tmp_painter);
	//tmp_painter.end();

	//还原设置原来的感兴趣区域
	tmp_ret_int = qt_svg_process_set_roi(process, tmp_prev_roi_rect);
	if (tmp_ret_int) {
		cp_qt_svg_process_log(error, process, "set end roi failed.");
		return cp_vdu_status_system_error;
	}

	//将图片保存在文件中
	qt_svg_process_save_file(process, &tmp_image);

#if CP_QT_SVG_DEBUG_TEST_SAVE_TO_FILE

	//QByteArray tmp_byte_array;
	//QBuffer tmp_buffer(&tmp_byte_array);
	//image.save(&buffer, "PNG"); // writes the image in PNG format inside the buffer
	tmp_image.save("files\\out_process_svg_file_by_rect.png", "PNG"); // writes the image in PNG format inside the buffer
	//tmp_image.save(&tmp_buffer); // writes the image in PNG format inside the buffer

	//判断内存是否够用
	// 	if (tmp_byte_array.count() > (cp_int32_t)buf_len) {
	// 		cp_qt_svg_process_log(error, process, 
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

/*表示插入场景*/
/*******************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: qt_svg_process_insert_svg_channel
*
* 函数全名: qt_svg_process_insert_svg_channel
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
* 创建日期：2018-2-1 10:48:18
********************************************************************************/
cp_int32_t qt_svg_process_insert_svg_channel(
	cp_qt_svg_process_t *process,
	cp_qt_svg_channel_t *channel,
	cp_rect_t rect)
{
	cp_int32_t						tmp_ret_int = 0;



	//判断process是否已经初始化
	if (qt_svg_process_check_ready(process)) {
		cp_qt_svg_process_log(error, process, "process render module not ready.");
		return cp_vdu_status_module_not_ready;
	}

	//插入channel到process中
	tmp_ret_int = qt_svg_channel_insert_scene(process, channel, rect);
	if (tmp_ret_int) {
		cp_qt_svg_process_log(error, process,
			"qt_svg_channel_insert_scene() error.");
		return tmp_ret_int;
	}

	//赋值并添加item
	channel->scene.process = process;
	process->scene->addItem(channel->item);

	return 0;
}

/*表示退出场景*/
/*******************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: qt_svg_process_remove_svg_channel
*
* 函数全名: qt_svg_process_remove_svg_channel
*
* 函数访问: public
*
* 函数说明: 表示退出场景
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
* 创建日期：2018-2-1 10:48:28
********************************************************************************/
cp_int32_t qt_svg_process_remove_svg_channel(
	cp_qt_svg_process_t *process,
	cp_qt_svg_channel_t *channel)
{
	cp_int32_t						tmp_ret_int = 0;



	//判断process是否已经初始化
	if (qt_svg_process_check_ready(process)) {
		cp_qt_svg_process_log(error, process, "process render module not ready.");
		return cp_vdu_status_module_not_ready;
	}

	//插入channel到process中
	tmp_ret_int = qt_svg_channel_remove_scene(process, channel);
	if (tmp_ret_int) {
		cp_qt_svg_process_log(error, process,
			"qt_svg_channel_remove_scene() error.");
		return tmp_ret_int;
	}

	//删除item
	process->scene->removeItem(channel->item);

	return 0;
}

/*表示修改通道的index，即图层属性*/
/*******************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: qt_svg_process_update_svg_channel_index
*
* 函数全名: qt_svg_process_update_svg_channel_index
*
* 函数访问: public
*
* 函数说明: 表示修改通道的index，即图层属性
*
* 参    数: cp_qt_svg_process_t * process						[in/out]参数说明
* 参    数: cp_qt_svg_channel_t * channel						[in/out]参数说明
* 参    数: cp_int32_t index						[in/out]参数说明
*
* 返 回 值: cp_int32_t
*           0  : 成功
*         非0  : 失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2018-2-1 10:17:09
********************************************************************************/
cp_int32_t qt_svg_process_update_svg_channel_index(
	cp_qt_svg_process_t *process,
	cp_qt_svg_channel_t *channel,
	cp_int32_t index)
{
	cp_int32_t						tmp_ret_int = 0;



	//判断process是否已经初始化
	if (qt_svg_process_check_ready(process)) {
		cp_qt_svg_process_log(error, process, "process render module not ready.");
		return cp_vdu_status_module_not_ready;
	}

	//更新场景信息
	tmp_ret_int = qt_svg_channel_update_index(channel, index);
	if (tmp_ret_int) {
		cp_qt_svg_process_log(error, process,
			"qt_svg_channel_update_index() error.");
		return tmp_ret_int;
	}

	return 0;
}

/*停止qt_svg_process 信息*/
/*******************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: stop_qt_svg_process
*
* 函数全名: stop_qt_svg_process
*
* 函数访问: public
*
* 函数说明: 停止qt_svg_process 信息
*
* 参    数: cp_qt_svg_process_t * process						[in/out]参数说明
*
* 返 回 值: cp_int32_t
*           0  : 成功
*         非0  : 失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2018-1-31 10:38:42
********************************************************************************/
cp_int32_t stop_qt_svg_process(cp_qt_svg_process_t *process)
{
	if (!process) {
		return -1;
	}

	//销毁所有通道信息
	qt_svg_process_destroy_all_svg_channel(process);

	//停止通道管理器
	stop_channel_manager(&process->channel_manager);

	//销毁资源
	qt_svg_process_destroy_source(process);

	return 0;
}







