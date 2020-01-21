/*******************************************************************************
*
*Copyright:novigo
*
*File name: main.c
*
*Author:fangzhenmu@novigo.com.cn
*
*Version: 1.0
*
*Date:2018/02/05
*
*Description: create (main.c)
*
*Others:
*
*History:
*******************************************************************************/

#define		CP_VDU_DEBUG_CHECK_MEMORY_VDU										1
#define		CP_VDU_DEBUG_CHECK_MEMORY_VDU_CHANNEL								1



#ifdef __linux__
#include <errno.h>
#endif



#if defined(WIN32) && (CP_VDU_DEBUG_CHECK_MEMORY_VDU || CP_VDU_DEBUG_CHECK_MEMORY_VDU_CHANNEL)
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <windows.h>
#endif




#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>
#include "cp_vdu.h"




//默认的缓存大小
#define		CP_VDU_SAMPLE_DEMO_DEFAULT_BUFFER_LENGTH							50 * 1024 * 1024

//文件目录名称
#ifdef WIN32
#define		CP_VDU_SAMPLE_DEMO_DEFAULT_FILE_PATH								"files\\"
#else
#define		CP_VDU_SAMPLE_DEMO_DEFAULT_FILE_PATH								"files/"
#endif






//通道中处理svg xml格式数据
int read_file(char *file_name, char *buf, int buf_length)
{
	FILE					*tmp_fd;
	int						tmp_read_length = 0;



	tmp_fd = fopen(file_name, "rb");
	if (!tmp_fd) {
		printf("open file[%s] error. errno[%d] \r\n",
			file_name,
			errno);
		return -2;
	}

	tmp_read_length = fread(buf, 1, buf_length, tmp_fd);
	if (tmp_read_length <= 0) {
		printf("read file[%s] error. errno[%d] \r\n",
			file_name,
			errno);
		return -2;
	}

	if (tmp_fd) {
		fclose(tmp_fd);
	}

	return tmp_read_length;
}

int write_file(char *file_name, const char *buf, int buf_length)
{
	FILE					*tmp_fd;
	int						tmp_write_length = 0;



	tmp_fd = fopen(file_name, "wb");
	if (!tmp_fd) {
		printf("open file[%s] error. errno[%d] \r\n",
			file_name,
			errno);
		return -2;
	}

	tmp_write_length = fwrite(buf, 1, buf_length, tmp_fd);
	if (tmp_write_length != buf_length) {
		printf("write file[%s] error. write lenght[%d] errno[%d] \r\n",
			file_name,
			tmp_write_length,
			errno);
		return -2;
	}

	if (tmp_fd) {
		fclose(tmp_fd);
	}

	return 0;
}

#ifdef WIN32

void odprintf(const char *format, ...)
{
	va_list		args;
	char		buf[128] = { 0, }, *p = buf;



	va_start(args, format);
	p += _vsnprintf(p, sizeof buf - 1, format, args);
	va_end(args);

#if 0
	while (p > buf && isspace(p[-1])) {
		*--p = '\0';
		*p++ = '\r';
		*p++ = '\n';*p = '\0';
	}
#endif

	OutputDebugString(buf);
}

#endif


int test_vdu() {
	int							tmp_ret_int = 0;
	int							vdu_memory_different_count = 0;
	int							vdu_channel_memory_different_count = 0;
	cp_vdu_t					*vdu = NULL;
	cp_vdu_channel_t			*vdu_channel = NULL;
	cp_vdu_version_t			vdu_version = { 0, };




#if defined(WIN32) && CP_VDU_DEBUG_CHECK_MEMORY_VDU
	_CrtMemState vdu_s1, vdu_s2, vdu_s3;

	//_CrtDumpMemoryLeaks();

	_CrtMemCheckpoint(&vdu_s1);
#endif

	//未创建vdu时，获取版本号信息
	vdu_version = cp_vdu_get_version(NULL);
	printf("version information: [%s_%s (%d)]\r\n",
		vdu_version.name, vdu_version.str_version, vdu_version.version);

	//创建一个vdu处理单元
	vdu = cp_vdu_create();
	if (!vdu) {
		printf("cp_vdu_create() error.\r\n");
		return -1;
	}

	//打开调试模式，将信息保存在目录中
	tmp_ret_int = cp_vdu_open_debug_mode(vdu, "output_files");
	if (tmp_ret_int) {
		printf("cp_vdu_open_debug_mode() error. reason:[%d %s]\r\n",
			cp_vdu_get_status(vdu),
			cp_vdu_strstatus(cp_vdu_get_status(vdu)));
		return -1;
	}

	//设置vdu的类型
	tmp_ret_int = cp_vdu_set_type(vdu, cp_vdu_type_svg);
	if (tmp_ret_int) {
		printf("cp_vdu_set_type() error. reason:[%d %s]\r\n",
			cp_vdu_get_status(vdu),
			cp_vdu_strstatus(cp_vdu_get_status(vdu)));
		return -1;
	}

	//设置感兴趣区域，即需要渲染处理的
	cp_vdu_rect_t			vdu_rect = { 0, 0, 3840, 2160 };
	//cp_vdu_rect_t			vdu_rect = { 0, 0, 1920, 1080 };
	//cp_vdu_rect_t			vdu_rect = { 0, 0, 800, 600 };


	tmp_ret_int = cp_vdu_set_roi(vdu, vdu_rect);
	if (tmp_ret_int) {
		printf("cp_vdu_set_roi() error. reason:[%d %s]\r\n",
			cp_vdu_get_status(vdu),
			cp_vdu_strstatus(cp_vdu_get_status(vdu)));
		return -1;
	}


#if defined(WIN32) && CP_VDU_DEBUG_CHECK_MEMORY_VDU_CHANNEL
	_CrtMemState vdu_channel_s1, vdu_channel_s2, vdu_channel_s3;

	//_CrtDumpMemoryLeaks();

	_CrtMemCheckpoint(&vdu_channel_s1);
#endif

	//通道中处理svg xml格式数据
	int							tmp_read_length = 0;
	char						*tmp_buf = NULL;
	char						*tmp_input_file_name = CP_VDU_SAMPLE_DEMO_DEFAULT_FILE_PATH "input_svg_file.svg";
	char						*tmp_output_file_name = CP_VDU_SAMPLE_DEMO_DEFAULT_FILE_PATH "output_file.data";



	//创建单独的处理通道
	vdu_channel = cp_vdu_create_channel(vdu, cp_vdu_channel_type_svg);
	if (!vdu_channel) {
		printf("cp_vdu_create_channel() error. reason:[%d %s]\r\n",
			cp_vdu_get_status(vdu),
			cp_vdu_strstatus(cp_vdu_get_status(vdu)));
		return -1;
	}

	tmp_buf = (char*)malloc(CP_VDU_SAMPLE_DEMO_DEFAULT_BUFFER_LENGTH);
	if (!tmp_buf) {
		printf("malloc() memory[%d] error. errno:[%d]\r\n",
			CP_VDU_SAMPLE_DEMO_DEFAULT_BUFFER_LENGTH,
			errno);
		return -1;
	}
	else {
		memset(tmp_buf, 0, CP_VDU_SAMPLE_DEMO_DEFAULT_BUFFER_LENGTH);
	}

	tmp_read_length = read_file(tmp_input_file_name, tmp_buf, CP_VDU_SAMPLE_DEMO_DEFAULT_BUFFER_LENGTH);
	if (tmp_read_length <= 0) {
		printf("read_file[%s] error.\r\n",
			tmp_input_file_name);
		return -1;
	}
	//设置需要处理的矢量数据
	tmp_ret_int = cp_vdu_channel_set_vector_stream(vdu_channel,
		cp_vdu_vector_stream_type_svg_xml, tmp_buf, tmp_read_length);
	if (tmp_ret_int) {
		printf("cp_vdu_set_roi() error. reason:[%d %s]\r\n",
			cp_vdu_get_status(vdu),
			cp_vdu_strstatus(cp_vdu_get_status(vdu)));
		return -1;
	}

	//获取渲染位图方法：
	//1、采用roi方式
	cp_vdu_rect_t			vdu_channel_rect = { 0, 0, 3840, 2160 };
	//cp_vdu_rect_t			vdu_channel_rect = { 0, 0, 800, 600 };


	//设置感兴趣区域
	tmp_ret_int = cp_vdu_channel_set_roi(vdu_channel, vdu_channel_rect);
	if (tmp_ret_int) {
		printf("cp_vdu_channel_set_roi() error. reason:[%d %s]\r\n",
			cp_vdu_channel_get_status(vdu_channel),
			cp_vdu_strstatus(cp_vdu_channel_get_status(vdu_channel)));
		return -1;
	}

	//获取感兴趣区域的位图
	tmp_ret_int = cp_vdu_channel_get_roi_pixel(vdu_channel,
		tmp_buf, CP_VDU_SAMPLE_DEMO_DEFAULT_BUFFER_LENGTH, cp_vdu_pixel_format_rgba8888, NULL);
	if (tmp_ret_int <= 0) {
		printf("cp_vdu_channel_get_roi_pixel() error. reason:[%d %s]\r\n",
			cp_vdu_channel_get_status(vdu_channel),
			cp_vdu_strstatus(cp_vdu_channel_get_status(vdu_channel)));
		return -1;
	}

	//1、采用rect方式
	cp_vdu_rect_t			get_vdu_channel_rect = { 0, 0, 3840, 2160 };
	//cp_vdu_rect_t			get_vdu_channel_rect = { 0, 0, 400, 300 };

	tmp_ret_int = cp_vdu_channel_get_rect_pixel(vdu_channel,
		tmp_buf, CP_VDU_SAMPLE_DEMO_DEFAULT_BUFFER_LENGTH, cp_vdu_pixel_format_rgba8888,
		get_vdu_channel_rect, NULL);
	if (tmp_ret_int <= 0) {
		printf("cp_vdu_channel_get_rect_pixel() error. reason:[%d %s]\r\n",
			cp_vdu_channel_get_status(vdu_channel),
			cp_vdu_strstatus(cp_vdu_channel_get_status(vdu_channel)));
		return -1;
	}

	//保存文件
	tmp_ret_int = write_file(tmp_output_file_name, tmp_buf, tmp_ret_int);
	if (tmp_ret_int < 0) {
		printf("write_file() error. return:[%d]\r\n", tmp_ret_int);
		return -1;
	}

	//添加channel
	tmp_ret_int = cp_vdu_insert_channel(vdu, vdu_channel);
	if (tmp_ret_int < 0) {
		printf("cp_vdu_insert_channel() error. return:[%d]\r\n", tmp_ret_int);
		return -1;
	}

	//获取感兴趣区域的位图
	tmp_ret_int = cp_vdu_get_roi_pixel(vdu,
		tmp_buf, CP_VDU_SAMPLE_DEMO_DEFAULT_BUFFER_LENGTH, cp_vdu_pixel_format_rgba8888, NULL);
	if (tmp_ret_int <= 0) {
		printf("cp_vdu_get_roi_pixel() error. reason:[%d %s]\r\n",
			cp_vdu_get_status(vdu),
			cp_vdu_strstatus(cp_vdu_get_status(vdu)));
		return -1;
	}


	//1、采用rect方式
	cp_vdu_rect_t			get_vdu_rect = { 0, 0, 3840, 2160 };
	//cp_vdu_rect_t			get_vdu_rect = { 0, 0, 400, 300 };

	tmp_ret_int = cp_vdu_get_rect_pixel(vdu,
		tmp_buf, CP_VDU_SAMPLE_DEMO_DEFAULT_BUFFER_LENGTH, cp_vdu_pixel_format_rgba8888,
		get_vdu_rect, NULL);
	if (tmp_ret_int <= 0) {
		printf("cp_vdu_get_rect_pixel() error. reason:[%d %s]\r\n",
			cp_vdu_get_status(vdu),
			cp_vdu_strstatus(cp_vdu_get_status(vdu)));
		return -1;
	}

	//销毁释放的资源
	if (tmp_buf) {
		free(tmp_buf);
	}

	//销毁channel内容
	tmp_ret_int = cp_vdu_destroy_channel(vdu_channel);
	if (tmp_ret_int < 0) {
		printf("cp_vdu_destroy_channel() error. return:[%d]\r\n", tmp_ret_int);
		return -1;
	}

#if defined(WIN32) && CP_VDU_DEBUG_CHECK_MEMORY_VDU_CHANNEL
	_CrtMemCheckpoint(&vdu_channel_s2);

	if (_CrtMemDifference(&vdu_channel_s3, &vdu_channel_s1, &vdu_channel_s2)) {
		++vdu_channel_memory_different_count;
		//_CrtMemDumpStatistics(&vdu_channel_s3);
		odprintf("vdu_channel different count[%d]\r\n", vdu_channel_memory_different_count);
	}
#endif

	//销毁所有channel内容
	tmp_ret_int = cp_vdu_destroy_all_channels(vdu);
	if (tmp_ret_int < 0) {
		printf("cp_vdu_destroy_all_channels() error. return:[%d]\r\n", tmp_ret_int);
		return -1;
	}

	//销毁vdu内容
	tmp_ret_int = cp_vdu_destroy(vdu);
	if (tmp_ret_int < 0) {
		printf("cp_vdu_destroy() error. return:[%d]\r\n", tmp_ret_int);
		return -1;
	}

	//_CrtDumpMemoryLeaks();

#if defined(WIN32) && CP_VDU_DEBUG_CHECK_MEMORY_VDU
	_CrtMemCheckpoint(&vdu_s2);

	if (_CrtMemDifference(&vdu_s3, &vdu_s1, &vdu_s2)) {
		//_CrtMemDumpStatistics(&vdu_s3);
		++vdu_memory_different_count;

		odprintf("vdu different count[%d]\r\n", vdu_memory_different_count);
	}

#endif

	return 0;
}

int main(int argc, char** argv) {
	return test_vdu();
}