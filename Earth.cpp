#include "Earth.h"
#include "GeodesicDome.h"
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
    SphericalTriangle tri[NUM_HEMISPHERES] = {
        { { 0, rightAngle }, { rightAngle, 0 }, { 0, 0 } },
        { { 0, 0 }, { rightAngle, 0 }, { 0, - rightAngle } },
    };

    for (int i = 0; i < NUM_HEMISPHERES; ++i) {
        GeodesicDome geom(i == 0);
        geom.calc(tri[i], 4);
        geom.initVertexArray(vertexArrays[i]);
    }
}

void Earth::Render(Shader* shader, float rotation)
{
    for (int i = 0; i < NUM_FACES; ++i) {
        shader->SetWorldTransform(rotation + 90.0f * (i % FACES_PER_HEMISPHERES));
        textures[i].SetActive();
        VertexArray& vertexArray = vertexArrays[i / FACES_PER_HEMISPHERES];
        vertexArray.SetActive();
        glDrawElements(GL_TRIANGLES, vertexArray.GetNumIndices(), GL_UNSIGNED_INT, nullptr);
    }
}
