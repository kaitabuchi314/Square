#include "MeshLoader.h"
#include <fstream>
#include <stdexcept>
#include <vector>
#include <sstream>
#include <iostream>
#include <unordered_map>
#include <thread>
#include <future>
#include <functional>
#include <mutex>

namespace Square
{
    void loadAssimp(const std::string& path,
        std::vector<float>& vertices,
        std::vector<int>& indices,
        std::vector<float>& textureCoords,
        std::vector<float>& normals)
    {
        Assimp::Importer importer;

        // Load the mesh from file
        const aiScene* scene = importer.ReadFile(path,
            aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

        // Check if the import was successful
        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
        {
            Log(std::string("ERROR::ASSIMP::") + std::string(importer.GetErrorString()));
            return;
        }

        for (unsigned int i = 0; i < scene->mNumMeshes; ++i)
        {
            aiMesh* mesh = scene->mMeshes[i];
            loadSingleMesh(mesh, vertices, indices, textureCoords, normals);
        }
    }

    void loadSingleMesh(aiMesh* mesh, std::vector<float>& vertices, std::vector<int>& indices, std::vector<float>& textureCoords, std::vector<float>& normals)
    {
        // Debug information

        for (unsigned int i = 0; i < mesh->mNumVertices; i++)
        {
            vertices.push_back(mesh->mVertices[i].x);
            vertices.push_back(mesh->mVertices[i].y);
            vertices.push_back(mesh->mVertices[i].z);

            if (mesh->HasNormals())
            {
                normals.push_back(mesh->mNormals[i].x);
                normals.push_back(mesh->mNormals[i].y);
                normals.push_back(mesh->mNormals[i].z);
            }

            if (mesh->mTextureCoords[0])
            {
                textureCoords.push_back(mesh->mTextureCoords[0][i].x);
                textureCoords.push_back(mesh->mTextureCoords[0][i].y);
            }
            else
            {
                textureCoords.push_back(0.0f);
                textureCoords.push_back(0.0f);
            }
        }

        // Extract indices
        for (unsigned int i = 0; i < mesh->mNumFaces; i++)
        {
            aiFace face = mesh->mFaces[i];
            for (unsigned int j = 0; j < face.mNumIndices; j++)
            {
                indices.push_back(face.mIndices[j]);
            }
        }

        // Debug information
    }

    Mesh* loadMesh(const char* path)
    {
        std::vector<float> v;
        std::vector<int> i;
        std::vector<float> t;
        std::vector<float> n;

        // Load the mesh in a separate thread
        loadAssimp(path, v, i, t, n);

        Mesh* mesh = new Mesh(v.data(), t.data(), n.data(), i.data(), v.size(), t.size(), n.size(), i.size());

        Log(std::string("Square::MeshLoader:: Mesh ") + std::string(path) + " Loaded");
        return mesh;
    }
}
