/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/


/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/
#include "cp_include.h"
#include "cp_css_encrypt_module_type.h"
#include "cp_css_encrypt_dev_manager.h"
#include "cp_css_encrypt_dev_manager_conf_string.h"



extern cp_module_register_t  codec_module_list[];




//模块创建接口，表示创建一个模块
cp_int32_t init_css_encrypt_dev_manager(cp_css_encrypt_dev_manager_t *manager, const cp_css_encrypt_dev_manager_info_t *info);
//模块打开运行接口，在模块init之后，会被调用
cp_int32_t start_css_encrypt_dev_manager(cp_css_encrypt_dev_manager_t *manager, const cp_css_encrypt_dev_manager_info_t *info);
//读取模块数据，flag为读取模式的扩展标志。默认为0，其他为预留
cp_int32_t stop_css_encrypt_dev_manager(cp_css_encrypt_dev_manager_t *manager);
//设置模块参数
cp_int32_t ctrl_css_encrypt_dev_manager(cp_css_encrypt_dev_manager_t *manager, cp_int32_t optname, const cp_void_t* optval);
//模块创建接口，表示创建一个模块
cp_codec_t* create_css_encrypt_dev_module(cp_css_encrypt_dev_manager_t *manager, const cp_codec_info_t *info);
//模块查询接口，表示从管理器中查询一个模块
cp_codec_t* get_css_encrypt_dev_module(cp_css_encrypt_dev_manager_t *manager, const cp_codec_info_t *info);
//写模块数据，flag为写模式的扩展标志。默认为0，其他为预留
cp_int32_t register_css_encrypt_dev_module(cp_css_encrypt_dev_manager_t *manager, cp_codec_t *codec);
//关闭模块
cp_int32_t cancel_css_encrypt_dev_module(cp_css_encrypt_dev_manager_t *manager, cp_codec_t *codec);
//退出模块
cp_int32_t destroy_css_encrypt_dev_module(cp_css_encrypt_dev_manager_t *manager, cp_codec_t *codec);
//设置模块参数
cp_int32_t ctrl_css_encrypt_dev_module(cp_css_encrypt_dev_manager_t *manager, cp_codec_t *codec, cp_int32_t optname, const cp_void_t* optval);




cp_css_encrypt_dev_manager_t* create_css_encrypt_dev_manager(cp_module_manager_register_t *register_info, cp_app_t *app, cp_css_encrypt_dev_manager_info_t *info)
{
	cp_css_encrypt_dev_manager_t			*tmp_manager = CP_NULL;


	if (!app || !info) {
		return tmp_manager;
	}

	//配置一个manager 内存空间
	CP_MODULE_MANAGER_MALLOC(tmp_manager, app, cp_css_encrypt_dev_manager_t);

	if (tmp_manager) {
		//配置manager信息
		tmp_manager->register_info = *register_info;
		//为设备分配空间
		tmp_manager->pool = cp_create_pool(app);
		//设置各种操作句柄
		CP_MODULE_MANAGER_SET_HANDLERS(tmp_manager, css_encrypt_dev);
		//初始化模块中的所有队列
		cp_manager_create_register_memory(tmp_manager, CP_LIBRARY_MODULE_MANAGER_MAX_SIZE,
			CP_LIBRARY_MODULE_MANAGER_MAX_SIZE, CP_LIBRARY_MODULE_MAX_SIZE);
	}

	return tmp_manager;
}

cp_int32_t destroy_css_encrypt_dev_manager(cp_app_t *app, cp_css_encrypt_dev_manager_t* manager)
{
	if (!manager) {
		return 0;
	}

	if (manager->pool) {
		cp_destroy_pool(manager->pool);
	}

	CP_MODULE_MANAGER_FREE(manager);

	return 0;
}



//模块创建接口，表示创建一个模块
cp_int32_t init_css_encrypt_dev_manager(cp_css_encrypt_dev_manager_t *manager, const cp_css_encrypt_dev_manager_info_t *info)
{
	cp_int32_t					tmp_ret_int = 0;


	tmp_ret_int = css_encrypt_dev_manager_parse_configure(manager, &manager->cedc);
	if (tmp_ret_int) {
		cp_manager_log(error, manager, "css_encrypt_dev_manager_parse_configure() error.");
		return tmp_ret_int;
	}

	return 0;
}
//模块打开运行接口，在模块init之后，会被调用
cp_int32_t start_css_encrypt_dev_manager(cp_css_encrypt_dev_manager_t *manager, const cp_css_encrypt_dev_manager_info_t *info)
{
	cp_int32_t										tmp_ret_int = 0;
	cp_int32_t										tmp_module_type = -1;
	cp_char_t										tmp_buf[CP_APP_DEFAULT_BUFFER_LENGTH] = { 0, };
	cp_module_info_t								tmp_module_info = { 0, };



	//获取模块类型
	if (!cp_strcmp(CP_CSS_ENCRYPT_DEV_MANAGER_DEV_STRING_HI3536, manager->cedc.type)) {
		tmp_module_type = cp_css_encrypt_module_type_hi3536_dev;
	}

	if (tmp_module_type < 0) {
		cp_manager_log(error, manager,
			"unsupport type[%s] error. please check you configure.",
			manager->cedc.type);
		return -1;
	}

	//创建模块
	manager->encrypt_dev = cp_manager_create_module_by_type(manager, tmp_module_type);
	if (!manager->encrypt_dev) {
		cp_manager_log(error, manager, 
			"create [%s] module[%d] failed!.",
			manager->cedc.type,
			tmp_module_type);
		return -1;
	}

	//初始化模块
	CP_MODULE_INFO_SET_DATA(&tmp_module_info, &manager->cedc)
	tmp_ret_int = cp_init_module(manager->encrypt_dev, &tmp_module_info);
	if (tmp_ret_int) {
		cp_manager_log(error, manager,
			"init %s failed!.",
			print_module_register_info(&manager->encrypt_dev->register_info, tmp_buf, cp_sizeof(tmp_buf)));
		return -1;
	}

	//启动模块
	tmp_ret_int = cp_open_module(manager->encrypt_dev, &tmp_module_info);
	if (tmp_ret_int) {
		cp_manager_log(error, manager,
			"open %s failed!.",
			print_module_register_info(&manager->encrypt_dev->register_info, tmp_buf, cp_sizeof(tmp_buf)));
		return -1;
	}

	return 0;
}
//读取模块数据，flag为读取模式的扩展标志。默认为0，其他为预留
cp_int32_t stop_css_encrypt_dev_manager(cp_css_encrypt_dev_manager_t *manager)
{
	cp_int32_t									tmp_ret_int = 0;
	cp_char_t									tmp_buf[CP_APP_DEFAULT_BUFFER_LENGTH] = { 0, };


	if (!manager->encrypt_dev) {
		cp_manager_log(error, manager,
			"encrypt module is null error.");
		return -1;
	}

	//关闭模块
	tmp_ret_int = cp_close_module(manager->encrypt_dev);
	if (tmp_ret_int) {
		cp_manager_log(error, manager,
			"close %s failed!.",
			print_module_register_info(&manager->encrypt_dev->register_info, tmp_buf, cp_sizeof(tmp_buf)));
		return -1;
	}

	//销毁模块
	tmp_ret_int = cp_destroy_module(manager, manager->encrypt_dev);
	if (tmp_ret_int) {
		cp_manager_log(error, manager,
			"create [%s] module[0x%x] failed!.",
			manager->cedc.type,
			manager->encrypt_dev);
		return -1;
	}

	return 0;
}
//设置模块参数
cp_int32_t ctrl_css_encrypt_dev_manager(cp_css_encrypt_dev_manager_t *manager, cp_int32_t optname, const cp_void_t* optval)
{
	return 0;
}
//模块创建接口，表示创建一个模块
cp_codec_t* create_css_encrypt_dev_module(cp_css_encrypt_dev_manager_t *manager, const cp_codec_info_t *info)
{
	return CP_NULL;
}

//模块查询接口，表示从管理器中查询一个模块
cp_codec_t* get_css_encrypt_dev_module(cp_css_encrypt_dev_manager_t *manager, const cp_codec_info_t *info)
{
	return CP_NULL;
}

//写模块数据，flag为写模式的扩展标志。默认为0，其他为预留
cp_int32_t register_css_encrypt_dev_module(cp_css_encrypt_dev_manager_t *manager, cp_codec_t *module)
{
	return 0;
}
//关闭模块
cp_int32_t cancel_css_encrypt_dev_module(cp_css_encrypt_dev_manager_t *manager, cp_codec_t *module)
{
	return 0;
}
//退出模块
cp_int32_t destroy_css_encrypt_dev_module(cp_css_encrypt_dev_manager_t *manager, cp_codec_t *module)
{
	return 0;
}
//设置模块参数
cp_int32_t ctrl_css_encrypt_dev_module(cp_css_encrypt_dev_manager_t *manager, cp_codec_t *module, cp_int32_t optname, const cp_void_t* optval)
{
	return 0;
}

