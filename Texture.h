#pragma once

class Texture {
public:
    ~Texture();

    bool Load(const char* fileName);

    void SetActive();

private:
    unsigned int textureId = 0;
};
