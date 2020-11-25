#pragma once
#include "Shader.h"
#include "Viewport.h"
#include "Earth.h"
#include "VertexArray.h"
#include "Text.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_ttf.h>

class Game {
public:
    static constexpr const char* WINDOW_TITLE = "SDL Game (3D)";

    static constexpr int SCREEN_WIDTH = 1024;
    static constexpr int SCREEN_HEIGHT = 768;

    bool Initialize();
    void RunLoop();
    void Shutdown();

private:
    void ProcessInput();
    void UpdateGame();
    void GenerateOutput();

    SDL_Window* window;
    SDL_GLContext context;

    Shader shader;
    Viewport viewport;
    Earth earth;

    TTF_Font* largeFont;
    VertexArray textVertexArray;
    Text destinationText;

    bool isRunning;
    int ticksCount;

    int move;
    int turn;
    Vector3d position;
    Vector3d direction;
};
