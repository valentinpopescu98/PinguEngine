#include "World.h"

Texture texture;

void World::Init()
{
	// Data for a plane
	std::vector<VertexStruct> planeVertices =
	{
		//	             COORDS		                   NORMALS                 TEXT COORDS                  COLORS
		{ glm::vec3(-0.5f, 0.0f, -0.5f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f) }, // front left
		{ glm::vec3(-0.5f, 0.0f,  0.5f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f) }, // back left
		{ glm::vec3( 0.5f, 0.0f,  0.5f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(1.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f) }, // back right
		{ glm::vec3( 0.5f, 0.0f, -0.5f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 0.0f) }  // front right
	};

	std::vector<GLuint> planeIndices
	{
		0, 1, 2,		// top left triangle
		0, 3, 2			// bottom right triangle
	};

	// Data for a pyramid
	std::vector<VertexStruct> pyramidVertices
	{
		//	             COORDS		                    NORMALS                  TEXT COORDS                  COLORS
		// Base face
		{ glm::vec3(-0.5f, 0.0f, -0.5f), glm::vec3( 0.0f, -1.0f,  0.0f), glm::vec2(0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f) }, // front left
		{ glm::vec3(-0.5f, 0.0f,  0.5f), glm::vec3( 0.0f, -1.0f,  0.0f), glm::vec2(0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f) }, // back left
		{ glm::vec3( 0.5f, 0.0f,  0.5f), glm::vec3( 0.0f, -1.0f,  0.0f), glm::vec2(1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f) }, // back right
		{ glm::vec3( 0.5f, 0.0f, -0.5f), glm::vec3( 0.0f, -1.0f,  0.0f), glm::vec2(1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 0.0f) }, // front right

		// Left face
		{ glm::vec3(-0.5f, 0.0f,  0.5f), glm::vec3(-1.0f,  0.5f,  0.0f), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f) }, // back left
		{ glm::vec3(-0.5f, 0.0f, -0.5f), glm::vec3(-1.0f,  0.5f,  0.0f), glm::vec2(1.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f) }, // front left
		{ glm::vec3( 0.0f, 1.0f,  0.0f), glm::vec3(-1.0f,  0.5f,  0.0f), glm::vec2(0.5f, 1.0f), glm::vec3(0.0f, 1.0f, 1.0f) }, // top

		// Front face
		{ glm::vec3(-0.5f, 0.0f, -0.5f), glm::vec3( 0.0f,  0.5f, -1.0f), glm::vec2(0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f) }, // front left
		{ glm::vec3( 0.5f, 0.0f, -0.5f), glm::vec3( 0.0f,  0.5f, -1.0f), glm::vec2(1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 0.0f) }, // front right
		{ glm::vec3( 0.0f, 1.0f,  0.0f), glm::vec3( 0.0f,  0.5f, -1.0f), glm::vec2(0.5f, 1.0f), glm::vec3(0.0f, 1.0f, 1.0f) }, // top

		// Right face
		{ glm::vec3( 0.5f, 0.0f, -0.5f), glm::vec3( 1.0f,  0.5f,  0.0f), glm::vec2(0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 0.0f) }, // front right
		{ glm::vec3( 0.5f, 0.0f,  0.5f), glm::vec3( 1.0f,  0.5f,  0.0f), glm::vec2(1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f) }, // back right
		{ glm::vec3( 0.0f, 1.0f,  0.0f), glm::vec3( 1.0f,  0.5f,  0.0f), glm::vec2(0.5f, 1.0f), glm::vec3(0.0f, 1.0f, 1.0f) }, // top

		// Back face
		{ glm::vec3(-0.5f, 0.0f,  0.5f), glm::vec3( 0.0f,  0.5f,  1.0f), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f) }, // back left
		{ glm::vec3( 0.5f, 0.0f,  0.5f), glm::vec3( 0.0f,  0.5f,  1.0f), glm::vec2(1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f) }, // back right
		{ glm::vec3( 0.0f, 1.0f,  0.0f), glm::vec3( 0.0f,  0.5f,  1.0f), glm::vec2(0.5f, 1.0f), glm::vec3(0.0f, 1.0f, 1.0f) }  // top
	};

	std::vector<GLuint> pyramidIndices
	{
		0, 1, 2,		// top left base triangle
		0, 3, 2,		// bottom right base triangle
		4, 5, 6,		// left face triangle
		7, 9, 8,		// back face triangle
		10, 11, 12,		// right face triangle
		13, 15, 14		// front face triangle
	};

	// Data for a cube
	std::vector<VertexStruct> cubeVertices
	{
		//	             COORDS		                    NORMALS                  TEXT COORDS                  COLORS
		// Front face
		{ glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3( 0.0f,  0.0f, -1.0f), glm::vec2(0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f) }, // front bottom left
		{ glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec3( 0.0f,  0.0f, -1.0f), glm::vec2(0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f) }, // front top left
		{ glm::vec3( 0.5f,  0.5f, -0.5f), glm::vec3( 0.0f,  0.0f, -1.0f), glm::vec2(1.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f) }, // front top right
		{ glm::vec3( 0.5f, -0.5f, -0.5f), glm::vec3( 0.0f,  0.0f, -1.0f), glm::vec2(1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 0.0f) }, // front bottom right

		// Back face
		{ glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec3( 0.0f,  0.0f,  1.0f), glm::vec2(0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f) }, // back bottom left
		{ glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec3( 0.0f,  0.0f,  1.0f), glm::vec2(0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f) }, // back top left
		{ glm::vec3( 0.5f,  0.5f,  0.5f), glm::vec3( 0.0f,  0.0f,  1.0f), glm::vec2(1.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f) }, // back top right
		{ glm::vec3( 0.5f, -0.5f,  0.5f), glm::vec3( 0.0f,  0.0f,  1.0f), glm::vec2(1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 0.0f) }, // back bottom right

		// Left face
		{ glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec3(-1.0f,  0.0f,  0.0f), glm::vec2(0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f) }, // back bottom left
		{ glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec3(-1.0f,  0.0f,  0.0f), glm::vec2(0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f) }, // back top left
		{ glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec3(-1.0f,  0.0f,  0.0f), glm::vec2(1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f) }, // front top left
		{ glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(-1.0f,  0.0f,  0.0f), glm::vec2(1.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f) }, // front bottom left

		// Right face
		{ glm::vec3( 0.5f, -0.5f,  0.5f), glm::vec3( 1.0f,  0.0f,  0.0f), glm::vec2(1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 0.0f) }, // back bottom right
		{ glm::vec3( 0.5f,  0.5f,  0.5f), glm::vec3( 1.0f,  0.0f,  0.0f), glm::vec2(1.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f) }, // back top right
		{ glm::vec3( 0.5f,  0.5f, -0.5f), glm::vec3( 1.0f,  0.0f,  0.0f), glm::vec2(0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f) }, // back top right
		{ glm::vec3( 0.5f, -0.5f, -0.5f), glm::vec3( 1.0f,  0.0f,  0.0f), glm::vec2(0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 0.0f) }, // back bottom right

		// Top face
		{ glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec3( 0.0f,  1.0f,  0.0f), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f) }, // front top left
		{ glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec3( 0.0f,  1.0f,  0.0f), glm::vec2(0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f) }, // back top left
		{ glm::vec3( 0.5f,  0.5f,  0.5f), glm::vec3( 0.0f,  1.0f,  0.0f), glm::vec2(1.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f) }, // back top right
		{ glm::vec3( 0.5f,  0.5f, -0.5f), glm::vec3( 0.0f,  1.0f,  0.0f), glm::vec2(1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f) }, // front top right

		// Bottom face
		{ glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3( 0.0f, -1.0f,  0.0f), glm::vec2(0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f) }, // front bottom left
		{ glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec3( 0.0f, -1.0f,  0.0f), glm::vec2(0.0f, 1.0f), glm::vec3(1.0f, 0.0f, 0.0f) }, // back bottom left
		{ glm::vec3( 0.5f, -0.5f,  0.5f), glm::vec3( 0.0f, -1.0f,  0.0f), glm::vec2(1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 0.0f) }, // back bottom right
		{ glm::vec3( 0.5f, -0.5f, -0.5f), glm::vec3( 0.0f, -1.0f,  0.0f), glm::vec2(1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 0.0f) }  // front bottom right
	};

	std::vector<GLuint> cubeIndices
	{
		0, 1, 2,		// top left, front face triangle
		0, 3, 2,		// bottom right, front face triangle

		4, 5, 6,		// top left, back face triangle
		4, 7, 6,		// bottom right, back face triangle

		8, 9, 10,		// top left, left face triangle
		8, 11, 10,		// bottom right, left face triangle

		12, 13, 14,		// top right, right face triangle
		12, 15, 14,		// bottom left, right face triangle

		16, 17, 18,		// top left, top face triangle
		16, 19, 18,		// bottom right, top face triangle

		20, 21, 22,		// bottom left, bottom face triangle
		20, 23, 22		// top right, bottom face triangle
	};

	// Supports: texture_diffuse, texture_specular, texture_normal, texture_height
	std::vector<TextureStruct> objectTextures
	{
		{ "texture_diffuse", "resources/textures/default.png" }
	};

	std::vector<TextureStruct> object2Textures
	{
		{ "texture_diffuse", "resources/textures/noise.png" }
	};

	// Create shaders
	lightShader.Create("src/shaders/light.vert", "src/shaders/light.frag");
	objectShader.Create("src/shaders/object.vert", "src/shaders/object.frag");

	// Create meshes
	meshObjects.push_back(Mesh());
	meshObjects[0].CreateBuffers(cubeVertices, cubeIndices, objectTextures);
	meshObjects.push_back(Mesh());
	meshObjects[1].CreateBuffers(pyramidVertices, pyramidIndices, object2Textures);

	// Create models
	modelLights.push_back(Model());
	modelLights[0].Import("resources/models/sphere.obj");
	modelObjects.push_back(Model());
	modelObjects[0].Import("resources/models/sphere.obj", object2Textures);
	modelObjects.push_back(Model());
	modelObjects[1].Import("resources/models/backpack.obj", "resources/textures/backpack/");
	modelObjects.push_back(Model());
	modelObjects[2].Import("resources/models/scimitar.obj", "resources/textures/scimitar/");

	// Create textures
	//meshObjects[0].CreateTextures(objectShader.id, GL_TEXTURE_2D, GL_LINEAR, GL_REPEAT);
	//meshObjects[1].CreateTextures(objectShader.id, GL_TEXTURE_2D, GL_LINEAR, GL_REPEAT);

	// Create texture
	//meshObjects[0].hasTexture = true;
	//texture.Create(meshObjects[0].textures[0].path.c_str(), 0, GL_TEXTURE0); // Load proper image and create a texture for it
	////Send1i_Uniform(objectShader.id, "texture_diffuse1", 0); // Send texture name to the shader
	//texture.Bind(GL_TEXTURE_2D, 0); // Bind proper texture to the GPU
	//texture.GenerateMipmap(GL_LINEAR, GL_REPEAT); // Generate mipmap
	//texture.Unbind(); // Unbind texture

	//// Create texture
	//meshObjects[1].hasTexture = true;
	//texture.Create(meshObjects[1].textures[0].path.c_str(), 2, GL_TEXTURE0); // Load proper image and create a texture for it
	////Send1i_Uniform(objectShader.id, "texture_diffuse1", 2); // Send texture name to the shader
	//texture.Bind(GL_TEXTURE_2D, 0); // Bind proper texture to the GPU
	//texture.GenerateMipmap(GL_LINEAR, GL_REPEAT); // Generate mipmap
	//texture.Unbind(); // Unbind texture
}

void World::End()
{
	// Delete buffers
	meshObjects[0].DeleteBuffers(); // Delete object's buffers
	meshObjects[1].DeleteBuffers(); // Delete object's buffers

	// Delete textures
	modelLights[0].DeleteTextures(); // Delete light source's textures
	modelObjects[0].DeleteTextures(); // Delete all textures and meshes for the model
	modelObjects[1].DeleteTextures(); // Delete all textures and meshes for the model
	modelObjects[2].DeleteTextures(); // Delete all textures and meshes for the model

	// Delete shaders
	lightShader.Delete();
	objectShader.Delete();
}

void World::BeforeDrawing()
{
	glClearColor(0.05f, 0.1f, 0.2f, 1.0f); // Wipe drawing from previous frame with a black color
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color buffer and depth buffer
}

void World::Draw(GLFWwindow* window)
{
	// Treat camera inputs (WASD - move on X/Z axis, LEFT CTRL/SPACE - move on Y axis, SHIFT - speed modifier)
	camera.TreatInputs(window, Engine::deltaTime);
	camera.UpdateMatrices(60.0f, 0.1f, 100.0f, view, projection); // Compute view and projection matrices

	// RENDER LIGHT SOURCES SECTION
	lightShader.Use(); // Use light source's shaders
	lightShader.InitMatrices(view, projection); // Send view and projection matrix to light source's shaders

	// Render without texture
	modelLights[0].Draw(lightShader.id, glm::vec3(-2.0f, 2.0f, -6.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f));

	// RENDER NORMAL OBJECTS SECTION
	objectShader.Use(); // Use object's shader
	// Send material data to object's shaders
	objectShader.InitMaterial(modelLights[0].position, modelLights[0].color, camera.position,
		glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(1.0f, 0.5f, 0.31f), glm::vec3(0.5f, 0.5f, 0.5f), 32.0f);
	objectShader.InitMatrices(view, projection); // Send view and projection matrix to object's shaders

	meshObjects[0].CreateTextures(objectShader.id, GL_TEXTURE_2D, GL_LINEAR, GL_REPEAT);
	meshObjects[0].Draw(objectShader.id, glm::vec3(0.0f, 0.0f, -2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f)); // Create texture then draw
	meshObjects[1].CreateTextures(objectShader.id, GL_TEXTURE_2D, GL_LINEAR, GL_REPEAT);
	meshObjects[1].DrawChild(objectShader.id, meshObjects[0], glm::vec3(2.0f, 0.0f, -2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 1.0f, 1.0f)); // Create texture then draw

	modelObjects[0].Draw(objectShader.id, glm::vec3(2.0f, 2.0f, -6.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 0.0f, 1.0f)); // Create all meshes, then all textures and apply them to every mesh
	modelObjects[1].Draw(objectShader.id, glm::vec3(7.0f, 0.0f, -15.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f)); // Create all meshes
	modelObjects[2].Draw(objectShader.id, glm::vec3(-5.0f, 0.0f, -7.0f), glm::vec3(-90.0f, 0.0f, 0.0f), glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(1.0f, 1.0f, 1.0f));
}

void World::AfterDrawing(GLFWwindow* window)
{
	glfwSwapBuffers(window); // Swap front and back buffer
	glfwPollEvents(); // Take care of GLFW events
}

void World::Run(GLFWwindow* window)
{
	glEnable(GL_DEPTH_TEST); // Enable depth

	// Initialize camera with window dimensions and with specified starting position
	camera.Init(Engine::resX, Engine::resY, glm::vec3(0.0f, 0.0f, 0.0f));

	// Loop until window is closed
	while (!glfwWindowShouldClose(window))
	{
		BeforeDrawing();
		Draw(window);
		AfterDrawing(window);

		Engine::SetTimeValues(); // Compute deltaTime
		Engine::CheckErrorCodes(); // Check for GLAD error codes
	}
}