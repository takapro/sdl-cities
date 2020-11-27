#include "Text.h"

Text::~Text()
{
    glDeleteTextures(1, &textureId);
}

void Text::Init(TTF_Font* font, VertexArray* vertexArray, Vector2d screenSize, Vector2d position)
{
    this->font = font;
    this->vertexArray = vertexArray;
    this->screenSize = screenSize;
    this->position = position;

    glGenTextures(1, &textureId);
}

void Text::SetText(const char* text)
{
    SDL_Color color = { 255, 255, 255, 255 };
    SDL_Surface* surface = TTF_RenderUTF8_Blended(font, text, color);
    int width = surface->w;
    int height = surface->h;

    glBindTexture(GL_TEXTURE_2D, textureId);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, surface->pixels);
    SDL_FreeSurface(surface);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    matrix = Matrix4d::move({ position.x, position.y, 0.0f })
        * Matrix4d::scale({ width / screenSize.x, height / screenSize.y, 1.0f });
}

void Text::Render(Shader& shader)
{
    shader.SetWorldTransform(matrix);
    shader.SetViewProjection(Matrix4d::identity());
    glBindTexture(GL_TEXTURE_2D, textureId);
    vertexArray->Render();
}
