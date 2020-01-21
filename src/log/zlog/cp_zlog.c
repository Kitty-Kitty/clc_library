/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/
#include "cp_zlog.h"



int cp_zlog_init(cp_log_t *logger, int argc, char ** argv) {
	int rc;
	zlog_category_t *zc;

	if (!argv) {
		printf("init failed. argument is null.\n");
		return -1;
	}

	rc = zlog_init(argv[0]);
	if (rc) {
		printf("init failed %s\n", argv[0]);
		return -1;
	}

	zc = zlog_get_category("my_cat");
	if (!zc) {
		printf("get cat fail\n");
		zlog_fini();
		return -2;
	}

	logger->data = zc;
	return 0;
}

int cp_zlog_start(cp_log_t *logger, int argc, char ** argv) {
	return 0;
}

int cp_zlog_stop(cp_log_t *logger, int argc, char ** argv) {
	zlog_fini();
	return 0;
}






