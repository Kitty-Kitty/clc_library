/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-12-20

Description:

**************************************************************************/

#ifndef _CP_HI3531_VPSS_CONF_STRING_INCLUDE_H_
#define _CP_HI3531_VPSS_CONF_STRING_INCLUDE_H_


#define CP_HI3531_VPSS_CONF_STRING_CODEC_CONFIGURE						"codec_configure"
#define CP_HI3531_VPSS_CONF_STRING_WIDTH								"width"
#define CP_HI3531_VPSS_CONF_STRING_HEIGTH								"heigth"
#define CP_HI3531_VPSS_CONF_STRING_FPS									"fps"
#define CP_HI3531_VPSS_CONF_STRING_BITRATE								"bitrate"
#define CP_HI3531_VPSS_CONF_STRING_MODE									"mode"
#define CP_HI3531_VPSS_CONF_STRING_VENC_CHANNEL							"venc_channel"


#define CP_HI3531_VPSS_CONF_STRING_LEFT_CAMERA_CONFIGURE				"left_camera_configure"
#define CP_HI3531_VPSS_CONF_STRING_RIGHT_CAMERA_CONFIGURE				"right_camera_configure"
#define CP_HI3531_VPSS_CONF_STRING_ROTATE								"rotate"									//表示旋转角度，取值[90, 180, 270, 360]
#define CP_HI3531_VPSS_CONF_STRING_IS_MIRROR							"is_mirror"									//是否水平翻转，0表示不翻转；1表示翻转
#define CP_HI3531_VPSS_CONF_STRING_IS_FLIP								"is_flip"									//是否垂直翻转，0表示不翻转；1表示翻转
#define CP_HI3531_VPSS_CONF_STRING_MOUNT_MODE							"mount_mode"								//鱼眼校正安装模式:0表示底装模式；1表示顶装模式；2壁装模式。
#define CP_HI3531_VPSS_CONF_STRING_VIEW_MODE 							"view_mode"									//该校正区域的校正模式:0表示360全景校正；1表示180全景校正；2表示Normal 校正。
#define CP_HI3531_VPSS_CONF_STRING_HOR_OFFSET							"hor_offset"								//镜头中心点相对于SENSOR 中心点的水平偏移，取值范围[-127, 127]，单位为像素。
#define CP_HI3531_VPSS_CONF_STRING_VER_OFFSET 							"ver_offset"								//镜头中心点相对于SENSOR 中心点的垂直偏移，取值范围[-127, 127]，单位为像素。
#define CP_HI3531_VPSS_CONF_STRING_TRAPEZOID_COEF						"trapezoid_coef"							//梯形强度系数TrapezoidCoef 只在壁装时的normal 和180 校正时有效。
#define CP_HI3531_VPSS_CONF_STRING_FAN_STRENGTH 						"fan_strength"								//扇形强度系数FanStrength 只在180 校正时有效，用于调整图像水平方向的线条。
#define CP_HI3531_VPSS_CONF_STRING_IN_RADIUS							"in_radius"									//360 全景模式表示该校正区域所对应原图的内半径，其他模式无效
#define CP_HI3531_VPSS_CONF_STRING_OUT_RADIUS							"out_radius"								//360 全景模式表示该校正区域所对应原图的外半径，其他模式为校正区域的可视半径;取值范围：[1, 2304]
#define CP_HI3531_VPSS_CONF_STRING_PAN									"pan"										//该校正区域PTZ 参数的Pan 值.视场角的左右转动，大于180 向右转动，小于180 向左转动
#define CP_HI3531_VPSS_CONF_STRING_TILT 								"tilt"										//该校正区域PTZ 参数的Tilt 值.视场角的上下转动，大于180 向上转动，小于180 向下转动。
#define CP_HI3531_VPSS_CONF_STRING_HOR_ZOOM								"hor_zoom"									//该校正区域PTZ 参数的水平Zoom 值.水平视场角大小，4095 为最大（180 度）。
#define CP_HI3531_VPSS_CONF_STRING_VER_ZOOM 							"ver_zoom"									//该校正区域PTZ 参数的垂直Zoom 值.垂直视场角大小，4095 为最大（90 度）。
#define CP_HI3531_VPSS_CONF_STRING_OUTRECT_X							"outrect_x"									//该校正区域的输出位置及宽高,起始点 x位置
#define CP_HI3531_VPSS_CONF_STRING_OUTRECT_Y 							"outrect_y"									//该校正区域的输出位置及宽高,起始点 y位置
#define CP_HI3531_VPSS_CONF_STRING_OUTRECT_WIDTH						"outrect_width"								//该校正区域的输出位置及宽高,图像宽度
#define CP_HI3531_VPSS_CONF_STRING_OUTRECT_HEIGHT						"outrect_height"							//该校正区域的输出位置及宽高,图像高度


#define CP_HI3531_VPSS_CONF_STRING_LUMINANCE							"luminance"									//亮度调节参数，默认值：50，取值范围[0, 100]
#define CP_HI3531_VPSS_CONF_STRING_CONTRAST								"contrast"									//对比度调节参数，默认值：50，取值范围[0, 100]
#define CP_HI3531_VPSS_CONF_STRING_HUE									"hue"										//色调调节参数，默认值：50，取值范围[0, 100]
#define CP_HI3531_VPSS_CONF_STRING_SATUATURE							"satuature"									//饱和度调节参数，默认值：50，取值范围[0, 100]


#define CP_HI3531_VPSS_CONF_STRING_STITCH_CONFIGURE						"stitch_configure"							//stitch配置项
#define CP_HI3531_VPSS_CONF_STRING_OUT_WIDTH							"out_width"									//拼接后图像的宽度。要求4 对齐，取值范围：[64, 8188]
#define CP_HI3531_VPSS_CONF_STRING_OUT_HEIGHT							"out_height"								//拼接后图像的高度。要求4 对齐，取值范围：[64, 4608]
#define CP_HI3531_VPSS_CONF_STRING_AUTO_CONFIGURE						"auto_configure"							//表示不用overlap_point配置信息,进行自动配置;系统优先自动配置
#define CP_HI3531_VPSS_CONF_STRING_IS_AUTO								"is_auto"									//表示是否自动配置：0表示不自动；1表示自动
#define CP_HI3531_VPSS_CONF_STRING_AUTO_SIZE							"auto_size"									//表示自动配置的大小
#define CP_HI3531_VPSS_CONF_STRING_OVERLAP_POINT_CONFIGURE				"overlap_point_configure"					//该校正区域的输出位置及宽高,图像高度
#define CP_HI3531_VPSS_CONF_STRING_OVERLAP_POINT_0						"overlap_point_0"							//该校正区域的输出位置及宽高,图像高度
#define CP_HI3531_VPSS_CONF_STRING_OVERLAP_POINT_1						"overlap_point_1"							//该校正区域的输出位置及宽高,图像高度
#define CP_HI3531_VPSS_CONF_STRING_OVERLAP_POINT_2						"overlap_point_2"							//该校正区域的输出位置及宽高,图像高度
#define CP_HI3531_VPSS_CONF_STRING_OVERLAP_POINT_3						"overlap_point_3"							//该校正区域的输出位置及宽高,图像高度
#define CP_HI3531_VPSS_CONF_STRING_OVERLAP_POINT_X						"x"											//该校正区域的输出位置及宽高,图像高度
#define CP_HI3531_VPSS_CONF_STRING_OVERLAP_POINT_Y						"y"											//该校正区域的输出位置及宽高,图像高度


#define CP_HI3531_VPSS_CONF_STRING_LEFT_STITCH_CORRECTION				"left_stitch_correction"					//左边图像， 双路拼接时stitching 校正
#define CP_HI3531_VPSS_CONF_STRING_RIGHT_STITCH_CORRECTION				"right_stitch_correction"					//右边图像， 双路拼接时stitching 校正
#define CP_HI3531_VPSS_CONF_STRING_IS_USE_CYLIND						"is_use_cylind"								//是否使用cylind柱面校正，0:表示不使用；1表示使用
#define CP_HI3531_VPSS_CONF_STRING_CENTER_HORIZONTAL_OFFSET				"center_horizontal_offset"					//中心水平偏移，取值范围：[-127, 127]
#define CP_HI3531_VPSS_CONF_STRING_CENTER_VERTICAL_OFFSET				"center_vertical_offset"					//中心垂直偏移，取值范围：[-127, 127]
#define CP_HI3531_VPSS_CONF_STRING_RATIO								"ratio"										//柱面投影校正程度，取值范围：[0, 500]

#endif