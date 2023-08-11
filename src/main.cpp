#include <iostream>
#include "engine/Engine.h"
#include "engine/World.h"

int main() 
{
	Engine::Init(); // Initialize GLFW
	// Create window of given resolution and choose if using fullscreen
	GLFWwindow* window = Engine::CreateWindow(800, 600, false);
	Engine::EnableVsync(true); // Enable vertical synchronization

	World world; // Create world object
	world.Init(window); // Create prerequisites
	world.Run(window); // Run main loop
	world.End(); // Terminate prerequisites

	Engine::End(window); // Destroy window and terminate GLFW
	return 0;
}