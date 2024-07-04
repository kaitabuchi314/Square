#include "Texture2D.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace Square
{
    Texture2D loadTexture(const char* path)
    {
        unsigned int textureID;
        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_2D, textureID);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        int width, height, nrChannels;
        unsigned char* data = stbi_load(path, &width, &height, &nrChannels, 0);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
        {
            Square::Log("Failed to load texture");
        }
        stbi_image_free(data);
        return textureID;
    }

    void BindTexture(Texture2D t, int channel)
    {
        if (channel == 0)
            glActiveTexture(GL_TEXTURE0);
        else if (channel == 1)
            glActiveTexture(GL_TEXTURE1);
        else if (channel == 2)
            glActiveTexture(GL_TEXTURE2);

        glBindTexture(GL_TEXTURE_2D, t);
    }

    void UnbindTexture(Texture2D t)
    {
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}