#include "CitiesGame.h"
#include "Cities.h"
#include <stdlib.h>
#include <stdio.h>

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
    countryText.Init(smallFont, &textVertexArray, { SCREEN_WIDTH, SCREEN_HEIGHT }, { 0.0f, 0.32f });
    distanceText.Init(smallFont, &textVertexArray, { SCREEN_WIDTH, SCREEN_HEIGHT }, { 0.0f, 0.8f });
    ResetDestination();

    position = { 0.0f, 0.0f, 1.0f };
    direction = { 0.0f, 1.0f, 0.0f };

    cameraInput = 2;
    cameraDistance = 2.0f;

    return true;
}

void CitiesGame::ResetDestination()
{
    const City& city = City::cities[rand() % City::NUM_CITIES];
    cityText.SetText(city.name);
    countryText.SetText(city.country);
    destination = Vector3d::rotate3d({ deg2rad(city.longitude + 180.0f), deg2rad(city.latitude) });
    Vector3d direction = cross(cross(destination, { 0.0f, 1.0f, 0.0f }), destination).normalized();
    cityActor.SetPosition(destination, direction);
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

    if (cameraInput != 2) {
        cameraInput = 0;
    }
    if (state[SDL_SCANCODE_A]) {
        cameraInput = -1;
    } else if (state[SDL_SCANCODE_S]) {
        cameraInput = 2;
    } else if (state[SDL_SCANCODE_D]) {
        cameraInput = 1;
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

    if (cameraInput == 2) {
        if (cameraDistance < 1.0f) {
            cameraDistance = fminf(cameraDistance + deltaTime, 1.0f);
        } else if (cameraDistance > 1.0f) {
            cameraDistance = fmaxf(cameraDistance - deltaTime, 1.0f);
        }
    } else if (cameraInput != 0) {
        cameraDistance += cameraInput * deltaTime / 2;
    }

    viewport.LookAt(cameraDistance * (1.1f * position - 0.2f * direction),
        direction - (0.35f + 2 * (cameraDistance - 1.0f)) * position, position);
    shipActor.SetPosition(position, direction);

    int distance;
    while ((distance = static_cast<int>(2 * EARTH_RADIUS * asinf((destination - position).length() / 2))) < 100) {
        ResetDestination();
    }
    char distanceString[16];
    if (distance >= 1000) {
        snprintf(distanceString, sizeof distanceString, "%d,%03d km", distance / 1000, distance % 1000);
    } else {
        snprintf(distanceString, sizeof distanceString, "%d km", distance);
    }
    distanceText.SetText(distanceString);
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
    distanceText.Render(shader);

    SDL_GL_SwapWindow(window);
}
