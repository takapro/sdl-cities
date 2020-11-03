#pragma once
#include <SOIL/SOIL.h>

class Texture {
public:
    Texture() : textureId(0) {};
    ~Texture();

    bool Load(const char* fileName);

    void SetActive();

    int GetWidth() const { return width; }
    int GetHeight() const { return height; }

private:
    unsigned int textureId;
    int width;
    int height;
};
