/*******************************************************************************
*
*Copyright:novigo
*
*File name: cp_hi3559_av_define.h
*
*Author:fangzhenmu@novigo.com.cn
*
*Version: 1.0
*
*Date:2018/04/27
*
*Description: create (cp_hi3559_av_define.h)
*
*Others:
*
*History:
*******************************************************************************/

#ifndef _CP_HI3559_AV_DEFINE_H_
#define _CP_HI3559_AV_DEFINE_H_



/*******************************************************
enum define
*******************************************************/

typedef enum cp_hi_ispcfg_opt_enum
{
	cp_hi_ispcfg_opt_none = 0,
	cp_hi_ispcfg_opt_save = 1,
	cp_hi_ispcfg_opt_load = 2,
	cp_hi_ispcfg_opt_butt
} sample_cfg_opt;

typedef enum cp_hi_vi_mode_enum
{
	cp_hi_vi_mode_aptina_ar0130_dc_720p_30fps = 0,
	cp_hi_vi_mode_aptina_9m034_dc_720p_30fps,
	cp_hi_vi_mode_sony_imx122_dc_1080p_30fps,
	cp_hi_vi_mode_aptina_mt9p006_dc_1080p_30fps,
	cp_hi_vi_mode_sample_vi_mode_1_d1,
	cp_hi_vi_mode_sample_vi_mode_bt1120_1080i,
	cp_hi_vi_mode_sample_vi_mode_bt1120_720p,
	cp_hi_vi_mode_sample_vi_mode_bt1120_1080p,
	cp_hi_vi_mode_panasonic_mn34220_sublvds_1080p_30fps,
	cp_hi_vi_mode_panasonic_mn34220_sublvds_720p_120fps,
	cp_hi_vi_mode_sony_imx178_lvds_1080p_30fps,
	cp_hi_vi_mode_sony_imx185_mipi_1080p_30fps,
	cp_hi_vi_mode_sony_imx290_mipi_1080p_30fps,
	cp_hi_vi_mode_panasonic_mn34220_mipi_1080p_30fps,
	cp_hi_vi_mode_panasonic_mn34220_mipi_720p_120fps,
	cp_hi_vi_mode_sony_imx178_lvds_5m_30fps,
	cp_hi_vi_mode_sony_imx226_lvds_4k_30fps,
	cp_hi_vi_mode_sony_imx226_lvds_9m_30fps,
	cp_hi_vi_mode_sony_imx226_lvds_12m_30fps,
	cp_hi_vi_mode_sony_imx226_lvds_4k_60fps,
	cp_hi_vi_mode_sony_imx117_lvds_4k_30fps,
	cp_hi_vi_mode_sony_imx117_lvds_12m_28fps,
	cp_hi_vi_mode_sony_imx117_lvds_1080p_120fps,
	cp_hi_vi_mode_sony_imx117_lvds_720p_240fps,
	cp_hi_vi_mode_sony_imx377_mipi_8m_30fps_10bit,
	cp_hi_vi_mode_sony_imx377_mipi_8m_60fps_10bit,
	cp_hi_vi_mode_sony_imx377_mipi_1080p_120fps_12bit,
	cp_hi_vi_mode_sony_imx377_mipi_720p_240fps_10bit,
	cp_hi_vi_mode_sony_imx377_mipi_12m_30fps_12bit,
	cp_hi_vi_mode_sony_imx377_mipi_8m_30fps_12bit,
	cp_hi_vi_mode_sony_imx274_lvds_4k_30fps,
	cp_hi_vi_mode_panasonic_mn34120_lvds_16m_16p25fps,
	cp_hi_vi_mode_panasonic_mn34120_lvds_4k_30fps,
	cp_hi_vi_mode_panasonic_mn34120_lvds_1080p_60fps,
	cp_hi_vi_mode_aptina_ar0230_hispi_1080p_30fps,
	cp_hi_vi_mode_aptina_ar0330_mipi_1080p_30fps,
	cp_hi_vi_mode_aptina_ar0330_mipi_1536p_25fps,
	cp_hi_vi_mode_aptina_ar0330_mipi_1296p_25fps,
	cp_hi_vi_mode_omnivision_ov4689_mipi_4m_30fps,
	cp_hi_vi_mode_omnivision_ov4689_mipi_1080p_30fps,
	cp_hi_vi_mode_omnivision_ov5658_mipi_5m_30fps,
} cp_hi_vi_mode;

typedef enum cp_hi_vi_dev_enum
{
	cp_hi_vi_dev_bt656_d1_1mux = 0,
	cp_hi_vi_dev_bt656_d1_4mux,
	cp_hi_vi_dev_bt656_960h_1mux,
	cp_hi_vi_dev_bt656_960h_4mux,
	cp_hi_vi_dev_720p_hd_1mux,
	cp_hi_vi_dev_1080p_hd_1mux,
	cp_hi_vi_dev_butt
} cp_hi_vi_dev;

typedef enum cp_hi_vi_chn_set_enum
{
	cp_hi_vi_chn_set_normal = 0,		/* mirror, flip close */
	cp_hi_vi_chn_set_mirror,			/* open mirror */
	cp_hi_vi_chn_set_flip,				/* open filp */
	cp_hi_vi_chn_set_flip_mirror		/* mirror, flip */
} cp_hi_vi_chn_set;

typedef enum cp_hi_bind_mode_enum
{
	cp_hi_bind_mode_vi_vo = 0,			/* vi bind to vo */
	cp_hi_bind_mode_vpss_vo,			/* vpss bind to vo */
	cp_hi_bind_mode_vi_vpss_vo,			/* vi bind to vpss, vpss bind to vo */
	cp_hi_bind_mode_butt
} cp_hi_bind_mode;

typedef enum cp_hi_framerate_mode_enum
{
	cp_hi_framerate_mode_default = 0,
	cp_hi_framerate_mode_15fps = 15,
	cp_hi_framerate_mode_20fps = 20,
	cp_hi_framerate_mode_30fps = 30,
	cp_hi_framerate_mode_60fps = 60,
	cp_hi_framerate_mode_120fps = 120,
	cp_hi_framerate_mode_butt,
} cp_hi_framerate_mode;

typedef enum cp_hi_vo_mode_enum
{
	cp_hi_vo_mode_1mux = 0,
	cp_hi_vo_mode_2mux = 1,
	cp_hi_vo_mode_butt
} cp_hi_vo_mode;

typedef enum cp_hi_rc_enum
{
	cp_hi_rc_cbr = 0,
	cp_hi_rc_vbr,
	cp_hi_rc_avbr,
	cp_hi_rc_fixqp
} cp_hi_rc;

typedef enum cp_hi_cp_hi_rgn_change_type_enum
{
	cp_hi_rgn_change_type_fgalpha = 0,
	cp_hi_rgn_change_type_bgalpha,
	cp_hi_rgn_change_type_layer
} cp_hi_rgn_change_type;

typedef enum cp_hi_sensor_mode_enum
{
	cp_hi_sensor_mode_single = 0,
	cp_hi_sensor_mode_double = 1,
	cp_hi_sensor_mode_but
} cp_hi_sensor_mode;



#endif //_CP_HI3559_AV_DEFINE_H_


