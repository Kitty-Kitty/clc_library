/*******************************************************************************
*
*Copyright:novigo
*
*File name: cp_vdu_api.c
*
*Author:fangzhenmu@novigo.com.cn
*
*Version: 1.0
*
*Date:2018/02/05
*
*Description: create (cp_vdu_api.c)
*
*Others:
*
*History:
*******************************************************************************/
#include "cp_vdu_core.h"
#include "cp_vdu_codec_module_option.h"



int cp_vdu_init(cp_vdu_t *vdu, const cp_vdu_info_t *vdu_info);								/*模块创建接口，表示创建一个模块*/
int cp_vdu_open(cp_vdu_t *vdu, const cp_vdu_info_t *vdu_info);								/*模块打开运行接口，在模块init之后，会被调用*/
int cp_vdu_read(cp_vdu_t *vdu, char **buf, int len, int flag);								/*读取模块数据，flag为读取模式的扩展标志。默认为0，其他为预留*/
int cp_vdu_write(cp_vdu_t *vdu, const char **buf, int len, int flag);						/*写模块数据，flag为写模式的扩展标志。默认为0，其他为预留*/
int cp_vdu_close(cp_vdu_t *vdu);															/*关闭模块*/
int cp_vdu_exit(cp_vdu_t *vdu);																/*退出模块*/
int cp_vdu_set_option(cp_vdu_t *vdu, int optname, const void* optval);						/*设置模块参数*/
int cp_vdu_get_option(cp_vdu_t *vdu, int optname, void* optval);							/*获取模块参数*/




/************************************************************************/
/* 引入app info变量                                                      */
/************************************************************************/
CP_EXTERN_GLOBAL_APP_INFO();

//全局app参数定义
CP_EXTERN_APP_PARAMETER();

//创建一个cp_vdu_t对象
cp_vdu_t* cp_vdu_create() {
	cp_vdu_t					*tmp_vdu = CP_NULL;
	cp_vdu_app_t				*tmp_vdu_app = CP_NULL;
	cp_app_info_t				tmp_vdu_info = { 0, };
	cp_int32_t					tmp_ret_int = 0;
	char						tmp_buf[CP_APP_DEFAULT_BUFFER_LENGTH] = { 0, };


	//
	/********************************************************************************************************************/
	/* 这里定义一些全局变量，大致内容如下：																					*/
	/*cp_app_info_t		        cp_global_app_info = { type, name, version, description, NULL, 0, NULL };				*/
	/*cp_app_create_handle	    cp_global_app_create_handle = create_handle;											*/
	/*cp_app_destroy_handle		cp_global_app_destroy_handle = destroy_handle;											*/
	/********************************************************************************************************************/
	cp_app_register(CP_VDU_TYPE, CP_VDU_VAR, cp_vdu_version, CP_VDU_VER,
		(cp_app_create_handle)cp_vdu_app_create, (cp_app_destroy_handle)cp_vdu_app_destroy);

	//这里定义宏来表示是否启动日志
#ifdef CP_VDU_USED_LOG_SYSTEM
#if defined WIN32
	CP_APP_ENTRY_CONFIG_PATH("E:\\project_work\\project\\css_workspace\\cp_player\\app\\vector_data_unit\\vdu_sample_demo\\configs\\css.conf");
#endif 
#endif // CP_VDU_USED_LOG_SYSTEM

	//请求通道
	tmp_vdu = cp_malloc(sizeof(cp_vdu_t));
	if (!tmp_vdu) {
		printf("cp_vdu_create() error reason: malloc failed!");
		return CP_NULL;
	}
	else {
		cp_memset(tmp_vdu, 0, sizeof(cp_vdu_t));
	}

	tmp_vdu_info = cp_global_app_info;

	//创建设备
	tmp_vdu_app = (cp_vdu_app_t *)cp_global_app_create_handle(&tmp_vdu_info);
	if (!tmp_vdu_app) {
		cp_log_printf("create app failed! : \t%s",
			cp_print_app_info(&tmp_vdu_info, tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH));
		return CP_NULL;
	}
	else {
		cp_global_app = (cp_app_t *)tmp_vdu_app;
		tmp_vdu_app->daemon_info = cp_global_daemon_info;
		CP_UPDATE_APP_APP_INFO(tmp_vdu_app, tmp_vdu_app->app_info);
		CP_UPDATE_APP_REGISTER_INFO(tmp_vdu_app, tmp_vdu_app->app_info, cp_global_app_create_handle, cp_global_app_destroy_handle);
	}

	/*初始化设备，包括
	*读取设备配置文件
	*日志模块
	*初始化TCP/UDP监听服务
	*/
	tmp_ret_int = tmp_vdu_app->init((cp_app_t *)tmp_vdu_app, &tmp_vdu_info);
	if (tmp_ret_int) {
		cp_log_printf("init app failed! : \t%s",
			cp_print_app_info(&tmp_vdu_info, tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH));
		return CP_NULL;
	}
	else {
		cp_log_notice(tmp_vdu_app->logger, "init app success! : %s",
			cp_print_app_info(&tmp_vdu_info, tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH));
	}

	//启动设备
	tmp_ret_int = tmp_vdu_app->start((cp_app_t *)tmp_vdu_app, &tmp_vdu_info);
	if (tmp_ret_int) {
		cp_log_fatal(tmp_vdu_app->logger, "start app failed! : %s",
			cp_print_app_info(&tmp_vdu_info, tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH));
		return CP_NULL;
	}
	else {
		cp_log_notice(tmp_vdu_app->logger, "start app success! : %s",
			cp_print_app_info(&tmp_vdu_info, tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH));
	}

	//保存设备信息
	tmp_vdu->app = tmp_vdu_app;

	return tmp_vdu;
}

//销毁cp_vdu对象
cp_int32_t cp_vdu_destroy(cp_vdu_t *vdu) {
	cp_int32_t					tmp_ret_int = 0;
	cp_vdu_app_t				*tmp_vdu_app = CP_NULL;
	char						tmp_buf[CP_APP_DEFAULT_BUFFER_LENGTH] = { 0, };


	if (!vdu) {
		return cp_vdu_status_null_pointer;
	}

	//如果app存在则销毁
	if (vdu->app) {
		tmp_vdu_app = (cp_vdu_app_t *)vdu->app;

		//停止vdu
		tmp_ret_int = tmp_vdu_app->stop((cp_app_t *)tmp_vdu_app);
		if (tmp_ret_int) {
			cp_log_printf("stop app failed!");
			return -2;
		}
		else {
			cp_log_printf("stop app success!");
		}

		//销毁vdu
		tmp_ret_int = cp_global_app_destroy_handle((cp_app_t *)tmp_vdu_app);
		if (tmp_ret_int) {
			cp_log_printf("destroy app failed!");
			return -2;
		}
		else {
			cp_log_printf("destroy app success!");
		}
	}

	//释放vdu资源
	cp_free(vdu);

	return cp_vdu_status_success;
}

//获取版本信息
cp_vdu_version_t cp_vdu_get_version(cp_vdu_t *vdu)
{
	cp_vdu_version_t						tmp_version = {
		CP_VDU_VAR,
		cp_vdu_version,
		CP_VDU_VERSION,
		CP_VDU_VER
	};

	return tmp_version;
}

//获取vdu的状态码
cp_vdu_status_e cp_vdu_get_status(cp_vdu_t *vdu)
{
	cp_int32_t						tmp_ret_int = 0;
	cp_vdu_app_t					*tmp_vdu_app = CP_NULL;
	cp_vdu_process_t				tmp_process = { 0, };



	if (!vdu || !vdu->app) {
		return cp_vdu_status_null_pointer;
	}
	tmp_vdu_app = (cp_vdu_app_t *)(vdu->app);

	//初始化process struct
	fill_vdu_to_process_struct(&tmp_process, vdu);

	//创建channel
	tmp_ret_int = cp_get_option_module(tmp_vdu_app->vdu_func,
		cp_qt_svg_process_option_get_status, &tmp_process);
	if (tmp_ret_int) {
		return tmp_ret_int;
	}

	return (cp_vdu_status_e)(tmp_process.error_no);
}

//设置坐标信息
int cp_vdu_set_coordinate(cp_vdu_t *vdu, cp_vdu_coordinate_t coordinate)
{
	cp_int32_t						tmp_ret_int = 0;
	cp_vdu_app_t					*tmp_vdu_app = CP_NULL;
	cp_vdu_process_t				tmp_process = { 0, };



	if (!vdu || !vdu->app) {
		return cp_vdu_status_null_pointer;
	}
	tmp_vdu_app = (cp_vdu_app_t *)(vdu->app);

	//初始化process struct
	fill_vdu_to_process_struct(&tmp_process, vdu);
	tmp_process.coordinate.x = coordinate.x;
	tmp_process.coordinate.y = coordinate.y;
	tmp_process.coordinate.z = coordinate.z;

	//设置coordinate数据
	tmp_ret_int = cp_get_option_module(tmp_vdu_app->vdu_func,
		cp_qt_svg_process_option_set_coordinate, &tmp_process);
	if (tmp_ret_int) {
		return tmp_ret_int;
	}

	return tmp_ret_int;
}

int cp_vdu_get_coordinate(cp_vdu_t *vdu, cp_vdu_coordinate_t *coordinate)
{
	cp_int32_t						tmp_ret_int = 0;
	cp_vdu_app_t					*tmp_vdu_app = CP_NULL;
	cp_vdu_process_t				tmp_process = { 0, };



	if (!vdu || !vdu->app || !coordinate) {
		return cp_vdu_status_null_pointer;
	}
	tmp_vdu_app = (cp_vdu_app_t *)(vdu->app);

	//初始化process struct
	fill_vdu_to_process_struct(&tmp_process, vdu);

	//获取coordinate数据
	tmp_ret_int = cp_get_option_module(tmp_vdu_app->vdu_func,
		cp_qt_svg_process_option_get_coordinate, &tmp_process);
	if (tmp_ret_int) {
		return tmp_ret_int;
	}
	coordinate->x = tmp_process.coordinate.x;
	coordinate->y = tmp_process.coordinate.y;
	coordinate->z = tmp_process.coordinate.z;

	return tmp_ret_int;
}

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
* 参    数: cp_vdu_t * vdu						[in/out]参数说明
* 参    数: char * path						[in/out]参数说明
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
int cp_vdu_open_debug_mode(cp_vdu_t *vdu, char *path)
{
	cp_int32_t						tmp_ret_int = 0;
	cp_vdu_app_t					*tmp_vdu_app = CP_NULL;
	cp_vdu_process_t				tmp_process = { 0, };



	if (!vdu || !vdu->app) {
		return cp_vdu_status_null_pointer;
	}
	tmp_vdu_app = (cp_vdu_app_t *)(vdu->app);

	//初始化process struct
	fill_vdu_to_process_struct(&tmp_process, vdu);
	tmp_process.is_debug_mode = cp_true;
	tmp_process.debug_path = path;

	//设置debug 信息
	tmp_ret_int = cp_set_option_module(tmp_vdu_app->vdu_func,
		cp_qt_svg_process_option_set_debug_info, &tmp_process);
	if (tmp_ret_int) {
		return tmp_ret_int;
	}

	return tmp_ret_int;
}

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
* 参    数: cp_vdu_t * vdu						[in/out]参数说明
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
int cp_vdu_close_debug_mode(cp_vdu_t *vdu)
{
	cp_int32_t						tmp_ret_int = 0;
	cp_vdu_app_t					*tmp_vdu_app = CP_NULL;
	cp_vdu_process_t				tmp_process = { 0, };



	if (!vdu || !vdu->app) {
		return cp_vdu_status_null_pointer;
	}
	tmp_vdu_app = (cp_vdu_app_t *)(vdu->app);

	//初始化process struct
	fill_vdu_to_process_struct(&tmp_process, vdu);
	tmp_process.is_debug_mode = cp_false;

	//设置debug 信息
	tmp_ret_int = cp_set_option_module(tmp_vdu_app->vdu_func,
		cp_qt_svg_process_option_set_debug_info, &tmp_process);
	if (tmp_ret_int) {
		return tmp_ret_int;
	}

	return tmp_ret_int;
}

int cp_vdu_set_type(cp_vdu_t *vdu, cp_vdu_type_e type)
{
	cp_int32_t					tmp_ret_int = 0;
	cp_vdu_app_t				*tmp_vdu_app = CP_NULL;



	if (!vdu || !vdu->app) {
		return cp_vdu_status_null_pointer;
	}
	tmp_vdu_app = (cp_vdu_app_t *)(vdu->app);


	vdu->type = type;

	return cp_vdu_status_success;
}

cp_vdu_type_e cp_vdu_get_type(cp_vdu_t *vdu)
{
	cp_int32_t					tmp_ret_int = 0;
	cp_vdu_app_t				*tmp_vdu_app = CP_NULL;



	if (!vdu || !vdu->app) {
		return cp_vdu_type_none;
	}
	tmp_vdu_app = (cp_vdu_app_t *)(vdu->app);

	return vdu->type;
}

int cp_vdu_set_roi(cp_vdu_t *vdu, cp_vdu_rect_t rect)
{
	cp_int32_t						tmp_ret_int = 0;
	cp_vdu_app_t					*tmp_vdu_app = CP_NULL;
	cp_vdu_process_t				tmp_process = { 0, };



	if (!vdu || !vdu->app) {
		return cp_vdu_status_null_pointer;
	}
	tmp_vdu_app = (cp_vdu_app_t *)(vdu->app);

	//初始化process struct
	fill_vdu_to_process_struct(&tmp_process, vdu);
	convert_vdu_rect_to_cp_rect(&tmp_process.vdu_rect, &rect);

	//设置roi数据
	tmp_ret_int = cp_set_option_module(tmp_vdu_app->vdu_func,
		cp_qt_svg_process_option_set_roi, &tmp_process);
	if (tmp_ret_int) {
		return tmp_ret_int;
	}

	return tmp_ret_int;
}

int cp_vdu_set_roi_parameters(cp_vdu_t *vdu, int x, int y, int width, int height)
{
	cp_vdu_rect_t				tmp_rect = { 0, };


	tmp_rect.x = x;
	tmp_rect.y = y;
	tmp_rect.width = width;
	tmp_rect.height = height;

	return cp_vdu_set_roi(vdu, tmp_rect);
}

int cp_vdu_get_roi(cp_vdu_t *vdu, cp_vdu_rect_t *rect)
{
	cp_int32_t						tmp_ret_int = 0;
	cp_vdu_app_t					*tmp_vdu_app = CP_NULL;
	cp_vdu_process_t				tmp_process = { 0, };



	if (!vdu || !vdu->app) {
		return cp_vdu_status_null_pointer;
	}
	tmp_vdu_app = (cp_vdu_app_t *)(vdu->app);

	//初始化process struct
	fill_vdu_to_process_struct(&tmp_process, vdu);

	//获取roi数据
	tmp_ret_int = cp_get_option_module(tmp_vdu_app->vdu_func,
		cp_qt_svg_process_option_get_roi, &tmp_process);
	if (tmp_ret_int) {
		return tmp_ret_int;
	}
	convert_cp_rect_to_vdu_rect(&rect, &tmp_process.vdu_rect);

	return tmp_ret_int;
}

int cp_vdu_clear_roi(cp_vdu_t *vdu)
{
	cp_int32_t						tmp_ret_int = 0;
	cp_vdu_app_t					*tmp_vdu_app = CP_NULL;
	cp_vdu_process_t				tmp_process = { 0, };



	if (!vdu || !vdu->app) {
		return cp_vdu_status_null_pointer;
	}
	tmp_vdu_app = (cp_vdu_app_t *)(vdu->app);

	//初始化process struct
	fill_vdu_to_process_struct(&tmp_process, vdu);

	//获取roi数据
	tmp_ret_int = cp_get_option_module(tmp_vdu_app->vdu_func,
		cp_qt_svg_process_option_clear_roi, &tmp_process);
	if (tmp_ret_int) {
		return tmp_ret_int;
	}

	return tmp_ret_int;
}

int cp_vdu_get_roi_pixel(cp_vdu_t *vdu,
	char *buf, int len,
	cp_vdu_pixel_format_e vpf,
	cp_vdu_rect_t *scale_rect)
{
	cp_int32_t						tmp_ret_int = 0;
	cp_vdu_app_t					*tmp_vdu_app = CP_NULL;
	cp_vdu_process_t				tmp_process = { 0, };



	if (!vdu || !vdu->app) {
		return cp_vdu_status_null_pointer;
	}
	tmp_vdu_app = (cp_vdu_app_t *)(vdu->app);

	//初始化process struct
	fill_vdu_to_process_struct(&tmp_process, vdu);

	tmp_process.buf = buf;
	tmp_process.buf_length = len;
	tmp_process.pixel_format = convert_vdu_pf_to_cp_pf(vpf);

	if (scale_rect) {
		convert_vdu_rect_to_cp_rect(&tmp_process.image_rect, scale_rect);
	}

	//处理process
	tmp_ret_int = cp_get_option_module(tmp_vdu_app->vdu_func,
		cp_qt_svg_process_option_get_roi_pixel, &tmp_process);
	if (tmp_ret_int < 0) {
		return tmp_ret_int;
	}

	return tmp_process.image_length;
}

int cp_vdu_get_rect_pixel(cp_vdu_t *vdu,
	char *buf, int len,
	cp_vdu_pixel_format_e vpf,
	cp_vdu_rect_t rect,
	cp_vdu_rect_t *scale_rect)
{
	cp_int32_t						tmp_ret_int = 0;
	cp_vdu_app_t					*tmp_vdu_app = CP_NULL;
	cp_vdu_process_t				tmp_process = { 0, };



	if (!vdu || !vdu->app) {
		return cp_vdu_status_null_pointer;
	}
	tmp_vdu_app = (cp_vdu_app_t *)(vdu->app);

	//初始化process struct
	fill_vdu_to_process_struct(&tmp_process, vdu);

	tmp_process.buf = buf;
	tmp_process.buf_length = len;
	tmp_process.pixel_format = convert_vdu_pf_to_cp_pf(vpf);
	convert_vdu_rect_to_cp_rect(&tmp_process.vdu_rect, &rect);

	if (scale_rect) {
		convert_vdu_rect_to_cp_rect(&tmp_process.image_rect, scale_rect);
	}

	//处理process
	tmp_ret_int = cp_get_option_module(tmp_vdu_app->vdu_func,
		cp_qt_svg_process_option_get_rect_pixel, &tmp_process);
	if (tmp_ret_int < 0) {
		return tmp_ret_int;
	}

	return tmp_process.image_length;
}

int cp_vdu_init(cp_vdu_t *vdu, const cp_vdu_info_t *vdu_info)								/*模块创建接口，表示创建一个模块*/
{
	return cp_vdu_status_success;
}

int cp_vdu_open(cp_vdu_t *vdu, const cp_vdu_info_t *vdu_info)								/*模块打开运行接口，在模块init之后，会被调用*/
{
	return cp_vdu_status_success;
}

int cp_vdu_read(cp_vdu_t *vdu, char **buf, int len, int flag)								/*读取模块数据，flag为读取模式的扩展标志。默认为0，其他为预留*/
{
	return cp_vdu_status_success;
}

int cp_vdu_write(cp_vdu_t *vdu, const char **buf, int len, int flag)						/*写模块数据，flag为写模式的扩展标志。默认为0，其他为预留*/
{
	return cp_vdu_status_success;
}

int cp_vdu_close(cp_vdu_t *vdu)																/*关闭模块*/
{
	return cp_vdu_status_success;
}

int cp_vdu_exit(cp_vdu_t *vdu)																/*退出模块*/
{
	return cp_vdu_status_success;
}

int cp_vdu_set_option(cp_vdu_t *vdu, int optname, const void* optval)						/*设置模块参数*/
{
	return cp_vdu_status_success;
}

int cp_vdu_get_option(cp_vdu_t *vdu, int optname, void* optval)								/*获取模块参数*/
{
	return cp_vdu_status_success;
}


cp_vdu_channel_t* cp_vdu_create_channel(cp_vdu_t *vdu, cp_vdu_channel_type_e channel_type)
{
	cp_int32_t						tmp_ret_int = 0;
	cp_vdu_app_t					*tmp_vdu_app = CP_NULL;
	cp_vdu_channel_t				*tmp_vdu_channel = CP_NULL;
	cp_vdu_channel_process_t		tmp_channel_process = { 0, };



	if (!vdu || !vdu->app) {
		return CP_NULL;
	}
	tmp_vdu_app = (cp_vdu_app_t *)(vdu->app);

	//初始化channel process struct
	cp_vdu_channel_process_struct_set_type(&tmp_channel_process);

	//创建channel
	tmp_ret_int = cp_set_option_module(tmp_vdu_app->vdu_func,
		cp_qt_svg_process_option_create_channel, &tmp_channel_process);
	if (tmp_ret_int) {
		return CP_NULL;
	}

	//创建cp_vdu_channel_t内容
	tmp_vdu_channel = (cp_vdu_channel_t *)cp_malloc(cp_sizeof(cp_vdu_channel_t));
	if (!tmp_vdu_channel) {
		return CP_NULL;
	}

	//设置cp_vdu_channel_t的数据内容
	cp_memset(tmp_vdu_channel, 0, cp_sizeof(cp_vdu_channel_t));
	tmp_vdu_channel->app = vdu->app;
	tmp_vdu_channel->vdu = vdu;
	tmp_vdu_channel->channel = tmp_channel_process.channel;
	tmp_vdu_channel->index = tmp_channel_process.index;

	return tmp_vdu_channel;
}

int cp_vdu_destroy_all_channels(cp_vdu_t *vdu)
{
	cp_int32_t						tmp_ret_int = 0;
	cp_vdu_app_t					*tmp_vdu_app = CP_NULL;
	cp_vdu_channel_t				*tmp_vdu_channel = CP_NULL;
	cp_vdu_process_t				tmp_process = { 0, };



	if (!vdu || !vdu->app) {
		return cp_vdu_status_null_pointer;
	}
	tmp_vdu_app = (cp_vdu_app_t *)(vdu->app);

	//初始化process struct
	fill_vdu_to_process_struct(&tmp_process, vdu);

	//销毁所有通道
	tmp_ret_int = cp_set_option_module(tmp_vdu_app->vdu_func,
		cp_qt_svg_process_option_destroy_all_channel, &tmp_process);
	if (tmp_ret_int) {
		return tmp_ret_int;
	}
	
	return cp_vdu_status_success;
}

int cp_vdu_destroy_channel(cp_vdu_channel_t *vdu_channel)
{
	cp_int32_t						tmp_ret_int = 0;
	cp_vdu_app_t					*tmp_vdu_app = CP_NULL;
	cp_vdu_channel_t				*tmp_vdu_channel = CP_NULL;
	cp_vdu_channel_process_t		tmp_channel_process = { 0, };



	if (!vdu_channel || !vdu_channel->app) {
		return cp_vdu_status_null_pointer;
	}
	tmp_vdu_app = (cp_vdu_app_t *)(vdu_channel->app);

	//初始化channel process struct
	fill_vdu_channel_to_process_struct(&tmp_channel_process, vdu_channel);

	//创建channel
	tmp_ret_int = cp_set_option_module(tmp_vdu_app->vdu_func,
		cp_qt_svg_process_option_destroy_channel, &tmp_channel_process);
	if (tmp_ret_int) {
		return tmp_ret_int;
	}

	//销毁cp_vdu_channel_t内容
	cp_free(vdu_channel);

	return cp_vdu_status_success;
}

cp_vdu_status_e cp_vdu_channel_get_status(cp_vdu_channel_t *vdu_channel)
{
	cp_int32_t						tmp_ret_int = 0;
	cp_vdu_app_t					*tmp_vdu_app = CP_NULL;
	cp_vdu_channel_process_t		tmp_channel_process = { 0, };



	if (!vdu_channel || !vdu_channel->app) {
		return cp_vdu_status_null_pointer;
	}
	tmp_vdu_app = (cp_vdu_app_t *)(vdu_channel->app);

	//初始化channel process struct
	fill_vdu_channel_to_process_struct(&tmp_channel_process, vdu_channel);

	//创建channel
	tmp_ret_int = cp_get_option_module(tmp_vdu_app->vdu_func,
		cp_qt_svg_channel_option_get_status, &tmp_channel_process);
	if (tmp_ret_int) {
		return tmp_ret_int;
	}

	return (cp_vdu_status_e)(tmp_channel_process.error_no);
}

int cp_vdu_insert_channel(cp_vdu_t *vdu, cp_vdu_channel_t *vdu_channel)
{
	cp_int32_t						tmp_ret_int = 0;
	cp_vdu_app_t					*tmp_vdu_app = CP_NULL;
	cp_vdu_channel_process_t		tmp_channel_process = { 0, };



	if (!vdu_channel || !vdu_channel->app) {
		return cp_vdu_status_null_pointer;
	}
	tmp_vdu_app = (cp_vdu_app_t *)(vdu_channel->app);

	//初始化channel process struct
	fill_vdu_channel_to_process_struct(&tmp_channel_process, vdu_channel);

	//处理channel
	tmp_ret_int = cp_set_option_module(tmp_vdu_app->vdu_func,
		cp_qt_svg_channel_option_set_insert_channel, &tmp_channel_process);
	if (tmp_ret_int) {
		return tmp_ret_int;
	}

	return tmp_ret_int;
}

int cp_vdu_remove_channel(cp_vdu_t *vdu, cp_vdu_channel_t *vdu_channel)
{
	cp_int32_t						tmp_ret_int = 0;
	cp_vdu_app_t					*tmp_vdu_app = CP_NULL;
	cp_vdu_channel_process_t		tmp_channel_process = { 0, };



	if (!vdu_channel || !vdu_channel->app) {
		return cp_vdu_status_null_pointer;
	}
	tmp_vdu_app = (cp_vdu_app_t *)(vdu_channel->app);

	//初始化channel process struct
	fill_vdu_channel_to_process_struct(&tmp_channel_process, vdu_channel);

	//处理channel
	tmp_ret_int = cp_set_option_module(tmp_vdu_app->vdu_func,
		cp_qt_svg_channel_option_set_remove_channel, &tmp_channel_process);
	if (tmp_ret_int) {
		return tmp_ret_int;
	}

	return tmp_ret_int;
}

int cp_vdu_channel_set_index(cp_vdu_channel_t *vdu_channel, const int index)
{
	cp_int32_t						tmp_ret_int = 0;
	cp_vdu_app_t					*tmp_vdu_app = CP_NULL;
	cp_vdu_channel_process_t		tmp_channel_process = { 0, };



	if (!vdu_channel || !vdu_channel->app) {
		return cp_vdu_status_null_pointer;
	}
	tmp_vdu_app = (cp_vdu_app_t *)(vdu_channel->app);

	//初始化channel process struct
	fill_vdu_channel_to_process_struct(&tmp_channel_process, vdu_channel);
	tmp_channel_process.index = index;

	//处理channel
	tmp_ret_int = cp_set_option_module(tmp_vdu_app->vdu_func,
		cp_qt_svg_channel_option_set_channel_index, &tmp_channel_process);
	if (tmp_ret_int) {
		return tmp_ret_int;
	}

	//更新channel的index
	vdu_channel->index = tmp_channel_process.index;

	return tmp_ret_int;
}

int cp_vdu_channel_get_index(cp_vdu_channel_t *vdu_channel)
{
	cp_int32_t						tmp_ret_int = 0;
	cp_vdu_app_t					*tmp_vdu_app = CP_NULL;
	cp_vdu_channel_process_t		tmp_channel_process = { 0, };



	if (!vdu_channel || !vdu_channel->app) {
		return cp_vdu_status_null_pointer;
	}
	tmp_vdu_app = (cp_vdu_app_t *)(vdu_channel->app);

	//初始化channel process struct
	fill_vdu_channel_to_process_struct(&tmp_channel_process, vdu_channel);

	//处理channel
	tmp_ret_int = cp_set_option_module(tmp_vdu_app->vdu_func,
		cp_qt_svg_channel_option_get_channel_index, &tmp_channel_process);
	if (tmp_ret_int) {
		return -2;
	}

	return tmp_channel_process.index;
}

int cp_vdu_channel_set_vector_stream(cp_vdu_channel_t *vdu_channel,
	cp_vdu_vector_stream_type_e vs_type, const char *buf, const int len)
{
	cp_int32_t						tmp_ret_int = 0;
	cp_vdu_app_t					*tmp_vdu_app = CP_NULL;
	cp_vdu_channel_process_t		tmp_channel_process = { 0, };



	if (!vdu_channel || !vdu_channel->app) {
		return cp_vdu_status_null_pointer;
	}
	tmp_vdu_app = (cp_vdu_app_t *)(vdu_channel->app);

	//初始化channel process struct
	fill_vdu_channel_to_process_struct(&tmp_channel_process, vdu_channel);
	tmp_channel_process.buf = (cp_char_t *)buf;
	tmp_channel_process.buf_length = len;

	//处理channel
	tmp_ret_int = cp_set_option_module(tmp_vdu_app->vdu_func,
		cp_qt_svg_channel_option_set_vector_stream, &tmp_channel_process);
	if (tmp_ret_int) {
		return tmp_ret_int;
	}

	return tmp_ret_int;
}

int cp_vdu_channel_set_roi(cp_vdu_channel_t *vdu_channel, cp_vdu_rect_t rect)
{
	cp_int32_t						tmp_ret_int = 0;
	cp_vdu_app_t					*tmp_vdu_app = CP_NULL;
	cp_vdu_channel_process_t		tmp_channel_process = { 0, };



	if (!vdu_channel || !vdu_channel->app) {
		return cp_vdu_status_null_pointer;
	}
	tmp_vdu_app = (cp_vdu_app_t *)(vdu_channel->app);

	//初始化channel process struct
	fill_vdu_channel_to_process_struct(&tmp_channel_process, vdu_channel);
	convert_vdu_rect_to_cp_rect(&tmp_channel_process.vdu_rect, &rect);

	//处理channel
	tmp_ret_int = cp_set_option_module(tmp_vdu_app->vdu_func,
		cp_qt_svg_channel_option_set_roi, &tmp_channel_process);
	if (tmp_ret_int) {
		return tmp_ret_int;
	}

	return tmp_ret_int;
}

int cp_vdu_channel_set_roi_parameters(cp_vdu_channel_t *vdu_channel, int x, int y, int width, int height)
{
	cp_vdu_rect_t				tmp_rect = { 0, };


	tmp_rect.x = x;
	tmp_rect.y = y;
	tmp_rect.width = width;
	tmp_rect.height = height;

	return cp_vdu_channel_set_roi(vdu_channel, tmp_rect);
}

int cp_vdu_channel_get_roi(cp_vdu_channel_t *vdu_channel, cp_vdu_rect_t *roi_rect)
{
	cp_int32_t								tmp_ret_int = 0;
	cp_vdu_app_t							*tmp_vdu_app = CP_NULL;
	cp_vdu_channel_process_t				tmp_channel_process = { 0, };



	if (!vdu_channel || !vdu_channel->app || !roi_rect) {
		return cp_vdu_status_null_pointer;
	}
	tmp_vdu_app = (cp_vdu_app_t *)(vdu_channel->app);

	//初始化channel process struct
	fill_vdu_channel_to_process_struct(&tmp_channel_process, vdu_channel);

	//处理channel
	tmp_ret_int = cp_set_option_module(tmp_vdu_app->vdu_func,
		cp_qt_svg_channel_option_get_roi, &tmp_channel_process);
	if (tmp_ret_int) {
		return tmp_ret_int;
	}
	convert_cp_rect_to_vdu_rect(roi_rect, &tmp_channel_process.vdu_rect);

	return tmp_ret_int;
}

int cp_vdu_channel_clear_roi(cp_vdu_channel_t *vdu_channel)
{
	cp_int32_t								tmp_ret_int = 0;
	cp_vdu_app_t							*tmp_vdu_app = CP_NULL;
	cp_vdu_channel_process_t				tmp_channel_process = { 0, };



	if (!vdu_channel || !vdu_channel->app) {
		return cp_vdu_status_null_pointer;
	}
	tmp_vdu_app = (cp_vdu_app_t *)(vdu_channel->app);

	//初始化channel process struct
	fill_vdu_channel_to_process_struct(&tmp_channel_process, vdu_channel);

	//处理channel
	tmp_ret_int = cp_set_option_module(tmp_vdu_app->vdu_func,
		cp_qt_svg_channel_option_clear_roi, &tmp_channel_process);
	if (tmp_ret_int) {
		return tmp_ret_int;
	}

	return tmp_ret_int;
}

int cp_vdu_channel_get_roi_pixel(cp_vdu_channel_t *vdu_channel,
	char *buf, int len,
	cp_vdu_pixel_format_e vpf,
	cp_vdu_rect_t *scale_rect)
{
	cp_int32_t						tmp_ret_int = 0;
	cp_vdu_app_t					*tmp_vdu_app = CP_NULL;
	cp_vdu_channel_process_t		tmp_channel_process = { 0, };



	if (!vdu_channel || !vdu_channel->app) {
		return cp_vdu_status_null_pointer;
	}
	tmp_vdu_app = (cp_vdu_app_t *)(vdu_channel->app);

	//初始化channel process struct
	fill_vdu_channel_to_process_struct(&tmp_channel_process, vdu_channel);
	tmp_channel_process.buf = buf;
	tmp_channel_process.buf_length = len;
	tmp_channel_process.pixel_format = convert_vdu_pf_to_cp_pf(vpf);

	if (scale_rect) {
		convert_vdu_rect_to_cp_rect(&tmp_channel_process.image_rect, scale_rect);
	}

	//处理channel
	tmp_ret_int = cp_get_option_module(tmp_vdu_app->vdu_func,
		cp_qt_svg_channel_option_get_roi_pixel, &tmp_channel_process);
	if (tmp_ret_int < 0) {
		return tmp_ret_int;
	}

	return tmp_channel_process.image_length;
}

int cp_vdu_channel_get_roi_pixel_by_image_info(
	cp_vdu_channel_t *vdu_channel,
	cp_vdu_image_info_t *image_info)
{
	cp_int32_t						tmp_ret_int = 0;
	cp_vdu_app_t					*tmp_vdu_app = CP_NULL;
	cp_vdu_channel_process_t		tmp_channel_process = { 0, };



	if (!vdu_channel || !vdu_channel->app || !image_info) {
		return cp_vdu_status_null_pointer;
	}

	if (!image_info->buf || !image_info->buf_length) {
		return cp_vdu_status_invalid_parametes;
	}

	tmp_vdu_app = (cp_vdu_app_t *)(vdu_channel->app);

	//初始化channel process struct
	fill_vdu_channel_to_process_struct(&tmp_channel_process, vdu_channel);
	tmp_channel_process.buf = image_info->buf;
	tmp_channel_process.buf_length = image_info->buf_length;
	tmp_channel_process.pixel_format = convert_vdu_pf_to_cp_pf(image_info->vpf);
	convert_vdu_rect_to_cp_rect(&tmp_channel_process.image_rect, &image_info->image_rect);

	//转换为cp_codec_pixel_format定义的格式
	if (cp_codec_pixel_format_none == tmp_channel_process.pixel_format) {
		cp_log_printf("unsupport pixel_format[%d] error.", image_info->vpf);
		return cp_vdu_status_unsupport_pixel_format;
	}

	//处理channel
	tmp_ret_int = cp_get_option_module(tmp_vdu_app->vdu_func,
		cp_qt_svg_channel_option_get_roi_pixel, &tmp_channel_process);
	if (tmp_ret_int < 0) {
		return tmp_ret_int;
	}
	image_info->image_length = tmp_ret_int;

	return tmp_channel_process.image_length;
}

int cp_vdu_channel_get_rect_pixel(cp_vdu_channel_t *vdu_channel,
	char *buf, int len,
	cp_vdu_pixel_format_e vpf,
	cp_vdu_rect_t rect,
	cp_vdu_rect_t *scale_rect)
{
	cp_int32_t						tmp_ret_int = 0;
	cp_vdu_app_t					*tmp_vdu_app = CP_NULL;
	cp_vdu_channel_process_t		tmp_channel_process = { 0, };



	if (!vdu_channel || !vdu_channel->app) {
		return cp_vdu_status_null_pointer;
	}
	tmp_vdu_app = (cp_vdu_app_t *)(vdu_channel->app);

	//初始化channel process struct
	fill_vdu_channel_to_process_struct(&tmp_channel_process, vdu_channel);
	tmp_channel_process.buf = buf;
	tmp_channel_process.buf_length = len;
	tmp_channel_process.pixel_format = convert_vdu_pf_to_cp_pf(vpf);
	convert_vdu_rect_to_cp_rect(&tmp_channel_process.vdu_rect, &rect);

	if (scale_rect) {
		convert_vdu_rect_to_cp_rect(&tmp_channel_process.image_rect, scale_rect);
	}

	//处理channel
	tmp_ret_int = cp_get_option_module(tmp_vdu_app->vdu_func,
		cp_qt_svg_channel_option_get_rect_pixel, &tmp_channel_process);
	if (tmp_ret_int < 0) {
		return tmp_ret_int;
	}

	return tmp_channel_process.image_length;
}

int cp_vdu_channel_get_rect_pixel_by_image_info(
	cp_vdu_channel_t *vdu_channel,
	cp_vdu_image_info_t *image_info)
{
	cp_int32_t						tmp_ret_int = 0;
	cp_vdu_app_t					*tmp_vdu_app = CP_NULL;
	cp_vdu_channel_process_t		tmp_channel_process = { 0, };



	if (!vdu_channel || !vdu_channel->app) {
		return cp_vdu_status_null_pointer;
	}
	tmp_vdu_app = (cp_vdu_app_t *)(vdu_channel->app);

	//初始化channel process struct
	fill_vdu_channel_to_process_struct(&tmp_channel_process, vdu_channel);
	tmp_channel_process.buf = image_info->buf;
	tmp_channel_process.buf_length = image_info->buf_length;
	tmp_channel_process.pixel_format = convert_vdu_pf_to_cp_pf(image_info->vpf);
	convert_vdu_rect_to_cp_rect(&tmp_channel_process.vdu_rect, &image_info->vdu_rect);
	convert_vdu_rect_to_cp_rect(&tmp_channel_process.image_rect, &image_info->image_rect);

	//转换为cp_codec_pixel_format定义的格式
	if (cp_codec_pixel_format_none == tmp_channel_process.pixel_format) {
		cp_log_printf("unsupport pixel_format[%d] error.", image_info->vpf);
		return cp_vdu_status_unsupport_pixel_format;
	}

	//处理channel
	tmp_ret_int = cp_get_option_module(tmp_vdu_app->vdu_func,
		cp_qt_svg_channel_option_get_rect_pixel, &tmp_channel_process);
	if (tmp_ret_int < 0) {
		return tmp_ret_int;
	}
	image_info->image_length = tmp_ret_int;

	return tmp_channel_process.image_length;
}







//////////////////////////////////////////////////////////////////////////
//cp_vdu_media_info处理函数
//////////////////////////////////////////////////////////////////////////

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
* 参    数: cp_vdu_image_info_t * vdu_image						[in/out]参数说明
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
int cp_vdu_image_info_clear(cp_vdu_image_info_t *vdu_image)
{
	if (!vdu_image) {
		return cp_vdu_status_null_pointer;
	}

	cp_memset(vdu_image, 0, cp_sizeof(cp_vdu_image_info_t));

	return 0;
}

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
* 参    数: cp_vdu_image_info_t * vdu_image						[in/out]参数说明
* 参    数: cp_vdu_pixel_format_e vpf						[in/out]参数说明
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
int cp_vdu_image_info_set_pixel_format(cp_vdu_image_info_t *vdu_image, cp_vdu_pixel_format_e vpf)
{
	if (!vdu_image) {
		return cp_vdu_status_null_pointer;
	}

	vdu_image->vpf = vpf;

	return 0;
}

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
* 参    数: cp_vdu_image_info_t * vdu_image						[in/out]参数说明
*
* 返 回 值: cp_extern cp_vdu_pixel_format_e
*           0  : 成功
*         非0  : 失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2018-2-25 11:33:23
********************************************************************************/
cp_vdu_pixel_format_e cp_vdu_image_info_get_pixel_format(cp_vdu_image_info_t *vdu_image)
{
	if (!vdu_image) {
		return cp_vdu_pixel_format_end;
	}

	return vdu_image->vpf;
}

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
* 参    数: cp_vdu_image_info_t * vdu_image						[in/out]参数说明
* 参    数: cp_vdu_rect_t rect						[in/out]参数说明
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
int cp_vdu_image_info_set_vdu_rect(cp_vdu_image_info_t *vdu_image, cp_vdu_rect_t vdu_rect)
{
	if (!vdu_image) {
		return cp_vdu_status_null_pointer;
	}

	vdu_image->vdu_rect = vdu_rect;

	return 0;
}

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
* 参    数: cp_vdu_image_info_t * vdu_image						[in/out]参数说明
* 参    数: int x						[in/out]参数说明
* 参    数: int y						[in/out]参数说明
* 参    数: int width						[in/out]参数说明
* 参    数: int height						[in/out]参数说明
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
int cp_vdu_image_info_set_vdu_rect_parameters(cp_vdu_image_info_t *vdu_image, int x, int y, int width, int height)
{
	if (!vdu_image) {
		return cp_vdu_status_null_pointer;
	}

	vdu_image->vdu_rect.x = x;
	vdu_image->vdu_rect.y = y;
	vdu_image->vdu_rect.width = width;
	vdu_image->vdu_rect.height = height;

	return 0;
}

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
* 参    数: cp_vdu_image_info_t * vdu_image						[in/out]参数说明
*
* 返 回 值: cp_extern cp_vdu_rect_t
*           0  : 成功
*         非0  : 失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2018-2-25 11:34:29
********************************************************************************/
cp_vdu_rect_t cp_vdu_image_info_get_vdu_rect(cp_vdu_image_info_t *vdu_image)
{
	return vdu_image->vdu_rect;
}

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
* 参    数: cp_vdu_image_info_t * vdu_image						[in/out]参数说明
* 参    数: int width						[in/out]参数说明
* 参    数: int height						[in/out]参数说明
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
int cp_vdu_image_info_set_image_size(cp_vdu_image_info_t *vdu_image, int width, int height)
{
	if (!vdu_image) {
		return cp_vdu_status_null_pointer;
	}

	vdu_image->image_rect.x = 0;
	vdu_image->image_rect.y = 0;
	vdu_image->image_rect.width = width;
	vdu_image->image_rect.height = height;

	return 0;
}

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
* 参    数: cp_vdu_image_info_t * vdu_image						[in/out]参数说明
*
* 返 回 值: cp_extern cp_vdu_rect_t
*           0  : 成功
*         非0  : 失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2018-2-25 11:37:12
********************************************************************************/
cp_vdu_rect_t cp_vdu_image_info_get_image_rect(cp_vdu_image_info_t *vdu_image)
{
	return vdu_image->image_rect;
}

