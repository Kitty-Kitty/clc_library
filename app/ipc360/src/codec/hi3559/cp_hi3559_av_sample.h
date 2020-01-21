/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-12-25

Description:

**************************************************************************/

#ifndef _CP_HI3559_AV_SAMPLE_INCLUDE_H_
#define _CP_HI3559_AV_SAMPLE_INCLUDE_H_



#include "cp_hi3559_av_codec_core.h"
#include "cp_hi3559_include.h"
#include "cp_hi3559_av_define.h"



#define		CP_HI3559_AV_CODEC_PRINT_DEBUG_INFO						1			//��ʾ�Ƿ��ӡ��־
#define		CP_HI3559_AV_CODEC_USED_STITCH_CHANNEL_CROP				1			//��ʾʹ��stitchԭ����ͨ�����вü�


#define		CP_HI3559_AV_CODEC_MAX_CHANNEL_NUMBER					2			//��ʾ����ͨ����
#define		CP_HI3559_AV_CODEC_BEGIN_EXT_VI_CHANNEL_NUMBER			2			//��ʾ��ʼVI��չͨ����
#define		CP_HI3559_AV_CODEC_MAX_VPSS_CHANNEL_NUMBER				2			//��ʾ����vpssͨ����
#define		CP_HI3559_AV_CODEC_BEGIN_VPSS_CHANNEL_NUMBER			0			//��ʾ��ʼVPSSͨ����
#define		CP_HI3559_AV_CODEC_BEGIN_EXT_VPSS_CHANNEL_NUMBER		4			//��ʾ��ʼVPSS��չͨ����
#define		CP_HI3559_AV_CODEC_USED_VPSS_CHANNEL_NUMBER				0			//��ʾʹ�õ�VPSSͨ����
#define		CP_HI3559_AV_CODEC_VENC_FILE_POST_FIX_LENGTH			10			//��ʾfile post fix �ַ�
#define		CP_HI3559_AV_CODEC_VI_FISHEYE_CONFIG_LMF_LENGTH			128			//��ʾfisheye config lmf length
#define		CP_HI3559_AV_CODEC_VI_WIDTH								1920		//��ʾ������
#define		CP_HI3559_AV_CODEC_VI_HEIGHT							1080		//��ʾ����߶�
#define		CP_HI3559_AV_CODEC_VPSS_MAX_WIDTH						4096		//��ʾvpss�����
#define		CP_HI3559_AV_CODEC_VPSS_MAX_HEIGHT						1520		//��ʾvpss���߶�
#define		CP_HI3559_AV_CODEC_MAX_PACKS_SIZE						16			//����һ��������,�����ڴ�Ƶ������
#define		CP_HI3559_AV_CODEC_ERROR_SLEEP_INTERVAL_NS				2000000		//��������쳣����ʱ�䣨���룩


#define		CP_HI3559_AV_ALIGN_BACK(x, a)							((a) * (((x) / (a))))
#define		CP_HI3559_AV_SYS_ALIGN_WIDTH							64



typedef	struct cp_hi3559_av_channel_info_s							cp_hi3559_av_channel_info_t;
typedef	struct cp_hi3559_av_venc_info_s								cp_hi3559_av_venc_info_t;
typedef struct cp_hi3559_av_fisheye_info_s							cp_hi3559_av_fisheye_info_t;
typedef	struct cp_hi3559_av_vpss_channel_info_s						cp_hi3559_av_vpss_channel_info_t;
typedef	struct cp_hi3559_av_vpss_group_info_s						cp_hi3559_av_vpss_group_info_t;






#if defined(CP_HI3559_MODE)


typedef struct cp_hi_vi_config_struct
{
	cp_hi_vi_mode			enViMode;
	VIDEO_NORM_E			enNorm;           /*DC: VIDEO_ENCODING_MODE_AUTO */
	ROTATE_E				enRotate;
	cp_hi_vi_chn_set		enViChnSet;
	WDR_MODE_E				enWDRMode;
	cp_hi_framerate_mode	enFrmRate;
	cp_hi_sensor_mode		enSnsNum;
} cp_hi_vi_config_s;


/************************************************************************/
/* h3519ͨ����Ϣ                                                        */
/************************************************************************/
struct cp_hi3559_av_channel_info_s
{
	VI_CHN										index;								//��ʾ�����ͨ����
	VI_CHN										ext_index;							//��ʾ��չͨ����
	VI_DEV										dev;								//��ʾvi�豸���
	SIZE_S										pst_size;							//��ʾ����ͼƬ��С
	RECT_S										cap_rect;							//��ʾ�ü�������
	HI_U32										frame_rate;							//��ʾ��Ƶ����֡��
	cp_bool_t									is_used_fisheye;					//��ʾ�Ƿ�ʹ��fisheye
	cp_bool_t									is_used_crop;						//��ʾ�Ƿ�ʹ��crop����
	cp_bool_t									is_flip;							//�Ƿ�ֱ��ת��cp_false��ʾ����ת��cp_true��ʾ��ת
	cp_bool_t									is_mirror;							//�Ƿ�ˮƽ��ת��cp_false��ʾ����ת��cp_true��ʾ��ת
	ROTATE_E									rotate;								//��ʾ��ת�Ƕ�
	cp_hi_vi_config_s							channel_config;						//��ʾ��������
	VI_STITCH_CORRECTION_ATTR_S					stitch_attr;						//˫·ƴ��ʱstitching У��ʱ�Ľṹ��
};


/************************************************************************/
/* vpssͨ����Ϣ                                                         */
/************************************************************************/
struct cp_hi3559_av_vpss_channel_info_s
{
	VPSS_CHN									index;								//��ʾvpssͨ����
	VPSS_CHN									ext_index;							//��ʾvpss ��չͨ����
	cp_bool_t									is_used_fisheye;					//��ʾ�Ƿ�ʹ��fisheye
	VPSS_CHN_ATTR_S								attr;								//��ʾͨ��������Ϣ
	VPSS_EXT_CHN_ATTR_S							ext_attr;							//��ʾ��չ������Ϣ
	VPSS_CHN_MODE_S								mode;
	VPSS_CROP_INFO_S							crop_info;							//CROP ����������Ϣ
	ROTATE_E									rotate;								//��ʾ��ת�Ƕ�
};

/************************************************************************/
/* vpss����Ϣ                                                           */
/************************************************************************/
struct cp_hi3559_av_vpss_group_info_s
{
	VPSS_GRP									index;								//��ʾ������ͨ����
	VPSS_GRP_ATTR_S								attr;								//��ʾ������Ϣ
	VPSS_STITCH_BLEND_PARAM_S					stitch_blend_param;					//ƴ���ںϸ߼����Խṹ��
	cp_hi3559_av_vpss_channel_info_t			vpss_list[CP_HI3559_AV_CODEC_MAX_VPSS_CHANNEL_NUMBER];						//��ʾ����Ĵ������б�
};

#endif

/************************************************************************/
/* hi3559��������Ϣ                                                      */
/************************************************************************/
struct cp_hi3559_av_venc_info_s
{
	cp_char_t									file_post_fix[CP_HI3559_AV_CODEC_VENC_FILE_POST_FIX_LENGTH];		//ile post
	cp_rtp_socket_data_t						*rtp_sd;							//���������ݶ���
	cp_bool_t									is_enc;								//�Ƿ���б��봦��cp_true��ʾ���룻cp_false��ʾ������
#if defined(CP_HI3559_MODE)

	VENC_CHN									index;								//��ʾ������ͨ����
	VENC_CHN_ATTR_S								attr;								//��ʾ����������
	PAYLOAD_TYPE_E								payload;							//��ʾ������payload
	VIDEO_NORM_E								video_norm;							//��ʾ��Ƶģʽ
	PIC_SIZE_E									pic_size;							//��ʾ��Ƶ�ֱ���
	cp_hi_rc									rc;									//��ʾѹ����ʽ
	HI_U32										profile;							//
	VENC_GOP_ATTR_S								gop_attr;							//������GOP ����
	VENC_GOP_MODE_E								gop_mode;							//Gop Mode ����
	HI_S32										fd;									//��ȡ�����ļ����
	VENC_STREAM_BUF_INFO_S						stream_buf_info;					//��������Ϣ
#endif
};


/************************************************************************/
/* hi3559��������Ϣ                                                      */
/************************************************************************/
struct cp_hi3559_av_fisheye_info_s
{
	cp_fisheye_type_e							fisheye_type;													//��������
#if defined(CP_HI3559_MODE)
	FISHEYE_CONFIG_S							fisheye_config;													//��ʾvi��fisheye������Ϣ
	FISHEYE_ATTR_S								fisheye_attr;													//��ʾvi��fisheye����
#endif
};


/************************************************************************/
/* hi3559������Ϣ                                                        */
/************************************************************************/
struct cp_hi3559_av_conf_s
{
	cp_hi3559_av_codec_t						*hi3559_av_codec;												//��������Ϣ
	cp_thread_t									*thread;														//���ݻ�ȡ�߳�
	cp_rtp_socket_data_t						*rtp_sd_list[CP_HI3559_AV_CODEC_MAX_CHANNEL_NUMBER];			//��ʾ���ݶ���
	cp_bool_t									is_process_stream;												//��ʾ�Ƿ�������cp_true:��ʾһֱ����cp_false:��ʾֹͣ����
	cp_bool_t									is_used_vi_rotate;												//��ʾ�Ƿ�ʹ��vi����ת����
	cp_bool_t									is_process_angle;												//��ʾ�Ƿ����ֱ�Ǵ���
	cp_hi3559_av_venc_info_t					venc_list[1];													//��ʾ����ı������б�

#if defined(CP_HI3559_MODE)
	MPP_SYS_CONF_S								mpp_sys_conf;													//MPPϵͳ��������
	VB_CONF_S									vb_conf;														//��Ƶ���������
	VIDEO_NORM_E								video_norm;														//������Ƶ������ʽ����
	PIC_SIZE_E									pic_size;														//��ʾͼƬ��С
	SIZE_S										sensor_size;													//��ʾsensorͼƬ��С
	SIZE_S										vi_output_pic_size;												//��ʾvi���ͼ���С
	SIZE_S										vpss_output_pst_size;											//��ʾvpss���ͼ���С
	SIZE_S										stitch_input_pst_size;											//��ʾvpss����ͼ���С
	cp_hi3559_av_fisheye_info_t					fisheye_info[CP_HI3559_AV_CODEC_MAX_CHANNEL_NUMBER];			//��ʾfisheye������Ϣ
	cp_hi3559_av_vpss_group_info_t				stitch_vpss_info;												//��ʾvpss��Ϣ
	cp_hi3559_av_vpss_group_info_t				process_vpss_info[CP_HI3559_AV_CODEC_MAX_CHANNEL_NUMBER];	//��ʾvpss��Ϣ
	cp_hi3559_av_channel_info_t					channel_list[CP_HI3559_AV_CODEC_MAX_CHANNEL_NUMBER];			//��ʾ�����ͨ���б�
#endif
};

/*��ʾ����conf��Ϣ*/
cp_int32_t create_hi3559_av_codec_conf(cp_hi3559_av_codec_t *hi3559_av_codec, cp_hi3559_av_conf_t *hi3559_av_conf);

/*��ʼ��hi3559 ��Ϣ*/
cp_int32_t hi3559_av_init_info(cp_hi3559_av_codec_t *hi3559_av_codec, cp_hi3559_av_conf_t *hi3559_av_conf);

/*��ʼ��hi3559 ��Ϣ*/
cp_int32_t hi3559_av_init_info_bak(cp_hi3559_av_codec_t *hi3559_av_codec, cp_hi3559_av_conf_t *hi3559_av_conf);

/*��ʼ��������Ϣ*/
cp_int32_t hi3559_av_system_init(cp_hi3559_av_codec_t *hi3559_av_codec, cp_hi3559_av_conf_t *hi3559_av_conf);

/*�ж�vi vpss�Ƿ�����*/
cp_bool_t hi3559_av_is_vi_vpss_online(cp_hi3559_av_codec_t *hi3559_av_codec);


/*��ʼ��vi������Ϣ*/
cp_int32_t init_hi3559_av_vi_conf(cp_hi3559_av_codec_t *hi3559_av_codec, cp_hi3559_av_conf_t *hi3559_av_conf);

/*��ʼ��vi fisheye������Ϣ*/
cp_int32_t init_hi3559_av_fisheye_conf(cp_hi3559_av_codec_t *hi3559_av_codec, cp_hi3559_av_conf_t *hi3559_av_conf, cp_fisheye_type_e fisheye_type);

/*��ʼ��vi fisheye������Ϣ*/
cp_int32_t init_hi3559_av_fisheye_conf_from_config(cp_hi3559_av_codec_t *hi3559_av_codec, cp_hi3559_av_conf_t *hi3559_av_conf, cp_fisheye_type_e fisheye_type);

/*��ʼ��������������Ϣ*/
cp_int32_t init_hi3559_av_venc_conf(cp_hi3559_av_codec_t *hi3559_av_codec, cp_hi3559_av_conf_t *hi3559_av_conf);

#if defined(CP_HI3559_MODE)
cp_int32_t hi3559_av_venc_get_gopattr(cp_hi3559_av_codec_t *hi3559_av_codec, VENC_GOP_MODE_E gopmode, VENC_GOP_ATTR_S *pstgopattr, VIDEO_NORM_E norm);
#endif

/*��ʼ��ͼ������������Ϣ*/
cp_int32_t init_hi3559_av_stitch_vpss_conf(cp_hi3559_av_codec_t *hi3559_av_codec, cp_hi3559_av_conf_t *hi3559_av_conf);

/*��ʼ��ͼ������sttich������Ϣ*/
cp_int32_t init_hi3559_av_stitch_vpss_stitch_conf(cp_hi3559_av_codec_t *hi3559_av_codec, cp_hi3559_av_conf_t *hi3559_av_conf);

/*��ʼ��ͼ������sttich auto������Ϣ*/
cp_int32_t init_hi3559_av_stitch_vpss_stitch_auto_conf(cp_hi3559_av_codec_t *hi3559_av_codec, cp_hi3559_av_conf_t *hi3559_av_conf);

/*��ʼ��ͼ������sttich detail������Ϣ*/
cp_int32_t init_hi3559_av_stitch_vpss_stitch_detail_conf(cp_hi3559_av_codec_t *hi3559_av_codec, cp_hi3559_av_conf_t *hi3559_av_conf);

/*��ʼ��ͼ������������Ϣ*/
cp_int32_t init_hi3559_av_process_vpss_conf(cp_hi3559_av_codec_t *hi3559_av_codec, cp_hi3559_av_conf_t *hi3559_av_conf);

/*˫·ƴ��ʱstitching У��ʱ�Ľṹ��*/
cp_int32_t init_hi3559_av_stitch_correction_attr(cp_hi3559_av_codec_t *hi3559_av_codec, cp_hi3559_av_conf_t *hi3559_av_conf);

/*˫·ƴ��ʱstitching LDCͰ��У��ʱ�Ľṹ��*/
cp_int32_t init_hi3559_av_stitch_correction_attr_ldc(cp_hi3559_av_codec_t *hi3559_av_codec, cp_hi3559_av_conf_t *hi3559_av_conf);

/*˫·ƴ��ʱstitching CYLIND����У��ʱ�Ľṹ��*/
cp_int32_t init_hi3559_av_stitch_correction_attr_cylind(cp_hi3559_av_codec_t *hi3559_av_codec, cp_hi3559_av_conf_t *hi3559_av_conf);

/*��ʼ��hi3559 info �豸*/
cp_int32_t init_hi3559_av_info_mode_vi_venc(cp_hi3559_av_codec_t *hi3559_av_codec, cp_hi3559_av_conf_t *hi3559_av_conf);

/*��ʼ��hi3559 info �豸*/
cp_int32_t init_hi3559_av_info_mode_vi_stitch_vpss_venc(cp_hi3559_av_codec_t *hi3559_av_codec, cp_hi3559_av_conf_t *hi3559_av_conf);

/*��ʼ��hi3559 info �豸*/
cp_int32_t init_hi3559_av_info_mode_vi_fisheye_stitch_vpss_venc(cp_hi3559_av_codec_t *hi3559_av_codec, cp_hi3559_av_conf_t *hi3559_av_conf);

/*��ʼ��hi3559 info �豸*/
cp_int32_t init_hi3559_av_info_mode_vi_fisheye_process_vpss_venc(cp_hi3559_av_codec_t *hi3559_av_codec, cp_hi3559_av_conf_t *hi3559_av_conf);

/*��ʼ��hi3559 info �豸*/
cp_int32_t init_hi3559_av_info_mode_vi_fisheye_process_vpss_stitch_vpss_venc(cp_hi3559_av_codec_t *hi3559_av_codec, cp_hi3559_av_conf_t *hi3559_av_conf);

/*��ʼ��hi3559 info �豸*/
cp_int32_t init_hi3559_av_info_mode_vi_process_vpss_fisheye_stitch_vpss_venc(cp_hi3559_av_codec_t *hi3559_av_codec, cp_hi3559_av_conf_t *hi3559_av_conf);




/*����hi3559 info �豸*/
cp_int32_t start_hi3559_av_info(cp_hi3559_av_codec_t *hi3559_av_codec, cp_hi3559_av_conf_t *hi3559_av_conf);

/*����hi3559 info �豸*/
cp_int32_t start_hi3559_av_info_bak(cp_hi3559_av_codec_t *hi3559_av_codec, cp_hi3559_av_conf_t *hi3559_av_conf);

/*����hi3559 info �豸*/
cp_int32_t start_hi3559_av_info_mode_vi_venc(cp_hi3559_av_codec_t *hi3559_av_codec, cp_hi3559_av_conf_t *hi3559_av_conf);

/*����hi3559 info �豸*/
cp_int32_t start_hi3559_av_info_mode_vi_stitch_vpss_venc(cp_hi3559_av_codec_t *hi3559_av_codec, cp_hi3559_av_conf_t *hi3559_av_conf);

/*����hi3559 info �豸*/
cp_int32_t start_hi3559_av_info_mode_vi_fisheye_stitch_vpss_venc(cp_hi3559_av_codec_t *hi3559_av_codec, cp_hi3559_av_conf_t *hi3559_av_conf);

/*����hi3559 info �豸*/
cp_int32_t start_hi3559_av_info_mode_vi_fisheye_process_vpss_venc(cp_hi3559_av_codec_t *hi3559_av_codec, cp_hi3559_av_conf_t *hi3559_av_conf);

/*����hi3559 info �豸*/
cp_int32_t start_hi3559_av_info_mode_vi_fisheye_process_vpss_stitch_vpss_venc(cp_hi3559_av_codec_t *hi3559_av_codec, cp_hi3559_av_conf_t *hi3559_av_conf);

/*����hi3559 info �豸*/
cp_int32_t start_hi3559_av_info_mode_vi_process_vpss_fisheye_stitch_vpss_venc(cp_hi3559_av_codec_t *hi3559_av_codec, cp_hi3559_av_conf_t *hi3559_av_conf);




/*����hi3559 vi �豸*/
cp_int32_t	start_hi3559_av_vi(cp_hi3559_av_codec_t *hi3559_av_codec, cp_hi3559_av_conf_t *hi3559_av_conf);

/*����hi3559 vi _ext_channel�豸*/
cp_int32_t	start_hi3559_av_vi_ext_channel(cp_hi3559_av_codec_t *hi3559_av_codec, cp_hi3559_av_conf_t *hi3559_av_conf);

/*����vi������*/
cp_int32_t update_hi3559_av_vi_attr(cp_hi3559_av_codec_t *hi3559_av_codec, cp_hi3559_av_conf_t *hi3559_av_conf);

/*����vi��rotate����ʵ�ִ�ֱ��ת*/
cp_int32_t update_hi3559_av_vi_rotate(cp_hi3559_av_codec_t *hi3559_av_codec, cp_hi3559_av_conf_t *hi3559_av_conf);

/*����vi�Ĵ�ֱ��תflip����*/
cp_int32_t update_hi3559_av_vi_flip(cp_hi3559_av_codec_t *hi3559_av_codec, cp_hi3559_av_conf_t *hi3559_av_conf);

/*����vi�� SetSpreadAttr����*/
cp_int32_t update_hi3559_av_vi_set_spread_attr(cp_hi3559_av_codec_t *hi3559_av_codec, cp_hi3559_av_conf_t *hi3559_av_conf);

/*����vi�� ldc����*/
cp_int32_t update_hi3559_av_vi_set_ldc_attr(cp_hi3559_av_codec_t *hi3559_av_codec, cp_hi3559_av_conf_t *hi3559_av_conf);

/*����vi�� csc����*/
cp_int32_t update_hi3559_av_vi_set_csc_attr(cp_hi3559_av_codec_t *hi3559_av_codec, cp_hi3559_av_conf_t *hi3559_av_conf);

/*˫·ƴ��ʱstitching У��ʱ�Ľṹ��*/
cp_int32_t	update_hi3559_av_stitch_correction_attr_cylink(cp_hi3559_av_codec_t *hi3559_av_codec, cp_hi3559_av_conf_t *hi3559_av_conf);

/*˫·ƴ��ʱstitching У��ʱ�Ľṹ��*/
cp_int32_t	update_hi3559_av_stitch_correction_attr_ldc(cp_hi3559_av_codec_t *hi3559_av_codec, cp_hi3559_av_conf_t *hi3559_av_conf);

/*����hi3559 vi fisheye�豸*/
cp_int32_t	start_hi3559_av_fisheye(cp_hi3559_av_codec_t *hi3559_av_codec, cp_hi3559_av_conf_t *hi3559_av_conf);

/*����hi3559 vpss �豸*/
cp_int32_t	start_hi3559_av_stitch_vpss(cp_hi3559_av_codec_t *hi3559_av_codec, cp_hi3559_av_conf_t *hi3559_av_conf);

/*����hi3559 ext vpss �豸*/
cp_int32_t	start_hi3559_av_process_vpss(cp_hi3559_av_codec_t *hi3559_av_codec, cp_hi3559_av_conf_t *hi3559_av_conf);

/*����hi3559 ext vpss channel�豸*/
cp_int32_t	start_hi3559_av_process_vpss_ext_channel(cp_hi3559_av_codec_t *hi3559_av_codec, cp_hi3559_av_conf_t *hi3559_av_conf);

/*����vi��rotate����ʵ�ִ�ֱ��ת*/
cp_int32_t update_hi3559_av_vpss_rotate(cp_hi3559_av_codec_t *hi3559_av_codec, cp_hi3559_av_conf_t *hi3559_av_conf);

/*����vi�Ĵ�ֱ��תflip����*/
cp_int32_t update_hi3559_av_vpss_flip(cp_hi3559_av_codec_t *hi3559_av_codec, cp_hi3559_av_conf_t *hi3559_av_conf);

/*����hi3559 venc �豸*/
cp_int32_t	start_hi3559_av_general_venc(cp_hi3559_av_codec_t *hi3559_av_codec, cp_hi3559_av_conf_t *hi3559_av_conf);

/*����hi3559 ���õ� venc �豸*/
cp_int32_t	start_hi3559_av_config_venc(cp_hi3559_av_codec_t *hi3559_av_codec, cp_hi3559_av_conf_t *hi3559_av_conf);

/*����һ��hi3559 venc �豸*/
cp_int32_t	start_hi3559_av_one_venc(cp_hi3559_av_codec_t *hi3559_av_codec, cp_hi3559_av_conf_t *hi3559_av_conf, cp_hi3559_av_venc_info_t *venc_info);

/*����Ϣ*/
cp_int32_t	hi3559_av_bind_info(cp_hi3559_av_codec_t *hi3559_av_codec, cp_hi3559_av_conf_t *hi3559_av_conf);

/*��vi �� vpss*/
cp_int32_t	hi3559_av_bind_vi_vpss(cp_hi3559_av_codec_t *hi3559_av_codec, cp_hi3559_av_conf_t *hi3559_av_conf);

/*��vi fisheye �� vpss*/
cp_int32_t	hi3559_av_bind_vi_fisheye_vpss(cp_hi3559_av_codec_t *hi3559_av_codec, cp_hi3559_av_conf_t *hi3559_av_conf);

/*��vi �� process_vpss*/
cp_int32_t	hi3559_av_bind_vi_process_vpss(cp_hi3559_av_codec_t *hi3559_av_codec, cp_hi3559_av_conf_t *hi3559_av_conf);

/*��vi �� process_vpss*/
cp_int32_t	hi3559_av_bind_vi_fisheye_process_vpss(cp_hi3559_av_codec_t *hi3559_av_codec, cp_hi3559_av_conf_t *hi3559_av_conf);

/*��vpss �� process_vpss*/
cp_int32_t	hi3559_av_bind_process_vpss_stitch_vpss(cp_hi3559_av_codec_t *hi3559_av_codec, cp_hi3559_av_conf_t *hi3559_av_conf);

/*��vpss �� process_vpss*/
cp_int32_t	hi3559_av_bind_process_vpss_ext_channel_stitch_vpss(cp_hi3559_av_codec_t *hi3559_av_codec, cp_hi3559_av_conf_t *hi3559_av_conf);

/*��process vpss �� venc*/
cp_int32_t	hi3559_av_bind_process_vpss_venc(cp_hi3559_av_codec_t *hi3559_av_codec, cp_hi3559_av_conf_t *hi3559_av_conf);

/*��stitch vpss �� venc*/
cp_int32_t	hi3559_av_bind_stitch_vpss_venc(cp_hi3559_av_codec_t *hi3559_av_codec, cp_hi3559_av_conf_t *hi3559_av_conf);

/*��vi �� venc*/
cp_int32_t	hi3559_av_bind_vi_fisheye_venc(cp_hi3559_av_codec_t *hi3559_av_codec, cp_hi3559_av_conf_t *hi3559_av_conf);

/*��ʼ��ȡ����hi3559 venc */
cp_int32_t	start_hi3559_av_get_stream(cp_hi3559_av_codec_t *hi3559_av_codec, cp_hi3559_av_conf_t *hi3559_av_conf);

/*��ʼ��ȡ����hi3559 venc �߳�*/
cp_int32_t	start_hi3559_av_get_stream_thread(cp_hi3559_av_codec_t *hi3559_av_codec, cp_hi3559_av_conf_t *hi3559_av_conf);

/*����ý��������*/
cp_void_t	hi3559_av_stream_proc(cp_void_t* codec);

#if defined(CP_HI3559_MODE)
cp_int32_t hi3559_av_save_memory_stream(cp_hi3559_av_codec_t *hi3559_av_codec,
	cp_hi3559_av_venc_info_t *venc_info, VENC_STREAM_S *stream);

cp_int32_t hi3559_av_save_memory_h264(cp_hi3559_av_codec_t *hi3559_av_codec,
	cp_hi3559_av_venc_info_t *venc_info, VENC_STREAM_S *stream);

cp_int32_t hi3559_av_save_physical_stream(cp_hi3559_av_codec_t *hi3559_av_codec,
	cp_hi3559_av_venc_info_t *venc_info, VENC_STREAM_S *stream);

cp_int32_t hi3559_av_send_memory_stream(cp_hi3559_av_codec_t *hi3559_av_codec,
	cp_hi3559_av_venc_info_t *venc_info, VENC_STREAM_S *stream);

cp_int32_t hi3559_av_send_memory_h264(cp_hi3559_av_codec_t *hi3559_av_codec,
	cp_hi3559_av_venc_info_t *venc_info, VENC_STREAM_S *stream);

cp_int32_t hi3559_av_send_physical_stream(cp_hi3559_av_codec_t *hi3559_av_codec,
	cp_hi3559_av_venc_info_t *venc_info, VENC_STREAM_S *stream);

/******************************************************************************
* funciton : get file postfix according palyload_type.
******************************************************************************/
HI_S32 hi3559_av_get_file_post_fix(PAYLOAD_TYPE_E enPayload, char* szFilePostfix);

/******************************************************************************
* funciton : Start venc stream mode (h264, mjpeg)
* note      : rate control parameter need adjust, according your case.
******************************************************************************/
HI_S32 hi3559_av_venc_start(VENC_CHN VencChn, PAYLOAD_TYPE_E enType, VIDEO_NORM_E enNorm,
	PIC_SIZE_E enSize, cp_hi_rc enRcMode, HI_U32  u32Profile, VENC_GOP_ATTR_S *pstGopAttr);

/******************************************************************************
* function : get picture size(w*h), according Norm and enPicSize
******************************************************************************/
HI_S32 hi3559_av_sys_get_picture_size(VIDEO_NORM_E enNorm, PIC_SIZE_E enPicSize, SIZE_S* pstSize);

#endif




/*ֹͣ��ȡ����hi3559 venc �߳�*/
cp_int32_t	stop_hi3559_av_get_stream_thread(cp_hi3559_av_codec_t *hi3559_av_codec, cp_hi3559_av_conf_t *hi3559_av_conf);

/*ֹͣ��ȡ����hi3559 venc */
cp_int32_t	stop_hi3559_av_get_stream(cp_hi3559_av_codec_t *hi3559_av_codec, cp_hi3559_av_conf_t *hi3559_av_conf);

/*�����vpss �� venc*/
cp_int32_t	hi3559_av_unbind_vpss_venc(cp_hi3559_av_codec_t *hi3559_av_codec, cp_hi3559_av_conf_t *hi3559_av_conf);

/*�����vi �� vpss*/
cp_int32_t	hi3559_av_unbind_vi_vpss(cp_hi3559_av_codec_t *hi3559_av_codec, cp_hi3559_av_conf_t *hi3559_av_conf);

/*�����vi �� process_vpss*/
cp_int32_t	hi3559_av_unbind_vi_process_vpss(cp_hi3559_av_codec_t *hi3559_av_codec, cp_hi3559_av_conf_t *hi3559_av_conf);

/*�����process_vpss �� vpss*/
cp_int32_t	hi3559_av_unbind_process_vpss_vpss(cp_hi3559_av_codec_t *hi3559_av_codec, cp_hi3559_av_conf_t *hi3559_av_conf);

/*�����vi �� venc*/
cp_int32_t	hi3559_av_unbind_vi_fisheye_venc(cp_hi3559_av_codec_t *hi3559_av_codec, cp_hi3559_av_conf_t *hi3559_av_conf);

/*�������Ϣ*/
cp_int32_t	hi3559_av_unbind_info(cp_hi3559_av_codec_t *hi3559_av_codec, cp_hi3559_av_conf_t *hi3559_av_conf);






/*ֹͣhi3559 venc �豸*/
cp_int32_t	stop_hi3559_av_venc(cp_hi3559_av_codec_t *hi3559_av_codec, cp_hi3559_av_conf_t *hi3559_av_conf);

/*ֹͣhi3559 venc �豸*/
cp_int32_t	stop_hi3559_av_stitch_vpss(cp_hi3559_av_codec_t *hi3559_av_codec, cp_hi3559_av_conf_t *hi3559_av_conf);

/*ֹͣhi3559 vi �豸*/
cp_int32_t	stop_hi3559_av_vi(cp_hi3559_av_codec_t *hi3559_av_codec, cp_hi3559_av_conf_t *hi3559_av_conf);

/*ֹͣhi3559 �豸*/
cp_int32_t	stop_hi3559_av_info(cp_hi3559_av_codec_t *hi3559_av_codec, cp_hi3559_av_conf_t *hi3559_av_conf);


cp_int32_t hi3559_av_system_destroy(cp_hi3559_av_codec_t *hi3559_av_codec, cp_hi3559_av_conf_t *hi3559_av_conf);

/*��ʾ����conf��Ϣ*/
cp_int32_t destroy_hi3559_av_codec_conf(cp_hi3559_av_codec_t *hi3559_av_codec);

/*ֹͣ����*/
cp_int32_t stop_hi3559_all(cp_hi3559_av_codec_t *hi3559_av_codec, cp_hi3559_av_conf_t *hi3559_av_conf);



#endif