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
#define CP_HI3531_VPSS_CONF_STRING_ROTATE								"rotate"									//��ʾ��ת�Ƕȣ�ȡֵ[90, 180, 270, 360]
#define CP_HI3531_VPSS_CONF_STRING_IS_MIRROR							"is_mirror"									//�Ƿ�ˮƽ��ת��0��ʾ����ת��1��ʾ��ת
#define CP_HI3531_VPSS_CONF_STRING_IS_FLIP								"is_flip"									//�Ƿ�ֱ��ת��0��ʾ����ת��1��ʾ��ת
#define CP_HI3531_VPSS_CONF_STRING_MOUNT_MODE							"mount_mode"								//����У����װģʽ:0��ʾ��װģʽ��1��ʾ��װģʽ��2��װģʽ��
#define CP_HI3531_VPSS_CONF_STRING_VIEW_MODE 							"view_mode"									//��У�������У��ģʽ:0��ʾ360ȫ��У����1��ʾ180ȫ��У����2��ʾNormal У����
#define CP_HI3531_VPSS_CONF_STRING_HOR_OFFSET							"hor_offset"								//��ͷ���ĵ������SENSOR ���ĵ��ˮƽƫ�ƣ�ȡֵ��Χ[-127, 127]����λΪ���ء�
#define CP_HI3531_VPSS_CONF_STRING_VER_OFFSET 							"ver_offset"								//��ͷ���ĵ������SENSOR ���ĵ�Ĵ�ֱƫ�ƣ�ȡֵ��Χ[-127, 127]����λΪ���ء�
#define CP_HI3531_VPSS_CONF_STRING_TRAPEZOID_COEF						"trapezoid_coef"							//����ǿ��ϵ��TrapezoidCoef ֻ�ڱ�װʱ��normal ��180 У��ʱ��Ч��
#define CP_HI3531_VPSS_CONF_STRING_FAN_STRENGTH 						"fan_strength"								//����ǿ��ϵ��FanStrength ֻ��180 У��ʱ��Ч�����ڵ���ͼ��ˮƽ�����������
#define CP_HI3531_VPSS_CONF_STRING_IN_RADIUS							"in_radius"									//360 ȫ��ģʽ��ʾ��У����������Ӧԭͼ���ڰ뾶������ģʽ��Ч
#define CP_HI3531_VPSS_CONF_STRING_OUT_RADIUS							"out_radius"								//360 ȫ��ģʽ��ʾ��У����������Ӧԭͼ����뾶������ģʽΪУ������Ŀ��Ӱ뾶;ȡֵ��Χ��[1, 2304]
#define CP_HI3531_VPSS_CONF_STRING_PAN									"pan"										//��У������PTZ ������Pan ֵ.�ӳ��ǵ�����ת��������180 ����ת����С��180 ����ת��
#define CP_HI3531_VPSS_CONF_STRING_TILT 								"tilt"										//��У������PTZ ������Tilt ֵ.�ӳ��ǵ�����ת��������180 ����ת����С��180 ����ת����
#define CP_HI3531_VPSS_CONF_STRING_HOR_ZOOM								"hor_zoom"									//��У������PTZ ������ˮƽZoom ֵ.ˮƽ�ӳ��Ǵ�С��4095 Ϊ���180 �ȣ���
#define CP_HI3531_VPSS_CONF_STRING_VER_ZOOM 							"ver_zoom"									//��У������PTZ �����Ĵ�ֱZoom ֵ.��ֱ�ӳ��Ǵ�С��4095 Ϊ���90 �ȣ���
#define CP_HI3531_VPSS_CONF_STRING_OUTRECT_X							"outrect_x"									//��У����������λ�ü����,��ʼ�� xλ��
#define CP_HI3531_VPSS_CONF_STRING_OUTRECT_Y 							"outrect_y"									//��У����������λ�ü����,��ʼ�� yλ��
#define CP_HI3531_VPSS_CONF_STRING_OUTRECT_WIDTH						"outrect_width"								//��У����������λ�ü����,ͼ����
#define CP_HI3531_VPSS_CONF_STRING_OUTRECT_HEIGHT						"outrect_height"							//��У����������λ�ü����,ͼ��߶�


#define CP_HI3531_VPSS_CONF_STRING_LUMINANCE							"luminance"									//���ȵ��ڲ�����Ĭ��ֵ��50��ȡֵ��Χ[0, 100]
#define CP_HI3531_VPSS_CONF_STRING_CONTRAST								"contrast"									//�Աȶȵ��ڲ�����Ĭ��ֵ��50��ȡֵ��Χ[0, 100]
#define CP_HI3531_VPSS_CONF_STRING_HUE									"hue"										//ɫ�����ڲ�����Ĭ��ֵ��50��ȡֵ��Χ[0, 100]
#define CP_HI3531_VPSS_CONF_STRING_SATUATURE							"satuature"									//���Ͷȵ��ڲ�����Ĭ��ֵ��50��ȡֵ��Χ[0, 100]


#define CP_HI3531_VPSS_CONF_STRING_STITCH_CONFIGURE						"stitch_configure"							//stitch������
#define CP_HI3531_VPSS_CONF_STRING_OUT_WIDTH							"out_width"									//ƴ�Ӻ�ͼ��Ŀ�ȡ�Ҫ��4 ���룬ȡֵ��Χ��[64, 8188]
#define CP_HI3531_VPSS_CONF_STRING_OUT_HEIGHT							"out_height"								//ƴ�Ӻ�ͼ��ĸ߶ȡ�Ҫ��4 ���룬ȡֵ��Χ��[64, 4608]
#define CP_HI3531_VPSS_CONF_STRING_AUTO_CONFIGURE						"auto_configure"							//��ʾ����overlap_point������Ϣ,�����Զ�����;ϵͳ�����Զ�����
#define CP_HI3531_VPSS_CONF_STRING_IS_AUTO								"is_auto"									//��ʾ�Ƿ��Զ����ã�0��ʾ���Զ���1��ʾ�Զ�
#define CP_HI3531_VPSS_CONF_STRING_AUTO_SIZE							"auto_size"									//��ʾ�Զ����õĴ�С
#define CP_HI3531_VPSS_CONF_STRING_OVERLAP_POINT_CONFIGURE				"overlap_point_configure"					//��У����������λ�ü����,ͼ��߶�
#define CP_HI3531_VPSS_CONF_STRING_OVERLAP_POINT_0						"overlap_point_0"							//��У����������λ�ü����,ͼ��߶�
#define CP_HI3531_VPSS_CONF_STRING_OVERLAP_POINT_1						"overlap_point_1"							//��У����������λ�ü����,ͼ��߶�
#define CP_HI3531_VPSS_CONF_STRING_OVERLAP_POINT_2						"overlap_point_2"							//��У����������λ�ü����,ͼ��߶�
#define CP_HI3531_VPSS_CONF_STRING_OVERLAP_POINT_3						"overlap_point_3"							//��У����������λ�ü����,ͼ��߶�
#define CP_HI3531_VPSS_CONF_STRING_OVERLAP_POINT_X						"x"											//��У����������λ�ü����,ͼ��߶�
#define CP_HI3531_VPSS_CONF_STRING_OVERLAP_POINT_Y						"y"											//��У����������λ�ü����,ͼ��߶�


#define CP_HI3531_VPSS_CONF_STRING_LEFT_STITCH_CORRECTION				"left_stitch_correction"					//���ͼ�� ˫·ƴ��ʱstitching У��
#define CP_HI3531_VPSS_CONF_STRING_RIGHT_STITCH_CORRECTION				"right_stitch_correction"					//�ұ�ͼ�� ˫·ƴ��ʱstitching У��
#define CP_HI3531_VPSS_CONF_STRING_IS_USE_CYLIND						"is_use_cylind"								//�Ƿ�ʹ��cylind����У����0:��ʾ��ʹ�ã�1��ʾʹ��
#define CP_HI3531_VPSS_CONF_STRING_CENTER_HORIZONTAL_OFFSET				"center_horizontal_offset"					//����ˮƽƫ�ƣ�ȡֵ��Χ��[-127, 127]
#define CP_HI3531_VPSS_CONF_STRING_CENTER_VERTICAL_OFFSET				"center_vertical_offset"					//���Ĵ�ֱƫ�ƣ�ȡֵ��Χ��[-127, 127]
#define CP_HI3531_VPSS_CONF_STRING_RATIO								"ratio"										//����ͶӰУ���̶ȣ�ȡֵ��Χ��[0, 500]

#endif