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




//定义配置数量
#define		CP_HI3519_AV_CAMERA_CONFIGURE_SIZE					2

//定义overlap point 数量
#define		CP_HI3519_AV_OVERLAP_POINT_SIZE						4


typedef struct cp_hi3516c_av_auto_configure_s					cp_hi3516c_av_auto_configure_t;
typedef struct cp_hi3516c_av_overlap_point_s						cp_hi3516c_av_overlap_point_t;
typedef struct cp_hi3516c_av_stitch_configure_s					cp_hi3516c_av_stitch_configure_t;
typedef struct cp_hi3516c_av_cylind_stitch_correction_s			cp_hi3516c_av_cylind_stitch_correction_t;
typedef	struct cp_hi3516c_av_camera_configure_s					cp_hi3516c_av_camera_configure_t;
typedef struct cp_hi3516c_av_codec_configure_s					cp_hi3516c_av_codec_configure_t;
typedef enum cp_hi3516c_av_codec_mode_enum						cp_hi3516c_av_codec_mode_e;


/************************************************************************/
/* codec的工作模式                                                       */
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
/* auto配置信息                                                        */
/************************************************************************/
struct cp_hi3516c_av_auto_configure_s
{
	cp_bool_t							is_auto;									//表示是否自动配置：0表示不自动；1表示自动
	cp_int32_t							auto_size;									//表示自动配置的大小
};

/************************************************************************/
/* overlap point配置                                                    */
/************************************************************************/
struct cp_hi3516c_av_overlap_point_s
{
	cp_int32_t							x;											//拼接后图像的宽度。要求4 对齐，取值范围：[64, 8188]。
	cp_int32_t							y;											//拼接后图像的高度。要求4 对齐，取值范围：[64, 4608]。
};

/************************************************************************/
/*双路拼接校正配置                                                       */
/************************************************************************/
struct cp_hi3516c_av_cylind_stitch_correction_s
{
	cp_bool_t							is_used;									//表示是否使用：0表示不使用；1表示使用
	cp_int32_t							center_horizontal_offset;					//表示中心水平偏移，取值范围：[-127, 127]
	cp_int32_t							center_vertical_offset;						//表示中心垂直偏移，取值范围：[-127, 127]
	cp_int32_t							ratio;										//表示柱面投影校正程度，取值范围：[0, 500]
};

/************************************************************************/
/* stitch配置信息                                                        */
/************************************************************************/
struct cp_hi3516c_av_stitch_configure_s
{
	cp_int32_t							out_width;											//拼接后图像的宽度。要求4 对齐，取值范围：[64, 8188]。
	cp_int32_t							out_height;											//拼接后图像的高度。要求4 对齐，取值范围：[64, 4608]。
	cp_hi3516c_av_overlap_point_t		overlap_points[CP_HI3519_AV_OVERLAP_POINT_SIZE];	//overlap point数量
	cp_hi3516c_av_auto_configure_t		auto_config;										//表示是否自动配置
	cp_hi3516c_av_cylind_stitch_correction_t		csc[CP_HI3519_AV_CAMERA_CONFIGURE_SIZE];	//表示柱面校正配置
};

/************************************************************************/
/* 摄像头配置信息                                                        */
/************************************************************************/
struct cp_hi3516c_av_camera_configure_s
{
	cp_bool_t							is_mirror;									//是否水平翻转，0表示不翻转；1表示翻转
	cp_bool_t							is_flip;									//是否垂直翻转，0表示不翻转；1表示翻转
	cp_int32_t							rotate;										//表示旋转角度
	cp_int32_t							mount_mode;									//鱼眼校正安装模式:0表示底装模式；1表示顶装模式；2壁装模式。
	cp_int32_t							view_mode;									//该校正区域的校正模式:0表示360全景校正；1表示180全景校正；2表示Normal 校正。
	cp_int32_t							hor_offset;									//镜头中心点相对于SENSOR 中心点的水平偏移，取值范围[-127, 127]，单位为像素。
	cp_int32_t							ver_offset;									//镜头中心点相对于SENSOR 中心点的垂直偏移，取值范围[-127, 127]，单位为像素。
	cp_int32_t							trapezoid_coef;								//梯形强度系数TrapezoidCoef 只在壁装时的normal 和180 校正时有效。
	cp_int32_t							fan_strength;								//扇形强度系数FanStrength 只在180 校正时有效，用于调整图像水平方向的线条。
	cp_int32_t							in_radius;									//360 全景模式表示该校正区域所对应原图的内半径，其他模式无效
	cp_int32_t							out_radius;									//360 全景模式表示该校正区域所对应原图的外半径，其他模式为校正区域的可视半径;取值范围：[1, 2304]
	cp_int32_t							pan;										//该校正区域PTZ 参数的Pan 值.视场角的左右转动，大于180 向右转动，小于180 向左转动
	cp_int32_t							tilt;										//该校正区域PTZ 参数的Tilt 值.视场角的上下转动，大于180 向上转动，小于180 向下转动。
	cp_int32_t							hor_zoom;									//该校正区域PTZ 参数的水平Zoom 值.水平视场角大小，4095 为最大（180 度）。
	cp_int32_t							ver_zoom;									//该校正区域PTZ 参数的垂直Zoom 值.垂直视场角大小，4095 为最大（90 度）。
	cp_int32_t							outrect_x;									//该校正区域的输出位置及宽高,起始点 x位置
	cp_int32_t							outrect_y;									//该校正区域的输出位置及宽高,起始点 y位置
	cp_int32_t							outrect_width;								//该校正区域的输出位置及宽高,图像宽度
	cp_int32_t							outrect_height;								//该校正区域的输出位置及宽高,图像高度
	
	cp_int32_t							luminance;									//亮度调节参数，默认值：50，取值范围[0, 100]
	cp_int32_t							contrast;									//对比度调节参数，默认值：50，取值范围[0, 100]
	cp_int32_t							hue;										//色调调节参数，默认值：50，取值范围[0, 100]
	cp_int32_t							satuature;									//饱和度调节参数，默认值：50，取值范围[0, 100]
};


/************************************************************************/
/* 音频处理相关配置                                                      */
/************************************************************************/
struct cp_hi3516c_av_codec_configure_s
{
	cp_int32_t							width;										//表示编码器输出视频宽度
	cp_int32_t							heigth;										//表示编码器输出视频高度
	cp_int32_t							fps;										//表示编码帧率
	cp_int32_t							bitrate;									//表示编码器输出码率，单位kbps
	cp_int32_t							mode;										//表示codec工作模式，1表示vi-venc；2表示vi-fisheye-vpss-venc模式
	cp_int32_t							vi_channel;									//当codec工作模式为vi-venc时，使用的vi channel编号。取值为当前正在工作的vi channel：[0, 4]
	cp_hi3516c_av_camera_configure_t		camera_configs[CP_HI3519_AV_CAMERA_CONFIGURE_SIZE];		//表示摄像头配置文件数量
	cp_hi3516c_av_stitch_configure_t		stitch_config;								//表示stitch configure数据
};



/************************************************************************/
/*解析配置文件                                                           */
/************************************************************************/
cp_int32_t	hi3516c_av_codec_parse_configure(cp_module_t *module, cp_hi3516c_av_codec_configure_t *hacc);

/************************************************************************/
/*解析摄像头配置文件                                                     */
/************************************************************************/
cp_int32_t	hi3516c_av_codec_parse_camera_configure(cp_module_t *module, cp_hi3516c_av_codec_configure_t *hacc);

/************************************************************************/
/*解析stitch配置文件                                                     */
/************************************************************************/
cp_int32_t	hi3516c_av_codec_parse_stitch_configure(cp_module_t *module, cp_hi3516c_av_codec_configure_t *hacc);

/************************************************************************/
/*解析stitch 柱面校正配置文件                                            */
/************************************************************************/
cp_int32_t	hi3516c_av_codec_parse_cylind_stitch_correction(cp_module_t *module, cp_hi3516c_av_codec_configure_t *hacc);

/************************************************************************/
/*解析auto配置文件                                                     */
/************************************************************************/
cp_int32_t	hi3516c_av_codec_parse_auto_configure(cp_module_t *module, cp_hi3516c_av_codec_configure_t *hacc);

#endif