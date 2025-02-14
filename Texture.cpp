#include "Texture.h"
#include <SDL2/SDL.h>
#include <SOIL/SOIL.h>
#include <GL/glew.h>

Texture::~Texture()
{
    glDeleteTextures(1, &textureId);
}

bool Texture::Load(const char* fileName)
{
    int width, height, channels;
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
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    return true;
}

void Texture::InitRGBA(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
    unsigned char pixel[] = { r, g, b, a };

    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixel);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}

void Texture::SetActive()
{
    glBindTexture(GL_TEXTURE_2D, textureId);
}
