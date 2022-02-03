#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

class GuiDrawer
{
	public:
		static void Init(GLFWwindow* window);
		static void End();
		static void Draw();
	private:
		// Our state
		static bool show_demo_window;
		static bool show_another_window;
		static ImVec4 clear_color;
};