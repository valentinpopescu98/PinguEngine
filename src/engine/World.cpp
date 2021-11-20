#include "World.h"

// Data for a plane
//GLfloat vertices[] =
//{
//	 //    COORDS		    TEXT COORDS         NORMALS                  COLORS
//	-0.5f, 0.0f, -0.5f,		0.0f, 0.0f,		0.0f, 0.0f, -1.0f,		1.0f, 0.0f, 0.0f,  // bottom left
//	-0.5f, 0.0f,  0.5f,		0.0f, 1.0f,		0.0f, 0.0f, -1.0f,		0.0f, 0.0f, 1.0f,  // top left
//	 0.5f, 0.0f,  0.5f,		1.0f, 1.0f,		0.0f, 0.0f, -1.0f,		0.0f, 1.0f, 0.0f,  // top right
//	 0.5f, 0.0f, -0.5f,		1.0f, 0.0f,		0.0f, 0.0f, -1.0f,		1.0f, 1.0f, 0.0f   // bottom right
//};
//
//GLuint indices[] = 
//{
//	0, 1, 2,   // top left triangle
//	0, 3, 2    // bottom right triangle
//};

// Data for a cube
GLfloat objectVertices[] =
{
	//    COORDS		    TEXT COORDS         NORMALS                  COLORS
	// Front face
   -0.5f, -0.5f, -0.5f,		0.0f, 0.0f,		0.0f, 0.0f, -1.0f,		1.0f, 0.0f, 0.0f,  // bottom left
   -0.5f,  0.5f, -0.5f,		0.0f, 1.0f,		0.0f, 0.0f, -1.0f,		0.0f, 0.0f, 1.0f,  // top left
	0.5f,  0.5f, -0.5f,		1.0f, 1.0f,		0.0f, 0.0f, -1.0f,		0.0f, 1.0f, 0.0f,  // top right
	0.5f, -0.5f, -0.5f,		1.0f, 0.0f,		0.0f, 0.0f, -1.0f,		1.0f, 1.0f, 0.0f,  // bottom right

	// Back face
   -0.5f, -0.5f,  0.5f,		1.0f, 0.0f,		0.0f, 0.0f,  1.0f,		1.0f, 0.0f, 0.0f,  // bottom left
   -0.5f,  0.5f,  0.5f,		1.0f, 1.0f,		0.0f, 0.0f,  1.0f,		0.0f, 0.0f, 1.0f,  // top left
	0.5f,  0.5f,  0.5f,		0.0f, 1.0f,		0.0f, 0.0f,  1.0f,		0.0f, 1.0f, 0.0f,  // top right
	0.5f, -0.5f,  0.5f,		0.0f, 0.0f,		0.0f, 0.0f,  1.0f,		1.0f, 1.0f, 0.0f   // bottom right
};

GLuint objectIndices[] =
{
	0, 1, 2,	// top left, back face triangle
	0, 3, 2,	// bottom right, back face triangle

	4, 5, 6,	// top left, back face triangle
	4, 7, 6,	// bottom right, back face triangle

	0, 1, 5,	// top left, left face triangle
	0, 4, 5,	// bottom right, left face triangle

	2, 6, 7,	// top left, right face triangle
	3, 2, 7,	// bottom right, right face triangle

	5, 1, 2,	// top left, top face triangle
	5, 6, 2,	// bottom right, top face triangle

	4, 0, 3,	// top left, bottom face triangle
	4, 7, 3		// bottom right, bottom face triangle
};

// Data for a pyramid
GLfloat lightVertices[] =
{
	//    COORDS		        NORMALS                  COLORS
   -0.5f, 0.0f,  0.5f,		-1.0f, 1.0f,  1.0f,		1.0f, 0.0f, 0.0f,  // front left
   -0.5f, 0.0f, -0.5f,		-1.0f, 1.0f, -1.0f,		0.0f, 1.0f, 0.0f,  // back left
	0.5f, 0.0f, -0.5f,		 1.0f, 1.0f, -1.0f,		0.0f, 0.0f, 1.0f,  // back right
	0.5f, 0.0f,  0.5f,		 1.0f, 1.0f,  1.0f,		1.0f, 1.0f, 0.0f,  // front right
	0.0f, 1.0f,  0.0f,		 0.0f, 1.0f,  0.0f,		0.0f, 1.0f, 1.0f,  // top
};

GLuint lightIndices[] =
{
	0, 1, 2,	// top left base triangle
	0, 2, 3,	// bottom right base triangle
	0, 1, 4,	// left face triangle
	1, 2, 4,	// back face triangle
	2, 3, 4,	// right face triangle
	3, 0, 4		// front face triangle
};

void World::Init()
{
	// Create object shaders
	objectShader.Create("src/shaders/object.vert", "src/shaders/object.frag");

	// Create object buffers
	objectVAO.Create(); // Create object VAO
	objectVBO.Create(objectVertices, sizeof(objectVertices)); // Create object VBO, bind and send buffers to GPU
	objectEBO.Create(objectIndices, sizeof(objectIndices)); // Create object EBO, bind and send buffers to GPU

	objectVAO.LinkVBO(objectVBO, 0, 11 * sizeof(float), (void*)0); // Link object VBOs to location 0
	objectVAO.LinkVBO(objectVBO, 1, 11 * sizeof(float), (void*)(3 * sizeof(float))); // Link object VBOs to location 1
	objectVAO.LinkVBO(objectVBO, 2, 11 * sizeof(float), (void*)(5 * sizeof(float))); // Link object VBOs to location 2
	objectVAO.LinkVBO(objectVBO, 3, 11 * sizeof(float), (void*)(8 * sizeof(float))); // Link object VBOs to location 3

	objectVAO.Unbind(); // Unbind object VAO
	objectVBO.Unbind(); // Unbind object VBO
	objectEBO.Unbind(); // Unbind object EBO

	// Create light shaders
	lightShader.Create("src/shaders/light.vert", "src/shaders/light.frag");

	// Create light buffers
	lightVAO.Create(); // Create light source VAO
	lightVBO.Create(lightVertices, sizeof(lightVertices)); // Create light source VBO, bind and send buffers to GPU
	lightEBO.Create(lightIndices, sizeof(lightIndices)); // Create light source EBO, bind and send buffers to GPU

	lightVAO.LinkVBO(lightVBO, 0, 9 * sizeof(float), (void*)0); // Link light source VBOs to location 0
	lightVAO.LinkVBO(lightVBO, 1, 9 * sizeof(float), (void*)(3 * sizeof(float))); // Link light source VBOs to location 1
	lightVAO.LinkVBO(lightVBO, 2, 9 * sizeof(float), (void*)(6 * sizeof(float))); // Link light source VBOs to location 2

	lightVAO.Unbind(); // Unbind light source VAO
	lightVBO.Unbind(); // Unbind light source VBO
	lightEBO.Unbind(); // Unbind light source EBO

	// Create texture
	texture.Create("resources/textures/default.png", GL_TEXTURE0); // Load image and create a texture for it
	texture.Bind(GL_TEXTURE_2D); // Bind the texture

	// Use this overload for filling the empty space near the texture with a chosen color
	//float borderColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	//texture.GenerateMipmap(GL_LINEAR, borderColor);

	texture.GenerateMipmap(GL_LINEAR, GL_REPEAT); // Generate mipmap
	texture.Unbind(); // Unbind texture
}

void World::End()
{
	objectVAO.Delete(); // Delete object VAO
	objectVBO.Delete(); // Delete object VBO
	objectEBO.Delete(); // Delete object EBO
	objectShader.Delete(); // Delete object shader

	lightVAO.Delete(); // Delete light source VAO
	lightVBO.Delete(); // Delete light source VBO
	lightEBO.Delete(); // Delete light source EBO
	texture.Delete(); // Delete object texture
	lightShader.Delete(); // Delete light source shader
}

void World::BeforeDrawing()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Wipe drawing from previous frame with a black color
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color buffer and depth buffer
}

void World::Draw(GLFWwindow* window)
{
	// Treat camera inputs (WASD - move on X/Z axis, LEFT CTRL/SPACE - move on Y axis, SHIFT - speed modifier)
	camera.TreatInputs(window, deltaTime);
	camera.UpdateMatrices(60.0f, 0.1f, 100.0f, view, projection); // Compute view and projection matrices

	objectShader.Use(); // Use object's shader
	SendMatrix4x4_Uniform(objectShader.ID, "view", view); // Send view matrix as uniform to the GPU
	SendMatrix4x4_Uniform(objectShader.ID, "projection", projection); // Send projection matrix as uniform to the GPU
	// Compute and send model matrix, color and texture slot to the GPU then draw the mesh
	mesh.CreateMesh(objectShader, objectVAO, texture, "model", "uniColor", "textSlot",
		glm::vec3(0.0f, 1.0f, 1.0f), 0, glm::vec3(0.0f, 0.0f, 0.0f), GL_TRIANGLES, sizeof(objectIndices) / sizeof(*objectIndices));

	lightShader.Use(); // Use object's shader
	SendMatrix4x4_Uniform(lightShader.ID, "view", view); // Send view matrix as uniform to the GPU
	SendMatrix4x4_Uniform(lightShader.ID, "projection", projection); // Send projection matrix as uniform to the GPU
	// Compute and send model matrix and color to the GPU then draw the mesh
	mesh.CreateMesh(lightShader, lightVAO, "model", "uniColor",
		glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(-2.0f, 2.0f, -4.0f), GL_TRIANGLES, sizeof(lightIndices) / sizeof(*lightIndices));
}

void World::AfterDrawing(GLFWwindow* window)
{
	glfwSwapBuffers(window); // Swap front and back buffer
	glfwPollEvents(); // Take care of GLFW events
}

void World::Run(GLFWwindow* window)
{
	glEnable(GL_DEPTH_TEST); // Enable depth

	camera.Init(Engine::resX, Engine::resY, glm::vec3(0.0f, 0.0f, 2.0f)); // Initialize camera with window dimensions and with specified starting position

	// Loop until window is closed
	while (!glfwWindowShouldClose(window))
	{
		SetTimeValues(); // Compute deltaTime

		BeforeDrawing();
		Draw(window);
		AfterDrawing(window);

		CheckErrors(); // Check for errors
	}
}

void World::SetTimeValues()
{
	elapsedTime = glfwGetTime();
	deltaTime = elapsedTime - previousTime;
	previousTime = elapsedTime;
}

void World::CheckErrors()
{
	GLenum errCode;

	if ((errCode = glGetError()) != GL_NO_ERROR)
	{
		std::cout << errCode << std::endl;
	}
}