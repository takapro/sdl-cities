#include "CitiesGame.h"
#include "Cities.h"
#include <stdlib.h>

CitiesGame::~CitiesGame()
{
    TTF_CloseFont(largeFont);
    TTF_CloseFont(smallFont);
    TTF_Quit();
}

bool CitiesGame::Initialize()
{
    if (!Game::Initialize()) {
        return false;
    }

    if (TTF_Init() != 0) {
        SDL_Log("Unable to initialize TTF: %s", TTF_GetError());
        return false;
    }

    if (!shader.Load("Shader/sprite.vert", "Shader/sprite.frag")) {
        return false;
    }

    viewport.Perspective(deg2rad(45.0f), (float) SCREEN_WIDTH / SCREEN_HEIGHT, 0.1f, 100.0f);

    if (!earth.Load()) {
        return false;
    }

    cityActor.InitCity();
    shipActor.InitShip();

    largeFont = TTF_OpenFont("Font/Good Things.ttf", 112);
    if (!largeFont) {
        SDL_Log("Failed to load font: %s", TTF_GetError());
        return false;
    }

    smallFont = TTF_OpenFont("Font/Good Things.ttf", 56);
    if (!smallFont) {
        SDL_Log("Failed to load font: %s", TTF_GetError());
        return false;
    }

    textVertexArray.InitSquare();
    cityText.Init(largeFont, &textVertexArray, { SCREEN_WIDTH, SCREEN_HEIGHT }, { 0.0f, 0.56f });
    cityText.SetText("Hello, World!");
    countryText.Init(smallFont, &textVertexArray, { SCREEN_WIDTH, SCREEN_HEIGHT }, { 0.0f, 0.32f });
    countryText.SetText(" ");

    position = { 0.0f, 0.0f, 1.0f };
    direction = { 0.0f, 1.0f, 0.0f };

    return true;
}

void CitiesGame::ProcessSpaceKey()
{
    const City& city = City::cities[rand() % City::NUM_CITIES];
    cityText.SetText(city.name);
    countryText.SetText(city.country);
    position = Vector3d::rotate3d({ deg2rad(city.longitude + 180.0f), deg2rad(city.latitude) });
    direction = cross(cross(position, { 0.0f, 1.0f, 0.0f }), position).normalized();
    cityActor.SetPosition(position, direction);
}

void CitiesGame::ProcessKeyboard(const Uint8* state)
{
    move = 0;
    if (state[SDL_SCANCODE_UP]) {
        move = 1;
    } else if (state[SDL_SCANCODE_DOWN]) {
        move = -1;
    }

    turn = 0;
    if (state[SDL_SCANCODE_LEFT]) {
        turn = -1;
    } else if (state[SDL_SCANCODE_RIGHT]) {
        turn = 1;
    }
}

void CitiesGame::UpdateGame(float deltaTime)
{
    if (turn != 0) {
        direction = direction.rotated(position, deg2rad(30.0f * deltaTime * turn)).normalized();
    }
    if (move != 0) {
        Vector3d side = cross(position, direction).normalized();
        position = position.rotated(side, deg2rad(10.0f * deltaTime * move)).normalized();
        direction = cross(side, position).normalized();
    }
    viewport.LookAt(1.1f * position - 0.2f * direction, direction - 0.35f * position, position);
    shipActor.SetPosition(position, direction);
}

void CitiesGame::GenerateOutput()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glEnable(GL_DEPTH_TEST);
    glDisable(GL_BLEND);

    shader.SetActive();
    shader.SetViewProjection(viewport.GetViewProjection());
    earth.Render(shader);

    cityActor.Render(shader);
    shipActor.Render(shader);

    glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    cityText.Render(shader);
    countryText.Render(shader);

    SDL_GL_SwapWindow(window);
}
