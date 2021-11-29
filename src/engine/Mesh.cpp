#include "Mesh.h"

void Mesh::CreateBuffers(std::vector<VertexStruct> vertices, std::vector<unsigned int> indices, std::vector<TextureStruct> textures)
{
    this->vertices = vertices;
    this->indices = indices;
    this->textures = textures;

    // Create buffers
    vao.Create(); // Create VAO and bind it
    vbo.Create(vertices); // Create VBO, bind and send buffers to GPU
    ebo.Create(indices); // Create EBO, bind and send buffers to GPU

    vao.LinkVBO(vbo, 0, sizeof(VertexStruct), (void*)0); // Link VBOs to location 0
    vao.LinkVBO(vbo, 1, sizeof(VertexStruct), (void*)offsetof(VertexStruct, normals)); // Link VBOs to location 1
    vao.LinkVBO(vbo, 2, sizeof(VertexStruct), (void*)offsetof(VertexStruct, textCoords)); // Link VBOs to location 2
    vao.LinkVBO(vbo, 3, sizeof(VertexStruct), (void*)offsetof(VertexStruct, colors)); // Link VBOs to location 3

    vao.Unbind(); // Unbind VAO
    vbo.Unbind(); // Unbind VBO
    ebo.Unbind(); // Unbind EBO
}

void Mesh::DeleteBuffers()
{
    vao.Delete(); // Delete VAO
    vbo.Delete(); // Delete VBO
    ebo.Delete(); // Delete EBO
}

void Mesh::UseTextures(GLuint shaderID)
{
    GLuint diffuseNr = 1;
    GLuint specularNr = 1;
    GLuint normalNr = 1;
    GLuint heightNr = 1;
    std::string number;

    for (GLuint i = 0; i < textures.size(); i++)
    {
        // Create texture
        texture.Create(textures[i].path, GL_TEXTURE0 + i); // Load proper image and create a texture for it

        if (textures[i].type == "texture_diffuse")
            number = std::to_string(diffuseNr++); // Transfer unsigned int to string
        else if (textures[i].type == "texture_specular")
            number = std::to_string(specularNr++); // Transfer unsigned int to string
        else if (textures[i].type == "texture_normal")
            number = std::to_string(normalNr++); // transfer unsigned int to string
        else if (textures[i].type == "texture_height")
            number = std::to_string(heightNr++); // transfer unsigned int to string

        Send1i_Uniform(shaderID, (textures[i].type + number).c_str(), i);
        texture.Bind(GL_TEXTURE_2D);

        texture.GenerateMipmap(GL_LINEAR, GL_REPEAT); // Generate mipmap
        texture.Unbind(); // Unbind texture
    }
}

void Mesh::UseTextures(GLuint shaderID, glm::vec4 borderColor)
{
    GLuint diffuseNr = 1;
    GLuint specularNr = 1;
    GLuint normalNr = 1;
    GLuint heightNr = 1;
    std::string number;

    for (GLuint i = 0; i < textures.size(); i++)
    {
        // Create texture
        texture.Create(textures[i].path, GL_TEXTURE0 + i); // Load proper image and create a texture for it

        if (textures[i].type == "texture_diffuse")
            number = std::to_string(diffuseNr++); // Transfer unsigned int to string
        else if (textures[i].type == "texture_specular")
            number = std::to_string(specularNr++); // Transfer unsigned int to string
        else if (textures[i].type == "texture_normal")
            number = std::to_string(normalNr++); // transfer unsigned int to string
        else if (textures[i].type == "texture_height")
            number = std::to_string(heightNr++); // transfer unsigned int to string

        Send1i_Uniform(shaderID, (textures[i].type + number).c_str(), i);
        texture.Bind(GL_TEXTURE_2D);

        // Use this overload for filling the empty space near the texture with a chosen color
        texture.GenerateMipmap(GL_LINEAR, &borderColor[0]); // Generate mipmap
        texture.Unbind(); // Unbind texture
    }
}

void Mesh::Draw(GLuint shaderID, const char* modelUni, const char* colorUni, glm::vec3 position, glm::vec3 color)
{
    this->color = color;
    this->position = position;

    UseTextures(shaderID, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

    glm::mat4 model = glm::mat4(1.0f); // Create model matrix as identity matrix
    model = glm::translate(model, position); // Calculate object's global position

    SendMatrix4x4_Uniform(shaderID, modelUni, model); // Send view matrix as uniform to the GPU
    Send3f_Uniform(shaderID, colorUni, glm::vec3(color.r, color.g, color.b)); // Send color as uniform to the GPU

    // Draw mesh
    texture.Bind(GL_TEXTURE_2D);
    vao.Bind();
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    vao.Unbind();
    glActiveTexture(GL_TEXTURE0); // Reset to default texture
}