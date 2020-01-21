/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-12-20

Description:

**************************************************************************/

#ifndef _CP_CSS_ENCRYPT_DEV_MANAGER_CONF_STRING_INCLUDE_H_
#define _CP_CSS_ENCRYPT_DEV_MANAGER_CONF_STRING_INCLUDE_H_



#define CP_CSS_ENCRYPT_DEV_MANAGER_CONF_STRING_GENERAL								"general"									//表示general配置项
#define CP_CSS_ENCRYPT_DEV_MANAGER_CONF_STRING_TYPE									"type"										//表示加密类型，取值：hi3531；hi3536
#define CP_CSS_ENCRYPT_DEV_MANAGER_CONF_STRING_NAME									"name"										//表示程序的名称
#define CP_CSS_ENCRYPT_DEV_MANAGER_CONF_STRING_SN									"sn"										//表示序列号


#define CP_CSS_ENCRYPT_DEV_CONF_STRING_ENCRYPT_DATA_CONFIGURE						"encrypt_data_configure"					//加密数据配置信息
#define CP_CSS_ENCRYPT_DEV_CONF_STRING_SOURCE_FILE									"source_file"								//需要被加密的文件
#define CP_CSS_ENCRYPT_DEV_CONF_STRING_DESTINATION_FILE								"destination_file"							//加密后保存的文件



#define CP_CSS_ENCRYPT_DEV_MANAGER_CONF_STRING_HI3531_ENCRYPT_CONFIGURE				"hi3531_encrypt_configure"					//hi3531加密程序配置
#define CP_CSS_ENCRYPT_DEV_MANAGER_CONF_STRING_KEY									"key"										//表示加密的密钥


#define CP_CSS_ENCRYPT_DEV_MANAGER_CONF_STRING_HI3536_ENCRYPT_CONFIGURE				"hi3536_encrypt_configure"					//表示视频相关属性信息
#define CP_CSS_ENCRYPT_DEV_MANAGER_CONF_STRING_IV									"iv"										//表示最大支持分辨率宽度
#define CP_CSS_ENCRYPT_DEV_MANAGER_CONF_STRING_ALG									"alg"										//表示最大支持分辨率高度
#define CP_CSS_ENCRYPT_DEV_MANAGER_CONF_STRING_BIT_WIDTH							"bit_width"									//表示参考帧的数目,取值范围[1, 16],以帧为单位
#define CP_CSS_ENCRYPT_DEV_MANAGER_CONF_STRING_WORK_MODE							"work_mode"									//表示码流发送方式, 0:表示Stream以流方式；1表示frame以帧为单位
#define CP_CSS_ENCRYPT_DEV_MANAGER_CONF_STRING_KEY_LENGTH							"key_length"								//表示是否支持B帧解码, 取值范围[0, 1]
#define CP_CSS_ENCRYPT_DEV_MANAGER_CONF_STRING_CHANGE_FLAG_IV						"change_flag_iv"							//配置的hi3531vo内容


#define CP_CSS_ENCRYPT_DEV_MANAGER_DEV_STRING_HI3536								"hi3536"									//表示hi3536设置内容




#endif