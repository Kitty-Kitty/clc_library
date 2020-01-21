



#include "cp_env.h"


#ifdef WIN32
int cp_setenv(const char *name, const char * value, int overwrite) {
	char				tmp_buf[256] = { 0, };

	sprintf_s(tmp_buf, 256, "%s=%s", name, value);
	return _putenv(tmp_buf);
}

#endif

