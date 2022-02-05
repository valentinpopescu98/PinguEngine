#include <iostream>
#include "engine/Engine.h"
#include "engine/World.h"

int main() 
{
	Engine::Init(); // Initialize GLFW
	GLFWwindow* window = Engine::CreateWindow(1024, 768); // Create window of given resolution
	Engine::EnableVsync(true); // Enable vertical synchronization

	World world; // Create world object
	world.Init(window); // Create prerequisites
	world.Run(window); // Run main loop
	world.End(); // Terminate prerequisites

	Engine::End(window); // Destroy window and terminate GLFW
	return 0;
}