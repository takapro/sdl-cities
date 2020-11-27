#pragma once
#include "Game.h"
#include "Shader.h"
#include "Viewport.h"
#include "Earth.h"
#include "Actor.h"
#include "Text.h"

class CitiesGame : public Game {
public:
    static constexpr float EARTH_RADIUS = 6371.0f;

    ~CitiesGame();

    bool Initialize();

private:
    void ResetDestination();
    void ProcessKeyboard(const Uint8* state);
    void UpdateGame(float deltaTime);
    void GenerateOutput();

    Shader shader;
    Viewport viewport;
    Earth earth;

    Actor cityActor;
    Actor shipActor;

    TTF_Font* largeFont;
    TTF_Font* smallFont;
    VertexArray textVertexArray;

    Text cityText;
    Text countryText;
    Text distanceText;
    Vector3d destination;

    int move;
    int turn;
    Vector3d position;
    Vector3d direction;
};
