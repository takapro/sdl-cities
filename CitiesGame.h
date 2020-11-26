#pragma once
#include "Game.h"
#include "Shader.h"
#include "Viewport.h"
#include "Earth.h"
#include "VertexArray.h"
#include "Text.h"

class CitiesGame : public Game {
public:
    ~CitiesGame();

    bool Initialize();

private:
    void ProcessSpaceKey();
    void ProcessKeyboard(const Uint8* state);
    void UpdateGame(float deltaTime);
    void GenerateOutput();

    Shader shader;
    Viewport viewport;
    Earth earth;

    TTF_Font* largeFont;
    TTF_Font* smallFont;
    VertexArray textVertexArray;
    Text cityText;
    Text countryText;

    int move;
    int turn;
    Vector3d position;
    Vector3d direction;
};
