/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/
#include "cp_log.h"
#include "cp_conf.h"





cp_log_t* cp_log_create() {
	cp_log_t *logger = (cp_log_t*)cp_malloc(sizeof(cp_log_t));

	memset(logger, 0, sizeof(cp_log_t));

	return logger;
}

int cp_log_init(cp_log_t *logger, cp_conf_t *conf) {
	if (logger) {
		CP_LOAD_LOG_MODUE(logger);
	}

	int ret_int = 0;
	
	char *log_conf[] = { conf->log_conf };
	ret_int = logger->log_init(logger, 1, log_conf);
	if (ret_int) {
		printf("log init error");
		return -1;
	}

	ret_int = logger->log_start(logger, 0, CP_NULL);
	if (ret_int) {
		printf("log start error");
		return -1;
	}
	return 0;
}

int cp_log_destroy(cp_log_t *logger) {
	if (logger) {
		cp_free(logger);
	}
	return 0;
}


