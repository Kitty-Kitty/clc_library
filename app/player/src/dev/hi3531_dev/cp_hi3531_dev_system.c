/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2017-06-29

Description:

**************************************************************************/
#include "cp_hi3531_dev_core.h"
#include "cp_hi3531_dev_system.h"




//获取hi3531信息
cp_char_t *get_hi3531_version_info(const cp_module_manager_t *manager)
{
	return ((cp_hi3531_dev_manager_info_t *)(manager->info))->sys_info.version;
}

//打印hi3531信息
cp_char_t *print_hi3531_dev_system_info(const cp_module_manager_t *manager, cp_char_t *buf, cp_int32_t len)
{
	if (!manager || !buf || !len) {
		return buf;
	}

#if defined(CP_HI3531_DEV_MODE)

#endif

	return buf;
}

/*更新hi3531 配置信息*/
cp_int32_t update_hi3531_dev_system_info(const cp_module_manager_t *manager, cp_hi3531_dev_system_info_t *sys_info)
{
	cp_hi3531_dev_manager_t				*hi3531_dev_manager = (cp_hi3531_dev_manager_t *)manager;


#if defined(CP_HI3531_DEV_MODE)
	if (sys_info) {
		cp_memset(sys_info, 0, cp_sizeof(cp_hi3531_dev_system_info_t));
	}

	sys_info->vb_conf.u32MaxPoolCnt = hi3531_dev_manager->conf_info.system_conf.max_pool_count;
	sys_info->sys_conf.u32AlignWidth = hi3531_dev_manager->conf_info.system_conf.align_width;

#endif

	return 0;
}




/*初始化hi3531 系统信息*/
cp_int32_t init_hi3531_dev_system(const cp_module_manager_t *manager, cp_hi3531_dev_system_info_t *sys_info)
{
	cp_int32_t							tmp_ret_int = 0;
	cp_hi3531_dev_manager_t					*hi3531_dev_manager = (cp_hi3531_dev_manager_t *)manager;


	//更新系统配置信息
	tmp_ret_int = update_hi3531_dev_system_info((cp_module_manager_t*)manager, sys_info);
	if (tmp_ret_int) {
		cp_manager_log(error, manager, "update_hi3531_dev_system_info() error.");
		return tmp_ret_int;
	}

	tmp_ret_int = init_hi3531_dev_vb_conf(manager, sys_info);
	if (tmp_ret_int) {
		cp_manager_log(error, hi3531_dev_manager, "init_hi3531_dev_vb_conf() failed.");
		return -1;
	}

	tmp_ret_int = init_hi3531_dev_vdec_mem_conf(manager, sys_info);
	if (tmp_ret_int) {
		cp_manager_log(error, hi3531_dev_manager, "init_hi3531_dev_vdec_mem_conf() failed.");
		return -2;
	}

	return 0;
}

/*初始化hi3531 vb 配置信息*/
cp_int32_t init_hi3531_dev_vb_conf(const cp_module_manager_t *manager, cp_hi3531_dev_system_info_t *sys_info)
{
#if defined(CP_HI3531_DEV_MODE)
	HI_S32							tmp_ret_int = 0;
	cp_hi3531_dev_manager_t				*hi3531_dev_manager = (cp_hi3531_dev_manager_t *)manager;


	HI_MPI_SYS_Exit();
	HI_MPI_VB_Exit();

	tmp_ret_int = HI_MPI_VB_SetConf(&sys_info->vb_conf);
	if (HI_SUCCESS != tmp_ret_int) {
		cp_manager_log(error, hi3531_dev_manager, "HI_MPI_VB_SetConf() failed.");
		return -1;
	}

	tmp_ret_int = HI_MPI_VB_Init();
	if (HI_SUCCESS != tmp_ret_int) {
		cp_manager_log(error, hi3531_dev_manager, "HI_MPI_VB_Init() failed.");
		return -2;
	}

	tmp_ret_int = HI_MPI_SYS_SetConf(&sys_info->sys_conf);
	if (HI_SUCCESS != tmp_ret_int) {
		cp_manager_log(error, hi3531_dev_manager, "HI_MPI_SYS_SetConf() failed.");
		return -3;
	}

	tmp_ret_int = HI_MPI_SYS_Init();
	if (HI_SUCCESS != tmp_ret_int) {
		cp_manager_log(error, hi3531_dev_manager, "HI_MPI_SYS_Init() failed.");
		return -4;
	}

#endif
	return 0;
}

/*初始化hi3531 vdec 内存配置信息*/
cp_int32_t init_hi3531_dev_vdec_mem_conf(const cp_module_manager_t *manager, cp_hi3531_dev_system_info_t *sys_info)
{
#if defined(CP_HI3531_DEV_MODE)
	cp_hi3531_dev_manager_t				*hi3531_dev_manager = (cp_hi3531_dev_manager_t *)manager;
	HI_S32							i = 0;
	HI_S32							tmp_ret_int = 0;
	MPP_CHN_S						tmp_mpp_chn_vdec = {0, };
	HI_CHAR							*tmp_mmz_name = CP_NULL;



	/* VDEC chn max is mpp channel number*/
	for (i = 0; i < hi3531_dev_manager->conf_info.vdec_conf.vdec_mpp_channel_number; i++) {

		tmp_mpp_chn_vdec.enModId = HI_ID_VDEC;
		tmp_mpp_chn_vdec.s32DevId = hi3531_dev_manager->conf_info.vdec_conf.vdec_mpp_dev_id;
		tmp_mpp_chn_vdec.s32ChnId = i;

		if (0 == (i % 2)) {
			tmp_mmz_name = NULL;
		} else {
			tmp_mmz_name = hi3531_dev_manager->conf_info.vdec_conf.vdec_mmz_name;
		}

		tmp_ret_int = HI_MPI_SYS_SetMemConf(&tmp_mpp_chn_vdec, tmp_mmz_name);
		if (tmp_ret_int) {
			cp_manager_log(error, hi3531_dev_manager, "HI_MPI_SYS_SetMemConf() failed.");
			return -1;
		}
	}

#endif
	return 0;
}




/*启动hi3531 系统信息*/
cp_int32_t start_hi3531_dev_system(const cp_module_manager_t *manager, cp_hi3531_dev_system_info_t *sys_info)
{
	cp_hi3531_dev_manager_t				*hi3531_dev_manager = (cp_hi3531_dev_manager_t *)manager;
#if defined(CP_HI3531_DEV_MODE)

#endif
	return 0;
}




/*停止hi3531 系统信息*/
cp_int32_t stop_hi3531_dev_system(const cp_module_manager_t *manager)
{
#if defined(CP_HI3531_DEV_MODE)
	HI_MPI_SYS_Exit();
	HI_MPI_VB_Exit();
#endif
	return 0;
}


