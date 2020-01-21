/**************************************************************************

* Copyright: novigo

* Author: tianhuiming@novigo.com.cn

* Date��2016-5-12
        
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



//������°��ı��淽ʽ
typedef enum cp_update_packet_save_type_enum
{
	cp_update_packet_save_type_none = 0x00,
	cp_update_packet_save_type_all = 0x01,
	cp_update_packet_save_type_archive = 0x10,
}cp_update_packet_save_type;






typedef struct update_operation_flag_struct
{
	//ǰ�����ֽ���Ԥ������
	cp_uchar_t					h_first;						//��һ�ֽ�Ԥ��
	cp_uchar_t					h_second;						//�ڶ��ֽ�Ԥ��
	//�������ֽڱ�ʾOperation Flag
	unsigned int				op_flag_none7 : 1;				//Ԥ��
	unsigned int				op_flag_used : 1;				//�Ƿ����
	unsigned int				op_flag_must : 1;				//ǿ��
	unsigned int				op_flag_none4 : 1;				//Ԥ��
	unsigned int				op_flag_none3 : 1;				//Ԥ��
	unsigned int				op_flag_none2 : 1;				//Ԥ��
	unsigned int				op_flag_none1 : 1;				//Ԥ��
	unsigned int				op_flag_none0 : 1;				//Ԥ��
	//���ĸ��ֽڱ�ʾOperation Type
	unsigned int				op_type_none7 : 1;				//Ԥ��
	unsigned int				op_type_version_master : 1;		//���汾
	unsigned int				op_type_version_salve : 1;		//���汾
	unsigned int				op_type_datetime : 1;			//����ʱ��
	unsigned int				op_type_serial_master : 1;		//���ͺ�
	unsigned int				op_type_serial_slave : 1;		//���ͺ�
	unsigned int				op_type_platform_hardware : 1;	//Ӳ��ƽ̨
	unsigned int				op_type_platform_software : 1;	//���ƽ̨
}update_operation_flag;


typedef struct cp_update_info_s
{
/*
	cp_uchar_t						*m_program_file_p;				//���°���������
	cp_uchar_t						*m_file_data_p;					//���°��г�����������

	cp_bool_t						m_is_update_conf_file;			//��ʾ�Ƿ����conf/conf.xml�ļ���PC_TRUE��ʾ��Ҫ���£����ʱ��IP���ܻᱻ�޸ģ���PC_FLASE��ʾ����Ҫ����
	cp_bool_t						m_is_update_data_file;			//��ʾ�Ƿ����data�е������ļ���PC_TRUE��ʾ��Ҫ���£����ʱ�����ݿ��ܱ�ɾ������PC_FLASE��ʾ����Ҫ����

	cp_uint32_t						m_program_file_len;				//���°��������ݳ���
	cp_uint32_t						m_file_data_len;				//���°��г����������ݳ���
*/
	cp_char_t						id[CP_APP_DEFAULT_ID_LENGTH];									//��ʾ�豸�ı���ID
	cp_uchar_t						type;															//��ʾ�豸����
	cp_uchar_t						packet_type;													//��ʾ����������ʽ
	cp_int32_t						version;														//��ʾ�汾����Ϣ
	cp_int32_t						version_addtion;												//��ʾ�汾������Ϣ
	cp_uint32_t						time_s;															//��ʾ����ķ���ʱ����Ϣ,�벿������
	cp_uint32_t						time_ns;														//��ʾ����ķ���ʱ����Ϣ,���벿������

	cp_char_t						packet_name[CP_APP_DEFAULT_STRING_LENGTH];						//��ʾ���������
	cp_char_t						serial_master[CP_APP_DEFAULT_STRING_LENGTH];					//��ʾ�豸���ͺ�
	cp_char_t						serial_slave[CP_APP_DEFAULT_STRING_LENGTH];						//��ʾ�豸���ͺ�
	cp_char_t						platform_hardware[CP_APP_DEFAULT_STRING_LENGTH];				//��ʾƽ̨Ӳ����Ϣ
	cp_char_t						platform_software[CP_APP_DEFAULT_STRING_LENGTH];				//��ʾƽ̨�����Ϣ
	cp_char_t						change_log[CP_APP_DEFAULT_STRING_LENGTH];						//��ʾ����ĸ�����Ϣ
	update_operation_flag			operation_flag;													//��ʾʹ�ñ�ʶ
}cp_update_info_t;


#endif