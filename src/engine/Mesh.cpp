#include "Mesh.h"

// Overload for drawing with texture
void Mesh::CreateMesh(Shader& shader, VAO& vao, Texture& texture, const char* modelUni, const char* colorUni, const char* textureUni,
	glm::vec3 color, glm::vec3 position, GLuint textureSlot, GLenum drawMode, GLsizei count)
{
	this->color = color;
	this->position = position;

	glm::mat4 model = glm::mat4(1.0f); // Create model matrix as identity matrix
	model = glm::translate(model, position); // Calculate object's global position

	SendMatrix4x4_Uniform(shader.ID, modelUni, model); // Send view matrix as uniform to the GPU
	Send3f_Uniform(shader.ID, colorUni, glm::vec3(color.r, color.g, color.b)); // Send color as uniform to the GPU
	Send1i_Uniform(shader.ID, textureUni, textureSlot); // Send texture slot as uniform to the GPU

	texture.Bind(GL_TEXTURE_2D); // Bind the texture as 2D texture
	vao.Bind(); // Bind new VAO buffer to VAO target

	glDrawElements(drawMode, count, GL_UNSIGNED_INT, 0); // Draw VBO data from VAO with specified mode
}

// Overload for drawing without texture
void Mesh::CreateMesh(Shader& shader, VAO& vao, const char* modelUni, const char* colorUni,
	glm::vec3 color, glm::vec3 position, GLenum drawMode, GLsizei count)
{
	this->color = color;
	this->position = position;

	glm::mat4 model = glm::mat4(1.0f); // Create model matrix as identity matrix
	model = glm::translate(model, position); // Calculate object's global position

	SendMatrix4x4_Uniform(shader.ID, modelUni, model); // Send view matrix as uniform to the GPU
	Send3f_Uniform(shader.ID, colorUni, glm::vec3(color.r, color.g, color.b)); // Send color as uniform to the GPU

	vao.Bind(); // Bind new VAO buffer to VAO target

	glDrawElements(drawMode, count, GL_UNSIGNED_INT, 0); // Draw VBO data from VAO with specified mode
}

// TODO: to implement with assimp
void Mesh::ImportMesh(const char* meshPath)
{
	std::vector<glm::fvec3> vertex_coords;
	std::vector<glm::fvec2> vertex_textCoords;
	std::vector<glm::fvec3> vertex_normals;

	std::vector<GLuint> vertex_coordsIndices;
	std::vector<GLuint> vertex_textCoordsIndices;
	std::vector<GLuint> vertex_normalsIndices;

	std::vector<std::string> lines = GetFileLines(meshPath);
	std::stringstream ss;
	std::string prefix = "";
	glm::vec3 temp_vec3;
	glm::vec2 temp_vec2;

	for (std::string line : lines)
	{
		ss.clear();
		ss.str(line);
		ss >> prefix;

		if (prefix == "use_mtl")
		{
			
		}
			
		// Vertex coordinate
		if (prefix == "v")
		{
			ss >> temp_vec3.x >> temp_vec3.y >> temp_vec3.z;
			vertex_coords.push_back(temp_vec3);
		}
		// Vertex normal
		else if (prefix == "vn")
		{
			ss >> temp_vec3.x >> temp_vec3.y >> temp_vec3.z;
			vertex_normals.push_back(temp_vec3);
		}
		// Vertex texture coordinate
		else if (prefix == "vt")
		{
			ss >> temp_vec2.x >> temp_vec2.y;
			vertex_textCoords.push_back(temp_vec2);
		}
		else if (prefix == "f")
		{
			ss >> temp_vec3.x >> temp_vec3.y >> temp_vec3.z;
			vertex_coords.push_back(temp_vec3);
		}
	}
}