#include "Mesh.h"

void Mesh::CreateBuffers(std::vector<VertexStruct> vertices, std::vector<unsigned int> indices)
{
    this->vertices = vertices;
    this->indices = indices;

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

// Use this for objects with textures wrapped with anything except GL_CLAMP_TO_BORDER
void Mesh::CreateTextures(GLuint shaderID, GLenum textureDimension, GLint interpType, GLint wrapType)
{
    hasTexture = true;

    GLuint diffuseNr = 1;
    GLuint specularNr = 1;
    GLuint normalNr = 1;
    GLuint heightNr = 1;
    std::string number;

    for (GLuint i = 0; i < textures.size(); i++)
    {
        // Create texture
        texture.Create(textures[i].path.c_str(), i, GL_TEXTURE0 + i); // Load proper image and create a texture for it

        if (textures[i].type == "texture_diffuse")
            number = std::to_string(diffuseNr++); // Transfer unsigned int to string
        else if (textures[i].type == "texture_specular")
            number = std::to_string(specularNr++); // Transfer unsigned int to string
        else if (textures[i].type == "texture_normal")
            number = std::to_string(normalNr++); // transfer unsigned int to string

        Send1i_Uniform(shaderID, (textures[i].type + number).c_str(), i); // Send texture name to the shader
        texture.Bind(textureDimension, i); // Bind proper texture to the GPU

        texture.GenerateMipmap(interpType, wrapType); // Generate mipmap
        texture.Unbind(); // Unbind texture
    }
}

// Use this for objects with textures wrapped with GL_CLAMP_TO_BORDER
void Mesh::CreateTextures(GLuint shaderID, GLenum textureDimension, GLint interpType, glm::vec3 borderColor)
{
    hasTexture = true;

    GLuint diffuseNr = 1; // Counter for diffuse texture number
    GLuint specularNr = 1; // Counter for specular texture number
    GLuint normalNr = 1; // Counter for normal texture number
    GLuint heightNr = 1; // Counter for height texture number
    std::string number; // String for the number of the used texture

    for (GLuint i = 0; i < textures.size(); i++)
    {
        // Create texture
        texture.Create(textures[i].path.c_str(), i, GL_TEXTURE0 + i); // Load proper image and create a texture for it

        if (textures[i].type == "texture_diffuse")
            number = std::to_string(diffuseNr++); // Transfer unsigned int to string
        else if (textures[i].type == "texture_specular")
            number = std::to_string(specularNr++); // Transfer unsigned int to string
        else if (textures[i].type == "texture_normal")
            number = std::to_string(normalNr++); // transfer unsigned int to string
        else if (textures[i].type == "texture_height")
            number = std::to_string(heightNr++); // transfer unsigned int to string

        Send1i_Uniform(shaderID, (textures[i].type + number).c_str(), i); // Send texture name to the shader
        texture.Bind(textureDimension, i); // Bind proper texture to the GPU

        texture.GenerateMipmap(interpType, &borderColor[0]); // Generate mipmap with specific border color
        texture.Unbind(); // Unbind texture
    }
}

void Mesh::DeleteTextures()
{
    for (GLuint i = 0; i < textures.size(); i++)
    {
        texture.Delete(i); // Delete proper texture from memory
    }
}

// Use this to render a mesh with no texture
void Mesh::Draw(GLuint shaderID, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, glm::vec3 color)
{
    this->position = position;
    this->rotation = rotation;
    this->scale = scale;
    this->color = color;

    glm::mat4 model = glm::mat4(1.0f); // Create model matrix as identity matrix
    // Calculate object's global position, rotation and scale
    model = glm::translate(model, position);
    model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::scale(model, scale);

    Send1i_Uniform(shaderID, "hasTexture", hasTexture);
    SendMatrix4x4_Uniform(shaderID, "model", model); // Send view matrix as uniform to the GPU
    Send3f_Uniform(shaderID, "objColor", glm::vec3(color.r, color.g, color.b)); // Send color as uniform to the GPU

    // Draw mesh
    vao.Bind();
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    vao.Unbind();
    glActiveTexture(GL_TEXTURE0); // Reset to default texture
}

// Use this to render a child mesh with no texture
void Mesh::DrawChild(GLuint shaderID, Mesh& parent, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, glm::vec3 color)
{
    Draw(shaderID, position + parent.position, rotation + parent.rotation, scale * parent.scale, color);
}