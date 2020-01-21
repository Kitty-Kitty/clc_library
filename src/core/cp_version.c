/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/
#include "cp_core.h"



#ifdef CP_BUILD_HOST_INFO
#define		CP_VER_HOST		#CP_BUILD_HOST_INFO
#else
#define		CP_VER_HOST		""
#endif



//获取版本信息
int cp_get_version(cp_version_t *version)
{
	memset(version, 0, sizeof(cp_version_t));

	version->serial = cp_version;
	sprintf(version->version, "%s", CP_VERSION);
	sprintf(version->ver, "%s", CP_VER);
	sprintf(version->name, "%s", CP_VAR);
	sprintf(version->build_date, "%sT%s", __DATE__, __TIME__);
	sprintf(version->host, "%s", CP_VER_HOST);

#ifdef WIN32
	switch (_MSC_VER)
	{
		case 1800:
			sprintf(version->compiler, "%s", "Visual Studio 2013");
			break;
		case 1700:
			sprintf(version->compiler, "%s", "Visual Studio 2012");
			break;
		case 1600:
			sprintf(version->compiler, "%s", "Visual Studio 2010");
			break;
		case 1500:
			sprintf(version->compiler, "%s", "Visual Studio 2008");
			break;
		case 1400:
			sprintf(version->compiler, "%s", "Visual Studio 2005");
			break;
		case 1310:
			sprintf(version->compiler, "%s", "Visual Studio 2003");
			break;
		default:
			sprintf(version->compiler, "unknow compiler[MSC_VER=%d]", _MSC_VER);
			break;
	}
#else
	sprintf(version->compiler, "%s", __VERSION__);
#endif
	return 0;
}

//格式化版本信息
char* cp_get_format_version(char *buf, int len)
{
	cp_version_t					tmp_ver;


	if (!buf || !len) {
		return buf;
	}
	memset(buf, 0, len);
	memset(&tmp_ver, 0, sizeof(tmp_ver));
	cp_get_version(&tmp_ver);
	sprintf(buf, "%s (%d) / %s (%s)",
		tmp_ver.ver, tmp_ver.serial, tmp_ver.compiler, tmp_ver.host);

	return buf;
}

//将版本号从十进制转换为点分十进制表示
char* cp_version_itoa(int version, char *buf, int len)
{
	if (!buf || !len) {
		return buf;
	}
	memset(buf, 0, len);

	sprintf(buf, "V%d.%d.%d", (version / 10000), ((version % 10000) / 100), (version % 100));

	return buf;
}