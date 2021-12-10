#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "pugixml/pugiconfig.hpp"
#include "pugixml/pugixml.hpp"
#include <vector>
#include <iostream>

#include "Model.h"
#include "Culler.h"

class XMLParser
{
	public:
		void Init(const char* path, GLuint firstTextureID);
		void CreateModels(pugi::xml_node node);
		void DrawModelLights(GLuint shaderID, Camera& camera);
		void DrawModelObjects(GLuint shaderID, Camera& camera);

		pugi::xml_node scene;
		std::vector<Model> modelLights, modelObjects;
	private:
		pugi::xml_document doc;
		GLuint firstTextureID;
		Model parent;
};