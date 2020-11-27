#include "Actor.h"

void Actor::InitCity()
{
    float vertices[50];
    unsigned int indices[] = {
        0, 9, 6,
        1, 5, 7,
        2, 6, 8,
        3, 7, 9,
        4, 8, 5,
    };

    for (int i = 0; i < 5; ++i) {
        Vector2d vec = Vector2d::rotate2d(static_cast<float>(M_PI) * i * 2 / 5);

        vertices[i * 5 + 0] = vec.y;
        vertices[i * 5 + 1] = vec.x;
        vertices[i * 5 + 2] = 0.0f;
        vertices[i * 5 + 3] = 0.0f;
        vertices[i * 5 + 4] = 0.0f;

        vertices[(i + 5) * 5 + 0] = -0.38f * vec.y;
        vertices[(i + 5) * 5 + 1] = -0.38f * vec.x;
        vertices[(i + 5) * 5 + 2] = 0.0f;
        vertices[(i + 5) * 5 + 3] = 0.0f;
        vertices[(i + 5) * 5 + 4] = 0.0f;
    }

    texture.InitRGBA(255, 0, 0, 255);
    vertexArray.Init(vertices, 10, indices, 15);
    distance = 1.0001f;

    matrix = Matrix4d::scale(0.0f);
}

void Actor::InitShip()
{
    float vertices[] = {
         0.0f,  0.5f,  0.0f,  0.0f,  0.0f,
         0.3f, -0.5f,  0.0f,  1.0f,  1.0f,
        -0.3f, -0.5f,  0.0f,  0.0f,  1.0f,
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
