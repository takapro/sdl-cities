#include "Game.h"

bool Game::Initialize()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return false;
    }

    if (TTF_Init() != 0) {
        SDL_Log("Unable to initialize TTF: %s", TTF_GetError());
        return false;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

    window = SDL_CreateWindow(WINDOW_TITLE,
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT,
        SDL_WINDOW_OPENGL);
    if (!window) {
        SDL_Log("Failed to create window: %s", SDL_GetError());
        return false;
    }

    context = SDL_GL_CreateContext(window);
    if (!context) {
        SDL_Log("Failed to create context: %s", SDL_GetError());
        return false;
    }

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        SDL_Log("Failed to initialize glew");
        return false;
    }
    glGetError();

    if (!shader.Load("sprite.vert", "sprite.frag")) {
        return false;
    }

    viewport.Perspective(deg2rad(45.0f), (float) SCREEN_WIDTH / SCREEN_HEIGHT, 0.1f, 100.0f);

    if (!earth.Load()) {
        return false;
    }

    largeFont = TTF_OpenFont("Font/Good Things.ttf", 128);
    if (!largeFont) {
        SDL_Log("Failed to load font: %s", TTF_GetError());
        return false;
    }

    textVertexArray.InitSquare();
    destinationText.Init(largeFont, &textVertexArray, { SCREEN_WIDTH, SCREEN_HEIGHT }, { 0.0f, 0.5f });
    destinationText.SetText("Hello, World!");

    isRunning = true;
    ticksCount = SDL_GetTicks();

    position = { 0.0f, 0.0f, 1.0f };
    direction = { 0.0f, 1.0f, 0.0f };

    return true;
}

void Game::RunLoop()
{
    while (isRunning) {
        ProcessInput();
        UpdateGame();
        GenerateOutput();
    }
}

void Game::ProcessInput()
{
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                isRunning = false;
                break;
        }
    }

    const Uint8* state = SDL_GetKeyboardState(NULL);
    if (state[SDL_SCANCODE_ESCAPE]) {
        isRunning = false;
    }

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

void Game::UpdateGame()
{
    while (!SDL_TICKS_PASSED(SDL_GetTicks(), ticksCount + 16)) {
    }

    float deltaTime = (SDL_GetTicks() - ticksCount) / 1000.0f;
    if (deltaTime > 0.05f) {
        deltaTime = 0.05f;
    }
    ticksCount = SDL_GetTicks();

    if (turn != 0) {
        direction = direction.rotated(position, deg2rad(30.0f * deltaTime * turn)).normalized();
    }
    if (move != 0) {
        Vector3d side = cross(position, direction).normalized();
        position = position.rotated(side, deg2rad(10.0f * deltaTime * move)).normalized();
        direction = cross(side, position).normalized();
    }
    viewport.LookAt(1.1f * position - 0.15f * direction, direction - 0.4f * position, position);
}

void Game::GenerateOutput()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glEnable(GL_DEPTH_TEST);
    glDisable(GL_BLEND);

    shader.SetActive();
    shader.SetViewProjection(viewport.GetViewProjection());
    earth.Render(shader);

    glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    destinationText.Render(shader);

    SDL_GL_SwapWindow(window);
}

void Game::Shutdown()
{
    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
