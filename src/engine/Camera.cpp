#include "Camera.h"

void Camera::Init(GLuint width, GLuint height, glm::vec3 position, float fovY, float nearPlane, float farPlane)
{
	this->width = width;
	this->height = height;
	this->position = position;

	this->fovY = fovY;
	this->nearPlane = nearPlane;
	this->farPlane = farPlane;
}

void Camera::TreatInputs(GLFWwindow* window, double deltaTime)
{
	right = glm::normalize(glm::cross(forward, up));

	// When right click is pressed
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN); // Hide cursor

		if (firstClick)
		{
			glfwSetCursorPos(window, width / 2, height / 2); // Force cursor to the middle of the window
			firstClick = false;
		}

		TreatMouseRotation(window, deltaTime);
		TreatKeyboardInputs(window, deltaTime);
	}
	else
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL); // Show cursor again
		firstClick = true;
	}
}

void Camera::UpdateMatrices(glm::mat4& view, glm::mat4& projection)
{
	view = glm::mat4(1.0f); // Create view matrix as identity matrix
	projection = glm::mat4(1.0f); // Create projection matrix as identity matrix

	// Compute view matrix based on camera rotation
	view = glm::lookAt(position, position + forward, up);
	// Compute the projection matrix based on perspective
	projection = glm::perspective(glm::radians(fovY), Engine::aspectRatio, nearPlane, farPlane);
}

void Camera::TreatMouseRotation(GLFWwindow* window, double deltaTime)
{
	double mouseX, mouseY;
	glfwGetCursorPos(window, &mouseX, &mouseY); // Get cursor position

	float rotX = sensitivity * (float)deltaTime * (float)(mouseY - height / 2) / height; // Calculate new pitch angle in radians (rotation around OX axis)
	float rotY = sensitivity * (float)deltaTime * (float)(mouseX - width / 2) / width; // Calculate new yaw angle in radians (rotation around OY axis)

	// Calculate where the new orientation would be based on the pitch and yaw angles
	glm::vec3 newForward = glm::rotate(forward, glm::radians(-rotX), right);

	// Check if pitch (rotation around X axis) is in the [5, 175] degres interval
	if (abs(glm::angle(newForward, up) - glm::radians(90.0f)) <= glm::radians(85.0f))
	{
		forward = newForward; // Use the new rotation for the pitch
	}

	forward = glm::rotate(forward, glm::radians(-rotY), up); // Use the new rotation for the yaw

	glfwSetCursorPos(window, width / 2, height / 2); // Force cursor to the middle of the window
}

void Camera::TreatKeyboardInputs(GLFWwindow* window, double deltaTime)
{
	// Treat W as forward move
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		position += speed * forward * (float)deltaTime;
	}
	// Treat A as left move
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		position += speed * -right * (float)deltaTime;
	}
	// Treat S as backwards move
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		position += speed * -forward * (float)deltaTime;
	}
	// Treat D as right move
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		position += speed * right * (float)deltaTime;
	}
	// Treat SPACE as upwards move
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
	{
		position += speed * up * (float)deltaTime;
	}
	// Treat LEFT CTRL as downwards move
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
	{
		position += speed * -up * (float)deltaTime;
	}

	// When LEFT SHIFT is pressed increase move speed
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		speed = 10.0f;
	}
	// Treat LEFT SHIFT is released decrease move speed
	else if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
	{
		speed = 2.5f;
	}
}