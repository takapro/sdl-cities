#pragma once
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

class Game {
public:
    static constexpr const char* WINDOW_TITLE = "World Cities (CMPT 1267 Project 3)";

    static constexpr int SCREEN_WIDTH = 1024;
    static constexpr int SCREEN_HEIGHT = 768;

    ~Game();

    bool Initialize();
    void RunLoop();

protected:
    void ProcessInput();
    void UpdateGame();

    virtual void ProcessSpaceKey() = 0;
    virtual void ProcessKeyboard(const Uint8* state) = 0;
    virtual void UpdateGame(float deltaTime) = 0;
    virtual void GenerateOutput() = 0;

    SDL_Window* window;
    SDL_GLContext context;

    bool isRunning;
    int ticksCount;
};
