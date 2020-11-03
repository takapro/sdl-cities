#pragma once
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include "Shader.h"
#include "Texture.h"
#include "VertexArray.h"

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

	Shader* shader;
	Texture* texture;
	VertexArray* vertexArray;

	bool isRunning;
	int ticksCount;
};
