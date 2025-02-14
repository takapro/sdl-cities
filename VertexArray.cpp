#include "VertexArray.h"
#include <GL/glew.h>

VertexArray::~VertexArray()
{
    glDeleteBuffers(1, &vertexBuffer);
    glDeleteBuffers(1, &indexBuffer);
    glDeleteVertexArrays(1, &vertexArray);
}

void VertexArray::Init(const float* verts, unsigned int numVerts, const unsigned int* indices, unsigned int numIndices)
{
    constexpr int stride = 5;

    this->numVerts = numVerts;
    this->numIndices = numIndices;

    glGenVertexArrays(1, &vertexArray);
    glBindVertexArray(vertexArray);

    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * numVerts * stride, verts, GL_STATIC_DRAW);

    glGenBuffers(1, &indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * numIndices, indices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * stride, 0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * stride, reinterpret_cast<void*>(sizeof(float) * 3));
}

void VertexArray::InitSquare()
{
    float vertices[] = {
        -1.0f,  1.0f,  0.0f,  0.0f,  0.0f,
         1.0f,  1.0f,  0.0f,  1.0f,  0.0f,
         1.0f, -1.0f,  0.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  0.0f,  0.0f,  1.0f,
    };
    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0,
    };

    Init(vertices, 4, indices, 6);
}

void VertexArray::Render()
{
    glBindVertexArray(vertexArray);
    glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, nullptr);
}
