#pragma once
#include "Shader.h"
#include "Texture.h"
#include "VertexArray.h"

class Earth {
public:
    static constexpr int NUM_HEMISPHERES = 2;
    static constexpr int FACES_PER_HEMISPHERES = 4;
    static constexpr int NUM_FACES = NUM_HEMISPHERES * FACES_PER_HEMISPHERES;

    bool Load();
    void Render(Shader* shader, float rotation);

private:
    bool LoadTextures();
    void LoadVertexes();

    Texture textures[NUM_FACES];
    VertexArray vertexArrays[NUM_HEMISPHERES];
};
