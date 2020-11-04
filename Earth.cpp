#include "Earth.h"
#include <GL/glew.h>

bool Earth::Init()
{
    if (!LoadTextures()) {
        return false;
    }
    InitVertexes();
    return true;
}

bool Earth::LoadTextures()
{
    const char* fileNames[] = {
        "earth-a1.png", "earth-a2.png", "earth-a3.png", "earth-a4.png",
        "earth-b1.png", "earth-b2.png", "earth-b3.png", "earth-b4.png",
    };

    for (int i = 0; i < NUM_FACES; ++i) {
        if (!textures[i].Load(fileNames[i])) {
            return false;
        }
    }
    return true;
}

void Earth::InitVertexes()
{
    float vertBuffers[NUM_FACES][15] = {
        {
             0.0f,  0.5f,  0.0f,  0.5f,  0.0f,
             0.0f,  0.0f, -0.5f,  1.0f,  1.0f,
            -0.5f,  0.0f,  0.0f,  0.0f,  1.0f,
        },
        {
             0.0f,  0.5f,  0.0f,  0.5f,  0.0f,
             0.5f,  0.0f,  0.0f,  1.0f,  1.0f,
             0.0f,  0.0f, -0.5f,  0.0f,  1.0f,
        },
        {
             0.0f,  0.5f,  0.0f,  0.5f,  0.0f,
             0.0f,  0.0f,  0.5f,  1.0f,  1.0f,
             0.5f,  0.0f,  0.0f,  0.0f,  1.0f,
        },
        {
             0.0f,  0.5f,  0.0f,  0.5f,  0.0f,
            -0.5f,  0.0f,  0.0f,  1.0f,  1.0f,
             0.0f,  0.0f,  0.5f,  0.0f,  1.0f,
        },
        {
            -0.5f,  0.0f,  0.0f,  0.0f,  0.0f,
             0.0f,  0.0f, -0.5f,  1.0f,  0.0f,
             0.0f, -0.5f,  0.0f,  0.5f,  1.0f,
        },
        {
             0.0f,  0.0f, -0.5f,  0.0f,  0.0f,
             0.5f,  0.0f,  0.0f,  1.0f,  0.0f,
             0.0f, -0.5f,  0.0f,  0.5f,  1.0f,
        },
        {
             0.5f,  0.0f,  0.0f,  0.0f,  0.0f,
             0.0f,  0.0f,  0.5f,  1.0f,  0.0f,
             0.0f, -0.5f,  0.0f,  0.5f,  1.0f,
        },
        {
             0.0f,  0.0f,  0.5f,  0.0f,  0.0f,
            -0.5f,  0.0f,  0.0f,  1.0f,  0.0f,
             0.0f, -0.5f,  0.0f,  0.5f,  1.0f,
        },
    };
    unsigned int indexBuffer[] = {
        0, 1, 2,
    };

    for (int i = 0; i < NUM_FACES; ++i) {
        vertexArrays[i].Init(true, vertBuffers[i], 3, indexBuffer, 3);
    }
}

void Earth::Render()
{
    for (int i = 0; i < NUM_FACES; ++i) {
        textures[i].SetActive();
        vertexArrays[i].SetActive();
        glDrawElements(GL_TRIANGLES, vertexArrays[i].GetNumIndices(), GL_UNSIGNED_INT, nullptr);
    }
}
