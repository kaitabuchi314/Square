#pragma once
#include <Mesh.h>
#include <Debug.h>
#include <vector>
#include <iostream>
#include <thread>
#include <mutex>
#include <glm/glm.hpp>
#include <tinyxml2.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/version.h>

namespace Square
{
    inline std::mutex meshMutex;

    void loadAssimp(const std::string& path,
        std::vector<float>& vertices,
        std::vector<int>& indices,
        std::vector<float>& textureCoords,
        std::vector<float>& normals);

    void loadSingleMesh(aiMesh* mesh, std::vector<float>& vertices,
        std::vector<int>& indices,
        std::vector<float>& textureCoords,
        std::vector<float>& normals);

    Mesh* loadMesh(const char* path);
}

#include "MeshLoader.inl"