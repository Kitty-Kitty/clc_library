/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/


#include "cp_core.h"
#include "cp_app.h"


cp_app_t				*cp_cycle;





int main(int argc, char** argv) {
	
	int			ret_int = 0;
	char		*tmp_argv[] = { "E:\\project_work\\project\\css_player_fix\\configs\\cp_app_log.conf" };

	cp_cycle = malloc(sizeof(cp_app_t));
	cp_cycle->logger = malloc(sizeof(cp_log_t));

	CP_LOAD_LOG_MODUE(cp_cycle->logger);
	
	ret_int = cp_cycle->logger->log_init(cp_cycle->logger, 1, tmp_argv);
	if (ret_int) {
		printf("log init error");
		return 0;
	}

	ret_int = cp_cycle->logger->log_start(cp_cycle->logger, 1, tmp_argv);
	if (ret_int) {
		printf("log start error");
		return 0;
	}

	cp_log_info(cp_cycle->logger, "hello world£¡ %s  %d", "abc", 123);

	ret_int = cp_cycle->logger->log_stop(cp_cycle->logger, 1, tmp_argv);
	if (ret_int) {
		printf("log stop error");
		return 0;
	}

	return 0;
}
