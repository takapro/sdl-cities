#include "Earth.h"
#include "GeodesicDome.h"
#include <GL/glew.h>

bool Earth::Load()
{
    if (!LoadTextures()) {
        return false;
    }
    LoadVertexes();
    return true;
}

bool Earth::LoadTextures()
{
    const char* fileNames[] = {
        "Earth/earth-a1.png", "Earth/earth-a2.png", "Earth/earth-a3.png", "Earth/earth-a4.png",
        "Earth/earth-b1.png", "Earth/earth-b2.png", "Earth/earth-b3.png", "Earth/earth-b4.png",
    };

    for (int i = 0; i < NUM_FACES; ++i) {
        if (!textures[i].Load(fileNames[i])) {
            return false;
        }
    }
    return true;
}

void Earth::LoadVertexes()
{
    for (int i = 0; i < NUM_HEMISPHERES; ++i) {
        GeodesicDome dome(i == 0, 5);
        dome.LoadVertexArray(vertexArrays[i]);
    }
}

void Earth::Render(Shader& shader)
{
    for (int i = 0; i < NUM_FACES; ++i) {
        shader.SetWorldTransform(Matrix4d::rotateY(deg2rad(90.0f * (i % FACES_PER_HEMISPHERES))));
        textures[i].SetActive();
        vertexArrays[i / FACES_PER_HEMISPHERES].Render();
    }
}
