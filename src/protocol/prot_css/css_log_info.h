/**************************************************************************

* Copyright: novigo

* Author: tianhuiming@novigo.com.cn

* Date��2016-5-19
        
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
	cp_char_t						 id[CP_APP_DEFAULT_ID_LENGTH];					//��ʾ�豸�ı���id
	cp_uchar_t						 flag;											//��ʾ��ѯ����������
	cp_int32_t						 file_number;									//��ʾ�ļ�����
	cp_uint32_t						 file_size;										//��ʾ�ļ���С
	gmdt_rectpair_t					 file_create_time;								//��ʾ�ļ��Ĵ���ʱ��
	gmdt_rectpair_t					 file_modify_time;								//��ʾ�ļ�������޸�ʱ��,�������Ϊ�ļ���ǰ�Ľ���ʱ��
	cp_char_t						 file_name[CP_APP_DEFAULT_STRING_LENGTH];		//��ʾ��־�ļ���
	cp_char_t						 file_extension[CP_APP_DEFAULT_LENGTH];			//��ʾ�ļ�����չ��
	cp_char_t						 file_path[CP_APP_DEFAULT_STRING_LENGTH];		//��ʾ�ļ����������·����Ϣ
	cp_void_t						 *file_data_p;									//��ʾ��־�ļ�����
}cp_log_info_t;


#endif