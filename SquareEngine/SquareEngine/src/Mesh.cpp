#include "Mesh.h"

namespace Square
{
    Mesh::Mesh(float positions[], float textureCoords[], float normals[], unsigned int indices[], size_t positionsLength, size_t textureCoordsLength, size_t normalsLength, size_t indicesLength)
    {
        vertexCount = positionsLength / 3;
        glGenVertexArrays(1, &VAO);
        glGenBuffers(3, VBOs);
        glGenBuffers(1, &EBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
        glBufferData(GL_ARRAY_BUFFER, positionsLength, positions, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
        glBufferData(GL_ARRAY_BUFFER, textureCoordsLength, textureCoords, GL_STATIC_DRAW);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(2);

        glBindBuffer(GL_ARRAY_BUFFER, VBOs[2]);
        glBufferData(GL_ARRAY_BUFFER, normalsLength, normals, GL_STATIC_DRAW);
        glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(3);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesLength, indices, GL_STATIC_DRAW);
    }

    void Mesh::Bind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, VBOs[2]);
        glBindVertexArray(VAO);
    }

    void Mesh::Unbind() const
    {
        glBindVertexArray(0);
    }

    void Mesh::Flush() const
    {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(3, VBOs);
        glDeleteBuffers(1, &EBO);
    }
}