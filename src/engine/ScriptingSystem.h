#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <lua/lua.hpp>
#include <iostream>

#include "Utils.h"

class ScriptingSystem
{
	public:
		static void CallFunctionByName(const char* path, const char* functionName);
};