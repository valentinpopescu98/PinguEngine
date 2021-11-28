#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <iostream>

class Engine
{
public:
	static void Init();
	static void End(GLFWwindow* window);
	static GLFWwindow* CreateWindow(unsigned int resX, unsigned int resY);

	static unsigned int resX, resY;
	static float aspectRation;

private:
	static int CheckFailCreateWindow(GLFWwindow* window);
	static int LoadGlad();
};