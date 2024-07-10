#pragma once
#include <glad/glad.h>

namespace Square
{
    class Mesh
    {
    public:
        Mesh(float positions[], float textureCoords[], float normals[], int indices[], size_t positionsLength, size_t textureCoordsLength, size_t normalsLength, size_t indicesLength);

        void Bind() const;
        void Unbind() const;
        void Flush() const;

    public:
        unsigned int vertexCount;
    private:
        unsigned int VAO, VBOs[3], EBO;
    };
}