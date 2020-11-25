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

void Earth::LoadVertexes()
{
    for (int i = 0; i < NUM_HEMISPHERES; ++i) {
        GeodesicDome dome(i == 0, 5);
        dome.LoadVertexArray(vertexArrays[i], textures[0].GetWidth());
    }
}

void Earth::Render(Shader* shader)
{
    for (int i = 0; i < NUM_FACES; ++i) {
        shader->SetWorldTransform(Matrix4d::rotateY(deg2rad(90.0f * (i % FACES_PER_HEMISPHERES))));
        textures[i].SetActive();
        VertexArray& vertexArray = vertexArrays[i / FACES_PER_HEMISPHERES];
        vertexArray.SetActive();
        glDrawElements(GL_TRIANGLES, vertexArray.GetNumIndices(), GL_UNSIGNED_INT, nullptr);
    }
}
