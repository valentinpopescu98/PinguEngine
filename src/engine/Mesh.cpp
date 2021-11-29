#include "Mesh.h"

void Mesh::CreateBuffers(std::vector<VertexStruct> vertices, std::vector<unsigned int> indices, std::vector<TextureStruct> textures)
{
    this->vertices = vertices;
    this->indices = indices;
    this->textures = textures;

    SetupMesh();
}

void Mesh::SetupMesh()
{
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
    vao.Delete(); // Delete light source VAO
    vbo.Delete(); // Delete light source VBO
    ebo.Delete(); // Delete light source EBO
}

void Mesh::Draw(Shader& shader, const char* modelUni, const char* colorUni, const char* textureUni, glm::vec3 position, glm::vec3 color, GLuint textureSlot)
{
    this->color = color;
    this->position = position;

    texture.Create("resources/textures/default.png", GL_TEXTURE0); // Load image and create a texture for it
    texture.Bind(GL_TEXTURE_2D); // Bind the texture

    // Use this overload for filling the empty space near the texture with a chosen color
    //float borderColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    //texture.GenerateMipmap(GL_LINEAR, borderColor);

    texture.GenerateMipmap(GL_LINEAR, GL_REPEAT); // Generate mipmap
    texture.Unbind(); // Unbind texture

    //GLuint diffuseNr = 1;
    //GLuint specularNr = 1;

    //for (GLuint i = 0; i < textures.size(); i++)
    //{
    //    texture.Create(textures[i].path, GL_TEXTURE0 + i); // Create proper texture
    //    std::string number; // Retrieve texture number
    //    std::string name = textures[i].type; // Retrieve texture type
    //    if (name == "texture_diffuse")
    //        number = std::to_string(diffuseNr++);
    //    else if (name == "texture_specular")
    //        number = std::to_string(specularNr++);

    //    Send1f_Uniform(shader.id, ("material." + name + number).c_str(), i);
    //    texture.Bind(GL_TEXTURE_2D);
    //}
    //texture.Create(textures[0].path, GL_TEXTURE0);

    glm::mat4 model = glm::mat4(1.0f); // Create model matrix as identity matrix
    model = glm::translate(model, position); // Calculate object's global position

    SendMatrix4x4_Uniform(shader.id, modelUni, model); // Send view matrix as uniform to the GPU
    Send3f_Uniform(shader.id, colorUni, glm::vec3(color.r, color.g, color.b)); // Send color as uniform to the GPU
    Send1i_Uniform(shader.id, textureUni, textureSlot); // Send texture slot as uniform to the GPU

    // Draw mesh
    texture.Bind(GL_TEXTURE_2D);
    vao.Bind();
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    vao.Unbind();
}

void Mesh::Draw(Shader& shader, const char* modelUni, const char* colorUni, glm::vec3 position, glm::vec3 color)
{
    this->color = color;
    this->position = position;

    glm::mat4 model = glm::mat4(1.0f); // Create model matrix as identity matrix
    model = glm::translate(model, position); // Calculate object's global position

    SendMatrix4x4_Uniform(shader.id, modelUni, model); // Send view matrix as uniform to the GPU
    Send3f_Uniform(shader.id, colorUni, glm::vec3(color.r, color.g, color.b)); // Send color as uniform to the GPU

    // Draw mesh
    vao.Bind();
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    vao.Unbind();
}