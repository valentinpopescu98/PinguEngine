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
		void Init(unsigned int width, unsigned int height, glm::vec3 position);
		void UpdateMatrices(float FOVdeg, float nearPlane, float farPlane, glm::mat4& view, glm::mat4& projection);
		void TreatInputs(GLFWwindow* window, double deltaTime);

		// UNIFORMS
		GLuint viewLoc, projectionLoc;
	private:
		void TreatMouseRotation(GLFWwindow* window, double deltaTime);
		void TreatKeyboardInputs(GLFWwindow* window, double deltaTime);

		glm::vec3 position;
		glm::vec3 orientation = glm::vec3(0.0f, 0.0f, -1.0f);
		glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

		bool firstClick = true;
		unsigned int width, height;
		float speed = 2.5f;
		float sensitivity = 100.0f;
};