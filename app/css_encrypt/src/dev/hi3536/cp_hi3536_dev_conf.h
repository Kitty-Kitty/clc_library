/*******************************************************************************
*
*Copyright:novigo
*
*File name: cp_hi3536_dev_conf.h
*
*Author:fangzhenmu@novigo.com.cn
*
*Version: 1.0
*
*Date:2017/08/17
*
*Description: create (cp_hi3536_dev_conf.h)
*
*Others:
*
*History:
*******************************************************************************/

#ifndef _CP_HI3536_DEV_CONF_H_
#define _CP_HI3536_DEV_CONF_H_



#include "cp_core.h"
#include "cp_module_core.h"
#include "cp_hi3536_dev_conf_string.h"



#define CP_HI3536_DEV_ENCRYPT_KEY_LENGTH					128						//表示密钥的长度


typedef struct cp_hi3536_dev_configure_s					cp_hi3536_dev_configure_t;



#pragma pack(1)

/************************************************************************/
/* hi3536相关配置                                                      */
/************************************************************************/
struct cp_hi3536_dev_configure_s
{
	cp_char_t						key[CP_HI3536_DEV_ENCRYPT_KEY_LENGTH];			//表示加密密钥
	cp_char_t						iv[CP_HI3536_DEV_ENCRYPT_KEY_LENGTH];			//表示初始向量
	cp_int32_t						alg;											//表示加密算法,取值[0, 2]
	cp_int32_t						bit_width;										//表示加密或解密的位宽,取值[0, 3]
	cp_int32_t						work_mode;										//表示工作模式,取值[0, 5]
	cp_int32_t						key_length;										//表示密钥长度,取值[0, 4]
	cp_int32_t						change_flag_iv;									//表示向量变更,取值[0, 1]
};

#pragma pack()



/************************************************************************/
/*解析配置文件                                                           */
/************************************************************************/
cp_int32_t	hi3536_dev_parse_configure(cp_module_t *module, cp_hi3536_dev_configure_t *hdc);




#endif //_CP_HI3536_DEV_CONF_H_


