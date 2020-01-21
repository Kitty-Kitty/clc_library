/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/

#include "cp_core.h"
#include "cp_app.h"
#include "cp_utils.h"
#include "prot_core.h"



#ifdef WIN32
#define		CP_BUILD_DATE							
#endif // WIN32



/********************************************************************************************************************/
/* 这里定义一些全局变量，大致内容如下：																				*/
/*cp_app_t		           *cp_global_app;																					*/
/*cp_app_info_t		        cp_global_app_info = { type, name, version, description, NULL, 0, NULL };						*/
/*cp_app_create_handle	    cp_global_app_create_handle = create_handle;														*/
/*cp_app_destory_handle	app_destory_handle = destory_handle;														*/
/********************************************************************************************************************/
CP_APP_ENTRY(0, "cp_app", 1, "cp app", CP_NULL, CP_NULL);



cp_app_t* cp_app_create(cp_app_info_t *app_info) {
	cp_app_t		*app = CP_NULL;


	//为app分配空间
	app = cp_malloc(sizeof(cp_app_t));
	if (!app){
		cp_log_printf("cp_app_create () error reason: malloc failed!");
		return CP_NULL;
	} 
	cp_memset(app, 0, sizeof(cp_app_t));
	//分配一个内存池
	app->mpool = cp_create_mpool(CP_APP_DEFAULT_BUFFER_LENGTH);
	if (!app->mpool) {
		cp_log_printf("cp_app_create () error reason: cp_create_mpool() failed!");
		return CP_NULL;
	}
	//设置app的handle
	CP_APP_SET_HANDLERS(app, app);
	return app;
}

int cp_app_destroy(cp_app_t *app) {
	if (app->app_info)
	{
		cp_free(app->app_info);
	}
	if (app) {
		cp_free(app);
	}

	return 0;
}

cp_int32_t	cp_app_register(cp_int32_t type, cp_char_t *name, cp_int32_t version, cp_char_t *description, cp_app_create_handle para_app_create_handle, cp_app_destroy_handle para_app_destroy_handle)
{
	cp_memset(&cp_global_app_info, 0, cp_sizeof(cp_global_app_info));
	cp_global_app_info.type = type;
	cp_global_app_info.version = version;
	cp_sprintf(cp_global_app_info.name, "%s", name);
	cp_sprintf(cp_global_app_info.description, "%s", description);
	cp_global_app_create_handle = para_app_create_handle;
	cp_global_app_destroy_handle = para_app_destroy_handle;




	return 0;
}

cp_int32_t	cp_app_entry_config_path(cp_char_t *config_path)
{
	cp_memset(&cp_global_app_info.entry_config_path, 0, cp_sizeof(cp_global_app_info.entry_config_path));
	cp_sprintf(cp_global_app_info.entry_config_path, "%s", config_path);
	return 0;
}




