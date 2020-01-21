/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/
#include "cp_filter.h"



cp_filter_t *cp_filter_create();
/*ģ�鴴���ӿڣ���ʾ����һ��ģ��*/
cp_int32_t init_filter(cp_filter_t *filter, const cp_filter_info_t *filter_info);
/*ģ������нӿڣ���ģ��init֮�󣬻ᱻ����*/
cp_int32_t open_filter(cp_filter_t *filter, const cp_filter_info_t *filter_info);
/*��ȡģ�����ݣ�flagΪ��ȡģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��*/
cp_int32_t read_filter(cp_filter_t *filter, cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag);
/*дģ�����ݣ�flagΪдģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��*/
cp_int32_t write_filter(cp_filter_t *filter, const cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag);
/*�ر�ģ��*/
cp_int32_t close_filter(cp_filter_t *filter);
/*�˳�ģ��*/
cp_int32_t exit_filter(cp_filter_t *filter);
/*����ģ�����*/
cp_int32_t set_option_filter(cp_filter_t *filter, cp_int32_t optname, const cp_void_t* optval);
cp_int32_t get_option_filter(cp_filter_t *filter, cp_int32_t optname, cp_void_t* optval);




/*ģ�鴴���ӿڣ���ʾ����һ��ģ��*/
cp_int32_t init_filter(cp_filter_t *filter, const cp_filter_info_t *filter_info)
{
	return 0;
}
/*ģ������нӿڣ���ģ��init֮�󣬻ᱻ����*/
cp_int32_t open_filter(cp_filter_t *filter, const cp_filter_info_t *filter_info)
{
	return 0;
}
/*��ȡģ�����ݣ�flagΪ��ȡģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��*/
cp_int32_t read_filter(cp_filter_t *filter, cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag)
{
	return 0;
}
/*дģ�����ݣ�flagΪдģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��*/
cp_int32_t write_filter(cp_filter_t *filter, const cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag)
{
	return 0;
}
/*�ر�ģ��*/
cp_int32_t close_filter(cp_filter_t *filter)
{
	return 0;
}
/*�˳�ģ��*/
cp_int32_t exit_filter(cp_filter_t *filter)
{
	return 0;
}
/*����ģ�����*/
cp_int32_t set_option_filter(cp_filter_t *filter, cp_int32_t optname, const cp_void_t* optval)
{
	return 0;
}
cp_int32_t get_option_filter(cp_filter_t *filter, cp_int32_t optname, cp_void_t* optval)
{
	return 0;
}







