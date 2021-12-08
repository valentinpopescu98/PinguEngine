#include "Model.h"

// Import mesh. Use with render method without texture parameters
void Model::Import(std::string meshPath, Model& parent, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, glm::vec3 color)
{
    this->position = position + parent.position;
    this->rotation = rotation + parent.rotation;
    this->scale = scale * parent.scale;
    this->color = color;

    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(meshPath, aiProcess_Triangulate | aiProcess_FlipUVs);

    if (CheckErrors(scene, importer))
    {
        return;
    }

    ProcessNode(scene->mRootNode, scene);
}

// Import mesh and textures from a texture structure. Use with render method with texture parameters
void Model::Import(std::string meshPath, std::vector<TextureStruct> customTextures, Model& parent, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, glm::vec3 color)
{
    this->position = position + parent.position;
    this->rotation = rotation + parent.rotation;
    this->scale = scale * parent.scale;
    this->color = color;

    textures = customTextures;

    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(meshPath, aiProcess_Triangulate | aiProcess_FlipUVs);

    if (CheckErrors(scene, importer))
    {
        return;
    }

    ProcessNode(scene->mRootNode, scene);
}

// Import mesh and textures from a physical directory. Use with render method with texture parameters
void Model::Import(std::string meshPath, std::string texturesDirPath, Model& parent, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, glm::vec3 color)
{
    this->position = position + parent.position;
    this->rotation = rotation + parent.rotation;
    this->scale = scale * parent.scale;
    this->color = color;

    this->texturesDirPath = texturesDirPath;

    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(meshPath, aiProcess_Triangulate);

    if (CheckErrors(scene, importer))
    {
        return;
    }

    aiNode* root = scene->mRootNode;
    if (root->mNumMeshes == 0)
    {
        root = root->mChildren[0];
    }

    for (GLuint i = 0; i < root->mNumMeshes; i++)
    {
        aiMesh* mesh = scene->mMeshes[root->mMeshes[i]];
        aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

        std::vector<TextureStruct> diffuseMaps = ReadTexturesOfType(material, aiTextureType_DIFFUSE, "texture_diffuse");
        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

        std::vector<TextureStruct> specularMaps = ReadTexturesOfType(material, aiTextureType_SPECULAR, "texture_specular");
        textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());

        std::vector<TextureStruct> normalMaps = ReadTexturesOfType(material, aiTextureType_HEIGHT, "texture_normal");
        textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
    }

    ProcessNode(scene->mRootNode, scene);
}

// Create textures for imported models
void Model::CreateTextures()
{
    for (GLuint i = 0; i < meshes.size(); i++)
    {
        meshes[i].textures = textures;
        meshes[i].CreateTextures(shaderID, GL_TEXTURE_2D, GL_LINEAR, GL_REPEAT);
    }
}

// Delete all buffers for all the meshes
void Model::DeleteBuffers()
{
    for (GLuint i = 0; i < meshes.size(); i++)
    {
        meshes[i].DeleteBuffers();
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

// Render meshes. Use with import method without texture parameters
void Model::Draw(GLuint shaderID)
{
    for (GLuint i = 0; i < meshes.size(); i++)
    {
        meshes[i].Draw(shaderID, this->position, this->rotation, this->scale, this->color);
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

std::vector<TextureStruct> Model::ReadTexturesOfType(aiMaterial* mat, aiTextureType type, std::string typeName)
{
    std::vector<TextureStruct> textures;
    std::vector<TextureStruct> texturesLoaded;

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
    meshObj.CreateBuffers(vertices, indices, textures);

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