/**************************************************************************

* Copyright: novigo

* Author: tianhuiming@novigo.com.cn

* Date£º2016-4-27
        
* Description:

**************************************************************************/


#ifndef	_CP_UTILS_INCLUDE_H_
#define _CP_UTILS_INCLUDE_H_





#include "cp_typedef.h"



cp_char_t *cp_get_set_null_env(const cp_char_t *key, const cp_char_t *def);

cp_bool_t parse_string_color_value(cp_uchar_t *dest_p, cp_int32_t d_len, cp_uchar_t *str);

int cp_tolower(int c);
int cp_htoi(char *s, int len);



#endif