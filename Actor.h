#pragma once
#include "Shader.h"
#include "Texture.h"
#include "VertexArray.h"

class Actor {
public:
    void InitCity();
    void InitShip();

    void SetPosition(Vector3d position, Vector3d direction);

    void Render(Shader& shader);

private:
    Texture texture;
    VertexArray vertexArray;
    float distance;

    Matrix4d matrix;
};
