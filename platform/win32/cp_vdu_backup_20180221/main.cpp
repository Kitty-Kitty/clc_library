

#include <iostream>
#include <stdio.h>
#include "QtCore/QBuffer"
#include "QtWidgets/QApplication"
#include "QtWidgets/QGraphicsView"
#include "QtWidgets/QGraphicsRectItem"
#include "QtSvg/QGraphicsSvgItem"
#include "QtSvg/QSvgRenderer"
#include "QtCore/QObject"
#include <QtCore/QUrl>
#include <QtCore/QCommandLineOption>
#include <QtCore/QCommandLineParser>
#include "QtWidgets/QApplication"



#include "cp_vdu.h"



using namespace std;



//Ĭ�ϵĻ����С
#define		CP_VDU_SAMPLE_DEMO_DEFAULT_BUFFER_LENGTH							1 * 10 * 1024 * 1024

//ͨ���д���svg xml��ʽ����
static int read_file(char *file_name, char *buf, int buf_length)
{
	FILE					*tmp_fd = NULL;
	int						tmp_read_length = 0;
	errno_t					tmp_errno = 0;


#ifdef _CRT_SECURE_NO_WARNINGS
	tmp_fd = fopen(file_name, "rb");
#else
	tmp_errno = fopen_s(&tmp_fd, file_name, "rb");
#endif
	if (!tmp_fd) {
		printf("open file[%s] error. errno[%d] \r\n",
			file_name,
			tmp_errno);
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


#if 0

int main(int argc, char** argv)
{
	int							tmp_argc = 0;
	char						*tmp_argv = NULL;
	QApplication				*qt_app = NULL;						//��ʾqt��application
	QGraphicsView				*view = NULL;						//��ʾͼ�ε���ͼ����
	QGraphicsScene				*scene = NULL;						//��ʾͼ�γ���
	QGraphicsSvgItem			*item = NULL;						//��ʾһ��svgͼ��
	QSvgRenderer				*renderer = NULL;					//��ʾһ��svg renderer����



  	try
  	{
  		qt_app = new QApplication(tmp_argc, NULL);
  	}
  	catch (std::exception& e)
  	{
  		std::cout << "exception: " << e.what() << std::endl;
  	}

	try
	{
		view = new QGraphicsView();
	}
	catch (std::exception& e)
	{
		std::cout << "exception: " << e.what() << std::endl;
	}

	try
	{
		scene = new QGraphicsScene(0, 0, 1920, 1080, view);
	}
	catch (std::exception& e)
	{
		std::cout << "exception: " << e.what() << std::endl;
	}

	try
	{
		item = new QGraphicsSvgItem();
	}
	catch (std::exception& e)
	{
		std::cout << "exception: " << e.what() << std::endl;
	}

	try
	{
		renderer = new QSvgRenderer();
	}
	catch (std::exception& e)
	{
		std::cout << "exception: " << e.what() << std::endl;
	}

	//ͨ���д���svg xml��ʽ����
	int							tmp_read_length = 0;
	char						*tmp_buf = NULL;
#ifdef WIN32
	//char						*tmp_input_file_name = "files\input_svg_file.svg";
	char						*tmp_input_file_name = "files\\input_svg_file.svg";
	char						*tmp_output_file_name = "files\\out_svg_file.png";
#else
	//char						*tmp_input_file_name = "./files/input_svg_file.svg";
	char						*tmp_input_file_name = "files\\input_svg_file.svg";
	char						*tmp_output_file_name = "files\\out_svg_file.png";
#endif
	



	tmp_buf = (char *)malloc(CP_VDU_SAMPLE_DEMO_DEFAULT_BUFFER_LENGTH);
	if (!tmp_buf) {
		printf("malloc() memory[%d] error. errno:[%d]\r\n",
			CP_VDU_SAMPLE_DEMO_DEFAULT_BUFFER_LENGTH,
			errno);
		return -1;
	}

	tmp_read_length = read_file(tmp_input_file_name, tmp_buf, CP_VDU_SAMPLE_DEMO_DEFAULT_BUFFER_LENGTH);
	if (tmp_read_length <= 0) {
		printf("read_file[%s] error.\r\n",
			tmp_input_file_name);
		return -1;
	}

	//����svg�ļ�������
	if (!renderer->load(QByteArray((const char*)tmp_buf, (int)tmp_read_length))) {
		printf("load read_file[%s] error.\r\n",
			tmp_input_file_name);
		return -1;
	}

	//����SvgItem������Ϣ
	item->setSharedRenderer(renderer);
	item->setFlags(QGraphicsItem::ItemClipsToShape);
	item->setCacheMode(QGraphicsItem::NoCache);
	item->setZValue(0);



	//����ͼƬ�ļ�

	int								tmp_ret_int = 0;


	//QImage image(rect.right - rect.left, rect.bottom - rect.top, QImage::Format_ARGB32);
	QImage tmp_image(800, 600, QImage::Format_ARGB32);
	//image.fill(0xaaA08080);  // partly transparent red-ish background
	tmp_image.fill(Qt::transparent);

	//����painter
	//QPainter tmp_painter(&tmp_image);
	QPainter tmp_painter;

	//����ͼƬ,������Ⱦ��ʱ�����ʵ���Զ����Ŵ���
	tmp_painter.begin(&tmp_image);
	renderer->render(&tmp_painter);
	tmp_painter.end();

	QByteArray tmp_byte_array;
	QBuffer tmp_buffer(&tmp_byte_array);
	//image.save(&buffer, "PNG"); // writes the image in PNG format inside the buffer
	//tmp_image.save(&tmp_buffer); // writes the image in PNG format inside the buffer
	tmp_image.save(QString(tmp_output_file_name), "PNG"); // writes the image in PNG format inside the buffer

	//write_file(tmp_output_file_name, )


	return 0;
}

#endif


int main(int argc, char** argv) {
	int							tmp_ret_int = 0;
	cp_vdu_t					*vdu = NULL;
	cp_vdu_channel_t			*vdu_channel = NULL;
	cp_vdu_version_t			vdu_version = { 0, };



#ifdef WIN32
	_CrtMemState s1, s2, s3;

	_CrtDumpMemoryLeaks();

	_CrtMemCheckpoint(&s1);
#endif

	//δ����vduʱ����ȡ�汾����Ϣ
	vdu_version = cp_vdu_get_version(NULL);
	printf("version information: [%s_%s (%d)]\r\n",
		vdu_version.name, vdu_version.str_version, vdu_version.version);

	//����һ��vdu����Ԫ
	vdu = cp_vdu_create();
	if (!vdu) {
		printf("cp_vdu_create() error.\r\n");
		return -1;
	}

	//#if 0

	//����vdu������
	tmp_ret_int = cp_vdu_set_type(vdu, cp_vdu_type_svg);
	if (tmp_ret_int) {
		printf("cp_vdu_set_type() error. reason:[%d %s]\r\n",
			cp_vdu_get_status(vdu),
			cp_vdu_strstatus(cp_vdu_get_status(vdu)));
		return -1;
	}

	//���ø���Ȥ���򣬼���Ҫ��Ⱦ�����
	cp_vdu_rect_t			vdu_rect = { 0, 0, 1920, 1080 };


	tmp_ret_int = cp_vdu_set_roi(vdu, vdu_rect);
	if (tmp_ret_int) {
		printf("cp_vdu_set_roi() error. reason:[%d %s]\r\n",
			cp_vdu_get_status(vdu),
			cp_vdu_strstatus(cp_vdu_get_status(vdu)));
		return -1;
	}

	//���������Ĵ���ͨ��
	vdu_channel = cp_vdu_create_channel(vdu, cp_vdu_channel_type_svg);
	if (!vdu_channel) {
		printf("cp_vdu_create_channel() error. reason:[%d %s]\r\n",
			cp_vdu_get_status(vdu),
			cp_vdu_strstatus(cp_vdu_get_status(vdu)));
		return -1;
	}


	//ͨ���д���svg xml��ʽ����
	int							tmp_read_length = 0;
	char						*tmp_buf = NULL;
	char						*tmp_input_file_name = "files\\input_svg_file.svg";



	tmp_buf = (char *)malloc(CP_VDU_SAMPLE_DEMO_DEFAULT_BUFFER_LENGTH);
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
	//������Ҫ�����ʸ������
	tmp_ret_int = cp_vdu_channel_set_vector_stream(vdu_channel,
		cp_vdu_vector_stream_type_svg_xml, tmp_buf, tmp_read_length);
	if (tmp_ret_int) {
		printf("cp_vdu_set_roi() error. reason:[%d %s]\r\n",
			cp_vdu_get_status(vdu),
			cp_vdu_strstatus(cp_vdu_get_status(vdu)));
		return -1;
	}

	//��ȡ��Ⱦλͼ������
	//1������roi��ʽ
	cp_vdu_rect_t			vdu_channel_rect = { 0, 0, 800, 600 };


	//���ø���Ȥ����
	tmp_ret_int = cp_vdu_channel_set_roi(vdu_channel, vdu_channel_rect);
	if (tmp_ret_int) {
		printf("cp_vdu_channel_set_roi() error. reason:[%d %s]\r\n",
			cp_vdu_channel_get_status(vdu_channel),
			cp_vdu_strstatus(cp_vdu_channel_get_status(vdu_channel)));
		return -1;
	}

	//��ȡ����Ȥ�����λͼ
	tmp_ret_int = cp_vdu_channel_get_roi_pixel(vdu_channel,
		tmp_buf, CP_VDU_SAMPLE_DEMO_DEFAULT_BUFFER_LENGTH, cp_vdu_pixel_format_argb8888, NULL);
	if (tmp_ret_int <= 0) {
		printf("cp_vdu_channel_get_roi_pixel() error. reason:[%d %s]\r\n",
			cp_vdu_channel_get_status(vdu_channel),
			cp_vdu_strstatus(cp_vdu_channel_get_status(vdu_channel)));
		return -1;
	}

	//�����ļ�
	tmp_ret_int = write_file("./files/output_file.data", tmp_buf, tmp_ret_int);
	if (tmp_ret_int < 0) {
		printf("write_file() error. return:[%d]\r\n", tmp_ret_int);
		return -1;
	}

	//����channel����
	tmp_ret_int = cp_vdu_destroy_channel(vdu_channel);
	if (tmp_ret_int < 0) {
		printf("cp_vdu_destroy_channel() error. return:[%d]\r\n", tmp_ret_int);
		return -1;
	}

	//��������channel����
	tmp_ret_int = cp_vdu_destroy_all_channels(vdu);
	if (tmp_ret_int < 0) {
		printf("cp_vdu_destroy_all_channels() error. return:[%d]\r\n", tmp_ret_int);
		return -1;
	}

	//�����ͷŵ���Դ
	if (tmp_buf) {
		free(tmp_buf);
	}

	//#endif

	//����vdu����
	tmp_ret_int = cp_vdu_destroy(vdu);
	if (tmp_ret_int < 0) {
		printf("cp_vdu_destroy() error. return:[%d]\r\n", tmp_ret_int);
		return -1;
	}

	_CrtDumpMemoryLeaks();

#ifdef WIN32
	_CrtMemCheckpoint(&s2);

	if (_CrtMemDifference(&s3, &s1, &s2))
		_CrtMemDumpStatistics(&s3);
#endif

	return 0;
}