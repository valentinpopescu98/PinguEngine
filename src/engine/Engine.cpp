#include "Engine.h"

unsigned int Engine::resX, Engine::resY;
float Engine::aspectRation;

double Engine::previousTime = 0.0;
double Engine::elapsedTime = 0.0;
double Engine::deltaTime = 0.0;

void Engine::Init() 
{
	glfwInit(); // Initialize GLFW

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // GLFW version 3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // GLFW version 3.3
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // GLFW uses CORE profile
}

void Engine::End(GLFWwindow* window) 
{
	glfwDestroyWindow(window);
	glfwTerminate();
}

int Engine::CheckFailCreateWindow(GLFWwindow* window) 
{
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window." << std::endl;
		glfwTerminate();
		return -1;
	}
}

int Engine::LoadGlad()
{
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
}

GLFWwindow* Engine::CreateWindow(unsigned int resX, unsigned int resY) 
{
	GLFWwindow* window = glfwCreateWindow(resX, resY, "Pingu Engine", NULL, NULL); // Create window

	CheckFailCreateWindow(window);
	glfwMakeContextCurrent(window); // Make window's context current

	LoadGlad();
	glViewport(0, 0, resX, resY); // Set viewport between bottom left and top right corner of the window

	// Set resolution variables for further use
	Engine::resX = resX;
	Engine::resY = resY;
	Engine::aspectRation = (float)resX / resY; // Set aspect ratio variable for further use
	
	return window;
}

void Engine::SetTimeValues()
{
	elapsedTime = glfwGetTime();
	deltaTime = elapsedTime - previousTime;
	previousTime = elapsedTime;
}

void Engine::CheckErrorCodes()
{
	GLenum errCode;

	if ((errCode = glGetError()) != GL_NO_ERROR)
	{
		std::cout << errCode << std::endl;
	}
}