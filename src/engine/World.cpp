#include "World.h"

void World::Init()
{
	// Data for a plane
	std::vector<VertexStruct> vertices =
	{
		//	             COORDS		                   NORMALS                 TEXT COORDS                  COLORS
		{ glm::vec3(-0.5f, 0.0f, -0.5f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f) }, // front left
		{ glm::vec3(-0.5f, 0.0f,  0.5f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f) }, // back left
		{ glm::vec3( 0.5f, 0.0f,  0.5f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(1.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f) }, // back right
		{ glm::vec3( 0.5f, 0.0f, -0.5f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 0.0f) }  // front right
	};

	std::vector<GLuint> indices
	{
		0, 1, 2,		// top left triangle
		0, 3, 2			// bottom right triangle
	};

	// Supports: texture_diffuse, texture_specular, texture_normal, texture_height
	std::vector<TextureStruct> textures
	{
		{ "texture_diffuse", "resources/textures/default.png" }
	};

	// Data for a pyramid
	std::vector<VertexStruct> lightVertices
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

	std::vector<GLuint> lightIndices
	{
		0, 1, 2,		// top left base triangle
		0, 3, 2,		// bottom right base triangle
		4, 5, 6,		// left face triangle
		7, 9, 8,		// back face triangle
		10, 11, 12,		// right face triangle
		13, 15, 14		// front face triangle
	};

	std::vector<TextureStruct> lightTextures
	{
		{ "texture_diffuse", "resources/textures/default.png" }
	};

	// Data for a cube
	std::vector<VertexStruct> objectVertices
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

	std::vector<GLuint> objectIndices
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

	std::vector<TextureStruct> objectTextures
	{
		{ "texture_diffuse", "resources/textures/default.png" }
	};

	std::vector<TextureStruct> object2Textures
	{
		{ "texture_diffuse", "resources/textures/noise.png" }
	};

	// Create light shaders
	lightShader.Create("src/shaders/light.vert", "src/shaders/light.frag");
	meshLightSource.CreateBuffers(lightVertices, lightIndices, lightTextures);

	// Create object shaders
	objectShader.Create("src/shaders/object.vert", "src/shaders/object.frag");
	meshObject.CreateBuffers(objectVertices, objectIndices, objectTextures);

	object2.Import("resources/models/sphere.obj", "resources/textures/noise.png");
	object3.Import("resources/models/backpack.obj", "resources/models/backpack/");
}

void World::End()
{
	meshLightSource.DeleteBuffers(); // Delete light source's buffers
	meshLightSource.DeleteTextures(); // Delete light source's textures
	lightShader.Delete(); // Delete light source's shader

	meshObject.DeleteBuffers(); // Delete object's buffers
	meshObject.DeleteTextures(); // Delete object's textures
	objectShader.Delete(); // Delete object shader
}

void World::BeforeDrawing()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Wipe drawing from previous frame with a black color
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color buffer and depth buffer
}

void World::Draw(GLFWwindow* window)
{
	// Treat camera inputs (WASD - move on X/Z axis, LEFT CTRL/SPACE - move on Y axis, SHIFT - speed modifier)
	camera.TreatInputs(window, Engine::deltaTime);
	camera.UpdateMatrices(60.0f, 0.1f, 100.0f, view, projection); // Compute view and projection matrices

	lightShader.Use(); // Use light source's shaders
	lightShader.InitMatrices(view, projection); // Send view and projection matrix to light source's shaders
	// Compute and send model matrix and color to the GPU then draw the mesh
	meshLightSource.Draw(lightShader.id, glm::vec3(-2.0f, 2.0f, -6.0f), glm::vec3(1.0f, 1.0f, 1.0f));

	objectShader.Use(); // Use object's shader
	// Send material data to object's shaders
	objectShader.InitMaterial(meshLightSource.position, meshLightSource.color, camera.position,
		glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(1.0f, 0.5f, 0.31f), glm::vec3(0.5f, 0.5f, 0.5f), 32.0f);
	objectShader.InitMatrices(view, projection); // Send view and projection matrix to object's shaders
	meshObject.CreateTextures(objectShader.id, GL_TEXTURE_2D, GL_LINEAR, GL_REPEAT);
	// Compute and send model matrix, color and texture slot to the GPU then draw the mesh
	meshObject.Draw(objectShader.id, glm::vec3(0.0f, 0.0f, -2.0f), glm::vec3(0.0f, 1.0f, 1.0f));

	object2.CreateTextures(objectShader.id, GL_TEXTURE_2D, GL_LINEAR, GL_REPEAT);
	object2.Draw(objectShader.id, glm::vec3(2.0f, 2.0f, -6.0f), glm::vec3(1.0f, 0.0f, 1.0f));

	object3.Draw(objectShader.id, glm::vec3(4.0f, -2.0f, 0.0f), glm::vec3(1.0f, 1.0f, 0.0f));
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