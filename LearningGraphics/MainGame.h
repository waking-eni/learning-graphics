#pragma once
#include <SDL/SDL.h>
#include <GL/glew.h>

#include "Sprite.h"
#include "GLSLProgram.h"

enum class GameState { PLAY, EXIT };

class MainGame
{
public:
	MainGame();
	virtual ~MainGame();

	void run();

protected:

private:
	SDL_Window* _window;
	int _screenWidth;
	int _screenHeight;
	GameState _gameState;
	Sprite _sprite;
	GLSLProgram _colorProgram;

	void initSystems();
	void initShaders();
	void gameLoop();
	void processInput();
	void drawGame();
};