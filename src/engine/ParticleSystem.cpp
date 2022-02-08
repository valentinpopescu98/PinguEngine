#include "ParticleSystem.h"

void ParticleSystem::Init(GLuint particleCount)
{
	particles.resize(particleCount);
	particleIndex = particleCount - 1;

	origin.position = glm::vec3(0.0f, 0.0f, 0.0f);
	origin.rotation = glm::vec3(0.0f, 0.0f, 0.0f);
	origin.scale = glm::vec3(1.0f, 1.0f, 1.0f);
}

void ParticleSystem::CreateParticle(ImVec4 position, ImVec4 colorBirth, ImVec4 colorDeath, ImVec4 speed,
	 float scaleBirth, float scaleDeath, float lifeTime)
{
	Particle& particle = particles[particleIndex];

	particle.active = true;
	particle.position = glm::vec3(position.x, position.y, position.z);

	particle.rotation = glm::vec3(
		Utils::GetRandomFloat(0.0f, 2.0f * glm::pi<float>()),
		Utils::GetRandomFloat(0.0f, 2.0f * glm::pi<float>()),
		Utils::GetRandomFloat(0.0f, 2.0f * glm::pi<float>()));

	particle.colorBirth = glm::vec4(colorBirth.x, colorBirth.y, colorBirth.z, colorBirth.w);
	particle.colorDeath = glm::vec4(colorDeath.x, colorDeath.y, colorDeath.z, colorDeath.w);

	particle.speed = glm::vec3(speed.x, speed.y, speed.z) + Utils::GetRandomFloat(-0.5f, 0.5f);

	particle.scaleBirth = scaleBirth + Utils::GetRandomFloat(-0.5f, 0.5f);
	particle.scaleDeath = scaleDeath;

	particle.lifeTime = lifeTime;
	particle.lifeRemaining = lifeTime;

	glm::vec3 newRot = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 newScale = glm::vec3(1.0f, 1.0f, 1.0f);

	particleIndex = --particleIndex % particles.size();
}

void ParticleSystem::UpdateParticleData(double deltaTime)
{
	for (Particle& particle : particles)
	{
		if (!particle.active)
		{
			continue;
		}

		if (particle.lifeRemaining <= 0.0f)
		{
			particle.active = false;
			continue;
		}

		particle.lifeRemaining -= deltaTime;
		particle.position += particle.speed * (float)deltaTime;

		float rotDegrees = 0.01f * deltaTime;
		particle.rotation += glm::vec3(rotDegrees, rotDegrees, rotDegrees);
	}
}

void ParticleSystem::DrawParticle(GLuint shaderID, Mesh& parent)
{
	Mesh particleMesh;
	particleMesh.CreateBuffers(Utils::quadVertices, Utils::quadIndices);

	for (Particle& particle : particles)
	{
		if (!particle.active)
		{
			continue;
		}

		// Fade away particles
		float life = particle.lifeRemaining / particle.lifeTime;
		glm::vec4 color = glm::mix(particle.colorDeath, particle.colorBirth, life);
		color.a = color.a * life;

		float scale = glm::mix(particle.scaleDeath, particle.scaleBirth, life);

		particleMesh.Draw(shaderID, parent, particle.position, particle.rotation, glm::vec3(scale, scale, scale), color);
	}
}