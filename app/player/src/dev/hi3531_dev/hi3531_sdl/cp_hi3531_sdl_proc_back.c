/*******************************************************************************
*
*Copyright:novigo
*
*File name: cp_hi3531_sdl_proc.c
*
*Author:fangzhenmu@novigo.com.cn
*
*Version: 1.0
*
*Date:2017/07/28
*
*Description: create (cp_hi3531_sdl_proc.c)
*
*Others:
*
*History:
*******************************************************************************/

#include "cp_hi3531_sdl_core.h"
#include "cp_hi3531_dev_info.h"
#include "cp_hi3531_tde_core.h"




/*******************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: create_hi3531_vo_dev_list
*
* ����ȫ��: create_hi3531_vo_dev_list
*
* ��������: public
*
* ����˵��: ��ʼ��hi3531 vo �豸�б�
*
* ��    ��: cp_hi3531_sdl_t * dev						[in/out]����˵��
* ��    ��: cp_hi3531_dev_configure_t *conf						[in/out]����˵��
*
* �� �� ֵ: cp_int32_t
*           0  : �ɹ�
*         ��0  : ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2017-7-28 10:22:20
********************************************************************************/
cp_int32_t	create_hi3531_vo_dev_list(cp_hi3531_sdl_t *dev, cp_hi3531_dev_configure_t *conf)
{
	cp_int32_t								tmp_ret_int = 0;
	cp_int32_t								i = 0;
	cp_hi3531_dev_info_t					tmp_info = { 0, };
	cp_module_register_t					*tmp_module_register = CP_NULL;
	cp_dev_t								*tmp_vo = CP_NULL;
	cp_char_t								tmp_buf[CP_APP_DEFAULT_BUFFER_LENGTH] = { 0, };



	for (i = 0; i < cp_ary_size(conf->vo_conf); i++) {
		if (!conf->vo_conf[i].is_used) {
			//�����ʹ�ã��򷵻�
			continue;
		}

		//����ģ����Ϣ
		cp_memset(&tmp_info, 0, cp_sizeof(tmp_info));
		CP_MODULE_INFO_SET_DATA(&tmp_info, &(conf->vo_conf[i]));

		//��ȡģ��ע����Ϣ
		tmp_module_register = cp_manager_get_module_register(dev->manager, cp_player_module_type_hi3531_dev_vo);
		if (!tmp_module_register) {
			cp_hi3531_dev_log(warn, dev,
				"create hi3531_vo failed! not found dev_vo[type:%d] register.",
				cp_player_module_type_hi3531_dev_vo);
			continue;
		}

		//����ģ��ע����Ϣ����ģ����Ϣ
		CP_MODULE_INFO_SET_FROM_REGISTER(&tmp_info, tmp_module_register);
		tmp_vo = (cp_dev_t*)cp_create_module(tmp_module_register, dev->manager, &tmp_info);
		if (!tmp_vo) {
			cp_hi3531_dev_log(warn, dev,
				"create hi3531_vo[%s] failed! ",
				print_module_register_info(tmp_module_register, tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH));
			continue;
		}
		else {
			cp_hi3531_dev_log(notice, dev,
				"create hi3531_vo[%s] successed! ",
				print_module_register_info(tmp_module_register, tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH));
		}

		//��ʼ��ģ��
		tmp_ret_int = cp_init_module(tmp_vo, &tmp_info);
		if (tmp_ret_int) {
			cp_hi3531_dev_log(warn, dev,
				"init hi3531_vo[module:%p register:%s] failed! ",
				tmp_vo,
				print_module_register_info(tmp_module_register, tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH));
			continue;
		}
		else {
			cp_hi3531_dev_log(notice, dev,
				"init hi3531_vo[module:%p register:%s] successed! ",
				tmp_vo,
				print_module_register_info(tmp_module_register, tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH));
		}

		dev->m_hi3531_vo[i] = tmp_vo;
	}

	return 0;
}

/*******************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: start_hi3531_vo_dev_list
*
* ����ȫ��: start_hi3531_vo_dev_list
*
* ��������: public
*
* ����˵��: ����hi3531 vo �豸�б�
*
* ��    ��: cp_hi3531_sdl_t * dev						[in/out]����˵��
* ��    ��: cp_hi3531_dev_configure_t *conf						[in/out]����˵��
*
* �� �� ֵ: cp_int32_t
*           0  : �ɹ�
*         ��0  : ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2017-7-28 10:22:31
********************************************************************************/
cp_int32_t	start_hi3531_vo_dev_list(cp_hi3531_sdl_t *dev, cp_hi3531_dev_configure_t *conf)
{
	cp_int32_t								tmp_ret_int = 0;
	cp_int32_t								i = 0;
	cp_hi3531_dev_info_t					tmp_info = { 0, };
	cp_char_t								tmp_buf[CP_APP_DEFAULT_BUFFER_LENGTH] = { 0, };



	for (i = 0; i < cp_ary_size(dev->m_hi3531_vo); i++) {
		if (!dev->m_hi3531_vo[i]) {
			//�����ʹ�ã��򷵻�
			continue;
		}

		//����ģ����Ϣ
		cp_memset(&tmp_info, 0, cp_sizeof(tmp_info));
		CP_MODULE_INFO_SET_DATA(&tmp_info, &(conf->vo_conf[i]));

		//����ģ��
		tmp_ret_int = cp_open_module(dev->m_hi3531_vo[i], &tmp_info);
		if (tmp_ret_int) {
			cp_hi3531_dev_log(warn, dev,
				"open hi3531_vo[module:%p register:%s] failed! ",
				dev->m_hi3531_vo[i],
				print_module_register_info(&(dev->m_hi3531_vo[i]->register_info), tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH));
			continue;
		}
		else {
			cp_hi3531_dev_log(notice, dev,
				"open hi3531_vo[module:%p register:%s] successed! ",
				dev->m_hi3531_vo[i],
				print_module_register_info(&(dev->m_hi3531_vo[i]->register_info), tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH));
		}
	}

	return 0;
}

/*******************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: stop_hi3531_vo_dev_list
*
* ����ȫ��: stop_hi3531_vo_dev_list
*
* ��������: public
*
* ����˵��: ֹͣhi3531 vo �豸�б�
*
* ��    ��: cp_hi3531_sdl_t * dev						[in/out]����˵��
* ��    ��: cp_hi3531_dev_configure_t *conf						[in/out]����˵��
*
* �� �� ֵ: cp_int32_t
*           0  : �ɹ�
*         ��0  : ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2017-7-28 10:22:39
********************************************************************************/
cp_int32_t	stop_hi3531_vo_dev_list(cp_hi3531_sdl_t *dev, cp_hi3531_dev_configure_t *conf)
{
	cp_int32_t								tmp_ret_int = 0;
	cp_int32_t								i = 0;
	cp_char_t								tmp_buf[CP_APP_DEFAULT_BUFFER_LENGTH] = { 0, };



	for (i = 0; i < cp_ary_size(dev->m_hi3531_vo); i++) {
		if (!dev->m_hi3531_vo[i]) {
			//�����ʹ�ã��򷵻�
			continue;
		}

		//����ģ��
		tmp_ret_int = cp_close_module(dev->m_hi3531_vo[i]);
		if (tmp_ret_int) {
			cp_hi3531_dev_log(warn, dev,
				"close hi3531_vo[module:%p register:%s] failed! ",
				dev->m_hi3531_vo[i],
				print_module_register_info(&(dev->m_hi3531_vo[i]->register_info), tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH));
			continue;
		}
		else {
			cp_hi3531_dev_log(notice, dev,
				"close hi3531_vo[module:%p register:%s] successed! ",
				dev->m_hi3531_vo[i],
				print_module_register_info(&(dev->m_hi3531_vo[i]->register_info), tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH));
		}
	}

	return 0;
}

/*******************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: destory_hi3531_vo_dev_list
*
* ����ȫ��: destory_hi3531_vo_dev_list
*
* ��������: public
*
* ����˵��: ����hi3531 vo �豸�б�
*
* ��    ��: cp_hi3531_sdl_t * dev						[in/out]����˵��
* ��    ��: cp_hi3531_dev_configure_t * conf						[in/out]����˵��
*
* �� �� ֵ: cp_int32_t
*           0  : �ɹ�
*         ��0  : ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2017-7-28 14:07:27
********************************************************************************/
cp_int32_t	destory_hi3531_vo_dev_list(cp_hi3531_sdl_t *dev, cp_hi3531_dev_configure_t *conf)
{
	cp_int32_t								tmp_ret_int = 0;
	cp_int32_t								i = 0;



	for (i = 0; i < cp_ary_size(dev->m_hi3531_vo); i++) {
		if (!dev->m_hi3531_vo[i]) {
			//�����ʹ�ã��򷵻�
			continue;
		}

		//����ģ��
		tmp_ret_int = cp_destroy_module(dev->manager, dev->m_hi3531_vo[i]);
		if (tmp_ret_int) {
			cp_hi3531_dev_log(warn, dev,
				"destroy hi3531_vo[module:%p] failed! ",
				dev->m_hi3531_vo[i]);
			continue;
		}
		else {
			cp_hi3531_dev_log(notice, dev,
				"destroy hi3531_vo[module:%p] successed! ",
				dev->m_hi3531_vo[i]);
		}
	}

	return 0;
}


/*******************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: create_hi3531_tde_dev
*
* ����ȫ��: create_hi3531_tde_dev
*
* ��������: public
*
* ����˵��: ��ʼ��hi3531 tde �豸�б�
*
* ��    ��: cp_hi3531_sdl_t * dev						[in/out]����˵��
* ��    ��: cp_hi3531_dev_configure_t * conf						[in/out]����˵��
*
* �� �� ֵ: cp_int32_t
*           0  : �ɹ�
*         ��0  : ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2017-7-28 14:20:09
********************************************************************************/
cp_int32_t	create_hi3531_tde_dev(cp_hi3531_sdl_t *dev, cp_hi3531_dev_configure_t *conf)
{
	cp_int32_t								tmp_ret_int = 0;
	cp_int32_t								i = 0;
	cp_hi3531_dev_info_t					tmp_info = { 0, };
	cp_module_register_t					*tmp_module_register = CP_NULL;
	cp_dev_t								*tmp_tde = CP_NULL;
	cp_char_t								tmp_buf[CP_APP_DEFAULT_BUFFER_LENGTH] = { 0, };



	//��ȡģ��ע����Ϣ
	tmp_module_register = cp_manager_get_module_register(dev->manager, cp_player_module_type_hi3531_dev_tde);
	if (!tmp_module_register) {
		cp_hi3531_dev_log(warn, dev,
			"create hi3531_tde failed! not found dev_tde[type:%d] register.",
			cp_player_module_type_hi3531_dev_tde);
		return -1;
	}

	//����ģ��ע����Ϣ����ģ����Ϣ
	CP_MODULE_INFO_SET_FROM_REGISTER(&tmp_info, tmp_module_register);
	tmp_tde = (cp_dev_t*)cp_create_module(tmp_module_register, dev->manager, &tmp_info);
	if (!tmp_tde) {
		cp_hi3531_dev_log(warn, dev,
			"create hi3531_tde[%s] failed! ",
			print_module_register_info(tmp_module_register, tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH));
		return -2;
	}
	else {
		cp_hi3531_dev_log(notice, dev,
			"create hi3531_tde[%s] successed! ",
			print_module_register_info(tmp_module_register, tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH));
	}

	//��ʼ��ģ��
	tmp_ret_int = cp_init_module(tmp_tde, &tmp_info);
	if (tmp_ret_int) {
		cp_hi3531_dev_log(warn, dev,
			"init hi3531_tde[module:%p register:%s] failed! ",
			tmp_tde,
			print_module_register_info(tmp_module_register, tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH));
		return -3;
	}
	else {
		cp_hi3531_dev_log(notice, dev,
			"init hi3531_tde[module:%p register:%s] successed! ",
			tmp_tde,
			print_module_register_info(tmp_module_register, tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH));
	}

	dev->m_hi3531_tde = tmp_tde;

	return 0;
}

/*******************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: start_hi3531_tde_dev
*
* ����ȫ��: start_hi3531_tde_dev
*
* ��������: public
*
* ����˵��: ����hi3531 tde �豸�б�
*
* ��    ��: cp_hi3531_sdl_t * dev						[in/out]����˵��
* ��    ��: cp_hi3531_dev_configure_t * conf						[in/out]����˵��
*
* �� �� ֵ: cp_int32_t
*           0  : �ɹ�
*         ��0  : ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2017-7-28 14:20:20
********************************************************************************/
cp_int32_t	start_hi3531_tde_dev(cp_hi3531_sdl_t *dev, cp_hi3531_dev_configure_t *conf)
{
	cp_int32_t								tmp_ret_int = 0;
	cp_int32_t								i = 0;
	cp_hi3531_dev_info_t					tmp_info = { 0, };
	cp_char_t								tmp_buf[CP_APP_DEFAULT_BUFFER_LENGTH] = { 0, };



	if (!dev->m_hi3531_tde) {
		//�����ʹ�ã��򷵻�
		return -1;
	}

	//����ģ��
	tmp_ret_int = cp_open_module(dev->m_hi3531_tde, &tmp_info);
	if (tmp_ret_int) {
		cp_hi3531_dev_log(warn, dev,
			"open hi3531_tde[module:%p register:%s] failed! ",
			dev->m_hi3531_tde,
			print_module_register_info(&(dev->m_hi3531_tde->register_info), tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH));
		return -2;
	}
	else {
		cp_hi3531_dev_log(notice, dev,
			"open hi3531_tde[module:%p register:%s] successed! ",
			dev->m_hi3531_tde,
			print_module_register_info(&(dev->m_hi3531_tde->register_info), tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH));
	}

	return 0;
}

/*******************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: stop_hi3531_tde_dev
*
* ����ȫ��: stop_hi3531_tde_dev
*
* ��������: public
*
* ����˵��: ֹͣhi3531 tde �豸�б�
*
* ��    ��: cp_hi3531_sdl_t * dev						[in/out]����˵��
* ��    ��: cp_hi3531_dev_configure_t * conf						[in/out]����˵��
*
* �� �� ֵ: cp_int32_t
*           0  : �ɹ�
*         ��0  : ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2017-7-28 14:20:30
********************************************************************************/
cp_int32_t	stop_hi3531_tde_dev(cp_hi3531_sdl_t *dev, cp_hi3531_dev_configure_t *conf)
{
	cp_int32_t								tmp_ret_int = 0;
	cp_int32_t								i = 0;
	cp_char_t								tmp_buf[CP_APP_DEFAULT_BUFFER_LENGTH] = { 0, };



	if (!dev->m_hi3531_tde) {
		//�����ʹ�ã��򷵻�
		return -1;
	}

	//����ģ��
	tmp_ret_int = cp_close_module(dev->m_hi3531_tde);
	if (tmp_ret_int) {
		cp_hi3531_dev_log(warn, dev,
			"close hi3531_tde[module:%p register:%s] failed! ",
			dev->m_hi3531_tde,
			print_module_register_info(&(dev->m_hi3531_tde->register_info), tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH));
		return -2;
	}
	else {
		cp_hi3531_dev_log(notice, dev,
			"close hi3531_tde[module:%p register:%s] successed! ",
			dev->m_hi3531_tde,
			print_module_register_info(&(dev->m_hi3531_tde->register_info), tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH));
	}

	return 0;
}

/*******************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: destory_hi3531_tde_dev
*
* ����ȫ��: destory_hi3531_tde_dev
*
* ��������: public
*
* ����˵��: ����hi3531 tde �豸�б�
*
* ��    ��: cp_hi3531_sdl_t * dev						[in/out]����˵��
* ��    ��: cp_hi3531_dev_configure_t * conf						[in/out]����˵��
*
* �� �� ֵ: cp_int32_t
*           0  : �ɹ�
*         ��0  : ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2017-7-28 14:20:39
********************************************************************************/
cp_int32_t	destory_hi3531_tde_dev(cp_hi3531_sdl_t *dev, cp_hi3531_dev_configure_t *conf)
{
	cp_int32_t								tmp_ret_int = 0;
	cp_int32_t								i = 0;



	if (!dev->m_hi3531_tde) {
		//�����ʹ�ã��򷵻�
		return -1;
	}

	//����ģ��
	tmp_ret_int = cp_destroy_module(dev->manager, dev->m_hi3531_tde);
	if (tmp_ret_int) {
		cp_hi3531_dev_log(warn, dev,
			"destroy hi3531_tde[module:%p] failed! ",
			dev->m_hi3531_tde);
		return -2;
	}
	else {
		cp_hi3531_dev_log(notice, dev,
			"destroy hi3531_tde[module:%p] successed! ",
			dev->m_hi3531_tde);
	}

	return 0;
}

/*******************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: write_hi3531_frame_data
*
* ����ȫ��: write_hi3531_frame_data
*
* ��������: public
*
* ����˵��: дhi3531����
*
* ��    ��: cp_hi3531_sdl_t * hi3531_sdl						[in/out]����˵��
* ��    ��: const cp_uchar_t * * buf						[in/out]����˵��
* ��    ��: cp_int32_t len						[in/out]����˵��
* ��    ��: cp_int32_t flag						[in/out]����˵��
*
* �� �� ֵ: cp_int32_t
*           0  : �ɹ�
*         ��0  : ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2017-8-20 11:47:08
********************************************************************************/
cp_int32_t write_hi3531_frame_data(cp_hi3531_sdl_t *hi3531_sdl,
	const cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag)
{
	cp_int32_t						tmp_ret_int = 0;
	cp_video_frame_packet_t			*tmp_vfp = CP_NULL;



	if (!buf || !*buf || !len) {
		return -1;
	}

	//ת��ý�����ݣ���У�����ݺϷ���
	tmp_vfp = *((cp_video_frame_packet_t**)buf);
	if (cp_media_packet_type_video != tmp_vfp->mp.type) {
		cp_module_log(error, hi3531_sdl,
			"unknow media pakcet type[%d] error.",
			tmp_vfp->mp.type);
		return -2;
	}

	//ѭ��������Ƶ֡����
	return cycle_hi3531_frame_data(hi3531_sdl, CP_NULL, tmp_vfp);
}

/*******************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: cycle_hi3531_frame_data
*
* ����ȫ��: cycle_hi3531_frame_data
*
* ��������: public
*
* ����˵��: ѭ������hi3531����
*
* ��    ��: cp_hi3531_sdl_t * hi3531_sdl						[in/out]����˵��
* ��    ��: cp_media_surface_t * surfact						[in/out]����˵��
* ��    ��: cp_video_frame_packet_t * vfp						[in/out]����˵��
*
* �� �� ֵ: cp_int32_t
*           0  : �ɹ�
*         ��0  : ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2017-8-20 14:15:20
********************************************************************************/
cp_int32_t cycle_hi3531_frame_data(cp_hi3531_sdl_t *hi3531_sdl,
	cp_media_surface_t *surfact,
	cp_video_frame_packet_t	*vfp)
{
	cp_int32_t								tmp_ret_int = 0;
	cp_queue_t								*tmp_queue = CP_NULL;
	cp_queue_t								*tmp_current = CP_NULL;
	cp_frame_play_position_t				*tmp_fpp = CP_NULL;
	cp_video_frame_process_t				tmp_vfp = { 0, };



	//����cycle_hi3531_frame_data��������
	tmp_queue = &vfp->fpp_queue;
	for (tmp_current = cp_queue_next(tmp_queue); tmp_current != tmp_queue;
		tmp_current = cp_queue_next(tmp_current)) {
		tmp_fpp = cp_queue_data(tmp_current, cp_frame_play_position_t, vfpp_queue);
		if (!tmp_fpp) {
			continue;
		}

		//��ʼ��video frame process
		cp_memset(&tmp_vfp, 0, cp_sizeof(cp_video_frame_process_t));

		tmp_vfp.mpro->ms = surfact;
		tmp_vfp.mpro->mp = (cp_media_packet_t*)vfp;
		tmp_vfp.vfpp = tmp_vfpp;
		tmp_vfp.vfp_type = cp_video_frame_process_type_resize;

		//����ͼ������
		tmp_ret_int = cp_get_option_module(hi3531_sdl->m_hi3531_tde, cp_hi3531_tde_option_get_resize, &tmp_vfp);
		if (tmp_ret_int) {
			continue;
		}

		//��ʾͼ������
		tmp_ret_int = cp_write_module(hi3531_sdl->m_hi3531_vo, &tmp_vfp, cp_sizeof(cp_video_frame_process_t*), 0);
		if (tmp_ret_int) {
			continue;
		}
	}

	return 0;
}

/*******************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: write_ffmpeg_frame_data
*
* ����ȫ��: write_ffmpeg_frame_data
*
* ��������: public
*
* ����˵��: дffmpeg����
*
* ��    ��: cp_hi3531_sdl_t * hi3531_sdl						[in/out]����˵��
* ��    ��: const cp_uchar_t * * buf						[in/out]����˵��
* ��    ��: cp_int32_t len						[in/out]����˵��
* ��    ��: cp_int32_t flag						[in/out]����˵��
*
* �� �� ֵ: cp_int32_t
*           0  : �ɹ�
*         ��0  : ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2017-8-20 11:47:18
********************************************************************************/
cp_int32_t write_ffmpeg_frame_data(cp_hi3531_sdl_t *hi3531_sdl,
	const cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag)
{
	return 0;
}












