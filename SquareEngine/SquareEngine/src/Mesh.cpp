#include "Mesh.h"
#include <iostream>
// glad is included in Mesh.h
namespace Square
{
    Mesh::Mesh(float positions[], float textureCoords[], float normals[], int indices[], size_t positionsLength, size_t textureCoordsLength, size_t normalsLength, size_t indicesLength)
    {
        // Calculate the number of vertices based on the length of the positions array
        vertexCount = positionsLength;
        
        // Generate and bind VAO, VBOs, and EBO
        glGenVertexArrays(1, &VAO);
        glGenBuffers(3, VBOs);
        glGenBuffers(1, &EBO);

        glBindVertexArray(VAO);

        // Positions VBO
        glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
        glBufferData(GL_ARRAY_BUFFER, positionsLength * sizeof(float), positions, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        // Texture Coordinates VBO
        glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
        glBufferData(GL_ARRAY_BUFFER, textureCoordsLength * sizeof(float), textureCoords, GL_STATIC_DRAW);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(2);

        // Normals VBO
        glBindBuffer(GL_ARRAY_BUFFER, VBOs[2]);
        glBufferData(GL_ARRAY_BUFFER, normalsLength * sizeof(float), normals, GL_STATIC_DRAW);
        glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(3);

        // EBO
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesLength * sizeof(int), indices, GL_STATIC_DRAW);
    }

    void Mesh::Bind() const
    {
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
