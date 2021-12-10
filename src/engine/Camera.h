#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

#include "Engine.h"
#include "Shader.h"

class Camera
{
public:
	void Init(GLuint width, GLuint height, glm::vec3 position, float FOVdeg, float nearPlane, float farPlane);
	void UpdateMatrices(glm::mat4& view, glm::mat4& projection);
	void TreatInputs(GLFWwindow* window, double deltaTime);

	glm::vec3 position;
	glm::vec3 orientation = glm::vec3(0.0f, 0.0f, -1.0f); // Variable for the forward vector
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f); // Variable for the up vector
	glm::vec3 right = glm::vec3(1.0f, 0.0f, 0.0f); // Variable for the right vector
	float FOVdeg;
	float nearPlane, farPlane;

	// UNIFORMS
	GLuint viewLoc, projectionLoc;
private:
	void TreatMouseRotation(GLFWwindow* window, double deltaTime);
	void TreatKeyboardInputs(GLFWwindow* window, double deltaTime);

	bool firstClick = true; // Variable for moving cursor to the middle of the cursor only one time in the main loop
	unsigned int width, height;
	float speed = 2.5f; // Default speed with SHIFT unpressed
	float sensitivity = 5000.0f; // Default sensitivity
};