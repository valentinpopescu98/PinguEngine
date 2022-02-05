#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <vector>

#include "Mesh.h"
#include "Model.h"

class CollisionManager
{
	public:
		static void Uncollide(std::vector<Mesh>& meshObjects, std::vector<Model>& modelObjects);
	private:
		static void UncollideMeshToMesh(std::vector<Mesh>& meshObjects);
		static void UncollideModelToModel(std::vector<Model>& modelObjects);
		static void UncollideMeshToModel(std::vector<Mesh>& meshObjects, std::vector<Model>& modelObjects);
		static void UncollideModelToMesh(std::vector<Model>& modelObjects, std::vector<Mesh>& meshObjects);
};