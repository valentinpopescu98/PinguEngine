#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Camera.h"

struct Plan
{
    glm::vec3 normal = { 0.0f, 1.0f, 0.0f }; // Unit vector
    float distance = 0.0f; // Distance from origin to the nearest point in the plan
};

struct Frustum
{
    Plan topFace;
    Plan bottomFace;

    Plan leftFace;
    Plan rightFace;

    Plan nearFace;
    Plan farFace;
};

class Culler
{
	public:
		static void FrontFaceCulling();
		static void BackFaceCulling();
		static void FrustumCulling();
    private:
        Frustum CreateFrustumFromCamera(const Camera& cam, float aspect, float fovY, float zNear, float zFar);
};