#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <cstdlib>
#include <ctime>
#include <vector>

#include "Utils.h"
#include "Mesh.h"
#include "GuiDrawer.h"

class ParticleSystem
{
	public:
		void Init(GLuint particleCount);
		//void End();

		void CreateParticle(ImVec4 position, ImVec4 colorBirth, ImVec4 colorDeath, ImVec4 speed,
			float scaleBirth, float scaleDeath, float lifeTime);
		void UpdateParticleData(double deltaTime);
		void DrawParticle(GLuint shaderID, Mesh& parent);
	private:
		struct Particle
		{
			glm::vec3 position;
			glm::vec3 rotation;
			glm::vec4 colorBirth, colorDeath;
			glm::vec3 speed;

			float scaleBirth, scaleDeath;
			float lifeTime, lifeRemaining;
			bool active = false;
		};

		std::vector<Particle> particles;
		GLuint particleIndex;

		GLuint m_QuadVA = 0;
		Mesh origin;
};