#pragma once

class Texture {
public:
    ~Texture();

    bool Load(const char* fileName);
    void InitRGBA(unsigned char r, unsigned char g, unsigned char b, unsigned char a);

    void SetActive();

private:
    unsigned int textureId = 0;
};
