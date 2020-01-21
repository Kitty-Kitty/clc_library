/*******************************************************************************
*
*Copyright:novigo
*
*File name: cp_hi3531_vo_proc.c
*
*Author:fangzhenmu@novigo.com.cn
*
*Version: 1.0
*
*Date:2017/07/28
*
*Description: create (cp_hi3531_vo_proc.c)
*
*Others:
*
*History:
*******************************************************************************/

#include "cp_hi3531_vo_proc.h"
#include "cp_hi3531_dev_info.h"


/*******************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: hi3531_vo_get_resolution_attribute
*
* ����ȫ��: hi3531_vo_get_resolution_attribute
*
* ��������: public
*
* ����˵��: ��ȡ�豸�ķֱ�����Ϣ
*
* ��    ��: cp_int32_t intf_sync						[in/out]����˵��
* ��    ��: cp_int32_t * width						[in/out]����˵��
* ��    ��: cp_int32_t * height						[in/out]����˵��
* ��    ��: cp_int32_t * frame_rate						[in/out]����˵��
*
* �� �� ֵ: cp_int32_t
*           0  : �ɹ�
*         ��0  : ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2017-7-28 15:03:57
********************************************************************************/
cp_int32_t hi3531_vo_get_resolution_attribute(cp_int32_t intf_sync, cp_int32_t *width, cp_int32_t *height, cp_int32_t *frame_rate)
{
	cp_hi3531_vo_resolution_attribute_t				tmp_ra[] = {
		{ CP_HI3531_VO_INTF_SYNC_PAL, 720, 576, 25 },
		{ CP_HI3531_VO_INTF_SYNC_NTSC, 720, 480, 30 },
		{ CP_HI3531_VO_INTF_SYNC_800x600_60, 800, 600, 60 },
		{ CP_HI3531_VO_INTF_SYNC_720P50, 1280, 720, 50 },
		{ CP_HI3531_VO_INTF_SYNC_1080P24, 1920, 1080, 24 },
		{ CP_HI3531_VO_INTF_SYNC_720P60, 1280, 720, 60 },
		{ CP_HI3531_VO_INTF_SYNC_1080P30, 1920, 1080, 30 },
		{ CP_HI3531_VO_INTF_SYNC_1080P25, 1920, 1080, 25 },
		{ CP_HI3531_VO_INTF_SYNC_1080P50, 1920, 1080, 50 },
		{ CP_HI3531_VO_INTF_SYNC_1080P60, 1920, 1080, 60 },
		{ CP_HI3531_VO_INTF_SYNC_1024x768_60, 1024, 768, 60 },
		{ CP_HI3531_VO_INTF_SYNC_1280x1024_60, 1280, 1024, 60 },
		{ CP_HI3531_VO_INTF_SYNC_1366x768_60, 1366, 768, 60 },
		{ CP_HI3531_VO_INTF_SYNC_1440x900_60, 1440, 900, 60 },
		{ CP_HI3531_VO_INTF_SYNC_1280x800_60, 1280, 800, 60 },
	};

	if (intf_sync < CP_HI3531_VO_INTF_SYNC_PAL || intf_sync > CP_HI3531_VO_INTF_SYNC_1280x800_60) {
		return -1;
	}

	*width = tmp_ra[intf_sync].width;
	*height = tmp_ra[intf_sync].height;
	*frame_rate = tmp_ra[intf_sync].frame_rate;

	return 0;
}

/*******************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: hi3531_vo_set_mem_conf
*
* ����ȫ��: hi3531_vo_set_mem_conf
*
* ��������: public
*
* ����˵��: �豸�ڴ���Ϣ
*
* ��    ��: cp_hi3531_vo_t * hi3531_vo						[in/out]����˵��
* ��    ��: cp_hi3531_dev_vo_configure_t * vo_conf						[in/out]����˵��
*
* �� �� ֵ: cp_int32_t
*           0  : �ɹ�
*         ��0  : ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2017-7-28 15:16:16
********************************************************************************/
cp_int32_t hi3531_vo_set_mem_conf(cp_hi3531_vo_t *hi3531_vo, cp_hi3531_dev_vo_configure_t *vo_conf)
{
	cp_int32_t										tmp_ret_int = 0;



	if (!hi3531_vo || !vo_conf) {
		return -1;
	}

#if defined(CP_HI3531_DEV_MODE)

	/* config vo dev */
	hi3531_vo->vo_mpp_channel.enModId = HI_ID_VOU;
	hi3531_vo->vo_mpp_channel.s32DevId = vo_conf->dev_id;
	hi3531_vo->vo_mpp_channel.s32ChnId = vo_conf->channel_id;

	if (!cp_strlen(vo_conf->mem_name)) {
		tmp_ret_int = HI_MPI_SYS_SetMemConf(&hi3531_vo->vo_mpp_channel, CP_NULL);
	}
	else {
		tmp_ret_int = HI_MPI_SYS_SetMemConf(&hi3531_vo->vo_mpp_channel, vo_conf->mem_name);
	}

	if (HI_SUCCESS != tmp_ret_int) {
		cp_hi3531_dev_log(error, hi3531_vo,
			"HI_MPI_SYS_SetMemConf() dev[id:%d channel:%d mem_name:%s] failed!",
			hi3531_vo->vo_mpp_channel.s32DevId,
			vo_conf->channel_id,
			vo_conf->mem_name
			);
		return -1;
	}
	else {
		cp_hi3531_dev_log(notice, hi3531_vo,
			"HI_MPI_SYS_SetMemConf() dev[id:%d channel:%d mem_name:%s] successed!",
			hi3531_vo->vo_mpp_channel.s32DevId,
			vo_conf->channel_id,
			vo_conf->mem_name
			);
	}

#endif

	return 0;
}

/*******************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: hi3531_vo_set_pub_attr
*
* ����ȫ��: hi3531_vo_set_pub_attr
*
* ��������: public
*
* ����˵��: ��Ƶ����������Խṹ��
*
* ��    ��: cp_hi3531_vo_t * hi3531_vo						[in/out]����˵��
* ��    ��: cp_hi3531_dev_vo_configure_t * vo_conf						[in/out]����˵��
*
* �� �� ֵ: cp_int32_t
*           0  : �ɹ�
*         ��0  : ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2017-7-28 16:04:20
********************************************************************************/
cp_int32_t hi3531_vo_set_pub_attr(cp_hi3531_vo_t *hi3531_vo, cp_hi3531_dev_vo_configure_t *vo_conf)
{

#if defined(CP_HI3531_DEV_MODE)
	hi3531_vo->vo_pub_attr.enIntfSync = vo_conf->intf_sync;
	hi3531_vo->vo_pub_attr.enIntfType = (0x01L << vo_conf->intf_type);
	hi3531_vo->vo_pub_attr.u32BgColor = cp_htoi(vo_conf->back_color, cp_strlen(vo_conf->back_color));;
	hi3531_vo->vo_pub_attr.bDoubleFrame = vo_conf->enable_double_frame;
#endif
	return 0;
}

/*******************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: hi3531_vo_set_dev_video_layer
*
* ����ȫ��: hi3531_vo_set_dev_video_layer
*
* ��������: public
*
* ����˵��: �����豸ͼ����Ϣ
*
* ��    ��: cp_hi3531_vo_t * hi3531_vo						[in/out]����˵��
* ��    ��: cp_hi3531_dev_vo_configure_t * vo_conf						[in/out]����˵��
*
* �� �� ֵ: cp_int32_t
*           0  : �ɹ�
*         ��0  : ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2017-7-28 15:32:20
********************************************************************************/
cp_int32_t hi3531_vo_set_dev_video_layer(cp_hi3531_vo_t *hi3531_vo, cp_hi3531_dev_vo_configure_t *vo_conf)
{
#if defined(CP_HI3531_DEV_MODE)
	cp_int32_t				tmp_width = 0;
	cp_int32_t				tmp_height = 0;
	cp_int32_t				tmp_frame_rate = 0;
	cp_int32_t				tmp_ret_int = 0;


	tmp_ret_int = hi3531_vo_get_resolution_attribute(vo_conf->intf_sync, &tmp_width, &tmp_height, &tmp_frame_rate);
	if (tmp_ret_int) {
		cp_hi3531_dev_log(error, hi3531_vo, 
			"hi3531_vo_get_resolution_attribute() failed! intf_sync[%d]",
			vo_conf->intf_sync);
		return tmp_ret_int;
	}

	hi3531_vo->vo_video_layer_attr.enPixFormat = PIXEL_FORMAT_YUV_SEMIPLANAR_420;
	hi3531_vo->vo_video_layer_attr.u32DispFrmRt = vo_conf->source_frame_rate;

	hi3531_vo->vo_video_layer_attr.stDispRect.s32X = 0;
	hi3531_vo->vo_video_layer_attr.stDispRect.s32Y = 0;
	hi3531_vo->vo_video_layer_attr.stDispRect.u32Width = tmp_width;
	hi3531_vo->vo_video_layer_attr.stDispRect.u32Height = tmp_height;
	hi3531_vo->vo_video_layer_attr.stImageSize.u32Width = tmp_width;
	hi3531_vo->vo_video_layer_attr.stImageSize.u32Height = tmp_height;
#endif
	return 0;
}

/*******************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: hi3531_vo_set_channels_conf
*
* ����ȫ��: hi3531_vo_set_channels_conf
*
* ��������: public
*
* ����˵��: ����voͨ����Ϣ
*
* ��    ��: cp_hi3531_vo_t * hi3531_vo						[in/out]����˵��
* ��    ��: cp_hi3531_dev_vo_configure_t * vo_conf						[in/out]����˵��
*
* �� �� ֵ: cp_int32_t
*           0  : �ɹ�
*         ��0  : ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2017-7-29 17:33:21
********************************************************************************/
cp_int32_t hi3531_vo_set_channels_conf(cp_hi3531_vo_t *hi3531_vo, cp_hi3531_dev_vo_configure_t *vo_conf)
{
	hi3531_vo->vo_channels[0].id = 0;
	hi3531_vo->vo_channels[0].is_used = cp_true;

#if defined(CP_HI3531_DEV_MODE)

	hi3531_vo->vo_channels[0].attr.stRect.s32X = 0;
	hi3531_vo->vo_channels[0].attr.stRect.s32X = CP_ALIGN_BACK(0, 2);
	hi3531_vo->vo_channels[0].attr.stRect.s32Y = CP_ALIGN_BACK(0, 2);
	hi3531_vo->vo_channels[0].attr.stRect.u32Width = CP_ALIGN_BACK(hi3531_vo->vo_video_layer_attr.stDispRect.u32Width, 2);
	hi3531_vo->vo_channels[0].attr.stRect.u32Height = CP_ALIGN_BACK(hi3531_vo->vo_video_layer_attr.stImageSize.u32Height, 2);
	hi3531_vo->vo_channels[0].attr.u32Priority = 0;
	hi3531_vo->vo_channels[0].attr.bDeflicker = HI_FALSE;
#endif
	return 0;
}






/*******************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: hi3531_vo_start_dev_video_layer
*
* ����ȫ��: hi3531_vo_start_dev_video_layer
*
* ��������: public
*
* ����˵��: �����豸ͼ����Ϣ
*
* ��    ��: cp_hi3531_vo_t * hi3531_vo						[in/out]����˵��
* ��    ��: cp_hi3531_dev_vo_configure_t * vo_conf						[in/out]����˵��
*
* �� �� ֵ: cp_int32_t
*           0  : �ɹ�
*         ��0  : ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2017-7-28 15:22:41
********************************************************************************/
cp_int32_t hi3531_vo_start_dev_video_layer(cp_hi3531_vo_t *hi3531_vo, cp_hi3531_dev_vo_configure_t *vo_conf)
{
	cp_int32_t										tmp_ret_int = 0;



#if defined(CP_HI3531_DEV_MODE)

	tmp_ret_int = HI_MPI_VO_SetPubAttr(hi3531_vo->vo_mpp_channel.s32DevId, &hi3531_vo->vo_pub_attr);
	if (HI_SUCCESS != tmp_ret_int) {
		cp_hi3531_dev_log(error, hi3531_vo, 
			"HI_MPI_VO_SetPubAttr() dev[id:%d] failed! error_code[0x%x]",
			hi3531_vo->vo_mpp_channel.s32DevId,
			tmp_ret_int
			);
		return -1;
	}

	tmp_ret_int = HI_MPI_VO_Enable(hi3531_vo->vo_mpp_channel.s32DevId);
	if (HI_SUCCESS != tmp_ret_int) {
		cp_hi3531_dev_log(error, hi3531_vo, 
			"HI_MPI_VO_Enable() dev[id:%d] failed! error_code[0x%x]",
			hi3531_vo->vo_mpp_channel.s32DevId,
			tmp_ret_int
			);
		return -2;
	}

	tmp_ret_int = HI_MPI_VO_SetVideoLayerAttr(hi3531_vo->vo_mpp_channel.s32DevId, &hi3531_vo->vo_video_layer_attr);
	if (HI_SUCCESS != tmp_ret_int) {
		cp_hi3531_dev_log(error, hi3531_vo, 
			"HI_MPI_VO_SetVideoLayerAttr() dev[id:%d] failed! error_code[0x%x]",
			hi3531_vo->vo_mpp_channel.s32DevId,
			tmp_ret_int
			);
		return -3;
	}

	tmp_ret_int = HI_MPI_VO_EnableVideoLayer(hi3531_vo->vo_mpp_channel.s32DevId);
	if (HI_SUCCESS != tmp_ret_int) {
		cp_hi3531_dev_log(error, hi3531_vo, 
			"HI_MPI_VO_EnableVideoLayer() dev[id:%d] failed! error_code[0x%x]",
			hi3531_vo->vo_mpp_channel.s32DevId,
			tmp_ret_int
			);
		return -4;
	}

#endif

	return tmp_ret_int;
}

/*******************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: hi3531_vo_start_dev
*
* ����ȫ��: hi3531_vo_start_dev_channels
*
* ��������: public
*
* ����˵��: �����豸ͨ�����豸��Ϣ
*
* ��    ��: cp_hi3531_vo_t * hi3531_vo						[in/out]����˵��
* ��    ��: cp_hi3531_dev_vo_configure_t * vo_conf						[in/out]����˵��
*
* �� �� ֵ: cp_int32_t
*           0  : �ɹ�
*         ��0  : ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2017-7-29 17:55:34
********************************************************************************/
cp_int32_t hi3531_vo_start_dev_channels(cp_hi3531_vo_t *hi3531_vo, cp_hi3531_dev_vo_configure_t *vo_conf)
{
	cp_int32_t										tmp_ret_int = 0;
	cp_int32_t										i = 0;


#if defined(CP_HI3531_DEV_MODE)
	for (i = 0; i < cp_ary_size(hi3531_vo->vo_channels); i++) {
		if (!hi3531_vo->vo_channels[i].is_used) {
			continue;
		}

		tmp_ret_int = HI_MPI_VO_SetChnAttr(hi3531_vo->vo_mpp_channel.s32DevId, 
			hi3531_vo->vo_channels[i].id, &hi3531_vo->vo_channels[i].attr);
		if (HI_SUCCESS != tmp_ret_int) {
			cp_hi3531_dev_log(error, hi3531_vo,
				"HI_MPI_VO_SetChnAttr() dev[id:%d channel:%d] failed! error_code[0x%x]",
				hi3531_vo->vo_mpp_channel.s32DevId,
				hi3531_vo->vo_channels[i].id,
				tmp_ret_int
				);

			return HI_FAILURE;
		}

		tmp_ret_int = HI_MPI_VO_EnableChn(hi3531_vo->vo_mpp_channel.s32DevId, hi3531_vo->vo_channels[i].id);
		if (HI_SUCCESS != tmp_ret_int) {
			cp_hi3531_dev_log(error, hi3531_vo,
				"HI_MPI_VO_EnableChn() dev[id:%d channel:%d] failed! error_code[0x%x]",
				hi3531_vo->vo_mpp_channel.s32DevId,
				hi3531_vo->vo_channels[i].id,
				tmp_ret_int
				);

			return HI_FAILURE;
		}
	}
#endif

	return 0;
}

/*******************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: hi3531_vo_start_dev
*
* ����ȫ��: hi3531_vo_start_dev
*
* ��������: public
*
* ����˵��: �����豸
*
* ��    ��: cp_hi3531_vo_t * hi3531_vo						[in/out]����˵��
* ��    ��: cp_hi3531_dev_vo_configure_t * vo_conf						[in/out]����˵��
*
* �� �� ֵ: cp_int32_t
*           0  : �ɹ�
*         ��0  : ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2017-7-29 18:08:01
********************************************************************************/
cp_int32_t hi3531_vo_start_dev(cp_hi3531_vo_t *hi3531_vo, cp_hi3531_dev_vo_configure_t *vo_conf)
{
	cp_int32_t										tmp_ret_int = 0;


#if defined(CP_HI3531_DEV_MODE)
	//��������ͨ��
	tmp_ret_int = hi3531_vo_start_dev_video_layer(hi3531_vo, vo_conf);
	if (tmp_ret_int) {
		cp_hi3531_dev_log(error, hi3531_vo,
			"hi3531_vo_start_dev_video_layer() dev[id:%d] failed! error_code[%d]",
			hi3531_vo->vo_mpp_channel.s32DevId,
			tmp_ret_int
			);
		return tmp_ret_int;
	}

	tmp_ret_int= HI_MPI_VO_SetAttrBegin(hi3531_vo->vo_mpp_channel.s32DevId);
	if (HI_SUCCESS != tmp_ret_int) {
		cp_hi3531_dev_log(error, hi3531_vo,
			"HI_MPI_VO_SetAttrBegin() dev[id:%d] failed! error_code[0x%x]",
			hi3531_vo->vo_mpp_channel.s32DevId,
			tmp_ret_int
			);

		return HI_FAILURE;
	}

	//ֹͣ�豸����ͨ��
	tmp_ret_int = hi3531_vo_stop_dev_channels(hi3531_vo);

	//��������ͨ��
	tmp_ret_int = hi3531_vo_start_dev_channels(hi3531_vo, vo_conf);
	if (tmp_ret_int) {
		cp_hi3531_dev_log(error, hi3531_vo,
			"hi3531_vo_start_dev_channels() dev[id:%d] failed! error_code[%d]",
			hi3531_vo->vo_mpp_channel.s32DevId,
			tmp_ret_int
			);
		return tmp_ret_int;
	}

	tmp_ret_int= HI_MPI_VO_SetAttrEnd(hi3531_vo->vo_mpp_channel.s32DevId);
	if (HI_SUCCESS != tmp_ret_int) {
		cp_hi3531_dev_log(error, hi3531_vo,
			"HI_MPI_VO_SetAttrEnd() dev[id:%d] failed! error_code[0x%x]",
			hi3531_vo->vo_mpp_channel.s32DevId,
			tmp_ret_int
			);

		return HI_FAILURE;
	}

#endif

	return 0;
}


/*******************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: hi3531_vo_write_frame_data
*
* ����ȫ��: hi3531_vo_write_frame_data
*
* ��������: public 
*
* ����˵��: дģ������
*
* ��    ��: cp_hi3531_vo_t * hi3531_vo						[in/out]����˵��
* ��    ��: cp_video_frame_process_t * vfp						[in/out]����˵��
*
* �� �� ֵ: cp_int32_t
*           0  : �ɹ�
*         ��0  : ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2017-12-7 12:11:15
********************************************************************************/
cp_int32_t hi3531_vo_write_frame_data(cp_hi3531_vo_t *hi3531_vo, cp_video_frame_process_t *vfp)
{
	cp_int32_t										tmp_ret_int = 0;



#if defined(CP_HI3531_DEV_MODE)
	VIDEO_FRAME_INFO_S								tmp_vfi = {0, };


	//��Ƶ�����ID
	//tmp_vfi.u32PoolId = xxxx

	//������Ƶԭʼͼ��֡�ṹ
	//tmp_vfi.stVFrame.enPixelFormat = vfp->mpro->ms->

	tmp_ret_int = HI_MPI_VO_SendFrame(
		hi3531_vo->vo_mpp_channel.s32DevId, 
		hi3531_vo->vo_channels[0].id,
		&tmp_vfi);
	if (HI_SUCCESS != tmp_ret_int) {
		cp_hi3531_dev_log(error, hi3531_vo,
			"HI_MPI_VO_SendFrame() dev[id:%d channel:%d] failed! error_code[0x%x]",
			hi3531_vo->vo_mpp_channel.s32DevId,
			hi3531_vo->vo_channels[0].id,
			tmp_ret_int
			);

		return HI_FAILURE;
	}

#endif

	return 0;
}





/*******************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: hi3531_vo_stop_dev_video_layer
*
* ����ȫ��: hi3531_vo_stop_dev_video_layer
*
* ��������: public
*
* ����˵��: ֹͣ�豸ͼ����Ϣ
*
* ��    ��: cp_hi3531_vo_t * hi3531_vo						[in/out]����˵��
*
* �� �� ֵ: cp_int32_t
*           0  : �ɹ�
*         ��0  : ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2017-7-29 18:15:44
********************************************************************************/
cp_int32_t hi3531_vo_stop_dev_video_layer(cp_hi3531_vo_t *hi3531_vo)
{
	cp_int32_t										tmp_ret_int = 0;


#if defined(CP_HI3531_DEV_MODE)

	tmp_ret_int = HI_MPI_VO_DisableVideoLayer(hi3531_vo->vo_mpp_channel.s32DevId);
	if (HI_SUCCESS != tmp_ret_int) {
		cp_hi3531_dev_log(error, hi3531_vo,
			"HI_MPI_VO_DisableVideoLayer() dev[id:%d] failed! error_code[0x%x]",
			hi3531_vo->vo_mpp_channel.s32DevId,
			tmp_ret_int
			);
		return HI_FAILURE;
	}

#endif

	return 0;
}

/*******************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: hi3531_vo_stop_dev_channels
*
* ����ȫ��: hi3531_vo_stop_dev_channels
*
* ��������: public
*
* ����˵��: ֹͣ�豸ͨ�����豸��Ϣ
*
* ��    ��: cp_hi3531_vo_t * hi3531_vo						[in/out]����˵��
*
* �� �� ֵ: cp_int32_t
*           0  : �ɹ�
*         ��0  : ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2017-7-29 18:16:01
********************************************************************************/
cp_int32_t hi3531_vo_stop_dev_channels(cp_hi3531_vo_t *hi3531_vo)
{
	cp_int32_t										tmp_ret_int = 0;
	cp_int32_t										i = 0;


#if defined(CP_HI3531_DEV_MODE)
	for (i = 0; i < cp_ary_size(hi3531_vo->vo_channels); i++) {
		if (!hi3531_vo->vo_channels[i].is_used) {
			continue;
		}

		tmp_ret_int = HI_MPI_VO_DisableChn(hi3531_vo->vo_mpp_channel.s32DevId,
			hi3531_vo->vo_channels[i].id);
		if (HI_SUCCESS != tmp_ret_int) {
			cp_hi3531_dev_log(error, hi3531_vo,
				"HI_MPI_VO_DisableChn() dev[id:%d channel:%d] failed! error_code[0x%x]",
				hi3531_vo->vo_mpp_channel.s32DevId,
				hi3531_vo->vo_channels[i].id,
				tmp_ret_int
				);

			return HI_FAILURE;
		}
	}
#endif

	return 0;
}

/*******************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: hi3531_vo_stop_dev
*
* ����ȫ��: hi3531_vo_stop_dev
*
* ��������: public
*
* ����˵��: ֹͣ�豸
*
* ��    ��: cp_hi3531_vo_t * hi3531_vo						[in/out]����˵��
*
* �� �� ֵ: cp_int32_t
*           0  : �ɹ�
*         ��0  : ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2017-7-29 18:16:16
********************************************************************************/
cp_int32_t hi3531_vo_stop_dev(cp_hi3531_vo_t *hi3531_vo)
{
	cp_int32_t										tmp_ret_int = 0;



#if defined(CP_HI3531_DEV_MODE)

	//ֹͣ��Ƶͨ��
	tmp_ret_int = hi3531_vo_stop_dev_video_layer(hi3531_vo);
	if (tmp_ret_int) {
		cp_hi3531_dev_log(error, hi3531_vo,
			"hi3531_vo_stop_dev_video_layer() dev[id:%d] failed! error_code[%d]",
			hi3531_vo->vo_mpp_channel.s32DevId,
			tmp_ret_int
			);
		return tmp_ret_int;
	}

	//ֹͣ�豸����ͨ��
	tmp_ret_int = hi3531_vo_stop_dev_channels(hi3531_vo);
	if (tmp_ret_int) {
		cp_hi3531_dev_log(error, hi3531_vo,
			"hi3531_vo_stop_dev_channels() dev[id:%d] failed! error_code[%d]",
			hi3531_vo->vo_mpp_channel.s32DevId,
			tmp_ret_int
			);
		return tmp_ret_int;
	}

	tmp_ret_int = HI_MPI_VO_Disable(hi3531_vo->vo_mpp_channel.s32DevId);
	if (HI_SUCCESS != tmp_ret_int) {
		cp_hi3531_dev_log(error, hi3531_vo,
			"HI_MPI_VO_Disable() dev[id:%d channel:%d] failed! error_code[0x%x]",
			hi3531_vo->vo_mpp_channel.s32DevId,
			tmp_ret_int
			);
		return HI_FAILURE;
	}

#endif

	return tmp_ret_int;
}






