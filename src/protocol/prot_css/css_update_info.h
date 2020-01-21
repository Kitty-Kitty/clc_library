/**************************************************************************

* Copyright: novigo

* Author: tianhuiming@novigo.com.cn

* Date：2016-5-12
        
* Description:

**************************************************************************/



#ifndef _CSS_UPDATE_INFO_INCLUDE_H_
#define _CSS_UPDATE_INFO_INCLUDE_H_

#include "cp_core.h"



typedef	enum cp_packet_type_enum
{
	cp_packet_type_none = 0x00,
	cp_packet_type_player = 0x30,
	cp_packet_type_zip = 0x40,
}cp_packet_type;



//定义更新包的保存方式
typedef enum cp_update_packet_save_type_enum
{
	cp_update_packet_save_type_none = 0x00,
	cp_update_packet_save_type_all = 0x01,
	cp_update_packet_save_type_archive = 0x10,
}cp_update_packet_save_type;






typedef struct update_operation_flag_struct
{
	//前两个字节是预留部分
	cp_uchar_t					h_first;						//第一字节预留
	cp_uchar_t					h_second;						//第二字节预留
	//第三个字节表示Operation Flag
	unsigned int				op_flag_none7 : 1;				//预留
	unsigned int				op_flag_used : 1;				//是否操作
	unsigned int				op_flag_must : 1;				//强制
	unsigned int				op_flag_none4 : 1;				//预留
	unsigned int				op_flag_none3 : 1;				//预留
	unsigned int				op_flag_none2 : 1;				//预留
	unsigned int				op_flag_none1 : 1;				//预留
	unsigned int				op_flag_none0 : 1;				//预留
	//第四个字节表示Operation Type
	unsigned int				op_type_none7 : 1;				//预留
	unsigned int				op_type_version_master : 1;		//主版本
	unsigned int				op_type_version_salve : 1;		//副版本
	unsigned int				op_type_datetime : 1;			//日期时间
	unsigned int				op_type_serial_master : 1;		//主型号
	unsigned int				op_type_serial_slave : 1;		//副型号
	unsigned int				op_type_platform_hardware : 1;	//硬件平台
	unsigned int				op_type_platform_software : 1;	//软件平台
}update_operation_flag;


typedef struct cp_update_info_s
{
/*
	cp_uchar_t						*m_program_file_p;				//更新包数据内容
	cp_uchar_t						*m_file_data_p;					//更新包中程序数据内容

	cp_bool_t						m_is_update_conf_file;			//表示是否更新conf/conf.xml文件，PC_TRUE表示需要更新（这个时候IP可能会被修改）；PC_FLASE表示不需要更新
	cp_bool_t						m_is_update_data_file;			//表示是否更新data中的数据文件，PC_TRUE表示需要更新（这个时候数据可能被删除）；PC_FLASE表示不需要更新

	cp_uint32_t						m_program_file_len;				//更新包数据内容长度
	cp_uint32_t						m_file_data_len;				//更新包中程序数据内容长度
*/
	cp_char_t						id[CP_APP_DEFAULT_ID_LENGTH];									//表示设备的编码ID
	cp_uchar_t						type;															//表示设备类型
	cp_uchar_t						packet_type;													//表示软件包打包方式
	cp_int32_t						version;														//表示版本号信息
	cp_int32_t						version_addtion;												//表示版本附加信息
	cp_uint32_t						time_s;															//表示软件的发布时间信息,秒部分内容
	cp_uint32_t						time_ns;														//表示软件的发布时间信息,纳秒部分内容

	cp_char_t						packet_name[CP_APP_DEFAULT_STRING_LENGTH];						//表示软件包名称
	cp_char_t						serial_master[CP_APP_DEFAULT_STRING_LENGTH];					//表示设备主型号
	cp_char_t						serial_slave[CP_APP_DEFAULT_STRING_LENGTH];						//表示设备副型号
	cp_char_t						platform_hardware[CP_APP_DEFAULT_STRING_LENGTH];				//表示平台硬件信息
	cp_char_t						platform_software[CP_APP_DEFAULT_STRING_LENGTH];				//表示平台软件信息
	cp_char_t						change_log[CP_APP_DEFAULT_STRING_LENGTH];						//表示软件的更新信息
	update_operation_flag			operation_flag;													//表示使用标识
}cp_update_info_t;


#endif