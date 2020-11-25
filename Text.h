#pragma once
#include "VertexArray.h"
#include "Shader.h"
#include <SDL2/SDL_ttf.h>

class Text {
public:
    Text() : textureId(0) {};
    ~Text();

    void Init(TTF_Font* font, VertexArray* vertexArray, Vector2d screenSize, Vector2d position);

    void SetText(const char* text);
    void Render(Shader& shader);

private:
    TTF_Font* font;
    VertexArray* vertexArray;
    Vector2d screenSize;
    Vector2d position;

    unsigned int textureId;
    Matrix4d matrix;
};
