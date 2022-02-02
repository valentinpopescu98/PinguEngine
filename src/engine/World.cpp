#include "World.h"

//Texture texture;

void World::Init()
{
	// Data for a plane
	std::vector<VertexStruct> planeVertices =
	{
		//	             COORDS		                   NORMALS                 TEXT COORDS                  COLORS
		{ glm::vec3(-0.5f, 0.0f, -0.5f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f) }, // front left
		{ glm::vec3(0.5f, 0.0f, -0.5f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 0.0f) }, // front right
		{ glm::vec3(0.5f, 0.0f,  0.5f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(1.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f) }, // back right
		{ glm::vec3(-0.5f, 0.0f,  0.5f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f) }  // back left
	};

	std::vector<GLuint> planeIndices
	{
		0, 1, 2,		// bottom right triangle
		3, 2, 0			// top left triangle
	};

	// Data for a pyramid
	std::vector<VertexStruct> pyramidVertices
	{
		//	             COORDS		                    NORMALS                  TEXT COORDS                  COLORS
		// Base face
		{ glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.0f, -1.0f,  0.0f), glm::vec2(0.0f, 1.0f), glm::vec3(1.0f, 0.0f, 0.0f) }, // back left
		{ glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(0.0f, -1.0f,  0.0f), glm::vec2(1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 0.0f) }, // back right
		{ glm::vec3(0.5f, -0.5f,  0.5f), glm::vec3(0.0f, -1.0f,  0.0f), glm::vec2(1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f) }, // front right
		{ glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec3(0.0f, -1.0f,  0.0f), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f) }, // front left

		// Front face	    
		{ glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec3(0.0f,  1.0f,  1.0f), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f) }, // front left
		{ glm::vec3(0.5f, -0.5f,  0.5f), glm::vec3(0.0f,  1.0f,  1.0f), glm::vec2(1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f) }, // front right
		{ glm::vec3(0.0f,  0.5f,  0.0f), glm::vec3(0.0f,  1.0f,  1.0f), glm::vec2(0.5f, 1.0f), glm::vec3(0.0f, 1.0f, 1.0f) }, // top

		// Right face	    
		{ glm::vec3(0.5f, -0.5f,  0.5f), glm::vec3(1.0f,  1.0f,  0.0f), glm::vec2(1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f) }, // front right
		{ glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(1.0f,  1.0f,  0.0f), glm::vec2(0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 0.0f) }, // back right
		{ glm::vec3(0.0f,  0.5f,  0.0f), glm::vec3(1.0f,  1.0f,  0.0f), glm::vec2(0.5f, 1.0f), glm::vec3(0.0f, 1.0f, 1.0f) }, // top

		// Back face	    
		{ glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(0.0f,  1.0f, -1.0f), glm::vec2(0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 0.0f) }, // back right
		{ glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.0f,  1.0f, -1.0f), glm::vec2(1.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f) }, // back left
		{ glm::vec3(0.0f,  0.5f,  0.0f), glm::vec3(0.0f,  1.0f, -1.0f), glm::vec2(0.5f, 1.0f), glm::vec3(0.0f, 1.0f, 1.0f) }, // top

		// Left face	    
		{ glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(-1.0f,  1.0f,  0.0f), glm::vec2(1.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f) }, // back left
		{ glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec3(-1.0f,  1.0f,  0.0f), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f) }, // front left
		{ glm::vec3(0.0f,  0.5f,  0.0f), glm::vec3(-1.0f,  1.0f,  0.0f), glm::vec2(0.5f, 1.0f), glm::vec3(0.0f, 1.0f, 1.0f) }  // top
	};

	std::vector<GLuint> pyramidIndices
	{
		0, 1, 2,		// bottom right base triangle
		2, 3, 0,		// top left base triangle
		4, 5, 6,		// front face triangle
		7, 8, 9,		// right face triangle
		10, 11, 12,		// back face triangle
		13, 14, 15		// left face triangle
	};

	// Data for a cube
	std::vector<VertexStruct> cubeVertices
	{
		//	             COORDS		                    NORMALS                  TEXT COORDS                  COLORS
		// Bottom face
		{ glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.0f, -1.0f,  0.0f), glm::vec2(0.0f, 1.0f), glm::vec3(1.0f, 0.0f, 0.0f) }, // back bottom left
		{ glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(0.0f, -1.0f,  0.0f), glm::vec2(1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 0.0f) }, // back bottom right
		{ glm::vec3(0.5f, -0.5f,  0.5f), glm::vec3(0.0f, -1.0f,  0.0f), glm::vec2(1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f) }, // front bottom right
		{ glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec3(0.0f, -1.0f,  0.0f), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f) }, // front bottom left

		// Top face
		{ glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec3(0.0f,  1.0f,  0.0f), glm::vec2(0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f) }, // front top left
		{ glm::vec3(0.5f,  0.5f,  0.5f), glm::vec3(0.0f,  1.0f,  0.0f), glm::vec2(1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f) }, // front top right
		{ glm::vec3(0.5f,  0.5f, -0.5f), glm::vec3(0.0f,  1.0f,  0.0f), glm::vec2(1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 0.0f) }, // back top right
		{ glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec3(0.0f,  1.0f,  0.0f), glm::vec2(0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f) }, // back top left

		// Front face
		{ glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec3(0.0f,  0.0f,  1.0f), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f) }, // front bottom left
		{ glm::vec3(0.5f, -0.5f,  0.5f), glm::vec3(0.0f,  0.0f,  1.0f), glm::vec2(1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f) }, // front bottom right
		{ glm::vec3(0.5f,  0.5f,  0.5f), glm::vec3(0.0f,  0.0f,  1.0f), glm::vec2(1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f) }, // front top right
		{ glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec3(0.0f,  0.0f,  1.0f), glm::vec2(0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f) }, // front top left

		// Right face
		{ glm::vec3(0.5f, -0.5f,  0.5f), glm::vec3(1.0f,  0.0f,  0.0f), glm::vec2(1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f) }, // front bottom right
		{ glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(1.0f,  0.0f,  0.0f), glm::vec2(0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 0.0f) }, // back bottom right
		{ glm::vec3(0.5f,  0.5f, -0.5f), glm::vec3(1.0f,  0.0f,  0.0f), glm::vec2(0.0f, 1.0f), glm::vec3(1.0f, 1.0f, 0.0f) }, // back top right
		{ glm::vec3(0.5f,  0.5f,  0.5f), glm::vec3(1.0f,  0.0f,  0.0f), glm::vec2(1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f) }, // front top right

		// Back face
		{ glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(0.0f,  0.0f, -1.0f), glm::vec2(0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 0.0f) }, // back bottom right
		{ glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.0f,  0.0f, -1.0f), glm::vec2(1.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f) }, // back bottom left
		{ glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec3(0.0f,  0.0f, -1.0f), glm::vec2(1.0f, 1.0f), glm::vec3(1.0f, 0.0f, 0.0f) }, // back top left
		{ glm::vec3(0.5f,  0.5f, -0.5f), glm::vec3(0.0f,  0.0f, -1.0f), glm::vec2(0.0f, 1.0f), glm::vec3(1.0f, 1.0f, 0.0f) }, // back top right

		// Left face
		{ glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(-1.0f,  0.0f,  0.0f), glm::vec2(1.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f) }, // back bottom left
		{ glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec3(-1.0f,  0.0f,  0.0f), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f) }, // front bottom left
		{ glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec3(-1.0f,  0.0f,  0.0f), glm::vec2(0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f) }, // front top left
		{ glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec3(-1.0f,  0.0f,  0.0f), glm::vec2(1.0f, 1.0f), glm::vec3(1.0f, 0.0f, 0.0f) }  // back top left
	};

	std::vector<GLuint> cubeIndices
	{
		0, 1, 2,		// bottom right, front face triangle
		2, 3, 0,		// top left, front face triangle

		4, 5, 6,		// bottom right, back face triangle
		6, 7, 4,		// top left, back face triangle

		8, 9, 10,		// bottom right, left face triangle
		10, 11, 8,		// top left, left face triangle

		12, 13, 14,		// bottom right, right face triangle
		14, 15, 12,		// top left, right face triangle

		16, 17, 18,		// bottom right, top face triangle
		18, 19, 16,		// top left, top face triangle

		20, 21, 22,		// bottom right, bottom face triangle
		22, 23, 20		// top right, bottom face triangle
	};

	// Supports: texture_diffuse, texture_specular, texture_normal, texture_height
	std::vector<TextureStruct> defaultTexture
	{
		{ "texture_diffuse", "resources/textures/default.png" }
	};

	std::vector<TextureStruct> noiseTexture
	{
		{ "texture_diffuse", "resources/textures/noise.png" }
	};

	// Create shaders
	lightShader.Create("src/shaders/light.vert", "src/shaders/light.frag");
	objectShader.Create("src/shaders/object.vert", "src/shaders/object.frag");

	// Initialize camera
	camera.Init(Engine::resX, Engine::resY, glm::vec3(0.0f, 0.0f, 0.0f), 70.0f, 0.1f, 20.0f);

	// Create meshes
	Mesh origin;
	origin.position = glm::vec3(0.0f, 0.0f, 0.0f);
	origin.rotation = glm::vec3(0.0f, 0.0f, 0.0f);
	origin.scale = glm::vec3(1.0f, 1.0f, 1.0f);

	meshObjects.push_back(Mesh());
	meshObjects[0].CreateBuffers(cubeVertices, cubeIndices, defaultTexture,
		origin, glm::vec3(0.0f, 0.0f, -2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	meshObjects.push_back(Mesh());
	meshObjects[1].CreateBuffers(pyramidVertices, pyramidIndices, noiseTexture,
		meshObjects[0], glm::vec3(2.0f, 0.0f, -2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 1.0f, 1.0f));

	// Create mesh textures
	meshObjects[0].CreateTextures(objectShader.id, 0, GL_TEXTURE_2D, GL_LINEAR, GL_REPEAT);
	meshObjects[1].CreateTextures(objectShader.id, meshObjects[0].textures.size(), GL_TEXTURE_2D, GL_LINEAR, GL_REPEAT);

	// Create models
	parser.Init("src/xml/scene.xml", meshObjects[0].textures.size() + meshObjects[1].textures.size()); // Parse XML
	parser.CreateModels(parser.scene); // Initialize models from the XML

	// Enable backface culling
	Culler::BackFaceCulling();
}

void World::End()
{
	// Delete buffers
	meshObjects[0].DeleteBuffers();
	meshObjects[1].DeleteBuffers();

	for (GLuint i = 0; i < parser.modelLights.size(); i++)
	{
		parser.modelLights[i].DeleteBuffers();
	}
	for (GLuint i = 0; i < parser.modelLights.size(); i++)
	{
		parser.modelObjects[i].DeleteBuffers();
	}

	// Delete textures
	meshObjects[0].DeleteTextures();
	meshObjects[1].DeleteTextures();

	for (GLuint i = 0; i < parser.modelLights.size(); i++)
	{
		parser.modelLights[i].DeleteTextures();
	}
	for (GLuint i = 0; i < parser.modelLights.size(); i++)
	{
		parser.modelObjects[i].DeleteTextures();
	}

	// Delete shaders
	lightShader.Delete();
	objectShader.Delete();
}

void World::BeforeDrawing()
{
	glfwPollEvents(); // Take care of GLFW events
	glClearColor(0.05f, 0.1f, 0.2f, 1.0f); // Wipe drawing from previous frame with a black color
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color buffer and depth buffer
}

void World::Draw(GLFWwindow* window)
{
	// Treat camera inputs (WASD - move on X/Z axis, LEFT CTRL/SPACE - move on Y axis, SHIFT - speed modifier)
	camera.TreatInputs(window, Engine::deltaTime);
	camera.UpdateMatrices(view, projection); // Compute view and projection matrices

	// RENDER LIGHT SOURCES SECTION
	lightShader.Use(); // Use light source's shaders
	lightShader.InitMatrices(view, projection); // Send view and projection matrix to light source's shaders

	parser.DrawModelLights(lightShader.id, camera); // Draw all lights of type MODEL from the XML

	// RENDER NORMAL OBJECTS SECTION
	objectShader.Use(); // Use object's shader
	// Send material data to object's shaders
	objectShader.InitMaterial(parser.modelLights[0].position, parser.modelLights[0].color, camera.position,
		glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(1.0f, 0.5f, 0.31f), glm::vec3(0.5f, 0.5f, 0.5f), 32.0f);
	objectShader.InitMatrices(view, projection); // Send view and projection matrix to object's shaders

	if (Culler::MeshInFrustum(camera, meshObjects[0]))
	{
		meshObjects[0].Draw(objectShader.id);
	}
	if (Culler::MeshInFrustum(camera, meshObjects[1]))
	{
		meshObjects[1].Draw(objectShader.id);
	}

	parser.DrawModelObjects(objectShader.id, camera); // Draw all objects of type MODEL from the XML
}

void World::AfterDrawing(GLFWwindow* window)
{
	glfwSwapBuffers(window); // Swap front and back buffer
	glFlush(); // Empties buffers - improves performance
}

void World::Run(GLFWwindow* window)
{
	glEnable(GL_DEPTH_TEST); // Enable depth

	// Loop until window is closed
	while (!glfwWindowShouldClose(window))
	{
		//if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
		//{
		//	ReloadModels(); // LAGGY AF
		//}

		BeforeDrawing();
		Draw(window);
		AfterDrawing(window);

		Engine::SetTimeValues(); // Compute deltaTime
		Engine::CheckErrorCodes(); // Check for GLAD error codes
	}
}

void World::ReloadModels()
{
	parser.Init("src/xml/scene.xml", meshObjects[0].textures.size() + meshObjects[1].textures.size()); // Parse XML
	parser.CreateModels(parser.scene); // Initialize models from the XML
}