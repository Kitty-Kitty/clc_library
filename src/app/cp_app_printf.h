/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-11-08

Description:

**************************************************************************/

#ifndef _CP_APP_PRINTF_INCLUDE_H_
#define _CP_APP_PRINTF_INCLUDE_H_




//�����Ƿ���õ���ģʽ����־��ʽ����ʽģʽ����˺����Ĵ�ӡ
#define	CP_APP_PRINTF_DEBUG_FORMAT										1




#if defined(CP_APP_PRINTF_DEBUG_FORMAT)

//�������°�װ�˴�ӡ��Ϣ�ĸ�ʽ
#define	 cp_app_log(level, app, format, ...)								\
	do {																	\
			cp_log_##level((app)->logger, "app[%s(0x%x)] func[%s:%d] " format, (app)->register_info.description, (app), __FUNCTION__, __LINE__, ##__VA_ARGS__)			\
	;} while (0)

#else

//�������°�װ�˴�ӡ��Ϣ�ĸ�ʽ
#define	 cp_app_log(level, app, format, ...)								\
	do {																	\
			cp_log_##level((app)->logger, (format), ##__VA_ARGS__)			\
	;} while (0)

#endif


#endif