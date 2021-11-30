#include "Model.h"

void Model::Import(std::string path)
{
    Assimp::Importer import;
    const aiScene* scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

    if (!scene or scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE or !scene->mRootNode)
    {
        std::cout << "ASSIMP ERROR: " << import.GetErrorString() << std::endl;
        return;
    }
    directory = path.substr(0, path.find_last_of('/'));

    ProcessNode(scene->mRootNode, scene);
}

void Model::Draw(GLuint shaderID, const char* modelUni, const char* colorUni, glm::vec3 position, glm::vec3 color)
{
	for (GLuint i = 0; i < meshes.size(); i++)
		meshes[i].Draw(shaderID, modelUni, colorUni, position, color);
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
            if (std::strcmp(texturesLoaded[j].path, str.C_Str()) == 0)
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
            texture.type = typeName;
            texture.path = str.C_Str();

            textures.push_back(texture);
            texturesLoaded.push_back(texture); // add to loaded textures
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
    if (mesh->mMaterialIndex >= 0)
    {
        if (mesh->mMaterialIndex >= 0)
        {
            aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

            std::vector<TextureStruct> diffuseMaps = LoadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
            textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

            std::vector<TextureStruct> specularMaps = LoadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
            textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
        }
    }

    Mesh meshObj;
    return meshObj.CreateBuffers(vertices, indices, textures);
}

void Model::ProcessNode(aiNode* node, const aiScene* scene)
{
    // process all the node's meshes (if any)
    for (unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(ProcessMesh(mesh, scene));
    }
    // then do the same for each of its children
    for (unsigned int i = 0; i < node->mNumChildren; i++)
    {
        ProcessNode(node->mChildren[i], scene);
    }
}