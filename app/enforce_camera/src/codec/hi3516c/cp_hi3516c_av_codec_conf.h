/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-12-20

Description:

**************************************************************************/

#ifndef _CP_HI3519_AV_CODEC_CONF_INCLUDE_H_
#define _CP_HI3519_AV_CODEC_CONF_INCLUDE_H_


#include "cp_core.h"
#include "cp_module_core.h"
#include "cp_hi3516c_av_codec_conf_string.h"




//������������
#define		CP_HI3519_AV_CAMERA_CONFIGURE_SIZE					2

//����overlap point ����
#define		CP_HI3519_AV_OVERLAP_POINT_SIZE						4


typedef struct cp_hi3516c_av_auto_configure_s					cp_hi3516c_av_auto_configure_t;
typedef struct cp_hi3516c_av_overlap_point_s						cp_hi3516c_av_overlap_point_t;
typedef struct cp_hi3516c_av_stitch_configure_s					cp_hi3516c_av_stitch_configure_t;
typedef struct cp_hi3516c_av_cylind_stitch_correction_s			cp_hi3516c_av_cylind_stitch_correction_t;
typedef	struct cp_hi3516c_av_camera_configure_s					cp_hi3516c_av_camera_configure_t;
typedef struct cp_hi3516c_av_codec_configure_s					cp_hi3516c_av_codec_configure_t;
typedef enum cp_hi3516c_av_codec_mode_enum						cp_hi3516c_av_codec_mode_e;


/************************************************************************/
/* codec�Ĺ���ģʽ                                                       */
/************************************************************************/
enum cp_hi3516c_av_codec_mode_enum
{
	cp_hi3516c_av_codec_mode_none = 0,
	cp_hi3516c_av_codec_mode_vi_venc,
	cp_hi3516c_av_codec_mode_vi_stitch_vpss_venc,
	cp_hi3516c_av_codec_mode_vi_fisheye_stitch_vpss_venc,
	cp_hi3516c_av_codec_mode_vi_fisheye_process_vpss_venc,
	cp_hi3516c_av_codec_mode_vi_fisheye_process_vpss_stitch_vpss_venc,
	cp_hi3516c_av_codec_mode_vi_process_vpss_fisheye_stitch_vpss_venc,
	cp_hi3516c_av_codec_mode_end
};


/************************************************************************/
/* auto������Ϣ                                                        */
/************************************************************************/
struct cp_hi3516c_av_auto_configure_s
{
	cp_bool_t							is_auto;									//��ʾ�Ƿ��Զ����ã�0��ʾ���Զ���1��ʾ�Զ�
	cp_int32_t							auto_size;									//��ʾ�Զ����õĴ�С
};

/************************************************************************/
/* overlap point����                                                    */
/************************************************************************/
struct cp_hi3516c_av_overlap_point_s
{
	cp_int32_t							x;											//ƴ�Ӻ�ͼ��Ŀ�ȡ�Ҫ��4 ���룬ȡֵ��Χ��[64, 8188]��
	cp_int32_t							y;											//ƴ�Ӻ�ͼ��ĸ߶ȡ�Ҫ��4 ���룬ȡֵ��Χ��[64, 4608]��
};

/************************************************************************/
/*˫·ƴ��У������                                                       */
/************************************************************************/
struct cp_hi3516c_av_cylind_stitch_correction_s
{
	cp_bool_t							is_used;									//��ʾ�Ƿ�ʹ�ã�0��ʾ��ʹ�ã�1��ʾʹ��
	cp_int32_t							center_horizontal_offset;					//��ʾ����ˮƽƫ�ƣ�ȡֵ��Χ��[-127, 127]
	cp_int32_t							center_vertical_offset;						//��ʾ���Ĵ�ֱƫ�ƣ�ȡֵ��Χ��[-127, 127]
	cp_int32_t							ratio;										//��ʾ����ͶӰУ���̶ȣ�ȡֵ��Χ��[0, 500]
};

/************************************************************************/
/* stitch������Ϣ                                                        */
/************************************************************************/
struct cp_hi3516c_av_stitch_configure_s
{
	cp_int32_t							out_width;											//ƴ�Ӻ�ͼ��Ŀ�ȡ�Ҫ��4 ���룬ȡֵ��Χ��[64, 8188]��
	cp_int32_t							out_height;											//ƴ�Ӻ�ͼ��ĸ߶ȡ�Ҫ��4 ���룬ȡֵ��Χ��[64, 4608]��
	cp_hi3516c_av_overlap_point_t		overlap_points[CP_HI3519_AV_OVERLAP_POINT_SIZE];	//overlap point����
	cp_hi3516c_av_auto_configure_t		auto_config;										//��ʾ�Ƿ��Զ�����
	cp_hi3516c_av_cylind_stitch_correction_t		csc[CP_HI3519_AV_CAMERA_CONFIGURE_SIZE];	//��ʾ����У������
};

/************************************************************************/
/* ����ͷ������Ϣ                                                        */
/************************************************************************/
struct cp_hi3516c_av_camera_configure_s
{
	cp_bool_t							is_mirror;									//�Ƿ�ˮƽ��ת��0��ʾ����ת��1��ʾ��ת
	cp_bool_t							is_flip;									//�Ƿ�ֱ��ת��0��ʾ����ת��1��ʾ��ת
	cp_int32_t							rotate;										//��ʾ��ת�Ƕ�
	cp_int32_t							mount_mode;									//����У����װģʽ:0��ʾ��װģʽ��1��ʾ��װģʽ��2��װģʽ��
	cp_int32_t							view_mode;									//��У�������У��ģʽ:0��ʾ360ȫ��У����1��ʾ180ȫ��У����2��ʾNormal У����
	cp_int32_t							hor_offset;									//��ͷ���ĵ������SENSOR ���ĵ��ˮƽƫ�ƣ�ȡֵ��Χ[-127, 127]����λΪ���ء�
	cp_int32_t							ver_offset;									//��ͷ���ĵ������SENSOR ���ĵ�Ĵ�ֱƫ�ƣ�ȡֵ��Χ[-127, 127]����λΪ���ء�
	cp_int32_t							trapezoid_coef;								//����ǿ��ϵ��TrapezoidCoef ֻ�ڱ�װʱ��normal ��180 У��ʱ��Ч��
	cp_int32_t							fan_strength;								//����ǿ��ϵ��FanStrength ֻ��180 У��ʱ��Ч�����ڵ���ͼ��ˮƽ�����������
	cp_int32_t							in_radius;									//360 ȫ��ģʽ��ʾ��У����������Ӧԭͼ���ڰ뾶������ģʽ��Ч
	cp_int32_t							out_radius;									//360 ȫ��ģʽ��ʾ��У����������Ӧԭͼ����뾶������ģʽΪУ������Ŀ��Ӱ뾶;ȡֵ��Χ��[1, 2304]
	cp_int32_t							pan;										//��У������PTZ ������Pan ֵ.�ӳ��ǵ�����ת��������180 ����ת����С��180 ����ת��
	cp_int32_t							tilt;										//��У������PTZ ������Tilt ֵ.�ӳ��ǵ�����ת��������180 ����ת����С��180 ����ת����
	cp_int32_t							hor_zoom;									//��У������PTZ ������ˮƽZoom ֵ.ˮƽ�ӳ��Ǵ�С��4095 Ϊ���180 �ȣ���
	cp_int32_t							ver_zoom;									//��У������PTZ �����Ĵ�ֱZoom ֵ.��ֱ�ӳ��Ǵ�С��4095 Ϊ���90 �ȣ���
	cp_int32_t							outrect_x;									//��У����������λ�ü����,��ʼ�� xλ��
	cp_int32_t							outrect_y;									//��У����������λ�ü����,��ʼ�� yλ��
	cp_int32_t							outrect_width;								//��У����������λ�ü����,ͼ����
	cp_int32_t							outrect_height;								//��У����������λ�ü����,ͼ��߶�
	
	cp_int32_t							luminance;									//���ȵ��ڲ�����Ĭ��ֵ��50��ȡֵ��Χ[0, 100]
	cp_int32_t							contrast;									//�Աȶȵ��ڲ�����Ĭ��ֵ��50��ȡֵ��Χ[0, 100]
	cp_int32_t							hue;										//ɫ�����ڲ�����Ĭ��ֵ��50��ȡֵ��Χ[0, 100]
	cp_int32_t							satuature;									//���Ͷȵ��ڲ�����Ĭ��ֵ��50��ȡֵ��Χ[0, 100]
};


/************************************************************************/
/* ��Ƶ�����������                                                      */
/************************************************************************/
struct cp_hi3516c_av_codec_configure_s
{
	cp_int32_t							width;										//��ʾ�����������Ƶ���
	cp_int32_t							heigth;										//��ʾ�����������Ƶ�߶�
	cp_int32_t							fps;										//��ʾ����֡��
	cp_int32_t							bitrate;									//��ʾ������������ʣ���λkbps
	cp_int32_t							mode;										//��ʾcodec����ģʽ��1��ʾvi-venc��2��ʾvi-fisheye-vpss-vencģʽ
	cp_int32_t							vi_channel;									//��codec����ģʽΪvi-vencʱ��ʹ�õ�vi channel��š�ȡֵΪ��ǰ���ڹ�����vi channel��[0, 4]
	cp_hi3516c_av_camera_configure_t		camera_configs[CP_HI3519_AV_CAMERA_CONFIGURE_SIZE];		//��ʾ����ͷ�����ļ�����
	cp_hi3516c_av_stitch_configure_t		stitch_config;								//��ʾstitch configure����
};



/************************************************************************/
/*���������ļ�                                                           */
/************************************************************************/
cp_int32_t	hi3516c_av_codec_parse_configure(cp_module_t *module, cp_hi3516c_av_codec_configure_t *hacc);

/************************************************************************/
/*��������ͷ�����ļ�                                                     */
/************************************************************************/
cp_int32_t	hi3516c_av_codec_parse_camera_configure(cp_module_t *module, cp_hi3516c_av_codec_configure_t *hacc);

/************************************************************************/
/*����stitch�����ļ�                                                     */
/************************************************************************/
cp_int32_t	hi3516c_av_codec_parse_stitch_configure(cp_module_t *module, cp_hi3516c_av_codec_configure_t *hacc);

/************************************************************************/
/*����stitch ����У�������ļ�                                            */
/************************************************************************/
cp_int32_t	hi3516c_av_codec_parse_cylind_stitch_correction(cp_module_t *module, cp_hi3516c_av_codec_configure_t *hacc);

/************************************************************************/
/*����auto�����ļ�                                                     */
/************************************************************************/
cp_int32_t	hi3516c_av_codec_parse_auto_configure(cp_module_t *module, cp_hi3516c_av_codec_configure_t *hacc);

#endif