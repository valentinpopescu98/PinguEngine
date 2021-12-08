#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "pugixml/pugiconfig.hpp"
#include "pugixml/pugixml.hpp"
#include <vector>
#include <iostream>

#include "Model.h"

class XMLParser
{
	public:
		void ParseScene(const char* path);
		void CreateModels(pugi::xml_node node);
		void DrawModelLights(GLuint shaderID);
		void DrawModelObjects(GLuint shaderID);

		pugi::xml_node scene;
		std::vector<Model> modelLights, modelObjects;
	private:
		pugi::xml_document doc;
		Model parent;
};