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



int cp_vdu_init(cp_vdu_t *vdu, const cp_vdu_info_t *vdu_info);								/*ģ�鴴���ӿڣ���ʾ����һ��ģ��*/
int cp_vdu_open(cp_vdu_t *vdu, const cp_vdu_info_t *vdu_info);								/*ģ������нӿڣ���ģ��init֮�󣬻ᱻ����*/
int cp_vdu_read(cp_vdu_t *vdu, char **buf, int len, int flag);								/*��ȡģ�����ݣ�flagΪ��ȡģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��*/
int cp_vdu_write(cp_vdu_t *vdu, const char **buf, int len, int flag);						/*дģ�����ݣ�flagΪдģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��*/
int cp_vdu_close(cp_vdu_t *vdu);															/*�ر�ģ��*/
int cp_vdu_exit(cp_vdu_t *vdu);																/*�˳�ģ��*/
int cp_vdu_set_option(cp_vdu_t *vdu, int optname, const void* optval);						/*����ģ�����*/
int cp_vdu_get_option(cp_vdu_t *vdu, int optname, void* optval);							/*��ȡģ�����*/




/************************************************************************/
/* ����app info����                                                      */
/************************************************************************/
CP_EXTERN_GLOBAL_APP_INFO();

//ȫ��app��������
CP_EXTERN_APP_PARAMETER();

//����һ��cp_vdu_t����
cp_vdu_t* cp_vdu_create() {
	cp_vdu_t					*tmp_vdu = CP_NULL;
	cp_vdu_app_t				*tmp_vdu_app = CP_NULL;
	cp_app_info_t				tmp_vdu_info = { 0, };
	cp_int32_t					tmp_ret_int = 0;
	char						tmp_buf[CP_APP_DEFAULT_BUFFER_LENGTH] = { 0, };


	//
	/********************************************************************************************************************/
	/* ���ﶨ��һЩȫ�ֱ����������������£�																					*/
	/*cp_app_info_t		        cp_global_app_info = { type, name, version, description, NULL, 0, NULL };				*/
	/*cp_app_create_handle	    cp_global_app_create_handle = create_handle;											*/
	/*cp_app_destroy_handle		cp_global_app_destroy_handle = destroy_handle;											*/
	/********************************************************************************************************************/
	cp_app_register(CP_VDU_TYPE, CP_VDU_VAR, cp_vdu_version, CP_VDU_VER,
		(cp_app_create_handle)cp_vdu_app_create, (cp_app_destroy_handle)cp_vdu_app_destroy);

	//���ﶨ�������ʾ�Ƿ�������־
#ifdef CP_VDU_USED_LOG_SYSTEM
#if defined WIN32
	CP_APP_ENTRY_CONFIG_PATH("E:\\project_work\\project\\css_workspace\\cp_player\\app\\vector_data_unit\\vdu_sample_demo\\configs\\css.conf");
#endif 
#endif // CP_VDU_USED_LOG_SYSTEM

	//����ͨ��
	tmp_vdu = cp_malloc(sizeof(cp_vdu_t));
	if (!tmp_vdu) {
		printf("cp_vdu_create() error reason: malloc failed!");
		return CP_NULL;
	}
	else {
		cp_memset(tmp_vdu, 0, sizeof(cp_vdu_t));
	}

	tmp_vdu_info = cp_global_app_info;

	//�����豸
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

	/*��ʼ���豸������
	*��ȡ�豸�����ļ�
	*��־ģ��
	*��ʼ��TCP/UDP��������
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

	//�����豸
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

	//�����豸��Ϣ
	tmp_vdu->app = tmp_vdu_app;

	return tmp_vdu;
}

//����cp_vdu����
cp_int32_t cp_vdu_destroy(cp_vdu_t *vdu) {
	cp_int32_t					tmp_ret_int = 0;
	cp_vdu_app_t				*tmp_vdu_app = CP_NULL;
	char						tmp_buf[CP_APP_DEFAULT_BUFFER_LENGTH] = { 0, };


	if (!vdu) {
		return cp_vdu_status_null_pointer;
	}

	//���app����������
	if (vdu->app) {
		tmp_vdu_app = (cp_vdu_app_t *)vdu->app;

		//ֹͣvdu
		tmp_ret_int = tmp_vdu_app->stop((cp_app_t *)tmp_vdu_app);
		if (tmp_ret_int) {
			cp_log_printf("stop app failed!");
			return -2;
		}
		else {
			cp_log_printf("stop app success!");
		}

		//����vdu
		tmp_ret_int = cp_global_app_destroy_handle((cp_app_t *)tmp_vdu_app);
		if (tmp_ret_int) {
			cp_log_printf("destroy app failed!");
			return -2;
		}
		else {
			cp_log_printf("destroy app success!");
		}
	}

	//�ͷ�vdu��Դ
	cp_free(vdu);

	return cp_vdu_status_success;
}

//��ȡ�汾��Ϣ
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

//��ȡvdu��״̬��
cp_vdu_status_e cp_vdu_get_status(cp_vdu_t *vdu)
{
	cp_int32_t						tmp_ret_int = 0;
	cp_vdu_app_t					*tmp_vdu_app = CP_NULL;
	cp_vdu_process_t				tmp_process = { 0, };



	if (!vdu || !vdu->app) {
		return cp_vdu_status_null_pointer;
	}
	tmp_vdu_app = (cp_vdu_app_t *)(vdu->app);

	//��ʼ��process struct
	fill_vdu_to_process_struct(&tmp_process, vdu);

	//����channel
	tmp_ret_int = cp_get_option_module(tmp_vdu_app->vdu_func,
		cp_qt_svg_process_option_get_status, &tmp_process);
	if (tmp_ret_int) {
		return tmp_ret_int;
	}

	return (cp_vdu_status_e)(tmp_process.error_no);
}

//����������Ϣ
int cp_vdu_set_coordinate(cp_vdu_t *vdu, cp_vdu_coordinate_t coordinate)
{
	cp_int32_t						tmp_ret_int = 0;
	cp_vdu_app_t					*tmp_vdu_app = CP_NULL;
	cp_vdu_process_t				tmp_process = { 0, };



	if (!vdu || !vdu->app) {
		return cp_vdu_status_null_pointer;
	}
	tmp_vdu_app = (cp_vdu_app_t *)(vdu->app);

	//��ʼ��process struct
	fill_vdu_to_process_struct(&tmp_process, vdu);
	tmp_process.coordinate.x = coordinate.x;
	tmp_process.coordinate.y = coordinate.y;
	tmp_process.coordinate.z = coordinate.z;

	//����coordinate����
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

	//��ʼ��process struct
	fill_vdu_to_process_struct(&tmp_process, vdu);

	//��ȡcoordinate����
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
* ��Ȩ����: fz & novigo
*
* ��������: cp_vdu_open_debug_mode
*
* ����ȫ��: cp_vdu_open_debug_mode
*
* ��������: public
*
* ����˵��: ��ʾ�Ƿ���������ģʽ
*
* ��    ��: cp_vdu_t * vdu						[in/out]����˵��
* ��    ��: char * path						[in/out]����˵��
*
* �� �� ֵ: cp_extern int
*           0  : �ɹ�
*         ��0  : ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2018-2-28 17:21:57
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

	//��ʼ��process struct
	fill_vdu_to_process_struct(&tmp_process, vdu);
	tmp_process.is_debug_mode = cp_true;
	tmp_process.debug_path = path;

	//����debug ��Ϣ
	tmp_ret_int = cp_set_option_module(tmp_vdu_app->vdu_func,
		cp_qt_svg_process_option_set_debug_info, &tmp_process);
	if (tmp_ret_int) {
		return tmp_ret_int;
	}

	return tmp_ret_int;
}

/*******************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: cp_vdu_close_debug_mode
*
* ����ȫ��: cp_vdu_close_debug_mode
*
* ��������: public
*
* ����˵��: ��ʾ�رյ���ģʽ
*
* ��    ��: cp_vdu_t * vdu						[in/out]����˵��
*
* �� �� ֵ: cp_extern int
*           0  : �ɹ�
*         ��0  : ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2018-2-28 17:22:20
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

	//��ʼ��process struct
	fill_vdu_to_process_struct(&tmp_process, vdu);
	tmp_process.is_debug_mode = cp_false;

	//����debug ��Ϣ
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

	//��ʼ��process struct
	fill_vdu_to_process_struct(&tmp_process, vdu);
	convert_vdu_rect_to_cp_rect(&tmp_process.vdu_rect, &rect);

	//����roi����
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

	//��ʼ��process struct
	fill_vdu_to_process_struct(&tmp_process, vdu);

	//��ȡroi����
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

	//��ʼ��process struct
	fill_vdu_to_process_struct(&tmp_process, vdu);

	//��ȡroi����
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

	//��ʼ��process struct
	fill_vdu_to_process_struct(&tmp_process, vdu);

	tmp_process.buf = buf;
	tmp_process.buf_length = len;
	tmp_process.pixel_format = convert_vdu_pf_to_cp_pf(vpf);

	if (scale_rect) {
		convert_vdu_rect_to_cp_rect(&tmp_process.image_rect, scale_rect);
	}

	//����process
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

	//��ʼ��process struct
	fill_vdu_to_process_struct(&tmp_process, vdu);

	tmp_process.buf = buf;
	tmp_process.buf_length = len;
	tmp_process.pixel_format = convert_vdu_pf_to_cp_pf(vpf);
	convert_vdu_rect_to_cp_rect(&tmp_process.vdu_rect, &rect);

	if (scale_rect) {
		convert_vdu_rect_to_cp_rect(&tmp_process.image_rect, scale_rect);
	}

	//����process
	tmp_ret_int = cp_get_option_module(tmp_vdu_app->vdu_func,
		cp_qt_svg_process_option_get_rect_pixel, &tmp_process);
	if (tmp_ret_int < 0) {
		return tmp_ret_int;
	}

	return tmp_process.image_length;
}

int cp_vdu_init(cp_vdu_t *vdu, const cp_vdu_info_t *vdu_info)								/*ģ�鴴���ӿڣ���ʾ����һ��ģ��*/
{
	return cp_vdu_status_success;
}

int cp_vdu_open(cp_vdu_t *vdu, const cp_vdu_info_t *vdu_info)								/*ģ������нӿڣ���ģ��init֮�󣬻ᱻ����*/
{
	return cp_vdu_status_success;
}

int cp_vdu_read(cp_vdu_t *vdu, char **buf, int len, int flag)								/*��ȡģ�����ݣ�flagΪ��ȡģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��*/
{
	return cp_vdu_status_success;
}

int cp_vdu_write(cp_vdu_t *vdu, const char **buf, int len, int flag)						/*дģ�����ݣ�flagΪдģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��*/
{
	return cp_vdu_status_success;
}

int cp_vdu_close(cp_vdu_t *vdu)																/*�ر�ģ��*/
{
	return cp_vdu_status_success;
}

int cp_vdu_exit(cp_vdu_t *vdu)																/*�˳�ģ��*/
{
	return cp_vdu_status_success;
}

int cp_vdu_set_option(cp_vdu_t *vdu, int optname, const void* optval)						/*����ģ�����*/
{
	return cp_vdu_status_success;
}

int cp_vdu_get_option(cp_vdu_t *vdu, int optname, void* optval)								/*��ȡģ�����*/
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

	//��ʼ��channel process struct
	cp_vdu_channel_process_struct_set_type(&tmp_channel_process);

	//����channel
	tmp_ret_int = cp_set_option_module(tmp_vdu_app->vdu_func,
		cp_qt_svg_process_option_create_channel, &tmp_channel_process);
	if (tmp_ret_int) {
		return CP_NULL;
	}

	//����cp_vdu_channel_t����
	tmp_vdu_channel = (cp_vdu_channel_t *)cp_malloc(cp_sizeof(cp_vdu_channel_t));
	if (!tmp_vdu_channel) {
		return CP_NULL;
	}

	//����cp_vdu_channel_t����������
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

	//��ʼ��process struct
	fill_vdu_to_process_struct(&tmp_process, vdu);

	//��������ͨ��
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

	//��ʼ��channel process struct
	fill_vdu_channel_to_process_struct(&tmp_channel_process, vdu_channel);

	//����channel
	tmp_ret_int = cp_set_option_module(tmp_vdu_app->vdu_func,
		cp_qt_svg_process_option_destroy_channel, &tmp_channel_process);
	if (tmp_ret_int) {
		return tmp_ret_int;
	}

	//����cp_vdu_channel_t����
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

	//��ʼ��channel process struct
	fill_vdu_channel_to_process_struct(&tmp_channel_process, vdu_channel);

	//����channel
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

	//��ʼ��channel process struct
	fill_vdu_channel_to_process_struct(&tmp_channel_process, vdu_channel);

	//����channel
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

	//��ʼ��channel process struct
	fill_vdu_channel_to_process_struct(&tmp_channel_process, vdu_channel);

	//����channel
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

	//��ʼ��channel process struct
	fill_vdu_channel_to_process_struct(&tmp_channel_process, vdu_channel);
	tmp_channel_process.index = index;

	//����channel
	tmp_ret_int = cp_set_option_module(tmp_vdu_app->vdu_func,
		cp_qt_svg_channel_option_set_channel_index, &tmp_channel_process);
	if (tmp_ret_int) {
		return tmp_ret_int;
	}

	//����channel��index
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

	//��ʼ��channel process struct
	fill_vdu_channel_to_process_struct(&tmp_channel_process, vdu_channel);

	//����channel
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

	//��ʼ��channel process struct
	fill_vdu_channel_to_process_struct(&tmp_channel_process, vdu_channel);
	tmp_channel_process.buf = (cp_char_t *)buf;
	tmp_channel_process.buf_length = len;

	//����channel
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

	//��ʼ��channel process struct
	fill_vdu_channel_to_process_struct(&tmp_channel_process, vdu_channel);
	convert_vdu_rect_to_cp_rect(&tmp_channel_process.vdu_rect, &rect);

	//����channel
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

	//��ʼ��channel process struct
	fill_vdu_channel_to_process_struct(&tmp_channel_process, vdu_channel);

	//����channel
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

	//��ʼ��channel process struct
	fill_vdu_channel_to_process_struct(&tmp_channel_process, vdu_channel);

	//����channel
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

	//��ʼ��channel process struct
	fill_vdu_channel_to_process_struct(&tmp_channel_process, vdu_channel);
	tmp_channel_process.buf = buf;
	tmp_channel_process.buf_length = len;
	tmp_channel_process.pixel_format = convert_vdu_pf_to_cp_pf(vpf);

	if (scale_rect) {
		convert_vdu_rect_to_cp_rect(&tmp_channel_process.image_rect, scale_rect);
	}

	//����channel
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

	//��ʼ��channel process struct
	fill_vdu_channel_to_process_struct(&tmp_channel_process, vdu_channel);
	tmp_channel_process.buf = image_info->buf;
	tmp_channel_process.buf_length = image_info->buf_length;
	tmp_channel_process.pixel_format = convert_vdu_pf_to_cp_pf(image_info->vpf);
	convert_vdu_rect_to_cp_rect(&tmp_channel_process.image_rect, &image_info->image_rect);

	//ת��Ϊcp_codec_pixel_format����ĸ�ʽ
	if (cp_codec_pixel_format_none == tmp_channel_process.pixel_format) {
		cp_log_printf("unsupport pixel_format[%d] error.", image_info->vpf);
		return cp_vdu_status_unsupport_pixel_format;
	}

	//����channel
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

	//��ʼ��channel process struct
	fill_vdu_channel_to_process_struct(&tmp_channel_process, vdu_channel);
	tmp_channel_process.buf = buf;
	tmp_channel_process.buf_length = len;
	tmp_channel_process.pixel_format = convert_vdu_pf_to_cp_pf(vpf);
	convert_vdu_rect_to_cp_rect(&tmp_channel_process.vdu_rect, &rect);

	if (scale_rect) {
		convert_vdu_rect_to_cp_rect(&tmp_channel_process.image_rect, scale_rect);
	}

	//����channel
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

	//��ʼ��channel process struct
	fill_vdu_channel_to_process_struct(&tmp_channel_process, vdu_channel);
	tmp_channel_process.buf = image_info->buf;
	tmp_channel_process.buf_length = image_info->buf_length;
	tmp_channel_process.pixel_format = convert_vdu_pf_to_cp_pf(image_info->vpf);
	convert_vdu_rect_to_cp_rect(&tmp_channel_process.vdu_rect, &image_info->vdu_rect);
	convert_vdu_rect_to_cp_rect(&tmp_channel_process.image_rect, &image_info->image_rect);

	//ת��Ϊcp_codec_pixel_format����ĸ�ʽ
	if (cp_codec_pixel_format_none == tmp_channel_process.pixel_format) {
		cp_log_printf("unsupport pixel_format[%d] error.", image_info->vpf);
		return cp_vdu_status_unsupport_pixel_format;
	}

	//����channel
	tmp_ret_int = cp_get_option_module(tmp_vdu_app->vdu_func,
		cp_qt_svg_channel_option_get_rect_pixel, &tmp_channel_process);
	if (tmp_ret_int < 0) {
		return tmp_ret_int;
	}
	image_info->image_length = tmp_ret_int;

	return tmp_channel_process.image_length;
}







//////////////////////////////////////////////////////////////////////////
//cp_vdu_media_info������
//////////////////////////////////////////////////////////////////////////

/*******************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: cp_vdu_image_info_clear
*
* ����ȫ��: cp_vdu_image_info_clear
*
* ��������: public
*
* ����˵��: ���image info��Ϣ
*
* ��    ��: cp_vdu_image_info_t * vdu_image						[in/out]����˵��
*
* �� �� ֵ: cp_extern int
*           0  : �ɹ�
*         ��0  : ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2018-2-25 11:31:47
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
* ��Ȩ����: fz & novigo
*
* ��������: cp_vdu_image_info_set_pixel_format
*
* ����ȫ��: cp_vdu_image_info_set_pixel_format
*
* ��������: public
*
* ����˵��: ����ͼ��ɫ�ʿռ�
*
* ��    ��: cp_vdu_image_info_t * vdu_image						[in/out]����˵��
* ��    ��: cp_vdu_pixel_format_e vpf						[in/out]����˵��
*
* �� �� ֵ: cp_extern int
*           0  : �ɹ�
*         ��0  : ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2018-2-25 11:32:10
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
* ��Ȩ����: fz & novigo
*
* ��������: cp_vdu_image_info_get_pixel_format
*
* ����ȫ��: cp_vdu_image_info_get_pixel_format
*
* ��������: public
*
* ����˵��: ��ȡͼ��ɫ�ʿռ�
*
* ��    ��: cp_vdu_image_info_t * vdu_image						[in/out]����˵��
*
* �� �� ֵ: cp_extern cp_vdu_pixel_format_e
*           0  : �ɹ�
*         ��0  : ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2018-2-25 11:33:23
********************************************************************************/
cp_vdu_pixel_format_e cp_vdu_image_info_get_pixel_format(cp_vdu_image_info_t *vdu_image)
{
	if (!vdu_image) {
		return cp_vdu_pixel_format_end;
	}

	return vdu_image->vpf;
}

/*******************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: cp_vdu_image_info_set_vdu_rect
*
* ����ȫ��: cp_vdu_image_info_set_vdu_rect
*
* ��������: public
*
* ����˵��: ������Ҫ��ȡ��vduͼ��λ��
*
* ��    ��: cp_vdu_image_info_t * vdu_image						[in/out]����˵��
* ��    ��: cp_vdu_rect_t rect						[in/out]����˵��
*
* �� �� ֵ: cp_extern int
*           0  : �ɹ�
*         ��0  : ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2018-2-25 11:33:31
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
* ��Ȩ����: fz & novigo
*
* ��������: cp_vdu_image_info_set_vdu_rect_parameters
*
* ����ȫ��: cp_vdu_image_info_set_vdu_rect_parameters
*
* ��������: public
*
* ����˵��: ������Ҫ��ȡ��vduͼ��λ�õ���ϸ
*
* ��    ��: cp_vdu_image_info_t * vdu_image						[in/out]����˵��
* ��    ��: int x						[in/out]����˵��
* ��    ��: int y						[in/out]����˵��
* ��    ��: int width						[in/out]����˵��
* ��    ��: int height						[in/out]����˵��
*
* �� �� ֵ: cp_extern int
*           0  : �ɹ�
*         ��0  : ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2018-2-25 11:34:06
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
* ��Ȩ����: fz & novigo
*
* ��������: cp_vdu_image_info_get_vdu_rect
*
* ����ȫ��: cp_vdu_image_info_get_vdu_rect
*
* ��������: public
*
* ����˵��: ��ȡ��Ҫ��ȡ��vduͼ��λ��
*
* ��    ��: cp_vdu_image_info_t * vdu_image						[in/out]����˵��
*
* �� �� ֵ: cp_extern cp_vdu_rect_t
*           0  : �ɹ�
*         ��0  : ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2018-2-25 11:34:29
********************************************************************************/
cp_vdu_rect_t cp_vdu_image_info_get_vdu_rect(cp_vdu_image_info_t *vdu_image)
{
	return vdu_image->vdu_rect;
}

/*******************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: cp_vdu_image_info_set_image_size
*
* ����ȫ��: cp_vdu_image_info_set_image_size
*
* ��������: public
*
* ����˵��: ��������������ͼ��ߴ���Ϣ
*
* ��    ��: cp_vdu_image_info_t * vdu_image						[in/out]����˵��
* ��    ��: int width						[in/out]����˵��
* ��    ��: int height						[in/out]����˵��
*
* �� �� ֵ: cp_extern int
*           0  : �ɹ�
*         ��0  : ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2018-2-25 11:37:05
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
* ��Ȩ����: fz & novigo
*
* ��������: cp_vdu_image_info_get_image_rect
*
* ����ȫ��: cp_vdu_image_info_get_image_rect
*
* ��������: public
*
* ����˵��: ��ȡ����������ͼ��ߴ���Ϣ
*
* ��    ��: cp_vdu_image_info_t * vdu_image						[in/out]����˵��
*
* �� �� ֵ: cp_extern cp_vdu_rect_t
*           0  : �ɹ�
*         ��0  : ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2018-2-25 11:37:12
********************************************************************************/
cp_vdu_rect_t cp_vdu_image_info_get_image_rect(cp_vdu_image_info_t *vdu_image)
{
	return vdu_image->image_rect;
}

