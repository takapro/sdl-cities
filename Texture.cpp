#include "Texture.h"
#include <SDL2/SDL.h>
#include <GL/glew.h>

Texture::~Texture()
{
    glDeleteTextures(1, &textureId);
}

bool Texture::Load(const char* fileName)
{
    int channels = 0;
    unsigned char* image = SOIL_load_image(fileName, &width, &height, &channels, SOIL_LOAD_AUTO);
    if (image == nullptr) {
        SDL_Log("Failed to load texture %s", fileName);
        return false;
    }

    int format = GL_RGB;
    if (channels == 4) {
        format = GL_RGBA;
    }

    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, image);
    SOIL_free_image_data(image);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    return true;
}

void Texture::SetActive()
{
    glBindTexture(GL_TEXTURE_2D, textureId);
}
