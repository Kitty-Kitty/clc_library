/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/
#include "cp_session.h"



cp_session_t *cp_session_create();

/*ģ���ʼ���ӿڣ���ģ��create֮�󣬻ᱻ����*/
cp_int32_t init_session(cp_session_t *session, const cp_session_info_t *session_info);
/*ģ������нӿڣ���ģ��init֮�󣬻ᱻ����*/
cp_int32_t open_session(cp_session_t *session, const cp_session_info_t *session_info);
/*��ȡģ�����ݣ�flagΪ��ȡģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��*/
cp_int32_t read_session(cp_session_t *session, cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag);
/*дģ�����ݣ�flagΪдģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��*/
cp_int32_t write_session(cp_session_t *session, const cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag);
/*�ر�ģ��*/
cp_int32_t close_session(cp_session_t *session);
/*�˳�ģ��*/
cp_int32_t exit_session(cp_session_t *session);
/*����ģ�����*/
cp_int32_t set_option_session(cp_session_t *session, cp_int32_t optname, const cp_void_t* optval);
cp_int32_t get_option_session(cp_session_t *session, cp_int32_t optname, cp_void_t* optval);




/*ģ���ʼ���ӿڣ���ģ��create֮�󣬻ᱻ����*/
cp_int32_t init_session(cp_session_t *session, const cp_session_info_t *session_info)
{
	return 0;
}
/*ģ������нӿڣ���ģ��init֮�󣬻ᱻ����*/
cp_int32_t open_session(cp_session_t *session, const cp_session_info_t *session_info)
{
	return 0;
}
/*��ȡģ�����ݣ�flagΪ��ȡģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��*/
cp_int32_t read_session(cp_session_t *session, cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag)
{
	return 0;
}
/*дģ�����ݣ�flagΪдģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��*/
cp_int32_t write_session(cp_session_t *session, const cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag)
{
	return 0;
}
/*�ر�ģ��*/
cp_int32_t close_session(cp_session_t *session)
{
	return 0;
}
/*�˳�ģ��*/
cp_int32_t exit_session(cp_session_t *session)
{
	return 0;
}
/*����ģ�����*/
cp_int32_t set_option_session(cp_session_t *session, cp_int32_t optname, const cp_void_t* optval)
{
	return 0;
}
cp_int32_t get_option_session(cp_session_t *session, cp_int32_t optname, cp_void_t* optval)
{
	return 0;
}







