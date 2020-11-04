#pragma once
#include "Texture.h"
#include "VertexArray.h"

class Earth {
public:
    static constexpr int NUM_FACES = 8;

    bool Init();
    void Render();

private:
    bool LoadTextures();
    void InitVertexes();

    Texture textures[NUM_FACES];
    VertexArray vertexArrays[NUM_FACES];
};
