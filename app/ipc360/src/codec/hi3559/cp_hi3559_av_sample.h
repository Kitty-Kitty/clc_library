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



#define		CP_HI3559_AV_CODEC_PRINT_DEBUG_INFO						1			//表示是否打印日志
#define		CP_HI3559_AV_CODEC_USED_STITCH_CHANNEL_CROP				1			//表示使用stitch原来的通道进行裁剪


#define		CP_HI3559_AV_CODEC_MAX_CHANNEL_NUMBER					2			//表示最大的通道数
#define		CP_HI3559_AV_CODEC_BEGIN_EXT_VI_CHANNEL_NUMBER			2			//表示起始VI扩展通道号
#define		CP_HI3559_AV_CODEC_MAX_VPSS_CHANNEL_NUMBER				2			//表示最大的vpss通道数
#define		CP_HI3559_AV_CODEC_BEGIN_VPSS_CHANNEL_NUMBER			0			//表示起始VPSS通道号
#define		CP_HI3559_AV_CODEC_BEGIN_EXT_VPSS_CHANNEL_NUMBER		4			//表示起始VPSS扩展通道号
#define		CP_HI3559_AV_CODEC_USED_VPSS_CHANNEL_NUMBER				0			//表示使用的VPSS通道号
#define		CP_HI3559_AV_CODEC_VENC_FILE_POST_FIX_LENGTH			10			//表示file post fix 字符
#define		CP_HI3559_AV_CODEC_VI_FISHEYE_CONFIG_LMF_LENGTH			128			//表示fisheye config lmf length
#define		CP_HI3559_AV_CODEC_VI_WIDTH								1920		//表示输入宽度
#define		CP_HI3559_AV_CODEC_VI_HEIGHT							1080		//表示输入高度
#define		CP_HI3559_AV_CODEC_VPSS_MAX_WIDTH						4096		//表示vpss最大宽度
#define		CP_HI3559_AV_CODEC_VPSS_MAX_HEIGHT						1520		//表示vpss最大高度
#define		CP_HI3559_AV_CODEC_MAX_PACKS_SIZE						16			//定义一个最大包数,降低内存频繁申请
#define		CP_HI3559_AV_CODEC_ERROR_SLEEP_INTERVAL_NS				2000000		//定义出现异常休眠时间（纳秒）


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
/* h3519通道信息                                                        */
/************************************************************************/
struct cp_hi3559_av_channel_info_s
{
	VI_CHN										index;								//表示定义的通道号
	VI_CHN										ext_index;							//表示扩展通道号
	VI_DEV										dev;								//表示vi设备编号
	SIZE_S										pst_size;							//表示处理图片大小
	RECT_S										cap_rect;							//表示裁剪的区域
	HI_U32										frame_rate;							//表示视频输入帧率
	cp_bool_t									is_used_fisheye;					//表示是否使用fisheye
	cp_bool_t									is_used_crop;						//表示是否使用crop内容
	cp_bool_t									is_flip;							//是否垂直翻转，cp_false表示不翻转；cp_true表示翻转
	cp_bool_t									is_mirror;							//是否水平翻转，cp_false表示不翻转；cp_true表示翻转
	ROTATE_E									rotate;								//表示旋转角度
	cp_hi_vi_config_s							channel_config;						//表示输入配置
	VI_STITCH_CORRECTION_ATTR_S					stitch_attr;						//双路拼接时stitching 校正时的结构体
};


/************************************************************************/
/* vpss通道信息                                                         */
/************************************************************************/
struct cp_hi3559_av_vpss_channel_info_s
{
	VPSS_CHN									index;								//表示vpss通道号
	VPSS_CHN									ext_index;							//表示vpss 扩展通道号
	cp_bool_t									is_used_fisheye;					//表示是否使用fisheye
	VPSS_CHN_ATTR_S								attr;								//表示通道属性信息
	VPSS_EXT_CHN_ATTR_S							ext_attr;							//表示扩展属性信息
	VPSS_CHN_MODE_S								mode;
	VPSS_CROP_INFO_S							crop_info;							//CROP 功能所需信息
	ROTATE_E									rotate;								//表示旋转角度
};

/************************************************************************/
/* vpss组信息                                                           */
/************************************************************************/
struct cp_hi3559_av_vpss_group_info_s
{
	VPSS_GRP									index;								//表示处理器通道号
	VPSS_GRP_ATTR_S								attr;								//表示属性信息
	VPSS_STITCH_BLEND_PARAM_S					stitch_blend_param;					//拼接融合高级属性结构体
	cp_hi3559_av_vpss_channel_info_t			vpss_list[CP_HI3559_AV_CODEC_MAX_VPSS_CHANNEL_NUMBER];						//表示定义的处理器列表
};

#endif

/************************************************************************/
/* hi3559编码器信息                                                      */
/************************************************************************/
struct cp_hi3559_av_venc_info_s
{
	cp_char_t									file_post_fix[CP_HI3559_AV_CODEC_VENC_FILE_POST_FIX_LENGTH];		//ile post
	cp_rtp_socket_data_t						*rtp_sd;							//编码器数据队列
	cp_bool_t									is_enc;								//是否进行编码处理，cp_true表示编码；cp_false表示不编码
#if defined(CP_HI3559_MODE)

	VENC_CHN									index;								//表示编码器通道号
	VENC_CHN_ATTR_S								attr;								//表示编码器属性
	PAYLOAD_TYPE_E								payload;							//表示编码器payload
	VIDEO_NORM_E								video_norm;							//表示视频模式
	PIC_SIZE_E									pic_size;							//表示视频分辨率
	cp_hi_rc									rc;									//表示压缩方式
	HI_U32										profile;							//
	VENC_GOP_ATTR_S								gop_attr;							//编码器GOP 属性
	VENC_GOP_MODE_E								gop_mode;							//Gop Mode 类型
	HI_S32										fd;									//获取流的文件句柄
	VENC_STREAM_BUF_INFO_S						stream_buf_info;					//流缓存信息
#endif
};


/************************************************************************/
/* hi3559编码器信息                                                      */
/************************************************************************/
struct cp_hi3559_av_fisheye_info_s
{
	cp_fisheye_type_e							fisheye_type;													//鱼眼类型
#if defined(CP_HI3559_MODE)
	FISHEYE_CONFIG_S							fisheye_config;													//表示vi的fisheye配置信息
	FISHEYE_ATTR_S								fisheye_attr;													//表示vi的fisheye属性
#endif
};


/************************************************************************/
/* hi3559配置信息                                                        */
/************************************************************************/
struct cp_hi3559_av_conf_s
{
	cp_hi3559_av_codec_t						*hi3559_av_codec;												//编码器信息
	cp_thread_t									*thread;														//数据获取线程
	cp_rtp_socket_data_t						*rtp_sd_list[CP_HI3559_AV_CODEC_MAX_CHANNEL_NUMBER];			//表示数据队列
	cp_bool_t									is_process_stream;												//表示是否处理流；cp_true:表示一直处理；cp_false:表示停止处理
	cp_bool_t									is_used_vi_rotate;												//表示是否使用vi的旋转操作
	cp_bool_t									is_process_angle;												//表示是否进行直角处理
	cp_hi3559_av_venc_info_t					venc_list[1];													//表示定义的编码器列表

#if defined(CP_HI3559_MODE)
	MPP_SYS_CONF_S								mpp_sys_conf;													//MPP系统控制属性
	VB_CONF_S									vb_conf;														//视频缓存池属性
	VIDEO_NORM_E								video_norm;														//定义视频输入制式类型
	PIC_SIZE_E									pic_size;														//表示图片大小
	SIZE_S										sensor_size;													//表示sensor图片大小
	SIZE_S										vi_output_pic_size;												//表示vi输出图像大小
	SIZE_S										vpss_output_pst_size;											//表示vpss输出图像大小
	SIZE_S										stitch_input_pst_size;											//表示vpss输入图像大小
	cp_hi3559_av_fisheye_info_t					fisheye_info[CP_HI3559_AV_CODEC_MAX_CHANNEL_NUMBER];			//表示fisheye配置信息
	cp_hi3559_av_vpss_group_info_t				stitch_vpss_info;												//表示vpss信息
	cp_hi3559_av_vpss_group_info_t				process_vpss_info[CP_HI3559_AV_CODEC_MAX_CHANNEL_NUMBER];	//表示vpss信息
	cp_hi3559_av_channel_info_t					channel_list[CP_HI3559_AV_CODEC_MAX_CHANNEL_NUMBER];			//表示定义的通道列表
#endif
};

/*表示创建conf信息*/
cp_int32_t create_hi3559_av_codec_conf(cp_hi3559_av_codec_t *hi3559_av_codec, cp_hi3559_av_conf_t *hi3559_av_conf);

/*初始化hi3559 信息*/
cp_int32_t hi3559_av_init_info(cp_hi3559_av_codec_t *hi3559_av_codec, cp_hi3559_av_conf_t *hi3559_av_conf);

/*初始化hi3559 信息*/
cp_int32_t hi3559_av_init_info_bak(cp_hi3559_av_codec_t *hi3559_av_codec, cp_hi3559_av_conf_t *hi3559_av_conf);

/*初始化配置信息*/
cp_int32_t hi3559_av_system_init(cp_hi3559_av_codec_t *hi3559_av_codec, cp_hi3559_av_conf_t *hi3559_av_conf);

/*判断vi vpss是否在线*/
cp_bool_t hi3559_av_is_vi_vpss_online(cp_hi3559_av_codec_t *hi3559_av_codec);


/*初始化vi配置信息*/
cp_int32_t init_hi3559_av_vi_conf(cp_hi3559_av_codec_t *hi3559_av_codec, cp_hi3559_av_conf_t *hi3559_av_conf);

/*初始化vi fisheye配置信息*/
cp_int32_t init_hi3559_av_fisheye_conf(cp_hi3559_av_codec_t *hi3559_av_codec, cp_hi3559_av_conf_t *hi3559_av_conf, cp_fisheye_type_e fisheye_type);

/*初始化vi fisheye配置信息*/
cp_int32_t init_hi3559_av_fisheye_conf_from_config(cp_hi3559_av_codec_t *hi3559_av_codec, cp_hi3559_av_conf_t *hi3559_av_conf, cp_fisheye_type_e fisheye_type);

/*初始化编码器配置信息*/
cp_int32_t init_hi3559_av_venc_conf(cp_hi3559_av_codec_t *hi3559_av_codec, cp_hi3559_av_conf_t *hi3559_av_conf);

#if defined(CP_HI3559_MODE)
cp_int32_t hi3559_av_venc_get_gopattr(cp_hi3559_av_codec_t *hi3559_av_codec, VENC_GOP_MODE_E gopmode, VENC_GOP_ATTR_S *pstgopattr, VIDEO_NORM_E norm);
#endif

/*初始化图像处理器配置信息*/
cp_int32_t init_hi3559_av_stitch_vpss_conf(cp_hi3559_av_codec_t *hi3559_av_codec, cp_hi3559_av_conf_t *hi3559_av_conf);

/*初始化图像处理器sttich配置信息*/
cp_int32_t init_hi3559_av_stitch_vpss_stitch_conf(cp_hi3559_av_codec_t *hi3559_av_codec, cp_hi3559_av_conf_t *hi3559_av_conf);

/*初始化图像处理器sttich auto配置信息*/
cp_int32_t init_hi3559_av_stitch_vpss_stitch_auto_conf(cp_hi3559_av_codec_t *hi3559_av_codec, cp_hi3559_av_conf_t *hi3559_av_conf);

/*初始化图像处理器sttich detail配置信息*/
cp_int32_t init_hi3559_av_stitch_vpss_stitch_detail_conf(cp_hi3559_av_codec_t *hi3559_av_codec, cp_hi3559_av_conf_t *hi3559_av_conf);

/*初始化图像处理器配置信息*/
cp_int32_t init_hi3559_av_process_vpss_conf(cp_hi3559_av_codec_t *hi3559_av_codec, cp_hi3559_av_conf_t *hi3559_av_conf);

/*双路拼接时stitching 校正时的结构体*/
cp_int32_t init_hi3559_av_stitch_correction_attr(cp_hi3559_av_codec_t *hi3559_av_codec, cp_hi3559_av_conf_t *hi3559_av_conf);

/*双路拼接时stitching LDC桶形校正时的结构体*/
cp_int32_t init_hi3559_av_stitch_correction_attr_ldc(cp_hi3559_av_codec_t *hi3559_av_codec, cp_hi3559_av_conf_t *hi3559_av_conf);

/*双路拼接时stitching CYLIND柱面校正时的结构体*/
cp_int32_t init_hi3559_av_stitch_correction_attr_cylind(cp_hi3559_av_codec_t *hi3559_av_codec, cp_hi3559_av_conf_t *hi3559_av_conf);

/*初始化hi3559 info 设备*/
cp_int32_t init_hi3559_av_info_mode_vi_venc(cp_hi3559_av_codec_t *hi3559_av_codec, cp_hi3559_av_conf_t *hi3559_av_conf);

/*初始化hi3559 info 设备*/
cp_int32_t init_hi3559_av_info_mode_vi_stitch_vpss_venc(cp_hi3559_av_codec_t *hi3559_av_codec, cp_hi3559_av_conf_t *hi3559_av_conf);

/*初始化hi3559 info 设备*/
cp_int32_t init_hi3559_av_info_mode_vi_fisheye_stitch_vpss_venc(cp_hi3559_av_codec_t *hi3559_av_codec, cp_hi3559_av_conf_t *hi3559_av_conf);

/*初始化hi3559 info 设备*/
cp_int32_t init_hi3559_av_info_mode_vi_fisheye_process_vpss_venc(cp_hi3559_av_codec_t *hi3559_av_codec, cp_hi3559_av_conf_t *hi3559_av_conf);

/*初始化hi3559 info 设备*/
cp_int32_t init_hi3559_av_info_mode_vi_fisheye_process_vpss_stitch_vpss_venc(cp_hi3559_av_codec_t *hi3559_av_codec, cp_hi3559_av_conf_t *hi3559_av_conf);

/*初始化hi3559 info 设备*/
cp_int32_t init_hi3559_av_info_mode_vi_process_vpss_fisheye_stitch_vpss_venc(cp_hi3559_av_codec_t *hi3559_av_codec, cp_hi3559_av_conf_t *hi3559_av_conf);




/*启动hi3559 info 设备*/
cp_int32_t start_hi3559_av_info(cp_hi3559_av_codec_t *hi3559_av_codec, cp_hi3559_av_conf_t *hi3559_av_conf);

/*启动hi3559 info 设备*/
cp_int32_t start_hi3559_av_info_bak(cp_hi3559_av_codec_t *hi3559_av_codec, cp_hi3559_av_conf_t *hi3559_av_conf);

/*启动hi3559 info 设备*/
cp_int32_t start_hi3559_av_info_mode_vi_venc(cp_hi3559_av_codec_t *hi3559_av_codec, cp_hi3559_av_conf_t *hi3559_av_conf);

/*启动hi3559 info 设备*/
cp_int32_t start_hi3559_av_info_mode_vi_stitch_vpss_venc(cp_hi3559_av_codec_t *hi3559_av_codec, cp_hi3559_av_conf_t *hi3559_av_conf);

/*启动hi3559 info 设备*/
cp_int32_t start_hi3559_av_info_mode_vi_fisheye_stitch_vpss_venc(cp_hi3559_av_codec_t *hi3559_av_codec, cp_hi3559_av_conf_t *hi3559_av_conf);

/*启动hi3559 info 设备*/
cp_int32_t start_hi3559_av_info_mode_vi_fisheye_process_vpss_venc(cp_hi3559_av_codec_t *hi3559_av_codec, cp_hi3559_av_conf_t *hi3559_av_conf);

/*启动hi3559 info 设备*/
cp_int32_t start_hi3559_av_info_mode_vi_fisheye_process_vpss_stitch_vpss_venc(cp_hi3559_av_codec_t *hi3559_av_codec, cp_hi3559_av_conf_t *hi3559_av_conf);

/*启动hi3559 info 设备*/
cp_int32_t start_hi3559_av_info_mode_vi_process_vpss_fisheye_stitch_vpss_venc(cp_hi3559_av_codec_t *hi3559_av_codec, cp_hi3559_av_conf_t *hi3559_av_conf);




/*启动hi3559 vi 设备*/
cp_int32_t	start_hi3559_av_vi(cp_hi3559_av_codec_t *hi3559_av_codec, cp_hi3559_av_conf_t *hi3559_av_conf);

/*启动hi3559 vi _ext_channel设备*/
cp_int32_t	start_hi3559_av_vi_ext_channel(cp_hi3559_av_codec_t *hi3559_av_codec, cp_hi3559_av_conf_t *hi3559_av_conf);

/*更新vi的属性*/
cp_int32_t update_hi3559_av_vi_attr(cp_hi3559_av_codec_t *hi3559_av_codec, cp_hi3559_av_conf_t *hi3559_av_conf);

/*更新vi的rotate属性实现垂直翻转*/
cp_int32_t update_hi3559_av_vi_rotate(cp_hi3559_av_codec_t *hi3559_av_codec, cp_hi3559_av_conf_t *hi3559_av_conf);

/*更新vi的垂直翻转flip属性*/
cp_int32_t update_hi3559_av_vi_flip(cp_hi3559_av_codec_t *hi3559_av_codec, cp_hi3559_av_conf_t *hi3559_av_conf);

/*更新vi的 SetSpreadAttr属性*/
cp_int32_t update_hi3559_av_vi_set_spread_attr(cp_hi3559_av_codec_t *hi3559_av_codec, cp_hi3559_av_conf_t *hi3559_av_conf);

/*更新vi的 ldc属性*/
cp_int32_t update_hi3559_av_vi_set_ldc_attr(cp_hi3559_av_codec_t *hi3559_av_codec, cp_hi3559_av_conf_t *hi3559_av_conf);

/*更新vi的 csc属性*/
cp_int32_t update_hi3559_av_vi_set_csc_attr(cp_hi3559_av_codec_t *hi3559_av_codec, cp_hi3559_av_conf_t *hi3559_av_conf);

/*双路拼接时stitching 校正时的结构体*/
cp_int32_t	update_hi3559_av_stitch_correction_attr_cylink(cp_hi3559_av_codec_t *hi3559_av_codec, cp_hi3559_av_conf_t *hi3559_av_conf);

/*双路拼接时stitching 校正时的结构体*/
cp_int32_t	update_hi3559_av_stitch_correction_attr_ldc(cp_hi3559_av_codec_t *hi3559_av_codec, cp_hi3559_av_conf_t *hi3559_av_conf);

/*设置hi3559 vi fisheye设备*/
cp_int32_t	start_hi3559_av_fisheye(cp_hi3559_av_codec_t *hi3559_av_codec, cp_hi3559_av_conf_t *hi3559_av_conf);

/*启动hi3559 vpss 设备*/
cp_int32_t	start_hi3559_av_stitch_vpss(cp_hi3559_av_codec_t *hi3559_av_codec, cp_hi3559_av_conf_t *hi3559_av_conf);

/*启动hi3559 ext vpss 设备*/
cp_int32_t	start_hi3559_av_process_vpss(cp_hi3559_av_codec_t *hi3559_av_codec, cp_hi3559_av_conf_t *hi3559_av_conf);

/*启动hi3559 ext vpss channel设备*/
cp_int32_t	start_hi3559_av_process_vpss_ext_channel(cp_hi3559_av_codec_t *hi3559_av_codec, cp_hi3559_av_conf_t *hi3559_av_conf);

/*更新vi的rotate属性实现垂直翻转*/
cp_int32_t update_hi3559_av_vpss_rotate(cp_hi3559_av_codec_t *hi3559_av_codec, cp_hi3559_av_conf_t *hi3559_av_conf);

/*更新vi的垂直翻转flip属性*/
cp_int32_t update_hi3559_av_vpss_flip(cp_hi3559_av_codec_t *hi3559_av_codec, cp_hi3559_av_conf_t *hi3559_av_conf);

/*启动hi3559 venc 设备*/
cp_int32_t	start_hi3559_av_general_venc(cp_hi3559_av_codec_t *hi3559_av_codec, cp_hi3559_av_conf_t *hi3559_av_conf);

/*启动hi3559 配置的 venc 设备*/
cp_int32_t	start_hi3559_av_config_venc(cp_hi3559_av_codec_t *hi3559_av_codec, cp_hi3559_av_conf_t *hi3559_av_conf);

/*启动一个hi3559 venc 设备*/
cp_int32_t	start_hi3559_av_one_venc(cp_hi3559_av_codec_t *hi3559_av_codec, cp_hi3559_av_conf_t *hi3559_av_conf, cp_hi3559_av_venc_info_t *venc_info);

/*绑定信息*/
cp_int32_t	hi3559_av_bind_info(cp_hi3559_av_codec_t *hi3559_av_codec, cp_hi3559_av_conf_t *hi3559_av_conf);

/*绑定vi 和 vpss*/
cp_int32_t	hi3559_av_bind_vi_vpss(cp_hi3559_av_codec_t *hi3559_av_codec, cp_hi3559_av_conf_t *hi3559_av_conf);

/*绑定vi fisheye 和 vpss*/
cp_int32_t	hi3559_av_bind_vi_fisheye_vpss(cp_hi3559_av_codec_t *hi3559_av_codec, cp_hi3559_av_conf_t *hi3559_av_conf);

/*绑定vi 和 process_vpss*/
cp_int32_t	hi3559_av_bind_vi_process_vpss(cp_hi3559_av_codec_t *hi3559_av_codec, cp_hi3559_av_conf_t *hi3559_av_conf);

/*绑定vi 和 process_vpss*/
cp_int32_t	hi3559_av_bind_vi_fisheye_process_vpss(cp_hi3559_av_codec_t *hi3559_av_codec, cp_hi3559_av_conf_t *hi3559_av_conf);

/*绑定vpss 和 process_vpss*/
cp_int32_t	hi3559_av_bind_process_vpss_stitch_vpss(cp_hi3559_av_codec_t *hi3559_av_codec, cp_hi3559_av_conf_t *hi3559_av_conf);

/*绑定vpss 和 process_vpss*/
cp_int32_t	hi3559_av_bind_process_vpss_ext_channel_stitch_vpss(cp_hi3559_av_codec_t *hi3559_av_codec, cp_hi3559_av_conf_t *hi3559_av_conf);

/*绑定process vpss 和 venc*/
cp_int32_t	hi3559_av_bind_process_vpss_venc(cp_hi3559_av_codec_t *hi3559_av_codec, cp_hi3559_av_conf_t *hi3559_av_conf);

/*绑定stitch vpss 和 venc*/
cp_int32_t	hi3559_av_bind_stitch_vpss_venc(cp_hi3559_av_codec_t *hi3559_av_codec, cp_hi3559_av_conf_t *hi3559_av_conf);

/*绑定vi 和 venc*/
cp_int32_t	hi3559_av_bind_vi_fisheye_venc(cp_hi3559_av_codec_t *hi3559_av_codec, cp_hi3559_av_conf_t *hi3559_av_conf);

/*开始获取数据hi3559 venc */
cp_int32_t	start_hi3559_av_get_stream(cp_hi3559_av_codec_t *hi3559_av_codec, cp_hi3559_av_conf_t *hi3559_av_conf);

/*开始获取数据hi3559 venc 线程*/
cp_int32_t	start_hi3559_av_get_stream_thread(cp_hi3559_av_codec_t *hi3559_av_codec, cp_hi3559_av_conf_t *hi3559_av_conf);

/*处理媒体流数据*/
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




/*停止获取数据hi3559 venc 线程*/
cp_int32_t	stop_hi3559_av_get_stream_thread(cp_hi3559_av_codec_t *hi3559_av_codec, cp_hi3559_av_conf_t *hi3559_av_conf);

/*停止获取数据hi3559 venc */
cp_int32_t	stop_hi3559_av_get_stream(cp_hi3559_av_codec_t *hi3559_av_codec, cp_hi3559_av_conf_t *hi3559_av_conf);

/*解除绑定vpss 和 venc*/
cp_int32_t	hi3559_av_unbind_vpss_venc(cp_hi3559_av_codec_t *hi3559_av_codec, cp_hi3559_av_conf_t *hi3559_av_conf);

/*解除绑定vi 和 vpss*/
cp_int32_t	hi3559_av_unbind_vi_vpss(cp_hi3559_av_codec_t *hi3559_av_codec, cp_hi3559_av_conf_t *hi3559_av_conf);

/*解除绑定vi 和 process_vpss*/
cp_int32_t	hi3559_av_unbind_vi_process_vpss(cp_hi3559_av_codec_t *hi3559_av_codec, cp_hi3559_av_conf_t *hi3559_av_conf);

/*解除绑定process_vpss 和 vpss*/
cp_int32_t	hi3559_av_unbind_process_vpss_vpss(cp_hi3559_av_codec_t *hi3559_av_codec, cp_hi3559_av_conf_t *hi3559_av_conf);

/*解除绑定vi 和 venc*/
cp_int32_t	hi3559_av_unbind_vi_fisheye_venc(cp_hi3559_av_codec_t *hi3559_av_codec, cp_hi3559_av_conf_t *hi3559_av_conf);

/*解除绑定信息*/
cp_int32_t	hi3559_av_unbind_info(cp_hi3559_av_codec_t *hi3559_av_codec, cp_hi3559_av_conf_t *hi3559_av_conf);






/*停止hi3559 venc 设备*/
cp_int32_t	stop_hi3559_av_venc(cp_hi3559_av_codec_t *hi3559_av_codec, cp_hi3559_av_conf_t *hi3559_av_conf);

/*停止hi3559 venc 设备*/
cp_int32_t	stop_hi3559_av_stitch_vpss(cp_hi3559_av_codec_t *hi3559_av_codec, cp_hi3559_av_conf_t *hi3559_av_conf);

/*停止hi3559 vi 设备*/
cp_int32_t	stop_hi3559_av_vi(cp_hi3559_av_codec_t *hi3559_av_codec, cp_hi3559_av_conf_t *hi3559_av_conf);

/*停止hi3559 设备*/
cp_int32_t	stop_hi3559_av_info(cp_hi3559_av_codec_t *hi3559_av_codec, cp_hi3559_av_conf_t *hi3559_av_conf);


cp_int32_t hi3559_av_system_destroy(cp_hi3559_av_codec_t *hi3559_av_codec, cp_hi3559_av_conf_t *hi3559_av_conf);

/*表示消毁conf信息*/
cp_int32_t destroy_hi3559_av_codec_conf(cp_hi3559_av_codec_t *hi3559_av_codec);

/*停止所有*/
cp_int32_t stop_hi3559_all(cp_hi3559_av_codec_t *hi3559_av_codec, cp_hi3559_av_conf_t *hi3559_av_conf);



#endif