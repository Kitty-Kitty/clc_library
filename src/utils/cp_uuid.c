/**************************************************************************

* Copyright: novigo

* Author: tianhuiming@novigo.com.cn

* Date£º2016-4-23
        
* Description:

**************************************************************************/


#ifdef WIN32
#include <objbase.h>
#else
#include <inttypes.h>
#include <sys/types.h>
#include <uuid/uuid.h>
#endif


#define		CP_UUID_BUFFER_LEN				32



static const char *fmt_lower = 
"%08x%04x%04x%02x%02x%02x%02x%02x%02x%02x%02x";



int make_uuid_32(char *uuid_buf, int uuid_len)
{
	if (uuid_len < CP_UUID_BUFFER_LEN) {
		return -1;
	}

#ifdef WIN32
	GUID guid;
	CoCreateGuid(&guid);
	_snprintf_s(
		uuid_buf,
		uuid_len,
		uuid_len - 1,
		"%08x%04x%04x%02x%02x%02x%02x%02x%02x%02x%02x",
		guid.Data1, guid.Data2, guid.Data3,
		guid.Data4[0], guid.Data4[1],
		guid.Data4[2], guid.Data4[3],
		guid.Data4[4], guid.Data4[5],
		guid.Data4[6], guid.Data4[7]);
#else

	uuid_t			uuid_out;

	uuid_generate(uuid_out);
	uuid_unparse_x(uuid_out, uuid_buf, fmt_lower);
#endif

	return 0;
}

