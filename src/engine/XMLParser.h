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

class XmlParser
{
	public:
		void Init(const char* path, GLuint firstTextureID);
		void CreateModels(pugi::xml_node node, std::vector<Model>& modelLights, std::vector<Model>& modelObjects);

		pugi::xml_node scene;
	private:
		pugi::xml_document doc;
		GLuint firstTextureID;
		Model parent;
};