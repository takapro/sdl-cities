#pragma once
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

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

	bool isRunning;
	int ticksCount;
};
