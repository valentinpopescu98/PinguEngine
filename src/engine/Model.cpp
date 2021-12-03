#include "Model.h"

// Import mesh. Use with render method without texture parameters
void Model::Import(std::string meshPath)
{
    hasTexture = 0;

    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(meshPath, aiProcess_Triangulate | aiProcess_FlipUVs);

    if (CheckErrors(scene, importer))
    {
        return;
    }

    ProcessNode(scene->mRootNode, scene);
}

// Import mesh and textures from a texture structure. Use with render method with texture parameters
void Model::Import(std::string meshPath, std::vector<TextureStruct> customTextures)
{
    hasTexture = 1;
    this->customTextures = customTextures;

    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(meshPath, aiProcess_Triangulate | aiProcess_FlipUVs);

    if (CheckErrors(scene, importer))
    {
        return;
    }

    ProcessNode(scene->mRootNode, scene);
}

// Import mesh and textures from a physical directory. Use with render method with texture parameters
void Model::Import(std::string meshPath, std::string texturesDirPath)
{
    hasTexture = 2;
    this->texturesDirPath = texturesDirPath;

    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(meshPath, aiProcess_Triangulate | aiProcess_FlipUVs);

    if (CheckErrors(scene, importer))
    {
        return;
    }

    ProcessNode(scene->mRootNode, scene);
}

// Render mesh. Use with import method without texture parameters
void Model::Render(GLuint shaderID, glm::vec3 position, glm::vec3 color)
{
    for (GLuint i = 0; i < meshes.size(); i++)
    {
		meshes[i].Draw(shaderID, position, color);
    }
}

// Render mesh and textures with any wrapping except GL_CLAMP_TO_BORDER. Use with import method with texture parameters
void Model::Render(GLuint shaderID, glm::vec3 position, glm::vec3 color, GLenum textureDimension, GLint interpType, GLint wrapType)
{
    for (GLuint i = 0; i < meshes.size(); i++)
    {
        meshes[i].CreateTextures(shaderID, textureDimension, interpType, wrapType);
        meshes[i].Draw(shaderID, position, color);
    }
}

// Render mesh and textures with GL_CLAMP_TO_BORDER wrapping. Use with import method with texture parameters
void Model::Render(GLuint shaderID, glm::vec3 position, glm::vec3 color, GLenum textureDimension, GLint interpType, glm::vec3 borderColor)
{
    for (GLuint i = 0; i < meshes.size(); i++)
    {
        meshes[i].CreateTextures(shaderID, textureDimension, interpType, borderColor);
        meshes[i].Draw(shaderID, position, color);
    }
}

// Delete all textures for all the meshes
void Model::DeleteTextures()
{
    for (GLuint i = 0; i < meshes.size(); i++)
    {
        meshes[i].DeleteTextures();
    }
}

int Model::CheckErrors(const aiScene* scene, Assimp::Importer& importer)
{
    if (!scene or scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE or !scene->mRootNode)
    {
        std::cout << "ASSIMP ERROR: " << importer.GetErrorString() << std::endl;
        return -1;
    }
    return 0;
}

GLuint Model::TextureFromFile(const char* path)
{
    GLuint textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glGenerateMipmap(GL_TEXTURE_2D); // Create mip-map

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}

std::vector<TextureStruct> Model::LoadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName)
{
    std::vector<TextureStruct> textures;

    for (GLuint i = 0; i < mat->GetTextureCount(type); i++)
    {
        aiString str;

        mat->GetTexture(type, i, &str);
        bool skip = false;

        for (GLuint j = 0; j < texturesLoaded.size(); j++)
        {
            if (texturesLoaded[j].path == str.C_Str())
            {
                textures.push_back(texturesLoaded[j]);
                skip = true;
                break;
            }
        }

        if (!skip)
        {   
            // If texture hasn't been loaded already, load it
            TextureStruct texture;
            std::string textPath = texturesDirPath + str.C_Str();
            //texture.id = TextureFromFile(textPath.c_str());
            TextureFromFile(textPath.c_str());
            texture.type = typeName;
            texture.path = textPath;

            textures.push_back(texture);
            texturesLoaded.push_back(texture); // Add to loaded textures
        }
    }

    return textures;
}

Mesh Model::ProcessMesh(aiMesh* mesh, const aiScene* scene)
{
    std::vector<VertexStruct> vertices;
    std::vector<GLuint> indices;
    std::vector<TextureStruct> textures;

    for (GLuint i = 0; i < mesh->mNumVertices; i++)
    {
        VertexStruct vertex;

        // Process vertex positions, normals, texture coordinates and colors
        glm::vec2 vector2;
        glm::vec3 vector3;

        vector3.x = mesh->mVertices[i].x;
        vector3.y = mesh->mVertices[i].y;
        vector3.z = mesh->mVertices[i].z;
        vertex.coords = vector3;

        vector3.x = mesh->mNormals[i].x;
        vector3.y = mesh->mNormals[i].y;
        vector3.z = mesh->mNormals[i].z;
        vertex.normals = vector3;

        // Check if the mesh contains texture coordinates
        if (mesh->mTextureCoords[0])
        {
            vector2.x = mesh->mTextureCoords[0][i].x;
            vector2.y = mesh->mTextureCoords[0][i].y;
            vertex.textCoords = vector2;
        }
        else
        {
            vertex.textCoords = glm::vec2(0.0f, 0.0f);
        }

        // Check if the mesh contains colors
        if (mesh->mColors[0])
        {
            vector3.x = mesh->mColors[0][i].r;
            vector3.y = mesh->mColors[0][i].g;
            vector3.y = mesh->mColors[0][i].b;
            vertex.textCoords = vector3;
        }
        else
        {
            vertex.colors = glm::vec3(0.0f, 0.0f, 0.0f);
        }

        vertices.push_back(vertex);
    }

    // Process indices
    for (GLuint i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        for (GLuint j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }

    // Process material
    Mesh meshObj;

    if (hasTexture == 1)
    {
        meshObj.CreateBuffers(vertices, indices, customTextures);
    }
    else if(hasTexture == 0 or hasTexture == 2)
    {
        if (mesh->mMaterialIndex >= 0)
        {
            aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

            std::vector<TextureStruct> diffuseMaps = LoadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
            textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

            std::vector<TextureStruct> specularMaps = LoadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
            textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());

            meshObj.CreateBuffers(vertices, indices, textures);
        }
    }

    return meshObj;
}

void Model::ProcessNode(aiNode* node, const aiScene* scene)
{
    // Process all the node's meshes (if any)
    for (GLuint i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(ProcessMesh(mesh, scene));
    }
    // Do the same for each of its children
    for (GLuint i = 0; i < node->mNumChildren; i++)
    {
        ProcessNode(node->mChildren[i], scene);
    }
}