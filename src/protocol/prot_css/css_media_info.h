/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/
#ifndef _CSS_MEDIA_INFO_INCLUDE_H_
#define _CSS_MEDIA_INFO_INCLUDE_H_

#include "cp_typedef.h"
#include "cp_default.h"
#include "prot_gmp_core.h"
#include "css_device_info.h"




typedef struct cp_timestamp_s						cp_timestamp_t;
// typedef struct cp_rect_s							cp_rect_t;
typedef struct cp_play_position_s					cp_play_position_t;
typedef struct cp_play_channel_info_s				cp_play_channel_info_t;




#pragma pack(1)

typedef enum cp_media_process_type_enum
{
	cp_media_process_type_none = 0,
	cp_media_process_type_audio,
	cp_media_process_type_video,
	cp_media_process_type_all
}cp_media_process_type_e;


/************************************************************************/
/* ʱ�������                                                            */
/************************************************************************/
struct cp_timestamp_s
{
	cp_uint32_t						a_sec;								//��ʾʱ����еľ���ʱ�䣨absolutely time���� ����
	gm_std_uint						a_nsec;								//��ʾʱ����еľ���ʱ�䣨absolutely time������ ����
	gm_std_uint						r_sec;								//��ʾʱ����е����ʱ�䣨relatives time���� ����
	gm_std_uint						r_nsec;								//��ʾʱ����е����ʱ�䣨relatives time���� ����
};


/************************************************************************/
/* ����ͼ�ξ�����Ϣ                                                      */
/************************************************************************/
struct cp_play_position_s
{
	cp_rect_t						source;								//��ʾý��Դ������Ϣ
	cp_rect_t						dest;								//��ʾý��ԴĿ��λ����Ϣ
};

/************************************************************************/
/* �쳣�ϱ�                                                             */
/************************************************************************/
typedef struct cp_exception_info
{
	cp_uint64_t						time;
	cp_int32_t						media_exception_type;
	cp_int32_t						index;
	cp_int32_t						status;
	cp_int32_t						private_status;
	cp_char_t						description[CP_APP_DEFAULT_BUFFER_LENGTH];
	cp_char_t						meidia_id[CP_APP_DEFAULT_ID_LENGTH];
	cp_char_t						play_session[CP_APP_DEFAULT_SESSION_ID_LENGTH];
}cp_exception_info_t;

typedef struct cp_jpeg_info
{
	cp_int32_t						w;												//��һ����������ͼƬ��С
	cp_int32_t						h;
	cp_uint32_t						iobuflen;
	cp_char_t						id[CP_APP_DEFAULT_ID_LENGTH];					//ͼƬΨһ���
	cp_char_t						*iobuf;											//ͼƬ����
	cp_uint32_t						channelID;										//�豸����ID
	cp_uchar_t						bfps;
	cp_uchar_t						type;											//ͼƬ����
}cp_jpeg_info_t;

typedef struct cp_checkcolor_info_s
{
	cp_uchar_t						source_color[CP_APP_DEFAULT_LENGTH];			//��ʾԴ��ɫ��ֵ
	cp_uchar_t						dest_color[CP_APP_DEFAULT_LENGTH];				//��ʾĿ����ɫ��ֵ
}cp_checkcolor_info_t;

typedef struct cp_video_source_info_s
{
	cp_int32_t						height;											//ý��߶�
	cp_int32_t						width;											//ý����
	cp_int32_t						fps;											//ý��֡��
	cp_int32_t						bps;											//ý������������Ϣ
	cp_int32_t						encodec_type;									//ý��������ͱ��
	cp_char_t						encodec_name[CP_APP_DEFAULT_STRING_LENGTH];		//ý�����������
}cp_video_source_info_t;

typedef struct cp_audio_source_info_s
{

	cp_int32_t						volume;											//��Ƶ����
	cp_int32_t						bit_rate;										//��Ƶ�������
	cp_int32_t						sample_rate;									//����Ƶ�ʣ���λ��Hz��
	cp_int32_t						encodec_type;									//ý��������ͱ��
	cp_int32_t						sound_channel_type;								//�����������ͣ���sound channel name ��ѡһ
	cp_char_t						sound_channel_name[CP_APP_DEFAULT_STRING_LENGTH];			//������������
	cp_char_t						encodec_name[CP_APP_DEFAULT_STRING_LENGTH];		//ý�����������
}cp_audio_source_info_t;


typedef struct cp_media_info_s
{
	cp_uchar_t						type;											//ý������

	cp_video_source_info_t			video_source;									//��ʾ��Ƶ��Ϣ
	cp_audio_source_info_t			audio_source;									//��ʾ��Ƶ��Ϣ

	cp_char_t						id[CP_APP_DEFAULT_ID_LENGTH];					//ý��Ψһ���ID
	cp_char_t						name[CP_APP_DEFAULT_STRING_LENGTH];				//ý������
	cp_char_t						addr[CP_APP_DEFAULT_BUFFER_LENGTH];				//ý���ַ
}cp_media_info_t;

typedef struct cp_stream_description_s
{
	cp_int32_t						transport_type;									//��ʾ��ͨ��ý��Ĵ��䷽ʽ
	cp_int32_t						distribution_type;								//��ʾͨ��ý�����ַ�������	
}cp_stream_description_t;

typedef struct cp_cmd_info_s
{
	cp_uint32_t						time_s;											//��ʾָ��ʱ����
	cp_uint32_t						time_ns;										//��ʾָ��ʱ������
	cp_int32_t						sequence;										//��ʾָ�����
}cp_cmd_info_t;

typedef struct cp_channel_stop_info_s
{
	cp_char_t						play_session[CP_APP_DEFAULT_SESSION_ID_LENGTH];	//���浱ǰͨ����Ψһ�ỰID
	cp_char_t						id[CP_APP_DEFAULT_ID_LENGTH];					//ý��Ψһ���ID
	cp_uint32_t						index;										//ý��Ψһ���ID
	cp_uchar_t						type;											//ý������
	cp_char_t						encode_type;									//ý���������
	cp_int32_t						status;
}cp_channel_stop_info_t;

typedef struct cp_channel_info_s
{
	cp_int32_t						layer;											//ý����
	cp_uint32_t						index;											//ý��Ψһ���ID
	cp_int32_t						mode;											//ý�岥������
	cp_stream_description_t			stream_description;								//ͨ����ý�����������
	cp_play_addr_t					play_addr_info;									//���浱ǰͨ������ͨ�������IP��ַ
	cp_multicast_addr_t				multicast_info;									//��ʾ�鲥�ĵ�ַ
	cp_char_t						play_session[CP_APP_DEFAULT_SESSION_ID_LENGTH];	//���浱ǰͨ����Ψһ�ỰID
	cp_play_position_t				position;										//ý�岥�ŵĴ���λ��
}cp_channel_info_t;

typedef struct cp_channel_rect_info_s
{
	cp_uint32_t						index;											//��ʾý��ͨ����
	gmdt_rect_t						rect_pair[CP_APP_DEFAULT_RECT_PARE_NUMBER];		//��ʾ���ο���Ϣ
}cp_channel_rect_info_t;

typedef struct cp_media_group_info_s
{
	cp_int32_t						no;												//��ʾ�豸���
	cp_int32_t						group_id;										//��ʾ����
	list_node						chan_rect_list;									//��ʾͨ����Ϣ
}cp_media_group_info_t;

typedef struct cp_media_channel_info_s
{
	cp_int32_t						group_id;										//��ʾ����id����
	cp_channel_info_t				channel_info;									//��ʾͨ����Ϣ
	cp_media_info_t					media_info;										//��ʾý����Ϣ
}cp_media_channel_info_t;


struct cp_play_channel_info_s
{
	cp_media_process_type_e			mpy;											//ý�崦������
	cp_timestamp_t					command_time;									//��ʾָ��ִ��ʱ��
	cp_uint64_t						sequence_number;								//��ʾָ�����
	cp_array_t						mci_array;										//��ʾý��ͨ���б�cp_media_channel_info_t����
};


typedef struct cp_background_media_info_s
{
	cp_uchar_t						layer;											//��ʾ��ʾͼƬ��ͼ���ϵ
	cp_uchar_t						type;											//ý�����ͣ�����ͼƬ��ʾͼƬ���ͣ�������Ļ����Բ�ʹ��
	cp_char_t						id[CP_APP_DEFAULT_ID_LENGTH];					//ý��Ψһ���ID
	cp_uchar_t						back_color[CP_APP_DEFAULT_DOUBLE_LENGTH];		//��ʾ��ɫ����ͼƬ��ɫ
	cp_uchar_t						*picture_p;										//��ʾý��ͼƬ����
	gmdt_rectpair_t					size;											//��ʾ���ο���Ϣ

	gmdt_rectpair_t					position;										//ý�岥�ŵĴ���λ��
	gmdt_rectpair_t					back_size;										//��ʾ�������С
	cp_float_t						ruler_height;									//������Ļ�߶ȵ���������׵�ת������
	cp_float_t						ruler_width;									//������Ļ��ȵ���������׵�ת������
	cp_int32_t						rows;											//��ʾ��Ҫ�����õ�����
	cp_int32_t						columns;										//��ʾ��Ҫ�����õ�����
	cp_int32_t						content_font_size;								//��ʾ�ı����ֺŴ�С
	cp_int32_t						content_space;									//��ʾ�ı��ļ����С
	cp_char_t						content[CP_APP_DEFAULT_DEFAULT_WORDS_LENGTH];	//��ʾ�ı��������
	cp_char_t						content_font[CP_APP_DEFAULT_STRING_LENGTH];		//��ʾ�ı�����������
	gmdt_rectpair_t					border;											//��һ������������ʾ��Ļ�߿����������ĸ�����ߴ���Ϣ���ڶ�������Ԥ��
	cp_uchar_t						op_type;										//�������ͣ���Ҫ��Ϊ���ñ���ͼƬ��������Ļ����
	cp_uchar_t						content_style;									//��ʾ�ı��Ķ��뷽ʽ
	cp_uchar_t						content_encode;									//��ʾ�ı��ı��뷽ʽ
	cp_uchar_t						content_diaphanity;								//��ʾ�ı���͸����
	cp_uchar_t						back_diaphanity;								//��ʾ������͸����
	cp_uchar_t						content_color[CP_APP_DEFAULT_DOUBLE_LENGTH];	//��ʾ��Ļ������ɫ
}cp_background_media_info_t;

typedef struct cp_background_reflesh_info_s
{
	cp_char_t						type;											//��ʾˢ�µķ�ʽ
	cp_char_t						background[CP_APP_DEFAULT_ID_LENGTH];			//��ʾͼƬ��Ψһ����id
	gmdt_rectpair_t					size;											//�豸����Ļ��Ϣ
	gmdt_rectpair_t					reflesh_time;									//��ʾˢ��ʱ����Ϣ
}cp_background_reflesh_info_t;

typedef struct cp_player_background_info_s
{
	cp_uchar_t						is_set;											//��ʾ�Ƿ񽫴�����ͼƬ���õ��豸,0��ʾ����Ҫ��1��ʾ��Ҫ
	gmdt_rectpair_t					size;											//�豸����Ļ��Ϣ
	gmdt_rectpair_t					border;											//�豸����Ļ�߿���Ϣ
	cp_char_t						backcolor[CP_APP_DEFAULT_DOUBLE_LENGTH];		//��ʾ�豸��Ĭ�ϱ���ɫ
	cp_host_t						host_info;										//��ʾ���ݹ������豸��Ϣ
	cp_background_media_info_t		media_info;										//��ʾ�豸ý���б�
	cp_background_reflesh_info_t	reflesh_info;									//��ʾ�豸ˢ����Ϣ
}cp_player_background_info_t;

typedef struct cp_play_task_s
{
	cp_char_t						id[CP_APP_DEFAULT_ID_LENGTH];					//��ʾ����ı���ID
	cp_char_t						name[CP_APP_DEFAULT_LENGTH];					//��ʾ���������
	cp_int32_t						serial_number;									//��ʾ����ִ�б���
	cp_int32_t						status;											//��ʾ״̬��
	gmdt_rectpair_t					begin_time;										//��ʾ����ʼʱ��
	gmdt_rectpair_t					end_time;										//��ʾ�������ʱ��
	gmdt_rectpair_t					interval_time;									//��ʾ�����ظ����ʱ��
	cp_char_t						type;											//��ʾ��������
	cp_int32_t						loop_times;										//��ʾ����ѭ������
}cp_play_task_t;



#pragma pack()

#endif