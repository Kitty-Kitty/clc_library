/**************************************************************************

* Copyright: novigo

* Author: tianhuiming@novigo.com.cn

* Date：2016-5-19
        
* Description:

**************************************************************************/




#ifndef _CSS_LOG_INFO_INCLUDE_H_
#define _CSS_LOG_INFO_INCLUDE_H_

#include "cp_core.h"
#include "cp_default.h"
#include "prot_gmp_core.h"



#define			CSS_LOG_FILE_EXTENSION_ZIP							"zip"


typedef	enum cp_log_flag_enum
{
	cp_log_flag_all = 0x00,
	cp_log_flag_file_name = 0x02,
	cp_log_flag_file_type = 0x04,
	cp_log_flag_direction = 0x08,
	cp_log_flag_file_size = 0x10,
	cp_log_flag_file_time = 0x20,
}cp_log_flag;

typedef struct cp_log_info_s
{
	cp_char_t						 id[CP_APP_DEFAULT_ID_LENGTH];					//表示设备的编码id
	cp_uchar_t						 flag;											//表示查询操作的类型
	cp_int32_t						 file_number;									//表示文件数量
	cp_uint32_t						 file_size;										//表示文件大小
	gmdt_rectpair_t					 file_create_time;								//表示文件的创建时间
	gmdt_rectpair_t					 file_modify_time;								//表示文件的最后修改时间,可以理解为文件当前的结束时间
	cp_char_t						 file_name[CP_APP_DEFAULT_STRING_LENGTH];		//表示日志文件名
	cp_char_t						 file_extension[CP_APP_DEFAULT_LENGTH];			//表示文件的扩展名
	cp_char_t						 file_path[CP_APP_DEFAULT_STRING_LENGTH];		//表示文件保存的完整路径信息
	cp_void_t						 *file_data_p;									//表示日志文件内容
}cp_log_info_t;


#endif