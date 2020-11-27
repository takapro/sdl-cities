#include "Actor.h"

void Actor::InitCity()
{
    float vertices[30] = {
         0.0f,  0.0f,  0.8f,  0.0f,  0.0f,
         0.0f,  0.8f,  0.0f,  0.0f,  0.0f,
         0.8f,  0.0f,  0.0f,  0.0f,  0.0f,
         0.0f, -0.8f,  0.0f,  0.0f,  0.0f,
        -0.8f,  0.0f,  0.0f,  0.0f,  0.0f,
    };
    unsigned int indices[] = {
        0, 1, 2,
        0, 2, 3,
        0, 3, 4,
        0, 4, 1,
    };

    texture.InitRGBA(255, 0, 0, 255);
    vertexArray.Init(vertices, 5, indices, 12);
    distance = 1.0001f;
}

void Actor::InitShip()
{
    float vertices[] = {
         0.0f,  0.5f,  0.0f,  0.0f,  0.0f,
         0.3f, -0.5f,  0.0f,  0.0f,  0.0f,
        -0.3f, -0.5f,  0.0f,  0.0f,  0.0f,
    };
    unsigned int indices[] = {
        0, 1, 2,
    };

    texture.InitRGBA(255, 255, 0, 255);
    vertexArray.Init(vertices, 3, indices, 3);
    distance = 1.0002f;
}

void Actor::SetPosition(Vector3d position, Vector3d direction)
{
    Vector3d side = cross(position, direction);
    Matrix4d rotation = {
        side.x, direction.x, position.x, 0,
        side.y, direction.y, position.y, 0,
        side.z, direction.z, position.z, 0,
        0, 0, 0, 1,
    };
    matrix = Matrix4d::move(distance * position) * Matrix4d::scale(0.01f) * rotation;
}

void Actor::Render(Shader& shader)
{
    shader.SetWorldTransform(matrix);
    texture.SetActive();
    vertexArray.Render();
}
