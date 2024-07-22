#pragma once
#include <glad/glad.h>

#include <Debug.h>

namespace Square
{
    typedef unsigned int Texture2D;

    Texture2D loadTexture(const char* path);

    void BindTexture(Texture2D t, int channel);

    void UnbindTexture(Texture2D t);
}