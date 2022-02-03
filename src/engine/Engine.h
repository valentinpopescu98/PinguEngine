#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <iostream>

class Engine
{
	public:
		static int Init();
		static void End(GLFWwindow* window);
		static GLFWwindow* CreateWindow(int resX, int resY);
		static void SetTimeValues();
		static void EnableVsync(bool isEnabled);
		static void CheckErrorCodes();

		static GLint resX, resY;
		static float aspectRatio;

		static double previousTime;
		static double elapsedTime;
		static double deltaTime;
	private:
		static int CheckFailCreateWindow(GLFWwindow* window);
		static int LoadGlad();
};