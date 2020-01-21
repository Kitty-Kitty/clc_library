/**************************************************************************

* Copyright: novigo

* Author: tianhuiming@novigo.com.cn

* Date：2016-4-27
        
* Description:

**************************************************************************/

#include <string.h>


#include "cp_utils.h"
#include "cp_env.h"


cp_char_t *cp_get_set_null_env(const cp_char_t *key, const cp_char_t *def) {
	cp_char_t	*env_str = CP_NULL;

	env_str = getenv(key);
	if (!env_str){
		printf("get env [%s] failed! used default value[%s = %s]\n", key, key, def);
		env_str = (cp_char_t*)def;
		if (cp_setenv(key, env_str, 1)) {
			printf("update env [%s = %s] failed!\n", key, env_str);
		} else {
			printf("update env [%s = %s] success!\n", key, env_str);
		}
	}

	return env_str;
}

cp_bool_t parse_string_color_value(cp_uchar_t *dest_p, cp_int32_t d_len, cp_uchar_t *str)
{
	cp_int32_t					n = 3;
	cp_int32_t					i = 0;
	cp_uchar_t					*p;



	if (strlen(str) < 6 || d_len < 3) {
		return cp_false;
	}

	p = str;
	if (strlen(str) >= 8) {
		n = 4;
	}

	for (i = 0; i < n; ++i) {
		dest_p[i] = cp_htoi(&p[i * 2], 2);
	}

	return cp_true;
}

/*将大写字母转换成小写字母*/
int cp_tolower(int c)
{
	if (c >= 'A' && c <= 'Z') {
		return c + 'a' - 'A';
	} else {
		return c;
	}
}


//将十六进制的字符串转换成整数
int cp_htoi(char *s, int len)
{
	int							i;
	int							n = 0;


	if (s[0] == '0' && (s[1] == 'x' || s[1] == 'X')) {
		i = 2;
	} else {
		i = 0;
	}

	for (; ((s[i] >= '0' && s[i] <= '9') || 
		(s[i] >= 'a' && s[i] <= 'z') || 
		(s[i] >= 'A' && s[i] <= 'Z')) && i < len; ++i) {
		if (cp_tolower(s[i]) > '9')	{
			n = 16 * n + (10 + cp_tolower(s[i]) - 'a');
		} else {
			n = 16 * n + (cp_tolower(s[i]) - '0');
		}
	}

	return n;
}



