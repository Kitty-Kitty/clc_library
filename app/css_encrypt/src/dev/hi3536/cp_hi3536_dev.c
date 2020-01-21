/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/
#include "cp_hi3536_dev.h"
#include "cp_include.h"
#include "cp_hi3536_cipher.h"



/*模块创建接口，表示创建一个模块*/
cp_int32_t init_hi3536_dev(cp_hi3536_dev_t *hi3536_dev, const cp_hi3536_dev_info_t *hi3536_dev_info);
/*模块打开运行接口，在模块init之后，会被调用*/
cp_int32_t open_hi3536_dev(cp_hi3536_dev_t *hi3536_dev, const cp_hi3536_dev_info_t *hi3536_dev_info);
/*读取模块数据，flag为读取模式的扩展标志。默认为0，其他为预留*/
cp_int32_t read_hi3536_dev(cp_hi3536_dev_t *hi3536_dev, cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag);
/*写模块数据，flag为写模式的扩展标志。默认为0，其他为预留*/
cp_int32_t write_hi3536_dev(cp_hi3536_dev_t *hi3536_dev, const cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag);
/*关闭模块*/
cp_int32_t close_hi3536_dev(cp_hi3536_dev_t *hi3536_dev);
/*退出模块*/
cp_int32_t exit_hi3536_dev(cp_hi3536_dev_t *hi3536_dev);
/*设置模块参数*/
cp_int32_t set_option_hi3536_dev(cp_hi3536_dev_t *hi3536_dev, cp_int32_t optname, const cp_void_t* optval);
/*获取模块参数*/
cp_int32_t get_option_hi3536_dev(cp_hi3536_dev_t *hi3536_dev, cp_int32_t optname, cp_void_t* optval);




/*创建一个模块*/
cp_hi3536_dev_t* create_hi3536_dev(cp_module_register_t *register_info, cp_codec_manager_t *manager, cp_hi3536_dev_info_t *info)
{
	cp_int32_t							ret_int = 0;
	cp_hi3536_dev_t						*tmp_module = CP_NULL;
	cp_pool_info_t						tmp_pool_info = { 0, };


	if (!register_info || !manager || !info) {
		return CP_NULL;
	}

	tmp_module = cp_malloc_module(manager, cp_hi3536_dev_t, &tmp_pool_info);
	if (!tmp_module) {
		return CP_NULL;
	}
	CP_MODULE_SET_HANDLERS(tmp_module, hi3536_dev);
	return tmp_module;
}

/*释放模块*/
cp_int32_t destroy_hi3536_dev(cp_codec_manager_t *manager, cp_hi3536_dev_t* hi3536_dev)
{
	if (!manager || !hi3536_dev) {
		return -1;
	}
	cp_free_module(hi3536_dev);
	return 0;
}

/*模块创建接口，表示创建一个模块*/
cp_int32_t init_hi3536_dev(cp_hi3536_dev_t *hi3536_dev,
	const cp_hi3536_dev_info_t *hi3536_dev_info)
{
	cp_int32_t										tmp_ret_int = 0;



	//初始化配置信息
	tmp_ret_int = hi3536_dev_parse_configure((cp_module_t*)hi3536_dev, &hi3536_dev->hdc);
	if (tmp_ret_int) {
		cp_module_log(error, hi3536_dev, "hi3536_dev_parse_configure() error.");
		return tmp_ret_int;
	}

	//赋值配置信息
	hi3536_dev->cedc = (cp_css_encrypt_dev_configure_t *)(hi3536_dev_info->data);

	//创建cipher配置内容
	tmp_ret_int = cp_hi3536_cipher_create(hi3536_dev, &hi3536_dev->hdc);
	if (tmp_ret_int) {
		cp_module_log(error, hi3536_dev, "cp_hi3536_cipher_create() error.");
		return tmp_ret_int;
	}

	//初始化cipher配置内容
	tmp_ret_int = cp_hi3536_cipher_init(hi3536_dev, &hi3536_dev->hdc);
	if (tmp_ret_int) {
		cp_module_log(error, hi3536_dev, "cp_hi3536_cipher_init() error.");
		return tmp_ret_int;
	}

	return 0;
}

/*模块打开运行接口，在模块init之后，会被调用*/
cp_int32_t open_hi3536_dev(cp_hi3536_dev_t *hi3536_dev,
	const cp_hi3536_dev_info_t *hi3536_dev_info)
{
	cp_int32_t										tmp_ret_int = 0;



	if (!hi3536_dev) {
		return -1;
	}

	//打开cipher配置内容
	tmp_ret_int = cp_hi3536_cipher_open(hi3536_dev, hi3536_dev->hcc);
	if (tmp_ret_int) {
		cp_module_log(error, hi3536_dev, "cp_hi3536_cipher_open() error.");
		return tmp_ret_int;
	}

	//开始进行加密
	tmp_ret_int = cp_hi3536_cipher_encrypt(hi3536_dev, hi3536_dev->hcc);
	if (tmp_ret_int) {
		cp_module_log(error, hi3536_dev, "cp_hi3536_cipher_encrypt() error.");
		return tmp_ret_int;
	}

	return 0;
}

/*读取模块数据，flag为读取模式的扩展标志。默认为0，其他为预留*/
cp_int32_t read_hi3536_dev(cp_hi3536_dev_t *hi3536_dev,
	cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag)
{
	return 0;
}

/*写模块数据，flag为写模式的扩展标志。默认为0，其他为预留*/
cp_int32_t write_hi3536_dev(cp_hi3536_dev_t *hi3536_dev,
	const cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag)
{
	return 0;
}

/*关闭模块*/
cp_int32_t close_hi3536_dev(cp_hi3536_dev_t *hi3536_dev)
{
	cp_int32_t										tmp_ret_int = 0;



	if (!hi3536_dev) {
		return -1;
	}

	//打开cipher配置内容
	tmp_ret_int = cp_hi3536_cipher_close(hi3536_dev);
	if (tmp_ret_int) {
		cp_module_log(error, hi3536_dev, "cp_hi3536_cipher_close() error.");
		return tmp_ret_int;
	}

	return 0;
}

/*退出模块*/
cp_int32_t exit_hi3536_dev(cp_hi3536_dev_t *hi3536_dev)
{
	cp_int32_t										tmp_ret_int = 0;



	if (!hi3536_dev) {
		return -1;
	}

	//打开cipher配置内容
	tmp_ret_int = cp_hi3536_cipher_destroy(hi3536_dev);
	if (tmp_ret_int) {
		cp_module_log(error, hi3536_dev, "cp_hi3536_cipher_destroy() error.");
		return tmp_ret_int;
	}
	
	return 0;
}

/*设置模块参数*/
cp_int32_t set_option_hi3536_dev(cp_hi3536_dev_t *hi3536_dev, cp_int32_t optname, const cp_void_t* optval)
{
	return 0;
}

cp_int32_t get_option_hi3536_dev(cp_hi3536_dev_t *hi3536_dev, cp_int32_t optname, cp_void_t* optval)
{
	return 0;
}
