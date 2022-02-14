#include "ScriptingSystem.h"

void ScriptingSystem::CallFunctionByName(const char* path, const char* functionName)
{
	lua_State* state = luaL_newstate();

	std::string code = Utils::GetFileContents(path);
	
	luaL_dostring(state, code.c_str());
	lua_getglobal(state, functionName);

	if (lua_isfunction(state, -1))
	{
		// If you need to pass lua args, use next line and change lua_pcall second arg to lua method argc
		//lua_pushnumber(state, 9);

		/* lua_pcall params:
		*  pointer to lua state,
		*  number of parameters,
		*  number of variables returned,
		*  stack index to error handler (use no error handler if 0)
		*/
		lua_pcall(state, 0, 1, 0);
		lua_Number x = lua_tonumber(state, -1);
		std::cout << (int)x << std::endl;
	}

	lua_close(state);
}