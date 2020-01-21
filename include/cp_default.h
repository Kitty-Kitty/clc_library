/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-23

Description:

**************************************************************************/



#ifndef _CP_DEFAULT_INCLUDE_H_
#define _CP_DEFAULT_INCLUDE_H_






#if defined(WIN32)
#define CP_DEFAULT_CONF_FILE								"../../../../configs/css.conf"
#else
//#define CP_DEFAULT_CONF_FILE								"/data/etc/css.conf"
#define CP_DEFAULT_CONF_FILE								"./configs/css.conf"
#endif

#define CP_DEFAULT_ENV_CP_CONF_FILE							"CP_ENV_CONF_PATH"
#define CP_DEFAULT_ENV_CP_DAEMON_MODE						"CP_ENV_DAEMON_MODE"
#define CP_DEFAULT_ENV_CP_DAEMON_MODE_NO					"no"
#define CP_DEFAULT_ENV_CP_DAEMON_MODE_YES					"yes"


#define	GMP_RETURN_SUCCESSED								"Successed"
#define	GMP_RETURN_FAILED									"Failed"


//定义模块注册管理器的最大数量
#define CP_LIBRARY_MODULE_MANAGER_MAX_SIZE					16

//定义模块注册器的最大数量
#define CP_LIBRARY_MODULE_MAX_SIZE							16



#define CP_APP_DEFAULT_CHAR_LENGTH							1

#define CP_APP_DEFAULT_INT_LENGTH							4

#define CP_APP_DEFAULT_DOUBLE_LENGTH						8

#define CP_APP_DEFAULT_TIMER_TASK_NUM						12

#define CP_APP_DEFAULT_RECT_PARE_NUMBER						32

#define CP_APP_DEFAULT_LENGTH								16

#define CP_APP_DEFAULT_SESSION_ID_LENGTH					33

#define CP_APP_DEFAULT_ID_LENGTH							65

#define CP_APP_DEFAULT_STRING_LENGTH						128

#define CP_APP_DEFAULT_BUFFER_LENGTH						256

#define CP_APP_DEFAULT_CONFIG_FILENAME_LENGTH				256

#define CP_APP_DEFAULT_GMPH_BUFFER_LEN						512

#define	CP_APP_DEFAULT_ERROR_TEXT_BUFFER_LEN				512

#define CP_APP_DEFAULT_TIMER_TIMEOUT						1000

#define CP_APP_DEFAULT_TIMER_REPEAT							1000

#define CP_APP_DEFAULT_DEFAULT_WORDS_LENGTH					1024

#define CP_APP_DEFAULT_WIDTH_MAX							1920

#define CP_APP_DEFAULT_HEIGHT_MAX							1080





#endif


