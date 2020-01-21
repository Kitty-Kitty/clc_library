/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/


#include "cp_fusion_player.h"
#include "cp_process_core.h"
#include "cp_fusion_player_module_list.h"
#include "cp_fusion_player_proc.h"




extern cp_module_manager_register_t m_module_manager_list[];
extern cp_int32_t m_module_manager_size;




cp_int32_t init_player(cp_fusion_player_t *player, cp_app_info_t *app_info);
cp_int32_t start_player(cp_fusion_player_t *player, cp_app_info_t *app_info);
cp_int32_t stop_player(cp_fusion_player_t *player);




cp_fusion_player_t* cp_fusion_player_create(cp_app_info_t *app_info) {
	cp_fusion_player_t		*player = CP_NULL;


	player = cp_malloc(sizeof(cp_fusion_player_t));
	if (player) {
		cp_memset(player, 0, sizeof(cp_fusion_player_t));
	}
	else{
		printf("cp_fusion_player_create () error reason: malloc failed!");
	}
	//����һ���ڴ��
	player->mpool = cp_create_mpool(CP_APP_DEFAULT_BUFFER_LENGTH);
	if (!player->mpool) {
		cp_log_printf("cp_app_create () error reason: cp_create_mpool() failed!");
		return CP_NULL;
	}
	//����һ����Ϣ�ṹ����
	player->app_info = (cp_app_info_t *)cp_mpalloc(player->mpool, sizeof(cp_fusion_player_info_t));
	if (!player->app_info) {
		cp_log_fatal(player->logger, "malloc player info error!\r\n");
		return CP_NULL;
	}
	else{
		memset(player->app_info, 0, sizeof(cp_fusion_player_info_t));
		*(player->app_info) = *app_info;
	}
	//����app�ļ����������
	CP_APP_SET_HANDLERS(player, player);
	//��������ģ�������ע�����Ŀռ�
	create_app_root_register_memory((cp_app_t*)player, CP_GET_LIBRARY_REAL_MODULE_TYPE(cp_module_manager_type_end));

	return player;
}

cp_int32_t init_player(cp_fusion_player_t *player, cp_app_info_t *app_info) {
	cp_int32_t			ret_int = 0;


	//��ʼ����ģ�������ע������Ϣ
	CP_ROOT_MODULE_MANAGER_DEPENDENT(player, player);

	//��ʼ��app��������
	ret_int = cp_init_app(player, app_info);
	if (ret_int) {
		cp_log_printf("init_player() error. init_app() error.");
		return ret_int;
	}

	//��ʼ����ģ�������ע������Ϣ
	CP_SUB_MODULE_MANAGER_DEPENDENT(player, player);
	ret_int = init_app_manager((cp_app_t*)player,
		player->root_module_manager_array.elts, player->root_module_manager_array.nelts);
	if (ret_int) {
		cp_log_printf("init_player() error. init_app_manager() error.");
		return ret_int;
	}

	//��ʼ��ģ��ע������Ϣ
	CP_MODULE_DEPENDENT(player, player);

	//��app info��Ϣ����
	*player->app_info = *app_info;

	//��ʼ��player ��ص���Ϣ
	ret_int = init_player_info(player, (cp_fusion_player_info_t *)(player->app_info));
	if (ret_int) {
		cp_log_error(player->logger, "init_player() error. init_player_info() error.");
		return ret_int;
	}

	//��ʼ��player������Ϣ
	ret_int = init_player_other(player, player->app_info);
	if (ret_int) {
		cp_log_error(player->logger, "init_player() error. init_player_other() error.");
		return ret_int;
	}

	return 0;
}

cp_int32_t start_player(cp_fusion_player_t *player, cp_app_info_t *app_info) {
	cp_int32_t			ret_int = 0;



	ret_int = cp_start_app(player, player->app_info);
	if (ret_int) {
		cp_log_printf("start_player() error. start_app() error.");
		return ret_int;
	}
	ret_int = start_player_other(player, player->app_info);
	if (ret_int) {
		cp_log_printf("start_player() error. start_player_other() error.");
		return ret_int;
	}

	cp_log_notice(player->logger, "hello world!");
	
	return 0;
}

cp_int32_t stop_player(cp_fusion_player_t *player) {
	cp_int32_t			ret_int = 0;


	ret_int = player->logger->log_stop(player->logger, 0, CP_NULL);
	if (ret_int) {
		printf("log stop error");
		return 0;
	}

	return 0;
}

cp_int32_t cp_fusion_player_destroy(cp_fusion_player_t *player) {
	cp_int32_t			ret_int = 0;


	ret_int = cp_conf_destroy(player->conf);
	if (ret_int) {
		printf("cp_conf_destroy error!\r\n");
		return -1;
	}

	ret_int = cp_log_destroy(player->logger);
	if (ret_int) {
		printf("cp_log_destroy error!\r\n");
		return -1;
	}

	return 0;
}



