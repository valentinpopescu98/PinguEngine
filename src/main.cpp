#include <iostream>
#include "engine/Engine.h"
#include "engine/World.h"

int main() 
{
	Engine::Init(); // Initialize GLFW

	GLFWwindow* window = Engine::CreateWindow(800, 800); // Create window of given resolution

	World world; // Create world object
	world.Init(); // Create prerequisites
	world.Run(window); // Run main loop
	world.End(); // Terminate prerequisites

	Engine::End(window); // Destroy window and terminate GLFW
	return 0;
}