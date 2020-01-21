#include <stdio.h>   
#include <lua.h>  
#include <lualib.h>  
#include <lauxlib.h>  


lua_State* L;


int main(int argc, char *argv[]){
	int a = 110;
	int b = 120;
	int ret_int = 0;


	L = luaL_newstate();
	luaL_openlibs(L);
	//   luaL_dofile(L, "test.lua");
#if defined(WIN32)
	ret_int = luaL_loadfile(L, "H:\\project_work\\css_player_fix_org\\tests\\win32\\test_lua\\lua\\test.lua");
#else
	ret_int = luaL_loadfile(L, "./test.lua");
#endif
	if (ret_int) {
		printf("error %d \n", ret_int);
		return 1;
	}
	int iError = lua_pcall(L, 0, 0, 0);
	if (iError)	{
		printf("error %d \n", iError);
		lua_close(L);
		return 1;
	}

	lua_getglobal(L, "sum");
	lua_pushinteger(L, a);
	lua_pushinteger(L, b);
	int ret = lua_pcall(L, 2, 1, 0);
	if (ret != 0) {
		printf("error\n");
		return 1;
	}
	printf("sum:%d + %d = %ld\n", a, b, lua_tointeger(L, -1));
	lua_pop(L, 1);
	/* Çå³ýLua */
	lua_close(L);
	return 0;
}
