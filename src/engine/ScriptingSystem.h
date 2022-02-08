#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <lua/lua.h>
#include <lua/lualib.h>
#include <lua/lauxlib.h>
#include <iostream>

#include "Utils.h"

class ScriptingSystem
{
	public:
		void CallFunctionByName(const char* path);
	private:
		lua_State* state;
};